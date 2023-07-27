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
#include "histograms.h"

void plotsReco( int cuts = 0, float lum = 900)
{

  folder = TString::Format("../results/selection_cuts%i", cuts);

  TString samples[] = {
      "HV_qv100GeV",
      "HV_qv50GeV",
      "HV_qv10GeV",
      "qqSM"};


  //-------------------------------
  // 1d histograms to be plotted.. they have to exist in the selection_XXX.root file
  std::vector<TString> histonames = {"h_mjj", "h_mj1_mj2", "h_y23", "h_d23", "h_thrust", "h_major_thrust", "h_minor_thrust"};
  //labels
  TString histo1d_titles[] = {
      "",
      "M_{j_{1}j_{2}} [GeV]",
      "M_{j_{1}}+M_{j_{2}} [GeV]",
      "y23",
      "d23 [GeV]",
      "T-principle",
      "T-major",
      "T-minor"};


  //-------------------------------
  // 2d histograms to be plotted
  std::vector<TString> histonames_2d = {"h_nch", "h_npfos", "h_costheta_energy", "h_mw1_mw2", "h_major_minor_thrust", "h_npfos_minv"};

  //labels to be added to the 2d plots
  TString histo2d_titles_x[] = {
      "# tracks j_{1}",
      "# pfos j_{1}",
      "|cos #theta| most energetic #gamma_{cand}",
      "m_{W}^{cand.1} [GeV]",
      "T-major",
      "# pfos "};

  TString histo2d_titles_y[] = {
      "# tracks j_{2}",
      "# pfos j_{2}",
      "E most energetic #gamma_{cand} [GeV]",
      "m_{W}^{cand.2} [GeV]",
      "T-minor",
      "M_{j_{1}j_{2}} [GeV]"};

  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  for (int isample = 0; isample < sizeof(samples) / sizeof(TString); isample++)
  {

    std::vector<TH1F *> h1_bkg_temp = GetHisto1D(samples[isample], lum, histonames);
    h1_bkg.push_back(h1_bkg_temp);
    std::vector<TH2F *> h2_bkg_temp = GetHisto2D(samples[isample], lum, histonames_2d,false);
    h2_bkg.push_back(h2_bkg_temp);
  }

  for (int i = 0; i < h1_bkg.size(); i++)
  {
    cout << samples[i] << ": " << h1_bkg.at(i).at(1)->Integral() << " ";
  }
  cout << endl;

  SetQQbarStyle();
  TGaxis::SetMaxDigits(3);

  for (int k = 1; k < sizeof(histo1d_titles) / sizeof(TString); k++)
  {


        float xmin = 0.58, ymin = 0.7, xmax = 0.8, ymax = 0.9;

    TLegend *leg = new TLegend(xmin, 0.7, xmax, 0.9); //(0.4,0.3,0.5,0.6);
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
      if(histo1d_titles[k]=="T-principle") h1_bkg.at(j).at(k)->GetXaxis()->SetRangeUser(0.5,1);
      h1_bkg.at(j).at(k)->Draw("histosame");
      leg->AddEntry(h1_bkg.at(j).at(k), "#font[42]{" + samples[j] + "}", "l");
    }
    leg->SetFillStyle(0);
    leg->SetLineWidth(0);
    leg->SetLineColor(0);
    leg->SetBorderSize(0);

    LabelsReco();
    leg->Draw();
  }

  for (int k = 0; k < sizeof(histo2d_titles_y) / sizeof(TString); k++)
  {

    gStyle->SetPadRightMargin(0.2);
    TCanvas *canvas1 = new TCanvas(TString::Format("canvas2d_%i", k), TString::Format("canvas2d_%i", k), 2400, 800);
    canvas1->Divide(4, 2);

    for (int j = 0; j < h2_bkg.size(); j++)
    {
      canvas1->cd(j + 1);
      h2_bkg.at(j).at(k)->GetXaxis()->SetTitle(histo2d_titles_x[k]);
      h2_bkg.at(j).at(k)->GetYaxis()->SetTitle(histo2d_titles_y[k]);
      h2_bkg.at(j).at(k)->Draw("colz");
      QQBARLabel2(0.2, 0.85, TString::Format("#font[42]{%s, N_{total}=%i}", samples[j].Data(), int(h1_bkg.at(j).at(1)->Integral())), kRed);

      Labels();
    }
  }
}


void plotsProcLCWS2023(int cuts = 0)
{

  folder = TString::Format("../results/selectionPL_cuts%i", cuts);

  TString samples[] = {
      "qqSM",
      "HV_qv100GeV",
      "HV_qv50GeV",
      "HV_qv10GeV"};

    TString samples_labels[] = {
      "e^{+}e^{-}#rightarrow q#bar{q}",
      "e^{+}e^{-}#rightarrow D_{v}#bar{D}_{v}, m_{q_{v}}=100 GeV",
      "e^{+}e^{-}#rightarrow D_{v}#bar{D}_{v}, m_{q_{v}}= 50 GeV",
      "e^{+}e^{-}#rightarrow D_{v}#bar{D}_{v}, m_{q_{v}}= 10 GeV"};




  // 1d histograms:
  std::vector<TString> histonames = {"h_minv","h_nch","h_thrust"};//,"h_major_thrust","h_minor_thrust"};

  TString histo1d_titles[] = {
      "",
      "#sqrt{s}_{visible} [GeV]",
      "N_{ch.}",
      "T"};


  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  for (int isample = 0; isample < sizeof(samples) / sizeof(TString); isample++)
  {

    std::vector<TH1F *> h1_bkg_temp = GetHisto1D(samples[isample], 1000, histonames);//we use a random luminosity value of 1000 just to have a common noramlization
    h1_bkg.push_back(h1_bkg_temp);
  }

  for (int i = 0; i < h1_bkg.size(); i++)
  {
    cout << samples[i] << ": " << h1_bkg.at(i).at(1)->Integral() << " ";
  }
  cout << endl;

  SetQQbarStyle();
  TGaxis::SetMaxDigits(3);

  for (int k = 1; k < sizeof(histo1d_titles) / sizeof(TString); k++)
  {


        float xmin = 0.4, ymin = 0.7, xmax = 0.7, ymax = 0.9;

    TLegend *leg = new TLegend(xmin, 0.7, xmax, 0.9); //(0.4,0.3,0.5,0.6);
    leg->SetTextSize(0.035);

    TCanvas *canvas1 = new TCanvas(TString::Format("canvas_%i", k), TString::Format("canvas_%i", k), 800, 800);
    canvas1->cd(1);
    h1_bkg.at(1).at(k)->GetYaxis()->SetTitle("a.u.");
    h1_bkg.at(1).at(k)->GetXaxis()->SetTitle(histo1d_titles[k]);
    h1_bkg.at(1).at(k)->GetXaxis()->SetTitleOffset(1.5);

    

    for (int j = 1; j < h1_bkg.size()+1; j++)
    {

      if(j==h1_bkg.size()) j=0;
      if(k<3 && (j==0 || j==2 || j==3)) for(int ib=0; ib<2; ib++) h1_bkg.at(j).at(k)->SetBinContent(ib,0);//apparently there are some events with no visible energy at particle level, to be checked. I guess that this is a bug or very forward events (unlikely)
      h1_bkg.at(j).at(k)->SetLineColor(j + 1);
      h1_bkg.at(j).at(k)->SetLineWidth(2);
      if(j==0) {
        h1_bkg.at(j).at(k)->SetFillColor(j+1);
        h1_bkg.at(j).at(k)->SetFillStyle(3003);
      }
      if (j > 1)
      {
        h1_bkg.at(j).at(k)->SetLineStyle(j-1);
        h1_bkg.at(j).at(k)->SetLineWidth(j+2);
      }
      if(histo1d_titles[k]=="T") h1_bkg.at(j).at(k)->GetXaxis()->SetRangeUser(0.5,1);
      if(k==1) h1_bkg.at(j).at(k)->GetXaxis()->SetRangeUser(0,250);
      if(k==2) h1_bkg.at(j).at(k)->GetXaxis()->SetRangeUser(0,50);

      if(j==1 && k<3) h1_bkg.at(j).at(k)->GetYaxis()->SetRangeUser(0,h1_bkg.at(j).at(k)->GetMaximum()*1.5);
      if(j==1 && k==3) h1_bkg.at(j).at(k)->GetYaxis()->SetRangeUser(0,h1_bkg.at(j).at(k)->GetMaximum()*10);

      h1_bkg.at(j).at(k)->DrawNormalized("histosame");
      //h1_bkg.at(j).at(k)->DrawNormalized("csame");

      if(j==0) leg->AddEntry(h1_bkg.at(j).at(k), "#font[42]{" + samples_labels[j] + "}", "f");
      else leg->AddEntry(h1_bkg.at(j).at(k), "#font[42]{" + samples_labels[j] + "}", "l");
      if(j==0) break;
    }
    leg->SetFillStyle(0);
    leg->SetLineWidth(0);
    leg->SetLineColor(0);
    leg->SetBorderSize(0);

    Labels();
    leg->Draw();

    canvas1->Print(TString::Format("%s.eps",histonames[k-1].Data()));
  }

}

void selection_plots()
{

  float lum = 900;
  int pol = 0;
  cout << "Events for Polarization " << pol << " (0=left, 1=right, 2=80left,30right, 3=80right,30left) and Lum=" << lum << endl;
  for (int cuts = 0; cuts < 1; cuts++)
  {
    cout << cuts << " ";
    plotsReco(cuts);
    //plotsProcLCWS2023(cuts);

  }
}
