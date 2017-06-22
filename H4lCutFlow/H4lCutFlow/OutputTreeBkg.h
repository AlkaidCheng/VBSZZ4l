#ifndef OUTPUTTREEBKG_H
#define OUTPUTTREEBKG_H

// Base includes
#include "H4lCutFlow/EnumDef4l.h"
#include "HZZCutCommon/log.h"
#include "HZZCutCommon/OutputTree.h"

#include "PATInterfaces/SystematicRegistry.h"


class OutputTreeBkg : public OutputTree
{
    public:
        OutputTreeBkg(TString outName, TString sysName, TString sampleName);
        ~OutputTreeBkg();
    
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
        TTree* m_relaxIsoD0Tree;
        TTree* m_emuTree;
        TTree* m_ssTree;
        TTree* m_threeLplusXTree;
        // List of variables need to add variables
        void addVar();
        void addHistrogram();

};

#endif




