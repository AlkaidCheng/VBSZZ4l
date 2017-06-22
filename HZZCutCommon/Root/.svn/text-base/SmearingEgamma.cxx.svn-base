#include "HZZCutCommon/SmearingEgamma.h"
using namespace std;

SmearingEgamma::SmearingEgamma(EventContainer* eventcont) :
SmearingBase(eventcont)
{

    m_elRescale = ToolHandle<CP::IEgammaCalibrationAndSmearingTool>("EgammaCalibrationAndSmearingTool");
    if(m_elRescale.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingEgamma::SmearingEgamma() - cannot retrieve IEgammaCalibrationAndSmearingTool";
        exit(1);
    }
}

SmearingEgamma::~SmearingEgamma()
{
    clearVars();
}

// To reset for each new event
void SmearingEgamma::clearVars()
{
    m_elList.clear();
    m_phList.clear();
    
    m_elCont = 0;
    m_phCont = 0;
    
    SmearingBase::clearVars();
    
}

// Function that loops over the vector and smears it
void SmearingEgamma::process()
{
    // Smearing for electron
    if(m_elCont == 0 && m_elList.size() != 0)
    {
        LOG(logERROR)<<"Egamma Smear: Electron container not specified";
        exit(1);
    }
    else
    {
        m_elshallowCopy = xAOD::shallowCopyContainer( *m_elCont );
        m_eventCont->store->record( m_elshallowCopy.first, "elCorr" ).ignore();
        m_eventCont->store->record( m_elshallowCopy.second, "elCorrAux" ).ignore();
        Int_t i = 0;
        for(  auto el : *( m_elshallowCopy.first ) ) {
            processVar(el);
            m_elList[i]->addAnalParticle(m_eventCont->m_analType, el);
            m_elList[i]->addAnalTLV(TLVType::Unconstrained, el->p4());
            i++;
        }
        const xAOD::ElectronContainer* m_elCont;
        m_eventCont->getEvent()->retrieve( m_elCont, "Electrons" ).ignore();
        xAOD::setOriginalObjectLink( *m_elCont, *m_elshallowCopy.first);
    }
    
    // Smearing for electron
    if(m_phCont == 0 && m_phList.size() != 0)
    {
        LOG(logERROR)<<"Egamma Smear: Electron container not specified";
        exit(1);
    }
    else
    {
        m_phshallowCopy = xAOD::shallowCopyContainer( *m_phCont );
        m_eventCont->store->record( m_phshallowCopy.first, "phCorr" ).ignore();
        m_eventCont->store->record( m_phshallowCopy.second, "phCorrAux" ).ignore();
        Int_t i = 0;
        for( auto ph : *( m_phshallowCopy.first ) ) {
            processVar(ph);
            m_phList[i]->addAnalParticle(m_eventCont->m_analType, ph);
            m_phList[i]->addAnalTLV(TLVType::Unconstrained, ph->p4());
            i++;
        }
        const xAOD::PhotonContainer* m_phCont;
        m_eventCont->getEvent()->retrieve( m_phCont, "Photons" ).ignore();
        xAOD::setOriginalObjectLink( *m_phCont, *m_phshallowCopy.first );
    }
}

void SmearingEgamma::processVar(xAOD::IParticle* currPart)
{
    if(currPart->type() == xAOD::Type::Electron)
    {
        auto* currEl = dynamic_cast<xAOD::Electron*>(currPart);
        processEvent(currEl);
    }
    else if(currPart->type() == xAOD::Type::Photon)
    {
        auto* currPh = dynamic_cast<xAOD::Photon*>(currPart);
        processEvent(currPh);
    }
    else
    {
        LOG(logERROR)<<"SmearingEgamma::processVar particle type mismatch or supported type";
        LOG(logERROR)<<"Incoming part type: "<<currPart->type();
        exit(1);
    }
}

// Function to smear each individual event
void SmearingEgamma::processEvent(xAOD::Electron* currElectron)
{
    
    //m_elRescale->setRandomSeed(m_eventCont->eventInfo->eventNumber() + 100 * currEl->getIndex());
    
    if(m_eventCont->doSmear)
    {
        if(!m_elRescale->applyCorrection(*currElectron))
        {
            LOG(logERROR)<<"Cannot apply electron variation";
            exit(1);
        }
    }
    
    // decorate the isolation information need it for later
    float ptvarcone30 = -1;
    float ptvarcone20 = -1;
    float topoetcone20 = -1;
    currElectron->isolation(ptvarcone30,xAOD::Iso::ptvarcone30);
    currElectron->isolation(ptvarcone20,xAOD::Iso::ptvarcone20);
    currElectron->isolation(topoetcone20,xAOD::Iso::topoetcone20);
    
    currElectron->auxdecor< float >( "corr_ptvarcone30" )  = ptvarcone30;
    currElectron->auxdecor< float >( "corr_ptvarcone20" )  = ptvarcone20;
    currElectron->auxdecor< float >( "corr_topoetcone20" ) = topoetcone20;

    // Decorate the resolution information
    currElectron->auxdecor< float >( "resolution" ) = m_elRescale->getResolution(*currElectron) * currElectron->e()/1000;

}

// Function to smear each individual event
void SmearingEgamma::processEvent(xAOD::Photon* currPhoton)
{
    // Here is where smearing happens
    // If need pass this info through decorations
    //m_elRescale->setRandomSeed(m_eventCont->eventInfo->eventNumber() + 100 * currPh->getIndex());
    
    // This may create a issue with FSR...
    if(m_eventCont->doSmear)
    {
        // Only apply smearing to photons with author 4 or 16
        if(!((currPhoton->author() == 4 || currPhoton->author() == 16))) return;
        
        if(!m_elRescale->applyCorrection(*currPhoton))
        {
            LOG(logERROR)<<"Cannot apply photon variation";
            exit(1);
        }
    }


    // Decorate the resolution information
    currPhoton->auxdecor< float >( "resolution" ) = m_elRescale->getResolution(*currPhoton) * currPhoton->e()/1000;
}

