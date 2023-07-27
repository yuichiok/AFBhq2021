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


  TString samples[] = {
      "HV_qv100GeV",
      "HV_qv50GeV",
      "HV_qv10GeV",
      "qqSM"};

TString samples_labels[] = {
    "e^{+}e^{-}#rightarrow D_{v}#bar{D}_{v}, m_{q_{v}}=100 GeV",
    "e^{+}e^{-}#rightarrow D_{v}#bar{D}_{v}, m_{q_{v}}= 50 GeV",
    "e^{+}e^{-}#rightarrow D_{v}#bar{D}_{v}, m_{q_{v}}= 10 GeV",
    "e^{+}e^{-}#rightarrow q#bar{q}"};

TString histo1d_titles[] = {
    "",
    "",
    "# charged PFOs",
    "|#vec{p}_{PFOs}| [GeV]"};


TH1F * GetYield(TString sample_input, bool MC=false){

  TString sufix = "_rapidity";
  if (MC == true)
    sufix = "_MC_rapidity";

  std::vector<TString> histos_2d = {"S2" + sufix, "B2" + sufix};

  float expected_luminosity=2000;
  std::vector<TH2F *> h2_sig_temp = GetHisto2D(sample_input,expected_luminosity , histos_2d,true);
  std::vector<TH2F *> h2_bkg_temp = GetHisto2D("qqSM", expected_luminosity, histos_2d,true);//we use the SM as background always

   // gStyle->SetPadRightMargin(0.2);
    gStyle->SetOptTitle(0);

    TH1F *htemp;
    TH1F *htemp2;

    htemp = (TH1F *)h2_sig_temp.at(0)->ProjectionY("htemp", 16, 30);
    htemp2 = (TH1F *)h2_bkg_temp.at(1)->ProjectionY("htemp2", 16, 30);
   for(int i=0; i<htemp->GetNbinsX()+1; i++ ) {
    if(htemp2->GetBinContent(i)!=0 && htemp->GetBinContent(i)!=0 ) {
        double a=htemp->GetBinContent(i);
        double b=htemp2->GetBinContent(i);
        double ea=htemp->GetBinError(i);
        double eb=htemp2->GetBinError(i);
        htemp->SetBinError(i,sqrt(pow(ea/b,2)+pow(a*eb/(b*b),2)));
        htemp->SetBinContent(i,htemp->GetBinContent(i)/htemp2->GetBinContent(i));

    } else {
      htemp->SetBinContent(i,0);
      htemp->SetBinError(i,0);
    }
    }
   // htemp->Divide(htemp2);
    return htemp;

}

void CompareYield(int isample=0) {

  SetQQbarStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetTitleStyle(0);
  // gStyle->SetOptFit(0);
  // gStyle->SetOptStat(0);
  // gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleY(0.9);
  gStyle->SetMarkerSize(0);
  TGaxis::SetMaxDigits(3);

  TH1F* yield_reco=GetYield(samples[isample],false);
  TH1F* yield_mc=GetYield(samples[isample],true);

  TLegend *leg = new TLegend(0.6, 0.7, 0.8, 0.9,"#font[42]{" + samples[isample] + "}"); //(0.4,0.3,0.5,0.6);
  leg->SetTextSize(0.035);
  TCanvas *canvas1 = new TCanvas("yieldcanvas", "yieldcanvas", 800, 800);
  canvas1->cd();


  yield_reco->Draw("histoe");
  yield_mc->SetLineColor(2);
  yield_mc->SetMarkerColor(2);
  //yield_mc->SetMarkerStyle(2);
  yield_mc->Draw("pesame");

  leg->AddEntry(yield_reco, "#font[42]{Reco Level}", "l");
  leg->AddEntry(yield_mc, "#font[42]{MC Level}", "l");
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetBorderSize(0);
  leg->Draw();

}

void plotsC2LCWS2023(int cuts = 0, float lum = 900, bool MC = false, bool Yield = true)
{

  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  std::vector<TString> histos_1d = {"h_costheta_cuts", "ncharged", "mom"};
  TString sufix = "_rapidity";
  if (MC == true)
    sufix = "_MC_rapidity";
  std::vector<TString> histos_2d = {"S2" + sufix, "B2" + sufix};

  for (int isample = 0; isample < sizeof(samples) / sizeof(TString); isample++)
  {
    cout << samples[isample] << endl;
    std::vector<TH1F *> h1_bkg_temp = GetHisto1D(samples[isample], lum, histos_1d);
    h1_bkg.push_back(h1_bkg_temp);
    std::vector<TH2F *> h2_bkg_temp = GetHisto2D(samples[isample], lum, histos_2d,true);

    h2_bkg.push_back(h2_bkg_temp);
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

  if (Yield == false)
  {

    for (int i = 0; i < h2_bkg.size(); i++)
    {
      h2_bkg.at(i).at(0)->Divide(h2_bkg.at(3).at(1));
    }
    for (int k = 0; k < 1; k++)
    {

      // gStyle->SetPadRightMargin(0.2);
      gStyle->SetOptTitle(0);

      for (int j = 0; j < h2_bkg.size(); j++)
      {
        TCanvas *canvas1 = new TCanvas(TString::Format("canvas2d_%i_%i", k, j), TString::Format("canvas2d_%i_%i", k, j), 800, 800);
        canvas1->cd();
        // gPad->SetLogz();
        // h2_bkg.at(j).at(k)->GetXaxis()->SetTitle(histo2d_titles_x[k]);
        // h2_bkg.at(j).at(k)->GetYaxis()->SetTitle(histo2d_titles_y[k]);
        h2_bkg.at(j).at(k)->Draw("surf3");
        h2_bkg.at(j).at(k)->GetZaxis()->SetRangeUser(0, 5);
        h2_bkg.at(j).at(k)->GetXaxis()->SetTitleOffset(1.5);
        h2_bkg.at(j).at(k)->GetYaxis()->SetTitleOffset(1.5);
        h2_bkg.at(j).at(k)->GetZaxis()->SetTitleOffset(1.5);
        h2_bkg.at(j).at(k)->GetZaxis()->SetTitle("C^{(2)}(#Deltay, #Delta#phi)");
        h2_bkg.at(j).at(k)->GetYaxis()->SetTitle("#Delta#phi");
        h2_bkg.at(j).at(k)->GetXaxis()->SetTitle("#Deltay");
	      h2_bkg.at(j).at(k)->GetXaxis()->SetRangeUser(-3,3);

        // h2_bkg.at(j).at(k)->Draw("colz");

        QQBARLabel2(0.6, 0.05, TString::Format("#font[42]{%s}", samples_labels[j].Data()), kRed + 2);

      Labels();
        canvas1->Print(TString::Format("Correlations_%s_cuts%i.eps", samples[j].Data(), cuts));
      }
    }
  }
  else
  {

    // gStyle->SetPadRightMargin(0.2);
    gStyle->SetOptTitle(0);

    TH1F *htemp[10][10];
    TH1F *htemp2[10][10];

    for (int i = 0; i < 2; i++) // cuts
    {
      TCanvas *canvas1 = new TCanvas("yieldcanvas", "yieldcanvas", 800, 800);
      canvas1->cd();

      TLegend *leg = new TLegend(0.45, 0.7, 0.85, 0.9); //(0.4,0.3,0.5,0.6);
      leg->SetTextSize(0.035);

      for (int j = 0; j < h2_bkg.size(); j++)
      {

        if (i == 0)
        {
          htemp[j][i] = (TH1F *)h2_bkg.at(j).at(0)->ProjectionY(TString::Format("htemp_%i_%i", j, i), 0, 16);
          htemp2[j][i] = (TH1F *)h2_bkg.at(3).at(1)->ProjectionY(TString::Format("htemp2_%i_%i", j, i), 0, 16);
        }

        if (i == 1)
        {
          htemp[j][i] = (TH1F *)h2_bkg.at(j).at(0)->ProjectionY(TString::Format("htemp_%i_%i", j, i), 16, 30);
          htemp2[j][i] = (TH1F *)h2_bkg.at(3).at(1)->ProjectionY(TString::Format("htemp2_%i_%i", j, i), 16, 30);
        }
        htemp[j][i]->Divide(htemp2[j][i]);

        if (j == 0)
        {
          htemp[j][i]->SetLineColor(2);
          htemp[j][i]->SetLineWidth(2);
        }
        if (j == 1)
        {
          htemp[j][i]->SetLineColor(3);
          htemp[j][i]->SetLineWidth(4);
        }
        if (j == 2)
        {
          htemp[j][i]->SetLineColor(4);
          htemp[j][i]->SetLineWidth(4);
          htemp[j][i]->SetLineStyle(5);
        }
        if (j == 3)
        {
          htemp[j][i]->SetFillColor(1);
          htemp[j][i]->SetLineColor(1);
          htemp[j][i]->SetLineWidth(2);
          htemp[j][i]->SetFillStyle(3003);
        }

        htemp[j][i]->Draw("histosame");
        if(i==1) htemp[j][i]->GetYaxis()->SetRangeUser(0, 4);
        if(i==0) htemp[j][i]->GetYaxis()->SetRangeUser(0, 10);
        if (i == 1)
          htemp[j][i]->GetYaxis()->SetTitle("Yield, 1.6<|#Delta y|<3");
        if (i == 0)
          htemp[j][i]->GetYaxis()->SetTitle("Yield,   0<|#Delta y|<1.6");

        // htemp[j][i]->GetXaxis()->SetTitleOffset(1.5);
        // htemp[j][i]->GetYaxis()->SetTitleOffset(1.5);
        // htemp[j][i]->GetZaxis()->SetTitleOffset(1.5);
        if (j == 3)
          leg->AddEntry(htemp[j][i], "#font[42]{" + samples_labels[j] + "}", "f");
        else
          leg->AddEntry(htemp[j][i], "#font[42]{" + samples_labels[j] + "}", "l");
      }
      leg->SetFillStyle(0);
      leg->SetLineWidth(0);
      leg->SetLineColor(0);
      leg->SetBorderSize(0);

      leg->Draw();

      Labels();
      canvas1->Print(TString::Format("Yield_range%i.eps", i));
    }
  }
}

void C2()
{

  float lum = 900;
  int pol = 0;
  cout << "Events for Polarization " << pol << " (0=left, 1=right, 2=80left,30right, 3=80right,30left) and Lum=" << lum << endl;
  int cuts = 0;
  folder = TString::Format("../results/QCDcorrelations_cuts%i", cuts);
  cout << cuts << " ";
  plotsC2LCWS2023( cuts, 900, true, true);

  //CompareYield(0);
  
}


