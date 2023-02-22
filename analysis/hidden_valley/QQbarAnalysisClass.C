#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"

void QQbarAnalysisClass::Selection(int n_entries = -1, int selection_type = 0, float Kvcut = 50, int bkg = 0)
{

  TFile *MyFile = new TFile(TString::Format("selection_%s.root", process.Data()), "RECREATE");
  MyFile->cd();

  // costheta_nocuts
  TH1F *h_costheta_nocuts = new TH1F("h_costheta_nocuts", "h_costheta_nocuts", 20, 0, 1);

  // invariant mass
  TH1F *h_mjj = new TH1F("h_mjj", "h_mjj", 100, 0, 500);
  TH1F *h_mjj_radreturn = new TH1F("h_mjj_radreturn", "h_mjj_radreturn", 100, 0, 500);

  TH1F *h_y23_radreturn = new TH1F("h_y23_radreturn", "h_y23_radreturn", 400, 0.0001, 0.2501);
  TH1F *h_y23 = new TH1F("h_y23", "h_y23", 400, 0.0001, 0.2501);

  TH1F *h_d23_radreturn = new TH1F("h_d23_radreturn", "h_d23_radreturn", 500, 0.5, 5000.5);
  TH1F *h_d23 = new TH1F("h_d23", "h_d23", 500, 0.5, 5000.5);

  TH1F *h_thrust_radreturn = new TH1F("h_thrust_radreturn", "h_thrust_radreturn", 100, 0, 1);
  TH1F *h_thrust = new TH1F("h_thrust", "h_thrust", 100, 0, 1);

  TH1F *h_major_thrust_radreturn = new TH1F("h_major_thrust_radreturn", "h_major_thrust_radreturn", 100, 0, 1);
  TH1F *h_major_thrust = new TH1F("h_major_thrust", "h_major_thrust", 100, 0, 1);

  TH1F *h_minor_thrust_radreturn = new TH1F("h_minor_thrust_radreturn", "h_minor_thrust_radreturn", 100, 0, 1);
  TH1F *h_minor_thrust = new TH1F("h_minor_thrust", "h_minor_thrust", 100, 0, 1);

  TH2F *h_major_minor_thrust_radreturn = new TH2F("h_major_minor_thrust_radreturn", "h_major_minor_thrust_radreturn", 100, 0, 1, 100, 0, 1);
  TH2F *h_major_minor_thrust = new TH2F("h_major_minor_thrust", "h_major_minor_thrust", 100, 0, 1, 100, 0, 1);

  TH2F *h_costheta_energy_radreturn = new TH2F("h_costheta_energy_radreturn", "h_costheta_energy_radreturn", 100, 0, 1, 150, 0.5, 150.5);
  TH2F *h_costheta_energy = new TH2F("h_costheta_energy", "h_costheta_energy", 100, 0, 1, 150, 0.5, 150.5);

  TH2F *h_npfos_radreturn = new TH2F("h_npfos_radreturn", "h_npfos_radreturn", 101, -0.5, 100.5, 101, -0.5, 100.5);
  TH2F *h_npfos = new TH2F("h_npfos", "h_npfos", 101, -0.5, 100.5, 101, -0.5, 100.5);

  // mass of two jets
  TH1F *h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn", "h_mj1_mj2_radreturn", 400, 0, 200);
  TH1F *h_mj1_mj2 = new TH1F("h_mj1_mj2", "h_mj1_mj2", 400, 0, 200);

  TH2F *h_mw1_mw2_radreturn = new TH2F("h_mw1_mw2_radreturn", "h_mw1_mw2_radreturn", 201, -0.5, 200.5, 201, -0.5, 200.5);
  TH2F *h_mw1_mw2 = new TH2F("h_mw1_mw2", "h_mw1_mw2", 201, -0.5, 200.5, 201, -0.5, 200.5);


  Long64_t nentries;
  if (n_entries > 0)
    nentries = n_entries;
  else
    nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    //-------------------
    // Kv parton
    float gamma0_e = mc_ISR_E[0];
    float gamma1_e = mc_ISR_E[1];
    float gamma_e = gamma0_e + gamma1_e;

    if (jentry > 1000 && jentry % 1000 == 0)
      std::cout << "Progress: " << 100. * jentry / nentries << " %" << endl;

    // reco stuff
    double reco_b1mass = sqrt(pow(jet_E[0], 2) - pow(jet_px[0], 2) - pow(jet_py[0], 2) - pow(jet_pz[0], 2));
    double reco_b2mass = sqrt(pow(jet_E[1], 2) - pow(jet_px[1], 2) - pow(jet_py[1], 2) - pow(jet_pz[1], 2));
    double recomass = sqrt(pow(jet_E[0] + jet_E[1], 2) - pow(jet_px[0] + jet_px[1], 2) - pow(jet_py[0] + jet_py[1], 2) - pow(jet_pz[0] + jet_pz[1], 2));

    float costheta_qqbar;
    std::vector<float> p_qqbar;
    p_qqbar.push_back(jet_px[0] - jet_px[1]);
    p_qqbar.push_back(jet_py[0] - jet_py[1]);
    p_qqbar.push_back(jet_pz[0] - jet_pz[1]);
    costheta_qqbar = fabs(GetCostheta(p_qqbar));

    h_costheta_nocuts->Fill(costheta_qqbar);

    // parte importante
    bool selection = PreSelection(selection_type);
    if (selection == false)
      continue;

    // pfos identificados como fotones o como cargados?
    //---------------------
    // Radiative return cuts, photon INSIDE the detector
    PFOphotonQuantities();
    float photonjet_e_max = 0;
    float photonjet_cos_max = -2;
    if (photonjet_E[0] > photonjet_E[1])
    {
      photonjet_e_max = photonjet_E[0];
      photonjet_cos_max = photonjet_costheta[0];
    }
    else
    {
      photonjet_e_max = photonjet_E[1];
      photonjet_cos_max = photonjet_costheta[1];
    }

    std::vector<float> mw1mw2=MW1_MW2();

    // HASTA AQUI Las cosas de PFOs

    if (bkg == 1)
    {

      h_mjj->Fill(recomass);
      h_npfos->Fill(npfo[0], npfo[1]);

      h_y23->Fill(d23 / pow(recomass, 2));
      h_d23->Fill(d23);
      h_thrust->Fill(principle_thrust_value);
      h_major_thrust->Fill(major_thrust_value);
      h_minor_thrust->Fill(minor_thrust_value);
      h_major_minor_thrust->Fill(major_thrust_value, minor_thrust_value);

      h_mj1_mj2->Fill(reco_b1mass + reco_b2mass);
      h_costheta_energy->Fill(fabs(photonjet_cos_max), photonjet_e_max);
      h_mw1_mw2->Fill(mw1mw2.at(0),mw1mw2.at(1)) ;
    }
    else
    {
      if (gamma_e > Kvcut)
      {

        h_costheta_energy_radreturn->Fill(fabs(photonjet_cos_max), photonjet_e_max);
        h_mjj_radreturn->Fill(recomass);
        h_npfos_radreturn->Fill(npfo[0], npfo[1]);

        // -------------------------
        h_y23_radreturn->Fill(d23 / pow(recomass, 2));
        h_d23_radreturn->Fill(d23);
        h_thrust_radreturn->Fill(principle_thrust_value);
        h_major_thrust_radreturn->Fill(major_thrust_value);
        h_minor_thrust_radreturn->Fill(minor_thrust_value);
        h_major_minor_thrust_radreturn->Fill(major_thrust_value, minor_thrust_value);
        h_mj1_mj2_radreturn->Fill(reco_b1mass + reco_b2mass);
        h_mw1_mw2_radreturn->Fill(mw1mw2.at(0),mw1mw2.at(1)) ;

      }
      else
      {

        h_mjj->Fill(recomass);
        h_npfos->Fill(npfo[0], npfo[1]);

        h_y23->Fill(d23 / pow(recomass, 2));
        h_d23->Fill(d23);
        h_thrust->Fill(principle_thrust_value);
        h_major_thrust->Fill(major_thrust_value);
        h_minor_thrust->Fill(minor_thrust_value);
        h_major_minor_thrust->Fill(major_thrust_value, minor_thrust_value);

        h_mj1_mj2->Fill(reco_b1mass + reco_b2mass);
        h_costheta_energy->Fill(fabs(photonjet_cos_max), photonjet_e_max);

        h_mw1_mw2->Fill(mw1mw2.at(0),mw1mw2.at(1)) ;

      }
    }
  }

  cout << TString::Format("selection_%s.root", process.Data()) << endl;

  // save histograms
  h_costheta_nocuts->Write();

  h_mjj->Write();
  h_mjj_radreturn->Write();

  h_npfos->Write();
  h_npfos_radreturn->Write();

  h_y23->Write();
  h_y23_radreturn->Write();

  h_d23->Write();
  h_d23_radreturn->Write();

  h_thrust->Write();
  h_thrust_radreturn->Write();
  h_major_thrust->Write();
  h_major_thrust_radreturn->Write();
  h_minor_thrust->Write();
  h_minor_thrust_radreturn->Write();
  h_major_minor_thrust->Write();
  h_major_minor_thrust_radreturn->Write();

  h_mj1_mj2->Write();
  h_mj1_mj2_radreturn->Write();

  h_costheta_energy->Write();
  h_costheta_energy_radreturn->Write();

  h_mw1_mw2->Write();
  h_mw1_mw2_radreturn->Write();

}

void QQbarAnalysisClass::QCDCorr(int n_entries = -1, int selection_type = 0)
{

  TString name=TString::Format("/lhome/ific/a/airqui/QQbar/AFBhq2021-dev/analysis/hidden_valley/output/QCDcorrelations_%s.root", process.Data());

  TFile *MyFile = new TFile(name ,"RECREATE");
  MyFile->cd();

  TH1F *h_costheta_nocuts = new TH1F("h_costheta_nocuts", "h_costheta_nocuts", 20, 0, 1);
  TH1F *h_costheta_cuts = new TH1F("h_costheta_cuts", "h_costheta_cuts", 20, 0, 1);

  TH1F *ncharged = new TH1F("ncharged", "Content of charged PFOs. (p_{T}>1GeV); # charged PFOs; ",200, -0.5,199.5);
  TH1F *mom = new TH1F("mom", "Momentum of charged PFOs. (p_{T}>1GeV); |#vec{p_{PFO}}|; ",300 ,-0.5,149.5);

  TH1F *ncharged_MC = new TH1F("ncharged_MC", "Content of charged MCpart. (p_{T}>1GeV); # charged PFOs; ",200, -0.5,199.5);
  TH1F *mom_MC = new TH1F("mom_MC", "Momentum of charged MCpart. (p_{T}>1GeV); |#vec{p_{PFO}}|; ",300 ,-0.5,149.5);

  S2 = new TH2F("S2", "S2; #Delta Cos(#theta); #Delta #phi; S2", 200, -1, 1, 200, -6.283185307, 6.283185307);
  B2= new TH2F("B2", "B2; #Delta Cos(#theta); #Delta #phi; B2", 200, -1, 1, 200, -6.283185307, 6.283185307);
  S2_eta = new TH2F("S2_eta", "S2_eta; #Delta #eta; #Delta #phi; S2", 400, -4, 4, 200, -6.283185307, 6.283185307);
  B2_eta = new TH2F("B2_eta", "B2_eta; #Delta #eta; #Delta #phi; B2", 400, -4, 4, 200, -6.283185307, 6.283185307);
  
  S2_MC = new TH2F("S2_MC", "S2; #Delta Cos(#theta); #Delta #phi; S2", 200, -1, 1, 200, -6.283185307, 6.283185307);
  B2_MC= new TH2F("B2_MC", "B2; #Delta Cos(#theta); #Delta #phi; B2", 200, -1, 1, 200, -6.283185307, 6.283185307);
  S2_MC_eta = new TH2F("S2_MC_eta", "S2_eta; #Delta #eta; #Delta #phi; S2", 400, -4, 4, 200, -6.283185307, 6.283185307);
  B2_MC_eta = new TH2F("B2_MC_eta", "B2_eta; #Delta #eta; #Delta #phi; B2", 400, -4, 4, 200, -6.283185307, 6.283185307);

  Long64_t nentries;
  if (n_entries > 0)
    nentries = n_entries;
  else
    nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;

    //-------------------
    // Kv parton
    float gamma0_e = mc_ISR_E[0];
    float gamma1_e = mc_ISR_E[1];
    float gamma_e = gamma0_e + gamma1_e;
   
    h_costheta_nocuts->Fill(0.5);

    if (jentry > 1000 && jentry % 1000 == 0)
      std::cout << "Progress: " << 100. * jentry / nentries << " %" << endl;

    // parte importante
    bool selection = PreSelection(selection_type);
    if (selection == false)
      continue;

    h_costheta_cuts->Fill(0.5);


    //**************************************************************************************
    // DETECTOR LEVEL
    std::vector<float> Tprinc;
    Tprinc.push_back(principle_thrust_axis[0]);
    Tprinc.push_back(principle_thrust_axis[1]);
    Tprinc.push_back(principle_thrust_axis[2]);

    std::vector<float> Tmajor;
    Tmajor.push_back(major_thrust_axis[0]);
    Tmajor.push_back(major_thrust_axis[1]);
    Tmajor.push_back(major_thrust_axis[2]);

    std::vector<float> Tminor;
    Tminor.push_back(minor_thrust_axis[0]);
    Tminor.push_back(minor_thrust_axis[1]);
    Tminor.push_back(minor_thrust_axis[2]);

    int npfo_charged = 0;
    std::vector<float> theta_charged_temp;
    std::vector<float> eta_charged_temp;
    std::vector<float> phi_charged_temp;
    std::vector<int> ipfo_temp;

    for (int ipfo = 0; ipfo < pfo_n; ipfo++)
    {

      std::vector<float> angles = ChargedPFOThetaPhi(ipfo,Tprinc,Tmajor,Tminor);
      if(angles.size()==0) continue;
      mom->Fill(sqrt(pow(pfo_px[ipfo], 2) + pow(pfo_py[ipfo], 2) + pow(pfo_pz[ipfo], 2)));
      npfo_charged++;

      theta_charged_temp.push_back(angles.at(0));
      eta_charged_temp.push_back(angles.at(1));
      phi_charged_temp.push_back(angles.at(2));
      ipfo_temp.push_back(ipfo);
    }
    ncharged->Fill(npfo_charged);


    for (int jpfo = 0; jpfo < pfo_n; jpfo++)
    {
      std::vector<float> angles = ChargedPFOThetaPhi(jpfo,Tprinc,Tmajor,Tminor);
      if(angles.size()==0) continue;
      float theta2 = angles.at(0);
      float eta2 = angles.at(1);
      float phi2 = angles.at(2);

      for (int i = 0; i < theta_charged_temp.size(); i++)
      {
        if (jpfo == ipfo_temp.at(i))
          continue;

        float etadif = eta_charged_temp.at(i) - eta2;
        float thetadif = theta_charged_temp.at(i) - theta2;
        float phidif = phi_charged_temp.at(i) - phi2;
        S2->Fill(thetadif, phidif);
        S2_eta->Fill(etadif, phidif);

      }
    }

    FillBkg(theta_charged_temp,eta_charged_temp, phi_charged_temp);

    eta_charged_temp.clear();
    theta_charged_temp.clear();
    phi_charged_temp.clear();

    //**************************************************************************************
    // Particle LEVEL
    std::vector<float> TprincMC;
    TprincMC.push_back(mc_principle_thrust_axis[0]);
    TprincMC.push_back(mc_principle_thrust_axis[1]);
    TprincMC.push_back(mc_principle_thrust_axis[2]);

    std::vector<float> TmajorMC;
    TmajorMC.push_back(mc_major_thrust_axis[0]);
    TmajorMC.push_back(mc_major_thrust_axis[1]);
    TmajorMC.push_back(mc_major_thrust_axis[2]);

    std::vector<float> TminorMC;
    TminorMC.push_back(mc_minor_thrust_axis[0]);
    TminorMC.push_back(mc_minor_thrust_axis[1]);
    TminorMC.push_back(mc_minor_thrust_axis[2]);

    int nMC_charged = 0;
    std::vector<float> theta_charged_temp_MC;
    std::vector<float> eta_charged_temp_MC;
    std::vector<float> phi_charged_temp_MC;
    std::vector<int> iMC_temp;

    //MC
    for (int imc = 0; imc < mc_stable_n; imc++)
    {

      std::vector<float> angles = ChargedMCThetaPhi(imc,TprincMC,TmajorMC,TminorMC);
      if(angles.size()==0) continue;
      mom_MC->Fill(sqrt(pow(mc_stable_px[imc], 2) + pow(mc_stable_py[imc], 2) + pow(mc_stable_pz[imc], 2)));
      nMC_charged++;

      theta_charged_temp_MC.push_back(angles.at(0));
      eta_charged_temp_MC.push_back(angles.at(1));
      phi_charged_temp_MC.push_back(angles.at(2));
      iMC_temp.push_back(imc);
    }
    ncharged_MC->Fill(nMC_charged);

    for (int jmc = 0; jmc < mc_stable_n; jmc++)
    {
      std::vector<float> angles = ChargedMCThetaPhi(jmc,TprincMC,TmajorMC,TminorMC);
      if(angles.size()==0) continue;
      float theta2 = angles.at(0);
      float eta2 = angles.at(1);
      float phi2 = angles.at(2);

      for (int i = 0; i < theta_charged_temp_MC.size(); i++)
      {
        if (jmc == iMC_temp.at(i))
          continue;

        float etadif = eta_charged_temp_MC.at(i) - eta2;
        float thetadif = theta_charged_temp_MC.at(i) - theta2;
        float phidif = phi_charged_temp_MC.at(i) - phi2;
        S2_MC->Fill(thetadif, phidif);
        S2_MC_eta->Fill(etadif, phidif);

      }
      // C2->Fill(thetadif, phidif);
    }

    FillBkgMC(theta_charged_temp_MC,eta_charged_temp_MC, phi_charged_temp_MC);

    eta_charged_temp_MC.clear();
    theta_charged_temp_MC.clear();
    phi_charged_temp_MC.clear();



  } // jentry

  h_costheta_nocuts->Write();
  h_costheta_cuts->Write();

  ncharged->Write();
  mom->Write();

  S2->Write();
  B2->Write();
  S2_eta->Write();
  B2_eta->Write();

  ncharged_MC->Write();
  mom_MC->Write();

  S2_MC->Write();
  B2_MC->Write();
  S2_MC_eta->Write();
  B2_MC_eta->Write();

}

void QQbarAnalysisClass::FillBkg(std::vector<float> theta_charged_temp, std::vector<float> eta_charged_temp, std::vector<float> phi_charged_temp)
{

  if (theta_charged.size() > 0)
  {
    for (int jpfo = 0; jpfo < theta_charged.size(); jpfo++)
    {
      for (int i = 0; i < theta_charged_temp.size(); i++)
      {
        float etadif = eta_charged_temp.at(i) - eta_charged.at(jpfo);
        float thetadif = theta_charged_temp.at(i) - theta_charged.at(jpfo);
        float phidif = phi_charged_temp.at(i) - phi_charged.at(jpfo);
        B2->Fill(thetadif, phidif);
        B2_eta->Fill(etadif, phidif);
      }
    }
    eta_charged.clear();
    theta_charged.clear();
    phi_charged.clear();
  }

  if (theta_charged.size() == 0)
  {
    for (int i = 0; i < theta_charged_temp.size(); i++)
    {
      theta_charged.push_back(theta_charged_temp.at(i));
      eta_charged.push_back(eta_charged_temp.at(i));
      phi_charged.push_back(phi_charged_temp.at(i));
    }
  }
}

void QQbarAnalysisClass::FillBkgMC(std::vector<float> theta_charged_temp, std::vector<float> eta_charged_temp, std::vector<float> phi_charged_temp)
{

  if (theta_charged_MC.size() > 0)
  {
    for (int jpfo = 0; jpfo < theta_charged_MC.size(); jpfo++)
    {
      for (int i = 0; i < theta_charged_temp.size(); i++)
      {
        float etadif = eta_charged_temp.at(i) - eta_charged_MC.at(jpfo);
        float thetadif = theta_charged_temp.at(i) - theta_charged_MC.at(jpfo);
        float phidif = phi_charged_temp.at(i) - phi_charged_MC.at(jpfo);
        B2_MC->Fill(thetadif, phidif);
        B2_MC_eta->Fill(etadif, phidif);
      }
    }
    eta_charged_MC.clear();
    theta_charged_MC.clear();
    phi_charged_MC.clear();
  }

  if (theta_charged_MC.size() == 0)
  {
    for (int i = 0; i < theta_charged_temp.size(); i++)
    {
      theta_charged_MC.push_back(theta_charged_temp.at(i));
      eta_charged_MC.push_back(eta_charged_temp.at(i));
      phi_charged_MC.push_back(phi_charged_temp.at(i));
    }
  }
}



float QQbarAnalysisClass::ProjectionVector(std::vector<float> p, std::vector<float> T) {

  return (p.at(0)*T.at(0)+p.at(1)*T.at(1)+p.at(2)*T.at(2))/TMath::Sqrt(T.at(0)*T.at(0)+T.at(1)*T.at(1)+T.at(2)*T.at(2));  

}

std::vector<float> QQbarAnalysisClass::ChargedPFOThetaPhi(int ipfo, std::vector<float> Tprinc, std::vector<float> Tmajor, std::vector<float> Tminor)
{

  std::vector<float> result;

  if (pfo_charge[ipfo] == 0 || pfo_ntracks[ipfo] != 1)
    return result;

  if (sqrt(pow(pfo_px[ipfo], 2) + pow(pfo_py[ipfo], 2)) < 1)
    return result;

  std::vector<float> pfo_vec_0;
  pfo_vec_0.push_back(pfo_px[ipfo]);
  pfo_vec_0.push_back(pfo_py[ipfo]);
  pfo_vec_0.push_back(pfo_pz[ipfo]);

  std::vector<float> pfo_vec;
  pfo_vec.push_back(ProjectionVector(pfo_vec_0,Tprinc));
  pfo_vec.push_back(ProjectionVector(pfo_vec_0,Tmajor));
  pfo_vec.push_back(ProjectionVector(pfo_vec_0,Tminor));
  // std::vector<float> angles = GetAnglesThrust(pfo_vec, vectorT);
  // for the moment, we use the Lab frame
  float theta = GetCostheta(pfo_vec);
  float eta = 0.5 * log ( (pfo_E[ipfo] + pfo_vec.at(2) ) / (pfo_E[ipfo] - pfo_vec.at(2) ) );
  float phi = GetPhi(pfo_vec);

  result.push_back(theta);
  result.push_back(eta);
  result.push_back(phi);
  return result;
}


std::vector<float> QQbarAnalysisClass::ChargedMCThetaPhi(int ipfo, std::vector<float> Tprinc, std::vector<float> Tmajor, std::vector<float> Tminor)
{

  std::vector<float> result;

  if (pfo_charge[ipfo] == 0 )
    return result;

  if (sqrt(pow(mc_stable_px[ipfo], 2) + pow(mc_stable_py[ipfo], 2)) < 1)
    return result;

  std::vector<float> mc_stable_vec_0;
  mc_stable_vec_0.push_back(mc_stable_px[ipfo]);
  mc_stable_vec_0.push_back(mc_stable_py[ipfo]);
  mc_stable_vec_0.push_back(mc_stable_pz[ipfo]);

  std::vector<float> mc_stable_vec;
  mc_stable_vec.push_back(ProjectionVector(mc_stable_vec_0,Tprinc));
  mc_stable_vec.push_back(ProjectionVector(mc_stable_vec_0,Tmajor));
  mc_stable_vec.push_back(ProjectionVector(mc_stable_vec_0,Tminor));
  // std::vector<float> angles = GetAnglesThrust(mc_stable_vec, vectorT);
  // for the moment, we use the Lab frame
  float theta = GetCostheta(mc_stable_vec);
  float eta = 0.5 * log ( (mc_stable_E[ipfo] + mc_stable_vec.at(2) ) / (mc_stable_E[ipfo] - mc_stable_vec.at(2) ) );
  float phi = GetPhi(mc_stable_vec);

  result.push_back(theta);
  result.push_back(eta);
  result.push_back(phi);
  return result;
}
