#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <memory>

// Root includes
#include "TString.h"
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TTreeFormula.h"

// xAOD includes
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/ReturnCheck.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODRootAccess/TStore.h"
#include "xAODCore/ShallowCopy.h"
#include "xAODCutFlow/CutBookkeeper.h"
#include "xAODCutFlow/CutBookkeeperContainer.h"
#include "AsgTools/ToolHandle.h"

// For systematics
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/SystematicVariation.h"
#include "PATInterfaces/SystematicsUtil.h"

// Local Includes
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/log.h"
#include "HZZCutCommon/OutputTree.h"

class EventContainer 
{
    public:
        EventContainer();
        ~EventContainer();

        // Setters of Analysis Information
        void setFileName(TString name)      { fileName = name;      };
        void setTTree   (TTree* currTree)   { fileTree = currTree;  };
        void setFiles   (const std::vector<std::string> &inputFileNames) { m_inputFileNames = inputFileNames;    };
        void setOutName (TString name)      { outputBaseName = name; };
        
        // To increment the event
        Bool_t getEntry (Int_t i);

        // Getter
        xAOD::TEvent* getEvent() {return event;};
        TChain* getChain() {return m_chain;};

        // Intialize
        Bool_t initialize();
        Bool_t hasInit;


        ///////////////
        // sample Info
        ///////////////
        TString fileName;       // Sample Name

        Bool_t isMC;            // is MC?
        Bool_t m_AFII;          // is fast simulation?

        Bool_t isEFT;           // is EFT sample
        Bool_t m_isDAODTRUTH;   // is a DAOD truth sample
        Bool_t m_isAOD;         // is AOD sample

        Generator::Generator m_currGenerator;   // Generator - mainly intended for truth calculations

        SampleType::SampleType sampleType;      // sample Type
        Double_t mHTrue;                        // truth Higgs mass if it is a signal sample
        Bool_t isNoTau;                         // is no Tau sample


        ///////////////
        // event Info
        ///////////////
        Int_t runNumber;        // runNumber
        Int_t mcChannelNumber;  // MC number
        Int_t mcRunNumber;      // MC number gotten from name
        Int_t m_eventIndex;     // Numerical index that is currently being run over
        Int_t eventNumber;      // current event number

        // Data period
        Periods::Periods m_dataPeriod;
        TrigPeriods::TrigPeriods m_trigPeriod;

        ///////////////
        // Code Control Var
        ///////////////
        TString outputBaseName;                     // Output file name
        Bool_t isDebug;                             // For Debugging 

        const xAOD::EventInfo* eventInfo;           // Event Info
        xAOD::TStore* store;                        // TStore
                
        OutputTree* outTree;                        // Current output tree where the variables are stored
        
        CP::SystematicSet m_currVariation;          // Current Systematic that is being looped over

        Bool_t doSmear;                             // To Control is smearing need to be done
        AnalysisType::AnalysisType m_analType;      // To control what type of analysis to do;

        std::vector<CP::SystematicSet> m_sysList;   // Systematics
   
        void fillEventHist();                       // to fill event count info
        
        Int_t getDSID();                            // return the DSID obtained in an appropriate way, works on both TRUTH4 and reco (D)AOD

    private:
        // Input Files
        std::vector<std::string> m_inputFileNames;
        TChain* m_chain;
        TTree* fileTree;

        // TEvent
        xAOD::TEvent* event;
        

        // Helper functions
        void fillSampleTypeHiggsMass();
        void fillNoTau();
        void fillAFII();
        void fillIsDAODTRUTH();
        void fillIsAOD();

        void fillGeneratorInfo();

    
        TString getKernelName();
    
};

#endif


