#include "HZZCutCommon/SmearingJet.h"
using namespace std;

SmearingJet::SmearingJet(EventContainer* eventcont) :
    SmearingBase(eventcont)
{
    m_jetCalibTool = ToolHandle<IJetCalibrationTool>("JetCalibTool");
    if(m_jetCalibTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IJetCalibrationTool";
        exit(1);
    }
    
    m_jesTool = ToolHandle<ICPJetUncertaintiesTool>("JESTool");
    if(m_jesTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve ICPJetUncertaintiesTool";
        exit(1);
    }
    
    m_jerTool = ToolHandle<IJERSmearingTool>("JERSmearingTool");
    if(m_jerTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IJERSmearingTool";
        exit(1);
    }
    m_btagSelTool_60 = ToolHandle<IBTaggingSelectionTool>("BTagSelTool_60");
    if(m_btagSelTool_60.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IBTaggingSelectionTool_60";
        exit(1);
    }
    m_btagSelTool_70 = ToolHandle<IBTaggingSelectionTool>("BTagSelTool_70");
    if(m_btagSelTool_70.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IBTaggingSelectionTool_70";
        exit(1);
    }
    m_btagSelTool_77 = ToolHandle<IBTaggingSelectionTool>("BTagSelTool_77");
    if(m_btagSelTool_77.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IBTaggingSelectionTool_77";
        exit(1);
    }

    m_btagSelTool_85 = ToolHandle<IBTaggingSelectionTool>("BTagSelTool_85");
    if(m_btagSelTool_85.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IBTaggingSelectionTool_85";
        exit(1);
    }
    m_fJVTTool = ToolHandle<IJetModifier>("fJVTTool");
    if(m_fJVTTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IJetModifier fJVTTool ";
        exit(1);
    }
    m_jvtagup = ToolHandle<IJetUpdateJvt>("jvtag");
    if(m_jvtagup.retrieve().isFailure())
    {
        LOG(logERROR) <<"SmearingJet::SmearingJet() - cannot retrieve IJetUpdateJvt";
        exit(1);
    }
    m_jetJVTEffTool = ToolHandle<CP::IJetJvtEfficiency>("JetJvtEfficiency");
    if(m_jetJVTEffTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutParticleJet::CutParticleJet() - cannot retrieve IJetJvtEfficiency";
        exit(1);
    }

}

SmearingJet::~SmearingJet()
{
    clearVars();
}

// To reset for each new event
void SmearingJet::clearVars()
{
    m_jetCont = 0;
    SmearingBase::clearVars();
}


// Function that loops over the vector and smears it
void SmearingJet::process()
{
    if(m_jetCont == 0)
    {
        LOG(logERROR)<<"Jet Smear: Jet container not specified";
        exit(1);
    }
    
    
    m_shallowCopy = xAOD::shallowCopyContainer( *m_jetCont );
    m_eventCont->store->record( m_shallowCopy.first, "jetCorr" ).ignore();
    m_eventCont->store->record( m_shallowCopy.second, "jetCorrAux" ).ignore();
    Int_t i = 0;
    for( auto jet : *( m_shallowCopy.first ) ) {
        processVar(jet);
        m_partList[i]->addAnalParticle(m_eventCont->m_analType, jet);
        m_partList[i]->addAnalTLV(TLVType::Unconstrained, jet->p4());
        i++;
    }
   
    const xAOD::JetContainer* m_jetCont;
    m_eventCont->getEvent()->retrieve( m_jetCont, "AntiKt4EMTopoJets" ).ignore();
    xAOD::setOriginalObjectLink( *m_jetCont, *m_shallowCopy.first );

    if(m_eventCont->isMC)
    {
        // apply this here to trigger a decoration of the truth HS jets for later use in JVT dropping
        float jvtSF = 1;
        if(!m_jetJVTEffTool->applyAllEfficiencyScaleFactor(m_shallowCopy.first, jvtSF))
        {
            LOG(logERROR)<<"Cannot apply jet JVT SF in SmearingJet";
            exit(1);
        }
    }
    m_fJVTTool->modify(*(m_shallowCopy.first));
    
}

// Function to smear each individual event
void SmearingJet::processVar(xAOD::IParticle* currPart)
{
    
    if(currPart->type() != xAOD::Type::Jet)
    {
        LOG(logERROR)<<"SmearingJet::processVar particle type not supported";
        LOG(logERROR)<<"Incoming part type: "<<currPart->type();
        exit(1);
    }
    
    xAOD::Jet* currJet = dynamic_cast<xAOD::Jet*>(currPart);
    
    if(m_eventCont->doSmear)
    {
        if(!m_jetCalibTool->applyCalibration(*currJet).isSuccess())
        {
            LOG(logERROR)<<"Cannot apply Jet Calibration";
            exit(1);
        }

        /* b-tagging */

        // BTagging valid in pt > 20 GeV, |eta| < 2.5
        bool inBTagKinRange = currJet->pt() > 20 * 1000 && std::fabs(currJet->eta()) < 2.5;

        // B-Jet criteria
        bool isbjet = ( inBTagKinRange && m_btagSelTool_70->accept(*currJet) );
        currJet->auxdecor<int>("isBjet70") = isbjet;
        currJet->auxdecor<char>("IsBjet") = isbjet; // as an alternative to jet flavour uncertainties for bJets

        currJet->auxdecor<int>("isBjet85") = ( inBTagKinRange && m_btagSelTool_85->accept(*currJet) );
        currJet->auxdecor<int>("isBjet77") = ( inBTagKinRange && m_btagSelTool_77->accept(*currJet) );
        currJet->auxdecor<int>("isBjet60") = ( inBTagKinRange && m_btagSelTool_60->accept(*currJet) );



        if(!m_jesTool->applyCorrection(*currJet))
        {
            LOG(logERROR)<<"Cannot apply JES";
            exit(1);
        }

        if(!m_jerTool->applyCorrection(*currJet))
        {
            LOG(logERROR)<<"Cannot apply JER";
            exit(1);
        }
    } 

    // JVT update
    float newjvt = m_jvtagup->updateJvt(*currJet);
    currJet->auxdecor<float>("Jvt") = newjvt;



    //// Get b-tagging efficiency:
    //float weight = 0;
    //
    //if(currJet->auxdecor<float>("isBjet"))
    //{
    //    if(!m_btagEffTool->getScaleFactor(*currJet, weight))
    //    {
    //        LOG(logERROR)<<"Cannot get b-tagging SF"; exit(1);
    //    }
    //}
    //else if(inBTagKinRange)
    //{
    //    if(!m_btagEffTool->getInefficiencyScaleFactor(*currJet, weight))
    //    {
    //        LOG(logERROR)<<"Cannot get b-tagging SF"; exit(1);
    //    }
    //}
    //else
    //{
    //    weight = 1;
    //}

    //currJet->auxdecor<float>("Bjet_SF") = weight;
    
}




