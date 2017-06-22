#include "H4lCutFlow/TruthHelper.h"

using namespace std;

// Constructor
TruthHelper::TruthHelper(EventContainer* eventcont)
{
    m_eventCont = eventcont;
}

// Destructor
TruthHelper::~TruthHelper()
{
    clearVars();
}

// Clearing the internal memory
void TruthHelper::clearVars()
{
    while(!m_partContainer.empty()) delete m_partContainer.back(), m_partContainer.pop_back();
    while(!m_diLepContainer.empty()) delete m_diLepContainer.back(), m_diLepContainer.pop_back();
    while(!m_quadContainer.empty()) delete m_quadContainer.back(), m_quadContainer.pop_back();

    m_partContainer.clear();
    m_diLepContainer.clear();
    m_quadContainer.clear();

    m_bareQuad = 0;
}

/////////////////////////////////////
// Reco Match Truth functions
/////////////////////////////////////

// gets the linked truth particle
// if it is a muon and truth link fails, it returns a match using dR match
// Only supported for muons and electorns
const xAOD::TruthParticle* TruthHelper::getTruthParticle(const xAOD::IParticle *in_p)
{
    const xAOD::TruthParticle *t = 0;

    const xAOD::IParticle *p = 0;
    if(in_p->type() == xAOD::Type::Electron)
    {
        p = in_p;
    }
    else if(in_p->type() == xAOD::Type::Muon)
    {
        const xAOD::Muon* mu = dynamic_cast<const xAOD::Muon*>(in_p);
        p = mu->primaryTrackParticle();
    }
    else
    {
        // return 0, if not a muon or electrons
        return t;
    }
    
    // find the linked particle
    if(p->isAvailable<ElementLink<xAOD::TruthParticleContainer> >("truthParticleLink")) {
        const auto &link = p->auxdata<ElementLink<xAOD::TruthParticleContainer> >("truthParticleLink");
        t = link.isValid() ? *link : 0;
    }

    // Hack for muons for muons
    if(!t)
    {
        t = getClosestTruthPart(in_p);
    }

    // Debugging
    if(t != 0)
    {
        //LOG(logDEBUG)<<"incoming pT: "<<in_p->pt()<<" eta: "<<in_p->eta()<<" phi: "<<in_p->phi();
        //LOG(logDEBUG)<<"Truth particle pT: "<<t->pt()<<" eta: "<<t->eta()<<" phi: "<<t->phi()<<" barcode: "<<t->barcode()<<" pdg ID: "<<t->pdgId();
    }

    return t;
}

// Helper function to calling getTruthParticle on a LepCombBase function
vector<const xAOD::TruthParticle*> TruthHelper::getTruthParticles(const LepCombBase* q)
{
    vector<const xAOD::TruthParticle*> ts;

    for(Int_t i = 0; i < q->getLepSize(); i++)
    {
        ts.push_back(getTruthParticle(q->getLep(i)->getParticle()));

    }

    return ts;
}

// Helper function to calling getTruthParticle on a ParticleQuadlepton and returning a ParticleQuadlepton
// with pairing matching the reco pairing
ParticleQuadlepton* TruthHelper::getTruthQuad(const ParticleQuadlepton* q)
{
    vector<const xAOD::TruthParticle*> ts = getTruthParticles(q);

    vector<ParticleVar*> ps;
    for(size_t i = 0; i < ts.size(); i++)
    {
        if(!ts[i]) return 0;
        // No index for now
        ParticleVar* particle = new ParticleVar(m_eventCont, ts[i], -1);
        m_partContainer.push_back(particle);
        ps.push_back(particle);
    }

    // we know the pairing from before
    ParticleDilepton* Z1temp = new ParticleDilepton(m_eventCont, ps[0], ps[1]);
    m_diLepContainer.push_back(Z1temp);
    ParticleDilepton* Z2temp = new ParticleDilepton(m_eventCont, ps[2], ps[3]);
    m_diLepContainer.push_back(Z2temp);

    // Pairing is done inside
    ParticleQuadlepton* quadTemp = new ParticleQuadlepton(m_eventCont, Z1temp, Z2temp);
    m_quadContainer.push_back(quadTemp);

    return quadTemp;
}

/////////////////////////////////////
// Reco Match Truth function
// but using leptons from Bosons
/////////////////////////////////////

// Returns truth matched leptons but only coming from boson
vector<const xAOD::TruthParticle*> TruthHelper::getRecoMatchTruth(const LepCombBase* q)
{
    //vector<const xAOD::TruthParticle*> lepFromBoson = getBareTruthFromBoson();

    auto lepFromBoson = getBareLeptonsFromBoson();

    // replace the taus
    for(size_t i = 0; i < lepFromBoson.size(); i++)
    {
        const xAOD::TruthParticle* truthPart = lepFromBoson[i];
        if(lepFromBoson[i]->isTau())
        {
            truthPart = getTauLeptonChild(lepFromBoson[i]);
        }
        lepFromBoson[i] = truthPart;
    }


    // Debug
    for(size_t i = 0; i < lepFromBoson.size(); i++)
    {
        if(!lepFromBoson[i]) continue;
        LOG(logDEBUG)<<"Particle from boson: pT "<<lepFromBoson[i]->pt()<<" eta: "<<lepFromBoson[i]->eta()<<" phi: "<<lepFromBoson[i]->phi()<<" PDGID: "<<lepFromBoson[i]->pdgId();
    }
    vector<const xAOD::TruthParticle*> recoMatchedTruth;

    for(int i = 0; i < q->getLepSize(); i++)
    {
        // Assume the intiall the truth particle is not matched
        const xAOD::TruthParticle* tempTruth = 0;

        // Do a barcode match, which in our case is the same as getting the truth particle link
        tempTruth = TruthHelper::getTruthParticle(q->getLep(i)->getParticle());
        
        // First check if this tempTruth particle is one of the particles from the boson list
        // if not, this is considered a HSG2 fake
        if(std::find(lepFromBoson.begin(), lepFromBoson.end(), tempTruth)==lepFromBoson.end())
        {
            tempTruth = 0;
        }

        // Now if the particle wasn't found either due to no truth link or not being a lep from boson,
        // try to do a DeltaR match
        if(tempTruth == 0) tempTruth = getClosestTruthPart(q->getLep(i)->getParticle(), lepFromBoson);

        LOG(logDEBUG)<<"Reco pT: "<<q->getLep(i)->getParticle()->pt();
        if(tempTruth) LOG(logDEBUG)<<" truth pT: "<<tempTruth->pt();

        // remove the matched lepton
        lepFromBoson.erase(std::remove(lepFromBoson.begin(), lepFromBoson.end(), tempTruth), lepFromBoson.end());
        


        recoMatchedTruth.push_back(tempTruth);
    }

    return recoMatchedTruth;
}

// Helper for function above.. mostly used for reco match truth ... need to check if it can be replaced
vector<const xAOD::TruthParticle*> TruthHelper::getBareTruthFromBoson()
{
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    vector<const xAOD::TruthParticle*> partCont;
    
    // Dump of the information
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
         t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        
        // Continue if not the Z or a W
        // Not quite sure how the truth is organized for W.. Need to make sure this
        if(!truthPart->isZ() && !truthPart->isW()) continue;
        
        Bool_t isBareBornSameMother = checkBareBornSameMother(truthPart);
        
        // Loop over the the Z boson
        // Find the instances of the
        for(size_t i = 0; i < truthPart->nChildren(); i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            
            if(!child->isLepton()) continue;
            
            // This is a workaround for how the truth is organized in qq2ZZ samples
            // See the comment before the checkBareBornSameMother function
            if(isBareBornSameMother && child->status() == 3) continue;
            
            // get the corresponding bare leptons
            child = getBareLepton(child);
            
            partCont.push_back(child);
        }
    }
    
    // If any of the particles are taus replace them with leptons... sigh
    for(size_t i = 0; i < partCont.size(); i++)
    {
        const xAOD::TruthParticle* truthPart = partCont[i];
        if(partCont[i]->isTau())
        {
            truthPart = getTauLeptonChild(partCont[i]);
        }
        partCont[i] = truthPart;
    }
    
    
    // Clean the elements with 0
    for(Int_t i = 0; i < (Int_t) partCont.size(); i++)
    {
        if(!partCont[i])
        {
            partCont.erase(partCont.begin() + i);
            i--;
        }
    }
    
    return partCont;
}


/////////////////////////////////////
// Truth functions
/////////////////////////////////////


/////////////////////
// Bare truth from bosons
/////////////////////

// Gets the bare truth from the bosons
vector<const xAOD::TruthParticle*> TruthHelper::getBareLeptonsFromBoson()
{
    vector<const xAOD::TruthParticle*> bareLeptons;

    // Sherpa - making the world more complicated for you! (TM) 
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        std::vector<ParticleVar*> tps = getBareLeptonsFromBoson_Sherpa();
        for (ParticleVar* p : tps){
            bareLeptons.push_back(dynamic_cast<const xAOD::TruthParticle*>(p->getParticle()));
        }
        return bareLeptons;
    }

    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    // Dump of the information
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
            t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;

        // Continue if not the Z/W/HIggs
        if(!(truthPart->isZ() || truthPart->isW() || truthPart->isHiggs() || (truthPart->pdgId() == 21))) continue;

        size_t iEnd = truthPart->nChildren();
        // if it is a gluon, make sure that childs are atleast 2 leptons and a Z or 4 leptons
        if(truthPart->pdgId() == 21)
        {
            int ZCount = 0;
            int LeptonCount = 0;
            for(size_t i = 0; i < iEnd; i++)
            {
                const xAOD::TruthParticle* child = truthPart->child(i);
                if(!child) continue;
                if(child->isZ()) ZCount ++;
                if(child->isLepton()) LeptonCount ++;
            }
            //LOG(logINFO)<<"Looking at gluon: ZCount: "<<ZCount<<" leptonCount: "<<LeptonCount;
            if(!(ZCount == 1 && LeptonCount == 2) && !(LeptonCount == 4)) continue;

        }

        
        // If child is a WorZ continue, this can happen in a WH/ZH decay
        // Depends on what Feynman digram it is 
        if(truthPart->isZ() || truthPart->isW()) {
            bool isWZChildWZ = false;
            for(size_t i = 0; i < iEnd; i++)
            {
                const xAOD::TruthParticle* child = truthPart->child(i);
                if(child->isZ() || child->isW()) {
                    isWZChildWZ = true;
                    break;
                }
            }
            if(isWZChildWZ) continue;
        }


        // Loop over the the Z or W or Higgs boson
        // Find the instances of the bare lepton
        for(size_t i = 0; i < iEnd; i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            if(!(child->isElectron() || child->isMuon() || child->isTau() )) continue;

            if(std::find(bareLeptons.begin(), bareLeptons.end(), child)!=bareLeptons.end()) continue;
            // get the corresponding bare leptons
            child = getBareLepton(child);
            //LOG(logDEBUG) << " bare lepton status : " << child->status() << " , pdgid: " << child->pdgId()  << " ,barcode: " << child->barcode() ;
            bareLeptons.push_back(child);
        }
    }

    return bareLeptons;
}

// Sherpa specfic bare leptons from Boson
std::vector<ParticleVar*> TruthHelper::getBareLeptonsFromBoson_Sherpa(){
    LOG(logDEBUG)<<"running getBareLeptonsFromBoson_Sherpa: ";
    // book output container
    vector<ParticleVar*> tempCont;
    // More Sherpa-specific behavior...
    // The transition from status 11 to 1 is a 4->4 vertex
    // For tau channels, it can also combine 2->2 and 4->4 vertices
    // getBareLepton can not cope with this ambiguity and will end up selecting
    // the same lepton multiple times for 4l final states.
    // So we use a different approach to collect all unique status 1 leptons from the chain
    std::set<const xAOD::TruthParticle*> LeptonsSet;
    
    std::set<const xAOD::TruthParticle*> TestedLeptonsSet;
    
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    for (const xAOD::TruthParticle* aux : *truthCont){
        // When picking up the bare leptons, we want the children of status 11 leptons at the vertex
        if ((aux->isLepton() && !aux->isNeutrino()) && aux->status() == 11){
            //LOG(logDEBUG)<<"Getting leptons";
            collectStableChildren_Sherpa(aux, LeptonsSet,TestedLeptonsSet);
        }
    }
            //LOG(logDEBUG)<<"done Getting leptons";
    
    // now we move our objects into a vector and sort them by decreasing pt
    std::vector<const xAOD::TruthParticle*> auxLepV (LeptonsSet.begin(), LeptonsSet.end());
    std::sort (auxLepV.begin(),auxLepV.end(),
               [&](const xAOD::TruthParticle* p1, const xAOD::TruthParticle* p2){
                   return (p1->pt() > p2->pt());
               });
    
    // finally, we can package them into ParticleVars
    for (const xAOD::TruthParticle* TP : auxLepV){
        ParticleVar* particle = new ParticleVar(m_eventCont, TP, -1);
        m_partContainer.push_back(particle);
        tempCont.push_back(particle);
    }
    
    return tempCont;
}

// Helper for above
void TruthHelper::collectStableChildren_Sherpa(const xAOD::TruthParticle* part, std::set<const xAOD::TruthParticle*> & collection, std::set<const xAOD::TruthParticle*> testedParticle)
{

    testedParticle.insert(part);
    // nullptr protection.
    if (!part) return;
    
    // if part is a stable lepton, insert it into our set
    if (part->isLepton() && (part->status() == 1 || (abs(part->pdgId()) == 15 && part->status() == 2))){
        collection.insert(part);
        return; // we reached a stable particle. Don't want to go further (tau decays...)
    }
    // If we did not yet reach a stable particle, recursively check the children
    // (if there are any)
    else {
        for (size_t ic = 0; ic < part->nChildren();++ic)  
        {
            if(!part->child(ic)) continue;
           if(testedParticle.find(part->child(ic)) == testedParticle.end() && (part->child(ic)->isLepton() && !part->child(ic)->isNeutrino()))
                collectStableChildren_Sherpa(part->child(ic), collection, testedParticle);
        }
    }
}

// Helper to convert from TruthParicle to ParticleVar
vector<ParticleVar*> TruthHelper::getBareParticleVarFromBoson()
{
    // Sherpa - making the world more complicated for you! (TM)
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        return getBareLeptonsFromBoson_Sherpa();
    }
    vector<const xAOD::TruthParticle*> bareLeptons = getBareLeptonsFromBoson();
    vector<ParticleVar*> bareParticleVar;
    for(size_t i = 0; i < bareLeptons.size(); i++) {
        ParticleVar* bareLepton = new ParticleVar(m_eventCont, bareLeptons[i], -1);
        m_partContainer.push_back(bareLepton);
        bareParticleVar.push_back(bareLepton);
    }
    return bareParticleVar;
}

/// Get the corresponding bare lepton for the input truth particle
const xAOD::TruthParticle* TruthHelper::getBareLepton(const xAOD::TruthParticle* in_p) const
{
    if(!in_p->isLepton())
    {
        LOG(logWARNING)<<"TruthHelper::getBareLepton() - Input is not a lepton";
        LOG(logWARNING)<<"No support for non lepton. returning 0";
        return 0;
    }
    
    // Assume that the current particle is bare
    const xAOD::TruthParticle* bareLep = in_p;
    while(bareLep)
    {
        // Require status 1 at the moment for el and muons
        if((bareLep->isMuon() || bareLep->isElectron()) && bareLep->status() == 1) return bareLep;
        
        // For tau require status 2, which is right before the decay
        if(bareLep->isTau() && (bareLep->status() == 2 || bareLep->status() == 10902)) return bareLep;
        
        // Otherwise start travelling down the child chain till we find the bare lepton
        Bool_t overWrite = false;
        for(size_t i = 0; i < bareLep->nChildren(); i++)
        {
            const xAOD::TruthParticle* child = bareLep->child(i);
            //// the tau lepton could decay into a muon or electron and not have status 2
            //// if it did not come from the Z's from the Higgs.
            //if (bareLep->isTau()) {
            //    if(!child->isLepton() || child->isNeutrino()) continue;
            //}
            //// If the child is not the sample PDG return
            //else {
            //    if(child->pdgId() != bareLep->pdgId()) continue;
            //}
            if(child->pdgId() != bareLep->pdgId()) continue;
            // Otherwise assume this is bare and retry the conditions
            overWrite = true; // to break the potential infinite loop
            bareLep = child;
            break;
        }
        
        if(!overWrite) bareLep = 0;
    }
    return in_p;
}

/////////////////////
// Born Truth from Boson
/////////////////////
vector<ParticleVar*> TruthHelper::getBornLeptonsFromBoson()
{
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        return getBornLeptonsFromBoson_Sherpa();
    }
    vector<const xAOD::TruthParticle*> bareLeptons = getBareLeptonsFromBoson();
    vector<ParticleVar*> bornLeptons = getBornLeptonsFromBareLeptons(bareLeptons);
    return bornLeptons;
}

std::vector<ParticleVar*> TruthHelper::getBornLeptonsFromBoson_Sherpa()
{
    
    vector<ParticleVar*> tempCont;
    
    // When picking up the born leptons, we want the status 11 leptons
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    for (const xAOD::TruthParticle* aux : *truthCont){
        if (aux->isLepton() && aux->status() == 11){
        //if (aux->isLepton() && aux->status() == 3){
            const xAOD::TruthParticle* born = aux;
            ParticleVar* particle = new ParticleVar(m_eventCont, born, -1);
            m_partContainer.push_back(particle);
            tempCont.push_back(particle);
        }
    }
    return tempCont;
    
}

/////////////////////
// Bare -> Born
/////////////////////
vector<ParticleVar*> TruthHelper::getBornLeptonsFromBareLeptons(vector<const xAOD::TruthParticle*> bareLeptons)
{
    vector<ParticleVar*> truthParticles;
    
    for (size_t i = 0; i < bareLeptons.size(); i++)
    {
        ParticleVar* bornLepton = 0;
        const xAOD::TruthParticle* child = bareLeptons[i];
        if(child != 0)
        {
            const xAOD::TruthParticle* bornChild = getBornLepton(child);
            
            if(bornChild != child)
            {
                bornLepton = new ParticleVar(m_eventCont, bornChild, -1);
                m_partContainer.push_back(bornLepton);
            }
            // if not status 3 lepton assign the old one
            if(!bornLepton)
            {
                bornLepton = new ParticleVar(m_eventCont, bareLeptons[i], -1);
                m_partContainer.push_back(bornLepton);
            }
            //LOG(logDEBUG) << " born lepton status : " << bornChild->status() << " , pdgid: " << bornChild->pdgId() ;
        }
        truthParticles.push_back(bornLepton);
    }
    return truthParticles;
}


/////////////////////
// Bare Quad
/////////////////////

// Wrapper around the different bareQuadlepton function
// calls the correct one based on what the generator is
ParticleQuadlepton* TruthHelper::getBareQuadlepton()
{
   
    //LOG(logDEBUG)<<"Getting bare quad";
    if(m_bareQuad) return m_bareQuad;
    
    if(m_eventCont->m_analType == AnalysisType::Fiducial) {
        // ttH samples
        if(m_eventCont->m_currGenerator == Generator::aMcAtNloHerwigppEvtGen){
            m_bareQuad = getBareQuadlepton_aMcAtNloHerwigpp_RecoPairing();
        }
        // Sherpa samples
        else if (m_eventCont->m_currGenerator == Generator::Sherpa){
            m_bareQuad = getBareQuadlepton_Sherpa();
        }
        else if (m_eventCont->sampleType == SampleType::Background || m_eventCont->m_currGenerator == Generator::MCFMPythia8 ){
            std::vector<ParticleVar*> leptons = getBareParticleVarFromBoson();
            m_bareQuad = RunPairing(leptons);
        }
        else {
            m_bareQuad = getBareQuadlepton_RecoPairing();
        }
    }
    else {
        // ggH, VBF, WH, ZH and PP8 qq2ZZ samples
        if(m_eventCont->m_currGenerator == Generator::PowhegPythia8 || m_eventCont->m_currGenerator == Generator::MCFMPythia8){
            LOG(logDEBUG)<<"Running bare: getBareQuadlepton_PowhegPythia8";

 	    m_bareQuad =  getBareQuadlepton_PowhegPythia8();
        }
        // ttH samples
        else if(m_eventCont->m_currGenerator == Generator::aMcAtNloHerwigppEvtGen){
            LOG(logDEBUG)<<"Running bare: getBareQuadlepton_aMcAtNloHerwigppEvtGen";
            
	    m_bareQuad = getBareQuadlepton_aMcAtNloHerwigppEvtGen();
        }
        // Sherpa samples
        else if (m_eventCont->m_currGenerator == Generator::Sherpa){
	    LOG(logDEBUG)<<"Running bare: getBareQuadlepton_Sherpa";
            m_bareQuad = getBareQuadlepton_Sherpa();
        }
        // default to powheg pythia case
        else {
            LOG(logDEBUG)<<"Running bare: getBareQuadlepton_PowhegPythia8";
            m_bareQuad =  getBareQuadlepton_PowhegPythia8();
        }
    }
    m_bareQuad = RunPairing(m_bareQuad);
    return m_bareQuad;
}

// Powheg Pythia samples 8
ParticleQuadlepton*  TruthHelper::getBareQuadlepton_PowhegPythia8()
{
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    vector<ParticleDilepton*> ZCandidates;
    
    // Dump of the information
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
         t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        
        // Continue if not the Z
        if(!truthPart->isZ()) continue;
        
        // Continue if the parent is not Higgs - but only if the sample is signal
        if(truthPart->parent() && m_eventCont->sampleType != SampleType::Background)
        {
            // If higgs is not the parent and If status is not 22, continue
            if(!truthPart->parent()->isHiggs() && !(truthPart->status() == 22)  && !(m_eventCont->m_currGenerator == Generator::MCFMPythia8 && truthPart->status() == 62)) continue;
        }
        // continue if the sample is a signal samples and the Z has no parent
        else if(m_eventCont->sampleType != SampleType::Background && !truthPart->parent()) continue;
        else
        {
            // If the parent doesn't exist, must be atleast status 62
            // Comes from the ZH and qq2ZZ samples
            if(!(truthPart->status() == 62)) continue;
        }
        
        // If child is a Z continue, this can happen in a ZH decay
        // Depends on what Feynman digram it is
        bool isZChildZ = false;
        size_t iEnd = truthPart->nChildren();
        for(size_t i = 0; i < iEnd; i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            if(child->isZ()) {
                isZChildZ = true;
                break;
            }
        }
        if(isZChildZ) continue;
        
        
        vector<ParticleVar*> tempCont;
        
        Bool_t isBareBornSameMother = checkBareBornSameMother(truthPart);
        
        // Loop over the the Z boson
        // Find the instances of the
        for(size_t i = 0; i < iEnd; i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            
            if(!child->isLepton()) continue;
            
            // This is a workaround for how the truth is organized in qq2ZZ samples
            // See the comment before the checkBareBornSameMother function
            if(isBareBornSameMother && child->status() == 3) continue;
            
            // get the corresponding bare leptons
            child = getBareLepton(child);
            
            // No index for now
            ParticleVar* particle = new ParticleVar(m_eventCont, child, -1);
            
            m_partContainer.push_back(particle);
            tempCont.push_back(particle);
        }
        
        if(tempCont.size() != 2)
        {
            //LOG(logWARNING)<<"TruthHelper::getBareQuadLepton() - Z has other than 2 decaying bare leptons";
            //LOG(logWARNING)<<"Size: "<<tempCont.size()<<" returning 0";
            //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
            //if(m_eventCont->isDebug){
            //    for(size_t i = 0; i < truthPart->nChildren(); i++)
            //    {
            //        const xAOD::TruthParticle* child = truthPart->child(i);
            //        cout<<"Z Child i: "<<i<<" PDGID: "<<child->pdgId()<<" status: "<<child->status()<<endl;
            //    }
            //}
            //return 0;
            continue;
        }
        ParticleDilepton* diLepTemp = 0;
        // Make the dilepton combination
        if(tempCont[0]->getCharge() > tempCont[1]->getCharge())
        {
            diLepTemp = new ParticleDilepton(m_eventCont, tempCont[0], tempCont[1]);
        }
        else
        {
            diLepTemp = new ParticleDilepton(m_eventCont, tempCont[1], tempCont[0]);
        }
        
        ZCandidates.push_back(diLepTemp);
        m_diLepContainer.push_back(diLepTemp);
    }
    
    
    if(ZCandidates.size() != 2)
    {
        //LOG(logWARNING)<<"TruthHelper::getBareQuadLepton() - There are other than 2 Z avaliable in this event";
        //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        //LOG(logWARNING)<<"Size: "<<ZCandidates.size()<<" returning 0";
        return 0;
    }
    
    // Pairing is done inside
    ParticleQuadlepton* quadTemp = new ParticleQuadlepton(m_eventCont, ZCandidates[0], ZCandidates[1]);
    m_quadContainer.push_back(quadTemp);
    if(m_eventCont->isDebug){
        LOG(logDEBUG)<<"Bare Quadlepton";
        quadTemp->printDebug();
    }
    // LOG(logDEBUG)<<"Bare Quadlepton";
    // quadTemp->printDebug();
    //    for (Int_t i = 0; i < quadTemp->getLepSize(); i++)
    //    {
    //        quadTemp->getLep(i)->printDebug();
    //    }
    
    return quadTemp;
    
}
// welcome to the wonderful world of Sherpa!
ParticleQuadlepton*  TruthHelper::getBareQuadlepton_Sherpa()
{
    std::vector <ParticleVar*> tempCont = getBareLeptonsFromBoson_Sherpa();
    
    // Now do a pairing.
    // There is no "true" Z / H in Sherpa,
    // so we do the analysis pairing
    ParticleQuadlepton* myQuad =  RunPairing(tempCont);
    return myQuad;
}

ParticleQuadlepton*  TruthHelper::getBareQuadlepton_RecoPairing()
{
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    // Get the higgs information formation
    const xAOD::TruthParticle* truthHiggs = 0;
    
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
         t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        
        // Continue if not the higgs
        if(!truthPart->isHiggs()) continue;
        
        bool isChildHiggs = false;
        // If the child is a Higgs continue
        for(size_t i = 0; i < truthPart->nChildren(); i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            if(child->isHiggs())
            {
                isChildHiggs = true;
                break;
            }
        }
        if(isChildHiggs) continue;
        
        if (truthPart->nChildren() < 2) continue;
        // We have our higgs
        truthHiggs = truthPart;
        LOG(logDEBUG)<<"born higgs PID: " << truthHiggs->pdgId() << " status: " << truthHiggs->status()  << " pt : " << truthHiggs->pt() << " eta: " << truthHiggs->eta() << " phi: " << truthHiggs->phi() << " children: " << truthHiggs->nChildren();
        for(size_t i = 0; i < truthHiggs->nChildren(); i++)
        {
            const xAOD::TruthParticle* child = truthHiggs->child(i);
            LOG(logDEBUG)<<" higgs child " << i << " is PID " << child->pdgId() << " and status " << child->status();
        }
        
    }
    if(!truthHiggs)
    {
        LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_RecoPairing() - Truth Higgs not found";
        LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        return 0;
    }
    
    // get the Z candidates
    vector<ParticleVar*> tempCont;
    tempCont.clear();
    for(size_t i = 0; i < truthHiggs->nChildren(); i++)
    {
        const xAOD::TruthParticle* Zchild = truthHiggs->child(i);
        
        if (!Zchild->isZ()) continue;
        
        // Desend the Z chain to get the Z right before decay
        while(true)
        {
            // Desend the chain
            if(Zchild->nChildren() == 1)
            {
                if(Zchild->child(0)->isZ())
                {
                    Zchild = Zchild->child(0);
                    continue;
                }
            }
            
            // if it comes here, then the childern must be lepton
            // otherwise there is some error
            bool isChildLep = false;
            for(size_t j = 0; j < Zchild->nChildren(); j++)
            {
                if(Zchild->child(j)->isLepton())
                {
                    isChildLep = true;
                    break;
                }
            }
            if(!isChildLep)
            {
                //LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - reached Z chain end";
                //LOG(logWARNING)<<"no leptons in Z child";
                //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
                //return 0;
                Zchild = 0;
                break;
            }
            break;
        }
        
        if(!Zchild) continue;
        
        // Find the leptons
        for(size_t j = 0; j < Zchild->nChildren(); j++)
        {
            const xAOD::TruthParticle* child = Zchild->child(j);
            
            if(!child->isLepton()) continue;
            
            // get the corresponding bare leptons
            child = getBareLepton(child);
            
            // No index for now
            ParticleVar* particle = new ParticleVar(m_eventCont, child, -1);
            
            m_partContainer.push_back(particle);
            tempCont.push_back(particle);
        }
    }
    //now look for the lepton children of the Higgs decay
    for(size_t i = 0; i < truthHiggs->nChildren(); i++)
    {
        const xAOD::TruthParticle* lepChild = truthHiggs->child(i);
        
        if(!lepChild->isLepton()) continue;
        // get the corresponding bare leptons
        lepChild = getBareLepton(lepChild);
        ParticleVar* particle = new ParticleVar(m_eventCont, lepChild, -1);
        m_partContainer.push_back(particle);
        tempCont.push_back(particle);
    }
    
    if(tempCont.size() != 4)
    {
        LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_RecoPairing() - Higgs has other than 4 decaying bare leptons.";
        LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        LOG(logWARNING)<<"Size: "<<tempCont.size()<<" returning 0";
        return 0;
    }
    
    // Pairing is done inside
    ParticleQuadlepton* quadTemp = RunPairing(tempCont);
    
    // LOG(logDEBUG)<<"Bare Quadlepton";
    // quadTemp->printDebug();
    //    for (Int_t i = 0; i < quadTemp->getLepSize(); i++)
    //    {
    //        quadTemp->getLep(i)->printDebug();
    //    }
    
    return quadTemp;
    
}
ParticleQuadlepton*  TruthHelper::getBareQuadlepton_aMcAtNloHerwigpp_RecoPairing()
{
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    // Get the higgs information formation
    const xAOD::TruthParticle* truthHiggs = 0;
    
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
         t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        
        // Continue if not the higgs
        if(!truthPart->isHiggs()) continue;
        
        bool isChildHiggs = false;
        // If the child is a Higgs continue
        for(size_t i = 0; i < truthPart->nChildren(); i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            if(child->isHiggs())
            {
                isChildHiggs = true;
                break;
            }
        }
        if(isChildHiggs) continue;
        
        // Continue if there are not 2 childern
        if(truthPart->nChildren() != 2) continue;
        // We have our higgs
        truthHiggs = truthPart;
    }
    if(!truthHiggs)
    {
        LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - Truth Higgs not found";
        LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        return 0;
    }
    
    // get the Z candidates
    vector<ParticleVar*> tempCont;
    tempCont.clear();
    for(size_t i = 0; i < truthHiggs->nChildren(); i++)
    {
        const xAOD::TruthParticle* Zchild = truthHiggs->child(i);
        
        // Desend the Z chain to get the Z right before decay
        while(true)
        {
            // Desend the chain
            if(Zchild->nChildren() == 1)
            {
                if(Zchild->child(0)->isZ())
                {
                    Zchild = Zchild->child(0);
                    continue;
                }
            }
            
            // if it comes here, then the childern must be lepton
            // otherwise there is some error
            bool isChildLep = false;
            for(size_t j = 0; j < Zchild->nChildren(); j++)
            {
                if(Zchild->child(j)->isLepton())
                {
                    isChildLep = true;
                    break;
                }
            }
            if(!isChildLep)
            {
                //LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - reached Z chain end";
                //LOG(logWARNING)<<"no leptons in Z child";
                //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
                //return 0;
                Zchild = 0;
                break;
            }
            break;
        }
        
        if(!Zchild) continue;
        
        // Find the leptons
        for(size_t j = 0; j < Zchild->nChildren(); j++)
        {
            const xAOD::TruthParticle* child = Zchild->child(j);
            
            if(!child->isLepton()) continue;
            
            // get the corresponding bare leptons
            child = getBareLepton(child);
            
            // No index for now
            ParticleVar* particle = new ParticleVar(m_eventCont, child, -1);
            
            m_partContainer.push_back(particle);
            tempCont.push_back(particle);
        }
        
    }
    
    // if couldn't find Z's by tracing the higgs, just look for two decaying Zs
    if(tempCont.size() != 4)
    {
        tempCont.clear();
        // Look for two decaying Z's
        for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
             t_itr != truthCont->end(); ++t_itr)
        {
            const xAOD::TruthParticle* truthPart = *t_itr;
            
            // Continue if not the higgs
            if(!truthPart->isZ()) continue;
            if(truthPart->nChildren() < 2) continue;
            
            bool isChildLep = false;
            for(size_t j = 0; j < truthPart->nChildren(); j++)
            {
                if(truthPart->child(j)->isLepton())
                {
                    isChildLep = true;
                    break;
                }
            }
            if(!isChildLep) continue;
            
            const xAOD::TruthParticle* Zchild = truthPart;
            
            // Find the leptons
            for(size_t j = 0; j < Zchild->nChildren(); j++)
            {
                const xAOD::TruthParticle* child = Zchild->child(j);
                
                if(!child->isLepton()) continue;
                
                // get the corresponding bare leptons
                child = getBareLepton(child);
                
                // No index for now
                ParticleVar* particle = new ParticleVar(m_eventCont, child, -1);
                
                m_partContainer.push_back(particle);
                tempCont.push_back(particle);
            }
        }
        
    }
    
    
    if(tempCont.size() != 4)
    {
        LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen_RecoPairing() - There are other than 4 Z bare leptons in this event";
        LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        LOG(logWARNING)<<"Size: "<< tempCont.size()<<" returning 0";
        return 0;
    }
    
    // Pairing is done inside
    ParticleQuadlepton* quadTemp = RunPairing(tempCont);
    
    // LOG(logDEBUG)<<"Bare Quadlepton";
    // quadTemp->printDebug();
    //    for (Int_t i = 0; i < quadTemp->getLepSize(); i++)
    //    {
    //        quadTemp->getLep(i)->printDebug();
    //    }
    
    return quadTemp;
    
}
// MC@NLO with Herwig, current ttH samples
ParticleQuadlepton*  TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen()
{
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    // Get the higgs information formation
    const xAOD::TruthParticle* truthHiggs = 0;
    
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
         t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        
        // Continue if not the higgs
        if(!truthPart->isHiggs()) continue;
        
        bool isChildHiggs = false;
        // If the child is a Higgs continue
        for(size_t i = 0; i < truthPart->nChildren(); i++)
        {
            const xAOD::TruthParticle* child = truthPart->child(i);
            if(child->isHiggs())
            {
                isChildHiggs = true;
                break;
            }
        }
        if(isChildHiggs) continue;
        
        // Continue if there are not 2 childern
        if(truthPart->nChildren() != 2) continue;
        // We have our higgs
        truthHiggs = truthPart;
    }
    if(!truthHiggs)
    {
        LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - Truth Higgs not found";
        LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        return 0;
    }
    
    // get the Z candidates
    vector<ParticleDilepton*> ZCandidates;
    for(size_t i = 0; i < truthHiggs->nChildren(); i++)
    {
        const xAOD::TruthParticle* Zchild = truthHiggs->child(i);
        
        // Desend the Z chain to get the Z right before decay
        while(true)
        {
            // Desend the chain
            if(Zchild->nChildren() == 1)
            {
                if(Zchild->child(0)->isZ())
                {
                    Zchild = Zchild->child(0);
                    continue;
                }
            }
            
            // if it comes here, then the childern must be lepton
            // otherwise there is some error
            bool isChildLep = false;
            for(size_t j = 0; j < Zchild->nChildren(); j++)
            {
                if(Zchild->child(j)->isLepton())
                {
                    isChildLep = true;
                    break;
                }
            }
            if(!isChildLep)
            {
                //LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - reached Z chain end";
                //LOG(logWARNING)<<"no leptons in Z child";
                //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
                //return 0;
                Zchild = 0;
                break;
            }
            break;
        }
        
        if(!Zchild) continue;
        
        vector<ParticleVar*> tempCont;
        tempCont.clear();
        
        // Find the leptons
        for(size_t j = 0; j < Zchild->nChildren(); j++)
        {
            const xAOD::TruthParticle* child = Zchild->child(j);
            
            if(!child->isLepton()) continue;
            
            // get the corresponding bare leptons
            child = getBareLepton(child);
            
            // No index for now
            ParticleVar* particle = new ParticleVar(m_eventCont, child, -1);
            
            m_partContainer.push_back(particle);
            tempCont.push_back(particle);
        }
        
        if(tempCont.size() != 2)
        {
            LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - Z has other than 2 decaying bare leptons";
            LOG(logWARNING)<<"Size: "<<tempCont.size()<<" returning 0";
            LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
            if(m_eventCont->isDebug){
                for(size_t k = 0; k < Zchild->nChildren(); k++)
                {
                    const xAOD::TruthParticle* child = Zchild->child(k);
                    cout<<"Z Child i: "<<k<<" PDGID: "<<child->pdgId()<<" status: "<<child->status()<<endl;
                }
            }
            //return 0;
            continue;
        }
        ParticleDilepton* diLepTemp = 0;
        // Make the dilepton combination
        if(tempCont[0]->getCharge() > tempCont[1]->getCharge())
        {
            diLepTemp = new ParticleDilepton(m_eventCont, tempCont[0], tempCont[1]);
        }
        else
        {
            diLepTemp = new ParticleDilepton(m_eventCont, tempCont[1], tempCont[0]);
        }
        
        ZCandidates.push_back(diLepTemp);
        m_diLepContainer.push_back(diLepTemp);
    }
    
    // if couldn't find Z's by tracing the higgs, just look for two decaying Zs
    if(ZCandidates.size() != 2)
    {
        ZCandidates.clear();
        // Look for two decaying Z's
        for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
             t_itr != truthCont->end(); ++t_itr)
        {
            const xAOD::TruthParticle* truthPart = *t_itr;
            
            // Continue if not the higgs
            if(!truthPart->isZ()) continue;
            if(truthPart->nChildren() < 2) continue;
            
            bool isChildLep = false;
            for(size_t j = 0; j < truthPart->nChildren(); j++)
            {
                if(truthPart->child(j)->isLepton())
                {
                    isChildLep = true;
                    break;
                }
            }
            if(!isChildLep) continue;
            
            const xAOD::TruthParticle* Zchild = truthPart;
            
            // Now create the Zlepton pair
            vector<ParticleVar*> tempCont;
            tempCont.clear();
            
            // Find the leptons
            for(size_t j = 0; j < Zchild->nChildren(); j++)
            {
                const xAOD::TruthParticle* child = Zchild->child(j);
                
                if(!child->isLepton()) continue;
                
                // get the corresponding bare leptons
                child = getBareLepton(child);
                
                // No index for now
                ParticleVar* particle = new ParticleVar(m_eventCont, child, -1);
                
                m_partContainer.push_back(particle);
                tempCont.push_back(particle);
            }
            
            if(tempCont.size() != 2)
            {
                LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - Z has other than 2 decaying bare leptons";
                LOG(logWARNING)<<"Size: "<<tempCont.size()<<" returning 0";
                LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
                return 0;
            }
            ParticleDilepton* diLepTemp = 0;
            // Make the dilepton combination
            if(tempCont[0]->getCharge() > tempCont[1]->getCharge())
            {
                diLepTemp = new ParticleDilepton(m_eventCont, tempCont[0], tempCont[1]);
            }
            else
            {
                diLepTemp = new ParticleDilepton(m_eventCont, tempCont[1], tempCont[0]);
            }
            
            ZCandidates.push_back(diLepTemp);
            m_diLepContainer.push_back(diLepTemp);
        }
        
    }
    
    
    if(ZCandidates.size() != 2)
    {
        LOG(logWARNING)<<"TruthHelper::getBareQuadlepton_aMcAtNloHerwigppEvtGen() - There are other than 2 Z avaliable in this event";
        LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        LOG(logWARNING)<<"Size: "<<ZCandidates.size()<<" returning 0";
        return 0;
    }
    
    // Pairing is done inside
    ParticleQuadlepton* quadTemp = new ParticleQuadlepton(m_eventCont, ZCandidates[0], ZCandidates[1]);
    m_quadContainer.push_back(quadTemp);
    
    // LOG(logDEBUG)<<"Bare Quadlepton";
    // quadTemp->printDebug();
    //    for (Int_t i = 0; i < quadTemp->getLepSize(); i++)
    //    {
    //        quadTemp->getLep(i)->printDebug();
    //    }
    
    return quadTemp;
    
}


/////////////////////
// Born Quad
/////////////////////

ParticleQuadlepton* TruthHelper::getBornQuadlepton(ParticleQuadlepton* quad)
{ 
    // For Sherpa, we need to do something different:
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        return getBornQuadlepton_Sherpa();
    }
    if(!quad) quad = getBareQuadlepton();
    if(!quad) return 0;
    

    if(!quad->isTruth())
    {
        LOG(logERROR)<<"TruthHelper::getBornQuadlepton() - Input quad is not truth type";
        exit(1);
    }
    
    vector<ParticleVar*> truthParticles;
    
    for (Int_t i = 0; i < quad->getLepSize(); i++)
    {
        const xAOD::TruthParticle* child = dynamic_cast<const xAOD::TruthParticle* >(quad->getLep(i)->getParticle());
        
        const xAOD::TruthParticle* bornChild = getBornLepton(child);
        
        ParticleVar* bornLepton = 0;
        
        if(bornChild != child)
        {
            bornLepton = new ParticleVar(m_eventCont, bornChild, -1);
            m_partContainer.push_back(bornLepton);
        }
        // if not born lepton assign the old one
        if(!bornLepton) bornLepton = quad->getLep(i);
        truthParticles.push_back(bornLepton);
        //LOG(logDEBUG)<<"born higgs lepton PDGID: " << bornLepton->getTruthPID() << " charge: " << bornLepton->getCharge()  << " pt : " << bornLepton->getTLV().Pt() << " eta: " << bornLepton->getTLV().Eta() << " phi: " << bornLepton->getTLV().Phi();
    }
    
    ParticleQuadlepton* quadTemp = 0;
    
    if(m_eventCont->m_analType == AnalysisType::Fiducial) 
    {
        quadTemp = RunPairing(truthParticles);
    }
    else 
    {
        // we know the pairing from before
        ParticleDilepton* Z1temp = new ParticleDilepton(m_eventCont, truthParticles[0], truthParticles[1]);
        m_diLepContainer.push_back(Z1temp);
        ParticleDilepton* Z2temp = new ParticleDilepton(m_eventCont, truthParticles[2], truthParticles[3]);
        m_diLepContainer.push_back(Z2temp);
        
        // Pairing is done inside
        quadTemp = new ParticleQuadlepton(m_eventCont, Z1temp, Z2temp, false);
        m_quadContainer.push_back(quadTemp);
    }
    
    //quadTemp = RunPairing(truthParticles);
    
    
    return quadTemp;
}


// welcome to the wonderful world of Sherpa!
ParticleQuadlepton*  TruthHelper::getBornQuadlepton_Sherpa()
{
    // start with the prompt born leptons
    std::vector <ParticleVar*> tempCont = getBornLeptonsFromBoson();
    // Now do a pairing.
    // There is no "true" Z / H in Sherpa,
    // so we do the analysis pairing
    ParticleQuadlepton* myQuad =  RunPairing(tempCont);
    return myQuad;
}


/// Get the corresponding born lepton for the input truth particle
const xAOD::TruthParticle* TruthHelper::getBornLepton(const xAOD::TruthParticle* in_p) const
{
    if(!in_p->isLepton())
    {
        LOG(logWARNING)<<"TruthHelper::getBornLepton() - Input is not a lepton";
        LOG(logWARNING)<<"No support for non lepton. returning 0";
        return 0;
    }
    
    // This is a workaround for the truth in different generators
    // In Higgs signal samples, the truth is arranged as H -> Z -> l(born)->...-> l(bare)
    // In qq2ZZ, the truth is arranged as H -> Z -> l(born) l(born) l(bare) l(bare), and so on
    
    Bool_t isBareBornSameMother = false;
    
    if(in_p->parent()->isZ())
    {
        isBareBornSameMother = checkBareBornSameMother(in_p->parent());
    }
    
    if(isBareBornSameMother) return getBornLeptonMother(in_p);
    
    return getBornLeptonTree(in_p);
    
}

/// Gets the born lepton for particles where the truth is arranged in a tree structure like l(born) -> l -> ... -> l(bare)
const xAOD::TruthParticle* TruthHelper::getBornLeptonTree(const xAOD::TruthParticle* in_p) const
{
    if(!in_p->isLepton())
    {
        LOG(logWARNING)<<"TruthHelper::getBornLepton() - Input is not a lepton";
        LOG(logWARNING)<<"No support for non lepton. returning 0";
        return 0;
    }
    
    // Assume that the current particle is born
    const xAOD::TruthParticle* bornLep = in_p;
    // comment from Max: breaks down for vertices with >1 parent
    while(bornLep)
    {
        // if status is 23, this is born
        if(bornLep->status() == 23) return bornLep;
        // If no parent is found, just break from the loop and return the incoming particle
        if(!bornLep->parent()) break;
        
        // If parent is Z, the current lepton is born
        if(bornLep->parent()->isZ() || bornLep->parent()->isW() || bornLep->parent()->isHiggs()) return bornLep;
        
        // Now if the parent is not the same PDGID, break
        // but allow to climb up to the taus
        if((bornLep->parent()->pdgId() != bornLep->pdgId())) break;
        //if((bornLep->parent()->pdgId() != bornLep->pdgId()) && !(bornLep->parent()->isTau())) break;
        
        // Otherwise, consider the parent to be born lep
        bornLep = bornLep->parent();
    }
    
    
    //LOG(logWARNING)<<"TruthHelper::getBornLepton() - couldn't find born leptons";
    //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
    //LOG(logWARNING)<<"returning the input";
    // No born was found, simply return the incoming particle
    return in_p;
}

/// Gets the born lepton where bare and born leptons have the same mother
const xAOD::TruthParticle* TruthHelper::getBornLeptonMother(const xAOD::TruthParticle* in_p) const
{
    if(!in_p->isLepton())
    {
        LOG(logWARNING)<<"TruthHelper::getBornLepton() - Input is not a lepton";
        LOG(logWARNING)<<"No support for non lepton. returning 0";
        return 0;
    }
    
    const xAOD::TruthParticle* mother = in_p->parent();
    
    // For speeding up
    size_t jEnd = mother->nChildren();
    for(size_t j = 0; j < jEnd; j++)
    {
        const xAOD::TruthParticle* brother = mother->child(j);
        
        // we don't want bares
        if(brother->status() == in_p->status()) continue;
        // We want the same type and charge of particle
        if(brother->pdgId() != in_p->pdgId()) continue;
        
        // Born iff status 3
        if(brother->status() != 3) continue;
        
        return brother;
    }
    
    // Born copy for inparent not found
    // This means there is no FSR (I believe) and in_p is both born and bare
    
    return in_p;
}

// This is a workaround for the truth in different generators
// In Higgs signal samples, the truth is arranged as H -> Z -> l(born)->...-> l(bare)
// In qq2ZZ, the truth is arranged as H -> Z -> l(born) l(born) l(bare) l(bare), and so on
Bool_t TruthHelper::checkBareBornSameMother(const xAOD::TruthParticle* in_p) const
{
    if(!in_p->isZ() && !in_p->isW())
    {
        LOG(logWARNING)<<"TruthHelper::checkBareBornSameMother() - Input is not a Z boson";
        LOG(logWARNING)<<"Returning false";
        return false;
    }
    
    Bool_t isChildBare = false;
    Bool_t isChildBorn = false;
    
    
    // For speeding up
    size_t iEnd = in_p->nChildren();
    for(size_t i = 0; i < iEnd; i++)
    {
        const xAOD::TruthParticle* child = in_p->child(i);
        if(!child->isLepton()) continue;
        
        if(child->status() == 1) isChildBare = true;
        if(child->status() == 3) isChildBorn = true;
    }
    
    
    return isChildBorn && isChildBare;
}



/////////////////////
// Dressed Quad
/////////////////////
ParticleQuadlepton* TruthHelper::getDressedQuadlepton(ParticleQuadlepton* quad)
{
    if(!quad) quad = getBareQuadlepton();
    if(!quad) return 0;
    
    if(!quad->isTruth())
    {
        LOG(logERROR)<<"TruthHelper::getDressedQuadlepton() - Input quad is not truth type";
        exit(1);
    }
    
    vector<ParticleVar*> truthParticles;
    vector<const xAOD::TruthParticle*> bareParticles;
    vector<const xAOD::TruthParticle*> photons = getPhotonsForDressing();
    
    for (Int_t i = 0; i < quad->getLepSize(); i++)
    {
        const xAOD::TruthParticle* child = dynamic_cast<const xAOD::TruthParticle* >(quad->getLep(i)->getParticle());
        bareParticles.push_back(child);
    }
    
    truthParticles = getDressedLeptonsVector(bareParticles,photons,0.1);
    
    ParticleQuadlepton* quadTemp = 0;
    if(m_eventCont->m_analType == AnalysisType::Fiducial) {
        quadTemp = RunPairing(truthParticles);
    }
    else {
        // we know the pairing from before
        ParticleDilepton* Z1temp = new ParticleDilepton(m_eventCont, truthParticles[0], truthParticles[1]);
        m_diLepContainer.push_back(Z1temp);
        ParticleDilepton* Z2temp = new ParticleDilepton(m_eventCont, truthParticles[2], truthParticles[3]);
        m_diLepContainer.push_back(Z2temp);
        
        // Pairing is done inside
        ParticleQuadlepton* quadTemp = new ParticleQuadlepton(m_eventCont, Z1temp, Z2temp);
        m_quadContainer.push_back(quadTemp);
    }
    return quadTemp;
}


/////////////////////
// Dressing
/////////////////////

vector<ParticleVar*> TruthHelper::getDressedLeptonsFromBoson()
{
    vector<const xAOD::TruthParticle*> bareLeptons = getBareLeptonsFromBoson();
    vector<ParticleVar*> dressedLeptons;
    if(m_eventCont->isDebug)
    { //compare cone photons with photons from actual decay
        LOG(logDEBUG) << "TruthHelper::getDressedLeptonsFromBoson() - Find dressed photons actually associated to bare leptons: ";
        for (size_t i = 0; i < bareLeptons.size(); i++) dressedLeptons.push_back(getDressedLepton(bareLeptons[i]));
        LOG(logDEBUG) << "TruthHelper::getDressedLeptonsFromBoson() - Done with debug of dressed leptons.";
    }
    vector<const xAOD::TruthParticle*> photonList = getPhotonsForDressing();
    dressedLeptons = getDressedLeptonsVector(bareLeptons,photonList,0.1);
    return dressedLeptons;
}

vector<const xAOD::TruthParticle*> TruthHelper::getPhotonsForDressing()
{
    vector<const xAOD::TruthParticle*> photonList;
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();

    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
            t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        //LOG(logDEBUG) << " particle status : " << truthPart->status() << " , pdgid: " << truthPart->pdgId() << " , barcode: " << truthPart->barcode() << " charge : " << truthPart->charge() <<" pt : " << truthPart->pt() << " eta: " << truthPart->eta() << " phi: " << truthPart->phi();

        // Continue if not photon
        if(!truthPart->isPhoton()) continue;
        if(truthPart->status() != 1) continue;
        if(truthPart->barcode() >= 200000) continue; // Particle is from a registered secondary
        //bool passCut = (truthPart->eta() < 2.37) && (truthPart->pt() > 20000.0);
        //if(!passCut) continue;
        bool hasHadronParent = false;
        const xAOD::TruthParticle* hadPar = truthPart;
        //LOG(logDEBUG) << "START PHOTON PARENT LOOP";
        while(hadPar)
        {
        //LOG(logDEBUG)<<"photon parent pid : " << hadPar->pdgId() << " status: " << hadPar->status() << " pt : " << hadPar->pt() << " eta: " << hadPar->eta() << " phi: " << hadPar->phi() << " barcode: " << hadPar->barcode();
           //give up if we reach the initial state particles 
           //
            // Max: Special sauce for Sherpa. If we reach a HS lepton FSR vertex, we know these guys are good to use and stop.
            // If we don't we will run into the hadron veto due to incoming showered partons in the HS vertex.  
            if (m_eventCont->m_currGenerator == Generator::Sherpa){
                const xAOD::TruthVertex* creationVx = hadPar->prodVtx();
                if (creationVx){
                    bool isHSLeptonFsr = true; 
                    for (auto in : creationVx->incomingParticleLinks()){
                        if (in.isValid() && *in){
                            const xAOD::TruthParticle* inP = *in; 
                            if (inP->status() != 11 || !inP->isLepton()){
                                isHSLeptonFsr = false;
                                break;
                            }
                        }
                    }
                    if (isHSLeptonFsr){
                        break;
                    }
                }
            }
           if (hadPar->isHadron() && hadPar->pt() < 1e-5 && hadPar->p4().Z() > 1000) break;
            // if status is 101 or 102, this is beam particle
            if(hadPar->isHadron() && !(hadPar->status()==101 || hadPar->status()==102)) hasHadronParent = true;
            //if(hadPar->isHadron()) hasHadronParent = true;
            // Now if the parent is a hadron
            if (hasHadronParent) break;
            // If no parent is found, just break from the loop
            if(!hadPar->parent()) break;
            // Otherwise, consider the parent to be a hadron
            hadPar = hadPar->parent();
        }
        //LOG(logDEBUG) << "END PHOTON PARENT LOOP";
        if(hasHadronParent) continue;

        photonList.push_back(truthPart);
        LOG(logDEBUG)<<"photon status: " << truthPart->status() << " pt : " << truthPart->pt() << " eta: " << truthPart->eta() << " phi: " << truthPart->phi();
    }
    LOG(logDEBUG)<<"size of photon vector: " << photonList.size();
    return photonList;

}

ParticleVar* TruthHelper::getDressedLepton(const xAOD::TruthParticle* in_p)
{
    //Will dress lepton with truth photons that actually come from the lepton. Use TruthHelper::getDressedLeptonVecor to use cone-based dressing.
    //THIS FUNCTION ASSUMES THE STARTING PARTICLE IS BARE
    if(!in_p->isLepton())
    {
        LOG(logWARNING)<<"TruthHelper::getDressedLepton() - Input is not a lepton";
        LOG(logWARNING)<<"No support for non lepton. returning 0";
        return 0;
    }

    TLorentzVector dressedTLV = in_p->p4();
    // Assume that the current particle is bare
    const xAOD::TruthParticle* bareLep = in_p;
    bool firstLoop = true;
    while(bareLep)
    {
        if(firstLoop){
            firstLoop = false;
        }
        else {
            for(size_t i = 0; i < bareLep->nChildren(); ++i) {
                const xAOD::TruthParticle* child = bareLep->child(i);
                if(!child->isPhoton()) continue;
                if(child->status() != 1) continue;
                if(child->barcode() >= 200000) continue; // Particle is from a registered secondary
                double deltaR = RemoveOverlap4l::DeltaR(in_p->eta(),in_p->phi(),child->eta(),child->phi());
                if(deltaR > 0.1) continue;
                TLorentzVector photonTLV = child->p4(); 
                LOG(logDEBUG)<<"found photon pdgid " << child->pdgId() <<" barcode: "<< child->barcode()<< " status : " << child->status() << " pt: " << child->pt() << " eta: " << child->eta() << " phi: " << child->phi();
                LOG(logDEBUG)<<"attaching to lepton pdgid " << in_p->pdgId() <<" barcode: "<< in_p->barcode()<< " status : " << in_p->status()  ;
                dressedTLV += photonTLV;
            }
        }
        // if status is 23, this is born
        if(bareLep->status() == 23) break;
        // If no parent is found, break
        if(!bareLep->parent()) break;
        // If parent is Z, the current lepton is born
        if(bareLep->parent()->isZ() || bareLep->parent()->isW()) break;
        // Now if the parent is not the same PDGID, break
        if(bareLep->parent()->pdgId() != bareLep->pdgId()) break;
        // now go up again and keep adding photons.
        bareLep = bareLep->parent();
    }
    ParticleVar* dressedLepton = 0;
    dressedLepton = new ParticleVar(m_eventCont, in_p, -1);
    m_partContainer.push_back(dressedLepton);
    
    dressedLepton->addAnalTLV(TLVType::None, dressedTLV, true);
    dressedLepton->addAnalTLV(TLVType::Truth, dressedTLV, true);
    dressedLepton->setTLVType(TLVType::None);
    LOG(logDEBUG)<<"dressed lepton PDGID: " << dressedLepton->getTruthPID() << " charge: " << dressedLepton->getCharge()  << " pt : " << dressedLepton->getTLV().Pt() << " eta: " << dressedLepton->getTLV().Eta() << " phi: " << dressedLepton->getTLV().Phi();
    return dressedLepton;
}

std::vector<ParticleVar*> TruthHelper::getDressedLeptonsVector(std::vector<const xAOD::TruthParticle*> leptons, std::vector<const xAOD::TruthParticle*> photons, double dRcut)
{

    std::vector<TLorentzVector> dressedTLV;
    for (size_t i = 0; i < leptons.size(); i++){
        dressedTLV.push_back(leptons[i]->p4());
        LOG(logDEBUG)<<"bare lepton PDGID: " << leptons[i]->pdgId() << " charge: " << leptons[i]->charge()  << " pt : " << leptons[i]->pt() << " eta: " << leptons[i]->eta() << " phi: " << leptons[i]->phi();
    }
    for (size_t i = 0; i < photons.size(); i++) {
        int lepton_index = -1;
        double min_dR = 999.9;
        for (size_t j = 0; j < leptons.size(); j++) {
            double deltaR = RemoveOverlap4l::DeltaR(leptons[j]->eta(),leptons[j]->phi(),photons[i]->eta(),photons[i]->phi());
            if ((deltaR < dRcut) && (deltaR < min_dR)) {
                lepton_index = j;
                min_dR = deltaR;
            }
        }
        if (lepton_index >= 0) {
            LOG(logDEBUG)<<"found photon pdgid " << photons[i]->pdgId() <<" barcode: "<< photons[i]->barcode()<< " status : " << photons[i]->status() << " pt: " << photons[i]->pt() << " eta: " << photons[i]->eta() << " phi: " << photons[i]->phi();
            LOG(logDEBUG)<<"attaching to lepton pdgid " << leptons[lepton_index]->pdgId() <<" barcode: "<< leptons[lepton_index]->barcode()<< " status : " << leptons[lepton_index]->status()  ;
            dressedTLV[lepton_index] = dressedTLV[lepton_index] + photons[i]->p4();
            photons.erase(photons.begin() + i);
            i--;
        }
    }

    std::vector<ParticleVar*> dressedLeptonVec;
    for (size_t i = 0; i < leptons.size(); i++)
    {
        ParticleVar* dressedLepton = 0;
        dressedLepton = new ParticleVar(m_eventCont, leptons[i], -1);
        m_partContainer.push_back(dressedLepton);
        dressedLepton->addAnalTLV(TLVType::None, dressedTLV[i], true);
        dressedLepton->addAnalTLV(TLVType::Truth, dressedTLV[i], true);
        dressedLepton->setTLVType(TLVType::None);
        dressedLeptonVec.push_back(dressedLepton);
        LOG(logDEBUG)<<"dressed lepton PDGID: " << dressedLepton->getTruthPID() << " charge: " << dressedLepton->getCharge()  << " pt : " << dressedLepton->getTLV().Pt() << " eta: " << dressedLepton->getTLV().Eta() << " phi: " << dressedLepton->getTLV().Phi();
    }
    return dressedLeptonVec;
}

vector<ParticleVar*> TruthHelper::getDressedLeptonsFromBareLeptons(vector<const xAOD::TruthParticle*> bareLeptons) 
{
    //ths function looks for the photons in the decay tree of the truth particle.
    //if you want to dress using a dR cut and a cone, use TruthHelper::getDressedLeptonVector
    vector<ParticleVar*> dressedParticles;

    //now dress the bare leptons with photons assoicated with decay
    for (size_t i = 0; i < bareLeptons.size(); i++)
    {
        const xAOD::TruthParticle* bareLep = bareLeptons[i];
        ParticleVar* dressedLepton = 0;
        if(!bareLep) {
            //LOG(logWARNING) << " TruthHelper::getBornLeptonsFromDressedLeptons: No bare lepton, returning 0." ;
            dressedParticles.push_back(dressedLepton);
            continue;
        }

        LOG(logDEBUG)<<"bare lepton PDGID: " << bareLep->pdgId() << " charge: " << bareLep->charge()  << " status: " << bareLep->status()<< " pt : " << bareLep->pt() << " eta: " << bareLep->eta() << " phi: " << bareLep->phi();
        dressedLepton = getDressedLepton(bareLep);

        dressedParticles.push_back(dressedLepton);
    }
    return dressedParticles;
}


/////////////////////
// B-tagging
/////////////////////

std::vector<ParticleVar*> TruthHelper::findTruthBjets(std::vector<ParticleVar*> jetList)
{
    std::vector<ParticleVar*> bjetList;
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();

    // Dump of the information
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
            t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;

        // Continue if not photon
        //if(!truthPart->hasBottom()) continue;
        if(truthPart->hasBottom() || truthPart->isBottomMeson() || truthPart->isBottomBaryon() || truthPart->isBottomHadron())
        {
            if(truthPart->status() >= 11) continue; //status > 11 are intermediate particles
            if(truthPart->barcode() >= 200000) continue; // Particle is from a registered secondary
            int jet_index = -1;
            double min_dR = 999.9;
            double dRcut = 0.4;
            for (size_t i = 0; i < jetList.size(); i++) {
                double deltaR = RemoveOverlap4l::DeltaR(jetList[i]->getParticle()->eta(),jetList[i]->getParticle()->phi(),truthPart->eta(),truthPart->phi());
                if ((deltaR < dRcut) && (deltaR < min_dR)) {
                    jet_index = i;
                    min_dR = deltaR;
                }
            }
            if (jet_index >= 0) {
                LOG(logDEBUG)<<"found bottom quark pdgid " << truthPart->pdgId() <<" barcode: "<< truthPart->barcode()<< " status : " << truthPart->status() << " pt: " << truthPart->pt() << " eta: " << truthPart->eta() << " phi: " << truthPart->phi();
                LOG(logDEBUG)<<"associated to jet with pt: " << jetList[jet_index]->getParticle()->pt() << " eta: " << jetList[jet_index]->getParticle()->eta() << " phi: " << jetList[jet_index]->getParticle()->phi(); 
                bjetList.push_back(jetList[jet_index]);
                jetList.erase(jetList.begin() + jet_index);
            }
        }
    }
    LOG(logDEBUG)<<"size of bjet vector: " << bjetList.size();
    return bjetList;
}


/////////////////////
// Helpers
/////////////////////

QuadleptonType::QuadleptonType TruthHelper::getTruthHiggsType()
{

    QuadleptonType::QuadleptonType quadType = QuadleptonType::NA;
    ParticleQuadlepton* quad = getBornQuadlepton();
    if(!quad) return quadType;
    vector<const xAOD::TruthParticle*> ZChild;
    const xAOD::TruthParticle* truthParticle = dynamic_cast<const xAOD::TruthParticle* >(quad->getLep(0)->getParticle());
    ZChild.push_back(truthParticle);

    truthParticle = dynamic_cast<const xAOD::TruthParticle* >(quad->getLep(2)->getParticle());
    ZChild.push_back(truthParticle);


    if(ZChild[0]->isMuon() && ZChild[1]->isMuon())          quadType = QuadleptonType::_4mu;
    if(ZChild[0]->isMuon() && ZChild[1]->isElectron())      quadType = QuadleptonType::_2mu2e;
    if(ZChild[0]->isMuon() && ZChild[1]->isTau())           quadType = QuadleptonType::_2mu2tau;

    if(ZChild[0]->isElectron() && ZChild[1]->isMuon())      quadType = QuadleptonType::_2e2mu;
    if(ZChild[0]->isElectron() && ZChild[1]->isElectron())  quadType = QuadleptonType::_4e;
    if(ZChild[0]->isElectron() && ZChild[1]->isTau())       quadType = QuadleptonType::_2e2tau;

    if(ZChild[0]->isTau() && ZChild[1]->isMuon())           quadType = QuadleptonType::_2tau2mu;
    if(ZChild[0]->isTau() && ZChild[1]->isElectron())       quadType = QuadleptonType::_2tau2e;
    if(ZChild[0]->isTau() && ZChild[1]->isTau())            quadType = QuadleptonType::_4tau;

    ZChild.clear();
    return quadType;

}

const xAOD::TruthParticle* TruthHelper::getClosestTruthPart(const xAOD::IParticle *in_p) const
{
    const xAOD::TruthParticle* t = 0;
    
    Int_t pdgIdCut = -999;
    if(in_p->type() == xAOD::Type::Electron) pdgIdCut = 11;
    else if(in_p->type() == xAOD::Type::Muon) pdgIdCut = 13;
    
    Double_t deltaRDiff = 9999;
    
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    // Dump of the information
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
         t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;
        
        // skip geant particles
        if(truthPart->barcode() > 100000) continue;
        
        if(!(truthPart->absPdgId() == pdgIdCut && truthPart->status() == 1)) continue;
        
        Double_t deltaR = truthPart->p4().DeltaR(in_p->p4());
        
        if(deltaR < deltaRDiff && deltaR < 0.2)
        {
            t = truthPart;
            deltaRDiff = deltaR;
        }
    }

    
    return t;
}


/// Get the closest truth particle for input reco particle with the same PDGID, but from the list of input particles
const xAOD::TruthParticle* TruthHelper::getClosestTruthPart(const xAOD::IParticle *in_p, std::vector<const xAOD::TruthParticle*> particleList) const
{
    const xAOD::TruthParticle* t = 0;
    
    if(!in_p) return t;
    

    Int_t pdgIdCut = -999;
    if(in_p->type() == xAOD::Type::Electron) pdgIdCut = 11;
    else if(in_p->type() == xAOD::Type::Muon) pdgIdCut = 13;
    
    Double_t deltaRDiff = 9999;
    
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();
    
    // Dump of the information
    for (size_t i = 0; i < particleList.size(); i++)
    {
        const xAOD::TruthParticle* truthPart = particleList[i];
       
        if(!truthPart) continue;

        Double_t deltaR = truthPart->p4().DeltaR(in_p->p4());
        LOG(logDEBUG)<<"in_p pT: "<<in_p->pt()<<" eta: "<<in_p->eta()<<" PDGID: "<<pdgIdCut<<" test_p pT: "<<truthPart->pt()<<" eta: "<<truthPart->eta()<<" pdgID: "<<truthPart->absPdgId()<<" delta R: "<<deltaR;
        
        if(!(truthPart->absPdgId() == pdgIdCut)) continue;
        
        if(deltaR < deltaRDiff && deltaR < 0.2)
        {
            t = truthPart;
            deltaRDiff = deltaR;
        }
    }
    LOG(logDEBUG)<<"looking for the closest particle for pt: "<<in_p->pt()<<" deltaR: "<<deltaRDiff<<" match particle pT: "<<t->pt();
    
    return t;
}


/////////////////////
// Truth -> Reco
/////////////////////
ParticleQuadlepton* TruthHelper::getRecoQuadlepton(ParticleQuadlepton* quad, vector<ParticleVar*> muList, vector<ParticleVar*> elList)
{

    if(!quad) quad = getBareQuadlepton();
    if(!quad) return 0;

    if(!quad->isTruth())
    {
        LOG(logERROR)<<"TruthHelper::getRecoQuadlepton() - Input quad is not truth type";
        exit(1);
    }

    // Pairing is coming from the truth particle
    vector<ParticleVar*> recoParticles;

    for (Int_t i = 0; i < quad->getLepSize(); i++)
    {
        const xAOD::TruthParticle* truthParticle = dynamic_cast<const xAOD::TruthParticle* >(quad->getLep(i)->getParticle());

        if(truthParticle->isElectron())
        {
            ParticleVar* reco = getClosestRecoPart(truthParticle, elList);
            if(!reco) return 0;

            recoParticles.push_back(reco);
        }
        else if (truthParticle->isMuon())
        {
            ParticleVar* reco = getClosestRecoPart(truthParticle, muList);
            if(!reco) return 0;

            recoParticles.push_back(reco);
        }
    }

    if((Int_t)recoParticles.size() != quad->getLepSize()) {return 0;}


    // we know the pairing from before
    ParticleDilepton* Z1temp = new ParticleDilepton(m_eventCont, recoParticles[0], recoParticles[1]);
    m_diLepContainer.push_back(Z1temp);
    ParticleDilepton* Z2temp = new ParticleDilepton(m_eventCont, recoParticles[2], recoParticles[3]);
    m_diLepContainer.push_back(Z2temp);

    // Pairing is done inside
    ParticleQuadlepton* quadTemp = new ParticleQuadlepton(m_eventCont, Z1temp, Z2temp);
    m_quadContainer.push_back(quadTemp);

    return quadTemp;
}

ParticleVar* TruthHelper::getClosestRecoPart(const xAOD::TruthParticle* th, vector<ParticleVar*> lepList) const
{
    ParticleVar* temp = 0;
    Double_t deltaRDiff = 9999;

    for (auto recoLep: lepList)
    {
        Double_t deltaR = th->p4().DeltaR(recoLep->getTLV());

        if(deltaR < deltaRDiff && deltaR < 0.1)
        {
            temp = recoLep;
            deltaRDiff = deltaR;
        }
    }

    if(m_eventCont->isDebug && !temp)
    {
        LOG(logDEBUG)<<"Cannot find reco Pairing for truth particle";
        LOG(logDEBUG)<<"Truth PDGID: "<<th->pdgId()<<" pT: "<<th->pt()<<" eta:"<<th->eta()
            <<" phi: "<<th->phi();
    }

    return temp;
}

ParticleQuadlepton* TruthHelper::RunPairing(ParticleQuadlepton* quad) 
{
    if(!quad) return quad;
    vector<ParticleVar*> lep;
    for (int i = 0; i < 4; i++)
    {
        lep.push_back(quad->getLep(i));
    }

    return RunPairing(lep);
}

ParticleQuadlepton* TruthHelper::RunPairing(vector<ParticleVar*> & leptons) {

    // step 1: Dilepton pairs
    std::vector < ParticleDilepton*> dileptons;

    for(ParticleVar* l1 : leptons)
    {
        for(ParticleVar* l2 : leptons)
        {
            if (l1 == l2) continue;
            if (l1->getCharge() + l2->getCharge() != 0) continue;
            if (abs(l1->getTruthPID()) != abs(l2->getTruthPID())) continue;
            // Don't want to create a dilep combination with the same lepton
            ParticleDilepton* temp = 0; 

            if(l1->getCharge() > 0) {
                temp = new ParticleDilepton(m_eventCont, l1, l2);
            }
            else{
                temp = new ParticleDilepton(m_eventCont, l2, l1);
            }
            m_diLepContainer.push_back(temp);
            dileptons.push_back(temp);
        }
    }
    // sort by proximity to the PDG Z mass 
    std::sort(dileptons.begin(), dileptons.end(), [&](ParticleDilepton* a, ParticleDilepton* b) {
        return (fabs(pdgZMass-a->getTLV().M()) < fabs(pdgZMass-b->getTLV().M()));
    });
    // now we remove pairs using leptons from pairs closer to MZ. The resulting vector
    // will contain orthogonal pairs, still sorted by proximity to mz
    for(std::vector<ParticleDilepton*>::iterator iter_DL1 = dileptons.begin(); iter_DL1!=dileptons.end();++iter_DL1){
        for(std::vector<ParticleDilepton*>::iterator iter_DL2 = iter_DL1+1; iter_DL2!=dileptons.end();++iter_DL2){
            if ((*iter_DL1)->isOverlap(*iter_DL2)) {
                dileptons.erase(iter_DL2--);   // decrement thisPair2 since we will increment it in the for loop
            }
        }
    }
    // catch cases where we run out of pairs
    if (dileptons.size() < 2){
        //LOG(logWARNING)<<"oops, ran out of pairs in the  truth pairing!";
        return 0;
    }
    // now, the quad is formed from the two closest pairs
    ParticleQuadlepton* quad = new ParticleQuadlepton (m_eventCont, dileptons.at(0), dileptons.at(1));
    m_quadContainer.push_back(quad);
    return quad;

}

const xAOD::TruthParticle* TruthHelper::getTauLeptonChild(const xAOD::TruthParticle* in_p) const
{
    // For speeding up    
    size_t iEnd = in_p->nChildren();    
    for(size_t i = 0; i < iEnd; i++)
    {
        if(!in_p->child(i)) continue;

        // If a lepton, return that
        if(in_p->child(i)->isMuon() || in_p->child(i)->isElectron())
            return in_p->child(i);

        // if a tau, check it for a lepton child
        if(in_p->child(i)->isTau()) return getTauLeptonChild(in_p->child(i));

        // If not a neutrino or above conditions, it is a hadron decay
        if(!in_p->child(i)->isNeutrino()) return 0;
    }

    return 0;
}


vector<ParticleVar*> TruthHelper::getParticleVar(vector<const xAOD::TruthParticle*> ts)
{
    vector<ParticleVar*> ps;
    for(size_t i = 0; i < ts.size(); i++)
    {
        // No index for now
        ParticleVar* particle = 0;
        if(ts[i]) particle = new ParticleVar(m_eventCont, ts[i], -1);
        m_partContainer.push_back(particle);
        ps.push_back(particle);
    }

    return ps;
}


// This function gets the first four leptons from the truth record that have higgs in the parent list
// Needed by Andrea for his study
vector<ParticleVar*> TruthHelper::getFirstFourLeptonsFromHiggs()
{
    vector<ParticleVar*> lepList;
    vector<const xAOD::TruthParticle*> parList;

    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();

    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
            t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;

        // Continue if not a muon or electron
        if(!(truthPart->isMuon() || truthPart->isElectron())) continue;

        // check if this is a copy of something already saved in the tree
        bool isCopy = false;
        for(auto part:parList)
        {
            if(checkParent(truthPart, part))
            {
                isCopy = true;
                break;
            }
        }
        if(isCopy) continue;

        if(!checkParentPDGID(truthPart, 25))
        {
            //LOG(logWARNING)<<"Rejecting a lepton due to it not having a higgs parent before finding the 4 leptons";
            continue;
        }

        ParticleVar* particle = new ParticleVar(m_eventCont, truthPart, -1);
        m_partContainer.push_back(particle);
        lepList.push_back(particle);
        parList.push_back(truthPart);

        // return, if the 4 leptons have been found
        if(lepList.size() == 4) break;
    }
    return lepList;
}

// recursive function that checkes if a parent in the decay chain has the given PDGID
// it returns false if the sample is ... I don't want to deal with it, leaving it for someone else ... HA
bool TruthHelper::checkParentPDGID(const xAOD::TruthParticle* in, int pdgid) const
{
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        return false;
    }


    int iter = 0;
    while(in)
    {
        // If no parent is found, just break from the loop and return false
        if(!in->parent()) return false;

        // If parent, check if the PDG ID matches
        if(in->parent()->pdgId() == pdgid) return true;

        // Otherwise, climb up the chain
        in = in->parent();

        iter++;

        if(iter > 50)
        {
            LOG(logWARNING)<<"checkParentPDGID: more than 50th iteration... suspecting an infinite loop, so breaking and returning false";
            return false;
        }
    }

    return false;
}

// function that checkes if a parent in the decay chain matches the input
// it returns false if the sample is ... I don't want to deal with it, leaving it for someone else ... HA
bool TruthHelper::checkParent(const xAOD::TruthParticle* in, const xAOD::TruthParticle* toCheck) const
{
    if (m_eventCont->m_currGenerator == Generator::Sherpa){
        return false;
    }

    if(in == toCheck) return true;

    int iter = 0;
    while(in)
    {
        // If no parent is found, just break from the loop and return false
        if(!in->parent()) return false;

        // If parent, check if the PDG ID matches
        if(in->parent() == toCheck) return true;

        // Otherwise, climb up the chain
        in = in->parent();

        iter++;

        if(iter > 50)
        {
            LOG(logWARNING)<<"checkParentPDGID: more than 50th iteration... suspecting an infinite loop, so breaking and returning false";
            return false;
        }
    }

    return false;
}


// For tagging the Higgs decay
int TruthHelper::getHiggsDecayTag()
{
    const xAOD::TruthParticleContainer *truthCont = 0;
    m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess();


    const xAOD::TruthParticle* truthHiggs = 0;

    // Dump of the information
    for (xAOD::TruthParticleContainer::const_iterator t_itr = truthCont->begin();
            t_itr != truthCont->end(); ++t_itr)
    {
        const xAOD::TruthParticle* truthPart = *t_itr;

        // Continue if not the Higgs
        if(!truthPart->isHiggs()) continue;
        // Continue if the Higgs has only one child
        if(truthPart->nChildren() <=1 ) continue;

        truthHiggs = truthPart;
    }

    if(!truthHiggs) 
    {
        //LOG(logWARNING)<<"TruthHelper::getHiggsDecayTag() - Higgs not found";
        //LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        return -1;
    }

    int nZBoson = 0;
    int nLeptons = 0;
    int nQuark = 0;
    int nGamma = 0;
    int nTauTau = 0;
    int nWBoson = 0;
    int nTauDecay = 0;
    int nLeptonDecay = 0;
    int nNeutrinoDecay = 0;
    int nQuarkDecay = 0;
    // Loop over the the Z or W or Higgs boson
    // Find the instances of the bare lepton
    for(size_t i = 0; i < truthHiggs->nChildren(); i++)
    {
        const xAOD::TruthParticle* child = truthHiggs->child(i);

        if(!child) continue;
        LOG(logDEBUG) << "Higgs child status : " << child->status() << " , pdgid: " << child->pdgId() ;

        // Check the not boson decay first
        if(child->isTau())
        {
            nTauTau++;
            continue;
        }
        else if(child->isPhoton())
        {
            nGamma++;
            continue;
        }
        else if(child->isQuark())
        {
            nQuark++;
            continue;
        }
        else if(child->isLepton())
        {
            nLeptons++;
            continue;
        }

        // descend down the chain till there are more than 1 decay particle)
        while(child->nChildren() == 1)
        {
            child = child->child(0);

            if(!child) break;
            
        }

        if(!child) continue;
        

        if(child->isZ())
        {
            nZBoson++;
        }
        else if(child->isW())
        {
            nWBoson++;
        }
        else
        {
            LOG(logWARNING)<<"Found Higgs decay that isn't Z or W boson or tau";
            LOG(logWARNING)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber();
        }


        bool isBBMother = checkBareBornSameMother(child);
        
        for(size_t j = 0; j < child->nChildren(); j++)
        {
            const xAOD::TruthParticle* gchild = child->child(j);

            if(isBBMother && gchild->status() != 1) continue;
            LOG(logDEBUG) << "\tHiggs gchild status : " << gchild->status() << " , gchild: " << gchild->pdgId() ;

            if(gchild->isNeutrino()) nNeutrinoDecay++;
            else if(gchild->isTau()) nTauDecay++;
            else if(gchild->isLepton()) nLeptonDecay++;
            else if(gchild->isPhoton()) continue;
            else nQuarkDecay++;
            
        }

    }

    LOG(logDEBUG)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber()<<" Higgs childern info-"<<" nZBoson: " << nZBoson<<" nWBoson: "<<nWBoson<<" nTauTau: " << nTauTau ;
    LOG(logDEBUG)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber()<<" Higgs childern info-"<<" nLeptons: " << nLeptons<<" nGamma: "<<nGamma;
    LOG(logDEBUG)<<"Event Number: "<<m_eventCont->eventInfo->eventNumber()<<" Higgs gchildern info-"<<" nNeutrinoDecay: "<<nNeutrinoDecay<<" nLeptonDecay: "<<nLeptonDecay<<" nQuarkDecay: "<<nQuarkDecay<<" nTauDecay: "<< nTauDecay;

    if(nTauTau == 2)
    {
        return HiggsDecay::Htautau;
    }
    if(nLeptons == 2)
    {
        return HiggsDecay::Hmumu;
    }
    if(nZBoson == 1 && nGamma == 1)
    {
        return HiggsDecay::HZgamma;
    }
    if(nQuark == 2)
    {
        return HiggsDecay::Hbb;
    }
    if(nZBoson == 2)
    {
        if(nLeptonDecay == 4) return HiggsDecay::HZZ_4l;
        if(nLeptonDecay == 2 && nNeutrinoDecay == 2) return HiggsDecay::HZZ_2l2v;
        if(nTauDecay == 2 && nNeutrinoDecay == 2) return HiggsDecay::HZZ_2tau2v;
        if(nLeptonDecay == 2 && nTauDecay == 2) return HiggsDecay::HZZ_2l2tau;
        if(nTauDecay == 4) return HiggsDecay::HZZ_2l2tau;
        if(nQuarkDecay == 2 && nNeutrinoDecay == 2) return HiggsDecay::HZZ_2q2v;
        if(nQuarkDecay == 2 && nTauDecay == 2) return HiggsDecay::HZZ_2q2tau;
        if(nQuarkDecay == 2 && nLeptonDecay == 2) return HiggsDecay::HZZ_2q2l;
    }
    if(nWBoson == 2)
    {
        return HiggsDecay::HWW;
    }
    LOG(logWARNING)<<"Assigning this event as HOther Event Number: "<<m_eventCont->eventInfo->eventNumber();
    return HiggsDecay::HOther;

}
