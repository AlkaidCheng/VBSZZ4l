#include "HZZUtils/SampleShowerInfo.h"


#include <TString.h>

void SampleShowerInfo::fillEffMapForBTag(std::string& effMap)
{
    // This is mapping from the DSID to Showering
    //"410000" - 0 (Pythia6+EvtGen)
    //"410004" - 1 (HerwigPP+EvtGen)
    //"410500" - 2 (Pythia8+EvtGen)
    //"410187" - 3 (Sherpa v2.2 or newer)
    //"410021" - 4 (Sherpa v2.11 or older)
    effMap = "410000;410004;410500;410187;410021";
}


void SampleShowerInfo::fillSampleShowerInfo(const std::string& containerName, std::string& showerMCName)
{
    TString name(containerName);

    // default option
    showerMCName = "PY6EG";

         if(name.Contains("Pythia8EvtGen"))    showerMCName = "PY8EG";
    else if(name.Contains("Py8EG"))            showerMCName = "PY8EG";
    else if(name.Contains("HerwigppEvtGen"))   showerMCName = "HerwigEG";
    else if(name.Contains("Sherpa_221"))       showerMCName = "Sherpa_221";
    else if(name.Contains("Sherpa_221"))       showerMCName = "Sherpa_221";
    else if(name.Contains("Sherpa"))           showerMCName = "Sherpa";
}

void SampleShowerInfo::fillIndexForBTag(const std::string& containerName, int& index)
{   
    std::string showerMCName = "";
    fillSampleShowerInfo(containerName, showerMCName);

    TString sShowerMCName(showerMCName);

    // default option
    index = 0;

    // The choice here must match the ordering defined in fillEffMapForBtag
         if(sShowerMCName.Contains("PY8EG"))        index = 2;
    else if(sShowerMCName.Contains("PY6EG"))        index = 0;
    else if(sShowerMCName.Contains("HerwigEG"))     index = 1;
    else if(sShowerMCName.Contains("Sherpa_221"))   index = 3;
    else if(sShowerMCName.Contains("Sherpa"))       index = 4;

    return;

}

