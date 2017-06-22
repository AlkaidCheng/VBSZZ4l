#include "H4lCutFlow/CutFlowllee.h"
using namespace std;

CutFlowllee::CutFlowllee(EventContainer* eventcont, ApplyWeight4l* applyWeight)
: CutFlow4l(eventcont, applyWeight)
{
    m_cutflowType = lleeCutFlow::NA;
}

CutFlowllee::~CutFlowllee()
{

}



// To set the cutFlow type
void CutFlowllee::cutFlowType(Int_t cutflowType)
{
    m_cutflowType = static_cast<lleeCutFlow::lleeCutFlow>(cutflowType);
    
    if(m_cutflowType == lleeCutFlow::relax)
    {
        m_cutFlowName += " relax llee";
        m_currQuadAnalType = QuadAnalType::ZplusXX;
    }
    if(m_cutflowType == lleeCutFlow::threeLplusX)
    {
        m_cutFlowName += " 3l+X llee";
        m_currQuadAnalType = QuadAnalType::threeLplusX;        
    }
    if(m_cutflowType == lleeCutFlow::ZplusXX)
    { 
        m_cutFlowName += " Z+XX llee";
        m_currQuadAnalType = QuadAnalType::ZplusXX;        
    }
    if(m_cutflowType == lleeCutFlow::NA)
    {
        LOG(logERROR)<<"CutFlowllee - cutflow type not set";
        exit(1);
    }


}
void CutFlowllee::setQuadAnalysisType(Int_t quadType)
{
    m_limitQuadType = static_cast<QuadleptonType::QuadleptonType>(quadType);
    
    if(m_limitQuadType == QuadleptonType::_4e) m_cutFlowName += " 4e";
    else if(m_limitQuadType == QuadleptonType::_2mu2e) m_cutFlowName += " 2mu2e";
    else
    {
        LOG(logERROR)<<"quadType not supported";
        LOG(logERROR)<<"quadType requested: "<<quadType;
        exit(1);
    }
    
    
}
////////////////////////////////////////////////
//
// Main function controlling the higgs selection
//
////////////////////////////////////////////////
void CutFlowllee::process()
{
    createLepList();
    
    // Lepton Cut
    if(!cutNumLep()) return;
    updateCutFlow(cutFlow3lx::Lepton);
    
    // Getting the dilep combination
    getDilepComb();
    
    // Getting the quadLepton combination
    getQuadComb();
    
    // Overide the internal quad list with some intial cuts,
    // to contain all the possible combination of quads
    // After this start cutting on this list
    // Done this at it is easier to control
    m_quadList = m_quadInitList;
    
    cutMuonType();
    cutCharge();
    cutQuadFlavour();
    
    // SFOS cut
    if(m_quadList.size() == 0) return;
    updateCutFlow(cutFlow3lx::SFOS);
    
    // Kinematic cut
    cutKinematic();
    
    if(m_quadList.size() == 0) return;
    updateCutFlow(cutFlow3lx::Kinematics);
    
    // Trigger Match cut
    cutTrigMatch();
    
    if(m_quadList.size() == 0) return;
    updateCutFlow(cutFlow3lx::TriggerMatch);
    if(m_eventCont->isDebug)
    {
        for(size_t i = 0; i < m_quadList.size(); i++)
        {
            LOG(logDEBUG)<<m_cutFlowName<<" before any Z cuts - llee Quadlep i: "<<i;
            m_quadList[i]->printDebug();
        }
        cout<<endl<<endl<<endl;;
    }
    // Cut to ensure that all the Z1 contain loose ID electrons
    cutZ1ID();
    updateCutFlow(cutFlow3lx::Z1ID, m_quadList.size());
    cutZ2ID();
    updateCutFlow(cutFlow3lx::Z2ID, m_quadList.size());
    
    pickQuadEvent();
    
    updateCutFlow(cutFlow3lx::Z2ID, m_quadList.size());
    
    if(m_eventCont->isDebug)
    {
        for(size_t i = 0; i < m_quadList.size(); i++)
        {
            m_cutQuad->cutIsolation(m_quadList[i]);
            m_cutQuad->cutD0Sig(m_quadList[i]);
            LOG(logDEBUG)<<m_cutFlowName<<" llee after picking quad i: "<<i;
            m_quadList[i]->printDebug();
            
            for(int j = 0; j < m_quadList[i]->getLepSize(); j++)
            {
                LOG(logDEBUG)<<"lep i "<<j
                <<" iso: "<<m_quadList[i]->getLep(j)->getParticle()->auxdecor< int >( "isoCut" )
                <<" d0: "<<m_quadList[i]->getLep(j)->getParticle()->auxdecor< int >( "passD0Sig" )
                <<" charge: "<<m_quadList[i]->getLep(j)->getCharge()
                <<" loose: "<<m_quadList[i]->getLep(j)->getParticle()->auxdecor< int >( "looseID" )
                <<" pt: "<<m_quadList[i]->getLep(j)->getParticle()->pt();
            }
        }
        cout<<endl<<endl<<endl;;

    }
    
    
    cutLeadingZ();
    updateCutFlow(cutFlow3lx::LeadingZIsoD0, m_quadList.size());
    
    if(m_eventCont->isDebug)
    {
        for(size_t i = 0; i < m_quadList.size(); i++)
        {
            LOG(logDEBUG)<<m_cutFlowName<<" llee after leading Z1 cut i: "<<i;
            m_quadList[i]->printDebug();
        }
        cout<<endl<<endl<<endl;;

    }
    
    

    // Picking quad closest with Z1 closest to the ZPDG mass;
    performHiggsCuts();
    if(m_eventCont->isDebug)
    {
        for(size_t i = 0; i < m_quadList.size(); i++)
        {
            LOG(logDEBUG)<<m_cutFlowName<<" llee after Quadlep i: "<<i;
            m_quadList[i]->printDebug();
        
            for(int j = 0; j < m_quadList[i]->getLepSize(); j++)
            {
                LOG(logDEBUG)<<"lep i "<<j
                <<" iso: "<<m_quadList[i]->getLep(j)->getParticle()->auxdecor< int >( "isoCut" )
                <<" d0: "<<m_quadList[i]->getLep(j)->getParticle()->auxdecor< int >( "passD0Sig" )
                <<" charge: "<<m_quadList[i]->getLep(j)->getCharge()
                <<" pt: "<<m_quadList[i]->getLep(j)->getParticle()->pt();
            }
        }
        cout<<endl<<endl<<endl;;

    }

    // 3l+x cut
    if(m_cutflowType == lleeCutFlow::threeLplusX) cut3lx();
    updateCutFlow(cutFlow3lx::_3lXCuts, m_quadList.size());
    

}


// To cut on the charge of the dilep
Bool_t CutFlowllee::cutDilepCharge(ParticleDilepton* currDilep)
{
    // If relax, don't cut on charge here since we relax the requirnments on
    // the subleading electrons
    if(m_cutflowType == lleeCutFlow::relax)
    {
        return true;
    }
    
    // If threeLplusX, cut charge at Quad level
    if(m_cutflowType == lleeCutFlow::threeLplusX)
    {
        return true;
    }
    // if ZplusXX, std cut
    if(m_cutflowType == lleeCutFlow::ZplusXX)
    {
        if(currDilep->getCharge() == 0) return true;
    }
    
    return false;
}

// To cut on the flavour of the dilep
Bool_t CutFlowllee::cutDilepType(ParticleDilepton* currDilep)
{
    if(currDilep->getDilepType() == DileptonType::_2mu) return true;
    else if(currDilep->getDilepType() == DileptonType::_2e)  return true;
    return false;
}

// Helper functions
// Cut based on the charge of the quad
Bool_t CutFlowllee::cutQuadCharge(ParticleQuadlepton* currQuad)
{
    if(currQuad->getZ1()->getCharge() != 0) return false;
    
    // if relax quad - no cut here
    if(m_cutflowType == lleeCutFlow::relax) return true;
    
    // if threeLplusX - Z2 is same sign
    if(m_cutflowType == lleeCutFlow::threeLplusX)
    {
        if(currQuad->getZ2()->getCharge() == 0) return false;
        else return true;
    }
    // if ZplusXX - Z2 is opposite sign
    if(m_cutflowType == lleeCutFlow::ZplusXX)
    {
        if(currQuad->getZ2()->getCharge() != 0) return false;
        else return true;
    }

    return false;
    
}
// Cut based on the favour of the quad
Bool_t CutFlowllee::cutQuadType(ParticleQuadlepton* currQuad)
{
    if(currQuad->getZ2()->getDilepType() != DileptonType::_2e) return false;
    
    if(m_limitQuadType == QuadleptonType::_2mu2e &&
       currQuad->getQuadType() == QuadleptonType::_2mu2e)  return true;
    if(m_limitQuadType == QuadleptonType::_4e &&
       currQuad->getQuadType() == QuadleptonType::_4e)     return true;
    if(m_limitQuadType == QuadleptonType::NA) return true;

    
    return false;
}

// Cut on the leading Z Isolation and d0
Bool_t CutFlowllee::cutLeadingIsoD0(ParticleQuadlepton* currQuad)
{
    m_cutQuad->cutIsolation(currQuad);
    m_cutQuad->cutD0Sig(currQuad);

    // Iso
    if(!currQuad->getZ1()->getLepOne()->getParticle()->auxdecor<int>("isoCut") || !currQuad->getZ1()->getLepTwo()->getParticle()->auxdecor<int>("isoCut")) return false;
   
    // D0 cut
    if(!currQuad->getZ1()->getLepOne()->getParticle()->auxdecor<int>("passD0Sig") || !currQuad->getZ1()->getLepTwo()->getParticle()->auxdecor<int>("passD0Sig")) return false;
    
    
    return true;
}

void CutFlowllee::cutQuadFlavour()
{
    for (Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        keep = cutQuadType(m_quadList[i]);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}
void CutFlowllee::cutLeadingZ()
{
    for (Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        
        keep = cutLeadingIsoD0(m_quadList[i]);
        
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}



// Remove all the quads that fail the muon cuts
void CutFlowllee::cutMuonType()
{
    for (Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        
        keep = CutFlow4l::cutMuonType(m_quadList[i]);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// Remove all the quads that fail the charge cuts
void CutFlowllee::cutCharge()
{
    //// charge and pt thresholds
    for (Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        
        keep = cutQuadCharge(m_quadList[i]);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// Remove all the quads that fail the kinematic cuts
void CutFlowllee::cutKinematic()
{
    //// charge and pt thresholds
    for (Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        
        keep = m_cutQuad->cutKinematic(m_quadList[i]);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// For trigger match the leptons in the quad
void CutFlowllee::cutTrigMatch()
{
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        keep = m_cutQuad->cutTrigMatch(m_quadList[i]);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// cut on the Z1 ID
void CutFlowllee::cutZ1ID()
{
    //el_i->auxdecor< int >( "looseID" )
    
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        keep = m_quadList[i]->getZ1()->getLepOne()->getParticle()->auxdecor< int >( "looseID" ) && m_quadList[i]->getZ1()->getLepTwo()->getParticle()->auxdecor< int >( "looseID" );
        
        // for leading muon pair
        if(m_quadList[i]->getZ1()->getDilepType() == DileptonType::_2mu) keep = true;
        
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}


// cut on the Z2 ID
void CutFlowllee::cutZ2ID()
{
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        // For 3l+x ask for atleast 1 lepton passing the looseID
        keep = m_quadList[i]->getZ2()->getLepOne()->getParticle()->auxdecor< int >( "looseID" ) || m_quadList[i]->getZ2()->getLepTwo()->getParticle()->auxdecor< int >( "looseID" );
       
        // For 3l+x, the highest pT Z2 lepton must be the looseID
        if(m_cutflowType == lleeCutFlow::threeLplusX)
        {

            bool z2Pass = true;

            // Ask the highest subleading to pass ID and iso and d0
            if(m_quadList[i]->getZ2()->getLepOne()->getParticle()->pt() > m_quadList[i]->getZ2()->getLepTwo()->getParticle()->pt())
            {
                if(!m_quadList[i]->getZ2()->getLepOne()->getParticle()->auxdecor< int >( "looseID" )) z2Pass = z2Pass && false;
            }
            else
            {
                if(!m_quadList[i]->getZ2()->getLepTwo()->getParticle()->auxdecor< int >( "looseID" )) z2Pass = z2Pass && false;
            }

            keep = z2Pass;
        }

        // for leading muon pair
        if(m_quadList[i]->getZ2()->getDilepType() == DileptonType::_2mu) keep = true;

  
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }

    }
}


// To pick a quadreplut with Z1 and Z2 closest to PDG mass
void CutFlowllee::pickQuadEvent()
{
    Double_t diffZ1 = 9999 * 1000;
    
    ParticleDilepton* closestZ1 = 0;
    
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        ParticleQuadlepton* temp =  m_quadList[i];
        
        // Find the closest one z mass
        Double_t tempDiff1 = fabs(temp->getZ1()->getTLV().M() - pdgZMass);
        
        if(tempDiff1 < diffZ1)
        {
            diffZ1 = tempDiff1;
            closestZ1 = temp->getZ1();
        }
    }
    
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        if(closestZ1 != m_quadList[i]->getZ1()) keep = false;
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}

// mZ and deltaR and overlapcuts
void CutFlowllee::performHiggsCuts()
{
    // mZ1 cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutMZ1(m_higgs);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else
        {
            updateCutFlow(cutFlow3lx::Z1Mass);
        }
    }
    
    // mZ2 cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutMZ2(m_higgs);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else
        {
            updateCutFlow(cutFlow3lx::Z2Mass);
        }
    }
    
    // DeltaR and Jpsi cut
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];
        keep = m_cutQuad->cutDeltaR(m_higgs) && m_cutQuad->JPsiVeto(m_higgs);
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else
        {
            updateCutFlow(cutFlow3lx::DeltaR);
        }
    }
    
    // el and el overlap
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {
        Bool_t keep = true;
        m_higgs = m_quadList[i];

        // Loop over all the electrons and make sure that there are no overlaps
        for(Int_t i = 0; i < m_higgs->getLepSize(); i++)
        {
            if(m_higgs->getLep(i)->getPartType() != ParticleType::Electron) continue;
            
            for (Int_t j = i + 1; j < m_higgs->getLepSize(); j++)
            {
                if(m_higgs->getLep(j)->getPartType() != ParticleType::Electron) continue;
                
                if(RemoveOverlap4l::elClusOlp(m_higgs->getLep(i), m_higgs->getLep(j)))
                {
                    keep = false;
                    break;
                }
            }
            
            if(!keep) break;
        }
        
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
        else
        {
            updateCutFlow(cutFlow3lx::eeOlv);
        }

    }
}



// cut on the Z2 ID
void CutFlowllee::cut3lx()
{
    for(Int_t i = 0; i < (Int_t) m_quadList.size(); i++)
    {

        m_cutQuad->cutIsolation(m_quadList[i], false);
        m_cutQuad->cutD0Sig(m_quadList[i], false);


        Bool_t keep = true;
         
        bool z1Pass = true;
        
        // Ask for Loose Z1
        if(!m_quadList[i]->getZ1()->getLepOne()->getParticle()->auxdecor< int >( "looseID" )) z1Pass = z1Pass && false;
        if(!m_quadList[i]->getZ1()->getLepTwo()->getParticle()->auxdecor< int >( "looseID" )) z1Pass = z1Pass && false;
        // Overide the above muons
        if(m_quadList[i]->getZ1()->getDilepType() == DileptonType::_2mu) z1Pass = true;


        // Ask for isolated and D0
        if(!m_quadList[i]->getZ1()->getLepOne()->getParticle()->auxdecor< int >( "isoCut" )) z1Pass = z1Pass && false;
        if(!m_quadList[i]->getZ1()->getLepTwo()->getParticle()->auxdecor< int >( "isoCut" )) z1Pass = z1Pass && false;
        
        if(!m_quadList[i]->getZ1()->getLepOne()->getParticle()->auxdecor< int >( "passD0Sig" )) z1Pass = z1Pass && false;
        if(!m_quadList[i]->getZ1()->getLepTwo()->getParticle()->auxdecor< int >( "passD0Sig" )) z1Pass = z1Pass && false;


        bool z2Pass = true;

        // Ask the highest subleading to pass ID and iso and d0
        if(m_quadList[i]->getZ2()->getLepOne()->getParticle()->pt() > m_quadList[i]->getZ2()->getLepTwo()->getParticle()->pt())
        {
            if(!m_quadList[i]->getZ2()->getLepOne()->getParticle()->auxdecor< int >( "looseID" )) z2Pass = z2Pass && false;
            if(!m_quadList[i]->getZ2()->getLepOne()->getParticle()->auxdecor< int >( "isoCut" )) z2Pass = z2Pass && false;
            if(!m_quadList[i]->getZ2()->getLepOne()->getParticle()->auxdecor< int >( "passD0Sig" )) z2Pass = z2Pass && false;
        }
        else
        {
            if(!m_quadList[i]->getZ2()->getLepTwo()->getParticle()->auxdecor< int >( "looseID" )) z2Pass = z2Pass && false;
            if(!m_quadList[i]->getZ2()->getLepTwo()->getParticle()->auxdecor< int >( "isoCut" )) z2Pass = z2Pass && false;
            if(!m_quadList[i]->getZ2()->getLepTwo()->getParticle()->auxdecor< int >( "passD0Sig" )) z2Pass = z2Pass && false;
        }

        for(int j = 0; j < 4; j++)
        {
            LOG(logDEBUG)<<"3lX specific cuts";
            LOG(logDEBUG)<<"pT: "<<m_quadList[i]->getLep(j)->getParticle()->pt();
            LOG(logDEBUG)<<"looseID: "<< m_quadList[i]->getLep(j)->getParticle()->auxdecor<int>("looseID");
            LOG(logDEBUG)<<"iso: "<< m_quadList[i]->getLep(j)->getParticle()->auxdecor<int>("isoCut");
            LOG(logDEBUG)<<"d0: "<< m_quadList[i]->getLep(j)->getParticle()->auxdecor<int>("passD0Sig");
        }

        keep = z1Pass && z2Pass;
  
        if(!keep)
        {
            m_quadList.erase(m_quadList.begin() + i);
            i--;
        }
    }
}






// For cutflow
void CutFlowllee::initCutFlow()
{
    for(Int_t i = 0; i <= cutFlow3lx::Final; i++)
    {
        m_cutName.push_back("");
    }
    for(Int_t i = 0; i < prodTypeSimp::MaxProdTypeSimp; i++)
    {
        m_catergoryName.push_back("");
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
    for (auto sysListItr:m_eventCont->m_sysList){
        m_rawCatNumber[sysListItr].reserve(m_cutName.size());
        m_weightCatNumber[sysListItr].reserve(m_cutName.size());
        
        for(Int_t i = 0; i < (Int_t) m_catergoryName.size(); i++)
        {
            m_rawCatNumber[sysListItr].push_back(0);
            m_weightCatNumber[sysListItr].push_back(0);
        }
    }
    
    m_cutName[cutFlow3lx::Total]             = "Total";
    m_cutName[cutFlow3lx::DataPreselection]  = "DataPreselection";
    m_cutName[cutFlow3lx::Preselection]      = "Preselection";
    m_cutName[cutFlow3lx::Trigger]           = "Trigger";
    m_cutName[cutFlow3lx::Lepton]            = "Lepton";
    m_cutName[cutFlow3lx::SFOS]              = "SFOS";
    m_cutName[cutFlow3lx::Kinematics]        = "Kinematics";
    m_cutName[cutFlow3lx::TriggerMatch]      = "TriggerMatch";
    m_cutName[cutFlow3lx::Z1ID]              = "Z1ID";
    m_cutName[cutFlow3lx::Z2ID]              = "Z2ID";
    m_cutName[cutFlow3lx::LeadingZIsoD0]     = "LeadingZIsoD0";
    m_cutName[cutFlow3lx::Z1Mass]            = "Z1Mass";
    m_cutName[cutFlow3lx::Z2Mass]            = "Z2Mass";
    m_cutName[cutFlow3lx::DeltaR]            = "DeltaR";
    m_cutName[cutFlow3lx::eeOlv]             = "eeOlv";
    m_cutName[cutFlow3lx::_3lXCuts]          = "_3lXCuts";
    m_cutName[cutFlow3lx::Final]             = "Final";
    
    m_catergoryName[prodTypeSimp::njet0]    = "nJet0";
    m_catergoryName[prodTypeSimp::njet1]    = "nJet1";
    m_catergoryName[prodTypeSimp::njet2_VH] = "nJet2_VH";
    m_catergoryName[prodTypeSimp::njet2_VBF]= "nJet2_VBF";
    m_catergoryName[prodTypeSimp::leptonic] = "leptonic";
    m_catergoryName[prodTypeSimp::ttH]      = "ttH";



}







