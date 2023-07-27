#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_selection( TString file="", TString process="2f_hadronic", int file_n=0, int cuts=4){

  TString s_cuts=TString::Format("cuts%i_",cuts);
  cout<< " "<<endl;
  cout<< file << endl;
  QQbarAnalysisClass ss3(file);
  if(file_n<10) ss3.process=s_cuts+process+TString::Format("_file_000%i",file_n);
  else if(file_n<100) ss3.process=s_cuts+process+TString::Format("_file_00%i",file_n);
  else if(file_n<1000) ss3.process=s_cuts+process+TString::Format("_file_0%i",file_n);
  else ss3.process=s_cuts+process+TString::Format("_file_%i",file_n);

  ss3.Selection(-1,cuts);
  if(cuts<1) ss3.SelectionParticleLevel(-1,cuts);
  gSystem->Exit(0);

  return 0;
}
