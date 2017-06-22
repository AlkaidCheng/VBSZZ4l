#include "HZZCutCommon/AnalysisBase.h"

using namespace std;

// Constructor
AnalysisBase::AnalysisBase()
{
    // Intializing the event info
    m_eventCont = new EventContainer();
    
    // configurable from the outside world
    m_eventCont->m_analType = AnalysisType::Nominal;
    m_eventCont->doSmear = true;
    m_smearMuon = 0;    
    m_smearJet = 0;     
    m_smearEgamma = 0;  
    m_smearTau = 0;     

    m_doSys = false;
    
    hasInitializedDebug = false;
    
    m_nEventTest = -1;

    m_version = "";
    m_comment = "";

    m_opts.clear();
}

// Destructor
AnalysisBase::~AnalysisBase()
{
    if(m_eventCont)       delete m_eventCont;

    if(m_smearMuon)       delete m_smearMuon;
    if(m_smearJet)        delete m_smearJet;
    if(m_smearEgamma)     delete m_smearEgamma;
    if(m_smearTau)        delete m_smearTau;

}


// For intializating that depends after variables
// have been setup from the job and after the first 
// event has been read
// Typically all classes are expected to be created
// and intialized here
void AnalysisBase::initialize()
{
    if(!m_eventCont || !m_eventCont->hasInit)
    {
        LOG(logERROR) << "EventContainer not intialized. This is the responsibility of the derived class";
        exit(1);
    }
    
    if(!m_toolBase || !m_toolBase->hasInit)
    {
        LOG(logERROR) << "ToolInitBase not intialized. This is the responsibility of the derived class";
        exit(1);
    }

    if(m_eventCont->m_analType == AnalysisType::Fiducial)
    {
        LOG(logWARNING) << "Fiducial Analysis - Will not do Smearing.";
    } 
    else 
    {
        m_smearMuon   = new SmearingMuon(m_eventCont);
        m_smearJet    = new SmearingJet(m_eventCont);
        m_smearEgamma = new SmearingEgamma(m_eventCont);
        m_smearTau    = new SmearingTau(m_eventCont);

        m_smearMuon->initialize();
        m_smearJet->initialize();
        m_smearEgamma->initialize();
        m_smearTau->initialize();
    }
}

// Main event loop
Bool_t AnalysisBase::process()
{
    
    // Initialization
    // Event container loads event zero and reads the meta-data
    initialize();
   
    // Retrive the pileup tool for later usage
    m_pileupTool = ToolHandle<CP::IPileupReweightingTool>("PileupTool");
    if(m_pileupTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight::ApplyWeight() - cannot retrieve IPileupReweightingTool";
        exit(1);
    }


    Int_t nEvents = m_eventCont->getEvent()->getEntries();
    LOG(logINFO) <<"Num Event = "<<nEvents;
    
    // Listing the variations configured for this job
    LOG(logINFO)<<"Variation configured for this job";
    for (auto sysListItr:m_eventCont->m_sysList){
        if((sysListItr).name()=="") LOG(logINFO)<< "Nominal (no syst) ";
        else LOG(logINFO) << "Systematic: " << (sysListItr).name();
    }
    
    if(m_nEventTest != -1)
    {
        nEvents = m_nEventTest;
        LOG(logINFO) <<"Running over "<<m_nEventTest<<" events";

    }
    
    // Main event loop
    for(Int_t i = 0; i < nEvents; i++)
    {
        if((i % 500) == 0)
        {
           LOG(logINFO) <<"Processing event "<<i; 
        }
        
        m_eventCont->getEntry(i);
        
        //LOG(logINFO) <<"Processing event "<<i<<" eventNumber: "<<m_eventCont->eventInfo->eventNumber();
        
        for (auto sysListItr:m_eventCont->m_sysList)
        {
            // Setting the curr variation so tools can setup based on this    
            m_eventCont->m_currVariation = sysListItr;
            
            // Setting the output tree for event
            m_eventCont->outTree = m_outTreeMap[sysListItr];

            // Processing the event
            processEvent();
        }
    }

    finalize();

    return true;
}

void AnalysisBase::finalize()
{
    fillMetaData();

    // Output trees are saved here
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        m_eventCont->m_currVariation = sysListItr;
        m_eventCont->outTree = m_outTreeMap[sysListItr];
        // Do the last filling of events
        m_eventCont->fillEventHist();
        // Any cutflow histrograms are copied to output
        // if need by the analysis
        updateHistCutFlow();
        
        if(m_eventCont->outTree) m_eventCont->outTree->writeTree();
    }
}


// Cuts that are implemented for a given event
Bool_t AnalysisBase::processEvent()
{
    // Clear vars 
    clearVars();

    initEvent();
    
    updateEvtsProc();
    // Fill Physics objects
    if (!fillPhyObjects()) return false;
    // Preselection cuts
    if (!eventPreSelection()) return false;
    // Smearing
    if (m_eventCont->doSmear) smearPhyObjects();
    // Selection cuts on individual physics objects
    selectPhyObjects();
    // Main Event selection
    if (!eventSelection()) return false;
    // To calculate the variables
    calcVars();
    
    return true;
}

void AnalysisBase::initEvent()
{
    if(m_eventCont->m_isDAODTRUTH)
    {
        if(m_eventCont->m_eventIndex == 0) {LOG(logWARNING)<<"DAOD_TRUTH - skipping assiging data period, trigger won't be correct";}
        return;
    }
    // trigger the pileup tool
    // Since everything is run number dependant, we pretty much always want this to happen
    //m_pileupTool->apply(*m_eventCont->eventInfo, false).ignore();  
    m_pileupTool->apply(*m_eventCont->eventInfo).ignore();  


    // For triggers
    int runNumber = -1;

    if(m_eventCont->isMC)
    {
        runNumber =  m_eventCont->eventInfo->auxdecor<unsigned int>("RandomRunNumber");
    }
    else
    {
        runNumber = m_eventCont->eventInfo->runNumber();        
    }

    m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") = runNumber;

    //aLOG(logINFO)<<"runNumber: "<<runNumber;

    // For data periods
    if(runNumber <= 276954) m_eventCont->m_dataPeriod = Periods::periodD2015;
    else if(runNumber <= 279928) m_eventCont->m_dataPeriod = Periods::periodE2015;
    else if(runNumber <= 280422) m_eventCont->m_dataPeriod = Periods::periodF2015;
    else if(runNumber <= 281075) m_eventCont->m_dataPeriod = Periods::periodG2015;
    else if(runNumber <= 281411) m_eventCont->m_dataPeriod = Periods::periodH2015;
    else if(runNumber <= 282482) m_eventCont->m_dataPeriod = Periods::periodI2015;
    else if(runNumber <= 284484) m_eventCont->m_dataPeriod = Periods::periodJ2015;
    else if(runNumber <= 300287) m_eventCont->m_dataPeriod = Periods::periodA2016;
    else if(runNumber <= 300908) m_eventCont->m_dataPeriod = Periods::periodB2016;
    else if(runNumber <= 302393) m_eventCont->m_dataPeriod = Periods::periodC2016;
    else if(runNumber <= 303560) m_eventCont->m_dataPeriod = Periods::periodD2016;
    else if(runNumber <= 303892) m_eventCont->m_dataPeriod = Periods::periodE2016;
    else if(runNumber <= 304494) m_eventCont->m_dataPeriod = Periods::periodF2016;
    else if(runNumber <= 306714) m_eventCont->m_dataPeriod = Periods::periodG2016;
    else if(runNumber <= 308084) m_eventCont->m_dataPeriod = Periods::periodI2016;
    else if(runNumber <= 309166) m_eventCont->m_dataPeriod = Periods::periodJ2016;
    else if(runNumber <= 309759) m_eventCont->m_dataPeriod = Periods::periodK2016;
    //else if(runNumber <= 305359) m_eventCont->m_dataPeriod = Periods::periodH2016;
    else m_eventCont->m_dataPeriod = Periods::periodL2016;

    // For trigger
    if(m_eventCont->m_dataPeriod == Periods::periodD2015) m_eventCont->m_trigPeriod = TrigPeriods::trig_2015_D;
    else if(m_eventCont->m_dataPeriod <= Periods::periodJ2015) m_eventCont->m_trigPeriod = TrigPeriods::trig_2015_EtoJ;
    else m_eventCont->m_trigPeriod = TrigPeriods::trig_2016_A;

}


// Electrons, muons, jets and photons are read and filled into
// container classes
Bool_t AnalysisBase::fillPhyObjects()
{
    if(!m_eventCont->m_isDAODTRUTH)
    {
        // Retrieving the containers and filling it in local particle containers
        if(!m_eventCont->getEvent()->retrieve( m_muonCont, "Muons" ).isSuccess())
        {
            LOG(logERROR)<<"AnalysisBase::fillPhyObjects - Failed to retrieve the Muon Container";
            exit(1);
        }
        fillMuon(m_muonCont);

        if(!m_eventCont->getEvent()->retrieve( m_phCont, "Photons" ).isSuccess())
        {
            LOG(logERROR)<<"AnalysisBase::fillPhyObjects - Failed to retrieve the Photon Container";
            exit(1);
        }
        fillPhoton(m_phCont);

        if(!m_eventCont->getEvent()->retrieve( m_elCont, "Electrons" ).isSuccess())
        {
            LOG(logERROR)<<"AnalysisBase::fillPhyObjects - Failed to retrieve the Electron Container";
            exit(1);
        }
        fillElectron(m_elCont);

        if(!m_eventCont->getEvent()->retrieve( m_jetCont, "AntiKt4EMTopoJets" ).isSuccess())
        {
            LOG(logERROR)<<"AnalysisBase::fillPhyObjects - Failed to retrieve the Jet Container";
            exit(1);
        }
        fillJet(m_jetCont);
    }
    else
    {
        if(m_eventCont->m_eventIndex == 0) {LOG(logWARNING)<<"DAOD_TRUTH - skipping filling of reco particles";}
    }


    if(m_eventCont->isMC)
    {
        if(m_eventCont->m_isAOD || m_eventCont->m_isDAODTRUTH) {
            if(!m_eventCont->getEvent()->retrieve( m_truthJetCont, "AntiKt4TruthWZJets" ).isSuccess())
            {
                LOG(logERROR)<<"AnalysisBase::fillPhyObjects - Failed to retrieve the truth jet Container";
                exit(1);
            }
        }
        else {
            if(!m_eventCont->getEvent()->retrieve( m_truthJetCont, "AntiKt4TruthJets" ).isSuccess())
            {
                LOG(logERROR)<<"AnalysisBase::fillPhyObjects - Failed to retrieve the truth jet Container";
                exit(1);
            }
        }
        fillTruthJet(m_truthJetCont);
        
    }
    
    // For taus
    // Recipe for taus
//    RETURN_CHECK("AnalysisBase::process", m_eventCont->getEvent()->retrieve( m_tauCont, "TauJets" ) );
//    RETURN_CHECK("AnalysisBase::process", m_eventCont->getEvent()->retrieve( m_tauTrackPartCont , "InDetTrackParticles" ) );
//    RETURN_CHECK("AnalysisBase::process", m_eventCont->getEvent()->retrieve( m_tauVertCont , "PrimaryVertices" ) );
//    RETURN_CHECK("AnalysisBase::process", m_eventCont->getEvent()->retrieve( m_tauTruthPartCont , "TruthParticles" ) );
//    fillTau(m_tauCont);

    return true;
}

// Smearing is carried out for the physics objects
void AnalysisBase::smearPhyObjects()
{
    // Update the tool variation
    m_toolBase->updateToolVariation();
    
    // Smearing
    m_smearJet->setJetCont(m_jetCont);
    m_smearJet->setParticles(m_jetList);
    m_smearJet->process();
    
    m_smearMuon->setMuonCont(m_muonCont);
    m_smearMuon->setParticles(m_muonList);
    m_smearMuon->process();
    
    m_smearEgamma->setElectronCont(m_elCont);
    m_smearEgamma->setElParticles(m_electronList);
    m_smearEgamma->setPhotonCont(m_phCont);
    m_smearEgamma->setPhParticles(m_photonList);
    m_smearEgamma->process();
    
//    m_smearTau->setTauCont(m_tauCont);
//    m_smearTau->setParticles(m_tauList);
//    m_smearTau->process();
//    
    // Getting the right analysis type
    setAnalType();
}

// This adds the the relavant systematic sets
// for the job
void AnalysisBase::addSystematicsSet()
{
    // Systematic registry
    // loop over systematics registry:
    const CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
    const CP::SystematicSet& recommendedSystematics = registry.recommendedSystematics();
    // get list of recommended systematics
    if(m_doSys)
    {
        vector<CP::SystematicSet> sysList  = CP::make_systematics_vector(recommendedSystematics);
        
        for(auto sysListItr:sysList)
        {
            if(matchPatternSys((sysListItr).name()))
            {
                m_eventCont->m_sysList.push_back(sysListItr);
            }
        }
    }
    else
    {
        m_eventCont->m_sysList.push_back(CP::SystematicSet());
    }
    
    
    if(m_eventCont->m_sysList.size() == 0)
    {
        LOG(logERROR)<<"AnalysisBase::addSystematicsSet() - zero variations have been requested in this job. Please check";
        LOG(logERROR)<<"Most likely cause of this error is that no systematics match the name required by the user";
        exit(1);
    }
    
}

// Does the sysName match any pattern that has been given by the user?
Bool_t AnalysisBase::matchPatternSys(const string sysName) const
{
    for(auto st: m_sysPattern)
    {
        string sysPat(st);
        
        const boost::regex ex(boost::replace_all_copy(sysPat, ".", "\\S+"));
        string::const_iterator start, end;
        start = sysName.begin();
        end = sysName.end();
        boost::match_results<string::const_iterator> what;
        boost::match_flag_type flags = boost::match_default;
        
        if(boost::regex_search(start, end, what, ex, flags)) return true;
    }
    
    return false;
}

// Debug
// Loops over to find a specific event and process that
// Sets the flag to report all the debuging as well
Bool_t AnalysisBase::processDebug(ULong64_t t_eventNumber)
{
    
    LOG::ReportingLevel() = LOG::FromString("DEBUG");

    LOG(logDEBUG) <<"Processing : "<<t_eventNumber;


    // Initialization
    // Event container loads event zero and reads the meta-data
    if(!hasInitializedDebug) initialize();
    hasInitializedDebug = true;
   
    // Retrive the pileup tool for later usage
    m_pileupTool = ToolHandle<CP::IPileupReweightingTool>("PileupTool");
    if(m_pileupTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight::ApplyWeight() - cannot retrieve IPileupReweightingTool";
        exit(1);
    }




    Int_t nEvents = m_eventCont->getEvent()->getEntries();
    for(Int_t i = 0; i < nEvents; i++)
    {
        m_eventCont->getEntry(i);

        if(m_eventCont->eventInfo->eventNumber() == t_eventNumber)
        {
            LOG(logDEBUG) <<"EventNumber: "<<t_eventNumber;
            for (auto sysListItr:m_eventCont->m_sysList)
            {
                
                LOG(logDEBUG) <<"Variation: "<<sysListItr.name();

                // Setting the curr variation so tools can setup based on this
                m_eventCont->m_currVariation = sysListItr;
                m_eventCont->isDebug = true;
                // Setting the output tree for event
                m_eventCont->outTree = m_outTreeMap[sysListItr];
                
                // Processing the event
                processEvent();
            }
            
            return true;
        }
    }
    return false;
}

// Helper function to fill in physics objects into local container classes
// To fill particles in their local type
void AnalysisBase::fillMuon(const xAOD::MuonContainer* muonCont)
{
    auto m_muons_shallowCopy = xAOD::shallowCopyContainer( *muonCont );
    
    // Record shallowCopy in the Store
    m_eventCont->store->record( m_muons_shallowCopy.first, "muRaw" ).ignore();
    m_eventCont->store->record( m_muons_shallowCopy.second, "muRawAux" ).ignore();
    Int_t i = 0;
    for( const auto mu : *( m_muons_shallowCopy.first ) ) {
        ParticleVar* partMuon = new ParticleVar(m_eventCont, mu, i);
        m_muonList.push_back(partMuon);
        i++;
    }

}
void AnalysisBase::fillElectron(const xAOD::ElectronContainer* elCont)
{
    auto m_electrons_shallowCopy = xAOD::shallowCopyContainer( *elCont );
    
    // Record shallowCopy in the Store
    m_eventCont->store->record( m_electrons_shallowCopy.first, "elRaw" ).ignore();
    m_eventCont->store->record( m_electrons_shallowCopy.second, "elRawAux" ).ignore();
    
    Int_t i = 0;
    for( const auto electron : *( m_electrons_shallowCopy.first ) ) {
        ParticleVar* partElectron = new ParticleVar(m_eventCont, electron, i);
        m_electronList.push_back(partElectron);
        i++;
    }
}

void AnalysisBase::fillPhoton(const xAOD::PhotonContainer* phCont)
{
    auto m_photons_shallowCopy = xAOD::shallowCopyContainer( *phCont );
    // Record shallowCopy in the Store
    m_eventCont->store->record( m_photons_shallowCopy.first, "phRaw" ).ignore();
    m_eventCont->store->record( m_photons_shallowCopy.second, "phRawAux" ).ignore();
    Int_t i = 0;
    for( const auto photon : *( m_photons_shallowCopy.first ) ) {
        ParticleVar* partPhoton = new ParticleVar(m_eventCont, photon, i);
        m_photonList.push_back(partPhoton);
        i++;
    }
}

void AnalysisBase::fillJet(const xAOD::JetContainer* jetCont)
{
    auto m_jets_shallowCopy = xAOD::shallowCopyContainer( *jetCont );
    // Record shallowCopy in the Store
    m_eventCont->store->record( m_jets_shallowCopy.first, "jetRaw" ).ignore();
    m_eventCont->store->record( m_jets_shallowCopy.second, "jetRawAux" ).ignore();
    Int_t i = 0;
    for( const auto jet : *( m_jets_shallowCopy.first ) ) {
        ParticleVar* partJet = new ParticleVar(m_eventCont, jet, i);
        m_jetList.push_back(partJet);
        i++;
    }
}

void AnalysisBase::fillTruthJet(const xAOD::JetContainer* truthJetCont)
{
    auto m_truthJets_shallowCopy = xAOD::shallowCopyContainer( *truthJetCont );
    // Record shallowCopy in the Store
    m_eventCont->store->record( m_truthJets_shallowCopy.first, "truthJetRaw" ).ignore();
    m_eventCont->store->record( m_truthJets_shallowCopy.second, "truthJetRawAux" ).ignore();
    Int_t i = 0;
    for( const auto jet : *( m_truthJets_shallowCopy.first ) ) {
        ParticleVar* partJet = new ParticleVar(m_eventCont, jet, i);
        m_truthJetList.push_back(partJet);
        //LOG(logDEBUG) << "Got jet "<< i << " with pT: "<< partJet->getTLV().Pt()
        //<<" eta: "<< partJet->getTLV().Eta()
        //<<" phi: "<< partJet->getTLV().Phi()
        //<<" charge: " << partJet->getCharge();
        i++;
    }
}

void AnalysisBase::fillTau(const xAOD::TauJetContainer* tauCont)
{
    auto m_taus_shallowCopy = xAOD::shallowCopyContainer( *tauCont );
    m_eventCont->store->record( m_taus_shallowCopy.first, "tauRaw" ).ignore();
    m_eventCont->store->record( m_taus_shallowCopy.second, "tauRawAux" ).ignore();
    Int_t i = 0;
    for( const auto tau : *( m_taus_shallowCopy.first ) ) {
        ParticleVar* partTau = new ParticleVar(m_eventCont, tau, i);
        m_tauList.push_back(partTau);
        i++;
    }
    
}

// To set the base analysis type
void AnalysisBase::setAnalType()
{
    for(Int_t i = 0; i < (Int_t) m_muonList.size(); i++)
        m_muonList[i]->setAnalysisType(m_eventCont->m_analType);

    for(Int_t i = 0; i < (Int_t) m_electronList.size(); i++)
        m_electronList[i]->setAnalysisType(m_eventCont->m_analType);

    for(Int_t i = 0; i < (Int_t) m_photonList.size(); i++)
        m_photonList[i]->setAnalysisType(m_eventCont->m_analType);
    
    for(Int_t i = 0; i < (Int_t) m_jetList.size(); i++)
        m_jetList[i]->setAnalysisType(m_eventCont->m_analType);
    
    //for(Int_t i = 0; i < (Int_t) m_truthJetList.size(); i++)
    //    m_truthJetList[i]->setAnalysisType(m_eventCont->m_analType);
    //for(Int_t i = 0; i < (Int_t) m_tauList.size(); i++)
    //    m_tauList[i]->setAnalysisType(m_eventCont->m_analType);

}

// This clears the variables and free memory that are specific
// to a given event
void AnalysisBase::clearVars()
{
   
    
    while(!m_muonList.empty()) delete m_muonList.back(), m_muonList.pop_back();
    while(!m_electronList.empty()) delete m_electronList.back(), m_electronList.pop_back();
    while(!m_photonList.empty()) delete m_photonList.back(), m_photonList.pop_back();
    while(!m_jetList.empty()) delete m_jetList.back(), m_jetList.pop_back();
    while(!m_truthJetList.empty()) delete m_truthJetList.back(), m_truthJetList.pop_back();
    while(!m_tauList.empty()) delete m_tauList.back(), m_tauList.pop_back();

    if(m_smearMuon) m_smearMuon->clearVars();
    if(m_smearJet) m_smearJet->clearVars();
    if(m_smearEgamma) m_smearEgamma->clearVars();
    if(m_smearTau) m_smearTau->clearVars();
    
    m_eventCont->store->clear();
        
}

// Print truth
void AnalysisBase::printTruth(Int_t eventNumber)
{
    m_eventCont->initialize();
    cout<<"Event Number"<<endl;
    
    Int_t nEvents = m_eventCont->getEvent()->getEntries();
    
    for(Int_t i = 0; i < nEvents; i++)
    {
        m_eventCont->getEntry(i);
        if((Int_t) m_eventCont->eventInfo->eventNumber() == eventNumber)
        {
            cout<<"Here2"<<endl; 
            
            const xAOD::TruthParticleContainer *truthCont = 0;
            if(!m_eventCont->getEvent()->retrieve(truthCont, "TruthParticles").isSuccess())
            {
                cout<<"Failed to retrieve the truth Container"<<endl;
                return;
            }
            
            Int_t j = 0;
        
        
            // Find a map from every truth particle to its index
            map<const xAOD::TruthParticle*, int> truthMap;
            for (auto t_itr = truthCont->begin(); t_itr != truthCont->end(); ++t_itr)
            {
                truthMap[*t_itr] = j;
                j++;
            }
            j = 0;

            LOG(logDEBUG) <<"EventNumber: "<<eventNumber;
        
            cout<<"Index\tparticleName\tPDG ID\tMcStatus\tbarcode\tparent\tparentName\tchildSize\tchildPDGID(Index)\tpt\teta\tphi\tm"<<endl;
        
            // Dump of the information
            for (auto t_itr = truthCont->begin(); t_itr != truthCont->end(); ++t_itr)
            {
                const xAOD::TruthParticle* truthPart = (*t_itr);
                
                cout<<j<<"\t";
                cout<<getParticleName(truthPart->pdgId())<<"\t";
                cout<<truthPart->pdgId()<<"\t";
                cout<<truthPart->status()<<"\t";
                cout<<truthPart->barcode()<<"\t";
                
                if(truthMap.find(truthPart->parent()) != truthMap.end())
                {
                    cout<<truthMap.at(truthPart->parent())<<"\t";
                }
                else
                {
                    cout<<"- \t";
                }
                if(truthPart->parent()) cout<<getParticleName(truthPart->parent()->pdgId())<<"\t";
                else cout<<"- \t";
                cout<<truthPart->nChildren()<<"\t";
                
                for(Size_t k = 0; k < truthPart->nChildren(); k++)
                {
                    if(truthPart->child(k)) cout<<truthPart->child(k)->pdgId()<<" ("<<truthMap.at(truthPart->child(k))<<") ";
                }
                cout<<"\t";
                cout<<truthPart->pt()<<"\t";
                cout<<truthPart->eta()<<"\t";
                cout<<truthPart->phi()<<"\t";
                cout<<truthPart->p4().M()<<"\t";

                cout<<"\n";
                
                j++;
            }
            
            return;
            
        }
    }   
}


TString AnalysisBase::getParticleName(int pdgID)
{
    pdgID = TMath::Abs(pdgID);
    switch (pdgID)
    {
        case 1: return "d";
        case 2: return "u";
        case 3: return "s";
        case 4: return "c";
        case 5: return "b";
        case 6: return "t";
            
        case 11: return "El";
        case 12: return "ElNu";
        case 13: return "Mu";
        case 14: return "MuNu";
        case 15: return "Tau";
        case 16: return "TauNu";
            
        case 21: return "gluon";
        case 22: return "photon";
        case 23: return "Z_boson";
        case 24: return "w_boson";
        case 25: return "Higgs";
            
        case 211: return "pion";
        case 111: return "pion";
        case 130: return "kaon";
            
        default: return "Other";
    }
}


// Accessor to input arguments
TString AnalysisBase::getCmdArg(TString key) const
{
    if(m_opts.find(key) != m_opts.end())
    {
        return m_opts.at(key); 
    }
    else
    {
        LOG(logERROR) <<"AnalysisBase::getCmdArg()"<< " Input arg not found";
        LOG(logERROR) <<"Argument requested: "<<key;
        exit(-1);
    }
}


// check if input arguments
bool AnalysisBase::hasCmdArg(TString key) const
{
    if(m_opts.find(key) != m_opts.end())
    {
        return true; 
    }
    else
    {
        return false;   
    }
}

