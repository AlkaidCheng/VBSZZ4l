#ifndef CROSSSECTION_H
#define CROSSSECTION_H

namespace CrossSections{

  enum LHCEnergy{
    SevenTeV = 0,
    EightTeV = 1,
    ThirteenTeV = 2,   
    ThirteenHalfTeV = 3,
    FourteenTeV = 4
  };
}

namespace CentreOfMass{
  enum is{
    is7TeV = 0,
    is8TeV = 1,
    is13TeV = 2,
    is13_5TeV = 3,
    is14TeV = 4
  };
}

namespace ColumnXS{
    enum col{
      m = 0,
      xsecGGF = 1,
      scaleGGFup = 2,
      scaleGGFdown = 3,
      pdfGGFup = 4,
      pdfGGFdown = 5,
      xsecVBF = 6,
      scaleVBFup = 7,
      scaleVBFdown = 8,
      pdfVBFup = 9,
      pdfVBFdown = 10,
      xsecWH = 11,
      scaleWHup = 12,
      scaleWHdown = 13,
      pdfWHup = 14,
      pdfWHdown = 15,
      xsecZH = 16,
      scaleZHup = 17,
      scaleZHdown = 18,
      pdfZHup = 19,
      pdfZHdown = 20,
      xsecttH = 21,
      scalettHup = 22,
      scalettHdown = 23,
      pdfttHup = 24,
      pdfttHdown = 25,
      xsecbbH = 26,
      scalebbHup = 27,
      scalebbHdown = 28,
      pdfbbHup = 29,
      pdfbbHdown = 30,
      xsecWpH = 31,
      xsecWmH = 32,
      xsecggZH = 33,
      xsecqqZH = 34
    };
}

#endif
