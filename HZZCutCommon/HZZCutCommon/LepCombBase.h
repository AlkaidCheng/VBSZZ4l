#ifndef LEPCOMBBASE_H
#define LEPCOMBBASE_H

// C++ includes
#include <stdlib.h>

// Local includes
#include "HZZCutCommon/ParticleVar.h"

class LepCombBase
{
    /// Simple iterator interface for the multi-lepton classes  
    public:
        LepCombBase() {};
        virtual ~LepCombBase() {};

        /// Return number of leptons stored internally          
        virtual Int_t getLepSize() const = 0 ;
        
        /// Return specific lepton denote by i          
        virtual ParticleVar* getLep(Int_t i) const = 0;
        
};

#endif


