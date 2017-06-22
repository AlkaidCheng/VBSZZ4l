#ifndef THEORYVARIATION_H
#define THEORYVARIATION_H

#include <map>
#include "HZZUtils/ITheoryVariation.h"
#include "AsgTools/AsgTool.h"

class TheoryVariation : public virtual ITheoryVariation,
                          public asg::AsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_CLASS( TheoryVariation, ITheoryVariation )

public:
  
  TheoryVariation(const std::string&);
  virtual ~TheoryVariation();

  /** @brief initialize method*/
  virtual StatusCode initialize();
  /** @brief finalize method*/
  virtual StatusCode finalize() ;
  /** @brief execute method*/
  virtual StatusCode execute( int chanNumber, std::map<std::string, int>& result) const;
  virtual std::map<std::string, int> execute( int chanNumber) const;

  TString getTheorySysName(const std::string mapSysKey) const;

 private :

  std::map<int, std::map<std::string, int>> m_variations;


};



#endif
