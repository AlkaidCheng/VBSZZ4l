#ifndef CALCULATEVAR3L_H
#define CALCULATEVAR3L_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <vector>

// Root includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/ParticleMulti.h"
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
#include "xAODMissingET/MissingETContainer.h"
#include "xAODTracking/VertexContainer.h"

// Tools include
#include "FsrUtils/IFsrPhotonTool.h"
#include "ZMassConstraint/IConstraintFit.h"
#include "H4lBDTWeights/IH4lBDTWeights.h"

#include "ElectronPhotonFourMomentumCorrection/IEgammaCalibrationAndSmearingTool.h"
#include "MuonMomentumCorrections/IMuonCalibrationAndSmearingTool.h"
#include "HZZUtils/HelicityAngles.h"
#include "HZZUtils/IElectronMCClassification.h"
#include "HZZUtils/IElectronRecoClassification.h"
#include "MCTruthClassifier/IMCTruthClassifier.h"
#include "MCTruthClassifier/MCTruthClassifierDefs.h"
#include "AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h"
#include "GoodRunsLists/TGRLCollection.h"

class CalculateVar3l
{
    public:
        CalculateVar3l(EventContainer* eventCont);
        virtual ~CalculateVar3l();
        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};

        // Setters
        void setZplusL (ParticleMulti* ZplusL) {m_ZplusL = ZplusL;};
        void setFidJets   (const std::vector<ParticleVar*>& jetList) {m_fidJetList = jetList; m_isJetFidFilled = true;};
        void setJets  (const std::vector<ParticleVar*>& jetList) {m_jetList = jetList; m_isJetFilled = true;};
        void setElectron  (const std::vector<ParticleVar*>& elList) {m_elList = elList; m_isElFilled = true;};
        void setMuon  (const std::vector<ParticleVar*>& muList) {m_muList = muList; m_isMuFilled = true;};
        void setCalPhCont  (const xAOD::PhotonContainer* phCont) {m_phCont = phCont;};
        void setCalElCont  (const xAOD::ElectronContainer* elCont) {m_elCont = elCont;};

        void setMETClass(std::shared_ptr<METCalc> met){m_metCalc = met;};

        // To calculate
        void process ();

        // To clear var
        void clearVars();
    
        // For setting the candidate index
        void setCandIndex(int i = 0){m_candIndex = i;};

    protected:
        EventContainer* m_eventCont;

        ParticleMulti* m_ZplusL;

        OutputTree* m_outTree;
    
        std::vector<ParticleVar*> m_elList;
        std::vector<ParticleVar*> m_muList;
        std::vector<ParticleVar*> m_jetList;
        std::vector<ParticleVar*> m_fidJetList;
        Bool_t m_isElFilled;
        Bool_t m_isMuFilled;
        Bool_t m_isJetFilled;
        Bool_t m_isJetFidFilled;
    
        const xAOD::ElectronContainer* m_elCont;
        const xAOD::PhotonContainer* m_phCont;
        std::shared_ptr<METCalc> m_metCalc;

        // Tools
        ToolHandle<FSR::IFsrPhotonTool> m_fsrTool;
        ToolHandle<IH4lBDTWeights> m_BDTtool;
        ToolHandle<ZMassConstraint::IConstraintFit> m_massConstraint;
        ToolHandle<CP::IEgammaCalibrationAndSmearingTool> m_energyRescaler;
    
        ToolHandle<IElectronMCClassification> m_electronMCClassifier;
        ToolHandle<IElectronRecoClassification> m_recoClassification;
        ToolHandle<IMCTruthClassifier> m_MCTruthClassifier;
        ToolHandle<IGoodRunsListSelectionTool> m_grl;

        // For Cuts helper
        CutLepComb* m_cutQuad;
    
        // For truth Calculations
        TruthHelper* m_truthHelper;

        // helper vars
        void fillGeneralVars();
        void fillMassVars();
        void fillFSRVars();
        void addFSRCandidate(FSR::FsrCandidate candidate);

        void fillZMCVars();
        ZMassConstraint::ConstraintFitInput getZMCInput(ParticleDilepton* diLep, Bool_t skipFSR = false);
    
        void fillLeptonVars();
        void fillJetVars();
        //void fillFidJetVars();
        Bool_t m_jetVarFilled; // For caching results;

        //void fillMassBDTVars();
        //void fillCategory();
        //Bool_t isGoodExtraLepton(ParticleVar* lep);
    
    
        ParticleVar* m_leadingJet;
        ParticleVar* m_subLeadingJet;

        //void fillTruthMatched();
        //void fillTruth();
        void fillMET();
        //void fillAngularVar();
    
        void fill3lVar();
    
        // For clean up
        std::vector<ParticleVar*>        m_partContainer;


        int m_candIndex;

        void fillGRLDecision();

        // For sorting particlevar py bt
        static bool sortParticleVarPt (ParticleVar* i ,ParticleVar*j);


    
};

#endif


