#include "H4lCutFlow/CutParticleElectron.h"
using namespace std;

CutParticleElectron::CutParticleElectron(EventContainer* eventcont)
    : CutParticleBase(eventcont)
{
    m_cutFlowName = "electron";
    
    m_likelihoodCut = ToolHandle<IAsgElectronLikelihoodTool>("likelihoodCut");
    if(m_likelihoodCut.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleElectron::CutParticleElectron() - cannot retrieve IAsgElectronLikelihoodTool";
        exit(1);
    }
    m_likelihoodCutVL = ToolHandle<IAsgElectronLikelihoodTool>("likelihoodCutVL");
    if(m_likelihoodCutVL.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleElectron::CutParticleElectron() - cannot retrieve IAsgElectronLikelihoodTool VeryLoose";
        exit(1);
    }
    
    m_likelihoodCutM = ToolHandle<IAsgElectronLikelihoodTool>("likelihoodCutM");
    if(m_likelihoodCutM.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleElectron::CutParticleElectron() - cannot retrieve IAsgElectronLikelihoodTool Medium";
        exit(1);
    }
    
    m_likelihoodCutT = ToolHandle<IAsgElectronLikelihoodTool>("likelihoodCutT");
    if(m_likelihoodCutT.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleElectron::CutParticleElectron() - cannot retrieve IAsgElectronLikelihoodTool Tight";
        exit(1);
    }
    
    m_doVeryLooseID = false;
    m_doBasicID = false;

}

CutParticleElectron::~CutParticleElectron()
{
    clearVars();
}



// For cutflow
void CutParticleElectron::initCutFlow() 
{
    for(Int_t i = 0; i <= elCut::OverLap; i++)
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
    
    m_cutName[elCut::Total]           = "Total";
    m_cutName[elCut::Preselection]    = "Preselection";
    m_cutName[elCut::Trigger]         = "Trigger";
    m_cutName[elCut::Author]          = "Author";
    m_cutName[elCut::Loose]           = "Loose";
    m_cutName[elCut::Eta]             = "Eta";
    m_cutName[elCut::Et]              = "Et";
    m_cutName[elCut::ObjectQuality]   = "OQ";
    m_cutName[elCut::Z0]              = "Z0";
    m_cutName[elCut::OverLap]         = "OverLap";

}


// Electrons cuts
Bool_t CutParticleElectron::processParticle(const ParticleVar* currPart)
{
    
    if(currPart->getPartType() != ParticleType::Electron)
    {
        LOG(logERROR)<<"CutParticleElectron::processParticle - Particle Type not supported";
        LOG(logERROR)<<"Particle Type: "<<currPart->getPartType();
        exit(1);
    }

    // For keeping track
    //static Int_t printInfo = 0;

    // get the xAOD Electron
    const xAOD::Electron* el_i = dynamic_cast<const xAOD::Electron*>(currPart->getParticle());
        
    const xAOD::VertexContainer* vertexCont = 0;
    m_eventCont->getEvent()->retrieve( vertexCont, "PrimaryVertices" ).isSuccess();
    
    // Assume this is the primary vertex
    const xAOD::Vertex* pvx = vertexCont->at(0);

    Double_t currZ0 = el_i->trackParticle()->z0() + el_i->trackParticle()->vz() - pvx->z();
    currZ0 = currZ0 * sin(el_i->trackParticle()->theta());

    // calculationg of vars
    Double_t Et     = 0.0;
    Double_t Eta_cl = 0.0;
    Double_t Eta_tr = 0.0;

    Eta_cl  = el_i->caloCluster()->etaBE(2);
    Eta_tr  = el_i->trackParticle()->eta(); 
    Et      = el_i->p4().Pt();

    fillIDCut(el_i);

    //LOG(logDEBUG)<<"El pT: "<<el_i->pt();
    ////LOG(logDEBUG)<<"El author: "<<el_i->author();
    //LOG(logDEBUG)<<"El tight ID: "<<el_i->auxdecor< int >( "tightID" );
    //LOG(logDEBUG)<<"El medium ID: "<<el_i->auxdecor< int >( "mediumID" );
    //LOG(logDEBUG)<<"El loose ID: "<<el_i->auxdecor< int >( "looseID" );
    //LOG(logDEBUG)<<"El Vloose ID: "<<el_i->auxdecor< int >( "veryLooseID" );
    //LOG(logDEBUG)<<"El Basic ID: "<<el_i->auxdecor< int >( "basicID" );
    //LOG(logDEBUG)<<"El Eta_cl: "<<Eta_cl;
    //LOG(logDEBUG)<<"El Et: "<<Et;
    //LOG(logDEBUG)<<"El OQ: "<<(el_i->auxdata< uint32_t >("OQ") & 1446);
    //LOG(logDEBUG)<<"El currZ0: "<<currZ0;
    
    //Author cut
    if((el_i->author() == 1 || el_i->author() == 16))
    {updateCutFlow(1,elCut::Author);}
    else return false;

    //// Loose cut
    bool el_loose = false;
    
    
    // Likelihood cut
    el_loose = el_i->auxdecor< int >( "looseID" );
    if (m_doVeryLooseID) el_loose = el_i->auxdecor< int >( "veryLooseID" );
    if (m_doBasicID) el_loose = el_i->auxdecor< int >( "basicID" );

    if(!(el_loose == 1)) return false;
    updateCutFlow(1,elCut::Loose);
    
    m_eventCont->outTree->updateHistVar("elETHist",  Et);
    m_eventCont->outTree->updateHistVar("elEtaHist", Eta_cl);

    //Eta
    if(fabs(Eta_cl) < 2.47) // These variables come from above intiia
    {updateCutFlow(1,elCut::Eta);}
    else return false;
    
    // Et
    if(Et > 7 * 1000)
    {updateCutFlow(1,elCut::Et);}
    else return false;

    // Object Quality
    if((el_i->auxdata< uint32_t >("OQ") & 1446) == 0)
    {updateCutFlow(1,elCut::ObjectQuality);}
    else return false;

    if(fabs(currZ0) < 0.5)
    {updateCutFlow(1,elCut::Z0);}
    else return false;
    
    m_eventCont->outTree->updateHistVar("elETHistAfterSel",  Et);
    m_eventCont->outTree->updateHistVar("elEtaHistAfterSel", Eta_cl);

    return true;
}

// To fill the ID cut
void CutParticleElectron::fillIDCut(const xAOD::Electron* el)
{

    
    Root::TAccept acc = m_likelihoodCut->accept(el);
    el->auxdecor< int >( "basicID" )     = (acc.getCutResult("NPixel") && acc.getCutResult("NSilicon"));
    el->auxdecor< int >( "looseID" )     = (bool) acc;

    // Loose ID without bLayer
    acc.setCutResult("NBlayer",true);
    el->auxdecor< int >( "looseID_noBL" )     = (bool) acc;

    
    el->auxdecor< int >( "veryLooseID" ) = m_likelihoodCutVL->accept(el);
    el->auxdecor< int >( "mediumID" )    = m_likelihoodCutM->accept(el);
    el->auxdecor< int >( "tightID" )     = m_likelihoodCutT->accept(el);
}


