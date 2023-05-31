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

void Plots_R_AFB() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);

  TH1F * q_eL = new TH1F("c_eL","c_eL",12,-0.5,11.5);
  TH1F * q_eR = new TH1F("c_eR","c_eR",12,-0.5,11.5);

  TH1F * c_eL = new TH1F("c_eL","c_eL",11,0.,11.);
  TH1F * c_eR = new TH1F("c_eR","c_eR",11,0.,11.);
  TH1F * b_eL = new TH1F("b_eL","b_eL",11,0.,11.);
  TH1F * b_eR = new TH1F("b_eR","b_eR",11,0.,11.);

  double y[8]={r_stat[0],r_stat[1],afb_stat[0],afb_stat[1],r_stat[2],r_stat[3],afb_stat[2],afb_stat[3]};
  double x[8]={0.5,1.5,3.5,4.5,6.5,7.5,9.5,10.5};

  double ey[8]={0,0,0,0,0,0,0,0};
  double ex[8]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  TGraphErrors * gstat = new TGraphErrors(8,x,y,ex,ey);

  double y2[4]={sqrt(pow(afb_stat[0]/sqrt(0.25),2)+pow(afb_syst[0],2)),sqrt(pow(afb_stat[1]/sqrt(0.25),2)+pow(afb_syst[1],2)),sqrt(pow(afb_stat[2]/sqrt(0.54),2)+pow(afb_syst[2],2)),sqrt(pow(afb_stat[3]/sqrt(0.54),2)+pow(afb_syst[2],2))};
  double x2[4]={3.5,4.5,9.5,10.5};

  double ex2[4]={0,0,0,0};
  double ey2[4]={y2[0]-sqrt( pow(afb_stat[0],2)+pow(afb_syst[0],2)),y2[1],y2[2]-sqrt( pow(afb_stat[2],2)+pow(afb_syst[2],2)),y2[3]};//0.5,0.5,0.5,0.5};
  TGraphAsymmErrors * g_noTPC = new TGraphAsymmErrors(4,x2,y2,ex2,ex2,ey2,ex2);


  c_eL->Fill(0.5, sqrt( pow(r_stat[0],2)+pow(r_syst[0],2)));
  c_eL->Fill(3.5, sqrt( pow(afb_stat[0],2)+pow(afb_syst[0],2)));

  c_eR->Fill(1.5, sqrt( pow(r_stat[1],2)+pow(r_syst[1],2)));
  c_eR->Fill(4.5, sqrt( pow(afb_stat[1],2)+pow(afb_syst[1],2)));

  b_eL->Fill(6.5, sqrt( pow(r_stat[2],2)+pow(r_syst[2],2)));
  b_eL->Fill(9.5, sqrt( pow(afb_stat[2],2)+pow(afb_syst[2],2)));

  b_eR->Fill(7.5, sqrt( pow(r_stat[3],2)+pow(r_syst[3],2)));
  b_eR->Fill(10.5, sqrt( pow(afb_stat[3],2)+pow(afb_syst[3],2)));
  cout<< sqrt( pow(afb_stat[3],2)+pow(afb_syst[3],2))<<endl;


  //LABELS
  /* const Int_t nx = 11;
  const char *obs[nx] = {".","R_{c}","..","...","A_{FB}^{c}","....",".....",
			 "R_{b}","......",".......","A_{FB}^{b#bar{b}}"};
   q_eL->SetCanExtend(TH1::kAllAxes);
   for (Int_t i=0;i<11;i++) {
      q_eL->Fill(obs[i],5);
   }
   q_eL->LabelsDeflate();*/

  q_eL->GetXaxis()->SetBinLabel(2,"R_{c}");
  q_eL->GetXaxis()->SetBinLabel(5,"A_{FB}^{c}");
  q_eL->GetXaxis()->SetBinLabel(8,"R_{b}");
  q_eL->GetXaxis()->SetBinLabel(11,"A_{FB}^{b}");

  TCanvas* c_R_AFB = new TCanvas("c_R_AFB","c_AFB",1400,800);
  c_R_AFB->cd(1);
  // gPad->SetLogy();
  // c_eL->GetXaxis()->SetTitle("cos #theta");
  q_eL->GetYaxis()->SetTitle("total relative uncertainty [%]");
  q_eL->GetYaxis()->SetRangeUser(0,1.5);
  q_eL->GetXaxis()->SetRangeUser(0,11);
  q_eL->GetXaxis()->SetTickLength(0);
  //q_eL->SetFillStyle(3001);
  //  q_eL->GetXaxis()->SetNdivisions(512);
  q_eL->GetXaxis()->SetLabelSize(0.1);

  q_eL->SetLineWidth(0);
  q_eL->SetLineStyle(0);
  q_eL->SetFillColor(kGreen+3);
  q_eL->Draw("");
  q_eR->SetLineWidth(0);
  q_eR->SetLineStyle(0);
  q_eR->SetFillColor(kGreen-4);
  //  q_eR->SetFillStyle(3003);

  g_noTPC->SetMarkerStyle(29);
  g_noTPC->SetMarkerColor(kGreen+1);
  g_noTPC->SetLineWidth(1);
  g_noTPC->SetLineColor(kGreen+1);
  g_noTPC->SetMarkerSize(1.4);
  g_noTPC->Draw("pe");
  
  c_eL->SetLineWidth(0);
  c_eL->SetLineStyle(0);
  c_eL->SetFillColor(kGreen+3);
  //c_eL->SetFillStyle(3001);
  c_eL->Draw("histosame");

  c_eR->SetLineWidth(0);
  c_eR->SetLineStyle(0);
  c_eR->SetFillColor(kGreen-4);
  //  c_eR->SetFillStyle(3003);
  c_eR->Draw("histosame");

  b_eL->SetLineWidth(0);
  b_eL->SetLineStyle(0);
  b_eL->SetFillColor(kGreen+3);
  //b_eL->SetFillStyle(3001);
  b_eL->Draw("histosame");

  b_eR->SetLineWidth(0);
  b_eR->SetLineStyle(0);
  b_eR->SetFillColor(kGreen-4);
  //b_eR->SetFillStyle(3003);
  b_eR->Draw("histosame");

  gstat->SetMarkerStyle(21);
  gstat->SetMarkerColor(kBlack);
  gstat->SetLineColor(kBlack);
  gstat->Draw("pe");

  
  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  // Labels(-1,-1,900);
  //    QQBARLabel2(0.1,0.05, "e^{-}e^{+} #rightarrow "+quark,color+2);
  QQBARLabel(0.89,0.954,"");
  QQBARLabel2(0.15,0.96, "ILC250 2000 fb^{-1} ",960);
  
  TLegend *leg_b = new TLegend(0.2,0.75,0.4,0.9);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(q_eL,"P_{e^{-}e^{+}}(-0.8,+0.3)","f");
  leg_b->AddEntry(q_eR,"P_{e^{-}e^{+}}(+0.8,-0.3)","f");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  TLegend *leg_b2 = new TLegend(0.5,0.75,0.7,0.9);
  leg_b2->SetTextSize(0.035);
  leg_b2->SetTextFont(42);
  leg_b2->AddEntry(gstat,"Only stat. unc.","pl");
  leg_b2->AddEntry(g_noTPC,"w/o TPC kaon ID","pe");
  leg_b2->SetFillColor(0);
  leg_b2->SetLineColor(0);
  leg_b2->SetShadowColor(0);
  leg_b2->Draw();

  c_R_AFB->Print("plots_"+energy+"_final/Observables_Unc.eps");

  
}

void Plots_R_AFB_comparison() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);

  TH1F * q_eL = new TH1F("q_eL","q_eL",12,-0.5,11.5);
  TH1F * q_eR = new TH1F("q_eR","q_eR",12,-0.5,11.5);
  TH1F * q_eR_2 = new TH1F("q_eR_2","q_eR_2",12,-0.5,11.5);


  TH1F * c_eL = new TH1F("c_eL","c_eL",11,-0.03,10.97);
  TH1F * c_eR = new TH1F("c_eR","c_eR",11,0.,11.);
  TH1F * b_eL = new TH1F("b_eL","b_eL",11,-0.03,10.97);
  TH1F * b_eR = new TH1F("b_eR","b_eR",11,0.,11.);

  TH1F * c_eL_noTPC = new TH1F("c_eL_noTPC","c_eL_noTPC",11,-0.03,10.97);
  TH1F * c_eR_noTPC = new TH1F("c_eR_noTPC","c_eR_noTPC",11,0.,11.);
  TH1F * b_eL_noTPC = new TH1F("b_eL_noTPC","b_eL_noTPC",11,-0.03,10.97);
  TH1F * b_eR_noTPC = new TH1F("b_eR_noTPC","b_eR_noTPC",11,0.,11.);

  TH1F * c_eL_dNdx = new TH1F("c_eL_dNdx","c_eL_dNdx",11,-0.03,10.97);
  TH1F * c_eR_dNdx = new TH1F("c_eR_dNdx","c_eR_dNdx",11,0.,11.);
  TH1F * b_eL_dNdx = new TH1F("b_eL_dNdx","b_eL_dNdx",11,-0.03,10.97);
  TH1F * b_eR_dNdx = new TH1F("b_eR_dNdx","b_eR_dNdx",11,0.,11.);

  double y[8]={r_stat[0],r_stat[1],afb_stat[0],afb_stat[1],r_stat[2],r_stat[3],afb_stat[2],afb_stat[3]};
  double x[8]={0.5,1.5,3.5,4.5,6.5,7.5,9.5,10.5};

  double ey[8]={0,0,0,0,0,0,0,0};
  double ex[8]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  TGraphErrors * gstat = new TGraphErrors(8,x,y,ex,ey);

  double y2[4]={sqrt(pow(afb_stat[0]/sqrt(0.25),2)+pow(afb_syst[0],2)),sqrt(pow(afb_stat[1]/sqrt(0.25),2)+pow(afb_syst[1],2)),sqrt(pow(afb_stat[2]/sqrt(0.54),2)+pow(afb_syst[2],2)),sqrt(pow(afb_stat[3]/sqrt(0.54),2)+pow(afb_syst[2],2))};
  double x2[4]={3.5,4.5,9.5,10.5};

  double ex2[4]={0,0,0,0};
  double ey2[4]={y2[0]-sqrt( pow(afb_stat[0],2)+pow(afb_syst[0],2)),y2[1],y2[2]-sqrt( pow(afb_stat[2],2)+pow(afb_syst[2],2)),y2[3]};//0.5,0.5,0.5,0.5};
  TGraphAsymmErrors * g_noTPC = new TGraphAsymmErrors(4,x2,y2,ex2,ex2,ey2,ex2);


  //ILD baseline
  c_eL->Fill(0.5, sqrt( pow(r_stat_dEdx[0],2)+pow(r_syst[0],2)));
  c_eL->Fill(3.5, sqrt( pow(afb_stat[0],2)+pow(afb_syst[0],2)));

  c_eR->Fill(1.5, sqrt( pow(r_stat_dEdx[1],2)+pow(r_syst[1],2)));
  c_eR->Fill(4.5, sqrt( pow(afb_stat[1],2)+pow(afb_syst[1],2)));

  b_eL->Fill(6.5, sqrt( pow(r_stat_dEdx[2],2)+pow(r_syst[2],2)));
  b_eL->Fill(9.5, sqrt( pow(afb_stat[2],2)+pow(afb_syst[2],2)));

  b_eR->Fill(7.5, sqrt( pow(r_stat_dEdx[3],2)+pow(r_syst[3],2)));
  b_eR->Fill(10.5, sqrt( pow(afb_stat[3],2)+pow(afb_syst[3],2)));

  //ILD dNdx
  c_eL_dNdx->Fill(0.5, sqrt( pow(r_stat_dNdx[0],2)+pow(r_syst[0],2)));
  c_eL_dNdx->Fill(3.5, sqrt( pow(afb_stat_dNdx[0],2)+pow(afb_syst[0],2)));

  c_eR_dNdx->Fill(1.5, sqrt( pow(r_stat_dNdx[1],2)+pow(r_syst[1],2)));
  c_eR_dNdx->Fill(4.5, sqrt( pow(afb_stat_dNdx[1],2)+pow(afb_syst[1],2)));

  b_eL_dNdx->Fill(6.5, sqrt( pow(r_stat_dNdx[2],2)+pow(r_syst[2],2)));
  b_eL_dNdx->Fill(9.5, sqrt( pow(afb_stat_dNdx[2],2)+pow(afb_syst[2],2)));

  b_eR_dNdx->Fill(7.5, sqrt( pow(r_stat_dNdx[3],2)+pow(r_syst[3],2)));
  b_eR_dNdx->Fill(10.5, sqrt( pow(afb_stat_dNdx[3],2)+pow(afb_syst[3],2)));

  //ILD noTPC
  c_eL_noTPC->Fill(0.5, sqrt( pow(r_stat[0],2)+pow(r_syst[0],2)));
  c_eL_noTPC->Fill(3.5, y2[0] );

  c_eR_noTPC->Fill(1.5, sqrt( pow(r_stat[1],2)+pow(r_syst[1],2)));
  c_eR_noTPC->Fill(4.5, y2[1] );

  b_eL_noTPC->Fill(6.5, sqrt( pow(r_stat[2],2)+pow(r_syst[2],2)));
  b_eL_noTPC->Fill(9.5, y2[2] );

  b_eR_noTPC->Fill(7.5, sqrt( pow(r_stat[3],2)+pow(r_syst[3],2)));
  b_eR_noTPC->Fill(10.5, y2[3] );




  q_eL->GetXaxis()->SetBinLabel(2,"R_{c}");
  q_eL->GetXaxis()->SetBinLabel(5,"A_{FB}^{c}");
  q_eL->GetXaxis()->SetBinLabel(8,"R_{b}");
  q_eL->GetXaxis()->SetBinLabel(11,"A_{FB}^{b}");

  TCanvas* c_R_AFB = new TCanvas("c_R_AFB","c_AFB",1400,800);
  c_R_AFB->cd(1);
   gPad->SetLogy();
  // c_eL->GetXaxis()->SetTitle("cos #theta");
  q_eL->GetYaxis()->SetTitle("total relative uncertainty [%]");
  q_eL->GetYaxis()->SetRangeUser(0.09,3);
  q_eL->GetXaxis()->SetRangeUser(0,11);
  q_eL->GetXaxis()->SetTickLength(0);
  //q_eL->SetFillStyle(3001);
  //  q_eL->GetXaxis()->SetNdivisions(512);
  q_eL->GetXaxis()->SetLabelSize(0.1);

  q_eL->SetLineWidth(3);
  q_eL->SetLineStyle(1);
  q_eL->SetFillColor(kBlack);
  q_eL->Draw("");
  q_eR->SetLineWidth(3);
  q_eR->SetLineStyle(1);
  q_eR->SetFillStyle(3002);
  q_eR->SetFillColor(kBlack);
  q_eR_2->SetLineWidth(3);
  q_eR_2->SetLineStyle(1);
  q_eR_2->SetFillStyle(0);
  q_eR_2->SetFillColor(kBlack);
  //  q_eR->SetFillStyle(3003);

  //
  c_eL->SetLineWidth(2);
  c_eL->SetLineStyle(1);
  c_eL->SetFillColor(kGreen+3);
  c_eL->SetLineColor(kGreen+3);
  c_eL->SetFillStyle(3002);

  c_eR->SetLineWidth(2);
  c_eR->SetLineStyle(1);
  c_eR->SetFillColor(kRed-7);
  c_eR->SetLineColor(kRed-7);
  c_eR->SetFillStyle(3002);

  b_eL->SetLineWidth(2);
  b_eL->SetLineStyle(1);
  b_eL->SetFillColor(kGreen+3);
  b_eL->SetLineColor(kGreen+3);
  b_eL->SetFillStyle(3002);

  b_eR->SetLineWidth(2);
  b_eR->SetLineStyle(1);
  b_eR->SetFillColor(kRed-7);
  b_eR->SetLineColor(kRed-7);
  b_eR->SetFillStyle(3002);


  //
  c_eL_dNdx->SetLineWidth(2);
  c_eL_dNdx->SetLineStyle(1);
  c_eL_dNdx->SetFillColor(kGreen+3);
  c_eL_dNdx->SetLineColor(kGreen+3);

  c_eR_dNdx->SetLineWidth(2);
  c_eR_dNdx->SetLineStyle(1);
  c_eR_dNdx->SetFillColor(kRed-7);
  c_eR_dNdx->SetLineColor(kRed-7);

  b_eL_dNdx->SetLineWidth(2);
  b_eL_dNdx->SetLineStyle(1);
  b_eL_dNdx->SetFillColor(kGreen+3);
  b_eL_dNdx->SetLineColor(kGreen+3);

  b_eR_dNdx->SetLineWidth(2);
  b_eR_dNdx->SetLineStyle(1);
  b_eR_dNdx->SetFillColor(kRed-7);
  b_eR_dNdx->SetLineColor(kRed-7);

 //
  c_eL_noTPC->SetLineWidth(2);
  c_eL_noTPC->SetLineStyle(1);
  c_eL_noTPC->SetLineColor(kGreen+3);
  c_eL_noTPC->SetFillStyle(0);

  c_eR_noTPC->SetLineWidth(2);
  c_eR_noTPC->SetLineStyle(1);
  c_eR_noTPC->SetLineColor(kRed-7);
  c_eR_noTPC->SetFillStyle(0);

  b_eL_noTPC->SetLineWidth(2);
  b_eL_noTPC->SetLineStyle(1);
  b_eL_noTPC->SetLineColor(kGreen+3);
  b_eL_noTPC->SetFillStyle(0);

  b_eR_noTPC->SetLineWidth(2);
  b_eR_noTPC->SetLineStyle(1);
  b_eR_noTPC->SetLineColor(kRed-7);
  b_eR_noTPC->SetFillStyle(0);

  c_eL_noTPC->Draw("histosame");
  c_eL->Draw("histosame");
  c_eL_dNdx->Draw("histosame");
  c_eR_noTPC->Draw("histosame");
  c_eR->Draw("histosame");
  c_eR_dNdx->Draw("histosame");
  
  b_eL_noTPC->Draw("histosame");
  b_eL->Draw("histosame");
  b_eL_dNdx->Draw("histosame");
  b_eR_noTPC->Draw("histosame");
  b_eR->Draw("histosame");
  b_eR_dNdx->Draw("histosame");

  q_eR->Draw("histosame");



  
  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  // Labels(-1,-1,900);
  //    QQBARLabel2(0.1,0.05, "e^{-}e^{+} #rightarrow "+quark,color+2);
  QQBARLabel(0.89,0.954,"");
  QQBARLabel2(0.15,0.96, "ILC250 2000 fb^{-1} ",960);
  
  TLegend *leg_b = new TLegend(0.2,0.79,0.4,0.94,"color coding");
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(b_eL_dNdx,"P_{e^{-}e^{+}}(-0.8,+0.3)","f");
  leg_b->AddEntry(b_eR_dNdx,"P_{e^{-}e^{+}}(+0.8,-0.3)","f");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  TLegend *leg_b2 = new TLegend(0.5,0.75,0.7,0.94,"fill coding");
  leg_b2->SetTextSize(0.035);
  leg_b2->SetTextFont(42);
  leg_b2->AddEntry(q_eR_2,"w/o TPC kaon ID","f");
  leg_b2->AddEntry(q_eR,"ILD baseline PID","f");
  leg_b2->AddEntry(q_eL,"ILD with dNdx","f");
  leg_b2->SetFillColor(0);
  leg_b2->SetLineColor(0);
  leg_b2->SetShadowColor(0);
  leg_b2->Draw();

  c_R_AFB->Print("plots_"+energy+"_final/Observables_Unc.eps");

  
}

void R_AFB_results() {

  //Plots_AFB_method();
  Plots_R_AFB_comparison();
  
}
    
