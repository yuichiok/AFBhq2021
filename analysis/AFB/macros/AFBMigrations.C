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

TString energy="250GeV";

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


void Migrations(int pol=2,int quark=5, int syst=0) {

  folder="../results_"+energy+"/AFBreco_";

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);
  TGaxis::SetMaxDigits(3);


  TH1F *reco_0 = GetHisto2(1,TString::Format("h_AFBreco_cat0_syst%i",syst),pol,quark,900,1,0);
  TH1F *reco_1 = GetHisto2(1,TString::Format("h_AFBreco_cat1_syst%i",syst),pol,quark,900,1,0);
  TH1F *reco_2 = GetHisto2(1,TString::Format("h_AFBreco_cat2_syst%i",syst),pol,quark,900,1,0);
  reco_0->Add(reco_1);
  reco_0->Add(reco_2);

  TH1F *corrected_0 = GetHisto2(1,TString::Format("h_AFBreco_pqcorrectedreco_cat0_syst%i",syst),pol,quark,900,1,0);
  TH1F *corrected_1 = GetHisto2(1,TString::Format("h_AFBreco_pqcorrectedreco_cat1_syst%i",syst),pol,quark,900,1,0);
  TH1F *corrected_2 = GetHisto2(1,TString::Format("h_AFBreco_pqcorrectedreco_cat2_syst%i",syst),pol,quark,900,1,0);
  corrected_0->Add(corrected_1);
  corrected_0->Add(corrected_2);
  if(pol==2 && quark==5) corrected_0->SetBinError(1,500.);
  if(pol==3 && quark==4) corrected_0->SetBinError(1,100.);

  TH1F *chargecheatreco_0 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat0_syst%i",syst),pol,quark,900,1,0);
  TH1F *chargecheatreco_1 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat1_syst%i",syst),pol,quark,900,1,0);
  TH1F *chargecheatreco_2 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat2_syst%i",syst),pol,quark,900,1,0);
  chargecheatreco_0->Add(chargecheatreco_1);
  chargecheatreco_0->Add(chargecheatreco_2);


  TCanvas* c_f1_MC = new TCanvas(TString::Format("c_f1_MC_%i_%i",quark,pol),TString::Format("c_f1_MC_%i",quark),800,800);
  c_f1_MC->cd(1);

  chargecheatreco_0->GetXaxis()->SetTitle("cos #theta");
  chargecheatreco_0->GetYaxis()->SetTitle("entries");
  chargecheatreco_0->SetLineColor(kGray+1);
  chargecheatreco_0->SetLineWidth(2);
  chargecheatreco_0->SetLineStyle(2);
  chargecheatreco_0->SetFillStyle(3003);
  chargecheatreco_0->SetFillColor(kGray+1);
  chargecheatreco_0->Draw("histo");
  
  corrected_0->SetLineColor(4);
  corrected_0->SetMarkerColor(4);
  corrected_0->SetLineWidth(2);
  corrected_0->SetMarkerStyle(4);
  corrected_0->SetMarkerColor(4);
  corrected_0->Draw("pesame");

  reco_0->SetLineColor(2);
  reco_0->SetLineWidth(2);
  reco_0->SetMarkerStyle(20);
  reco_0->SetMarkerColor(2);
  reco_0->Draw("pesame");


  Labels(pol,quark,900,960);

  TLegend *leg = new TLegend(0.18,0.70,0.7,0.85,"","blNDC");
  leg->SetTextFont(42);
  leg->SetTextSize(0.028);
  leg->AddEntry(chargecheatreco_0,"Detector Level (true-MC charge)","f");
  leg->AddEntry(reco_0,"Detector Level (w/o charge correction)","pe");
  leg->AddEntry(corrected_0,"Detector Level (w/ charge correction)","pe");
  // leg->AddEntry(bkg_zz_0,"ZZ","lf");
  
  // leg->SetFillStyle(1001);
  leg->SetFillColor(0);
  // leg->SetLineColor(1);
  leg->SetBorderSize(0);
  leg->Draw();

  c_f1_MC->Print(TString::Format("plots_"+energy+"_AFB/Migrations_pdg_%i_pol_%i.eps",quark,pol));
    
    
}

void AFBMigrations(int pol=3,int quark=4) {

  Migrations(2,4);
  Migrations(3,4);
  Migrations(2,5);
  Migrations(3,5);

}
