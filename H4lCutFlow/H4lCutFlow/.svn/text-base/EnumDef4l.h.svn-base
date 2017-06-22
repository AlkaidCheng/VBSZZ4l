#ifndef ENUMDEF4l_H
#define ENUMDEF4l_H

// For enumerating muon cuts
namespace muCut 
{
    enum muCut 
    {
        Total,
        Preselection,
        Trigger,
        ID,
        Pt,
        D0,
        OverLap,
    };
}

// For enumerating el cuts
namespace elCut 
{
    enum elCut
    {
        Total,
        Preselection,
        Trigger,
        Author,
        Loose,
        Eta,
        Et,
        ObjectQuality,
        Z0,
        OverLap,
    };
}

// For enumerating jet cuts
namespace jetCut 
{
    enum jetCut
    {
        Total,
        Preselection,
        Trigger,
        Pt,
        Eta,
        Pileup,
        Clean,
        OverLap
    };
}

// For enumerating quad cuts
namespace cutFlow 
{
    enum cutFlow 
    {
        Total,
        DataPreselection,
        Preselection,
        Trigger,
        Lepton,
        SFOS,
        Kinematics,
        TriggerMatch,
        Z1Mass,
        Z2Mass,
        MassWindow,
        DeltaR,
        JPsiVeto,
        Iso,
        D0Sig,
        Final
    };
}

// For enumerating quad cuts
namespace cutFlow3lx
{
    enum cutFlow3lx 
    {
        Total,
        DataPreselection,
        Preselection,
        Trigger,
        Lepton,
        SFOS,
        Kinematics,
        TriggerMatch,
        Z1ID,
        Z2ID,
        LeadingZIsoD0,
        Z1Mass,
        Z2Mass,
        DeltaR,
        eeOlv,
        _3lXCuts,
        Final
    };
}

// For enumerating cuts on Z+L cutflow
namespace cutFlowZl
{
    enum cutFlowZl
    {
        Total,
        DataPreselection,
        Preselection,
        Trigger,
        Lepton,
        SFOS,
        Kinematics,
        TriggerMatch,
        ZMass,
        DeltaR,
        MET,
        Iso,
        D0Sig,
        DeltaR_l,
        Final
    };
}

// For enumerating cuts on Z+L cutflow
namespace OverlapRemoval
{
    enum OverlapRemoval
    {
        Initial,
        ee,
        e_caloMuon,
        ASGtool,
    };
}


// Enum for eventType
namespace quadType{
    enum quadType{
        _4mu,      // 0
        _4e,       // 1
        _2mu2e,    // 2
        _2e2mu,    // 3
        _4tau,     // 4
        _2e2tau,   // 5
        _2tau2e,   // 6
        _2mu2tau,  // 7
        _2tau2mu,  // 8
        _emu2mu,   // 9
        _2mumu,    // 10
        _2mue,     // 11
        _2emu,     // 12
        _2ee,      // 13

        other
    };
}

// Enum for prodType
namespace prodType{
    enum prodType{
        // For backup
        ggF,  // 0
        VBF,  // 1
        VHLep,// 2
        VHHad, // 3

        Total
    };
}

// Enum for prodType
namespace prodTypeSimp{
    enum prodTypeSimp{
        njet0,            // 0
        njet1,            // 1
        njet2_VH,         // 2
        njet2_VBF,        // 3
        leptonic,         // 4
        ttH,              // 5
        MaxProdTypeSimp   // 6
    };
}

namespace prodTypeHighMass{
    enum prodTypeHighMass{
        ggF_HM,           // 0
        VBF_HM,           // 1
        MaxProdTypeHM     // 2
    };
}

// Enum for fsrType
namespace fsrType{
    enum fsrType{
        collFSRZ1mumu,
        farFSRZ1,
        farFSRZ2,
        noFSR,
    };
}

// For accessing cov matrix parameters
namespace TrackParameters{
    enum TrackParameters {
        d0     = 0,
        z0     = 1,
        phi0   = 2,
        theta  = 3,
        qOverP = 4,
        x      = 0,
        y      = 1,
        z      = 2
    };
}

// Bkg specific
// Enum for lepton quality
namespace LeptonQuality{
    enum LeptonQuality{
        looseID,
        veryLooseID,
        basicID,
        otherEl,
        otherMu
    };
}


namespace leptonIDType{
    enum {
        mu_CB,          // 0 combined
        mu_ST,          // 1 Segment Tagged
        mu_SA,          // 2 StandAlone
        mu_CA,          // 3 Calo muons
        mu_SAFM,        // 4 Silicon Associated Forward Muons
        el_Basic,       // 5        
        el_VLoose,      // 6
        el_Loose_noBL,  // 7
        el_Loose,       // 8
        el_Medium,      // 9
        el_Tight,       // 10
        unknown,        // 11
    };
}


namespace miniTreeType{
    enum miniTreeType{
        Nominal,        // 0
        Fiducial,       // 1
        FidAndNom,      // 2
        Systematic,     // 3 
        NormSystematic, // 4
        BkgCR,          // 5
        BkgCRZpl,       // 6
        nMinitrees      // 7
    };
}

namespace PairingInfo{
    enum PairingInfo{
        correct,      // 0 <- correct four leptons and Z1 Z2
        misorder,     // 1 <- correct four leptons, but mixing Z1 Z2
        wronglep,      // 2 <- Wrong lep in both Z1 and Z2
        unknown,      // 3 <- reserved for signal (e.g. ttH?) with tricky truth records

    };
}


namespace HiggsDecay{
    enum HiggsDecay{
        HZZ_4l,         // 0
        HZZ_2l2v,       // 1
        HZZ_2tau2v,     // 2
        HZZ_2l2tau,     // 3
        HZZ_2q2v,       // 4
        HZZ_2q2tau,     // 5
        HZZ_2q2l,       // 6
        HWW,            // 7
        Hbb,            // 8
        Htautau,        // 9
        Hmumu,          // 10
        HZgamma,        // 11
        HOther,         // 12
    };
}
#endif
