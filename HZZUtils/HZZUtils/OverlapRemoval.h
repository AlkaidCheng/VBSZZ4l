#ifndef OVERLAPREMOVAL_H
#define OVERLAPREMOVAL_H

#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthVertex.h"
#include "TLorentzVector.h"


    /*virtual*/ float killEvent(unsigned int runNumber, const xAOD::TruthParticleContainer * truthParticles, bool doZZHighMass = true, bool doZZLowMass = true, bool doTtbar4l = true);

#endif//OVERLAPREMOVAL_H
