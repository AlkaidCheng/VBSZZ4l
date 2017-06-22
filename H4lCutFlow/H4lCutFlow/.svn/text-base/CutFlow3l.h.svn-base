#ifndef CUTFLOW3l_H
#define CUTFLOW3l_H

// Local includes
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/ApplyWeight4l.h"
#include "H4lCutFlow/CutEventTrigger.h"

#include "HZZCutCommon/CutFlowBase.h"
#include "HZZCutCommon/ParticleDilepton.h"
#include "HZZCutCommon/ParticleMulti.h"
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/METCalc.h"
#include "H4lCutFlow/CutFlow4l.h"
#include "xAODMissingET/MissingETContainer.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"

// Enum to control the cutflow
namespace ZlCutFlowType
{
    enum ZlCutFlowType
    {
        NA,
        ZplusMu,
        ZplusX,
    };
    
}

class CutFlow3l : public CutFlowBase
{
    public:
        CutFlow3l(EventContainer* eventcont, ApplyWeight4l* applyWeight);
        ~CutFlow3l();
    
        void process();
        void initialize();
    
        void clearVars();

        // to initialize the cutflow, every class inheriting should implement with it own version
        void initCutFlow();
        void printCutFlow();

        cutFlowZl::cutFlowZl getLastCutPassed()  const{return m_lastCutPassed;};
    
        /// To set what type of llee cutflow to do
        void cutFlowType(Int_t cutflowType);
    
        void setCutEventTrigger(CutEventTrigger * trig) {m_cutLepComb->setCutEventTrigger(trig);};

        void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1);
        void updateCategory(Int_t currCat, Int_t valToAdd = 1);
    
        std::vector<ParticleMulti*> getZlCand() {return m_candList;};
    
        void setMETClass(std::shared_ptr<METCalc> met){m_metCalc = met;};
    
    protected:
        // Process Zmu and Zx cutflow differently
        void processZmu();
        void processZel();
    
        // For storing Categories
        std::vector<TString> m_catergoryName;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawCatNumber;
        std::map<CP::SystematicSet, std::vector<Float_t>> m_weightCatNumber;
    
        // To get weight for cutflow
        ApplyWeight4l* m_applyWeight;

        // For Cuts helper
        CutLepComb* m_cutLepComb;
    
        // To keep a track of which cutflow to do
        ZlCutFlowType::ZlCutFlowType m_cutflowType;
    
        // Keep track of the last cut passed
        cutFlowZl::cutFlowZl m_lastCutPassed;

        // lepton container
        std::vector<ParticleVar*> m_lepList;
    
        // Dilep container
        std::vector<ParticleDilepton*> m_dilepInitList;
        std::vector<ParticleDilepton*> m_dilepList;
    
        ParticleDilepton* m_ZPart;
    
        // Particle mutli List
        std::vector<ParticleMulti*> m_candList;
    
        std::shared_ptr<METCalc> m_metCalc;
    
        // Helpers
        void createLepList();
    
        // Dilep creator
        void getDilepComb();
        Bool_t cutDilepCharge(ParticleDilepton* currDilep);
        Bool_t cutDilepType(ParticleDilepton* currDilep);
        Bool_t cutDilepID(ParticleDilepton* currDilep);
    
        void cutKinematic();
        void cutTrigMatch();
        void pickDilep();
 
        std::vector<ParticleMulti*> create3lCand(ParticleDilepton* ZPart, std::vector<ParticleVar*>& partList);
        std::vector<ParticleMulti*> m_3lInitList;
    
        // To cut on SA and Calo muon #
        Bool_t cutMuonType(LepCombBase* currComb);
    
        // Apply the JPsi and delta R cut
        void clean3lList(std::vector<ParticleMulti*>& m_3lInitList, Bool_t doJpsiCut);
    
        // For calculating the MET
        void processMET();
    
        // Apply all cut is leading Z is ee
        bool cutZeeElCut();

        // Apply isolation and d0 cut to leading Z
        void cutZIsoD0(std::vector<ParticleMulti*>& m_3lList);    
};

#endif


