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

TString energy="250GeV";


void Labels(int quark){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(quark==4)
    QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c}",kGray+2);
  if(quark==5)
    QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow b#bar{b}",kGray+2);
  
  //QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);

}


void EffCharge(int quark=5) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
    //**********************
  TString filename2 = TString::Format("../weights_"+energy+"/pq_pdg%i_pol2.root",quark);
  TFile *f2 = new TFile(filename2);
  TH1F*  purity_vtx = (TH1F*)f2->Get("purity_Vtx");
  TH1F*  purity_kc = (TH1F*)f2->Get("purity_Kc");
  
  TString filename = TString::Format("../weights_"+energy+"/eff_weights_pdg%i_pol2.root",quark);
  TFile *f = new TFile(filename);
  TH1F*  eff_q = (TH1F*)f->Get("eff_tagging");

  filename = TString::Format("../weights_"+energy+"/eff_weights_pdg%i_pol3.root",quark);
  TFile *ff = new TFile(filename);
  TH1F*  eff_q2 = (TH1F*)ff->Get("eff_tagging");

  TString filename1 = TString::Format("../weights_"+energy+"/chargeeff_weights_pdg%i_pol2.root",quark);
  TFile *f1 = new TFile(filename1);
  TH1F*  eff_vtx = (TH1F*)f1->Get("eff_charge_Vtx");
  eff_vtx->Multiply(eff_q);
  // eff_vtx->Multiply(purity_vtx);

  TH1F*  eff_kc = (TH1F*)f1->Get("eff_charge_Kc");
  eff_kc->Multiply(eff_q);
  //eff_kc->Multiply(purity_kc);

  /*eff_kc->Add(eff_vtx);
    eff_kc->Multiply(eff_q);*/
  eff_vtx->Scale(100);
  eff_kc->Scale(100);

  filename1 = TString::Format("../weights_"+energy+"/chargeeff_weights_pdg%i_pol3.root",quark);
  TFile *ff1 = new TFile(filename1);
  TH1F*  eff_vtx2 = (TH1F*)ff1->Get("eff_charge_Vtx");
  eff_vtx2->Multiply(eff_q2);
  TH1F*  eff_kc2 = (TH1F*)ff1->Get("eff_charge_Kc");
  eff_kc2->Multiply(eff_q2);
  eff_vtx2->Scale(100);
  eff_kc2->Scale(100);
  
  TCanvas* c_eff_b = new TCanvas(TString::Format("c_eff_%i",quark),TString::Format("c_eff_%i",quark),800,800);
  c_eff_b->cd(1);
  //gPad->SetLogy();
  eff_vtx->GetXaxis()->SetTitle("cos #theta");
  eff_vtx->GetYaxis()->SetTitle("Eff [%]");
  eff_vtx->GetYaxis()->SetTitleOffset(1.25);
  eff_vtx->GetXaxis()->SetTitleOffset(1.);
  eff_vtx->GetYaxis()->SetRangeUser(0,50);
  eff_vtx->GetXaxis()->SetRangeUser(0,1);

  eff_vtx->SetLineColor(4);
  eff_vtx->SetMarkerColor(4);
  eff_vtx->SetLineWidth(2);
  eff_vtx->SetLineStyle(1);
  eff_vtx->Draw("histoe");

  eff_kc->SetLineColor(2);
  eff_kc->SetMarkerColor(2);
  eff_kc->SetLineWidth(2);
  eff_kc->SetLineStyle(1);
  eff_kc->Draw("histoesame");

  eff_vtx2->SetLineColor(4);
  eff_vtx2->SetMarkerColor(4);
  eff_vtx2->SetLineWidth(2);
  eff_vtx2->SetLineStyle(2);
  eff_vtx2->Draw("histoesame");

  eff_kc2->SetLineColor(2);
  eff_kc2->SetMarkerColor(2);
  eff_kc2->SetLineWidth(2);
  eff_kc2->SetLineStyle(2);
  eff_kc2->Draw("histoesame");

  eff_q->SetLineColor(1);
  eff_q->SetLineWidth(2);
  eff_q->SetLineStyle(1);
  
  eff_q2->SetLineColor(1);
    eff_q2->SetLineWidth(2);
  eff_q2->SetLineStyle(2);

  Labels(quark);
  
  TLegend *leg_b = new TLegend(0.2,0.55,0.8,0.75);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(eff_vtx,"Vtx-method","le");
  leg_b->AddEntry(eff_kc,"K-method","le");
  leg_b->AddEntry(eff_q,"P_{e^{-}e^{+}}=(-0.8,+0.3)","l");
  leg_b->AddEntry(eff_q2,"P_{e^{-}e^{+}}=(+0.8,-0.3)","l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();


  
  purity_vtx->Scale(100);
  purity_kc->Scale(100);

  TCanvas* c_purity_b = new TCanvas(TString::Format("c_purity_%i",quark),TString::Format("c_purity_%i",quark),800,800);
  c_purity_b->cd(1);
  //gPad->SetLogy();
  purity_vtx->GetXaxis()->SetTitle("cos #theta");
  purity_vtx->GetYaxis()->SetTitle("Purity [%]");
  purity_vtx->GetYaxis()->SetTitleOffset(1.25);
  purity_vtx->GetXaxis()->SetTitleOffset(1.);
  purity_vtx->GetYaxis()->SetRangeUser(0,100.);
  purity_vtx->GetXaxis()->SetRangeUser(0,1);

  purity_vtx->SetLineColor(4);
  purity_vtx->SetLineWidth(2);
  purity_vtx->SetLineStyle(1);
  purity_vtx->Draw("histo");

  purity_kc->SetLineColor(2);
  purity_kc->SetLineWidth(2);
  purity_kc->SetLineStyle(1);
  purity_kc->Draw("histosame");

 
  Labels(quark);
  
  TLegend *leg_purity = new TLegend(0.2,0.65,0.8,0.75);
  leg_purity->SetTextSize(0.035);
  leg_purity->SetTextFont(42);
  leg_purity->AddEntry(purity_vtx,"Vtx-method","l");
  leg_purity->AddEntry(purity_kc,"K-method","l");
  leg_purity->SetFillColor(0);
  leg_purity->SetLineColor(0);
  leg_purity->SetShadowColor(0);
  leg_purity->Draw();

}

