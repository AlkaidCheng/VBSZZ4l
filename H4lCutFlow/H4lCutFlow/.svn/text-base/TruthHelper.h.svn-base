#ifndef TRUTHHELPER_H
#define TRUTHHELPER_H

// C++ includes
#include <vector>

// Root includes
#include "HZZCutCommon/ParticleVar.h"
#include "HZZCutCommon/ParticleDilepton.h"
#include "HZZCutCommon/ParticleQuadlepton.h"
#include "HZZCutCommon/LepCombBase.h"
#include "HZZCutCommon/EventContainer.h"
#include "H4lCutFlow/RemoveOverlap4l.h"

// xAOD EDM include
#include "xAODTruth/TruthVertexContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"

class TruthHelper {
    public:
        TruthHelper(EventContainer* eventcont);
        virtual ~TruthHelper();
    
        void clearVars();
    
        // Mainly to setup anything depedant on systematics
        virtual void initialize() {};
    
    
        /////////////////////////////////////
        // Reco Match Truth functions
        /////////////////////////////////////
        /// get the linked truth particle
        const xAOD::TruthParticle* getTruthParticle(const xAOD::IParticle *in_p);
    
        /// Get the truth level quadruplet for the input reco quad
        /// For this function, the matching comes from the truthParticle links
        ParticleQuadlepton* getTruthQuad(const ParticleQuadlepton* q);
    
        /////////////////////////////////////
        // Reco Match Truth function
        // but using leptons from Bosons
        /////////////////////////////////////
        /// Get the truth level quadruplet for the input reco quad
        /// For this function, the matching comes what is defined in HSG2... This is still being decided
        std::vector<const xAOD::TruthParticle*> getRecoMatchTruth(const LepCombBase* q);
    
    
        /////////////////////
        // Bare truth from bosons
        /////////////////////
        // Gets the bare leptons but in a particleVar format
        std::vector<ParticleVar*> getBareParticleVarFromBoson();
    
        /////////////////////
        // Born Truth from Boson
        /////////////////////
        // Gets the born truth
        std::vector<ParticleVar*> getBornLeptonsFromBoson();
    
        /////////////////////
        // Bare -> Born
        /////////////////////
        /// Match bare leptons to born leptons. Need this for fiducial sstudies.
        std::vector<ParticleVar*> getBornLeptonsFromBareLeptons(std::vector<const xAOD::TruthParticle*> bareLeptons);
    
    
        /////////////////////
        // Bare Quad
        /////////////////////
        /// Get the bare truthQuadLepton
        ParticleQuadlepton* getBareQuadlepton();
    
        /////////////////////
        // Born Quad
        /////////////////////
        /// To get the born truthQuadlepton
        /// Input is the output from getBareQuadlepton
        ParticleQuadlepton* getBornQuadlepton(ParticleQuadlepton* quad = 0);
    
        /// Get the corresponding born lepton for the input truth particle
        const xAOD::TruthParticle* getBornLepton(const xAOD::TruthParticle* in_p) const;
    
    
        /////////////////////
        // Dressed Quad
        /////////////////////
        //to get the dressed quadlepton based on the truth
        ParticleQuadlepton* getDressedQuadlepton(ParticleQuadlepton* quad = 0);
    
        /////////////////////
        // B-tagging
        /////////////////////
        std::vector<ParticleVar*> findTruthBjets(std::vector<ParticleVar*> jetList);

        /////////////////////
        // Dressing
        /////////////////////
        std::vector<ParticleVar*> getDressedLeptonsFromBoson();
        std::vector<ParticleVar*> getDressedLeptonsFromBareLeptons(std::vector<const xAOD::TruthParticle*> bareLeptons);


        ////////////////////////
        // Lepton finding helper
        ////////////////////////
        std::vector<ParticleVar*> getFirstFourLeptonsFromHiggs();
       
    
        /////////////////////
        // Helpers
        /////////////////////
        /// Get the true truth type of the Higgs particle
        QuadleptonType::QuadleptonType getTruthHiggsType();
        

        //ParticleQuadlepton* getQuadleptonFromTruthHiggs();


        /////////////////////
        // Truth -> Reco
        /////////////////////
        /// To get the reco quadlepton based on the truth
        ParticleQuadlepton* getRecoQuadlepton(ParticleQuadlepton* quad, std::vector<ParticleVar*> muList, std::vector<ParticleVar*> elList);
    
        /// get the closest reco particle from the list to the given input particle list
        ParticleVar* getClosestRecoPart(const xAOD::TruthParticle* th, std::vector<ParticleVar*> lepList) const;


        std::vector<ParticleVar*> getParticleVar(std::vector<const xAOD::TruthParticle*> tps);


        // For tagging the higgs decay
        int getHiggsDecayTag();
    
    private:
        // Private Variables
        EventContainer* m_eventCont;
    
        std::vector<ParticleVar*>        m_partContainer;
        std::vector<ParticleDilepton*>   m_diLepContainer;
        std::vector<ParticleQuadlepton*> m_quadContainer;

        // For caching the results of getBareQuadlepton()
        ParticleQuadlepton* m_bareQuad;
    
        /////////////////////////////////////
        // Reco Match Truth functions
        /////////////////////////////////////
        /// Get reco matched truth particle
        std::vector<const xAOD::TruthParticle*> getTruthParticles(const LepCombBase* q);
    
        /////////////////////////////////////
        // Reco Match Truth function
        // but using leptons from Bosons
        /////////////////////////////////////
        // Mainly used by getRecoMatchTruth
        // Need to check if the dependancy can be moved to getBareTruthFromBoson
        std::vector<const xAOD::TruthParticle*> getBareTruthFromBoson();
    
        /////////////////////
        // Bare truth from bosons
        /////////////////////
        /// Gets the bare leptons from bosons... need this for reco-matched
        std::vector<const xAOD::TruthParticle*> getBareLeptonsFromBoson(); // only get electron and muon
        // Sherpa specific
        std::vector<ParticleVar*> getBareLeptonsFromBoson_Sherpa();
        // helper method, mainly needed for sherpa samples.
        // Fills the "collection" set with all unique status 1 leptons found in the decay chain of 'part'
        // depth function is to prevent an infinite recursion
        void collectStableChildren_Sherpa(const xAOD::TruthParticle* part, std::set<const xAOD::TruthParticle*> & collection, std::set<const xAOD::TruthParticle*> testedParticle);
    
        /// Get the corresponding bare lepton for the input truth particle
        const xAOD::TruthParticle* getBareLepton(const xAOD::TruthParticle* in_p) const;

        /////////////////////
        // Born Truth from Boson
        /////////////////////
        // Same getBornLeptonsFromBoson but for sherpa
        std::vector<ParticleVar*> getBornLeptonsFromBoson_Sherpa();
    
        /////////////////////
        // Bare Quad
        /////////////////////
        // Generator dependant implementation of the algorithm
        ParticleQuadlepton* getBareQuadlepton_PowhegPythia8();
        ParticleQuadlepton* getBareQuadlepton_aMcAtNloHerwigppEvtGen();
        ParticleQuadlepton* getBareQuadlepton_aMcAtNloHerwigpp_RecoPairing();
        ParticleQuadlepton* getBareQuadlepton_Sherpa();
        ParticleQuadlepton* getBareQuadlepton_RecoPairing();
    
        /////////////////////
        // Born Quad
        /////////////////////
        // special Sherpa flavour
        ParticleQuadlepton* getBornQuadlepton_Sherpa();
    
        /// Gets the born lepton for particles where the truth is arranged in a tree structure like l(born) -> l -> ... -> l(bare)
        const xAOD::TruthParticle* getBornLeptonTree(const xAOD::TruthParticle* in_p) const;
        /// Gets the born lepton where bare and born leptons have the same mother
        const xAOD::TruthParticle* getBornLeptonMother(const xAOD::TruthParticle* in_p) const;
    
        /// Input is a Z boson, returns a flag indicating if Z's child contains both bare and born letpons
        Bool_t checkBareBornSameMother(const xAOD::TruthParticle* in_p) const;
    
    
        /////////////////////
        // Dressing
        /////////////////////
        std::vector<const xAOD::TruthParticle*> getPhotonsForDressing();
    
        /// Get the corresponding dressed lepton for the input truth particle
        ParticleVar* getDressedLepton(const xAOD::TruthParticle* in_p);
        std::vector<ParticleVar*> getDressedLeptonsVector(std::vector<const xAOD::TruthParticle*> leptons, std::vector<const xAOD::TruthParticle*> photons, double dRcut);

    
        /////////////////////
        // Helpers
        /////////////////////
        /// Get the closest truth particle for input reco particle with the same PDGID
        const xAOD::TruthParticle* getClosestTruthPart(const xAOD::IParticle *in_p) const;
        /// Get the closest truth particle for input reco particle with the same PDGID, but from the list of input particles
        const xAOD::TruthParticle* getClosestTruthPart(const xAOD::IParticle *in_p, std::vector<const xAOD::TruthParticle*> particleList) const;
    
        // perform the fiducial pairing on the (four) leptons we found. Needed for Sherpa.
        ParticleQuadlepton* RunPairing(std::vector<ParticleVar*> & leptons);
        ParticleQuadlepton* RunPairing(ParticleQuadlepton* quad);
    
        /// Tau child
        const xAOD::TruthParticle* getTauLeptonChild(const xAOD::TruthParticle* in_p) const;



        // function that checkes if a parent in the decay chain has the given PDGID
        // it returns false if the sample is sherpa... I don't want to deal with it, leaving it for someone else ... HA
        bool checkParentPDGID(const xAOD::TruthParticle* in, int pdgid) const;
        bool checkParent(const xAOD::TruthParticle* in, const xAOD::TruthParticle* toCheck) const;        
};

#endif
