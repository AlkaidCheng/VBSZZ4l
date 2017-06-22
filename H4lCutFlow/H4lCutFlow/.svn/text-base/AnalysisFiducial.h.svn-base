#ifndef ANALYSISFIDUCIAL_H
#define ANALYSISFIDUCIAL_H

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

#include "H4lCutFlow/ApplyWeight4l.h"

//#include "H4lCutFlow/OutputTree4lFiducial.h"
#include "H4lCutFlow/OutputTree4lInclusive.h"
#include "HZZCutCommon/OutputTree.h"

#include "H4lCutFlow/CutFlow4lFiducial.h"
#include "HZZCutCommon/ParticleQuadlepton.h"

//#include "H4lCutFlow/CalculateVar4lFiducial.h"
#include "H4lCutFlow/CalculateVar4lInclusive.h"
#include "H4lCutFlow/TruthHelper.h"
#include "H4lBDTWeights/IH4lBDTWeights.h"
#include "H4lCutFlow/ToolInit4l.h"

// xAOD includes
#include "xAODMetaData/FileMetaData.h"


class AnalysisFiducial : public AnalysisBase
{
    public:
        AnalysisFiducial();
        virtual ~AnalysisFiducial();
    
        /// To print any cutflow or information after the
        /// processing of all events
        /// Called from the steering script
        void printCutFlow();


    protected:
        // Variables
        CutEventDataPreSel* m_dataPreSel;
        CutEventPreSel* m_preSel;

        CutParticleMuon* m_cutMuon;
        CutParticleElectron* m_cutElectron;
        CutParticleJet* m_cutJetTruthFid;
        //CutParticleJet* m_cutWZJetTruthFid;

    
        CutFlow4lFiducial* m_cutFlow4l;
        CutFlow4lFiducial* m_cutFlow4mu;
        CutFlow4lFiducial* m_cutFlow2mu2e;
        CutFlow4lFiducial* m_cutFlow2e2mu;
        CutFlow4lFiducial* m_cutFlow4e;
    
        ApplyWeight4l* m_applyWeight;
    
        //CalculateVar4lFiducial* m_calculateVar;
        CalculateVar4lInclusive* m_calculateVar;
    
        TruthHelper* m_truthHelper;

        //const xAOD::TruthParticleContainer *m_truthCont;
        //void fillTruth(const xAOD::TruthParticleContainer* truthCont);
        //std::pair< xAOD::TruthParticleContainer*, xAOD::ShallowAuxContainer* > m_truth_shallowCopy;
        std::vector<ParticleVar*> m_fidMuonsList;
	    std::vector<ParticleVar*> m_fidElectronsList;
	    std::vector<ParticleVar*> m_fidJetsList;

    
        // Candidate Higgs
        Bool_t m_passCutflow;
        ParticleQuadlepton* m_higgs;
        ParticleQuadlepton* m_higgs_fid;
    
        // Tool store
        ToolInit4l* tool4l;
    
        // Tools

        // functions
    
        /// Intialization of all the local classes need for the analysis
        /// Called in the process function
        void initialize();

        /// Called at the beginning of the processevent function
        /// Clears any memory or vectors that are specific for a given event
        void clearVars();
        void smearPhyObjects();
	void setAnalType();

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
    
        Bool_t checkPairingOverlap(LepCombBase* partOne, LepCombBase* partTwo);
        Bool_t checkAllOverlap(LepCombBase* partOne, LepCombBase* partTwo);
    
    
        /// Store the number of events processed
        void updateEvtsProc();
        
        //do simple fiducial selection of fiducial objects
        std::vector<ParticleVar*> removeOverlapFidJets(std::vector<ParticleVar*> truthJets,std::vector<ParticleVar*> fidElectrons,std::vector<ParticleVar*> fidMuons);
        std::vector<ParticleVar*> chooseFidMuons(std::vector<ParticleVar*> truthMuons);
        std::vector<ParticleVar*> chooseFidElectrons(std::vector<ParticleVar*> truthElectrons);
        Double_t DeltaR (Double_t eta_1, Double_t phi_1, Double_t eta_2, Double_t phi_2);

    
        void fillMetaData();

    

    
};

#endif


