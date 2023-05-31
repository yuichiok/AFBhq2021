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

void Labels(int i = 0, TString pol = "eL", float textsize=0.045)
{

  QQBARLabel(0.8, 0.954, "");
  if (i == 0)
    QQBARLabel2(0.04, 0.07, "[No Cuts]", kOrange + 2, textsize);
  if (i == 1)
    QQBARLabel2(0.04, 0.07, "photon veto_{0}", kOrange + 2, textsize);
  if (i == 2)
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 2, textsize);
  if (i == 3)
    QQBARLabel2(0.04, 0.082, "photon veto & acolinearity cuts", kOrange + 2, textsize);

  if (i == 4)
  {
    QQBARLabel2(0.04, 0.08, "photon veto & acolinearity", kOrange + 2, textsize);
    QQBARLabel2(0.04, 0.028, "& K_{reco} & m_{j1j1} cuts", kOrange + 2, textsize);
  }
  if (i == 5)
  {
    QQBARLabel2(0.04, 0.08, "photon veto & acolinearity", kOrange + 2, textsize);
    QQBARLabel2(0.04, 0.028, "& K_{reco} & m_{j1j1} & y_{23} cuts", kOrange + 2, textsize);
  }

  if (pol == "eL")
    QQBARLabel2(0.3, 0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, (q=udscb)", kGray + 2);
  if (pol == "eR")
    QQBARLabel2(0.3, 0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, (q=udscb)", kGray + 2);
}

void selection_plots2(int polarisation = 0, bool normalised = true, TString output = "B_S")
{

  TString pol = "eL_pR";
  if (polarisation == 1)
    pol = "eR_pL";

  cout << output << endl;
  float luminosity_0 = 1;

  int cuts = 0;

  //**********************************************************
  // /*ZZ
  TString folder = TString::Format("../results_"+energy+"_2023/selection_cuts%i_", cuts);

  TString filename = folder + "2f_hadronic_sample_" + pol + ".root";

  TFile *f = new TFile(filename);
  TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");

  TH2F *h_npfos_bb = (TH2F *)f->Get("h_npfos_bb");
  TH2F *h_costheta_energy_bb = (TH2F *)f->Get("h_costheta_energy_bb");

  TH2F *h_npfos_cc = (TH2F *)f->Get("h_npfos_cc");
  TH2F *h_costheta_energy_cc = (TH2F *)f->Get("h_costheta_energy_cc");

  TH2F *h_npfos_qq = (TH2F *)f->Get("h_npfos_qq");
  TH2F *h_costheta_energy_qq = (TH2F *)f->Get("h_costheta_energy_qq");

  TH2F *h_npfos_radreturn = (TH2F *)f->Get("h_npfos_radreturn");
  TH2F *h_costheta_energy_radreturn = (TH2F *)f->Get("h_costheta_energy_radreturn");

  h_npfos_bb->Add(h_npfos_cc);
  h_npfos_bb->Add(h_npfos_qq);

  h_costheta_energy_bb->Add(h_costheta_energy_cc);
  h_costheta_energy_bb->Add(h_costheta_energy_qq);

  h_npfos_cc->Scale(0.);
  for (int i = 0; i < 101; i++)
  {
    h_npfos_cc->SetBinContent(1, i + 1, 100000);
    h_npfos_cc->SetBinContent(2, i + 1, 100000);
    h_npfos_cc->SetBinContent(i + 1, 1, 100000);
    h_npfos_cc->SetBinContent(i + 1, 2, 100000);
  }

  h_costheta_energy_cc->Scale(0.);
  for (int i = 0; i < 151; i++)
  {
    h_costheta_energy_cc->SetBinContent(101, i + 1, 100000);
    h_costheta_energy_cc->SetBinContent(100, i + 1, 100000);
    h_costheta_energy_cc->SetBinContent(99, i + 1, 100000);
    h_costheta_energy_cc->SetBinContent(98, i + 1, 100000);
  }
  for (int i = 0; i < 101; i++)
  {
    for (int j = 112; j < 151; j++)
    {
      h_costheta_energy_cc->SetBinContent(i + 1, j, 100000);
    }
  }

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(1.);

  gStyle->SetMarkerSize(1.5);
  gStyle->SetPadRightMargin(0.12);
  TGaxis::SetMaxDigits(3);

  TCanvas *canvas_N_1 = new TCanvas("canvas_npfos", "canvas_npfos", 800, 800);
  canvas_N_1->cd(1);

  h_npfos_bb->SetTitle("Signal");
  h_npfos_bb->GetYaxis()->SetTitle("# pfos jet_{2}");
  h_npfos_bb->GetXaxis()->SetTitle("# pfos jet_{1}");
  h_npfos_bb->GetXaxis()->SetRangeUser(0, 40);
  h_npfos_bb->GetYaxis()->SetRangeUser(0, 40);
  h_npfos_bb->Draw("colz");
  h_npfos_cc->SetFillColor(kRed);
  h_npfos_cc->SetFillStyle(3005);
  h_npfos_cc->SetLineColor(kRed);
  h_npfos_cc->Draw("boxsame");
  //  h_npfos_qq->Draw("boxsame");
  Labels(0, pol);

  canvas_N_1->Print("plots_"+energy+"_2023/npfos_signal.eps");

  TCanvas *canvas_N_2 = new TCanvas("canvas_npfos2", "canvas_npfos2", 800, 800);
  canvas_N_2->cd(1);

  h_npfos_radreturn->SetTitle("Radiative Return");
  h_npfos_radreturn->GetYaxis()->SetTitle("# pfos jet_{2}");
  h_npfos_radreturn->GetXaxis()->SetTitle("# pfos jet_{1}");
  h_npfos_radreturn->GetXaxis()->SetRangeUser(0, 40);
  h_npfos_radreturn->GetYaxis()->SetRangeUser(0, 40);
  h_npfos_radreturn->GetZaxis()->SetRangeUser(100, h_npfos_radreturn->GetMaximum());
  h_npfos_radreturn->Draw("colz");
  h_npfos_cc->Draw("boxsame");
  // h_npfos_qq->Draw("boxsame");
  Labels(0, pol);
  canvas_N_2->Print("plots_"+energy+"_2023/npfos_radreturn.eps");

  TCanvas *canvas_e_1 = new TCanvas("canvas_costheta_energy", "canvas_costheta_energy", 800, 800);
  canvas_e_1->cd(1);
  //  gPad->SetLogz();

  h_costheta_energy_bb->SetTitle("Signal");
  h_costheta_energy_bb->GetYaxis()->SetTitle("E_{#gamma_{clus}}");
  h_costheta_energy_bb->GetXaxis()->SetTitle("|cos#left(#theta_{#gamma_{clus}}#right)|");
  h_costheta_energy_bb->GetXaxis()->SetTitleOffset(1.6);

  h_costheta_energy_bb->Draw("colz");
  h_costheta_energy_cc->SetFillColor(kRed);
  h_costheta_energy_cc->SetFillStyle(3005);
  h_costheta_energy_cc->SetLineColor(kRed);
  h_costheta_energy_cc->Draw("boxsame");
  Labels(0, pol);
  canvas_e_1->Print("plots_"+energy+"_2023/energy_costheta_signal.eps");

  TCanvas *canvas_e_2 = new TCanvas("canvas_costheta_energy2", "canvas_costheta_energy2", 800, 800);
  canvas_e_2->cd(1);
  //  gPad->SetLogz();

  h_costheta_energy_radreturn->SetTitle("Radiative Return");
  h_costheta_energy_radreturn->GetYaxis()->SetTitle("E_{#gamma_{clus}}");
  h_costheta_energy_radreturn->GetXaxis()->SetTitle("|cos#left(#theta_{#gamma_{clus}}#right)|");
  h_costheta_energy_radreturn->GetXaxis()->SetTitleOffset(1.6);
  h_costheta_energy_radreturn->Draw("colz");
  h_costheta_energy_cc->Draw("boxsame");
  Labels(0, pol);
  canvas_e_2->Print("plots_"+energy+"_2023/energy_costheta_radreturn.eps");
}
