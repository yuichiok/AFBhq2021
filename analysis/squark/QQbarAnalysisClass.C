#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"


void QQbarAnalysisClass::AFBreconstruction(int n_entries=-1, float Kvcut=35, TString polString="eL_pR", int method=0)
{

  //Ntotal_nocuts                                                                                                                    
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);


  //initialize histograms
  TH1F * h_N[5][10];//this is used to calculate efficiencies
  TH1F * h_AFB_true[5][10];
  TH1F * h_AFB_reco[5][10];//these two to study migrations

  for(int q=0; q<5; q++) {
    for (int isel=0; isel<10; isel++) {
      h_N[q][isel]= new TH1F(TString::Format("h_N_q%i_sel%i",q,isel),TString::Format("h_N_q%i_sel%i",q,isel),20,0,1);
      h_AFB_true[q][isel]= new TH1F(TString::Format("h_AFB_true_q%i_sel%i",q,isel),TString::Format("h_AFB_true_q%i_sel%i",q,isel),40,-1,1);
      h_AFB_reco[q][isel]= new TH1F(TString::Format("h_AFB_reco_q%i_sel%i",q,isel),TString::Format("h_AFB_reco_q%i_sel%i",q,isel),40,-1,1);
    }
  } 

  //polarisation scenarios
  //pol=0 (eLpR), pol=1 (eRpL), pol=2 eLpRat80/30, pol=3 eRpLat80/30
  int pol=0;
  if(polString=="eL_pR") pol=0;
  else  if(polString=="eR_pL") pol=1;
  else {
    cout<<" WRONG PARAMETER polString !! "<<polString<<endl;
    return;
  }

  
  float pcut=3.;
  //optimal dedx cutone
  //if(dedxcut==7) {
  dedxcut_up=1.1;
  dedxcut_down=-2.45;
  //}

  //methods 0=no cheat on Kaon id, 1= cheat on the kaon ID
  TString method_string[4]={"","_cheat"};

  //**************
  //new file
  TString filename=TString::Format("s_AFB_tests_%s_250GeV%s.root",process.Data(),method_string[method].Data());
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  //nentries=30000;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


    h_Ntotal_nocuts->Fill(0.5);//this is simply to count the total number of events in the sample.
    //using the cross section of simulated sample, we can calculate the luminosity of the sample
    //cross section is stroed in common/cross_sections.h


    //Definition of signal (i.e. ee-->qqbar without radiative return)
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

    TVector3 v1(mc_quark_ps_jet_px[0],mc_quark_ps_jet_py[0],mc_quark_ps_jet_pz[0]);
    TVector3 v2(mc_quark_ps_jet_px[1],mc_quark_ps_jet_py[1],mc_quark_ps_jet_pz[1]);
    float acol=GetSinacol(v1,v2);
    if(fabs(mc_quark_pdg[0])!=quark || gamma_e>Kvcut  ||  acol>0.3) continue;

    //jet direction
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta=GetCostheta(p);
    
    //cheat angle
    float costheta_cheat=1;
    std::vector<float> p_cheat;
    p_cheat.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_cheat.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_cheat.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_cheat=GetCostheta(p_cheat);
    costheta_cheat=  (mc_quark_charge[0] < 0) ? -costheta_cheat: costheta_cheat;
    if(fabs(mc_quark_pdg[0])==5 || fabs(mc_quark_pdg[0])==3 || fabs(mc_quark_pdg[0])==1) costheta_cheat*=-1;

    //run the preselection steps, 0-6 are steps to remove radiative return and keep same fraction of udscb quarks
    for(int isel=0; isel<7; isel++) {
      bool selection=PreSelection(isel,Kvcut);
      if(selection==true) {

        //fill histograms quark by quark
        for(int q=0; q<6; q++) {
          if(fabs(mc_quark_pdg[0])==q) {
            h_N[q][isel]->Fill(fabs(costheta)); //we use the jet angle, using the mc 
            //angle is also ok but then we need to correct for the resolution effects 
            //(mc angle vsjet angle) with an unfolding correction or a covariant matrix or similar
            h_AFB_true[q][isel]->Fill(costheta_cheat); //we know the direction
            //we don't fill the reco, since we still have no info about the jet charge
          }
        }
      }
    }

    //selection 7: both jets with no secondary vtx --> this cleans most of the b's but still not the c's
    if(jet_nvtx_j1==0 && jet_nvtx_j2==0) {
      for(int q=0; q<6; q++) {
          if(fabs(mc_quark_pdg[0])==q) {
            h_N[q][7]->Fill(fabs(costheta));
            h_AFB_true[q][7]->Fill(costheta_cheat);
          }
      }
    } else continue;
    
    //selection 8: leading K candidate (cheating!)
    //we find the charged kaon with highest momentum and we use this as leading_kaon in the jet
    //note: it is different than looking for the leading charged pfo and later check if it is or not a kaon
    // momentum of the kaon > 10GeV
    // we require both jets to have one of such kaons and that both have opposite charges
    float ch0_cheat=ChargeKJetCheat(0,10,1);
    float ch1_cheat=ChargeKJetCheat(1,10,1);
    if(ch0_cheat*ch1_cheat<0) {
      for(int q=0; q<6; q++) {
        if(fabs(mc_quark_pdg[0])==q) {
          h_N[q][8]->Fill(fabs(costheta));
          h_AFB_true[q][8]->Fill(costheta_cheat);
          h_AFB_reco[q][8]->Fill(fabs(costheta)*ch0_cheat/fabs(ch0_cheat);
        }
      }
    }

    //selection 9: same than 8 but not cheating
    float ch0=ChargeKJet(0,10,1);
    float ch1=ChargeKJet(1,10,1);
    if(ch0*ch1<0) {
      for(int q=0; q<6; q++) {
        if(fabs(mc_quark_pdg[0])==q) {
          h_N[q][9]->Fill(fabs(costheta));
          h_AFB_true[q][9]->Fill(costheta_cheat);
          h_AFB_reco[q][9]->Fill(fabs(costheta)*ch0/fabs(ch0);
        }
      }
    }

  }
    

  MyFile->cd();
  h_Ntotal_nocuts->Write();
  for(int q=0; q<5; q++) {
    for (int isel=0; isel<10; isel++) {
      h_N[q][isel]->Write();
      h_AFB_true[q][isel]->Write();
      h_AFB_reco[q][isel]->Write();
    }
  }

}


float QQbarAnalysisClass::ChargeKJetCheat(int ijet, float pcut=2., float offset_cut=1){

  float charge=0;
  float momentum_kaon_max=-1;
  float n_pfo_selected=-1;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
    if(pfo_ntracks!=1) continue;
    float offset=sqrt(pfo_d0*pfo_d0+pfo_z0*pfo_z0);
    if(offset>offset_cut) continue;
    float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
    if(momentum<pcut) continue;
    if(fabs(pfo_pdgcheat[ipfo])!=321) continue;
    
    //select the kaon-pfo with highest momentum
    if(momentum>momentum_kaon_max) {
      momentum_kaon_max=momentum;
      n_pfo_selected=ipfo;
    }
  }
  if(n_pfo_selected!=-1) charge=-pfo_charge[ipfo];
  //take care with the sign... should be inverted depending of the flavour?
  return charge;
}

float QQbarAnalysisClass::ChargeKJet(int ijet, float pcut=2., float offset_cut=1){

  float charge=0;
  float momentum_kaon_max=-1;
  float n_pfo_selected=-1;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
    if(pfo_ntracks!=1) continue;
    float offset=sqrt(pfo_d0*pfo_d0+pfo_z0*pfo_z0);
    if(offset>offset_cut) continue;
    float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
    if(momentum<pcut) continue;

    //kaon selection
    bool nhits_bool=false;
    if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
    if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
    if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;
    if(  nhits_bool!=true) continue;
    float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
    if(dedx_dist <dedxcut_down || dedx_dist > dedxcut_up) continue;
    
    //select the kaon-pfo with highest momentum
    if(momentum>momentum_kaon_max) {
      momentum_kaon_max=momentum;
      n_pfo_selected=ipfo;
    }
  }
  if(n_pfo_selected!=-1) charge=-pfo_charge[ipfo];
  //take care with the sign... should be inverted depending of the flavour?
  return charge;
}




