#include "HZZCutCommon/ApplyWeight.h"
using namespace std;

ApplyWeight::ApplyWeight(EventContainer* t_eventcont)
{
    m_eventCont = t_eventcont;

    m_pileupTool = ToolHandle<CP::IPileupReweightingTool>("PileupTool");
    if(m_pileupTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight::ApplyWeight() - cannot retrieve IPileupReweightingTool";
        exit(1);
    }
    
    m_xsTool = ToolHandle<IHiggsCrossSection>("xsTool");
    if(m_xsTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight::ApplyWeight() - cannot retrieve IHiggsCrossSection";
        exit(1);
    }

    m_varTool = ToolHandle<ITheoryVariation>("varTool");
    if(m_varTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight::ApplyWeight() - cannot retrieve ITheoryVariation";
        exit(1);
    }
    
    m_brTool = ToolHandle<IH4lBrRatio>("brTool");
    if(m_brTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"ApplyWeight::ApplyWeight() - cannot retrieve IH4lBrRatio";
        exit(1);
    }
}


ApplyWeight::~ApplyWeight()
{
}

// Below are used for cutflow weight
Double_t ApplyWeight::getEventWeight()
{

    if(!m_eventCont->doSmear) return 1;
    if(!m_eventCont->isMC) return 1;

    Double_t weight = 1;
    
    weight *= getMCWeight();
    weight *= getPileUpWeight();

    return weight;
}

Double_t ApplyWeight::getPileUpWeight()
{   
    // Return if it is a TRUTH AOD sample
    if(m_eventCont->m_isDAODTRUTH)
    {
        if(m_eventCont->m_eventIndex == 0) LOG(logWARNING)<<"DAOD_TRUTH - skipping pileup weight";
        return 1;
    }


    if(m_pileupCached) return m_pileupWeight;


    // For data, need to apply the pileup tool
    // This is to get the correct average interaction per event information
    //m_pileupTool->apply(*m_eventCont->eventInfo, false).ignore();
    m_pileupTool->apply(*m_eventCont->eventInfo).ignore();

    // If below conditions are true, 
    // overwrite the pileupweight with 1, to prevent any other code from breaking
    if(!m_eventCont->doSmear)
    {
        m_eventCont->eventInfo->auxdecor< float >("PileupWeight") = 1;
        return 1;
    }
    if(!m_eventCont->isMC)
    {
        m_eventCont->eventInfo->auxdecor< float >("PileupWeight") = 1;
        return 1;
    }


    // cache first and then overwrite the changes in systematics due to PRW tool changing SF
    TString sysName((m_eventCont->m_currVariation).name());
    //LOG(logDEBUG)<<"sysName: "<<sysName;
    if(!sysName.Contains("PRW_DATASF"))
    {
        m_pileupRandRunNumber = m_eventCont->eventInfo->auxdecor< unsigned int>("RandomRunNumber");
        //LOG(logDEBUG)<<"caching m_pileupRandRunNumber "<<m_pileupRandRunNumber;
    }    
    else
    {
        //LOG(logDEBUG)<<"current m_pileupRandRunNumber "<<m_eventCont->eventInfo->auxdecor< unsigned int>("RandomRunNumber");
        //LOG(logDEBUG)<<"overwriting m_pileupRandRunNumber "<<m_pileupRandRunNumber;
        
        m_eventCont->eventInfo->auxdecor< unsigned int>("RandomRunNumber") = m_pileupRandRunNumber;
    }




    
   
    Double_t weight = 1; 
    // Applying the pileup Weight
    weight *= m_eventCont->eventInfo->auxdata< float >("PileupWeight");
   
    // cache the weight
    m_pileupWeight = weight;

    //LOG(logDEBUG)<<"Pileup weight - sys "<<m_eventCont->m_currVariation.name()<<" weight: "<<weight;

    m_pileupCached = false;

    return weight;
}

// Sample weights
Double_t ApplyWeight::getCrossSection() const
{
    if(!m_eventCont->isMC) return 1;
    
    Double_t xsWeight = -999;
    
    // Check if this cross-section is avaliable in the tool
    Int_t DSID = m_eventCont->eventInfo->mcChannelNumber();
    // Some truth derivation are weird... they store DSID in runNumber
    // Max provided this fix
    if (m_eventCont->m_isDAODTRUTH && DSID == 0)
    {
        DSID = m_eventCont->eventInfo->runNumber();
    }
    // Check if this cross-section is avaliable in the tool
    xsWeight = CrossSections::GetBkgCrossSection13TeV(DSID);

    // This sample was avaliable in the BkgCrossSection tool,
    // Just return this
    // bbH ybyt XS is negative... need a work around
    // default if not found is -1
    if(abs((xsWeight + 1)) > 0.001) return xsWeight;
    
    // Well this maybe a signal sample
    if(m_eventCont->sampleType == SampleType::ggF)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecGGF);
    }
    else if(m_eventCont->sampleType == SampleType::VBF)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecVBF);
    }
    else if(m_eventCont->sampleType == SampleType::WH)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecWH);
    }
    else if(m_eventCont->sampleType == SampleType::WpH)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecWpH);
    }
    else if(m_eventCont->sampleType == SampleType::WmH)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecWmH);
    }
    else if(m_eventCont->sampleType == SampleType::ZH)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecZH);
    }
    else if(m_eventCont->sampleType == SampleType::bbH)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecbbH);
    }
    else if(m_eventCont->sampleType == SampleType::ttH)
    {
        xsWeight = m_xsTool->execute(CentreOfMass::is13TeV,
                                     m_eventCont->mHTrue,
                                     ColumnXS::xsecttH);
    }
    else
    {
        LOG(logERROR)<<"ApplyWeight::getCrossSection(): Sample Type not supported";
        exit(1);
    }
    
    return xsWeight;
}
Double_t ApplyWeight::getBranchingRaio() const
{
    return 1;
}


// MC weight
Double_t ApplyWeight::getMCWeight()
{
    if(!m_eventCont->doSmear && (m_eventCont->m_analType != AnalysisType::Fiducial)) return 1;
    if(!m_eventCont->isMC) return 1;
    
    
    std::vector< float > weights = m_eventCont->eventInfo->mcEventWeights();
    const xAOD::TruthEventContainer* truthEvent = 0;
    if(m_eventCont->m_isAOD){
        m_eventCont->getEvent()->retrieve( truthEvent, "TruthEvents" ).isSuccess();
        xAOD::TruthEventContainer::const_iterator itTruth = truthEvent->begin();
        weights = (*itTruth)->weights();
    }

       // Check if this cross-section is avaliable in the tool
    Int_t runNumber = m_eventCont->eventInfo->mcChannelNumber();
    // Some truth derivation are weird... they store DSID in runNumber
    if (m_eventCont->m_isDAODTRUTH && runNumber == 0)
    {
        runNumber = m_eventCont->eventInfo->runNumber();
    }
    //LOG(logINFO)<<"Weight size(): "<< weights.size();
    if(runNumber == 345060) {
    	if(weights.size() > 151) return weights[151];
        // herwig hack
        if(weights.size() == 3) return weights[1];
    }
    if(runNumber == 344235) {
        if(weights.size() > 107) return weights[107];
        // herwig hack
        if(weights.size() == 3) return weights[1];
    }
    if(runNumber == 345038 || runNumber == 345039 || runNumber == 345040) {
        if(weights.size() > 109) return weights[109];
        // herwig hack
        if(weights.size() == 3) return weights[1];   
    }

    if( weights.size() > 0 ) return weights[0];

    return 1;
}


// Luminosity
Double_t ApplyWeight::getLumi()
{
    if(!m_eventCont->isMC) return 1;
    
    // To convert to fb^-1
    Double_t lumi = m_pileupTool->GetIntegratedLumi()/(1000);
    
    return lumi;
    
}


// Clear vars
void ApplyWeight::clearVars()
{
    m_pileupCached = false;
    m_pileupWeight = -999;
}

