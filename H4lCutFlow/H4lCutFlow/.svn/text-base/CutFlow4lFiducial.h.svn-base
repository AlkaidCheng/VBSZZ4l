#ifndef CUTFLOW4lFIDUCIAL_H
#define CUTFLOW4lFIDUCIAL_H

// Local includes
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/ApplyWeight4l.h"
#include "HZZCutCommon/CutFlowBase.h"
#include "H4lCutFlow/CutEventTrigger.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"



class CutFlow4lFiducial : public CutFlowBase
{
    public:
        CutFlow4lFiducial(EventContainer* eventcont, ApplyWeight4l* applyWeight);
        ~CutFlow4lFiducial();
    
        virtual void process();
        void clearVars();

        // to initialize the cutflow, every class inheriting should implement with it own version
        void initCutFlow();
    
        void printCutFlow();

        cutFlow::cutFlow getLastCutPassed()  const{return m_lastCutPassed;};
        ParticleQuadlepton* getHiggsCandidate()  const {return m_higgs;};
        void setHiggsCandidate(ParticleQuadlepton* higgs)  {m_higgs = higgs;};
        void disableMassWindowCut() {m_doMassWindowCut = false;};
        void enableMassWindowCut() {m_doMassWindowCut = true;};

        // To limit the quad type that will be allowed
        virtual void setQuadAnalysisType(Int_t quadType);
    
        void setCutEventTrigger(CutEventTrigger * trig) {m_cutQuad->setCutEventTrigger(trig);};

        void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1);
        void updateCategory(Int_t currCat, Int_t valToAdd = 1);
    
        std::vector<ParticleQuadlepton*> getHiggsList() {return m_quadList_trigCut;};
    
        std::vector<ParticleQuadlepton*> getAllHiggsList() {return m_quadInitList;};

    protected:
        // For storing Categories
        std::vector<TString> m_catergoryName;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawCatNumber;
        std::map<CP::SystematicSet, std::vector<Float_t>> m_weightCatNumber;
    
        // do mass window cut for low mass analysis
        Bool_t m_doMassWindowCut;
        // To get weight for cutflow
        ApplyWeight4l* m_applyWeight;

        // For Cuts helper
        CutLepComb* m_cutQuad;

        // Last Cut passed
        cutFlow::cutFlow m_lastCutPassed;

        // For limiting the flavour of Quad
        QuadleptonType::QuadleptonType m_limitQuadType;

        // Candidate quadlepton
        ParticleQuadlepton* m_higgs;

        // lepton container
        std::vector<ParticleVar*> m_lepList;

        std::vector<ParticleDilepton*> m_dilepInitList;
        std::vector<ParticleDilepton*> m_dilepList;
        
        std::vector<ParticleQuadlepton*> m_quadInitList;
        std::vector<ParticleQuadlepton*> m_quadList;
        std::vector<ParticleQuadlepton*> m_quadList_kinCut;
        std::vector<ParticleQuadlepton*> m_quadList_trigCut;

        // Helper functions for cutFlow - cutting
        Bool_t cutNumLep();

        // General Helpers
        void createLepList();

        void getDilepComb();
        virtual Bool_t cutDilepCharge(ParticleDilepton* currDilep);
        virtual Bool_t cutDilepType(ParticleDilepton* currDilep);
        
        void getQuadComb();
        virtual Bool_t cutQuadCharge(ParticleQuadlepton* currQuad);
        virtual Bool_t cutQuadType(ParticleQuadlepton* currQuad);
        Bool_t cutQuadMuonType(ParticleQuadlepton* currQuad);

        virtual void cutKinematic();
        virtual void cutTrigMatch();

        virtual void pickQuadEvent();
    
        virtual void performHiggsCuts();
    
};

#endif


