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


void MigrationsPlots(int isel=6, TString pol="eL_pR") {

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

    TH1F*  h_AFB_reco[6];
    TH1F*  h_AFB_true[6];
    for(int q=1; q<6; q++) {
      h_AFB_true[q] = (TH1F*)f->Get(TString::Format("h_AFB_true_q%i_sel%i",q,isel));
      h_AFB_reco[q] = (TH1F*)f->Get(TString::Format("h_AFB_reco_q%i_sel%i",q,isel));
      h_AFB_true[q]->Sumw2();
      h_AFB_reco[q]->Sumw2();      
    }
  
    TCanvas* c_eff_MC = new TCanvas("c_eff_MC"+KID,"c_eff_MC"+KID,800,800);
    c_eff_MC->cd(1);
    c_eff_MC->SetGrid();
    h_AFB_true[3]->GetXaxis()->SetTitle("cos #theta_{j_{1}j_{2}}");
    h_AFB_true[3]->GetYaxis()->SetTitle("Selection Eff [%]");
    h_AFB_true[3]->GetYaxis()->SetTitleOffset(1.25);
    h_AFB_true[3]->GetXaxis()->SetTitleOffset(1.);
    //h_AFB_true[3]->GetYaxis()->SetRangeUser(0,12);
    h_AFB_true[3]->GetXaxis()->SetRangeUser(-1,1);

    h_AFB_true[3]->SetLineColor(3);
    h_AFB_true[3]->SetLineWidth(2);
    h_AFB_true[3]->Draw("histo");

    h_AFB_reco[3]->SetLineColor(1);
    h_AFB_reco[3]->SetMarkerColor(1);
    h_AFB_reco[3]->SetLineWidth(2);
    h_AFB_reco[3]->Draw("pesame");

    

    Labels(pol);

    TLegend *leg2 = new TLegend(0.2,0.76,0.4,0.9,KID);//(0.4,0.3,0.5,0.6);
    leg2->SetTextSize(0.035);
    leg2->AddEntry(h_AFB_true[3],TString::Format("%s, %s -- True q-charge sign",quark_string[3].Data(),pol.Data()),"l");
    leg2->AddEntry(h_AFB_reco[3],TString::Format("%s, %s -- K-charge sign",quark_string[3].Data(),pol.Data()),"pel");
    leg2->SetFillStyle(0);
    leg2->SetLineWidth(0);
    leg2->SetLineColor(0);
    leg2->SetBorderSize(0);
    leg2->Draw();


  //c_eff_MC->Print(TString::Format("summaryplots/UnEff_sample_%i_pdg_%i_twopols.pdf",sample,iquark));
  }
}



void Migrations() {

  int isel=8;
  //EffPlotsPresel(isel);
  MigrationsPlots(isel);

  //
  //MCeffPlotPols(sample,5,900);
  //  MCuneffPlotPols(sample,5,900);

}
