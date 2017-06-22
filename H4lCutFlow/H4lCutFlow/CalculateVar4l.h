#ifndef CALCULATEVAR4L_H
#define CALCULATEVAR4L_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "TSystem.h"

// Root includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/OutputTree.h"
#include "HZZCutCommon/METCalc.h"

#include "H4lCutFlow/EnumDef4l.h"
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/TruthHelper.h"

// xAOD includes
#include "xAODBase/IParticle.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODJet/JetContainer.h"
#include "FourMomUtils/xAODP4Helpers.h"
#include "xAODTracking/VertexContainer.h"

// Tools include
#include "FsrUtils/IFsrPhotonTool.h"
#include "ZMassConstraint/IConstraintFit.h"
#include "H4lBDTWeights/IH4lBDTWeights.h"
#include "CategoriesMVA/ICategoriesMVA.h"

#include "ElectronPhotonFourMomentumCorrection/IEgammaCalibrationAndSmearingTool.h"
#include "MuonMomentumCorrections/IMuonCalibrationAndSmearingTool.h"
#include "HZZUtils/HelicityAngles.h"
#include "HZZUtils/IElectronMCClassification.h"
#include "HZZUtils/IElectronRecoClassification.h"
#include "MCTruthClassifier/IMCTruthClassifier.h"
#include "MCTruthClassifier/MCTruthClassifierDefs.h"
#include "AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h"
#include "GoodRunsLists/TGRLCollection.h"
#include "AsgAnalysisInterfaces/IPileupReweightingTool.h"
#include "TrigBunchCrossingTool/BunchCrossingToolBase.h"
#include "MCFM_MatrixElement/MatrixElementProvider.h"

// Probably not needed...
// ME includes
// SM ggF
#include "MadGraphME/CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem.h"
#include "MadGraphME/CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum.h"

// SM VBF
#include "MadGraphME/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemmupmumuux.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ud_epemepemud.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ud_epemmupmumud.h"
#include "MadGraphME/CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux.h"

#include "LHAPDF/LHAPDF.h"

#include "MadGraphME/ComputeMGME.h"



class CalculateVar4l
{
    public:
        CalculateVar4l(EventContainer* eventCont);
        virtual ~CalculateVar4l();
        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};

        // Setters
        void setHiggs (ParticleQuadlepton* higgs) {m_higgs = higgs;};
        void setSingleTrigger (CutEventTrigger* m_trig) {m_singleTrigger = m_trig;};
        void setFidJets   (const std::vector<ParticleVar*>& jetList) {m_fidJetList = jetList; m_isJetFidFilled = true;};
        void setJets  (const std::vector<ParticleVar*>& jetList) {m_jetList = jetList; m_isJetFilled = true;};
        void setElectron  (const std::vector<ParticleVar*>& elList) {m_elList = elList; m_isElFilled = true;};
        void setMuon  (const std::vector<ParticleVar*>& muList) {m_muList = muList; m_isMuFilled = true;};
        void setCalPhCont  (const xAOD::PhotonContainer* phCont) {m_phCont = phCont;};
        void setCalElCont  (const xAOD::ElectronContainer* elCont) {m_elCont = elCont;};
    
        void setMETClass(std::shared_ptr<METCalc> met){m_metCalc = met;};
    
        void fillMET(TString sysName = "");
        void fillTriggerVars();

        // To calculate
        void process ();

        // To clear var
        void clearVars();

        // For setting the candidate index
        void setCandIndex(int i = 0){m_candIndex = i;};

        // Is there an extra lepton for the given quad
        bool isExtraLepton() { return m_isExtraLep; };

    protected:
        EventContainer* m_eventCont;

        ParticleQuadlepton* m_higgs;
        CutEventTrigger* m_singleTrigger;

        OutputTree* m_outTree;
    
        std::vector<ParticleVar*> m_elList;
        std::vector<ParticleVar*> m_muList;
        std::vector<ParticleVar*> m_jetList;
        std::vector<ParticleVar*> m_fidJetList;
        Bool_t m_isElFilled;
        Bool_t m_isMuFilled;
        Bool_t m_isFSRFilled;
        Bool_t m_isJetFilled;
        Bool_t m_isJetFidFilled;
    
        const xAOD::ElectronContainer* m_elCont;
        const xAOD::PhotonContainer* m_phCont;
    
        std::shared_ptr<METCalc> m_metCalc;

        // Tools
        ToolHandle<FSR::IFsrPhotonTool> m_fsrTool;
        ToolHandle<IH4lBDTWeights> m_BDTtool;
        
        ToolHandle<ICategoriesMVA>             m_oneJet_jptetadR_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_VBFCatMVATool;
        ToolHandle<ICategoriesMVA>             m_VHnoPtHjjCatMVATool;
        ToolHandle<ICategoriesMVA>             m_VBF_TOPO_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_VBF_Rest_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_1J_pt4l_60_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_1J_pt4l_120_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_1J_pt4l_60_120_CatMVATool;
        ToolHandle<Trig::IBunchCrossingTool>   m_bunchCrossingTool;

        ToolHandle<ZMassConstraint::IConstraintFit> m_massConstraint;
        ToolHandle<CP::IEgammaCalibrationAndSmearingTool> m_energyRescaler;
    
        ToolHandle<IElectronMCClassification> m_electronMCClassifier;
        ToolHandle<IElectronRecoClassification> m_recoClassification;
        ToolHandle<IMCTruthClassifier> m_MCTruthClassifier;
        ToolHandle<IGoodRunsListSelectionTool> m_grl;
        ToolHandle<CP::IPileupReweightingTool> m_pileupTool;     
	ToolHandle<HSG2_MCFM::IMatrixElementProvider> m_matrixElementProvider;

        // For Cuts helper
        CutLepComb* m_cutQuad;
    
        // For truth Calculations
        TruthHelper* m_truthHelper;

        // helper vars
        void fillGeneralVars();
        void fillMassVars();
        void fillFSRVars();
        void fillZMCVars();
        ZMassConstraint::ConstraintFitInput getZMCInput(ParticleDilepton* diLep, Bool_t skipFSR = false);
    
        void fillLeptonVars();
        void fillBkgLeptonVars();
        void fillJetVars();
        void fillFidJetVars();
        Bool_t m_jetVarFilled; // For caching results;

        void fillMassBDTVars();
        void fillCategory();
        Bool_t isGoodExtraLepton(ParticleVar* lep);
        Bool_t deltaRMatch(const xAOD::TruthParticle* tp1, const xAOD::TruthParticle* tp2);
 
        void addFSRCandidate(FSR::FsrCandidate candidate, Int_t whichZ);
    
        ParticleVar* m_leadingJet;
        ParticleVar* m_subLeadingJet;

        void fillTruthMatched();
        void fillTruth();
        void fillTruthPairing();
     
        void fillAngularVar();
    
        void fillFileInfo();

        // For Simplified XS
        void fillSimpleXS();
    
        // For clean up
        std::vector<ParticleVar*>        m_partContainer;
        int m_candIndex;

        void fillVertexInfo();

        // EFT and cat analysis
        void fillCatBDT();

        float computeMinDeltaR(const std::vector<const xAOD::IParticle*>& leptons,
                              const std::vector<const xAOD::IParticle*>& jets) const;

        // SM ggF
        CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemepem*                       m_heft_pp_H_ZZ_4l_heft_gg_epemepem;
        CPPProcess_P0_Sigma_heft_pp_H_ZZ_4l_heft_gg_epemmupmum*                     m_heft_pp_H_ZZ_4l_heft_gg_epemmupmum;

        // SM VBF
        CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux*                       m_sm_hVBF_ZZ_4l_sm_ddx_epemepemuux;
        CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ddx_epemmupmumuux*                     m_sm_hVBF_ZZ_4l_sm_ddx_epemmupmumuux;
        CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ud_epemepemud*                         m_sm_hVBF_ZZ_4l_sm_ud_epemepemud;
        CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_ud_epemmupmumud*                       m_sm_hVBF_ZZ_4l_sm_ud_epemmupmumud;
        CPPProcess_P0_Sigma_sm_hVBF_ZZ_4l_sm_uux_epemepemuux*                       m_sm_hVBF_ZZ_4l_sm_uux_epemepemuux;

        LHAPDF::PDF* m_ct10PDF;
        
        void fillME();
        float fillMEVec(std::vector<float> ME); 

        // GRL
        void fillGRLDecision();
        
        // Truth jets for jetBin migration
        void fillTruthJets();

        // For sorting particlevar py bt
        static bool sortParticleVarPt (ParticleVar* i ,ParticleVar*j); 


        void fillCategoryfJVT();

	bool m_isExtraLep;   
 
};

#endif


