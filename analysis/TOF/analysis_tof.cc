#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis_tof(TString file, TString output, bool ignoreoverlay){

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  cout<<file<<endl;
  observable ss3(file);

  ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),0),true,ignoreoverlay,0);
  ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),1),true,ignoreoverlay,1);
  ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),2),true,ignoreoverlay,2);
  ss3.TOF(-1,TString::Format("%s_cut_%i",output.Data(),3),true,ignoreoverlay,3);
  
  
  //ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),2),true,ignoreoverlay,2.);
  //  ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),0),true,ignoreoverlay,0.);
  //  ss3.dEdx(-1,output,false,ignoreoverlay);
  
  gSystem->Exit(0);

  return 0;
}
