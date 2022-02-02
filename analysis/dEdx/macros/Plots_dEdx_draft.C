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


bool cquark;
int iquark=3;

void Labels(TString pol){
  // QQBARLabel(0.86,0.952,"Work in Progress");
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(iquark==5) {
    if(pol=="eL")
      QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow b#bar{b}",kGray+2);
    else 
      if(pol=="eR")
	QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow b#bar{b}",kGray+2);
      else 
	QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow b#bar{b}",kGray+2);
  }

  if(iquark==4) {
    if(pol=="eL")
      QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow c#bar{c}",kGray+2);
    else 
      if(pol=="eR")
	QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow c#bar{c}",kGray+2);
      else 
	QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c}",kGray+2);
  }
      

  if(iquark==3) {
    if(pol=="eL")
      QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q} (q=uds)",kGray+2);
    else 
      if(pol=="eR")
	QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} (q=uds)",kGray+2);
      else 
	QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q} (q=uds)",kGray+2);
  }

 if(iquark==0) {
    if(pol=="eL")
      QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q} (q=udscb)",kGray+2);
    else 
      if(pol=="eR")
	QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q} (q=udscb)",kGray+2);
      else 
	QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q} (q=udscb)",kGray+2);
 }
      
}

void Mom(int quarkid=4) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  iquark=quarkid;
  TString squark="cquark";
  if(iquark==3) squark="udsquark";
  if(iquark==5) squark="bquark";

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  p_pion = (TH1F*)f->Get("p_pion");
  TH1F*  p_proton = (TH1F*)f->Get("p_proton");
  TH1F*  p_kaontest = (TH1F*)f->Get("kdEdx_dist_kaon");

  TString filename2 = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";
  TFile *f2 = new TFile(filename2);
  TH1F*  p_kaon2 = (TH1F*)f2->Get("p_kaon");
  TH1F*  p_pion2 = (TH1F*)f2->Get("p_pion");
  TH1F*  p_proton2 = (TH1F*)f2->Get("p_proton");
  TH1F*  p_kaontest2 = (TH1F*)f2->Get("kdEdx_dist_kaon");

  p_pion2->Scale(p_pion->GetEntries()/p_pion2->GetEntries());
  p_kaon2->Scale(p_pion->GetEntries()/p_pion2->GetEntries());
  p_proton2->Scale(p_pion->GetEntries()/p_pion2->GetEntries());

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  p_pion->GetXaxis()->SetTitle("momentum [GeV]");
  p_pion->GetYaxis()->SetTitle("a.u.");
  p_pion->GetXaxis()->SetRangeUser(0,60);

  p_pion->SetLineColor(4);
  p_pion->SetLineWidth(3);
  p_pion->SetLineStyle(1);
  p_pion->Draw("histo");

  p_kaon->SetLineColor(2);
  p_kaon->SetLineWidth(3);
  p_kaon->SetLineStyle(1);
  p_kaon->Draw("histosame");

  p_proton->SetLineColor(kGreen+2);
  p_proton->SetLineWidth(3);
  p_proton->SetLineStyle(1);
  p_proton->Draw("histosame");

  p_pion2->SetLineColor(4);
  p_pion2->SetLineWidth(3);
  p_pion2->SetLineStyle(2);
  p_pion2->Draw("histosame");

  p_kaon2->SetLineColor(2);
  p_kaon2->SetLineWidth(3);
  p_kaon2->SetLineStyle(2);
  p_kaon2->Draw("histosame");

  p_proton2->SetLineColor(kGreen+2);
  p_proton2->SetLineWidth(3);
  p_proton2->SetLineStyle(2);
  p_proton2->Draw("histosame");
   
  p_kaontest->SetLineColor(1);
  p_kaontest->SetLineWidth(3);
  p_kaontest->SetLineStyle(1);
  p_kaontest2->SetLineColor(1);
  p_kaontest2->SetLineWidth(3);
  p_kaontest2->SetLineStyle(2);

  Labels("");
  if(quarkid==3)   QQBARLabel2(0.4,0.8,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.4,0.8,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.4,0.8,"Secondary Tracks in b-jets",kGray+4);

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.75);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(p_kaontest,"e_{L}^{-}e_{R}^{+}","l");
  leg->AddEntry(p_kaontest2,"e_{R}^{-}e_{L}^{+}","l");

  leg->AddEntry(p_pion,"pions","l");
  leg->AddEntry(p_kaon,"kaons","l");
  leg->AddEntry(p_proton,"protons","l");
  leg->SetFillStyle(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


  c_mom->Print("plots_draft/MomentumSecTracks_in_"+squark+"jets.eps");

}

void dEdx(int quarkid=4) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  iquark=quarkid;
  TString squark="cquark";
  if(iquark==3) squark="udsquark";
  if(iquark==5) squark="bquark";

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH2F*  kaon = (TH2F*)f->Get("kaon");
  TH2F*  pion = (TH2F*)f->Get("pion");
  TH2F*  proton = (TH2F*)f->Get("proton");
  TH1F*  kaontest = (TH1F*)f->Get("kdEdx_dist_kaon");

     float max=0;
 for(int i=0; i<37; i++) {
    for(int j=0; j<199; j++) if(proton->GetBinContent(i+1,j+1)>max) max=proton->GetBinContent(i+1,j+1);
 }
  for(int i=0; i<37; i++) {

    for(int j=0; j<199; j++) proton->SetBinContent(i+1,j+1,300.*proton->GetBinContent(i+1,j+1)/max);
  }

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  gPad->SetLogx();
  pion->GetXaxis()->SetTitle("momentum [GeV]");
  pion->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV/cm]");
  pion->GetXaxis()->SetRangeUser(0.8,80);

  pion->SetLineColor(4);
  pion->SetFillColor(4);
  pion->SetMarkerColor(4);
  pion->SetMarkerStyle(1);
  pion->Draw("p");

  kaon->SetLineColor(2);
  kaon->SetFillColor(2);
  kaon->SetMarkerColor(2);
  kaon->SetMarkerStyle(1);
  kaon->Draw("psame");

  proton->SetLineColor(kGreen+2);
  proton->SetFillColor(kGreen+2);
  proton->SetMarkerColor(kGreen+2);
  proton->SetMarkerStyle(1);
  proton->Draw("psame");

  Labels("");
  if(quarkid==3)   QQBARLabel2(0.2,0.87,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.2,0.87,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.2,0.87,"Secondary Tracks in b-jets",kGray+4);

  TLegend *leg = new TLegend(0.6,0.7,0.8,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  // leg->AddEntry(kaontest,"e_{L}^{-}e_{R}^{+}","l");
  //leg->AddEntry(kaontest2,"e_{R}^{-}e_{L}^{+}","l");

  leg->AddEntry(pion,"pions","fl");
  leg->AddEntry(kaon,"kaons","fl");
  leg->AddEntry(proton,"protons","fl");
  leg->SetFillStyle(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


  c_mom->Print("plots_draft/dEdx.eps");

}


void Ntracks() {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  TH1F*  n_sectracks_eL[3];
  TH1F*  n_sectracks_eR[3];

  TH1F*  test;
  TH1F*  test2;

  for(int quarkid=3; quarkid<6; quarkid++) {
    TString squark="udsquark";
    if(quarkid==4) squark="cquark";
    if(quarkid==5) squark="bquark";
    
    TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
    TFile *f = new TFile(filename);
    cout<<filename<<endl;
    n_sectracks_eL[quarkid-3] = (TH1F*)f->Get("n_sectracks");
    if(quarkid==3) test = (TH1F*)f->Get("kdEdx_dist_proton");

    filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";
    TFile *f2 = new TFile(filename);
    n_sectracks_eR[quarkid-3] = (TH1F*)f2->Get("n_sectracks");
    n_sectracks_eR[quarkid-3]->Scale(n_sectracks_eL[quarkid-3]->GetEntries()/n_sectracks_eR[quarkid-3]->GetEntries());
    if(quarkid==3) test2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  }

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  n_sectracks_eL[0]->GetXaxis()->SetTitle("# secondary tracks per jet");
  n_sectracks_eL[0]->GetYaxis()->SetTitle("a.u.");
  n_sectracks_eL[0]->GetXaxis()->SetRangeUser(0,24);

  n_sectracks_eL[0]->SetLineColor(kGreen+2);
  n_sectracks_eL[0]->SetLineWidth(3);
  n_sectracks_eL[0]->SetLineStyle(1);
  n_sectracks_eL[0]->Draw("histo");
 
  n_sectracks_eR[0]->SetLineColor(kGreen+2);
  n_sectracks_eR[0]->SetLineWidth(3);
  n_sectracks_eR[0]->SetLineStyle(2);
  n_sectracks_eR[0]->Draw("histosame");

  n_sectracks_eL[1]->SetLineColor(2);
  n_sectracks_eL[1]->SetLineWidth(3);
  n_sectracks_eL[1]->SetLineStyle(1);
  n_sectracks_eL[1]->Draw("histosame");
 
  n_sectracks_eR[1]->SetLineColor(2);
  n_sectracks_eR[1]->SetLineWidth(3);
  n_sectracks_eR[1]->SetLineStyle(2);
  n_sectracks_eR[1]->Draw("histosame");

  n_sectracks_eL[2]->SetLineColor(4);
  n_sectracks_eL[2]->SetLineWidth(3);
  n_sectracks_eL[2]->SetLineStyle(1);
  n_sectracks_eL[2]->Draw("histosame");
 
  n_sectracks_eR[2]->SetLineColor(4);
  n_sectracks_eR[2]->SetLineWidth(3);
  n_sectracks_eR[2]->SetLineStyle(2);
  n_sectracks_eR[2]->Draw("histosame");

  
  test->SetLineColor(1);
  test->SetLineWidth(3);
  test->SetLineStyle(1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

  Labels("");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.75);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(test,"e_{L}^{-}e_{R}^{+}","l");
  leg->AddEntry(test2,"e_{R}^{-}e_{L}^{+}","l");

  leg->AddEntry(n_sectracks_eL[2],"b-jets","l");
  leg->AddEntry(n_sectracks_eL[1],"c-jets","l");
  leg->AddEntry(n_sectracks_eL[0],"uds-jets","l");
  leg->SetFillStyle(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


  c_mom->Print("plots_draft/NSecTracks_in_jets.eps");

}


void dEdxdist(int quarkid=3) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);
  iquark=quarkid;
  TString squark="udsquark";
  if(quarkid==4) squark="cquark";
  if(quarkid==5) squark="bquark";

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";

  TFile *f = new TFile(filename);

  TH1F*  kdEdx_dist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  test = (TH1F*)f->Get("n_sectracks");

  TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV_costheta_lt0.8.root";

  TFile *f2 = new TFile(filename2);

  TH1F*  kdEdx_dist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  TH1F*  test2 = (TH1F*)f2->Get("n_sectracks");

  kdEdx_dist_pion2->Scale(kdEdx_dist_pion->GetEntries()/kdEdx_dist_pion2->GetEntries());
  kdEdx_dist_kaon2->Scale(kdEdx_dist_pion->GetEntries()/kdEdx_dist_pion2->GetEntries());
  kdEdx_dist_proton2->Scale(kdEdx_dist_pion->GetEntries()/kdEdx_dist_pion2->GetEntries());
  
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  kdEdx_dist_pion->GetXaxis()->SetTitle("signed [(dE/dx-dE/dx_{fit-kaon})/#Delta_{dE/dx}]^{2}");
  kdEdx_dist_pion->GetYaxis()->SetTitle("a.u.");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);

  kdEdx_dist_pion->SetLineColor(4);
  kdEdx_dist_pion->SetLineWidth(3);
  kdEdx_dist_pion->SetLineStyle(1);
  kdEdx_dist_pion->Draw("histo");

  kdEdx_dist_kaon->SetLineColor(2);
  kdEdx_dist_kaon->SetLineWidth(3);
  kdEdx_dist_kaon->SetLineStyle(1);
  kdEdx_dist_kaon->Draw("histosame");

  kdEdx_dist_proton->SetLineColor(kGreen+2);
  kdEdx_dist_proton->SetLineWidth(3);
  kdEdx_dist_proton->SetLineStyle(1);
  kdEdx_dist_proton->Draw("histosame");

  kdEdx_dist_pion2->SetLineColor(4);
  kdEdx_dist_pion2->SetLineWidth(3);
  kdEdx_dist_pion2->SetLineStyle(2);
  kdEdx_dist_pion2->Draw("histosame");

  kdEdx_dist_kaon2->SetLineColor(2);
  kdEdx_dist_kaon2->SetLineWidth(3);
  kdEdx_dist_kaon2->SetLineStyle(2);
  kdEdx_dist_kaon2->Draw("histosame");

  kdEdx_dist_proton2->SetLineColor(kGreen+2);
  kdEdx_dist_proton2->SetLineWidth(3);
  kdEdx_dist_proton2->SetLineStyle(2);
  kdEdx_dist_proton2->Draw("histosame");

  
  test->SetLineColor(1);
  test->SetLineWidth(3);
  test->SetLineStyle(1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

 
  Labels("");
  
  TLegend *leg = new TLegend(0.22,0.6,0.5,0.85);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(test,"All secondary tracks","l");
  leg->AddEntry(test2,"|p_{trk}|>3 GeV & |cos#theta_{trk}|<0.8","l");
  leg->AddEntry(kdEdx_dist_pion,"pions","l");
  leg->AddEntry(kdEdx_dist_kaon,"kaons","l");
  leg->AddEntry(kdEdx_dist_proton,"protons","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c_mom->Print("plots_draft/dEdx_dist_"+squark+".eps");


}


void EffPurity_angle(int quarkid) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  iquark=quarkid;
  TString squark="udsquark";
  if(quarkid==4) squark="cquark";
  if(quarkid==5) squark="bquark";

 
  TString filename =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("costheta_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("costheta_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("costheta_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("costheta_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("costheta_kdEdx_dist_electron");
  TH1F* test = (TH1F*)f->Get("n_sectracks");

  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=1;i<21; i++) {
    int ipion=22;
    if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x[i-1]=i*1./20;
    eff[i-1]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV.root";

  TFile *f2 = new TFile(filename2);
  TH2F*  kdEdxdist_kaon2 = (TH2F*)f2->Get("costheta_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion2 = (TH2F*)f2->Get("costheta_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton2 = (TH2F*)f2->Get("costheta_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon2 = (TH2F*)f2->Get("costheta_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron2 = (TH2F*)f2->Get("costheta_kdEdx_dist_electron");
  TH1F* test2 = (TH1F*)f2->Get("n_sectracks");

  float x2[100], eff2[100], pur2[100];
  int n2=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=1;i<21; i++) {
    int ipion=22;
    if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon2->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion2->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton2->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon2->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron2->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon2->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x2[i-1]=i*1./20;
    eff2[i-1]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur2[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }
 

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);
  

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  efficiency->GetXaxis()->SetTitle("p [GeV]");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);
  efficiency->GetXaxis()->SetRangeUser(0,60);

  efficiency->SetLineColor(kMagenta+1);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(1);
  efficiency->Draw("al");
  
  purity->SetLineColor(kOrange+1);
  purity->SetLineWidth(3);
  purity->SetLineStyle(1);
  purity->Draw("lsame");

  efficiency2->SetLineColor(kMagenta+1);
  efficiency2->SetLineWidth(3);
  efficiency2->SetLineStyle(2);
  efficiency2->Draw("same");
  
  purity2->SetLineColor(kOrange+1);
  purity2->SetLineWidth(3);
  purity2->SetLineStyle(2);
  purity2->Draw("lsame");



  test->SetLineColor(1);
  test->SetLineWidth(3);
  test->SetLineStyle(1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

  
  Labels("");
  
  TLegend *leg0 = new TLegend(0.25,0.3,0.5,0.5);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(test,"All secondary tracks","l");
  leg0->AddEntry(test2,"|p_{trk}|>3 GeV","l");
  leg0->AddEntry(efficiency,"Efficiency of Kaon ID","l");
  leg0->AddEntry(purity,"Purity of Kaon ID","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  c_mom->Print("plots_draft/eff_purity_angle_"+squark+".eps");
  
 


}


void EffPurity_momentum(int quarkid=4) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  iquark=quarkid;
  TString squark="udsquark";
  if(quarkid==4) squark="cquark";
  if(quarkid==5) squark="bquark";

 
  TString filename =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  TH1F* test = (TH1F*)f->Get("n_sectracks");

  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=2;i<80; i++) {
    int ipion=22;
    // if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x[i-2]=i;
    eff[i-2]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i-2]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
  /*  //-----------------------
  filename =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV_costheta_lt0.8.root";

  f = new TFile(filename);
  kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  TH1F* test2 = (TH1F*)f->Get("n_sectracks");

  n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=2;i<80; i++) {
    int ipion=22;
    // if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x[i-2]=i;
    eff[i-2]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i-2]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

 
  TGraph* efficiency2 = new TGraph(n,x,eff);
  TGraph* purity2 = new TGraph(n,x,pur);
  TGraph* efficiency_purity2 = new TGraph(n,eff,pur);
  */

 
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  efficiency->GetXaxis()->SetTitle("p_{trk} [GeV]");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);
  efficiency->GetXaxis()->SetRangeUser(0,60);

  efficiency->SetLineColor(kMagenta+1);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(1);
  efficiency->Draw("al");
  
  purity->SetLineColor(kOrange+1);
  purity->SetLineWidth(3);
  purity->SetLineStyle(1);
  purity->Draw("lsame");

  /*  efficiency2->SetLineColor(kMagenta+1);
  efficiency2->SetLineWidth(3);
  efficiency2->SetLineStyle(2);
  efficiency2->Draw("same");
  
  purity2->SetLineColor(kOrange+1);
  purity2->SetLineWidth(3);
  purity2->SetLineStyle(2);
  purity2->Draw("lsame");



  test->SetLineColor(1);
  test->SetLineWidth(3);
  test->SetLineStyle(1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);
  */
  
  Labels("");
  
  TLegend *leg0 = new TLegend(0.25,0.3,0.5,0.5);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  // leg0->AddEntry(test,"All secondary tracks","l");
  // leg0->AddEntry(test2,"|cos#theta_{trk}|<0.8","l");
  leg0->AddEntry(efficiency,"Efficiency of Kaon ID","l");
  leg0->AddEntry(purity,"Purity of Kaon ID","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  c_mom->Print("plots_draft/eff_purity_momentum_"+squark+".eps");
  
 
  


}


void Plots_dEdx_draft() {
  for(int i=3; i<5; i++) Mom(i);
  Ntracks();
  dEdx(3);
  for(int i=4; i<6; i++)  dEdxdist(i);
  for(int i=4; i<6; i++) EffPurity_momentum(i);
  for(int i=4; i<6; i++) EffPurity_angle(i);
  
  //EffPurity_default();
  // EffPurity_dedxdist4();
  // EffPurity_dedxdist2();
  // EffPurity_dedxdist5();
  // dEdxdist(false);
}
