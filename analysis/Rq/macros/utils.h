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




void Labels(int ipol, int iquark, int lum){
  QQBARLabel(0.86,0.952," work in progress");
  TString quark= "c#bar{c}";
  if(iquark==5) quark="b#bar{b}";

  TString pol[]={"e_{L}^{-}e_{R}^{+}","e_{R}^{-}e_{L}^{+}","e_{L,80%}^{-}e_{R,30%}^{+}","e_{R,80%}^{-}e_{L,30%}^{+}","e^{-}e^{+}"};
  QQBARLabel2(0.1,0.05, pol[ipol]+" #rightarrow "+quark+" mc-2020. "+TString::Format("Lum = %i fb^{-1}",lum),kGray+2);


}

