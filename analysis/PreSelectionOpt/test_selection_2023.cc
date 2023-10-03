#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

void test_selection_2023(){

  TString file = "/group/ilc/users/yokugawa/QQbar250/l5/P4f_ww_h/eLpR/500066/15311/dEdx_corr/QQbarProcessor_out/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500066.P4f_ww_h.eL.pR.n078.d_dstm_15311_37.root";

  // TString s_type=TString::Format("cuts%i_",type);
  // cout<< " "<<endl;
  // cout<< file << endl;

  int type = 3;
  int bkg = 1;

  QQbarAnalysisClass ss3(file);
  ss3.process="cuts2_P4f_ww_h_eLpR";
  ss3.Selection(-1,type,bkg);

  // if(file_n<10) ss3.process=s_type+process+"_"+pol+TString::Format("_file_00%i",file_n);
  // else if(file_n<100) ss3.process=s_type+process+"_"+pol+TString::Format("_file_0%i",file_n);
  // else ss3.process=s_type+process+"_"+pol+TString::Format("_file_%i",file_n);

  // ss3.Selection(-1,type,bkg);
  // gSystem->Exit(0);

  // return 0;
}
