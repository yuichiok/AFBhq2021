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
#include "utils.h"



TString energy="dNdx_500GeV_2023";


void PurityChargePlots(int quark=5) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString filename = TString::Format("../weights_"+energy+"/eff_weights_pdg%i_pol2.root",quark);
  TFile *f = new TFile(filename);
  TH1F*  eff_q = (TH1F*)f->Get("eff_tagging");

  filename = TString::Format("../weights_"+energy+"/eff_weights_pdg%i_pol3.root",quark);
  TFile *ff = new TFile(filename);
  TH1F*  eff_q2 = (TH1F*)ff->Get("eff_tagging");
    
     //**********************
  TString filename3 = TString::Format("../weights_"+energy+"/pq_pdg%i_pol3.root",quark);
  TFile *f3 = new TFile(filename3);
  TH1F*  purity_vtx_2 = (TH1F*)f3->Get("purity_Vtx");
  TH1F*  purity_kc_2 = (TH1F*)f3->Get("purity_Kc");

  //**********************
  TString filename2 = TString::Format("../weights_"+energy+"/pq_pdg%i_pol2.root",quark);
  TFile *f2 = new TFile(filename2);
  TH1F*  purity_vtx = (TH1F*)f2->Get("purity_Vtx");
  TH1F*  purity_kc = (TH1F*)f2->Get("purity_Kc");
  
  purity_vtx->Scale(100);
  purity_kc->Scale(100);
  purity_vtx_2->Scale(100);
  purity_kc_2->Scale(100);
  
  TCanvas* c_purity_b = new TCanvas(TString::Format("c_purity_%i",quark),TString::Format("c_purity_%i",quark),800,800);
  c_purity_b->cd(1);
  //gPad->SetLogy();
  purity_vtx->GetXaxis()->SetTitle("cos #theta");
  purity_vtx->GetYaxis()->SetTitle("P_{chg.} [%]");
  purity_vtx->GetYaxis()->SetTitleOffset(1.25);
  purity_vtx->GetXaxis()->SetTitleOffset(1.);
  purity_vtx->GetYaxis()->SetRangeUser(0,100.);
  purity_vtx->GetXaxis()->SetRangeUser(0,1);

  purity_vtx->SetLineColor(4);
  purity_vtx->SetLineWidth(4);
  purity_vtx->SetLineStyle(1);
  purity_vtx->Draw("histo");

  purity_kc->SetLineColor(2);
  purity_kc->SetLineWidth(2);
  purity_kc->SetLineStyle(1);
  purity_kc->Draw("histosame");

  purity_vtx_2->SetLineColor(4);
  purity_vtx_2->SetLineWidth(4);
  purity_vtx_2->SetLineStyle(2);
  purity_vtx_2->Draw("histoesame");

  purity_kc_2->SetLineColor(2);
  purity_kc_2->SetLineWidth(2);
  purity_kc_2->SetLineStyle(2);
  purity_kc_2->Draw("histosame");

  eff_q->SetLineColor(1);
  eff_q->SetLineWidth(2);
  eff_q->SetLineStyle(1);
  
  eff_q2->SetLineColor(1);
  eff_q2->SetLineWidth(2);
  eff_q2->SetLineStyle(2);

 
  Labels(-1,quark,-1);

  TString header = "e^{-}e^{+}#rightarrow b#bar{b}";
  if(quark==4) header = "e^{-}e^{+}#rightarrow c#bar{c}";
  TLegend *leg_purity = new TLegend(0.2,0.35,0.8,0.55,header);
  leg_purity->SetTextSize(0.035);
  leg_purity->SetTextFont(42);
  leg_purity->AddEntry(purity_vtx,"Vtx-method","l");
  leg_purity->AddEntry(purity_kc,"K-method","l");
  leg_purity->AddEntry(eff_q,"P_{e^{-}e^{+}}=(-0.8,+0.3)","l");
  leg_purity->AddEntry(eff_q2,"P_{e^{-}e^{+}}=(+0.8,-0.3)","l");
  leg_purity->SetFillColor(0);
  leg_purity->SetLineColor(0);
  leg_purity->SetShadowColor(0);
  leg_purity->Draw();

  QQBARLabel2(0.15,0.954, "ILC500",960,0.05);

  c_purity_b->Print(TString::Format("plots_"+energy+"_AFB/purity_pdg_%i.eps",quark));


}
void PurityCharge() {

  PurityChargePlots(4);
  PurityChargePlots(5);

}
