#ifndef OUTPUTTREE_H
#define OUTPUTTREE_H

// C++ includes
#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>

// Boost includes
#include "boost/regex.hpp"
#include "boost/algorithm/string/replace.hpp"

// Root includes
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TH1F.h"

// Local includes
#include "HZZCutCommon/EnumDefCommon.h"
#include "HZZCutCommon/log.h"
#include "HZZUtils/ITheoryVariation.h"
#include "AsgTools/ToolHandle.h"

class OutputTree 
{
    public:
        OutputTree(TString outName, TString sysName, TString sampleName);
        virtual ~OutputTree();
    
        /// To setup anything depedant on systematics
        virtual void initialize();
    
        /// Fill all the int/float vars with -999
        virtual void clearVars();
    
        /// To update the variables. See comments inside the function
        void updateIntVar(std::string varName, Int_t varValue);
        void updateLongIntVar(std::string varName, ULong64_t varValue);
    
        /// To update the variables. See comments inside the function
        void updateFloatVar(std::string varName, Float_t varValue);
    
        /// To update the variables
        void updateIntArrayVar(std::string varName, std::array<int, 4> varValue);
    
        /// To update the variables
        void updateFloatArrayVar(std::string varName, std::array<float, 4> varValue);
 
        /// To update the variables
        void updateStringVar(std::string varName, std::string varValue);
    
    
        /// For Z+x... Maybe not needed?
        /// We should be able to find some templated fit?
        void updateInt3ArrayVar(std::string varName, std::array<int, 3> varValue);
        void updateFloat3ArrayVar(std::string varName, std::array<float, 3> varValue);

        //add variation variables
        void addVariationSpecificVar();
    
        // Start of the template fit, slowly move the others to match this
        template< class T > void updateMetaData(std::string varName, T varValue );

    
        /// To update the variables
        void updateHistVar(std::string varName, Float_t varValue, Float_t weightValue = 1);
        void updateHistVar(std::string varName, std::vector<Int_t> varValue);
        void updateHistVar(std::string varName, std::vector<Float_t> varValue);
        void updateHistBinName(std::string varName, int bin, std::string binName);

        template< class T > void updateVar(std::string varName, T varValue);
    
        // Getter
        Int_t getIntVar(std::string varName);
        Float_t getFloatVar(std::string varName);
        double getDoubleVar(std::string varName);

    
        // Checks if the variable exits in the tree
        Bool_t isIntVar(std::string varName);
        // Checks if the variable exits
        Bool_t isFloatVar(std::string varName);
        Bool_t isDoubleVar(std::string varName);
        // Checks if the variable exits
        Bool_t isFloatArrayVar(std::string varName);
        Bool_t isIntArrayVar(std::string varName);
        Bool_t isTHistVar(std::string varName);

        /// To write to trees
        virtual void fillTree(OutputTreeType::OutputTreeType type) = 0;
        virtual void fillMetaData();

        /// Final output of trees
        virtual void writeTree() = 0;
 
        void setIsMC(bool isMC) {m_isMC = isMC;};
        void setRunNumber(int runNumber) {m_runNumber = runNumber;};        

    protected:
        // Things which actually store variables
        std::map<std::string, Int_t>                m_intVar;
        std::map<std::string, ULong64_t>            m_intLongVar;
        std::map<std::string, Float_t>              m_floatVar;
        std::map<std::string, double>               m_doubleVar;
        std::map<std::string, std::string>          m_stringVar;
        std::map<std::string, TH1F*>                m_THistVar;
        std::map<std::string, std::array<int, 4>>   m_intArrayVar;
        std::map<std::string, std::array<float, 4>> m_floatArrayVar;
        std::map<std::string, std::array<int, 3>>   m_int3ArrayVar;
        std::map<std::string, std::array<float, 3>> m_float3ArrayVar;
        std::map<std::string, std::vector<int>>     m_intVectorVar;
        std::map<std::string, std::vector<float>>   m_floatVectorVar;
    
        // List of variables to be removed from the outputtree
        std::vector<std::string> m_varToRemove;
    
        TString m_outName;
        TString m_sysName;
        TString m_sampleName;


        // To do run dependant stuff
        bool m_isMC;
        int m_runNumber;

        virtual void bookTree(TTree* currTree);

        // List of variables need to add variables
        virtual void addVar() {};
        virtual void addHistrogram();

        // MetaData
        //
        // For metadata data
        std::map<std::string, Int_t> m_intMetaData;
        std::map<std::string, std::string> m_stringMetaData;

        virtual void initMetaData();
        void bookMetaDataTree(TTree* currTree);

        virtual void addMetaData();
        TTree* m_metaDataTree;

    
        // To check if the variable has been marked for removal
        Bool_t isMarkedRemove(const std::string varName) const;


        // Tool handle for variation tool
        ToolHandle<ITheoryVariation> m_varTool;
        

};

#endif




