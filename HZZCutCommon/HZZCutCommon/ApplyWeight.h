#ifndef APPLYWEIGHT_H
#define APPLYWEIGHT_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <map>

// Local includes
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/LepCombBase.h"
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"

// xAOD EDM include
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"
#include "xAODJet/Jet.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticleContainer.h"

// Tool includes
#include "AsgAnalysisInterfaces/IPileupReweightingTool.h"
#include "HZZUtils/IHiggsCrossSection.h"
#include "HZZUtils/ITheoryVariation.h"
#include "HZZUtils/IH4lBrRatio.h"
#include "HZZUtils/BkgCrossSection.h"

class ApplyWeight 
{
    public:
        ApplyWeight(EventContainer* t_eventcont);
        virtual ~ApplyWeight();
    
        /// setup anything dependant on systematics
        virtual void initialize() {};
        
        /// Gets event weight such as pileup, zvertex
        /// Still to implement fully
        virtual Double_t getEventWeight();

        /// Cross-Section weight
        virtual Double_t getCrossSection() const;
        
        /// Branching ratio weight
        virtual Double_t getBranchingRaio() const;
    
        /// MC weight
        virtual Double_t getMCWeight() ;
    
        /// Pileup weight
        virtual Double_t getPileUpWeight() ;
    
        /// Luminosity
        virtual Double_t getLumi();
    
        /// To Fill the output to the TTree
        virtual void fillWeight(const LepCombBase*){};
    
        // To clear vars
        virtual void clearVars();

    protected:
        EventContainer* m_eventCont;

        // for caching the pileup weight
        bool m_pileupCached;
        double m_pileupWeight;
        // this is to overwrite the random run number differences that come when doing a PRW systematic
        unsigned int m_pileupRandRunNumber;

        // Pile up tool
        ToolHandle<CP::IPileupReweightingTool> m_pileupTool;
        ToolHandle<IHiggsCrossSection> m_xsTool;
        ToolHandle<ITheoryVariation> m_varTool;
        ToolHandle<IH4lBrRatio> m_brTool;



};

#endif




