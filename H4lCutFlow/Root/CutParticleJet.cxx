#include "H4lCutFlow/CutParticleJet.h"
#include "JetJvtEfficiency/IJetJvtEfficiency.h"
using namespace std;

CutParticleJet::CutParticleJet(EventContainer* eventcont)
    : CutParticleBase(eventcont)
{
    m_cutFlowName = "jet";
    m_jetSelection = NA;
        
    m_jetcleaningTool = ToolHandle<IJetSelector>("JetCleaningTool");
    if(m_jetcleaningTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleJet::CutParticleJet() - cannot retrieve IJetSelector";
        exit(1);
    }
    
    m_jetJVTEffTool = ToolHandle<CP::IJetJvtEfficiency>("JetJvtEfficiency");
    if(m_jetJVTEffTool.retrieve().isFailure())
    {
	LOG(logERROR) <<"CutParticleJet::CutParticleJet() - cannot retrieve IJetJvtEfficiency";
	exit(1);
    }
}

CutParticleJet::~CutParticleJet()
{
    clearVars();
}


void CutParticleJet::initialize()
{
    if(m_jetSelection == NA)
    {
        LOG(logERROR)<<"CutParticleJet::initialize - jetSelection type not specified";
        exit(1);
    }
    else if (m_jetSelection == NominalReco)     m_cutFlowName = "jet";
    else if (m_jetSelection == FiducialReco)    m_cutFlowName = "jet - Fiducial";
    else if (m_jetSelection == NominalTruth)    m_cutFlowName = "jet - Truth";
    else if (m_jetSelection == FiducialTruth)   m_cutFlowName = "jet - Fiducial Truth";
    
    CutParticleBase::initialize();
}


// For cutflow
void CutParticleJet::initCutFlow() 
{
    for(Int_t i = 0; i <= jetCut::OverLap; i++)
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
    m_cutName[jetCut::Total]          = "Total";
    m_cutName[jetCut::Preselection]   = "Preselection";
    m_cutName[jetCut::Trigger]        = "Trigger";
    m_cutName[jetCut::Pt]             = "Pt";
    m_cutName[jetCut::Eta]            = "Eta";
    m_cutName[jetCut::Pileup]         = "Pileup";
    m_cutName[jetCut::Clean]          = "Clean";
    m_cutName[jetCut::OverLap]        = "OverLap";

}


// Jets cuts
Bool_t CutParticleJet::processParticle(const ParticleVar* currPart)
{

    if(currPart->getPartType() != ParticleType::Jet)
    {
        LOG(logERROR)<<"CutParticleJet::processParticle - Particle Type not supported";
        LOG(logERROR)<<"Particle Type: "<<currPart->getPartType();
        exit(1);
    }
    
    
    // Do the selection based on what is setup from outside
    // Technically at any point the user can change what they want to do
    // However, it is assumed that the user will create a CutParticleJet class for each selection type
    if(m_jetSelection == NominalReco)   return nominalRecoSel(currPart);
    if(m_jetSelection == FiducialReco)  return fidRecoSel(currPart);
    if(m_jetSelection == NominalTruth)  return truthNomRecoSel(currPart);
    if(m_jetSelection == FiducialTruth) return truthFidRecoSel(currPart);
    
    
    return false;
}


// Nominal selection
Bool_t CutParticleJet::nominalRecoSel(const ParticleVar* currPart)
{
    // get the xAOD Jet
    const xAOD::Jet *jet_i = dynamic_cast<const xAOD::Jet*>(currPart->getParticle());
    
    Float_t pt = jet_i->pt();
    Float_t eta = jet_i->jetP4(xAOD::JetEMScaleMomentum).eta();
    
    // For Plots
    m_eventCont->outTree->updateHistVar("jetPTHist" ,pt);
    m_eventCont->outTree->updateHistVar("jetEtaHist",eta);
    
    // Pt Cut
    if(nomPtCut(pt))
    {updateCutFlow(1,jetCut::Pt);}
    else return false;

    // Eta Cut
    if(nomEtaCut(eta, pt))
    {updateCutFlow(1,jetCut::Eta);}
    else return false;
    
    if(pileupCut(jet_i))
    {
        updateCutFlow(1,jetCut::Pileup);
    }
    else
    {
        m_jetFailJvt.push_back(currPart);
        return false;
    }
    
    if(cleanCut(jet_i))
    {
        updateCutFlow(1,jetCut::Clean);
    }
    else return false;
    
    m_eventCont->outTree->updateHistVar("jetPTHistAfterSel" ,pt);
    m_eventCont->outTree->updateHistVar("jetEtaHistAfterSel",eta);
    
    return true;
}

// Fiducial selection
Bool_t CutParticleJet::fidRecoSel(const ParticleVar* currPart)
{
    // get the xAOD Jet
    const xAOD::Jet *jet_i = dynamic_cast<const xAOD::Jet*>(currPart->getParticle());
    
    Float_t pt = jet_i->pt();
    Float_t eta = jet_i->rapidity();
    
    // Pt Cut
    if(fidPtCut(pt))
    {updateCutFlow(1,jetCut::Pt);}
    else return false;
    
    // Eta Cut
    if(fidEtaCut(eta))
    {updateCutFlow(1,jetCut::Eta);}
    else return false;
    
    if(pileupCut(jet_i))
    {
        updateCutFlow(1,jetCut::Pileup);
    }
    else
    {
        m_jetFailJvt.push_back(currPart);
        return false;
    }
    
    if(cleanCut(jet_i))
    {
        updateCutFlow(1,jetCut::Clean);
    }
    else return false;
    
    return true;
}


// Nominal selection
Bool_t CutParticleJet::truthNomRecoSel(const ParticleVar* currPart)
{
    // get the xAOD Jet
    const xAOD::Jet *jet_i = dynamic_cast<const xAOD::Jet*>(currPart->getParticle());
    
    Float_t pt = jet_i->pt();
    Float_t eta = jet_i->eta();
    
    // Pt Cut
    if(nomPtCut(pt))
    {updateCutFlow(1,jetCut::Pt);}
    else return false;
    
    // Eta Cut
    if(nomEtaCut(eta, pt))
    {updateCutFlow(1,jetCut::Eta);}
    else return false;

    return true;
}

// Fiducial selection
Bool_t CutParticleJet::truthFidRecoSel(const ParticleVar* currPart)
{
    // get the xAOD Jet
    const xAOD::Jet *jet_i = dynamic_cast<const xAOD::Jet*>(currPart->getParticle());
    
    Float_t pt = jet_i->pt();
    Float_t rapidity = jet_i->rapidity();
    
    // Pt Cut
    if(fidPtCut(pt))
    {updateCutFlow(1,jetCut::Pt);}
    else return false;
    
    // Rapidity Cut
    if(fidEtaCut(rapidity))
    {updateCutFlow(1,jetCut::Eta);}
    else return false;

    return true;
}

// Helper functions

// Pt cut for nominal selections
Bool_t CutParticleJet::nomPtCut(double pT)
{
    if(pT > 30 * 1000) return true;
    return false;
}

// Eta Cut for Nominal jets
Bool_t CutParticleJet::nomEtaCut(double eta, double pt)
{
    if((pt > 30 * 1000 && fabs(eta) < 2.4) || (pt > 30 * 1000 && fabs(eta) > 2.4 && fabs(eta) < 4.5)) return true;
    return false;
}


// Pt cut for fiducial selections
Bool_t CutParticleJet::fidPtCut(double pT)
{
    if(pT > 30 * 1000) return true;
    return false;
}

// Eta Cut for fiducial jets
Bool_t CutParticleJet::fidEtaCut(double rapidity)
{
    if(fabs(rapidity) < 4.4) return true;
    return false;
}

// JVT Cut
Bool_t CutParticleJet::pileupCut(const xAOD::Jet* jet_i)
{
    Float_t pt = jet_i->pt();
    //Float_t eta = jet_i->jetP4(xAOD::JetEMScaleMomentum).eta();
    Float_t eta = jet_i->eta();
    
    LOG(logDEBUG) << "JVT cut - pt: "<<jet_i->pt()<<" eta: "<<jet_i->eta()
        <<" JVT: "<<jet_i->auxdecor<float>("Jvt");
    
    // Apply cut on data
    if(!m_eventCont->isMC)
    {
        // Pileup Removal
        Double_t jvtCut = 0.59;    
        if((pt < 60*1000 && fabs(eta) < 2.4))
        {
            if(jet_i->auxdecor<float>("Jvt") < jvtCut) return false;
        }
        return true;
    }
    // TODO: fJVT is experimental at the moment
    // so don't cut, rather store output to minitree
    //if(jet_i->auxdata<char>("passFJVT") == 0) return false;
   

    // Apply the random dropping method

    unsigned int seed = 1 + std::abs( jet_i->phi() )*1E6 + std::abs( jet_i->eta() )*1E3 + m_eventCont->eventInfo->eventNumber();
    m_jetJVTEffTool->setRandomSeed(seed);
    m_jetJVTEffTool->applyRandomDropping(*jet_i);

    LOG(logDEBUG)<<"JVT random dropping: "<<jet_i->auxdecor<float>("Jvt")<<" seed: "<<seed<<" drop? "<<m_jetJVTEffTool->passesJvtCut(*jet_i);
    
    return m_jetJVTEffTool->passesJvtCut(*jet_i);
}

Bool_t CutParticleJet::cleanCut(const xAOD::Jet* jet_i)
{
    // Now this is an event level cut
    jet_i->auxdecor<int> ("badJet") = m_jetcleaningTool->keep(*jet_i);
    return true;

    return m_jetcleaningTool->keep(*jet_i);
}


// Clean information

void CutParticleJet::clearVars()
{
    CutParticleBase::clearVars();
    m_jetFailJvt.clear();
}

