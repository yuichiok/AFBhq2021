#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"


void QQbarAnalysisClass::Selection(int n_entries=-1, int selection_type=0, float Kvcut=50, int bkg=0)
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s.root",process.Data()),"RECREATE");
  MyFile->cd();
  


  //costheta_nocuts
  TH1F * h_costheta_nocuts = new TH1F("h_costheta_nocuts","h_costheta_nocuts",20,0,1);

  //invariant mass
  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);

  TH1F * h_y23_radreturn = new TH1F("h_y23_radreturn","h_y23_radreturn",400,0.0001,0.2501);
  TH1F * h_y23_qq = new TH1F("h_y23_qq","h_y23_qq",400,0.0001,0.2501);

  TH1F * h_d23_radreturn = new TH1F("h_d23_radreturn","h_d23_radreturn",500,0.5,5000.5);
  TH1F * h_d23_qq = new TH1F("h_d23_qq","h_d23_qq",500,0.5,5000.5);

  TH1F * h_thrust_radreturn = new TH1F("h_thrust_radreturn","h_thrust_radreturn",100,0,1);
  TH1F * h_thrust_qq = new TH1F("h_thrust_qq","h_thrust_qq",100,0,1);

  TH1F * h_major_thrust_radreturn = new TH1F("h_major_thrust_radreturn","h_major_thrust_radreturn",100,0,1);
  TH1F * h_major_thrust_qq = new TH1F("h_major_thrust_qq","h_major_thrust_qq",100,0,1);

  TH1F * h_minor_thrust_radreturn = new TH1F("h_minor_thrust_radreturn","h_minor_thrust_radreturn",100,0,1);
  TH1F * h_minor_thrust_qq = new TH1F("h_minor_thrust_qq","h_minor_thrust_qq",100,0,1);

  TH2F * h_major_minor_thrust_radreturn = new TH2F("h_major_minor_thrust_radreturn","h_major_minor_thrust_radreturn",100,0,1,100,0,1);
  TH2F * h_major_minor_thrust_qq = new TH2F("h_major_minor_thrust_qq","h_major_minor_thrust_qq",100,0,1,100,0,1);

  TH2F *h_costheta_energy_radreturn = new TH2F("h_costheta_energy_radreturn", "h_costheta_energy_radreturn", 100, 0, 1, 150, 0.5, 150.5);
  TH2F *h_costheta_energy_qq = new TH2F("h_costheta_energy_qq", "h_costheta_energy_qq", 100, 0, 1, 150, 0.5, 150.5);

  TH2F *h_npfos_radreturn = new TH2F("h_npfos_radreturn", "h_npfos_radreturn", 101, -0.5, 100.5, 101, -0.5, 100.5);
  TH2F *h_npfos_qq = new TH2F("h_npfos_qq", "h_npfos_qq", 101, -0.5, 100.5, 101, -0.5, 100.5);

  //mass of two jets
  TH1F * h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",400,0,200);
  TH1F * h_mj1_mj2_qq = new TH1F("h_mj1_mj2_qq","h_mj1_mj2_qq",400,0,200);
 
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

   
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

 
    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco stuff
    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_qqmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    float costheta_qqbar;
    std::vector<float> p_qqbar;
    p_qqbar.push_back(jet_px[0]-jet_px[1]);
    p_qqbar.push_back(jet_py[0]-jet_py[1]);
    p_qqbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta_qqbar=fabs(GetCostheta(p_qqbar));

    h_costheta_nocuts->Fill(costheta_qqbar);

    float Kv=Kreco();
    float reco_acol_v=AcolValue();
    //parte importante
    bool selection=PreSelection(selection_type);
    if(selection==false) continue;

    //pfos identificados como fotones o como cargados?
    //---------------------
    //Radiative return cuts, photon INSIDE the detector
    PFOphotonQuantities();
    float photonjet_e_max=0;
    float photonjet_cos_max=-2;
    if(photonjet_E[0]>photonjet_E[1]) {
      photonjet_e_max=photonjet_E[0];
      photonjet_cos_max=photonjet_costheta[0];
    } else {
      photonjet_e_max=photonjet_E[1];
      photonjet_cos_max=photonjet_costheta[1];
    }

    // HASTA AQUI Las cosas de PFOs

    if(bkg==1)  {

      h_mjj_qq->Fill(reco_qqmass);
      h_npfos_qq->Fill(npfo[0],npfo[1]);
     
    
      h_y23_qq->Fill(d23/pow(reco_qqmass,2));
      h_d23_qq->Fill(d23);
      h_thrust_qq->Fill(principle_thrust_value);
      h_major_thrust_qq->Fill(major_thrust_value);
      h_minor_thrust_qq->Fill(minor_thrust_value);
      h_major_minor_thrust_qq->Fill(major_thrust_value,minor_thrust_value);

      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_costheta_energy_qq->Fill(fabs(photonjet_cos_max), photonjet_e_max);

    } else {   
      if(gamma_e>Kvcut ) {
   
      h_costheta_energy_radreturn->Fill(fabs(photonjet_cos_max), photonjet_e_max);
      h_mjj_radreturn->Fill(reco_qqmass);
      h_npfos_radreturn->Fill(npfo[0],npfo[1]);
      
      // -------------------------
      h_y23_radreturn->Fill(d23/pow(reco_qqmass,2));
      h_d23_radreturn->Fill(d23);
      h_thrust_radreturn->Fill(principle_thrust_value);
      h_major_thrust_radreturn->Fill(major_thrust_value);
      h_minor_thrust_radreturn->Fill(minor_thrust_value);
      h_major_minor_thrust_radreturn->Fill(major_thrust_value,minor_thrust_value);
      h_mj1_mj2_radreturn->Fill(reco_b1mass+reco_b2mass);
     } else {
   
      h_mjj_qq->Fill(reco_qqmass);
      h_npfos_qq->Fill(npfo[0],npfo[1]);     
    
      h_y23_qq->Fill(d23/pow(reco_qqmass,2));
      h_d23_qq->Fill(d23);
      h_thrust_qq->Fill(principle_thrust_value);
      h_major_thrust_qq->Fill(major_thrust_value);
      h_minor_thrust_qq->Fill(minor_thrust_value);
      h_major_minor_thrust_qq->Fill(major_thrust_value,minor_thrust_value);

      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_costheta_energy_qq->Fill(fabs(photonjet_cos_max), photonjet_e_max);
    }

    
    }
  }

  cout<<TString::Format("selection_%s.root",process.Data())<<endl;

  // save histograms
  h_costheta_nocuts->Write();
      
  h_mjj_qq->Write();
  h_mjj_radreturn->Write();

  h_npfos_qq->Write();
  h_npfos_radreturn->Write();

  h_y23_qq->Write();
  h_y23_radreturn->Write();

  h_d23_qq->Write();
  h_d23_radreturn->Write();

  h_thrust_qq->Write();
  h_thrust_radreturn->Write();
  h_major_thrust_qq->Write();
  h_major_thrust_radreturn->Write();
  h_minor_thrust_qq->Write();
  h_minor_thrust_radreturn->Write();
  h_major_minor_thrust_qq->Write();
  h_major_minor_thrust_radreturn->Write();

  h_mj1_mj2_qq->Write();
  h_mj1_mj2_radreturn->Write();

  h_costheta_energy_qq->Write();
  h_costheta_energy_radreturn->Write();

   
}


