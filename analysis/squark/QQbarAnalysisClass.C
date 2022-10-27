#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"


void QQbarAnalysisClass::AFBreconstruction(int n_entries=-1, TString process="eL_pR", int tight=0, float Kvcut=35, float acolcut=0.3, int bkg=0)
{

  //optimal dedx cut
  dedxcut_up=1.0;
  dedxcut_down=-1.5;

  //pcut for kaon seleciton
  float pcut=10;
  
  //ofssets for kaon seleciton
  float offsetcut=1.0;

  //Ntotal_nocuts                                                                                                                    
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);
  //initialize histograms
  TH1F * h_N[6][10];//this is used to calculate efficiencies
  TH1F * h_AFB_true[6][10];
  TH1F * h_AFB_reco[6][10];//these two to study migrations

  for(int q=0; q<6; q++) {
    for (int isel=0; isel<10; isel++) {
      h_N[q][isel]= new TH1F(TString::Format("h_N_q%i_sel%i",q,isel),TString::Format("h_N_q%i_sel%i",q,isel),20,0,1);
      h_AFB_true[q][isel]= new TH1F(TString::Format("h_AFB_true_q%i_sel%i",q,isel),TString::Format("h_AFB_true_q%i_sel%i",q,isel),40,-1,1);
      h_AFB_reco[q][isel]= new TH1F(TString::Format("h_AFB_reco_q%i_sel%i",q,isel),TString::Format("h_AFB_reco_q%i_sel%i",q,isel),40,-1,1);
    }
  } 

  // TH1F * h_ntracks[6];
  // TH1F * h_npfos[6];
  // TH1F * h_noffsets[6];
  // TH1F * h_kaon_candidates[6];
  // TH1F * h_mom_charged[6];
  // TH1F * h_jetmass[6];

  // for(int q=0; q<6; q++) {
  //   h_ntracks[q] = new TH1F(TString::Format("h_ntracks_q%i",q),TString::Format("h_ntracks_q%i",q),40,-0.5,39.5);
  //   h_npfos[q] = new TH1F(TString::Format("h_npfos_q%i",q),TString::Format("h_npfos_q%i",q),200,-0.5,199.5);
  //   h_noffsets[q] = new TH1F(TString::Format("h_noffsets_q%i",q),TString::Format("h_noffsets_q%i",q),40,-0.5,39.5);
  //   h_kaon_candidates[q] = new TH1F(TString::Format("h_kaon_candidates_q%i",q),TString::Format("h_kaon_candidates_q%i",q),40,-0.5,39.5);
  //   h_mom_charged[q] = new TH1F(TString::Format("h_mom_charged_q%i",q),TString::Format("h_mom_charged_q%i",q),200,-0.5,199.5);
  //   h_jetmass[q] = new TH1F(TString::Format("h_jetmass_q%i",q),TString::Format("h_jetmass_q%i",q),500,-0.5,499.5);
  // } 




  //**************
  //new file
  TString filename;
  if(tight==1) filename=TString::Format("s_AFB_tight_%s_250GeV.root",process.Data());
  if(tight==2) filename=TString::Format("s_AFB_doubletight_%s_250GeV.root",process.Data());
  if(tight==0) filename=TString::Format("s_AFB_loose_%s_250GeV.root",process.Data());

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

    if ( jentry > 1000 && jentry % 10000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


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
    if( bkg==0 && (gamma_e>Kvcut  ||  acol>acolcut) )continue;
    if( bkg==1 && gamma_e<Kvcut && acol<acolcut )continue;

    //jet direction
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta=GetCostheta(p);
    
    //cheat quark-charge
    float costheta_cheat=1;
    std::vector<float> p_cheat;
    p_cheat.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_cheat.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_cheat.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_cheat=GetCostheta(p_cheat);
    costheta_cheat= fabs(costheta) * costheta_cheat/fabs(costheta_cheat); //we are interested in the sign. 

    //run the preselection steps, 0-6 are steps to remove radiative return and keep same fraction of udscb quarks
    for(int isel=0; isel<7; isel++) {
      bool selection=PreSelection(isel,Kvcut);
      if(selection==true) {

        //fill histograms quark by quark
        for(int q=1; q<6; q++) {
          if(fabs(mc_quark_pdg[0])==q) {
            h_N[q][isel]->Fill(fabs(costheta)); //we use the jet angle, using the mc 
            //angle is also ok but then we need to correct for the resolution effects 
            //(mc angle vs jet angle) with an unfolding correction or a covariant matrix or similar
            h_AFB_true[q][isel]->Fill(costheta_cheat); //we know the direction
            //we don't fill the reco, since we still have no info about the jet charge
          }
        }
      }
    }

    bool selection=PreSelection(6,Kvcut);
    if(selection==false) continue;
    //selection 7: both jets with no secondary vtx --> this cleans most of the b's but still not the c's
    if(jet_nvtx_j1==0 && jet_nvtx_j2==0) {
      for(int q=1; q<6; q++) {
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
    float ch0_cheat=ChargeKJetCheat(0,pcut,offsetcut);
    float ch1_cheat=ChargeKJetCheat(1,pcut,offsetcut);
    float ch0_cheat_ti=ChargeKJetCheat(0,pcut*2.,offsetcut);
    float ch1_cheat_ti=ChargeKJetCheat(1,pcut*2.,offsetcut);
    if(ch0_cheat_ti!=0) ch0_cheat=ch0_cheat_ti;
    if(ch1_cheat_ti!=0) ch1_cheat=ch1_cheat_ti;
    if( (tight==2 && ch0_cheat_ti*ch1_cheat_ti<0 )
	|| (tight==1 && (ch0_cheat*ch1_cheat<0 && (ch0_cheat_ti!=0 || ch1_cheat_ti!=0) ))  
	|| (tight==0 && ch0_cheat*ch1_cheat<0 ) ){
      for(int q=1; q<6; q++) {
        if(fabs(mc_quark_pdg[0])==q) {
          h_N[q][8]->Fill(fabs(costheta));
          h_AFB_true[q][8]->Fill(costheta_cheat);
          if(ch0_cheat>0) {
            h_AFB_reco[q][8]->Fill(-costheta);
          } else {
            h_AFB_reco[q][8]->Fill(costheta);
          }
        }
      }
    }

    //selection 9: same than 8 but not cheating
    float ch0=ChargeKJet(0,pcut,offsetcut);
    float ch1=ChargeKJet(1,pcut,offsetcut);
    float ch0_ti=ChargeKJetTight(0,pcut,offsetcut);
    float ch1_ti=ChargeKJetTight(1,pcut,offsetcut);
    if(ch0_ti!=0) ch0=ch0_ti;
    if(ch1_ti!=0) ch1=ch1_ti;
    if( (tight==2 && ch0_ti*ch1_ti<0 )
	|| (tight==1 && (ch0*ch1<0 && (ch0_ti!=0 || ch1_ti!=0) ))  
	|| (tight==0 && ch0*ch1<0 ) ){
      for(int q=1; q<6; q++) {
        if(fabs(mc_quark_pdg[0])==q) {
          h_N[q][9]->Fill(fabs(costheta));
          h_AFB_true[q][9]->Fill(costheta_cheat);
          if(ch0>0) {
            h_AFB_reco[q][9]->Fill(-costheta);
          } else {
            h_AFB_reco[q][9]->Fill(costheta);
          }
        }
      }
    

      // //Try to find variables able to filter contamination from ud and c
      // for(int q=1; q<6; q++) {
      //   if(fabs(mc_quark_pdg[0])==q) {
      //     float ntracks=0;//
      //     float npfos=0;//
      //     float noffsets=0;//
      //     float nkaons=0;
      //     float jetmass=0;//
      //     float mom_charged_x=0,mom_charged_y=0,mom_charged_z=0;//
      //     for(int ijet=0; ijet<2; ijet++) {
      //       //jet mass stuff
      //       jetmass+= sqrt(pow(jet_E[ijet],2)-pow(jet_px[ijet],2)-pow(jet_py[ijet],2)-pow(jet_pz[ijet],2));

      //       for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      //         if(pfo_match[ipfo]!=ijet) continue;
      //         npfos++;
      //         //tracks
      //         if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
      //         if(pfo_ntracks[ipfo]!=1) continue;
      //         //kaon selection
      //         float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
      //         if(momentum<pcut*2) continue;
      //         ntracks++;
      //         mom_charged_x+=pfo_px[ipfo];
      //         mom_charged_y+=pfo_py[ipfo];
      //         mom_charged_z+=pfo_pz[ipfo];
      //         float offset=sqrt(pfo_d0[ipfo]*pfo_d0[ipfo]+pfo_z0[ipfo]*pfo_z0[ipfo]);
      //         if(offset>offsetcut) continue;
      //         noffsets++;
      //         bool nhits_bool=false;
      //         float costheta_track;
      //         std::vector<float> p_track;
      //         p_track.push_back(pfo_px[ipfo]);
      //         p_track.push_back(pfo_py[ipfo]);
      //         p_track.push_back(pfo_pz[ipfo]);
      //         costheta_track=GetCostheta(p_track);
      //         if(fabs(costheta_track)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      //         if(fabs(costheta_track)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta_track)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      //         if(fabs(costheta_track)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;
      //         if(  nhits_bool!=true) continue;
      //         float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
      //         if(dedx_dist <-0.75|| dedx_dist > 0.) continue;
      //         nkaons++;
      //       }
      //       h_kaon_candidates[q]->Fill(nkaons);
      //       nkaons=0;
      //       h_ntracks[q] ->Fill(ntracks);
      //       ntracks=0;
      //       h_npfos[q]->Fill(npfos);
      //       npfos=0;
      //       h_noffsets[q]->Fill(noffsets);
      //       noffsets=0;
      //       h_mom_charged[q]->Fill(sqrt(mom_charged_x*mom_charged_x+mom_charged_y*mom_charged_y+mom_charged_z*mom_charged_z));
      //       mom_charged_x=0; mom_charged_y=0; mom_charged_z=0;
      //     }
          
      //     h_jetmass[q]->Fill(jetmass);
          
      //   }
      // }
    }


  }
    

  MyFile->cd();
  h_Ntotal_nocuts->Write();
  for (int isel=0; isel<10; isel++) {
    for(int q=1; q<6; q++) {
      h_N[q][isel]->Write();
      h_AFB_true[q][isel]->Write();
      h_AFB_reco[q][isel]->Write();
    }
  }

  // for(int q=1; q<6; q++) {
  //   h_ntracks[q]->Write();
  //   h_npfos[q]->Write();
  //   h_noffsets[q]->Write();
  //   h_kaon_candidates[q]->Write();
  //   h_mom_charged[q]->Write();
  //   h_jetmass[q]->Write();
  // }

}


void QQbarAnalysisClass::KaonEfficiency(int n_entries=-1, TString process="eL_pR", float Kvcut=35, float acolcut=0.3, int bkg=0)
{

  //optimal dedx cut
  dedxcut_up=1.0;
  dedxcut_down=-1.5;
  
  //ofssets for kaon seleciton
  float offsetcut=1.0;

  //initialize histograms
  TH1F * h_N_K_MC[6];//this is used to calculate efficiencies
  TH1F * h_N_track_K_correct[6][2];
  TH1F * h_N_track_K_wrong[6][2];
  TH1F * h_N_track_K_true[6];

  for(int q=0; q<6; q++) {
    h_N_K_MC[q]= new TH1F(TString::Format("h_N_K_MC_q%i",q),TString::Format("h_N_K_MC_q%i",q),50,0,125,40,-1,1);
    h_N_track_K_true[q]= new TH1F(TString::Format("h_N_track_K_true_q%i",q),TString::Format("h_N_track_K_true_q%i",q),50,0,125,40,-1,1);
    for(int i=0; i<2; i++) {
      h_N_track_K_correct[q][i]= new TH1F(TString::Format("h_N_track_K_correct_q%i_sel%i",q,i),TString::Format("h_N_track_K_correct_q%i_sel%i",q,i),50,0,125,40,-1,1);
      h_N_track_K_wrong[q][i]= new TH1F(TString::Format("h_N_track_K_wrong_q%_sel%i",q,i),TString::Format("h_N_track_K_wrong_q%i_sel%i",q,i),50,0,125,40,-1,1);
    } 
    
  }
 
  //**************
  //new file
  TString filename=TString::Format("s_K_eff_tight_%s_250GeV.root",process.Data());

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

    if ( jentry > 1000 && jentry % 10000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;


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
    if( bkg==0 && (gamma_e>Kvcut  ||  acol>acolcut) )continue;
    if( bkg==1 && gamma_e<Kvcut && acol<acolcut )continue;

    //jet direction
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta=GetCostheta(p);
    
    bool selection=PreSelection(6,Kvcut);
    if(selection==false) continue;

    for(int q=0; q<6; q++) {
      if(fabs(mc_quark_pdg[0])==q || q==0) {

        //MC stable
        std::vector<int> i_mc=NMCK();
        for(int i=0; i<i_mc.size(); i++) {
          float momentum = sqrt (pow(mc_stable_px[i],2) +pow(mc_stable_py[i],2) +pow(mc_stable_pz[i],2) );
          float costheta_temp;
          std::vector<float> p_track;
          p_track.push_back(mc_stable_px[i_mc.at(i)]);
          p_track.push_back(mc_stable_py[i_mc.at(i)]);
          p_track.push_back(mc_stable_pz[i_mc.at(i)]);
          costheta_temp=GetCostheta(p_track);
          h_N_K_MC[q]->Fill(momentum,costheta_temp);
        }
        i_mc.clear();
        
        //reconstructed tracks, but true PID
        for(int ijet=0; ijet<2; ijet++) {
          std::vector<int> i_pfo_truth=NPFOKJetCheat(ijet,offsetcut);
          for(int i=0; i<i_pfo_truth(); i++) {
            float momentum = sqrt (pow(pfo_px[i_pfo_truth.at(i)],2) +pow(pfo_py[i_pfo_truth.at(i)],2) +pow(pfo_pz[i_pfo_truth.at(i)],2) );
            float costheta_temp;
            std::vector<float> p_track;
            p_track.push_back(pfo_px[i_pfo_truth.at(i)]);
            p_track.push_back(pfo_py[i_pfo_truth.at(i)]);
            p_track.push_back(pfo_pz[i_pfo_truth.at(i)]);
            costheta_temp=GetCostheta(p_track);
            h_N_track_K_true[q]->Fill(momentum,costheta_temp);
          }
          i_pfo_truth.clear();
        }

        //reconstructed tracks, real PID, wrong and correct tracks
        for(int ijet=0; ijet<2; ijet++) {
	        //loose
          std::vector<int> i_pfo_loose=NPFOKJet(ijet,offsetcut,0);
          for(int i=0; i<i_pfo_loose(); i++) {
            int ipfo=fabs(i_pfo_loose.at(i));
            if(ipfo==100000) ipfo=0;
	          float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
	          float costheta_temp;
	          std::vector<float> p_track;
	          p_track.push_back(pfo_px[ipfo]);
	          p_track.push_back(pfo_py[ipfo]);
	          p_track.push_back(pfo_pz[ipfo]);
	          costheta_temp=GetCostheta(p_track);
	          if(i_pfo_loose.at(i)>0 || i_pfo_loose.at(i)==100000) h_N_track_K_correct[q][0]->Fill(momentum,costheta_temp);
	          if(i_pfo_loose.at(i)<0 || i_pfo_loose.at(i)==-100000) h_N_track_K_wrong[q][0]->Fill(momentum,costheta_temp);
	        }
          i_pfo_loose.clear();

          std::vector<int> i_pfo_tight=NPFOKJet(ijet,offsetcut,1);
          for(int i=0; i<i_pfo_tight(); i++) {
            int ipfo=fabs(i_pfo_tight.at(i));
            if(ipfo==100000) ipfo=0;
	          float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
	          float costheta_temp;
	          std::vector<float> p_track;
	          p_track.push_back(pfo_px[ipfo]);
	          p_track.push_back(pfo_py[ipfo]);
	          p_track.push_back(pfo_pz[ipfo]);
	          costheta_temp=GetCostheta(p_track);
	          if(i_pfo_tight.at(i)>0 || i_pfo_tight.at(i)==100000) h_N_track_K_correct[q][1]->Fill(momentum,costheta_temp);
	          if(i_pfo_tight.at(i)<0 || i_pfo_tight.at(i)==-100000) h_N_track_K_wrong[q][1]->Fill(momentum,costheta_temp);
	        }
          i_pfo_tight.clear();
        }

      }//q=quark
    }//loop q
  }


    

  MyFile->cd();
  h_Ntotal_nocuts->Write();
  for(int q=0; q<6; q++) {
    for (int isel=0; isel<2; isel++) {
      h_N_track_K_correct[q][isel]->Write();
 	    h_N_track_K_correct[q][isel]->Write();
    }
    h_N_track_K_true[q]->Write();
    h_N_K_MC[q]->Write();
  }

}


  float QQbarAnalysisClass::ChargeKJetCheat(int ijet, float pcut=10., float offset_cut=1){

    float charge=0;
    float momentum_kaon_max=-1;
    int n_pfo_selected=-1;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if(pfo_match[ipfo]!=ijet) continue;
      if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
      if(pfo_ntracks[ipfo]!=1) continue;
      float offset=sqrt(pfo_d0[ipfo]*pfo_d0[ipfo]+pfo_z0[ipfo]*pfo_z0[ipfo]);
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
    if(n_pfo_selected!=-1) charge=pfo_charge[n_pfo_selected];
    //take care with the sign... should be inverted depending of the flavour?
    return charge;
  }

  float QQbarAnalysisClass::ChargeKJet(int ijet, float pcut=10., float offset_cut=1){

    float charge=0;
    float momentum_kaon_max=-1;
    float kaonness_diff=10000;

    int n_pfo_selected=-1;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if(pfo_match[ipfo]!=ijet) continue;
      if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
      if(pfo_ntracks[ipfo]!=1) continue;
      float offset=sqrt(pfo_d0[ipfo]*pfo_d0[ipfo]+pfo_z0[ipfo]*pfo_z0[ipfo]);
      if(offset>offset_cut) continue;
      float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
      if(momentum<pcut) continue;

      float costheta;
      std::vector<float> p_track;
      p_track.push_back(pfo_px[ipfo]);
      p_track.push_back(pfo_py[ipfo]);
      p_track.push_back(pfo_pz[ipfo]);
      costheta=GetCostheta(p_track);

      //kaon selection
      bool nhits_bool=false;
      if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;
      if(  nhits_bool!=true) continue;
      float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
      if(dedx_dist <dedxcut_down || dedx_dist > dedxcut_up) continue;
    
      //select the kaon-pfo with highest momentum
      if(momentum>momentum_kaon_max ) {
	//kaonness_diff=fabs(dedx_dist);
	momentum_kaon_max=momentum;
	n_pfo_selected=ipfo;
      }
    }
    if(n_pfo_selected!=-1) charge=pfo_charge[n_pfo_selected];
    return charge;
  }

  float QQbarAnalysisClass::ChargeKJetTight(int ijet, float pcut=10., float offset_cut=1){

    float charge=0;
    float momentum_kaon_max=-1;
    int n_pfo_selected=-1;
    float kaonness_diff=10000;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if(pfo_match[ipfo]!=ijet) continue;
      if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
      if(pfo_ntracks[ipfo]!=1) continue;
      float offset=sqrt(pfo_d0[ipfo]*pfo_d0[ipfo]+pfo_z0[ipfo]*pfo_z0[ipfo]);
      if(offset>offset_cut) continue;
      float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
      if(momentum<pcut*2) continue;

      float costheta;
      std::vector<float> p_track;
      p_track.push_back(pfo_px[ipfo]);
      p_track.push_back(pfo_py[ipfo]);
      p_track.push_back(pfo_pz[ipfo]);
      costheta=GetCostheta(p_track);

      //kaon selection
      bool nhits_bool=false;
      if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;
      if(  nhits_bool!=true) continue;
      float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
      if(dedx_dist <dedxcut_down/2. || dedx_dist > 0) continue;
    
      //select the kaon-pfo with highest momentum
      if(momentum>momentum_kaon_max ) {
	//kaonness_diff=fabs(dedx_dist);
	momentum_kaon_max=momentum;
	n_pfo_selected=ipfo;
      }
    }
    if(n_pfo_selected!=-1) charge=pfo_charge[n_pfo_selected];
    return charge;
  }


  std::vector<int> QQbarAnalysisClass::NMCK(){

    std::vector<int> i_mc_stable;

    for(int imc_stable=0; imc_stable<mc_stable_n; imc_stable++) {
      if(fabs(n_mc_stable_pdg[imc_stable])!=321) continue;
      i_mc_stable.push_back(imc_stable);
    }

    return i_mc_stable;
  }

  std::vector<int> QQbarAnalysisClass::NPFOKJetCheat(int ijet, float offset_cut=1){

    std::vector<int> i_pfo;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if(pfo_match[ipfo]!=ijet) continue;
      if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
      if(pfo_ntracks[ipfo]!=1) continue;
      float offset=sqrt(pfo_d0[ipfo]*pfo_d0[ipfo]+pfo_z0[ipfo]*pfo_z0[ipfo]);
      if(offset>offset_cut) continue;
      if(fabs(pfo_pdgcheat[ipfo])!=321) continue;
      i_pfo.push_back(ipfo);
    }

    return i_pfo;
  }

  std::vector<int> QQbarAnalysisClass::NPFOKJet(int ijet, float offset_cut=1, int tight=0){

    std::vector<int> i_pfo;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if(pfo_match[ipfo]!=ijet) continue;
      if(pfo_vtx[ipfo]!=0) continue;//we only want tracks from the primary vtx, not displaced tracks
      if(pfo_ntracks[ipfo]!=1) continue;
      float offset=sqrt(pfo_d0[ipfo]*pfo_d0[ipfo]+pfo_z0[ipfo]*pfo_z0[ipfo]);
      if(offset>offset_cut) continue;

      float costheta;
      std::vector<float> p_track;
      p_track.push_back(pfo_px[ipfo]);
      p_track.push_back(pfo_py[ipfo]);
      p_track.push_back(pfo_pz[ipfo]);
      costheta=GetCostheta(p_track);

      //kaon selection
      bool nhits_bool=false;
      if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;
      if(  nhits_bool!=true) continue;
      float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
      if(tight==0 && (dedx_dist <dedxcut_down || dedx_dist > dedxcut_up) )continue;
      if(tight==1 && (dedx_dist <dedxcut_down/2. || dedx_dist > 0) )continue;
    
      if(ipfo>0) {
        if(fabs(pfo_pdgcheat[ipfo])==321)i_pfo.push_back(ipfo);
        else i_pfo.push_back(-ipfo);
      } else {
        if(fabs(pfo_pdgcheat[ipfo])==321)i_pfo.push_back(100000);
        else i_pfo.push_back(-100000);
      }
    }

    return i_pfo;
  }




