#ifndef CALCULATEVAR4LINCLUSIVE_H
#define CALCULATEVAR4LINCLUSIVE_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

// Root includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/OutputTree.h"

#include "H4lCutFlow/EnumDef4l.h"
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/TruthHelper.h"

// xAOD includes
#include "xAODBase/IParticle.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODJet/JetContainer.h"
#include "FourMomUtils/xAODP4Helpers.h"
#include "xAODTracking/VertexContainer.h"

// Tools include
#include "FsrUtils/IFsrPhotonTool.h"
#include "ZMassConstraint/IConstraintFit.h"
#include "H4lBDTWeights/IH4lBDTWeights.h"
#include "CategoriesMVA/CategoriesMVA.h"

#include "ElectronPhotonFourMomentumCorrection/IEgammaCalibrationAndSmearingTool.h"
#include "MuonMomentumCorrections/IMuonCalibrationAndSmearingTool.h"
#include "HZZUtils/HelicityAngles.h"
#include "HZZUtils/IElectronMCClassification.h"
#include "HZZUtils/IElectronRecoClassification.h"
#include "MCTruthClassifier/IMCTruthClassifier.h"
#include "MCTruthClassifier/MCTruthClassifierDefs.h"
#include "AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h"
#include "GoodRunsLists/TGRLCollection.h"




class CalculateVar4lInclusive
{
    public:
        CalculateVar4lInclusive(EventContainer* eventCont);
        virtual ~CalculateVar4lInclusive();
        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};

        // Setters
        void setHiggs (ParticleQuadlepton* higgs) {m_higgs = higgs;};
        void setHiggsFiducial (ParticleQuadlepton* higgs_fid) {m_higgs_fid = higgs_fid;};
        void setJets  (const std::vector<ParticleVar*>& jetList) {m_jetList = jetList; m_isJetFilled = true;};
        //void setWZJets  (const std::vector<ParticleVar*>& WZjetList) {m_WZjetList = WZjetList; m_isWZJetFilled = true;};
        void setElectron  (const std::vector<ParticleVar*>& elList) {m_elList = elList; m_isElFilled = true;};
        void setMuon  (const std::vector<ParticleVar*>& muList) {m_muList = muList; m_isMuFilled = true;};
        void setCalPhCont  (const xAOD::PhotonContainer* phCont) {m_phCont = phCont;};
        void setCalElCont  (const xAOD::ElectronContainer* elCont) {m_elCont = elCont;};

        static bool sortParticleVarPt (ParticleVar* i ,ParticleVar*j);

        // To calculate
        void process (Bool_t passFidCut);

        // To clear var
        void clearVars();

        //putters and setters
        void setLeptonType(std::string leptonType);


    protected:
        EventContainer* m_eventCont;

        ParticleQuadlepton* m_higgs;
        ParticleQuadlepton* m_higgs_fid;

        OutputTree* m_outTree;
    
        std::vector<ParticleVar*> m_elList;
        std::vector<ParticleVar*> m_muList;
        std::vector<ParticleVar*> m_jetList;
        Bool_t m_isElFilled;
        Bool_t m_isMuFilled;
        Bool_t m_isJetFilled;

        Bool_t m_passFidCut;
        std::string m_leptonType;
    
        const xAOD::ElectronContainer* m_elCont;
        const xAOD::PhotonContainer* m_phCont;

        // Tools
        ToolHandle<IMCTruthClassifier> m_MCTruthClassifier;
        ToolHandle<IGoodRunsListSelectionTool> m_grl;
        //for coupling
        ToolHandle<IH4lBDTWeights>             m_BDTtool;
        ToolHandle<ICategoriesMVA>             m_oneJet_jptetadR_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_VBFCatMVATool;
        ToolHandle<ICategoriesMVA>             m_VHnoPtHjjCatMVATool;
        ToolHandle<ICategoriesMVA>             m_VBF_TOPO_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_VBF_Rest_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_1J_pt4l_60_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_1J_pt4l_120_CatMVATool;
        ToolHandle<ICategoriesMVA>             m_1J_pt4l_60_120_CatMVATool;


        // For Cuts helper
        CutLepComb* m_cutQuad;
    
        // For truth Calculations
        TruthHelper* m_truthHelper;

        // helper vars
        void fillGeneralVars();
        void fillMassVars();
    
        void fillLeptonVars();
        void fillJetVars();
        //void fillWZJetVars();
        void fillAngularVar();
        Bool_t m_jetVarFilled; // For caching results;
        //Bool_t m_WZjetVarFilled; // For caching results;

        void fillMassBDTVars();
        void fillCategory();
        void fillPtHRESReweight();
        Bool_t isGoodExtraLepton(ParticleVar* lep);

    
        ParticleVar* m_leadingJet;
        ParticleVar* m_subLeadingJet;
        //ParticleVar* m_leadingWZJet;
        //ParticleVar* m_subLeadingWZJet;

        void fillFiducial();
        void fillSimpleXS();
        // EFT and cat analysis
        void fillCatBDT();



        void fillME();
        float fillMEVec(std::vector<float> ME);



        // For clean up
        std::vector<ParticleVar*>        m_partContainer;

    
};

#endif


