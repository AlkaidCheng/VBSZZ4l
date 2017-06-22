#include "HZZCutCommon/EventContainer.h"

// xAOD includes
#include "xAODMetaData/FileMetaData.h"

using namespace std;

EventContainer::EventContainer()
{
    LOG::ReportingLevel() = LOG::FromString("INFO");


    // Default values
    fileName = "";
    fileTree = 0;
    isDebug  = false;

    doSmear = true;
    mHTrue = -1;
    mcChannelNumber = -1;
    mcRunNumber = -1;
    eventNumber = -1;
    m_eventIndex = -1;
    isNoTau = false;
    m_AFII = false;
    isEFT = false;
    m_isDAODTRUTH = false;
    m_isAOD = false;
    
    outTree = 0;

    outputBaseName = "testOutput";

    hasInit = false;

    m_dataPeriod = Periods::periodNone;
    m_trigPeriod = TrigPeriods::None;

    // Default as powheg pythia 8 for generator
    m_currGenerator = Generator::PowhegPythia8;
}

EventContainer::~EventContainer()
{
    if(event) delete event;
    if(store) delete store;
}


// Intialize
Bool_t EventContainer::initialize()
{
    // check to see if the minimum number of information has been provided
    if(fileName == "")
    {
        LOG(logERROR) <<"EventContainer::initialize() - File Name not provided";
        exit(1);
    }
    if(fileTree == 0 && m_inputFileNames.size() == 0)
    {
        LOG(logERROR) <<"EventContainer::initialize() - TTree or TChain or fileList not provided";      
        exit(1);
    }

    RETURN_CHECK("EventContainer", xAOD::Init("Analysis")); // Has to be done first

    TFile* dummyFile = TFile::Open( m_inputFileNames[ 0 ].c_str(), "READ" ); // Triggers the loading of all the dictionaries
    if (dummyFile->IsZombie()) {
        LOG(logERROR) <<"EventContainer::initialize() - Error reading the file";
        LOG(logERROR) <<"Probably something wrong with the path for file "<< m_inputFileNames[ 0 ].c_str() ;
        exit(1);
    }
    delete dummyFile; // We don't need the file object anymore

    // Create the chain:
    m_chain = new TChain( "CollectionTree" );
    for(size_t i = 0; i < m_inputFileNames.size(); ++i ) {

        // Check files one by one for their validity
        TFile* dummyFile = TFile::Open( m_inputFileNames[ i ].c_str());

        // if the file doesn't exist, exit
        if(!dummyFile)
        {
            LOG(logERROR) <<"Error - TFile check can't open file: "<< m_inputFileNames[ i ].c_str()<<" exiting "; 
            exit(1);
        }

        if(dummyFile->Get("CollectionTree") == 0)
        {
            LOG(logWARNING) <<"Error - CollectionTree not found... adding it to the chain as a just in case, but without error checking exiting ";            
            m_chain->Add(m_inputFileNames[ i ].c_str());
            delete dummyFile;
            continue;
        }
        // clean up the memory
        delete dummyFile;

        int status = m_chain->Add( m_inputFileNames[ i ].c_str(), -1); 

        if(status != 1)
        {
            LOG(logERROR) <<"Error - can't open file: "<< m_inputFileNames[ i ].c_str()<<" TChain Status: "<<status<<" exiting ";
            exit(1);
        }

        LOG(logINFO) <<"Adding: "<< m_inputFileNames[ i ].c_str()<<" Status: "<<status ;     

    }

    // fill it is a DAOD
    fillIsAOD();

    // Reading into the TEvent
    //event = new xAOD::TEvent(xAOD::TEvent::kBranchAccess);
    if(!m_isAOD)  event = new xAOD::TEvent(xAOD::TEvent::kClassAccess);
    else event = new xAOD::TEvent(xAOD::TEvent::kAthenaAccess);

    //event = new xAOD::TEvent(xAOD::TEvent::kAthenaAccess);
    RETURN_CHECK( "EventContainer", event->readFrom( m_chain ) ); // All dictionaries are already in memory by now

    // Hack to loop over multiple files in TChain
    Int_t nEvents = event->getEntries();
    LOG(logINFO) <<"Num Event = "<<nEvents;


    // If nEvents == 0, the DxAOD doesn't have any event
    if(nEvents == 0)
    {
        // Just make sure that it is really missing
        TFile* dummyFile = TFile::Open( m_inputFileNames[ 0 ].c_str());
        if(dummyFile->Get("CollectionTree") == 0)
        {
            // really not file
            LOG(logINFO)<<"No file found - will exit gracefully";
            // Create the output file so Grid doesn't complain
            TFile* tempFile = new TFile(outputBaseName+"_nom.root", "recreate");
            tempFile->Close();           
            tempFile = new TFile(outputBaseName+"_BkgCR.root", "recreate");
            tempFile->Close();
            tempFile = new TFile(outputBaseName+"_Zplusl.root", "recreate");
            tempFile->Close();
            exit(-1);
        }
    }

    // Intial info
    event->getEntry(0); 
    RETURN_CHECK("AnalysisBase::process()", event->retrieve( eventInfo, "EventInfo" ) );

    // Initial information for event 
    isMC = false;
    if(eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) {isMC = true;}
    runNumber = eventInfo->runNumber();
    if(isMC) mcChannelNumber = getDSID();
    
    // check if it is a truth DAOD
    fillIsDAODTRUTH();
    if (this->m_isDAODTRUTH && mcChannelNumber == 0)
    {
        mcChannelNumber = eventInfo->runNumber();
    }


    // To fill the sample type
    fillSampleTypeHiggsMass();
    fillNoTau();
    fillAFII();
    fillGeneratorInfo();


    // Debug Ouptut
    LOG(logINFO) << "isMC: "<<isMC;
    if(sampleType == SampleType::data){LOG(logINFO) << "Sample Type: data";}
    if(sampleType == SampleType::ggF) {LOG(logINFO) << "Sample Type: ggF";}
    if(sampleType == SampleType::VBF) {LOG(logINFO) << "Sample Type: VBF";}
    if(sampleType == SampleType::WH)  {LOG(logINFO) << "Sample Type: WH";}
    if(sampleType == SampleType::WpH) {LOG(logINFO) << "Sample Type: WpH";}
    if(sampleType == SampleType::WmH) {LOG(logINFO) << "Sample Type: WmH";}
    if(sampleType == SampleType::ZH)  {LOG(logINFO) << "Sample Type: ZH";}
    if(sampleType == SampleType::ttH) {LOG(logINFO) << "Sample Type: ttH";}
    if(sampleType == SampleType::bbH) {LOG(logINFO) << "Sample Type: bbH";}
    if(sampleType == SampleType::Background) {LOG(logINFO) << "Sample Type: Background";}
    LOG(logINFO) << "Higgs Mass: "<<mHTrue;
    LOG(logINFO) << "is NoTau: "<<isNoTau;
    LOG(logINFO) << "is AFII: "<<m_AFII;


    // TStore
    store = new xAOD::TStore();

    hasInit = true;

    return true;

}



// To increment Counter
Bool_t EventContainer::getEntry(Int_t i)
{       
    // Getting the entry
    event->getEntry(i);
    m_eventIndex = i;

    RETURN_CHECK("AnalysisBase::process()", event->retrieve( eventInfo, "EventInfo" ) );

    eventNumber = eventInfo->eventNumber();
    //LOG(logINFO) << "the event number is : " << eventNumber;

    return true;

}


// To fill the sample Type
void EventContainer::fillSampleTypeHiggsMass()
{
    if(!isMC)
    {
        sampleType = SampleType::data;
        mHTrue = -1;
        return;
    }

    // Splitting the file path
    TObjArray *parts = fileName.Tokenize(".");
    vector<TString> partName;
    if(parts->GetEntriesFast()) {
        TIter iString(parts);
        TObjString* os=0;
        while ((os=(TObjString*)iString())) {
            partName.push_back(os->GetString());
        }
    }

    // To loop over all the parts
    Int_t nMax = partName.size();

    for(Int_t i = 0; i < nMax; i++)
    { 
        // Getting the first part of the container name
        if(partName[i].Contains("TeV") 
                || partName[i].Contains("valid") 
                || partName[i].Contains("angabrie") // hack for Andrea's samples
                || partName[i].Contains("salvucci") // hack for Antonio's samples
                || partName[i].Contains("jomeyer") // hack for jochen's samples
                || partName[i].Contains("sabidi") // hack for Haider's samples
                || (!fileName.Contains("TeV") && partName[i].Contains("phys-higgs") && !fileName.Contains("sabidi"))
                )
        { 
            int initialI = i;
            //cout << name << ":  ";
            // Getting the mc Run Number
            Int_t j = i + 1;
            TString numSample = partName[j];
            mcRunNumber = numSample.Atoi();

            // Disable this check for truth DAOD as they don't have the mcchannelnumber
            if(!m_isDAODTRUTH)
            {
                if(mcRunNumber != mcChannelNumber)
                {
                    LOG(logERROR) << "MC runNumber does not match the file runNumber";
                    LOG(logERROR) << "MC runNumber: "<<mcChannelNumber;
                    LOG(logERROR) << "File runNumber: "<< mcRunNumber;
                    exit(1);
                }
            }

            
            // Higgs mass is 2 aways
            Int_t indexStart = 0;
            i = i+2;

            if(partName[initialI].Contains("salvucci")) i =  j;

            
            
            // Find the sample type and the start index of the mass
            //
            //
            if(partName[initialI].Contains("angabrie")) 
            {
                indexStart = -2;
                sampleType = SampleType::ggF;
            }
            else if(partName[i].Contains("MCFMPythia8EvtGen_ggH_ZZ")) 
            {
                indexStart = -2;
                sampleType = SampleType::Background;
            }
            // veto SBI
            else if(partName[i].Contains("ggH")&& !partName[i].Contains("MCFMPythia8EvtGen_ggH_gg_ZZ")) 
            {
                indexStart = partName[i].Index("ggH") + 3;
                sampleType = SampleType::ggF;
            }
            else if(partName[i].Contains("VBF"))
            {
                indexStart = partName[i].Index("VBF") + 3;
                // workaround for VBFH sample
                if(partName[i].Contains("VBFH")) indexStart++;
                sampleType = SampleType::VBF;
            }
            else if(partName[i].Contains("vbfhzz4l"))
            {
                // EFT workaround
                indexStart = -2;
                isEFT = true;
                sampleType = SampleType::VBF;
            }
            else if(partName[i].Contains("vhlep125"))
            {
                // EFT workaround
                indexStart = -2;
                isEFT = true;
                sampleType = SampleType::VBF;
            }
            else if(partName[i].Contains("FxFx"))
            {
                // EFT workaround
                indexStart = -2;
                isEFT = true;                
                sampleType = SampleType::ggF;
            }
            else if(partName[i].Contains("_HZZ4l"))
            {
                TString str = "_HZZ4l";
                indexStart = partName[i].Index(str) + str.Length();
                sampleType = SampleType::ggF;
            }
            else if(partName[i].Contains("WH"))
            {
                indexStart = partName[i].Index("WH") + 2;
                sampleType = SampleType::WH;
            }
            else if(partName[i].Contains("WpH"))
            {
                indexStart = partName[i].Index("WpH") + 3;
                sampleType = SampleType::WpH;
            }
            else if(partName[i].Contains("WmH"))
            {
                indexStart = partName[i].Index("WmH") + 3;
                sampleType = SampleType::WmH;
            }
            else if(partName[i].Contains("ZH"))
            {
                indexStart = partName[i].Index("ZH") + 2;
                sampleType = SampleType::ZH;
            }
            else if(partName[i].Contains("bbH"))
            {
                //cout<<"ttH Sample ";
                indexStart = partName[i].Index("bbH") + 3;
                sampleType = SampleType::bbH;
            }
            else if(partName[i].Contains("ttH"))
            {
                //cout<<"ttH Sample ";
                indexStart = partName[i].Index("ttH") + 3;
                sampleType = SampleType::ttH;
            }
            else
            {
                sampleType = SampleType::Background;
                mHTrue = -1;
                return;
            }

            // Now looping over the name to find where the mass term ends
            if(indexStart == -2)
            {
                // EFT sample workaround
                mHTrue = 125;
                return;
            }

            // Now looping over the name to find where the mass term ends 
            TString nameSample = partName[i];

            Int_t indexEnd = indexStart;
            Int_t len = 0;
            TString charac = nameSample[indexEnd];
            do
            {
                indexEnd++;
                len++;
                charac = nameSample[indexEnd];
            }while(charac.IsDec());

            // For the decimal place
            Double_t decimalMass = 0;

            if(nameSample[indexEnd] == 'p')
            {
                //cout<<"There is a point"<<endl;
                Int_t indexEndDec = indexEnd + 1;
                Double_t lenDec = 0;
                TString characDec = nameSample[indexEndDec];
                do
                {
                    indexEndDec++;
                    lenDec++;
                    characDec = nameSample[indexEndDec];
                }while(characDec.IsDec());
                TString higgsMassDecStr = nameSample(indexEnd + 1, lenDec);
                decimalMass = higgsMassDecStr.Atoi();

                // Fix the decimal place
                decimalMass = decimalMass/pow(10.0, lenDec);
                //cout<<"Decimal Mass Higgs: "<<decimalMass<<endl;
            }

            // Getting the mass and returning it
            TString higgsMassStr = nameSample(indexStart, len);
            Int_t higgsMass = higgsMassStr.Atoi();

            mHTrue = higgsMass+decimalMass;
            delete parts;
            return;
        }
    }
    LOG(logERROR)<< "EventContainer: Something went wrong with the sampleProduciton type";
    exit(1);
}



void EventContainer::fillNoTau()
{
    if(!isMC) 
    {
        isNoTau = false;
        return;
    }

    if(fileName.Contains("noTau")) isNoTau = true;
    else if(fileName.Contains("notau")) isNoTau = true;
    else if (mcChannelNumber >= 342561 && mcChannelNumber <= 342569) isNoTau = true; //ttH sample
    else if (mcRunNumber >= 342561 && mcRunNumber <= 342569) isNoTau = true; //ttH sample
    else if (mcRunNumber == 345060) isNoTau = true; //ggF NNLOPS sample
    else isNoTau = false;
}

void EventContainer::fillAFII()
{
    if(!isMC) m_AFII = false;

    // This is not ready at the moment in the DAODs
    //string simFlavour = "";
    //// check the metadata first
    //if (this->getEvent()->containsMeta<xAOD::FileMetaData>("FileMetaData")) 
    //{
    //    const xAOD::FileMetaData* fmd = 0;
    //    if(this->getEvent()->retrieveMetaInput(fmd, "FileMetaData"))
    //    {
    //        fmd->value(xAOD::FileMetaData::simFlavour, simFlavour);
    //    }
    //}
   
    
    if(fileName.Contains("_a")) m_AFII = true;
    else m_AFII = false;
}

void EventContainer::fillEventHist()
{
    if(!isMC) return;
    if(m_isDAODTRUTH) return;

    for(size_t i = 0; i < m_inputFileNames.size(); ++i ) 
    {
        TFile* tempFile = TFile::Open( m_inputFileNames[ i ].c_str(), "READ" );
        // get the MetaData tree once a new file is opened, with
        TTree *MetaData = dynamic_cast<TTree*>(tempFile->Get("MetaData"));
        if (!MetaData) {
            // TODO: report Error and return FAILURE?
            LOG(logWARNING)<<"EventContainer::fillEventHist() - metadata not found";
            delete tempFile;
            continue;
        }
        MetaData->LoadTree(0);

        //check if file is from a DxAOD
        bool m_isDerivation = !MetaData->GetBranch("StreamAOD"); 
        if(m_isDerivation)
        {
            // Create a new TEvent for this file 
            // and read it from this file
            xAOD::TEvent* eventTemp =0; 
            eventTemp = new xAOD::TEvent(xAOD::TEvent::kClassAccess);            
            eventTemp->readFrom( tempFile ).ignore(); // All dictionaries are already
            eventTemp->setActive();
            eventTemp->getEntry(0);

            // Now, let's find the actual information
            const xAOD::CutBookkeeperContainer* completeCBC = 0;
            if(!eventTemp->retrieveMetaInput(completeCBC, "CutBookkeepers").isSuccess())
            {
                LOG(logERROR)<<"Failed to retrieve CutBookkeepers from MetaData! Exiting.";
                exit(1);
            }

            // Info on the DxAOD
            const xAOD::CutBookkeeper* DxAODEventsCBK=0;
            std::string derivationName = getKernelName().Data(); //need to replace by appropriate name
            for ( auto cbk :  *completeCBC ) 
            {
                TString nameCBK = cbk->name();
                if (nameCBK.Contains(derivationName))
                    DxAODEventsCBK = cbk;
            }
            // New for 20.7
            int maxcycle=-1;
            int var_count=-1;
            const xAOD::CutBookkeeper* allEventsCBK = 0;
            //let's find the right CBK (latest with StreaAOD input before derivations)
            for ( auto cbk : *completeCBC ) {
                //std::cout << cbk->nameIdentifier() << " : " << cbk->name() << " : desc = " << cbk->description()
                //       << " : inputStream = " << cbk->inputStream()  << " : outputStreams = " << (cbk->outputStreams().size() ? cbk->outputStreams()[0] : "")
                //       << " : cycle = " << cbk->cycle() << " :  allEvents = " << cbk->nAcceptedEvents() << " :  sumOfEventWeights = " << cbk->sumOfEventWeights()
                //       << std::endl;


                TString bookkeeperName = "AllExecutedEvents";
                if (mcRunNumber == 345060) bookkeeperName = "LHE3Weight_nnlops-nominal";
                
                if ( cbk->name() == bookkeeperName && cbk->inputStream() == "StreamAOD" && cbk->cycle() > maxcycle){
                    maxcycle = cbk->cycle();
                    allEventsCBK = cbk;
                }

                // For the systematic variations
                if (outTree->isTHistVar("VariationHist") ) {
                    if ( ((cbk->name()).find("LHE3Weight") != std::string::npos) && (cbk->inputStream() == "StreamAOD") ){
                        var_count++;
                        //variation weights
                        outTree->updateHistVar("VariationHist", var_count, cbk->sumOfEventWeights());
                        outTree->updateHistBinName("VariationHist", var_count, cbk->name());
                        //std::cout<<cbk->name()<<" var_count: "<<var_count<<" cbk: "<<cbk->sumOfEventWeights()<<std::endl;
                    }
                }
            }

            if(allEventsCBK == 0 || DxAODEventsCBK == 0)
            {
                LOG(logERROR)<<"Couldn't find bookkeeper";
                //return;
                exit(1);

            }

            outTree->updateHistVar("CountingHist", 3, allEventsCBK->nAcceptedEvents()); // nEvents intial
            outTree->updateHistVar("CountingHist", 4, DxAODEventsCBK->nAcceptedEvents()); // nEvents selected in DxAOD

            outTree->updateHistVar("CountingHist", 5, allEventsCBK->sumOfEventWeights()); // sumOfWeights intial
            outTree->updateHistVar("CountingHist", 6, DxAODEventsCBK->sumOfEventWeights()); // sumOfWeights selected in DxAOD
            // Clean up memory
            delete eventTemp;
            // set the normal TEvent as the active one
            event->setActive();
        }
        else
        {
            // For AOD
            xAOD::TEvent* eventTemp =0; 
            eventTemp = new xAOD::TEvent(xAOD::TEvent::kAthenaAccess);
            //xAOD::TEvent* eventTemp = new xAOD::TEvent(xAOD::TEvent::kAthenaAccess);
            eventTemp->readFrom( tempFile ).ignore(); // All dictionaries are already
            eventTemp->setActive();
            eventTemp->getEntry(0);

            // Now, let's find the actual information
            const xAOD::CutBookkeeperContainer* completeCBC = 0;
            if(!eventTemp->retrieveMetaInput(completeCBC, "CutBookkeepers").isSuccess())
            {
                LOG(logERROR)<<"Failed to retrieve CutBookkeepers from MetaData! Exiting.";
                exit(1);
            }

            // New for 20.7
            int maxcycle=-1;
            int var_count=-1;
            const xAOD::CutBookkeeper* allEventsCBK = 0;
            //let's find the right CBK (latest with StreaAOD input before derivations)
            for ( auto cbk : *completeCBC ) {
                 LOG(logINFO) << cbk->nameIdentifier() << " : " << cbk->name() 
                     << " : desc = " << cbk->description()
                     << " : inputStream = " << cbk->inputStream()  
                     << " : outputStreams = " << (cbk->outputStreams().size() ? cbk->outputStreams()[0] : "")
                     << " : cycle = " << cbk->cycle() << " :  allEvents = " << cbk->nAcceptedEvents();

                if ( cbk->name() == "AllExecutedEvents" && cbk->inputStream() == "StreamAOD" && cbk->cycle() > maxcycle){
                    maxcycle = cbk->cycle();
                    allEventsCBK = cbk;
                }
                // For the systematic variations
                if (outTree->isTHistVar("VariationHist") ) {
                    if ( ((cbk->name()).find("LHE3Weight") != std::string::npos) && (cbk->inputStream() == "StreamAOD") ){
                        var_count++;
                        //variation weights
                        outTree->updateHistVar("VariationHist", var_count, cbk->sumOfEventWeights());
                        outTree->updateHistBinName("VariationHist", var_count, cbk->name());
                        //std::cout<<cbk->name()<<" var_count: "<<var_count<<" cbk: "<<cbk->sumOfEventWeights()<<std::endl;
                    }
                }
            }

            if(allEventsCBK == 0)
            {
                LOG(logERROR)<<"Couldn't find bookkeeper";
                exit(1);
            }

            outTree->updateHistVar("CountingHist", 3, allEventsCBK->nAcceptedEvents()); // nEvents intial
            outTree->updateHistVar("CountingHist", 4, allEventsCBK->nAcceptedEvents()); // nEvents selected in AOD
            outTree->updateHistVar("CountingHist", 5, allEventsCBK->sumOfEventWeights()); // sumOfWeights intial
            outTree->updateHistVar("CountingHist", 6, allEventsCBK->sumOfEventWeights()); // sumOfWeights in AOD
            // Clean up memory
            delete eventTemp;
            // set the normal TEvent as the active one
            event->setActive();

        }
        delete tempFile;
    }
}


TString EventContainer::getKernelName()
{

    TString kernelName = "";
    // Splitting the file path
    TObjArray *parts = fileName.Tokenize(".");
    vector<TString> partName;
    if(parts->GetEntriesFast()) {
        TIter iString(parts);
        TObjString* os=0;
        while ((os=(TObjString*)iString())) {
            partName.push_back(os->GetString());
        }
    }

    // To loop over all the parts
    Int_t nMax = partName.size();

    for(Int_t i = 0; i < nMax; i++)
    {
        // Getting the first part of the container name
        if(partName[i].Contains("DAOD"))
        {
            TObjArray *parts = partName[i].Tokenize("_");
            vector<TString> kernelNamePart;
            if(parts->GetEntriesFast()) {
                TIter iString(parts);
                TObjString* os=0;
                while ((os=(TObjString*)iString())) {
                    kernelNamePart.push_back(os->GetString());
                }
            }

            if(kernelNamePart.size() > 1)
            {
                kernelName = kernelNamePart[1] + "Kernel";
                return kernelName;
            }
        }

        else if(partName[i].Contains(".AOD."))
        {
            LOG(logERROR)<<"EventContainer::getKernelName() - Kernel name is being requested, however the fileName isn't a DAOD file";
            exit(1);
        }

    }
    return kernelName;
}


// Fills is the current file is a truth DAOD
void EventContainer::fillIsDAODTRUTH()
{
    if(!isMC) return;

    // Assume that atleast one file is there already
    TFile* tempFile = TFile::Open( m_inputFileNames[ 0 ].c_str(), "READ" );
    // get the MetaData tree once a new file is opened, with
    TTree *MetaData = dynamic_cast<TTree*>(tempFile->Get("MetaData"));
    if (!MetaData) {
        // TODO: report Error and return FAILURE?
        LOG(logWARNING)<<"EventContainer::fillIsDAODTRUTH() - metadata not found";
        delete tempFile;
        return;
    }
    MetaData->LoadTree(0);

    //check if file is from a DxAOD
    if(MetaData->GetBranch("StreamDAOD_TRUTH0")) m_isDAODTRUTH = true; 
    if(MetaData->GetBranch("StreamDAOD_TRUTH1")) m_isDAODTRUTH = true; 
    if(MetaData->GetBranch("StreamDAOD_TRUTH2")) m_isDAODTRUTH = true; 
    if(MetaData->GetBranch("StreamDAOD_TRUTH3")) m_isDAODTRUTH = true; 
    if(MetaData->GetBranch("StreamDAOD_TRUTH4")) m_isDAODTRUTH = true; 


    if(m_isDAODTRUTH)
    {
        LOG(logINFO)<<"DAOD_TRUTH sample found";
        LOG(logINFO)<<"The rest of the analysis will be treated as such (many features and checks have been disabled)";
    }

    delete tempFile;
}

// Fills is the current file is a truth DAOD
void EventContainer::fillIsAOD()
{
    if(fileName.Contains("AOD") && !fileName.Contains("DAOD")) m_isAOD = true;
    LOG(logINFO)<<"Is AOD: "<<m_isAOD;
}

void EventContainer::fillGeneratorInfo()
{
    if(fileName.Contains("aMcAtNloHerwigppEvtGen")) m_currGenerator = Generator::aMcAtNloHerwigppEvtGen;
    if(fileName.Contains("aMcAtNloPythia8EvtGen")) m_currGenerator = Generator::aMcAtNloPythia8;
    if(fileName.Contains("MadGraphPythia8EvtGen") || fileName.Contains("MGPy8EG")) m_currGenerator = Generator::MadGraphPythia8;
    if(fileName.Contains("Sherpa")) m_currGenerator = Generator::Sherpa;
    if(fileName.Contains("MCFMPythia8EvtGen")) m_currGenerator = Generator::MCFMPythia8;

    LOG(logINFO)<<"current generator: "<<m_currGenerator;
    //if(fileName.Contains("angabrie")) m_currGenerator = Generator::MadGraphPythia8;
}
Int_t EventContainer::getDSID(){
    Int_t DSID = eventInfo->mcChannelNumber();
    if (m_isDAODTRUTH && DSID == 0)
    {
        DSID = eventInfo->runNumber();
    }
    return DSID;
}
