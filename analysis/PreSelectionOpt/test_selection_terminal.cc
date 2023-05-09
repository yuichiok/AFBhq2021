#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_selection_terminal( TString file="", TString process="2f_hadronic", TString pol="eL", int type=4, float Kv=35, int bkg=0){

  TString s_type=TString::Format("cuts%i_",type);
  cout<< " "<<endl;
  cout<< file << endl;
  QQbarAnalysisClass ss3(file);
  ss3.process=s_type+process+"_"+pol;
  ss3.Selection(-1,type,Kv,bkg);
  gSystem->Exit(0);

  return 0;
}
