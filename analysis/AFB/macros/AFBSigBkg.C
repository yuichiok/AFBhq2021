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
#include "../../common/histograms.h"
#include "utils.h"


TString energy="500GeV";

/*
  void Labels(int quark){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(quark==4)
  QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c}",kGray+2);
  if(quark==5)
  QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow b#bar{b}",kGray+2);
  
  //QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);

  }*/


void SigBkg(int pol=3,int quark=4, float lum=2000) {

  folder="../results_"+energy+"_dEdx/SigBkg_";

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  // TGaxis::SetMaxDigits(2);

  int iquark=0, iquark2=1, iquark3=2;
  if(quark==4) {
    iquark=1;
    iquark2=0;
  }
  TH1F *signal_0 = GetHisto2(1,TString::Format("h_AFBreco_cat0_%i",iquark),pol,quark,lum,1);
  TH1F *signal_1 = GetHisto2(1,TString::Format("h_AFBreco_cat1_%i",iquark),pol,quark,lum,1);
  TH1F *signal_2 = GetHisto2(1,TString::Format("h_AFBreco_cat2_%i",iquark),pol,quark,lum,1);
  signal_0->Add(signal_1);
  signal_0->Add(signal_2);

  TH1F *bkg_hq_0 = GetHisto2(1,TString::Format("h_AFBreco_cat0_%i",iquark2),pol,quark,lum,1);
  TH1F *bkg_hq_1 = GetHisto2(1,TString::Format("h_AFBreco_cat1_%i",iquark2),pol,quark,lum,1);
  TH1F *bkg_hq_2 = GetHisto2(1,TString::Format("h_AFBreco_cat2_%i",iquark2),pol,quark,lum,1);
  bkg_hq_0->Add(bkg_hq_1);
  bkg_hq_0->Add(bkg_hq_2);

  TH1F *bkg_uds_0 = GetHisto2(1,TString::Format("h_AFBreco_cat0_%i",iquark3),pol,quark,lum,1);
  TH1F *bkg_uds_1 = GetHisto2(1,TString::Format("h_AFBreco_cat1_%i",iquark3),pol,quark,lum,1);
  TH1F *bkg_uds_2 = GetHisto2(1,TString::Format("h_AFBreco_cat2_%i",iquark3),pol,quark,lum,1);
  bkg_uds_0->Add(bkg_uds_1);
  bkg_uds_0->Add(bkg_uds_2);

  TH1F *bkg_radret_0 = GetHisto2(1,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,lum,1);
  TH1F *bkg_radret_1 = GetHisto2(1,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,lum,1);
  TH1F *bkg_radret_2 = GetHisto2(1,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,lum,1);
  bkg_radret_0->Add(bkg_radret_1);
  bkg_radret_0->Add(bkg_radret_2);

  //  TString process[5]={"4f_ZZ_hadronic","qqH","4f_WW_hadronic","2f_hadronic_sample","2f_hadronic"};

 
  TH1F *bkg_zz_0 = GetHisto2(2,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,lum,0);
  TH1F *bkg_zz_1 = GetHisto2(2,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,lum,0);
  TH1F *bkg_zz_2 = GetHisto2(2,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,lum,0);
  bkg_zz_0->Add(bkg_zz_1);
  bkg_zz_0->Add(bkg_zz_2);

  TH1F *bkg_qqH_0 = GetHisto2(3,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,lum,0);
  TH1F *bkg_qqH_1 = GetHisto2(3,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,lum,0);
  TH1F *bkg_qqH_2 = GetHisto2(3,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,lum,0);
  bkg_qqH_0->Add(bkg_qqH_1);
  bkg_qqH_0->Add(bkg_qqH_2);

  TH1F *bkg_ww_0 = GetHisto2(4,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,lum,0);
  TH1F *bkg_ww_1 = GetHisto2(4,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,lum,0);
  TH1F *bkg_ww_2 = GetHisto2(4,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,lum,0);
  bkg_ww_0->Add(bkg_ww_1);
  bkg_ww_0->Add(bkg_ww_2);

  TH1F *bkg_ttbar_0 = GetHisto2(5,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,lum,0);
  TH1F *bkg_ttbar_1 = GetHisto2(5,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,lum,0);
  TH1F *bkg_ttbar_2 = GetHisto2(5,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,lum,0);
  bkg_ttbar_0->Add(bkg_ttbar_1);
  bkg_ttbar_0->Add(bkg_ttbar_2);


  //gPad->SetLogy();
  if(quark==4) {
    //signal
    signal_0->SetLineColor(2);
    signal_0->SetLineWidth(2);
    signal_0->SetFillColor(2);
  }

  if(quark==5) {
     //signakl
    signal_0->SetLineColor(4);
    signal_0->SetLineWidth(2);
    signal_0->SetFillColor(4);
  }

  //hq
  bkg_hq_0->SetFillColor(kGray);
  bkg_hq_0->SetLineColor(kGray);
  bkg_hq_0->SetFillStyle(3002);

  //uds quark bkg
  bkg_uds_0->SetFillColor(kGray);
  bkg_uds_0->SetLineColor(kGray);
  bkg_uds_0->SetFillStyle(3002);
  
  //radreturn
  bkg_radret_0->SetLineColor(kGreen+1);
  bkg_radret_0->SetLineWidth(2);
  bkg_radret_0->SetFillColor(kGreen+1);
  bkg_radret_0->SetFillStyle(3001);

  bkg_ww_0->SetFillColor(kGray);
  bkg_ww_0->SetLineColor(kGray);
  bkg_ww_0->SetFillStyle(3002);

  bkg_ttbar_0->SetFillColor(kGray);
  bkg_ttbar_0->SetLineColor(kGray);
  bkg_ttbar_0->SetFillStyle(3002);
  
  bkg_qqH_0->SetFillColor(kGray);
  bkg_qqH_0->SetLineColor(kGray);
  bkg_qqH_0->SetFillStyle(3002);

  bkg_zz_0->SetFillColor(kGray);
  bkg_zz_0->SetLineColor(kGray);
  bkg_zz_0->SetFillStyle(3002);
  
  THStack *f1stack = new THStack("f1stack","");
  f1stack->Add(bkg_zz_0);
  f1stack->Add(bkg_qqH_0);
  f1stack->Add(bkg_ww_0);
  f1stack->Add(bkg_ttbar_0);
  f1stack->Add(bkg_radret_0);
  f1stack->Add(bkg_uds_0);
  f1stack->Add(bkg_hq_0);
  f1stack->Add(signal_0);

  float bs_rad=100.*bkg_radret_0->Integral()/signal_0->Integral();
  float bs_other=100.*(bkg_zz_0->Integral()+bkg_ww_0->Integral()+bkg_ttbar_0->Integral()+bkg_qqH_0->Integral()+bkg_hq_0->Integral()+bkg_uds_0->Integral())/signal_0->Integral();

  TCanvas* c_f1_MC = new TCanvas(TString::Format("c_f1_MC_%i_%i",quark,pol),TString::Format("c_f1_MC_%i",quark),800,800);
  c_f1_MC->cd(1);
  // c_f1_MC->SetGrid();
  f1stack->Draw("histoe");
  f1stack->GetXaxis()->SetTitle("|cos #theta|");
  f1stack->GetYaxis()->SetTitle("entries");

  c_f1_MC->Update();
  f1stack->GetYaxis()->SetRangeUser(0,100);

  Labels(pol,iquark,lum);

  TLegend *leg = new TLegend(0.4,0.30,0.8,0.5,"","blNDC");
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  TString signal="Signal: c#bar{c}";
  TString qbkg="b#bar{b}";

  if(quark==5) {
    signal="Signal: b#bar{b}";
    qbkg="c#bar{c}";
  }

  leg->AddEntry(signal_0,signal,"lf");
  leg->AddEntry(bkg_radret_0,TString::Format("Rad. Ret., (B/S=%.1f%)",bs_rad),"lf");
  leg->AddEntry(bkg_uds_0,TString::Format("Other bkg, (B/S=%.1f%)",bs_other),"lf");

  // leg->AddEntry(bkg_ww_0,"WW","lf");
  // leg->AddEntry(bkg_qqH_0,"q#bar{q}H","lf");
  // leg->AddEntry(bkg_zz_0,"ZZ","lf");
  
  leg->SetFillStyle(1001);
  leg->SetFillColor(0);
  leg->SetLineColor(1);
  leg->SetBorderSize(1);
  leg->Draw();

  c_f1_MC->Print(TString::Format("plots_"+energy+"_AFB/SigBkg_pdg_%i_pol_%i.eps",quark,pol));
    
    
}

void AFBSigBkg(int pol=3,int quark=4) {

  SigBkg(2,5);
  //SigBkg(3,4);
  //SigBkg(2,5);
  //SigBkg(3,5);


}
