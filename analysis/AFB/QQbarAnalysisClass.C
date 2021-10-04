#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"


void QQbarAnalysisClass::AFBc1(int n_entries=-1, int method=0, float Kvcut=35, float pcut=2)
{
  AFB1(n_entries, method,  Kvcut, pcut,4);

}

void QQbarAnalysisClass::AFBb1(int n_entries=-1, int method=0, float Kvcut=35, float pcut=2)
{
  AFB1(n_entries, method,  Kvcut, pcut,5);
}

void QQbarAnalysisClass::AFB1(int n_entries=-1, int method=0, float Kvcut=35, float pcut=2, int quark=4)
{

  if(dedxcut==1) {
    dedxcut_up=0.75;
    dedxcut_down=-2.25;
  }

  if(dedxcut==2) {
    dedxcut_up=0.75;
    dedxcut_down=-2.45;
  }

  if(dedxcut==3) {
    dedxcut_up=0.8;
    dedxcut_down=-2.25;
  }

  if(dedxcut==4) {
    dedxcut_up=0.8;
    dedxcut_down=-2.45;
  }

  if(dedxcut==5) {
    dedxcut_up=1.0;
    dedxcut_down=-2.45;
  }

  if(dedxcut==6) {
    dedxcut_up=0.9;
    dedxcut_down=-2.45;
  }

  if(dedxcut==7) {
    dedxcut_up=1.1;
    dedxcut_down=-2.45;
  }


  TString filename=TString::Format("AFBc%i_method%i_%s_250GeV.root",dedxcut,method,process.Data());
  if(quark==5) filename=TString::Format("AFBb%i_method%i_%s_250GeV.root",dedxcut,method,process.Data());
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  //Ntotal_nocuts
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);
  TH1F * h_Nparton = new TH1F("h_Nparton","h_Nparton",20,0,1);
  TH1F * h_AFB = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_N0[4];//events after charge measurement (two flavour tag already done)
  TH1F * h_N1[4];//events 1 tag
  TH1F * h_N2[4];//events 2 tags

  TH1F * h_Charge[4];
  TH1F * h_Nacc[4];//events with compatible charge
  TH1F * h_Nrej[4];//events with non compatible charge

  for(int i=0;i<4;i++) {
    h_N0[i] = new TH1F(TString::Format("h_N0_%i",i),TString::Format("h_N0_%i",i),20,0,1);
    h_N1[i] = new TH1F(TString::Format("h_N1_%i",i),TString::Format("h_N1_%i",i),20,0,1);
    h_N2[i] = new TH1F(TString::Format("h_N2_%i",i),TString::Format("h_N2_%i",i),20,0,1);
    h_Charge[i] = new TH1F(TString::Format("h_Charge_%i",i),TString::Format("h_Charge_%i",i),400,-10,10);
    h_Nacc[i] = new TH1F(TString::Format("h_Nacc_%i",i),TString::Format("h_Nacc_%i",i),40,-1,1);
    h_Nrej[i] = new TH1F(TString::Format("h_Nrej_%i",i),TString::Format("h_Nrej_%i",i),40,-1,1);
    // 0=K, 1=Kcheat, 2=Kcheat&TOF, 3=Vtx
  }

  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();
  //nentries=30000;

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

    float costheta_thrust;
    std::vector<float> p_thrust;
    p_thrust.push_back(principle_thrust_axis[0]);
    p_thrust.push_back(principle_thrust_axis[1]);
    p_thrust.push_back(principle_thrust_axis[2]);
    costheta_thrust=fabs(GetCostheta(p_thrust));
    h_Ntotal_nocuts->Fill(costheta_thrust);

    if(fabs(mc_quark_pdg[0])!=quark || gamma_e>Kvcut) continue;
    
    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    float costheta_ccbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_ccbar=GetCostheta(p_bbar);
    costheta_ccbar=  (mc_quark_charge[0] < 0) ? -costheta_ccbar: costheta_ccbar;
    if(quark==5) costheta_ccbar*=-1;
    if(costheta_ccbar<0) costheta_thrust*=-1.;

    h_Nparton->Fill(fabs(costheta_thrust));
    h_AFB->Fill(costheta_thrust);

    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta_jet=GetCostheta(p);

    //reco level distributions
    float Kv=Kreco();
    bool selection=PreSelection(6,Kvcut);
    if(selection==false) continue;
    //jet flavour
    bool jettag[2]={false,false};
    if(quark==4) {
      if(jet_ctag[0]>ctag1) jettag[0]=true;
      if(jet_ctag[1]>ctag2) jettag[1]=true;
    } else if(quark==5) {
      if(jet_btag[0]>btag1) jettag[0]=true;
      if(jet_btag[1]>btag2) jettag[1]=true;
    } else {
      cout<<"ERROR, wrong argument for the quark quark-to-study"<<endl;
      break;
    }

    if(jettag[0]==false || jettag[1]==false) continue;

    float charge[2][4]={0};
    for(int ijet=0; ijet<2; ijet++) {
      charge[ijet][0]=ChargeKJet(method,ijet,pcut,false,false);
      charge[ijet][1]=ChargeKJet(method,ijet,pcut,true,false);
      charge[ijet][2]=ChargeKJet(method,ijet,pcut,true,true);
      charge[ijet][3]=ChargeVtxJet(method,ijet,pcut);
      if(quark==5) {
	charge[ijet][0]*=-1;
	charge[ijet][1]*=-1;
	charge[ijet][2]*=-1;
      }
    }

    //Efficiencies && charge purity
    for(int i=0; i<4; i++) {
      //Efficiencies
      h_N0[i]->Fill(fabs(costheta_thrust));
      for(int ijet=0; ijet<2; ijet++) {
	if(charge[ijet][i]!=0) {
	  h_Charge[i]->Fill(charge[ijet][i]);
	  h_N1[i]->Fill(fabs(costheta_thrust));
	}
      }
      if(charge[0][i]!=0 && charge[1][i]!=0) h_N2[i]->Fill(fabs(costheta_thrust));

      float costheta_temp=  (charge[0][i] < 0) ? -costheta_jet: costheta_jet;

      //purities
      if(charge[0][i]*charge[1][i]<0) h_Nacc[i]->Fill(fabs(costheta_thrust)*costheta_temp/fabs(costheta_temp));
      if(charge[0][i]*charge[1][i]>0) {
	h_Nrej[i]->Fill(costheta_thrust);
	h_Nrej[i]->Fill(-costheta_thrust);
      }
    }

  }//entries
  
  cout<<filename<<endl;
  
  h_Ntotal_nocuts->Write();
  h_Nparton->Write();
  h_AFB->Write();

  for(int i=0; i<4; i++) {
    h_N0[i]->Write();
    h_N1[i]->Write();
    h_N2[i]->Write();
    h_Charge[i]->Write();
    h_Nacc[i]->Write();
    h_Nrej[i]->Write();
  }

}


float QQbarAnalysisClass::ChargeVtxJet(int method, int ijet, float pcut=2.){//, int eff=0.88) {
  
  if(method==0) return ChargeVtxJetMethod0(ijet,pcut);
  if(method==1) return ChargeVtxJetMethod1(ijet,pcut);
  if(method==2) return ChargeVtxJetMethod2(ijet,pcut);

  return 0;
}


float QQbarAnalysisClass::ChargeVtxJetMethod0(int ijet, float pcut=2.){//, int eff=0.88) {

  float charge=0;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]<1) continue;
    if(pfo_ntracks[ipfo]!=1) continue;
    float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
    charge+=pfo_charge[ipfo];
  }
  return charge;
}

float QQbarAnalysisClass::ChargeVtxJetMethod1(int ijet, float pcut=2.){//, int eff=0.88) {

  float charge=0;
  float momtotal=0;
  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]<1) continue;
    if(pfo_ntracks[ipfo]!=1) continue;
    float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
    momtotal+=momentum;
    charge+=pfo_charge[ipfo]*momentum;
  }
  if(momtotal>0) charge/=momtotal;
  return charge;
}


float QQbarAnalysisClass::ChargeVtxJetMethod2(int ijet, float pcut=2.){//, int eff=0.88) {

  float charge=0;
  int ipfo_max=-1;
  int mom_max=-1;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]<1) continue;
    if(pfo_ntracks[ipfo]!=1) continue;
    float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
    if(momentum>mom_max) {
      ipfo_max=ipfo;
      mom_max=momentum;
    }
  }
  if(ipfo_max>-0.5)  charge=pfo_charge[ipfo_max];

  return charge;
}

float QQbarAnalysisClass::ChargeKJet(int method, int ijet, float pcut=2., bool cheat=false, bool tof=false){//, int eff=0.88) {
  
  if(method==0) return ChargeKJetMethod0(ijet,pcut,cheat,tof);
  if(method==1) return ChargeKJetMethod1(ijet,pcut,cheat,tof);
  if(method==2) return ChargeKJetMethod2(ijet,pcut,cheat,tof);

  return 0;
}

float QQbarAnalysisClass::ChargeKJetMethod0(int ijet, float pcut=2., bool cheat=false, bool tof=false){

  float charge=0;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]<1) continue;
      float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
      float costheta;
      std::vector<float> p_track;
      p_track.push_back(pfo_px[ipfo]);
      p_track.push_back(pfo_py[ipfo]);
      p_track.push_back(pfo_pz[ipfo]);
      costheta=GetCostheta(p_track);
      if(pfo_ntracks[ipfo]!=1) continue;
      if(cheat==true && fabs(pfo_pdgcheat[ipfo])==321 && momentum>pcut) {
	charge-=pfo_charge[ipfo];
	continue;
      }
      if(tof==false && momentum<pcut) continue;
      if(tof==true && momentum<pcut && fabs(pfo_pdgcheat[ipfo])==321) {
	charge-=pfo_charge[ipfo];
	continue;
      }
      bool nhits_bool=false;
      if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

      if(  nhits_bool==true) {
	float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
	if(dedx_dist >dedxcut_down && dedx_dist < dedxcut_up) charge-=pfo_charge[ipfo];
      }
  }

  return charge;
}


float QQbarAnalysisClass::ChargeKJetMethod1(int ijet, float pcut=2., bool cheat=false, bool tof=false){

  float charge=0;
  float momtotal=0;
  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]<1) continue;
      float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
      momtotal+=momentum;
      float costheta;
      std::vector<float> p_track;
      p_track.push_back(pfo_px[ipfo]);
      p_track.push_back(pfo_py[ipfo]);
      p_track.push_back(pfo_pz[ipfo]);
      costheta=GetCostheta(p_track);
      if(pfo_ntracks[ipfo]!=1) continue;
      if(cheat==true && fabs(pfo_pdgcheat[ipfo])==321 && momentum>pcut) {
	charge-=pfo_charge[ipfo]*momentum;
	continue;
      }
      if(tof==false && momentum<pcut) continue;
      if(tof==true && momentum<pcut && fabs(pfo_pdgcheat[ipfo])==321) {
	charge-=pfo_charge[ipfo]*momentum;
	continue;
      }
      bool nhits_bool=false;
      if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

      if(  nhits_bool==true) {
	float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
	if(dedx_dist >dedxcut_down && dedx_dist < dedxcut_up) charge-=pfo_charge[ipfo]*momentum;
      }
  }
  if(momtotal>0) charge/=momtotal;
  return charge;
}


float QQbarAnalysisClass::ChargeKJetMethod2(int ijet, float pcut=2., bool cheat=false, bool tof=false){

  float charge=0;
  int ipfo_max_cheat=-1;
  float mom_max_cheat=-1;
  int ipfo_max=-1;
  float mom_max=-1;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {
    if(pfo_match[ipfo]!=ijet) continue;
    if(pfo_vtx[ipfo]<1) continue;
      float momentum = sqrt (pow(pfo_px[ipfo],2) +pow(pfo_py[ipfo],2) +pow(pfo_pz[ipfo],2) );
      float costheta;
      std::vector<float> p_track;
      p_track.push_back(pfo_px[ipfo]);
      p_track.push_back(pfo_py[ipfo]);
      p_track.push_back(pfo_pz[ipfo]);
      costheta=GetCostheta(p_track);
      if(pfo_ntracks[ipfo]!=1) continue;
      if(cheat==true && fabs(pfo_pdgcheat[ipfo])==321 && momentum>pcut) {
	if(momentum>mom_max_cheat) {
	  ipfo_max_cheat=ipfo;
	  mom_max_cheat=momentum;
	}
      }
  
      bool nhits_bool=false;
      if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
      if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
      if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

      if(  nhits_bool==true) {
	float dedx_dist=pfo_piddedx_k_dedxdist[ipfo];
	if(dedx_dist >dedxcut_down && dedx_dist < dedxcut_up) {
	  if(momentum>mom_max) {
	    ipfo_max=ipfo;
	    mom_max=momentum;
	  }
	}
      }
  }

  if(cheat==true && ipfo_max_cheat>-0.5 && mom_max_cheat>pcut) charge=-pfo_charge[ipfo_max_cheat];
  if(tof==true && ipfo_max_cheat>-0.5 && mom_max_cheat<pcut) charge=-pfo_charge[ipfo_max_cheat];
  if(cheat==false && ipfo_max>-0.5) charge=-pfo_charge[ipfo_max];

  return charge;
}
