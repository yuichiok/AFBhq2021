#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int AFBAnalysis( TString file="", TString process="2f_hadronic", TString pol="eL", int file_n=0, float Kv=35, int quark=4, int bkg=0){

  cout<< file << endl;
  QQbarAnalysisClass ss3(file);
  if(file_n<10) ss3.process=process+"_"+pol+TString::Format("_file_00%i",file_n);
  else if(file_n<100) ss3.process=process+"_"+pol+TString::Format("_file_0%i",file_n);
  else ss3.process=process+"_"+pol+TString::Format("_file_%i",file_n);

  ss3.dedxcut=8;
  ss3.AFBAnalysis(-1,bkg,Kv,quark);
  gSystem->Exit(0);
  
  return 0;
}
