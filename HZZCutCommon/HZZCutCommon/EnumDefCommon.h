#ifndef ENUMDEF_H
#define ENUMDEF_H

// particle mass
#define pdgZMass  91187.6
#define pdgMuMass 105.6583715
#define pdgElMass 0.510998928


// For keeping a track of the overall analysis job type
namespace AnalysisType
{
    enum AnalysisType
    {
        None,  // No correction or smearing
        Nominal, // Nominal Systematics and corrections
        Systematic,
        Fiducial,
        Truth,
    };
}

// To keep track of some of the extra TLV types
namespace TLVType
{
    enum TLVType
    {
        None,  // No correction or smearing
        Unconstrained, // corrections (and if systematics applied) + unconstrained
        FSR, // FSR TLV - only for Dilepton and Quadlepton
        Constrained, // corrections (and if systematics applied) + constrained
        Truth, // Truth
        end,
    };
}

// To keep track of particle types
namespace ParticleType
{
    enum ParticleType
    {
        None, //0
        Muon, //1
        Electron, //2
        Photon, //3
        Tau, //4
        Jet, //5
        Truth, //6
        Dilepton, //7
        Quadlepton, //8
        Multi, //9
    };
}


// For keep track of dilep types
namespace DileptonType
{
    enum DileptonType
    {
        NA,
        _2mu, 
        _2e,
        _2tau,
        emu,
        //_2muSS // Same sign
        //_2eSS  // Same sign
        //emuSS  // Same sign

    };
}

// For keep track of quad flavour
namespace QuadleptonType
{
    enum QuadleptonType
    {
        _4mu,
        _4e,
        _2mu2e,
        _2e2mu,

        _4tau,
        _2e2tau,
        _2tau2e,
        _2mu2tau,
        _2tau2mu,

        _emu2mu,
        _emu2e,

        NA,
    };
}

// For keep track of quad 'setting'
namespace QuadAnalType
{
    enum QuadAnalType
    {
        Nominal, 
        
        // 4l bkg trees
        d0IsoRelax,
        emu,
        sameSign,
        threeLplusX,
        ZplusXX,

        Truth,

        NA,
    };
}


// For the different types of output tree
namespace OutputTreeType
{
    enum OutputTreeType
    {
        NA,
        
        // Standard tree
        _4mu,
        _2e2mu,
        _2mu2e,
        _4e,
        
        // 4l bkg trees
        d0IsoRelax,
        emu,
        sameSign,
        threeLplusX,
        ZplusXX,
        
        // Z+X bkg trees
        ZplusMu,
        ZplusEl,

    };
}

// For different type of sample type
namespace SampleType
{
    enum SampleType {
        data,
        ggF,
        VBF,
        WH,
	WpH,
	WmH,
        ZH,
        bbH,
        ttH,
        Background,
    };
}
namespace Periods
{
   // Enum list of periods and their begin/end run
    enum Periods {
        // D2015 276073-276954
        periodD2015,  //  0
        // E2015 278727-279928
        periodE2015,  //  1
        // F2015 279932: 280422
        periodF2015,  //  2
        // G2015 280423: 281075
        periodG2015,  //  3
        // H2015 281130: 281411
        periodH2015,  //  4
        // I2015 281662: 282482
        periodI2015,  //  5
        // J2015 282625: 284484
        periodJ2015,  //  6
        // A2016 296939: 300287
        periodA2016,  //  7
        // B2016 300345:300908
        periodB2016,  //  8
        // C2016 301912:302393
        periodC2016,  //  9
        // D2016 302737:303560
        periodD2016,  // 11
        // E2016 303638:303892       
        periodE2016,  // 12
        // F2016 303943:304494       
        periodF2016,  // 13
        // G2016 305291:306714
	    periodG2016,  // 14
	    // H2016 305359
	    periodH2016,  // 15
	    // I2016 307124:308084
	    periodI2016,  // 16
        // J2016 308979:309166
        periodJ2016,  // 16
        // K2016 309311:309759
        periodK2016,  // 16
        // L2016 310015:
        periodL2016,  // 16

        periodNone
    };
}

namespace TrigPeriods
{
    // enums for trigger periods - a new one for each trigger variation
    enum TrigPeriods {
        trig_2015_D,     // 0
        trig_2015_EtoJ,  // 1
        trig_2016_A,     // 2
        nTrigPeriods,    // 3
        None
    };
}


namespace Generator
{
    enum Generator {
        PowhegPythia8,
        aMcAtNloHerwigppEvtGen,
        aMcAtNloPythia8,
        MadGraphPythia8,
        Sherpa,
        MCFMPythia8,
    };
}
#endif
