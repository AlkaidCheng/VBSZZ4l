#include "H4lCutFlow/AnalysisFiducial.h"
using namespace std;

// Constructor
AnalysisFiducial::AnalysisFiducial()
    :AnalysisBase()
{
    m_eventCont->doSmear = false;
}

// Destructor
AnalysisFiducial::~AnalysisFiducial()
{
    
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        // Deleting the output minitree
        delete m_outTreeMap[sysListItr];
    }
    
    //if(m_dataPreSel)      delete m_dataPreSel;
    //if(m_preSel)          delete m_preSel;
    
    //if(m_cutMuon)         delete m_cutMuon;
    //if(m_cutElectron)     delete m_cutElectron;
    if(m_cutJetTruthFid)  delete m_cutJetTruthFid;
    //if(m_cutWZJetTruthFid)  delete m_cutWZJetTruthFid;
    //if(m_removeOverlap)   delete m_removeOverlap;
    if(m_cutFlow4l)       delete m_cutFlow4l;
    if(m_cutFlow4mu)      delete m_cutFlow4mu;
    if(m_cutFlow2mu2e)    delete m_cutFlow2mu2e;
    if(m_cutFlow2e2mu)    delete m_cutFlow2e2mu;
    if(m_cutFlow4e)       delete m_cutFlow4e;
    
    if(m_applyWeight)     delete m_applyWeight;
    
    if(m_calculateVar)    delete m_calculateVar;
    
    if(m_truthHelper)     delete m_truthHelper;
    if(tool4l) delete tool4l;

}


// For intializating that depends after variables
// have been setup from the job and after the first 
// event has been read
// Typically all classes are expected to be created
// and intialized here
void AnalysisFiducial::initialize()
{
    
    m_eventCont->initialize();
    
    tool4l = new ToolInit4l(m_eventCont);
    tool4l->initialize();
    m_toolBase = (ToolInitBase*) tool4l;
    
    AnalysisBase::initialize();
    
    // Constructor
    //m_dataPreSel  = new CutEventDataPreSel(m_eventCont);
    //m_preSel      = new CutEventPreSel(m_eventCont);
    //m_cutMuon             = new CutParticleMuon(m_eventCont);
    //m_cutElectron         = new CutParticleElectron(m_eventCont);
    m_cutJetTruthFid      = new CutParticleJet(m_eventCont);
    m_cutJetTruthFid->setJetSelType(CutParticleJet::FiducialTruth);
    //m_cutWZJetTruthFid      = new CutParticleJet(m_eventCont);
    //m_cutWZJetTruthFid->setJetSelType(CutParticleJet::FiducialTruth);

    //m_removeOverlap = new RemoveOverlap4l(m_eventCont);
    
    m_applyWeight   = new ApplyWeight4l(m_eventCont);
    
    m_cutFlow4l    = new CutFlow4lFiducial(m_eventCont, m_applyWeight);
    m_cutFlow4mu   = new CutFlow4lFiducial(m_eventCont, m_applyWeight);
    m_cutFlow4mu->setQuadAnalysisType(QuadleptonType::_4mu);
    
    m_cutFlow2mu2e = new CutFlow4lFiducial(m_eventCont, m_applyWeight);
    m_cutFlow2mu2e->setQuadAnalysisType(QuadleptonType::_2mu2e);
    
    m_cutFlow2e2mu = new CutFlow4lFiducial(m_eventCont, m_applyWeight);
    m_cutFlow2e2mu->setQuadAnalysisType(QuadleptonType::_2e2mu);
    
    m_cutFlow4e    = new CutFlow4lFiducial(m_eventCont, m_applyWeight);
    m_cutFlow4e->setQuadAnalysisType(QuadleptonType::_4e);

    m_calculateVar = new CalculateVar4lInclusive(m_eventCont);
    
    m_truthHelper = new TruthHelper(m_eventCont);

    addSystematicsSet();
    
    // Set of initialization - to be called only by the derived class
    // This is intended to setup any thing after all the tools have be initialized
    // Mainly will be used for any setup dependant on systematics
    //m_dataPreSel->initialize();
    //m_preSel->initialize();
    //m_cutMuon->initialize();
    //m_cutElectron->initialize();
    m_cutJetTruthFid->initialize();
    //m_cutWZJetTruthFid->initialize();

    //m_removeOverlap->initialize();
    m_applyWeight->initialize();
    m_calculateVar->initialize();
    
    m_cutFlow4l->initialize();
    m_cutFlow4mu->initialize();
    m_cutFlow2mu2e->initialize();
    m_cutFlow2e2mu->initialize();
    m_cutFlow4e->initialize();
    // Initialization of the output trees
    
    for (auto sysListItr:m_eventCont->m_sysList){
        OutputTree4lInclusive* outTree
        =  new OutputTree4lInclusive(m_eventCont->outputBaseName, (sysListItr).name(), m_eventCont->fileName);
        
       outTree->setIsMC(m_eventCont->isMC); 

       if(getCmdArg("truthLeptonType") == "dressed")   {outTree->setLeptonType("Dres"); }
       else if(getCmdArg("truthLeptonType") == "born") {outTree->setLeptonType("Born"); }
       else if(getCmdArg("truthLeptonType") == "bare") {outTree->setLeptonType("Bare"); }
       else {outTree->setLeptonType("Unkn");}

       // Check if this cross-section is avaliable in the tool
       Int_t DSID = m_eventCont->getDSID();
       // Some truth derivation are weird... they store DSID in runNumber
       // Max provided this fix
       // if(m_eventCont->m_isDAODTRUTH && DSID == 0) DSID = m_eventCont->eventInfo->runNumber();        
       if(m_eventCont->isMC) outTree->setRunNumber(DSID);
       if(getCmdArg("addTheoryVar") == "true") outTree->addVariationSpecificVar();
       outTree->initialize();
       m_outTreeMap[sysListItr] = (OutputTree*) outTree;
    }
    LOG(logINFO) << "Truth Lepton Type: " << getCmdArg("truthLeptonType") ;
    LOG(logINFO) << "Do Mass Window Cut: " << getCmdArg("doMassWindowCut") ;
    LOG(logINFO) << "Add Scale/PDF weights: " << getCmdArg("addTheoryVar") ;

}


/// Event preselection cuts are implemented here
/// Expected cuts: dataPreselection, selection and trigger cuts
Bool_t AnalysisFiducial::eventPreSelection()
{
    if(m_eventCont->isMC)
    {
    	m_eventCont->outTree->updateHistVar("truthQuadType", m_truthHelper->getTruthHiggsType());
    }
    updateCutFlow(cutFlow::Total);
    // No data- skip this cut
    //if(!m_dataPreSel->passCut()) return false;
    updateCutFlow(cutFlow::DataPreselection);
    
    // Fiducial selection does not do vertex cut - skip this cut
    //if(!m_preSel->passCut()) return false;
    updateCutFlow(cutFlow::Preselection);
    
    // No triggers in fiducial analysis - skip this cut
    //if(!m_trigger->passCut()) return false;
    updateCutFlow(cutFlow::Trigger);


    return true;
}

void AnalysisFiducial::clearVars()
{
    AnalysisBase::clearVars();
    
    //m_cutMuon->clearVars();
    //m_cutElectron->clearVars();
    m_cutJetTruthFid->clearVars();
    //m_cutWZJetTruthFid->clearVars();
    
    //m_removeOverlap->clearVars();
    
    m_cutFlow4l->clearVars();
    m_cutFlow4mu->clearVars();
    m_cutFlow2mu2e->clearVars();
    m_cutFlow2e2mu->clearVars();
    m_cutFlow4e->clearVars();

    m_calculateVar->clearVars();
    m_truthHelper->clearVars();
    m_applyWeight->clearVars();

    m_higgs = 0;
    m_higgs_fid = 0;
    m_passCutflow = false;

    m_fidMuonsList.clear();
    m_fidElectronsList.clear();
    m_fidJetsList.clear();
    //m_fidWZJetsList.clear();

}

void AnalysisFiducial::smearPhyObjects()
{
    setAnalType();
    //cout << "Debug 1" << endl;
}

void AnalysisFiducial::setAnalType()
{

    //for(Int_t i = 0; i < (Int_t) m_truthList.size(); i++)
    //    m_truthList[i]->setAnalysisType(m_eventCont->m_analType);
}

void AnalysisFiducial::selectPhyObjects()
{
    
    ParticleQuadlepton* truthBareHiggs = m_truthHelper->getBareQuadlepton();
    if(getCmdArg("truthLeptonType") == "bare"){
        m_higgs = truthBareHiggs;
    } 
    else if(getCmdArg("truthLeptonType") == "born"){
        m_higgs = m_truthHelper->getBornQuadlepton(truthBareHiggs);
    } 
    else if(getCmdArg("truthLeptonType") == "dressed"){
        m_higgs = m_truthHelper->getDressedQuadlepton(truthBareHiggs);
    } 
    else {
        LOG(logERROR)<<"AnalysisFiducial::selectPhyObjects() - No truth lepton type called " << getCmdArg("truthLeptonType") <<  "! Must be bare, born, or dressed.";
        exit(-1);
    }

    if(m_higgs)
    {
        vector<ParticleVar*> truthParticles;
        if(getCmdArg("truthLeptonType") == "bare"){
            truthParticles = m_truthHelper->getBareParticleVarFromBoson();
        } 
        else if(getCmdArg("truthLeptonType") == "born"){
            truthParticles = m_truthHelper->getBornLeptonsFromBoson();
        } 
        else if(getCmdArg("truthLeptonType") == "dressed"){
            truthParticles = m_truthHelper->getDressedLeptonsFromBoson();
        } 
        else {
            LOG(logERROR)<<"AnalysisFiducial::selectPhyObjects() - No truth lepton type called " << getCmdArg("truthLeptonType") <<  "! Must be bare, born, or dressed.";
            exit(-1);
        }
        
        std::vector<ParticleVar*> allMuons;
        std::vector<ParticleVar*> allElectrons;
        for(unsigned int i = 0; i < truthParticles.size(); i++) {
            if(truthParticles[i]->getName() == "Truth") {
                if(abs(truthParticles[i]->getTruthPID()) == 11) allElectrons.push_back(truthParticles[i]);
                else if(abs(truthParticles[i]->getTruthPID()) == 13) allMuons.push_back(truthParticles[i]);
            }
        }
    
        //m_cutMuon->updateCutFlow      	  (m_removeOverlap->getMuons().size(),      muCut::OverLap);
        //m_cutElectron->updateCutFlow  	  (m_removeOverlap->getElectrons().size(),  elCut::OverLap);
        //m_cutJetTruthFid->updateCutFlow       (m_removeOverlap->getJets().size(),       jetCut::OverLap);

        m_fidMuonsList = chooseFidMuons(allMuons);
        m_fidElectronsList = chooseFidElectrons(allElectrons);

        m_cutJetTruthFid->setParticles(m_truthJetList);
        m_cutJetTruthFid->process();
        m_fidJetsList = removeOverlapFidJets(m_cutJetTruthFid->getParticles(),m_fidElectronsList, m_fidMuonsList);

        LOG(logDEBUG) << "Number of fid elctrons: " << m_fidElectronsList.size() << " Number of fid muons : " << m_fidMuonsList.size() << " Number of fid jets: " << m_fidJetsList.size();
    }
}


Bool_t AnalysisFiducial::eventSelection()
{
    if(!m_higgs)
    {
        LOG(logERROR)<<"AnalysisFiducial::eventSelection() - No truth Higgs found in event " << m_eventCont->eventInfo->eventNumber() <<  "!";
        return false;
    }

    m_passCutflow = false;

    if (getCmdArg("doMassWindowCut")=="false") 
    {
        m_cutFlow4l->disableMassWindowCut();
        m_cutFlow4mu->disableMassWindowCut();
        m_cutFlow2mu2e->disableMassWindowCut();
        m_cutFlow2e2mu->disableMassWindowCut();
        m_cutFlow4e->disableMassWindowCut();
    }

    // Cut for the quadlepton for each flavour
    // This is to mimic the run 1 type selection
    m_cutFlow4mu->setMuons(m_fidMuonsList);
    m_cutFlow4mu->setElectrons(m_fidElectronsList);
    m_cutFlow4mu->process();

    m_cutFlow2e2mu->setMuons(m_fidMuonsList);
    m_cutFlow2e2mu->setElectrons(m_fidElectronsList);
    m_cutFlow2e2mu->process();

    m_cutFlow2mu2e->setMuons(m_fidMuonsList);
    m_cutFlow2mu2e->setElectrons(m_fidElectronsList);
    m_cutFlow2mu2e->process();

    m_cutFlow4e->setMuons(m_fidMuonsList);
    m_cutFlow4e->setElectrons(m_fidElectronsList);
    m_cutFlow4e->process();

    m_cutFlow4l->setMuons(m_fidMuonsList);
    m_cutFlow4l->setElectrons(m_fidElectronsList);
    m_cutFlow4l->process();

    cutFlow::cutFlow lastCut = cutFlow::JPsiVeto;
    //cutFlow::cutFlow lastCut = cutFlow::Z1Mass;
    
    // For run 1 type selection
    if(m_cutFlow4mu->getLastCutPassed() == lastCut)
    {
        m_passCutflow = true;
        m_higgs_fid = m_cutFlow4mu->getHiggsCandidate();
	    m_cutFlow4mu->updateCutFlow(cutFlow::Final, 1);
    }
    else if(m_cutFlow2e2mu->getLastCutPassed() == lastCut)
    {
        m_passCutflow = true;
        m_higgs_fid = m_cutFlow2e2mu->getHiggsCandidate();
	    m_cutFlow2e2mu->updateCutFlow(cutFlow::Final, 1);
    }
    else if(m_cutFlow2mu2e->getLastCutPassed() == lastCut)
    {
        m_passCutflow = true;
        m_higgs_fid = m_cutFlow2mu2e->getHiggsCandidate();
	    m_cutFlow2mu2e->updateCutFlow(cutFlow::Final, 1);
    }
    else if(m_cutFlow4e->getLastCutPassed() == lastCut)
    {
        m_passCutflow = true;
        m_higgs_fid = m_cutFlow4e->getHiggsCandidate();
	    m_cutFlow4e->updateCutFlow(cutFlow::Final, 1);
    }

    if(m_passCutflow) m_cutFlow4l->updateCutFlow(cutFlow::Final, 1);
    
    return true;
}

void AnalysisFiducial::calcVars()
{
   if(getCmdArg("truthLeptonType") == "dressed")   { m_calculateVar->setLeptonType("Dres"); }
   else if(getCmdArg("truthLeptonType") == "born") { m_calculateVar->setLeptonType("Born"); }
   else if(getCmdArg("truthLeptonType") == "bare") { m_calculateVar->setLeptonType("Bare"); }
   else {m_calculateVar->setLeptonType("Unkn");}
    // To calculate the variables in the minitree
    m_calculateVar->setHiggs(m_higgs);
    if(m_passCutflow) m_calculateVar->setHiggsFiducial(m_higgs_fid);
    else m_calculateVar->setHiggsFiducial(0);
    m_calculateVar->setJets(m_fidJetsList);
    //m_calculateVar->setWZJets(m_fidWZJetsList);
 
    //m_calculateVar0;
    m_calculateVar->process(m_passCutflow);

    //OutputTree4lFiducial* outTree = dynamic_cast<OutputTree4lFiducial*>(m_eventCont->outTree);
    //OutputTree4lInclusive* outTree = dynamic_cast<OutputTree4lInclusive*>(m_eventCont->outTree);
    
    Int_t prodType = m_eventCont->outTree->getIntVar("prod_type");
    

    // Update the production type numbers
    if(m_higgs->getQuadType() == QuadleptonType::_4mu)
    {
        m_cutFlow4mu->setHiggsCandidate(m_higgs);
        m_cutFlow4mu->updateCategory(prodType);
    }
    else if(m_higgs->getQuadType() == QuadleptonType::_2mu2e)
    {
        m_cutFlow2mu2e->setHiggsCandidate(m_higgs);
        m_cutFlow2mu2e->updateCategory(prodType);
    }
    else if(m_higgs->getQuadType() == QuadleptonType::_2e2mu)
    {
        m_cutFlow2e2mu->setHiggsCandidate(m_higgs);
        m_cutFlow2e2mu->updateCategory(prodType);
    }
    else if(m_higgs->getQuadType() == QuadleptonType::_4e)
    {
        m_cutFlow4e->setHiggsCandidate(m_higgs);
        m_cutFlow4e->updateCategory(prodType);
    }
    
    // Weight
    m_applyWeight->fillWeight(m_higgs);
    if(getCmdArg("addTheoryVar") == "true") m_applyWeight->fillTheoryVariationWeight();
    
    
    // Writing it to the tree
    m_eventCont->outTree->fillTree(OutputTreeType::NA);
}

void AnalysisFiducial::printCutFlow()
{

    m_cutJetTruthFid->printCutFlow();
    //m_cutWZJetTruthFid->printCutFlow();

    m_cutFlow4mu->printCutFlow();
    m_cutFlow2e2mu->printCutFlow();
    m_cutFlow2mu2e->printCutFlow();
    m_cutFlow4e->printCutFlow();
}

// To update the cutflow
void AnalysisFiducial::updateCutFlow(Int_t cutLevel, Int_t valToAdd)
{
    m_cutFlow4l->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow4mu->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow2mu2e->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow2e2mu->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow4e->updateCutFlow(cutLevel, valToAdd);

}

void AnalysisFiducial::updateHistCutFlow()
{
    m_eventCont->outTree->updateHistVar("4lcutFlowHist",    m_cutFlow4l->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("4mucutFlowHist",   m_cutFlow4mu->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("2mu2ecutFlowHist", m_cutFlow2mu2e->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("2e2mucutFlowHist", m_cutFlow2e2mu->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("4ecutFlowHist",    m_cutFlow4e->getRawCutFlow());


    m_eventCont->outTree->updateHistVar("4mucutFlowWHist",   m_cutFlow4mu->getWeightedCutFlow());
    m_eventCont->outTree->updateHistVar("2mu2ecutFlowWHist", m_cutFlow2mu2e->getWeightedCutFlow());
    m_eventCont->outTree->updateHistVar("2e2mucutFlowWHist", m_cutFlow2e2mu->getWeightedCutFlow());
    m_eventCont->outTree->updateHistVar("4ecutFlowWHist",    m_cutFlow4e->getWeightedCutFlow());

}

Bool_t AnalysisFiducial::checkPairingOverlap(LepCombBase* partOne, LepCombBase* partTwo)
{
    if(partOne->getLepSize() != partTwo->getLepSize()) return false;
    
    for(Int_t i = 0; i < partOne->getLepSize(); i++)
    {
        if(partOne->getLep(i) != partTwo->getLep(i)) return false;
    }
    
    return true;
}

Bool_t AnalysisFiducial::checkAllOverlap(LepCombBase* partOne, LepCombBase* partTwo)
{
    if(partOne->getLepSize() != partTwo->getLepSize()) return false;
    
    Bool_t overlap = true;
    
    for(Int_t i = 0; i < partOne->getLepSize(); i++)
    {
        Bool_t lepOverlap = false;
        for(Int_t j = 0; j < partTwo->getLepSize(); j++)
        {
            if(partOne->getLep(i) == partTwo->getLep(j)) lepOverlap = true;
        }
        overlap = overlap & lepOverlap;
    }
    
    return overlap;
}

void AnalysisFiducial::updateEvtsProc()
{
    // To keep track number of event in the histrogram
    // This is need for normalization for the overall minitree
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 1, 1); // Raw count
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 2, m_applyWeight->getEventWeight() /*get weight*/); // Weight count
    if(m_eventCont->m_isDAODTRUTH) { //assume truth DAOD make no cuts on events generated
        if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 3, 1); // Raw count
        if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 4, 1); // Raw count
        if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 5, m_applyWeight->getEventWeight() /*get weight*/); // Weight count
        if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 6, m_applyWeight->getEventWeight() /*get weight*/); // Weight count
        m_applyWeight->fillVariationHist();
    }
}

vector<ParticleVar*> AnalysisFiducial::chooseFidElectrons(vector<ParticleVar*> truthElectrons)
{
    vector<ParticleVar*> fidElectrons;
    for(unsigned int i = 0; i < truthElectrons.size(); i++) {
        bool passCut = true;
        if(truthElectrons[i]->getTLV().Pt() < 7000) passCut = false;
        if(fabs(truthElectrons[i]->getTLV().Eta()) > 2.47) passCut = false;
        if(passCut) { fidElectrons.push_back(truthElectrons[i]);
        LOG(logDEBUG) << "Found fiducial electron with pT: "<<truthElectrons[i]->getTLV().Pt()
        <<" eta: "<<truthElectrons[i]->getTLV().Eta()
        <<" phi: "<<truthElectrons[i]->getTLV().Phi()
        <<" charge: "<<truthElectrons[i]->getCharge();
        }
    }
    return fidElectrons;
}

vector<ParticleVar*> AnalysisFiducial::chooseFidMuons(vector<ParticleVar*> truthMuons)
{
    vector<ParticleVar*> fidMuons;
    for(unsigned int i = 0; i < truthMuons.size(); i++) {
        bool passCut = true;
        if(truthMuons[i]->getTLV().Pt() < 5000) passCut = false;
        if(fabs(truthMuons[i]->getTLV().Eta()) > 2.7) passCut = false;
        if(passCut) { fidMuons.push_back(truthMuons[i]);
        LOG(logDEBUG) << "Found fiducial muon with pT: "<<truthMuons[i]->getTLV().Pt()
        <<" eta: "<<truthMuons[i]->getTLV().Eta()
        <<" phi: "<<truthMuons[i]->getTLV().Phi()
        <<" charge: "<<truthMuons[i]->getCharge();
        }
    }
    return fidMuons;
}

vector<ParticleVar*> AnalysisFiducial::removeOverlapFidJets(vector<ParticleVar*> truthJets, vector<ParticleVar*> fidElectrons, vector<ParticleVar*> fidMuons)
{
    vector<ParticleVar*> fidJets;
    for(unsigned int i = 0; i < truthJets.size(); i++) 
    {
        bool noOverlap = true;
        //overlap removal with the truth higgs leptons, but not for inclusive analysis
        if(getCmdArg("truthLeptonType") != "born"){
         //overlap removal with the truth higgs leptons
             //for(int j = 0; j < 4; j++)
             //{
             //    double deltaRJetLep = DeltaR(truthJets[i]->getTLV().Eta(),truthJets[i]->getTLV().Phi(),
             //                                m_higgs->getLep(j)->getTLV().Eta(),m_higgs->getLep(j)->getTLV().Phi());
             //    if(deltaRJetLep < 0.4) { noOverlap = false; break; }
             //}
            //overlap removal with fiducial electrons
            for(unsigned int j = 0; j < fidElectrons.size(); j++) {
                double deltaRJetElectron = DeltaR(truthJets[i]->getTLV().Eta(),truthJets[i]->getTLV().Phi(),
                                                 fidElectrons[j]->getTLV().Eta(),fidElectrons[j]->getTLV().Phi());
                if(deltaRJetElectron < 0.2) { noOverlap = false; break; }
            }
            for(unsigned int j = 0; j < fidMuons.size(); j++) {
                double deltaRJetMuon = DeltaR(truthJets[i]->getTLV().Eta(),truthJets[i]->getTLV().Phi(),
                                                 fidMuons[j]->getTLV().Eta(),fidMuons[j]->getTLV().Phi());
                if(deltaRJetMuon < 0.1) { noOverlap = false; break; }
            }
        }
        if(noOverlap) {
        fidJets.push_back(truthJets[i]);
        LOG(logDEBUG) << "Found fiducial jet with pT: "<<truthJets[i]->getTLV().Pt()
        <<" rap: "<<truthJets[i]->getTLV().Rapidity()
        <<" phi: "<<truthJets[i]->getTLV().Phi()
        <<" charge: "<<truthJets[i]->getCharge();
        }
    }
    return fidJets;
}

Double_t AnalysisFiducial::DeltaR (Double_t eta_1, Double_t phi_1, Double_t eta_2, Double_t phi_2)
{
    Double_t dR=0;
    Double_t eta2 = (eta_1-eta_2)*(eta_1-eta_2);
    Double_t tmp_dphi = (fabs(phi_1-phi_2) > TMath::Pi()) ? 2*TMath::Pi()-fabs(phi_1-phi_2) : fabs(phi_1-phi_2);
    Double_t phi2 = tmp_dphi*tmp_dphi;
    dR = sqrt( eta2 + phi2 );
    return dR;
}

void AnalysisFiducial::fillMetaData()
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
        outTree->updateMetaData<int>("type", miniTreeType::Fiducial);
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
}
