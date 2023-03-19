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

TString energy="250GeV";
  
TH1F *average (TH1F* h1, TH1F* h2, TH1F* h3, TString title="") {

  TH1F* result= new TH1F("average",title,40,-1,1);
  
  for(int i=0; i<40; i++) {
    
    double w1=h1->GetBinError(i+1);
    double w2=h2->GetBinError(i+1);
    double w3=h3->GetBinError(i+1);

    double y1=h1->GetBinContent(i+1);
    double y2=h2->GetBinContent(i+1);
    double y3=h3->GetBinContent(i+1);
    
    double sumw = w1+w2+w3;
    
    double ynew= 0;
    double eynew= 0;

    if(sumw>0) {
      /*  ynew=(y1*w1+y2*w2+y3*w3) / sumw;
      eynew= w1*pow(y1-ynew,2)+w2*pow(y2-ynew,2)+w3*pow(y3-ynew,2);
      eynew/=sumw;*/

       ynew=(y1+y2+y3)/3.;
	    eynew=sqrt(pow(w1,2)+pow(w2,2)+pow(w3,2));

    }
    result->SetBinContent(i+1,ynew);
    result->SetBinError(i+1,eynew);
  }
  
  return result;
  
}


TH1F *Efficiency (TH1F* h1, TH1F* h2, TH1F* h3, TH1F* parton, TString title="") {

  TH1F *input = average(h1,h2,h3,title);
  input->Divide(parton);
  
  TF1* func = new TF1("func","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",-0.05,0.9);
  input->Fit(func,"MER");
  float a=func->GetParameter(0);
  float b=func->GetParameter(1);
  float c=func->GetParameter(2);
  float d=func->GetParameter(3);
  float e=func->GetParameter(4);
  float f=func->GetParameter(5);

  
  TH1F* result= new TH1F("efficiency",title,40,-1,1);

  for(int j=20; j<40; j++) {
    int abs_value_costheta_bin = int(fabs(h1->GetBinCenter(j+1)*100./5));
    float x=h1->GetBinCenter(j+1);
    float eff_pres_=a+x*b+x*x*c+x*x*x*d+x*x*x*x*e+x*x*x*x*x*f;
    result->SetBinContent(j+1,eff_pres_);
    result->SetBinContent(40-j+1,eff_pres_);
    result->SetBinError(40-j+1,0);
    result->SetBinError(j+1,0);

  }

  return result;
}



TH1F *Efficiency (TH1F* h1, TH1F* parton, TH1F* parton2, TString title="",int error=0) {

  TH1F* input=(TH1F*)h1->Clone("input");
  input->Divide(parton);

  TF1* func = new TF1("func","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",0,0.9);
  input->Fit(func,"MER");
  float a=func->GetParameter(0);
  float b=func->GetParameter(1);
  float c=func->GetParameter(2);
  float d=func->GetParameter(3);
  float e=func->GetParameter(4);
  float f=func->GetParameter(5);

  TF1* func2 = new TF1("func2","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",-0.9,0.0);
  input->Fit(func2,"MER");
  float a2=func2->GetParameter(0);
  float b2=func2->GetParameter(1);
  float c2=func2->GetParameter(2);
  float d2=func2->GetParameter(3);
  float e2=func2->GetParameter(4);
  float f2=func2->GetParameter(5);

  
  TH1F* result= new TH1F("efficiency",title,40,-1,1);
  
   // for(int j=20; j<40; j++) {
   //  int abs_value_costheta_bin = int(fabs(input->GetBinCenter(j+1)*100./5));
   //  float x=input->GetBinCenter(j+1);
   //  float eff_pres_=a+x*b+x*x*c+x*x*x*d+x*x*x*x*e+x*x*x*x*x*f;
   //  result->SetBinContent(j+1,eff_pres_);
   //  result->SetBinContent(40-j+1,eff_pres_);
   //  result->SetBinError(40-j+1,input->GetBinError(40-j+1));
   //  result->SetBinError(j+1,input->GetBinError(j+1));
   // }
  for(int j=0; j<40; j++) {
    float x=input->GetBinCenter(j+1);
    float eff_pres_plus=a+x*b+x*x*c+x*x*x*d+x*x*x*x*e+x*x*x*x*x*f;
    float eff_pres_minus=a2+x*b2+x*x*c2+x*x*x*d2+x*x*x*x*e2+x*x*x*x*x*f2;
    float eff_pres_=eff_pres_plus;
    if(x<0) eff_pres_=eff_pres_minus;
    if(error==0) {
      result->SetBinContent(j+1,input->GetBinContent(j+1));//eff_pres_);
      result->SetBinError(j+1,0);
    } else {
      result->SetBinContent(j+1,input->GetBinContent(j+1)+error*0.05*input->GetBinContent(j+1));//eff_pres_);
      result->SetBinError(j+1,input->GetBinError(j+1));
    }
    parton->SetBinError(j+1,0);
    parton2->SetBinError(j+1,0);
    
    //result->SetBinError(40-j+1,input->GetBinError(40-j+1));
    //    result->SetBinError(j+1,input->GetBinError(j+1));
   }
   result->SetBinContent(1,0);
   result->SetBinError(1,0);
   result->SetBinContent(2,0);
   result->SetBinError(2,0);
   result->SetBinContent(39,0);
   result->SetBinError(39,0);
   result->SetBinContent(40,0);
   result->SetBinError(40,0);

   
   parton->Divide(parton2);
   result->Multiply(parton);


  return result;
}


void Plots_AFB(int quark=4, int ipol=0, float lum=900, int cheatmethod=0) {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.8);
  TGaxis::SetMaxDigits(3);

  int iprocess=1; //cut in radiative return

  float luminosity[2]={0};
  TH1F *hstats[2];

  TString pol="eL_pR";
  TString filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
  TFile *f = new TFile(filename);
  hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[0]->Integral()>0) luminosity[0]=hstats[0]->Integral()/cross_section[0][iprocess];
  else luminosity[0]=0;
  
  TH1F* AFBparton_eL = (TH1F*)f->Get("h_AFB");
  TH1F* AFBparton2_eL = (TH1F*)f->Get("h_AFB2");
  TH1F* AFBcheat_eL= (TH1F*)f->Get("h_AFBcheat");
  TH1F* AFB_pqcorrectedreco_effcorr_0_eL= (TH1F*)f->Get("h_AFBreco_pqcorrectedreco_effcorrected_cat0_syst0");
  TH1F* AFB_pqcorrectedreco_effcorr_1_eL= (TH1F*)f->Get("h_AFBreco_pqcorrectedreco_effcorrected_cat1_syst0");
  TH1F* AFB_pqcorrectedreco_effcorr_2_eL= (TH1F*)f->Get("h_AFBreco_pqcorrectedreco_effcorrected_cat2_syst0");
  TH1F* AFB_pqcorrectedreco_effcorr_eL=average(AFB_pqcorrectedreco_effcorr_0_eL,AFB_pqcorrectedreco_effcorr_1_eL,AFB_pqcorrectedreco_effcorr_2_eL);
  TH1F* AFB_chargecheatreco_effcorr_0_eL= (TH1F*)f->Get("h_AFBreco_chargecheatreco_effcorrected_cat0_syst0");
  TH1F* AFB_chargecheatreco_effcorr_1_eL= (TH1F*)f->Get("h_AFBreco_chargecheatreco_effcorrected_cat1_syst0");
  TH1F* AFB_chargecheatreco_effcorr_2_eL= (TH1F*)f->Get("h_AFBreco_chargecheatreco_effcorrected_cat2_syst0");
  TH1F* AFB_chargecheatreco_effcorr_eL=average(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL);

  //TH1F* eff_eL=Efficiency(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL,AFBparton_eL);

  pol="eR_pL";
  filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
  f = new TFile(filename);
  hstats[1]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[1]->Integral()>0) luminosity[1]=hstats[1]->Integral()/cross_section[1][iprocess];
  else luminosity[1]=0;
  
  TH1F* AFBparton_eR = (TH1F*)f->Get("h_AFB");
  TH1F* AFBparton2_eR = (TH1F*)f->Get("h_AFB2");
  TH1F* AFBcheat_eR= (TH1F*)f->Get("h_AFBcheat");
  TH1F* AFB_pqcorrectedreco_effcorr_0_eR= (TH1F*)f->Get("h_AFBreco_pqcorrectedreco_effcorrected_cat0_syst0");
  TH1F* AFB_pqcorrectedreco_effcorr_1_eR= (TH1F*)f->Get("h_AFBreco_pqcorrectedreco_effcorrected_cat1_syst0");
  TH1F* AFB_pqcorrectedreco_effcorr_2_eR= (TH1F*)f->Get("h_AFBreco_pqcorrectedreco_effcorrected_cat2_syst0");
  TH1F* AFB_pqcorrectedreco_effcorr_eR=average(AFB_pqcorrectedreco_effcorr_0_eR,AFB_pqcorrectedreco_effcorr_1_eR,AFB_pqcorrectedreco_effcorr_2_eR);
  TH1F* AFB_chargecheatreco_effcorr_0_eR= (TH1F*)f->Get("h_AFBreco_chargecheatreco_effcorrected_cat0_syst0");
  TH1F* AFB_chargecheatreco_effcorr_1_eR= (TH1F*)f->Get("h_AFBreco_chargecheatreco_effcorrected_cat1_syst0");
  TH1F* AFB_chargecheatreco_effcorr_2_eR= (TH1F*)f->Get("h_AFBreco_chargecheatreco_effcorrected_cat2_syst0");
  TH1F* AFB_chargecheatreco_effcorr_eR=average(AFB_chargecheatreco_effcorr_0_eR,AFB_chargecheatreco_effcorr_1_eR,AFB_chargecheatreco_effcorr_2_eR);

  //**********************Pol Histos
  TH1F * AFBparton=PolHisto(AFBparton_eL,AFBparton_eR,ipol,luminosity,lum,1);
  TH1F * AFBparton2=PolHisto(AFBparton2_eL,AFBparton2_eR,ipol,luminosity,lum,1);
  TH1F * AFBcheat=PolHisto(AFB_chargecheatreco_effcorr_eL,AFB_chargecheatreco_effcorr_eR,ipol,luminosity,lum,1);
  TH1F * AFBcorrected=PolHisto(AFB_pqcorrectedreco_effcorr_eL,AFB_pqcorrectedreco_effcorr_eR,ipol,luminosity,lum,1);
  TH1F* eff=Efficiency(AFBcheat,AFBparton,AFBparton2);
  AFBcorrected->Divide(eff);
  
  //***** DRAW
  TF1 *func_parton=fit_histo(AFBparton2, -1,1,false);
  TF1 *func_corrected=fit_histo(AFBcorrected, -0.9,0.9,false);

  TH1F *hparton=new TH1F("hparton","hparton",40,-1,1);
  hparton->Add(func_parton);
  TH1F *hcorrected=new TH1F("hcorrected","hcorrected",40,-1,1);
  hcorrected->Add(func_corrected);
  
  TCanvas* c_AFBb = new TCanvas(TString::Format("c_AFB_%i_%i",quark,ipol),TString::Format("c_AFB_%i_%i",quark,ipol),800,800);
  c_AFBb->cd(1);
  // gPad->SetLogy();
  func_parton->GetXaxis()->SetTitle("cos #theta");
  func_parton->GetYaxis()->SetTitle("entries");
  func_parton->GetYaxis()->SetRangeUser(0,func_parton->GetMaximum());
  func_parton->SetLineColor(kGreen+2);
  func_parton->SetLineWidth(4);
  func_parton->SetLineStyle(1);
  func_parton->Draw("l");
  
  AFBcorrected->SetLineColor(2);
  AFBcorrected->SetLineWidth(2);
  AFBcorrected->SetLineStyle(1);
  AFBcorrected->SetMarkerColor(2);
  AFBcorrected->SetMarkerStyle(20);
  AFBcorrected->Draw("esame");
  
  func_corrected->SetLineColor(2);
  func_corrected->SetLineWidth(2);
  func_corrected->SetLineStyle(2);
  func_corrected->Draw("lsame");
  //eff->Draw("histo");

  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  Labels(ipol,quark,900,960);

  float plus = func_parton->Integral(0,1);
  float minus = func_parton->Integral(-1,0);
  float plus_e = func_parton->IntegralError(0,1);
  float minus_e = func_parton->IntegralError(1,0);
  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);

  float plus_corrected = func_corrected->Integral(0,1);
  float minus_corrected = func_corrected->Integral(-1,0);
  float plus_e_corrected = func_corrected->IntegralError(0,1);
  float minus_e_corrected = func_corrected->IntegralError(1,0);
  float Afb_corrected=Afb_v(plus_corrected,minus_corrected);
  float dAfb_corrected=dAfb_v(plus_corrected,minus_corrected, plus_e_corrected, minus_e_corrected);

  
  float ratio=100.*(1-(1-Afb_corrected/Afb)/2.);
  float eratio=100.*sqrt(pow(dAfb_corrected,2))/Afb;
  QQBARLabel2(0.55,0.32, TString::Format("#frac{AFB^{fit}_{reco}}{AFB^{fit}_{LO}}=%.1f#pm %.1f (stat.)",ratio,eratio)+"%",kGray+2);

  float plus2 = AFBcorrected->Integral(21,41);
  cout<<plus2<<endl;
  float minus2 = AFBcorrected->Integral(1,20);
  cout<<minus2<<endl;
  float plus2_e = sqrt(plus2);
  float minus2_e = sqrt(minus2);
  float Afb2=Afb_v(plus2,minus2);
  float dAfb2=dAfb_v(plus2,minus2, plus2_e, minus2_e);

  float plus_corrected2 = func_corrected->Integral(0,0.9);
  float minus_corrected2 = func_corrected->Integral(-0.9,0);
  float plus_e_corrected2 = func_corrected->IntegralError(0,0.9);
  float minus_e_corrected2 = func_corrected->IntegralError(0.9,0);
  float Afb_corrected2=Afb_v(plus_corrected2,minus_corrected2);
  float dAfb_corrected2=dAfb_v(plus_corrected2,minus_corrected2, plus_e_corrected2, minus_e_corrected2);

  float ratio2=100.*(1-(1-Afb_corrected2/Afb2)/2.);
  float eratio2=100.*sqrt(pow(dAfb_corrected2,2))/Afb2;
  QQBARLabel2(0.55,0.22, TString::Format("#frac{AFB^{fid.}_{reco}}{AFB^{fid.}_{LO}}=%.1f#pm %.1f (stat.)",ratio2,eratio2)+"%",kGray+2);

  // TString pol_string1 = "e_{L}^{-}e_{R}^{+}";
  // TString pol_string2 = "e_{R}^{-}e_{L}^{+}";

  // TString string1 = "";
  // TString string2 = "";

  // if(mode==1) {
  //   pol_string1 = "e^{-}e^{+}";
  //   pol_string2 = "e^{-}e^{+}";
  //   string1 = ", P_{e^{-}e^{+}}=(-0.8,+0.3)";
  //   string2 = ", P_{e^{-}e^{+}}=(+0.8,-0.3)";
  // }
  
  TLegend *leg_b = new TLegend(0.2,0.65,0.5,0.85);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(func_parton,"Whizard 2.8.5 LO","l");
  leg_b->AddEntry(AFBcorrected,"Reconstructed and corrected","pel");
  leg_b->AddEntry(func_corrected,"fit to reconstructed","l");
  //  leg_b->AddEntry(AFBcheat,"CheatCharge","lf");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_AFBb->Print(TString::Format("plots_"+energy+"_AFB/Fit_pdg_%i_pol_%i.eps",quark,ipol));

  
  
}

void AFBSyst(int quark=4, int ipol=0, float lum=900, int cheatmethod=0) {

  float Afb_corrected[100]={0};
  float dAfb_corrected[100]={0};

  for(int syst_=0; syst_<23; syst_++) {
  int iprocess=1; //cut in radiative return

  int syst=syst_;
  if(syst_==22) syst=21;
  float luminosity[2]={0};
  TH1F *hstats[2];

  TString pol="eL_pR";
  TString filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
  TFile *f = new TFile(filename);
  hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[0]->Integral()>0) luminosity[0]=hstats[0]->Integral()/cross_section[0][iprocess];
  else luminosity[0]=0;
  
  TH1F* AFBparton_eL = (TH1F*)f->Get("h_AFB");
  TH1F* AFBparton2_eL = (TH1F*)f->Get("h_AFB2");
  TH1F* AFBcheat_eL= (TH1F*)f->Get("h_AFBcheat");
  TH1F* AFB_pqcorrectedreco_effcorr_0_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat0_syst%i",syst));
  TH1F* AFB_pqcorrectedreco_effcorr_1_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat1_syst%i",syst));
  TH1F* AFB_pqcorrectedreco_effcorr_2_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat2_syst%i",syst));
  TH1F* AFB_pqcorrectedreco_effcorr_eL=average(AFB_pqcorrectedreco_effcorr_0_eL,AFB_pqcorrectedreco_effcorr_1_eL,AFB_pqcorrectedreco_effcorr_2_eL);
  TH1F* AFB_chargecheatreco_effcorr_0_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat0_syst%i",0));
  TH1F* AFB_chargecheatreco_effcorr_1_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat1_syst%i",0));
  TH1F* AFB_chargecheatreco_effcorr_2_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat2_syst%i",0));
  TH1F* AFB_chargecheatreco_effcorr_eL=average(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL);

  //TH1F* eff_eL=Efficiency(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL,AFBparton_eL);

  pol="eR_pL";
  filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
  f = new TFile(filename);
  hstats[1]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[1]->Integral()>0) luminosity[1]=hstats[1]->Integral()/cross_section[1][iprocess];
  else luminosity[1]=0;
  
  TH1F* AFBparton_eR = (TH1F*)f->Get("h_AFB");
  TH1F* AFBparton2_eR = (TH1F*)f->Get("h_AFB2");
  TH1F* AFBcheat_eR= (TH1F*)f->Get("h_AFBcheat");
  TH1F* AFB_pqcorrectedreco_effcorr_0_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat0_syst%i",syst));
  TH1F* AFB_pqcorrectedreco_effcorr_1_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat1_syst%i",syst));
  TH1F* AFB_pqcorrectedreco_effcorr_2_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat2_syst%i",syst));
  TH1F* AFB_pqcorrectedreco_effcorr_eR=average(AFB_pqcorrectedreco_effcorr_0_eR,AFB_pqcorrectedreco_effcorr_1_eR,AFB_pqcorrectedreco_effcorr_2_eR);
  TH1F* AFB_chargecheatreco_effcorr_0_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat0_syst%i",0));
  TH1F* AFB_chargecheatreco_effcorr_1_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat1_syst%i",0));
  TH1F* AFB_chargecheatreco_effcorr_2_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat2_syst%i",0));
  TH1F* AFB_chargecheatreco_effcorr_eR=average(AFB_chargecheatreco_effcorr_0_eR,AFB_chargecheatreco_effcorr_1_eR,AFB_chargecheatreco_effcorr_2_eR);

  //**********************Pol Histos
  if(syst>20) lum=2000;
  TH1F * AFBparton=PolHisto(AFBparton_eL,AFBparton_eR,ipol,luminosity,lum,1);
  TH1F * AFBparton2=PolHisto(AFBparton2_eL,AFBparton2_eR,ipol,luminosity,lum,1);
  TH1F * AFBcheat=PolHisto(AFB_chargecheatreco_effcorr_eL,AFB_chargecheatreco_effcorr_eR,ipol,luminosity,lum,1);
  TH1F * AFBcorrected=PolHisto(AFB_pqcorrectedreco_effcorr_eL,AFB_pqcorrectedreco_effcorr_eR,ipol,luminosity,lum,1);
  float error=0;
  if(syst==21 && syst_==22) error=-1;
  if(syst==21 && syst_==21) error=1;
  
  TH1F* eff=Efficiency(AFBcheat,AFBparton,AFBparton2,"",error);
  if(syst==0)  eff=Efficiency(AFBcheat,AFBparton,AFBparton2);
  AFBcorrected->Divide(eff);
  
  //***** DRAW
  TF1 *func_parton=fit_histo(AFBparton2, -1,1,false);
  TF1 *func_corrected=fit_histo(AFBcorrected, -0.9,0.9,false);

  float plus_corrected = func_corrected->Integral(0,0.9);
  float minus_corrected = func_corrected->Integral(-0.9,0);
  float plus_e_corrected = func_corrected->IntegralError(0,0.9);
  float minus_e_corrected = func_corrected->IntegralError(-0.9,0);
  Afb_corrected[syst_]=Afb_v(plus_corrected,minus_corrected);
  dAfb_corrected[syst_]=dAfb_v(plus_corrected,minus_corrected, plus_e_corrected, minus_e_corrected);

  }

  for(int syst=0; syst<23; syst++)  std::cout<<setprecision(7)<<"PDG: "<<quark<<" polarisation:"<<ipol<<" Syst:"<<syst<<"  --> AFB:"<<Afb_corrected[syst]<<" Rel_Error:"<<100.*dAfb_corrected[syst]/Afb_corrected[syst]<<"%"<<endl;

}



void AFBPol(int quark=4, int ipol=0, float lum=900, int cheatmethod=0) {

  float Afb_parton[100]={0};
  float dAfb_parton[100]={0};
  float eel=0;
  float epos=0;
  
  if(ipol==2) {
    eel=0.001;
    epos=0.001;
  }
  if(ipol==3) {
    eel=0.001;
    epos=0.0014;
  }

  int syst=0;
  for(int i=-1; i<2; i+=2) {
    for(int j=-1; j<2; j+=2) {
      p1error=eel*i;
      p2error=epos*j;

      int iprocess=1; //cut in radiative return

  float luminosity[2]={0};
  TH1F *hstats[2];

  TString pol="eL_pR";
  TString filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
  TFile *f = new TFile(filename);
  hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[0]->Integral()>0) luminosity[0]=hstats[0]->Integral()/cross_section[0][iprocess];
  else luminosity[0]=0;
  
  TH1F* AFBparton2_eL = (TH1F*)f->Get("h_AFB2");
  //TH1F* eff_eL=Efficiency(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL,AFBparton_eL);

pol="eR_pL";
  filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
  f = new TFile(filename);
  hstats[1]=(TH1F*)f->Get("h_Ntotal_nocuts");
  if(hstats[1]->Integral()>0) luminosity[1]=hstats[1]->Integral()/cross_section[1][iprocess];
  else luminosity[1]=0;
  
  TH1F* AFBparton2_eR = (TH1F*)f->Get("h_AFB2");

  //**********************Pol Histos
  TH1F * AFBparton2=PolHisto(AFBparton2_eL,AFBparton2_eR,ipol,luminosity,lum,1);  
  //***** DRAW
  TF1 *func_parton=fit_histo(AFBparton2, -1,1,false);
  float plus_parton = func_parton->Integral(0,1);
  float minus_parton = func_parton->Integral(-1,0);
  float plus_e_parton = func_parton->IntegralError(0,1);
  float minus_e_parton = func_parton->IntegralError(1,0);
  Afb_parton[syst]=Afb_v(plus_parton,minus_parton);
  dAfb_parton[syst]=dAfb_v(plus_parton,minus_parton, plus_e_parton, minus_e_parton);

  syst++;

  }
  }

    for(int isyst=0; isyst<syst; isyst++)  std::cout<<setprecision(7)<<"PDG: "<<quark<<" polarisation:"<<ipol<<" Syst:"<<syst<<"  --> AFB:"<<Afb_parton[isyst]<<" Rel_Error:"<<100.*dAfb_parton[isyst]/Afb_parton[isyst]<<"%"<<endl;

}


  void AFBFit() {
    Plots_AFB(4,2,900);
    //Plots_AFB(4,3,900);
    //Plots_AFB(5,2,900);
    //Plots_AFB(5,3,900);

    //    AFBSyst(4,2,900,1);
    //    AFBPol(4,3,900,1);

  }
    
