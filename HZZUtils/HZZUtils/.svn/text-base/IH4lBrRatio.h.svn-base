// Dear Emacs, this is -*- C++ -*-

#ifndef IH4LBRRATIO_H_
#define IH4LBRRATIO_H_

#include "AsgTools/IAsgTool.h"
#include "HZZUtils/BrRatio.h"

class IH4lBrRatio : virtual public asg::IAsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_INTERFACE( IH4lBrRatio )

public:
  
  virtual ~IH4lBrRatio() {};

  /** @brief initialize method*/
  virtual StatusCode initialize() = 0;
  /** @brief finalize method*/
  virtual StatusCode finalize() = 0;
  /** @brief execute method*/
  virtual StatusCode execute(const double mass , const ColumnBR::col outputType, double& result) const =0;
  virtual double execute(const double mass , const ColumnBR::col outputType) const =0;
};

#endif //IH4LBRRATIO_H_
