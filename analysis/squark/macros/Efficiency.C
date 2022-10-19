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

void Labels(TString pol){
  // QQBARLabel(0.86,0.952,"Work in Progress");
  QQBARLabel(0.86,0.954,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
	if(pol=="eL")
	  QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
	if(pol=="eR")
    QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
}

void EffPlotsPresel(int isel=6, TString pol="eL_pR") {

  TString quark_string[6] ={"","d","u","s","c","b"};

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);

  TString filename = "../results/s_AFB_loose_2f_hadronic_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH1F*  h_N_isel[6];
  TH1F*  h_N0[6];
  for(int q=1; q<6; q++) {
    h_N0[q] = (TH1F*)f->Get(TString::Format("h_N_q%i_sel%i",q,0));
    h_N_isel[q] = (TH1F*)f->Get(TString::Format("h_N_q%i_sel%i",q,isel));
    h_N0[q]->Sumw2();
    h_N_isel[q]->Sumw2();
    h_N_isel[q]->Divide(h_N0[q]);
    h_N_isel[q]->Scale(100.);
  }
  
  TCanvas* c_eff_MC = new TCanvas("c_eff_MC","c_eff_MC",800,800);
  c_eff_MC->cd(1);
  c_eff_MC->SetGrid();
  h_N_isel[1]->GetXaxis()->SetTitle("cos #theta_{j_{1}j_{2}}");
  h_N_isel[1]->GetYaxis()->SetTitle("Selection Eff [%]");
  h_N_isel[1]->GetYaxis()->SetTitleOffset(1.25);
  h_N_isel[1]->GetXaxis()->SetTitleOffset(1.);
  h_N_isel[1]->GetYaxis()->SetRangeUser(0,100);
  h_N_isel[1]->GetXaxis()->SetRangeUser(0,1);
  for(int q=1; q<6; q++) {
    h_N_isel[q]->SetLineColor(q);
    h_N_isel[q]->SetLineWidth(2);
    h_N_isel[q]->Draw("histoesame");
  }

  Labels(pol);

  TLegend *leg2 = new TLegend(0.57,0.76,0.85,0.9);//(0.4,0.3,0.5,0.6);
  leg2->SetTextSize(0.035);
  for(int q=1; q<6; q++) leg2->AddEntry(h_N_isel[q],TString::Format("%s, %s",quark_string[q].Data(),pol.Data()),"l");
  leg2->SetFillStyle(0);
  leg2->SetLineWidth(0);
  leg2->SetLineColor(0);
  leg2->SetBorderSize(0);
  leg2->Draw();


  //c_eff_MC->Print(TString::Format("summaryplots/UnEff_sample_%i_pdg_%i_twopols.pdf",sample,iquark));
}

void EffPlotsKID(int isel=6, TString pol="eL_pR") {

  TString quark_string[6] ={"","d","u","s","c","b"};

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);

  for(int ikaon=0; ikaon<3; ikaon++) {
    TString KID="loose";
    if(ikaon==1)KID="tight";
    if(ikaon==2)KID="doubletight";
    TString filename = "../results/s_AFB_"+KID+"_2f_hadronic_"+pol+"_250GeV.root";
    TFile *f = new TFile(filename);
    cout<<filename<<endl;

    TH1F*  h_N_isel[6];
    TH1F*  h_N0[6];
    for(int q=1; q<6; q++) {
      h_N0[q] = (TH1F*)f->Get(TString::Format("h_N_q%i_sel%i",q,0));
      h_N_isel[q] = (TH1F*)f->Get(TString::Format("h_N_q%i_sel%i",q,isel));
      h_N0[q]->Sumw2();
      h_N_isel[q]->Sumw2();
      h_N_isel[q]->Divide(h_N0[q]);
      h_N_isel[q]->Scale(100.);
    }
  
    TCanvas* c_eff_MC = new TCanvas("c_eff_MC"+KID,"c_eff_MC"+KID,800,800);
    c_eff_MC->cd(1);
    c_eff_MC->SetGrid();
    h_N_isel[1]->GetXaxis()->SetTitle("cos #theta_{j_{1}j_{2}}");
    h_N_isel[1]->GetYaxis()->SetTitle("Selection Eff [%]");
    h_N_isel[1]->GetYaxis()->SetTitleOffset(1.25);
    h_N_isel[1]->GetXaxis()->SetTitleOffset(1.);
    h_N_isel[1]->GetYaxis()->SetRangeUser(0,12);
    h_N_isel[1]->GetXaxis()->SetRangeUser(0,1);
    for(int q=1; q<6; q++) {
      h_N_isel[q]->SetLineColor(q);
      h_N_isel[q]->SetLineWidth(2);
      h_N_isel[q]->Draw("histoesame");
    }

    Labels(pol);

    TLegend *leg2 = new TLegend(0.57,0.76,0.85,0.9,KID);//(0.4,0.3,0.5,0.6);
    leg2->SetTextSize(0.035);
    for(int q=1; q<6; q++) leg2->AddEntry(h_N_isel[q],TString::Format("%s, %s",quark_string[q].Data(),pol.Data()),"l");
    leg2->SetFillStyle(0);
    leg2->SetLineWidth(0);
    leg2->SetLineColor(0);
    leg2->SetBorderSize(0);
    leg2->Draw();


  //c_eff_MC->Print(TString::Format("summaryplots/UnEff_sample_%i_pdg_%i_twopols.pdf",sample,iquark));
  }
}



void Efficiency() {

  int isel=9;
  //EffPlotsPresel(isel);
  EffPlotsKID(isel);

  //
  //MCeffPlotPols(sample,5,900);
  //  MCuneffPlotPols(sample,5,900);

}
