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

double QcRR=pow(0.085,2);
double QcRL=pow(0.012,2);
double QbRR=pow(0.035,2);
double QbRL=pow(0.028,2);

double QcLL=pow(0.014,2);
double QbLL=pow(0.014,2);


double Pm=-(Pel+Ppos)/(1+Pel*Ppos);
double Pp=-Pm;

double AcL=0.625;
double AcR=0.70;
double AbL=0.71;
double AbR=0.41;

double RcL=0.245;
double RcR=0.317;
double RbL=0.17;
double RbR=0.13;

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

  /*double r_stat[4]={0.18,0.27,0.12,0.23};//c-left, c-right, b-left, b-right
  double afb_stat[4]={0.29,0.40,0.34,1.02};
  double r_syst[4]={0.15,0.12,0.18,0.29};
  double afb_syst[4]={0.13,0.15,0.14,0.34};*/
  TRandom *rsave = gRandom;
  TRandom *rtest = new TRandomRanlux48();
  TRandom *rtest2 = new TRandomRanlux48();
  double error[8]={0.};

  TH1F * h_solution[8];
  for(int i=0; i<8; i++) h_solution[i] = new TH1F(TString::Format("1Mxsol_%i",i),TString::Format("1Mxsol_%i",i),1000000,0,10);

  cout<<"First calculation"<<endl;
  for(int type=0; type<8; type++) {

    for(int jr=0; jr<niter; jr++) {

      AcL=0.625;
      AcR=0.70;
      AbL=0.71;
      AbR=0.41;
      
      RcL=0.245;
      RcR=0.317;
      RbL=0.17;
      RbR=0.13;
      
      double r_AcL=0;
      double r_AcR=0;
      double r_RcL=0;
      double r_RcR=0;
      
      double r_AbL=0;
      double r_AbR=0;
      double r_RbL=0;
      double r_RbR=0;

      if(tpc_out==1) {
        afb_stat[0]=afb_stat[0]/sqrt(0.25);
        afb_stat[1]=afb_stat[1]/sqrt(0.25);
        afb_stat[2]=afb_stat[2]/sqrt(0.54);
        afb_stat[3]=afb_stat[3]/sqrt(0.54);
      }

      if(type==1) r_AcL=rtest->Gaus(AcL,sqrt(afb_stat[0]*afb_stat[0]*stat+afb_syst[0]*afb_syst[0]*syst)*AcL/100.);
      if(type==2) r_AcR=rtest->Gaus(AcR,sqrt(afb_stat[1]*afb_stat[1]*stat+afb_syst[1]*afb_syst[1]*syst)*AcR/100.);
      if(type==3) r_RcL=rtest->Gaus(RcL,sqrt(r_stat[0]*r_stat[0]*stat+r_syst[0]*r_syst[0]*syst)*RcL/100.);
      if(type==4) r_RcR=rtest->Gaus(RcR,sqrt(r_stat[1]*r_stat[1]*stat+r_syst[1]*r_syst[1]*syst)*RcR/100.);
      
      if(type==5) r_AbL=rtest->Gaus(AbL,sqrt(afb_stat[2]*afb_stat[2]*stat+afb_syst[2]*afb_syst[2]*syst)*AbL/100.);
      if(type==6) r_AbR=rtest->Gaus(AbR,sqrt(afb_stat[3]*afb_stat[3]*stat+afb_syst[3]*afb_syst[3]*syst)*AbR/100.);
      if(type==7) r_RbL=rtest->Gaus(RbL,sqrt(r_stat[2]*r_stat[2]*stat+r_syst[2]*r_syst[2]*syst)*RbL/100.);
      if(type==8) r_RbR=rtest->Gaus(RbR,sqrt(r_stat[3]*r_stat[3]*stat+r_syst[3]*r_syst[3]*syst)*RbR/100.);

  
      
      if(type==1) AcL=r_AcL;
      if(type==2) AcR=r_AcR;
      if(type==3) RcL=r_RcL;
      if(type==4) RcR=r_RcR;

      if(type==5) AbL=r_AbL;
      if(type==6) AbR=r_AbR;
      if(type==7) RbL=r_RbL;
      if(type==8) RbR=r_RbR;
      

      double solution_1[6]={((3 + 4*AbR)*(3 + 4*AcL)*(1 + Pm)*(-1 + Pp)*QcLL*RbR*RcL - (3 + 4*AbL)*(3 + 4*AcR)*(-1 + Pm)*(1 + Pp)*QcLL*RbL*RcR + 
    2*(3 + 4*AcL)*(3 + 4*AcR)*(Pm - Pp)*QbLL*RcL*RcR)/((1 + Pm)*(1 + Pp)*((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
  (2*(12*AcR + 9*Pm - 9*Pp - 12*AcR*Pm*Pp - 4*AcL*(3 + 4*AcR*(Pm - Pp) - 3*Pm*Pp))*QbLL*RcL*RcR + 
    QcLL*(-((3 + 4*AbR)*(-3 + 4*AcL)*(1 + Pm)*(-1 + Pp)*RbR*RcL) + (3 + 4*AbL)*(-3 + 4*AcR)*(-1 + Pm)*(1 + Pp)*RbL*RcR))/
   ((1 + Pm)*(1 + Pp)*((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
  ((3 + 4*AbR)*(-3 + 4*AcL)*QcLL*RbR*RcL - (3 + 4*AbL)*(-3 + 4*AcR)*QcLL*RbL*RcR + 24*(-AcL + AcR)*QbLL*RcL*RcR)/
   (-((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL) + (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR), (2*(3 + 4*AbL)*(3 + 4*AbR)*Pp*QcLL*RbL*RbR - (3 + 4*AbR)*(3 + 4*AcL)*QbLL*RbR*RcL + 
    (3 + 4*AbL)*(3 + 4*AcR)*QbLL*RbL*RcR - Pp*QbLL*((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL + (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR) + 
    Pm*(-2*(3 + 4*AbL)*(3 + 4*AbR)*QcLL*RbL*RbR + (3 + 4*AbR)*(3 + 4*AcL)*(1 + Pp)*QbLL*RbR*RcL - (3 + 4*AbL)*(3 + 4*AcR)*(-1 + Pp)*QbLL*RbL*RcR))/
   ((1 + Pm)*(1 + Pp)*((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
  (4*AbR*RbR*(6*(-1 + Pm*Pp)*QcLL*RbL - (3 + 4*AcL)*(-1 + Pm)*(1 + Pp)*QbLL*RcL) + 
    4*AbL*RbL*(2*(3 + 4*AbR*(Pm - Pp) - 3*Pm*Pp)*QcLL*RbR + (3 + 4*AcR)*(1 + Pm)*(-1 + Pp)*QbLL*RcR) + 
    3*(6*Pp*QcLL*RbL*RbR - (3 + 4*AcL)*QbLL*RbR*RcL + (3 + 4*AcR)*QbLL*RbL*RcR - Pp*QbLL*((3 + 4*AcL)*RbR*RcL + (3 + 4*AcR)*RbL*RcR) + 
      Pm*(-6*QcLL*RbL*RbR + (3 + 4*AcL)*(1 + Pp)*QbLL*RbR*RcL - (3 + 4*AcR)*(-1 + Pp)*QbLL*RbL*RcR)))/
   ((1 + Pm)*(1 + Pp)*((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
  (-24*AbR*QcLL*RbL*RbR - 3*(3 + 4*AcL)*QbLL*RbR*RcL + 4*AbR*(3 + 4*AcL)*QbLL*RbR*RcL + 3*(3 + 4*AcR)*QbLL*RbL*RcR + 4*AbL*RbL*(6*QcLL*RbR - (3 + 4*AcR)*QbLL*RcR))/
   (-((3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL) + (3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)};

      h_solution[0]->Fill(sqrt(solution_1[0]));
      h_solution[2]->Fill(sqrt(solution_1[1]));
      h_solution[3]->Fill(sqrt(solution_1[2]));
      h_solution[4]->Fill(sqrt(solution_1[3]));
      h_solution[6]->Fill(sqrt(solution_1[4]));
      h_solution[7]->Fill(sqrt(solution_1[5]));
      //  cout<<solution_1[5]<<endl;
    }
 
  }

  cout<<"Second calculation"<<endl;
  //rtest.clear();
  //rtest2.clear();
 // TRandom *rtest = new TRandomRanlux48();
  //TRandom *rtest2 = new TRandomRanlux48();
  //calculation of QcLL^2
  for(int type=0; type<8; type++) {
    cout<<type<<endl;
    for(int jr=0; jr<niter/10000; jr++) {

      AcL=0.625;
      AcR=0.70;
      AbL=0.71;
      AbR=0.41;
      
      RcL=0.245;
      RcR=0.317;
      RbL=0.17;
      RbR=0.13;
      
      double r_AcL;
      double r_AcR;
      double r_RcL;
      double r_RcR;
      
      double r_AbL;
      double r_AbR;
      double r_RbL;
      double r_RbR;

      if(tpc_out==1) {
        afb_stat[0]=afb_stat[0]/sqrt(0.25);
        afb_stat[1]=afb_stat[1]/sqrt(0.25);
        afb_stat[2]=afb_stat[2]/sqrt(0.54);
        afb_stat[3]=afb_stat[3]/sqrt(0.54);
      }

      if(type==0) r_AcL=rtest->Gaus(AcL,sqrt(afb_stat[0]*afb_stat[0]*stat+afb_syst[0]*afb_syst[0]*syst)*AcL/100.);
      if(type==1) r_AcR=rtest->Gaus(AcR,sqrt(afb_stat[1]*afb_stat[1]*stat+afb_syst[1]*afb_syst[1]*syst)*AcR/100.);
      if(type==2) r_RcL=rtest->Gaus(RcL,sqrt(r_stat[0]*r_stat[0]*stat+r_syst[0]*r_syst[0]*syst)*RcL/100.);
      if(type==3) r_RcR=rtest->Gaus(RcR,sqrt(r_stat[1]*r_stat[1]*stat+r_syst[1]*r_syst[1]*syst)*RcR/100.);
      
      if(type==4) r_AbL=rtest->Gaus(AbL,sqrt(afb_stat[2]*afb_stat[2]*stat+afb_syst[2]*afb_syst[2]*syst)*AbL/100.);
      if(type==5) r_AbR=rtest->Gaus(AbR,sqrt(afb_stat[3]*afb_stat[3]*stat+afb_syst[3]*afb_syst[3]*syst)*AbR/100.);
      if(type==6) r_RbL=rtest->Gaus(RbL,sqrt(r_stat[2]*r_stat[2]*stat+r_syst[2]*r_syst[2]*syst)*RbL/100.);
      if(type==7) r_RbR=rtest->Gaus(RbR,sqrt(r_stat[3]*r_stat[3]*stat+r_syst[3]*r_syst[3]*syst)*RbR/100.);

  
      
      AcL=r_AcL;
      AcR=r_AcR;
      RcL=r_RcL;
      RcR=r_RcR;

      AbL=r_AbL;
      AbR=r_AbR;
      RbL=r_RbL;
      RbR=r_RbR;
      
      for(int type2=0; type2<3; type2++) {
        double rc1=h_solution[0]->GetMean();
        if(type2==0) rc1=rtest2->Gaus(h_solution[0]->GetMean(),h_solution[0]->GetRMS());
        double rc2=h_solution[2]->GetMean();
        if(type2==1) rc2=rtest2->Gaus(h_solution[2]->GetMean(),h_solution[2]->GetRMS());
        double rc3=h_solution[3]->GetMean();
        if(type2==2) rc3=rtest2->Gaus(h_solution[3]->GetMean(),h_solution[3]->GetRMS());

        QcLL=
          sqrt(
            ( (1+Pm)*(4*AcL-3)*rc1*rc1 
            + (1+Pm)*(4*AcL+3)*rc2*rc2
            + (1-Pm)*(4*AcL+3)*rc3*rc3 )/
            (-(4*AcL-3)*(1-Pm))
          );
      
        if(QcLL>0) h_solution[5]->Fill(QcLL);
      }
    }    
  }

  /*cout<<"Third calculation"<<endl;
  //rtest.clear();
  //rtest2.clear();
  // TRandom *rtest = new TRandomRanlux48();
  //TRandom *rtest2 = new TRandomRanlux48();
  //calculation of QbLL^2
  for(int type=0; type<8; type++) {
    cout<<type<<endl;
    for(int jr=0; jr<niter/10000; jr++) {

      AcL=0.625;
      AcR=0.70;
      AbL=0.71;
      AbR=0.41;
      
      RcL=0.245;
      RcR=0.317;
      RbL=0.17;
      RbR=0.13;
      
      double r_AcL;
      double r_AcR;
      double r_RcL;
      double r_RcR;
      
      double r_AbL;
      double r_AbR;
      double r_RbL;
      double r_RbR;

      if(tpc_out==1) {
        afb_stat[0]=afb_stat[0]/sqrt(0.25);
        afb_stat[1]=afb_stat[1]/sqrt(0.25);
        afb_stat[2]=afb_stat[2]/sqrt(0.54);
        afb_stat[3]=afb_stat[3]/sqrt(0.54);
      }

      if(type==0) r_AcL=rtest->Gaus(AcL,sqrt(afb_stat[0]*afb_stat[0]*stat+afb_syst[0]*afb_syst[0]*syst)*AcL/100.);
      if(type==1) r_AcR=rtest->Gaus(AcR,sqrt(afb_stat[1]*afb_stat[1]*stat+afb_syst[1]*afb_syst[1]*syst)*AcR/100.);
      if(type==2) r_RcL=rtest->Gaus(RcL,sqrt(r_stat[0]*r_stat[0]*stat+r_syst[0]*r_syst[0]*syst)*RcL/100.);
      if(type==3) r_RcR=rtest->Gaus(RcR,sqrt(r_stat[1]*r_stat[1]*stat+r_syst[1]*r_syst[1]*syst)*RcR/100.);
      
      if(type==4) r_AbL=rtest->Gaus(AbL,sqrt(afb_stat[2]*afb_stat[2]*stat+afb_syst[2]*afb_syst[2]*syst)*AbL/100.);
      if(type==5) r_AbR=rtest->Gaus(AbR,sqrt(afb_stat[3]*afb_stat[3]*stat+afb_syst[3]*afb_syst[3]*syst)*AbR/100.);
      if(type==6) r_RbL=rtest->Gaus(RbL,sqrt(r_stat[2]*r_stat[2]*stat+r_syst[2]*r_syst[2]*syst)*RbL/100.);
      if(type==7) r_RbR=rtest->Gaus(RbR,sqrt(r_stat[3]*r_stat[3]*stat+r_syst[3]*r_syst[3]*syst)*RbR/100.);

  
      
      AcL=r_AcL;
      AcR=r_AcR;
      RcL=r_RcL;
      RcR=r_RcR;

      AbL=r_AbL;
      AbR=r_AbR;
      RbL=r_RbL;
      RbR=r_RbR;
      
      for(int type2=0; type2<3; type2++) {
        double rb1=h_solution[4]->GetMean();
        if(type2==0) rb1=rtest2->Gaus(h_solution[4]->GetMean(),h_solution[4]->GetRMS());
        double rb2=h_solution[6]->GetMean();
        if(type2==1) rb2=rtest2->Gaus(h_solution[6]->GetMean(),h_solution[6]->GetRMS());
        double rb3=h_solution[7]->GetMean();
        if(type2==2) rb3=rtest2->Gaus(h_solution[7]->GetMean(),h_solution[7]->GetRMS());

        QbLL=
          sqrt(
            ( (1+Pm)*(4*AbL-3)*rb1*rb1 
            + (1+Pm)*(4*AbL+3)*rb2*rb2
            + (1-Pm)*(4*AbL+3)*rb3*rb3 )/
            (-(4*AbL-3)*(1-Pm))
          );
      
        if(QbLL>0) h_solution[5]->Fill(QbLL);
      }
    }    
  }
*/

  //***********************-------------------------
  cout<<"Average"<<endl;
  h_solution[7]->Draw("same");

  for(int ihisto=0; ihisto<8; ihisto++) {
    //h_solution[ihisto]->GetXaxis()->SetRangeUser(h_solution[ihisto]->GetMean()-h_solution[ihisto]->GetRMS(),h_solution[ihisto]->GetMean()+h_solution[ihisto]->GetRMS());
    double temperror=pow(h_solution[ihisto]->GetRMS()/h_solution[ihisto]->GetMean(),2);
    if(temperror>0.00000001) error[ihisto]+=temperror;
    //cout<<error[ihisto]<< " "<<sqrt(error[ihisto])<<endl;
  }
  cout<<endl;
  
  std::vector<double> result; 
  for(int ihisto=0; ihisto<8; ihisto++) {
    cout<<error[ihisto]<< " "<<100.*sqrt(error[ihisto])<<endl;
    result.push_back(100.*sqrt(error[ihisto]));
  }

  return result;

}

std::vector<double> Extract1(int stat=1, int syst=1, int tpc_out=0) {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);

  TH1F * h_solution[8];
  for(int i=0; i<8; i++) h_solution[i] = new TH1F(TString::Format("1Mxsol_%i",i),TString::Format("1Mxsol_%i",i),10000,0,10);

  /*double r_stat[4]={0.18,0.27,0.12,0.23};//c-left, c-right, b-left, b-right
  double afb_stat[4]={0.29,0.40,0.34,1.02};
  double r_syst[4]={0.15,0.12,0.18,0.29};
  double afb_syst[4]={0.13,0.15,0.14,0.34};*/
  TRandom *rsave = gRandom;
  TRandom *rtest = new TRandom2();
  TRandom *rtest2 = new TRandom2();
  TRandom *rtest3 = new TRandom2();
  TRandom *rtest4 = new TRandom2();
  TRandom *rtest5 = new TRandom2();
  TRandom *rtest6  = new TRandom2();
  TRandom *rtest7  = new TRandom2();
  TRandom *rtest8  = new TRandom2();

  for(int jr=0; jr<1000000; jr++) {

    AcL=0.625;
    AcR=0.70;
    AbL=0.71;
    AbR=0.41;
    
    RcL=0.245;
    RcR=0.317;
    RbL=0.17;
    RbR=0.13;
    
    double r_AcL=0;
    double r_AcR=0;
    double r_RcL=0;
    double r_RcR=0;
    
    double r_AbL=0;
    double r_AbR=0;
    double r_RbL=0;
    double r_RbR=0;

   if(tpc_out==1) {
      afb_stat[0]=afb_stat[0]/sqrt(0.25);
      afb_stat[1]=afb_stat[1]/sqrt(0.25);
      afb_stat[2]=afb_stat[2]/sqrt(0.54);
      afb_stat[3]=afb_stat[3]/sqrt(0.54);
    }

    r_AcL=rtest->Gaus(AcL,sqrt(afb_stat[0]*afb_stat[0]*stat+afb_syst[0]*afb_syst[0]*syst)*AcL/100.);
    /*r_AcR=rtest2->Gaus(AcR,sqrt(afb_stat[1]*afb_stat[1]*stat+afb_syst[1]*afb_syst[1]*syst)*AcR/100.);
    r_RcL=rtest3->Gaus(RcL,sqrt(r_stat[0]*r_stat[0]*stat+r_syst[0]*r_syst[0]*syst)*RcL/100.);
    r_RcR=rtest4->Gaus(RcR,sqrt(r_stat[1]*r_stat[1]*stat+r_syst[1]*r_syst[1]*syst)*RcR/100.);
    
    r_AbL=rtest5->Gaus(AbL,sqrt(afb_stat[2]*afb_stat[2]*stat+afb_syst[2]*afb_syst[2]*syst)*AbL/100.);
    r_AbR=rtest6->Gaus(AbR,sqrt(afb_stat[3]*afb_stat[3]*stat+afb_syst[3]*afb_syst[3]*syst)*AbR/100.);
    r_RbL=rtest7->Gaus(RbL,sqrt(r_stat[2]*r_stat[2]*stat+r_syst[2]*r_syst[2]*syst)*RbL/100.);
    r_RbR=rtest8->Gaus(RbR,sqrt(r_stat[3]*r_stat[3]*stat+r_syst[3]*r_syst[3]*syst)*RbR/100.);*/

 
    
    AcL=r_AcL;
    /*AcR=r_AcR;
    RcL=r_RcL;
    RcR=r_RcR;

    AbL+=r_AbL;
    AbR=r_AbR;
    RbL=r_RbL;
    RbR=r_RbR;
    */

    double solution_1[6]={((-3 + 4*AbR)*(3 + 4*AcL)*(-1 + Pm)*(1 + Pp)*QcRR*RbR*RcL - (-3 + 4*AbL)*(3 + 4*AcR)*(1 + Pm)*(-1 + Pp)*QcRR*RbL*RcR + 
      2*(3 + 4*AcL)*(3 + 4*AcR)*(Pm - Pp)*QbRL*RcL*RcR)/((-1 + Pm)*(-1 + Pp)*((-3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (-3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
      ((-3 + 4*AbR)*(-3 + 4*AcL)*QcRR*RbR*RcL - (-3 + 4*AbL)*(-3 + 4*AcR)*QcRR*RbL*RcR + 24*(AcL - AcR)*QbRL*RcL*RcR)/
      (-((-3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL) + (-3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR), 
      (-((-3 + 4*AbR)*(-3 + 4*AcL)*(-1 + Pm)*(1 + Pp)*QcRR*RbR*RcL) + (-3 + 4*AbL)*(-3 + 4*AcR)*(1 + Pm)*(-1 + Pp)*QcRR*RbL*RcR - 
      8*AcL*(-3 + 4*AcR*(Pm - Pp) + 3*Pm*Pp)*QbRL*RcL*RcR + 6*(-4*AcR + 3*Pm - 3*Pp + 4*AcR*Pm*Pp)*QbRL*RcL*RcR)/
      ((-1 + Pm)*(-1 + Pp)*((-3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (-3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
      (-24*AbR*QcRR*RbL*RbR + 3*(3 + 4*AcL)*QbRL*RbR*RcL + 4*AbR*(3 + 4*AcL)*QbRL*RbR*RcL - 3*(3 + 4*AcR)*QbRL*RbL*RcR + 4*AbL*RbL*(6*QcRR*RbR - (3 + 4*AcR)*QbRL*RcR))/
      (-((-3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL) + (-3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR), (4*AbR*RbR*(6*(-1 + Pm*Pp)*QcRR*RbL - (3 + 4*AcL)*(1 + Pm)*(-1 + Pp)*QbRL*RcL) + 
      4*AbL*RbL*(2*(3 + 4*AbR*(Pm - Pp) - 3*Pm*Pp)*QcRR*RbR + (3 + 4*AcR)*(-1 + Pm)*(1 + Pp)*QbRL*RcR) - 
      3*(-6*Pp*QcRR*RbL*RbR - (3 + 4*AcL)*QbRL*RbR*RcL + (3 + 4*AcL)*Pp*QbRL*RbR*RcL + (3 + 4*AcR)*QbRL*RbL*RcR + (3 + 4*AcR)*Pp*QbRL*RbL*RcR + 
      Pm*(6*QcRR*RbL*RbR + (3 + 4*AcL)*(-1 + Pp)*QbRL*RbR*RcL - (3 + 4*AcR)*(1 + Pp)*QbRL*RbL*RcR)))/
      ((-1 + Pm)*(-1 + Pp)*((-3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (-3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR)), 
      (2*(-3 + 4*AbL)*(-3 + 4*AbR)*Pp*QcRR*RbL*RbR - (-3 + 4*AbR)*(3 + 4*AcL)*QbRL*RbR*RcL + (-3 + 4*AbR)*(3 + 4*AcL)*Pp*QbRL*RbR*RcL + 
      (-3 + 4*AbL)*(3 + 4*AcR)*QbRL*RbL*RcR + (-3 + 4*AbL)*(3 + 4*AcR)*Pp*QbRL*RbL*RcR + 
      Pm*(-2*(-3 + 4*AbL)*(-3 + 4*AbR)*QcRR*RbL*RbR + (-3 + 4*AbR)*(3 + 4*AcL)*(-1 + Pp)*QbRL*RbR*RcL - (-3 + 4*AbL)*(3 + 4*AcR)*(1 + Pp)*QbRL*RbL*RcR))/
      ((-1 + Pm)*(-1 + Pp)*((-3 + 4*AbR)*(3 + 4*AcL)*RbR*RcL - (-3 + 4*AbL)*(3 + 4*AcR)*RbL*RcR))
    };
    
    h_solution[1]->Fill(sqrt(solution_1[0]));
    h_solution[2]->Fill(sqrt(solution_1[1]));
    h_solution[3]->Fill(sqrt(solution_1[2]));
    h_solution[4]->Fill(sqrt(solution_1[3]));
    h_solution[5]->Fill(sqrt(solution_1[4]));
    h_solution[7]->Fill(sqrt(solution_1[5]));


  }

  for(int jr=0; jr<1000000; jr++) {

    AcL=0.625;
    AcR=0.70;
    AbL=0.71;
    AbR=0.41;
    
    RcL=0.245;
    RcR=0.317;
    RbL=0.17;
    RbR=0.13;
    
    double r_AcL;
    double r_AcR;
    double r_RcL;
    double r_RcR;
    
    double r_AbL;
    double r_AbR;
    double r_RbL;
    double r_RbR;

   if(tpc_out==1) {
      afb_stat[0]=afb_stat[0]/sqrt(0.25);
      afb_stat[1]=afb_stat[1]/sqrt(0.25);
      afb_stat[2]=afb_stat[2]/sqrt(0.54);
      afb_stat[3]=afb_stat[3]/sqrt(0.54);
    }

    r_AcL=rtest->Gaus(AcL,sqrt(afb_stat[0]*afb_stat[0]*stat+afb_syst[0]*afb_syst[0]*syst)*AcL/100.);
    r_AcR=rtest2->Gaus(AcR,sqrt(afb_stat[1]*afb_stat[1]*stat+afb_syst[1]*afb_syst[1]*syst)*AcR/100.);
    r_RcL=rtest3->Gaus(RcL,sqrt(r_stat[0]*r_stat[0]*stat+r_syst[0]*r_syst[0]*syst)*RcL/100.);
    r_RcR=rtest4->Gaus(RcR,sqrt(r_stat[1]*r_stat[1]*stat+r_syst[1]*r_syst[1]*syst)*RcR/100.);
    
    r_AbL=rtest5->Gaus(AbL,sqrt(afb_stat[2]*afb_stat[2]*stat+afb_syst[2]*afb_syst[2]*syst)*AbL/100.);
    r_AbR=rtest6->Gaus(AbR,sqrt(afb_stat[3]*afb_stat[3]*stat+afb_syst[3]*afb_syst[3]*syst)*AbR/100.);
    r_RbL=rtest7->Gaus(RbL,sqrt(r_stat[2]*r_stat[2]*stat+r_syst[2]*r_syst[2]*syst)*RbL/100.);
    r_RbR=rtest8->Gaus(RbR,sqrt(r_stat[3]*r_stat[3]*stat+r_syst[3]*r_syst[3]*syst)*RbR/100.);

 
    
    AcL=r_AcL;
    AcR=r_AcR;
    RcL=r_RcL;
    RcR=r_RcR;

    AbL=r_AbL;
    AbR=r_AbR;
    RbL=r_RbL;
    RbR=r_RbR;
    
  

    double rb1=rtest2->Gaus(h_solution[4]->GetMean(),h_solution[4]->GetRMS());
    double rb2=rtest3->Gaus(h_solution[5]->GetMean(),h_solution[5]->GetRMS());
    double rb3=rtest4->Gaus(h_solution[7]->GetMean(),h_solution[7]->GetRMS());

    QbRL=
      sqrt(
        ( (1+Pp)*(4*AbR-3)*rb1*rb1 
        + (1-Pp)*(4*AbR-3)*rb2*rb2
        + (1-Pp)*(4*AbR+3)*rb3*rb3 )/
        (-(4*AbR+3)*(1+Pp))
      );
    
    if(QbRL>0) h_solution[6]->Fill(QbRL);

    double rc1=rtest4->Gaus(h_solution[1]->GetMean(),h_solution[1]->GetRMS());
    double rc2=rtest5->Gaus(h_solution[2]->GetMean(),h_solution[2]->GetRMS());
    double rc3=rtest6->Gaus(h_solution[3]->GetMean(),h_solution[3]->GetRMS());

    QcRR=
      sqrt(
        ( (1-Pp)*(4*AcR-3)*rc1*rc1 
        + (1+Pp)*(4*AcR+3)*rc2*rc2
        + (1-Pp)*(4*AcR+3)*rc3*rc3 )/
        (-(4*AcR-3)*(1+Pp))
      );
    
    if(QcRR>0) h_solution[0]->Fill(QcRR);
  }

  std::vector<double> result;

  TCanvas * c1= new TCanvas("Extract1","Extract1");
  for(int i=0; i<8; i++) {
    h_solution[i]->SetLineColor(i+1);
    h_solution[i]->DrawNormalized("histosame");
    //h_solution[i]->GetXaxis()->SetRangeUser(h_solution[i]->GetMean()-h_solution[i]->GetRMS(),h_solution[i]->GetMean()+h_solution[i]->GetRMS());
    TF1 * testfit = new TF1(TString::Format("testfit_%i",i),"gaus",h_solution[i]->GetMean()-h_solution[i]->GetRMS(),h_solution[i]->GetMean()+h_solution[i]->GetRMS());
    h_solution[i]->Fit(testfit,"MR");
    result.push_back(100.*testfit->GetParameter(2)/testfit->GetParameter(1));
    testfit->Draw("same");
  }

  TCanvas * c2= new TCanvas("Extract2","Extract2");
  c2->cd();
  for(int i=0; i<8; i++) {
    h_solution[i]->SetLineColor(i+1);
    h_solution[i]->Draw("histosame");
  }

  return result;

}

void HelicityAmplitudes() {

  //Plots_AFB_method();
  std::vector<double> stat_and_syst=Test(1,1,0);
  /*std::vector<double> stat_and_syst=Extract1(1,1,0);
  //std::vector<double> stat=Extract1(1,0,0);
  //std::vector<double> no_tpc=Extract1(1,1,1);
  //Extract2();

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

  TCanvas * c1= new TCanvas("final","final");
  h_c_stat_and_syst->SetLineWidth(0);
  h_c_stat_and_syst->SetLineStyle(0);
  h_c_stat_and_syst->SetFillColor(kGreen+1);
  h_c_stat_and_syst->Draw("histo");
  h_b_stat_and_syst->SetLineWidth(0);
  h_b_stat_and_syst->SetLineStyle(0);
  h_b_stat_and_syst->SetFillColor(kOrange+1);
  h_b_stat_and_syst->Draw("histosame");*/

}
    
