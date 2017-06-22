#ifndef APPLYWEIGHT4l_H
#define APPLYWEIGHT4l_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <map>
#include <regex>

// Local includes
#include "HZZCutCommon/LepCombBase.h"
#include "HZZCutCommon/ApplyWeight.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "H4lCutFlow/EnumDef4l.h"
#include "H4lCutFlow/TruthHelper.h"
#include "HZZUtils/OverlapRemoval.h"
#include "H4lCutFlow/CutEventTrigger.h"

// Tool includes
#include "ElectronEfficiencyCorrection/IAsgElectronEfficiencyCorrectionTool.h"
#include "MuonEfficiencyCorrections/IMuonEfficiencyScaleFactors.h"

#include "HZZUtils/INLOreweighting.h"
#include "PATInterfaces/IWeightTool.h"

#include "JetJvtEfficiency/IJetJvtEfficiency.h"

#include "xAODBTaggingEfficiency/IBTaggingEfficiencyTool.h"
#include "TruthWeightTools/HiggsWeightTool.h"

class ApplyWeight4l : public ApplyWeight
{
    public:
        ApplyWeight4l(EventContainer* eventcont);
        ~ApplyWeight4l();
    
        void initialize() {};
    
        Double_t getEventWeight();
        Double_t getHiggsWeight(const LepCombBase* combLep);
        Double_t getTotalWeight(const LepCombBase* combLep);

        // To set the input jets
        void setJets  (const std::vector<ParticleVar*>& jetList) {m_jetList = jetList; m_isJetFilled = true;};
        void setFailJVTJets  (const std::vector<const ParticleVar*>& jetList) {m_jetListFailJVT = jetList;};
        
        /// Branching ratio weight
        Double_t getBranchingRatio(const LepCombBase* combLep) const;
    
        /// Sample overlap
        Double_t getSampleOlpWeight() const;

        void setCutEventTrigger(CutEventTrigger * trig) {m_trigger = trig;};

        /// Trigger SF
        Double_t getTriggerSF(const LepCombBase* combLep);
    
        /// To Fill the output to the TTree
        void fillWeight(const LepCombBase* combLep);
    
        /// Scale/PDF variation weight
        void fillTheoryVariationWeight() ;
        void fillVariationHist() ;

        /// Returns the total efficiency weight either the dilepton or quadlepton class
        Double_t getLepEff(const LepCombBase* combLep);
        void fillLepEff(const LepCombBase* combLep);
    
        /// Calculate weight_corr
        Double_t getWeightCorr(const LepCombBase* combLep);
    
        /// Calculate weight_lumi
        Double_t getWeightLumi(const LepCombBase* combLep);

        /// Calculate the total weight
        Double_t getWeight(const LepCombBase* combLep);
        
    
        /// for filling the systematic variations for weights in the norm weight tree
        void fillWeightSys(const LepCombBase* combLep, CP::SystematicSet sys);
    
        void clearVars();
    
        // EW correction
        double getEWCorr();
        double getEWNLOCorr();
        double getEWQCDCorr();

        // Sherpa correction
        double getSherpaCorr();
	    double getSherpaReweight();

        // Jet JVT SF
        double getJetJVTSF();

        // btag SF
        double getBtagSF();


    protected:
        TruthHelper* m_truthHelper;
    
        // Helper for retrieving trigSF
        xAOD::MuonContainer* myMuons;
    
        ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_egSFClassID;
        ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_egSFClassReco;
        ToolHandle<IAsgElectronEfficiencyCorrectionTool> m_egSFClassIso;
        ToolHandle<CP::IMuonEfficiencyScaleFactors> m_effTool;
        ToolHandle<CP::IMuonEfficiencyScaleFactors> m_effIsoTool;
        ToolHandle<CP::IMuonEfficiencyScaleFactors> m_effd0Tool;
        ToolHandle<INLOreweighting> m_NLOreweighting;
        ToolHandle<IWeightTool> m_pmgSherpaWeightTool;
        ToolHandle<CP::IJetJvtEfficiency> m_jetJVTEffTool;
        ToolHandle<CP::IJetJvtEfficiency> m_jetFJVTEffTool;

        ToolHandle<IBTaggingEfficiencyTool> m_btagEffTool;

        xAOD::HiggsWeightTool *m_higgsMCtool;
        
        std::vector<ParticleVar*> m_jetList;
        std::vector<const ParticleVar*> m_jetListFailJVT;
        Bool_t m_isJetFilled;
        
    
        CutEventTrigger* m_trigger;
        xAOD::IParticleContainer* m_jetCont;




};

#endif




