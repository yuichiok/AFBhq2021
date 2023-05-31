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
#include "uncertainties.h"



void Plots_AFB_results() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);



  TH1F * c_noTPC = new TH1F("c_noTPC","c_noTPC",12,0.,12.);
  TH1F * c_def = new TH1F("c_def","c_def",12,0.,12.);
  TH1F * c_dEdx = new TH1F("c_dEdx","c_dEdx",12,0.,12.);
  TH1F * c_dNdx = new TH1F("c_dNdx","c_dNdx",12,0.,12.);

  TH1F * q_eL = new TH1F("q_eL","q_eL",12,-0.5,11.5);

  //bquark  
  double x[8]={0.5,1.5,2.5,3.5,6.5,7.5,8.5,9.5};
  double y[8]={sqrt(pow(afb_stat[2]/sqrt(0.54),2)+pow(afb_syst[2],2)),afb_stat[2],afb_stat_dEdx[2],afb_stat_dNdx[2],sqrt(pow(afb_stat[3]/sqrt(0.54),2)+pow(afb_syst[3],2)),afb_stat[3],afb_stat_dEdx[3],afb_stat_dNdx[3]};

  //cquark
  double y2[8]={sqrt(pow(afb_stat[0]/sqrt(0.25),2)+pow(afb_syst[0],2)),afb_stat[0],afb_stat_dEdx[0],afb_stat_dNdx[0],sqrt(pow(afb_stat[1]/sqrt(0.25),2)+pow(afb_syst[1],2)),afb_stat[1],afb_stat_dEdx[1],afb_stat_dNdx[1]};


  c_noTPC->Fill(0.5, y2[0] );
  c_def->Fill(1.5, y2[1] );
  c_dEdx->Fill(2.5, y2[2] );
  c_dNdx->Fill(3.5, y2[3] );


  c_noTPC->Fill(5.5, y2[4] );
  c_def->Fill(6.5, y2[5] );
  c_dEdx->Fill(7.5, y2[6] );
  c_dNdx->Fill(8.5, y2[7] );


  TH1F * b_noTPC = new TH1F("b_noTPC","b_noTPC",12,0.,12.);
  TH1F * b_def = new TH1F("b_def","b_def",12,0.,12.);
  TH1F * b_dEdx = new TH1F("b_dEdx","b_dEdx",12,0.,12.);
  TH1F * b_dNdx = new TH1F("b_dNdx","b_dNdx",12,0.,12.);

  b_noTPC->Fill(0.5, y[0] );
  b_def->Fill(1.5, y[1] );
  b_dEdx->Fill(2.5, y[2] );
  b_dNdx->Fill(3.5, y[3] );


  b_noTPC->Fill(5.5, y[4] );
  b_def->Fill(6.5, y[5] );
  b_dEdx->Fill(7.5, y[6] );
  b_dNdx->Fill(8.5, y[7] );



  //LABELS
  /* const Int_t nx = 11;
  const char *obs[nx] = {".","R_{c}","..","...","A_{FB}^{c}","....",".....",
			 "R_{b}","......",".......","A_{FB}^{b#bar{b}}"};
   q_eL->SetCanExtend(TH1::kAllAxes);
   for (Int_t i=0;i<11;i++) {
      q_eL->Fill(obs[i],5);
   }
   q_eL->LabelsDeflate();*/

  q_eL->GetXaxis()->SetBinLabel(2,"P_{e^{-}e^{+}}(-0.8,+0.3)");
  q_eL->GetXaxis()->SetBinLabel(7,"P_{e^{-}e^{+}}(+0.8,-0.3)");


  TCanvas* c_AFB = new TCanvas("c_AFB","c_AFB",800,800);
  c_AFB->cd(1);
  q_eL->GetYaxis()->SetTitle("relative uncertainty [%]");
  q_eL->GetYaxis()->SetRangeUser(0,1.5);
  q_eL->GetXaxis()->SetRangeUser(0,9);
  q_eL->GetXaxis()->SetTickLength(0);
  //q_eL->SetFillStyle(3001);
  //  q_eL->GetXaxis()->SetNdivisions(512);
  q_eL->GetXaxis()->SetLabelSize(0.07);

  q_eL->SetLineWidth(0);
  q_eL->SetLineStyle(0);
  q_eL->SetFillColor(kGreen+3);
  q_eL->Draw("");

  
  c_noTPC->SetLineWidth(0);
  c_noTPC->SetLineStyle(0);
  c_noTPC->SetFillColor(kOrange+2);
  //c_noTPC->SetFillStyle(3001);
  c_noTPC->Draw("histosame");

  c_def->SetLineWidth(0);
  c_def->SetLineStyle(0);
  c_def->SetFillColor(kOrange);
  //c_def->SetFillStyle(3003);
  c_def->Draw("histosame");

  c_dEdx->SetLineWidth(0);
  c_dEdx->SetLineStyle(0);
  c_dEdx->SetFillColor(kGreen);
  //c_dEdx->SetFillStyle(1001);
  c_dEdx->Draw("histosame");

  c_dNdx->SetLineWidth(0);
  c_dNdx->SetLineStyle(0);
  c_dNdx->SetFillColor(kGreen+3);
  //c_dNdx->SetFillStyle(3005);
  c_dNdx->Draw("histosame");


  
  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  // Labels(-1,-1,900);
  QQBARLabel2(0.2,0.9, "Statistical unc. for AFB_{c}",kBlack,0.06);
  QQBARLabel(0.87,0.953,"");
  QQBARLabel2(0.15,0.96, "ILC250 2000 fb^{-1} ",960);
  
  TLegend *leg_b = new TLegend(0.2,0.65,0.4,0.8);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(c_noTPC,"No PID at all","f");
  leg_b->AddEntry(c_def,"No PID in flav. tagging","f");
  leg_b->AddEntry(c_dEdx,"PID from dEdx","f");
  leg_b->AddEntry(c_dNdx,"PID from dNdx","f");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  TCanvas* b_AFB = new TCanvas("b_AFB","b_AFB",800,800);
  b_AFB->cd(1);
  q_eL->GetYaxis()->SetTitle("relative uncertainty [%]");
  q_eL->GetYaxis()->SetRangeUser(0,1.5);
  q_eL->GetXaxis()->SetRangeUser(0,9);
  q_eL->GetXaxis()->SetTickLength(0);
  //q_eL->SetFillStyle(3001);
  //  q_eL->GetXaxis()->SetNdivisions(512);
  q_eL->GetXaxis()->SetLabelSize(0.07);

  q_eL->SetLineWidth(0);
  q_eL->SetLineStyle(0);
  q_eL->SetFillColor(kGreen+3);
  q_eL->Draw("");

  
  b_noTPC->SetLineWidth(0);
  b_noTPC->SetLineStyle(0);
  b_noTPC->SetFillColor(kOrange+2);
  //c_noTPC->SetFillStyle(3001);
  b_noTPC->Draw("histosame");

  b_def->SetLineWidth(0);
  b_def->SetLineStyle(0);
  b_def->SetFillColor(kOrange);
  //c_def->SetFillStyle(3003);
  b_def->Draw("histosame");

  b_dEdx->SetLineWidth(0);
  b_dEdx->SetLineStyle(0);
  b_dEdx->SetFillColor(kGreen);
  //c_dEdx->SetFillStyle(1001);
  b_dEdx->Draw("histosame");

  b_dNdx->SetLineWidth(0);
  b_dNdx->SetLineStyle(0);
  b_dNdx->SetFillColor(kGreen+3);
  //c_dNdx->SetFillStyle(3005);
  b_dNdx->Draw("histosame");


  
  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  // Labels(-1,-1,900);
  QQBARLabel2(0.2,0.9, "Statistical unc. for AFB_{b}",kBlack,0.06);
  QQBARLabel(0.87,0.953,"");
  QQBARLabel2(0.15,0.96, "ILC250 2000 fb^{-1} ",960);
  

  leg_b->Draw();

  //c_R_AFB->Print("plots_"+energy+"_final/Observables_Unc.eps");

  
}

void AFB_results() {

  Plots_AFB_results();
  
}
    
