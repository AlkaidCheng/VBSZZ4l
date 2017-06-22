#include "H4lCutFlow/CutParticleMuon.h"
using namespace std;

CutParticleMuon::CutParticleMuon(EventContainer* eventcont)
    : CutParticleBase(eventcont)
{
    m_cutFlowName = "muons";
    
    m_muonSelector = ToolHandle<CP::IMuonSelectionTool>("MuonSelectionTool");
    if(m_muonSelector.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleMuon::CutParticleMuon() - cannot retrieve CP::IMuonSelectionTool";
        exit(1);
    }
}

CutParticleMuon::~CutParticleMuon()
{
    clearVars();
}


// For cutflow
void CutParticleMuon::initCutFlow() 
{
    for(Int_t i = 0; i <= muCut::OverLap; i++)
    {
        m_cutName.push_back("");
    }
    for (auto sysListItr:m_eventCont->m_sysList){
        m_rawCutFlow[sysListItr].reserve(m_cutName.size());
        m_weightCutFlow[sysListItr].reserve(m_cutName.size());

        for(Int_t i = 0; i < (Int_t) m_cutName.size(); i++)
        {
            m_rawCutFlow[sysListItr].push_back(0);
            m_weightCutFlow[sysListItr].push_back(0);
        }
    }
    

    m_cutName[muCut::Total]           = "Total";
    m_cutName[muCut::Preselection]    = "Preselection";
    m_cutName[muCut::Trigger]         = "Trigger";
    m_cutName[muCut::ID]              = "mu_ID";
    m_cutName[muCut::Pt]              = "Pt";
    m_cutName[muCut::D0]              = "D0";
    m_cutName[muCut::OverLap]         = "OverLap";
    

}



// Function to smear each individual event
Bool_t CutParticleMuon::processParticle(const ParticleVar* currPart)
{
    if(currPart->getPartType() != ParticleType::Muon)
    {
        LOG(logERROR)<<"CutParticleMuon::processParticle - Particle Type not supported";
        LOG(logERROR)<<"Particle Type: "<<currPart->getPartType();
        exit(1);
    }
    
    // For keeping track
    //static Int_t printInfo = 0;
    
    // get the xAOD Jet
    const xAOD::Muon *mu = dynamic_cast<const xAOD::Muon*>(currPart->getParticle());
    

    // Treat Sili muons combined for now
    //if(mu->muonType() == xAOD::Muon::MuonStandAlone || mu->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon)
    if(mu->muonType() == xAOD::Muon::MuonStandAlone)
        return processStandAloneMuon(mu);
    else if (mu->muonType() == xAOD::Muon::CaloTagged)
        return processCaloMuon(mu);
    else return processCombinedMuon(mu);
    return true;
}


// Staco Muons cuts
Bool_t CutParticleMuon::processCombinedMuon(const xAOD::Muon* currMuon)
{
    // get the xAOD Muon
    const xAOD::Muon *mu_i = currMuon;

    //if(!mu_i->primaryTrackParticle())
    //{
    //    LOG(logERROR)<<"Event number: "<<m_eventCont->eventInfo->eventNumber();
    //}


    // To get the track informations
    const xAOD::TrackParticle* track_i = mu_i->primaryTrackParticle();

    // If there is no track, return false..
    if(!track_i) return false;
    
    const xAOD::VertexContainer* vertexCont = 0;
    m_eventCont->getEvent()->retrieve( vertexCont, "PrimaryVertices" ).isSuccess();
    // Assume this is the primary vertex
    const xAOD::Vertex* pvx = vertexCont->at(0);

    Double_t currZ0 = track_i->z0() + track_i->vz() - pvx->z();
    currZ0 = currZ0 * sin(track_i->theta());
    
    LOG(logDEBUG)<<"Combined muon";
    LOG(logDEBUG)<<"Mu pT: "<<mu_i->pt();
    LOG(logDEBUG)<<"Mu author: "<<mu_i->author();
    LOG(logDEBUG)<<"Mu quality: "<<m_muonSelector->getQuality(*mu_i);
    LOG(logDEBUG)<<"Mu currZ0: "<<currZ0;
    // For filling for plots
    m_eventCont->outTree->updateHistVar("muStacoPTHist",  mu_i->pt());
    m_eventCont->outTree->updateHistVar("muStacoEtaHist", mu_i->eta());
    
    // Muon selector tool Cut
    if(!(bool)m_muonSelector->accept(*mu_i)) return false;
    updateCutFlow(1, muCut::ID);
    
    // Kinematic Cut
    // Pt
    Double_t pTCut = 5 * 1000;
    if(mu_i->pt() > pTCut) 
    {updateCutFlow(1, muCut::Pt);}
    else return false;

    // D0 cut
    if(fabs(track_i->d0()) < 1 &&
        fabs(currZ0) < 0.5)
    {updateCutFlow(1,muCut::D0);}
    else return false;
    
    m_eventCont->outTree->updateHistVar("muStacoPTHistAfterSel",  mu_i->pt());
    m_eventCont->outTree->updateHistVar("muStacoEtaHistAfterSel", mu_i->eta());
 
    //LOG(logDEBUG)<<"This combined muon passed"; 
    return true;
}

// Calo muon cuts
Bool_t CutParticleMuon::processCaloMuon(const xAOD::Muon* currMuon)
{
    LOG(logDEBUG)<<"Calo muons";

    // get the xAOD Muon
    const xAOD::Muon *mu_i = currMuon;
    // To get the track informations
    const xAOD::TrackParticle* track_i = mu_i->primaryTrackParticle();
    const xAOD::VertexContainer* vertexCont = 0;
    m_eventCont->getEvent()->retrieve( vertexCont, "PrimaryVertices" ).isSuccess();
    
    // Assume this is the primary vertex
    const xAOD::Vertex* pvx = vertexCont->at(0);

    Double_t currZ0 = track_i->z0() + track_i->vz() - pvx->z();
    currZ0 = currZ0 * sin(track_i->theta());


    LOG(logDEBUG)<<"Calo muons";
    LOG(logDEBUG)<<"Mu pT: "<<mu_i->pt();
    LOG(logDEBUG)<<"Mu author: "<<mu_i->author();
    LOG(logDEBUG)<<"Mu quality: "<<m_muonSelector->getQuality(*mu_i);

    // For filling for plots
    m_eventCont->outTree->updateHistVar("muCaloPTHist",  mu_i->pt());
    m_eventCont->outTree->updateHistVar("muCaloEtaHist", mu_i->eta());
    
    // Muon selector tool Cut
    if(!(bool)m_muonSelector->accept(*mu_i)) return false;
    updateCutFlow(1, muCut::ID);
    
    // Kinematic Cut
    if(mu_i->pt() > 15 * 1000)
    {updateCutFlow(1, muCut::Pt);}
    else return false;

    if(fabs(track_i->d0()) < 1 &&
        fabs(currZ0) < 0.5)
    {updateCutFlow(1, muCut::D0);}
    else return false;
    
    m_eventCont->outTree->updateHistVar("muCaloPTHistAfterSel",  mu_i->pt());
    m_eventCont->outTree->updateHistVar("muCaloEtaHistAfterSel", mu_i->eta());

    //LOG(logDEBUG)<<"This calo muon passed";
    return true;
}


// StandAlone cuts
Bool_t CutParticleMuon::processStandAloneMuon(const xAOD::Muon* currMuon)
{
    LOG(logDEBUG)<<"StandAlone muons";
    
    // get the xAOD Muon
    const xAOD::Muon *mu_i = currMuon;
    
    LOG(logDEBUG)<<"Standalone muons";
    LOG(logDEBUG)<<"Mu pT: "<<mu_i->pt();
    LOG(logDEBUG)<<"Mu author: "<<mu_i->author();
    LOG(logDEBUG)<<"Mu quality: "<<m_muonSelector->getQuality(*mu_i);
    m_eventCont->outTree->updateHistVar("muSAPTHist",  mu_i->pt());
    m_eventCont->outTree->updateHistVar("muSAEtaHist", mu_i->eta());
    
    if(!(bool)m_muonSelector->accept(*mu_i)) return false;
    updateCutFlow(1, muCut::ID);

    // Kinematic Cut
    Double_t pTCut = 5 * 1000;
    if(mu_i->pt() > pTCut)
    {updateCutFlow(1, muCut::Pt);}
    else return false;

    updateCutFlow(1, muCut::D0);
    
    m_eventCont->outTree->updateHistVar("muSAPTHistAfterSel",  mu_i->pt());
    m_eventCont->outTree->updateHistVar("muSAEtaHistAfterSel", mu_i->eta());

    //LOG(logDEBUG)<<"Standalone muon passed";
    return true;

}

