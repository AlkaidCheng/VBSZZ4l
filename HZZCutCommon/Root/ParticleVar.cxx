#include "HZZCutCommon/ParticleVar.h"
using namespace std;

ParticleVar::ParticleVar(EventContainer* t_eventcont, const xAOD::IParticle* t_particle, Int_t t_index):
    ParticleBase(t_eventcont)
{
    // Store local copy
    m_currParticle = t_particle;

    if(m_currParticle->type() == xAOD::Type::Electron)
    {
        m_partType = ParticleType::Electron;
        m_partName = "Electron";
    }
    else if(m_currParticle->type() == xAOD::Type::Muon)
    {
        m_partType = ParticleType::Muon;
        m_partName = "Muon";
    }
    else if(m_currParticle->type() == xAOD::Type::Jet)
    {
        m_partType = ParticleType::Jet;
        m_partName = "Jet";
    }
    else if(m_currParticle->type() == xAOD::Type::Photon)
    {
        m_partType = ParticleType::Photon;
        m_partName = "Photon";
    }
    else if(m_currParticle->type() == xAOD::Type::Tau)
    {
        m_partType = ParticleType::Tau;
        m_partName = "Tau";
    }
    else if(m_currParticle->type() == xAOD::Type::TruthParticle)
    {
        m_partType = ParticleType::Truth;
        m_partName = "Truth";
        
        const xAOD::TruthParticle* temp = dynamic_cast<const xAOD::TruthParticle*> (m_currParticle);
        m_truthPDG = temp->pdgId();
        addAnalParticle(AnalysisType::Truth, m_currParticle);
        addAnalTLV(TLVType::Truth, m_currParticle->p4());
    }
    else
    {
        LOG(logERROR)<<"ParticleVar: particle type not supported";
        LOG(logERROR)<<"Incoming particle type: " << m_currParticle->type();
        exit(1);
    }

    // Adding it to the map
    addAnalParticle(AnalysisType::None, m_currParticle);

    m_index = t_index;

    m_charge=0;
    if(m_currParticle->type() == xAOD::Type::Muon)
    {
        const xAOD::Muon *partTemp = dynamic_cast<const xAOD::Muon*>(m_currParticle);
        xAOD::Muon *mu = const_cast<xAOD::Muon*>(partTemp);
        if  (xAOD::Muon::SiliconAssociatedForwardMuon == mu->muonType()) {
            const xAOD::TrackParticle* mu_tp_com = mu->trackParticle(xAOD::Muon::CombinedTrackParticle);
            if(mu_tp_com) mu->setCharge(mu_tp_com->charge());
        }
    }

    SG::AuxElement::Accessor< float > acc("charge");
    if(acc.isAvailable( *m_currParticle ) ){
        m_charge = acc( *m_currParticle);
    }
    else if(m_currParticle->type() == xAOD::Type::TruthParticle) {
        const xAOD::TruthParticle* temp = dynamic_cast<const xAOD::TruthParticle*> (m_currParticle);
        m_charge = temp->charge();
    }

    // Create the TLV
    addAnalTLV(TLVType::None, m_currParticle->p4());
    setTLVType(TLVType::None);
}

ParticleVar::~ParticleVar()
{
    m_particleCont.clear();
}



// adders 
// Adds TLV to the Analysis maps
void ParticleVar::addAnalParticle(AnalysisType::AnalysisType analType, const xAOD::IParticle* t_particle, Bool_t overWrite)
{
    // If we need to overwrite the TLV
    if(overWrite) 
    {
        m_particleCont[analType] = t_particle;
        return;
    }

    // Now if the map doesn't contain the TLV, add it, otherwise exist and complain
    if(m_particleCont.find(analType) == m_particleCont.end())
    {
        m_particleCont[analType] = t_particle;  
    }
    else
    {
        Error("ParticleVar::addAnalParticle()", "AnalysisType already in map");     
        exit(1);
    }
}

// Getters
// Simple getter
const xAOD::IParticle* ParticleVar::getParticle() const
{
    return m_currParticle;  
}

// To get a specific type of electron. Complains if the analysis type is not in present
const xAOD::IParticle* ParticleVar::getAnalParticle(AnalysisType::AnalysisType analType) const
{
    if(m_particleCont.find(analType) != m_particleCont.end())
    {
        return m_particleCont.at(analType);
    }
    else
    {
        Error("ParticleVar::getAnalParticle()", "Analysis type requested not in container");       
        exit(1);
    }
}


// sets the overall analysis type to analType
void ParticleVar::setAnalysisType(AnalysisType::AnalysisType analType)
{
    // To set the TLV
    ParticleBase::setAnalysisType(analType);

    // Setting the xAOD object  
    if(m_particleCont.find(analType) != m_particleCont.end())
    {
        m_currParticle = m_particleCont[analType];  
    }
    else
    {
        Error("ParticleVar::setAnalysisType()", "Analysis type requested not in container");       
        exit(1);
    }


    // Storing the currAnalysis Type
    m_analType = analType;
}


void ParticleVar::printDebug() const
{
    cout<<"type: "<<m_partName;
    if(m_partType == ParticleType::Truth) cout<<" PDGID: "<<m_truthPDG;
    cout<<" Charge: "<<m_charge;
    cout<<" pT: "<<getTLV().Pt();
    cout<<" eta: "<<getTLV().Eta();
    cout<<" phi: "<<getTLV().Phi();
    cout<<" M: "<<getTLV().M();
    cout<<endl;
}
