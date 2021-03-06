#ifndef _TMCFM_HH_
#define _TMCFM_HH_

//----------------------------------------------------------
//
// http://www.chiralcomp.com/support/mixing_f77_c_cpp/
//  (almost all) Fortran compilers add, during compilation, an underscore (_) at the end of the Fortran routine names. Our experience is that the f77 compiler in HP Unix environments does not do this.
//    * We noticed that if a fortran subroutine has an underscore anywhere in its name, the GNU g77 compiler adds two (2) underscores at the end of the name.
//
//   In the compiled Fortran code all arguments to functions are passed by their address.
//   If a Fortran function takes a character string as an argument, the string length must be passed as the last argument (i.e. after the "ordinary" argument list). 
//
//----------------------------------------------------------
// MCFM parameters
// nflavors constants.f 
enum {nf=5};
// maxpart constants.f 
enum {mxpart=14}; // MCFM 6.8+: CAUTION!!! IMPORTANT TO CHECK WHEN UPDATING MCFM!!!
//enum {mxpart=12}; // MCFM 6.7
//mxdim.f
enum {ndims=22};

enum {nmsq=11};


extern "C" {
//---------------------------------
// Structure
//---------------------------------
 extern struct {
   int nproc;
 } nproc_;


 /*  // MCFM 6.7
 #define bveg1_mcfm_ bveg1_
 extern struct{
   double xl[ndims], xu[ndims], acc;
   int ndim,  ncall, itmx, nprn;
 } bveg1_mcfm_;
 */

 #define bveg1_mcfm_ bveg1int_
 extern struct{
   int ndim, itmx, nprn;
 } bveg1_mcfm_;

 extern  struct {
   int ih1, ih2;
 } density_;

 extern  struct{
 	 double scale,musq;
 } mcfmscale_; // MCFM 6.8+
 //} scale_; // MCFM 6.7

 extern  struct {
     int n2; int n3; double mass2; double width2; double mass3; double width3;
 } breit_;

 extern struct{
   int nqcdjets,nqcdstart;
 } nqcdjets_;


 extern struct{
   double xmin;
 } xmin_;


 extern struct{
 	 int npart;
 } npart_;

 extern struct{
 	 double vsymfact;
 } vsymfact_;

 extern struct{
 	 bool interference;
 } interference_;

 extern struct{
        double cutoff;
 } cutoff_;

 extern struct{
        double amz;
 } couple_;

 extern struct{
   double Gf_inp,aemmz_inp,xw_inp,wmass_inp,zmass_inp;
 } ewinput_;

 extern struct{
   int ewscheme;
 } ewscheme_;

 extern struct {
   double gsq, as, ason2pi, ason4pi;
 } qcdcouple_;

 extern struct {
   double Gf,gw,xw,gwsq,esq,vevsq;
 } ewcouple_;

 extern   struct {
   double delg1_z, delg1_g, lambda_g, lambda_z, delk_g, delk_z,tevscale;
 } anomcoup_;

  //mcfm/src/Inc/masses.F
 #define masses_mcfm_ masses_

 extern  struct{
    double md,mu,ms,mc,mb,mt,
           mel,mmu,mtau,
           hmass,hwidth,
           wmass,wwidth,
           zmass,zwidth,
           twidth,
           tauwidth,
           mtausq,mcsq,mbsq;
  } masses_mcfm_;

//mcfm/src/Inc/zcouple.F

  extern struct{
    double l[nf],r[nf],q1,l1,r1,q2,l2,r2,le,ln,re,rn,sin2w;
  } zcouple_;


  extern struct{
    int nwz;
  } nwz_;
  extern  struct {
    double taumin;
  } taumin_;
 
  extern  struct {
    double sqrts;
  } energy_;

  extern  struct {
    int nlooprun;
  } nlooprun_;

  extern  struct {
    int nflav;
  } nflav_;

  extern  struct {
    char pdlabel[7];
  } pdlabel_;
//---------------------------------
// function
//---------------------------------


  //##############
  // Initialization
  //##############
  // #define mcfm_init_ mcfm_init_
  void   mcfm_init_(char * inputfile, char* workdir);
  void   chooser_();
  void   coupling_();
  void   coupling2_();
  
  //mcfm/src/Need/boost.F
  void boost_mcfm_(double* mass,double* p1,double* p_in,double* p_out);

  // Dynamic alpha_s calculator
  double alphas_(double* q, double* amz, int* nloop);

  //##############
  // ME calculator
  double lowint_(double* r, double* wgt);
  void   dotem_(int N,double* p,double* s);

  //###############
  // For WW/WZ/ZZ
  void fdist_ (int* ih1, double* xx, double* pdfscale, double* fx1);

  #define qqb_ww_ qqb_ww_
  void qqb_ww_(double* p, double* msq);

  #define qqb_wz_ qqb_wz_
  void qqb_wz_(double* p, double* msq);

  #define qqb_zz_ qqb_zz_
  void qqb_zz_(double* p, double* msq);
  void gen4_(double* r, double* p, double* wt4);  //r(22) p(4,12)

  //#define gg_zz_int_ gg_zz_int_
  //void gg_zz_int_(double* p, double* msq);

  //#define gg_zz_int_freenorm_ gg_zz_int_freenorm_
  //void gg_zz_int_freenorm_(double* p, double hcoupl[2], double* msq);

  // processes for the 128, 129, 131, 132 
  // from src/Procdep/lowint.f
  
  // 128:
  #define gg_hzz_tb_ gg_hzz_tb_
  void gg_hzz_tb_(double* p, double* msq); 
 
  // 129
  #define gg_zz_int_ gg_zz_int_
  void gg_zz_int_(double* p, double* msq);
   
  // 131
  #define gg_zz_all_ gg_zz_all_
  void gg_zz_all_(double* p, double* msq);
  
  // 132 
  #define gg_zz_ gg_zz_
  void gg_zz_(double* p, double* msq);
  
  
  // For H->WW
  void gen4h_(double* r, double* p, double* wt4);  //r(22) p(4,12)

  #define qqb_hww_ qqb_hww_
  void qqb_hww_(double* p, double* msq);

  #define qqb_hzz_ qqb_hzz_
  void qqb_hzz_(double* p, double* msq);

  #define qqb_hzz_tb_ qqb_hzz_tb_
  void qqb_hzz_tb_(double* p, double* msq);

  // For DY
  void gen2_(double* r,double* p,double* pswt);

  #define qqb_z_ qqb_z_
  void qqb_z_(double* p, double *msq);

  //used by Wgam
  void gen3_(double* r,double* p,double* pswt);
  void gen3jet_(double* r,double* p,double* pswt);

  #define qqb_wgam_ qqb_wgam_
  void qqb_wgam_(double* p, double* msq);

  // For Wgam
  void gen3_(double* r,double* p,double* pswt);
  void gen3jet_(double* r,double* p,double* pswt);

  #define qqb_wgam_ qqb_wgam_
  void qqb_wgam_(double* p, double* msq);
  void phi3m0_(double* xth,double* xphi,double* p0,double* p1,double* p2,double* wt);
  void breitw_(double* x1,double* mminsq,double* mmaxsq,double* rmass,double* rwidth,double* msq,double* wt);

  // For W 1jet
  #define gen_njets_ gen_njets_
  void gen_njets_(double* r, int*, double* p, double* msq);

  #define qqb_w_g_ qqb_w_g_
  void qqb_w_g_(double* p, double* msq);


  
}

#endif
