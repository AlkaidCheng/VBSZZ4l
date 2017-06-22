#include "HZZCutCommon/METCalc.h"
#include "METUtilities/METHelpers.h"
using namespace std;

METCalc::METCalc(EventContainer* eventcont)
{
    // Copying it for local use
    m_eventCont = eventcont;

    
    m_metMaker = ToolHandle<IMETMaker>("METMaker");
    if(m_metMaker.retrieve().isFailure())
    {
        LOG(logERROR) <<"METCalc::METCalc() - cannot retrieve METMaker";
        exit(1);
    }
    
    m_metSysTool = ToolHandle<IMETSystematicsTool>("METSystematicsTool");
    if(m_metSysTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"METCalc::METCalc() - cannot retrieve IMETSystematicsTool";
        exit(1);
    }
    m_metSysToolR = dynamic_cast<met::METSystematicsTool*>(m_metSysTool.operator->());

    
    m_doMETElCut = false;
    m_doMETMuCut = false;
    m_doMETPhCut = false;
    
    m_muList = new xAOD::MuonContainer(SG::VIEW_ELEMENTS);
    m_elList = new xAOD::ElectronContainer(SG::VIEW_ELEMENTS);
    m_phList = new xAOD::PhotonContainer(SG::VIEW_ELEMENTS);
    m_jetList = new xAOD::JetContainer(SG::VIEW_ELEMENTS);
    
    m_newMetContainer = 0;
    m_newMetAuxContainer = 0;
    
    clearVars();

}

METCalc::~METCalc()
{
    clearVars();
    
    if(m_muList)    delete m_muList;
    if(m_elList)    delete m_elList;
    if(m_jetList)   delete m_jetList;
}

void METCalc::clearVars()
{
    m_elVecList.clear();
    m_muVecList.clear();
    m_jetVecList.clear();
    m_phVecList.clear();
    
    m_muList->clear();
    m_elList->clear();
    m_phList->clear();
    m_jetList->clear();
    
    m_coreMet = 0;
    
    m_filledEl = false;
    m_filledMu = false;
    m_filledJet = false;
    m_filledPh = false;
}



void METCalc::process()
{
    // Retrive the MET
    if(m_eventCont->getEvent()->retrieve( m_coreMet, "MET_Core_AntiKt4EMTopo" ).isFailure())
    {
        LOG(logERROR) <<"METCalc::process() - cannot retrieve MET_Core_AntiKt4EMTopo";
        exit(1);
    }
    
    if(m_eventCont->getEvent()->retrieve( m_metMap, "METAssoc_AntiKt4EMTopo" ).isFailure())
    {
        LOG(logERROR) <<"METCalc::process() - cannot retrieve MET_Core_AntiKt4EMTopo";
        exit(1);
    }
    // It is necessary to reset the selected objects before every MET calculation
    m_metMap->resetObjSelectionFlags();

    // Fill everything
    fillEl();
    fillPh();
    fillMu();
    fillJet();
    
    //met::addGhostElecsToJets(*m_elList, *m_jetList); 
    //met::addGhostMuonsToJets(*m_muList, *m_jetList); 
   
    // create the met containers
    m_newMetContainer    = new xAOD::MissingETContainer();
    m_newMetAuxContainer = new xAOD::MissingETAuxContainer();
    m_newMetContainer->setStore(m_newMetAuxContainer);
    
    bool isOk = true;

    isOk &= m_eventCont->store->record( m_newMetContainer, ("newMetContainer" +TString::Itoa(n_nameItr, 10)).Data());
    isOk &= m_eventCont->store->record( m_newMetAuxContainer, ("newMetContainerAux." +TString::Itoa(n_nameItr, 10)).Data());
    n_nameItr++;
    
    isOk &= m_metMaker->rebuildMET("RefEle",             //name of metElectrons in metContainer
                                   xAOD::Type::Electron, //telling the rebuilder that this is electron met
                                   m_newMetContainer,    //filling this met container
                                   m_elList,             //using these metElectrons that accepted our cuts
                                   m_metMap).isSuccess();//and this association map
    
    isOk &= m_metMaker->rebuildMET("RefPhoton",          //name of metPhotonss in metContainer
                                   xAOD::Type::Photon,   //telling the rebuilder that this is photon met
                                   m_newMetContainer,    //filling this met container
                                   m_phList,             //using these metElectrons that accepted our cuts
                                   m_metMap).isSuccess();//and this association map
    
    isOk &= m_metMaker->rebuildMET("RefMuon",            //name of metElectrons in metContainer
                                   xAOD::Type::Muon,     //telling the rebuilder that this is electron met
                                   m_newMetContainer,    //filling this met container
                                   m_muList,             //using these metElectrons that accepted our cuts
                                   m_metMap).isSuccess();//and this association map
    
    isOk &=  m_metMaker->rebuildJetMET("RefJet",        //name of jet met
                                       "SoftClus",      //name of soft cluster term met
                                       "PVSoftTrk",     //name of soft track term met
                                       m_newMetContainer, //adding to this new met container
                                       m_jetList,       //using this jet collection to calculate jet met
                                       m_coreMet,         //core met container
                                       m_metMap,          //with this association map
                                       false            //don't apply jet jvt cut
                                       ).isSuccess();
    
    //get the soft cluster term, and applyCorrection
    //xAOD::MissingET * softClusMet = (*m_newMetContainer)["SoftClus"];
    //std::cout << "Soft cluster met term met " << softClusMet->met() << std::endl;
    //assert( softClusMet != nullptr); //check we retrieved the clust term
    //assert( m_metSysTool->applyCorrection(*softClusMet) );
    xAOD::MissingET * softTrkMet = (*m_newMetContainer)["PVSoftTrk"];
    //std::cout << "Soft track met term met " << softTrkMet->met() << std::endl;
    assert( softTrkMet != nullptr); //check we retrieved the soft trk
    m_metSysToolR->setRandomSeed(314159+m_eventCont->eventInfo->runNumber()*2718+m_eventCont->eventInfo->eventNumber());
   
    if(m_eventCont->isMC)
    {
        if(m_metSysTool->applyCorrection(*softTrkMet) == CP::CorrectionCode::Error)
        {
            LOG(logERROR) <<"METCalc::Process() - cannot apply systematic";
            exit(1);
        }
    }
    
    isOk &=  m_metMaker->buildMETSum("FinalTrk" , m_newMetContainer, MissingETBase::Source::Track).isSuccess();
    
    if(m_eventCont->isDebug)
    {
        LOG(logDEBUG)<<"met_et: "<<getTrackMET()->met()/1000.;
        LOG(logDEBUG)<<"met_sum_et: "<<getTrackMET()->sumet()/1000.;
        LOG(logDEBUG)<<"met_phi: "<<getTrackMET()->phi();
    }
}


bool METCalc::fillEl()
{
    if(!m_filledEl)
    {
        LOG(logERROR)<<"METCalc - Electrons not filled";
        exit(1);
    }
    
    for(auto part: m_elVecList)
    {
        if(part->getPartType() != ParticleType::Electron)
        {
            LOG(logERROR)<<"METCalc - Input Not an electron";
            LOG(logERROR)<<"Type: "<<part->getPartType();
            exit(1);
        }
        const xAOD::Electron *partTemp = dynamic_cast<const xAOD::Electron*>(part->getParticle());
        xAOD::Electron *part_i = const_cast<xAOD::Electron*>(partTemp);
        
        if(m_doMETElCut)
        {
            if(!CutsMETMaker::accept(part_i)) continue;
        }
        
        LOG(logDEBUG)<<"MET - adding El pt: "<<part_i->pt()
        <<" eta: "<<part_i->eta()
        <<" phi: "<<part_i->phi()
        <<" M: "<<part_i->m();
        
        m_elList->push_back(part_i);
    }
    return true;
}

bool METCalc::fillPh()
{
//    Photons are not required in this analysis
//    if(!m_filledPh)
//    {
//        LOG(logERROR)<<"METCalc - Photons not filled";
//        exit(1);
//    }
    
    for(auto part: m_phVecList)
    {
        if(part->getPartType() != ParticleType::Photon)
        {
            LOG(logERROR)<<"METCalc - Input not a photon";
            LOG(logERROR)<<"Type: "<<part->getPartType();
            exit(1);
        }
        
        const xAOD::Photon *partTemp = dynamic_cast<const xAOD::Photon*>(part->getParticle());
        xAOD::Photon *part_i = const_cast<xAOD::Photon*>(partTemp);
        
        if(m_doMETPhCut)
        {
            if(!CutsMETMaker::accept(part_i)) continue;
        }
        LOG(logDEBUG)<<"MET - adding Ph pt: "<<part_i->pt()
        <<" eta: "<<part_i->eta()
        <<" phi: "<<part_i->phi()
        <<" M: "<<part_i->m();
        m_phList->push_back(part_i);
    }
    return true;
}

bool METCalc::fillMu()
{
    if(!m_filledMu)
    {
        LOG(logERROR)<<"METCalc - Muons not filled";
        exit(1);
    }
    
    for(auto part: m_muVecList)
    {
        if(part->getPartType() != ParticleType::Muon)
        {
            LOG(logERROR)<<"METCalc - Input not a Muon";
            LOG(logERROR)<<"Type: "<<part->getPartType();
            exit(1);
        }
        
        const xAOD::Muon *partTemp = dynamic_cast<const xAOD::Muon*>(part->getParticle());
        xAOD::Muon *part_i = const_cast<xAOD::Muon*>(partTemp);
        
        if(m_doMETMuCut)
        {
            if(!CutsMETMaker::accept(part_i)) continue;
        }
        LOG(logDEBUG)<<"MET - adding Mu pt: "<<part_i->pt()
        <<" eta: "<<part_i->eta()
        <<" phi: "<<part_i->phi()
        <<" M: "<<part_i->m();
        m_muList->push_back(part_i);
    }
    return true;
}

bool METCalc::fillJet()
{
    if(!m_filledJet)
    {
        LOG(logERROR)<<"METCalc - Jets not filled";
        exit(1);
    }
    
    for(auto part: m_jetVecList)
    {
        if(part->getPartType() != ParticleType::Jet)
        {
            LOG(logERROR)<<"METCalc - Input not a Jet";
            LOG(logERROR)<<"Type: "<<part->getPartType();
            exit(1);
        }
    
        const xAOD::Jet *partTemp = dynamic_cast<const xAOD::Jet*>(part->getParticle());
        xAOD::Jet *part_i = const_cast<xAOD::Jet*>(partTemp);
        
        LOG(logDEBUG)<<"MET - adding Jet pt: "<<part_i->pt()
        <<" eta: "<<part_i->eta()
        <<" phi: "<<part_i->phi()
        <<" M: "<<part_i->m();
        
        m_jetList->push_back(part_i);
    }
    return true;
}

// For FSR particles
void METCalc::setFSRParticles(const std::vector<ParticleVar*> partList)
{
    if(!m_filledEl)
    {
        LOG(logERROR)<<"METCalc - Adding FSR particles has been requested";
        LOG(logERROR)<<"but el container has been filled yet";
        LOG(logERROR)<<"Pass the El container before this step";
        exit(1);
    }
    for(size_t i = 0; i < partList.size(); i++)
    {
        if(partList[i]->getPartType() == ParticleType::Photon)
            m_phVecList.push_back(partList[i]);
        // Check overlapping electrons first
        else if(partList[i]->getPartType() == ParticleType::Electron)
        {
            if(!isOvlEl(partList[i])) m_elVecList.push_back(partList[i]);
        }
        else
        {
            LOG(logERROR)<<"METCalc - setFSRParticles input part type not supported";
            LOG(logERROR)<<"Type: "<<partList[i]->getPartType();
            exit(1);
        }
    }
}

bool METCalc::isOvlEl(ParticleVar* part)
{
    for(size_t i = 0; i < m_elVecList.size(); i++)
    {
        if (m_elVecList[i]->getParticle() == part->getParticle())
        {
            return true;
        }
    }
    
    return false;
}



