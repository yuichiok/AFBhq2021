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
#include "fit.C"




void Labels(TString pol){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(pol=="eL_pR")
    QQBARLabel2(0.2,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}",kGray+2);
  else 
    if(pol=="eR_pL")
      QQBARLabel2(0.2,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}",kGray+2);
    else 
      QQBARLabel2(0.2,0.965, "e^{-}e^{+} #rightarrow q#bar{q}",kGray+2);

  //QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);

}


void Plots1(TString pol="eR_pL") {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  double AFBb[145]={0};
  double AFBb_COM[145]={0};
  double dAFBb[145]={0};
  double dAFBb_COM[145]={0};

  double AFBc[145]={0};
  double AFBc_COM[145]={0};
  double dAFBc[145]={0};
  double dAFBc_COM[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;
  for(int i=2; i<110; i+=3) {
    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_KLowerThan%i",i));
    std::vector<double>  result_AFBb=fit_histo_value(temp_AFBb, -1,1,false);
    AFBb[n]=100.*result_AFBb.at(0);
    dAFBb[n]=100.*result_AFBb.at(1)/2.;

    TH1F* temp_AFBb_COM = (TH1F*)f->Get(TString::Format("h_AFBb_COM_KLowerThan%i",i));
    std::vector<double>  result_AFBb_COM=fit_histo_value(temp_AFBb_COM, -1,1,false);
    AFBb_COM[n]=100.*result_AFBb_COM.at(0);
    dAFBb_COM[n]=100.*result_AFBb_COM.at(1)/2.;

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    std::vector<double>  result_AFBc=fit_histo_value(temp_AFBc, -1,1,false);
    AFBc[n]=100.*result_AFBc.at(0);
    dAFBc[n]=100.*result_AFBc.at(1)/2.;

    TH1F* temp_AFBc_COM = (TH1F*)f->Get(TString::Format("h_AFBc_COM_KLowerThan%i",i));
    std::vector<double>  result_AFBc_COM=fit_histo_value(temp_AFBc_COM, -1,1,false);
    AFBc_COM[n]=100.*result_AFBc_COM.at(0);
    dAFBc_COM[n]=100.*result_AFBc_COM.at(1)/2.;

    x[n]=i;
    n++;

  }


 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_COM = new TGraphErrors(n,x,AFBb_COM,ex,dAFBb_COM); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_COM = new TGraphErrors(n,x,AFBc_COM,ex,dAFBc_COM);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc_COM,ex,dAFBc_COM);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc_COM,ex,dAFBc_COM);


  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("K_{#gamma-cut}");
  gAFBb->GetYaxis()->SetTitle("AFB [%]");
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("alp");

  gAFBb_COM->SetLineColor(4);
  gAFBb_COM->SetLineWidth(2);
  gAFBb_COM->SetLineStyle(2);
  gAFBb_COM->Draw("lp");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("lp");

  gAFBc_COM->SetLineColor(2);
  gAFBc_COM->SetLineWidth(2);
  gAFBc_COM->SetLineStyle(2);
  gAFBc_COM->Draw("lp");

  test->SetLineColor(1);
  test->SetLineWidth(2);
  test->SetLineStyle(1);
  test2->SetLineColor(1);
  test2->SetLineWidth(2);
  test2->SetLineStyle(2);

  Labels(pol);
  
  TLegend *leg_b = new TLegend(0.2,0.25,0.5,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,"b-quark","l");
  leg_b->AddEntry(gAFBc,"c-quark","l");
  leg_b->AddEntry(test,"laboratory syst. of ref.","l");
  leg_b->AddEntry(test2,"c.of. mass syst. of ref.","l");

  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  //c_eff_b->Print("plots_draft/btagging_performance.eps");

}


void Plots2(TString pol="eR_pL") {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  double AFBb[145]={0};
  double AFBb_COM[145]={0};
  double dAFBb[145]={0};
  double dAFBb_COM[145]={0};

  double AFBc[145]={0};
  double AFBc_COM[145]={0};
  double dAFBc[145]={0};
  double dAFBc_COM[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;
  for(int i=2; i<100; i+=3) {
    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    std::vector<double>  result_AFBb=fit_histo_value(temp_AFBb, -1,1,false);
    AFBb[n]=100.*result_AFBb.at(0);
    dAFBb[n]=100.*result_AFBb.at(1)/2.;

    TH1F* temp_AFBb_COM = (TH1F*)f->Get(TString::Format("h_AFBb_COM_K35_AcolLowerThan%i",i));
    std::vector<double>  result_AFBb_COM=fit_histo_value(temp_AFBb_COM, -1,1,false);
    AFBb_COM[n]=100.*result_AFBb_COM.at(0);
    dAFBb_COM[n]=100.*result_AFBb_COM.at(1)/2.;

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));
    std::vector<double>  result_AFBc=fit_histo_value(temp_AFBc, -1,1,false);
    AFBc[n]=100.*result_AFBc.at(0);
    dAFBc[n]=100.*result_AFBc.at(1)/2.;

    TH1F* temp_AFBc_COM = (TH1F*)f->Get(TString::Format("h_AFBc_COM_K35_AcolLowerThan%i",i));
    std::vector<double>  result_AFBc_COM=fit_histo_value(temp_AFBc_COM, -1,1,false);
    AFBc_COM[n]=100.*result_AFBc_COM.at(0);
    dAFBc_COM[n]=100.*result_AFBc_COM.at(1)/2.;

    x[n]=i/100.;
    n++;

  }


 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_COM = new TGraphErrors(n,x,AFBb_COM,ex,dAFBb_COM); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_COM = new TGraphErrors(n,x,AFBc_COM,ex,dAFBc_COM);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc_COM,ex,dAFBc_COM);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc_COM,ex,dAFBc_COM);


  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("sin #Psi -cut");
  gAFBb->GetYaxis()->SetTitle("AFB [%]");
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("alp");

  gAFBb_COM->SetLineColor(4);
  gAFBb_COM->SetLineWidth(2);
  gAFBb_COM->SetLineStyle(2);
  gAFBb_COM->Draw("lp");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("lp");

  gAFBc_COM->SetLineColor(2);
  gAFBc_COM->SetLineWidth(2);
  gAFBc_COM->SetLineStyle(2);
  gAFBc_COM->Draw("lp");

  test->SetLineColor(1);
  test->SetLineWidth(2);
  test->SetLineStyle(1);
  test2->SetLineColor(1);
  test2->SetLineWidth(2);
  test2->SetLineStyle(2);

  Labels(pol);
  
  TLegend *leg_b = new TLegend(0.2,0.25,0.5,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,"b-quark","l");
  leg_b->AddEntry(gAFBc,"c-quark","l");
  leg_b->AddEntry(test,"laboratory syst. of ref.","l");
  leg_b->AddEntry(test2,"c.of. mass syst. of ref.","l");

  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  //c_eff_b->Print("plots_draft/btagging_performance.eps");

}


void Observables() {

  Plots1();


}
