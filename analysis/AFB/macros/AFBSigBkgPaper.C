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
#include "../../common/histograms.h"
#include "utils.h"


TString energy="250GeV";

void Presel(int quark=4) {

  folder="../results_"+energy+"_dNdx/SigBkg_";

  for(int pol=2; pol<4; pol++ ) {

    cout<<" DoubleTag------  Quark:"<<quark<< "pol:"<<pol<<endl;
  int iquark=0, iquark2=1, iquark3=2;
  if(quark==4) {
    iquark=1;
    iquark2=0;
  }

  TH1F *parton = GetHisto2(0,TString::Format("h_AFB_%i",iquark),pol,quark,900,1);
  TH1F *parton_1 = GetHisto2(0,TString::Format("h_AFB_%i",iquark2),pol,quark,900,1);
  TH1F *parton_2 = GetHisto2(0,TString::Format("h_AFB_%i",iquark3),pol,quark,900,1);
  parton->Add(parton_1);
  parton->Add(parton_2);

  TH1F *signal_0 = GetHisto2(0,TString::Format("h_AFBreco_pres_%i",iquark),pol,quark,900,1);
  TH1F *signal_1 = GetHisto2(0,TString::Format("h_AFBreco_pres_%i",iquark2),pol,quark,900,1);
  TH1F *signal_2 = GetHisto2(0,TString::Format("h_AFBreco_pres_%i",iquark3),pol,quark,900,1);
  signal_0->Add(signal_1);
  signal_0->Add(signal_2);

  //TH1F *bkg_hq_0 = GetHisto2(0,TString::Format("h_AFBreco_pres_%i",iquark2),pol,quark,900,1);

  //TH1F *bkg_uds_0 = GetHisto2(0,TString::Format("h_AFBreco_pres_%i",iquark3),pol,quark,900,1);

  TH1F *bkg_radret_0 = GetHisto2(0,TString::Format("h_AFBreco_pres_%i",3),pol,quark,900,1);
 
  TH1F *bkg_zz_0 = GetHisto2(2,TString::Format("h_AFBreco_pres_%i",3),pol,quark,900,0);

  TH1F *bkg_qqH_0 = GetHisto2(3,TString::Format("h_AFBreco_pres_%i",3),pol,quark,900,0);

  TH1F *bkg_ww_0 = GetHisto2(4,TString::Format("h_AFBreco_pres_%i",3),pol,quark,900,0);

  float bs=100.*(bkg_radret_0->Integral()+bkg_zz_0->Integral()+bkg_ww_0->Integral()+bkg_qqH_0->Integral())/signal_0->Integral();
  float eff=100.*(signal_0->Integral())/parton->Integral();
  cout<<"Eff:"<< eff<<"  B/S:"<<bs<< "   %"<<endl;
  }
    
}

void DT(int quark=4) {

  folder="../results_"+energy+"_dNdx/SigBkg_";

  for(int pol=2; pol<4; pol++ ) {

    cout<<" DoubleTag------  Quark:"<<quark<< "pol:"<<pol<<endl;
  int iquark=0, iquark2=1, iquark3=2;
  if(quark==4) {
    iquark=1;
    iquark2=0;
  }

  TH1F *parton = GetHisto2(0,TString::Format("h_AFB_%i",iquark),pol,quark,900,1);
    
  TH1F *signal_0 = GetHisto2(0,TString::Format("h_AFBreco_DT_%i",iquark),pol,quark,900,1);

  TH1F *bkg_hq_0 = GetHisto2(0,TString::Format("h_AFBreco_DT_%i",iquark2),pol,quark,900,1);

  TH1F *bkg_uds_0 = GetHisto2(0,TString::Format("h_AFBreco_DT_%i",iquark3),pol,quark,900,1);

  TH1F *bkg_radret_0 = GetHisto2(0,TString::Format("h_AFBreco_DT_%i",3),pol,quark,900,1);
 
  TH1F *bkg_zz_0 = GetHisto2(2,TString::Format("h_AFBreco_DT_%i",3),pol,quark,900,0);

  TH1F *bkg_qqH_0 = GetHisto2(3,TString::Format("h_AFBreco_DT_%i",3),pol,quark,900,0);

  TH1F *bkg_ww_0 = GetHisto2(4,TString::Format("h_AFBreco_DT_%i",3),pol,quark,900,0);

  float bs=100.*(bkg_radret_0->Integral()+bkg_zz_0->Integral()+bkg_ww_0->Integral()+bkg_qqH_0->Integral()+bkg_hq_0->Integral()+bkg_uds_0->Integral())/signal_0->Integral();
  float eff=100.*(signal_0->Integral())/parton->Integral();
  cout<<"Eff:"<< eff<<"  B/S:"<<bs<< "   %"<<endl;
  }
    
}


void DC(int quark=4) {

  folder="../results_"+energy+"_dNdx/SigBkg_";

  for(int pol=2; pol<4; pol++ ) {

    cout<<" DoubleCharge ------  Quark:"<<quark<< "pol:"<<pol<<endl;
  int iquark=0, iquark2=1, iquark3=2;
  if(quark==4) {
    iquark=1;
    iquark2=0;
  }

  TH1F *parton = GetHisto2(0,TString::Format("h_AFB_%i",iquark),pol,quark,900,1);
    
  TH1F *signal_0 = GetHisto2(0,TString::Format("h_AFBreco_cat0_%i",iquark),pol,quark,900,1);
  TH1F *signal_1 = GetHisto2(0,TString::Format("h_AFBreco_cat1_%i",iquark),pol,quark,900,1);
  TH1F *signal_2 = GetHisto2(0,TString::Format("h_AFBreco_cat2_%i",iquark),pol,quark,900,1);
  signal_0->Add(signal_1);
  signal_0->Add(signal_2);

  TH1F *bkg_hq_0 = GetHisto2(0,TString::Format("h_AFBreco_cat0_%i",iquark2),pol,quark,900,1);
  TH1F *bkg_hq_1 = GetHisto2(0,TString::Format("h_AFBreco_cat1_%i",iquark2),pol,quark,900,1);
  TH1F *bkg_hq_2 = GetHisto2(0,TString::Format("h_AFBreco_cat2_%i",iquark2),pol,quark,900,1);
  bkg_hq_0->Add(bkg_hq_1);
  bkg_hq_0->Add(bkg_hq_2);

  TH1F *bkg_uds_0 = GetHisto2(0,TString::Format("h_AFBreco_cat0_%i",iquark3),pol,quark,900,1);
  TH1F *bkg_uds_1 = GetHisto2(0,TString::Format("h_AFBreco_cat1_%i",iquark3),pol,quark,900,1);
  TH1F *bkg_uds_2 = GetHisto2(0,TString::Format("h_AFBreco_cat2_%i",iquark3),pol,quark,900,1);
  bkg_uds_0->Add(bkg_uds_1);
  bkg_uds_0->Add(bkg_uds_2);

  TH1F *bkg_radret_0 = GetHisto2(0,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,900,1);
  TH1F *bkg_radret_1 = GetHisto2(0,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,900,1);
  TH1F *bkg_radret_2 = GetHisto2(0,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,900,1);
  bkg_radret_0->Add(bkg_radret_1);
  bkg_radret_0->Add(bkg_radret_2);
 
  TH1F *bkg_zz_0 = GetHisto2(2,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,900,0);
  TH1F *bkg_zz_1 = GetHisto2(2,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,900,0);
  TH1F *bkg_zz_2 = GetHisto2(2,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,900,0);
  bkg_zz_0->Add(bkg_zz_1);
  bkg_zz_0->Add(bkg_zz_2);

  TH1F *bkg_qqH_0 = GetHisto2(3,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,900,0);
  TH1F *bkg_qqH_1 = GetHisto2(3,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,900,0);
  TH1F *bkg_qqH_2 = GetHisto2(3,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,900,0);
  bkg_qqH_0->Add(bkg_qqH_1);
  bkg_qqH_0->Add(bkg_qqH_2);

  TH1F *bkg_ww_0 = GetHisto2(4,TString::Format("h_AFBreco_cat0_%i",3),pol,quark,900,0);
  TH1F *bkg_ww_1 = GetHisto2(4,TString::Format("h_AFBreco_cat1_%i",3),pol,quark,900,0);
  TH1F *bkg_ww_2 = GetHisto2(4,TString::Format("h_AFBreco_cat2_%i",3),pol,quark,900,0);
  bkg_ww_0->Add(bkg_ww_1);
  bkg_ww_0->Add(bkg_ww_2);

  float bs=100.*(bkg_radret_0->Integral()+bkg_zz_0->Integral()+bkg_ww_0->Integral()+bkg_qqH_0->Integral()+bkg_hq_0->Integral()+bkg_uds_0->Integral())/signal_0->Integral();
  float eff=100.*(signal_0->Integral())/parton->Integral();
  cout<<"Eff:"<< eff<<"  B/S:"<<bs<< "   %"<<endl;
  }
    
}

void AFBSigBkgPaper(int quark=4) {

  Presel(4);
  Presel(5);
  
  DT(4);
  DT(5);

  DC(4);
  DC(5);

}
