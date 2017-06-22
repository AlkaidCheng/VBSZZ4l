#include "HZZUtils/TheoryVariation.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>

#include <regex>
#include <iterator>


TheoryVariation::TheoryVariation(const std::string& name) : AsgTool(  name ){

}

TheoryVariation::~TheoryVariation(){

}

StatusCode TheoryVariation::initialize(){

  #include "Variations/all_channel_variations.h"

  return StatusCode::SUCCESS;
}

StatusCode TheoryVariation::finalize() {

 return StatusCode::SUCCESS;
}

StatusCode TheoryVariation::execute( int chanNumber, std::map<std::string, int>& result) const{
  
  // if channel is not in m_variations, return an empty map.
  // Return 
  if ( m_variations.find(chanNumber) == m_variations.end())
  {
   std::map<std::string, int> emptyMap;
   result= emptyMap;
   ATH_MSG_DEBUG("Channel not in m_variations - returning an empty map.");
   return StatusCode::SUCCESS;
  }
   
  // Otherwise, just return the map
  std::map<std::string, int> my_result = m_variations.at(chanNumber);
  result= my_result;
  return StatusCode::SUCCESS;
}

std::map<std::string, int> TheoryVariation::execute( int chanNumber) const {
  
  // if channel is not in m_variations, return an empty map.
  // Return 
  if ( m_variations.find(chanNumber) == m_variations.end())
  {
   std::map<std::string, int> emptyMap;
   ATH_MSG_DEBUG("Channel not in m_variations - returning an empty map.");
   return emptyMap;
  }
   
  // Otherwise, just return the map
  return m_variations.at(chanNumber);
  
}

TString TheoryVariation::getTheorySysName(const std::string mapSysKey) const
{
    std::string w_name = mapSysKey; //variation
    TString name = "";
    //variation it is and fill the appropriate variable in the minitree. 
        
    // This is for SHERPA... making life hard again.. HA
    if((w_name.find("MUR") != std::string::npos))
    {
        name = w_name;
    }
    else if((w_name.find("PDF") != std::string::npos) || (w_name.find("pdfset") != std::string::npos)) {
        std::regex pdfsearch("\\d+"); //finds the number of the pdfset in the string 
        std::smatch pdfset;
        if(std::regex_search(w_name, pdfset, pdfsearch)) {
            std::string pdf_string = pdfset.str(0);
            name = "pdf_"+pdf_string;
            return name;
        }
        else {
            ATH_MSG_WARNING("TheoryVariation::getTheorySysName - couldn't find weight name for "<< w_name);
            name = "pdf_"+mapSysKey;
        }
    }
    else if((w_name.find("muR") != std::string::npos)) {
        std::regex rsearch("(\\d\\.\\d+)"); //finds the two numbers after muR and muF 
        std::sregex_iterator itWord(w_name.begin(), w_name.end(), rsearch);
        std::sregex_iterator endWord;
        std::vector<std::string> muR_muF;
        while(itWord != endWord) {std::smatch w = *itWord; muR_muF.push_back(w.str()); itWord++;}
        if( muR_muF.size() >= 2) {
            std::string muR_str = muR_muF[0];
            std::string muF_str = muR_muF[1];
            if((muR_str=="0.5"||muR_str=="0.50000") && (muF_str=="0.5"||muF_str=="0.50000")) {
                name = "muR0p5_muF0p5";
            } else if((muR_str=="0.5"||muR_str=="0.50000") && (muF_str=="1.0"||muF_str=="0.10000")) {
                name = "muR0p5_muF1p0";
            } else if((muR_str=="0.5"||muR_str=="0.50000") && (muF_str=="2.0"||muF_str=="0.20000")) {
                name = "muR0p5_muF2p0";
            } else if((muR_str=="1.0"||muR_str=="0.10000") && (muF_str=="0.5"||muF_str=="0.50000")) {
                name = "muR1p0_muF0p5";
            } else if((muR_str=="1.0"||muR_str=="0.10000") && (muF_str=="2.0"||muF_str=="0.20000")) {
                name = "muR1p0_muF2p0";
            } else if((muR_str=="2.0"||muR_str=="0.20000") && (muF_str=="0.5"||muF_str=="0.50000")) {
                name = "muR2p0_muF0p5";
            } else if((muR_str=="2.0"||muR_str=="0.20000") && (muF_str=="1.0"||muF_str=="0.10000")) {
                name = "muR2p0_muF1p0";
            } else if((muR_str=="2.0"||muR_str=="0.20000") && (muF_str=="2.0"||muF_str=="0.20000")) {
                name = "muR2p0_muF2p0";
            } else if((muR_str=="1.0"||muR_str=="0.10000") && (muF_str=="1.0"||muF_str=="0.10000")) {
                name = "muR1p0_muF1p0";
            } 
            else {
                ATH_MSG_WARNING("TheoryVariation::getTheorySysName - couldn't find weight name for "<< w_name);
                name = ""+mapSysKey;
            }
            //LOG(logINFO)<<"weight_var_"+w_name<<" "<<var_weight;
        }
        else {
            ATH_MSG_WARNING("TheoryVariation::getTheorySysName - couldn't find weight name for "<< w_name);
            name = ""+mapSysKey;
            return name;
        }
    }
    else
    {
        name = ""+mapSysKey;        
    }

    name.ReplaceAll("-","_");
    name.ReplaceAll("0.","0p");
    return name;
}

