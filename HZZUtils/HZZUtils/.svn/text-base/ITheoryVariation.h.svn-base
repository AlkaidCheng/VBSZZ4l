// Dear Emacs, this is -*- C++ -*-

#ifndef ITHEORYVARIATION_H_
#define ITHEORYVARIATION_H_

#include "AsgTools/IAsgTool.h"
#include "TString.h"
class ITheoryVariation : virtual public asg::IAsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_INTERFACE( ITheoryVariation )

public:
  
  virtual ~ITheoryVariation() {};

  /** @brief initialize method*/
  virtual StatusCode initialize() = 0;
  /** @brief finalize method*/
  virtual StatusCode finalize() = 0;
  /** @brief execute method*/
  virtual StatusCode execute(const int chanNumber, std::map<std::string, int>& result) const =0;
  virtual std::map<std::string, int> execute(const int chanNumber) const =0;

  virtual TString getTheorySysName(const std::string mapSysKey) const = 0;
  
};

#endif 
