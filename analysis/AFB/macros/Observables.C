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




void Labels(TString extra=""){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);

  QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q}"+extra,kGray+2);

  //QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);

}

void Plots_AFB(int mode=1) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
  int ipol1=0;
  int ipol2=1;
  if(mode == 1) {
    ipol1=2; ipol2=3;
  }
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  float luminosity=0;
  float luminosity_eR=0;

  for(int i=2; i<110; i+=1) {

    if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      float totalev=total->Integral();
      float totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][4];
      luminosity_eR=totalev_eR/cross_section[1][4];
    }
      
    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    temp_AFBb->Scale(1./luminosity);
    temp_AFBb_eR->Scale(1./luminosity_eR);

    std::vector<double>  result_AFBb_eR=fit_histo_value(temp_AFBb,temp_AFBb_eR, -1,1,false,ipol2);
    AFBb_eR[n]=100.*result_AFBb_eR.at(0);
    dAFBb_eR[n]=100.*result_AFBb_eR.at(1)/2.;

    std::vector<double>  result_AFBb=fit_histo_value(temp_AFBb,temp_AFBb_eR, -1,1,false,ipol1);
    AFBb[n]=100.*result_AFBb.at(0);
    dAFBb[n]=100.*result_AFBb.at(1)/2.;

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));
    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));

    temp_AFBc->Scale(1./luminosity);
    temp_AFBc_eR->Scale(1./luminosity_eR);
    
    std::vector<double>  result_AFBc=fit_histo_value(temp_AFBc,temp_AFBc_eR, -1,1,false,ipol1);
    AFBc[n]=100.*result_AFBc.at(0);
    dAFBc[n]=100.*result_AFBc.at(1)/2.;

    std::vector<double>  result_AFBc_eR=fit_histo_value(temp_AFBc,temp_AFBc_eR, -1,1,false,ipol2);
    AFBc_eR[n]=100.*result_AFBc_eR.at(0);
    dAFBc_eR[n]=100.*result_AFBc_eR.at(1)/2.;

    x[n]=i;
    n++;

  }

  
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);


  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("E_{#gamma}^{cut}");
  gAFBb->GetYaxis()->SetTitle("AFB [%]");
  gAFBb->GetYaxis()->SetRangeUser(-40,90);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("alp");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("lp");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("lp");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("lp");

  Labels(", sin(#Psi_{acol})<0.3");

  TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.25,0.5,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,TString::Format("%s#rightarrow b#bar{b}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBb_eR,TString::Format("%s#rightarrow b#bar{b}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBc,TString::Format("%s#rightarrow c#bar{c}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBc_eR,TString::Format("%s#rightarrow c#bar{c}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_AFBb->Print(TString::Format("plots_draft/AFB_kcut_mode%i.eps",mode));

}


void Plots_AFB2(int mode=1) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
  int ipol1=0;
  int ipol2=1;
  if(mode == 1) {
    ipol1=2; ipol2=3;
  }
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  float luminosity=0;
  float luminosity_eR=0;

  for(int i=2; i<100; i+=1) {

    if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      float totalev=total->Integral();
      float totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][4];
      luminosity_eR=totalev_eR/cross_section[1][4];
    }
      
    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    temp_AFBb->Scale(1./luminosity);
    temp_AFBb_eR->Scale(1./luminosity_eR);

    std::vector<double>  result_AFBb_eR=fit_histo_value(temp_AFBb,temp_AFBb_eR, -1,1,false,ipol2);
    AFBb_eR[n]=100.*result_AFBb_eR.at(0);
    dAFBb_eR[n]=100.*result_AFBb_eR.at(1)/2.;

    std::vector<double>  result_AFBb=fit_histo_value(temp_AFBb,temp_AFBb_eR, -1,1,false,ipol1);
    AFBb[n]=100.*result_AFBb.at(0);
    dAFBb[n]=100.*result_AFBb.at(1)/2.;

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));
    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));

    temp_AFBc->Scale(1./luminosity);
    temp_AFBc_eR->Scale(1./luminosity_eR);
    
    std::vector<double>  result_AFBc=fit_histo_value(temp_AFBc,temp_AFBc_eR, -1,1,false,ipol1);
    AFBc[n]=100.*result_AFBc.at(0);
    dAFBc[n]=100.*result_AFBc.at(1)/2.;

    std::vector<double>  result_AFBc_eR=fit_histo_value(temp_AFBc,temp_AFBc_eR, -1,1,false,ipol2);
    AFBc_eR[n]=100.*result_AFBc_eR.at(0);
    dAFBc_eR[n]=100.*result_AFBc_eR.at(1)/2.;

    x[n]=i/100.;
    n++;

  }

  
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);


  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("sin(#Psi_{acol})^{cut}");
  gAFBb->GetYaxis()->SetTitle("AFB [%]");
  gAFBb->GetYaxis()->SetRangeUser(-40,90);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("alp");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("lp");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("lp");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("lp");

  Labels(", E_{#gamma}<35 GeV");

  TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  
  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  TLegend *leg_b = new TLegend(0.2,0.25,0.5,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,TString::Format("%s#rightarrow b#bar{b}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBb_eR,TString::Format("%s#rightarrow b#bar{b}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBc,TString::Format("%s#rightarrow c#bar{c}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBc_eR,TString::Format("%s#rightarrow c#bar{c}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_AFBb->Print(TString::Format("plots_draft/AFB_acolcut_mode%i.eps",mode));

}


void Plots_CrossDiff(int mode=0) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  TGraph* gAFBb;
  TGraph* gAFBb_eR;
  TGraph* gAFBc;
  TGraph* gAFBc_eR;
  TGraph* test;
  TGraph* test2;
 
  double totalev=0;
  double totalev_eR=0;
  double luminosity=0;
  double luminosity_eR=0;

  
  TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
  TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
  totalev=total->Integral();
  totalev_eR=total_eR->Integral();
  luminosity=totalev/cross_section[0][3];
  luminosity_eR=totalev_eR/cross_section[1][3];
  
  TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",35));
  TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",35));
  temp_AFBb->Scale(1./luminosity);
  temp_AFBb_eR->Scale(1./luminosity_eR);
  if(mode==0) {
    gAFBb = new TGraph(temp_AFBb);
    gAFBb_eR = new TGraph(temp_AFBb_eR);
  }

  if(mode==1) {
    TH1F * h = (TH1F*)temp_AFBb->Clone("h");
    TH1F * h_eR = (TH1F*)temp_AFBb_eR->Clone("h_eR");
    h->Scale(0.58);
    h_eR->Scale(0.035);
    h->Add(h_eR);
    gAFBb = new TGraph(h);
    delete h, h_eR;

    TH1F * h2 = (TH1F*)temp_AFBb->Clone("h2");
    TH1F * h2_eR = (TH1F*)temp_AFBb_eR->Clone("h2_eR");
    h2->Scale(0.035);
    h2_eR->Scale(0.58);
    h2->Add(h2_eR);
    gAFBb_eR = new TGraph(h2);
    delete h2, h2_eR;
  }

  TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",35));
  TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",35));
  temp_AFBc->Scale(1./luminosity);
  temp_AFBc_eR->Scale(1./luminosity_eR);
  if(mode==0) {
    gAFBc = new TGraph(temp_AFBc);
    gAFBc_eR = new TGraph(temp_AFBc_eR);
    test = new TGraph(temp_AFBc);
    test2 = new TGraph(temp_AFBc);
  }
  if(mode==1) {
    TH1F * h = (TH1F*)temp_AFBc->Clone("h");
    TH1F * h_eR = (TH1F*)temp_AFBc_eR->Clone("h_eR");
    h->Scale(0.58);
    h_eR->Scale(0.035);
    h->Add(h_eR);
    gAFBc = new TGraph(h);
    delete h, h_eR;

    TH1F * h2 = (TH1F*)temp_AFBc->Clone("h2");
    TH1F * h2_eR = (TH1F*)temp_AFBc_eR->Clone("h2_eR");
    h2->Scale(0.035);
    h2_eR->Scale(0.58);
    h2->Add(h2_eR);
    gAFBc_eR = new TGraph(h2);
    delete h2, h2_eR;

    test = new TGraph(temp_AFBc);
    test2 = new TGraph(temp_AFBc); 
  }



  TGaxis::SetMaxDigits(3);

  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("cos(#theta_{q})");
  gAFBb->GetYaxis()->SetTitle("cross section [fb] / 0.05");
  gAFBb->GetYaxis()->SetRangeUser(0,500);
  gAFBb->GetXaxis()->SetRangeUser(-1,1);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("ac");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("c");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("c");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("c");


  test->SetLineColor(1);
  test->SetLineWidth(2);
  test->SetLineStyle(1);
  test2->SetLineColor(1);
  test2->SetLineWidth(2);
  test2->SetLineStyle(2);

  Labels(", sin(#Psi_{acol})<0.3 ");


  TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.72,0.5,0.91);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(test,TString::Format("%s#rightarrow q#bar{q}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(test2,TString::Format("%s#rightarrow q#bar{q}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBb,"q=b","l");
  leg_b->AddEntry(gAFBc,"q=c","l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

    
  c_AFBb->Print(TString::Format("plots_draft/DiffCrossSection_acolcut_kcut_mode%i.eps",mode));

}

void Plots_Cross0(int mode=0) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double AFBq[145]={0};
  double AFBq_eR[145]={0};
  double dAFBq[145]={0};
  double dAFBq_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  double totalev=0;
  double totalev_eR=0;
  double luminosity=0;
  double luminosity_eR=0;

  for(int i=2; i<110; i+=1) {
   if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      totalev=total->Integral();
      totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][3];
      luminosity_eR=totalev_eR/cross_section[1][3];
    }

    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_KLowerThan%i",i));
    AFBb[n]=temp_AFBb->Integral()/luminosity;
    dAFBb[n]=0;

    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_KLowerThan%i",i));
    AFBb_eR[n]=temp_AFBb_eR->Integral()/luminosity_eR;
    dAFBb_eR[n]=0;

    float temp=AFBb[n];
    float temp_eR=AFBb_eR[n];
    if(mode==1) {
      AFBb[n]=temp*0.58+0.035*temp_eR;
      AFBb_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    temp=AFBc[n];
    temp_eR=AFBc_eR[n];
    if(mode==1) {
      AFBc[n]=temp*0.58+0.035*temp_eR;
      AFBc_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_KLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_KLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;

    temp=AFBq[n];
    temp_eR=AFBq_eR[n];
    if(mode==1) {
      AFBq[n]=temp*0.58+0.035*temp_eR;
      AFBq_eR[n]=temp*0.035+0.58*temp_eR;
    }

    x[n]=i;
    n++;

  }

 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* gAFBq = new TGraphErrors(n,x,AFBq,ex,dAFBq);
  TGraphErrors* gAFBq_eR = new TGraphErrors(n,x,AFBq_eR,ex,dAFBq_eR);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc,ex,dAFBc);

  TGaxis::SetMaxDigits(3);

  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("E_{#gamma}^{cut}");
  gAFBb->GetYaxis()->SetTitle("cross section [fb]");
  gAFBb->GetYaxis()->SetRangeUser(500,30000);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("al");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("l");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("l");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("l");

  gAFBq->SetLineColor(kGreen+1);
  gAFBq->SetLineWidth(2);
  gAFBq->SetLineStyle(1);
  gAFBq->Draw("l");

  gAFBq_eR->SetLineColor(kGreen+1);
  gAFBq_eR->SetLineWidth(2);
  gAFBq_eR->SetLineStyle(2);
  gAFBq_eR->Draw("l");


 test->SetLineColor(1);
  test->SetLineWidth(2);
  test->SetLineStyle(1);
  test2->SetLineColor(1);
  test2->SetLineWidth(2);
  test2->SetLineStyle(2);

  Labels("");


  TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.72,0.5,0.91);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(test,TString::Format("%s#rightarrow q#bar{q}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(test2,TString::Format("%s#rightarrow q#bar{q}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBb,"q=b","l");
  leg_b->AddEntry(gAFBc,"q=c","l");
  leg_b->AddEntry(gAFBq,"q=u,d,s","l"); 
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

    
  c_AFBb->Print(TString::Format("plots_draft/IncCrossSection_kcut_noacol_mode%i.eps",mode));

}


void Plots_Cross(int mode=0) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double AFBq[145]={0};
  double AFBq_eR[145]={0};
  double dAFBq[145]={0};
  double dAFBq_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  double totalev=0;
  double totalev_eR=0;
  double luminosity=0;
  double luminosity_eR=0;

  for(int i=2; i<110; i+=1) {
   if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      totalev=total->Integral();
      totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][3];
      luminosity_eR=totalev_eR/cross_section[1][3];
    }

    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    AFBb[n]=temp_AFBb->Integral()/luminosity;
    dAFBb[n]=0;

    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    AFBb_eR[n]=temp_AFBb_eR->Integral()/luminosity_eR;
    dAFBb_eR[n]=0;

    float temp=AFBb[n];
    float temp_eR=AFBb_eR[n];
    if(mode==1) {
      AFBb[n]=temp*0.58+0.035*temp_eR;
      AFBb_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    temp=AFBc[n];
    temp_eR=AFBc_eR[n];
    if(mode==1) {
      AFBc[n]=temp*0.58+0.035*temp_eR;
      AFBc_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_acol30_KLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_acol30_KLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;

    temp=AFBq[n];
    temp_eR=AFBq_eR[n];
    if(mode==1) {
      AFBq[n]=temp*0.58+0.035*temp_eR;
      AFBq_eR[n]=temp*0.035+0.58*temp_eR;
    }

    x[n]=i;
    n++;

  }

 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* gAFBq = new TGraphErrors(n,x,AFBq,ex,dAFBq);
  TGraphErrors* gAFBq_eR = new TGraphErrors(n,x,AFBq_eR,ex,dAFBq_eR);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc,ex,dAFBc);

  TGaxis::SetMaxDigits(3);

  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("E_{#gamma}^{cut}");
  gAFBb->GetYaxis()->SetTitle("cross section [fb]");
  gAFBb->GetYaxis()->SetRangeUser(500,30000);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("al");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("l");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("l");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("l");

  gAFBq->SetLineColor(kGreen+1);
  gAFBq->SetLineWidth(2);
  gAFBq->SetLineStyle(1);
  gAFBq->Draw("l");

  gAFBq_eR->SetLineColor(kGreen+1);
  gAFBq_eR->SetLineWidth(2);
  gAFBq_eR->SetLineStyle(2);
  gAFBq_eR->Draw("l");


 test->SetLineColor(1);
  test->SetLineWidth(2);
  test->SetLineStyle(1);
  test2->SetLineColor(1);
  test2->SetLineWidth(2);
  test2->SetLineStyle(2);

  Labels(", sin(#Psi_{acol})<0.3");


  TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.72,0.5,0.91);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(test,TString::Format("%s#rightarrow q#bar{q}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(test2,TString::Format("%s#rightarrow q#bar{q}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBb,"q=b","l");
  leg_b->AddEntry(gAFBc,"q=c","l");
  leg_b->AddEntry(gAFBq,"q=u,d,s","l"); 
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

    
  c_AFBb->Print(TString::Format("plots_draft/IncCrossSection_kcut_mode%i.eps",mode));

}


void Plots_Cross2(int mode=0) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double AFBq[145]={0};
  double AFBq_eR[145]={0};
  double dAFBq[145]={0};
  double dAFBq_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  double totalev=0;
  double totalev_eR=0;
  double luminosity=0;
  double luminosity_eR=0;

  for(int i=2; i<110; i+=1) {
   if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      totalev=total->Integral();
      totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][3];
      luminosity_eR=totalev_eR/cross_section[1][3];
    }

    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    AFBb[n]=temp_AFBb->Integral()/luminosity;
    dAFBb[n]=0;

    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    AFBb_eR[n]=temp_AFBb_eR->Integral()/luminosity_eR;
    dAFBb_eR[n]=0;

    float temp=AFBb[n];
    float temp_eR=AFBb_eR[n];
    if(mode==1) {
      AFBb[n]=temp*0.58+0.035*temp_eR;
      AFBb_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    temp=AFBc[n];
    temp_eR=AFBc_eR[n];
    if(mode==1) {
      AFBc[n]=temp*0.58+0.035*temp_eR;
      AFBc_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_K35_AcolLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_K35_AcolLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;

    temp=AFBq[n];
    temp_eR=AFBq_eR[n];
    if(mode==1) {
      AFBq[n]=temp*0.58+0.035*temp_eR;
      AFBq_eR[n]=temp*0.035+0.58*temp_eR;
    }

    x[n]=i/100.;
    n++;

  }

 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
  TGraphErrors* gAFBq = new TGraphErrors(n,x,AFBq,ex,dAFBq);
  TGraphErrors* gAFBq_eR = new TGraphErrors(n,x,AFBq_eR,ex,dAFBq_eR);
  TGraphErrors* test= new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* test2= new TGraphErrors(n,x,AFBc,ex,dAFBc);

  TGaxis::SetMaxDigits(3);

  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("sin(#Psi_{acol})");
  gAFBb->GetYaxis()->SetTitle("cross section [fb]");
  gAFBb->GetYaxis()->SetRangeUser(500,30000);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("al");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("l");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("l");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("l");

  gAFBq->SetLineColor(kGreen+1);
  gAFBq->SetLineWidth(2);
  gAFBq->SetLineStyle(1);
  gAFBq->Draw("l");

  gAFBq_eR->SetLineColor(kGreen+1);
  gAFBq_eR->SetLineWidth(2);
  gAFBq_eR->SetLineStyle(2);
  gAFBq_eR->Draw("l");


 test->SetLineColor(1);
  test->SetLineWidth(2);
  test->SetLineStyle(1);
  test2->SetLineColor(1);
  test2->SetLineWidth(2);
  test2->SetLineStyle(2);

  Labels(", E_{#gamma}<35 GeV");


  TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.72,0.5,0.91);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(test,TString::Format("%s#rightarrow q#bar{q}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(test2,TString::Format("%s#rightarrow q#bar{q}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBb,"q=b","l");
  leg_b->AddEntry(gAFBc,"q=c","l");
  leg_b->AddEntry(gAFBq,"q=u,d,s","l"); 
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

    
  c_AFBb->Print(TString::Format("plots_draft/IncCrossSection_acolcut_mode%i.eps",mode));

}

  
void Plots_R(int mode=0) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double AFBq[145]={0};
  double AFBq_eR[145]={0};
  double dAFBq[145]={0};
  double dAFBq_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  double totalev=0;
  double totalev_eR=0;
  double luminosity=0;
  double luminosity_eR=0;

  for(int i=2; i<110; i+=1) {
   if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      totalev=total->Integral();
      totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][3];
      luminosity_eR=totalev_eR/cross_section[1][3];
    }

    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    AFBb[n]=temp_AFBb->Integral()/luminosity;
    dAFBb[n]=0;

    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    AFBb_eR[n]=temp_AFBb_eR->Integral()/luminosity_eR;
    dAFBb_eR[n]=0;

    float temp=AFBb[n];
    float temp_eR=AFBb_eR[n];
    if(mode==1) {
      AFBb[n]=temp*0.58+0.035*temp_eR;
      AFBb_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    temp=AFBc[n];
    temp_eR=AFBc_eR[n];
    if(mode==1) {
      AFBc[n]=temp*0.58+0.035*temp_eR;
      AFBc_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_acol30_KLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_acol30_KLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;

    temp=AFBq[n];
    temp_eR=AFBq_eR[n];
    if(mode==1) {
      AFBq[n]=temp*0.58+0.035*temp_eR;
      AFBq_eR[n]=temp*0.035+0.58*temp_eR;
    }

    
    // AFBb[n]=temp_AFBb->Integral()/(temp_AFBb->Integral()+temp_AFBc->Integral()+temp_AFBq->Integral());
    // AFBb_eR[n]=temp_AFBb_eR->Integral()/(temp_AFBb_eR->Integral()+temp_AFBc_eR->Integral()+temp_AFBq_eR->Integral());
    // AFBc[n]=temp_AFBc->Integral()/(temp_AFBc->Integral()+temp_AFBc->Integral()+temp_AFBq->Integral());
    // AFBc_eR[n]=temp_AFBc_eR->Integral()/(temp_AFBc_eR->Integral()+temp_AFBc_eR->Integral()+temp_AFBq_eR->Integral());

    float ab=AFBb[n];
    float ac=AFBc[n];
    float aq=AFBq[n];
    AFBb[n]=ab/(ab+ac+aq);
    AFBc[n]=ac/(ab+ac+aq);
    AFBq[n]=aq/(ab+ac+aq);


    ab=AFBb_eR[n];
    ac=AFBc_eR[n];
    aq=AFBq_eR[n];
    AFBb_eR[n]=ab/(ab+ac+aq);
    AFBc_eR[n]=ac/(ab+ac+aq);
    AFBq_eR[n]=aq/(ab+ac+aq);


    x[n]=i;
    n++;

  }

 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
 
  TGaxis::SetMaxDigits(3);

  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("E_{#gamma}^{cut}");
  gAFBb->GetYaxis()->SetTitle("R");
  gAFBb->GetYaxis()->SetRangeUser(0,0.6);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("al");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("l");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("l");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("l");


  Labels(", sin(#Psi_{acol})<0.3");
  
   TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.7,0.5,0.9);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,TString::Format("%s#rightarrow b#bar{b}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBb_eR,TString::Format("%s#rightarrow b#bar{b}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBc,TString::Format("%s#rightarrow c#bar{c}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBc_eR,TString::Format("%s#rightarrow c#bar{c}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();


  c_AFBb->Print(TString::Format("plots_draft/R_kcut_mode%i.eps",mode));

}


  
void Plots_R2(int mode=0) {

  //if mode == 0 --> pure polarization assumed
  //if mode == 1 --> 80,30 polarisations
   
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString pol="eL_pR";
  TString filename = "../results/AFBenergyDep_2f_hadronic_sample_"+pol+"_250GeV.root";
  TFile *f = new TFile(filename);

  TString pol2="eR_pL";
  TString filename2 = "../results/AFBenergyDep_2f_hadronic_sample_"+pol2+"_250GeV.root";
  TFile *f2 = new TFile(filename2);

  double AFBb[145]={0};
  double AFBb_eR[145]={0};
  double dAFBb[145]={0};
  double dAFBb_eR[145]={0};

  double AFBc[145]={0};
  double AFBc_eR[145]={0};
  double dAFBc[145]={0};
  double dAFBc_eR[145]={0};

  double AFBq[145]={0};
  double AFBq_eR[145]={0};
  double dAFBq[145]={0};
  double dAFBq_eR[145]={0};

  double x[145]={0};
  double ex[145]={0};
  int n=0;

  double totalev=0;
  double totalev_eR=0;
  double luminosity=0;
  double luminosity_eR=0;

  for(int i=2; i<110; i+=1) {
   if(i==2) {
      TH1F* total = (TH1F*)f->Get("h_Ntotal_nocuts");
      TH1F* total_eR = (TH1F*)f2->Get("h_Ntotal_nocuts");
      totalev=total->Integral();
      totalev_eR=total_eR->Integral();
      luminosity=totalev/cross_section[0][3];
      luminosity_eR=totalev_eR/cross_section[1][3];
    }

    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    AFBb[n]=temp_AFBb->Integral()/luminosity;
    dAFBb[n]=0;

    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_K35_AcolLowerThan%i",i));
    AFBb_eR[n]=temp_AFBb_eR->Integral()/luminosity_eR;
    dAFBb_eR[n]=0;

    float temp=AFBb[n];
    float temp_eR=AFBb_eR[n];
    if(mode==1) {
      AFBb[n]=temp*0.58+0.035*temp_eR;
      AFBb_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_K35_AcolLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    temp=AFBc[n];
    temp_eR=AFBc_eR[n];
    if(mode==1) {
      AFBc[n]=temp*0.58+0.035*temp_eR;
      AFBc_eR[n]=temp*0.035+0.58*temp_eR;
    }

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_K35_AcolLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_K35_AcolLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;

    temp=AFBq[n];
    temp_eR=AFBq_eR[n];
    if(mode==1) {
      AFBq[n]=temp*0.58+0.035*temp_eR;
      AFBq_eR[n]=temp*0.035+0.58*temp_eR;
    }

    
    // AFBb[n]=temp_AFBb->Integral()/(temp_AFBb->Integral()+temp_AFBc->Integral()+temp_AFBq->Integral());
    // AFBb_eR[n]=temp_AFBb_eR->Integral()/(temp_AFBb_eR->Integral()+temp_AFBc_eR->Integral()+temp_AFBq_eR->Integral());
    // AFBc[n]=temp_AFBc->Integral()/(temp_AFBc->Integral()+temp_AFBc->Integral()+temp_AFBq->Integral());
    // AFBc_eR[n]=temp_AFBc_eR->Integral()/(temp_AFBc_eR->Integral()+temp_AFBc_eR->Integral()+temp_AFBq_eR->Integral());

    float ab=AFBb[n];
    float ac=AFBc[n];
    float aq=AFBq[n];
    AFBb[n]=ab/(ab+ac+aq);
    AFBc[n]=ac/(ab+ac+aq);
    AFBq[n]=aq/(ab+ac+aq);


    ab=AFBb_eR[n];
    ac=AFBc_eR[n];
    aq=AFBq_eR[n];
    AFBb_eR[n]=ab/(ab+ac+aq);
    AFBc_eR[n]=ac/(ab+ac+aq);
    AFBq_eR[n]=aq/(ab+ac+aq);


    x[n]=i/100.;
    n++;

  }

 
  TGraphErrors* gAFBb = new TGraphErrors(n,x,AFBb,ex,dAFBb);
  TGraphErrors* gAFBb_eR = new TGraphErrors(n,x,AFBb_eR,ex,dAFBb_eR); 
  TGraphErrors* gAFBc = new TGraphErrors(n,x,AFBc,ex,dAFBc);
  TGraphErrors* gAFBc_eR = new TGraphErrors(n,x,AFBc_eR,ex,dAFBc_eR);
 
  TGaxis::SetMaxDigits(3);

  TCanvas* c_AFBb = new TCanvas("c_AFBb","c_AFBb",800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  gAFBb->GetXaxis()->SetTitle("sin(#Psi_{acol})^{cut}");
  gAFBb->GetYaxis()->SetTitle("R");
  gAFBb->GetYaxis()->SetRangeUser(0,0.6);
  gAFBb->SetLineColor(4);
  gAFBb->SetLineWidth(2);
  gAFBb->SetLineStyle(1);
  gAFBb->Draw("al");

  gAFBb_eR->SetLineColor(4);
  gAFBb_eR->SetLineWidth(2);
  gAFBb_eR->SetLineStyle(2);
  gAFBb_eR->Draw("l");

  gAFBc->SetLineColor(2);
  gAFBc->SetLineWidth(2);
  gAFBc->SetLineStyle(1);
  gAFBc->Draw("l");

  gAFBc_eR->SetLineColor(2);
  gAFBc_eR->SetLineWidth(2);
  gAFBc_eR->SetLineStyle(2);
  gAFBc_eR->Draw("l");


  Labels(", E_{#gamma}<35  GeV");
  
    TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  TString string1 = "";
  TString string2 = "";

  if(mode==1) {
    pol_string1 = "e^{-}e^{+}";
    pol_string2 = "e^{-}e^{+}";
    string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
    string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  }
  
  TLegend *leg_b = new TLegend(0.2,0.7,0.5,0.9);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,TString::Format("%s#rightarrow b#bar{b}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBb_eR,TString::Format("%s#rightarrow b#bar{b}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->AddEntry(gAFBc,TString::Format("%s#rightarrow c#bar{c}%s",pol_string1.Data(),string1.Data()),"l");
  leg_b->AddEntry(gAFBc_eR,TString::Format("%s#rightarrow c#bar{c}%s",pol_string2.Data(),string2.Data()),"l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();



  c_AFBb->Print(TString::Format("plots_draft/R_acolcut_mode%i.eps",mode));

}

/*


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
    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_acol30_KLowerThan%i",i));
    std::vector<double>  result_AFBb=fit_histo_value(temp_AFBb, -1,1,false);
    AFBb[n]=100.*result_AFBb.at(0);
    dAFBb[n]=100.*result_AFBb.at(1)/2.;

    TH1F* temp_AFBb_COM = (TH1F*)f->Get(TString::Format("h_AFBb_COM_acol30_KLowerThan%i",i));
    std::vector<double>  result_AFBb_COM=fit_histo_value(temp_AFBb_COM, -1,1,false);
    AFBb_COM[n]=100.*result_AFBb_COM.at(0);
    dAFBb_COM[n]=100.*result_AFBb_COM.at(1)/2.;

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_acol30_KLowerThan%i",i));
    std::vector<double>  result_AFBc=fit_histo_value(temp_AFBc, -1,1,false);
    AFBc[n]=100.*result_AFBc.at(0);
    dAFBc[n]=100.*result_AFBc.at(1)/2.;

    TH1F* temp_AFBc_COM = (TH1F*)f->Get(TString::Format("h_AFBc_COM_acol30_KLowerThan%i",i));
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
  gAFBb->GetXaxis()->SetTitle("E_{#gamma^{cut}}");
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
  gAFBb->GetXaxis()->SetTitle("sin #Psi ^{cut}");
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
*/

void Observables() {

  //Plots_Cross();
  for(int i=0; i<2; i++) {
    /* Plots_AFB(i);
    Plots_AFB2(i);
    Plots_Cross0(i);
    Plots_Cross(i);
    Plots_Cross2(i);*/
    Plots_CrossDiff(i);
    //Plots_R(i);
    //Plots_R2(i);
  }

  //Plots_R();

}
