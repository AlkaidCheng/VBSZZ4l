// C++ includes
#include <stdlib.h>
#include <iostream>
#include <map>

// Local includes
#include "H4lCutFlow/Analysis4l.h"
#include "H4lCutFlow/AnalysisFiducial.h"
#include "H4lCutFlow/Analysisbkg.h"
#include "HZZCutCommon/AnalysisBase.h"

using namespace std;
// Functions
bool cmdline(int argc, char** argv, map<TString,TString>& opts);

int main(int argc, char** argv)
{
    
    map<TString,TString> opts;
    if (!cmdline(argc,argv,opts)) return 0;
    
    
    cout<<"SampleName: "<<opts["sampleName"]<<endl;
    cout<<"FileName: "<<opts["sampleFile"]<<endl;
    cout<<"OutBaseName: "<<opts["outputBaseName"]<<endl;
    cout<<"systematic: "<<opts["systematic"]<<endl;
    cout<<"analType: "<<opts["analType"]<<endl;
    cout<<"ProdVersion: "<<opts["prodVersion"]<<endl;
    cout<<"Comment: "<<opts["comment"]<<endl;
    
    AnalysisBase* cutflow = 0;
    
    vector<TString> analTypeList;    
    // Splitting the file path
    TObjArray *analParts = opts["analType"].Tokenize(",");
    if(analParts->GetEntriesFast()) {
        TIter iString(analParts);
        TObjString* os=0;
        while ((os=(TObjString*)iString())) {
            TString fileName = os->GetString();
            analTypeList.push_back(fileName.Data());
        }
    }


    // Loop over the multiple analTypes
    for(size_t t = 0; t < analTypeList.size(); t++)
    {
        TString analType = analTypeList[t];
        
        if(analType.Contains("reco"))
        {
            cutflow = new Analysis4l();
        }
        else if(analType.Contains("bkg"))
        {
            cutflow = new Analysisbkg();
        }
        else if(analType.Contains("fid"))
        {
            cutflow = new AnalysisFiducial();
        }
        else
        {
            cout<<"analtype option not recongnized"<<endl;
            cout<<"input option: "<<analType<<endl;
        }


        // Setters for Analysis
        cutflow->setFileName(opts["sampleName"]);

        // Reading the file
        vector<string> inputFilenames;

        // Splitting the file path
        TObjArray *parts = opts["sampleFile"].Tokenize(",");
        if(parts->GetEntriesFast()) {
            TIter iString(parts);
            TObjString* os=0;
            while ((os=(TObjString*)iString())) {
                TString fileName = os->GetString();
                inputFilenames.push_back(fileName.Data());
            }
        }

        cutflow->setFiles(inputFilenames);
        cutflow->setOutName(opts["outputBaseName"]);
        cutflow->setAnalysisType(AnalysisType::Nominal);
        if(opts["analType"].Length() != 0)
        {
            TString analType = opts["analType"];
            if(analType.Contains("fid"))
            {
                cutflow->setAnalysisType(AnalysisType::Fiducial);
            }
        }
        cutflow->setMinitreeVersion(opts["prodVersion"]);
        cutflow->setComment(opts["comment"]);
        cutflow->setCommandOpts(opts);

        vector<TString> sysList;
        if(opts["systematic"].Length() != 0)
        {
            //Splitting the file path
            TObjArray *parts = opts["systematic"].Tokenize(",");
            if(parts->GetEntriesFast()) {
                TIter iString(parts);
                TObjString* os=0;
                while ((os=(TObjString*)iString())) {
                    sysList.push_back(os->GetString());
                }
            }
            cutflow->doSystematic(true, sysList);
        }
        else
        {
            cutflow->doSystematic(false, sysList);
        }

        // Process everything
        cutflow->process();

        // Print the cutflow
        cutflow->printCutFlow();


        delete cutflow;
        inputFilenames.clear();
    }
    return 0;
}


bool cmdline(int argc, char** argv, map<TString,TString>& opts)
{
    opts.clear();
    
    // defaults
    opts["sampleName"]          = "Grid";
    opts["sampleFile"]          = "Grid";
    opts["analType"]            = "reco";
    opts["outputBaseName"]      = "EventSummary";
    opts["systematic"]          = "";
    opts["prodVersion"]         = "";
    opts["doTrigStudy"]         = "false";
    opts["addTheoryVar"]        = "false";
    opts["truthLeptonType"]     = "dressed";
    opts["doMassWindowCut"]     = "true";
    opts["comment"]             = "";
    opts["reducedSys"]          = "";
    opts["fullEgammaSys"]       = "false";
    
    for (int i=1;i<argc;i++) {
        
        string opt=argv[i];
        
        if (opt=="--help") {
            cout<<"-sampleName : name of the Container"<<endl;
            cout<<"-sampleFile : fileName delimted by ,"<<endl;
            cout<<"-outputBaseName : output baseName"<<endl;
            cout<<"-doTrigStudy : save trigger variables to minitree to do efficiency studies."<<endl;
            cout<<"-addTheoryVar : (false, true) save ScalePDF variables to minitree to do theory systematics."<<endl;
            cout<<"-truthLeptonType : choices are bare, born, or dressed."<<endl;
            cout<<"-doMassWindowCut : Only for fiducial analysis. Apply the mass window cut in cutflow."<<endl;
            cout<<"-reducedSys      : (false, true) Only useful if systematics are being run. It set to true, only the reduced systematic set will be run. Default is false"<<endl;
            
            return false;
        }
        
        if(0!=opt.find("-")) {
            cout<<"ERROR: options start with '-'!"<<endl;
            return false;
        }
        opt.erase(0,1);
        if(opts.find(opt)==opts.end()) {
            cout<<"ERROR: invalid option '"<<opt<<"'!"<<endl;
            return false;
        }
        string nxtopt=argv[i+1];
        if(0==nxtopt.find("-")||i+1>=argc) {
            cout<<"ERROR: option '"<<opt<<"' requires value!"<<endl;
            return false;
        }
        
        opts[opt]=nxtopt;
        i++;
    }
    
    return true;
}
