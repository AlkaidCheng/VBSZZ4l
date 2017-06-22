#include "HZZUtils/ElectronMCClassification.h"
#include "HZZUtils/H4lMCTruthClassifierDefs.h"
#include "xAODTruth/xAODTruthHelpers.h"

#include "MCTruthClassifier/IMCTruthClassifier.h"
#include  "MCTruthClassifier/MCTruthClassifierDefs.h"

  ElectronMCClassification::ElectronMCClassification(const std::string& name)
    : AsgTool (name), m_useMcClassifier(true)
{
  declareProperty("MCTruthClassifierTool",m_mcClassifierTool);
  declareProperty("UseMCTruthClassifier", m_useMcClassifier);
}

StatusCode ElectronMCClassification::initialize()
{
  if (m_mcClassifierTool.retrieve().isFailure()) {
    ATH_MSG_ERROR( "Cannot retrieve MCClassifier Tool " << m_mcClassifierTool);
    return StatusCode::FAILURE;
  }
  return StatusCode::SUCCESS;
}

ElectronMCClassification::~ElectronMCClassification()
{
}

ElectronDetailedTruth::MCDetailedType ElectronMCClassification::getDetailedMCClassification(const xAOD::Electron& electron) const
{
  ElectronDetailedTruth::MCDetailedType detailedType = ElectronDetailedTruth::UnKnown;
  if(getDetailedMCClassification(electron, detailedType).isSuccess())
  {
    return detailedType;
  }else{
    return ElectronDetailedTruth::UnKnown;
  }
}

StatusCode ElectronMCClassification::getDetailedMCClassification(const xAOD::Electron& electron, ElectronDetailedTruth::MCDetailedType& detailedType) const
{
  int type = 0 ;
  int origin = 0 ;
  int type_bkg = -1;
  int origin_bkg = -1;
  
  if(m_useMcClassifier)
  {
    std::pair<MCTruthPartClassifier::ParticleType,MCTruthPartClassifier::ParticleOrigin>
      classification = m_mcClassifierTool->particleTruthClassifier(&electron);
    type = classification.first;
    origin = classification.second;

    const xAOD::TruthParticle *truthParticle =m_mcClassifierTool->getGenPart();
    std::pair<MCTruthPartClassifier::ParticleType,MCTruthPartClassifier::ParticleOrigin>
      classification_bkg = m_mcClassifierTool->checkOrigOfBkgElec(truthParticle);

    type_bkg = classification_bkg.first;
    origin_bkg = classification_bkg.second;
    
  }else{
    type = xAOD::TruthHelpers::getParticleTruthType(electron);
    origin = xAOD::TruthHelpers::getParticleTruthOrigin(electron);
  }

  //// hack for the case the classification fails in the derivation; useful for fakes in Sherpa 2.2
  if (type==H4lMCTruthPartClassifier::Unknown){
    // check the decorated type...
    int builtInType = xAOD::TruthHelpers::getParticleTruthType(electron);
    if (builtInType!=H4lMCTruthPartClassifier::Unknown) {
      //ATH_MSG_WARNING( "failed to assign type to electron, using type from decoration: " << builtInType );
      type = builtInType;
    }
  }
  ////
   
  if(type==H4lMCTruthPartClassifier::IsoElectron){ //isolated electron

    if(origin==H4lMCTruthPartClassifier::ZBoson){
      detailedType = ElectronDetailedTruth::Zboson;
      return StatusCode::SUCCESS;
    }

    else if(origin==H4lMCTruthPartClassifier::WBoson){
      detailedType = ElectronDetailedTruth::Wboson;
      return StatusCode::SUCCESS;
    }

    else{
      detailedType = ElectronDetailedTruth::OtherIsolated;
      return StatusCode::SUCCESS;
    }
  }

  else if(type==H4lMCTruthPartClassifier::NonIsoElectron){ //Non-isolated electron --> heavy
    detailedType = ElectronDetailedTruth::HeavyFlavor;
    return StatusCode::SUCCESS;
  }

  else if(type==H4lMCTruthPartClassifier::BkgElectron && origin==H4lMCTruthPartClassifier::PhotonConv){ //Photon conversions --> many cases as we need to find the origin of the photon
    if(m_useMcClassifier || type_bkg != -1 || origin_bkg != -1)
    {
      //we have bkg information
      ATH_MSG_DEBUG("Using MCTruthClasifier");
      if(origin_bkg==H4lMCTruthPartClassifier::ZBoson){ //brem from Z
        detailedType = ElectronDetailedTruth::ZbosonBrem;
        return StatusCode::SUCCESS;
      }
      else if(origin_bkg==H4lMCTruthPartClassifier::WBoson){//brem from W
        detailedType = ElectronDetailedTruth::WbosonBrem;
        return StatusCode::SUCCESS;
      }
      else if(origin_bkg==H4lMCTruthPartClassifier::FSRPhot){//FSR
        detailedType = ElectronDetailedTruth::FSR;
        return StatusCode::SUCCESS;
      }

      else if(origin_bkg==H4lMCTruthPartClassifier::PiZero || origin_bkg==H4lMCTruthPartClassifier::LightMeson 
          || origin_bkg==H4lMCTruthPartClassifier::StrangeMeson || origin_bkg==H4lMCTruthPartClassifier::LightBaryon ||
          origin_bkg==H4lMCTruthPartClassifier::StrangeBaryon) { //Pi0 Zero or light meson/baryon
        detailedType = ElectronDetailedTruth::LightMesonDecay;
        return StatusCode::SUCCESS;
      }

      else if ((origin_bkg>=H4lMCTruthPartClassifier::CharmedMeson && origin_bkg<=H4lMCTruthPartClassifier::BBbarMeson) 
          || (origin_bkg>=H4lMCTruthPartClassifier::CharmedBaryon &&origin_bkg<=H4lMCTruthPartClassifier::BottomBaryon)){ //heavy meson/baryon
        detailedType = ElectronDetailedTruth::HeavyFlavorBrem;
        return StatusCode::SUCCESS;
      }

      else{
        detailedType = ElectronDetailedTruth::OtherBkgConversion;
        return StatusCode::SUCCESS;
      }

    }else{
      //no bkg information try a best guess ourselves
      ATH_MSG_DEBUG("Using Built in Classifier");
      if(xAOD::TruthHelpers::getTruthParticle(electron))
      {
        return getMotherPhoton(xAOD::TruthHelpers::getTruthParticle(electron), detailedType);
      }else{
        ATH_MSG_ERROR("No truth particle found for detailed information");
        detailedType = ElectronDetailedTruth::UnKnown;
        return StatusCode::FAILURE;
      }
    }
  }
  else if(type==H4lMCTruthPartClassifier::BkgElectron ){ //BkgElectron but no conversion.
    detailedType = ElectronDetailedTruth::OtherBkgElectron;
    return StatusCode::SUCCESS;
  }
  else if(type==H4lMCTruthPartClassifier::Hadron){//Hadron
    detailedType = ElectronDetailedTruth::Hadron;
    return StatusCode::SUCCESS;
  }

  else if( type==H4lMCTruthPartClassifier::IsoMuon || type==H4lMCTruthPartClassifier::NonIsoMuon || type==H4lMCTruthPartClassifier::BkgMuon){//Muon
    detailedType = ElectronDetailedTruth::Muon;
    return StatusCode::SUCCESS;
  }

  else if (type==H4lMCTruthPartClassifier::Unknown || type==H4lMCTruthPartClassifier::UnknownElectron || type==H4lMCTruthPartClassifier::UnknownMuon){ //Unknown
    detailedType = ElectronDetailedTruth::UnKnown;
    return StatusCode::SUCCESS;
  }

  else{ //everything else
    detailedType = ElectronDetailedTruth::Other;    
    return StatusCode::SUCCESS;
  }

}
ElectronTruth::MCType ElectronMCClassification::getMCClassification(ElectronDetailedTruth::MCDetailedType detailedtype) const
{

  if(detailedtype==ElectronDetailedTruth::Zboson || detailedtype==ElectronDetailedTruth::Wboson ||
      detailedtype==ElectronDetailedTruth::ZbosonBrem || detailedtype==ElectronDetailedTruth::WbosonBrem ||
      detailedtype==ElectronDetailedTruth::OtherIsolated || detailedtype==ElectronDetailedTruth::ElectronBrem){
    return ElectronTruth::Isolated; 
  }
  else if(detailedtype==ElectronDetailedTruth::HeavyFlavor ||detailedtype==ElectronDetailedTruth::HeavyFlavorBrem){
    return ElectronTruth::Heavy;
  }
  else if(detailedtype==ElectronDetailedTruth::FSR){
    return ElectronTruth::FSR;
  }
  else if(detailedtype==ElectronDetailedTruth::Muon){
    return ElectronTruth::Muon;
  }
  else if(detailedtype==ElectronDetailedTruth::LightMesonDecay || detailedtype==ElectronDetailedTruth::OtherBkgConversion ){
    return ElectronTruth::Photon; 
  }
  else if(detailedtype==ElectronDetailedTruth::Hadron){
    return ElectronTruth::Hadron;
  }

  return ElectronTruth::Other;
}

StatusCode ElectronMCClassification::getMCClassification(const xAOD::Electron& electron, ElectronTruth::MCType& mcType) const
{
  ElectronDetailedTruth::MCDetailedType detailedType = ElectronDetailedTruth::UnKnown;

  StatusCode status = getDetailedMCClassification(electron, detailedType);

  if(status.isSuccess())
  {
    mcType = getMCClassification(detailedType);
    return status;
  }else{
    ATH_MSG_DEBUG( "Could not getDetailedMCClassification!" );
    mcType =  ElectronTruth::Other;
    return status;
  }
}

ElectronTruth::MCType ElectronMCClassification::getMCClassification(const xAOD::Electron& electron) const
{
  ElectronTruth::MCType mcType = ElectronTruth::Other;

  if(getMCClassification(electron, mcType).isSuccess())
  {
    return mcType;
  }else{
    return ElectronTruth::Other;
  }
}


StatusCode ElectronMCClassification::getMotherPhoton(const xAOD::TruthParticle* truthel, ElectronDetailedTruth::MCDetailedType& detailedType) const
{
  ATH_MSG_DEBUG("Begin getMotherPhoton");
  if (!truthel && getAbsPdgId(truthel) !=11){ //Truth must exist and be electron
    ATH_MSG_DEBUG("Not an electron");
    detailedType =  ElectronDetailedTruth::Other;
    return StatusCode::FAILURE;
  }
  ATH_MSG_DEBUG("\te(" << truthel->status() << ")");

  for  (size_t i =0;i < truthel->nParents();++i){ //Loop over the truth el parents

    const xAOD::TruthParticle *truthph = truthel->parent(i);
    if (getAbsPdgId(truthph) == 22) //find parent photon
    {
      ATH_MSG_DEBUG("\t photon(" << truthph->status() << ")");
      for (size_t j = 0; j < truthph->nParents(); ++j){ //loop over photons parents

        const xAOD::TruthParticle *truthGel = truthph->parent(j);

        if(getAbsPdgId(truthGel) ==22){ //photon comes from a photon 
          ATH_MSG_DEBUG("\t  photon(" << truthGel->status() << ")");
          ATH_MSG_DEBUG("FSR");
          detailedType =  ElectronDetailedTruth::FSR;
          return StatusCode::SUCCESS;
        }
        else if(getAbsPdgId(truthGel) == 11){//photon from electron therfore Brem
          ATH_MSG_DEBUG("\t  e("  << truthGel->status() << ")");
          for(size_t k = 0; k < truthGel->nParents(); ++k){
            ATH_MSG_DEBUG(" bremParents");
            const xAOD::TruthParticle *bremParent = truthGel->parent(k);
            if(getAbsPdgId(bremParent) == 22){
              ATH_MSG_DEBUG("\t   photon("  << bremParent->status() << ")");
              ATH_MSG_DEBUG("FSR");
              detailedType =  ElectronDetailedTruth::FSR;
              return StatusCode::SUCCESS;
            }else if (getAbsPdgId(bremParent) == 0){
              ATH_MSG_ERROR("No truth parent found for detailed information");
              detailedType = ElectronDetailedTruth::UnKnown;
              return StatusCode::FAILURE;
            }else if (truthGel->status() == 1){
              ATH_MSG_DEBUG("\t   " << getAbsPdgId(bremParent) << "(" << bremParent->status() << ")");
              ATH_MSG_DEBUG("ElectronBrem");
              detailedType = ElectronDetailedTruth::ElectronBrem;
              return StatusCode::SUCCESS;
            }else {
              ATH_MSG_DEBUG("\t   " << getAbsPdgId(bremParent) << "(" << bremParent->status() << ")");
              ATH_MSG_DEBUG("Other");
              detailedType = ElectronDetailedTruth::Other;
              return StatusCode::SUCCESS;
            }
          }
        }
        else if((getAbsPdgId(truthGel))%1000 > 100  && (getAbsPdgId(truthGel))%1000 < 400) { // electron comes from Light MEson pi or K
          ATH_MSG_DEBUG("\t  "<< truthGel->absPdgId() << "(" << truthGel->status() << ")");
          ATH_MSG_DEBUG("LightMeson ");

          detailedType =  ElectronDetailedTruth::LightMesonDecay;
          return StatusCode::SUCCESS;
        }
        else if((getAbsPdgId(truthGel))%1000 > 400  && (getAbsPdgId(truthGel))%1000 < 600) { // electron comes from Light MEson pi or K
          ATH_MSG_DEBUG("\t  "<< truthGel->absPdgId() << "(" << truthGel->status() << ")");
          ATH_MSG_DEBUG("HeavyMeson");
          detailedType =  ElectronDetailedTruth::HeavyFlavorBrem;
          return StatusCode::SUCCESS;
        }
        else if (getAbsPdgId(truthGel) == 0){
          ATH_MSG_ERROR("No truth parent found for detailed information");
          detailedType = ElectronDetailedTruth::UnKnown;
          return StatusCode::FAILURE;
        }else{
          ATH_MSG_DEBUG("\t   "<< truthGel->absPdgId() << "(" << truthGel->status() << ")");
          ATH_MSG_DEBUG("Other");
          detailedType = ElectronDetailedTruth::OtherBkgConversion;
          return StatusCode::SUCCESS;
        }
      }
    }else{
      ATH_MSG_DEBUG("non photon parent");
    }
  }

  ATH_MSG_ERROR("No truth photon parent found for detailed information");
  detailedType = ElectronDetailedTruth::UnKnown;
  return StatusCode::FAILURE;
}

int ElectronMCClassification::getAbsPdgId(const xAOD::TruthParticle* truthel) const
{
  if(truthel && truthel->isAvailable<int>("pdgId"))
  {
    return truthel->absPdgId();
  }else{
    return 0;
  }

}

