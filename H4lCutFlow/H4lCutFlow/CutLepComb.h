#ifndef CUTLEPCOMB_H
#define CUTLEPCOMB_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>

// Local includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"

#include "HZZCutCommon/LepCombBase.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/ParticleBase.h"
#include "HZZCutCommon/ParticleVar.h"
#include "H4lCutFlow/RemoveOverlap4l.h"
#include "H4lCutFlow/CutEventTrigger.h"
#include "H4lCutFlow/EnumDef4l.h"


// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"
#include "xAODTracking/TrackingPrimitives.h"
#include "xAODTracking/TrackParticlexAODHelpers.h"
#include "xAODTracking/VertexContainer.h"

// Tool includes
#include "IsolationSelection/IIsolationSelectionTool.h"
#include "IsolationSelection/IIsolationCloseByCorrectionTool.h"
#include "IsolationCorrections/IIsolationCorrectionTool.h"


class CutLepComb
{
    public:
        CutLepComb(EventContainer* eventcont);
        virtual ~CutLepComb();

        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};

        void setCutEventTrigger(CutEventTrigger * trig) {m_trigger = trig;};

        // CutValues
        Double_t m_pT1CutVal;
        Double_t m_pT2CutVal;
        Double_t m_pT3CutVal;
        Bool_t cutKinematic(const LepCombBase* currComb) const;

        Bool_t cutTrigMatch(const LepCombBase* currComb) const;

        // mZ1 cut
        Double_t m_mZ1LwrCutVal;
        Double_t m_mZ1UprCutVal;
        Bool_t cutMZ1(const ParticleQuadlepton* currQuad) const;

        // mZ2 cut
        Int_t m_nBinMZ2Cut;
        Double_t* m_massMZ2Cut;
        Double_t* m_cutMZ2Cut;
        Double_t m_mZ2UprCutVal;
        Bool_t cutMZ2(const ParticleQuadlepton* currQuad) const;

        // DeltaR
        Double_t m_SFdRCut;
        Double_t m_OFdRCut;
        Bool_t cutDeltaR(const LepCombBase* currComb) const;
        Bool_t cutDeltaR(const std::vector<ParticleVar*>& vecLep) const;

        // Jpsi veto
        Double_t m_JPsiVetoVal;
        Bool_t JPsiVeto(const ParticleQuadlepton* currQuad) const;
        Bool_t JPsiVeto(const std::vector<ParticleVar*>& vecLep) const;

        // Isolation
        Bool_t cutIsolation(const LepCombBase* currComb, bool preventDebug = false) const;
        Bool_t cutIsolation(const std::vector<ParticleVar*>& vecLep, bool preventDebug = false) const;

        // D0 sig
        Double_t m_muD0SigCut;
        Double_t m_elD0SigCut;
        Bool_t cutD0Sig(const LepCombBase* currComb, bool preventDebug = false) const;
        Bool_t cutD0Sig(const std::vector<ParticleVar*>& vecLep, bool preventDebug = false) const;


        void doTrigMatching() {m_doTriggerMatch = true;};  

        Double_t m_4mVrtCut;
        Double_t m_4e_2l2l_VrtCut;

        // Vertex cut
        double getVertexQuality(const ParticleQuadlepton* currQuad) const;      

        Bool_t cutVertex(const ParticleQuadlepton* currQuad) const;

    protected:
        Bool_t m_doTriggerMatch;

        EventContainer* m_eventCont;

        ToolHandle<CP::IIsolationSelectionTool> m_isoTool;
        ToolHandle<CP::IIsolationCloseByCorrectionTool> m_isoSelMu;
        ToolHandle<CP::IIsolationCloseByCorrectionTool> m_isoSelEl;
        ToolHandle<CP::IIsolationCorrectionTool> m_isoCorrTool;

        CutEventTrigger* m_trigger;

        Bool_t matchSingleMu(const LepCombBase* currComb) const;
        Bool_t matchDiMu(const LepCombBase* currComb) const;
        Bool_t matchTriMu(const LepCombBase* currComb) const;
        Bool_t matchSingleEl(const LepCombBase* currComb) const;
        Bool_t matchDiEl(const LepCombBase* currComb) const;
        Bool_t matchTriEl(const LepCombBase* currComb) const;
        Bool_t matchElMu(const LepCombBase* currComb) const;

        std::vector<xAOD::Iso::IsolationType> m_isotypes;
        std::vector<std::string> m_isotypesString;
        void decorateCorrectIso(const std::vector<ParticleVar*>& vecLep) const ;


};

#endif


