#ifndef SMEARINGTAU_H
#define SMEARINGTAU_H

// C++ includes
#include <stdlib.h>
#include <iostream>

// Root includes
#include "HZZCutCommon/SmearingBase.h"

// xAOD EDM include
#include "xAODTau/TauJet.h"
#include "xAODTau/TauJetContainer.h"

//// CP tools
//#include "TauAnalysisTools/ITauSmearingTool.h"
//#include "TauAnalysisTools/ITauTruthMatchingTool.h"

class SmearingTau : public SmearingBase 
{
    public:
        SmearingTau(EventContainer* eventcont);
        virtual ~SmearingTau();

        void process();
    
        void setTauCont(const xAOD::TauJetContainer* jetCont)
        {m_tauCont = jetCont;};
        const xAOD::TauJetContainer* getCalTauCont() const
        {return m_shallowCopy.first;};
    
        void clearVars();
    
        void processVar(xAOD::IParticle* currPart);

    protected:
        const xAOD::TauJetContainer* m_tauCont;
    
        std::pair< xAOD::TauJetContainer*, xAOD::ShallowAuxContainer* > m_shallowCopy;
    
        //ToolHandle<TauAnalysisTools::ITauSmearingTool> m_tauCalibTool;
        //ToolHandle<TauAnalysisTools::ITauTruthMatchingTool> m_tauTruthMatchTool;



};

#endif


