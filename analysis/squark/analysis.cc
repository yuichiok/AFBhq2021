#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"


int analysis(TString file, TString output, int tight=0, int bkg=0){

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  cout<<file<<endl;
  QQbarAnalysisClass ss3(file);

  ss3.AFBreconstruction(-1,TString::Format("%s",output.Data()),tight,bkg); 

  //  ss3.dEdx(-1,output,false,ignoreoverlay);
  
  gSystem->Exit(0);

  return 0;
}
