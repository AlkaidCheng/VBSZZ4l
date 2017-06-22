#include "H4lCutFlow/Analysis4l.h"

// Boost includes
#include "boost/regex.hpp"
#include "boost/algorithm/string/replace.hpp"

#include <limits>

using namespace std;

// Constructor
    Analysis4l::Analysis4l()
:AnalysisBase()
{
    //m_eventCont->doSmear = false;
    // For configuration
    m_forAcceptanceChallenge = true;
    m_doNormSys = false;
    m_doMETSys = false;
    m_doTrigStudy = false;
}

// Destructor
Analysis4l::~Analysis4l()
{
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        // Deleting the output minitree
        delete m_outTreeMap[sysListItr];
    }

    if(m_dataPreSel)      delete m_dataPreSel;
    if(m_preSel)          delete m_preSel;
    if(m_trigger)         delete m_trigger;

    if(m_cutMuon)         delete m_cutMuon;
    if(m_cutElectron)     delete m_cutElectron;
    if(m_cutJet)          delete m_cutJet;
    if(m_cutJetFid)       delete m_cutJetFid;
    if(m_removeOverlap)   delete m_removeOverlap;
    if(m_removeOverlapFid)delete m_removeOverlapFid;
    if(m_cutFlow4l)       delete m_cutFlow4l;
    if(m_cutFlow4mu)      delete m_cutFlow4mu;
    if(m_cutFlow2mu2e)    delete m_cutFlow2mu2e;
    if(m_cutFlow2e2mu)    delete m_cutFlow2e2mu;
    if(m_cutFlow4e)       delete m_cutFlow4e;
    if(m_applyWeight)     delete m_applyWeight;

    if(m_calculateVar)    delete m_calculateVar;

    if(m_truthHelper)     delete m_truthHelper;

    if(tool4l) delete tool4l;

}


// For intializating that depends after variables
// have been setup from the job and after the first 
// event has been read
// Typically all classes are expected to be created
// and intialized here
void Analysis4l::initialize()
{
    LOG(logINFO) << "initialize event info";
    StatusCode::enableFailure();
    m_eventCont->initialize();

    tool4l = new ToolInit4l(m_eventCont);

    // For doing the reduced systematic set
    if (getCmdArg("reducedSys") == "true") 
    {
        tool4l->setDoReducedSys();
        LOG(logWARNING) << "Analysis4l::initialize() - Reduced systematic set.";
    }

    
    if(hasCmdArg("fullEgammaSys"))
    {
        if(getCmdArg("fullEgammaSys") == "true")
        {
            tool4l->setDoFullEgammaSys();
            LOG(logWARNING) << "Analysis4l::initialize() - Doing full egamma sys... will overwrite the Reduced set, if set.";
        }
    }

    tool4l->initialize();
    m_toolBase = (ToolInitBase*) tool4l;

    if(m_doSys) m_forAcceptanceChallenge = false;

    AnalysisBase::initialize();

    // Trigger studies
    if (getCmdArg("doTrigStudy") == "true") 
    {
        enableTrigStudy();
        LOG(logWARNING) << "Analysis4l::initialize() - Enabling trigger studies. Will save trigger variables.";
    }


    // Constructor
    m_dataPreSel  = new CutEventDataPreSel(m_eventCont);
    m_preSel      = new CutEventPreSel(m_eventCont);
    m_trigger     = new CutEventTrigger(m_eventCont);
    if(m_doTrigStudy) m_trigger->enableTrigStudy();

    m_cutMuon     = new CutParticleMuon(m_eventCont);
    m_cutElectron = new CutParticleElectron(m_eventCont);
    m_cutJet      = new CutParticleJet(m_eventCont);
    m_cutJet->setJetSelType(CutParticleJet::NominalReco);

    m_cutJetFid   = new CutParticleJet(m_eventCont);
    m_cutJetFid->setJetSelType(CutParticleJet::FiducialReco);

    m_removeOverlap = new RemoveOverlap4l(m_eventCont);
    m_removeOverlapFid = new RemoveOverlap4l(m_eventCont);

    m_applyWeight   = new ApplyWeight4l(m_eventCont);

    m_cutFlow4l    = new CutFlow4l(m_eventCont, m_applyWeight);
    m_cutFlow4mu   = new CutFlow4l(m_eventCont, m_applyWeight);
    m_cutFlow4mu->setQuadAnalysisType(QuadleptonType::_4mu);

    m_cutFlow2mu2e = new CutFlow4l(m_eventCont, m_applyWeight);
    m_cutFlow2mu2e->setQuadAnalysisType(QuadleptonType::_2mu2e);

    m_cutFlow2e2mu = new CutFlow4l(m_eventCont, m_applyWeight);
    m_cutFlow2e2mu->setQuadAnalysisType(QuadleptonType::_2e2mu);

    m_cutFlow4e    = new CutFlow4l(m_eventCont, m_applyWeight);
    m_cutFlow4e->setQuadAnalysisType(QuadleptonType::_4e);

    m_METCalc = std::make_shared<METCalc>(m_eventCont);

    m_calculateVar = new CalculateVar4l(m_eventCont);
    m_calculateVar->setMETClass(m_METCalc);

    m_truthHelper = new TruthHelper(m_eventCont);

    // Set the last cut
    m_cutFlow4mu->setLastCut(cutFlow::D0Sig);
    m_cutFlow2mu2e->setLastCut(cutFlow::D0Sig);
    m_cutFlow2e2mu->setLastCut(cutFlow::D0Sig);
    m_cutFlow4e->setLastCut(cutFlow::D0Sig);


    addSystematicsSet();

    // Set of initialization - to be called only by the derived class
    // This is intended to setup any thing after all the tools have be initialized
    // Mainly will be used for any setup dependant on systematics
    m_dataPreSel->initialize();
    m_preSel->initialize();
    m_trigger->initialize();

    m_cutMuon->initialize();
    m_cutElectron->initialize();
    m_cutJet->initialize();
    m_cutJetFid->initialize();

    m_removeOverlap->initialize();
    m_removeOverlapFid->initialize();

    //m_applyWeight->setCutEventTrigger(m_trigger);
    m_applyWeight->initialize();
    m_calculateVar->initialize();
    m_METCalc->initialize();

    m_cutFlow4l->setCutEventTrigger(m_trigger);
    m_cutFlow4mu->setCutEventTrigger(m_trigger);
    m_cutFlow2mu2e->setCutEventTrigger(m_trigger);
    m_cutFlow2e2mu->setCutEventTrigger(m_trigger);
    m_cutFlow4e->setCutEventTrigger(m_trigger);

    m_cutFlow4l->initialize();
    m_cutFlow4mu->initialize();
    m_cutFlow2mu2e->initialize();
    m_cutFlow2e2mu->initialize();
    m_cutFlow4e->initialize();

    // Initialization of the output trees
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        OutputTree4l* outTree
            =  new OutputTree4l(m_eventCont->outputBaseName, (sysListItr).name(), m_eventCont->fileName);

        if(m_doNormSys) outTree->setupVarsNormSys(m_sysNormList);
        if(m_doMETSys) outTree->setupVarMETSys(m_sysMETList);

        outTree->setIsMC(m_eventCont->isMC);
        if(m_eventCont->isMC)
        {
            // Check if this cross-section is avaliable in the tool
            Int_t DSID = m_eventCont->getDSID();
            // Some truth derivation are weird... they store DSID in runNumber
            // Max provided this fix
            // if (m_eventCont->m_isDAODTRUTH && DSID == 0) DSID = m_eventCont->eventInfo->runNumber();        
            if(m_eventCont->isMC) outTree->setRunNumber(DSID);
        }
        // If data
        if(!m_eventCont->isMC) outTree->addDataSpecificVar();
        // If Trigger Study
        if(m_doTrigStudy) outTree->addTriggerSpecificVar();
        // If calculating Theory systematics
        if(getCmdArg("addTheoryVar") == "true") outTree->addVariationSpecificVar(); 


        // If going a full egamma set, remove extra variables
        if(hasCmdArg("fullEgammaSys"))
        {
            if(getCmdArg("fullEgammaSys") == "true")
            {
                outTree->removeFullEgammaSysVar();
                LOG(logWARNING) << "Analysis4l::initialize() - Doing full egamma sys... remove extraVars";
            }
        }
        LOG(logINFO) << "Add Scale/PDF weights: " << getCmdArg("addTheoryVar") ;
        
        outTree->initialize();
        m_outTreeMap[sysListItr] = (OutputTree*) outTree;
    }

    m_BDTtool = ToolHandle<IH4lBDTWeights>("H4lBDTWeights");
    if(m_BDTtool.retrieve().isFailure())
    {
        LOG(logERROR) <<"Analysis4l::Analysis4l() - cannot retrieve IH4lBDTWeights";
        exit(1);
    }

}

/// Event preselection cuts are implemented here
/// Expected cuts: dataPreselection, selection and trigger cuts
Bool_t Analysis4l::eventPreSelection()
{
    //if(m_eventCont->isMC)
    //{
    //    m_eventCont->outTree->updateHistVar("truthQuadType", m_truthHelper->getTruthHiggsType());
    //}
    updateCutFlow(cutFlow::Total);

    // Data Preselection cut
    if(!m_dataPreSel->passCut()) return false;
    updateCutFlow(cutFlow::DataPreselection);

    // Preselection cut
    if(!m_preSel->passCut()) return false;
    updateCutFlow(cutFlow::Preselection);

    // Trigger
    // This to speed up the systematic jobs
    // Only apply the trigger at the very end
    if(m_forAcceptanceChallenge)
    {
        if(!m_trigger->passCut()) return false;
        updateCutFlow(cutFlow::Trigger);
    }
    return true;
}


void Analysis4l::clearVars()
{
    AnalysisBase::clearVars();

    m_cutMuon->clearVars();
    m_cutElectron->clearVars();
    m_cutJet->clearVars();
    m_cutJetFid->clearVars();

    m_removeOverlap->clearVars();
    m_removeOverlapFid->clearVars();

    m_cutFlow4l->clearVars();
    m_cutFlow4mu->clearVars();
    m_cutFlow2mu2e->clearVars();
    m_cutFlow2e2mu->clearVars();
    m_cutFlow4e->clearVars();

    m_applyWeight->clearVars();
    m_calculateVar->clearVars();

    m_truthHelper->clearVars();
    m_METCalc->clearVars();

    m_higgsCandList.clear();

    m_higgs = 0;

}


void Analysis4l::selectPhyObjects()
{

    // Cut particle level
    m_cutMuon->setParticles(m_muonList);
    m_cutMuon->process();

    m_cutElectron->setParticles(m_electronList);
    m_cutElectron->process();

    m_cutJet->setParticles(m_jetList);
    m_cutJet->process();

    m_cutJetFid->setParticles(m_jetList);
    m_cutJetFid->process();

    // Overlap removal
    m_removeOverlap->setElectrons(m_cutElectron->getParticles());
    m_removeOverlap->setMuons(m_cutMuon->getParticles());
    m_removeOverlap->setJets(m_cutJet->getParticles());
    m_removeOverlap->process();


    // For Fiducial
    m_removeOverlapFid->setElectrons(m_cutElectron->getParticles());
    m_removeOverlapFid->setMuons(m_cutMuon->getParticles());
    m_removeOverlapFid->setJets(m_cutJetFid->getParticles());
    m_removeOverlapFid->process();

    // update the numbers for muons
    m_cutMuon->updateCutFlow      (m_removeOverlap->getMuons().size(),      muCut::OverLap);
    m_cutElectron->updateCutFlow  (m_removeOverlap->getElectrons().size(),  elCut::OverLap);
    m_cutJet->updateCutFlow       (m_removeOverlap->getJets().size(),       jetCut::OverLap);
    m_cutJetFid->updateCutFlow    (m_removeOverlapFid->getJets().size(),    jetCut::OverLap);

    m_eventCont->outTree->updateHistVar("nPassMuHist", m_removeOverlap->getMuons().size());
    m_eventCont->outTree->updateHistVar("nPassElHist", m_removeOverlap->getElectrons().size());
    m_eventCont->outTree->updateHistVar("nPassJetHist", m_removeOverlap->getJets().size());
    m_eventCont->outTree->updateHistVar("nPassPhotonHist", m_photonList.size());


    // Just set the vars for the METCalc. It is internally processed
    m_METCalc->setElParticles(m_removeOverlap->getMETElectrons());
    m_METCalc->setMuParticles(m_removeOverlap->getMETMuons());
    m_METCalc->setJetParticles(m_jetList); // need the full jets
}

Bool_t Analysis4l::eventSelection()
{
    // check the bad jets
    auto jetCollection = m_removeOverlap->getJets();

    for(const auto& jet: jetCollection)
    {
        if(jet->getParticle()->auxdecor<int>("badJet") == 0)
        {
            LOG(logDEBUG)<<"Reject event due to bad jet";
            LOG(logDEBUG)<<"jet pt: "<<jet->getParticle()->pt()/1000;
            return false;
        }
    }

    // Cut for the quadlepton for each flavour
    // This is to mimic the run 1 type selection
    m_cutFlow4mu->setMuons(m_removeOverlap->getMuons());
    m_cutFlow4mu->setElectrons(m_removeOverlap->getElectrons());
    m_cutFlow4mu->process();

    m_cutFlow2e2mu->setMuons(m_removeOverlap->getMuons());
    m_cutFlow2e2mu->setElectrons(m_removeOverlap->getElectrons());
    m_cutFlow2e2mu->process();

    m_cutFlow2mu2e->setMuons(m_removeOverlap->getMuons());
    m_cutFlow2mu2e->setElectrons(m_removeOverlap->getElectrons());
    m_cutFlow2mu2e->process();

    m_cutFlow4e->setMuons(m_removeOverlap->getMuons());
    m_cutFlow4e->setElectrons(m_removeOverlap->getElectrons());
    m_cutFlow4e->process();

    // If any of the cutflow has a candidate quad, then apply the trigger
    // This is really to save time in the trigger decision
    // Only apply the trigger at the very end
    if(!m_forAcceptanceChallenge)
    {
        if(!m_trigger->passCut()) return false;
        updateCutFlow(cutFlow::Trigger);
    }

    // For run 1 type selection
    /*    vector<ParticleQuadlepton*> higgsVec;
          higgsVec = m_cutFlow4mu->getHiggsVec();
          if(higgsVec.size() > 1)
          {
          LOG(logERROR)<<"Too many candidates for 4mu";
          LOG(logERROR)<<"Candidates: "<<higgsVec.size();
          exit(1);
          }
          else if(higgsVec.size() == 1 && !m_higgs)
          {
          m_higgs = higgsVec[0];
          m_cutFlow4mu->updateCutFlow(cutFlow::Final, 1);
          }

          higgsVec = m_cutFlow2e2mu->getHiggsVec();
          if(higgsVec.size() > 1)
          {
          LOG(logERROR)<<"Too many candidates for 2e2mu";
          LOG(logERROR)<<"Candidates: "<<higgsVec.size();
          exit(1);
          }
          else if(higgsVec.size() == 1 && !m_higgs)
          {
          m_higgs = higgsVec[0];
          m_cutFlow2e2mu->updateCutFlow(cutFlow::Final, 1);
          }

          higgsVec = m_cutFlow2mu2e->getHiggsVec();
          if(higgsVec.size() > 1)
          {
          LOG(logERROR)<<"Too many candidates for 2mu2e";
          LOG(logERROR)<<"Candidates: "<<higgsVec.size();
          exit(1);
          }
          else if(higgsVec.size() == 1 && !m_higgs)
          {
          m_higgs = higgsVec[0];
          m_cutFlow2mu2e->updateCutFlow(cutFlow::Final, 1);
          }

          higgsVec = m_cutFlow4e->getHiggsVec();
          if(higgsVec.size() > 1)
          {
          LOG(logERROR)<<"Too many candidates for 4e";
          LOG(logERROR)<<"Candidates: "<<higgsVec.size();
          exit(1);
          }
          else if(higgsVec.size() == 1 && !m_higgs)
          {
          m_higgs = higgsVec[0];
          m_cutFlow4e->updateCutFlow(cutFlow::Final, 1);
          }

          if(!m_higgs) return false;
          */


    // For run 1 type selection
    vector<ParticleQuadlepton*> higgsVec4mu;
    vector<ParticleQuadlepton*> higgsVec2mu2e;
    vector<ParticleQuadlepton*> higgsVec2e2mu;
    vector<ParticleQuadlepton*> higgsVec4e;

    higgsVec4mu = m_cutFlow4mu->getHiggsVec();
    if(higgsVec4mu.size() > 0 && !m_higgs)
    {
        m_higgs = higgsVec4mu[0];
        m_cutFlow4mu->updateCutFlow(cutFlow::Final, 1);
    }
    // if the higgs that passed the selection is the one not with the closest mZ1mZ2 reject it
    if(m_higgs && !m_higgs->getMetadataInt("isNominal")) m_higgs = 0;

    higgsVec2e2mu = m_cutFlow2e2mu->getHiggsVec();
    if(higgsVec2e2mu.size() > 0  && !m_higgs)
    {
        m_higgs = higgsVec2e2mu[0];
        m_cutFlow2e2mu->updateCutFlow(cutFlow::Final, 1);
    }
    // if the higgs that passed the selection is the one not with the closest mZ1mZ2 reject it
    if(m_higgs && !m_higgs->getMetadataInt("isNominal")) m_higgs = 0;

    higgsVec2mu2e = m_cutFlow2mu2e->getHiggsVec();
    if(higgsVec2mu2e.size() > 0 && !m_higgs)
    {
        m_higgs = higgsVec2mu2e[0];
        m_cutFlow2mu2e->updateCutFlow(cutFlow::Final, 1);
    }
    // if the higgs that passed the selection is the one not with the closest mZ1mZ2 reject it
    if(m_higgs && !m_higgs->getMetadataInt("isNominal")) m_higgs = 0;

    higgsVec4e = m_cutFlow4e->getHiggsVec();
    if(higgsVec4e.size() > 0 && !m_higgs)
    {
        m_higgs = higgsVec4e[0];
        m_cutFlow4e->updateCutFlow(cutFlow::Final, 1);
    }
    // if the higgs that passed the selection is the one not with the closest mZ1mZ2 reject it
    if(m_higgs && !m_higgs->getMetadataInt("isNominal")) m_higgs = 0;


    m_higgsCandList.insert(m_higgsCandList.end(), higgsVec4mu.begin(), higgsVec4mu.end() );
    m_higgsCandList.insert(m_higgsCandList.end(), higgsVec2e2mu.begin(), higgsVec2e2mu.end() );
    m_higgsCandList.insert(m_higgsCandList.end(), higgsVec2mu2e.begin(), higgsVec2mu2e.end() );
    m_higgsCandList.insert(m_higgsCandList.end(), higgsVec4e.begin(), higgsVec4e.end() );

    if(!m_higgs) return false;


    return true;
}

void Analysis4l::calcVars()
{
    LOG(logDEBUG)<<"------------------- calculating for the nominal quad -------------------";
    // Calculate the nominal higgs info
    calcHiggsVars(m_higgs, 0 ,1);
    LOG(logDEBUG)<<"------------------- done calculating for the nominal quad -------------------";


    LOG(logDEBUG)<<"------------------- calculating for the best ME quad -------------------";    
    // Check if there was an extra lepton event
    bool checkExtraLep = m_calculateVar->isExtraLepton();
    if(checkExtraLep)
    {
        ParticleQuadlepton* currQuad = 0;
        double MECurr = -1 * std::numeric_limits<double>::infinity();

        for(auto quad: m_higgsCandList)
        {
            vector<const xAOD::IParticle*> particleList;
            // Getting the leptons
            for (Int_t i = 0; i < (Int_t) quad->getLepSize(); i++)
            {
                particleList.push_back(quad->getLep(i)->getParticle());
            }

            // Set input
            m_BDTtool->setBDTInputs(particleList[0],
                    particleList[1],
                    particleList[2],
                    particleList[3],
                    -999,
                    false);

            double ME = m_BDTtool->getSignalME();

            if(ME > MECurr)
            {
                MECurr = ME;
                currQuad = quad;
            }

            if(m_eventCont->isDebug)
            {
                LOG(logDEBUG)<<"\033[35m"<<"--------------";
                LOG(logDEBUG)<<"Finding best extra Quad ";
                if(m_eventCont->isDebug) quad->printDebug();
                LOG(logDEBUG)<<"Signal ME: "<<ME;

                LOG(logDEBUG)<<"\033[35m"<<"--------------";

            }
        } 

        if(!currQuad)
        {
            LOG(logERROR)<<"Analysis4l::calcVars() - there is an extra lep in this event but we didn't select a quad based on the ME pairing";
            LOG(logERROR)<<"This shouldn't ever happen, please check";
        }
        if(m_eventCont->isDebug)
        {
            LOG(logDEBUG)<<"\033[35m"<<"--------------";
            LOG(logDEBUG)<<"Best extra Quad ";
            if(m_eventCont->isDebug) currQuad->printDebug();
            LOG(logDEBUG)<<"Signal ME: "<<MECurr;

            LOG(logDEBUG)<<"\033[35m"<<"--------------";

        }

        // Clear the calculate classes and weight class
        m_applyWeight->clearVars();
        m_calculateVar->clearVars();
        m_truthHelper->clearVars();
        m_METCalc->clearVars();

        // Just set the vars for the METCalc. It is internally processed
        m_METCalc->setElParticles(m_removeOverlap->getMETElectrons());
        m_METCalc->setMuParticles(m_removeOverlap->getMETMuons());
        m_METCalc->setJetParticles(m_jetList); // need the full jets

        // Store the quad from ME based pairing
        calcHiggsVars(currQuad, 1, 0);
    } 
    LOG(logDEBUG)<<"------------------- done calculating for the best ME quad -------------------";    

}


void Analysis4l::calcHiggsVars(ParticleQuadlepton* currHiggs, int candIndex, int isNominal)
{
    // To calculate the variables in the minitree
    m_calculateVar->setHiggs(currHiggs);

    m_calculateVar->setJets(m_removeOverlap->getJets());
    m_calculateVar->setFidJets(m_removeOverlapFid->getJets());
    m_calculateVar->setMuon(m_removeOverlap->getMuons());
    m_calculateVar->setElectron(m_removeOverlap->getElectrons());

    m_calculateVar->setCalElCont(m_smearEgamma->getCalElectronCont());
    m_calculateVar->setCalPhCont(m_smearEgamma->getCalPhotonCont());
    m_calculateVar->process();

    if(m_eventCont->outTree->isIntVar("prod_type"))
    {
        Int_t prodType = m_eventCont->outTree->getIntVar("prod_type");
        // Update the production type numbers
        if(currHiggs->getQuadType() == QuadleptonType::_4mu)
        {
            m_cutFlow4mu->updateCategory(prodType);
        }
        else if(currHiggs->getQuadType() == QuadleptonType::_2mu2e)
        {
            m_cutFlow2mu2e->updateCategory(prodType);
        }
        else if(currHiggs->getQuadType() == QuadleptonType::_2e2mu)
        {
            m_cutFlow2e2mu->updateCategory(prodType);
        }
        else if(currHiggs->getQuadType() == QuadleptonType::_4e)
        {
            m_cutFlow4e->updateCategory(prodType);
        }
    }

    // This is a nominal quad... Update this info in the minitree
    m_eventCont->outTree->updateVar<double>("w_couplings", isNominal);
    m_eventCont->outTree->updateIntVar("cand_index", candIndex);
    m_eventCont->outTree->updateIntVar("hasExtraLepNominal", m_calculateVar->isExtraLepton());

    // This is a hack - remove it later for easier use
    if(candIndex > 0) // we know that the nominal quad was an extra lep event
    {
        m_eventCont->outTree->updateIntVar("hasExtraLepNominal", 1);
    }

    // Weights
    m_applyWeight->setJets(m_removeOverlap->getJets());
    m_applyWeight->setFailJVTJets(m_cutJet->getFailJVTJets());
    m_applyWeight->fillWeight(currHiggs);
    if(getCmdArg("addTheoryVar") == "true") m_applyWeight->fillTheoryVariationWeight();

    // If doing norm sys
    if(m_doNormSys)
    {
        for(auto sys:m_sysNormList)
        {
            m_eventCont->m_currVariation = sys;
            tool4l->updateToolVariation();
            m_applyWeight->clearVars();
            m_applyWeight->setJets(m_removeOverlap->getJets());
            m_applyWeight->setFailJVTJets(m_cutJet->getFailJVTJets());            
            m_applyWeight->fillWeightSys(currHiggs, sys);
        }
        // we know that there is only one in the sysList and it is the nominal one for now
        m_eventCont->m_currVariation = m_eventCont->m_sysList[0];
        tool4l->updateToolVariation();
    }

    if(m_doMETSys)
    {
        for(auto sys:m_sysMETList)
        {
            m_eventCont->m_currVariation = sys;
            tool4l->updateToolVariation();
            // Update the MEt tool
            m_METCalc->clearVars();
            m_METCalc->setElParticles(m_removeOverlap->getMETElectrons());
            m_METCalc->setMuParticles(m_removeOverlap->getMETMuons());
            m_METCalc->setJetParticles(m_jetList); // need the full jets
            m_calculateVar->fillMET(sys.name());
        }

        // we know that there is only one in the sysList and it is the nominal one for now
        m_eventCont->m_currVariation = m_eventCont->m_sysList[0];
        tool4l->updateToolVariation();
    }

    if(m_doTrigStudy)
    {
        m_calculateVar->setSingleTrigger(m_trigger);
        m_calculateVar->fillTriggerVars();
    }
    m_eventCont->outTree->fillTree(OutputTreeType::NA);
}


void Analysis4l::printCutFlow()
{
    m_cutMuon->printCutFlow();
    m_cutElectron->printCutFlow();
    m_cutJet->printCutFlow();
    m_cutJetFid->printCutFlow();

    m_removeOverlap->printCutFlow();
    m_cutFlow4mu->printCutFlow();
    m_cutFlow2e2mu->printCutFlow();
    m_cutFlow2mu2e->printCutFlow();
    m_cutFlow4e->printCutFlow();
}

// To update the cutflow
void Analysis4l::updateCutFlow(Int_t cutLevel, Int_t valToAdd)
{
    m_cutFlow4l->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow4mu->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow2mu2e->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow2e2mu->updateCutFlow(cutLevel, valToAdd);
    m_cutFlow4e->updateCutFlow(cutLevel, valToAdd);

    if(cutLevel == cutFlow::Total)
    {
        m_cutMuon->updateCutFlow(m_muonList.size(), cutLevel);
        m_cutElectron->updateCutFlow(m_electronList.size(), cutLevel);
        m_cutJet->updateCutFlow(m_jetList.size(), cutLevel);
        m_cutJetFid->updateCutFlow(m_jetList.size(), cutLevel);
    }
    else if(cutLevel == cutFlow::Preselection || cutLevel == cutFlow::Trigger)
    {
        m_cutMuon->updateCutFlow(m_muonList.size(), cutLevel-1);
        m_cutElectron->updateCutFlow(m_electronList.size(), cutLevel-1);
        m_cutJet->updateCutFlow(m_jetList.size(), cutLevel-1);
        m_cutJetFid->updateCutFlow(m_jetList.size(), cutLevel-1);
    }
}

void Analysis4l::updateHistCutFlow()
{
    m_eventCont->outTree->updateHistVar("mucutFlowHist",    m_cutMuon->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("elcutFlowHist",    m_cutElectron->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("jetcutFlowHist",   m_cutJet->getRawCutFlow());

    m_eventCont->outTree->updateHistVar("4lcutFlowHist",    m_cutFlow4l->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("4mucutFlowHist",   m_cutFlow4mu->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("2mu2ecutFlowHist", m_cutFlow2mu2e->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("2e2mucutFlowHist", m_cutFlow2e2mu->getRawCutFlow());
    m_eventCont->outTree->updateHistVar("4ecutFlowHist",    m_cutFlow4e->getRawCutFlow());


    m_eventCont->outTree->updateHistVar("4mucutFlowWHist",   m_cutFlow4mu->getWeightedCutFlow());
    m_eventCont->outTree->updateHistVar("2mu2ecutFlowWHist", m_cutFlow2mu2e->getWeightedCutFlow());
    m_eventCont->outTree->updateHistVar("2e2mucutFlowWHist", m_cutFlow2e2mu->getWeightedCutFlow());
    m_eventCont->outTree->updateHistVar("4ecutFlowWHist",    m_cutFlow4e->getWeightedCutFlow());
}

void Analysis4l::updateEvtsProc()
{
    m_applyWeight->getSampleOlpWeight();
    // To keep track number of event in the histrogram
    // This is need for normalization for the overall minitree
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 1, 1); // Raw count
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("CountingHist", 2, m_applyWeight->getEventWeight()); // Weight count

    // Just to force the pileup tool to run and fill the corrected averageInteractionsPerInteraction for data
    m_applyWeight->getPileUpWeight();

    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("pileUpHist", m_eventCont->eventInfo->auxdata< float >("corrected_averageInteractionsPerCrossing"), 1); // Raw count
    if(m_eventCont->outTree) m_eventCont->outTree->updateHistVar("pileUpWeightHist", m_eventCont->eventInfo->auxdata< float >("corrected_averageInteractionsPerCrossing"), m_applyWeight->getPileUpWeight()); // Weight count
}

// This adds the the relavant systematic sets
// for the job
void Analysis4l::addSystematicsSet()
{
    // Check if there is any normalization systematic request
    for(auto st: m_sysPattern)
    {
        if(st.Contains("Norm")) m_doNormSys = true;
        if(st.Contains("MET")) m_doMETSys = true;
    }

    // Currently normalzation + other systematic in one job is not supported
    if(m_doNormSys && m_sysPattern.size() > 1)
    {
        LOG(logERROR)<<"Analysis4l::addSystematicsSet() - Normalization systematics requested in addition to other systematics";
        LOG(logERROR)<<"This behaviour is currently not supported";
        exit(1);
    }

    // Currently MET + other systematic in one job is not supported
    if(m_doMETSys && m_sysPattern.size() > 1)
    {
        LOG(logERROR)<<"Analysis4l::addSystematicsSet() - MET systematics requested in addition to other systematics";
        LOG(logERROR)<<"This behaviour is currently not supported";
        exit(1);
    }


    // If not a normalization job, just do the default behaviour
    if(!m_doNormSys && !m_doMETSys)
    {
        AnalysisBase::addSystematicsSet();
        return;
    }

    if(m_doNormSys)
    {
        addNormSystematicsSet();
        return;
    }
    if(m_doMETSys)
    {
        addMETSystematicsSet();
        return;
    }


}

// Add the norm systematics
void Analysis4l::addNormSystematicsSet()
{
    // If norm, first make sure that the nominal job is being run
    m_eventCont->m_sysList.push_back(CP::SystematicSet());

    vector<TString> normSysList;
    normSysList.push_back("EL_EFF*");
    normSysList.push_back("MUON_EFF*");
    normSysList.push_back("MUON_ISO*");
    normSysList.push_back("MUON_TTVA*");
    normSysList.push_back("HOEW_*");
    normSysList.push_back("HOQCD_*");
    normSysList.push_back("PRW_DATASF_*");
    //normSysList.push_back("JET_Jvt*"); // due to random dropping this is now a shape systematic
    normSysList.push_back("FT_EFF*");

    // Systematic registry
    // loop over systematics registry:
    const CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
    const CP::SystematicSet& recommendedSystematics = registry.recommendedSystematics();
    // get list of recommended systematics
    vector<CP::SystematicSet> sysList  = CP::make_systematics_vector(recommendedSystematics);

    // Loop over all the systematics in the registry
    for(auto sysListItr:sysList)
    {
        // Loop over all the normalization systematic to see if it in the list
        // if yes, include it in the list of norm sys to run
        for(auto sysName:normSysList)
        {
            if(isPatternMatch(sysListItr.name(), sysName.Data()) && (sysListItr).name().size() > 0)
            {
                m_sysNormList.push_back(sysListItr);
            }
        }
    }
    // Listing the variations configured for this job
    LOG(logINFO)<<"Norm Variation configured for this job";
    for (auto sysListItr:m_sysNormList){
        if((sysListItr).name()=="") LOG(logINFO)<< "Nominal (no syst) ";
        else LOG(logINFO) << "Systematic: " << (sysListItr).name();
    }
}

bool Analysis4l::isPatternMatch(const std::string varName, const std::string pattern)
{
    const boost::regex ex(boost::replace_all_copy(pattern, "*", "\\S+"));
    string::const_iterator start, end;
    start = varName.begin();
    end = varName.end();
    boost::match_results<std::string::const_iterator> what;
    boost::match_flag_type flags = boost::match_default;

    if(boost::regex_search(start, end, what, ex, flags)) return true;
    return false;

}


// Add the norm systematics
void Analysis4l::addMETSystematicsSet()
{
    // If norm, first make sure that the nominal job is being run
    m_eventCont->m_sysList.push_back(CP::SystematicSet());

    vector<TString> METSysList;
    METSysList.push_back("MET_JetTrk_ScaleDown");
    METSysList.push_back("MET_JetTrk_ScaleUp");
    METSysList.push_back("MET_SoftTrk_ResoPara");
    METSysList.push_back("MET_SoftTrk_ResoPerp");
    METSysList.push_back("MET_SoftTrk_ScaleDown");
    METSysList.push_back("MET_SoftTrk_ScaleUp");


    // Systematic registry
    // loop over systematics registry:
    const CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
    const CP::SystematicSet& recommendedSystematics = registry.recommendedSystematics();
    // get list of recommended systematics
    vector<CP::SystematicSet> sysList  = CP::make_systematics_vector(recommendedSystematics);

    // Loop over all the systematics in the registry
    for(auto sysListItr:sysList)
    {
        // Loop over all the normalization systematic to see if it in the list
        // if yes, include it in the list of norm sys to run
        for(auto sysName:METSysList)
        {
            if(sysName.Contains((sysListItr).name()) && (sysListItr).name().size() > 0)
            {
                m_sysMETList.push_back(sysListItr);
            }
        }
    }
    // Listing the variations configured for this job
    LOG(logINFO)<<"MET Variation configured for this job";
    for (auto sysListItr:m_sysNormList){
        if((sysListItr).name()=="") LOG(logINFO)<< "Nominal (no syst) ";
        else LOG(logINFO) << "Systematic: " << (sysListItr).name();
    }
}

void Analysis4l::fillMetaData()
{
    string productionRelease = "";
    string amiTag = "";
    string dataType = "";
    string geometryVersion = "";
    string conditionsTag = "";

    if (m_eventCont->getEvent()->containsMeta<xAOD::FileMetaData>("FileMetaData")) 
    {
        const xAOD::FileMetaData* fmd = 0;
        if(m_eventCont->getEvent()->retrieveMetaInput(fmd, "FileMetaData"))
        {
            LOG(logINFO)<<"fillMetaData: metaData found";

            fmd->value(xAOD::FileMetaData::productionRelease, productionRelease);
            fmd->value(xAOD::FileMetaData::amiTag, amiTag);
            fmd->value(xAOD::FileMetaData::dataType, dataType);
            fmd->value(xAOD::FileMetaData::geometryVersion, geometryVersion);
            fmd->value(xAOD::FileMetaData::conditionsTag, conditionsTag);

        }
    }

    // Fill in the metaData
    // Initialization of the output trees
    for (auto sysListItr:m_eventCont->m_sysList)
    {
        OutputTree* outTree = m_outTreeMap[sysListItr];
        outTree->updateMetaData<int>("isMC", m_eventCont->isMC);

        // Tree type
        TString sysName(sysListItr.name());
        if(m_doNormSys)         outTree->updateMetaData<int>("type", miniTreeType::NormSystematic);
        else if(sysName == "")  outTree->updateMetaData<int>("type", miniTreeType::Nominal);
        else                    outTree->updateMetaData<int>("type", miniTreeType::Systematic);

        outTree->updateMetaData<int>("createdBy", 0);


        outTree->updateMetaData<string>("sampleName", m_eventCont->fileName.Data());
        outTree->updateMetaData<string>("version", m_version.Data());
        outTree->updateMetaData<string>("comment", m_comment.Data());
        outTree->updateMetaData<string>("systematicVariation", sysName.Data());

        outTree->updateMetaData<string>("productionRelease", productionRelease);
        outTree->updateMetaData<string>("amiTag", amiTag);
        outTree->updateMetaData<string>("dataType", dataType);
        outTree->updateMetaData<string>("geometryVersion", geometryVersion);
        outTree->updateMetaData<string>("conditionsTag", conditionsTag);

        outTree->fillMetaData();
    }
}

