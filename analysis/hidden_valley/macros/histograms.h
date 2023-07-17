TString folder = "../results/";
void Labels(int i = 0, int ipol = 1, float lum = 900, float ildx=0.86)
{

  //QQBARLabel(ildx, 0.953, "");
  QQBARLabel2(0.04, 0.04, TString::Format("cuts-%i",i), kOrange + 3);
  /*if (i == 0)
    QQBARLabel2(0.04, 0.07, "[No Cuts]", kOrange + 3);
  if (i == 1)
    QQBARLabel2(0.04, 0.07, "photon veto_{0}", kOrange + 3);
  if (i == 2)
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 3);
  if (i == 3)
  {
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 3);
    QQBARLabel2(0.04, 0.04, "& m_{jj} cuts", kOrange + 3);
  }
    if (i == 4)
  {
    QQBARLabel2(0.04, 0.07, "photon veto cut", kOrange + 3);
    QQBARLabel2(0.04, 0.04, "& m_{jj} & T<0.8 cuts", kOrange + 3);
  }*/

  QQBARLabel2(0.8, 0.03, TString::Format("Int.Lum=%i fb^{-1}", int(lum)), kGray + 1);

  if (ipol == 0)
    QQBARLabel2(0.7, 0.03, "e_{L}^{-}e_{R}^{+} ", kGray + 1);
  if (ipol == 1)
    QQBARLabel2(0.7, 0.03, "e_{R}^{-}e_{L}^{+} ", kGray + 1);

  if (ipol == 2)
    QQBARLabel2(0.6, 0.03, "e_{L}^{-}e_{R}^{+}(80,30) ", kGray + 1);
  if (ipol == 3)
    QQBARLabel2(0.6, 0.03, "e_{R}^{-}e_{L}^{+}(80,30)", kGray + 1);
}

TH1F * PolHisto(TH1F *h1, TH1F* h2, int pol) {

  // this function takes two histograms, 100% polarized, normalized to the same luminosity 
  // and calcualtes the result of the ILC polarisation default options
  // 0=100% eL, 1=100% eR, 2=80%eL,30%pR, 2=80%eR,30%pL

  TH1F *hnew = (TH1F*)h1->Clone("hnew");
  float global=0, a=0., b=0.;
  float p1=-0.8, p2=0.3;

  if(pol==3) {
    p1=0.8;
    p2=-0.3;
  }


  global= 0.25* (1-p1*p2);
  float peff = (p1-p2)/(1-p1*p2);

  a=global*(1-peff);
  b=global*(1+peff);

  for(int i=0; i<hnew->GetNbinsX()+1; i++) {
    float nprime1=a*h1->GetBinContent(i);
    float nprime2=b*h2->GetBinContent(i);
    
    hnew->SetBinError(i,sqrt(nprime1+nprime2));
    hnew->SetBinContent(i, nprime1 + nprime2 );
  }
 
  return hnew;

}

TH2F * PolHisto(TH2F *h1, TH2F* h2, int pol) {

  // this function takes two histograms, 100% polarized, normalized to the same luminosity 
  // and calcualtes the result of the ILC polarisation default options
  // 0=100% eL, 1=100% eR, 2=80%eL,30%pR, 2=80%eR,30%pL

  TH2F *hnew = (TH2F*)h1->Clone("hnew");
  float global=0, a=0., b=0.;
  float p1=-0.8, p2=0.3;

  if(pol==3) {
    p1=0.8;
    p2=-0.3;
  }

  global= 0.25* (1-p1*p2);
  float peff = (p1-p2)/(1-p1*p2);

  a=global*(1-peff);
  b=global*(1+peff);

  for(int i=0; i<hnew->GetNbinsX()+1; i++) {
      for(int j=0; j<hnew->GetNbinsY()+1; j++) {

        float nprime1=a*h1->GetBinContent(i,j);
        float nprime2=b*h2->GetBinContent(i,j);
      
        hnew->SetBinError(i,j,sqrt(nprime1+nprime2));
        hnew->SetBinContent(i,j, nprime1 + nprime2 );
      }
  }
 
  return hnew;

}

std::vector<TH1F *> GetHisto1D(TString sample = "2f_hadronic_sample", int ipol = 0, int ibkg = 0, float lum = 900, std::vector<TString> histonames={"h_mjj","h_mj1_mj2","h_y23","h_d23","h_thrust","h_major_thrust","h_minor_thrust"} , bool radret=true)
{

  TString pol[2] = {"eL_pR", "eR_pL"};

  std::vector<TH1F *> h1_pol[3];

  for (int i = 0; i < 2; i++)
  {

    TString filename = folder + "_" + sample + "_" + pol[i] + ".root";
    if (sample == "radreturn")
    {
      filename = folder + "_" + "2f_hadronic_sample_" + pol[i] + ".root";
      //ibkg = 1;
    }
    if (sample == "qq")
    {
      filename = folder + "_" + "2f_hadronic_" + pol[i] + ".root";
      //ibkg = 1;
    }


    TFile *f = new TFile(filename);
    TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");
    if (sample == "radreturn" && radret==true)
    {
      h1_pol[i].push_back(h_luminosity_cross_2f);
      TH1F * htemp[20];
      for(int j=0; j<histonames.size(); j++) {
        htemp[j]= (TH1F *)f->Get(histonames.at(j)+"_radreturn");
        h1_pol[i].push_back(htemp[j]);
      }
    }
    else
    {

      h1_pol[i].push_back(h_luminosity_cross_2f);
      TH1F * htemp[20];
      for(int j=0; j<histonames.size(); j++) {
        htemp[j]= (TH1F *)f->Get(histonames.at(j));
        h1_pol[i].push_back(htemp[j]);
      }
    }

    float luminosity_sample = h_luminosity_cross_2f->GetEntries() / cross_section[i][ibkg];
    for (int j = 0; j < h1_pol[i].size(); j++) 
      h1_pol[i].at(j)->Scale(lum / luminosity_sample);
  }

  if(ipol<2) return h1_pol[ipol];

  for (int j = 0; j < h1_pol[0].size(); j++)  {
    h1_pol[2].push_back(PolHisto(h1_pol[0].at(j),h1_pol[1].at(j),ipol));
  }

  return h1_pol[2];
}




std::vector<TH2F *> GetHisto2D(TString sample = "2f_hadronic_sample", int ipol = 0, int ibkg = 0, float lum = 900, std::vector<TString> histonames={"h_nch","h_npfos","h_costheta_energy","h_mw1_mw2","h_major_minor_thrust"},bool norm=true, bool radret=true)
{

  TString pol[2] = {"eL_pR", "eR_pL"};
  std::vector<TH2F *> h1_pol[3];
  for (int i = 0; i < 2; i++)
  {
    TString filename = folder + "_" + sample + "_" + pol[i] + ".root";
    if (sample == "radreturn")
    {
      filename = folder + "_" + "2f_hadronic_sample_" + pol[i] + ".root";
      //ibkg = 1;
    }
    if (sample == "qq")
    {
      filename = folder + "_" + "2f_hadronic_" + pol[i] + ".root";
      //ibkg = 1;
    }


  
    TFile *f = new TFile(filename);
    TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");
    
    if (sample == "radreturn" && radret==true)
    {
      TH2F * htemp[20];
      for(int j=0; j<histonames.size(); j++) {
        htemp[j]= (TH2F *)f->Get(histonames.at(j)+"_radreturn");
        h1_pol[i].push_back(htemp[j]);
      }
    }
    else
    {
      TH2F * htemp[20];
      for(int j=0; j<histonames.size(); j++) {
        htemp[j]= (TH2F *)f->Get(histonames.at(j));
        h1_pol[i].push_back(htemp[j]);
      }
    }

    float luminosity_sample = h_luminosity_cross_2f->GetEntries() / cross_section[i][ibkg];
    if(norm==true) {
      for (int j = 0; j < h1_pol[i].size(); j++)
        h1_pol[i].at(j)->Scale(lum / luminosity_sample);
    }
  }
  if(ipol<2) return h1_pol[ipol];

  for (int j = 0; j < h1_pol[0].size(); j++)  {
    h1_pol[2].push_back(PolHisto(h1_pol[0].at(j),h1_pol[1].at(j),ipol));
  }

  return h1_pol[2];  // Scale histograms with polarisation //to be done

}
