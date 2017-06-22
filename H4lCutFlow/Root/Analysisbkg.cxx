#include "H4lCutFlow/Analysisbkg.h"
using namespace std;

// Constructor
Analysisbkg::Analysisbkg()
    :AnalysisBase()
{
    m_eventCont->doSmear = true;
    m_forAcceptanceChallenge = true;
}

// Destructor
Analysisbkg::~Analysisbkg()
{
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        // Deleting the output minitree
        delete m_outTreeMap[sysListItr];
        delete m_outTree3lMap[sysListItr];
    }
    
    if(m_dataPreSel)            delete m_dataPreSel;
    if(m_preSel)                delete m_preSel;
    if(m_trigger)               delete m_trigger;
    if(m_triggerllee)           delete m_triggerllee;
    if(m_cutMuon)               delete m_cutMuon;
    if(m_cutElectron)           delete m_cutElectron;
    if(m_cutElectronLoose)      delete m_cutElectronLoose;
    if(m_cutJet)                delete m_cutJet;
    if(m_removeOverlap)         delete m_removeOverlap;
    if(m_removeOverlapLoose)    delete m_removeOverlapLoose;
    
    for(auto cf: m_bkgCutFlows)
    {
       if(cf) delete cf; 
    } 

    for(auto cf: m_llmumuCutFlows)
    {
       if(cf) delete cf; 
    }
    for(auto cf: m_lleeCutFlows)
    {
       if(cf) delete cf;
    }
    for(auto cf: m_3lCutFlows)
    {
       if(cf) delete cf; 
    } 
    if(m_applyWeight)           delete m_applyWeight;
    if(m_calculateVar)          delete m_calculateVar;
    if(m_calculateVar3l)        delete m_calculateVar3l;
    if(m_truthHelper)           delete m_truthHelper;
    
    if(tool4l)                  delete tool4l;
}


// For intializating that depends after variables
// have been setup from the job and after the first 
// event has been read
// Typically all classes are expected to be created
// and intialized here
void Analysisbkg::initialize()
{
    LOG(logINFO) << "initialize event info";
    
    m_eventCont->initialize();
    
    tool4l = new ToolInit4l(m_eventCont);
    tool4l->initialize();
    m_toolBase = (ToolInitBase*) tool4l;
    
    AnalysisBase::initialize();
    
    // Constructor
    
    // Preselection
    m_dataPreSel  = new CutEventDataPreSel(m_eventCont);
    m_preSel      = new CutEventPreSel(m_eventCont);
    m_trigger     = new CutEventTrigger(m_eventCont);
    m_triggerllee = new CutEventTrigger(m_eventCont);
    m_triggerllee->removeTriMu();
    m_triggerllee->removeTriEl();
    m_triggerllee->removeElMu();
    
    
    // Particle Level
    m_cutMuon     = new CutParticleMuon(m_eventCont);
    m_cutElectron = new CutParticleElectron(m_eventCont);

    m_cutElectronLoose = new CutParticleElectron(m_eventCont);
    m_cutElectronLoose->doVeryLooseID();
    m_cutElectronLoose->doBasicID();
    
    m_cutJet      = new CutParticleJet(m_eventCont);
    m_cutJet->setJetSelType(CutParticleJet::NominalReco);

    m_removeOverlap = new RemoveOverlap4l(m_eventCont);
    m_removeOverlapLoose = new RemoveOverlap4l(m_eventCont);
    
    
    // Weights
    m_applyWeight   = new ApplyWeight4l(m_eventCont);
    
    
    
    // Main cutflow
    m_cutFlowRelaxIsoD04mu    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowRelaxIsoD04mu->cutFlowType(bkgCutFlow::d0_Iso_relax);
    m_cutFlowRelaxIsoD04mu->setQuadAnalysisType(QuadleptonType::_4mu);
    
    m_cutFlowRelaxIsoD02e2mu    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowRelaxIsoD02e2mu->cutFlowType(bkgCutFlow::d0_Iso_relax);
    m_cutFlowRelaxIsoD02e2mu->setQuadAnalysisType(QuadleptonType::_2e2mu);

    m_cutFlowRelaxIsoD02mu2e    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowRelaxIsoD02mu2e->cutFlowType(bkgCutFlow::d0_Iso_relax);
    m_cutFlowRelaxIsoD02mu2e->setQuadAnalysisType(QuadleptonType::_2mu2e);

    m_cutFlowRelaxIsoD04e    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowRelaxIsoD04e->cutFlowType(bkgCutFlow::d0_Iso_relax);
    m_cutFlowRelaxIsoD04e->setQuadAnalysisType(QuadleptonType::_4e);

    m_cutFlowSS4mu    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowSS4mu->cutFlowType(bkgCutFlow::sameSign);
    m_cutFlowSS4mu->setQuadAnalysisType(QuadleptonType::_4mu);
    
    m_cutFlowSS2e2mu    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowSS2e2mu->cutFlowType(bkgCutFlow::sameSign);
    m_cutFlowSS2e2mu->setQuadAnalysisType(QuadleptonType::_2e2mu);

    m_cutFlowSS2mu2e    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowSS2mu2e->cutFlowType(bkgCutFlow::sameSign);
    m_cutFlowSS2mu2e->setQuadAnalysisType(QuadleptonType::_2mu2e);

    m_cutFlowSS4e    = new CutFlowBkg(m_eventCont, m_applyWeight);
    m_cutFlowSS4e->cutFlowType(bkgCutFlow::sameSign);
    m_cutFlowSS4e->setQuadAnalysisType(QuadleptonType::_4e);

    
    m_cutFlowemu    = new CutFlowllmumu(m_eventCont, m_applyWeight);
    m_cutFlowemu->cutFlowType(llmumuCutFlow::emu);
    
    
    m_bkgCutFlows.push_back(m_cutFlowRelaxIsoD04mu);
    m_bkgCutFlows.push_back(m_cutFlowRelaxIsoD02e2mu);
    m_bkgCutFlows.push_back(m_cutFlowRelaxIsoD02mu2e);
    m_bkgCutFlows.push_back(m_cutFlowRelaxIsoD04e);
    m_bkgCutFlows.push_back(m_cutFlowSS4mu);
    m_bkgCutFlows.push_back(m_cutFlowSS2e2mu);
    m_bkgCutFlows.push_back(m_cutFlowSS2mu2e);
    m_bkgCutFlows.push_back(m_cutFlowSS4e);

    m_llmumuCutFlows.push_back(m_cutFlowemu);

    m_METCalc = std::make_shared<METCalc>(m_eventCont);
    
    m_3lxCR4e    = new CutFlowllee(m_eventCont, m_applyWeight);
    m_3lxCR4e->cutFlowType(lleeCutFlow::threeLplusX);
    m_3lxCR4e->setQuadAnalysisType(QuadleptonType::_4e);
    
    m_3lxCR2mu2e    = new CutFlowllee(m_eventCont, m_applyWeight);
    m_3lxCR2mu2e->cutFlowType(lleeCutFlow::threeLplusX);
    m_3lxCR2mu2e->setQuadAnalysisType(QuadleptonType::_2mu2e);
    
    m_lleeCutFlows.push_back(m_3lxCR4e);
    m_lleeCutFlows.push_back(m_3lxCR2mu2e);
    
    m_ZplusEl = new CutFlow3l(m_eventCont, m_applyWeight);
    m_ZplusEl->cutFlowType(ZlCutFlowType::ZplusX);
    m_ZplusEl->setMETClass(m_METCalc);
    
    m_ZplusMu = new CutFlow3l(m_eventCont, m_applyWeight);
    m_ZplusMu->cutFlowType(ZlCutFlowType::ZplusMu);
    m_ZplusMu->setMETClass(m_METCalc);
    
    m_3lCutFlows.push_back(m_ZplusEl);
    m_3lCutFlows.push_back(m_ZplusMu);
    
    // Helper
    m_calculateVar = new CalculateVar4l(m_eventCont);
    m_calculateVar->setMETClass(m_METCalc);

    m_calculateVar3l = new CalculateVar3l(m_eventCont);
    m_calculateVar3l->setMETClass(m_METCalc);
    
    m_truthHelper = new TruthHelper(m_eventCont);
    

    addSystematicsSet();
    
    // Set of initialization - to be called only by the derived class
    // This is intended to setup any thing after all the tools have be initialized
    // Mainly will be used for any setup dependant on systematics
    m_dataPreSel->initialize();
    m_preSel->initialize();
    m_trigger->initialize();
    m_triggerllee->initialize();
    
    m_cutMuon->initialize();
    m_cutElectron->initialize();
    m_cutElectronLoose->initialize();
    m_cutJet->initialize();

    m_removeOverlap->initialize();
    m_removeOverlapLoose->initialize();
    //m_applyWeight->setCutEventTrigger(m_trigger);
    m_applyWeight->initialize();
    m_calculateVar->initialize();
    m_calculateVar3l->initialize();
    m_METCalc->initialize();

    for(auto cf: m_bkgCutFlows)
    {
        cf->setCutEventTrigger(m_trigger);
        cf->initialize();
    }
    for(auto cf: m_llmumuCutFlows)
    {
        cf->setCutEventTrigger(m_trigger);
        cf->initialize();
    }
    for(auto cf: m_lleeCutFlows)
    {
        cf->setCutEventTrigger(m_trigger);
        cf->initialize();
    }
    for(auto cf: m_3lCutFlows)
    {
        cf->setCutEventTrigger(m_triggerllee);
        cf->initialize();
    }

    // Initialization of the output trees
    for (auto sysListItr:m_eventCont->m_sysList){
        OutputTreeBkg* outTree
        =  new OutputTreeBkg(m_eventCont->outputBaseName+"_BkgCR", (sysListItr).name(), m_eventCont->fileName);
               // If data
        if(!m_eventCont->isMC) outTree->addDataSpecificVar();

        outTree->setIsMC(m_eventCont->isMC);
        if(m_eventCont->isMC) outTree->setRunNumber(m_eventCont->getDSID());

        outTree->initialize();
        m_outTreeMap[sysListItr] = (OutputTree*) outTree;
        
        
        OutputTree3l* outTree3l
        =  new OutputTree3l(m_eventCont->outputBaseName+"_Zplusl", (sysListItr).name(), m_eventCont->fileName);
       
        outTree3l->setIsMC(m_eventCont->isMC);
        if(m_eventCont->isMC) outTree3l->setRunNumber(m_eventCont->getDSID());


        outTree3l->initialize();
        m_outTree3lMap[sysListItr] = (OutputTree*) outTree3l;
    }

    
}

void Analysisbkg::finalize()
{
    AnalysisBase::finalize();
    
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        m_eventCont->m_currVariation = sysListItr;
        m_eventCont->outTree = m_outTree3lMap[sysListItr];
        
        // Do the last filling of events
        m_eventCont->fillEventHist();
        
        // Any cutflow histrograms are copied to output
        // if need by the analysis
        updateHistCutFlow();
        
        if(m_eventCont->outTree) m_eventCont->outTree->writeTree();
    }

}

/// Event preselection cuts are implemented here
/// Expected cuts: dataPreselection, selection and trigger cuts
Bool_t Analysisbkg::eventPreSelection()
{    
    updateCutFlow(cutFlow::Total);

    // Data Preselection cut
    if(!m_dataPreSel->passCut()) return false;
    updateCutFlow(cutFlow::DataPreselection);
    
    // Preselection cut
    if(!m_preSel->passCut()) return false;
    updateCutFlow(cutFlow::Preselection);
    
    // Trigger
    // This to speed up
    // Only apply the trigger at the very end
    if(m_forAcceptanceChallenge)
    {
        if(!m_trigger->passCut()) return false;
        updateCutFlow(cutFlow::Trigger);
    }
    
    return true;
}

void Analysisbkg::clearVars()
{
    AnalysisBase::clearVars();
    
    m_cutMuon->clearVars();
    m_cutElectron->clearVars();
    m_cutElectronLoose->clearVars();
    m_cutJet->clearVars();
    
    m_removeOverlap->clearVars();
    m_removeOverlapLoose->clearVars();
    m_METCalc->clearVars();

    for(auto cf: m_llmumuCutFlows) cf->clearVars();
    for(auto cf: m_bkgCutFlows) cf->clearVars();
    for(auto cf: m_lleeCutFlows) cf->clearVars();
    for(auto cf: m_3lCutFlows) cf->clearVars();

    m_calculateVar->clearVars();
    m_calculateVar3l->clearVars();
    m_truthHelper->clearVars();
    m_applyWeight->clearVars();

    m_triggerllee->clearVars();
    m_trigger->clearVars();
    m_higgs = 0;

}

void Analysisbkg::selectPhyObjects()
{
    // Cut particle level
    m_cutMuon->setParticles(m_muonList);
    m_cutMuon->process();
    
    m_cutElectron->setParticles(m_electronList);
    m_cutElectron->process();
    
    m_cutElectronLoose->setParticles(m_electronList);
    m_cutElectronLoose->process();

    m_cutJet->setParticles(m_jetList);
    m_cutJet->process();

    
    // Overlap removal
    m_removeOverlap->setElectrons(m_cutElectron->getParticles());
    m_removeOverlap->setMuons(m_cutMuon->getParticles());
    m_removeOverlap->setJets(m_cutJet->getParticles());
    m_removeOverlap->process();
    
    // Overlap removal
    m_removeOverlapLoose->setElectrons(m_cutElectronLoose->getParticles());
    m_removeOverlapLoose->setMuons(m_cutMuon->getParticles());
    m_removeOverlapLoose->setJets(m_cutJet->getParticles());
    m_removeOverlapLoose->process();

    // update the numbers for muons
    m_cutMuon->updateCutFlow      (m_removeOverlap->getMuons().size(),      muCut::OverLap);
    m_cutElectron->updateCutFlow  (m_removeOverlap->getElectrons().size(),  elCut::OverLap);
    m_cutJet->updateCutFlow       (m_removeOverlap->getJets().size(),       jetCut::OverLap);
    m_cutElectronLoose->updateCutFlow  (m_removeOverlapLoose->getElectrons().size(),  elCut::OverLap);

    m_eventCont->outTree->updateHistVar("nPassMuHist", m_removeOverlap->getMuons().size());
    m_eventCont->outTree->updateHistVar("nPassElHist", m_removeOverlap->getElectrons().size());
    m_eventCont->outTree->updateHistVar("nPassJetHist", m_removeOverlap->getJets().size());
    m_eventCont->outTree->updateHistVar("nPassPhotonHist", m_photonList.size());
}

Bool_t Analysisbkg::eventSelection()
{
   
    // Skip event if bad jet
    auto jetCollection = m_removeOverlap->getJets();

    bool badJet = false;
    bool loosebadJet = false;
    for(const auto& jet: jetCollection)
    {
        if(jet->getParticle()->auxdecor<int>("badJet") == 0) badJet = true;
    }

    jetCollection = m_removeOverlapLoose->getJets();
    for(const auto& jet: jetCollection)
    {
        if(jet->getParticle()->auxdecor<int>("badJet") == 0) loosebadJet = true;
    }


    for(auto cf: m_llmumuCutFlows)
    {
        LOG(logDEBUG)<<"Running CutFlow: "<<cf->getCutFlowName();
        cf->setMuons(m_removeOverlap->getMuons());
        cf->setElectrons(m_removeOverlap->getElectrons());
        if(!badJet) cf->process();
    }
    for(auto cf: m_lleeCutFlows)
    {
        LOG(logDEBUG)<<"Running CutFlow: "<<cf->getCutFlowName();        
        cf->setMuons(m_removeOverlapLoose->getMuons());
        cf->setElectrons(m_removeOverlapLoose->getElectrons());
        if(!loosebadJet) cf->process();
    }
    for(auto cf: m_bkgCutFlows)
    {
        LOG(logDEBUG)<<"Running CutFlow: "<<cf->getCutFlowName();        
        cf->setMuons(m_removeOverlap->getMuons());
        cf->setElectrons(m_removeOverlap->getElectrons());
        if(!badJet) cf->process();
    }

    LOG(logDEBUG)<<"Running CutFlow: "<<m_ZplusEl->getCutFlowName();    
    m_ZplusEl->setMuons(m_removeOverlapLoose->getMuons());
    m_ZplusEl->setElectrons(m_removeOverlapLoose->getElectrons());
    setupMETClass();
    if(!loosebadJet) m_ZplusEl->process();
   
    LOG(logDEBUG)<<"Running CutFlow: "<<m_ZplusMu->getCutFlowName();        
    m_ZplusMu->setMuons(m_removeOverlap->getMuons());
    m_ZplusMu->setElectrons(m_removeOverlap->getElectrons());
    setupMETClass();
    if(!badJet) m_ZplusMu->process();
    
    if(!m_forAcceptanceChallenge)
    {
        if(!m_trigger->passCut()) return false;
        updateCutFlow(cutFlow::Trigger);
    }
    
    return true;
}

void Analysisbkg::calcVars()
{
    // Do each analysis one by one
    // For llmumu, last cut is D0Sig (on Z1)
    //cutFlow::cutFlow lastCut = cutFlow::D0Sig;
    // relaxD0Iso
    if(m_cutFlowRelaxIsoD04mu->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowRelaxIsoD04mu, OutputTreeType::d0IsoRelax);
    }
    else if(m_cutFlowRelaxIsoD02e2mu->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowRelaxIsoD02e2mu, OutputTreeType::d0IsoRelax);
    }
    else if(m_cutFlowRelaxIsoD02mu2e->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowRelaxIsoD02mu2e, OutputTreeType::d0IsoRelax);
    }
    else if(m_cutFlowRelaxIsoD04e->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowRelaxIsoD04e, OutputTreeType::d0IsoRelax);
    }

    // emu
    if(m_cutFlowemu->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowemu, OutputTreeType::emu);
    }

    // ss
    if(m_cutFlowSS4mu->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowSS4mu, OutputTreeType::sameSign);
    }
    else if(m_cutFlowSS2e2mu->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowSS2e2mu, OutputTreeType::sameSign);
    }
    else if(m_cutFlowSS2mu2e->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowSS2mu2e, OutputTreeType::sameSign);
    }
    else if(m_cutFlowSS4e->getHiggsCandNum() > 0)
    {
        calcResults4lCutflow(m_cutFlowSS4e, OutputTreeType::sameSign);
    }


    if(!m_triggerllee->passCut())
    {
        LOG(logDEBUG)<<"Trigger did not pass for the llee CR... Rejecting the event";                                        
    }

    // 3l+X
    //
    // For quad indexing
    int quadIndex = 0;

    vector<ParticleQuadlepton*> higgsCand = m_3lxCR4e->getHiggsVec();
    // Reject if the trigger didn't pass
    if(!m_triggerllee->passCut()) higgsCand.clear();

    // Sort the quads based on mZ2
    std::sort (higgsCand.begin(), higgsCand.end(), sortmZ2); 
    
    // Loop and save
    for(size_t i = 0; i < higgsCand.size(); i++)
    {
        LOG(logDEBUG)<<"Calculating Vars for m_3lxCR4e";                                        
        m_higgs = higgsCand[i];
        
        // Clear the vars
        m_calculateVar->clearVars();
        // Set the index
        m_calculateVar->setCandIndex(quadIndex);
        quadIndex++;

        // Add the extenal info and trigger tha calculation
        calcVarHelperSiEl();

        // push the output to the tree
        if(m_eventCont->outTree->isIntVar("prod_type"))
            m_3lxCR4e->updateCategory(m_eventCont->outTree->getIntVar("prod_type"));

        m_3lxCR4e->updateCutFlow(cutFlow3lx::Final, 1);
        
        m_eventCont->outTree->fillTree(OutputTreeType::threeLplusX);
    }
    // 2mu2e
    higgsCand = m_3lxCR2mu2e->getHiggsVec();
    // refect if the trigger didn't pass
    if(!m_triggerllee->passCut()) higgsCand.clear();    
   
    // Sort the quads based on mZ2
    std::sort (higgsCand.begin(), higgsCand.end(), sortmZ2); 
    
    // Loop and save
    for(size_t i = 0; i < higgsCand.size(); i++)
    {
        LOG(logDEBUG)<<"Calculating Vars for m_3lxCR2mu2e";                                                
        m_higgs = higgsCand[i];
        
        // Clear the vars
        m_calculateVar->clearVars();
        // Set the index
        m_calculateVar->setCandIndex(quadIndex);
        quadIndex++;

        // Add the extenal info and trigger tha calculation
        calcVarHelperSiEl();

        // push the output to the tree
        if(m_eventCont->outTree->isIntVar("prod_type"))
            m_3lxCR2mu2e->updateCategory(m_eventCont->outTree->getIntVar("prod_type"));

        m_3lxCR2mu2e->updateCutFlow(cutFlow3lx::Final, 1);
        
        m_eventCont->outTree->fillTree(OutputTreeType::threeLplusX);
    }
   

    quadIndex = 0;
    
    // switch tree for 3l
    OutputTree* tempTree = m_eventCont->outTree;

    // Setting the output tree for event
    m_eventCont->outTree = m_outTree3lMap.at(m_eventCont->m_currVariation);
    vector<ParticleMulti*> ZmuVec = m_ZplusMu->getZlCand();
    if(!m_triggerllee->passCut()) ZmuVec.clear();    
    // Sort based on lep pt    
    std::sort (ZmuVec.begin(), ZmuVec.end(), sortmZ2Lep); 
    
    for(size_t i = 0; i < ZmuVec.size(); i++)
    {
        LOG(logDEBUG)<<"Calculating Vars for m_ZplusMu";                                                
        m_ZplusMu->updateCutFlow(cutFlowZl::Final, 1);
        
        ParticleMulti* Zmu = ZmuVec[i];
        m_calculateVar3l->clearVars();

        m_calculateVar3l->setCandIndex(quadIndex);
        quadIndex++;

        // give the vars
        m_calculateVar3l->setZplusL(Zmu);
        m_calculateVar3l->setJets(m_removeOverlap->getJets());
        m_calculateVar3l->setMuon(m_removeOverlap->getMuons());
        m_calculateVar3l->setElectron(m_removeOverlap->getElectrons());
        setupMETClass();

        m_calculateVar3l->setCalElCont(m_smearEgamma->getCalElectronCont());
        m_calculateVar3l->setCalPhCont(m_smearEgamma->getCalPhotonCont());
        m_calculateVar3l->process();
       
        m_applyWeight->setJets(m_removeOverlap->getJets());        
        m_applyWeight->fillWeight(Zmu);

        m_eventCont->outTree->fillTree(OutputTreeType::ZplusMu);
    }
    
    vector<ParticleMulti*> ZelVec = m_ZplusEl->getZlCand();
    if(!m_triggerllee->passCut()) ZelVec.clear();    
    std::sort (ZelVec.begin(), ZelVec.end(), sortmZ2Lep); 
    
    quadIndex = 0;
     LOG(logDEBUG)<<"Z+X cand size: "<<ZelVec.size();                                                
    for(size_t i = 0; i < ZelVec.size(); i++)
    {
        LOG(logDEBUG)<<"Calculating Vars for ZelVec";                                                
        m_ZplusEl->updateCutFlow(cutFlowZl::Final, 1);
        
        ParticleMulti* Zel = ZelVec[i];
        m_calculateVar3l->clearVars();

        m_calculateVar3l->setCandIndex(quadIndex);
        quadIndex++;

        auto jetList_xOverlap = RemoveOverlap4l::xJetOverlap(Zel, m_removeOverlapLoose->getJets());


        // give the vars        
        m_calculateVar3l->setZplusL(Zel);
        m_calculateVar3l->setJets(jetList_xOverlap);
        m_calculateVar3l->setMuon(m_removeOverlapLoose->getMuons());
        m_calculateVar3l->setElectron(m_removeOverlapLoose->getElectrons());
        setupMETClass();

        m_calculateVar3l->setCalElCont(m_smearEgamma->getCalElectronCont());
        m_calculateVar3l->setCalPhCont(m_smearEgamma->getCalPhotonCont());
        m_calculateVar3l->process();
        
        m_applyWeight->setJets(jetList_xOverlap);                
        m_applyWeight->fillWeight(Zel);

        m_eventCont->outTree->fillTree(OutputTreeType::ZplusEl);
    }
    // Setting the output tree for event
    m_eventCont->outTree = tempTree;
    
    
}

void Analysisbkg::calcVarHelper()
{
    // To calculate the variables in the minitree
    m_calculateVar->setHiggs(m_higgs);
    m_calculateVar->setJets(m_removeOverlap->getJets());
    m_calculateVar->setMuon(m_removeOverlap->getMuons());
    m_calculateVar->setElectron(m_removeOverlap->getElectrons());
    setupMETClass();

    m_calculateVar->setCalElCont(m_smearEgamma->getCalElectronCont());
    m_calculateVar->setCalPhCont(m_smearEgamma->getCalPhotonCont());
    m_calculateVar->process();

    // Weights
    m_applyWeight->setJets(m_removeOverlap->getJets());            
    m_applyWeight->fillWeight(m_higgs);
}
void Analysisbkg::calcVarHelperSiEl()
{
    // To calculate the variables in the minitree
    m_calculateVar->setHiggs(m_higgs);
    
    auto jetList_xOverlap = RemoveOverlap4l::xJetOverlap(m_higgs, m_removeOverlapLoose->getJets());

    m_calculateVar->setJets(jetList_xOverlap);
    m_calculateVar->setMuon(m_removeOverlapLoose->getMuons());
    m_calculateVar->setElectron(m_removeOverlapLoose->getElectrons());
    setupMETClass();

    m_calculateVar->setCalElCont(m_smearEgamma->getCalElectronCont());
    m_calculateVar->setCalPhCont(m_smearEgamma->getCalPhotonCont());
    m_calculateVar->process();

    // Weights
    m_applyWeight->setJets(jetList_xOverlap);            
    m_applyWeight->fillWeight(m_higgs);
}


void Analysisbkg::calcResults4lCutflow(CutFlow4l* cutFlow, OutputTreeType::OutputTreeType type)
{
    LOG(logDEBUG)<<"Calculating Vars for "<<cutFlow->getCutFlowName();

    if(cutFlow->getHiggsCandNum() > 1)
    {
        LOG(logERROR)<<"Too Many Candidates for "<<cutFlow->getCutFlowName();
        LOG(logERROR)<<"Candidates: "<<cutFlow->getHiggsCandNum();
        exit(1);
    }
    
    m_higgs = cutFlow->getHiggsVec()[0];
    m_calculateVar->clearVars();
    calcVarHelper();
    if(m_eventCont->outTree->isIntVar("prod_type"))
        cutFlow->updateCategory(m_eventCont->outTree->getIntVar("prod_type"));

    cutFlow->updateCutFlow(cutFlow::Final, 1);
    
    m_eventCont->outTree->fillTree(type);
}

void Analysisbkg::printCutFlow()
{
    m_cutMuon->printCutFlow();
    m_cutElectron->printCutFlow();
    m_cutElectronLoose->printCutFlow();
    m_cutJet->printCutFlow();

    m_removeOverlap->printCutFlow();
    m_removeOverlapLoose->printCutFlow();
    
    for(auto cf: m_llmumuCutFlows) cf->printCutFlow();
    for(auto cf: m_bkgCutFlows) cf->printCutFlow();
    for(auto cf: m_lleeCutFlows) cf->printCutFlow();
    for(auto cf: m_3lCutFlows) cf->printCutFlow();
}

// To update the cutflow
void Analysisbkg::updateCutFlow(Int_t cutLevel, Int_t valToAdd)
{
    for(auto cf: m_bkgCutFlows) cf->updateCutFlow(cutLevel, valToAdd);
    for(auto cf: m_llmumuCutFlows) cf->updateCutFlow(cutLevel, valToAdd);
    for(auto cf: m_lleeCutFlows) cf->updateCutFlow(cutLevel, valToAdd);
    for(auto cf: m_3lCutFlows) cf->updateCutFlow(cutLevel, valToAdd);
    
    if(cutLevel == cutFlow::Total)
    {
        m_cutMuon->updateCutFlow(m_muonList.size(), cutLevel);
        m_cutElectron->updateCutFlow(m_electronList.size(), cutLevel);
        m_cutElectronLoose->updateCutFlow(m_electronList.size(), cutLevel);
        m_cutJet->updateCutFlow(m_jetList.size(), cutLevel);
    }
    else if(cutLevel == cutFlow::Preselection || cutLevel == cutFlow::Trigger)
    {
        m_cutMuon->updateCutFlow(m_muonList.size(), cutLevel-1);
        m_cutElectron->updateCutFlow(m_electronList.size(), cutLevel-1);
        m_cutElectronLoose->updateCutFlow(m_electronList.size(), cutLevel-1);
        m_cutJet->updateCutFlow(m_jetList.size(), cutLevel-1);
    }
}

void Analysisbkg::updateHistCutFlow()
{
    m_eventCont->outTree->updateHistVar("mucutFlowHist",    m_cutMuon->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("elcutFlowHist",    m_cutElectron->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("elLoosecutFlowHist",    m_cutElectronLoose->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("jetcutFlowHist",   m_cutJet->getRawCutFlow());
    
}

void Analysisbkg::updateEvtsProc()
{
    // To keep track number of event in the histrogram
    // This is need for normalization for the overall minitree
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 1, 1); // Raw count
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 2, 1 /*get weight*/); // Weight count

    // Just to force the pileup tool to run and fill the corrected averageInteractionsPerInteraction for data
    m_applyWeight->getPileUpWeight();
}

void Analysisbkg::setupMETClass()
{
    m_METCalc->clearVars();
    m_METCalc->setElParticles(m_removeOverlap->getMETElectrons());
    m_METCalc->setMuParticles(m_removeOverlap->getMETMuons());
    m_METCalc->setJetParticles(m_jetList); // need the full jets

}


// For sorting the quards
bool Analysisbkg::sortmZ2 (ParticleQuadlepton* i ,ParticleQuadlepton*j) 
{
    return (fabs(i->getZ2()->getTLV().M() - pdgZMass) < fabs(j->getZ2()->getTLV().M() - pdgZMass)); 
}

// For sorting the quards
bool Analysisbkg::sortmZ2Lep (ParticleMulti* i ,ParticleMulti*j) 
{
    return i->getLep(2)->getTLV().Pt() > j->getLep(2)->getTLV().Pt(); 
}

void Analysisbkg::fillMetaData()
{
    string productionRelease = "";
    string amiTag = "";
    string dataType = "";
    string geometryVersion = "";
    string conditionsTag = "";

    if (m_eventCont->getEvent()->containsMeta<xAOD::FileMetaData>("FileMetaData")) 
    {
        const xAOD::FileMetaData* fmd = 0;
        if(m_eventCont->getEvent()->retrieveMetaInput(fmd, "FileMetaData"))
        {
            LOG(logINFO)<<"fillMetaData: metaData found";

            fmd->value( xAOD::FileMetaData::productionRelease, productionRelease);
            fmd->value( xAOD::FileMetaData::amiTag, amiTag);
            fmd->value( xAOD::FileMetaData::dataType, dataType);
            fmd->value( xAOD::FileMetaData::geometryVersion, geometryVersion);
            fmd->value( xAOD::FileMetaData::conditionsTag, conditionsTag);

        }
    }


    // Fill in the metaData
    // Initialization of the output trees
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        OutputTree* outTree = m_outTreeMap[sysListItr];
        outTree->updateMetaData<int>("isMC", m_eventCont->isMC);

        // Tree type
        TString sysName(sysListItr.name());
        outTree->updateMetaData<int>("type", miniTreeType::BkgCR);

        outTree->updateMetaData<int>("createdBy", 0);
        
        outTree->updateMetaData<string>("sampleName", m_eventCont->fileName.Data());
        outTree->updateMetaData<string>("version", m_version.Data());
        outTree->updateMetaData<string>("comment", m_comment.Data());
        outTree->updateMetaData<string>("systematicVariation", sysName.Data());

        outTree->updateMetaData<string>("productionRelease", productionRelease);
        outTree->updateMetaData<string>("amiTag", amiTag);
        outTree->updateMetaData<string>("dataType", dataType);
        outTree->updateMetaData<string>("geometryVersion", geometryVersion);
        outTree->updateMetaData<string>("conditionsTag", conditionsTag);

        outTree->fillMetaData();
    }


    // Initialization of the output trees
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        OutputTree* outTree = m_outTree3lMap[sysListItr];

        outTree->updateMetaData<int>("isMC", m_eventCont->isMC);

        // Tree type
        TString sysName(sysListItr.name());
        outTree->updateMetaData<int>("type", miniTreeType::BkgCRZpl);

        outTree->updateMetaData<int>("createdBy", 0);

        outTree->updateMetaData<string>("sampleName", m_eventCont->fileName.Data());
        outTree->updateMetaData<string>("version", m_version.Data());
        outTree->updateMetaData<string>("comment", m_comment.Data());
        outTree->updateMetaData<string>("sys_variation", sysName.Data());

        outTree->updateMetaData<string>("productionRelease", productionRelease);
        outTree->updateMetaData<string>("amiTag", amiTag);
        outTree->updateMetaData<string>("dataType", dataType);
        outTree->updateMetaData<string>("geometryVersion", geometryVersion);
        outTree->updateMetaData<string>("conditionsTag", conditionsTag);

        outTree->fillMetaData();
    }
}
