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

    TH1F*  h_AFB_reco[6];
    TH1F*  h_AFB_true[6];
    for(int q=1; q<6; q++) {
      h_AFB_true[q] = (TH1F*)f->Get(TString::Format("h_AFB_true_q%i_sel%i",q,isel));
      h_AFB_reco[q] = (TH1F*)f->Get(TString::Format("h_AFB_reco_q%i_sel%i",q,isel));
      h_AFB_true[q]->Sumw2();
      h_AFB_reco[q]->Sumw2();      
    }
  
    TCanvas* c_migrations_MC = new TCanvas("c_migrations_MC"+KID,"c_migrations_MC"+KID,800,800);
    c_migrations_MC->cd(1);
    c_migrations_MC->SetGrid();
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

    

    Labels(pol,luminosity);

    TLegend *leg2 = new TLegend(0.2,0.76,0.4,0.9);//(0.4,0.3,0.5,0.6);
    if(isel==9) leg2->SetHeader(KID);
    leg2->SetTextSize(0.035);
    leg2->AddEntry(h_AFB_true[3],TString::Format("%s, %s -- Sign from true q-charge",quark_string[3].Data(),pol.Data()),"l");
    if(isel==8) leg2->AddEntry(h_AFB_reco[3],TString::Format("%s, %s -- Sign from Cheat K-ID",quark_string[3].Data(),pol.Data()),"pel");
    if(isel==9) leg2->AddEntry(h_AFB_reco[3],TString::Format("%s, %s -- Sign from reco K-ID",quark_string[3].Data(),pol.Data()),"pel");
    leg2->SetFillStyle(0);
    leg2->SetLineWidth(0);
    leg2->SetLineColor(0);
    leg2->SetBorderSize(0);
    leg2->Draw();


  c_migrations_MC->Print(TString::Format("c_migrations_MC_sel%i_%s_%s.png",isel,KID.Data(),pol.Data()));
  }
}



void Migrations() {

  for(int isel=8; isel<10; isel++) {
    MigrationsPlots(isel,"eL_pR");
    MigrationsPlots(isel,"eR_pL");
  }


}
