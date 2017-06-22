#include "HZZCutCommon/ParticleMulti.h"
using namespace std;

ParticleMulti::ParticleMulti(EventContainer* t_eventcont):
    ParticleBase(t_eventcont), LepCombBase()
{
    // change partice type
    m_partType = ParticleType::Multi;
    
        
    initMap();
    setTLVType(TLVType::None);
}

ParticleMulti::~ParticleMulti()
{
    m_particleList.clear();
    m_particleVarList.clear();
    m_particleMap.clear();
}

// To init the map
void ParticleMulti::initMap()
{
    for(Int_t i = 0; i < TLVType::end; i++)
    {
        TLVType::TLVType currTLVType = static_cast<TLVType::TLVType>(i);
        TLorentzVector tlv;
        bool update = true;
        for(size_t i = 0; i < m_particleList.size(); i++)
        {
            if(!m_particleList[i]->checkTLVType(currTLVType))
            {
                update = false;
                continue;
            }
            
            tlv += m_particleList[i]->getAnalTLV(currTLVType);
        }

        // Only add the tlv if all particle contain it
        if(update) addAnalTLV(currTLVType, tlv, true);
    }
}

ParticleBase* ParticleMulti::getParticle(std::string name) const
{
    if(m_particleMap.find(name) != m_particleMap.end())
    {
        return m_particleMap.at(name);
    }
    else
    {
        LOG(logERROR) <<"ParticleMulti::getParticle - Particle not found";
        LOG(logERROR) <<"Particle requested: "<<name;
        exit(1);
    }
}

void ParticleMulti::addParticle(std::string name, ParticleBase* particle, Bool_t overWrite)
{
    // Now if the map doesn't contain the particle
    if(m_particleMap.find(name) == m_particleMap.end())
    {
        m_particleMap[name] = particle;
        m_particleList.push_back(particle);
        initMap();
        setAnalysisType(m_analType);
        
    }
    else if (overWrite)
    {
        for(size_t i = 0; i < m_particleList.size(); i++)
        {
            if(m_particleList[i] == m_particleMap[name])
                m_particleList[i] = particle;
        }
        m_particleMap[name] = particle;
        initMap();
        setAnalysisType(m_analType);
    }
    else
    {
        Error("ParticleMulti::addParticle", "Name already in map");
        LOG(logERROR) <<"Particle trying to add: "<<name;
        exit(1);
    }
}

void ParticleMulti::addParticleVar(ParticleVar* particle, Bool_t overWrite)
{
    int index = -1;
    for(size_t i = 0; i < m_particleVarList.size(); i++)
    {
        if(m_particleVarList[i] == particle) index = i;
    }
    
    if(overWrite && index != -1) m_particleVarList[index] = particle;
    else if (index == -1) m_particleVarList.push_back(particle);
    else
    {
        Error("ParticleMulti::addParticleVar", "ParticleVar already in map");
        exit(1);
    }
}


void ParticleMulti::setTLVType(TLVType::TLVType tlvType)
{
    for(size_t i = 0; i < m_particleList.size(); i++)
    {
        m_particleList[i]->setTLVType(tlvType);
    }
    
    ParticleBase::setTLVType(tlvType);
}

void ParticleMulti::setAnalysisType(AnalysisType::AnalysisType analType)
{
    for(size_t i = 0; i < m_particleList.size(); i++)
    {
        m_particleList[i]->setAnalysisType(analType);
    }
    ParticleBase::setAnalysisType(analType);
}




// To print debug information
void ParticleMulti::printDebug() const
{
    for(size_t i = 0; i < m_particleVarList.size(); i++)
    {
        m_particleVarList[i]->printDebug();
    }
}

Bool_t ParticleMulti::isOverlap(const ParticleBase* part) const
{
    for(size_t i = 0; i < m_particleList.size(); i++)
    {
        if(m_particleList[i] == part) return true;
    }
    
    return false;
}




