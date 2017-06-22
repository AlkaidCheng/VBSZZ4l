#ifndef CUTEVENTTRIGGER_H
#define CUTEVENTTRIGGER_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <map>

// Base class include
#include "HZZCutCommon/CutEventBase.h"

// xAOD EDM include

// Tool include
#include "TrigConfxAOD/xAODConfigTool.h"
#include "TrigDecisionTool/TrigDecisionTool.h"

class CutEventTrigger : public CutEventBase 
{
    public:
        CutEventTrigger(EventContainer* eventcont);
        virtual ~CutEventTrigger();
    
        void initialize();

        Bool_t passCut() const;

        void clearVars();
        

        
        Bool_t singleMuonTrigger() const;
        Bool_t diMuonTrigger() const;
        Bool_t triMuonTrigger() const;
    
        Bool_t singleElectronTrigger() const;
        Bool_t diElectronTrigger() const;
        Bool_t triElectronTrigger() const;

        Bool_t passTrigger(const TString& trigList) const;

        Bool_t elMuTrigger() const;

        Int_t singleTrigger(TString singleTrigName) const;
    
        std::vector<TString> getSingleMuTrig() const;
        std::vector<TString> getDiMuTrig() const;
        std::vector<TString> getTriMuTrig() const;
        std::vector<TString> getSingleElTrig() const;
        std::vector<TString> getDiElTrig() const;
        std::vector<TString> getTriElTrig() const;
        std::vector<TString> getElMuTrig() const;
    
        TString getTriggerString(const std::vector<TString>& trigName) const;

        void removeTriMu(){m_doTriMu = false;}   
        void removeTriEl(){m_doTriEl = false;}   
        void removeElMu(){m_doElMu = false;}   
        void enableTrigStudy(){m_doTrigStudy = true;}

    private:
        ToolHandle<Trig::ITrigDecisionTool> m_tdt;
    
        TString singleMuTrigList;
        TString diMuTrigList;
        TString triMuTrigList;
        TString singleElTrigList;
        TString diElTrigList;
        TString triElTrigList;
        TString elMuTrigList;
 
        // For debugging
        Bool_t overWriteTrig;

        Bool_t m_doTriMu;
        Bool_t m_doTriEl;
        Bool_t m_doElMu;
        Bool_t m_doTrigStudy;

        // To reduce the number of times the output is printed
        // this is mutable, since it only affects during debugging to print crazy print out
        mutable Bool_t m_printDebug;
};

#endif


