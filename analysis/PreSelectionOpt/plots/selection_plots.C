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
#include "../../common/cross_sections.h"

TString energy="250GeV";

void Labels(int i = 0, TString pol = "eL")
{

  QQBARLabel(0.86, 0.954, "");
  if (i == 0)
    QQBARLabel2(0.04, 0.07, "[No Cuts]", kOrange + 3);
  if (i == 1)
    QQBARLabel2(0.04, 0.07, "photon veto_{0}", kOrange + 3);
  if (i == 2)
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 3);
  if (i == 3)
    QQBARLabel2(0.04, 0.082, "photon veto & acolinearity cuts", kOrange + 3);

  if (i == 4)
  {
    QQBARLabel2(0.04, 0.082, "photon veto & acolinearity", kOrange + 3);
    // QQBARLabel2(0.04,0.03, "& K_{reco} & m_{jj} cuts",kOrange+3);
    QQBARLabel2(0.04, 0.03, "& m_{jj} cuts", kOrange + 3);
  }
  if (i == 5)
  {
    QQBARLabel2(0.04, 0.082, "photon veto & acolinearity", kOrange + 3);
    // QQBARLabel2(0.04,0.03, "& K_{reco} & m_{jj} & y_{23} cuts",kOrange+3);
    QQBARLabel2(0.04, 0.03, "& m_{jj} & y_{23} cuts", kOrange + 3);
  }

  if (pol == "eL")
    QQBARLabel2(0.3, 0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, (q=udscb)", kGray + 2);
  if (pol == "eR")
    QQBARLabel2(0.3, 0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, (q=udscb)", kGray + 2);
}

void selection_plots(bool normalised = true, TString output = "efficiency")
{
  for (int polarisation = 0; polarisation < 1; polarisation++)
  {
    cout << "bb qq radreturn ww zz hz 6fttbar " << endl;

    // Efficiency y23.
    float bb_integral[100];
    float qq_integral[100];
    float cc_integral[100];
    float radreturn_integral[100];
    float zz_integral[100];
    float ww_integral[100];
    float qqH_integral[100];
    for (int i = 0; i < 100; i++)
    {
      bb_integral[i] = 0;
      qq_integral[i] = 0;
      cc_integral[i] = 0;
      radreturn_integral[i] = 0;
      zz_integral[i] = 0;
      ww_integral[i] = 0;
      qqH_integral[i] = 0;
    }

    float bb_integral_0 = 0.;
    float qq_integral_0 = 0.;
    float cc_integral_0 = 0.;
    float radreturn_integral_0 = 0.;
    float zz_integral_0 = 0.;
    float ww_integral_0 = 0.;
    float qqH_integral_0 = 0.;

    TString pol = "eR_pL";
    if (polarisation == 1)
      pol = "eL_pR";

    cout << output << endl;
    float luminosity_0 = 1;

    for (int i = 0; i < 5; i++)
    {

      // if(i==1) i=8;

      int cuts = i;

      //**********************************************************
      // /*ZZ
      TString folder = TString::Format("../results_"+energy+"_2023/selection_cuts%i_", cuts);

      TString filename = folder + "2f_hadronic_sample_" + pol + ".root";

      TFile *f = new TFile(filename);
      TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");

      TH1F *h_mjj_bb = (TH1F *)f->Get("h_mjj_bb");
      TH1F *h_mj1_mj2_bb = (TH1F *)f->Get("h_mj1_mj2_bb");
      TH1F *h_thrust_bb = (TH1F *)f->Get("h_thrust_bb");
      TH1F *h_sphericity_bb = (TH1F *)f->Get("h_sphericity_bb");
      TH1F *h_y23_bb = (TH1F *)f->Get("h_y23_bb");
      TH1F *h_d23_bb = (TH1F *)f->Get("h_d23_bb");
      TH1F *h_acol_bb = (TH1F *)f->Get("h_acol_bb");
      TH1F *h_costheta_bb = (TH1F *)f->Get("h_costheta_bb");
      TH1F *h_K_bb = (TH1F *)f->Get("h_K_bb");

      TH1F *h_mjj_cc = (TH1F *)f->Get("h_mjj_cc");
      TH1F *h_mj1_mj2_cc = (TH1F *)f->Get("h_mj1_mj2_cc");
      TH1F *h_thrust_cc = (TH1F *)f->Get("h_thrust_cc");
      TH1F *h_sphericity_cc = (TH1F *)f->Get("h_sphericity_cc");
      TH1F *h_y23_cc = (TH1F *)f->Get("h_y23_cc");
      TH1F *h_d23_cc = (TH1F *)f->Get("h_d23_cc");
      TH1F *h_acol_cc = (TH1F *)f->Get("h_acol_cc");
      TH1F *h_costheta_cc = (TH1F *)f->Get("h_costheta_cc");
      TH1F *h_K_cc = (TH1F *)f->Get("h_K_cc");

      TH1F *h_mjj_qq = (TH1F *)f->Get("h_mjj_qq");
      TH1F *h_mj1_mj2_qq = (TH1F *)f->Get("h_mj1_mj2_qq");
      TH1F *h_thrust_qq = (TH1F *)f->Get("h_thrust_qq");
      TH1F *h_sphericity_qq = (TH1F *)f->Get("h_sphericity_qq");
      TH1F *h_y23_qq = (TH1F *)f->Get("h_y23_qq");
      TH1F *h_d23_qq = (TH1F *)f->Get("h_d23_qq");
      TH1F *h_acol_qq = (TH1F *)f->Get("h_acol_qq");
      TH1F *h_costheta_qq = (TH1F *)f->Get("h_costheta_qq");
      TH1F *h_K_qq = (TH1F *)f->Get("h_K_qq");

      TH1F *h_mjj_radreturn = (TH1F *)f->Get("h_mjj_radreturn");
      TH1F *h_mj1_mj2_radreturn = (TH1F *)f->Get("h_mj1_mj2_radreturn");
      TH1F *h_thrust_radreturn = (TH1F *)f->Get("h_thrust_radreturn");
      TH1F *h_sphericity_radreturn = (TH1F *)f->Get("h_sphericity_radreturn");
      TH1F *h_y23_radreturn = (TH1F *)f->Get("h_y23_radreturn");
      TH1F *h_d23_radreturn = (TH1F *)f->Get("h_d23_radreturn");
      TH1F *h_acol_radreturn = (TH1F *)f->Get("h_acol_radreturn");
      TH1F *h_costheta_radreturn = (TH1F *)f->Get("h_costheta_radreturn");
      TH1F *h_K_radreturn = (TH1F *)f->Get("h_K_radreturn");

      bb_integral_0 = h_mjj_bb->GetEntries();
      qq_integral_0 = h_mjj_qq->GetEntries();
      cc_integral_0 = h_mjj_cc->GetEntries();
      radreturn_integral_0 = h_mjj_radreturn->GetEntries();

      float luminosity = h_luminosity_cross_2f->GetEntries() / cross_section[polarisation][0];
      if (i == 0)
        luminosity_0 = h_luminosity_cross_2f->GetEntries() / cross_section[polarisation][0];

      if (i > 0)
      {
        h_mjj_bb->Scale(luminosity_0 / luminosity);
        h_mj1_mj2_bb->Scale(luminosity_0 / luminosity);
        h_thrust_bb->Scale(luminosity_0 / luminosity);
        h_sphericity_bb->Scale(luminosity_0 / luminosity);
        h_y23_bb->Scale(luminosity_0 / luminosity);
        h_d23_bb->Scale(luminosity_0 / luminosity);
        h_acol_bb->Scale(luminosity_0 / luminosity);
        h_costheta_bb->Scale(luminosity_0 / luminosity);
        h_K_bb->Scale(luminosity_0 / luminosity);

        h_mjj_cc->Scale(luminosity_0 / luminosity);
        h_mj1_mj2_cc->Scale(luminosity_0 / luminosity);
        h_thrust_cc->Scale(luminosity_0 / luminosity);
        h_sphericity_cc->Scale(luminosity_0 / luminosity);
        h_y23_cc->Scale(luminosity_0 / luminosity);
        h_d23_cc->Scale(luminosity_0 / luminosity);
        h_acol_cc->Scale(luminosity_0 / luminosity);
        h_costheta_cc->Scale(luminosity_0 / luminosity);
        h_K_cc->Scale(luminosity_0 / luminosity);

        h_mjj_qq->Scale(luminosity_0 / luminosity);
        h_mj1_mj2_qq->Scale(luminosity_0 / luminosity);
        h_thrust_qq->Scale(luminosity_0 / luminosity);
        h_sphericity_qq->Scale(luminosity_0 / luminosity);
        h_y23_qq->Scale(luminosity_0 / luminosity);
        h_d23_qq->Scale(luminosity_0 / luminosity);
        h_acol_qq->Scale(luminosity_0 / luminosity);
        h_costheta_qq->Scale(luminosity_0 / luminosity);
        h_K_qq->Scale(luminosity_0 / luminosity);

        h_mjj_radreturn->Scale(luminosity_0 / luminosity);
        h_mj1_mj2_radreturn->Scale(luminosity_0 / luminosity);
        h_thrust_radreturn->Scale(luminosity_0 / luminosity);
        h_sphericity_radreturn->Scale(luminosity_0 / luminosity);
        h_y23_radreturn->Scale(luminosity_0 / luminosity);
        h_d23_radreturn->Scale(luminosity_0 / luminosity);
        h_acol_radreturn->Scale(luminosity_0 / luminosity);
        h_costheta_radreturn->Scale(luminosity_0 / luminosity);
        h_K_radreturn->Scale(luminosity_0 / luminosity);
      }
      //**********************************************************
      // WW
      filename = folder + "4f_WW_hadronic_" + pol + ".root";
      //    cout<<filename<<endl;
      TFile *f2 = new TFile(filename);
      TH1F *h_luminosity_cross_ww = (TH1F *)f2->Get("h_costheta_nocuts");
      TH1F *h_mjj_ww = (TH1F *)f2->Get("h_mjj_bb");
      TH1F *h_mj1_mj2_ww = (TH1F *)f2->Get("h_mj1_mj2_bb");
      TH1F *h_thrust_ww = (TH1F *)f2->Get("h_thrust_bb");
      TH1F *h_sphericity_ww = (TH1F *)f2->Get("h_sphericity_bb");
      TH1F *h_y23_ww = (TH1F *)f2->Get("h_y23_bb");
      TH1F *h_d23_ww = (TH1F *)f2->Get("h_d23_bb");
      TH1F *h_acol_ww = (TH1F *)f2->Get("h_acol_bb");
      TH1F *h_costheta_ww = (TH1F *)f2->Get("h_costheta_bb");
      TH1F *h_K_ww = (TH1F *)f2->Get("h_K_bb");

      ww_integral_0 = h_mjj_ww->GetEntries();
      float luminosity_ww = h_luminosity_cross_ww->GetEntries() / cross_section[polarisation][4];

      h_mjj_ww->Scale(luminosity / luminosity_ww);
      h_mj1_mj2_ww->Scale(luminosity / luminosity_ww);
      h_thrust_ww->Scale(luminosity / luminosity_ww);
      h_sphericity_ww->Scale(luminosity / luminosity_ww);
      h_y23_ww->Scale(luminosity / luminosity_ww);
      h_d23_ww->Scale(luminosity / luminosity_ww);
      h_acol_ww->Scale(luminosity / luminosity_ww);
      h_costheta_ww->Scale(luminosity / luminosity_ww);
      h_K_ww->Scale(luminosity / luminosity_ww);

      //**********************************************************
      // qqH
      filename = folder + "qqH_" + pol + ".root";
      TFile *f3 = new TFile(filename);
      TH1F *h_luminosity_cross_qqH = (TH1F *)f3->Get("h_costheta_nocuts");
      TH1F *h_mjj_qqH = (TH1F *)f3->Get("h_mjj_bb");
      TH1F *h_mj1_mj2_qqH = (TH1F *)f3->Get("h_mj1_mj2_bb");
      TH1F *h_thrust_qqH = (TH1F *)f3->Get("h_thrust_bb");
      TH1F *h_sphericity_qqH = (TH1F *)f3->Get("h_sphericity_bb");
      TH1F *h_y23_qqH = (TH1F *)f3->Get("h_y23_bb");
      TH1F *h_d23_qqH = (TH1F *)f3->Get("h_d23_bb");
      TH1F *h_acol_qqH = (TH1F *)f3->Get("h_acol_bb");
      TH1F *h_costheta_qqH = (TH1F *)f3->Get("h_costheta_bb");
      TH1F *h_K_qqH = (TH1F *)f3->Get("h_K_bb");

      qqH_integral_0 = h_mjj_qqH->GetEntries();
      float luminosity_qqH = h_luminosity_cross_qqH->GetEntries() / cross_section[polarisation][3];

      h_mjj_qqH->Scale(luminosity / luminosity_qqH);
      h_mj1_mj2_qqH->Scale(luminosity / luminosity_qqH);
      h_thrust_qqH->Scale(luminosity / luminosity_qqH);
      h_sphericity_qqH->Scale(luminosity / luminosity_qqH);
      h_y23_qqH->Scale(luminosity / luminosity_qqH);
      h_d23_qqH->Scale(luminosity / luminosity_qqH);
      h_acol_qqH->Scale(luminosity / luminosity_qqH);
      h_costheta_qqH->Scale(luminosity / luminosity_qqH);
      h_K_qqH->Scale(luminosity / luminosity_qqH);

      //**********************************************************
      // ZZ
      filename = folder + "4f_ZZ_hadronic_" + pol + ".root";
      TFile *f4 = new TFile(filename);
      TH1F *h_luminosity_cross_zz = (TH1F *)f4->Get("h_costheta_nocuts");
      TH1F *h_mjj_zz = (TH1F *)f4->Get("h_mjj_bb");
      TH1F *h_mj1_mj2_zz = (TH1F *)f4->Get("h_mj1_mj2_bb");
      TH1F *h_thrust_zz = (TH1F *)f4->Get("h_thrust_bb");
      TH1F *h_sphericity_zz = (TH1F *)f4->Get("h_sphericity_bb");
      TH1F *h_y23_zz = (TH1F *)f4->Get("h_y23_bb");
      TH1F *h_d23_zz = (TH1F *)f4->Get("h_d23_bb");
      TH1F *h_acol_zz = (TH1F *)f4->Get("h_acol_bb");
      TH1F *h_costheta_zz = (TH1F *)f4->Get("h_costheta_bb");
      TH1F *h_K_zz = (TH1F *)f4->Get("h_K_bb");

      zz_integral_0 = h_mjj_zz->GetEntries();
      float luminosity_zz = h_luminosity_cross_zz->GetEntries() / cross_section[polarisation][2];

      h_mjj_zz->Scale(luminosity / luminosity_zz);
      h_mj1_mj2_zz->Scale(luminosity / luminosity_zz);
      h_thrust_zz->Scale(luminosity / luminosity_zz);
      h_sphericity_zz->Scale(luminosity / luminosity_zz);
      h_y23_zz->Scale(luminosity / luminosity_zz);
      h_d23_zz->Scale(luminosity / luminosity_zz);
      h_acol_zz->Scale(luminosity / luminosity_zz);
      h_costheta_zz->Scale(luminosity / luminosity_zz);
      h_K_zz->Scale(luminosity / luminosity_zz);

      // Efficiency
      bb_integral[i + 1] = h_mjj_bb->Integral();
      qq_integral[i + 1] = h_mjj_qq->Integral();
      cc_integral[i + 1] = h_mjj_cc->Integral();
      radreturn_integral[i + 1] = h_mjj_radreturn->Integral();
      zz_integral[i + 1] = h_mjj_zz->Integral();
      qqH_integral[i + 1] = h_mjj_qqH->Integral();
      ww_integral[i + 1] = h_mjj_ww->Integral();

      if (i == 0)
      {
        bb_integral[i] = h_mjj_bb->Integral();
        qq_integral[i] = h_mjj_qq->Integral();
        cc_integral[i] = h_mjj_cc->Integral();
        radreturn_integral[i] = h_mjj_radreturn->Integral();
        zz_integral[i] = h_mjj_zz->Integral();
        qqH_integral[i] = h_mjj_qqH->Integral();
        ww_integral[i] = h_mjj_ww->Integral();
      }

      h_y23_bb->Rebin(10);
      h_y23_cc->Rebin(10);
      h_y23_qq->Rebin(10);
      h_y23_radreturn->Rebin(10);
      h_y23_zz->Rebin(10);
      h_y23_qqH->Rebin(10);
      h_y23_ww->Rebin(10);

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

      h_sphericity_bb->Rebin(10);
      h_sphericity_cc->Rebin(10);
      h_sphericity_qq->Rebin(10);
      h_sphericity_radreturn->Rebin(10);
      h_sphericity_zz->Rebin(10);
      h_sphericity_qqH->Rebin(10);
      h_sphericity_ww->Rebin(10);

      TString cut_string = ""; // Nocuts";
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

      if (i == 0)
        cout << std::setprecision(3) << " Cross-Section " << bb_integral_0 / luminosity << " " << cc_integral_0 / luminosity << " " << qq_integral_0 / luminosity << " " << radreturn_integral_0 / luminosity << " " << ww_integral_0 / luminosity_ww << " " << zz_integral_0 / luminosity_zz << " " << qqH_integral_0 / luminosity_qqH << " " << endl;

      if (output == "efficiency")
        cout << std::setprecision(3) << i << " " << 100. * bb_integral[i + 1] / bb_integral[0] << " " << 100. * cc_integral[i + 1] / cc_integral[0] << " " << 100. * qq_integral[i + 1] / qq_integral[0] << " " << 100. * radreturn_integral[i + 1] / radreturn_integral[0] << " " << 100. * ww_integral[i + 1] / ww_integral[0] << " " << 100. * zz_integral[i + 1] / zz_integral[0] << " " << 100. * qqH_integral[i + 1] / qqH_integral[0] << " " << endl;

      //    cout<<std::setprecision(3)<< cut_string<<" & bb:"<< 100.*bb_integral[i+1]/bb_integral[0]<<"\\% & cc:"<<100.*cc_integral[i+1]/cc_integral[0]<<"\\% & qq:"<<100.*qq_integral[i+1]/qq_integral[0]<<"\\% & rad:"<<100.*radreturn_integral[i+1]/(bb_integral[i+1]+qq_integral[i+1]+cc_integral[i+1])<<"\\% & WW:"<<100.*ww_integral[i+1]/(bb_integral[i+1]+qq_integral[i+1]+cc_integral[i+1])<<"\\% &  ZZ:"<<100.*zz_integral[i+1]/(bb_integral[i+1]+qq_integral[i+1]+cc_integral[i+1])<<"\\% & qqH:"<<100.*qqH_integral[i+1]/(bb_integral[i+1]+qq_integral[i+1]+cc_integral[i+1])<<"\\% & \\\\"<<endl;

      if (output == "B_S")
        cout << std::setprecision(3) << cut_string << " " << 100. * bb_integral[i + 1] / bb_integral[0] << " " << 100. * cc_integral[i + 1] / cc_integral[0] << " " << 100. * qq_integral[i + 1] / qq_integral[0] << " " << 100. * radreturn_integral[i + 1] / (bb_integral[i + 1] + qq_integral[i + 1] + cc_integral[i + 1]) << " " << 100. * ww_integral[i + 1] / (bb_integral[i + 1] + qq_integral[i + 1] + cc_integral[i + 1]) << " " << 100. * zz_integral[i + 1] / (bb_integral[i + 1] + qq_integral[i + 1] + cc_integral[i + 1]) << " " << 100. * qqH_integral[i + 1] / (bb_integral[i + 1] + qq_integral[i + 1] + cc_integral[i + 1]) << " " << endl;

      SetQQbarStyle();
      // gStyle->SetOptFit(0);
      // gStyle->SetOptStat(0);
      // gStyle->SetOptTitle(0);

      // gStyle->SetTitleBorderSize(0);
      // gStyle->SetTitleX(0.2);
      // gStyle->SetMarkerSize(1.5);
      TGaxis::SetMaxDigits(3);

      TCanvas *canvas0 = new TCanvas("canvas_acol", "canvas_acol", 800, 800);
      canvas0->cd(1);
      //    gPad->SetLogy();

      if (normalised == true)
        h_acol_radreturn->GetYaxis()->SetTitle("norm to 1");
      else
        h_acol_radreturn->GetYaxis()->SetTitle("Entries");
      h_acol_radreturn->GetXaxis()->SetTitle("sin(#Psi_{acol})");
      h_acol_radreturn->GetXaxis()->SetRangeUser(0, 1);
      h_acol_bb->SetLineColor(4);
      h_acol_qq->SetLineColor(1);
      h_acol_cc->SetLineStyle(2);
      h_acol_radreturn->SetLineColor(2);
      h_acol_ww->SetLineColor(kOrange);
      h_acol_zz->SetLineColor(6);
      h_acol_qqH->SetLineColor(7);

      h_acol_bb->SetLineWidth(2);
      h_acol_cc->SetLineWidth(2);
      h_acol_qq->SetLineWidth(2);
      h_acol_radreturn->SetLineWidth(2);
      h_acol_ww->SetLineWidth(2);
      h_acol_zz->SetLineWidth(2);
      h_acol_qqH->SetLineWidth(2);

      if (normalised == true)
      {
        h_acol_radreturn->DrawNormalized("histo");
        h_acol_qq->DrawNormalized("histosame");
        h_acol_cc->DrawNormalized("histosame");
        h_acol_bb->DrawNormalized("histosame");
        h_acol_ww->DrawNormalized("histosame");
        h_acol_zz->DrawNormalized("histosame");
        h_acol_qqH->DrawNormalized("histosame");
      }
      else
      {
        h_acol_bb->Draw("histo");
        h_acol_qq->Draw("histosame");
        h_acol_cc->Draw("histosame");
        h_acol_radreturn->Draw("histosame");
        h_acol_ww->Draw("histosame");
        h_acol_zz->Draw("histosame");
        h_acol_qqH->Draw("histosame");
      }

      TLegend *leg1 = new TLegend(0.2, 0.78, 0.4, 0.9); //(0.4,0.3,0.5,0.6);
      leg1->SetTextSize(0.035);
      leg1->AddEntry(h_acol_bb, "#font[42]{b#bar{b}}", "l");
      leg1->AddEntry(h_acol_cc, "#font[42]{c#bar{c}}", "l");
      leg1->AddEntry(h_acol_qq, "#font[42]{q#bar{q} (q=uds)}", "l");
      leg1->SetFillStyle(0);
      leg1->SetLineWidth(0);
      leg1->SetLineColor(0);
      leg1->SetBorderSize(0);
      // leg1->Draw();

      float xmin = 0.58, ymin = 0.76, xmax = 0.8, ymax = 0.9;
      if (i == 2)
      {
        xmin = 0.54;
        xmax = 0.76;
      }

      TLegend *leg3 = new TLegend(xmin, 0.48, xmax, 0.6); //(0.4,0.3,0.5,0.6);
      leg3->SetTextSize(0.035);
      leg3->AddEntry(h_acol_bb, "#font[42]{b#bar{b}}", "l");
      leg3->AddEntry(h_acol_cc, "#font[42]{c#bar{c}}", "l");
      leg3->AddEntry(h_acol_qq, "#font[42]{q#bar{q} (q=uds)}", "l");
      leg3->SetFillStyle(0);
      leg3->SetLineWidth(0);
      leg3->SetLineColor(0);
      leg3->SetBorderSize(0);
      leg3->Draw();

      TLegend *leg2 = new TLegend(xmin, 0.76, xmax, 0.9); //(0.4,0.3,0.5,0.6);
      leg2->SetTextSize(0.035);
      // leg2->AddEntry(h_acol_radreturn,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
      leg2->AddEntry(h_acol_radreturn, "#font[42]{Radiative Return}", "l");
      leg2->AddEntry(h_acol_qqH, "#font[42]{qqH}", "l");
      leg2->AddEntry(h_acol_zz, "#font[42]{ZZ}", "l");
      leg2->AddEntry(h_acol_ww, "#font[42]{WW}", "l");
      leg2->SetFillStyle(0);
      leg2->SetLineWidth(0);
      leg2->SetLineColor(0);
      leg2->SetBorderSize(0);
      leg2->Draw();
      Labels(i, pol);

      TArrow *arr0 = new TArrow(0.3, 0, 0.3, 0.31, 0.02, "<|>");
      arr0->SetLineColor(kGray);
      arr0->SetFillColor(kGray);
      arr0->Draw();

      if (i == 2)
        canvas0->Print("plots_"+energy+"_2023/acolinearity_cut.eps");

      TCanvas *canvas1 = new TCanvas("canvas_K", "canvas_K", 800, 800);
      canvas1->cd(1);

      if (normalised == true)
        h_K_radreturn->GetYaxis()->SetTitle("norm to 1");
      else
        h_K_radreturn->GetYaxis()->SetTitle("Entries");
      h_K_radreturn->GetXaxis()->SetTitle("K_{reco} [GeV]");
      // h_K_bb->GetYaxis()->SetRangeUser(10,h_K_bb->GetMaximum()*2);
      h_K_radreturn->GetXaxis()->SetRangeUser(0, 125);
      h_K_bb->SetLineColor(4);
      h_K_qq->SetLineColor(1);
      h_K_cc->SetLineStyle(2);
      h_K_radreturn->SetLineColor(2);
      h_K_ww->SetLineColor(kOrange);
      h_K_zz->SetLineColor(6);
      h_K_qqH->SetLineColor(7);

      h_K_bb->SetLineWidth(2);
      h_K_cc->SetLineWidth(2);
      h_K_qq->SetLineWidth(2);
      h_K_radreturn->SetLineWidth(2);
      h_K_ww->SetLineWidth(2);
      h_K_zz->SetLineWidth(2);
      h_K_qqH->SetLineWidth(2);

      if (normalised == true)
      {
        h_K_radreturn->DrawNormalized("histo");
        h_K_qq->DrawNormalized("histosame");
        h_K_cc->DrawNormalized("histosame");
        h_K_bb->DrawNormalized("histosame");
        h_K_ww->DrawNormalized("histosame");
        h_K_zz->DrawNormalized("histosame");
        h_K_qqH->DrawNormalized("histosame");
      }
      else
      {
        h_K_radreturn->Draw("histo");
        h_K_qq->Draw("histosame");
        h_K_cc->Draw("histosame");
        h_K_bb->Draw("histosame");
        h_K_ww->Draw("histosame");
        h_K_zz->Draw("histosame");
        h_K_qqH->Draw("histosame");
      }
      Labels(i, pol);

      leg3->Draw();
      leg2->Draw();

      TArrow *arr1 = new TArrow(35., 0, 35., 0.126, 0.02, "<|>");
      arr1->SetLineColor(kGray);
      arr1->SetFillColor(kGray);
      arr1->Draw();

      if (i == 2)
        canvas1->Print("plots_"+energy+"_2023/Kreco_cut.eps");

      TCanvas *canvas2 = new TCanvas("canvas_mjj", "canvas_mjj", 800, 800);
      canvas2->cd(1);
      //  gPad->SetLogy();
      if (normalised == true)
        h_mjj_qq->GetYaxis()->SetTitle("norm to 1");
      else
        h_mjj_qq->GetYaxis()->SetTitle("Entries");
      h_mjj_qq->GetXaxis()->SetTitle("m_{j_{1},j_{2}} [GeV]");
      // h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*2);
      //   h_mjj_bb->GetYaxis()->SetRangeUser(0,h_mjj_bb->GetMaximum()*10);
      //   h_mjj_bb->GetXaxis()->SetRangeUser(0,0.11);
      h_mjj_bb->SetLineColor(4);
      h_mjj_qq->SetLineColor(1);
      h_mjj_cc->SetLineStyle(2);
      h_mjj_radreturn->SetLineColor(2);
      h_mjj_ww->SetLineColor(kOrange);
      h_mjj_zz->SetLineColor(6);
      h_mjj_qqH->SetLineColor(7);

      h_mjj_bb->SetLineWidth(2);
      h_mjj_cc->SetLineWidth(2);
      h_mjj_qq->SetLineWidth(2);
      h_mjj_radreturn->SetLineWidth(2);
      h_mjj_ww->SetLineWidth(2);
      h_mjj_zz->SetLineWidth(2);
      h_mjj_qqH->SetLineWidth(2);

      if (normalised == true)
      {
        h_mjj_qq->DrawNormalized("histo");
        h_mjj_bb->DrawNormalized("histosame");
        h_mjj_cc->DrawNormalized("histosame");
        h_mjj_radreturn->DrawNormalized("histosame");
        h_mjj_ww->DrawNormalized("histosame");
        h_mjj_zz->DrawNormalized("histosame");
        h_mjj_qqH->DrawNormalized("histosame");
      }
      else
      {
        h_mjj_qq->Draw("histo");
        h_mjj_bb->Draw("histosame");
        h_mjj_cc->Draw("histosame");
        h_mjj_radreturn->Draw("histosame");
        h_mjj_ww->Draw("histosame");
        h_mjj_zz->Draw("histosame");
        h_mjj_qqH->Draw("histosame");
      }
      Labels(i, pol);
      leg3->Draw();
      leg2->Draw();

      TArrow *arr2 = new TArrow(140., h_mjj_bb->GetMinimum(), 140, 0.178, 0.02, "<|>");
      arr2->SetLineColor(kGray);
      arr2->SetFillColor(kGray);
      arr2->Draw();

      if (i == 4)
        canvas2->Print("plots_"+energy+"_2023/mjj_cut.eps");

      TCanvas *canvas3 = new TCanvas("canvas_y23", "canvas_y23", 800, 800);
      canvas3->cd(1);
      gPad->SetLogy();

      if (normalised == true)
        h_y23_bb->GetYaxis()->SetTitle("norm to 1");
      else
        h_y23_bb->GetYaxis()->SetTitle("Entries");
      h_y23_bb->GetXaxis()->SetTitle("y_{23}");
      // h_y23_bb->GetYaxis()->SetRangeUser(10,h_y23_bb->GetMaximum()*10);
      h_y23_bb->GetXaxis()->SetRangeUser(0, 0.2);

      h_y23_bb->SetLineColor(4);
      h_y23_qq->SetLineColor(1);
      h_y23_cc->SetLineStyle(2);
      h_y23_radreturn->SetLineColor(2);
      h_y23_ww->SetLineColor(kOrange);
      h_y23_zz->SetLineColor(6);
      h_y23_qqH->SetLineColor(7);

      h_y23_bb->SetLineWidth(2);
      h_y23_cc->SetLineWidth(2);
      h_y23_qq->SetLineWidth(2);
      h_y23_radreturn->SetLineWidth(2);
      h_y23_ww->SetLineWidth(2);
      h_y23_zz->SetLineWidth(2);
      h_y23_qqH->SetLineWidth(2);

      if (normalised == true)
      {
        h_y23_bb->DrawNormalized("histo");
        h_y23_qq->DrawNormalized("histosame");
        h_y23_cc->DrawNormalized("histosame");
        h_y23_radreturn->DrawNormalized("histosame");
        h_y23_ww->DrawNormalized("histosame");
        h_y23_zz->DrawNormalized("histosame");
        h_y23_qqH->DrawNormalized("histosame");
      }
      else
      {
        h_y23_bb->Draw("histo");
        h_y23_qq->Draw("histosame");
        h_y23_cc->Draw("histosame");
        h_y23_radreturn->Draw("histosame");
        h_y23_ww->Draw("histosame");
        h_y23_zz->Draw("histosame");
        h_y23_qqH->Draw("histosame");
      }
      Labels(i, pol);
      leg1->Draw();
      leg2->Draw();

      TArrow *arr3 = new TArrow(0.0125, h_y23_bb->GetMinimum(), 0.0125, 0.4, 0.02, "<|>");
      arr3->SetLineColor(kGray);
      arr3->SetFillColor(kGray);
      arr3->Draw();

      if (i == 4)
        canvas3->Print("plots_"+energy+"_2023/y23_cut.eps");
    }
  }
}
