#ifndef HIGGSCROSSSECTION_H
#define HIGGSCROSSSECTION_H


#include "HZZUtils/IHiggsCrossSection.h"
#include "AsgTools/AsgTool.h"

class HiggsCrossSection : public virtual IHiggsCrossSection,
                          public asg::AsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_CLASS( HiggsCrossSection, IHiggsCrossSection )

public:
  
  HiggsCrossSection(const std::string&);
  virtual ~HiggsCrossSection();

  /** @brief initialize method*/
  virtual StatusCode initialize();
  /** @brief finalize method*/
  virtual StatusCode finalize() ;
  /** @brief execute method*/
  virtual StatusCode execute(const CentreOfMass::is CentreOfMass, const double mass , const ColumnXS::col outputType, double& result) const;
  virtual double execute(const CentreOfMass::is CentreOfMass, const double mass , const ColumnXS::col outputType) const ;

 private :

  double getCrossSection(const std::vector<std::vector<double> >& table, const double mass , const ColumnXS::col outputType) const;


};



#endif
