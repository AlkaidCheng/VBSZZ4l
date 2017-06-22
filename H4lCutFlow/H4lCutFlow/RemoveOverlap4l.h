#ifndef REMOVEOVERLAP4l_H
#define REMOVEOVERLAP4l_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>

// Root Include
#include <TMath.h>

// Local includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/LepCombBase.h"
#include "H4lCutFlow/EnumDef4l.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"
#include "xAODEgamma/EgammaxAODHelpers.h"
#include "xAODJet/Jet.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODJet/JetContainer.h"

// Tool includes
#include "AssociationUtils/IOverlapRemovalTool.h"
#include "AsgTools/AnaToolHandle.h"


class RemoveOverlap4l
{
    public:
        RemoveOverlap4l(EventContainer* eventcont);
        virtual ~RemoveOverlap4l();
    
        // Mainly to setup anything depedant on systematics
        virtual void initialize();

        void initCutFlow();
        void printCutFlow();
        void updateCutFlow(Int_t valToAdd, Int_t cutLevel, std::map<CP::SystematicSet, std::vector<Int_t>>& m_rawCutFlow);
        
        

        void process();
        void clearVars();

        std::vector<ParticleVar*>  getMuons()     {return m_mu_final;};
        std::vector<ParticleVar*>  getElectrons() {return m_el_all_final;};
        std::vector<ParticleVar*>  getLooseElectrons() {return m_el_L_final;};
        std::vector<ParticleVar*>  getVLooseElectrons() {return m_el_VL_final;};
        std::vector<ParticleVar*>  getJets()      {return m_jet_final;};
    
    
        std::vector<ParticleVar*>  getMETMuons()     {return m_mu_MET;};
        std::vector<ParticleVar*>  getMETElectrons() {return m_el_MET;};

        void setMuons    (const std::vector<ParticleVar*>& currList) {m_mu_init = currList;};
        void setElectrons(const std::vector<ParticleVar*>& currList) {m_el_init = currList;};
        void setJets     (const std::vector<ParticleVar*>& currList) {m_jet_init = currList;};

        static Double_t DeltaR (Double_t eta_1, Double_t phi_1, Double_t eta_2, Double_t phi_2);
    
        // X-jet overlap
        static std::vector<ParticleVar*> xJetOverlap(LepCombBase* combLep, const std::vector<ParticleVar*>& jetVect);



        static Bool_t elTrackOlp(ParticleVar* el1, ParticleVar* el2);
        static Bool_t elClusOlp(ParticleVar* el1, ParticleVar* el2);
    
    protected:
        EventContainer* m_eventCont;

        std::vector<ParticleVar*> m_mu_init;
        std::vector<ParticleVar*> m_el_init;
        std::vector<ParticleVar*> m_jet_init;

        std::vector<ParticleVar*> m_mu_list;
        std::vector<ParticleVar*> m_el_list;
        std::vector<ParticleVar*> m_jet_list;
    
        std::vector<ParticleVar*> m_mu_final;
        std::vector<ParticleVar*> m_el_all_final;
        std::vector<ParticleVar*> m_el_L_final;
        std::vector<ParticleVar*> m_el_VL_final;
        std::vector<ParticleVar*> m_jet_final;
    
        // To seperate the loose and very loose muons
        std::vector<ParticleVar*> m_el_loose;
        std::vector<ParticleVar*> m_el_veryloose;
    
    
        // For MET calculations
        std::vector<ParticleVar*> m_mu_MET;
        std::vector<ParticleVar*> m_el_MET;


        std::vector<ParticleVar*> m_af_elelOlp;  // After internal elel overlap


    
        void splitElID();

        void removeElElOverlap();
	    void removeMuJetOverlap();
        Bool_t checkEETrOlp(ParticleVar* currElectron, std::vector<ParticleVar*>& inList);
        Bool_t checkEEClOlp(ParticleVar* currElectron, std::vector<ParticleVar*>& inList);
    
        void removesASGCaloElOverlap();
        std::vector<ParticleVar*> m_mu_ASGCaloEl; // all Electron after overlap
        Bool_t checkCaloMuElOlpASG(ParticleVar* currMuon, std::vector<ParticleVar*>& inList);

    
        void asgOverlap();
        void fillFinalVector(std::vector<ParticleVar*>& inList, std::vector<ParticleVar*>& outList);
        void fillVector(std::vector<ParticleVar*>& inList, std::vector<ParticleVar*>& outList);
        xAOD::MuonContainer* m_muList;
        xAOD::ElectronContainer* m_elList;
        xAOD::JetContainer* m_jetList;

    
        asg::AnaToolHandle<ORUtils::IOverlapRemovalTool> m_orTool;


        // For cutflow
        TString m_cutFlowName;
        std::vector<TString> m_cutName;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawMuCutFlow;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawElCutFlow;
        std::map<CP::SystematicSet, std::vector<Int_t>> m_rawJetCutFlow;
    
    

    

};

#endif


