#include <TLorentzVector.h>
#include <TH1F.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TMath.h>

// Local include(s):
#include "HZZUtils/NLOreweighting.h"
#include "PathResolver/PathResolver.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODJet/JetContainer.h"
#include "FourMomUtils/xAODP4Helpers.h"

StatusCode NLOreweighting::GetWeightHOEW( const TLorentzVector& v1, const TLorentzVector& v2,
                                          const TLorentzVector& v3, const TLorentzVector& v4,
                                          const int& type, const int& DSID, double& central_yy_weight,
                                          double& weight_syst_up, double& weight_syst_down,
                                          double& weight_qcd_syst_up, double& weight_qcd_syst_down,
                                          double& rho ) {

    if(!m_isInitialized){
        ATH_MSG_INFO("Tool not initialized - will initilize now.");
        initialize();
    }

    central_yy_weight = 1.;
    weight_syst_down = 1;
    weight_syst_up = 1.;
    weight_qcd_syst_down = 1.;
    weight_qcd_syst_up = 1.;
    rho = 1.;

    if( !(DSID==361603 || DSID==342556 || DSID==343232 || DSID==206618 || DSID==206619 || DSID==206620 ||
          DSID==187180 || DSID==187181 || DSID==187182 || DSID==187183 || DSID==187184 || DSID==187185 ||
          DSID==363490 || DSID==345107 || DSID==345108 || // Turn on EW for new sherpa samples
          DSID==364250 || DSID==364251 || DSID==364252 // Turn on EW for new sherpa samples
          ) ){
        ATH_MSG_DEBUG("Sample not supported - returning weights of value one: "<<DSID);
        return StatusCode::SUCCESS;
    }

    TLorentzVector leptons[4];
    leptons[0] = v1; leptons[1] = v2; leptons[2] = v3; leptons[3] = v4;

    // calculate rho
    TVector2 ptvector(0., 0.);
    double denominator = 0.;
    for(unsigned int i=0; i<4; ++i){
        TVector2 tmp_pt((leptons[i]).Px() , (leptons[i]).Py());
        ptvector += tmp_pt;
        denominator += (leptons[i]).Pt();
    }

    double numerator = sqrt( ptvector.Px() * ptvector.Px() + ptvector.Py() * ptvector.Py() );
    rho = numerator / denominator;

    // four lepton mass
    TLorentzVector ZZ = ( v1 + v2 + v3 + v4);
    float mZZ = ZZ.M()/1000;

    if( mZZ >= 2500.) {
        // ATH_MSG_WARNING("NLOEWreweighting :: There is no EW weight for mZZ =" << mZZ << ". Setting mZZ to maximum with weight still available." );
        mZZ = 2499.5;
    }

    if( mZZ <= 67.) {
        // ATH_MSG_WARNING("NLOEWreweighting :: There is no EW weight for mZZ =" << mZZ << ". Setting mZZ to minimum with weight still available." );
        mZZ = 67.5;
    }

    Int_t bin = m_HOEW_factors[type]->FindBin(mZZ);
    central_yy_weight = m_HOEW_factors[type]->GetBinContent(bin);
    
    ATH_MSG_DEBUG("mZZ: "<<mZZ<<" HO EW central_yy_weight : "<<central_yy_weight);        


    // down and up are defined like that because the effect is mainly negative
    if(rho > 0.3 ) {
        // down means 2x the NLO EW effect
        weight_qcd_syst_down = 1. - 2. * (1. - central_yy_weight );
        // up means no effect
        weight_qcd_syst_up = central_yy_weight + (1. - central_yy_weight); // always 1 per definition
    } else {
        // weight_qcd_syst_down = 1.;
        // weight_qcd_syst_up = 1.;
        weight_qcd_syst_down = central_yy_weight;
        weight_qcd_syst_up = central_yy_weight;
    }

    bin = m_HOEW_factors[type+4]->FindBin(mZZ);
    double syst_weight = m_HOEW_factors[type+4]->GetBinContent(bin);
    // down means correction including yy plus difference between correction w/ and w/o yy
    weight_syst_down = central_yy_weight + ( (central_yy_weight - 1.) - (syst_weight - 1.) );
    // up means correction including yy minus difference between correction w/ and w/o yy
    weight_syst_up = central_yy_weight - ( (central_yy_weight - 1.) - (syst_weight - 1.) );

    return StatusCode::SUCCESS;
}

StatusCode NLOreweighting::GetWeightHOQCD( const TLorentzVector& v1, const TLorentzVector& v2,
                                           const TLorentzVector& v3, const TLorentzVector& v4,
                                           const int& type, const int& DSID, double& central_weight,
                                           double& weight_scale_up, double& weight_scale_down  ) {

    if(!m_isInitialized){
        ATH_MSG_INFO("Tool not initialized - will initilize now.");
        initialize();
    }

    central_weight = 1.;
    weight_scale_up = 1;
    weight_scale_down = 1.;


    // override behaviour for sherpa
    if( (DSID==363490 || DSID==345107 || DSID==345108 || DSID==364250 || DSID==364251 || DSID==364252 ) ){
        return GetWeightHOQCDSherpa( v1, v2, v3, v4, type, DSID, central_weight, weight_scale_up, weight_scale_down );
    }
    
    // bug fix - Removed DSID 361604 as it was just evaluating to be true always
    if( !(DSID==361603 || DSID==342556 || DSID==343232 || DSID==206618 || DSID==206619 || DSID==206620 ||
          DSID==187180 || DSID==187181 || DSID==187182 || DSID==187183 || DSID==187184 || DSID==187185 ) ){
        ATH_MSG_DEBUG("Sample not supported - returning weights of value one.");
        return StatusCode::SUCCESS;
    }
    
    // four lepton mass
    TLorentzVector ZZ = ( v1 + v2 + v3 + v4);
    float mZZ = ZZ.M()/1000;

    if( mZZ > 1500.) {
        // ATH_MSG_WARNING("NLOEWreweighting :: There is no QCD weight for mZZ =" << mZZ << ". Setting mZZ to maximum with weight still available." );
        mZZ = 1500.;
    }

    if( mZZ < 80.) {
        // ATH_MSG_WARNING("NLOEWreweighting :: There is no QCD weight for mZZ =" << mZZ << ". Setting mZZ to minimum with weight still available." );
        mZZ = 80.;
    }

    central_weight = m_HOQCD_factors[0]->Eval(mZZ);

    return StatusCode::SUCCESS;
}


// This is for sherpa
StatusCode NLOreweighting::GetWeightHOQCDSherpa( const TLorentzVector& /*v1*/, const TLorentzVector& /*v2*/,
                                           const TLorentzVector& /*v3*/, const TLorentzVector& /*v4*/,
                                           const int& type, const int& DSID, double& central_weight,
                                           double& weight_scale_up, double& weight_scale_down  ) {

    if(!m_isInitialized){
        ATH_MSG_INFO("Tool not initialized - will initilize now.");
        initialize();
    }

    central_weight = 1.;
    weight_scale_up = 1;
    weight_scale_down = 1.;

    if( !(DSID==363490 || DSID==345107 || DSID==345108 || DSID==364250 || DSID==364251 || DSID==364252  ) ){
        ATH_MSG_ERROR("Sample not supported - asking for sherpa SF, but DSID is not one of the sherpa ones");
        return StatusCode::FAILURE;
    }

    // For Sherpa 2.2.1, we have decided to NOT apply the HO QCD SF. Something should be done for
    // the 0-jet emission at the BORN level, but it is not possibile to correctly identify this as
    // all information about jets comes after the parton shower.  RDS 2017/04
    return StatusCode::SUCCESS;
    

    const xAOD::TruthParticleContainer *truthCont = 0;
    if (!truthCont && !evtStore()->retrieve(truthCont, "TruthParticles")) {
        ATH_MSG_ERROR("Could not retrieve the xAOD::TruthParticles. Return 1");
        return StatusCode::FAILURE;
    }

    const xAOD::EventInfo* info = 0;
    if (!info && !evtStore()->retrieve(info, "EventInfo")) {
        ATH_MSG_ERROR("Could not retrieve the xAOD::EventInfo. Return 1");
        return StatusCode::FAILURE;
    }

    xAOD::TruthParticleContainer::const_iterator tp_itr = truthCont->begin();
    xAOD::TruthParticleContainer::const_iterator tp_end = truthCont->end();
    std::vector <TLorentzVector*> leptons_status3; // For Inclusive Sherpa...
    std::vector < const xAOD::TruthParticle*> leptons_xAOD; // For Inclusive Sherpa...

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

        leptons_xAOD.push_back((*tp_itr));
    }

    if(leptons_status3.size() != 4 || leptons_xAOD.size() != 4)
    {
        ATH_MSG_ERROR("Could not find 4 status 3 leptons. Return 1");
        return StatusCode::FAILURE;
    }
    
    TLorentzVector combined_status3 = (*leptons_status3.at(0) + *leptons_status3.at(1) + *leptons_status3.at(2) + *leptons_status3.at(3));

    double m4l_status3 = combined_status3.M()/1000;
    double pt4l_status3 = combined_status3.Pt()/1000;
    //ATH_MSG_INFO("Event found with pT4l: "<<pt4l_status3<<" m4l: "<<m4l_status3);

    const xAOD::JetContainer* truthJetCont = 0;

    // do the AntiKt4 jets
    if(!evtStore()->retrieve( truthJetCont, "AntiKt4TruthJets" ))
    {
        ATH_MSG_ERROR("Could not retrieve the xAOD::TruthJets. Return 1");
        return StatusCode::FAILURE;
    }

    std::vector<const xAOD::Jet*> truthJet;
    for( const auto& jet : *( truthJetCont ) ) 
    {
        if(jet->pt() < 30 * 1000) continue;
        if(fabs(jet->eta()) > 4.5) continue;
        
        // compute the overlap with leptons
        bool rejectJet = false;
        for(const auto* lep:leptons_xAOD)
        {
            if(xAOD::P4Helpers::deltaR(*lep, *jet) < 0.4)
            {
                ATH_MSG_DEBUG("rejecting jet - pt "<<jet->pt()<<" eta: "<<jet->eta()<<" phi: "<<jet->phi()<<" lep - pt "<<lep->pt()<<" eta: "<<lep->eta()<<" phi: "<<lep->phi());
                rejectJet = true;
                break;
            }
        }
        if(rejectJet) continue;
        truthJet.push_back(jet);
    }

    

    // The SF are only valid for n_jet = 0, otherwise return 1
    if(truthJet.size() != 0) 
    { 
        ATH_MSG_DEBUG("Event #: "<<info->eventNumber()<<" continue since n_jets_ruth "<<truthJet.size());        
        return StatusCode::SUCCESS;
    }
    
    
    ATH_MSG_DEBUG("Event #: "<<info->eventNumber()<<" m4l_status3: "<<m4l_status3);        

    // To fix the range issues
    if( m4l_status3 > 1500.) {
        m4l_status3 = 1500.;
    }
    if( m4l_status3 < 100.) {
        m4l_status3 = 100.;
    }

    central_weight = m_HOQCD_Sherpa_factors[type]->Eval(m4l_status3);

    ATH_MSG_DEBUG("Event #: "<<info->eventNumber()<<" corrected m4l_status3: "<<m4l_status3<<" HO QCD central_weight : "<<central_weight);        


    return StatusCode::SUCCESS;
}


StatusCode NLOreweighting::GetWeightHOQCD( const TLorentzVector& Z1, const TLorentzVector& Z2,
                                           const int& type, const int& DSID, double& central_weight,
                                           double& weight_scale_up, double& weight_scale_down ) {

    if(!m_isInitialized){
        ATH_MSG_INFO("Tool not initialized - will initilize now.");
        initialize();
    }

    central_weight = 1.;
    weight_scale_up = 1;
    weight_scale_down = 1.;

        // override behaviour for sherpa
    if( (DSID==363490 || DSID==345107 || DSID==345108 ||  DSID==364250 || DSID==364251 || DSID==364252 ) ){
        // The input vectors don't matter for this, so just use whatever is input
        return GetWeightHOQCDSherpa( Z1, Z1, Z2, Z2, type, DSID, central_weight, weight_scale_up, weight_scale_down );
    }


    // bug fix - Removed DSID 361604 as it was just evaluating to be true always
    if( !(DSID==361603 || DSID==342556 || DSID==343232 || DSID==206618 || DSID==206619 || DSID==206620 ||
          DSID==187180 || DSID==187181 || DSID==187182 || DSID==187183 || DSID==187184 || DSID==187185 ) ){
        ATH_MSG_DEBUG("Sample not supported - returning weights of value one.");
        return StatusCode::SUCCESS;
    }
    
    // four lepton mass
    TLorentzVector ZZ = ( Z1 + Z2 );
    float mZZ = ZZ.M()/1000;

    if( mZZ > 1500.) {
        // ATH_MSG_WARNING("NLOEWreweighting :: There is no QCD weight for mZZ =" << mZZ << ". Setting mZZ to maximum with weight still available." );
        mZZ = 1500.;
    }

    if( mZZ < 80.) {
        // ATH_MSG_WARNING("NLOEWreweighting :: There is no QCD weight for mZZ =" << mZZ << ". Setting mZZ to minimum with weight still available." );
        mZZ = 80.;
    }

    central_weight = m_HOQCD_factors[0]->Eval(mZZ);

    return StatusCode::SUCCESS;
}

NLOreweighting::NLOreweighting(const std::string& name) : AsgTool ( name ), m_isInitialized(false) {
}

NLOreweighting::~NLOreweighting()
{
    if(m_isInitialized) {
        for(unsigned int i=0; i<8; ++i) {
            delete m_HOEW_factors[i];
            m_HOEW_factors[i]=nullptr;
        }
        m_HOEW_f->Close();

        for(unsigned int i=0; i<3; ++i) {
            delete m_HOQCD_factors[i];
            m_HOQCD_factors[i]=nullptr;
        }
        m_HOQCD_f->Close();

        for(unsigned int i=0; i<4; ++i) {
            delete m_HOQCD_Sherpa_factors[i];
            m_HOQCD_Sherpa_factors[i]=nullptr;
        }
        m_HOQCD_Sherpa_f->Close();

    }
}

StatusCode NLOreweighting::initialize(){

    m_HOEW_inputFileName = "HZZUtils/NLOreweighting/v2/HOEW_KFactors.root";
    std::string fullfilename_HOEW = PathResolver::find_file(m_HOEW_inputFileName, "CALIBPATH");

    if( fullfilename_HOEW.empty() ) {
        ATH_MSG_ERROR("Something wrong, could not find k-factor file "<< fullfilename_HOEW );
        return StatusCode::FAILURE;
    }
    else {

        m_HOEW_f = new TFile( fullfilename_HOEW.c_str(), "READ");

        m_HOEW_f->cd();

        m_HOEW_factors[0] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_yy_mmmm")) );
        m_HOEW_factors[1] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_yy_eeee")) );
        m_HOEW_factors[2] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_yy_mmee")) );
        m_HOEW_factors[3] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_yy_eemm")) );

        m_HOEW_factors[4] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_mmmm")) );
        m_HOEW_factors[5] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_eeee")) );
        m_HOEW_factors[6] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_mmee")) );
        m_HOEW_factors[7] = new TH1F( *((TH1F*)m_HOEW_f->Get("qq_eemm")) );
        
        m_currSys = Nominal;

        // Register systematic

        if( !applySystematicVariation( CP::SystematicSet() ) ) {
            ATH_MSG_ERROR( "Unable to run with no systematic" );
            return StatusCode::FAILURE;
        }
        CP::SystematicRegistry& registry = CP::SystematicRegistry::getInstance();
        if( registry.registerSystematics( *this ) != CP::SystematicCode::Ok ) return StatusCode::FAILURE;

    }

    // This is now only for powheg
    m_HOQCD_inputFileName = "HZZUtils/NLOreweighting/HOQCD_KFactors.root";
    std::string fullfilename_HOQCD = PathResolver::find_file(m_HOQCD_inputFileName, "CALIBPATH");

    if( fullfilename_HOQCD.empty() ) {
        ATH_MSG_ERROR("Something wrong, could not find k-factor file "<< fullfilename_HOQCD );
        return StatusCode::FAILURE;
    }
    else {

        m_HOQCD_f = new TFile( fullfilename_HOQCD.c_str(), "READ");

        m_HOQCD_f->cd();

        m_HOQCD_factors[0] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_f->Get("qq_nom")) );
        m_HOQCD_factors[1] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_f->Get("qq_dbl")) );
        m_HOQCD_factors[2] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_f->Get("qq_hlf")) );

    }


    // These are the HO QCD corrections for Sherpa
    m_HOQCD_Sherpa_inputFileName = "HZZUtils/NLOreweighting/v2/HOQCD_KFactors_Sherpa.root";
    std::string fullfilename_HOQCD_Sherpa = PathResolver::find_file(m_HOQCD_Sherpa_inputFileName, "CALIBPATH");

    if( fullfilename_HOQCD_Sherpa.empty() ) {
        ATH_MSG_ERROR("Something wrong, could not find k-factor file "<< fullfilename_HOQCD_Sherpa );
        return StatusCode::FAILURE;
    }
    else {

        m_HOQCD_Sherpa_f = new TFile( fullfilename_HOQCD_Sherpa.c_str(), "READ");

        m_HOQCD_Sherpa_f->cd();

        m_HOQCD_Sherpa_factors[0] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_Sherpa_f->Get("qq_mmmm_ctr")) );
        m_HOQCD_Sherpa_factors[1] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_Sherpa_f->Get("qq_eeee_ctr")) );
        m_HOQCD_Sherpa_factors[2] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_Sherpa_f->Get("qq_mmee_ctr")) );
        m_HOQCD_Sherpa_factors[3] = new TGraphErrors( *((TGraphErrors*)m_HOQCD_Sherpa_f->Get("qq_eemm_ctr")) );
    }


    m_isInitialized = true;
    return StatusCode::SUCCESS;

}

bool NLOreweighting::isAffectedBySystematic( const CP::SystematicVariation& systematic ) const {

    CP::SystematicSet sys = affectingSystematics();
    return sys.find( systematic ) != sys.end();

}

CP::SystematicSet NLOreweighting::affectingSystematics() const {

    CP::SystematicSet result;

    //::: NLO systematics
    result.insert( CP::SystematicVariation( "HOEW_syst", 1 ) );
    result.insert( CP::SystematicVariation( "HOEW_syst", -1 ) );

    //::: NLO QCG systematics
    result.insert( CP::SystematicVariation( "HOEW_QCD_syst", 1 ) );
    result.insert( CP::SystematicVariation( "HOEW_QCD_syst", -1 ) );

    //::: NLO QCG systematics
    result.insert( CP::SystematicVariation( "HOQCD_scale_syst", 1 ) );
    result.insert( CP::SystematicVariation( "HOQCD_scale_syst", -1 ) );

    return result;

}

CP::SystematicSet NLOreweighting::recommendedSystematics() const {

    return affectingSystematics();

}

CP::SystematicCode NLOreweighting::applySystematicVariation( const CP::SystematicSet& systConfig ) {

    //::: Then check if it is actually supported
    static CP::SystematicSet affSysts = affectingSystematics();
    CP::SystematicSet checkSysConf;
    if( !CP::SystematicSet::filterForAffectingSystematics( systConfig, affSysts, checkSysConf ) ) {
        ATH_MSG_ERROR( "Passing unsupported systematic to the tool!" );
        return CP::SystematicCode::Unsupported;
    }

    m_currSys = Nominal;

    //::: NLO EW systematics
    CP::SystematicVariation syst = systConfig.getSystematicByBaseName( "HOEW_syst" );

    if( syst == CP::SystematicVariation( "HOEW_syst", 1 ) ) {
        m_currSys = EW_Syst_up;
    }
    else if( syst == CP::SystematicVariation( "HOEW_syst", -1 ) ) {
        m_currSys = EW_Syst_down;
    }
    else if( !syst.empty() ) return CP::SystematicCode::Unsupported;

    //::: NLO EW systematics
    syst = systConfig.getSystematicByBaseName( "HOEW_QCD_syst" );

    if( syst == CP::SystematicVariation( "HOEW_QCD_syst", 1 ) ) {
        m_currSys = EW_Syst_QCD_up;
    }
    else if( syst == CP::SystematicVariation( "HOEW_QCD_syst", -1 ) ) {
        m_currSys = EW_Syst_QCD_down;
    }
    else if( !syst.empty() ) return CP::SystematicCode::Unsupported;

    //::: NLO QCD systematics
    syst = systConfig.getSystematicByBaseName( "HOQCD_scale_syst" );

    if( syst == CP::SystematicVariation( "HOQCD_scale_syst", 1 ) ) {
        m_currSys = QCD_Syst_scale_up;
    }
    else if( syst == CP::SystematicVariation( "HOQCD_scale_syst", -1 ) ) {
        m_currSys = QCD_Syst_scale_down;
    }
    else if( !syst.empty() ) return CP::SystematicCode::Unsupported;

    return CP::SystematicCode::Ok;

}

StatusCode NLOreweighting::fillWeightHOEW( const TLorentzVector& v1, const TLorentzVector& v2,
                                           const TLorentzVector& v3, const TLorentzVector& v4,
                                           const int& type, const int& DSID, double& weight )
{
    double central_yy_weight;
    double weight_syst_up;
    double weight_syst_down;
    double weight_qcd_syst_up;
    double weight_qcd_syst_down;
    double rho;

    bool isOk = this->GetWeightHOEW(v1,
                    v2,
                    v3,
                    v4,
                    type,
                    DSID,
                    central_yy_weight,
                    weight_syst_up,
                    weight_syst_down,
                    weight_qcd_syst_up,
                    weight_qcd_syst_down,
                    rho).isSuccess();

    if(!isOk)
    {
        weight = -1;
        return StatusCode::FAILURE;
    }

    if(m_currSys == Nominal) weight = central_yy_weight;
    else if (m_currSys == EW_Syst_up) weight = weight_syst_up;
    else if (m_currSys == EW_Syst_down) weight = weight_syst_down;
    else if (m_currSys == EW_Syst_QCD_up) weight = weight_qcd_syst_up;
    else if (m_currSys == EW_Syst_QCD_down) weight = weight_qcd_syst_down;
    else weight = central_yy_weight; // i.e. for QCD_Syst_scale_up, QCD_Syst_scale_down
    
    return StatusCode::SUCCESS;

}

StatusCode NLOreweighting::fillWeightHOQCD( const TLorentzVector& v1, const TLorentzVector& v2,
                                            const TLorentzVector& v3, const TLorentzVector& v4,
                                            const int& type, const int& DSID, double& weight )
{
    double central_weight;
    double weight_scale_up;
    double weight_scale_down;

    bool isOk = this->GetWeightHOQCD(v1,
                    v2,
                    v3,
                    v4,
                    type,
                    DSID,
                    central_weight,
                    weight_scale_up,
                    weight_scale_down).isSuccess();

    if(!isOk)
    {
        weight = -1;
        return StatusCode::FAILURE;
    }

    if(m_currSys == Nominal) weight = central_weight;
    else if (m_currSys == QCD_Syst_scale_up) weight = central_weight; // weight_scale_up at some point
    else if (m_currSys == QCD_Syst_scale_down) weight = central_weight; // weight_scale_down at some point
    else weight = central_weight; // i.e. for EW_Syst_up, EW_Syst_down, EW_Syst_QCD_up, EW_Syst_QCD_down

    return StatusCode::SUCCESS;

}

StatusCode NLOreweighting::fillWeightHOQCD( const TLorentzVector& Z1, const TLorentzVector& Z2,
                                            const int& type, const int& DSID, double& weight )
{
    double central_weight;
    double weight_scale_up;
    double weight_scale_down;

    bool isOk = this->GetWeightHOQCD(Z1,
                    Z2,
                    type,
                    DSID,
                    central_weight,
                    weight_scale_up,
                    weight_scale_down).isSuccess();

    if(!isOk)
    {
        weight = -1;
        return StatusCode::FAILURE;
    }

    if(m_currSys == Nominal) weight = central_weight;
    else if (m_currSys == QCD_Syst_scale_up) weight = central_weight; // weight_scale_up at some point
    else if (m_currSys == QCD_Syst_scale_down) weight = central_weight; // weight_scale_down at some point
    else weight = central_weight; // i.e. for EW_Syst_up, EW_Syst_down, EW_Syst_QCD_up, EW_Syst_QCD_down
    
    return StatusCode::SUCCESS;

}
