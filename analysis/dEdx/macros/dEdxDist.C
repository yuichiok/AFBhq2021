#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "../../../style/Style.C"
#include "../../../style/Labels.C"



void dEdxDist(TString reference="kaon",TString type="") {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);


  TString filename = "../results/dEdxdist_"+reference+"_2f_hadronic_sample_eL_pR_cutP_3.root";

  TFile *f = new TFile(filename);

  TString name[6]={"kaon","pion","proton","muon","electron","others"};

  TH2F*  histo2d[6];
  for(int i=0; i<6; i++) histo2d[i] = (TH2F*)f->Get("costheta_kdEdx_dist_"+name[i]+type);
  
  float mean[6][10]={0};
  float rms[6][10]={0};
  for(int i=0; i<6; i++) {
    for(int ip=0; ip<10; ip++) {
      TH1F *h1 =(TH1F*)histo2d[i] ->ProjectionY(TString::Format(name[i]+"_%i",ip),ip,ip+1);
      TF1 * f1 = new TF1("f1","gaus",h1->GetMean()-h1->GetRMS(),h1->GetMean()+3*h1->GetRMS());
      h1->Fit(f1,"MR");
      mean[i][ip]=f1->GetParameter(1);
      rms[i][ip]=f1->GetParameter(2);
    }
  }

  cout<<" ############################## "<<endl;
  cout<< reference <<" "<< type<< endl;
 for(int i=0; i<6; i++) {
    cout<< "std::vector<float> _dedx_dist_BB"<<reference<<"_"<<name[i]<<"_mean={";
    for(int ip=0; ip<10; ip++) {
      if(ip<9) cout<<mean[i][ip]<<",";
      else cout<<mean[i][ip]<<"};"<<endl;
    }
  
    cout<< "std::vector<float> _dedx_dist_BB"<<reference<<"_"<<name[i]<<"_rms={";
    for(int ip=0; ip<10; ip++) {
      if(ip<9) cout<<rms[i][ip]<<",";
      else cout<<rms[i][ip]<<"};"<<endl;
    }
  }
  


}

