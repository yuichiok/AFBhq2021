#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"

int AFBReco( TString file="", TString process="2f_hadronic", TString pol="eL", int file_n=0, int quark=4){

  cout<< file << endl;
  QQbarAnalysisClass ss3(file);
  if(file_n<10) ss3.process=process+"_"+pol+TString::Format("_file_00%i",file_n);
  else if(file_n<100) ss3.process=process+"_"+pol+TString::Format("_file_0%i",file_n);
  else ss3.process=process+"_"+pol+TString::Format("_file_%i",file_n);

  ss3.AFBreconstruction(-1,quark,pol);
  gSystem->Exit(0);
  
  return 0;
}
