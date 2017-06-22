#include "HZZCutCommon/ParticleBase.h"
using namespace std;

ParticleBase::ParticleBase(EventContainer* t_eventcont)
{
    m_eventCont = t_eventcont;

    // Certain default values
    m_partType = ParticleType::None;
    m_analType = AnalysisType::None;

    m_index = -1;
    m_charge = -999;

    
    m_intMetaData.clear();

}


ParticleBase::~ParticleBase()
{
    m_tlvCont.clear();
}


// gets a specific TLV 
TLorentzVector ParticleBase::getAnalTLV(TLVType::TLVType tlvType) const
{
    if(m_tlvCont.find(tlvType) != m_tlvCont.end())
    {
        return m_tlvCont.at(tlvType);
    }
    else
    {
        Error("ParticleBase::getAnalTLV()", "TLV type requested not in container");
        LOG(logERROR)<<"Class name: "<<getName()<<" requested TLV type: "<<tlvType;
        exit(1);
    }
}


// adders 
// Adds TLV to the Analysis maps
void ParticleBase::addAnalTLV(TLVType::TLVType tlvType, TLorentzVector tlv, Bool_t overWrite)
{
    // If we need to overwrite the TLV
    if(overWrite) 
    {
        m_tlvCont[tlvType] = tlv;
        return;
    }

    // Now if the map doesn't contain the TLV, add it, otherwise exist and complain
    if(m_tlvCont.find(tlvType) == m_tlvCont.end())
    {
        m_tlvCont[tlvType] = tlv;   
    }
    else
    {
        Error("ParticleBase::addAnalTLV()", "AnalysisType already in map");     
        exit(1);
    }
}

// Setters
// sets the TLV type to the tlvType
void ParticleBase::setTLVType(TLVType::TLVType tlvType)
{
    if(m_tlvCont.find(tlvType) != m_tlvCont.end())
    {
        m_currTLV = m_tlvCont[tlvType]; 
        m_currTLVType = tlvType;
    }
    else
    {
        Error("ParticleBase::setTLVType()", "Analysis type requested not in container");
        LOG(logERROR)<<"Derived Class: "<<getPartType();
        exit(1);
    }

}

// sets the overall analysis type to analType
void ParticleBase::setAnalysisType(AnalysisType::AnalysisType analType)
{
    if(analType == AnalysisType::None)         setTLVType(TLVType::None);
    else if(analType == AnalysisType::Nominal) setTLVType(TLVType::Unconstrained);
    else if(analType == AnalysisType::Truth)   setTLVType(TLVType::Truth);
    else setTLVType(TLVType::Unconstrained);

    // Storing the currAnalysis Type
    m_analType = analType;
}


// To check if the type is in the map
Bool_t ParticleBase::checkTLVType(TLVType::TLVType tlvType) const
{
    if(m_tlvCont.find(tlvType) != m_tlvCont.end()) return true;
    else return false;
}


int ParticleBase::getMetadataInt(TString key)
{
    if(m_intMetaData.find(key) != m_intMetaData.end())
    {
        return m_intMetaData[key];
    }
    else
    {
        Error("ParticleBase::getMetadataInt()", "Key requested is not in the map");
        LOG(logERROR)<<"Key: "<<key;
        LOG(logERROR)<<"Derived Class: "<<getPartType();
        exit(1);
    }

}

