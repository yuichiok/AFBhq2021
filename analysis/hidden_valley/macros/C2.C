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

  TString samples[4] = {
      "qq_radreturn",
      "4f_ZZ_hadronic",
      "qqH",
      "4f_WW_hadronic"};

  TString histo1d_titles[4] = {
      "",
      "",
      "# charged PFOs",
      "|#vec{p}_{PFOs}| [GeV]"};


void plotsN(int ipol = 2, int cuts = 0, float lum = 900)
{


  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  for (int isample = 0; isample < 4; isample++)
  {
    std::vector<TH1F *> h1_bkg_temp = GetHisto1D_2(samples[isample], ipol, isample + 2, lum,{"h_costheta_cuts","ncharged","mom"});
    h1_bkg.push_back(h1_bkg_temp);
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

  for (int k = 2; k < 4; k++)
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

    Labels(cuts, ipol, lum);
    leg->Draw();
  }

}

void plotsC2(int ipol = 2, int cuts = 0, float lum = 900)
{

  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  for (int isample = 0; isample < 4; isample++)
  {
    std::vector<TH1F *> h1_bkg_temp = GetHisto1D_2(samples[isample], ipol, isample + 2, lum,{"h_costheta_cuts","ncharged","mom"});
    h1_bkg.push_back(h1_bkg_temp);
    std::vector<TH2F *> h2_bkg_temp = GetHisto2D_2(samples[isample], ipol, isample + 2, lum,{"S2","B2","S2"});
    h2_bkg.push_back(h2_bkg_temp);
  }

  for(int i=0; i<h2_bkg.size(); i++) {
    h2_bkg.at(i).at(0)->Rebin2D(50);
    h2_bkg.at(i).at(1)->Rebin2D(50);
    h2_bkg.at(i).at(2)->Rebin2D(50);

    h2_bkg.at(i).at(2)->Divide(h2_bkg.at(i).at(1));

    //h2_bkg.at(i).at(0)->Scale(1./h1_bkg.at(i).at(1)->Integral()); 
    //h2_bkg.at(i).at(1)->Scale(1./h1_bkg.at(i).at(1)->Integral()); 
  }

  for (int i = 0; i < h1_bkg.size(); i++)
  {
    cout << samples[i] << ": " << h1_bkg.at(i).at(1)->Integral() << " ";
  }
  cout << endl;

  SetQQbarStyle();
  gStyle->SetOptTitle(1);
  gStyle->SetTitleStyle(0);
  // gStyle->SetOptFit(0);
  // gStyle->SetOptStat(0);
  // gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleY(0.9);
  // gStyle->SetMarkerSize(1.5);
  TGaxis::SetMaxDigits(3);

    for (int k = 0; k < 3; k++)
  {

    gStyle->SetPadRightMargin(0.2);
    TCanvas *canvas1 = new TCanvas(TString::Format("canvas2d_%i", k), TString::Format("canvas2d_%i", k), 2400, 800);
    canvas1->Divide(3, 2);

    for (int j = 0; j < h2_bkg.size(); j++)
    {
      canvas1->cd(j + 1);
      gPad->SetLogz();
      //h2_bkg.at(j).at(k)->GetXaxis()->SetTitle(histo2d_titles_x[k]);
      //h2_bkg.at(j).at(k)->GetYaxis()->SetTitle(histo2d_titles_y[k]);
      if(k==0) h2_bkg.at(j).at(k)->SetTitle("S_{2} }");
      if(k==1) h2_bkg.at(j).at(k)->SetTitle("B_{2} ");
      if(k==2) h2_bkg.at(j).at(k)->SetTitle("C_{2}");
     // h2_bkg.at(j).at(k)->Draw("surf1");
      h2_bkg.at(j).at(k)->Draw("surf3");

      QQBARLabel2(0.3, 0.05, TString::Format("#font[42]{%s, N_{events}=%i}",samples[j].Data(),int(h1_bkg.at(j).at(1)->Integral())), kRed);

      Labels(cuts, ipol, lum, 0.7);
    }
  }

}

void C2()
{


  float lum = 900;
  int pol = 2;
  cout << "Events for Polarization " << pol << " (0=left, 1=right, 2=80left,30right, 3=80right,30left) and Lum=" << lum << endl;
  int cuts = 4;
  folder = TString::Format("../results/QCDcorrelations_cuts%i", cuts);
  cout << cuts << " ";
  plotsC2(pol,cuts, 900);
  
}
