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

TString energy="250GeV";
void Labels(TString pol)
{
  QQBARLabel(0.86, 0.954, "");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if (pol == "eL")
    QQBARLabel2(0.3, 0.965, "e^{-}e^{+} #rightarrow c#bar{c} mc-2020", kGray + 2);
  else if (pol == "eR")
    QQBARLabel2(0.3, 0.965, "e_{R}^{-}e_{L}^{+} #rightarrow c#bar{c} mc-2020", kGray + 2);
  else
    QQBARLabel2(0.15, 0.965, "e^{-}e^{+} #rightarrow q#bar{q} (q=uds,c,b same size samples)", kGray + 2);

  // QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);
}

void Plots()
{

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.);
  // TGaxis::SetMaxDigits(2);

  TString filename = "../results_"+energy+"_2023/jettag_cuts5_2f_hadronic_eL_pR.root";
  TFile *f = new TFile(filename);
  TH1F *btag[40][2];
  TH1F *ctag[40][2];
  for (int i = 0; i < 40; i++)
  {
    btag[i][0] = (TH1F *)f->Get(TString::Format("h_jet_btag_%i", i));
    ctag[i][0] = (TH1F *)f->Get(TString::Format("h_jet_ctag_%i", i));
  }

  filename = "../results_"+energy+"_2023/jettag_cuts5_2f_hadronic_eR_pL.root";
  TFile *f2 = new TFile(filename);

  for (int i = 0; i < 40; i++)
  {
    btag[i][1] = (TH1F *)f2->Get(TString::Format("h_jet_btag_%i", i));
    ctag[i][1] = (TH1F *)f2->Get(TString::Format("h_jet_ctag_%i", i));
  }

  float x[40], eff_b[2][3][40], eff_c[2][3][40];
  float eff2_b[2][3][40], eff2_c[2][3][40];
  float WP_b[2], WP_c[2];
  float y2[2];
  y2[0]=-10;
  y2[1]=110;
  WP_b[0]=0.85;
  WP_b[1]=0.85;
  WP_c[0]=0.875;
  WP_c[1]=0.875;

  int n = 0;
  for (int i = 0; i < 40; i++)
  {
    x[n] = i * 0.025;
    float ntotal[3];
    float nb[3];
    float nc[3];
    for (int iflav = 0; iflav < 3; iflav++)
    {
      int quark = 0;
      if (iflav == 1)
        quark = 4;
      if (iflav == 2)
        quark = 5;

      for (int ipol = 0; ipol < 2; ipol++)
      {
        ntotal[iflav] = btag[0][ipol]->GetBinContent(quark + 1);

        nb[iflav] = btag[n][ipol]->GetBinContent(quark + 1);
        nc[iflav] = ctag[n][ipol]->GetBinContent(quark + 1);

        eff_b[ipol][iflav][n] = 100. * nb[iflav] / ntotal[iflav];
        eff_c[ipol][iflav][n] = 100. * nc[iflav] / ntotal[iflav];
        eff2_b[ipol][iflav][n] = 100. - 100. * nb[iflav] / ntotal[iflav];
        eff2_c[ipol][iflav][n] = 100. - 100. * nc[iflav] / ntotal[iflav];
      }
    }
    n++;
  }

  TGraph *efficiency_b_b_eL = new TGraph(n, x, eff_b[0][2]);
  TGraph *efficiency_c_b_eL = new TGraph(n, x, eff2_b[0][1]);
  TGraph *efficiency_uds_b_eL = new TGraph(n, x, eff2_b[0][0]);

  TGraph *efficiency_b_b_eR = new TGraph(n, x, eff_b[1][2]);
  TGraph *efficiency_c_b_eR = new TGraph(n, x, eff2_b[1][1]);
  TGraph *efficiency_uds_b_eR = new TGraph(n, x, eff2_b[1][0]);

  TGraph *g_WP_b = new TGraph(2,WP_b,y2);

  TCanvas *c_eff_b = new TCanvas("c_eff_b", "c_eff_b", 800, 800);
  c_eff_b->cd(1);
  // gPad->SetLogy();
  efficiency_b_b_eL->GetXaxis()->SetTitle("btag_{cut}");
  efficiency_b_b_eL->GetYaxis()->SetTitle("[%]");
  efficiency_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  efficiency_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  efficiency_b_b_eL->GetYaxis()->SetRangeUser(0, 101);
  efficiency_b_b_eL->GetXaxis()->SetRangeUser(0, 1);

  efficiency_b_b_eL->SetLineColor(4);
  efficiency_b_b_eL->SetLineWidth(4);
  efficiency_b_b_eL->SetLineStyle(1);
  efficiency_b_b_eL->Draw("alp");

  efficiency_c_b_eL->SetLineColor(kGreen + 1);
  efficiency_c_b_eL->SetLineWidth(1);
  efficiency_c_b_eL->SetLineStyle(1);
  efficiency_c_b_eL->Draw("lp");

  efficiency_uds_b_eL->SetLineColor(2);
  efficiency_uds_b_eL->SetLineWidth(4);
  efficiency_uds_b_eL->SetLineStyle(7);
  efficiency_uds_b_eL->Draw("lp");

  g_WP_b->SetLineColor(kGray);
  g_WP_b->SetLineWidth(2);
  g_WP_b->SetLineStyle(2);
  g_WP_b->SetMarkerStyle(0);
  g_WP_b->Draw("l");

  /*efficiency_b_b_eR->SetLineColor(4);
  efficiency_b_b_eR->SetLineWidth(3);
  efficiency_b_b_eR->SetLineStyle(2);
  efficiency_b_b_eR->Draw("lp");

  efficiency_c_b_eR->SetLineColor(kGreen+2);
  efficiency_c_b_eR->SetLineWidth(3);
  efficiency_c_b_eR->SetLineStyle(2);
  efficiency_c_b_eR->Draw("lp");

  efficiency_uds_b_eR->SetLineColor(2);
  efficiency_uds_b_eR->SetLineWidth(3);
  efficiency_uds_b_eR->SetLineStyle(2);
  efficiency_uds_b_eR->Draw("lp");*/

  btag[1][1]->SetLineColor(1);
  btag[1][1]->SetLineStyle(1);
  btag[1][2]->SetLineColor(1);
  btag[1][2]->SetLineStyle(2);
  btag[1][2]->SetLineWidth(2);
  btag[1][1]->SetLineWidth(2);

  Labels("");

  TLegend *leg_b = new TLegend(0.55, 0.25, 0.7, 0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(efficiency_b_b_eL, "#varepsilon_{b}", "l");
  leg_b->AddEntry(efficiency_c_b_eL, "1-#tilde{#varepsilon}_{c}", "l");
  leg_b->AddEntry(efficiency_uds_b_eL, "1-#tilde{#varepsilon}_{uds}", "l");
  leg_b->AddEntry(g_WP_b, "working point", "l");
  // leg_b->AddEntry(btag[1][1],"e_{L}^{-}e_{R}^{+}","l");
  // leg_b->AddEntry(btag[1][2],"e_{R}^{-}e_{L}^{+}","l");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_eff_b->Print("plots_"+energy+"_2023/btagging_performance.eps");

  ///---------------------------------------------
  TGraph *efficiency_c_c_eL = new TGraph(n, x, eff_c[0][1]);
  TGraph *efficiency_b_c_eL = new TGraph(n, x, eff2_c[0][2]);
  TGraph *efficiency_uds_c_eL = new TGraph(n, x, eff2_c[0][0]);

  TGraph *efficiency_c_c_eR = new TGraph(n, x, eff_c[1][1]);
  TGraph *efficiency_b_c_eR = new TGraph(n, x, eff2_c[1][2]);
  TGraph *efficiency_uds_c_eR = new TGraph(n, x, eff2_c[1][0]);

  TGraph *g_WP_c = new TGraph(2,WP_c,y2);

  TCanvas *c_eff_c = new TCanvas("c_eff_c", "c_eff_c", 800, 800);
  c_eff_c->cd(1);
  // gPad->SetLogy();
  //  c_eff_c->SetGrid();
  efficiency_c_c_eL->GetXaxis()->SetTitle("ctag_{cut}");
  efficiency_c_c_eL->GetYaxis()->SetTitle("[%]");
  efficiency_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  efficiency_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  efficiency_c_c_eL->GetYaxis()->SetRangeUser(0, 101);
  efficiency_c_c_eL->GetXaxis()->SetRangeUser(0, 1);

  efficiency_c_c_eL->SetLineColor(4);
  efficiency_c_c_eL->SetLineWidth(4);
  efficiency_c_c_eL->SetLineStyle(1);
  efficiency_c_c_eL->Draw("al");

  efficiency_b_c_eL->SetLineColor(kGreen + 1);
  efficiency_b_c_eL->SetLineWidth(1);
  efficiency_b_c_eL->SetLineStyle(1);
  efficiency_b_c_eL->Draw("l");

  efficiency_uds_c_eL->SetLineColor(2);
  efficiency_uds_c_eL->SetLineWidth(4);
  efficiency_uds_c_eL->SetLineStyle(2);
  efficiency_uds_c_eL->Draw("l");

  g_WP_c->SetLineColor(kGray);
  g_WP_c->SetLineWidth(2);
  g_WP_c->SetLineStyle(2);
  g_WP_c->SetMarkerStyle(0);
  g_WP_c->Draw("l");

  /*efficiency_c_c_eR->SetLineColor(4);
  efficiency_c_c_eR->SetLineWidth(3);
  efficiency_c_c_eR->SetLineStyle(2);
  efficiency_c_c_eR->Draw("l");

  efficiency_b_c_eR->SetLineColor(kGreen+2);
  efficiency_b_c_eR->SetLineWidth(3);
  efficiency_b_c_eR->SetLineStyle(2);
  efficiency_b_c_eR->Draw("l");

  efficiency_uds_c_eR->SetLineColor(2);
  efficiency_uds_c_eR->SetLineWidth(3);
  efficiency_uds_c_eR->SetLineStyle(2);
  efficiency_uds_c_eR->Draw("l");*/

  ctag[1][1]->SetLineColor(1);
  ctag[1][1]->SetLineStyle(1);
  ctag[1][2]->SetLineColor(1);
  ctag[1][2]->SetLineStyle(2);

  Labels("");

  TLegend *leg_c = new TLegend(0.55, 0.25, 0.7, 0.45);
  leg_c->SetTextSize(0.035);
  leg_c->SetTextFont(42);
  leg_c->AddEntry(efficiency_c_c_eL, "#varepsilon_{c}", "l");
  leg_c->AddEntry(efficiency_b_c_eL, "1-#tilde{#varepsilon}_{b}", "l");
  leg_c->AddEntry(efficiency_uds_c_eL, "1-#tilde{#varepsilon}_{uds}", "l");
  leg_c->AddEntry(g_WP_c, "working point", "l");
  // leg_c->AddEntry(btag[1][1],"e_{L}^{-}e_{R}^{+}","l");
  // leg_c->AddEntry(btag[1][2],"e_{R}^{-}e_{L}^{+}","l");
  leg_c->SetFillColor(0);
  leg_c->SetLineColor(0);
  leg_c->SetShadowColor(0);
  leg_c->Draw();
  c_eff_c->Print("plots_"+energy+"_2023/ctagging_performance.eps");
}

void JetTag()
{

  Plots();
}
