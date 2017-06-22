#ifndef CUTFLOW4l_H
#define CUTFLOW4l_H

// Local includes
#include "H4lCutFlow/CutLepComb.h"
#include "H4lCutFlow/ApplyWeight4l.h"
#include "HZZCutCommon/CutFlowBase.h"
#include "H4lCutFlow/CutEventTrigger.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"

class CutFlow4l : public CutFlowBase
{
public:
    CutFlow4l(EventContainer* eventcont, ApplyWeight4l* applyWeight);
    ~CutFlow4l();
    
    virtual void process();
    void clearVars();
    
    // to initialize the cutflow, every class inheriting should implement with it own version
    virtual void initCutFlow();
    
    void printCutFlow();
    
    // Get the last cut that was passed
    cutFlow::cutFlow getLastCutPassed()  const{return m_lastCutPassed;};
    // To control what is the last cut that should be applied
    void setLastCut(cutFlow::cutFlow mCut)  {m_setLastCut = mCut;};
    
    //ParticleQuadlepton* getHiggsCandidate()  const {return m_higgs;};
    std::vector<ParticleQuadlepton*> getHiggsVec(){return m_quadList;};
    int getHiggsCandNum(){return m_quadList.size();};
    
    
    // To limit the quad type that will be allowed
    virtual void setQuadAnalysisType(Int_t quadType);
    
    void setCutEventTrigger(CutEventTrigger * trig) {m_cutQuad->setCutEventTrigger(trig);};
    
    void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1);
    void updateCategory(Int_t currCat, Int_t valToAdd = 1);
    
    std::vector<ParticleQuadlepton*> getHiggsList() {return m_quadInitList;};
    
    std::vector<ParticleQuadlepton*> getAllHiggsList() {return m_quadInitList;};
    
protected:
    // For storing Categories
    std::vector<TString> m_catergoryName;
    std::map<CP::SystematicSet, std::vector<Int_t>> m_rawCatNumber;
    std::map<CP::SystematicSet, std::vector<Float_t>> m_weightCatNumber;
    
    // To get weight for cutflow
    ApplyWeight4l* m_applyWeight;
    
    // For Cuts helper
    CutLepComb* m_cutQuad;
    
    // Last Cut passed
    cutFlow::cutFlow m_lastCutPassed;
    
    // Set the last cut to check
    cutFlow::cutFlow m_setLastCut;
    
    // For limiting the flavour of Quad
    QuadleptonType::QuadleptonType m_limitQuadType;
    
    // Candidate quadlepton
    ParticleQuadlepton* m_higgs;
    
    // For setting the right analysis type
    QuadAnalType::QuadAnalType m_currQuadAnalType;
    
    // lepton container
    std::vector<ParticleVar*> m_lepList;
    
    std::vector<ParticleDilepton*> m_dilepInitList;
    std::vector<ParticleDilepton*> m_dilepList;
    
    std::vector<ParticleQuadlepton*> m_quadInitList;
    std::vector<ParticleQuadlepton*> m_quadList;
    
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
    Bool_t cutMuonType(LepCombBase* currQuad);
    
    virtual void cutKinematic();
    virtual void cutTrigMatch();
    
    virtual void pickQuadEvent();
    
    virtual void performHiggsCuts();
    
    virtual void cutMZ1();
    virtual void cutMZ2();
    virtual void cutDeltaRJpsi();
    virtual void calcIsoD0();
    virtual void cutIsolation();
    virtual void cutD0();
    
    
    static bool sortmZ1mZ2 (ParticleQuadlepton* i ,ParticleQuadlepton*j);


};

#endif


