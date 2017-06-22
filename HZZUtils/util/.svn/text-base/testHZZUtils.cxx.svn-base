#include "HZZUtils/HiggsCrossSection.h"
#include "HZZUtils/H4lBrRatio.h"
#include "AsgTools/AsgMessaging.h"

int main(){

  //Set MSG Levels
  MSG::Level mylevel=MSG::DEBUG;
  asg::AsgMessaging mymsg("testHZZUtils");
  mymsg.msg().setLevel(mylevel); 

  // Higgs Cross Section
  HiggsCrossSection myHiggs("myHiggs") ;
  myHiggs.msg().setLevel(mylevel); 

  mymsg.msg(mylevel)<<"Normal Examples for HiggsCrossSection"<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is14TeV, 125, ColumnXS::xsecGGF)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is7TeV, 125, ColumnXS::xsecGGF)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is8TeV, 125.05, ColumnXS::xsecGGF)<< endmsg;

  mymsg.msg(mylevel)<<"Request for a mass outside the range provided "<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is8TeV, 0, ColumnXS::xsecGGF)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is14TeV, -1, ColumnXS::xsecGGF)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is14TeV, 5000, ColumnXS::xsecGGF)<< endmsg;

  mymsg.msg(mylevel)<<"Request for a value that is not there "<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myHiggs.execute(CentreOfMass::is8TeV, 125.05, ColumnXS::pdfbbHdown)<< endmsg;


  // H4l Br Ratio
  H4lBrRatio myBR("myBR") ;
  myBR.msg().setLevel(mylevel); 

  mymsg.msg(mylevel)<<"Normal Examples for H4lBrRatio"<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myBR.execute(125, ColumnBR::br_emutau)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myBR.execute(125, ColumnBR::br_2e2mu)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myBR.execute(125.05, ColumnBR::br_emutau)<< endmsg;

  mymsg.msg(mylevel)<<"Request for a mass outside the range provided "<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myBR.execute(0, ColumnBR::br_emutau)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myBR.execute(-1, ColumnBR::br_emutau)<< endmsg;
  mymsg.msg(mylevel)<<"Result : "<<myBR.execute(5000, ColumnBR::br_emutau)<< endmsg;


  return 0;
}
