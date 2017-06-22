#include "H4lCutFlow/CalculateVar4lInclusive.h"
using namespace std;

CalculateVar4lInclusive::CalculateVar4lInclusive(EventContainer* eventCont)
{
    // Copying it for local use
    m_eventCont = eventCont;
    m_outTree = 0;
    m_leptonType = "";

    m_MCTruthClassifier = ToolHandle<IMCTruthClassifier>("MCClassifier");
    if(m_MCTruthClassifier.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve MCTruthClassifier";
        exit(1);
    }
    
    m_grl = ToolHandle<IGoodRunsListSelectionTool>("GoodRunsListSelectionTool");
    if(m_grl.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IGoodRunsListSelectionTool";
        exit(1);
    } 
    
    m_cutQuad = new CutLepComb(m_eventCont);
    m_truthHelper = new TruthHelper(m_eventCont);
    
    // BDT tools
    m_BDTtool = ToolHandle<IH4lBDTWeights>("H4lBDTWeights");
    if(m_BDTtool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve IH4lBDTWeights";
        exit(1);
    }
    m_VBFCatMVATool = ToolHandle<ICategoriesMVA>("VBF_ICHEP2016_30GeV_BinptHjj50");
    if(m_VBFCatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VBFCatMVATool";
        exit(1);
    }
    m_VHnoPtHjjCatMVATool = ToolHandle<ICategoriesMVA>("VH_ICHEP2016_30GeV_noptHjj");
    if(m_VHnoPtHjjCatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VHnoPtHjjCatMVATool";
        exit(1);
    }
    m_oneJet_jptetadR_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_ICHEP2016_jptetadR");
    if(m_oneJet_jptetadR_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA oneJet_jptetadR_CatMVATool";
        exit(1);
    }
    m_VBF_TOPO_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_TOPO_Moriond2017");
    if(m_VBF_TOPO_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VBF_TOPO_CatMVATool";
        exit(1);
    }
    m_VBF_Rest_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_Rest_Moriond2017");
    if(m_VBF_Rest_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_VBF_Rest_CatMVATool";
        exit(1);
    }
    m_1J_pt4l_60_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_pT4l_0_60_Moriond2017");
    if(m_1J_pt4l_60_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_1J_pt4l_60_CatMVATool";
        exit(1);
    }
    m_1J_pt4l_120_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_pT4l_0_120_Moriond2017");
    if(m_1J_pt4l_120_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_1J_pt4l_120_CatMVATool";
        exit(1);
    }
    m_1J_pt4l_60_120_CatMVATool = ToolHandle<ICategoriesMVA>("VBF_1j_pT4l_60_120_Moriond2017");
    if(m_1J_pt4l_60_120_CatMVATool.retrieve().isFailure())
    {
        LOG(logERROR) <<"CalculateVar4l::CalculateVar4l() - cannot retrieve ICategoriesMVA m_1J_pt4l_60_120_CatMVATool";
        exit(1);
    }

    clearVars();

}

CalculateVar4lInclusive::~CalculateVar4lInclusive()
{
    delete m_cutQuad;
    delete m_truthHelper;
}

void CalculateVar4lInclusive::process(Bool_t passFidCut)
{
    m_passFidCut = passFidCut;
    // A local copy to limit the amount of typing
    m_outTree = m_eventCont->outTree;
    if(!m_outTree)
    {
        LOG(logERROR)<<"Error: CalculateVar4lInclusive - the output tree has not been specified";
        exit(-1);
    }

    LOG(logDEBUG) << "Lepton Type in Tree set to: " << m_leptonType; 
    // General Variables
    fillGeneralVars();
    
    // Lepton related vars
    fillLeptonVars();
    
    //fill angular vars
    fillAngularVar();

    // Mass related vars
    fillMassVars();
    // Mass BDT
    fillMassBDTVars();
    
    fillCategory();
    
    // Truth vars
    fillPtHRESReweight();
    fillFiducial();
    fillSimpleXS();
    fillCatBDT();

}



void CalculateVar4lInclusive::clearVars() 
{
    // Clearing the variables
    if(m_outTree) m_outTree->clearVars();
    m_leptonType = "";
    
    m_truthHelper->clearVars();

    m_higgs = 0;
    m_higgs_fid = 0;
    
    m_isJetFilled = false;
    
    m_leadingJet = 0;
    m_subLeadingJet = 0;
    m_jetVarFilled = false;

    m_passFidCut = false;
    
    m_phCont = 0;
    m_elCont = 0;
    
    m_elList.clear();
    m_muList.clear();
    m_jetList.clear();

    while(!m_partContainer.empty()) delete m_partContainer.back(), m_partContainer.pop_back();
    
}



// Helper

// To fill in the general information
void CalculateVar4lInclusive::fillGeneralVars()
{
    m_outTree->updateLongIntVar("event", m_eventCont->eventInfo->eventNumber());
    if(m_eventCont->isMC)
    {
        Int_t DSID = m_eventCont->getDSID();
        // Some truth derivation are weird... they store DSID in runNumber
        // Max provided this fix
        // if (m_eventCont->m_isDAODTRUTH && DSID == 0) DSID = m_eventCont->eventInfo->runNumber(); 
        m_outTree->updateIntVar("run",  DSID);
    }
    else
    {
        m_outTree->updateIntVar("run",  m_eventCont->eventInfo->runNumber());
    }
    
    m_outTree->updateIntVar("lbn",  m_eventCont->eventInfo->lumiBlock());



}

// To fill the general lepton vars
void CalculateVar4lInclusive::fillLeptonVars()
{
    std::array<float, 4> lepton_pt    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m     = {{-999, -999, -999, -999}};
    std::array<int, 4> lepton_pdgid  = {{-999, -999, -999, -999}};

    vector<float> ordered_lepton_pt;
    for(int i = 0; i < 4; i++)
    {
        lepton_pt[i]  = m_higgs->getLep(i)->getTLV().Pt()/1000;
        ordered_lepton_pt.push_back(lepton_pt[i]);
        lepton_eta[i] = m_higgs->getLep(i)->getTLV().Eta();
        lepton_phi[i] = m_higgs->getLep(i)->getTLV().Phi();
        lepton_m[i]   = m_higgs->getLep(i)->getTLV().M()/1000;
        lepton_pdgid[i]= m_higgs->getLep(i)->getTruthPID();
    }
    std::sort(ordered_lepton_pt.begin(),ordered_lepton_pt.end(), std::greater<float>());
    m_outTree->updateFloatVar("leading_lepton_pt_fid"+m_leptonType+"_truth", ordered_lepton_pt[0]);
    m_outTree->updateFloatVar("subleading_lepton_pt_fid"+m_leptonType+"_truth", ordered_lepton_pt[1]);

    m_outTree->updateFloatArrayVar("lepton_pt_fid"+m_leptonType+"_truth", lepton_pt);
    m_outTree->updateFloatArrayVar("lepton_pt_fid"+m_leptonType+"_truth", lepton_pt);
    m_outTree->updateFloatArrayVar("lepton_phi_fid"+m_leptonType+"_truth", lepton_phi);
    m_outTree->updateFloatArrayVar("lepton_eta_fid"+m_leptonType+"_truth", lepton_eta);
    m_outTree->updateFloatArrayVar("lepton_m_fid"+m_leptonType+"_truth", lepton_m);
    m_outTree->updateIntArrayVar("lepton_pdgid_fid"+m_leptonType+"_truth", lepton_pdgid);

    if(m_passFidCut) {
        std::array<float, 4> lepton_pt_4l    = {{-999, -999, -999, -999}};
        std::array<float, 4> lepton_phi_4l   = {{-999, -999, -999, -999}};
        std::array<float, 4> lepton_eta_4l   = {{-999, -999, -999, -999}};
        std::array<float, 4> lepton_m_4l     = {{-999, -999, -999, -999}};

        vector<float> ordered_lepton_pt_4l;
        for(int i = 0; i < 4; i++)
        {
            lepton_pt_4l[i]  = m_higgs_fid->getLep(i)->getTLV().Pt()/1000;
            ordered_lepton_pt_4l.push_back(lepton_pt_4l[i]);
            lepton_eta_4l[i] = m_higgs_fid->getLep(i)->getTLV().Eta();
            lepton_phi_4l[i] = m_higgs_fid->getLep(i)->getTLV().Phi();
            lepton_m_4l[i]   = m_higgs_fid->getLep(i)->getTLV().M()/1000;
        }
        std::sort(ordered_lepton_pt_4l.begin(),ordered_lepton_pt_4l.end(), std::greater<float>());
        m_outTree->updateFloatVar("leading_lepton_pt_fid"+m_leptonType+"_4lsel", ordered_lepton_pt_4l[0]);
        m_outTree->updateFloatVar("subleading_lepton_pt_fid"+m_leptonType+"_4lsel", ordered_lepton_pt_4l[1]);

        m_outTree->updateFloatArrayVar("lepton_pt_fid"+m_leptonType+"_4lsel", lepton_pt_4l);
        m_outTree->updateFloatArrayVar("lepton_phi_fid"+m_leptonType+"_4lsel", lepton_phi_4l);
        m_outTree->updateFloatArrayVar("lepton_eta_fid"+m_leptonType+"_4lsel", lepton_eta_4l);
        m_outTree->updateFloatArrayVar("lepton_m_fid"+m_leptonType+"_4lsel", lepton_m_4l);
    }


    auto lepList = m_truthHelper->getFirstFourLeptonsFromHiggs();
    std::array<float, 4> lepton_pt_fR    = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_phi_fR   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_eta_fR   = {{-999, -999, -999, -999}};
    std::array<float, 4> lepton_m_fR     = {{-999, -999, -999, -999}};
    std::array<int, 4> lepton_pdgid_fR  = {{-999, -999, -999, -999}};
    std::array<int, 4> lepton_status_fR  = {{-999, -999, -999, -999}};

    int index = 0;
    for(const auto& lep:lepList)
    {
        lepton_pt_fR[index]     = lep->getTLV().Pt()/1000;
        lepton_eta_fR[index]    = lep->getTLV().Eta();
        lepton_phi_fR[index]    = lep->getTLV().Phi();
        lepton_m_fR[index]      = lep->getTLV().M()/1000;
        lepton_pdgid_fR[index]  = lep->getTruthPID();
        const xAOD::TruthParticle* part = dynamic_cast<const xAOD::TruthParticle*>(lep->getParticle());
        lepton_status_fR[index] = part->status();
        index++;
    }

    m_outTree->updateFloatArrayVar("lepton_pt_fR", lepton_pt_fR);
    m_outTree->updateFloatArrayVar("lepton_eta_fR", lepton_eta_fR);
    m_outTree->updateFloatArrayVar("lepton_phi_fR", lepton_phi_fR);
    m_outTree->updateFloatArrayVar("lepton_m_fR"  , lepton_m_fR);
    m_outTree->updateIntArrayVar("lepton_pdgid_fR", lepton_pdgid_fR);
    m_outTree->updateIntArrayVar("lepton_status_fR", lepton_status_fR);

}


void CalculateVar4lInclusive::fillJetVars()
{
    if(!m_isJetFilled)
    {
        LOG(logERROR)<<"CalculateVar4lInclusive: Jet vector not filled";
        exit(-1);
    }
    
    // Caching the results
    if(m_jetVarFilled) return;
    m_jetVarFilled = true;


    LOG(logDEBUG)<<"Jet list before size: "<<m_jetList.size();
    std::sort (m_jetList.begin(), m_jetList.end(), sortParticleVarPt);
    std::vector<ParticleVar*> bjetList;
    for(unsigned int i = 0; i < m_jetList.size(); i++) {
        int label = -1;
        const xAOD::Jet* jet = dynamic_cast<const xAOD::Jet*>(m_jetList[i]->getParticle());
        jet->getAttribute("ConeTruthLabelID",label);
        LOG(logDEBUG) << "Jet " << i << " has truth cone label " << label;
        if (abs(label) == 5) {
            bjetList.push_back(m_jetList[i]);
        }
    }
    LOG(logDEBUG)<<"Jet list after size: "<<m_jetList.size();
    LOG(logDEBUG)<<"bJet list after size: "<<bjetList.size();

    m_outTree->updateIntVar("n_jets_fid"+m_leptonType+"_truth", m_jetList.size());
    m_outTree->updateIntVar("n_bjets_fid"+m_leptonType+"_truth", bjetList.size());

    std::array<float, 4> jet_pt = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_eta = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_phi = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_m = {{-999, -999, -999, -999}};
 
    int nJets = 4;
    if(m_jetList.size() < 4) nJets = m_jetList.size();

    for(int i = 0; i < nJets; i++)
    {
        jet_pt[i] = m_jetList[i]->getTLV().Pt()/1000;
        jet_eta[i] = m_jetList[i]->getTLV().Eta();
        jet_phi[i] = m_jetList[i]->getTLV().Phi();
        jet_m[i] = m_jetList[i]->getTLV().M()/1000;

        if(i == 0)
        {
            m_outTree->updateFloatVar("leading_jet_pt_fid"+m_leptonType+"_truth", m_jetList[i]->getTLV().Pt()/1000.0);
        }
        else if(i == 1)
        {
            m_outTree->updateFloatVar("subleading_jet_pt_fid"+m_leptonType+"_truth", m_jetList[i]->getTLV().Pt()/1000.0);
        }
    }
    m_outTree->updateFloatArrayVar("jet_pt_fid"+m_leptonType+"_truth", jet_pt);
    m_outTree->updateFloatArrayVar("jet_eta_fid"+m_leptonType+"_truth", jet_eta);
    m_outTree->updateFloatArrayVar("jet_phi_fid"+m_leptonType+"_truth", jet_phi);
    m_outTree->updateFloatArrayVar("jet_m_fid"+m_leptonType+"_truth", jet_m);
    // for rest of the code
    if(m_jetList.size() > 0)
    {
        m_leadingJet = m_jetList[0];
    }
    if(m_jetList.size() > 1)
    {
        m_subLeadingJet = m_jetList[1];
    }

    // If both leading and subleading jets are found
    if (m_jetList.size() >=2 ) {
        Int_t iLeadingJet = 0;
        Int_t iSubleadingJet = 1;
        TLorentzVector combined = m_jetList[iLeadingJet]->getTLV() + m_jetList[iSubleadingJet]->getTLV();

        m_outTree->updateFloatVar("dijet_m_fid"+m_leptonType+"_truth", combined.M()/1000);
        m_outTree->updateFloatVar("dijet_deltaeta_fid"+m_leptonType+"_truth", fabs(m_jetList[iLeadingJet]->getTLV().Eta() - m_jetList[iSubleadingJet]->getTLV().Eta()));

        float dijet_deltaphi = -999;
        if (m_jetList[iLeadingJet]->getTLV().Eta() > m_jetList[iSubleadingJet]->getTLV().Eta()) {
            dijet_deltaphi = m_jetList[iLeadingJet]->getTLV().Phi() - m_jetList[iSubleadingJet]->getTLV().Phi(); 
        }
        if (m_jetList[iLeadingJet]->getTLV().Eta() <= m_jetList[iSubleadingJet]->getTLV().Eta()){
            dijet_deltaphi = m_jetList[iSubleadingJet]->getTLV().Phi() - m_jetList[iLeadingJet]->getTLV().Phi(); 
        }
        if(dijet_deltaphi < 0) dijet_deltaphi = dijet_deltaphi + 2.0*TMath::Pi(); 
        m_outTree->updateFloatVar("dijet_deltaphi_fid"+m_leptonType+"_truth", dijet_deltaphi);
    }

    if(m_passFidCut) {
        m_outTree->updateIntVar("n_jets_fid"+m_leptonType+"_4lsel", m_jetList.size());
       //LOG(logINFO) << "Event " << m_eventCont->eventInfo->eventNumber() << " passed fid cutflow";
        //if(bjetList.size() == 0) LOG(logINFO) << "Event " << m_eventCont->eventInfo->eventNumber() << " has 0 bjets.";
        m_outTree->updateIntVar("n_bjets_fid"+m_leptonType+"_4lsel", bjetList.size());

        m_outTree->updateFloatArrayVar("jet_pt_fid"+m_leptonType+"_4lsel", jet_pt);
        m_outTree->updateFloatArrayVar("jet_eta_fid"+m_leptonType+"_4lsel", jet_eta);
        m_outTree->updateFloatArrayVar("jet_phi_fid"+m_leptonType+"_4lsel", jet_phi);
        m_outTree->updateFloatArrayVar("jet_m_fid"+m_leptonType+"_4lsel", jet_m);

        if (m_leadingJet) {
            m_outTree->updateFloatVar("leading_jet_pt_fid"+m_leptonType+"_4lsel", m_leadingJet->getTLV().Pt()/1000.0);
        }
        
        if (m_subLeadingJet) {
            m_outTree->updateFloatVar("subleading_jet_pt_fid"+m_leptonType+"_4lsel", m_subLeadingJet->getTLV().Pt()/1000.0);
        }
        if (m_jetList.size() >=2 ) {
            Int_t iLeadingJet = 0;
            Int_t iSubleadingJet = 1;
            TLorentzVector combined = m_jetList[iLeadingJet]->getTLV() + m_jetList[iSubleadingJet]->getTLV();

            m_outTree->updateFloatVar("dijet_m_fid"+m_leptonType+"_4lsel", combined.M()/1000);
            m_outTree->updateFloatVar("dijet_deltaeta_fid"+m_leptonType+"_4lsel", fabs(m_jetList[iLeadingJet]->getTLV().Eta() - m_jetList[iSubleadingJet]->getTLV().Eta()));
            float dijet_4l_deltaphi = -999;
            if (m_jetList[iLeadingJet]->getTLV().Eta() > m_jetList[iSubleadingJet]->getTLV().Eta()) {
                dijet_4l_deltaphi = m_jetList[iLeadingJet]->getTLV().Phi() - m_jetList[iSubleadingJet]->getTLV().Phi(); 
            }
            if (m_jetList[iLeadingJet]->getTLV().Eta() <= m_jetList[iSubleadingJet]->getTLV().Eta()){
                dijet_4l_deltaphi = m_jetList[iSubleadingJet]->getTLV().Phi() - m_jetList[iLeadingJet]->getTLV().Phi(); 
            }
            if(dijet_4l_deltaphi < 0) dijet_4l_deltaphi = dijet_4l_deltaphi + 2.0*TMath::Pi(); 
            m_outTree->updateFloatVar("dijet_deltaphi_fid"+m_leptonType+"_4lsel", dijet_4l_deltaphi);
        }

    }   

    //fill truth jets
    const xAOD::JetContainer* truthJetCont = 0;
    if(m_eventCont->m_isAOD || m_eventCont->m_isDAODTRUTH) {
        m_eventCont->getEvent()->retrieve( truthJetCont, "AntiKt4TruthWZJets" ).isSuccess();
    } else { 
        m_eventCont->getEvent()->retrieve( truthJetCont, "AntiKt4TruthJets" ).isSuccess();
    }

    int countJets_20 = 0;
    int countJets_25 = 0;
    int countJets_30 = 0;

    vector<const xAOD::Jet*> jetList;

    for( auto truthJet : *( truthJetCont ) )
    {
        bool overlap = false;
        for(int i = 0; i < 4; i++)
        {
            float deltaR = fabs(xAOD::P4Helpers::deltaR(*truthJet,
                        *m_higgs->getLep(i)->getParticle()));
            if(deltaR < 0.4)
            {
                overlap = true;
                break;
            }
        }
        // For David
        if(!overlap && (truthJet->pt() > 30 * 1000) ) countJets_30++;
        if(!overlap && (truthJet->pt() > 25 * 1000) ) countJets_25++;

        // For Higgs Pt Reweighing
        if(!overlap && (truthJet->pt() > 20 * 1000) )
        {
            countJets_20++;
            jetList.push_back(truthJet);
        }
    }
    m_outTree->updateIntVar("n_jets_truth_20", countJets_20);
    m_outTree->updateIntVar("n_jets_truth_25", countJets_25);
    m_outTree->updateIntVar("n_jets_truth_30", countJets_30);

    std::array<float, 4> jet_pt_truth    = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_phi_truth   = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_eta_truth   = {{-999, -999, -999, -999}};
    std::array<float, 4> jet_m_truth     = {{-999, -999, -999, -999}};

    for(Int_t i = 0; i < (Int_t) jetList.size(); i++)
    {
        // Can only store 4 jets at the momemtn
        if(i > 3) break;

        TLorentzVector l = jetList[i]->p4();

        jet_pt_truth[i]     = l.Pt() / 1000.;
        jet_phi_truth[i]    = l.Phi();
        jet_eta_truth[i]    = l.Eta();
        jet_m_truth[i]      = jetList[i]->m()  / 1000.;

    }

    m_outTree->updateFloatArrayVar("jet_pt_truth", jet_pt_truth);
    m_outTree->updateFloatArrayVar("jet_phi_truth", jet_phi_truth);
    m_outTree->updateFloatArrayVar("jet_eta_truth", jet_eta_truth);
    m_outTree->updateFloatArrayVar("jet_m_truth", jet_m_truth);


}

void CalculateVar4lInclusive::fillAngularVar()
{
    Float_t cthstr = -999;
    Float_t phi1 = -999;
    Float_t cth1 = -999;
    Float_t cth2 = -999;
    Float_t phi = -999;

    // This function requires z1 lep neg, z1 lep plus, z2 lep neg, z2 lep plus
    // weird ordering... sigh
    HZZUtils::helicityAngles(m_higgs->getLep(1)->getTLV(),
            m_higgs->getLep(0)->getTLV(),
            m_higgs->getLep(3)->getTLV(),
            m_higgs->getLep(2)->getTLV(),
            cthstr, phi1, cth1, cth2, phi);

    m_outTree->updateFloatVar("cthstr_fid"+m_leptonType+"_truth", cthstr);
    m_outTree->updateFloatVar("phi1_fid"+m_leptonType+"_truth", phi1);
    m_outTree->updateFloatVar("cth1_fid"+m_leptonType+"_truth", cth1);
    m_outTree->updateFloatVar("cth2_fid"+m_leptonType+"_truth", cth2);
    m_outTree->updateFloatVar("phi_fid"+m_leptonType+"_truth", phi);
    
    if(m_passFidCut) {
        Float_t cthstr_4l = -999;
        Float_t phi1_4l = -999;
        Float_t cth1_4l = -999;
        Float_t cth2_4l = -999;
        Float_t phi_4l = -999;
        HZZUtils::helicityAngles(m_higgs_fid->getLep(1)->getTLV(),
                m_higgs_fid->getLep(0)->getTLV(),
                m_higgs_fid->getLep(3)->getTLV(),
                m_higgs_fid->getLep(2)->getTLV(),
                cthstr_4l, phi1_4l, cth1_4l, cth2_4l, phi_4l);

        m_outTree->updateFloatVar("cthstr_fid"+m_leptonType+"_4lsel", cthstr_4l);
        m_outTree->updateFloatVar("phi1_fid"+m_leptonType+"_4lsel", phi1_4l);
        m_outTree->updateFloatVar("cth1_fid"+m_leptonType+"_4lsel", cth1_4l);
        m_outTree->updateFloatVar("cth2_fid"+m_leptonType+"_4lsel", cth2_4l);
        m_outTree->updateFloatVar("phi_fid"+m_leptonType+"_4lsel", phi_4l);
    }
}

// BDT
void CalculateVar4lInclusive::fillMassBDTVars()
{
    QuadleptonType::QuadleptonType quadType =m_higgs->getQuadType();
    if(quadType != QuadleptonType::_4mu &&
            quadType != QuadleptonType::_2e2mu &&
            quadType != QuadleptonType::_2mu2e &&
            quadType != QuadleptonType::_4e ) return;
    vector<const xAOD::IParticle*> particleList;

    // Getting the FSR Photon
    for (Int_t i = 0; i < (Int_t) m_higgs->getLepSize(); i++)
    {
        particleList.push_back(m_higgs->getLep(i)->getParticle());
    }

    // Set input
    m_BDTtool->setBDTInputs(particleList[0],
            particleList[1],
            particleList[2],
            particleList[3],
            m_higgs->getTLV().Pt()/1000,
            -999,
            false);
 
   // Set output
    float KD_discriminant       = -999;
    float BDT_discriminant      = -999;
    float BDTGuass_discriminant = -999;
    float ptSysupFac            = -999;
    float ptSysdownFac          = -999;

    m_BDTtool->fillBDTOutputs(KD_discriminant,
            BDT_discriminant,
            BDTGuass_discriminant,
            ptSysupFac,
            ptSysdownFac);

    m_outTree->updateFloatVar("BDT_discriminant_fid"+m_leptonType+"_truth", BDT_discriminant);
    m_outTree->updateFloatVar("KD_discriminant_fid"+m_leptonType+"_truth", KD_discriminant);
    m_outTree->updateFloatVar("HiggsME_fid"+m_leptonType+"_truth", m_BDTtool->getSignalME());


    LOG(logDEBUG)<<"BDT_discriminant: "<<BDT_discriminant;

    if(m_passFidCut) {
        QuadleptonType::QuadleptonType quadType_fid =m_higgs_fid->getQuadType();
        if(quadType_fid != QuadleptonType::_4mu &&
                quadType_fid != QuadleptonType::_2e2mu &&
                quadType_fid != QuadleptonType::_2mu2e &&
                quadType_fid != QuadleptonType::_4e ) return;
        vector<const xAOD::IParticle*> particleList_fid;

        // Getting the FSR Photon
        for (Int_t i = 0; i < (Int_t) m_higgs_fid->getLepSize(); i++)
        {
            particleList_fid.push_back(m_higgs_fid->getLep(i)->getParticle());
        }

        // Set input
        m_BDTtool->setBDTInputs(particleList_fid[0],
                particleList_fid[1],
                particleList_fid[2],
                particleList_fid[3],
                m_higgs->getTLV().Pt()/1000,                
                -999,
                false);
     
       // Set output
        float KD_discriminant_fid       = -999;
        float BDT_discriminant_fid      = -999;
        float BDTGuass_discriminant_fid = -999;
        float ptSysupFac_fid            = -999;
        float ptSysdownFac_fid          = -999;

        m_BDTtool->fillBDTOutputs(KD_discriminant_fid,
                BDT_discriminant_fid,
                BDTGuass_discriminant_fid,
                ptSysupFac_fid,
                ptSysdownFac_fid);

        m_outTree->updateFloatVar("BDT_discriminant_fid"+m_leptonType+"_4lsel", BDT_discriminant_fid);
        m_outTree->updateFloatVar("KD_discriminant_fid"+m_leptonType+"_4lsel", KD_discriminant_fid);
        m_outTree->updateFloatVar("HiggsME_fid"+m_leptonType+"_4lsel", m_BDTtool->getSignalME());


        LOG(logDEBUG)<<"BDT_discriminant_4lsel: "<<BDT_discriminant_fid;
        
    }
}


// To Caclulate the mass
void CalculateVar4lInclusive::fillMassVars()
{

    m_outTree->updateFloatVar("higgs_m_fid"+m_leptonType+"_truth", m_higgs->getTLV().M() / 1000.);
    m_outTree->updateFloatVar("Z1_m_fid"+m_leptonType+"_truth", m_higgs->getZ1()->getTLV().M() / 1000.);
    m_outTree->updateFloatVar("Z2_m_fid"+m_leptonType+"_truth", m_higgs->getZ2()->getTLV().M() / 1000.);

    m_outTree->updateFloatVar("higgs_pt_fid"+m_leptonType+"_truth", m_higgs->getTLV().Pt() / 1000.);
    m_outTree->updateFloatVar("pt4l_truth_born", m_higgs->getTLV().Pt() / 1000.);
    m_outTree->updateFloatVar("Z1_pt_fid"+m_leptonType+"_truth", m_higgs->getZ1()->getTLV().Pt() / 1000.);
    m_outTree->updateFloatVar("Z2_pt_fid"+m_leptonType+"_truth", m_higgs->getZ2()->getTLV().Pt() / 1000.);

    m_outTree->updateFloatVar("Z1_eta_fid"+m_leptonType+"_truth", m_higgs->getZ1()->getTLV().Eta() );
    m_outTree->updateFloatVar("Z2_eta_fid"+m_leptonType+"_truth", m_higgs->getZ2()->getTLV().Eta() );

    m_outTree->updateFloatVar("Z1_phi_fid"+m_leptonType+"_truth", m_higgs->getZ1()->getTLV().Phi() );
    m_outTree->updateFloatVar("Z2_phi_fid"+m_leptonType+"_truth", m_higgs->getZ2()->getTLV().Phi() );

    m_outTree->updateFloatVar("higgs_eta_fid"+m_leptonType+"_truth", m_higgs->getTLV().Eta());
    m_outTree->updateFloatVar("higgs_y_fid"+m_leptonType+"_truth", m_higgs->getTLV().Rapidity());

    if(m_passFidCut) {
        m_outTree->updateFloatVar("higgs_m_fid"+m_leptonType+"_4lsel", m_higgs_fid->getTLV().M() / 1000.);
        m_outTree->updateFloatVar("Z1_m_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ1()->getTLV().M() / 1000.);
        m_outTree->updateFloatVar("Z2_m_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ2()->getTLV().M() / 1000.);

        m_outTree->updateFloatVar("higgs_pt_fid"+m_leptonType+"_4lsel", m_higgs_fid->getTLV().Pt() / 1000.);
        
        m_outTree->updateFloatVar("Z1_pt_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ1()->getTLV().Pt() / 1000.);
        m_outTree->updateFloatVar("Z2_pt_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ2()->getTLV().Pt() / 1000.);

        m_outTree->updateFloatVar("higgs_eta_fid"+m_leptonType+"_4lsel", m_higgs_fid->getTLV().Eta());
        m_outTree->updateFloatVar("Z1_eta_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ1()->getTLV().Eta() );
        m_outTree->updateFloatVar("Z2_eta_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ2()->getTLV().Eta() );

        m_outTree->updateFloatVar("Z1_phi_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ1()->getTLV().Phi() );
        m_outTree->updateFloatVar("Z2_phi_fid"+m_leptonType+"_4lsel", m_higgs_fid->getZ2()->getTLV().Phi() );

        m_outTree->updateFloatVar("higgs_y_fid"+m_leptonType+"_4lsel", m_higgs_fid->getTLV().Rapidity());
    }
    
}




// pT reweighing for ggF
void CalculateVar4lInclusive::fillPtHRESReweight()
{

    float w_higgs_pt_reweight = 1.0;        
    float higgs_pt = m_higgs->getTLV().Pt() / 1000.0;
    if (m_eventCont->sampleType == SampleType::ggF) {
        if (m_jetList.size() == 0) {
            if(higgs_pt < 20.0) w_higgs_pt_reweight = 1.11; 
            else if(higgs_pt < 45.0) w_higgs_pt_reweight = 1.11 - (higgs_pt-20.0)/25.0*0.2; 
            else if(higgs_pt < 135.0) w_higgs_pt_reweight = 0.91 - (higgs_pt-45.0)/90.0*0.36; 
            else w_higgs_pt_reweight = 0.55;
        }
        else if( (m_jetList.size() == 1) && (m_leadingJet->getTLV().Pt()/1000.0 > 25.0) && (m_leadingJet->getTLV().Eta() < 4.5) ) {
            if(higgs_pt < 20.0) w_higgs_pt_reweight = 1.11; 
            else if(higgs_pt < 45.0) w_higgs_pt_reweight = 1.11 - (higgs_pt-20.0)/25.0*0.2; 
            else if(higgs_pt < 135.0) w_higgs_pt_reweight = 0.91 - (higgs_pt-45.0)/90.0*0.36; 
            else w_higgs_pt_reweight = 0.55;
        }
    }
    m_outTree->updateVar<double>("w_Higgs_pt", w_higgs_pt_reweight);
        
}
    




// Categorization
void CalculateVar4lInclusive::fillCategory()
{
        // Fill the jet var before
    
    fillJetVars();
    
    if (m_jetList.size() >= 2 && !(m_leadingJet || m_subLeadingJet))
    {
        LOG(logERROR)<<"FillCategory: nJet >= 2 but no leading or subleading jet";
        exit(-1);
    }
    
    
    Bool_t nJets2 = false;
    Bool_t nJets1 = false;
    Bool_t Mjj120 = false;
    Bool_t isolatedLep = false;
    Bool_t MjjEtaHM = false;
    
    // couting bJets
    int n_jets_btag60 = 0;
    int n_jets_btag70 = 0;
    int n_jets_btag77 = 0;
    int n_jets_btag85 = 0;
    for(const auto jetVar: m_jetList)
    {
        if(jetVar->getParticle()->auxdecor<int>("isBjet60")) n_jets_btag60++;
        if(jetVar->getParticle()->auxdecor<int>("isBjet70")) n_jets_btag70++;
        if(jetVar->getParticle()->auxdecor<int>("isBjet77")) n_jets_btag77++;
        if(jetVar->getParticle()->auxdecor<int>("isBjet85")) n_jets_btag85++;
    }
    m_outTree->updateIntVar("n_jets_btag60", n_jets_btag60 );
    m_outTree->updateIntVar("n_jets_btag70", n_jets_btag70 );
    m_outTree->updateIntVar("n_jets_btag77", n_jets_btag77 );
    m_outTree->updateIntVar("n_jets_btag85", n_jets_btag85 );
     
    if(m_jetList.size() >= 2)
    {
        nJets2 = true;
        const xAOD::Jet* leadingJet = dynamic_cast<const xAOD::Jet*>(m_leadingJet->getParticle());
        const xAOD::Jet* subleadingJet = dynamic_cast<const xAOD::Jet*>(m_subLeadingJet->getParticle());
        TLorentzVector sumJet = leadingJet->p4() + subleadingJet->p4();
        
        double deltaEta = fabs(leadingJet->eta() - subleadingJet->eta());
        if(sumJet.M() > 120*1000) Mjj120 = true;
        if(sumJet.M() > 400*1000 && deltaEta > 3.3)MjjEtaHM = true;

        
    }
    if(m_jetList.size() >= 1) nJets1 = true;

    // Extra Lepton
    for (auto* lep: m_elList)
    {
        if(isGoodExtraLepton(lep)) isolatedLep = true;
    }
    for (auto* lep: m_muList)
    {
        if(isGoodExtraLepton(lep)) isolatedLep = true;
    }
    
    prodTypeSimp::prodTypeSimp          currProductionType = prodTypeSimp::njet0;

    if((n_jets_btag70 > 0) && (m_jetList.size() > 3))   currProductionType = prodTypeSimp::ttH;
    else if((n_jets_btag70 > 0) && ((m_jetList.size() > 1) && isolatedLep))   currProductionType = prodTypeSimp::ttH;
    else if(isolatedLep)                currProductionType = prodTypeSimp::leptonic;
    else if(nJets2 && Mjj120)           currProductionType = prodTypeSimp::njet2_VBF;
    else if(nJets2 && !Mjj120)          currProductionType = prodTypeSimp::njet2_VH;
    else if(nJets1)                     currProductionType = prodTypeSimp::njet1;


    m_outTree->updateIntVar("prod_type", currProductionType);

    prodTypeHighMass::prodTypeHighMass  currProductionTypeHM = prodTypeHighMass::ggF_HM;
    if(MjjEtaHM)                        currProductionTypeHM = prodTypeHighMass::VBF_HM;

    m_outTree->updateIntVar("prod_type_HM", currProductionTypeHM);

 
    quadType::quadType currQuadTypeEvent = quadType::other;
    
    if(m_higgs->getQuadType() == QuadleptonType::_4mu) currQuadTypeEvent = quadType::_4mu;
    else if(m_higgs->getQuadType() == QuadleptonType::_2mu2e) currQuadTypeEvent = quadType::_2mu2e;
    else if(m_higgs->getQuadType() == QuadleptonType::_2e2mu) currQuadTypeEvent = quadType::_2e2mu;
    else if(m_higgs->getQuadType() == QuadleptonType::_4e) currQuadTypeEvent = quadType::_4e;
    else currQuadTypeEvent = quadType::other;
    
    m_outTree->updateIntVar("event_type", currQuadTypeEvent);

    
    quadType::quadType currQuadType = quadType::other;

    if(m_higgs->getQuadType() == QuadleptonType::_4mu) {currQuadType = quadType::_4mu; }
    else if(m_higgs->getQuadType() == QuadleptonType::_2mu2e) {currQuadType = quadType::_2mu2e;}
    else if(m_higgs->getQuadType() == QuadleptonType::_2e2mu) {currQuadType = quadType::_2e2mu;}
    else if(m_higgs->getQuadType() == QuadleptonType::_4e) {currQuadType = quadType::_4e;}
    else currQuadType = quadType::other;
    
    m_outTree->updateIntVar("event_type_fid"+m_leptonType+"_truth", currQuadType);

    if(m_passFidCut) {
        quadType::quadType fidQuadType = quadType::other;

        if(m_higgs_fid->getQuadType() == QuadleptonType::_4mu) {fidQuadType = quadType::_4mu;}
        else if(m_higgs_fid->getQuadType() == QuadleptonType::_2mu2e) {fidQuadType = quadType::_2mu2e;}
        else if(m_higgs_fid->getQuadType() == QuadleptonType::_2e2mu) {fidQuadType = quadType::_2e2mu;}
        else if(m_higgs_fid->getQuadType() == QuadleptonType::_4e) {fidQuadType = quadType::_4e;}
        else fidQuadType = quadType::other;
        
        m_outTree->updateIntVar("event_type_fid"+m_leptonType+"_4lsel", fidQuadType);

    }
}

void CalculateVar4lInclusive::fillSimpleXS()
{
    if(!m_eventCont->isMC) return;

    if(m_eventCont->eventInfo->isAvailable< int >( "HTXS_Stage0_Category" ))
    {
        m_outTree->updateIntVar("HTXS_Stage0_Category", m_eventCont->eventInfo->auxdata< int >( "HTXS_Stage0_Category" ));
        m_outTree->updateIntVar("HTXS_Stage1_Category_pTjet25", m_eventCont->eventInfo->auxdata< int >( "HTXS_Stage1_Category_pTjet25" ));
        m_outTree->updateIntVar("HTXS_Stage1_Category_pTjet30", m_eventCont->eventInfo->auxdata< int >( "HTXS_Stage1_Category_pTjet30" ));
    }
}

void CalculateVar4lInclusive::fillCatBDT()
{
    // Set input
    const xAOD::IParticle* m_leadingJetPart = 0;
    const xAOD::IParticle* m_subleadingJetPart = 0;

    if(m_leadingJet) m_leadingJetPart = m_leadingJet->getParticle();
    if(m_subLeadingJet) m_subleadingJetPart = m_subLeadingJet->getParticle();


    vector<const xAOD::IParticle*> jets;
    vector<const xAOD::IParticle*> leptons;

    // Get the jets
    if(m_leadingJetPart) jets.push_back(m_leadingJetPart);
    if(m_subleadingJetPart) jets.push_back(m_subleadingJetPart);


    // Get the leptons
    for(int i = 0; i < 4; i++)
    {
        leptons.push_back(m_higgs->getLep(i)->getParticle());
    }
    // To retrieve the results
    float resultME;
    float resultME_temp;
    bool  passesCut;
    float BDTScore;
    // One Jet BDT
    if(jets.size() == 1)
    {
        if(m_oneJet_jptetadR_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"One jet BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_OneJet_jptetadR_discriminant_fid"+m_leptonType+"_truth", BDTScore);
        LOG(logDEBUG)<<"BDT_OneJet_jptetadR_discriminant: "<<BDTScore;

        if(m_1J_pt4l_60_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_1J_pt4l_60_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_1Jet_pt4l_60_fid"+m_leptonType+"_truth", BDTScore);

        if(m_1J_pt4l_120_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_1J_pt4l_120_CatMVATool Calc failed";
        }
        m_outTree->updateFloatVar("BDT_1Jet_pt4l_120_fid"+m_leptonType+"_truth", BDTScore);
        if(m_1J_pt4l_60_120_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_1J_pt4l_60_120_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_1Jet_pt4l_60_120_fid"+m_leptonType+"_truth", BDTScore);

    }
    else if(jets.size() >= 1)
    {
        if(m_VBFCatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VBFCatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_TwoJet_discriminant_fid"+m_leptonType+"_truth", BDTScore);

        if(m_VHnoPtHjjCatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VHnoPtHjjCatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_VH_noptHjj_discriminant_fid"+m_leptonType+"_truth", BDTScore);

        if(m_VBF_TOPO_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VBF_TOPO_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_VBF_TOPO_fid"+m_leptonType+"_truth", BDTScore);

        if(m_VBF_Rest_CatMVATool->applyMVA(leptons, jets,
                    BDTScore,
                    resultME,
                    passesCut).isFailure())
        {
            LOG(logERROR)<<"m_VBF_Rest_CatMVATool BDT Calc failed";
        }
        m_outTree->updateFloatVar("BDT_VBF_Rest_fid"+m_leptonType+"_truth", BDTScore);
    }
    if(m_passFidCut) {
        vector<const xAOD::IParticle*> leptons_fid;
        // Get the leptons
        for(int i = 0; i < 4; i++)
        {
            leptons_fid.push_back(m_higgs_fid->getLep(i)->getParticle());
        }
        // To retrieve the results
        // One Jet BDT
        if(jets.size() == 1)
        {
            if(m_oneJet_jptetadR_CatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"One jet BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_OneJet_jptetadR_discriminant_fid"+m_leptonType+"_4lsel", BDTScore);
            LOG(logDEBUG)<<"BDT_OneJet_jptetadR_discriminant_fid: "<<BDTScore;

            if(m_1J_pt4l_60_CatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_1J_pt4l_60_CatMVATool BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_1Jet_pt4l_60_fid"+m_leptonType+"_4lsel", BDTScore);

            if(m_1J_pt4l_120_CatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_1J_pt4l_120_CatMVATool Calc failed";
            }
            m_outTree->updateFloatVar("BDT_1Jet_pt4l_120_fid"+m_leptonType+"_4lsel", BDTScore);
            if(m_1J_pt4l_60_120_CatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_1J_pt4l_60_120_CatMVATool BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_1Jet_pt4l_60_120_fid"+m_leptonType+"_4lsel", BDTScore);

        }
        else if(jets.size() >= 1)
        {
            if(m_VBFCatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_VBFCatMVATool BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_TwoJet_discriminant_fid"+m_leptonType+"_4lsel", BDTScore);

            if(m_VHnoPtHjjCatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_VHnoPtHjjCatMVATool BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_VH_noptHjj_discriminant_fid"+m_leptonType+"_4lsel", BDTScore);

            if(m_VBF_TOPO_CatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_VBF_TOPO_CatMVATool BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_VBF_TOPO_fid"+m_leptonType+"_4lsel", BDTScore);

            if(m_VBF_Rest_CatMVATool->applyMVA(leptons_fid, jets,
                        BDTScore,
                        resultME,
                        passesCut).isFailure())
            {
                LOG(logERROR)<<"m_VBF_Rest_CatMVATool BDT Calc failed";
            }
            m_outTree->updateFloatVar("BDT_VBF_Rest_fid"+m_leptonType+"_4lsel", BDTScore);
        }
    }
}

Bool_t CalculateVar4lInclusive::isGoodExtraLepton(ParticleVar* lep)
{
    if(m_higgs->isOverlap(lep)) return false;

    if(!(lep->getTLV().Pt() > 12*1000)) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed pt Cut";
    vector<ParticleVar*> vecLep;
    for(Int_t i = 0; i < m_higgs->getLepSize(); i++)
    {
        vecLep.push_back(m_higgs->getLep(i));
    }
    vecLep.push_back(lep);

    // deltaR Cut
    if(!m_cutQuad->cutDeltaR(vecLep)) return false;
    LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed DeltaR";
    // Iso Cut
    //m_cutQuad->cutIsolation(vecLep);
    //if(!lep->getParticle()->auxdecor< int >("isoCut")) return false;
    //LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed Iso";

    // D0Sig
    //m_cutQuad->cutD0Sig(vecLep);
    //if(!lep->getParticle()->auxdecor< int >("passD0Sig")) return false;
    //LOG(logDEBUG)<<"isGoodExtraLepton - Extra Lep passed D0";

    vecLep.clear();
    return true;

}


void CalculateVar4lInclusive::fillFiducial()
{
    if(m_passFidCut) m_outTree->updateIntVar("pass_fid"+m_leptonType+"_cut", 1);
    else m_outTree->updateIntVar("pass_fid"+m_leptonType+"_cut", 0);
    m_outTree->updateIntVar("truth_event_type", m_truthHelper->getTruthHiggsType());
}

bool CalculateVar4lInclusive::sortParticleVarPt (ParticleVar* i ,ParticleVar*j)
{
    return i->getTLV().Pt() > j->getTLV().Pt();
}

void CalculateVar4lInclusive::setLeptonType(std::string leptonType) {m_leptonType = leptonType;}

