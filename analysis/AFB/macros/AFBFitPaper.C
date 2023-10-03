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

TString energy="250GeV_dNdx";
  
TH1F *average (TH1F* h1, TH1F* h2, TH1F* h3, TString title="") {

  TH1F* result= new TH1F("average",title,40,-1,1);
  
  for(int i=0; i<40; i++) {
    
    double w1=1./h1->GetBinError(i+1);
    double w2=1./h2->GetBinError(i+1);
    double w3=1./h3->GetBinError(i+1);

    double y1=h1->GetBinContent(i+1);
    double y2=h2->GetBinContent(i+1);
    double y3=h3->GetBinContent(i+1);
    
    double sumw = w1+w2+w3;
    double sumw2 = w2+w3;
    double ynew= 0;
    double eynew= 0;
    
    if(sumw>0) {
      ynew=(y1*w1+y2*w2+y3*w3) / sumw;
      eynew= w1*pow(y1-ynew,2)+w2*pow(y2-ynew,2)+w3*pow(y3-ynew,2);
      eynew/=sumw;

      /*      ynew=y1;//(y1+y2+y3)/3.;
      eynew=sqrt(pow(w1,2)+pow(w2,2)+pow(w3,2));
      */
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


  TF1* func2 = new TF1("func2","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",-0.9,0.0);
  input->Fit(func2,"MER");
  float a2=func2->GetParameter(0);
  float b2=func2->GetParameter(1);
  float c2=func2->GetParameter(2);
  float d2=func2->GetParameter(3);
  float e2=func2->GetParameter(4);
  float f2=func2->GetParameter(5);

  TF1* func = new TF1("func","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x",0,0.9);
  input->Fit(func,"MER");
  float a=func->GetParameter(0);
  float b=func->GetParameter(1);
  float c=func->GetParameter(2);
  float d=func->GetParameter(3);
  float e=func->GetParameter(4);
  float f=func->GetParameter(5);


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
    result->SetBinContent(j+1,eff_pres_);//input->GetBinContent(j+1));//eff_pres_);
    result->SetBinError(j+1,0);//input->GetBinError(j+1));                                                                                                                                                                          
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
 



void Plots_AFB(int quark=4, float lum=900) {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.0);
  TGaxis::SetMaxDigits(3);

  TH1F * AFBcorrected[2];
  TF1 *func_parton[2];
  TF1 *func_corrected[2];
  TF1 *func_cheat[2];

  int ipol=0;
  for(int i=0; i<2; i++) {
    
    ipol=i+2;
  int iprocess=1; //cut in radiative return

  float luminosity[2]={0};
  TH1F *hstats[2];

  TString pol="eL_pR";
  TString filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s.root",quark,pol.Data());
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
  filename = TString::Format("../results_"+energy+"/AFBreco_pdg%i_2f_hadronic_%s.root",quark,pol.Data());
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
  AFBcorrected[i]=PolHisto(AFB_pqcorrectedreco_effcorr_eL,AFB_pqcorrectedreco_effcorr_eR,ipol,luminosity,lum,1);
  TH1F* eff=Efficiency(AFBcheat,AFBparton,AFBparton2);

  AFBcorrected[i]->Divide(eff);

  AFBcheat->Divide(eff);

  
  //***** DRAW
  func_parton[i]=fit_histo2(AFBparton2, -1,1,false);
  func_corrected[i]=fit_histo2(AFBcorrected[i], -0.9,0.9,false);
  func_cheat[i]=fit_histo2(AFBcheat, -0.9,0.9,false);
  
  }

  TCanvas* c_AFBb = new TCanvas(TString::Format("c_AFB_%i",quark),TString::Format("c_AFB_%i",quark),800,800);
  c_AFBb->cd(1);

  TLegend *leg_1 = new TLegend(0.2,0.75,0.5,0.85,"H20, P:(-0.8,+0.3)");
  leg_1->SetTextSize(0.035);
  leg_1->SetTextFont(42);

  TLegend *leg_2 = new TLegend(0.2,0.64,0.5,0.74,"H20, P:(+0.8,-0.3)");
  leg_2->SetTextSize(0.035);
  leg_2->SetTextFont(42);



  for(int ipol=0; ipol<2; ipol++) {

  // gPad->SetLogy();
  func_parton[ipol]->GetXaxis()->SetTitle("cos #theta");
  func_parton[ipol]->GetYaxis()->SetTitle("entries");
  func_parton[ipol]->GetYaxis()->SetRangeUser(0,func_parton[ipol]->GetMaximum()*1.25);
  func_parton[ipol]->SetLineColor(kGreen-1);
  func_parton[ipol]->SetLineWidth(4);
  func_parton[ipol]->SetLineStyle(1);
  if(ipol==1) func_parton[ipol]->SetLineColor(kGreen+1);
  if(ipol==0) func_parton[ipol]->Draw("l");
  func_parton[ipol]->Draw("lsame");


  AFBcorrected[ipol]->SetLineWidth(2);
  AFBcorrected[ipol]->SetLineStyle(1);
  AFBcorrected[ipol]->SetMarkerColor(kRed);
  AFBcorrected[ipol]->SetLineColor(kRed);
  AFBcorrected[ipol]->SetMarkerStyle(20);
  if(ipol==1) AFBcorrected[ipol]->SetMarkerStyle(4);
  AFBcorrected[ipol]->Draw("esame");
  
  //  QQBARLabel(0.86,0.954,"");
  QQBARLabel(0.75,0.83,"",-1, 0.1);

  TString squark= "c#bar{c}";
  if(quark==5) squark="b#bar{b}";
  if(quark==0) squark="q#bar{q}";
  //  QQBARLabel2(0.1,0.35, "e^{-}e^{+} #rightarrow "+squark,960+2);

  //  if(quark==4 && ipol==0) QQBARLabel2(0.55,0.2, "e^{-}e^{+} #rightarrow "+squark,kOrange+2,0.05);
  //if(quark==5 && ipol==0) QQBARLabel2(0.55,0.2, "e^{-}e^{+} #rightarrow "+squark,kViolet+2,0.05);

  if(ipol==0) QQBARLabel2(0.2,0.87, "ILC250, e^{#minus}e^{#plus} #rightarrow "+squark,960,0.05);
  
  if(ipol==0) {
    leg_1->AddEntry(func_parton[ipol],"Whizard 2.8.5 LO","l");
    leg_1->AddEntry(AFBcorrected[ipol],"Full sim. reconstruction","pe");
  }
  if(ipol==1) {
    leg_2->AddEntry(func_parton[ipol],"Whizard 2.8.5 LO","l");
    leg_2->AddEntry(AFBcorrected[ipol],"Full sim. reconstruction","pe");
  }
  }
  //leg_b->AddEntry(func_corrected[ipol],"fit to reconstructed","l");
  //  leg_b->AddEntry(AFBcheat,"CheatCharge","lf");
  leg_1->SetFillColor(0);
  leg_1->SetLineColor(0);
  leg_1->SetShadowColor(0);
  leg_1->Draw();

  leg_2->SetFillColor(0);
  leg_2->SetLineColor(0);
  leg_2->SetShadowColor(0);
  leg_2->Draw();



  c_AFBb->Print(TString::Format("plots_"+energy+"_AFB/Fit_"+energy+"_pdg_%i.eps",quark));

  
}

  void AFBFitPaper() {
    Plots_AFB(5,900);
    Plots_AFB(4,900);
    //Plots_AFB(5,2,900);
    //Plots_AFB(5,3,900);
    
    
    //AFBSyst(4,3,1800);
    //AFBPol(4,3,1800);

  }
    
