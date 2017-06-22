#ifndef H4LBRRATIO_H
#define H4LBRRATIO_H

#include "HZZUtils/IH4lBrRatio.h"
#include "AsgTools/AsgTool.h"


class H4lBrRatio : public virtual IH4lBrRatio,
                   public asg::AsgTool{
  /// Declare the interface that the class provides
  ASG_TOOL_CLASS( H4lBrRatio, IH4lBrRatio )

public:
  
  H4lBrRatio(const std::string&);
  virtual ~H4lBrRatio();

  /** @brief initialize method*/
  virtual StatusCode initialize();
  /** @brief finalize method*/
  virtual StatusCode finalize() ;
  /** @brief execute method*/
  virtual StatusCode execute(const double mass , const ColumnBR::col outputType, double& result) const;
  virtual double execute(const double mass , const ColumnBR::col outputType) const ;

 private :

  double getBrRatio(const std::vector<std::vector<double> >& table, const double mass , const ColumnBR::col outputType) const;


};



#endif
