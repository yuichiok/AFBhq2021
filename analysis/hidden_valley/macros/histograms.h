TString folder = "../results/";
void Labels()
{

  //QQBARLabel(ildx, 0.953, "");
  QQBARLabel2(0.04, 0.04,"Analysis at particle level, Pythia8", kOrange + 3);

}

void LabelsReco()
{

  //QQBARLabel(ildx, 0.953, "");
  QQBARLabel2(0.04, 0.04,"Pythia8+SGV (ILC detector)", kOrange + 3);

}

std::vector<TH1F *> GetHisto1D(TString sample = "2f_hadronic_sample", float lum = 900, std::vector<TString> histonames={"h_mjj","h_mj1_mj2","h_y23","h_d23","h_thrust","h_major_thrust","h_minor_thrust"}, TString pol="unpol")
{


  std::vector<TH1F *> h1;
  std::vector<TH1F *> h0;

  TString filename = folder + "_" + sample +  ".root";
  cout<<filename<<endl;

  TFile *f = new TFile(filename);
  TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");
  h1.push_back(h_luminosity_cross_2f);
  TH1F * htemp[20];
  for(int j=0; j<histonames.size(); j++) {
    htemp[j]= (TH1F *)f->Get(histonames.at(j));
    h1.push_back(htemp[j]);
  }

  float cross_sec_temp=0;
  for(int i=0; i<cross_section_pairs.size(); i++) {
    if(cross_section_pairs.at(i).first==sample+"_"+pol) cross_sec_temp=cross_section_pairs.at(i).second;
  }
  if(cross_sec_temp==0) {
    cout<<" ERRORR !! NO CROSS SECTION FOUND FOR SAMPLE "<<sample<<" ... in GetHisto1D"<<endl;
    return h0;
  }

  float luminosity_sample = h_luminosity_cross_2f->GetEntries() / cross_sec_temp;
  for (int j = 0; j < h1.size(); j++) 
    h1.at(j)->Scale(lum / luminosity_sample);


  return h1;

}




std::vector<TH2F *> GetHisto2D(TString sample = "2f_hadronic_sample", float lum = 900, std::vector<TString> histonames={"h_nch","h_npfos","h_costheta_energy","h_mw1_mw2","h_major_minor_thrust"},bool norm=true, TString pol="unpol")
{

  std::vector<TH2F *> h1;
  std::vector<TH2F *> h0;


  TString filename = folder + "_" + sample +  ".root";
  TFile *f = new TFile(filename);
  TH1F *h_luminosity_cross_2f = (TH1F *)f->Get("h_costheta_nocuts");
  TH2F * htemp[20];
  for(int j=0; j<histonames.size(); j++) {
    htemp[j]= (TH2F *)f->Get(histonames.at(j));
    h1.push_back(htemp[j]);
  }

  float cross_sec_temp=0;
  for(int i=0; i<cross_section_pairs.size(); i++) {
    if(cross_section_pairs.at(i).first==sample+"_"+pol) cross_sec_temp=cross_section_pairs.at(i).second;
  }
  if(cross_sec_temp==0) {
    cout<<" ERRORR !! NO CROSS SECTION FOUND FOR SAMPLE"<<sample<<" ... in GetHisto2D"<<endl;
    return h0;
  }

  float luminosity_sample = h_luminosity_cross_2f->GetEntries() / cross_sec_temp;
  if(norm==true) {
    for (int j = 0; j < h1.size(); j++)
      h1.at(j)->Scale(lum / luminosity_sample);
  }

  return h1;


}
