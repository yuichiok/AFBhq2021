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
#include "AFBFit.C"

double afb_stat_dNdx_500[4]={0.39,0.53,0.29,0.70};
double afb_stat_dNdx_250[4]={0.32,0.44,0.2,0.62};


void Plots() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);

  TH1F * q_eL = new TH1F("c_eL","c_eL",11,-0.5,10.5);
  TH1F * q_eR = new TH1F("c_eR","c_eR",11,-0.5,10.5);

  TH1F * eL250 = new TH1F("eL250","eL250",11,0.,11.);
  TH1F * eR250 = new TH1F("eR250","eR250",11,0.,11.);
  TH1F * eL500 = new TH1F("eL500","eL500",11,0.,11.);
  TH1F * eR500 = new TH1F("eR500","eR500",11,0.,11.);


  eL250->Fill(0.5,afb_stat_dNdx_250[0]);
  eL250->Fill(5.5,afb_stat_dNdx_500[0]);

  eR250->Fill(1.5,afb_stat_dNdx_250[1]);
  eR250->Fill(6.5,afb_stat_dNdx_500[1]);

  eL500->Fill(2.5,afb_stat_dNdx_250[2]);
  eL500->Fill(7.5,afb_stat_dNdx_500[2]);

  eR500->Fill(3.5,afb_stat_dNdx_250[3]);
  eR500->Fill(8.5,afb_stat_dNdx_500[3]);
  

  q_eL->GetXaxis()->SetBinLabel(3,"A_{FB}^{c}");
  q_eL->GetXaxis()->SetBinLabel(8,"A_{FB}^{b}");

  TCanvas* c_R_AFB = new TCanvas("c_R_AFB","c_AFB",800,800);
  c_R_AFB->cd(1);
  // gPad->SetLogy();
  // c_eL->GetXaxis()->SetTitle("cos #theta");
  q_eL->GetYaxis()->SetTitle("stat. relative uncertainty [%]");
  q_eL->GetYaxis()->SetRangeUser(0,0.85);
  q_eL->GetXaxis()->SetRangeUser(0,9);
  q_eL->GetXaxis()->SetTickLength(0);
  //q_eL->SetFillStyle(3001);
  //  q_eL->GetXaxis()->SetNdivisions(512);
  q_eL->GetXaxis()->SetLabelSize(0.1);
  q_eL->Draw("");
  //
  eL250->SetLineWidth(2);
  eL250->SetLineStyle(1);
  eL250->SetFillColor(kBlue-6);
  eL250->SetLineColor(kBlue-6);
  //eR250->SetFillStyle(3002);
  eL250->Draw("histosame");
  eR250->SetLineWidth(0);
  eR250->SetLineStyle(1);
  eR250->SetFillColor(kBlack);
  eR250->SetLineColor(kBlack);
  eR250->SetFillStyle(3002);
  eR250->Draw("histosame");

  eL500->SetLineWidth(0);
  eL500->SetLineStyle(1);
  eL500->SetFillColor(kRed-2);
  eL500->SetLineColor(kRed-2);
  //eR500->SetFillStyle(3002);
  eL500->Draw("histosame");
  eR500->SetLineWidth(0);
  eR500->SetLineStyle(1);
  eR500->SetFillColor(kBlack);
  eR500->SetLineColor(kBlack);
  eR500->SetFillStyle(3013);
  eR500->Draw("histosame");

  q_eL->Draw("histosame");


  
  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  // Labels(-1,-1,900);
  //    QQBARLabel2(0.1,0.05, "e^{-}e^{+} #rightarrow "+quark,color+2);
  QQBARLabel(0.75,0.854,"",-1, 0.1);
  //QQBARLabel2(0.15,0.96, "ILC500 2000 fb^{-1} ",960);
  
  TLegend *leg_b = new TLegend(0.2,0.77,0.4,0.94);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(eL250,"ILC250 (-0.8,+0.3)","f");
  leg_b->AddEntry(eR250,"ILC250 (+0.8,-0.3)","f");
  leg_b->AddEntry(eL500,"ILC500 (-0.8,+0.3)","f");
  leg_b->AddEntry(eR500,"ILC500 (+0.8,-0.3)","f");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_R_AFB->Print("stat_AFB_ILC250_ILC500.eps");

  
}

void AFB_resultsILC250_ILC500() {

  //Plots_AFB_method();
  Plots();

}
    
