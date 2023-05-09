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
double afb_stat[4]={0.38,0.52,0.24,0.7};
double r_syst[4]={0.15,0.12,0.18,0.29};
double afb_syst[4]={0.16,0.19,0.13,0.22};


// double AFBStat(int quark=4, int ipol=0, float lum=900, int cheatmethod=0) {

//   float Afb_corrected[100]={0};
//   float dAfb_corrected[100]={0};

//   for(int syst_=0; syst_<1; syst_++) {
//   int iprocess=4; //cut in radiative return

//   int syst=syst_;
//   if(syst_==22) syst=21;
//   float luminosity[2]={0};
//   TH1F *hstats[2];

//   TString pol="eL_pR";
//   TString filename = TString::Format("../results/AFBreco_pdg%i_2f_hadronic_%s_250GeV_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
//   TFile *f = new TFile(filename);
//   hstats[0]=(TH1F*)f->Get("h_Ntotal_nocuts");
//   if(hstats[0]->Integral()>0) luminosity[0]=hstats[0]->Integral()/cross_section[0][iprocess];
//   else luminosity[0]=0;
  
//   TH1F* AFBparton_eL = (TH1F*)f->Get("h_AFB");
//   TH1F* AFBparton2_eL = (TH1F*)f->Get("h_AFB2");
//   TH1F* AFBcheat_eL= (TH1F*)f->Get("h_AFBcheat");
//   TH1F* AFB_pqcorrectedreco_effcorr_0_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat0_syst%i",syst));
//   TH1F* AFB_pqcorrectedreco_effcorr_1_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat1_syst%i",syst));
//   TH1F* AFB_pqcorrectedreco_effcorr_2_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat2_syst%i",syst));
//   TH1F* AFB_pqcorrectedreco_effcorr_eL=average(AFB_pqcorrectedreco_effcorr_0_eL,AFB_pqcorrectedreco_effcorr_1_eL,AFB_pqcorrectedreco_effcorr_2_eL);
//   TH1F* AFB_chargecheatreco_effcorr_0_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat0_syst%i",0));
//   TH1F* AFB_chargecheatreco_effcorr_1_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat1_syst%i",0));
//   TH1F* AFB_chargecheatreco_effcorr_2_eL= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat2_syst%i",0));
//   TH1F* AFB_chargecheatreco_effcorr_eL=average(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL);

//   //TH1F* eff_eL=Efficiency(AFB_chargecheatreco_effcorr_0_eL,AFB_chargecheatreco_effcorr_1_eL,AFB_chargecheatreco_effcorr_2_eL,AFBparton_eL);

//   pol="eR_pL";
//   filename = TString::Format("../results/AFBreco_pdg%i_2f_hadronic_%s_250GeV_cheatmethod_%i.root",quark,pol.Data(),cheatmethod);
//   f = new TFile(filename);
//   hstats[1]=(TH1F*)f->Get("h_Ntotal_nocuts");
//   if(hstats[1]->Integral()>0) luminosity[1]=hstats[1]->Integral()/cross_section[1][iprocess];
//   else luminosity[1]=0;
  
//   TH1F* AFBparton_eR = (TH1F*)f->Get("h_AFB");
//   TH1F* AFBparton2_eR = (TH1F*)f->Get("h_AFB2");
//   TH1F* AFBcheat_eR= (TH1F*)f->Get("h_AFBcheat");
//   TH1F* AFB_pqcorrectedreco_effcorr_0_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat0_syst%i",syst));
//   TH1F* AFB_pqcorrectedreco_effcorr_1_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat1_syst%i",syst));
//   TH1F* AFB_pqcorrectedreco_effcorr_2_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat2_syst%i",syst));
//   TH1F* AFB_pqcorrectedreco_effcorr_eR=average(AFB_pqcorrectedreco_effcorr_0_eR,AFB_pqcorrectedreco_effcorr_1_eR,AFB_pqcorrectedreco_effcorr_2_eR);
//   TH1F* AFB_chargecheatreco_effcorr_0_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat0_syst%i",0));
//   TH1F* AFB_chargecheatreco_effcorr_1_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat1_syst%i",0));
//   TH1F* AFB_chargecheatreco_effcorr_2_eR= (TH1F*)f->Get(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat2_syst%i",0));
//   TH1F* AFB_chargecheatreco_effcorr_eR=average(AFB_chargecheatreco_effcorr_0_eR,AFB_chargecheatreco_effcorr_1_eR,AFB_chargecheatreco_effcorr_2_eR);

//   //**********************Pol Histos
//   if(syst>20) lum=2000;
//   TH1F * AFBparton=PolHisto(AFBparton_eL,AFBparton_eR,ipol,luminosity,lum,1);
//   TH1F * AFBparton2=PolHisto(AFBparton2_eL,AFBparton2_eR,ipol,luminosity,lum,1);
//   TH1F * AFBcheat=PolHisto(AFB_chargecheatreco_effcorr_eL,AFB_chargecheatreco_effcorr_eR,ipol,luminosity,lum,1);
//   TH1F * AFBcorrected=PolHisto(AFB_pqcorrectedreco_effcorr_eL,AFB_pqcorrectedreco_effcorr_eR,ipol,luminosity,lum,1);
//   float error=0;
//   if(syst==21 && syst_==22) error=-1;
//   if(syst==21 && syst_==21) error=1;
  
//   TH1F* eff=Efficiency(AFBcheat,AFBparton,AFBparton2,"",error);
//   AFBcorrected->Divide(eff);
  
//   //***** DRAW
//   TF1 *func_parton=fit_histo(AFBparton2, -1,1,false);
//   TF1 *func_corrected=fit_histo(AFBcorrected, -0.9,0.9,false);

//   float plus_corrected = func_corrected->Integral(0,1);
//   float minus_corrected = func_corrected->Integral(-1,0);
//   float plus_e_corrected = func_corrected->IntegralError(0,1);
//   float minus_e_corrected = func_corrected->IntegralError(1,0);
//   Afb_corrected[syst_]=Afb_v(plus_corrected,minus_corrected);
//   dAfb_corrected[syst_]=dAfb_v(plus_corrected,minus_corrected, plus_e_corrected, minus_e_corrected);

//   }

//   return 100.*dAfb_corrected[0]/Afb_corrected[0];

// }

void Plots_R_AFB() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.);

  TGaxis::SetMaxDigits(3);

  TH1F * q_eL = new TH1F("c_eL","c_eL",12,-0.5,11.5);
  TH1F * q_eR = new TH1F("c_eR","c_eR",12,-0.5,11.5);

  TH1F * c_eL = new TH1F("c_eL","c_eL",11,0.,11.);
  TH1F * c_eR = new TH1F("c_eR","c_eR",11,0.,11.);
  TH1F * b_eL = new TH1F("b_eL","b_eL",11,0.,11.);
  TH1F * b_eR = new TH1F("b_eR","b_eR",11,0.,11.);

  double y[8]={r_stat[0],r_stat[1],afb_stat[0],afb_stat[1],r_stat[2],r_stat[3],afb_stat[2],afb_stat[3]};
  double x[8]={0.5,1.5,3.5,4.5,6.5,7.5,9.5,10.5};

  double ey[8]={0,0,0,0,0,0,0,0};
  double ex[8]={0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  TGraphErrors * gstat = new TGraphErrors(8,x,y,ex,ey);

  double y2[4]={sqrt(pow(afb_stat[0]/sqrt(0.25),2)+pow(afb_syst[0],2)),sqrt(pow(afb_stat[1]/sqrt(0.25),2)+pow(afb_syst[1],2)),sqrt(pow(afb_stat[2]/sqrt(0.54),2)+pow(afb_syst[2],2)),sqrt(pow(afb_stat[3]/sqrt(0.54),2)+pow(afb_syst[2],2))};
  double x2[4]={3.5,4.5,9.5,10.5};

  double ex2[4]={0,0,0,0};
  double ey2[4]={y2[0]-sqrt( pow(afb_stat[0],2)+pow(afb_syst[0],2)),y2[1],y2[2]-sqrt( pow(afb_stat[2],2)+pow(afb_syst[2],2)),y2[3]};//0.5,0.5,0.5,0.5};
  TGraphAsymmErrors * g_noTPC = new TGraphAsymmErrors(4,x2,y2,ex2,ex2,ey2,ex2);


  c_eL->Fill(0.5, sqrt( pow(r_stat[0],2)+pow(r_syst[0],2)));
  c_eL->Fill(3.5, sqrt( pow(afb_stat[0],2)+pow(afb_syst[0],2)));

  c_eR->Fill(1.5, sqrt( pow(r_stat[1],2)+pow(r_syst[1],2)));
  c_eR->Fill(4.5, sqrt( pow(afb_stat[1],2)+pow(afb_syst[1],2)));

  b_eL->Fill(6.5, sqrt( pow(r_stat[2],2)+pow(r_syst[2],2)));
  b_eL->Fill(9.5, sqrt( pow(afb_stat[2],2)+pow(afb_syst[2],2)));

  b_eR->Fill(7.5, sqrt( pow(r_stat[3],2)+pow(r_syst[3],2)));
  b_eR->Fill(10.5, sqrt( pow(afb_stat[3],2)+pow(afb_syst[3],2)));


  //LABELS
  /* const Int_t nx = 11;
  const char *obs[nx] = {".","R_{c}","..","...","A_{FB}^{c}","....",".....",
			 "R_{b}","......",".......","A_{FB}^{b#bar{b}}"};
   q_eL->SetCanExtend(TH1::kAllAxes);
   for (Int_t i=0;i<11;i++) {
      q_eL->Fill(obs[i],5);
   }
   q_eL->LabelsDeflate();*/

  q_eL->GetXaxis()->SetBinLabel(2,"R_{c}");
  q_eL->GetXaxis()->SetBinLabel(5,"A_{FB}^{c}");
  q_eL->GetXaxis()->SetBinLabel(8,"R_{b}");
  q_eL->GetXaxis()->SetBinLabel(11,"A_{FB}^{b}");

  TCanvas* c_R_AFB = new TCanvas("c_R_AFB","c_AFB",1400,800);
  c_R_AFB->cd(1);
  // gPad->SetLogy();
  // c_eL->GetXaxis()->SetTitle("cos #theta");
  q_eL->GetYaxis()->SetTitle("total relative uncertainty [%]");
  q_eL->GetYaxis()->SetRangeUser(0,1.5);
  q_eL->GetXaxis()->SetRangeUser(0,11);
  q_eL->GetXaxis()->SetTickLength(0);
  //q_eL->SetFillStyle(3001);
  //  q_eL->GetXaxis()->SetNdivisions(512);
  q_eL->GetXaxis()->SetLabelSize(0.1);

  q_eL->SetLineWidth(0);
  q_eL->SetLineStyle(0);
  q_eL->SetFillColor(kGreen+3);
  q_eL->Draw("");
  q_eR->SetLineWidth(0);
  q_eR->SetLineStyle(0);
  q_eR->SetFillColor(kGreen-4);
  //  q_eR->SetFillStyle(3003);

  g_noTPC->SetMarkerStyle(29);
  g_noTPC->SetMarkerColor(kGreen+1);
  g_noTPC->SetLineWidth(1);
  g_noTPC->SetLineColor(kGreen+1);
  g_noTPC->SetMarkerSize(1.4);
  g_noTPC->Draw("pe");
  
  c_eL->SetLineWidth(0);
  c_eL->SetLineStyle(0);
  c_eL->SetFillColor(kGreen+3);
  //c_eL->SetFillStyle(3001);
  c_eL->Draw("histosame");

  c_eR->SetLineWidth(0);
  c_eR->SetLineStyle(0);
  c_eR->SetFillColor(kGreen-4);
  //  c_eR->SetFillStyle(3003);
  c_eR->Draw("histosame");

  b_eL->SetLineWidth(0);
  b_eL->SetLineStyle(0);
  b_eL->SetFillColor(kGreen+3);
  //b_eL->SetFillStyle(3001);
  b_eL->Draw("histosame");

  b_eR->SetLineWidth(0);
  b_eR->SetLineStyle(0);
  b_eR->SetFillColor(kGreen-4);
  //b_eR->SetFillStyle(3003);
  b_eR->Draw("histosame");

  gstat->SetMarkerStyle(21);
  gstat->SetMarkerColor(kBlack);
  gstat->SetLineColor(kBlack);
  gstat->Draw("pe");

  
  // AFBcorrected->Divide(AFBparton2);
  // AFBcorrected->Draw("ep");
  // Labels(-1,-1,900);
  //    QQBARLabel2(0.1,0.05, "e^{-}e^{+} #rightarrow "+quark,color+2);
  QQBARLabel(0.89,0.954,"");
  QQBARLabel2(0.15,0.96, "ILC250 2000 fb^{-1} ",960);
  
  TLegend *leg_b = new TLegend(0.2,0.75,0.4,0.9);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(q_eL,"P_{e^{-}e^{+}}(-0.8,+0.3)","f");
  leg_b->AddEntry(q_eR,"P_{e^{-}e^{+}}(+0.8,-0.3)","f");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  TLegend *leg_b2 = new TLegend(0.5,0.75,0.7,0.9);
  leg_b2->SetTextSize(0.035);
  leg_b2->SetTextFont(42);
  leg_b2->AddEntry(gstat,"Only stat. unc.","pl");
  leg_b2->AddEntry(g_noTPC,"w/o TPC kaon ID","pe");
  leg_b2->SetFillColor(0);
  leg_b2->SetLineColor(0);
  leg_b2->SetShadowColor(0);
  leg_b2->Draw();

  c_R_AFB->Print("plots_"+energy+"_final/Observables_Unc.eps");

  
}

// void Plots_AFB_method() {

//   SetQQbarStyle();
//   gStyle->SetOptFit(0); 
//   gStyle->SetOptStat(0);
//   gStyle->SetOptTitle(0);
  
//   gStyle->SetTitleBorderSize(0);
//   gStyle->SetTitleStyle(0);
//   gStyle->SetTitleX(0.2);
//   gStyle->SetMarkerSize(1.);

//   TGaxis::SetMaxDigits(3);

//   TH1F * q_eL = new TH1F("c_eL","c_eL",42,-0.5,41.5);
//   TH1F * q_eR = new TH1F("c_eR","c_eR",42,-0.5,41.5);

//   TH1F * c_eL[4];
//   TH1F * c_eR[4];

 
//   for(int i=0; i<4; i++) {
//     c_eL[i]= new TH1F(TString::Format("c_eL_%i",i),TString::Format("c_eL_%i",i),40,0.,40.);
//     c_eR[i]= new TH1F(TString::Format("c_eR_%i",i),TString::Format("c_eR_%i",i),40,0.,40.);
//    }
  
 
//   double afb_stat_1[4]={0};
//   double afb_stat_2[4]={0};
//   double afb_stat_3[4]={0};

//   int i=0;
//   for(int quark=4; quark<6; quark++) {
//     int j=0;
//     for(int pol=2; pol<4; pol++) {
//       double test_1=AFBStat(quark, pol, 900, 1);
//       afb_stat_1[2*i+j]=test_1;
//       double test_2=AFBStat(quark, pol, 900, 2);
//       afb_stat_2[2*i+j]=test_2;
//       double test_3=AFBStat(quark, pol, 900, 3);
//       afb_stat_3[2*i+j]=test_3;
//       j++;
//     }
//     i++;
//   }
  
//   c_eL[0]->Fill(0.5, afb_stat[0]);
//   c_eR[0]->Fill(5.5, afb_stat[1]);
//   c_eL[0]->Fill(12.5, afb_stat[2]);
//   c_eR[0]->Fill(17.5, afb_stat[3]);

  
//   c_eL[1]->Fill(1.5, afb_stat_1[0]);
//   c_eR[1]->Fill(6.5, afb_stat_1[1]);
//   c_eL[1]->Fill(13.5, afb_stat_1[2]);
//   c_eR[1]->Fill(18.5, afb_stat_1[3]);

//   c_eL[2]->Fill(2.5, afb_stat_2[0]);
//   c_eR[2]->Fill(7.5, afb_stat_2[1]);
//   c_eL[2]->Fill(14.5, afb_stat_2[2]);
//   c_eR[2]->Fill(19.5, afb_stat_2[3]);

//   c_eL[3]->Fill(3.5, afb_stat_3[0]);
//   c_eR[3]->Fill(8.5, afb_stat_3[1]);
//   c_eL[3]->Fill(15.5, afb_stat_3[2]);
//   c_eR[3]->Fill(20.5, afb_stat_3[3]);

//   q_eL->GetXaxis()->SetBinLabel(5,"A_{FB}^{c}");
//   q_eL->GetXaxis()->SetBinLabel(17,"A_{FB}^{b}");

//   TCanvas* c_R_AFB = new TCanvas("c_R_AFB","c_AFB",1400,800);
//   c_R_AFB->cd(1);
//   // gPad->SetLogy();
//   // c_eL->GetXaxis()->SetTitle("cos #theta");
//   q_eL->GetYaxis()->SetTitle("statistics relative uncertainty [%]");
//   q_eL->GetYaxis()->SetRangeUser(0,1.2);
//   q_eL->GetXaxis()->SetRangeUser(0,21);
//   q_eL->GetXaxis()->SetTickLength(0);
//   //  q_eL->GetXaxis()->SetNdivisions(512);
//   q_eL->GetXaxis()->SetLabelSize(0.08);

//   q_eL->SetLineWidth(0);
//   q_eL->SetLineStyle(0);
//   q_eL->SetFillColor(kBlack);
//   q_eL->Draw("");
//   q_eR->SetLineWidth(0);
//   q_eR->SetLineStyle(0);
//   q_eR->SetFillColor(kBlack);
//   q_eR->SetFillStyle(3003);

  
//   c_eL[0]->SetLineWidth(0);
//   c_eL[0]->SetLineStyle(0);
//   c_eL[0]->SetFillColor(kBlue-4);
//   c_eL[0]->Draw("histosame");

//   c_eR[0]->SetLineWidth(0);
//   c_eR[0]->SetLineStyle(0);
//   c_eR[0]->SetFillColor(kBlue-4);
//   c_eR[0]->SetFillStyle(3003);
//   c_eR[0]->Draw("histosame");


//   c_eL[1]->SetLineWidth(0);
//   c_eL[1]->SetLineStyle(0);
//   c_eL[1]->SetFillColor(kRed+1);
//   c_eL[1]->Draw("histosame");

//   c_eR[1]->SetLineWidth(0);
//   c_eR[1]->SetLineStyle(0);
//   c_eR[1]->SetFillColor(kRed+1);
//   c_eR[1]->SetFillStyle(3003);
//   c_eR[1]->Draw("histosame");

//   c_eL[2]->SetLineWidth(0);
//   c_eL[2]->SetLineStyle(0);
//   c_eL[2]->SetFillColor(kOrange+1);
//   c_eL[2]->Draw("histosame");

//   c_eR[2]->SetLineWidth(0);
//   c_eR[2]->SetLineStyle(0);
//   c_eR[2]->SetFillColor(kOrange+1);
//   c_eR[2]->SetFillStyle(3003);
//   c_eR[2]->Draw("histosame");

//   c_eL[3]->SetLineWidth(0);
//   c_eL[3]->SetLineStyle(0);
//   c_eL[3]->SetFillColor(kAzure+1);
//   c_eL[3]->Draw("histosame");

//   c_eR[3]->SetLineWidth(0);
//   c_eR[3]->SetLineStyle(0);
//   c_eR[3]->SetFillColor(kAzure+1);
//   c_eR[3]->SetFillStyle(3003);
//   c_eR[3]->Draw("histosame");

//    // AFBcorrected->Divide(AFBparton2);
//   // AFBcorrected->Draw("ep");
//   // Labels(-1,-1,900);
//   //    QQBARLabel2(0.1,0.05, "e^{-}e^{+} #rightarrow "+quark,color+2);
//   QQBARLabel(0.89,0.954,"");
//   QQBARLabel2(0.15,0.954, "ILC250 2000 fb^{-1} ",960);
  
//   TLegend *leg_b = new TLegend(0.2,0.65,0.4,0.85);
//   leg_b->SetTextSize(0.035);
//   leg_b->SetTextFont(42);
//   leg_b->AddEntry(q_eL,"P_{e^{-}e^{+}}(-0.8,+0.3)","f");
//   leg_b->AddEntry(q_eR,"P_{e^{-}e^{+}}(+0.8,-0.3)","f");
//   leg_b->SetFillColor(0);
//   leg_b->SetLineColor(0);
//   leg_b->SetShadowColor(0);
//   leg_b->Draw();

//   //  c_AFBb->Print(TString::Format("plots_"+energy+"_AFB/Fit_pdg_%i_pol_%i.eps",quark,ipol));

  
// }

void R_AFB_results() {

  //Plots_AFB_method();
  Plots_R_AFB();
  
}
    
