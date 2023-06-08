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
#include "fit.C"

TString energy="500GeV_";


float error_calc(int quark=4, int ipol=0, float lum=900, TString pid="dEdx") {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.8);
  TGaxis::SetMaxDigits(3);

  int iprocess=1; //cut in radiative return

  float luminosity[2]={0};
  TH1F *hstats[2];


  //dEdx
  TString pol="eL_pR";
  TString filename = TString::Format("../results_"+energy+pid+"/AFBreco_pdg%i_2f_hadronic_%s.root",quark,pol.Data());
  TFile *f = new TFile(filename);
  hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[0]->Integral()>0) luminosity[0]=hstats[0]->Integral()/cross_section[0][iprocess];
  else luminosity[0]=0;
  
  TH1F* AFBcheat_eL= (TH1F*)f->Get("h_AFBcheat");
  //TH1F* eff_eL=Efficiency(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL,AFBparton_eL);

  pol="eR_pL";
  filename = TString::Format("../results_"+energy+pid+"/AFBreco_pdg%i_2f_hadronic_%s.root",quark,pol.Data());
  f = new TFile(filename);
  hstats[1]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[1]->Integral()>0) luminosity[1]=hstats[1]->Integral()/cross_section[1][iprocess];
  else luminosity[1]=0;
  
  TH1F* AFBcheat_eR= (TH1F*)f->Get("h_AFBcheat");
  
  //**********************Pol Histos
  TH1F * AFBcheat=PolHisto(AFBcheat_eR,AFBcheat_eL,ipol,luminosity,lum,1);
  
  //***** DRAW
  TF1 *func_parton=fit_histo(AFBcheat, -0.85,0.85,false);

  float plus = func_parton->Integral(0,1);
  float minus = func_parton->Integral(-1,0);
  float plus_e = func_parton->IntegralError(0,1);
  float minus_e = func_parton->IntegralError(1,0);
  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);

  return 100.*dAfb/Afb;
  
}

void AFBSyst(int quark=4, int ipol=0, float lum=900) {

  float error1=error_calc(quark, ipol, lum, "dEdx");
  float error2=error_calc(quark, ipol, lum, "dNdx");
  cout<<error1 << " "<<error2<<endl;

  double afb_stat_dEdx[4]={0.36,0.49,0.22,0.64};

  if(quark==4 && ipol==2) cout << " dEdx ="<<afb_stat_dEdx[0]<<" dNdx ="<<afb_stat_dEdx[0]*error2/error1<<endl;
  if(quark==4 && ipol==3) cout << " dEdx ="<<afb_stat_dEdx[1]<<" dNdx ="<<afb_stat_dEdx[1]*error2/error1<<endl;
  if(quark==5 && ipol==2) cout << " dEdx ="<<afb_stat_dEdx[2]<<" dNdx ="<<afb_stat_dEdx[2]*error2/error1<<endl;
  if(quark==5 && ipol==3) cout << " dEdx ="<<afb_stat_dEdx[3]<<" dNdx ="<<afb_stat_dEdx[3]*error2/error1<<endl;



}


  void AFB_dEdx_vs_dNdx() {
    AFBSyst(4,2,2000);
  }
    
