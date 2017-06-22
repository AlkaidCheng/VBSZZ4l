#ifndef PARTICLEBASE_H
#define PARTICLEBASE_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <map>

// Root includes
#include "TString.h"
#include "TLorentzVector.h"

// Local includes
#include "HZZCutCommon/EventContainer.h"
#include "HZZCutCommon/EnumDefCommon.h"

class ParticleBase 
{
    public:
        ParticleBase(EventContainer* t_eventcont);
        virtual ~ParticleBase();

        /// Getters for internal stored types
        ParticleType::ParticleType  getPartType() const  {return m_partType;};
        TLVType::TLVType            getTLVType()  const  {return m_currTLVType;};
        AnalysisType::AnalysisType  getAnalType() const  {return m_analType;};

        /// Gets the current TLV 
        TLorentzVector getTLV() const {return m_currTLV;};
        /// Gets a specifically stored TLV
        TLorentzVector getAnalTLV(TLVType::TLVType tlvType) const;

        /// Index of particle in the container
        Int_t getIndex() const {return m_index;};
        /// Gets the charge of the particles
        Int_t getCharge() const {return m_charge;};
    
        /// String version of type of this event
        virtual TString getName() const {return "ParticleBase";};

        /// Adds a TLV to the map
        void addAnalTLV(TLVType::TLVType tlvType, TLorentzVector tlv, Bool_t overWrite = false);

        /// Sets the current TLV
        virtual void setTLVType(TLVType::TLVType tlvType);
        /// Sets the current Analysis type of this particle and makes any associated change
        virtual void setAnalysisType(AnalysisType::AnalysisType analType);

        /// To check if the analysis type are in the TLV
        virtual Bool_t checkTLVType(TLVType::TLVType tlvType) const;

	virtual void addMetadataInt(TString key, int val) { m_intMetaData[key] = val;};
        virtual int getMetadataInt(TString key);



    protected:
        EventContainer* m_eventCont;

        // To store the current information about the particle
        ParticleType::ParticleType m_partType;
        TLVType::TLVType m_currTLVType;
        AnalysisType::AnalysisType m_analType;

        // Stores the current TLV
        TLorentzVector m_currTLV;

        // ParticleLevel info
        Int_t m_index;
        Int_t m_charge;
    
        // maps that contain everything
        std::map<TLVType::TLVType, TLorentzVector> m_tlvCont; 

	// Store any information about this particle
        std::map<TString, int> m_intMetaData;

};

#endif




