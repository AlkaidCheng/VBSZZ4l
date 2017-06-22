#include "HZZCutCommon/ParticleQuadlepton.h"
using namespace std;

ParticleQuadlepton::ParticleQuadlepton(EventContainer* t_eventcont, ParticleDilepton* Z1, ParticleDilepton* Z2, bool domZ1mZ2Pair):
    ParticleBase(t_eventcont), LepCombBase()
{
    // change partice type
    m_partType = ParticleType::Quadlepton;

    // do an internal repairing of the information
    if(domZ1mZ2Pair)
    {
        // closest to z mass
        Double_t tempDiff_i = fabs(Z1->getTLV().M() - pdgZMass);
        Double_t tempDiff_j = fabs(Z2->getTLV().M() - pdgZMass);
        if(tempDiff_i < tempDiff_j)
        {
            m_Z1 = Z1;
            m_Z2 = Z2;
        }
        else
        {
            m_Z1 = Z2;
            m_Z2 = Z1;
        }
    }
    else
    {
        m_Z1 = Z1;
        m_Z2 = Z2;
    }

    m_charge = m_Z1->getCharge() + m_Z2->getCharge();

    m_quadType = QuadleptonType::NA;
    m_quadAnalType = QuadAnalType::NA;

    m_isTruth = false;
    // Add more as types are needed
    if(m_Z1->getDilepType() == DileptonType::_2mu)
    {
        if(m_Z2->getDilepType() == DileptonType::_2mu) m_quadType = QuadleptonType::_4mu;
        if(m_Z2->getDilepType() == DileptonType::_2e) m_quadType = QuadleptonType::_2mu2e;
        if(m_Z2->getDilepType() == DileptonType::_2tau) m_quadType = QuadleptonType::_2mu2tau;
    }
    else if(m_Z1->getDilepType() == DileptonType::_2e)
    {
        if(m_Z2->getDilepType() == DileptonType::_2mu) m_quadType = QuadleptonType::_2e2mu;
        if(m_Z2->getDilepType() == DileptonType::_2e) m_quadType = QuadleptonType::_4e;
        if(m_Z2->getDilepType() == DileptonType::_2tau) m_quadType = QuadleptonType::_2e2tau;
    }
    else if(m_Z1->getDilepType() == DileptonType::_2tau)
    {
        if(m_Z2->getDilepType() == DileptonType::_2mu) m_quadType = QuadleptonType::_2tau2mu;
        if(m_Z2->getDilepType() == DileptonType::_2e) m_quadType = QuadleptonType::_2tau2e;
        if(m_Z2->getDilepType() == DileptonType::_2tau) m_quadType = QuadleptonType::_4tau;
    }
    else if(m_Z1->getDilepType() == DileptonType::emu)
    {
        if(m_Z2->getDilepType() == DileptonType::_2mu) m_quadType = QuadleptonType::_emu2mu;
        if(m_Z2->getDilepType() == DileptonType::_2e) m_quadType = QuadleptonType::_emu2e;
    } 
    if(m_Z1->isTruth() && m_Z2->isTruth()) m_isTruth = true;
    else if(!m_Z1->isTruth() && !m_Z2->isTruth()) m_isTruth = false;
    else
    {
        LOG(logERROR)<<"ParticleQuadlepton - truth type mismatch";
        LOG(logERROR)<<"Z1 isTruth: "<<m_Z1->isTruth();
        LOG(logERROR)<<"Z2 isTruth: "<<m_Z2->isTruth();
        exit(1);
    }
    
        
    initMap();
    setTLVType(TLVType::None);
    if(m_isTruth) setAnalysisType(AnalysisType::Truth);
    else setAnalysisType(m_eventCont->m_analType);

    m_hasFSR = false;
}

ParticleQuadlepton::~ParticleQuadlepton()
{
    
}

// For quad name
TString ParticleQuadlepton::getQuadName() const
{
    if(m_quadType == QuadleptonType::NA)        return "NA";
    if(m_quadType == QuadleptonType::_4mu)      return "4mu";
    if(m_quadType == QuadleptonType::_2e2mu)    return "2e2mu";
    if(m_quadType == QuadleptonType::_2mu2e)    return "2mu2e";
    if(m_quadType == QuadleptonType::_4e)       return "4e";
    if(m_quadType == QuadleptonType::_4tau)     return "4tau";
    if(m_quadType == QuadleptonType::_2e2tau)   return "2e2tau";
    if(m_quadType == QuadleptonType::_2tau2e)   return "2tau2e";
    if(m_quadType == QuadleptonType::_2mu2tau)  return "2mu2tau";
    if(m_quadType == QuadleptonType::_2tau2mu)  return "2tau2mu";
    if(m_quadType == QuadleptonType::_emu2mu)   return "emu2mu";
    if(m_quadType == QuadleptonType::_emu2e)    return "emu2e";
    return "NA";
}


// To init the map
void ParticleQuadlepton::initMap()
{
    for(Int_t i = 0; i < TLVType::end; i++)
    {
        TLVType::TLVType currTLVType = static_cast<TLVType::TLVType>(i);

        if(m_Z1->checkTLVType(currTLVType) && m_Z2->checkTLVType(currTLVType))
        {
            addAnalTLV(currTLVType, (m_Z1->getAnalTLV(currTLVType) + m_Z2->getAnalTLV(currTLVType)));
        }
    }
}

// Getters
ParticleVar* ParticleQuadlepton::getLep(Int_t i) const
{
         if(i == 0) return m_Z1->getLep(0);
    else if(i == 1) return m_Z1->getLep(1);
    else if(i == 2) return m_Z2->getLep(0);
    else if(i == 3) return m_Z2->getLep(1);
    else return NULL;
}


// Setters
void ParticleQuadlepton::setFSR(ParticleVar *fsr, Int_t whichZ)
{
    m_hasFSR = true;
    
    if(whichZ == 1) 
    {
        m_Z1->setFSR(fsr);
        m_Z1->addAnalTLV(TLVType::FSR, (m_Z1->getTLV() + fsr->getTLV()), true);
    }
    else if(whichZ == 2)
    {
        m_Z2->setFSR(fsr);
        m_Z2->addAnalTLV(TLVType::FSR, (m_Z2->getTLV() + fsr->getTLV()), true); 
    }
    else 
    {
        cout<<"ParticleQuadlepton::setFSR(ParticleBase *fsr, Int_t whichZ): whichZ not recognized - val: "<<whichZ<<endl;
        exit(1);
    }
    
    addAnalTLV(TLVType::FSR, (m_Z1->getAnalTLV(TLVType::FSR) + m_Z2->getAnalTLV(TLVType::FSR)), true);


}

// Clear FSR so CalculateVar4l can deal with multiple higgs candidates with common Zs
void ParticleQuadlepton::clearFSR()
{
    // clear the boolean for FSR
    m_hasFSR = false;
    // clear FSR internally in each dilepton
    m_Z1->clearFSR();
    m_Z2->clearFSR();
}

void ParticleQuadlepton::setTLVType(TLVType::TLVType tlvType)
{
    if(m_Z1) m_Z1->setTLVType(tlvType);
    if(m_Z2) m_Z2->setTLVType(tlvType);

    ParticleBase::setTLVType(tlvType);

}

void ParticleQuadlepton::setAnalysisType(AnalysisType::AnalysisType analType)
{
    if(m_Z1) m_Z1->setAnalysisType(analType);
    if(m_Z2) m_Z2->setAnalysisType(analType);

    ParticleBase::setAnalysisType(analType);

}


// To print debug information
void ParticleQuadlepton::printDebug() const
{
    cout<<"type: ";
    if(m_quadType == QuadleptonType::NA) cout<<"NA";
    if(m_quadType == QuadleptonType::_4mu) cout<<"_4mu";
    if(m_quadType == QuadleptonType::_2e2mu) cout<<"_2e2mu";
    if(m_quadType == QuadleptonType::_2mu2e) cout<<"_2mu2e";
    if(m_quadType == QuadleptonType::_4e) cout<<"_4e";
    if(m_quadType == QuadleptonType::_4tau) cout<<"_4tau";
    if(m_quadType == QuadleptonType::_2e2tau) cout<<"_2e2tau";
    if(m_quadType == QuadleptonType::_2tau2e) cout<<"_2tau2e";
    if(m_quadType == QuadleptonType::_2mu2tau) cout<<"_2mu2tau";
    if(m_quadType == QuadleptonType::_2tau2mu) cout<<"_2tau2mu";
    if(m_quadType == QuadleptonType::_emu2mu) cout<<"_emu2mu";
    if(m_quadType == QuadleptonType::_emu2e) cout<<"_emu2e";

    
    cout<<endl;
    cout<<"Charge: "<<m_charge<<endl;
    cout<<"m4l Mass: "<<getTLV().M()<<endl;
    cout<<"mZ1 Mass: "<<m_Z1->getTLV().M()<<endl;
    cout<<"mZ2 Mass: "<<m_Z2->getTLV().M()<<endl;
    
    for(Int_t i = 0; i < getLepSize(); i++) getLep(i)->printDebug();

}

Bool_t ParticleQuadlepton::isOverlap(const ParticleVar* lep) const
{
    for(Int_t i = 0; i < getLepSize(); i++)
    {
        if(this->getLep(i) == lep) return true;
    }
    
    return false;
}




