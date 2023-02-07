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
#include "../../common/hidden_cross_sections.h"

TString folder = "../results/";
void Labels(int i = 0, int ipol = 1, float lum = 900, float ildx=0.86)
{

  QQBARLabel(ildx, 0.953, "");
  if (i == 0)
    QQBARLabel2(0.04, 0.07, "[No Cuts]", kOrange + 3);
  if (i == 1)
    QQBARLabel2(0.04, 0.07, "photon veto_{0}", kOrange + 3);
  if (i == 2)
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 3);
  if (i == 3)
  {
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 3);
    QQBARLabel2(0.04, 0.03, "& m_{jj} cuts", kOrange + 3);
  }

  QQBARLabel2(0.8, 0.03, TString::Format("Int.Lum=%i fb^{-1}", int(lum)), kGray + 1);

  if (ipol == 0)
    QQBARLabel2(0.7, 0.03, "e_{L}^{-}e_{R}^{+} ", kGray + 1);
  if (ipol == 1)
    QQBARLabel2(0.7, 0.03, "e_{R}^{-}e_{L}^{+} ", kGray + 1);
}

TH1F * PolHisto(TH1F *h1, TH1F* h2, int pol) {

  // this function takes two histograms, 100% polarized, normalized to the same luminosity 
  // and calcualtes the result of the ILC polarisation default options
  // 0=100% eL, 1=100% eR, 2=80%eL,30%pR, 2=80%eR,30%pL

  TH1F *hnew = (TH1F*)h1->Clone("hnew");
  float global=0, a=0., b=0.;
  float p1=-0.8, p2=0.3;

  if(pol==3) {
    p1=0.8;
    p2=-0.3;
  }


  global= 0.25* (1-p1*p2);
  float peff = (p1-p2)/(1-p1*p2);

  a=global*(1-peff);
  b=global*(1+peff);

  for(int i=0; i<hnew->GetNbinsX()+1; i++) {
    float nprime1=a*h1->GetBinContent(i);
    float nprime2=b*h2->GetBinContent(i);
    
    hnew->SetBinError(i,sqrt(nprime1+nprime2));
    hnew->SetBinContent(i, nprime1 + nprime2 );
  }
 
  return hnew;

}

TH2F * PolHisto(TH2F *h1, TH2F* h2, int pol) {

  // this function takes two histograms, 100% polarized, normalized to the same luminosity 
  // and calcualtes the result of the ILC polarisation default options
  // 0=100% eL, 1=100% eR, 2=80%eL,30%pR, 2=80%eR,30%pL

  TH2F *hnew = (TH2F*)h1->Clone("hnew");
  float global=0, a=0., b=0.;
  float p1=-0.8, p2=0.3;

  if(pol==3) {
    p1=0.8;
    p2=-0.3;
  }

  global= 0.25* (1-p1*p2);
  float peff = (p1-p2)/(1-p1*p2);

  a=global*(1-peff);
  b=global*(1+peff);

  for(int i=0; i<hnew->GetNbinsX()+1; i++) {
      for(int j=0; j<hnew->GetNbinsY()+1; j++) {

        float nprime1=a*h1->GetBinContent(i,j);
        float nprime2=b*h2->GetBinContent(i,j);
      
        hnew->SetBinError(i,j,sqrt(nprime1+nprime2));
        hnew->SetBinContent(i,j, nprime1 + nprime2 );
      }
  }
 
  return hnew;

}

std::vector<TH1F *> GetHisto1D(TString sample = "2f_hadronic_sample", int ipol = 0, int ibkg = 0, float lum = 900)
{

  TString pol[2] = {"eL_pR", "eR_pL"};

  std::vector<TH1F *> h1_pol[3];

  for (int i = 0; i < 2; i++)
  {

    TString filename = folder + "_" + sample + "_" + pol[i] + ".root";
    if (sample == "radreturn")
    {
      filename = folder + "_" + "2f_hadronic_sample_" + pol[i] + ".root";
      ibkg = 1;
    }
    if (sample == "qq")
    {
      filename = folder + "_" + "2f_hadronic_sample_" + pol[i] + ".root";
      ibkg = 1;
    }

    TFile *f = new TFile(filename);
    TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");
    if (sample == "radreturn")
    {
      TH1F *h_mjj = (TH1F *)f->Get("h_mjj_radreturn");
      TH1F *h_mj1_mj2 = (TH1F *)f->Get("h_mj1_mj2_radreturn");
      TH1F *h_y23 = (TH1F *)f->Get("h_y23_radreturn");
      TH1F *h_d23 = (TH1F *)f->Get("h_d23_radreturn");
      TH1F *h_thrust = (TH1F *)f->Get("h_thrust_radreturn");
      TH1F *h_major_thrust = (TH1F *)f->Get("h_major_thrust_radreturn");
      TH1F *h_minor_thrust = (TH1F *)f->Get("h_minor_thrust_radreturn");
      h1_pol[i].push_back(h_luminosity_cross_2f);
      h1_pol[i].push_back(h_mjj);
      h1_pol[i].push_back(h_mj1_mj2);
      h1_pol[i].push_back(h_y23);
      h1_pol[i].push_back(h_d23);
      h1_pol[i].push_back(h_thrust);
      h1_pol[i].push_back(h_major_thrust);
      h1_pol[i].push_back(h_minor_thrust);
    }
    else
    {
      TH1F *h_mjj = (TH1F *)f->Get("h_mjj_qq");
      TH1F *h_mj1_mj2 = (TH1F *)f->Get("h_mj1_mj2_qq");
      TH1F *h_y23 = (TH1F *)f->Get("h_y23_qq");
      TH1F *h_d23 = (TH1F *)f->Get("h_d23_qq");
      TH1F *h_thrust = (TH1F *)f->Get("h_thrust_qq");
      TH1F *h_major_thrust = (TH1F *)f->Get("h_major_thrust_qq");
      TH1F *h_minor_thrust = (TH1F *)f->Get("h_minor_thrust_qq");
      h1_pol[i].push_back(h_luminosity_cross_2f);
      h1_pol[i].push_back(h_mjj);
      h1_pol[i].push_back(h_mj1_mj2);
      h1_pol[i].push_back(h_y23);
      h1_pol[i].push_back(h_d23);
      h1_pol[i].push_back(h_thrust);
      h1_pol[i].push_back(h_major_thrust);
      h1_pol[i].push_back(h_minor_thrust);
    }

    float luminosity_sample = h_luminosity_cross_2f->GetEntries() / cross_section[i][ibkg];
    for (int j = 0; j < h1_pol[i].size(); j++) 
      h1_pol[i].at(j)->Scale(lum / luminosity_sample);
  }

  if(ipol<2) return h1_pol[ipol];

  for (int j = 0; j < h1_pol[0].size(); j++)  {
    h1_pol[2].push_back(PolHisto(h1_pol[0].at(j),h1_pol[1].at(j),ipol));
  }

  return h1_pol[2];
}

std::vector<TH2F *> GetHisto2D(TString sample = "2f_hadronic_sample", int ipol = 0, int ibkg = 0, float lum = 900)
{

  TString pol[2] = {"eL_pR", "eR_pL"};

  std::vector<TH2F *> h1_pol[3];

  for (int i = 0; i < 2; i++)
  {

    TString filename = folder + "_" + sample + "_" + pol[i] + ".root";
    if (sample == "radreturn")
    {
      filename = folder + "_" + "2f_hadronic_sample_" + pol[i] + ".root";
      ibkg = 1;
    }
    if (sample == "qq")
    {
      filename = folder + "_" + "2f_hadronic_sample_" + pol[i] + ".root";
      ibkg = 1;
    }

    TFile *f = new TFile(filename);
    TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");
    if (sample == "radreturn")
    {
      TH2F *h_major_minor_thrust = (TH2F *)f->Get("h_major_minor_thrust_radreturn");
      TH2F *h_costheta_energy = (TH2F *)f->Get("h_costheta_energy_radreturn");
      TH2F *h_npfos = (TH2F *)f->Get("h_npfos_radreturn");
      h1_pol[i].push_back(h_major_minor_thrust);
      h1_pol[i].push_back(h_costheta_energy);
      h1_pol[i].push_back(h_npfos);
    }
    else
    {
      TH2F *h_major_minor_thrust = (TH2F *)f->Get("h_major_minor_thrust_qq");
      TH2F *h_costheta_energy = (TH2F *)f->Get("h_costheta_energy_qq");
      TH2F *h_npfos = (TH2F *)f->Get("h_npfos_qq");
      h1_pol[i].push_back(h_major_minor_thrust);
      h1_pol[i].push_back(h_costheta_energy);
      h1_pol[i].push_back(h_npfos);
    }

    float luminosity_sample = h_luminosity_cross_2f->GetEntries() / cross_section[i][ibkg];
    for (int j = 0; j < h1_pol[i].size(); j++)
      h1_pol[i].at(j)->Scale(lum / luminosity_sample);
  }
  if(ipol<2) return h1_pol[ipol];

  for (int j = 0; j < h1_pol[0].size(); j++)  {
    h1_pol[2].push_back(PolHisto(h1_pol[0].at(j),h1_pol[1].at(j),ipol));
  }

  return h1_pol[2];  // Scale histograms with polarisation //to be done

}

void plots(int ipol = 2, int cuts = 0, float lum = 900)
{

  folder = TString::Format("../results/selection_cuts%i", cuts);

  TString samples[5] = {
      "qq",
      "radreturn",
      "4f_ZZ_hadronic",
      "qqH",
      "4f_WW_hadronic"};

  TString histo1d_titles[8] = {
      "",
      "M_{j_{1}j_{2}} [GeV]",
      "M_{j_{1}}+M_{j_{2}} [GeV]",
      "y23",
      "d23 [GeV]",
      "T-principle",
      "T-major",
      "T-minor"};

    TString histo2d_titles_x[3] = {
      "T-major",
      "cos #theta (photon-candidate)",
      " # pfos j_{1}"};
    TString histo2d_titles_y[3] = {
      "T-mimor",
      "E (photon candidate) [GeV] ",
      "# pfos j_{2}"};

  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  for (int isample = 0; isample < 5; isample++)
  {
    std::vector<TH1F *> h1_bkg_temp = GetHisto1D(samples[isample], ipol, isample + 1, lum);
    h1_bkg.push_back(h1_bkg_temp);
    std::vector<TH2F *> h2_bkg_temp = GetHisto2D(samples[isample], ipol, isample + 1, lum);
    h2_bkg.push_back(h2_bkg_temp);
  }

  for (int i = 0; i < h1_bkg.size(); i++)
  {
    cout << samples[i] << ": " << h1_bkg.at(i).at(1)->Integral() << " ";
  }
  cout << endl;

  SetQQbarStyle();
  // gStyle->SetOptFit(0);
  // gStyle->SetOptStat(0);
  // gStyle->SetTitleBorderSize(0);
  // gStyle->SetTitleX(0.2);
  // gStyle->SetMarkerSize(1.5);
  TGaxis::SetMaxDigits(3);

  for (int k = 1; k < 8; k++)
  {

    float xmin = 0.58, ymin = 0.7, xmax = 0.8, ymax = 0.9;
 
    TLegend *leg = new TLegend(xmin, 0.76, xmax, 0.9); //(0.4,0.3,0.5,0.6);
    leg->SetTextSize(0.035);

    TCanvas *canvas1 = new TCanvas(TString::Format("canvas_%i", k), TString::Format("canvas_%i", k), 800, 800);
    canvas1->cd(1);
    h1_bkg.at(0).at(k)->GetYaxis()->SetTitle("Entries");
    h1_bkg.at(0).at(k)->GetXaxis()->SetTitle(histo1d_titles[k]);

    for (int j = 0; j < h1_bkg.size(); j++)
    {
      h1_bkg.at(j).at(k)->SetLineColor(j + 1);
      h1_bkg.at(j).at(k)->SetLineWidth(2);
      if (j > 2)
      {
        h1_bkg.at(j).at(k)->SetLineStyle(2);
        h1_bkg.at(j).at(k)->SetLineWidth(4);
      }
      h1_bkg.at(j).at(k)->Draw("histosame");
      leg->AddEntry(h1_bkg.at(j).at(k), "#font[42]{" + samples[j]+"}", "l");
    }
    leg->SetFillStyle(0);
    leg->SetLineWidth(0);
    leg->SetLineColor(0);
    leg->SetBorderSize(0);

    Labels(k, ipol, lum);
    leg->Draw();
  }

  if (cuts == 3)
  {

    for (int k = 0; k < 1; k++)
    {

      gStyle->SetPadRightMargin(0.2);
      TCanvas *canvas1 = new TCanvas(TString::Format("canvas2d_%i", k), TString::Format("canvas2d_%i", k), 2400, 800);
      canvas1->Divide(3, 2);

      for (int j = 0; j < h2_bkg.size(); j++)
      {
        canvas1->cd(j + 1);
        h2_bkg.at(j).at(k)->GetXaxis()->SetTitle(histo2d_titles_x[k]);
        h2_bkg.at(j).at(k)->GetYaxis()->SetTitle(histo2d_titles_y[k]);
        h2_bkg.at(j).at(k)->Draw("colz");
        QQBARLabel2(0.2, 0.7, TString::Format("#font[42]{%s, aaN_{total}=%i}",samples[j].Data(),int(h1_bkg.at(j).at(0)->Integral())), kBlack);

        Labels(k, ipol, lum, 0.7);
      }
    }
  }
}

void selection_plots()
{

  float lum = 900;
  int pol = 3;
  cout << "Events for Polarization " << pol << " (0=left, 1=right, 2=80left,30right, 3=80right,30left) and Lum=" << lum << endl;
  for (int cuts = 3; cuts < 4; cuts++)
  {
    cout << cuts << " ";
    plots(pol,cuts, 900);
  }
}
