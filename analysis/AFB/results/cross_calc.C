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
#include "../../common/cross_sections.h"

void cross_calc() {

  for(int ipol=0; ipol<2; ipol++) {

  TString pol_string="eL_pR";
  if(ipol==1) pol_string="eR_pL";
  
  for(int quark=4; quark<5; quark++) {

    float n_signal=0;
    float n_radret=0;
    float n_total=0;
    float n_qq=0;
    float n_bb=0;
    float n_cc=0;

    TString filename = TString::Format("AFB_PQ_pdg%i_2f_hadronic_sample_"+pol_string+"_250GeV.root",quark);
    TFile *f2 = new TFile(filename);
    cout<<filename<<endl;
    TH1F* h_total= (TH1F*)f2->Get("h_Ntotal_nocuts");
    TH1F* h_qqbar0= (TH1F*)f2->Get("h_Ntotal_nocuts_0");
    TH1F* h_qqbar1= (TH1F*)f2->Get("h_Ntotal_nocuts_1");
    TH1F* h_qqbar2= (TH1F*)f2->Get("h_Ntotal_nocuts_2");
    TH1F* h_qqbar3= (TH1F*)f2->Get("h_Ntotal_nocuts_3");

    n_total=h_total->Integral();
    n_signal+=h_qqbar0->Integral();
    n_signal+=h_qqbar1->Integral();
    n_signal+=h_qqbar2->Integral();
    n_radret=h_qqbar3->Integral();
    n_qq=h_qqbar2->Integral();
    n_cc=h_qqbar1->Integral();
    n_bb=h_qqbar0->Integral();
    
    float lum= (n_total)/cross_section[ipol][3];
    float cross_signal=n_signal/lum;
    float cross_radret=n_radret/lum;
    float cross_qq=n_qq/lum;
    float cross_cc=n_cc/lum;
    float cross_bb=n_bb/lum;

    cout<<quark<<" "<<pol_string<<" #simga [fb] qqbar="<<cross_signal<<" uds="<<cross_qq<<" cc="<<cross_cc<<" bb="<<cross_bb<<" radret="<<cross_radret<<endl;

  }
  }
}
