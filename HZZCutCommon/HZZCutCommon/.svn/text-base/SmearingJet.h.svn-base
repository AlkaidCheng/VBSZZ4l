#ifndef SMEARINGJET_H
#define SMEARINGJET_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/SmearingBase.h"

// xAOD EDM include
#include "xAODJet/Jet.h"
#include "xAODJet/JetContainer.h"
#include "xAODBase/IParticleHelpers.h"

// CP tools
#include "JetCalibTools/IJetCalibrationTool.h"
#include "JetCPInterfaces/ICPJetUncertaintiesTool.h"
#include "JetResolution/IJERSmearingTool.h"
#include "JetMomentTools/JetForwardJvtTool.h"
#include "JetMomentTools/JetVertexTaggerTool.h"
#include "JetJvtEfficiency/IJetJvtEfficiency.h"

// b-jet tagging tools
#include <xAODBTaggingEfficiency/IBTaggingSelectionTool.h>

class SmearingJet : public SmearingBase 
{
    public:
        SmearingJet(EventContainer* eventcont);
        virtual ~SmearingJet();

        void process();
    
        void setJetCont(const xAOD::JetContainer* jetCont)
        {m_jetCont = jetCont;};
        const xAOD::JetContainer* getCalJetCont() const
        {return m_shallowCopy.first;};
    
        void clearVars();
    
        void processVar(xAOD::IParticle* currPart);

    protected:
        const xAOD::JetContainer* m_jetCont;
    
        std::pair< xAOD::JetContainer*, xAOD::ShallowAuxContainer* > m_shallowCopy;
    
        ToolHandle<IJetCalibrationTool> m_jetCalibTool;
        ToolHandle<ICPJetUncertaintiesTool> m_jesTool;
        ToolHandle<IJERSmearingTool> m_jerTool;
        ToolHandle<IBTaggingSelectionTool> m_btagSelTool_60;
        ToolHandle<IBTaggingSelectionTool> m_btagSelTool_70;
        ToolHandle<IBTaggingSelectionTool> m_btagSelTool_77;
        ToolHandle<IBTaggingSelectionTool> m_btagSelTool_85;
	    ToolHandle<CP::IJetJvtEfficiency> m_jetJVTEffTool;

        ToolHandle<IJetModifier> m_fJVTTool;
        ToolHandle<IJetUpdateJvt> m_jvtagup;

};

#endif


