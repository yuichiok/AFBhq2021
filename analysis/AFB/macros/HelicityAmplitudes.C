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
#include "AFBFit.C"

double r_stat[4]={0.18,0.27,0.12,0.23};//c-left, c-right, b-left, b-right
double afb_stat[4]={0.29,0.40,0.34,1.02};
double r_syst[4]={0.15,0.12,0.18,0.29};
double afb_syst[4]={0.13,0.15,0.14,0.34};
double Pel=0.8;
double Ppos=0.3;

double QcRR=pow(0.1,2);
double QcRL=pow(0.015,2);
double QcLL=pow(0.141577,2);
double QcLR=pow(0.035,2);

double QbRR=pow(0.043,2);
double QbRL=pow(0.028,2);
double QbLL=pow(0.12,2);
double QbLR=pow(0.025,2);
/*
double QbRR=pow(0.07,2);
double QbRL=pow(0.05,2);
double QbLL=pow(0.17,2);
double QbLR=pow(0.025,2);*/


double Pm=-(Pel+Ppos)/(1+Pel*Ppos);
double Pp=-Pm;

double AcL0=0.625;
double AcR0=0.70;
double AbL0=0.71;
double AbR0=0.41;

double RcL0=0.245;
double RcR0=0.32;
double RbL0=0.17;
double RbR0=0.0983011;

double CL=1./0.168535;
double CR=1./0.0678028;

void calc() {

  double cL=((1-Pm)*(QcLL+QcLR)+(1+Pm)*(QcRR+QcRL))/RcL0;
  cout <<cL<<endl;

  double cL2=((1-Pm)*(QbLL+QbLR)+(1+Pm)*(QbRR+QbRL))/RbL0;
  cout <<cL2<<endl;

  double cR=((1-Pp)*(QcLL+QcLR)+(1+Pp)*(QcRR+QcRL))/RcR0;
  cout <<cR<<endl;

  double cR2=((1-Pp)*(QbLL+QbLR)+(1+Pp)*(QbRR+QbRL))/RbR0;
  cout <<cR2<<endl;

  double testRbR=((1-Pp)*(QbLL+QbLR)+(1+Pp)*(QbRR+QbRL))/cR;
  cout<<testRbR<<endl;
  double testQcLL=(cL2*RcL0-(1+Pm)*(QcRR+QcRL))/(1-Pm)-QcLR;
  cout<<sqrt(testQcLL)<<endl;

}

std::vector<double> Test(int stat=1, int syst=1, int tpc_out=0) {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);

  int niter=1000000;

  if(tpc_out==1) {
    afb_stat[0]=afb_stat[0]/sqrt(0.2);
    afb_stat[1]=afb_stat[1]/sqrt(0.2);
    afb_stat[2]=afb_stat[2]/sqrt(0.3);
    afb_stat[3]=afb_stat[3]/sqrt(0.3);
  }

  //double r_stat[4]={0.18,0.27,0.12,0.23};//c-left, c-right, b-left, b-right
  //double afb_stat[4]={0.29,0.40,0.34,1.02};
  //double r_syst[4]={0.15,0.12,0.18,0.29};
  //double afb_syst[4]={0.13,0.15,0.14,0.34};
  TRandom *rsave = gRandom;
  TRandom *rtest = new TRandomRanlux48();
  TRandom *rtest2 = new TRandomRanlux48();
  double error[8]={0.};

  cout<<"First calculation"<<endl;
  for(int type=0; type<8; type++) {

    TH1F * h_solution[8];
    for(int i=0; i<8; i++) h_solution[i] = new TH1F(TString::Format("1Mxsol_%i",i),TString::Format("1Mxsol_%i",i),10000,0,0.2);

    for(int jr=0; jr<niter; jr++) {

      double AcL=AcL0;
      double AcR=AcR0;
      double AbL=AbL0;
      double AbR=AbR0;

      double RcL=RcL0;
      double RcR=RcR0;
      double RbL=RbL0;
      double RbR=RbR0;
            
      double r_AcL=0;
      double r_AcR=0;
      double r_RcL=0;
      double r_RcR=0;
      
      double r_AbL=0;
      double r_AbR=0;
      double r_RbL=0;
      double r_RbR=0;

     

      if(type==0) r_AcL=rtest->Gaus(AcL,sqrt(afb_stat[0]*afb_stat[0]*stat+afb_syst[0]*afb_syst[0]*syst)*AcL/100.);
      if(type==1) r_AcR=rtest->Gaus(AcR,sqrt(afb_stat[1]*afb_stat[1]*stat+afb_syst[1]*afb_syst[1]*syst)*AcR/100.);
      if(type==2) r_RcL=rtest->Gaus(RcL,sqrt(r_stat[0]*r_stat[0]*stat+r_syst[0]*r_syst[0]*syst)*RcL/100.);
      if(type==3) r_RcR=rtest->Gaus(RcR,sqrt(r_stat[1]*r_stat[1]*stat+r_syst[1]*r_syst[1]*syst)*RcR/100.);
      
      if(type==0) r_AbL=rtest->Gaus(AbL,sqrt(afb_stat[2]*afb_stat[2]*stat+afb_syst[2]*afb_syst[2]*syst)*AbL/100.);
      if(type==1) r_AbR=rtest->Gaus(AbR,sqrt(afb_stat[3]*afb_stat[3]*stat+afb_syst[3]*afb_syst[3]*syst)*AbR/100.);
      if(type==2) r_RbL=rtest->Gaus(RbL,sqrt(r_stat[2]*r_stat[2]*stat+r_syst[2]*r_syst[2]*syst)*RbL/100.);
      if(type==3) r_RbR=rtest->Gaus(RbR,sqrt(r_stat[3]*r_stat[3]*stat+r_syst[3]*r_syst[3]*syst)*RbR/100.);

  
      
      if(type==0) AcL=r_AcL;
      if(type==1) AcR=r_AcR;
      if(type==2) RcL=r_RcL;
      if(type==3) RcR=r_RcR;

      if(type==0) AbL=r_AbL;
      if(type==1) AbR=r_AbR;
      if(type==2) RbL=r_RbL;
      if(type==3) RbR=r_RbR;
      

      double solution_1[8]={
        (-((3 + 4*AcL)*CR*(-1 + Pp)*RcL) + (3 + 4*AcR)*CL*(-1 + Pm)*RcR)/(12*CL*CR*(Pm - Pp)), 
        (-((3 + 4*AcL)*CR*(1 + Pp)*RcL) + (3 + 4*AcR)*CL*(1 + Pm)*RcR)/(12*CL*CR*(Pm - Pp)), 
        ((-3 + 4*AcL)*CR*(-1 + Pp)*RcL - (-3 + 4*AcR)*CL*(-1 + Pm)*RcR)/(12*CL*CR*(Pm - Pp)), 
        ((-3 + 4*AcL)*CR*(1 + Pp)*RcL - (-3 + 4*AcR)*CL*(1 + Pm)*RcR)/(12*CL*CR*(Pm - Pp)), 
        (-((3 + 4*AbL)*CR*(-1 + Pp)*RbL) + (3 + 4*AbR)*CL*(-1 + Pm)*RbR)/(12*CL*CR*(Pm - Pp)), 
        (-((3 + 4*AbL)*CR*(1 + Pp)*RbL) + (3 + 4*AbR)*CL*(1 + Pm)*RbR)/(12*CL*CR*(Pm - Pp)), 
        ((-3 + 4*AbL)*CR*(-1 + Pp)*RbL - (-3 + 4*AbR)*CL*(-1 + Pm)*RbR)/(12*CL*CR*(Pm - Pp)), 
        ((-3 + 4*AbL)*CR*(1 + Pp)*RbL - (-3 + 4*AbR)*CL*(1 + Pm)*RbR)/(12*CL*CR*(Pm - Pp))
        };
      //cout<<solution_1[0]<<endl;
      h_solution[0]->Fill(sqrt(solution_1[0]));
      h_solution[1]->Fill(sqrt(solution_1[1]));
      h_solution[2]->Fill(sqrt(solution_1[2]));
      h_solution[3]->Fill(sqrt(solution_1[3]));
      h_solution[4]->Fill(sqrt(solution_1[4]));
      h_solution[5]->Fill(sqrt(solution_1[5]));
      h_solution[6]->Fill(sqrt(solution_1[6]));
      h_solution[7]->Fill(sqrt(solution_1[7]));
      //  cout<<solution_1[5]<<endl;
    }

    for(int i=0; i<8; i++) {
      /*h_solution[i]->SetLineColor(i+1);
      h_solution[i]->Draw("same");*/
      h_solution[i]->GetXaxis()->SetRangeUser(h_solution[i]->GetMean()-h_solution[i]->GetRMS(),h_solution[i]->GetMean()+h_solution[i]->GetRMS());
      double temperror=pow(h_solution[i]->GetRMS()/h_solution[i]->GetMean(),2);
      if(temperror>0.) error[i]+=temperror;
      cout<<type<<" "<<i<<" "<<error[i]<< " "<<sqrt(error[i])<<" "<<h_solution[i]->GetMean()<<endl;
    }
  }
 
  //***********************-------------------------
  cout<<"Average"<<endl;

  //for(int ihisto=0; ihisto<8; ihisto++) {
  //  cout<<ihisto<<" "<<sqrt(error[ihisto])<<endl;
 // }
  cout<<endl;
  
  std::vector<double> result; 
  for(int ihisto=0; ihisto<8; ihisto++) {
    cout<<error[ihisto]<< " "<<100.*sqrt(error[ihisto])<<endl;
    result.push_back(100.*sqrt(error[ihisto]));
  }

  return result;

}

void HelicityAmplitudes() {

  TH1F * htest0 = new TH1F("htest0","htest0",13,0.,13.);
  TH1F * htest1 = new TH1F("htest1","htest1",13,0.,13.);
  htest1->SetFillStyle(3005);
  htest1->SetFillColor(kGray+1);
  htest1->SetLineWidth(0);
  htest1->SetLineColor(kGray+1);

 // htest1->SetFillStyle();
  htest0->SetFillColor(kGray+1);
  htest0->SetLineColor(kGray+1);
  htest0->SetLineWidth(1);

  //calc();
  //Plots_AFB_method();
  std::vector<double> stat_and_syst=Test(1,1,0);
  TH1F * h_c_stat_and_syst = new TH1F("h_c_stat_and_syst","h_c_stat_and_syst",13,0.,13.);
  h_c_stat_and_syst->Fill(1.5,stat_and_syst.at(0));
  h_c_stat_and_syst->Fill(4.5,stat_and_syst.at(1));
  h_c_stat_and_syst->Fill(7.5,stat_and_syst.at(2));
  h_c_stat_and_syst->Fill(10.5,stat_and_syst.at(3));
  
  TH1F * h_b_stat_and_syst = new TH1F("h_b_stat_and_syst","h_b_stat_and_syst",13,0.,13.);
  h_b_stat_and_syst->Fill(2.5,stat_and_syst.at(4));
  h_b_stat_and_syst->Fill(5.5,stat_and_syst.at(5));
  h_b_stat_and_syst->Fill(8.5,stat_and_syst.at(6));
  h_b_stat_and_syst->Fill(11.5,stat_and_syst.at(7));

  std::vector<double> stat=Test(1,0,0);
  TH1F * h_c_stat = new TH1F("h_c_stat","h_c_stat",13,0.,13.);
  h_c_stat->Fill(1.5,stat.at(0));
  h_c_stat->Fill(4.5,stat.at(1));
  h_c_stat->Fill(7.5,stat.at(2));
  h_c_stat->Fill(10.5,stat.at(3));
 for(int i=0; i<13; i++){
    if(h_c_stat->GetBinContent(i+1)>0) h_c_stat->SetBinError(i+1,0.000001);
    else h_c_stat->SetBinContent(i+1,-10);
  } 
  TH1F * h_b_stat = new TH1F("h_b_stat","h_b_stat",13,0.,13.);
  h_b_stat->Fill(2.5,stat.at(4));
  h_b_stat->Fill(5.5,stat.at(5));
  h_b_stat->Fill(8.5,stat.at(6));
  h_b_stat->Fill(11.5,stat.at(7));
  for(int i=0; i<13; i++){
    if(h_b_stat->GetBinContent(i+1)>0) h_b_stat->SetBinError(i+1,0.000001);
    else h_b_stat->SetBinContent(i+1,-10);
  } 

  std::vector<double> notpc=Test(1,1,1);
  TH1F * h_c_notpc = new TH1F("h_c_notpc","h_c_notpc",13,0.,13.);
  h_c_notpc->Fill(1.5,notpc.at(0));
  h_c_notpc->Fill(4.5,notpc.at(1));
  h_c_notpc->Fill(7.5,notpc.at(2));
  h_c_notpc->Fill(10.5,notpc.at(3));
  
  TH1F * h_b_notpc = new TH1F("h_b_notpc","h_b_notpc",13,0.,13.);
  h_b_notpc->Fill(2.5,notpc.at(4));
  h_b_notpc->Fill(5.5,notpc.at(5));
  h_b_notpc->Fill(8.5,notpc.at(6));
  h_b_notpc->Fill(11.5,notpc.at(7));

  h_c_stat_and_syst->GetXaxis()->SetBinLabel(2,"Q_{e_{R}q_{R}}");
  h_c_stat_and_syst->GetXaxis()->SetBinLabel(5,"Q_{e_{L}q_{L}}");
  h_c_stat_and_syst->GetXaxis()->SetBinLabel(8,"Q_{e_{R}q_{L}}");
  h_c_stat_and_syst->GetXaxis()->SetBinLabel(11,"Q_{e_{L}q_{R}}");

  TCanvas * c1= new TCanvas("final","final",800,800);
  gPad->SetLogy();
  h_c_stat_and_syst->GetXaxis()->SetLabelSize(0.09);
  h_c_stat_and_syst->GetYaxis()->SetRangeUser(0.01,20);
  h_c_stat_and_syst->GetYaxis()->SetTitle("total uncertainty [%]");
  h_c_stat_and_syst->GetYaxis()->SetNdivisions(5+100*5+10000*0);
  h_c_stat_and_syst->GetXaxis()->SetTickLength(0);

  h_c_stat_and_syst->SetLineWidth(0);
  h_c_stat_and_syst->SetLineStyle(0);
  h_c_stat_and_syst->SetFillColor(kGreen-2);
  h_c_stat_and_syst->Draw("histo");
  h_b_stat_and_syst->SetLineWidth(0);
  h_b_stat_and_syst->SetLineStyle(0);
  h_b_stat_and_syst->SetFillColor(kMagenta+2);
  h_b_stat_and_syst->Draw("histosame");

  h_c_notpc->SetLineWidth(0);
  h_c_notpc->SetLineStyle(1);
  h_c_notpc->SetLineColor(kGreen-2);
  h_c_notpc->SetFillStyle(3005);
  h_c_notpc->SetFillColor(kGreen-2);
  h_c_notpc->Draw("histosame");

  h_b_notpc->SetLineWidth(0);
  h_b_notpc->SetLineStyle(1);
  h_b_notpc->SetLineColor(kMagenta+2);
  h_b_notpc->SetFillStyle(3005);
  h_b_notpc->SetFillColor(kMagenta+2);
  h_b_notpc->Draw("histosame");

  h_c_stat->SetMarkerStyle(21);
  h_c_stat->SetMarkerColor(kBlack);
  h_c_stat->SetLineColor(kBlack);
  h_c_stat->Draw("psame");

  h_b_stat->SetMarkerStyle(21);
  h_b_stat->SetMarkerColor(kBlack);
  h_b_stat->SetLineColor(kBlack);
  h_b_stat->Draw("psame");

  QQBARLabel(0.865,0.953,"");
  QQBARLabel2(0.15,0.96, "ILC250 2000 fb^{-1} ",960);

  TLegend *leg_c = new TLegend(0.3,0.88,0.5,0.93);
  leg_c->SetTextSize(0.035);
  leg_c->SetTextFont(42);
  leg_c->AddEntry(h_c_stat_and_syst,"q=c-quark","f");
  leg_c->SetFillColor(0);
  leg_c->SetLineColor(0);
  leg_c->SetShadowColor(0);
  leg_c->Draw();

  TLegend *leg_b = new TLegend(0.6,0.88,0.9,0.93);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(h_b_stat_and_syst,"q=b-quark","f");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  TLegend *leg = new TLegend(0.18,0.66,0.4,0.80);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(h_b_stat,"ILD baseline (only stats)","pl");
  leg->AddEntry(htest0,"ILD baseline","f");
  leg->AddEntry(htest1,"ILD w/o TPC PID","f");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c1->Print("plots_draft_final/HelicityAmplitude_Unc.eps");

}
    
