/* 
 * The followin information is extracted using Marjorie's script as expelained at
 * https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/LHE3EventWeights
 *
 * As input, files downloiaded by Jared Vasquez are used
 * checkMetaSG.py /eos/atlas/user/j/jvasquez/public/mc15_13TeV.345319.PowhegPythia8EvtGen_NNPDF30_AZNLO_ZH125J_Hyy_Zincl_MINLO.merge.DAOD_HIGG1D1.e5743_s2726_r7772_r7676_p3015/DAOD_HIGG1D1.10803453._000002.pool.root.1 | tee metadata_ZH.txt
 * Exactly the same structre is observed in the W+H and W-H samples (also downloaded by Jared)
 *
 * from makeWeightMetaData import *
 * dsid=0
 * makeWeightMetaData("metadata_ZH.txt",dsid,"meta_ZH.h")
 * 
 * Slightly reformatting the output to get a vector of strings
 * grep var meta_WmH.h | grep inser |grep -v 150\, | cut -f3 -d'(' | cut -f1 -d')' | awk -F'", ' '{print $2"--"$1"\""}' | sort -n 
 * 
 */

// Local include(s):
#include "TruthWeightTools/HiggsWeightTool.h"
#include <vector>
#include <string>

const std::vector<std::string> xAOD::HiggsWeightTool::getDefaultVHweightNames() {
  return {"nominal ",
      " muR = 0.5, muF = 1.0 ",
      " muR = 2.0, muF = 1.0 ",
      " muR = 1.0, muF = 0.5 ",
      " muR = 0.5, muF = 0.5 ",
      " muR = 2.0, muF = 0.5 ",
      " muR = 1.0, muF = 2.0 ",
      " muR = 0.5, muF = 2.0 ",
      " muR = 2.0, muF = 2.0 ",
      " PDF set = 260001 ",
      " PDF set = 260002 ",
      " PDF set = 260003 ",
      " PDF set = 260004 ",
      " PDF set = 260005 ",
      " PDF set = 260006 ",
      " PDF set = 260007 ",
      " PDF set = 260008 ",
      " PDF set = 260009 ",
      " PDF set = 260010 ",
      " PDF set = 260011 ",
      " PDF set = 260012 ",
      " PDF set = 260013 ",
      " PDF set = 260014 ",
      " PDF set = 260015 ",
      " PDF set = 260016 ",
      " PDF set = 260017 ",
      " PDF set = 260018 ",
      " PDF set = 260019 ",
      " PDF set = 260020 ",
      " PDF set = 260021 ",
      " PDF set = 260022 ",
      " PDF set = 260023 ",
      " PDF set = 260024 ",
      " PDF set = 260025 ",
      " PDF set = 260026 ",
      " PDF set = 260027 ",
      " PDF set = 260028 ",
      " PDF set = 260029 ",
      " PDF set = 260030 ",
      " PDF set = 260031 ",
      " PDF set = 260032 ",
      " PDF set = 260033 ",
      " PDF set = 260034 ",
      " PDF set = 260035 ",
      " PDF set = 260036 ",
      " PDF set = 260037 ",
      " PDF set = 260038 ",
      " PDF set = 260039 ",
      " PDF set = 260040 ",
      " PDF set = 260041 ",
      " PDF set = 260042 ",
      " PDF set = 260043 ",
      " PDF set = 260044 ",
      " PDF set = 260045 ",
      " PDF set = 260046 ",
      " PDF set = 260047 ",
      " PDF set = 260048 ",
      " PDF set = 260049 ",
      " PDF set = 260050 ",
      " PDF set = 260051 ",
      " PDF set = 260052 ",
      " PDF set = 260053 ",
      " PDF set = 260054 ",
      " PDF set = 260055 ",
      " PDF set = 260056 ",
      " PDF set = 260057 ",
      " PDF set = 260058 ",
      " PDF set = 260059 ",
      " PDF set = 260060 ",
      " PDF set = 260061 ",
      " PDF set = 260062 ",
      " PDF set = 260063 ",
      " PDF set = 260064 ",
      " PDF set = 260065 ",
      " PDF set = 260066 ",
      " PDF set = 260067 ",
      " PDF set = 260068 ",
      " PDF set = 260069 ",
      " PDF set = 260070 ",
      " PDF set = 260071 ",
      " PDF set = 260072 ",
      " PDF set = 260073 ",
      " PDF set = 260074 ",
      " PDF set = 260075 ",
      " PDF set = 260076 ",
      " PDF set = 260077 ",
      " PDF set = 260078 ",
      " PDF set = 260079 ",
      " PDF set = 260080 ",
      " PDF set = 260081 ",
      " PDF set = 260082 ",
      " PDF set = 260083 ",
      " PDF set = 260084 ",
      " PDF set = 260085 ",
      " PDF set = 260086 ",
      " PDF set = 260087 ",
      " PDF set = 260088 ",
      " PDF set = 260089 ",
      " PDF set = 260090 ",
      " PDF set = 260091 ",
      " PDF set = 260092 ",
      " PDF set = 260093 ",
      " PDF set = 260094 ",
      " PDF set = 260095 ",
      " PDF set = 260096 ",
      " PDF set = 260097 ",
      " PDF set = 260098 ",
      " PDF set = 260099 ",
      " PDF set = 260100 ",
      " PDF set = 90400 ",
      " PDF set = 90401 ",
      " PDF set = 90402 ",
      " PDF set = 90403 ",
      " PDF set = 90404 ",
      " PDF set = 90405 ",
      " PDF set = 90406 ",
      " PDF set = 90407 ",
      " PDF set = 90408 ",
      " PDF set = 90409 ",
      " PDF set = 90410 ",
      " PDF set = 90411 ",
      " PDF set = 90412 ",
      " PDF set = 90413 ",
      " PDF set = 90414 ",
      " PDF set = 90415 ",
      " PDF set = 90416 ",
      " PDF set = 90417 ",
      " PDF set = 90418 ",
      " PDF set = 90419 ",
      " PDF set = 90420 ",
      " PDF set = 90421 ",
      " PDF set = 90422 ",
      " PDF set = 90423 ",
      " PDF set = 90424 ",
      " PDF set = 90425 ",
      " PDF set = 90426 ",
      " PDF set = 90427 ",
      " PDF set = 90428 ",
      " PDF set = 90429 ",
      " PDF set = 90430 ",
      " PDF set = 90431 ",
      " PDF set = 90432 "};
}
      