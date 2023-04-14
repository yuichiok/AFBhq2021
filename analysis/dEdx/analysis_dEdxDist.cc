#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis_dEdxDist(TString file, TString output, float cut_p){

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  cout<<file<<endl;
  observable ss3(file);
  
  ss3.dEdxDist(-1,TString::Format("%s",output.Data()),"kaon",cut_p); 
  ss3.dEdxDist(-1,TString::Format("%s",output.Data()),"pion",cut_p); 
  ss3.dEdxDist(-1,TString::Format("%s",output.Data()),"proton",cut_p); 

  gSystem->Exit(0);

  return 0;
}
