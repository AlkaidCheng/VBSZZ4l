#ifndef PROCESSMINITREE_H
#define PROCESSMINITREE_H

// C++ includes
#include <vector>
#include <string>

// Root includes
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

// ASG includes
#include "AsgTools/AsgMessaging.h"
#include "AsgTools/ToolHandle.h"
#include "MCFM_MatrixElement/IMatrixElementProvider.h"


class GoodRunsListSelectionTool;

// HZZ includes
class IH4lBrRatio;
class ITheoryVariation;

// Enum for miniTree file types
namespace MiniTreeFileType {
    enum miniTreeFileType {
        Nominal,        // 0
        Fiducial,       // 1
        FidAndNom,      // 2
        Systematic,     // 3 
        NormSystematic, // 4
        BkgCR,          // 5
        BkgCRZpl,       // 6
        nMinitreeFileTypes  // 7
    };
}

namespace QuadType {
    enum quadType{
      _4mu,      //  0
      _4e,       //  1
      _2mu2e,    //  2
      _2e2mu,    //  3
      _4tau,     //  4
      _2e2tau,   //  5
      _2tau2e,   //  6
      _2mu2tau,  //  7
      _2tau2mu,  //  8
      _emu2mu,   //  9
      _2mumu,    // 10
      _2mue,     // 11
      _2emu,     // 12
      _2ee,      // 13
      NA
    };
}

class ProcessMinitree : public asg::AsgMessaging
{
public:
    ProcessMinitree();

    ~ProcessMinitree();

    /// Setter
    void setInFile(const TString& inFile)       {m_fileList = inFile;};
    void setOutFolder(const TString& outFolder) {m_outFolder = outFolder;};

    /// Actual processing
    void process();

    /// Set debug mode
    void  setDoDebug(bool doDebug = true) { (doDebug) ? msg().setLevel(MSG::DEBUG) : msg().setLevel(MSG::INFO);
        m_doDebug = doDebug; }

    /// Set do vertex cut
    void  setDoVrtCut() { m_doVrtCut = true; }

    /// Set do Higgs pt reweighting - only for ggF
    void setDoPtReweighting();
    
    /// Set do x-section fix
    void  setDoXSFix()  { m_doXSFix = true; }

    /// Set do branching ratio fix
    void  setDoBRFix()  { m_doBRFix = true; }

    /// Set do m_H shift
    void  setDoMHShift();

    /// Set to recalculate new isolation cuts -
    ///   doNewIsoCuts == true  use optimized cuts
    ///   doNewIsoCuts == false use standard cuts
    void setDoIsoCuts(bool doNewIsoCuts);

    /// Set to blind data - keep <110 and >140 and fix >200 to 200 GeV
    void  setBlindData(bool doBlinding);

    /// Set xml GRL files
    bool setXML4GRL(const TString& xml);

    /// Set flag to ignore GRL - for data only
    void setIgnoreGRL() { m_ignoreGRL = true; }  
    
    /// Set flag to ignore trigger - for data only
    void setIgnoreTrig() { m_ignoreTrig = true; }  

    void setAddMELA();

    /// set branches inactive
    void setBranchStatus(bool status);

protected:

    enum MiniTreeType {
        // Type of miniTree
        singleMiniTree,          // 0 
        relaxeeMiniTree,         // 1
        relaxIsoD0MiniTree,      // 2
        invIsoMiniTree,          // 3
        invD0MiniTree,           // 4
        Z2SSMiniTree,            // 5  std anal, Z2 is SS
        emuZ2mumuMiniTree,       // 6
        ZeMiniTree,              // 7
        ZmuMiniTree,             // 8
        nMiniTreeTypes           // 9
    };


    // For storing the file
    TString m_fileList;
    TString m_outFolder;
    TString m_xml4GRL;
    GoodRunsListSelectionTool* m_grlTool;
    ToolHandle<IH4lBrRatio> m_higgsBR;

    std::vector<TString> m_sampleList;

    // Helper functions
        
    // For clearing the file
    void clearVars();
    void clearTTreeVars();

    ////////
    // Reads input sample info
    ///////
    void readSampleList();

    ///////
    // For processing each sample
    ///////
    void processSample(TString sample);


    // Fill the ttree info
    // What trees are in the file and what should be processed
    void fillTTreeInfo();

    // Fill meta data 
    void fillMetaData();

       
    // Gets the base name of the sample
    void getSampleName(TFile *file, std::string& sampleName);
        
    // Gets which systematic variation the current minitree is
    void getVariationName(TFile *file, TString& variationName);
    // check if is a norm file
    bool isNormFile();
    // Check it is DxAOD
    bool isDxAOD(TFile *file);
        
    // Get the list of normalization systematics weights
    void getNormSysName(std::vector<TString>& normSysName);

    // Set flags for missing variables
    void checkVariables();

    ///////
    // output stuff
    ///////

    // Setups up the ouptup stuff
    // computes the output name
    // create the output folder
    void setupOutput();

    // For pattern matching
    bool matchPattern(const std::string brName);

    void setupReadTree(TTree *tree);
    void getVariableTree(TTree *tree);


    ///////
    // For the actual weight calculation
    ///////
    void fillCountingVar();
    TH1F* m_countingHist;

    // Process the TTree
    // requires the in/out file and in/out tree to be set
    void processTTree();
    void calcWeight();
    bool cutEvent(); // Apply any event level cuts
       
    bool cutInvD0(); // Cuts for invISO
    bool cutInvIso(); // Cuts for invIso

    void calcIso(); // recalculate the isolation selection

    /// For Higgs pt reweighting, must check that we have a Nominal input file and that it is ggF
    void checkFor_ggF();
    /// only for ggF events with 0 or 1 jets with pT>25 GeV
    /// input: Higgs boson pT in GeV !
    double ggF_01jet_hpT_weight(double hpT) const;

    void calcMELA();

    /// string tokenizer
    void tokenizeString(const std::string& str_in,
                        const std::string& delimiters,
                        std::vector<std::string>& strs_out) const;
     

    // For theory sys reweighing
    void checkFor_theorySys();
    
    ///////
    // MetaData 
    ///////
    std::string m_sampleName;
    TString m_currVariation;
    bool    m_isNormSys; 
    bool    m_isFidTree; 
    bool    m_isDxAOD;
    bool    m_hasWeight;
    bool    m_hasWeightJet;
    bool    m_hasWeightbTag;
    bool    m_hasWeightCorr;
    bool    m_hasSherpaJetWeight;
    bool    m_hasSherpaLepWeight;
    bool    m_hasCandIndex;
    bool    m_isData;

    void setupReadMetaDataTree(TTree *tree);

    ////////
    // vars to control the processing
    ///////
    bool    m_blindData;
    bool    m_doDebug;
    bool    m_doVrtCut;
    bool    m_doPtReweighting;
    bool    m_doXSFix;
    bool    m_doBRFix;
    bool    m_doMHShift;
    bool    m_doTTVAdown;
    bool    m_doTTVAup;
    bool    m_doNewIsoCuts;
    bool    m_applyIsoCuts;
    bool    m_foundFirstEvent;
    bool    m_ignoreGRL;
    bool    m_ignoreTrig;
    bool    m_hasTrigVar;
    bool    m_hasWeightCorrForNormSyst;
    bool    m_isggF;
    bool    m_isNoTau;
    bool    m_outputCount;
    float   m_xsFix;
    float   m_brFix;
    float   m_br4e;
    float   m_br2e2mu;
    bool    m_hasTheorySys;
    bool    m_addMELA;

    ///////
    // For reading the TTree's variable
    ///////
    struct int_array   { int array[4]; };        
    struct float_array { float array[4]; };        
    std::map<std::string, Int_t>       m_intVar;
    std::map<std::string, ULong64_t>   m_ulong64Var;
    std::map<std::string, Float_t>     m_floatVar;
    std::map<std::string, double>      m_doubleVar;
    std::map<std::string, int_array>   m_intArrayVar;
    std::map<std::string, float_array> m_floatArrayVar;   
    std::map<std::string, ULong64_t>   m_ulongIntArrayVar;        
    std::set<std::string>              m_brsToRead;
    std::vector<std::string>           m_m4lVars;

    std::map<std::string, Int_t>       m_intMetaDataVar;
    std::map<std::string, std::string*>m_stringMetaDataVar;
    
        
    // variables needed for processing each samples
    TString       m_currInSampleName;
    TFile*        m_inFile;
    TFile*        m_outFile;
    TTree*        m_currInTree;
    TTree*        m_currOutTree;
    MiniTreeType  m_currOutTreeType;

    TTree* m_metaDataTree;
    TTree* m_outMetaDataTree;

    TString                    m_outFilePath;
    std::vector<TString>       m_inTreeNames;
    std::vector<TString>       m_outTreeNames;
    std::vector<MiniTreeType>  m_outTreeTypes;
    std::vector<std::string>   m_outTreeTypeNames;


    ///////
    // For the actual weight calculation
    ///////
    double               m_nSimEvent_raw;
    double               m_nSimEvent;
    std::vector<TString> m_normSysName; // to keep a track of the normalization systematics


    // For the Theory systematics
    TH1F* m_variationHist;
    // Tool handle for variation tool
    ToolHandle<ITheoryVariation> m_varTool;
    ToolHandle<HSG2_MCFM::IMatrixElementProvider> m_MEprovider;
};

#endif


