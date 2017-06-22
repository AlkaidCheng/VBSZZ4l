#include "HZZUtils/H4lBrRatio.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
namespace {

  //tables definitions, helpers local only to this scope

  typedef std::vector< std::vector<double> > vec2D_t; 
  
  const  vec2D_t Table_H4l_BrRatio = {
    #include "Table_H4l_BrRatio.def"
  };

  struct Comp{
    bool operator() (const std::vector<double>& row, const double mass){
      return row.at(0) < mass;
    }
  };
}

H4lBrRatio::H4lBrRatio(const std::string& name) : AsgTool ( name ) {

}

H4lBrRatio::~H4lBrRatio() {

}

StatusCode H4lBrRatio::initialize() {

    return StatusCode::SUCCESS;
}

StatusCode H4lBrRatio::finalize() {

    return StatusCode::SUCCESS;
}


StatusCode H4lBrRatio::execute(const double mass, const ColumnBR::col outputType, double& result) const{

  ATH_MSG_DEBUG("BrRatio table is Table_H4l_BrRatio " );    
  if (mass > 130.)
    result=getBrRatio(Table_H4l_BrRatio, 130., outputType);
  else
    result=getBrRatio(Table_H4l_BrRatio, mass, outputType);
  
  return StatusCode::SUCCESS;
}

double H4lBrRatio::execute(const double mass, const ColumnBR::col outputType) const {

  double result(0);
  if (! ( execute(mass, outputType, result).isFailure() ) ){
    ATH_MSG_DEBUG("Returning mass: " << mass << " returning outputType: " << outputType );    
  }

  return result;
}

double H4lBrRatio::getBrRatio(const std::vector<std::vector<double>>& table, const double mass, const ColumnBR::col outputType) const {

  if ( mass < table.at(0).at(0) || mass > table.back().at(0)){
    ATH_MSG_WARNING("mass : " << mass << " outside available range");    
    return -999;
  }
 
  const unsigned int col= static_cast<unsigned int> (outputType);

  if(col>=table.at(0).size()){
    ATH_MSG_ERROR("Unavailable BR column : " << col << " requested");    
    return -999;
  }

  auto row2 = std::lower_bound (begin(table), end(table), mass, Comp());

  //We were lucky the mass exists exactly
  if (fabs(row2->at(0)-mass)<std::numeric_limits<double>::epsilon()){
    ATH_MSG_DEBUG(" mass : " << mass << " exists exactly no need to interpolate");    
    return row2->at(col);
  }
  //The first row found  with mass larger that the input, is the first row of the table.
  //so either we were lucky (above) or we have an issue.
  if (row2 == table.begin()){
    ATH_MSG_WARNING("mass : " << mass << " smaller than the ones available");    
    return -999;
  }

  auto row1= (row2-1);

  //y = y1 +( (y2-y1)/(x2-x1) )* (x -x1)
  ATH_MSG_DEBUG(" interpolating for mass : " << mass );    
  return row1->at(col)+ ((row2->at(col)- row1->at(col))/(row2->at(0) - row1->at(0))) *(mass - row1->at(0));

}
