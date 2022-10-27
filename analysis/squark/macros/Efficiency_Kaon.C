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

void EffPlotsKID(TString pol="eL_pR", int tight=0, int purity=0) {

  TString quark_string[6] ={"udscb","d","u","s","c","b"};

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetNumberContours(10);
  TString filename = "../results/s_K_eff_2f_hadronic_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH2F*  h_N_correct[6];
  TH2F*  h_N_wrong[6];
  TH2F*  h_N_true[6];

  for(int q=0; q<6; q++) {
    h_N_correct[q] = (TH2F*)f->Get(TString::Format("h_N_track_K_correct_q%i_sel%i",q,tight));
    h_N_wrong[q] = (TH2F*)f->Get(TString::Format("h_N_track_K_wrong_q%i_sel%i",q,tight));
    h_N_true[q] = (TH2F*)f->Get(TString::Format("h_N_track_K_true_q%i",q));
  
    // efficiency = correct+wrong / total true kaons
    if(purity==0)  {
      h_N_correct[q]->Add(h_N_wrong[q]);
      h_N_correct[q]->Divide(h_N_true[q]);
    } else {
      // purity = wrong / (correct)
      h_N_true[q]->Divide(h_N_true[q]);
      h_N_wrong[q]->Divide(h_N_correct[q]);
      h_N_wrong[q]->Scale(-1);
      h_N_wrong[q]->Add(h_N_true[q]);
    }
    
    }
  
  for(int q=0; q<6; q++) {
    TCanvas* c_eff_MC = new TCanvas(TString::Format("c_eff_%i_%s.png",q,pol.Data()),TString::Format("c_eff_%i_%s.png",q,pol.Data()),800,800);
    c_eff_MC->cd(1);
    c_eff_MC->SetGrid();
    if(purity==0) {
      h_N_correct[q]->SetTitle("Eff: correct&wrongID/TrueKaonTracks - flav:"+quark_string[q]);
      h_N_correct[q]->GetXaxis()->SetTitle("cos #theta_{track}");
      h_N_correct[q]->GetYaxis()->SetTitle("|p_{track}|");
      h_N_correct[q]->GetYaxis()->SetTitleOffset(1.25);
      h_N_correct[q]->GetXaxis()->SetTitleOffset(1.);
      h_N_correct[q]->GetXaxis()->SetRangeUser(-1,1);
      h_N_correct[q]->GetYaxis()->SetRangeUser(0,100);
      h_N_correct[q]->GetZaxis()->SetRangeUser(0,1.);
      h_N_correct[q]->Draw("colzcont");
    }
    if(purity==1) {
      h_N_wrong[q]->SetTitle("Purity: 1-wrongID/correctID - flav:"+quark_string[q]);
      h_N_wrong[q]->GetXaxis()->SetTitle("cos #theta_{track}");
      h_N_wrong[q]->GetYaxis()->SetTitle("|p_{track}|");
      h_N_wrong[q]->GetYaxis()->SetTitleOffset(1.25);
      h_N_wrong[q]->GetXaxis()->SetTitleOffset(1.);
      h_N_wrong[q]->GetXaxis()->SetRangeUser(-1,1);
      h_N_wrong[q]->GetYaxis()->SetRangeUser(0,100);
      h_N_wrong[q]->GetZaxis()->SetRangeUser(0,1.);
      h_N_wrong[q]->Draw("colz,cont0");
    }
  
    if(purity==0) c_eff_MC->Print(TString::Format("./rootfiles/c_K_eff_q%i_tight%i_%s.root",q,tight,pol.Data()));
    else c_eff_MC->Print(TString::Format("./rootfiles/c_K_purity_q%i_tight%i_%s.root",q,tight,pol.Data()));
  }
}

void EffPlotsTracking(TString pol="eL_pR") {

  TString quark_string[6] ={"udscb","d","u","s","c","b"};

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetNumberContours(10);

  TString filename = "../results/s_K_eff_2f_hadronic_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH2F*  h_N_true[6];
  TH2F*  h_N_MC[6];


  for(int q=0; q<6; q++) {
    h_N_true[q] = (TH2F*)f->Get(TString::Format("h_N_track_K_true_q%i",q));
    h_N_MC[q] = (TH2F*)f->Get(TString::Format("h_N_K_MC_q%i",q));

    // efficiency = (recp/ particle level
    h_N_true[q]->Divide(h_N_MC[q]);
        
    }
  
  for(int q=0; q<6; q++) {
    TCanvas* c_eff_MC = new TCanvas(TString::Format("c_eff_%i_%s.png",q,pol.Data()),TString::Format("c_eff_%i_%s.png",q,pol.Data()),800,800);
    c_eff_MC->cd(1);
    c_eff_MC->SetGrid();
    h_N_true[q]->SetTitle("Eff: KaonTracks (cheatID) / Kaons(HadronLevel) - flav:"+quark_string[q]);
    h_N_true[q]->GetXaxis()->SetTitle("cos #theta_{track}");
    h_N_true[q]->GetYaxis()->SetTitle("|p_{track}|");
    h_N_true[q]->GetYaxis()->SetTitleOffset(1.25);
    h_N_true[q]->GetXaxis()->SetTitleOffset(1.);
    h_N_true[q]->GetXaxis()->SetRangeUser(-1,1);
    h_N_true[q]->GetYaxis()->SetRangeUser(0,100);
    h_N_true[q]->GetZaxis()->SetRangeUser(0,3.);
    h_N_true[q]->Draw("colzcont");
    
    c_eff_MC->Print(TString::Format("rootfiles/c_K_track_eff_q%i%s.root",q,pol.Data()));
  }
}

void PlotsTracks(TString pol="eL_pR") {

  TString quark_string[6] ={"udscb","d","u","s","c","b"};

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.0);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadRightMargin(0.13);
  gStyle->SetNumberContours(10);
  TGaxis::SetMaxDigits(3);

  TString filename = "../results/s_K_eff_2f_hadronic_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH2F*  h_N_true[6];
  TH2F*  h_N_MC[6];


  for(int q=0; q<6; q++) {
    h_N_true[q] = (TH2F*)f->Get(TString::Format("h_N_track_K_true_q%i",q));
    h_N_MC[q] = (TH2F*)f->Get(TString::Format("h_N_K_MC_q%i",q));
  
    }
  
  for(int q=0; q<6; q++) {
    TCanvas* c_eff_MC = new TCanvas(TString::Format("c_eff_%i_%s.png",q,pol.Data()),TString::Format("c_eff_%i_%s.png",q,pol.Data()),800,800);
    c_eff_MC->cd(1);
    c_eff_MC->SetGrid();
    h_N_true[q]->SetTitle("N-tracks that are kaons (cheat) - flav:"+quark_string[q]);
    h_N_true[q]->GetXaxis()->SetTitle("cos #theta_{track}");
    h_N_true[q]->GetYaxis()->SetTitle("|p_{track}|");
    h_N_true[q]->GetYaxis()->SetTitleOffset(1.25);
    h_N_true[q]->GetXaxis()->SetTitleOffset(1.);
    h_N_true[q]->GetXaxis()->SetRangeUser(-1,1);
    h_N_true[q]->GetYaxis()->SetRangeUser(0,100);
    //h_N_true[q]->GetZaxis()->SetRangeUser(0,3.);
    h_N_true[q]->Draw("colzcont");
    
    c_eff_MC->Print(TString::Format("rootfiles/c_K_Ntrack_q%i%s.root",q,pol.Data()));
  }
}

void Efficiency_Kaon() {

  EffPlotsKID("eL_pR", 0, 1);
  EffPlotsKID("eL_pR", 0, 0);
  EffPlotsKID("eL_pR", 1, 1);
  EffPlotsKID("eL_pR", 1, 0);
  PlotsTracks("eL_pR");
  EffPlotsTracking("eL_pR");

}
