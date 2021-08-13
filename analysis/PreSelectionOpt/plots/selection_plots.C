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
#include "cross_sections.h"

void Labels(int i=0, TString pol="eL"){

  QQBARLabel(0.86,0.952,"");
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, " K_{reco}<35 GeV",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 1",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 2",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>130 GeV",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 3",kOrange+3);
  }
   

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, XX fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, XX fb^{-1}",kGray+2);

}



void selection_plots(int polarisation=0, bool normalised=true) {

  cout<< "bb qq radreturn ww zz hz "<<endl;

  //Efficiency y23.
  float bb_integral[100];
  float qq_integral[100];
  float cc_integral[100];
  float radreturn_integral[100];
  float zz_integral[100];
  float ww_integral[100];
  float qqH_integral[100];
  for(int i=0; i<100; i++) {
    bb_integral[i]=0;
    qq_integral[i]=0;
    cc_integral[i]=0;
    radreturn_integral[i]=0;
    zz_integral[i]=0;
    ww_integral[i]=0;
    qqH_integral[i]=0;
  }

  TString pol="eL_pR";
  if(polarisation==1) pol="eR_pL";
    
  for(int i=0; i<2; i++) {

    //if(i==1) i=8;

    int cuts=i;
    
    //**********************************************************
    // ZZ
    TString folder=TString::Format("../results/selection_cuts%i_",cuts);
    
    TString filename = folder+"2f_hadronic_sample_"+pol+"_250GeV.root";
 
    TFile *f = new TFile(filename);
    TH1F *h_luminosity_cross_2f = (TH1F*)f->Get("h_costheta_nocuts");

    TH1F *h_mjj_bb = (TH1F*)f->Get("h_mjj_bb");
    TH1F *h_mj1_mj2_bb = (TH1F*)f->Get("h_mj1_mj2_bb");
    TH1F *h_y23_bb = (TH1F*)f->Get("h_y23_bb");
    TH1F *h_d23_bb = (TH1F*)f->Get("h_d23_bb");
    TH1F *h_costheta_th_vs_lab_bb = (TH1F*)f->Get("h_costheta_th_vs_lab_bb");
    TH1F *h_costheta_bb = (TH1F*)f->Get("h_costheta_bb");
    TH1F *h_K_bb = (TH1F*)f->Get("h_K_bb");
   
    TH1F *h_mjj_cc = (TH1F*)f->Get("h_mjj_cc");
    TH1F *h_mj1_mj2_cc = (TH1F*)f->Get("h_mj1_mj2_cc");
    TH1F *h_y23_cc = (TH1F*)f->Get("h_y23_cc");
    TH1F *h_d23_cc = (TH1F*)f->Get("h_d23_cc");
    TH1F *h_costheta_th_vs_lab_cc = (TH1F*)f->Get("h_costheta_th_vs_lab_cc");
    TH1F *h_costheta_cc = (TH1F*)f->Get("h_costheta_cc");
    TH1F *h_K_cc = (TH1F*)f->Get("h_K_cc");
    
    TH1F *h_mjj_qq = (TH1F*)f->Get("h_mjj_qq");
    TH1F *h_mj1_mj2_qq = (TH1F*)f->Get("h_mj1_mj2_qq");
    TH1F *h_y23_qq = (TH1F*)f->Get("h_y23_qq");
    TH1F *h_d23_qq = (TH1F*)f->Get("h_d23_qq");
    TH1F *h_costheta_th_vs_lab_qq = (TH1F*)f->Get("h_costheta_th_vs_lab_qq");
    TH1F *h_costheta_qq = (TH1F*)f->Get("h_costheta_qq");
    TH1F *h_K_qq = (TH1F*)f->Get("h_K_qq");
    

    TH1F *h_mjj_radreturn = (TH1F*)f->Get("h_mjj_radreturn");
    TH1F *h_mj1_mj2_radreturn = (TH1F*)f->Get("h_mj1_mj2_radreturn");
    TH1F *h_y23_radreturn = (TH1F*)f->Get("h_y23_radreturn");
    TH1F *h_d23_radreturn = (TH1F*)f->Get("h_d23_radreturn");
    TH1F *h_costheta_th_vs_lab_radreturn = (TH1F*)f->Get("h_costheta_th_vs_lab_radreturn");
    TH1F *h_costheta_radreturn = (TH1F*)f->Get("h_costheta_radreturn");
    TH1F *h_K_radreturn = (TH1F*)f->Get("h_K_radreturn");

    float luminosity = h_luminosity_cross_2f->GetEntries()/cross_section[polarisation][3];
      
    //**********************************************************
    // WW
    filename = folder+"4f_WW_hadronic_"+pol+"_250GeV.root";
    cout<<filename<<endl;
    TFile *f2 = new TFile(filename);
    TH1F *h_luminosity_cross_ww = (TH1F*)f2->Get("h_costheta_nocuts");
    TH1F *h_mjj_ww = (TH1F*)f2->Get("h_mjj_bb");
    TH1F *h_mj1_mj2_ww = (TH1F*)f2->Get("h_mj1_mj2_bb");
    TH1F *h_y23_ww = (TH1F*)f2->Get("h_y23_bb");
    TH1F *h_d23_ww = (TH1F*)f2->Get("h_d23_bb");
    TH1F *h_costheta_th_vs_lab_ww = (TH1F*)f2->Get("h_costheta_th_vs_lab_bb");
    TH1F *h_costheta_ww = (TH1F*)f2->Get("h_costheta_bb");
    TH1F *h_K_ww = (TH1F*)f2->Get("h_K_bb");

    float luminosity_ww = h_luminosity_cross_ww->GetEntries()/cross_section[polarisation][2];

    h_mjj_ww->Scale(luminosity/luminosity_ww);
    h_mj1_mj2_ww->Scale(luminosity/luminosity_ww);
    h_y23_ww->Scale(luminosity/luminosity_ww);
    h_d23_ww->Scale(luminosity/luminosity_ww);
    h_costheta_th_vs_lab_ww->Scale(luminosity/luminosity_ww);
    h_costheta_ww->Scale(luminosity/luminosity_ww);
    h_K_ww->Scale(luminosity/luminosity_ww);
  
    //**********************************************************
    // qqH
    filename = folder+"qqH_"+pol+"_250GeV.root";
    TFile *f3 = new TFile(filename);
    TH1F *h_luminosity_cross_qqH = (TH1F*)f3->Get("h_costheta_nocuts");
    TH1F *h_mjj_qqH = (TH1F*)f3->Get("h_mjj_bb");
    TH1F *h_mj1_mj2_qqH = (TH1F*)f3->Get("h_mj1_mj2_bb");
    TH1F *h_y23_qqH = (TH1F*)f3->Get("h_y23_bb");
    TH1F *h_d23_qqH = (TH1F*)f3->Get("h_d23_bb");
    TH1F *h_costheta_th_vs_lab_qqH = (TH1F*)f3->Get("h_costheta_th_vs_lab_bb");
    TH1F *h_costheta_qqH = (TH1F*)f3->Get("h_costheta_bb");
    TH1F *h_K_qqH = (TH1F*)f3->Get("h_K_bb");

    float luminosity_qqH = h_luminosity_cross_qqH->GetEntries()/cross_section[polarisation][1];

    h_mjj_qqH->Scale(luminosity/luminosity_qqH);
    h_mj1_mj2_qqH->Scale(luminosity/luminosity_qqH);
    h_y23_qqH->Scale(luminosity/luminosity_qqH);
    h_d23_qqH->Scale(luminosity/luminosity_qqH);
    h_costheta_th_vs_lab_qqH->Scale(luminosity/luminosity_qqH);
    h_costheta_qqH->Scale(luminosity/luminosity_qqH);
    h_K_qqH->Scale(luminosity/luminosity_qqH);
  

    //**********************************************************
    // ZZ
    filename = folder+"4f_ZZ_hadronic_"+pol+"_250GeV.root";
    TFile *f4 = new TFile(filename);
    TH1F *h_luminosity_cross_zz = (TH1F*)f4->Get("h_costheta_nocuts");
    TH1F *h_mjj_zz = (TH1F*)f4->Get("h_mjj_bb");
    TH1F *h_mj1_mj2_zz = (TH1F*)f4->Get("h_mj1_mj2_bb");
    TH1F *h_y23_zz = (TH1F*)f4->Get("h_y23_bb");
    TH1F *h_d23_zz = (TH1F*)f4->Get("h_d23_bb");
    TH1F *h_costheta_th_vs_lab_zz = (TH1F*)f4->Get("h_costheta_th_vs_lab_bb");
    TH1F *h_costheta_zz = (TH1F*)f4->Get("h_costheta_bb");
    TH1F *h_K_zz = (TH1F*)f4->Get("h_K_bb");

    float luminosity_zz = h_luminosity_cross_zz->GetEntries()/cross_section[polarisation][0];

    h_mjj_zz->Scale(luminosity/luminosity_zz);
    h_mj1_mj2_zz->Scale(luminosity/luminosity_zz);
    h_y23_zz->Scale(luminosity/luminosity_zz);
    h_d23_zz->Scale(luminosity/luminosity_zz);
    h_costheta_th_vs_lab_zz->Scale(luminosity/luminosity_zz);
    h_costheta_zz->Scale(luminosity/luminosity_zz);
    h_K_zz->Scale(luminosity/luminosity_zz);
 

 
    //Efficiency 
    bb_integral[i+1]=h_mjj_bb->Integral();
    qq_integral[i+1]=h_mjj_qq->Integral();
    cc_integral[i+1]=h_mjj_cc->Integral();
    radreturn_integral[i+1]=h_mjj_radreturn->Integral();
    zz_integral[i+1]=h_mjj_zz->Integral();
    qqH_integral[i+1]=h_mjj_qqH->Integral();
    ww_integral[i+1]=h_mjj_ww->Integral();

    if(i==0) {
      bb_integral[i]=h_mjj_bb->Integral();
      qq_integral[i]=h_mjj_qq->Integral();
      cc_integral[i]=h_mjj_cc->Integral();
      radreturn_integral[i]=h_mjj_radreturn->Integral();
      zz_integral[i]=h_mjj_zz->Integral();
      qqH_integral[i]=h_mjj_qqH->Integral();
      ww_integral[i]=h_mjj_ww->Integral();
    }
  
 
    h_y23_bb->Rebin(100);
    h_y23_cc->Rebin(100);
    h_y23_qq->Rebin(100);
    h_y23_radreturn->Rebin(100);
    h_y23_zz->Rebin(100);
    h_y23_qqH->Rebin(100);
    h_y23_ww->Rebin(100); 

    h_d23_bb->Rebin(100);
    h_d23_cc->Rebin(100);
    h_d23_qq->Rebin(100);
    h_d23_radreturn->Rebin(100);
    h_d23_zz->Rebin(100);
    h_d23_qqH->Rebin(100);
    h_d23_ww->Rebin(100);

    h_K_bb->Rebin(10);
    h_K_cc->Rebin(10);
    h_K_qq->Rebin(10);
    h_K_radreturn->Rebin(10);
    h_K_zz->Rebin(10);
    h_K_qqH->Rebin(10);
    h_K_ww->Rebin(10);


    TString cut_string= "";//Nocuts";
    /*  if(cuts==1) cut_string="$K_{reco}<35\\,GeV$";
	if(cuts==2) cut_string="$+ m_{j_{1},j_{2}}>130 \\,GeV$";
	if(cuts==3) cut_string="$+ E^{max}_{nPFO}<100 \\,GeV$";
	if(cuts==4) cut_string="$+ |cos(\\theta_{E^{max}_{nPFO}})|<0.95$";
	if(cuts==5) cut_string="mjets<90GeV";
	if(cuts==6) cut_string="$+ Thrust > 0.9$";
	if(cuts==11) cut_string="$>1\\,b-jet tagged$";
	if(cuts==12) cut_string="$2\\,b-jet tagged$";
	if(cuts==13) cut_string="$>1\\,b-jet tagged$";
	if(cuts==14) cut_string="$2\\,b-jet tagged$";*/


    // cout<<std::setprecision(3)<< cut_string<<" & "<< 100.*bb_integral[i+1]/bb_integral[0]<<"\\% & "<<100.*cc_integral[i+1]/cc_integral[0]<<"\\% & "<<100.*qq_integral[i+1]/qq_integral[0]<<"\\% & "<<100.*radreturn_integral[i+1]/radreturn_integral[0]<<"\\% & "<< 100.*qqH_integral[i+1]/qqH_integral[0]<<"\\% & "<< 100.*zz_integral[i+1]/zz_integral[0]<<"\\% & "<< 100.*ww_integral[i+1]/ww_integral[0]<<" \\\\"<<endl;

    cout<<std::setprecision(3)<< cut_string<<" & bb:"<< 100.*bb_integral[i+1]/bb_integral[0]<<"\\% & cc:"<<100.*cc_integral[i+1]/cc_integral[0]<<"\\% & qq:"<<100.*qq_integral[i+1]/qq_integral[0]<<"\\% & rad:"<<100.*radreturn_integral[i+1]/radreturn_integral[0]<<"\\% & WW:"<<100.*ww_integral[i+1]/ww_integral[0]<<"\\% &  ZZ:"<<100.*zz_integral[i+1]/zz_integral[0]<<"\\% & qqH:"<<100.*qqH_integral[i+1]/qqH_integral[0]<<"\\% & \\\\"<<endl;
  
    SetQQbarStyle();
    gStyle->SetOptFit(0); 
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
  
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetTitleX(0.2);
    gStyle->SetMarkerSize(1.5);

    TCanvas * canvas = new TCanvas("canvas_y23","canvas_y23",1800,800);
    canvas->Divide(3,2);
    canvas->cd(1);
    gPad->SetLogy();
    
    if(normalised==true) h_y23_bb->GetYaxis()->SetTitle("norm to 1");
    else h_y23_bb->GetYaxis()->SetTitle("Entries");
    h_y23_bb->GetXaxis()->SetTitle("y_{23}");
    h_y23_bb->GetYaxis()->SetRangeUser(10,h_y23_bb->GetMaximum()*10);
    h_y23_bb->GetXaxis()->SetRangeUser(0,0.1);
   
    h_y23_bb->SetLineColor(4);
    h_y23_qq->SetLineColor(1);
    h_y23_cc->SetLineStyle(2);
    h_y23_radreturn->SetLineColor(2);
    h_y23_ww->SetLineColor(5);
    h_y23_zz->SetLineColor(6);
    h_y23_qqH->SetLineColor(7);

    if(normalised==true) {
      h_y23_bb->DrawNormalized("histo");
      h_y23_qq->DrawNormalized("histosame");
      h_y23_cc->DrawNormalized("histosame");
      h_y23_radreturn->DrawNormalized("histosame");
      h_y23_ww->DrawNormalized("histosame");
      h_y23_zz->DrawNormalized("histosame");
      h_y23_qqH->DrawNormalized("histosame");
    } else {
      h_y23_bb->Draw("histo");
      h_y23_qq->Draw("histosame");
      h_y23_cc->Draw("histosame");
      h_y23_radreturn->Draw("histosame");
      h_y23_ww->Draw("histosame");
      h_y23_zz->Draw("histosame");
      h_y23_qqH->Draw("histosame");
    }
    Labels(i,pol);
  
    TLegend *leg1 = new TLegend(0.3,0.78,0.5,0.9);//(0.4,0.3,0.5,0.6);
    leg1->SetTextSize(0.035);
    leg1->AddEntry(h_y23_bb,"#font[42]{b#bar{b}}","l");
    leg1->AddEntry(h_y23_cc,"#font[42]{c#bar{c}}","l");
    leg1->AddEntry(h_y23_qq,"#font[42]{q#bar{q} (q=uds)}","l");
    leg1->SetFillStyle(0);
    leg1->SetLineWidth(0);
    leg1->SetLineColor(0);
    leg1->SetBorderSize(0);
    leg1->Draw();

    TLegend *leg2 = new TLegend(0.57,0.76,0.85,0.9);//(0.4,0.3,0.5,0.6);
    leg2->SetTextSize(0.035);
    leg2->AddEntry(h_y23_radreturn,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    leg2->AddEntry(h_y23_qqH,"#font[42]{qqH}","l");
    leg2->AddEntry(h_y23_zz,"#font[42]{ZZ}","l");
    leg2->AddEntry(h_y23_ww,"#font[42]{WW}","l");
    leg2->SetFillStyle(0);
    leg2->SetLineWidth(0);
    leg2->SetLineColor(0);
    leg2->SetBorderSize(0);
    leg2->Draw();

    canvas->cd(2);
    gPad->SetLogy();
    
    if(normalised==true) h_d23_bb->GetYaxis()->SetTitle("norm to 1");
    else h_d23_bb->GetYaxis()->SetTitle("Entries");  
    h_d23_bb->GetXaxis()->SetTitle("d_{23}");
    h_d23_bb->GetYaxis()->SetRangeUser(10,h_d23_bb->GetMaximum()*2);
    //  h_d23_bb->GetYaxis()->SetRangeUser(0,h_d23_bb->GetMaximum()*10);
    h_d23_bb->GetXaxis()->SetRangeUser(0,150);
    h_d23_bb->SetLineColor(4);
    h_d23_qq->SetLineColor(1);
    h_d23_cc->SetLineStyle(2);
    h_d23_radreturn->SetLineColor(2);
    h_d23_ww->SetLineColor(5);
    h_d23_zz->SetLineColor(6);
    h_d23_qqH->SetLineColor(7);

    if(normalised==true) {
      h_d23_bb->DrawNormalized("histo");
      h_d23_qq->DrawNormalized("histosame");
      h_d23_cc->DrawNormalized("histosame");
      h_d23_radreturn->DrawNormalized("histosame");
      h_d23_ww->DrawNormalized("histosame");
      h_d23_zz->DrawNormalized("histosame");
      h_d23_qqH->DrawNormalized("histosame");
    } else {
      h_d23_bb->Draw("histo");
      h_d23_qq->Draw("histosame");
      h_d23_cc->Draw("histosame");
      h_d23_radreturn->Draw("histosame");
      h_d23_ww->Draw("histosame");
      h_d23_zz->Draw("histosame");
      h_d23_qqH->Draw("histosame");
    }


    canvas->cd(3);
    
    if(normalised==true) h_costheta_th_vs_lab_bb->GetYaxis()->SetTitle("norm to 1");
    else h_costheta_th_vs_lab_bb->GetYaxis()->SetTitle("Entries"); 
    h_costheta_th_vs_lab_bb->GetXaxis()->SetTitle("|cos #theta_{T}| - |cos #theta_{lab}|");
    // h_costheta_th_vs_lab_bb->GetYaxis()->SetRangeUser(10,h_costheta_th_vs_lab_bb->GetMaximum()*10);
    h_costheta_th_vs_lab_bb->SetLineColor(4);
    h_costheta_th_vs_lab_qq->SetLineColor(1);
    h_costheta_th_vs_lab_cc->SetLineStyle(2);
    h_costheta_th_vs_lab_radreturn->SetLineColor(2);
    h_costheta_th_vs_lab_ww->SetLineColor(5);
    h_costheta_th_vs_lab_zz->SetLineColor(6);
    h_costheta_th_vs_lab_qqH->SetLineColor(7);

    if(normalised==true) {
      h_costheta_th_vs_lab_bb->DrawNormalized("histo");
      h_costheta_th_vs_lab_qq->DrawNormalized("histosame");
      h_costheta_th_vs_lab_cc->DrawNormalized("histosame");
      h_costheta_th_vs_lab_radreturn->DrawNormalized("histosame");
      h_costheta_th_vs_lab_ww->DrawNormalized("histosame");
      h_costheta_th_vs_lab_zz->DrawNormalized("histosame");
      h_costheta_th_vs_lab_qqH->DrawNormalized("histosame");
    } else {
      h_costheta_th_vs_lab_bb->Draw("histo");
      h_costheta_th_vs_lab_qq->Draw("histosame");
      h_costheta_th_vs_lab_cc->Draw("histosame");
      h_costheta_th_vs_lab_radreturn->Draw("histosame");
      h_costheta_th_vs_lab_ww->Draw("histosame");
      h_costheta_th_vs_lab_zz->Draw("histosame");
      h_costheta_th_vs_lab_qqH->Draw("histosame");
    }

  
    canvas->cd(4);
    // gPad->SetLogy();
    
    if(normalised==true) h_K_bb->GetYaxis()->SetTitle("norm to 1");
    else h_K_bb->GetYaxis()->SetTitle("Entries"); 
    h_K_bb->GetXaxis()->SetTitle("K_{reco} [GeV]");
    h_K_bb->GetYaxis()->SetRangeUser(10,h_K_bb->GetMaximum()*10);
    //  h_K_bb->GetYaxis()->SetRangeUser(0,h_K_bb->GetMaximum()*10);
    h_K_bb->SetLineColor(4);
    h_K_qq->SetLineColor(1);
    h_K_cc->SetLineStyle(2);
    h_K_radreturn->SetLineColor(2);
    h_K_ww->SetLineColor(5);
    h_K_zz->SetLineColor(6);
    h_K_qqH->SetLineColor(7);

    if(normalised==true) {
      h_K_bb->DrawNormalized("histo");
      h_K_qq->DrawNormalized("histosame");
      h_K_cc->DrawNormalized("histosame");
      h_K_radreturn->DrawNormalized("histosame");
      h_K_ww->DrawNormalized("histosame");
      h_K_zz->DrawNormalized("histosame");
      h_K_qqH->DrawNormalized("histosame");
    } else {
      h_K_bb->Draw("histo");
      h_K_qq->Draw("histosame");
      h_K_cc->Draw("histosame");
      h_K_radreturn->Draw("histosame");
      h_K_ww->Draw("histosame");
      h_K_zz->Draw("histosame");
      h_K_qqH->Draw("histosame");
    }

  
    canvas->cd(5);
    //  gPad->SetLogy();
    if(normalised==true) h_mjj_bb->GetYaxis()->SetTitle("norm to 1");
    else h_mjj_bb->GetYaxis()->SetTitle("Entries"); 
    h_mjj_bb->GetXaxis()->SetTitle("m_{j_{1},j_{2}} [GeV]");
    h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*2);
    //  h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*10);
    //  h_mjj_bb->GetXaxis()->SetRangeUser(0,0.11);
    h_mjj_bb->SetLineColor(4);
    h_mjj_qq->SetLineColor(1);
    h_mjj_cc->SetLineStyle(2);
    h_mjj_radreturn->SetLineColor(2);
    h_mjj_ww->SetLineColor(5);
    h_mjj_zz->SetLineColor(6);
    h_mjj_qqH->SetLineColor(7);

    if(normalised==true) {
      h_mjj_bb->DrawNormalized("histo");
      h_mjj_qq->DrawNormalized("histosame");
      h_mjj_cc->DrawNormalized("histosame");
      h_mjj_radreturn->DrawNormalized("histosame");
      h_mjj_ww->DrawNormalized("histosame");
      h_mjj_zz->DrawNormalized("histosame");
      h_mjj_qqH->DrawNormalized("histosame");
    } else {
      h_mjj_bb->Draw("histo");
      h_mjj_qq->Draw("histosame");
      h_mjj_cc->Draw("histosame");
      h_mjj_radreturn->Draw("histosame");
      h_mjj_ww->Draw("histosame");
      h_mjj_zz->Draw("histosame");
      h_mjj_qqH->Draw("histosame");
    }

  
    canvas->cd(6);
    //  gPad->SetLogy();
    if(normalised==true) h_mj1_mj2_bb->GetYaxis()->SetTitle("norm to 1");
    else h_mj1_mj2_bb->GetYaxis()->SetTitle("Entries"); 
    h_mj1_mj2_bb->GetXaxis()->SetTitle("m_{j_{1}}+m_{j_{2}} [GeV]");
    h_mj1_mj2_bb->GetYaxis()->SetRangeUser(0,h_mj1_mj2_bb->GetMaximum()*2);
    h_mj1_mj2_bb->GetXaxis()->SetRangeUser(0,200);
    h_mj1_mj2_bb->SetLineColor(4);
    h_mj1_mj2_qq->SetLineColor(1);
    h_mj1_mj2_cc->SetLineStyle(2);
    h_mj1_mj2_radreturn->SetLineColor(2);
    h_mj1_mj2_ww->SetLineColor(5);
    h_mj1_mj2_zz->SetLineColor(6);
    h_mj1_mj2_qqH->SetLineColor(7);

    if(normalised==true) {
      h_mj1_mj2_bb->DrawNormalized("histo");
      h_mj1_mj2_qq->DrawNormalized("histosame");
      h_mj1_mj2_cc->DrawNormalized("histosame");
      h_mj1_mj2_radreturn->DrawNormalized("histosame");
      h_mj1_mj2_ww->DrawNormalized("histosame");
      h_mj1_mj2_zz->DrawNormalized("histosame");
      h_mj1_mj2_qqH->DrawNormalized("histosame");
    } else {
      h_mj1_mj2_bb->Draw("histo");
      h_mj1_mj2_qq->Draw("histosame");
      h_mj1_mj2_cc->Draw("histosame");
      h_mj1_mj2_radreturn->Draw("histosame");
      h_mj1_mj2_ww->Draw("histosame");
      h_mj1_mj2_zz->Draw("histosame");
      h_mj1_mj2_qqH->Draw("histosame");
    }
  
  

  }

}
