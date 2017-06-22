#include "HZZCutCommon/ParticleDilepton.h"
using namespace std;

ParticleDilepton::ParticleDilepton(EventContainer* t_eventcont, ParticleVar* lepOne, ParticleVar* lepTwo):
    ParticleBase(t_eventcont), LepCombBase()
{
    // change partice type
    m_partType = ParticleType::Dilepton;

    // assume that order comes from outside
    m_lepOne = lepOne;
    m_lepTwo = lepTwo;
    m_fsr = 0;

    m_charge = lepOne->getCharge() + lepTwo->getCharge();

    m_dilepType = DileptonType::NA;
    m_isTruth = false;
    // Add more as types are needed
    if(m_lepOne->getPartType() == ParticleType::Muon 
            && m_lepTwo->getPartType() == ParticleType::Muon)
    {
        m_dilepType = DileptonType::_2mu;
    }
    else if(m_lepOne->getPartType() == ParticleType::Electron 
            && m_lepTwo->getPartType() == ParticleType::Electron)
    {
        m_dilepType = DileptonType::_2e;
    }
    
    else if((m_lepOne->getPartType() == ParticleType::Muon
            && m_lepTwo->getPartType() == ParticleType::Electron))
    {
        m_dilepType = DileptonType::emu;
    }
    else if((m_lepOne->getPartType() == ParticleType::Electron
             && m_lepTwo->getPartType() == ParticleType::Muon))
    {
        m_dilepType = DileptonType::emu;
    }
    else if(m_lepOne->getPartType() == ParticleType::Truth
            && m_lepTwo->getPartType() == ParticleType::Truth)
    {
        m_isTruth = true;
        
        if(abs(m_lepOne->getTruthPID()) == 11
           && abs(m_lepTwo->getTruthPID()) == 11 )
            m_dilepType = DileptonType::_2e;
        
        else if(abs(m_lepOne->getTruthPID()) == 13
                && abs(m_lepTwo->getTruthPID()) == 13 )
            m_dilepType = DileptonType::_2mu;
        
        else if(abs(m_lepOne->getTruthPID()) == 15
                && abs(m_lepTwo->getTruthPID()) == 15 )
            m_dilepType = DileptonType::_2tau;
                
        // TO deal with fakes
        //else
        //{
        //    LOG(logERROR)<<"ParticleDilepton: Truth Lep type not recongnized";
        //    LOG(logERROR)<<"m_lepOne PDGID: "<<m_lepOne->getTruthPID();
        //    LOG(logERROR)<<"m_lepTwo PDGID: "<<m_lepTwo->getTruthPID();

        //    exit(1);
        //}
    }
    // Need to add support for _mue and _emu before this fix can be added
//    else
//    {
//        LOG(logERROR)<<"ParticleDilepton: particle type not supported";
//        LOG(logERROR)<<"Incoming m_lepOne type: " << m_lepOne->getPartType();
//        LOG(logERROR)<<"Incoming m_lepTwp type: " << m_lepTwo->getPartType();
//        exit(1);
//    }

    initMap();
    setTLVType(TLVType::None);
    if(m_isTruth) setAnalysisType(AnalysisType::Truth);
    else setAnalysisType(m_eventCont->m_analType);
    
    m_hasFSR = false;
}

ParticleDilepton::~ParticleDilepton()
{

}

// To init the map
void ParticleDilepton::initMap()
{
    for(Int_t i = 0; i < TLVType::end; i++)
    {
        TLVType::TLVType currTLVType = static_cast<TLVType::TLVType>(i);

        if(m_lepOne->checkTLVType(currTLVType) && m_lepTwo->checkTLVType(currTLVType))
        {
            addAnalTLV(currTLVType, (m_lepOne->getAnalTLV(currTLVType) + m_lepTwo->getAnalTLV(currTLVType)));
        }
    }


}

// Getters
ParticleVar* ParticleDilepton::getLep(Int_t i) const
{
    if(i == 0) return m_lepOne;
    else if(i == 1) return m_lepTwo;
    else return NULL;
}


// Setters
void ParticleDilepton::setFSR(ParticleVar *fsr)
{
    m_fsr = fsr;
    m_hasFSR = true;

}

// Clear FSR so Calculate4l can deal with multiple higgs candidates with common Zs
void ParticleDilepton::clearFSR()
{
    // clear the boolean variable
    m_hasFSR = false;
    m_fsr = 0;
}

void ParticleDilepton::setTLVType(TLVType::TLVType tlvType)
{
    if(m_lepOne) m_lepOne->setTLVType(tlvType);
    if(m_lepTwo) m_lepTwo->setTLVType(tlvType);
    if(m_fsr) m_fsr->setTLVType(tlvType);

    ParticleBase::setTLVType(tlvType);

}

void ParticleDilepton::setAnalysisType(AnalysisType::AnalysisType analType)
{
    if(m_lepOne) m_lepOne->setAnalysisType(analType);
    if(m_lepTwo) m_lepTwo->setAnalysisType(analType);
    if(m_fsr) m_fsr->setAnalysisType(analType);

    ParticleBase::setAnalysisType(analType);

}

// To print debug information
void ParticleDilepton::printDebug() const
{
    cout<<"type: ";
    if(m_dilepType == DileptonType::NA) cout<<"NA";
    if(m_dilepType == DileptonType::_2mu) cout<<"_2mu";
    if(m_dilepType == DileptonType::_2e) cout<<"_2e";
    cout<<endl;
    cout<<"Charge: "<<m_charge<<endl;

    for(Int_t i = 0; i < 2; i++)
    {
        cout<<"Lep "<<i<<" pT: "<<getLep(i)->getTLV().Pt()<<" charge: "<<getLep(i)->getCharge();
        if(getLep(i)->getPartType() == ParticleType::Muon) cout<<" PartType: Muons";
        if(getLep(i)->getPartType() == ParticleType::Electron) cout<<" PartType: Electron";
        cout<<endl;
    }
    cout<<"Mass: "<<getTLV().M()<<endl;
}


// To check with overlap
Bool_t ParticleDilepton::isOverlap(const ParticleDilepton* temp) const
{
    if(this->getLepOne() == temp->getLepOne()) return true;
    if(this->getLepOne() == temp->getLepTwo()) return true;
    if(this->getLepTwo() == temp->getLepOne()) return true;
    if(this->getLepTwo() == temp->getLepTwo()) return true;

    return false;
}

// To check with overlap
Bool_t ParticleDilepton::isOverlap(const ParticleVar* temp) const
{
    if(this->getLepOne() == temp) return true;
    if(this->getLepTwo() == temp) return true;
    
    return false;
}

