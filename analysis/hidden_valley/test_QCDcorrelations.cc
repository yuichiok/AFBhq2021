#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_QCDcorrelations( TString file="", TString process="2f_hadronic", int file_n=0, int cut=4){

  TString s_cut=TString::Format("cuts%i_",cut);
  cout<< " "<<endl;
  cout<< file << endl;
  QQbarAnalysisClass ss3(file);
  if(file_n<10) ss3.process=s_cut+process+TString::Format("_file_00%i",file_n);
  else if(file_n<100) ss3.process=s_cut+process+TString::Format("_file_0%i",file_n);
  else ss3.process=s_cut+process+TString::Format("_file_%i",file_n);

  ss3.QCDCorr(-1,cut);
  
  gSystem->Exit(0);

  return 0;
}
