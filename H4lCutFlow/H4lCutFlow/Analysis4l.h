#ifndef ANALYSIS4l_H
#define ANALYSIS4l_H

// Base class include
#include "HZZCutCommon/AnalysisBase.h"
#include "HZZCutCommon/ToolInitBase.h"

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

#include "H4lCutFlow/OutputTree4l.h"
#include "HZZCutCommon/OutputTree.h"

#include "H4lCutFlow/CutFlow4l.h"
#include "HZZCutCommon/ParticleQuadlepton.h"

#include "H4lCutFlow/CalculateVar4l.h"
#include "H4lCutFlow/TruthHelper.h"

#include "H4lCutFlow/ToolInit4l.h"
#include "HZZCutCommon/METCalc.h"

// Systematics
#include "PATInterfaces/SystematicRegistry.h"

// xAOD includes
#include "xAODMetaData/FileMetaData.h"

// ME based tools
#include "H4lBDTWeights/IH4lBDTWeights.h"


class Analysis4l : public AnalysisBase
{
    public:
        Analysis4l();
        virtual ~Analysis4l();
    
        /// To print any cutflow or information after the
        /// processing of all events
        /// Called from the steering script
        void printCutFlow();
        void enableTrigStudy() {m_doTrigStudy = true;};

    protected:
        // Variables
        CutEventDataPreSel* m_dataPreSel;
        CutEventPreSel* m_preSel;
        CutEventTrigger* m_trigger;

        CutParticleMuon* m_cutMuon;
        CutParticleElectron* m_cutElectron;
        CutParticleJet* m_cutJet;
        CutParticleJet* m_cutJetFid;

        RemoveOverlap4l* m_removeOverlap;
        RemoveOverlap4l* m_removeOverlapFid;
    
        CutFlow4l* m_cutFlow4l;
        CutFlow4l* m_cutFlow4mu;
        CutFlow4l* m_cutFlow2mu2e;
        CutFlow4l* m_cutFlow2e2mu;
        CutFlow4l* m_cutFlow4e;
    
        ApplyWeight4l* m_applyWeight;
    
        CalculateVar4l* m_calculateVar;
    
        TruthHelper* m_truthHelper;
    
        std::shared_ptr<METCalc> m_METCalc;

    
        // Candidate Higgs
        ParticleQuadlepton* m_higgs;
    
        // Tool store
        ToolInit4l* tool4l;
    
        // For Acceptance challenge
        // This is used to control were the trigger decision is applied
        Bool_t m_forAcceptanceChallenge;
    
        /// If we are doing systematic that are only normalization
        Bool_t m_doNormSys;
    
        /// If we are doing systematic that are only MET
        Bool_t m_doMETSys;
        /// If you are doing efficiency studies, add all the trigger variables.
        Bool_t m_doTrigStudy;

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
    
        /// To update any cutflow for associated class
        void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1);
        
        /// To copy any cutflow numbers to the output histrograms        
        void updateHistCutFlow();
    
        /// Store the number of events processed
        void updateEvtsProc();
    
        /// systematic set
        void addSystematicsSet();
        /// systematic set with normalization systematic
        void addNormSystematicsSet();
    
        /// systematic set with MET systematic
        void addMETSystematicsSet();
    
        // Systematics
        std::vector<CP::SystematicSet> m_sysNormList;
        std::vector<CP::SystematicSet> m_sysMETList;

        // For norm searching systematics with regex search
        bool isPatternMatch(const std::string varName, const std::string pattern);
    
        void fillMetaData();

	// For saving the vector of higgs quads
	std::vector<ParticleQuadlepton*> m_higgsCandList;

        // Tool for ME calculations 
	ToolHandle<IH4lBDTWeights> m_BDTtool;

	void calcHiggsVars(ParticleQuadlepton* currHiggs, int candIndex, int isNominal = 1);

};

#endif


