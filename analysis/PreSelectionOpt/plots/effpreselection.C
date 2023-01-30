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

TString energy="500GeV";

void Labels(int i=0, TString pol="eL"){

  QQBARLabel(0.86,0.954,"");
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, "photon veto_{0}",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "photon veto cut",kOrange+3);
  if(i==3) QQBARLabel2(0.04,0.082, "photon veto & acolinearity cuts",kOrange+3);

  if(i==4) {
    QQBARLabel2(0.04,0.082, "photon veto & acolinearity",kOrange+3);
    //QQBARLabel2(0.04,0.03, "& K_{reco} & m_{j1j1} cuts",kOrange+3);
    QQBARLabel2(0.04,0.03, "& m_{j1j1} cuts",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.082, "photon veto & acolinearity",kOrange+3);
    //QQBARLabel2(0.04,0.03, "& K_{reco} & m_{j1j1} & y_{23} cuts",kOrange+3);
    QQBARLabel2(0.04,0.03, "& m_{j1j1} & y_{23} cuts",kOrange+3);

  }

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, (q=udscb)",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, (q=udscb)",kGray+2);

}


void effpreselection() {

  cout<< "bb qq radreturn ww zz hz "<<endl;

  for(int step=5; step<6; step++) {
    
  TH1F *h_costheta_bb[2]; 
  TH1F *h_costheta_cc[2]; 
  TH1F *h_costheta_qq[2]; 
  TH1F *h_costheta_radreturn[2]; 
  /*  TH1F *h_costheta_ww[2]; 
  TH1F *h_costheta_zz[2]; 
  TH1F *h_costheta_hz[2]; */

  TString pol="eR_pL";

  float luminosity_0=1;
  for(int i=0; i<2; i++) {

    int cuts=0;
    if(i==0) cuts=0;
    if(i==1) cuts=step;
    
    TString folder=TString::Format("../results_"+energy+"/selection_cuts%i_",cuts);
    
    //----------------------------------
    TString filename = folder+"2f_hadronic_sample_"+pol+".root";//folder+"bbbar_"+kt+sel+"250GeV_"+pol+".root";
    //  if(i==0) filename = folder+"bbbar_radret_genkt_R100_Kgamma35_250GeV_"+pol+".root";
    cout<<" Z-->qq file: "<<filename<<endl;
    TFile *f = new TFile(filename);
    h_costheta_radreturn[i] = (TH1F*)f->Get("h_costheta_radreturn");
    TFile *f1 = new TFile(filename);
    h_costheta_bb[i] = (TH1F*)f->Get("h_costheta_bb");
    h_costheta_qq[i] = (TH1F*)f->Get("h_costheta_qq");
    h_costheta_cc[i] = (TH1F*)f->Get("h_costheta_cc");
    TH1F *h_luminosity_cross_2f = (TH1F*)f->Get("h_costheta_nocuts");
    if(i==0) luminosity_0=h_luminosity_cross_2f->GetEntries();
    else {
      h_costheta_radreturn[i]->Scale(luminosity_0/h_luminosity_cross_2f->GetEntries());
      h_costheta_bb[i]->Scale(luminosity_0/h_luminosity_cross_2f->GetEntries());
      h_costheta_cc[i]->Scale(luminosity_0/h_luminosity_cross_2f->GetEntries());
      h_costheta_qq[i]->Scale(luminosity_0/h_luminosity_cross_2f->GetEntries());
    }
  }
  
  
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  // gStyle->SetMarkerSize(1.5);

  h_costheta_radreturn[1]->Divide(h_costheta_radreturn[0]);
  h_costheta_bb[1]->Divide(h_costheta_bb[0]);
  h_costheta_cc[1]->Divide(h_costheta_cc[0]);
  h_costheta_qq[1]->Divide(h_costheta_qq[0]);
  
  TCanvas * canvas2 = new TCanvas(TString::Format("canvas_cut%i",step),TString::Format("canvas_cut%i",step),800,800);
  canvas2->cd(1);
  h_costheta_bb[1]->GetYaxis()->SetTitle("#varepsilon_{pres-X}");
  h_costheta_bb[1]->GetYaxis()->SetRangeUser(0,1.4);
  h_costheta_bb[1]->GetXaxis()->SetRangeUser(0,1.);
  h_costheta_bb[1]->GetXaxis()->SetTitle("|cos#theta|");
  h_costheta_bb[1]->GetYaxis()->SetTitleOffset(1.3);

  h_costheta_bb[1]->SetLineColor(4);
  h_costheta_bb[1]->Draw("histoe");

  h_costheta_qq[1]->SetLineColor(1);
  h_costheta_qq[1]->Draw("histoesame");
  h_costheta_cc[1]->SetLineStyle(2);
  h_costheta_cc[1]->Draw("histoesame");
  h_costheta_radreturn[1]->SetLineColor(2);
  h_costheta_radreturn[1]->Draw("histoesame");

  Labels(step,pol);

  TLegend *leg1 = new TLegend(0.4,0.7,0.8,0.85);//(0.4,0.3,0.5,0.6);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(h_costheta_bb[1],"#font[52]{X}= signal b-quark","le");
  leg1->AddEntry(h_costheta_cc[1],"#font[52]{X}= signal c-quark","le");
  leg1->AddEntry(h_costheta_qq[1],"#font[52]{X}= signal uds-quarks","le");
  leg1->AddEntry(h_costheta_radreturn[1],"#font[52]{X}= bkg rad ret","le");
  leg1->SetFillStyle(0);
  leg1->SetLineWidth(0);
  leg1->SetLineColor(0);
  //  leg1->SetShadowColor(0);
  leg1->SetBorderSize(0);
  leg1->Draw();

  TFile * newfile=new TFile("eff_pres.root","RECREATE");
  newfile->cd();
  h_costheta_bb[1]->SetName("Eff Presel");
  h_costheta_bb[1]->SetTitle("Eff Presel");
  h_costheta_bb[1]->Write();
  canvas2->Print(TString::Format("plots_"+energy+"/epsilonhad_cuts%i_%s.eps",step,pol.Data()));

 
  }
  
}
