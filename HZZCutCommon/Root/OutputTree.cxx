#include "HZZCutCommon/OutputTree.h"

#include <regex>

using namespace std;

OutputTree::OutputTree(TString outName, TString sysName, TString sampleName)
{
    m_outName = outName;
    m_sampleName = sampleName;

    if(sysName == ""){ m_sysName = ""; }
    else m_sysName = "_" + sysName;
    

    m_isMC = true;
    m_runNumber = -1;

    m_varTool = ToolHandle<ITheoryVariation>("varTool");
    if(m_varTool.retrieve().isFailure())
    {
        LOG(logERROR) <<"OutputTree::OutputTree() - cannot retrieve ITheoryVariation";
        exit(1);
    }

}


OutputTree::~OutputTree()
{
    m_intVar.clear();
    m_floatVar.clear();
    m_doubleVar.clear();
    m_intArrayVar.clear();
    m_floatArrayVar.clear();
    m_intLongVar.clear();
    m_stringVar.clear();

//    For some reason deleting the hist, creates a seg fault..
//    Is there a transfer of ownership when we write a ttree?
//    for (auto it = m_THistVar.begin(); it != m_THistVar.end(); ++it)
//    {
//        delete it->second;
//    }

    m_THistVar.clear();


}


void OutputTree::initialize()
{
    // To initialize all the var
    addVar();
    addHistrogram();
    clearVars();

}


// To clear all the variables
void OutputTree::clearVars()
{
    for (auto it = m_intVar.begin(); it != m_intVar.end(); ++it)
    {
        it->second = -999;
    }
    for (auto it = m_intLongVar.begin(); it != m_intLongVar.end(); ++it)
    {
        it->second = 0;
    }
    for (auto it = m_floatVar.begin(); it != m_floatVar.end(); ++it)
    {
        it->second = -999;
    }
    for (auto it = m_doubleVar.begin(); it != m_doubleVar.end(); ++it)
    {
        it->second = -999;
    }
    for (auto it = m_intArrayVar.begin(); it != m_intArrayVar.end(); ++it)
    {
        it->second = {{-999, -999, -999, -999}};
    }
    for (auto it = m_floatArrayVar.begin(); it != m_floatArrayVar.end(); ++it)
    {
        it->second = {{-999, -999, -999, -999}};
    }
    for (auto it = m_int3ArrayVar.begin(); it != m_int3ArrayVar.end(); ++it)
    {
        it->second = {{-999, -999, -999}};
    }
    for (auto it = m_float3ArrayVar.begin(); it != m_float3ArrayVar.end(); ++it)
    {
        it->second = {{-999, -999, -999}};
    }
    for (auto it = m_stringVar.begin(); it != m_stringVar.end(); ++it)
    {
        it->second = "";
    }

    for(auto& currV:m_intVectorVar)
    {
        currV.second.clear();
    }
    for(auto& currV:m_floatVectorVar)
    {
        currV.second.clear();
    }

}

// Booking the tree
void OutputTree::bookTree(TTree* currTree)
{
    for (auto it = m_intVar.begin(); it != m_intVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName+"/I");
    }
    for (auto it = m_intLongVar.begin(); it != m_intLongVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName+"/l");
    }
    for (auto it = m_floatVar.begin(); it != m_floatVar.end(); ++it)
    {
        TString varName = it->first;        
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName+"/F");
    }
    for (auto it = m_doubleVar.begin(); it != m_doubleVar.end(); ++it)
    {
        TString varName = it->first;        
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName+"/D");
    }
    for (auto it = m_intArrayVar.begin(); it != m_intArrayVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName + "[4]/I");
    }
    for (auto it = m_floatArrayVar.begin(); it != m_floatArrayVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName + "[4]/F");
    }
    for (auto it = m_int3ArrayVar.begin(); it != m_int3ArrayVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName + "[3]/I");
    }
    for (auto it = m_float3ArrayVar.begin(); it != m_float3ArrayVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second, varName + "[3]/F");
    }
    for (auto it = m_stringVar.begin(); it != m_stringVar.end(); ++it)
    {
        TString varName = it->first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &it->second);
    }
    for(auto& currV:m_intVectorVar)
    {
        TString varName = currV.first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &currV.second);
    }
    for(auto& currV:m_floatVectorVar)
    {
        TString varName = currV.first;
        if(isMarkedRemove(varName.Data())) continue;
        currTree->Branch(varName, &currV.second);
    }
}

// Setters
// Updated the values as defined by the outside world.
void OutputTree::updateIntVar(string varName, Int_t varValue)
{
    if(m_intVar.find(varName) != m_intVar.end())
    {
        m_intVar[varName] = varValue;   
    }
    else
    {
        // Aug 8th, removed the hard constraint on the code
        // that the variable must exist, otherwise it was going to exit
        // This to increase the reusability of the code to allow for
        // Calculate4l to be used for bkg minitrees
        return;
        
        LOG(logERROR) <<"OutputTree::updateIntVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }
}

void OutputTree::updateLongIntVar(string varName, ULong64_t varValue)
{
    if(m_intLongVar.find(varName) != m_intLongVar.end())
    {
        m_intLongVar[varName] = varValue;
    }
    else
    {
        // Aug 8th, removed the hard constraint on the code
        // that the variable must exist, otherwise it was going to exit
        // This to increase the reusability of the code to allow for
        // Calculate4l to be used for bkg minitrees
        return;
        
        LOG(logERROR) <<"OutputTree::updateIntVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }
}
void OutputTree::updateFloatVar(string varName, Float_t varValue)
{
    if(m_floatVar.find(varName) != m_floatVar.end())
    {
        m_floatVar[varName] = varValue; 
    }
    else
    {
        // Aug 8th, removed the hard constraint on the code
        // that the variable must exist, otherwise it was going to exit
        // This to increase the reusability of the code to allow for
        // Calculate4l to be used for bkg minitrees
        return;
        
        LOG(logERROR) <<"OutputTree::updateFloatVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }
}

void OutputTree::updateIntArrayVar(std::string varName, std::array<int, 4>varValue)
{
    if(m_intArrayVar.find(varName) != m_intArrayVar.end())
    {
        for(Int_t i = 0; i <(Int_t) varValue.size(); i++)
        {
            m_intArrayVar.at(varName)[i] = varValue[i];
        }
    }
    else
    {
        // Aug 8th, removed the hard constraint on the code
        // that the variable must exist, otherwise it was going to exit
        // This to increase the reusability of the code to allow for
        // Calculate4l to be used for bkg minitrees
        return;
        LOG(logERROR) <<"OutputTree::updateIntArrayVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(-1);
    }
    
}

void OutputTree::updateFloatArrayVar(std::string varName, std::array<float, 4>varValue)
{
    if(m_floatArrayVar.find(varName) != m_floatArrayVar.end())
    {
        for(Int_t i = 0; i <(Int_t) varValue.size(); i++)
        {
            m_floatArrayVar.at(varName)[i] = varValue[i];
        }
    }
    else
    {
        // Aug 8th, removed the hard constraint on the code
        // that the variable must exist, otherwise it was going to exit
        // This to increase the reusability of the code to allow for
        // Calculate4l to be used for bkg minitrees
        return;
        LOG(logERROR) <<"OutputTree::updateFloatArrayVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(-1);
    }
    
}

void OutputTree::updateStringVar(std::string varName, std::string varValue)
{
    if(m_stringVar.find(varName) != m_stringVar.end())
    {
        m_stringVar[varName] = varValue;
    }
    else
    {
        // Aug 8th, removed the hard constraint on the code
        // that the variable must exist, otherwise it was going to exit
        // This to increase the reusability of the code to allow for
        // Calculate4l to be used for bkg minitrees
        return;
        
        LOG(logERROR) <<"OutputTree::updateFloatVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }

}

void OutputTree::updateInt3ArrayVar(std::string varName, std::array<int, 3>varValue)
{
    if(m_int3ArrayVar.find(varName) != m_int3ArrayVar.end())
    {
        for(Int_t i = 0; i <(Int_t) varValue.size(); i++)
        {
            m_int3ArrayVar.at(varName)[i] = varValue[i];
        }
    }
    else
    {
        return;
        LOG(logERROR) <<"OutputTree::updateIntArrayVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(-1);
    }
    
}

void OutputTree::updateFloat3ArrayVar(std::string varName, std::array<float, 3>varValue)
{
    if(m_float3ArrayVar.find(varName) != m_float3ArrayVar.end())
    {
        for(Int_t i = 0; i <(Int_t) varValue.size(); i++)
        {
            m_float3ArrayVar.at(varName)[i] = varValue[i];
        }
    }
    else
    {
        return;
        LOG(logERROR) <<"OutputTree::updateFloatArrayVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(-1);
    }
    
}


void OutputTree::updateHistVar(string varName, Float_t varValue, Float_t weightValue)
{
    if(m_THistVar.find(varName) != m_THistVar.end())
    {
        m_THistVar.at(varName)->Fill(varValue, weightValue);
    }
    else
    {
        LOG(logERROR) <<"OutputTree::updateHistVar() - "<< varName << " Variable not found";
        exit(1);
    }
}

void OutputTree::updateHistBinName(std::string varName, int bin, std::string binName)
{
    if(m_THistVar.find(varName) != m_THistVar.end())
    {
        m_THistVar.at(varName)->GetXaxis()->SetBinLabel(bin+1, binName.c_str());
    }
    else
    {
        LOG(logERROR) <<"OutputTree::updateHistBinName() - "<< varName << " Variable not found";
        exit(1);
    }
}

void OutputTree::updateHistVar(string varName, vector<Int_t> varValue)
{
    for(Int_t i = 0; i < (Int_t) varValue.size(); i++)
    {
        this->updateHistVar(varName, i, varValue.at(i));
    }
}

void OutputTree::updateHistVar(string varName, vector<Float_t> varValue)
{
    for(Int_t i = 0; i < (Int_t) varValue.size(); i++)
    {
        this->updateHistVar(varName, i, varValue.at(i));
    }
}


// Update function
template< class T > 
void OutputTree::updateVar(std::string varName, T varValue )
{
    LOG(logERROR)<<"Class type not supported for updatevar";
    exit(1);
}
// Specfic implementation
template <> 
void OutputTree::updateVar <vector<int>> (std::string varName, vector<int> varValue )
{
    if(m_intVectorVar.find(varName) != m_intVectorVar.end())
    {
        for(const auto val: varValue)
        {
            m_intVectorVar[varName].push_back(val);
        }
    }
}
template <> 
void OutputTree::updateVar <vector<float>> (std::string varName, vector<float> varValue )
{
    LOG(logINFO) <<"Variable requested: "<<varName;

    if(m_floatVectorVar.find(varName) != m_floatVectorVar.end())
    {
        LOG(logINFO) <<"Variable found: "<<varName;        
        for(const auto val: varValue)
        {
            m_floatVectorVar[varName].push_back(val);
        }
    }
}
template <> 
void OutputTree::updateVar <double> (std::string varName, double varValue )
{
    if(m_doubleVar.find(varName) != m_doubleVar.end())
    {
        m_doubleVar[varName] = varValue;
    }
}
// Getter
Int_t OutputTree::getIntVar(std::string varName)
{
    if(m_intVar.find(varName) != m_intVar.end())
    {
        return m_intVar[varName];
    }
    else
    {
        LOG(logERROR) <<"OutputTree::getIntVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }
}

Float_t OutputTree::getFloatVar(std::string varName)
{
    if(m_floatVar.find(varName) != m_floatVar.end())
    {
        return m_floatVar[varName];
    }
    else
    {
        LOG(logERROR) <<"OutputTree::getFloatVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }
}

double OutputTree::getDoubleVar(std::string varName)
{
    if(m_doubleVar.find(varName) != m_doubleVar.end())
    {
        return m_doubleVar[varName];
    }
    else
    {
        LOG(logERROR) <<"OutputTree::getDoubleVar()"<< " Variable not found";
        LOG(logERROR) <<"Variable requested: "<<varName;
        exit(1);
    }
}


// Checks if the variable exits in the tree
Bool_t OutputTree::isIntVar(std::string varName)
{
    if(m_intVar.find(varName) != m_intVar.end())
    {
        return true;
    }
    return false;
}
// Checks if the variable exits
Bool_t OutputTree::isFloatVar(std::string varName)
{
    if(m_floatVar.find(varName) != m_floatVar.end())
    {
        return true;
    }
    return false;
}
Bool_t OutputTree::isDoubleVar(std::string varName)
{
    if(m_doubleVar.find(varName) != m_doubleVar.end())
    {
        return true;
    }
    return false;
}

Bool_t OutputTree::isFloatArrayVar(std::string varName)
{
    if(m_floatArrayVar.find(varName) != m_floatArrayVar.end())
    {
        return true;
    }
    return false;
}

Bool_t OutputTree::isIntArrayVar(std::string varName)
{
    if(m_intArrayVar.find(varName) != m_intArrayVar.end())
    {
        return true;
    }
    return false;
}

Bool_t OutputTree::isTHistVar(std::string varName)
{
    if(m_THistVar.find(varName) != m_THistVar.end())
    {
        return true;
    }
    return false;
}


void OutputTree::addHistrogram()
{
    m_THistVar["CountingHist"] = new TH1F("CountingHist" + m_sysName, "CountingHist", 10, 0, 10);
    m_THistVar["VariationHist"] = new TH1F("VariationHist" + m_sysName, "VariationHist", 200, 0, 200);
    m_THistVar["VariationggFQCDHist"] = new TH1F("VariationHistggfQCD" + m_sysName, "VariationHistggfQCD", 200, 0, 200);
    
}

Bool_t OutputTree::isMarkedRemove(const std::string varName) const
{
    for(auto st: m_varToRemove)
    {
        const boost::regex ex("^"+boost::replace_all_copy(st, "*", "\\S+"));
        string::const_iterator start, end;
        start = varName.begin();
        end = varName.end();
        boost::match_results<std::string::const_iterator> what;
        boost::match_flag_type flags = boost::match_default;
        
        if(boost::regex_search(start, end, what, ex, flags)) return true;
    }
    
    return false;
}


// MetaData
void OutputTree::addMetaData()
{
    m_intMetaData["type"] = -999;
    m_intMetaData["isMC"] = -999;
    m_intMetaData["createdBy"] = -999;
    
    m_stringMetaData["sampleName"] = "";
    m_stringMetaData["systematicVariation"] = "";
    m_stringMetaData["version"] = "";
    m_stringMetaData["comment"] = "";
    
    m_stringMetaData["productionRelease"] = "";
    m_stringMetaData["amiTag"] = "";
    m_stringMetaData["dataType"] = "";
    m_stringMetaData["geometryVersion"] = "";
    m_stringMetaData["conditionsTag"] = "";
}

void OutputTree::addVariationSpecificVar()
{
    //get the map that relates the variation to the index in mcEventWeights
    std::map<std::string, int> weight_vars = m_varTool->execute(m_runNumber);

    for(auto pair: weight_vars)
    {
        TString name = "weight_var_th_"+ m_varTool->getTheorySysName(pair.first);
        LOG(logINFO)<<"Adding Theory sys: "<<name;
        m_doubleVar[name.Data()] = -999;
    }

    if(m_runNumber == 345060)
    {
        LOG(logINFO)<<"Adding QCD ggF vars";
        m_doubleVar["weight_var_th_qcd_wg1_mu"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_res"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_mig01"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_mig12"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_pTH"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_qm_b"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_qm_t"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_vbf2j"] = -999;
        m_doubleVar["weight_var_th_qcd_wg1_vbf3j"] = -999;
        m_doubleVar["weight_var_th_ggF_qcd_stxs_dsig60"] = -999;
        m_doubleVar["weight_var_th_ggF_qcd_stxs_dsig120"] = -999;
        m_doubleVar["weight_var_th_ggF_qcd_stxs_dsig200"] = -999;
        m_doubleVar["weight_var_th_ggF_qcd_2017_pTH60"] = -999;
        m_doubleVar["weight_var_th_ggF_qcd_2017_pTH120"] = -999;

    }
}

void OutputTree::initMetaData()
{
    // To initialize all the var
    addMetaData();
    
    m_metaDataTree    = new TTree("MetaData", "all");
    m_metaDataTree->SetAutoFlush();
    bookMetaDataTree(m_metaDataTree);
}

// Booking the tree
void OutputTree::bookMetaDataTree(TTree* currTree)
{
    for (auto it = m_intMetaData.begin(); it != m_intMetaData.end(); ++it)
    {
        TString varName = it->first;
        currTree->Branch(varName, &it->second, varName+"/I");
    }
    for (auto it = m_stringMetaData.begin(); it != m_stringMetaData.end(); ++it)
    {
        TString varName = it->first;
        currTree->Branch(varName, &it->second);
    }
}

// Update function
template< class T > 
void OutputTree::updateMetaData(std::string varName, T varValue )
{
    LOG(logERROR)<<"Class type not supported for update metadata";
    exit(1);
}
// Specfic implementation
template <> 
void OutputTree::updateMetaData <int> (std::string varName, int varValue )
{
    if(m_intMetaData.find(varName) != m_intMetaData.end())
    {
        m_intMetaData[varName] = varValue;   
    }
}
template <> 
void OutputTree::updateMetaData <std::string> (std::string varName, std::string varValue )
{
    if(m_stringMetaData.find(varName) != m_stringMetaData.end())
    {
        m_stringMetaData[varName] = varValue;   
    }
}
template <> 
void OutputTree::updateMetaData <TString> (std::string varName, TString varValue )
{
    if(m_stringMetaData.find(varName) != m_stringMetaData.end())
    {
        m_stringMetaData[varName] = varValue;   
    }
}


void OutputTree::fillMetaData()
{
    m_metaDataTree->Fill();
}
