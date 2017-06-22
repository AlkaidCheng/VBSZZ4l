#include "HZZUtils/HiggsCrossSection.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include <limits>

namespace {

  //tables definitions, helpers local only to this scope

  typedef std::vector< std::vector<double> > vec2D_t; 
  
  const  vec2D_t Table_7TeV_Xsections = {
    #include "Table_7Tev_Xsections.def"
  };

  const vec2D_t Table_8TeV_Xsections = {
    #include "Table_8Tev_Xsections.def"
  };

  const vec2D_t Table_13TeV_Xsections = {
    #include "Table_13Tev_Xsections.def"
  };

  const vec2D_t Table_13_5TeV_Xsections = {
    #include "Table_13_5Tev_Xsections.def"
  };

  const vec2D_t Table_14TeV_Xsections = {
    #include "Table_14Tev_Xsections.def"
  };

  const std::vector<vec2D_t const *  > tables= {&Table_7TeV_Xsections, &Table_8TeV_Xsections, 
					 &Table_13TeV_Xsections,&Table_13_5TeV_Xsections,
					 &Table_14TeV_Xsections};

  struct Comp{
    bool operator() (const std::vector<double>& row, const double mass){
      return row.at(0) < mass;
    }
  };
}


HiggsCrossSection::HiggsCrossSection(const std::string& name) : AsgTool(  name ){

}

HiggsCrossSection::~HiggsCrossSection(){

}

StatusCode HiggsCrossSection::initialize(){

  return StatusCode::SUCCESS;
}

StatusCode HiggsCrossSection::finalize() {

 return StatusCode::SUCCESS;
}

StatusCode HiggsCrossSection::execute(const CentreOfMass::is CentreOfMass, const double mass , const ColumnXS::col outputType, double& result) const{
  
  // For high mass, set the XS to 1 
  // Return 
  if (CentreOfMass == CentreOfMass::is13TeV && mass >= 200.)
  {
   // set values to 1 for high mass
   result= 1;
   return StatusCode::SUCCESS;
  }
   
  // Otherwise, calculate from the table 
  unsigned int cofm= static_cast<unsigned int> (CentreOfMass);
  ATH_MSG_DEBUG("Centre Of Mass : " << CentreOfMass);    
  if(cofm>=tables.size()){
    ATH_MSG_ERROR("Unknown Centre Of Mass : " << CentreOfMass);    
    return StatusCode::FAILURE;
  }
  
  result=getCrossSection( *(tables.at(cofm)), mass, outputType);
  return StatusCode::SUCCESS;
}

double HiggsCrossSection::execute(const CentreOfMass::is CentreOfMass, const double mass , const ColumnXS::col outputType) const {
  
  double result(0);
  if (! ( execute(CentreOfMass,  mass ,outputType,result).isFailure() ) ){
    ATH_MSG_DEBUG("Returning CenterOfMass : " << CentreOfMass);    
  }
  return result;
}

double HiggsCrossSection::getCrossSection(const std::vector<std::vector<double>>& table, const double mass , const ColumnXS::col outputType) const {  

  if ( mass < table.at(0).at(0) || mass > table.back().at(0)){
    //ATH_MSG_WARNING("mass : " << mass << " outside available range");
    return -999;
  }
 
  const unsigned int col= static_cast<unsigned int> (outputType);

  if(col>=table.at(0).size()){
    ATH_MSG_ERROR("Unavailable XS column : " << col << " requested");    
    return -999;
  }

  auto row2 = std::lower_bound (begin(table), end(table), mass, Comp());

  //We were lucky the mass exists exactly
  if (fabs(row2->at(0)-mass)<std::numeric_limits<double>::epsilon()){
    ATH_MSG_DEBUG(" mass : " << mass << " exists exactly no need to interpolate");    
    return row2->at(col)*1.e3;
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
  return (row1->at(col)+ ((row2->at(col)- row1->at(col))/(row2->at(0) - row1->at(0))) *(mass - row1->at(0)))*1.e3;
}
