#ifndef OUTPUTTREE4lINCLUSIVE_H
#define OUTPUTTREE4lINCLUSIVE_H

// Base includes
#include "H4lCutFlow/EnumDef4l.h"
#include "HZZCutCommon/log.h"
#include "HZZCutCommon/OutputTree.h"

#include "PATInterfaces/SystematicRegistry.h"


class OutputTree4lInclusive : public OutputTree
{
    public:
        OutputTree4lInclusive(TString outName, TString sysName, TString sampleName);
        ~OutputTree4lInclusive();
    
        // Main booking of trees happen here
        // Gives a oppurtunity to remove variables from the tree
        void initialize();
    
        void fillTree(OutputTreeType::OutputTreeType t_type);

        void writeTree();

        void setLeptonType(std::string leptonType);
        std::string getLeptonType();
    
        // List of variables that we would like to remove from the xAOD
        // Can make like easier if we want to create smaller trees for different
        // studies
        void removeVar();
    
        // Specific variables that we need to remove for the systematic minitrees
        void removeSysVar();
        // This function setup the minitree for the normalization systematic tree
        void setupVarsNormSys(std::vector<CP::SystematicSet> normSysList);
        Bool_t m_isNormSys;

    protected:
        // OutputFile
        TFile *output;

        TTree * m_inclTree;
        std::string m_leptonType;

        // List of variables need to add variables
        void addVar();
        void addHistrogram();

};

#endif




