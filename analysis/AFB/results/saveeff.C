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

void saveeff() {

  TFile *MyFile = new TFile("efficiencies_ILDZpole.root","RECREATE");
  
  for(int quark=4; quark<6; quark++) {
    TString filename = TString::Format("AFBreco_pdg%i_2f_hadronic_sample_eL_pR_250GeV_cheatmethod_0.root",quark);
    TFile *f2 = new TFile(filename);
    TH1F* h_AFB=(TH1F*)f2->Get("h_AFB");
    TH1F* h_AFBcheat=(TH1F*)f2->Get("h_AFBcheat");
    
    filename = TString::Format("../weights/eff_weights_pdg%i_pol0.root",quark);
    TFile *f3 = new TFile(filename);
    TH1F* h_pres=(TH1F*)f3->Get("eff_pres");
    h_pres->Sumw2();

    TH1F* h_tagging=(TH1F*)f3->Get("eff_tagging");
    h_tagging->Sumw2();
    
    TH1F* h_AFB2= new TH1F("h_AFB2","h_AFB2",20,0,1);
    TH1F* h_AFBcheat2= new TH1F("h_AFBcheat2","h_AFB2",20,0,1);
    for(int i=0; i<20; i++) {
      h_AFB2->SetBinContent(i+1,h_AFB->GetBinContent(21+i));
      h_AFBcheat2->SetBinContent(i+1,h_AFBcheat->GetBinContent(21+i));
    }
    h_AFBcheat2->Divide(h_AFB2);
    for(int i=0; i<20; i++) {
      h_AFBcheat2->SetBinContent(i+1,h_AFBcheat2->GetBinContent(i+1)/h_pres->GetBinContent(i+1));
    }
    
    h_AFBcheat2->Draw();
    
  

    if(quark==4) {
      MyFile->cd();
      //  h_pres->SetName("eff_preselection");
      // h_pres->Write();
      h_tagging->SetName("effc");
      h_tagging->Write();
      h_AFBcheat2->SetName("eff_AFBc");
      h_AFBcheat2->Write();
    }
    if(quark==5) {
      MyFile->cd();
      h_tagging->SetName("effb");
      h_tagging->Write();
      h_AFBcheat2->SetName("eff_AFBb");
      h_AFBcheat2->Write();
    }

  }
}
