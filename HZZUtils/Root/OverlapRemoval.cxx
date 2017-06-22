#include "HZZUtils/OverlapRemoval.h"
#include "HZZUtils/H4lMCTruthClassifierDefs.h"
#include "xAODEgamma/EgammaxAODHelpers.h"
#include <algorithm>

float killEvent(unsigned int runNumber, const xAOD::TruthParticleContainer * truthParticles, bool doZZHighMass, bool doZZLowMass, bool doTtbar4l)
{

    static unsigned int lastRunNumber = 0;
    static bool         doOverlap     = true;
    if (runNumber == lastRunNumber && !doOverlap) return 1;

    // removals to be taken care of 
    bool removeZZ = false;
    bool removeZjets = false;
    bool removeTtbar = false;
    bool removeTtbarIncl = false;

    // decide on the removal to be done according to the sample
    if (runNumber == 206618 || runNumber == 206619 || runNumber == 206620) // NOTE: only for testing
        removeZZ = false;//true;
    else if (runNumber == 341106 || runNumber == 341104) // NOTE: only for testing
        removeZjets = false; 
    else if (runNumber == 344171) // NOTE: only for testing
        removeTtbarIncl = false;
    else if ((runNumber >= 187180 && runNumber <= 187183) || runNumber == 361603 || runNumber == 363490 || runNumber == 364250) // take only 4mu/4e/2e2mu  inclusive ZZ samples
        removeZZ = true;
    // Don't apply the filter on low mass filter and high mass filter samples for now
    //else if (runNumber == 345107 || runNumber == 345108)
    //    removeZZ = true;
    else if (runNumber >= 361372 && runNumber <= 361443) // inclusive Zjets samples [Sherpa 2.1]
        removeZjets = true;
    else if ((runNumber >= 363103 && runNumber <= 363122) || (runNumber >= 363361 && runNumber <= 363411)) // new NNPDF30NNLO Z+jets smaples [Sherpa 2.2]
        removeZjets = true;
    else if ((runNumber >= 364100 && runNumber <= 364141)) // new NNPDF30NNLO Z+jets smaples [Sherpa 2.2.1]
        removeZjets = true; 
    else if (runNumber == 410000 ) // ttbar single-lepton filter
        removeTtbarIncl = true;
    else if (runNumber == 410009) // ttbar di-lepton filter
        removeTtbar = true;

    //else if ((runNumber >= 167749 && runNumber <= 167754) || (runNumber >= 167797 && runNumber <= 167802) || (runNumber >= 167809 && runNumber <= 167814) || (runNumber >= 167821 && runNumber <= 167826)) // old inclusive Zjets sample

    // if nothing to be done, just exit here
    if (!removeZZ && !removeZjets && !removeTtbar && !removeTtbarIncl) {
        lastRunNumber = runNumber;
        doOverlap     = false;
        return 1;
    }




    // cuts to be used corresponding to the filter cuts
    double lepPtCut = 0.;
    double lepEtaCut = 5.;
    double lepEtaCut2 = 5.;
    double mll1Cut = 40.;
    double mll2Cut = 8.;
    double minM4lCutLowZZ = 100.e3;
    double maxM4lCutLowZZ = 150.e3;
    double minM4lCutHighZZ = 500.e3;
    double maxM4lCutHighZZ = 50.e6;
    int nLep = 2;
    double lepPtCut2 = 0.;


    // set cuts according to the removal type
    if (removeZZ && !(runNumber == 363490 || runNumber == 345107 || runNumber == 345108 || runNumber == 364250))
    {
        lepPtCut = 3.e3;
        lepEtaCut = 5.;
        lepEtaCut2 = 10.;
        mll1Cut = 0.;
        mll2Cut = 0.;
        minM4lCutLowZZ = 100.e3;
        maxM4lCutLowZZ = 150.e3;
        minM4lCutHighZZ = 500.e3;
        maxM4lCutHighZZ = 50.e6;
    }
    else if (removeZZ && (runNumber == 363490 || runNumber == 345107 || runNumber == 345108 || runNumber == 364250))
    {
        lepPtCut = 3.e3;
        lepEtaCut = 5.;
        lepEtaCut2 = 10.;
        mll1Cut = 0.;
        mll2Cut = 0.;
        minM4lCutLowZZ = 100.e3;
        maxM4lCutLowZZ = 150.e3;
        minM4lCutHighZZ = 300.e3;
        maxM4lCutHighZZ = 50.e6;
    }
    else if (removeZjets)
    {
        lepPtCut = 4.e3;
        lepEtaCut = 3.;
        lepEtaCut2 = 10.;
        mll1Cut = 40.e3;
        mll2Cut = 8.e3;
        minM4lCutLowZZ = 0.;
        maxM4lCutLowZZ = 0.;
        minM4lCutHighZZ = 0.;
        maxM4lCutHighZZ = 0.;
    }
    else if (removeTtbar || removeTtbarIncl)
    {
        lepPtCut = 4.e3;
        lepEtaCut = 4.;
        lepEtaCut2 = 10.;
        mll1Cut = 40.e3;
        mll2Cut = 8.e3;
        minM4lCutLowZZ = 100.e3;
        maxM4lCutLowZZ = 150.e3;
        minM4lCutHighZZ = 500.e3;
        maxM4lCutHighZZ = 50.e6;
    }

    xAOD::TruthParticleContainer::const_iterator tp_itr = truthParticles->begin();
    xAOD::TruthParticleContainer::const_iterator tp_end = truthParticles->end();

    unsigned int lep = 0;
    std::vector <TLorentzVector*> leptons;
    std::vector <TLorentzVector*> leptons_status3; // For Inclusive Sherpa...
    std::vector <int> leptonsId;
    for (;tp_itr !=tp_end; ++tp_itr)
    {
        if ((*tp_itr)->barcode() >= 200000)
            continue;

        if ((*tp_itr)->status() != 1)
            continue;

        if (!(*tp_itr)->isElectron() && !(*tp_itr)->isMuon())// && !(*tp_itr)->isTau())
            continue;

        if ((*tp_itr)->pt() < lepPtCut)
            continue;

        if (fabs((*tp_itr)->eta()) > lepEtaCut)
            continue;

        TLorentzVector * tmpLep = new TLorentzVector();
        //tmpLep->SetPtEtaPhiM((*tp_itr)->pt(), (*tp_itr)->eta(), (*tp_itr)->phi(), (*tp_itr)->m()); //gives diff result than SetPxPyPzE (used in filter)...
        tmpLep->SetPxPyPzE((*tp_itr)->px(), (*tp_itr)->py(), (*tp_itr)->pz(), (*tp_itr)->e());
        leptons.push_back(tmpLep);
        leptonsId.push_back((*tp_itr)->pdgId());
        lep++;
    }

    // Sherpa making life hard...
    if((runNumber == 363490 || runNumber == 345107 || runNumber == 345108 || runNumber == 364250))
    {
        tp_itr = truthParticles->begin();        
        for (;tp_itr !=tp_end; ++tp_itr)
        {
            if ((*tp_itr)->barcode() >= 200000)
                continue;

            if ((*tp_itr)->status() != 3)
                continue;

            if (!(*tp_itr)->isElectron() && !(*tp_itr)->isMuon() && !(*tp_itr)->isTau())
                continue;

            TLorentzVector * tmpLep = new TLorentzVector();
            tmpLep->SetPxPyPzE((*tp_itr)->px(), (*tp_itr)->py(), (*tp_itr)->pz(), (*tp_itr)->e());
            leptons_status3.push_back(tmpLep);
        }
    }


    unsigned int lep2 = 0;
    if (removeZjets)
    {
        tp_itr = truthParticles->begin();
        for (;tp_itr !=tp_end; ++tp_itr)
        {
            if ((*tp_itr)->barcode() >= 200000)
                continue;

            if ((*tp_itr)->status() != 1)
                continue;

            if (!(*tp_itr)->isElectron() && !(*tp_itr)->isMuon())// && !(*tp_itr)->isTau())
                continue;

            if ((*tp_itr)->pt() < lepPtCut)
                continue;

            if (fabs((*tp_itr)->eta()) > lepEtaCut2)
                continue;

            lep2++;
        }
    }

    // Look for Hadronic taus (leptonic ones will be saved by above) that have status!=3 and don't decay to another tau (FSR) 
    tp_itr = truthParticles->begin();
    unsigned int ntau = 0;
    if (removeZjets)
    {
        std::vector <TLorentzVector*> taus;
        for (;tp_itr !=tp_end; ++tp_itr)
        {
            const xAOD::TruthParticle *tau(0), *taunu(0);

            if ((*tp_itr)->barcode() >= 200000)
                continue;

            if (!(*tp_itr)->isTau())
                continue;

            if ((*tp_itr)->status() == 3)
                continue;

            tau = *tp_itr;

            // Loop over children and:
            // 1. Find if it is hadronic (i.e. no decay lepton).
            // 2. Veto tau -> tau (FSR)
            // 3. Store the tau neutino to calculate the visible momentum
            const xAOD::TruthVertex* tauVx = tau->decayVtx();
            if (tauVx)
            {
                const int nTauChild = tauVx->nOutgoingParticles();
                for (int citr = 0; citr < nTauChild; citr++)
                {
                    const xAOD::TruthParticle* tmp(0);
                    tmp = tauVx->outgoingParticle(citr);
                    if (!tmp)
                        continue;

                    if (tmp->barcode() >= 200000)
                        continue;

                    // Ignore tau -> tau (FSR)
                    if ((*tp_itr)->pdgId() == tmp->pdgId()) 
                    {
                        tau = 0;
                        break;
                    }

                    // Ignore leptonic decays
                    if (abs(tmp->pdgId()) == 13 || abs(tmp->pdgId()) == 11) 
                    {
                        tau = 0;
                        break;
                    }

                    // Find tau decay nu
                    if (fabs(tmp->pdgId()) == 16)
                        taunu = tmp;
                }    
            }

            if (tau)
            {
                // Good hadronic decay
                TLorentzVector* tauVisMom = new TLorentzVector;
                if (taunu) tauVisMom->SetPxPyPzE(tau->px() - taunu->px(), tau->py() - taunu->py(), tau->pz() - taunu->pz(), tau->e() - taunu->e());
                else       tauVisMom->SetPxPyPzE(tau->px(), tau->py(), tau->pz(), tau->e());
                if (tauVisMom->Pt() >= 10000. && fabs(tauVisMom->PseudoRapidity()) <= 10.0) 
                    ntau++;
            }
        }
    }

    // Look for two Ws decaying leptonically
    bool ttbarWlep = false;
    if (removeTtbarIncl)
    {
        int N_quark_t    = 0;
        int N_quark_tbar = 0;
        int N_quark_t_all    = 0;
        int N_quark_tbar_all = 0;
        int N_pt_above_cut = 0;

        tp_itr = truthParticles->begin();
        for (;tp_itr !=tp_end; ++tp_itr)
        {
            if (fabs((*tp_itr)->pdgId()) == 6) {
                if ((*tp_itr)->pdgId() == 6) N_quark_t_all++;
                if ((*tp_itr)->pdgId() == -6) N_quark_tbar_all++;

                int n_daughters = 0;
                const xAOD::TruthVertex* decayVtx = (*tp_itr)->decayVtx();

                // Verify if we got a valid pointer and retrieve the number of daughters
                if (decayVtx != 0) n_daughters = decayVtx->nOutgoingParticles();
                // For this analysis we are not interested in t->t MC structures, only in decays
                if (n_daughters >= 2) {
                    for (int citr = 0; citr < n_daughters; citr++)
                    {
                        const xAOD::TruthParticle* child_mcpart(0);
                        child_mcpart = decayVtx->outgoingParticle(citr);
                        if (!child_mcpart)
                            continue;
                        if (fabs(child_mcpart->pdgId()) == 24) {
                            if ((*tp_itr)->pdgId() == 6) N_quark_t++;
                            if ((*tp_itr)->pdgId() == -6) N_quark_tbar++;

                            bool  useNextVertex = false;
                            int n_grandaughters = 0;
                            const xAOD::TruthVertex* w_decayVtx = child_mcpart->decayVtx();

                            while (w_decayVtx) {
                                useNextVertex = false;
                                if (w_decayVtx != 0) n_grandaughters = w_decayVtx->nOutgoingParticles();

                                for (int gitr = 0; gitr < n_grandaughters; gitr++) {
                                    const xAOD::TruthParticle* grandchild_mcpart(0);
                                    grandchild_mcpart = w_decayVtx->outgoingParticle(gitr);
                                    // Check if the W's child is W again. If yes, then move to its next decay vertex in a decay tree
                                    int grandchild_pid = grandchild_mcpart->pdgId();
                                    if (fabs(grandchild_pid) == 24) {
                                        w_decayVtx = grandchild_mcpart->decayVtx();

                                        // If something wrong comes from truth...
                                        if (!w_decayVtx) {
                                            std::cout << "A stable W is found... " << std::endl;;
                                            break;
                                        }

                                        useNextVertex = true;
                                        break;
                                    }
                                    if (abs(grandchild_pid) == 11 || abs(grandchild_pid) == 13 || abs(grandchild_pid) == 15) {
                                        if (grandchild_mcpart->pt() >= lepPtCut2) N_pt_above_cut++;
                                        // W decay lepton is found. Break loop over the decay product particles
                                        break;
                                    }
                                }
                                // If investigation of W's next decay vertex is not required then finish looking for leptons
                                if (!useNextVertex) break;
                            }
                        }
                    }
                }
            }
        }

        if (N_quark_t_all < 1 || N_quark_tbar_all < 1) {
            std::cout << "No t or tbar quarks were found in a (presumably) ttbar event! Event is rejected." << std::endl;
            ttbarWlep = false;
        }
        else if (N_quark_t < 1 || N_quark_tbar < 1) {
            std::cout << "No t or tbar quarks were found decaying to W in a (presumably) ttbar event! Event is rejected. Event dump follows." << std::endl;
            int event = 0;
            //       for (McEventCollection::const_iterator itr = events()->begin(); itr!=events()->end(); ++itr) {
            //         event++;
            //         const HepMC::GenEvent* genEvt = (*itr);
            //         HepMC::GenEvent::particle_const_iterator mcpartItr  = genEvt->particles_begin();
            //         HepMC::GenEvent::particle_const_iterator mcpartItrE = genEvt->particles_end();
            //         int part ( 0 );
            //         for (; mcpartItr != mcpartItrE; ++mcpartItr) {
            //           part++;
            //           HepMC::GenParticle * mcpart = (*mcpartItr);
            //           int pid = mcpart->pdg_id();
            //           std::cout << "In event (from MC collection) " << event << " particle number " << part << " has pdg_id = " << pid << std::endl;
            // 
            //           // retrieve decay vertex
            //           const HepMC::GenVertex * decayVtx = mcpart->end_vertex();
            // 
            //           // verify if we got a valid pointer
            //           if ( decayVtx != 0 ) {
            //             HepMC::GenVertex::particles_in_const_iterator child_mcpartItr  = decayVtx->particles_out_const_begin();
            //             HepMC::GenVertex::particles_in_const_iterator child_mcpartItrE = decayVtx->particles_out_const_end();
            //             int part_child ( 0 );
            //             for (; child_mcpartItr != child_mcpartItrE; ++child_mcpartItr) {
            //               part_child++;
            //               HepMC::GenParticle * child_mcpart = (*child_mcpartItr);
            //               int child_pid = child_mcpart->pdg_id();
            //               std::cout << "          child " << part_child << " with pdg_id = " << child_pid << std::endl;
            //             }
            //           }
            //         }
            //       }
            //       setFilterPassed(false);
            //       return StatusCode::SUCCESS;
            ttbarWlep = false;
        }

        // If NumLeptons is negative (default), accept if Nlep > 0, otherwise only accept an exact match
        if (nLep < 0) {
            if (N_quark_t >= 2 || N_quark_tbar >= 2) {
                std::cout << "More than one t -> W X or tbar -> W X decays found. Event is accepted anyway." << std::endl;
            }
            ttbarWlep = (N_pt_above_cut > 0);
        } else {
            ttbarWlep = (N_pt_above_cut == nLep);
        }
    }

    // check the m4l of the 4-lep events
    bool highMassEvent = false;
    bool lowMassEvent = false;
    bool heavyFlavorEvent = false;
    bool heavyFlavor3lEvent = false;
    bool tt4lEvent = false;
    bool ttbar4lEvent = false;
    bool ttbar2lEvent = false;
    if (lep >= 4 && (removeZZ || removeZjets || ((removeTtbar || removeTtbarIncl) && doTtbar4l)))
    {
        for (unsigned int l1 = 0; l1 < lep; l1++)
        {
            //       for (unsigned int l2 = l1 + 1; l2 < lep; l2++)
            for (unsigned int l2 = 0; l2 < lep; l2++)
            {
                if (l1 == l2)
                    continue;
                //         for (unsigned int l3 = l2 + 1; l3 < lep; l3++)
                for (unsigned int l3 = 0; l3 < lep; l3++)
                {
                    if (l3 == l2 || l3 == l1)
                        continue;
                    //           for (unsigned int l4 = l3 + 1; l4 < lep; l4++)
                    for (unsigned int l4 = 0; l4 < lep; l4++)
                    {
                        if (l4 == l3 || l4 == l2 || l4 == l1)
                            continue;

                        // no check is done in the filter concerning SF OS pairs so this is not needed
                        //             if (leptonsId.at(l1) + leptonsId.at(l2) + leptonsId.at(l3) + leptonsId.at(l4) != 0)
                        //               continue;

                        double m4l = (*leptons.at(l1) + *leptons.at(l2) + *leptons.at(l3) + *leptons.at(l4)).M();
                        //             Info("execute()", "m4l = %f", m4l);

                        if (removeZZ && doZZHighMass && m4l > minM4lCutHighZZ && m4l < maxM4lCutHighZZ)
                            highMassEvent = true;
                        if (removeZZ && doZZLowMass && m4l > minM4lCutLowZZ && m4l < maxM4lCutLowZZ)
                            lowMassEvent = true;

                        double m12 = (*leptons.at(l1) + *leptons.at(l2)).M();
                        double m34 = (*leptons.at(l3) + *leptons.at(l4)).M();
                        double m13 = (*leptons.at(l1) + *leptons.at(l3)).M();
                        double m24 = (*leptons.at(l2) + *leptons.at(l4)).M();
                        double m14 = (*leptons.at(l1) + *leptons.at(l4)).M();
                        double m23 = (*leptons.at(l2) + *leptons.at(l3)).M();
                        if ((std::max(m12, m34) > mll1Cut && std::min(m12, m34) > mll2Cut) || (std::max(m13, m24) > mll1Cut && std::min(m13, m24) > mll2Cut) || (std::max(m14, m23) > mll1Cut && std::min(m14, m23) > mll2Cut))
                        {
                            if (removeZjets)
                                heavyFlavorEvent = true;
                            if ((removeTtbar || removeTtbarIncl) && doTtbar4l)
                                tt4lEvent = true;
                        }
                    }
                }
            }
        }
    }

    // Sherpa making life hard...
    // Roberto and Haider wrote this code... ask if there are questions...
    if((runNumber == 363490 || runNumber == 345107 || runNumber == 345108 || runNumber == 364250))
    {
        double m4l_status3 = 0;

        if(leptons_status3.size() == 4)
        {
            m4l_status3 = (*leptons_status3.at(0) + *leptons_status3.at(1) + *leptons_status3.at(2) + *leptons_status3.at(3)).M();
        }
        else
        {
            Info("execute()", Form("Doing sherpa, but it can't find exactly 4 status 3 leptons... we found %d", leptons_status3.size()));    
        }
        //Info("execute()", Form("m4l %f", m4l_status3));    
        
        if(lowMassEvent && !(m4l_status3 > 100*1000 && m4l_status3 < 300 *1000) ) lowMassEvent = false;

        if(m4l_status3 > 300*1000) highMassEvent = true;
        else highMassEvent = false;

        double incl_lowMass  = 271514.4913;
        double incl_highMass = 376320.8692;
        double lowMass       = 1313223.402;
        double highMass      = 632121.734;
   
        // don't do scaling for now - just remove the overlap, we have a 10M sample now
        //     if(runNumber == 363490 && lowMassEvent)    return incl_lowMass/(incl_lowMass + lowMass);
        //else if(runNumber == 363490 && highMassEvent)   return incl_highMass/(incl_highMass + highMass);

        //else if(runNumber == 345108) return highMass/(incl_highMass + highMass);
        //else if(runNumber == 345107) return lowMass/(incl_lowMass + lowMass);

             if(runNumber == 363490 && lowMassEvent)    return 0;
        else if(runNumber == 363490 && highMassEvent)   return 0;
        else if(runNumber == 364250 && lowMassEvent)    return 0;
        else if(runNumber == 364250 && highMassEvent)   return 0;
        else return 1;
    }



    if (removeZjets && !heavyFlavorEvent && ntau + lep2 >= 3)
        heavyFlavor3lEvent = true;
    if (removeTtbarIncl && doTtbar4l && (tt4lEvent || ttbarWlep))
        ttbar4lEvent = true;
    if (removeTtbar && doTtbar4l && tt4lEvent)
        ttbar4lEvent = true;
    //   if (removeTtbar && !doTtbar4l && ttbarWlep) // NOTE: just for checks - to be removed!!!!
    //     ttbar2lEvent = true;
    if (removeTtbarIncl && !doTtbar4l && ttbarWlep)
        ttbar2lEvent = true;

    if (highMassEvent)
    {
        //Info("execute()", "Event vetoed as a high mass ZZ event");
        return 0;
    }
    else if (lowMassEvent)
    {
        //Info("execute()", "Event vetoed as a low mass ZZ event");
        return 0;
    }
    else if (heavyFlavorEvent)
    {
        //Info("execute()", "Event vetoed as a 4l-filtered 'heavy flavor' event");
        return 0;
    }
    else if (heavyFlavor3lEvent)
    {
        //Info("execute()", "Event vetoed as a 3l-filtered 'heavy flavor' event");
        return 0;
    }
    else if (ttbar2lEvent)
    {
        //     Info("execute()", "Event vetoed as a ttbar '2l' event");
        return 0;
    }
    else if (ttbar4lEvent)
    {
        //     Info("execute()", "Event vetoed as a ttbar '4l' event");
        return 0;
    }
    else
    {
        //     Info("execute()", "Event ======= not vetoed!");
        return 1;
    }
}

