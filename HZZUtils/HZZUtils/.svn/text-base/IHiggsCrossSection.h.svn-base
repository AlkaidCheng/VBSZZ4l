// Dear Emacs, this is -*- C++ -*-

#ifndef IHIGGSCROSSSECTIOM_H_
#define IHIGGSCROSSSECTIOM_H_

#include "AsgTools/IAsgTool.h"
#include "HZZUtils/CrossSection.h"

class IHiggsCrossSection : virtual public asg::IAsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_INTERFACE( IHiggsCrossSection )

public:
  
  virtual ~IHiggsCrossSection() {};

  /** @brief initialize method*/
  virtual StatusCode initialize() = 0;
  /** @brief finalize method*/
  virtual StatusCode finalize() = 0;
  /** @brief execute method*/
  virtual StatusCode execute(const CentreOfMass::is CentreOfMass, const double mass , const ColumnXS::col outputType, double& result) const =0;
  virtual double execute(const CentreOfMass::is CentreOfMass, const double mass , const ColumnXS::col outputType) const =0;
};

#endif //IHIGGSCROSSSECTIOM_H_
