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

TString energy="500GeV";
TString pid="dEdx";


void EffCat(int quark=5, int syst=0) {


  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  //*************
  int pol=0;
  folder="../results_"+energy+"_"+pid+"/AFBreco_";

  TString filename = TString::Format("../weights_"+pid+"_"+energy+"_2023/eff_weights_pdg%i_pol%i.root",quark,pol);
  TFile *f = new TFile(filename);
  TH1F*  eff_q = (TH1F*)f->Get("eff_pres");
  TH1F * eff40_q = new TH1F("eff40_q","eff40_q",40,-1,1);
  for(int i=20; i<40; i++){
    eff40_q->SetBinContent(i+1-20,eff_q->GetBinContent(40-20-i+1));
    eff40_q->SetBinError(i+1-20,eff_q->GetBinError(40-20-i+1));
    eff40_q->SetBinContent(i+1,eff_q->GetBinContent(i+1-20));
    eff40_q->SetBinError(i+1,eff_q->GetBinError(i+1-20));
  }
  
  TH1F *AFB = GetHisto2(1,"h_AFB",pol,quark,900,1,0);

  TH1F *chargecheatreco_0 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat0_syst%i",syst),pol,quark,900,1,0);
  TH1F *chargecheatreco_1 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat1_syst%i",syst),pol,quark,900,1,0);
  TH1F *chargecheatreco_2 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat2_syst%i",syst),pol,quark,900,1,0);

  TH1F *chargecheatreco_3 = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat2_syst%i",syst),pol,quark,900,1,0);
  
  chargecheatreco_3->Add(chargecheatreco_0);
  chargecheatreco_3->Add(chargecheatreco_1);
  chargecheatreco_3->Divide(AFB);
  chargecheatreco_3->Divide(eff40_q);
  chargecheatreco_3->Scale(100.);
  
  chargecheatreco_0->Divide(AFB);
  chargecheatreco_0->Divide(eff40_q);
  chargecheatreco_0->Scale(100.);

  chargecheatreco_1->Divide(AFB);
  chargecheatreco_1->Divide(eff40_q);
  chargecheatreco_1->Scale(100.);

  chargecheatreco_2->Divide(AFB);
  chargecheatreco_2->Divide(eff40_q);
  chargecheatreco_2->Scale(100.);




  //***********
  pol=1;
  //folder="../results_"+energy+"/AFBreco_";

  filename = TString::Format("../weights_"+pid+"_"+energy+"_2023/eff_weights_pdg%i_pol%i.root",quark,pol);
  f = new TFile(filename);
  TH1F*  eff_q_eR = (TH1F*)f->Get("eff_pres");
  TH1F * eff40_q_eR = new TH1F("eff40_q_eR","eff40_q_eR",40,-1,1);
  for(int i=20; i<40; i++){
    eff40_q_eR->SetBinContent(i+1-20,eff_q_eR->GetBinContent(40-20-i+1));
    eff40_q_eR->SetBinError(i+1-20,eff_q_eR->GetBinError(40-20-i+1));
    eff40_q_eR->SetBinContent(i+1,eff_q_eR->GetBinContent(i+1-20));
    eff40_q_eR->SetBinError(i+1,eff_q_eR->GetBinError(i+1-20));
  }

  TH1F *AFB_eR = GetHisto2(1,"h_AFB",pol,quark,900,1,0);

  TH1F *chargecheatreco_0_eR = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat0_syst%i",syst),pol,quark,900,1,0);
  TH1F *chargecheatreco_1_eR = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat1_syst%i",syst),pol,quark,900,1,0);
  TH1F *chargecheatreco_2_eR = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat2_syst%i",syst),pol,quark,900,1,0);

  TH1F *chargecheatreco_3_eR = GetHisto2(1,TString::Format("h_AFBreco_chargecheatreco_cat2_syst%i",syst),pol,quark,900,1,0);
  
  chargecheatreco_3_eR->Add(chargecheatreco_0_eR);
  chargecheatreco_3_eR->Add(chargecheatreco_1_eR);
  chargecheatreco_3_eR->Divide(AFB_eR);
  chargecheatreco_3_eR->Divide(eff40_q_eR);
  chargecheatreco_3_eR->Scale(100.);

  
  chargecheatreco_0_eR->Divide(AFB_eR);
  chargecheatreco_0_eR->Divide(eff40_q_eR);
  chargecheatreco_0_eR->Scale(100.);

  chargecheatreco_1_eR->Divide(AFB_eR);
  chargecheatreco_1_eR->Divide(eff40_q_eR);
  chargecheatreco_1_eR->Scale(100.);

  chargecheatreco_2_eR->Divide(AFB_eR);
  chargecheatreco_2_eR->Divide(eff40_q_eR);
  chargecheatreco_2_eR->Scale(100.);


    TCanvas* c_f1_MC = new TCanvas(TString::Format("c_f1_MC_%i_%i",quark,pol),TString::Format("c_f1_MC_%i",quark),800,800);
  c_f1_MC->cd(1);

  chargecheatreco_0->GetXaxis()->SetTitle("|cos #theta|");
  chargecheatreco_0->GetYaxis()->SetTitle("Eff [%]");
  chargecheatreco_0->GetXaxis()->SetRangeUser(0,1);
  chargecheatreco_0->GetYaxis()->SetRangeUser(0,40);
  if(quark==4) chargecheatreco_0->GetYaxis()->SetRangeUser(0,10);
  chargecheatreco_0->SetLineColor(kBlue+1);
  chargecheatreco_0->SetLineWidth(3);
  chargecheatreco_0->SetLineStyle(1);
  chargecheatreco_0->SetMarkerColor(kBlue+1);
  chargecheatreco_0->Draw("histoe");

  chargecheatreco_1->SetLineColor(kGreen+2);
  chargecheatreco_1->SetLineWidth(2);
  chargecheatreco_1->SetLineStyle(1);
  chargecheatreco_1->SetMarkerColor(kGreen+2);
  chargecheatreco_1->Draw("histoesame");

  chargecheatreco_2->SetLineColor(kRed+1);
  chargecheatreco_2->SetLineWidth(1);
  chargecheatreco_2->SetLineStyle(1);
  chargecheatreco_2->SetMarkerColor(kRed+1);
  chargecheatreco_2->Draw("histoesame");

  chargecheatreco_3->SetLineColor(kGray+1);
  chargecheatreco_3->SetLineWidth(1);
  chargecheatreco_3->SetLineStyle(1);
  chargecheatreco_3->SetMarkerSize(1.6);
  chargecheatreco_3->SetMarkerStyle(3);
  chargecheatreco_3->SetMarkerColor(kGray+1);
  chargecheatreco_3->Draw("histopesame");
  
  chargecheatreco_0_eR->SetMarkerColor(kBlue+1);
  chargecheatreco_0_eR->SetFillColor(kBlue+1);
  chargecheatreco_0_eR->SetFillStyle(3003);
  chargecheatreco_0_eR->Draw("e2same");
  
  chargecheatreco_1_eR->SetMarkerColor(kGreen+2);
  chargecheatreco_1_eR->SetFillColor(kGreen+2);
  chargecheatreco_1_eR->SetFillStyle(3003);
  chargecheatreco_1_eR->Draw("e2same");
    
  chargecheatreco_2_eR->SetMarkerColor(kRed+1);
  chargecheatreco_2_eR->SetFillColor(kRed+1);
  chargecheatreco_2_eR->SetFillStyle(3003);
  chargecheatreco_2_eR->Draw("e2same");
  
  chargecheatreco_3_eR->SetMarkerColor(kGray+1);
  chargecheatreco_3_eR->SetFillColor(kGray+1);
  chargecheatreco_3_eR->SetFillStyle(3003);
  chargecheatreco_3_eR->Draw("e2same");
  
  eff_q->SetLineColor(kBlack);
  eff_q->SetLineWidth(2);
  eff_q->SetLineStyle(1);
  eff_q->SetMarkerColor(kBlack);
 
  eff_q_eR->SetMarkerColor(kBlack);
  eff_q_eR->SetFillColor(kBlack);
  eff_q_eR->SetFillStyle(3003);
  eff_q_eR->SetLineWidth(0);
  Labels(-1,quark,-1);

  TLegend *leg = new TLegend(0.18,0.70,0.4,0.85,"","blNDC");
  leg->SetTextFont(42);
  leg->SetTextSize(0.03);
  leg->AddEntry(chargecheatreco_0,"#varepsilon_{Cat.1}","pl");
  leg->AddEntry(chargecheatreco_1,"#varepsilon_{Cat.2}","pl");
  leg->AddEntry(chargecheatreco_2,"#varepsilon_{Cat.3}","pl");
  leg->AddEntry(chargecheatreco_3,"#varepsilon_{Cat.1,2,3}","pl");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

  TLegend *leg2 = new TLegend(0.42,0.70,0.7,0.85,"","blNDC");
  leg2->SetTextFont(42);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(eff_q,"P_{e^{-}e^{+}}=(-0.8,+0.3)","pl");
  leg2->AddEntry(eff_q_eR,"P_{e^{-}e^{+}}=(+0.8,-0.3)","pf");
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();

  c_f1_MC->Print(TString::Format("plots_"+energy+"_AFB/EffCat_pdg_%i.eps",quark));
    
    
}

void AFBEffCat() {

  EffCat(4,0);
  EffCat(5,0);

}
