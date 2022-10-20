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
#include "../../common/cross_sections.h"

void Labels(TString pol, float luminosity=0){
  // QQBARLabel(0.86,0.952,"Work in Progress");
  QQBARLabel(0.86,0.954,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
	if(pol=="eL")
	  QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
	if(pol=="eR")
    QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  QQBARLabel2(0.6,0.2, TString::Format("Luminosity=%i fb^{-1}",int(luminosity)),kBlack);
}


void ContaminationPlots(int isel=6, TString pol="eL_pR") {

  TString quark_string[7] ={"","d","u","s","c","b","radret"};

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  for(int ikaon=0; ikaon<3; ikaon++) {

    float luminosity=0;
    TString KID="loose";
    if(ikaon==1)KID="tight";
    if(ikaon==2)KID="doubletight";
    TString filename = "../results/s_AFB_"+KID+"_2f_hadronic_"+pol+"_250GeV.root";
    TFile *f = new TFile(filename);
    cout<<filename<<endl;

    TH1F * h_Ntotal_nocuts = (TH1F*)f->Get("h_Ntotal_nocuts");
    luminosity=h_Ntotal_nocuts->GetEntries()/cross_section[0][4];
    if(pol=="eR_pL") luminosity=h_Ntotal_nocuts->GetEntries()/cross_section[1][4];

    TH1F*  h_AFB_reco[7];
    TH1F*  h_AFB_true[7];
    for(int q=1; q<6; q++) {
      h_AFB_true[q] = (TH1F*)f->Get(TString::Format("h_AFB_true_q%i_sel%i",q,isel));
      h_AFB_reco[q] = (TH1F*)f->Get(TString::Format("h_AFB_reco_q%i_sel%i",q,isel));
      h_AFB_true[q]->Sumw2();
      h_AFB_reco[q]->Sumw2();      
    }
    filename = "../results/s_AFB_"+KID+"_2f_hadronic_"+pol+"_250GeV_radret.root";
    f = new TFile(filename);
    for(int q=1; q<6; q++) {
      if(q==1) {
        h_AFB_true[6] = (TH1F*)f->Get(TString::Format("h_AFB_true_q%i_sel%i",q,isel));
        h_AFB_reco[6] = (TH1F*)f->Get(TString::Format("h_AFB_reco_q%i_sel%i",q,isel));
      } else {
        TH1F* temp1 = (TH1F*)f->Get(TString::Format("h_AFB_true_q%i_sel%i",q,isel));
        TH1F* temp2 = (TH1F*)f->Get(TString::Format("h_AFB_reco_q%i_sel%i",q,isel));  
        h_AFB_true[6]->Add(temp1);
        h_AFB_reco[6]->Add(temp2);
      }
      h_AFB_true[6]->Sumw2();
      h_AFB_reco[6]->Sumw2();      
    }
//---------------
    THStack *bkg_true = new THStack("bkg_true","");
    for(int i=1; i<7; i++) {
      if(i!=3) bkg_true->Add(h_AFB_true[i]);
      h_AFB_true[i]->SetLineColor(i);
      h_AFB_true[i]->SetLineWidth(2);
      h_AFB_true[i]->SetFillColor(i);
      h_AFB_true[i]->SetFillStyle(3001+i);
    }
    h_AFB_true[3]->SetLineColor(1);
    h_AFB_true[3]->SetMarkerColor(1);
    h_AFB_true[3]->SetLineWidth(2);
    bkg_true->Add(h_AFB_true[3]);
  
    TCanvas* c_eff_MC_true = new TCanvas("c_eff_MC_true"+KID,"c_eff_MC_true"+KID,800,800);
    c_eff_MC_true->cd(1);
    c_eff_MC_true->SetGrid();
    bkg_true->Draw("histo");
    bkg_true->GetXaxis()->SetTitle("cos #theta_{j_{1}j_{2}}");
    bkg_true->GetYaxis()->SetTitle("Selection Eff [%]");
    bkg_true->GetYaxis()->SetTitleOffset(1.25);
    bkg_true->GetXaxis()->SetTitleOffset(1.);
    //h_AFB_true[3]->GetYaxis()->SetRangeUser(0,12);
    bkg_true->GetXaxis()->SetRangeUser(-1,1);
    c_eff_MC_true->Update();

    Labels(pol,luminosity);

    TLegend *leg_true = new TLegend(0.2,0.7,0.4,0.9);//(0.4,0.3,0.5,0.6);
    if(isel==8) leg_true->SetHeader("reco-level, cheat on K-ID, "+KID);
    leg_true->SetTextSize(0.035);
    for(int q=1; q<7; q++) leg_true->AddEntry(h_AFB_true[q],TString::Format("%s, %s",quark_string[q].Data(),pol.Data()),"fl");
    leg_true->SetFillStyle(0);
    leg_true->SetLineWidth(0);
    leg_true->SetLineColor(0);
    leg_true->SetBorderSize(0);
    leg_true->Draw();

    c_eff_MC_true->Print(TString::Format("c_cont_true_MC_sel%i_%s_%s.pdf",isel,KID.Data(),pol.Data()));
//--------------------------------
    THStack *bkg_reco = new THStack("bkg_reco","");
    for(int i=1; i<7; i++) {
      if(i!=3) bkg_reco->Add(h_AFB_reco[i]);
      h_AFB_reco[i]->SetLineColor(i);
      h_AFB_reco[i]->SetLineWidth(2);
      h_AFB_reco[i]->SetFillColor(i);
      h_AFB_reco[i]->SetFillStyle(3001+i);
    }
    h_AFB_reco[3]->SetLineColor(1);
    h_AFB_reco[3]->SetMarkerColor(1);
    h_AFB_reco[3]->SetLineWidth(2);
    bkg_reco->Add(h_AFB_reco[3]);
  
    TCanvas* c_eff_MC_reco = new TCanvas("c_eff_MC_reco"+KID,"c_eff_MC_reco"+KID,800,800);
    c_eff_MC_reco->cd(1);
    c_eff_MC_reco->SetGrid();
    bkg_reco->Draw("histo");
    bkg_reco->GetXaxis()->SetTitle("cos #theta_{j_{1}j_{2}}");
    bkg_reco->GetYaxis()->SetTitle("Selection Eff [%]");
    bkg_reco->GetYaxis()->SetTitleOffset(1.25);
    bkg_reco->GetXaxis()->SetTitleOffset(1.);
    //h_AFB_true[3]->GetYaxis()->SetRangeUser(0,12);
    bkg_reco->GetXaxis()->SetRangeUser(-1,1);
    c_eff_MC_reco->Update();

    Labels(pol,luminosity);

    TLegend *leg_reco = new TLegend(0.2,0.7,0.4,0.9);//(0.4,0.3,0.5,0.6);
    if(isel==8) leg_reco->SetHeader("reco-level, cheat on K-ID, "+KID);
    leg_reco->SetTextSize(0.035);
    for(int q=1; q<7; q++) leg_reco->AddEntry(h_AFB_reco[q],TString::Format("%s, %s",quark_string[q].Data(),pol.Data()),"fl");
    leg_reco->SetFillStyle(0);
    leg_reco->SetLineWidth(0);
    leg_reco->SetLineColor(0);
    leg_reco->SetBorderSize(0);
    leg_reco->Draw();


  //c_eff_MC->Print(TString::Format("summaryplots/UnEff_sample_%i_pdg_%i_twopols.pdf",sample,iquark));
    c_eff_MC_reco->Print(TString::Format("c_cont_reco_MC_sel%i_%s_%s.pdf",isel,KID.Data(),pol.Data()));

  }
}



void Contamination() {

  for(int isel=8; isel<10; isel++) {
    ContaminationPlots(isel,"eL_pR");
    ContaminationPlots(isel,"eR_pL");
  }

}
