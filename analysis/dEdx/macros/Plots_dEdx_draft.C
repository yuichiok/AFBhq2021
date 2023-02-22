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
int iquark=-1;

void Labels(TString pol){
  // QQBARLabel(0.86,0.952,"Work in Progress");
  if(iquark>-1)
    {
      QQBARLabel(0.86,0.954,"");
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
    } else {
      QQBARLabel(0.86,0.954,"");

  }
}

void NHits() {

  iquark=-1;
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadRightMargin(0.12);

  TGaxis::SetMaxDigits(3);
  
  TString squark="udscbquark";

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH2F*  nhits = (TH2F*)f->Get("n_costheta_kaon");

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  nhits->GetXaxis()->SetTitle("cos(#theta_{trk})");
  nhits->GetYaxis()->SetTitle("# TPC hits");
  nhits->GetXaxis()->SetRangeUser(-1,1);

  nhits->SetLineColor(4);
  nhits->SetLineWidth(3);
  nhits->SetLineStyle(1);
  nhits->Draw("colz");

  
  QQBARLabel(0.8,0.954,"");
  QQBARLabel2(0.3,0.25,"Secondary Tracks in q-jets (q=udscb)",kGray+4);

  c_mom->Print("plots_draft/TPCHits_in_"+squark+"jets.eps");

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
  p_kaon2->Scale(p_kaon->GetEntries()/p_kaon2->GetEntries());
  p_proton2->Scale(p_proton->GetEntries()/p_proton2->GetEntries());

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  //gPad->SetLogy();
  c_mom->cd(1);
  // c_mom->SetGrid();
  p_pion->GetXaxis()->SetTitle("|#vec{p}_{trk}| [GeV]");
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
  /* if(quarkid==3)   QQBARLabel2(0.5,0.9,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.5,0.9,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.5,0.9,"Secondary Tracks in b-jets",kGray+4);
  */
  TLegend *leg = new TLegend(0.6,0.65,0.8,0.85);
  leg->SetTextSize(0.03);
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

void Costheta(int quarkid=4) {

  
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

  TH1F*  costheta_kaon = (TH1F*)f->Get("costheta_kaon");
  TH1F*  costheta_pion = (TH1F*)f->Get("costheta_pion");
  TH1F*  costheta_proton = (TH1F*)f->Get("costheta_proton");
  TH1F*  costheta_kaontest = (TH1F*)f->Get("kdEdx_dist_kaon");

  TString filename2 = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";
  TFile *f2 = new TFile(filename2);
  TH1F*  costheta_kaon2 = (TH1F*)f2->Get("costheta_kaon");
  TH1F*  costheta_pion2 = (TH1F*)f2->Get("costheta_pion");
  TH1F*  costheta_proton2 = (TH1F*)f2->Get("costheta_proton");
  TH1F*  costheta_kaontest2 = (TH1F*)f2->Get("kdEdx_dist_kaon");

  costheta_pion2->Scale(costheta_pion->GetEntries()/costheta_pion2->GetEntries());
  costheta_kaon2->Scale(costheta_pion->GetEntries()/costheta_pion2->GetEntries());
  costheta_proton2->Scale(costheta_pion->GetEntries()/costheta_pion2->GetEntries());

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  // gPad->SetLogy();
  c_mom->cd(1);
  // c_mom->SetGrid();
  costheta_pion->GetXaxis()->SetTitle("cos(#theta_{trk})");
  costheta_pion->GetYaxis()->SetTitle("a.u.");
  costheta_pion->GetXaxis()->SetRangeUser(-1,1);
  costheta_pion->GetYaxis()->SetRangeUser(0,costheta_pion->GetMaximum()*1.1);

  costheta_pion->SetLineColor(4);
  costheta_pion->SetLineWidth(3);
  costheta_pion->SetLineStyle(1);
  costheta_pion->Draw("histo");

  costheta_kaon->SetLineColor(2);
  costheta_kaon->SetLineWidth(3);
  costheta_kaon->SetLineStyle(1);
  costheta_kaon->Draw("histosame");

  costheta_proton->SetLineColor(kGreen+2);
  costheta_proton->SetLineWidth(3);
  costheta_proton->SetLineStyle(1);
  costheta_proton->Draw("histosame");

  costheta_pion2->SetLineColor(4);
  costheta_pion2->SetLineWidth(3);
  costheta_pion2->SetLineStyle(2);
  costheta_pion2->Draw("histosame");

  costheta_kaon2->SetLineColor(2);
  costheta_kaon2->SetLineWidth(3);
  costheta_kaon2->SetLineStyle(2);
  costheta_kaon2->Draw("histosame");

  costheta_proton2->SetLineColor(kGreen+2);
  costheta_proton2->SetLineWidth(3);
  costheta_proton2->SetLineStyle(2);
  costheta_proton2->Draw("histosame");
   
  costheta_kaontest->SetLineColor(1);
  costheta_kaontest->SetLineWidth(3);
  costheta_kaontest->SetLineStyle(1);
  costheta_kaontest2->SetLineColor(1);
  costheta_kaontest2->SetLineWidth(3);
  costheta_kaontest2->SetLineStyle(2);

  Labels("");
  /* if(quarkid==3)   QQBARLabel2(0.4,0.9,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.4,0.9,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.4,0.9,"Secondary Tracks in b-jets",kGray+4);
  */
  TLegend *leg = new TLegend(0.65,0.4,0.8,0.58);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(costheta_kaontest,"e_{L}^{-}e_{R}^{+}","l");
  leg->AddEntry(costheta_kaontest2,"e_{R}^{-}e_{L}^{+}","l");

  leg->AddEntry(costheta_pion,"pions","l");
  leg->AddEntry(costheta_kaon,"kaons","l");
  leg->AddEntry(costheta_proton,"protons","l");
  leg->SetFillStyle(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


  c_mom->Print("plots_draft/CosthetaSecTracks_in_"+squark+"jets.eps");

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
  gStyle->SetPadLeftMargin(0.18);
  TGaxis::SetMaxDigits(3);
  
  iquark=quarkid;
  TString squark="cquark";
  if(iquark==3) squark="udsquark";
  if(iquark==5) squark="bquark";
  if(iquark==0) squark="udscbquark";

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";
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
  pion->GetXaxis()->SetTitle("|#vec{p}_{trk}| [GeV]");
  pion->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV/cm]");
  pion->GetYaxis()->SetTitleOffset(1.6);

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
  if(quarkid==3)   QQBARLabel2(0.25,0.87,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.25,0.87,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.25,0.87,"Secondary Tracks in b-jets",kGray+4);
  if(quarkid==0)   QQBARLabel2(0.25,0.87,"Secondary Tracks in q-jets (q=udscb)",kGray+4);

  TLegend *leg = new TLegend(0.6,0.7,0.8,0.85);
  leg->SetTextSize(0.03);
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


  c_mom->Print("plots_draft/dEdx_p.eps");
  c_mom->Print("plots_draft/dEdx_p.pdf");

}


void dEdx2(int quarkid=4) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  gStyle->SetPadLeftMargin(0.18);
  TGaxis::SetMaxDigits(3);
  
  iquark=quarkid;
  TString squark="cquark";
  if(iquark==3) squark="udsquark";
  if(iquark==5) squark="bquark";
  if(iquark==0) squark="udscbquark";

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";
  TFile *f = new TFile(filename);
  cout<<filename<<endl;

  TH2F*  kaon = (TH2F*)f->Get("kaon_cos");
  TH2F*  pion = (TH2F*)f->Get("pion_cos");
  TH2F*  proton = (TH2F*)f->Get("proton_cos");
  TH1F*  kaontest = (TH1F*)f->Get("kdEdx_dist_kaon");

  /*float max=0;
  for(int i=0; i<37; i++) {
    for(int j=0; j<199; j++) if(proton->GetBinContent(i+1,j+1)>max) max=proton->GetBinContent(i+1,j+1);
  }
  for(int i=0; i<37; i++) {
    
    for(int j=0; j<199; j++) proton->SetBinContent(i+1,j+1,300.*proton->GetBinContent(i+1,j+1)/max);
    }*/
  proton->Scale(5);
  kaon->Scale(1.);
  pion->Scale(0.1);

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  pion->GetXaxis()->SetTitle("cos(#theta_{trk})");
  pion->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV/cm]");
  pion->GetYaxis()->SetTitleOffset(1.6);

  //  pion->GetXaxis()->SetRangeUser(0.8,80);

  pion->SetLineColor(4);
  pion->SetFillColor(4);
  pion->SetMarkerColor(4);
  pion->SetMarkerStyle(6);
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
  if(quarkid==3)   QQBARLabel2(0.25,0.87,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.25,0.87,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.25,0.87,"Secondary Tracks in b-jets",kGray+4);
  if(quarkid==0)   QQBARLabel2(0.25,0.87,"Secondary Tracks in q-jets (q=udscb)",kGray+4);

  TLegend *leg = new TLegend(0.6,0.7,0.8,0.85);
  leg->SetTextSize(0.03);
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


  c_mom->Print("plots_draft/dEdx_costheta.eps");
  c_mom->Print("plots_draft/dEdx_costheta.pdf");

}


void Ntracks() {

  iquark=-1;
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
    n_sectracks_eL[quarkid-3] = (TH1F*)f->Get("n_secvtx");
    if(quarkid==3) test = (TH1F*)f->Get("kdEdx_dist_proton");
    // n_sectracks_eL[quarkid-3]->Scale( n_sectracks_eL[0]->Integral()/ n_sectracks_eL[quarkid-3]->Integral());

    filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_0GeV.root";
    TFile *f2 = new TFile(filename);
    n_sectracks_eR[quarkid-3] = (TH1F*)f2->Get("n_secvtx");
    // n_sectracks_eR[quarkid-3]->Scale( n_sectracks_eR[0]->Integral()/ n_sectracks_eR[quarkid-3]->Integral());

    //  n_sectracks_eR[quarkid-3]->Scale( n_sectracks_eL[quarkid-3]->Integral()/ n_sectracks_eR[quarkid-3]->Integral());

    if(quarkid==3) test2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  }

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  n_sectracks_eL[0]->GetXaxis()->SetTitle("number of vtx per jet");
  //  n_sectracks_eL[0]->GetYaxis()->SetTitle("a.u.");
  n_sectracks_eL[0]->GetXaxis()->SetRangeUser(0,2.5);

  n_sectracks_eL[0]->SetLineColor(kGreen+2);
  n_sectracks_eL[0]->SetLineWidth(3);
  n_sectracks_eL[0]->SetLineStyle(1);
  n_sectracks_eL[0]->DrawNormalized("p");

  n_sectracks_eL[1]->SetLineColor(2);
  n_sectracks_eL[1]->SetLineWidth(3);
  n_sectracks_eL[1]->DrawNormalized("psame");
 
  n_sectracks_eL[2]->SetLineColor(4);
  n_sectracks_eL[2]->SetLineWidth(3);
  n_sectracks_eL[2]->SetLineStyle(1);
  n_sectracks_eL[2]->DrawNormalized("psame");

  
  n_sectracks_eR[0]->SetLineColor(kGreen+2);
  n_sectracks_eR[0]->SetLineWidth(3);
  n_sectracks_eR[0]->SetLineStyle(2);

  n_sectracks_eR[1]->SetLineColor(2);
  n_sectracks_eR[1]->SetLineWidth(3);
  n_sectracks_eR[1]->SetLineStyle(2);
   
  n_sectracks_eR[2]->SetLineColor(4);
  n_sectracks_eR[2]->SetLineWidth(3);
  n_sectracks_eR[2]->SetLineStyle(2);

  n_sectracks_eR[0]->DrawNormalized("psame");
  n_sectracks_eR[1]->DrawNormalized("psame");
  n_sectracks_eR[2]->DrawNormalized("psame");


  test->SetLineColor(1);
  test->SetLineWidth(3);
  test->SetLineStyle(1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

  Labels("");

  TLegend *leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetTextSize(0.03);
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


  c_mom->Print("plots_draft/NSecVtx_in_jets.eps");

}

void Ntracks2() {
  iquark=-1;

  
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
    
    TString filename = "../results/histos_"+squark+"_secondary_tracks_2f_hadronic_sample_eL_pR_0GeV.root";
    TFile *f = new TFile(filename);
    cout<<filename<<endl;
    n_sectracks_eL[quarkid-3] = (TH1F*)f->Get("n_sectracks_vtx");
    if(quarkid==3) test = (TH1F*)f->Get("kdEdx_dist_proton");


    filename = "../results/histos_"+squark+"_secondary_tracks_2f_hadronic_sample_eR_pL_0GeV.root";
    TFile *f2 = new TFile(filename);
    n_sectracks_eR[quarkid-3] = (TH1F*)f2->Get("n_sectracks_vtx");
 
    if(quarkid==3) test2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  }

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  // c_mom->SetGrid();
  gPad->SetLogy();
  n_sectracks_eL[0]->GetXaxis()->SetTitle("# of tracks per vtx");
  //n_sectracks_eL[0]->GetYaxis()->SetTitle("a.u.");
  n_sectracks_eL[0]->GetXaxis()->SetRangeUser(0,20);
  n_sectracks_eL[0]->GetYaxis()->SetRangeUser(1000,3000000);

  n_sectracks_eL[0]->SetLineColor(kGreen+2);
  n_sectracks_eL[0]->SetLineWidth(3);
  n_sectracks_eL[0]->SetLineStyle(1);
  n_sectracks_eL[0]->SetFillStyle(3004);
  n_sectracks_eL[0]->SetFillColor(kGreen+2);
  n_sectracks_eL[0]->DrawNormalized("h");

  n_sectracks_eL[1]->SetLineColor(2);
  n_sectracks_eL[1]->SetLineWidth(3);
  n_sectracks_eL[1]->SetFillStyle(3005);
  n_sectracks_eL[1]->SetFillColor(2);
  n_sectracks_eL[1]->DrawNormalized("hsame");
 
  n_sectracks_eL[2]->SetLineColor(4);
  n_sectracks_eL[2]->SetLineWidth(3);
  n_sectracks_eL[2]->SetLineStyle(1);
  n_sectracks_eL[2]->SetFillStyle(3003);
  n_sectracks_eL[2]->SetFillColor(4);
  n_sectracks_eL[2]->DrawNormalized("hsame");

  
  n_sectracks_eR[0]->SetLineColor(kGreen+2);
  n_sectracks_eR[0]->SetLineWidth(3);
  n_sectracks_eR[0]->SetLineStyle(2);

  n_sectracks_eR[1]->SetLineColor(2);
  n_sectracks_eR[1]->SetLineWidth(3);
  n_sectracks_eR[1]->SetLineStyle(2);
   
  n_sectracks_eR[2]->SetLineColor(4);
  n_sectracks_eR[2]->SetLineWidth(3);
  n_sectracks_eR[2]->SetLineStyle(2);

  n_sectracks_eR[0]->DrawNormalized("psame");
  n_sectracks_eR[1]->DrawNormalized("psame");
  n_sectracks_eR[2]->DrawNormalized("psame");


  test->SetLineColor(1);
  test->SetLineWidth(3);
  test->SetLineStyle(1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

  Labels("");

  TLegend *leg = new TLegend(0.65,0.65,0.85,0.85);
  leg->SetTextSize(0.03);
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

  // TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV_costheta_lt0.8.root";
  TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV.root";


  TFile *f2 = new TFile(filename2);

  TH1F*  kdEdx_dist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  TH1F*  test2 = (TH1F*)f2->Get("n_sectracks");

  kdEdx_dist_pion2->Scale(kdEdx_dist_pion->GetEntries()/kdEdx_dist_pion2->GetEntries());
  kdEdx_dist_kaon2->Scale(kdEdx_dist_kaon->GetEntries()/kdEdx_dist_kaon2->GetEntries());
  kdEdx_dist_proton2->Scale(kdEdx_dist_proton->GetEntries()/kdEdx_dist_proton2->GetEntries());
  
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  kdEdx_dist_pion2->GetXaxis()->SetTitle("#Delta_{dE/dx-K}");
  //  kdEdx_dist_pion2->GetXaxis()->SetTitle("signed [(dE/dx-dE/dx_{fit-kaon})/#Delta_{dE/dx}]^{2}");
  kdEdx_dist_pion2->GetYaxis()->SetTitle("a.u.");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);

  kdEdx_dist_pion2->SetLineColor(4);
  kdEdx_dist_pion2->SetLineWidth(3);
  kdEdx_dist_pion2->SetLineStyle(2);
  kdEdx_dist_pion2->Draw("histo");

  kdEdx_dist_kaon->SetLineColor(2);
  kdEdx_dist_kaon->SetLineWidth(3);
  kdEdx_dist_kaon->SetLineStyle(1);
  kdEdx_dist_kaon->Draw("histosame");

  kdEdx_dist_proton->SetLineColor(kGreen+2);
  kdEdx_dist_proton->SetLineWidth(3);
  kdEdx_dist_proton->SetLineStyle(1);
  kdEdx_dist_proton->Draw("histosame");

  kdEdx_dist_pion->SetLineColor(4);
  kdEdx_dist_pion->SetLineWidth(3);
  kdEdx_dist_pion->SetLineStyle(1);
  kdEdx_dist_pion->Draw("histosame");

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
  
  TLegend *leg = new TLegend(0.18,0.6,0.46,0.85);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(test,"All secondary tracks","l");
  leg->AddEntry(test2,"|p_{trk}|>3 GeV","l");
  // leg->AddEntry(test2,"|p_{trk}|>3 GeV & |cos(#theta_{trk})|<0.8","l");
  leg->AddEntry(kdEdx_dist_pion,"pions","l");
  leg->AddEntry(kdEdx_dist_kaon,"kaons","l");
  leg->AddEntry(kdEdx_dist_proton,"protons","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c_mom->Print("plots_draft/dEdx_dist_"+squark+".eps");


}

void dEdxdist2(int quarkid=3) {

  
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

  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_3GeV_costheta_lt0.8.root";

  TFile *f = new TFile(filename);

  TH1F*  kdEdx_dist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  test = (TH1F*)f->Get("n_sectracks");

  // TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV_costheta_lt0.8.root";
  TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_improved_1_2f_hadronic_sample_eL_pR_3GeV_costheta_lt0.8.root";


  TFile *f2 = new TFile(filename2);

  TH1F*  kdEdx_dist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  TH1F*  test2 = (TH1F*)f2->Get("n_sectracks");

  kdEdx_dist_pion2->Scale(kdEdx_dist_pion->GetEntries()/kdEdx_dist_pion2->GetEntries());
  kdEdx_dist_kaon2->Scale(kdEdx_dist_kaon->GetEntries()/kdEdx_dist_kaon2->GetEntries());
  kdEdx_dist_proton2->Scale(kdEdx_dist_proton->GetEntries()/kdEdx_dist_proton2->GetEntries());
  
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  kdEdx_dist_pion2->GetXaxis()->SetTitle("#Delta_{dE/dx-K}");
  //  kdEdx_dist_pion2->GetXaxis()->SetTitle("signed [(dE/dx-dE/dx_{fit-kaon})/#Delta_{dE/dx}]^{2}");
  kdEdx_dist_pion2->GetYaxis()->SetTitle("a.u.");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);

  kdEdx_dist_pion2->SetLineColor(4);
  kdEdx_dist_pion2->SetLineWidth(3);
  kdEdx_dist_pion2->SetLineStyle(2);
  kdEdx_dist_pion2->Draw("histo");

  kdEdx_dist_kaon->SetLineColor(2);
  kdEdx_dist_kaon->SetLineWidth(3);
  kdEdx_dist_kaon->SetLineStyle(1);
  kdEdx_dist_kaon->Draw("histosame");

  kdEdx_dist_proton->SetLineColor(kGreen+2);
  kdEdx_dist_proton->SetLineWidth(3);
  kdEdx_dist_proton->SetLineStyle(1);
  kdEdx_dist_proton->Draw("histosame");

  kdEdx_dist_pion->SetLineColor(4);
  kdEdx_dist_pion->SetLineWidth(3);
  kdEdx_dist_pion->SetLineStyle(1);
  kdEdx_dist_pion->Draw("histosame");

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
  
  TLegend *leg = new TLegend(0.18,0.6,0.46,0.85);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(test,"Nominal dEdx performance, |p_{trk}|>3 GeV","l");
  leg->AddEntry(test2,"Estimated Cluster Counting dEdx performance, |p_{trk}|>3 GeV","l");
  // leg->AddEntry(test2,"|p_{trk}|>3 GeV & |cos(#theta_{trk})|<0.8","l");
  leg->AddEntry(kdEdx_dist_pion,"pions","l");
  leg->AddEntry(kdEdx_dist_kaon,"kaons","l");
  leg->AddEntry(kdEdx_dist_proton,"protons","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c_mom->Print("plots_draft/dEdx_dist_"+squark+".eps");


}

void dEdxdistProjection(int quarkid=3) {

  
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
  TH2F*  p_kdEdx_dist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  TH2F*  p_kdEdx_dist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  TH2F*  p_kdEdx_dist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  TH2F*  test = (TH2F*)f->Get("n_sectracks");

  TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV.root";

  TFile *f2 = new TFile(filename2);

  TH2F*  p_kdEdx_dist_kaon2 = (TH2F*)f2->Get("p_kdEdx_dist_kaon");
  TH2F*  p_kdEdx_dist_pion2 = (TH2F*)f2->Get("p_kdEdx_dist_pion");
  TH2F*  p_kdEdx_dist_proton2 = (TH2F*)f2->Get("p_kdEdx_dist_proton");
  TH2F*  test2 = (TH2F*)f2->Get("n_sectracks");

  double x[100], ex[100];
  double ykaon[100], eykaon[100];
  double y2kaon[100], ey2kaon[100];
  double ypion[100], eypion[100];
  double y2pion[100], ey2pion[100];
  double yproton[100], eyproton[100];
  double y2proton[100], ey2proton[100];
  
  for(int ip=0; ip<100; ip++) {
    x[ip]=ip+0.5;
    ex[ip]=0.5;
    TH1F *h1_kaon =(TH1F*)p_kdEdx_dist_kaon->ProjectionY(TString::Format("kaon1_%i",ip),ip,ip+1);
    ykaon[ip]=h1_kaon->GetMean();
    eykaon[ip]=h1_kaon->GetRMS();

    TH1F *h1_pion =(TH1F*)p_kdEdx_dist_pion->ProjectionY(TString::Format("pion1_%i",ip),ip,ip+1);
    ypion[ip]=h1_pion->GetMean();
    eypion[ip]=h1_pion->GetRMS();

    TH1F *h1_proton =(TH1F*)p_kdEdx_dist_proton->ProjectionY(TString::Format("proton1_%i",ip),ip,ip+1);
    yproton[ip]=h1_proton->GetMean();
    eyproton[ip]=h1_proton->GetRMS();
 
  }

  TGraphErrors * g_kaon = new TGraphErrors(100,x,ykaon,ex,eykaon);
  TGraphErrors * g_pion = new TGraphErrors(100,x,ypion,ex,eypion);
  TGraphErrors * g_proton = new TGraphErrors(100,x,yproton,ex,eyproton);

  int n=0;
  for(int ip=3; ip<100; ip+=4) {
    x[n]=ip+0.5;
    ex[n]=0.5;
    TH1F *h2_kaon =(TH1F*)p_kdEdx_dist_kaon2->ProjectionY(TString::Format("kaon2_%i",ip),ip,ip+1);
    y2kaon[n]=h2_kaon->GetMean();
    ey2kaon[n]=h2_kaon->GetRMS();

    TH1F *h2_pion =(TH1F*)p_kdEdx_dist_pion2->ProjectionY(TString::Format("pion2_%i",ip),ip,ip+1);
    y2pion[n]=h2_pion->GetMean();
    ey2pion[n]=h2_pion->GetRMS();

    TH1F *h2_proton =(TH1F*)p_kdEdx_dist_proton2->ProjectionY(TString::Format("proton2_%i",ip),ip,ip+1);
    y2proton[n]=h2_proton->GetMean();
    ey2proton[n]=h2_proton->GetRMS();
    n++;
  }

  TGraphErrors * g_kaon2 = new TGraphErrors(n,x,y2kaon,ex,ey2kaon);
  TGraphErrors * g_pion2 = new TGraphErrors(n,x,y2pion,ex,ey2pion);
  TGraphErrors * g_proton2 = new TGraphErrors(n,x,y2proton,ex,ey2proton);

  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  g_pion->GetXaxis()->SetTitle("|#vec{p}_{trk}| [GeV]");
  g_pion->GetYaxis()->SetTitle("#mu_{#Delta_{dE/dx-K}} #pm #sigma_{#Delta_{dE/dx-K}}");
  g_pion->GetYaxis()->SetTitleOffset(1.2);
  g_pion->GetYaxis()->SetRangeUser(-10,20);
  g_pion->GetXaxis()->SetRangeUser(0,80);

  g_pion->SetLineColor(4);
  g_pion->SetLineWidth(3);
  g_pion->SetLineStyle(1);
  g_pion->SetFillStyle(3004);
  g_pion->SetFillColor(4); 
  g_pion->Draw("a3");

  g_pion2->SetLineColor(4);
  g_pion2->SetLineWidth(3);
  g_pion2->SetLineStyle(2);
  g_pion2->Draw("l");

  g_kaon->SetLineColor(2);
  g_kaon->SetLineWidth(3);
  g_kaon->SetLineStyle(1);
  g_kaon->SetFillStyle(3005);
  g_kaon->SetFillColor(2); 
  g_kaon->Draw("3");

  g_kaon2->SetLineColor(2);
  g_kaon2->SetLineWidth(3);
  g_kaon2->SetLineStyle(2);
  g_kaon2->Draw("l");
  

  g_proton->SetLineColor(kGreen+2);
  g_proton->SetLineWidth(3);
  g_proton->SetLineStyle(1);
  g_proton->SetFillStyle(3003);
  g_proton->SetFillColor(kGreen+2); 
  g_proton->Draw("3");

  g_proton2->SetLineColor(kGreen+2);
  g_proton2->SetLineWidth(3);
  g_proton2->SetLineStyle(2);
  g_proton2->Draw("l");

  
  test->SetLineColor(1);
  test->SetLineWidth(0);
  test->SetLineStyle(0);
  test->SetFillStyle(3002);
  test->SetFillColor(kGray+1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

 
  if(quarkid==3)   QQBARLabel2(0.5,0.9,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.5,0.9,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.5,0.9,"Secondary Tracks in b/c-jets",kGray+4);
  
  TLegend *leg = new TLegend(0.18,0.6,0.46,0.85);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(test,"All secondary tracks","f");
  leg->AddEntry(test2,"|p_{trk}|>3 GeV","l");
  leg->AddEntry(g_pion,"pions","l");
  leg->AddEntry(g_kaon,"kaons","l");
  leg->AddEntry(g_proton,"protons","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c_mom->Print("plots_draft/dEdx_dist_Proj_vs_mom_"+squark+".eps");
  

}



void dEdxdistProjection2(int quarkid=3) {

  
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
  TH2F*  costheta_kdEdx_dist_kaon = (TH2F*)f->Get("costheta_kdEdx_dist_kaon");
  TH2F*  costheta_kdEdx_dist_pion = (TH2F*)f->Get("costheta_kdEdx_dist_pion");
  TH2F*  costheta_kdEdx_dist_proton = (TH2F*)f->Get("costheta_kdEdx_dist_proton");
  TH2F*  test = (TH2F*)f->Get("n_sectracks");

  TString filename2 =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV.root";

  TFile *f2 = new TFile(filename2);

  TH2F*  costheta_kdEdx_dist_kaon2 = (TH2F*)f2->Get("costheta_kdEdx_dist_kaon");
  TH2F*  costheta_kdEdx_dist_pion2 = (TH2F*)f2->Get("costheta_kdEdx_dist_pion");
  TH2F*  costheta_kdEdx_dist_proton2 = (TH2F*)f2->Get("costheta_kdEdx_dist_proton");
  TH2F*  test2 = (TH2F*)f2->Get("n_sectracks");

  double x[100], ex[100];
  double ykaon[100], eykaon[100];
  double y2kaon[100], ey2kaon[100];
  double ypion[100], eypion[100];
  double y2pion[100], ey2pion[100];
  double yproton[100], eyproton[100];
  double y2proton[100], ey2proton[100];
  
  for(int ip=0; ip<20; ip++) {
    x[ip]=(ip+1./20)/20.;
    ex[ip]=1./20.;
    TH1F *h1_kaon =(TH1F*)costheta_kdEdx_dist_kaon->ProjectionY(TString::Format("kaon1_%i",ip),ip,ip+1);
    ykaon[ip]=h1_kaon->GetMean();
    eykaon[ip]=h1_kaon->GetRMS();

    TH1F *h1_pion =(TH1F*)costheta_kdEdx_dist_pion->ProjectionY(TString::Format("pion1_%i",ip),ip,ip+1);
    ypion[ip]=h1_pion->GetMean();
    eypion[ip]=h1_pion->GetRMS();

    TH1F *h1_proton =(TH1F*)costheta_kdEdx_dist_proton->ProjectionY(TString::Format("proton1_%i",ip),ip,ip+1);
    yproton[ip]=h1_proton->GetMean();
    eyproton[ip]=h1_proton->GetRMS();
 
  }

  TGraphErrors * g_kaon = new TGraphErrors(20,x,ykaon,ex,eykaon);
  TGraphErrors * g_pion = new TGraphErrors(20,x,ypion,ex,eypion);
  TGraphErrors * g_proton = new TGraphErrors(20,x,yproton,ex,eyproton);

  int n=0;
  for(int ip=0; ip<17; ip+=1) {
    x[ip]=(ip+1./20)/20.;
    ex[ip]=1./20.;
    
    TH1F *h2_kaon =(TH1F*)costheta_kdEdx_dist_kaon2->ProjectionY(TString::Format("kaon2_%i",ip),ip,ip+1);
    y2kaon[n]=h2_kaon->GetMean();
    ey2kaon[n]=h2_kaon->GetRMS();

    TH1F *h2_pion =(TH1F*)costheta_kdEdx_dist_pion2->ProjectionY(TString::Format("pion2_%i",ip),ip,ip+1);
    y2pion[n]=h2_pion->GetMean();
    ey2pion[n]=h2_pion->GetRMS();

    TH1F *h2_proton =(TH1F*)costheta_kdEdx_dist_proton2->ProjectionY(TString::Format("proton2_%i",ip),ip,ip+1);
    y2proton[n]=h2_proton->GetMean();
    ey2proton[n]=h2_proton->GetRMS();
    n++;
  }

  TGraphErrors * g_kaon2 = new TGraphErrors(n,x,y2kaon,ex,ey2kaon);
  TGraphErrors * g_pion2 = new TGraphErrors(n,x,y2pion,ex,ey2pion);
  TGraphErrors * g_proton2 = new TGraphErrors(n,x,y2proton,ex,ey2proton);

  TCanvas* c_mom = new TCanvas("c_mom2","c_mom2",800,800);
  c_mom->cd(1);
  g_pion->GetXaxis()->SetTitle("cos(#theta_{trk})");
  g_pion->GetYaxis()->SetTitle("#mu_{#Delta_{dE/dx-K}} #pm #sigma_{#Delta_{dE/dx-K}}");
  g_pion->GetYaxis()->SetTitleOffset(1.2);
  g_pion->GetYaxis()->SetRangeUser(-10,20);
  g_pion->GetXaxis()->SetRangeUser(0,1);

  g_pion->SetLineColor(4);
  g_pion->SetLineWidth(3);
  g_pion->SetLineStyle(1);
  g_pion->SetFillStyle(3004);
  g_pion->SetFillColor(4); 
  g_pion->Draw("a3");

  g_pion2->SetLineColor(4);
  g_pion2->SetLineWidth(3);
  g_pion2->SetLineStyle(2);
  g_pion2->Draw("l");

  g_kaon->SetLineColor(2);
  g_kaon->SetLineWidth(3);
  g_kaon->SetLineStyle(1);
  g_kaon->SetFillStyle(3005);
  g_kaon->SetFillColor(2); 
  g_kaon->Draw("3");

  g_kaon2->SetLineColor(2);
  g_kaon2->SetLineWidth(3);
  g_kaon2->SetLineStyle(2);
  g_kaon2->Draw("l");
  

  g_proton->SetLineColor(kGreen+2);
  g_proton->SetLineWidth(3);
  g_proton->SetLineStyle(1);
  g_proton->SetFillStyle(3003);
  g_proton->SetFillColor(kGreen+2); 
  g_proton->Draw("3");

  g_proton2->SetLineColor(kGreen+2);
  g_proton2->SetLineWidth(3);
  g_proton2->SetLineStyle(2);
  g_proton2->Draw("l");

  
  test->SetLineColor(1);
  test->SetLineWidth(0);
  test->SetLineStyle(0);
  test->SetFillStyle(3002);
  test->SetFillColor(kGray+1);

  test2->SetLineColor(1);
  test2->SetLineWidth(3);
  test2->SetLineStyle(2);

 
  if(quarkid==3)   QQBARLabel2(0.5,0.9,"Secondary Tracks in q-jets (q=uds)",kGray+4);
  if(quarkid==4)   QQBARLabel2(0.5,0.9,"Secondary Tracks in c-jets",kGray+4);
  if(quarkid==5)   QQBARLabel2(0.5,0.9,"Secondary Tracks in b/c-jets",kGray+4);
  
  TLegend *leg = new TLegend(0.18,0.6,0.46,0.85);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(test,"All secondary tracks","f");
  leg->AddEntry(test2,"|#vec{p}_{trk}|>3 GeV","ple");
  leg->AddEntry(g_pion,"pions","l");
  leg->AddEntry(g_kaon,"kaons","l");
  leg->AddEntry(g_proton,"protons","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  c_mom->Print("plots_draft/dEdx_dist_Proj_vs_costheta_"+squark+".eps");
  

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
  

  TCanvas* c_mom = new TCanvas("c_mom2","c_mom2",800,800);
  c_mom->cd(1);
  efficiency->GetXaxis()->SetTitle("|cos(#theta_{trk})|");
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
  leg0->SetTextSize(0.03);
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
  
  // //-----------------------
  // filename =  "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV.root";

  // f = new TFile(filename);
  // kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  // kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  // kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  // kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  // kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  // TH1F* test2 = (TH1F*)f->Get("n_sectracks");

  // n=0;
  // //  option 1, 80eff, 92 pur = 16,21
  // //  option 1, 87eff, 87 pur = 16,23


  // for(int i=2;i<80; i++) {
  //   int ipion=22;
  //   // if(i>16) ipion=22-(i-16);
  //   float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
  //   float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
  //   float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
  //   float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
  //   float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
  //   float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
  //   if(nkaons==0) nkaons=10000000;
  //   x[i-2]=i;
  //   eff[i-2]=100.*(n_kaons)/nkaons;       
  //   //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
  //   pur[i-2]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
  //   n++;
  // }

 
  // TGraph* efficiency2 = new TGraph(n,x,eff);
  // TGraph* purity2 = new TGraph(n,x,pur);
  // TGraph* efficiency_purity2 = new TGraph(n,eff,pur);
  

 
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


  //  efficiency2->SetLineColor(kMagenta+1);
  // efficiency2->SetLineWidth(3);
  // efficiency2->SetLineStyle(2);
  // efficiency2->Draw("same");
  
  // purity2->SetLineColor(kOrange+1);
  // purity2->SetLineWidth(3);
  // purity2->SetLineStyle(2);
  // purity2->Draw("lsame");



  // test->SetLineColor(1);
  // test->SetLineWidth(3);
  // test->SetLineStyle(1);

  // test2->SetLineColor(1);
  // test2->SetLineWidth(3);
  // test2->SetLineStyle(2);
  
  Labels("");
  
  TLegend *leg0 = new TLegend(0.25,0.4,0.5,0.5);
  leg0->SetTextSize(0.03);
  leg0->SetTextFont(42);
  //  leg0->AddEntry(test,"All secondary tracks","l");
  // leg0->AddEntry(test2,"|cos(#theta_{trk})|<0.8","l");
  leg0->AddEntry(efficiency,"Efficiency of Kaon ID","l");
  leg0->AddEntry(purity,"Purity of Kaon ID","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();
  c_mom->Print("plots_draft/eff_purity_momentum_"+squark+".eps");
  

}

void EffPurity_dedxdist(int quarkid) {

  
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

  
  TString filename = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eL_pR_0GeV.root";
  TFile *f = new TFile(filename);
  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  kdEdxdist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon = (TH1F*)f->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron = (TH1F*)f->Get("kdEdx_dist_electron");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(16,i);
    float n_pions=  kdEdxdist_pion->Integral(16,i);
    float n_protons=  kdEdxdist_proton->Integral(16,i);
    float n_muons=  kdEdxdist_muon->Integral(16,i);
    float n_electrons=  kdEdxdist_electron->Integral(16,i);
    x[i-16]=i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-16]=100.*(n_kaons)/nkaons;                    
    pur[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);

  //----------
  TString filename2 = "../results/histos_"+squark+"_secondary_tracks_ignoreoverlay_2f_hadronic_sample_eR_pL_3GeV.root";
  TFile *f2 = new TFile(filename2);
  TH1F*  p_kaon2 = (TH1F*)f2->Get("p_kaon");
  TH1F*  kdEdxdist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon2 = (TH1F*)f2->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron2 = (TH1F*)f2->Get("kdEdx_dist_electron");
  float nkaons2=p_kaon2->GetEntries();

  float x2[10000], eff2[10000], pur2[10000];
  int n2=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon2->Integral(16,i);
    float n_pions=  kdEdxdist_pion2->Integral(16,i);
    float n_protons=  kdEdxdist_proton2->Integral(16,i);
    float n_muons=  kdEdxdist_muon2->Integral(16,i);
    float n_electrons=  kdEdxdist_electron2->Integral(16,i);
    x2[i-16]=i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                     
    eff2[i-16]=100.*(n_kaons)/nkaons2;
    pur2[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }

  x[0]=80.63;
  if(iquark==4) x[0]=80.65;
  float y[100]={0};
  y[0]=87.82;
  if(iquark==4) y[0]=90.54;

  TGraph* working_point = new TGraph(1,x,y);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);
  
  TCanvas* c_mom3 = new TCanvas("c_mom3","c_mom3",800,800);
  c_mom3->cd(1);
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");

  efficiency_purity2->SetLineColor(2);
  efficiency_purity2->SetLineWidth(3);
  efficiency_purity2->SetLineStyle(1);
  efficiency_purity2->Draw("lp");

  working_point->SetMarkerStyle(29);
  working_point->SetMarkerSize(4);
  working_point->SetMarkerColor(kYellow+2);
  working_point->Draw("p");

  Labels("");
  //  QQBARLabel2(0.3,0.2, "Method dEdx-distance",kBlack);

  TLegend *leg0 = new TLegend(0.25,0.5,0.5,0.6);
  leg0->SetTextSize(0.03);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency_purity,"All secondary tracks","l");
  leg0->AddEntry(efficiency_purity2,"|p_{trk}|>3 GeV","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TLegend *leg1 = new TLegend(0.4,0.3,0.6,0.35);
  leg1->SetTextSize(0.03);
  leg1->SetTextFont(42);
  leg1->AddEntry(working_point,"Working Point","p");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   
  c_mom3->Print("plots_draft/eff_purity_"+squark+".eps");

}

void Plots_dEdx_draft() {
  /*for(int i=3; i<6; i++) Mom(i);
  for(int i=3; i<6; i++) Costheta(i);
  Ntracks();*/
  //Ntracks2();

  for(int i=4; i<5; i++)  dEdxdist2(i);
  //for(int i=4; i<6; i++)  dEdxdistProjection(i);
  //for(int i=4; i<6; i++)  dEdxdistProjection2(i);

  /* NHits();
  for(int i=4; i<6; i++) EffPurity_momentum(i);
  for(int i=4; i<6; i++) EffPurity_angle(i);
  for(int i=4; i<6; i++) EffPurity_dedxdist(i);
  dEdx(0);
  dEdx2(0);*/

 
}
