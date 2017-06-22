#ifndef ANALYSISBKG_H
#define ANALYSISBKG_H

// C++ include
#include <vector> 
#include <algorithm>

// Base class include
#include "HZZCutCommon/AnalysisBase.h"

// Local include
#include "H4lCutFlow/EnumDef4l.h"

#include "H4lCutFlow/CutEventDataPreSel.h"
#include "H4lCutFlow/CutEventPreSel.h"
#include "H4lCutFlow/CutEventTrigger.h"

#include "H4lCutFlow/CutParticleMuon.h"
#include "H4lCutFlow/CutParticleElectron.h"
#include "H4lCutFlow/CutParticleJet.h"

#include "H4lCutFlow/RemoveOverlap4l.h"
#include "H4lCutFlow/ApplyWeight4l.h"

#include "H4lCutFlow/OutputTreeBkg.h"
#include "H4lCutFlow/OutputTree3l.h"
#include "HZZCutCommon/OutputTree.h"

#include "H4lCutFlow/CutFlowBkg.h"
#include "H4lCutFlow/CutFlowllmumu.h"
#include "H4lCutFlow/CutFlowllee.h"
#include "H4lCutFlow/CutFlow3l.h"


#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/ParticleMulti.h"
#include "H4lCutFlow/CalculateVar4l.h"
#include "H4lCutFlow/CalculateVar3l.h"
#include "H4lCutFlow/TruthHelper.h"
#include "H4lCutFlow/ToolInit4l.h"
#include "HZZCutCommon/METCalc.h"

// xAOD includes
#include "xAODMetaData/FileMetaData.h"


class Analysisbkg : public AnalysisBase
{
    public:
        Analysisbkg();
        virtual ~Analysisbkg();
    
        /// To print any cutflow or information after the
        /// processing of all events
        /// Called from the steering script
        void printCutFlow();


    protected:
        // Vector that stores the outtree for each type of variation in a given event
        // Expected to be implemented and filled by the dervied class
        std::map<CP::SystematicSet, OutputTree*> m_outTree3lMap;
    
    
        // Variables
        CutEventDataPreSel* m_dataPreSel;
        CutEventPreSel* m_preSel;
        CutEventTrigger* m_trigger;
        CutEventTrigger* m_triggerllee;

        CutParticleMuon* m_cutMuon;
        CutParticleElectron* m_cutElectronLoose;
        CutParticleElectron* m_cutElectron;
        CutParticleJet* m_cutJet;

        RemoveOverlap4l* m_removeOverlap;
        RemoveOverlap4l* m_removeOverlapLoose;
    
        CutFlowBkg* m_cutFlowRelaxIsoD04mu;
        CutFlowBkg* m_cutFlowRelaxIsoD02e2mu;
        CutFlowBkg* m_cutFlowRelaxIsoD02mu2e;
        CutFlowBkg* m_cutFlowRelaxIsoD04e;
        CutFlowBkg* m_cutFlowSS4mu;
        CutFlowBkg* m_cutFlowSS2e2mu;
        CutFlowBkg* m_cutFlowSS2mu2e;
        CutFlowBkg* m_cutFlowSS4e;
    
        CutFlowllmumu* m_cutFlowemu;
        
        CutFlowllee* m_3lxCR4e;
        CutFlowllee* m_3lxCR2mu2e;
    
        CutFlow3l* m_ZplusEl;
        CutFlow3l* m_ZplusMu;
  
        std::shared_ptr<METCalc> m_METCalc;

    
        std::vector<CutFlowllmumu*> m_llmumuCutFlows;
        std::vector<CutFlowBkg*> m_bkgCutFlows;
        std::vector<CutFlowllee*> m_lleeCutFlows;
        std::vector<CutFlow3l*> m_3lCutFlows;


        ApplyWeight4l* m_applyWeight;
    
        CalculateVar4l* m_calculateVar;
        CalculateVar3l* m_calculateVar3l;
    
        TruthHelper* m_truthHelper;
    
        // Candidate Higgs
        ParticleQuadlepton* m_higgs;
    
        // Tool store
        ToolInit4l* tool4l;
        // For Acceptance challenge
        // This is used to control were the trigger decision is applied
        Bool_t m_forAcceptanceChallenge;
    
        // functions
        /// Intialization of all the local classes need for the analysis
        /// Called in the process function
        void initialize();

        /// Called at the beginning of the processevent function
        /// Clears any memory or vectors that are specific for a given event
        void clearVars();

        /// Event preselection cuts are implemented here
        /// Expected cuts: dataPreselection, selection and trigger cuts
        Bool_t eventPreSelection();

        /// Selection for physics objects is implemented here
        /// Expected cuts: electron, muons, jets, and photons level cuts
        /// Overlap removal here as well
        void selectPhyObjects();
    
        /// Main event selection is implemented here
        Bool_t eventSelection();

        /// Calculation of final variables for the event
        /// Stored directly in container in outputtree class
        void calcVars();
    
        /// Called at the end of the event loop
        /// saves the output of the tree
        void finalize();
    
        /// To update any cutflow for associated class
        void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1);
        
        /// To copy any cutflow numbers to the output histrograms        
        void updateHistCutFlow();
    
        /// Store the number of events processed
        void updateEvtsProc();
    
    
        /// Just a helper to reduce the copying and pasting
        /// Used for calculating the var
        void calcVarHelper();
        void calcVarHelperSiEl();
    
        /// Helper to setup and run the met Calculations
        void setupMETClass();


        /// Used for custom sort a list of quads
        static bool sortmZ2 (ParticleQuadlepton* i ,ParticleQuadlepton*j);
        static bool sortmZ2Lep (ParticleMulti* i ,ParticleMulti*j);
    
        // HELPER to ease calculation
        void calcResults4lCutflow(CutFlow4l* cutFlow, OutputTreeType::OutputTreeType type);

        void fillMetaData();
    
};

#endif


