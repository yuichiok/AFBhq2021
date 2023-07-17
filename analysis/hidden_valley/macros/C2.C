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
      "radreturn",
      "qq"};

  TString histo1d_titles[] = {
      "",
      "",
      "# charged PFOs",
      "|#vec{p}_{PFOs}| [GeV]"};


void plotsN(int ipol = 2, int cuts = 0, float lum = 900)
{


  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  for (int isample = 0; isample < sizeof(samples)/sizeof(TString); isample++)
  {
    int sample_index=isample;
    if(isample>2) sample_index=isample + 1;
    std::vector<TH1F *> h1_bkg_temp = GetHisto1D(samples[isample], ipol, sample_index, lum,{"ncharged","mom"},false);
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

  for (int k = 1; k < sizeof(histo1d_titles) / sizeof(TString); k++)
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

void plotsC2(int ipol = 2, int cuts = 0, float lum = 900, bool MC=false, bool Yield=true)
{

  std::vector<std::vector<TH1F *>> h1_bkg;
  std::vector<std::vector<TH2F *>> h2_bkg;

  std::vector<TString> histos_1d={"h_costheta_cuts","ncharged","mom"};
  std::vector<TString> histos_2d={"S2_rapidity","B2_rapidity","S2_rapidity"};

  for (int isample = 0; isample < sizeof(samples)/sizeof(TString); isample++)
  {
    cout<<samples[isample]<<endl;
    int sample_index=isample;
    //if(isample>3) sample_index=isample + 1;
    std::vector<TH1F *> h1_bkg_temp = GetHisto1D(samples[isample], ipol, sample_index , lum,histos_1d,false);
    h1_bkg.push_back(h1_bkg_temp);
    std::vector<TH2F *> h2_bkg_temp = GetHisto2D(samples[isample], ipol, sample_index , lum,histos_2d,false,false);
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

  if(Yield==false)
  {

    for(int i=0; i<h2_bkg.size(); i++) {
      h2_bkg.at(i).at(2)->Divide(h2_bkg.at(i).at(1));
    }
    for (int k = 2; k < 3; k++)
    {

      //gStyle->SetPadRightMargin(0.2);
      gStyle->SetOptTitle(0);


      for (int j = 0; j < h2_bkg.size(); j++)
      {
        TCanvas *canvas1 = new TCanvas(TString::Format("canvas2d_%i_%i", k,j), TString::Format("canvas2d_%i_%i", k,j), 800, 800);
        canvas1->cd();
        //gPad->SetLogz();
        //h2_bkg.at(j).at(k)->GetXaxis()->SetTitle(histo2d_titles_x[k]);
        //h2_bkg.at(j).at(k)->GetYaxis()->SetTitle(histo2d_titles_y[k]);
        if(k==0) h2_bkg.at(j).at(k)->SetTitle("S_{2} }");
        if(k==1) h2_bkg.at(j).at(k)->SetTitle("B_{2} ");
        if(k==2) h2_bkg.at(j).at(k)->SetTitle("C_{2}");
        h2_bkg.at(j).at(k)->Draw("surf3");
        if(k==2) h2_bkg.at(j).at(k)->GetZaxis()->SetRangeUser(0,2.5);
        h2_bkg.at(j).at(k)->GetXaxis()->SetTitleOffset(1.5);
        h2_bkg.at(j).at(k)->GetYaxis()->SetTitleOffset(1.5);
        h2_bkg.at(j).at(k)->GetZaxis()->SetTitleOffset(1.5);

        //h2_bkg.at(j).at(k)->Draw("colz");

        QQBARLabel2(0.3, 0.05, TString::Format("#font[42]{%s, N_{events}=%i}",samples[j].Data(),int(h1_bkg.at(j).at(1)->Integral())), kRed);

        Labels(cuts, ipol, lum, 0.7);
        canvas1->Print(TString::Format("Correlations_%s_cuts%i.eps",samples[j].Data(),cuts));
      }
    }
  } else {

    gStyle->SetPadRightMargin(0.2);
    gStyle->SetOptTitle(0);


    TH1F* htemp[10][10]; 
    TH1F* htemp2[10][10]; 


    for (int j = 0; j < h2_bkg.size(); j++)
    {

      TCanvas *canvas1 = new TCanvas(TString::Format("canvas2d_%i", j), TString::Format("canvas2d_%i",j), 800, 800);
      canvas1->cd();

      TLegend *leg = new TLegend(0.5, 0.8, 0.9, 0.9); //(0.4,0.3,0.5,0.6);
      leg->SetTextSize(0.035);

      for(int i=0; i<2; i++) {
        if(i==0) {
          htemp[j][i] =(TH1F*)h2_bkg.at(j).at(0)->ProjectionY(TString::Format("htemp_%i_%i",j,i),0,16);
          htemp2[j][i] =(TH1F*)h2_bkg.at(j).at(1)->ProjectionY(TString::Format("htemp2_%i_%i",j,i),0,16);
        }

        if(i==1) {
          htemp[j][i] =(TH1F*)h2_bkg.at(j).at(0)->ProjectionY(TString::Format("htemp_%i_%i",j,i),16,30);
          htemp2[j][i] =(TH1F*)h2_bkg.at(j).at(1)->ProjectionY(TString::Format("htemp2_%i_%i",j,i),16,30);
        }
        htemp[j][i]->Divide(htemp2[j][i]);
        htemp[j][i]->SetLineColor(i+1);
        htemp[j][i]->SetLineWidth(2);
        htemp[j][i]->Draw("histosame");
        htemp[j][i]->GetYaxis()->SetRangeUser(0,2);
        htemp[j][i]->GetYaxis()->SetTitle("Yield");
        if(i==0) leg->AddEntry(htemp[j][i],"0<|#Delta y|<1.6");
        if(i==1) leg->AddEntry(htemp[j][i],"1.6<|#Delta y|<3");

        //htemp[j][i]->GetXaxis()->SetTitleOffset(1.5);
        //htemp[j][i]->GetYaxis()->SetTitleOffset(1.5);
        //htemp[j][i]->GetZaxis()->SetTitleOffset(1.5);
      }
      leg->SetFillStyle(0);
      leg->SetLineWidth(0);
      leg->SetLineColor(0);
      leg->SetBorderSize(0);

      leg->Draw();

      QQBARLabel2(0.3, 0.05, TString::Format("#font[42]{%s, N_{events}=%i}",samples[j].Data(),int(h1_bkg.at(j).at(1)->Integral())), kRed);

      Labels(cuts, ipol, lum, 0.7);
      canvas1->Print(TString::Format("Yield%s_cuts%i.eps",samples[j].Data(),cuts));

    }
  }




}

void C2()
{


  float lum = 900;
  int pol = 2;
  cout << "Events for Polarization " << pol << " (0=left, 1=right, 2=80left,30right, 3=80right,30left) and Lum=" << lum << endl;
  int cuts = 0;
  folder = TString::Format("../results/QCDcorrelations_cuts%i", cuts);
  cout << cuts << " ";
  plotsC2(pol,cuts, 900,true,true);
  
}
