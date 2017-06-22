#ifndef ANALYSISBASE_H
#define ANALYSISBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>

// Root includes
#include "TString.h"

// Boost includes
#include "boost/regex.hpp"
#include "boost/algorithm/string/replace.hpp"

// xAOD includes
#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/EgammaContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODEgamma/PhotonContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODTau/TauJetContainer.h"
#include "xAODCore/tools/IOStats.h"
#include "xAODCore/tools/ReadStats.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthEventContainer.h"

// Local includes
#include "HZZCutCommon/EventContainer.h"

#include "HZZCutCommon/ParticleVar.h"

#include "HZZCutCommon/SmearingMuon.h"
#include "HZZCutCommon/SmearingJet.h"
#include "HZZCutCommon/SmearingEgamma.h"
#include "HZZCutCommon/SmearingTau.h"

#include "HZZCutCommon/OutputTree.h"

#include "HZZCutCommon/ToolInitBase.h"

// Tool include
#include "AsgAnalysisInterfaces/IPileupReweightingTool.h"



class AnalysisBase
{
    public:
        AnalysisBase();
        virtual ~AnalysisBase();

        // Setters
        
        /// Setter for the name of the xAOD container
        void setFileName(TString name)      { m_eventCont->setFileName(name);   };
        
        /// Setter for a string vector which containers the files to run over
        void setFiles   (const std::vector<std::string> &inputFileNames)
            { m_eventCont->setFiles(inputFileNames);    };
        
        /// Setter for the otuput minitree base name 
        void setOutName(TString name)
            { m_eventCont->setOutName(name);    };
    
        /// Setter to control what type of analysis to do for the event
        /// The base class implements Noimal and Systematic
        void setAnalysisType(AnalysisType::AnalysisType analType)
            { m_eventCont->m_analType = analType;    };
        
        /// Setter to control if we need to run systematics
        void doSystematic(Bool_t doSys, std::vector<TString> sysPattern)
        { m_doSys = doSys;  m_sysPattern = sysPattern;  };

        /// Setter to add version string
        void setMinitreeVersion(TString version)
        { m_version = version;  };
        /// Setter to add comments to minitree
        void setComment(TString comment)
        { m_comment = comment;  };

        /// Processes all the events
        /// Called from the steering script
        virtual Bool_t process();

        /// Finds a specific event and runs on that
        /// Used for debugging
        /// Called from the steering script
        Bool_t processDebug(ULong64_t t_eventNumber);
    
        /// Dump of the truth for a specfic number
        void printTruth(Int_t eventNumber);
    
        /// To print any cutflow or information after the
        /// processing of all events
        /// Called from the steering script
        virtual void printCutFlow(){};
    
        /// To set the number of events for testing
        void setnEventTest(Int_t nEventTest){m_nEventTest = nEventTest;};

        /// To get the input command options
        void setCommandOpts(std::map<TString, TString> opts) {m_opts = opts;};


    protected:
        // Variables
        /// For preventing double intialized when using debug functions
        Bool_t hasInitializedDebug;
    
        // To read containers in xAOD
        const xAOD::MuonContainer* m_muonCont;
        const xAOD::PhotonContainer* m_phCont;
        const xAOD::ElectronContainer* m_elCont;
        const xAOD::JetContainer* m_jetCont;
        const xAOD::JetContainer* m_truthJetCont;
        const xAOD::TauJetContainer* m_tauCont;
        const xAOD::TruthParticleContainer* m_tauTruthPartCont;
        const xAOD::TrackParticleContainer* m_tauTrackPartCont;
        const xAOD::VertexContainer* m_tauVertCont;
    
        // EventContainer class is to store information
        // that control the settings for the entire job
        // These can include if debug info should be printed
        // or if xAOD is MC/data or flag to figure out if 
        // sample is signal/bkg/Dc14/MC15 ....
        EventContainer* m_eventCont;

        // To control if systematics are to be run in the job
        Bool_t m_doSys;
        std::vector<TString> m_sysPattern;

        // Classes that implement smearing
        SmearingMuon* m_smearMuon;
        SmearingJet* m_smearJet;
        SmearingEgamma* m_smearEgamma;
        SmearingTau* m_smearTau;
    
        // Vector to store the links to local container classes for physics objects
        std::vector<ParticleVar*> m_muonList;
        std::vector<ParticleVar*> m_electronList;
        std::vector<ParticleVar*> m_photonList;
        std::vector<ParticleVar*> m_jetList;
        std::vector<ParticleVar*> m_truthJetList;
        std::vector<ParticleVar*> m_tauList;

        // Vector that stores the outtree for each type of variation in a given event
        // Expected to be implemented and filled by the dervied class
        std::map<CP::SystematicSet, OutputTree*> m_outTreeMap;
    
        // functions
    
        /// Intialization of all the local classes need for the analysis
        /// Called in the process function
        virtual void initialize();

        /// implements the actual cuts and smearing that 
        /// are expected to be performed in a given event
        virtual Bool_t processEvent();

        /// Called at the beginning of the processevent function
        /// Clears any memory or vectors that are specific for a given event
        virtual void clearVars();       

        /// Event preselection cuts are implemented here
        /// Expected cuts: dataPreselection, selection and trigger cuts
        virtual Bool_t eventPreSelection() {return true;};

        /// Electrons, muons, jets and photons are read and filled into
        /// container classes
        virtual Bool_t fillPhyObjects();

        /// Smearing is carried out for the physics objects
        virtual void smearPhyObjects();

        /// Selection for physics objects is implemented here
        /// Expected cuts: electron, muons, jets, and photons level cuts
        /// Overlap removal here as well
        virtual void selectPhyObjects(){};

        /// Main event selection is implemented here
        virtual Bool_t eventSelection() {return true;};

        /// Calculation of final variables for the event
        /// Stored directly in container in outputtree class
        virtual void calcVars() {};
    
        /// Called at the end of the event loop
        /// saves the output of the tree
        virtual void finalize();
    
        /// For storing the systematic into the main list for looping
        virtual void addSystematicsSet();
    
        /// Does the systematic match any of the given systematic strings that user wants?
        Bool_t matchPatternSys(const std::string sysName) const;

        // Helper functions

        /// To fill in local particle container classes
        void fillMuon(const xAOD::MuonContainer* muonCont);
        void fillElectron(const xAOD::ElectronContainer* elCont);
        void fillPhoton(const xAOD::PhotonContainer* phCont);
        void fillJet(const xAOD::JetContainer* jetCont);
        void fillTruthJet(const xAOD::JetContainer* truthJetCont);
        void fillTau(const xAOD::TauJetContainer* jetCont);
    
        /// To set the right TLV analysis type after smearing
        void setAnalType();
     
        /// To update any cutflow for associated class
        virtual void updateCutFlow(Int_t cutLevel, Int_t valToAdd = 1)= 0;
        
        /// To copy any cutflow numbers to the output histrograms        
        virtual void updateHistCutFlow() {};
    
        /// Store the number of events processed
        /// This is relegated to the derived classes as weights need to be taken in account
        virtual void updateEvtsProc() = 0;


        // This function is designed to pre-cal/init the information needed for that event
        // Mainly random run number and trigger period
        virtual void initEvent();
    
        /// Converts the PDGID
        TString getParticleName(int pdgID);
    
        /// For creating all the tools
        ToolInitBase* m_toolBase;
    
        /// For Local testing
        Int_t m_nEventTest;

        // For triggers the calculation of random run number
        ToolHandle<CP::IPileupReweightingTool> m_pileupTool;     

        // For TTree metadata
        TString m_version;
        TString m_comment;

        virtual void fillMetaData(){};

        // Accessor to command line arguments 
        TString getCmdArg(TString key) const;
        bool hasCmdArg(TString key) const;

    private:
        // Command line opts
        // make this private the provide an accesor to this
        std::map<TString, TString> m_opts;

};

#endif


