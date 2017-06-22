#include "HZZCutCommon/SmearingMuon.h"
using namespace std;

SmearingMuon::SmearingMuon(EventContainer* eventcont) :
    SmearingBase(eventcont)
{
    m_muonCalSmearTool = ToolHandle<CP::IMuonCalibrationAndSmearingTool>("muonCalSmearTool");
    
    if(m_muonCalSmearTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingMuon::SmearingMuon() - cannot retrieve IMuonCalibrationAndSmearingTool";
        exit(1);
    }


    m_muonTool = dynamic_cast<CP::MuonCalibrationAndSmearingTool*>(&*m_muonCalSmearTool);

}

SmearingMuon::~SmearingMuon()
{
    clearVars();
}

// To reset for each new event
void SmearingMuon::clearVars()
{
    m_muonCont = 0;
    SmearingBase::clearVars();

}

// Function that loops over the vector and smears it
void SmearingMuon::process()
{
    if(m_muonCont == 0)
    {
        LOG(logERROR)<<"Muon Smear: Muon container not specified";
        exit(1);
    }
    
    m_shallowCopy = xAOD::shallowCopyContainer( *m_muonCont );
    m_eventCont->store->record( m_shallowCopy.first, "muonCorr" ).ignore();
    m_eventCont->store->record( m_shallowCopy.second, "muonCorrAux" ).ignore();
    Int_t i = 0;
    for( const auto mu : *( m_shallowCopy.first ) ) {
        processVar(mu);
        m_partList[i]->addAnalParticle(m_eventCont->m_analType, mu);
        m_partList[i]->addAnalTLV(TLVType::Unconstrained, mu->p4());
        i++;
    }
    
    const xAOD::MuonContainer* m_muonCont;
    m_eventCont->getEvent()->retrieve( m_muonCont, "Muons" ).ignore();
    xAOD::setOriginalObjectLink( *m_muonCont, *m_shallowCopy.first );
}

// Smears the given muon..
void SmearingMuon::processVar(xAOD::IParticle* currPart)
{
    
    if(currPart->type() != xAOD::Type::Muon)
    {
        LOG(logERROR)<<"SmearingMuon::processVar particle type not supported";
        LOG(logERROR)<<"Incoming part type: "<<currPart->type();
        exit(1);
    }
    
    xAOD::Muon* currMuon = dynamic_cast<xAOD::Muon*>(currPart);
    
    // Applying all
    if(m_eventCont->doSmear && fabs(currMuon->eta()) < 2.7)
    {
        if(!m_muonCalSmearTool->applyCorrection(*currMuon))
        {
            LOG(logERROR)<<"Cannot apply variation";
            exit(1);
        }
    }
    
    
    // decorate the isolation information need it for later
    float ptvarcone30 = -1;
    float ptvarcone20 = -1;
    float topoetcone20 = -1;
    currMuon->isolation(ptvarcone30,xAOD::Iso::ptvarcone30);
    currMuon->isolation(ptvarcone20,xAOD::Iso::ptvarcone20);
    currMuon->isolation(topoetcone20,xAOD::Iso::topoetcone20);
    
    currMuon->auxdecor< float >( "corr_ptvarcone30" )  = ptvarcone30;
    currMuon->auxdecor< float >( "corr_ptvarcone20" )  = ptvarcone20;
    currMuon->auxdecor< float >( "corr_topoetcone20" ) = topoetcone20;


    // Decorate the resolution information
    //currMuon->auxdecor< float >( "resolution" ) = m_muonTool->ExpectedResolution("CB", *currMuon, false);
    
    double muonRes = 0;
    if(currMuon->muonType() == xAOD::Muon::MuonStandAlone || currMuon->muonType() == xAOD::Muon::SiliconAssociatedForwardMuon)
        muonRes = m_muonTool->ExpectedResolution("MS", *currMuon, false);
    else if (currMuon->muonType() == xAOD::Muon::CaloTagged || currMuon->muonType() == xAOD::Muon::SegmentTagged)
        muonRes = m_muonTool->ExpectedResolution("ID", *currMuon, false);
    else
        muonRes = m_muonTool->ExpectedResolution("CB", *currMuon, false);


    currMuon->auxdecor< float >("resolution") = 0.5 * muonRes * currMuon->pt()/1000 * cosh(currMuon->eta());
}



