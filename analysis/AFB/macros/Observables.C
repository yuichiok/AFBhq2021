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

void Plots_AFB() {

  
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
  for(int i=2; i<110; i+=3) {
    TH1F* temp_AFBb = (TH1F*)f->Get(TString::Format("h_AFBb_KLowerThan%i",i));
    std::vector<double>  result_AFBb=fit_histo_value(temp_AFBb, -1,1,false);
    AFBb[n]=100.*result_AFBb.at(0);
    dAFBb[n]=100.*result_AFBb.at(1)/2.;

    TH1F* temp_AFBb_eR = (TH1F*)f2->Get(TString::Format("h_AFBb_KLowerThan%i",i));
    std::vector<double>  result_AFBb_eR=fit_histo_value(temp_AFBb_eR, -1,1,false);
    AFBb_eR[n]=100.*result_AFBb_eR.at(0);
    dAFBb_eR[n]=100.*result_AFBb_eR.at(1)/2.;

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    std::vector<double>  result_AFBc=fit_histo_value(temp_AFBc, -1,1,false);
    AFBc[n]=100.*result_AFBc.at(0);
    dAFBc[n]=100.*result_AFBc.at(1)/2.;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    std::vector<double>  result_AFBc_eR=fit_histo_value(temp_AFBc_eR, -1,1,false);
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
  gAFBb->GetXaxis()->SetTitle("K_{#gamma-cut}");
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

  Labels(pol);
  
  TLegend *leg_b = new TLegend(0.2,0.25,0.5,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,"e_{L}^{-}e_{R}^{+}#rightarrow b#bar{b}","l");
  leg_b->AddEntry(gAFBb_eR,"e_{R}^{-}e_{L}^{+}#rightarrow b#bar{b}","l");
  leg_b->AddEntry(gAFBc,"e_{L}^{-}e_{R}^{+}#rightarrow c#bar{c}","l");
  leg_b->AddEntry(gAFBc_eR,"e_{R}^{-}e_{L}^{+}#rightarrow c#bar{c}","l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_AFBb->Print("plots_draft/AFB_kcut.eps");

}


void Plots_Cross() {

  
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

  for(int i=2; i<110; i+=3) {
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

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_KLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_KLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;


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
  gAFBb->GetXaxis()->SetTitle("K_{#gamma-cut}");
  gAFBb->GetYaxis()->SetTitle("cross section [fb]");
  gAFBb->GetYaxis()->SetRangeUser(500,40000);
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

  // Labels(pol);
  
  TLegend *leg_b = new TLegend(0.2,0.65,0.5,0.85);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(test,"e_{L}^{-}e_{R}^{+}#rightarrow q#bar{q}","l");
  leg_b->AddEntry(test2,"e_{R}^{-}e_{L}^{+}#rightarrow q#bar{q}","l");
  leg_b->AddEntry(gAFBb,"q=b","l");
  leg_b->AddEntry(gAFBc,"q=c","l");
  leg_b->AddEntry(gAFBq,"q=u,d,s","l"); 
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_AFBb->Print("plots_draft/IncCrossSection_kcut.eps");

}


void Plots_R() {

  
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

  for(int i=2; i<110; i+=3) {
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

    TH1F* temp_AFBc = (TH1F*)f->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    AFBc[n]=temp_AFBc->Integral()/luminosity;
    dAFBc[n]=0;

    TH1F* temp_AFBc_eR = (TH1F*)f2->Get(TString::Format("h_AFBc_KLowerThan%i",i));
    AFBc_eR[n]=temp_AFBc_eR->Integral()/luminosity_eR;
    dAFBc_eR[n]=0;

    TH1F* temp_AFBq = (TH1F*)f->Get(TString::Format("h_AFBuds_KLowerThan%i",i));
    AFBq[n]=temp_AFBq->Integral()/luminosity;
    dAFBq[n]=0;

    TH1F* temp_AFBq_eR = (TH1F*)f2->Get(TString::Format("h_AFBuds_KLowerThan%i",i));
    AFBq_eR[n]=temp_AFBq_eR->Integral()/luminosity_eR;
    dAFBq_eR[n]=0;


    AFBb[n]=temp_AFBb->Integral()/(temp_AFBb->Integral()+temp_AFBc->Integral()+temp_AFBq->Integral());
    AFBb_eR[n]=temp_AFBb_eR->Integral()/(temp_AFBb_eR->Integral()+temp_AFBc_eR->Integral()+temp_AFBq_eR->Integral());
    AFBc[n]=temp_AFBc->Integral()/(temp_AFBc->Integral()+temp_AFBc->Integral()+temp_AFBq->Integral());
    AFBc_eR[n]=temp_AFBc_eR->Integral()/(temp_AFBc_eR->Integral()+temp_AFBc_eR->Integral()+temp_AFBq_eR->Integral());


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
  gAFBb->GetXaxis()->SetTitle("K_{#gamma-cut}");
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



  // Labels(pol);
  
  TLegend *leg_b = new TLegend(0.2,0.65,0.5,0.85);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(gAFBb,"e_{L}^{-}e_{R}^{+}#rightarrow b#bar{b}","l");
  leg_b->AddEntry(gAFBb_eR,"e_{R}^{-}e_{L}^{+}#rightarrow b#bar{b}","l");
  leg_b->AddEntry(gAFBc,"e_{L}^{-}e_{R}^{+}#rightarrow c#bar{c}","l");
  leg_b->AddEntry(gAFBc_eR,"e_{R}^{-}e_{L}^{+}#rightarrow c#bar{c}","l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_AFBb->Print("plots_draft/R_kcut.eps");

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

  Plots_Cross();
  Plots_AFB();
  Plots_R();


}
