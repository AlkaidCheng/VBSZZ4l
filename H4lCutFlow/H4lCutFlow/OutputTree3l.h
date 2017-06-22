#ifndef OUTPUTTREE3L_H
#define OUTPUTTREE3L_H

// Base includes
#include "H4lCutFlow/EnumDef4l.h"
#include "HZZCutCommon/log.h"
#include "HZZCutCommon/OutputTree.h"

#include "PATInterfaces/SystematicRegistry.h"


class OutputTree3l : public OutputTree
{
    public:
        OutputTree3l(TString outName, TString sysName, TString sampleName);
        ~OutputTree3l();
    
        // Main booking of trees happen here
        // Gives a oppurtunity to remove variables from the tree
        void initialize();
    
        void fillTree(OutputTreeType::OutputTreeType t_type);

        void writeTree();
    
        // List of variables that we would like to remove from the xAOD
        // Can make like easier if we want to create smaller trees for different
        // studies
        void removeVar();
    
        // Specific variables that we need to remove for the systematic minitrees
        void removeSysVar();
    
        // This function setup the minitree for the normalization systematic tree
        void setupVarsNormSys(std::vector<CP::SystematicSet> normSysList);
        Bool_t m_isNormSys;

        void addDataSpecificVar();

    protected:
        // OutputFile
        TFile *output;

        // OutputTrees
        TTree* m_ZplusMuTree;
        TTree* m_ZplusElTree;
        // List of variables need to add variables
        void addVar();
        void addHistrogram();
        void updateFloatArrayVar(std::string varName, std::array<float, 3> varValue);
        void updateIntArrayVar(std::string varName, std::array<int, 3> varValue);

};

#endif




