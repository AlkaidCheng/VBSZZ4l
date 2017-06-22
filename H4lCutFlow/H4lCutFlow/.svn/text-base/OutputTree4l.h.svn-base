#ifndef OUTPUTTREE4l_H
#define OUTPUTTREE4l_H

// Base includes
#include "H4lCutFlow/EnumDef4l.h"
#include "HZZCutCommon/log.h"
#include "HZZCutCommon/OutputTree.h"

#include "PATInterfaces/SystematicRegistry.h"


class OutputTree4l : public OutputTree
{
    public:
        OutputTree4l(TString outName, TString sysName, TString sampleName);
        ~OutputTree4l();
    
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

        void addTriggerSpecificVar();
        void removeFullEgammaSysVar();
    
    
        // This function setup the minitree for the normalization systematic tree
        void setupVarMETSys(std::vector<CP::SystematicSet> metSysList);
        Bool_t m_isMETSys;

    protected:
        // OutputFile
        TFile *output;

        // OutputTrees
        TTree * m_inclTree;

        // List of variables need to add variables
        void addVar();
        void addHistrogram();

};

#endif




