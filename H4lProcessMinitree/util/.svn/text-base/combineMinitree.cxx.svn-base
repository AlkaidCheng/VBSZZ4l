#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <vector>
#include <TString.h>

#include "H4lProcessMinitree/ProcessMinitree.h"

using namespace std;


// Functions
// For parsing the input
bool cmdline(int argc, char** argv, map<TString,TString>& opts);


// options
map<TString,TString> opts;


int main(int argc, char** argv)
{
    // Parce the input
    if (!cmdline(argc,argv,opts)) return 0;


    // create the object and pass along the info
    ProcessMinitree proc;

    proc.setInFile(opts["inputFile"]);
    proc.setOutFolder(opts["outputDir"]);

    // doDebug
    if (opts["doDebug"] == "true") {
        std::cout << "Set doDebug" << std::endl;
        proc.setDoDebug();
    }

    // do vertex cut
    if (opts["doVrtCut"] == "true") {
        std::cout << "Set do vertex cut" << std::endl;
        proc.setDoVrtCut();
    }
    
    // do ggF Higgs pt re-weighting
    if (opts["doPtReweighting"] == "true") {
        std::cout << "Set do ggF Higgs pt reweighting" << std::endl;
        proc.setDoPtReweighting();
    }
    
    // do XS fix (originally for Sherpa) - re-estimates the x-section from bkgCrossSection
    if (opts["doXSFix"] == "true") {
        std::cout << "Set XS fix" << std::endl;
        proc.setDoXSFix();
    }

    // do branching ratio fix - re-estimate the ZZ -> 4l branching ratio for each event
    if (opts["doBRFix"] == "true") {
        std::cout << "Set BR fix" << std::endl;
        proc.setDoBRFix();
    }

    if (opts["doMELA"] == "true") {
	std::cout << "Set MELA" << std::endl;
	proc.setAddMELA();
    }

    // do m_H shift to 125.09 - shift all m4l by +0.09, recompute XS and BR with M_H - 125.09 GeV
    if (opts["doMHShift"] == "true") {
        std::cout << "Set m_H shift" << std::endl;
        proc.setDoMHShift();
    }

    // apply new isolation cuts
    if (opts["doIsoCuts"] == "false") {
        // Default value - option was not selected so nothing to be done
    }
    else if (opts["doIsoCuts"] == "std") {
        std::cout << "Apply isolation cuts - use standard cuts" << std::endl;
        proc.setDoIsoCuts(false);
    }
    else if (opts["doIsoCuts"] == "opt") {
        std::cout << "Apply isolation cuts - use optimized cuts" << std::endl;
        proc.setDoIsoCuts(true);
    }
    else {
        std::cout << "Please specify 'std' or 'opt' for --doIsoCuts" << std::endl;
        exit(1);
    }
    
    
    // blind data
    if (opts["blindData"] == "true") {
        std::cout << "Unblind data" << std::endl;
        proc.setBlindData(true);
    }

    // add GRL xml file
    if (opts["xmlGRL"] != "") {
        proc.setXML4GRL(opts["xmlGRL"]);
    }

    // GRL pass-through - don't apply GRL
    if (opts["ignoreGRL"] == "true") {
        proc.setIgnoreGRL();
    }

    // Don't apply trigger selection - only for data
    if (opts["ignoreTrig"] == "true") {
        proc.setIgnoreTrig();
    }

    // Start the process
    proc.process();

}


bool cmdline(int argc, char** argv, map<TString,TString>& opts)
{
    opts.clear();

    // defaults
    opts["inputFile"]       = "ProcessMinitree/data/fileList.txt";
    opts["outputDir"]       = "ProcessMinitree/output/";
    opts["doDebug"]         = "false";
    opts["doVrtCut"]        = "false";
    opts["doPtReweighting"] = "false";
    opts["doXSFix"]         = "false";
    opts["doBRFix"]         = "false";
    opts["doMELA"]	    = "false";
    opts["doMHShift"]       = "false";
    opts["doNewIsoCuts"]    = "false";
    opts["blindData"]       = "false";
    opts["xmlGRL"]          = "";
    opts["ignoreGRL"]       = "false";
    opts["ignoreTrig"]      = "false";
    opts["doIsoCuts"]       = "false"; // false means 'not selected'

    for (int i=1;i<argc;i++) {

        string opt=argv[i];

        if (opt=="--help" || opt=="-h") {
            cout << "--inputFile       : .txt file containing the list + address of MC samples to run over" << endl;
            cout << "--outputDir       : output folder where the minitrees will be stored" << endl;
            cout << "--doDebug         : print out debug output" << endl;
            cout << "--doVrtCut        : use to apply the vertex cut, currently, sets the weight to zero - set this to false for 20.1 minitree" << endl;
            cout << "--doPtReweighting : use to apply Higgs pt reweighting (only affect ggF events)" << endl;
            cout << "--doXSFix         : use to apply x-section fix - reestimate the bkg x-section from tool" << endl;
            cout << "--doBRFix         : use to apply branching ratio fix - reestimate the ZZ -> 4l BR from tool" << endl;
	    cout << "--doMELA          : use to to add the MCFM-based matrix elements used in the MELA" << endl;
            cout << "--doMHShift       : use to shift all m4l variables by 0.09, take XS and BR for m_H = 125.09 GeV" << endl;
            cout << "--doIsoCuts       : use to apply new isolation cuts: arg is either 'std' or 'opt' " << endl;
            cout << "--blindData       : set flag ('true' or 'false') to blind data (default is false)" << endl;
            cout << "--ignoreGRL       : set flag ('true' or 'false') to ignore GRL for data (default is false)" << endl;
            cout << "--ignoreTrig      : set flag ('true' or 'false') to ignore Trig for data (default is false)" << endl;
            cout << "--xmlGRL          : set xml for GRL (seperate multiple files using ,)" << endl;
            return false;
        }

        if(0!=opt.find("--")) {
            cout << "ERROR: options start with '--'!" << endl;
            return false;
        }
        opt.erase(0,2);
        if(opts.find(opt)==opts.end()) {
            cout << "ERROR: invalid option '" << opt << "'!" << endl;
            return false;
        }

        // options without args
        if (opt == "doDebug") {
            opts["doDebug"] = "true";
            continue;
        }
        if (opt == "doVrtCut") {
            opts["doVrtCut"] = "true";
            continue;
        }
        if (opt == "doPtReweighting") {
            opts["doPtReweighting"] = "true";
            continue;
        }
        if (opt == "doXSFix") {
            opts["doXSFix"] = "true";
            continue;
        }
        if (opt == "doBRFix") {
            opts["doBRFix"] = "true";
            continue;
        }
	if (opt == "doMELA") {
	    opts["doMELA"] = "true";
	    continue;
	}
        if (opt == "doMHShift") {
            opts["doMHShift"] = "true";
            continue;
        }
        string nxtopt=argv[i+1];
        if(0==nxtopt.find("-")||i+1>=argc) {
            cout << "ERROR: option '" << opt << "' requires value!" << endl;
            return false;
        }

        opts[opt]=nxtopt;
        i++;
    }

    return true;
}
