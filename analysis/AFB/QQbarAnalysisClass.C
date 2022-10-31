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
  
  //optimal one
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
  TH1F * h_Nq = new TH1F("h_Nq","h_Nq",20,0,1);//quarks before preselection
  TH1F * h_N0tag= new TH1F("h_N0","h_N0",20,0,1);;//N after preselection
  TH1F * h_N1tag= new TH1F("h_N1","h_N1",20,0,1);;//events 1 tag
  TH1F * h_N2tag= new TH1F("h_N2","h_N2",20,0,1);;//events 2 tags
  
  TH1F * h_N0[4];//N after two flavour tag
  TH1F * h_N1[4];//events 1 charge
  TH1F * h_N2[4];//events 2 charge

  TH1F * h_Charge[4];
  TH1F * h_Nacc[4];//events with compatible charge
  TH1F * h_Nrej[4];//events with non compatible charge

  for(int i=0;i<4;i++) {
    h_N0[i] = new TH1F(TString::Format("h_N0c_%i",i),TString::Format("h_N0c_%i",i),20,0,1);
    h_N1[i] = new TH1F(TString::Format("h_N1c_%i",i),TString::Format("h_N1c_%i",i),20,0,1);
    h_N2[i] = new TH1F(TString::Format("h_N2c_%i",i),TString::Format("h_N2c_%i",i),20,0,1);
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

    TVector3 v1(mc_quark_ps_jet_px[0],mc_quark_ps_jet_py[0],mc_quark_ps_jet_pz[0]);
    TVector3 v2(mc_quark_ps_jet_px[1],mc_quark_ps_jet_py[1],mc_quark_ps_jet_pz[1]);
    float acol=GetSinacol(v1,v2);

    if(fabs(mc_quark_pdg[0])!=quark || gamma_e>Kvcut || acol>0.3) continue;
    h_Nq->Fill(fabs(costheta_thrust));

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
    h_N0tag->Fill(fabs(costheta_thrust));
    
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

    if(jettag[0]==true)  h_N1tag->Fill(fabs(costheta_thrust));
    if(jettag[1]==true)  h_N1tag->Fill(fabs(costheta_thrust));
    
    if(jettag[0]==false || jettag[1]==false) continue;
    h_N2tag->Fill(fabs(costheta_thrust));
    
    float charge[2][4]={0};
    for(int ijet=0; ijet<2; ijet++) {
      charge[ijet][0]=ChargeKJet(method,ijet,pcut,false,false);
      charge[ijet][1]=ChargeKJet(method,ijet,pcut,true,false);
      charge[ijet][2]=ChargeKJet(method,ijet,pcut,true,true);
      charge[ijet][3]=ChargeVtxJet(method,ijet,pcut);
      /*      if(quark==5) {
	      charge[ijet][0]*=-1;
	      charge[ijet][1]*=-1;
	      charge[ijet][2]*=-1;
	      }*/
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
  h_Nq->Write();
  h_N0tag->Write();
  h_N1tag->Write();
  h_N2tag->Write();

  for(int i=0; i<4; i++) {
    h_N0[i]->Write();
    h_N1[i]->Write();
    h_N2[i]->Write();
    h_Charge[i]->Write();
    h_Nacc[i]->Write();
    h_Nrej[i]->Write();
  }

}


void QQbarAnalysisClass::AFB_histos_for_PQ_analysis(int n_entries=-1, int bkg=0, float Kvcut=35, int quark=4)
{

  float pcut=3.;
  //optimal dedx cutone
  //if(dedxcut==7) {
  dedxcut_up=1.1;
  dedxcut_down=-2.45;
  //}


  TString filename=TString::Format("AFB_quark%i_%s_250GeV.root",quark,process.Data());
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  //Ntotal_nocuts
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);

  //indexes 0=b (or signal), 1=c, 2=uds, 3=rad return 

  TH1F * h_Ntotal_nocuts2[4];// = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);

  TH1F * h_Nparton[4];// = new TH1F("h_Nparton","h_Nparton",20,0,1);
  TH1F * h_AFB[4];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_Nq[4];// = new TH1F("h_Nq","h_Nq",20,0,1);//quarks before preselection
  TH1F * h_N0tag[4];//= new TH1F("h_N0tag","h_N0tag",20,0,1);;//N after preselection
  TH1F * h_N1tag[4];//= new TH1F("h_N1tag","h_N1tag",20,0,1);;//events 1 tag
  TH1F * h_N2tag[4];//= new TH1F("h_N2tag","h_N2tag",20,0,1);;//events 2 tags

  //second dimension indexes: Kc, KcCheatdEdx, KcCheatdEdxTOF, Vtx
  TString methodnames[5]={"Kc","KcCheatdEdx","KcCheatdEdxTOF","KcCheatTOF","Vtx"};
  TH1F * h_N0[4][5];//N after two flavour tag, 
  TH1F * h_N1[4][5];//events 1 charge
  TH1F * h_N2[4][5];//events 2 charge

  TH1F * h_Charge[4][5];
  TH1F * h_Nacc[4][5];//events with compatible charge
  TH1F * h_Nrej[4][5];//events with non compatible charge

  for(int i=0;i<4;i++) {

    h_Ntotal_nocuts2[i] = new TH1F(TString::Format("h_Ntotal_nocuts_%i",i),TString::Format("h_Ntotal_nocuts_%i",i),20,0,1);
    h_Nparton[i] = new TH1F(TString::Format("h_Nparton_%i",i),TString::Format("h_Nparton_%i",i),20,0,1);
    h_AFB[i] = new TH1F(TString::Format("h_AFB_%i",i),TString::Format("h_AFB_%i",i),40,-1,1);
    h_Nq[i] = new TH1F(TString::Format("h_Nq_%i",i),TString::Format("h_Nq_%i",i),20,0,1);//quarks before preselection
    h_N0tag[i] = new TH1F(TString::Format("h_N0_%i",i),TString::Format("h_N0_%i",i),20,0,1);//N after preselection
    h_N1tag[i] = new TH1F(TString::Format("h_N1_%i",i),TString::Format("h_N1_%i",i),20,0,1);//events 1 tag
    h_N2tag[i] = new TH1F(TString::Format("h_N2_%i",i),TString::Format("h_N2_%i",i),20,0,1);//events 2 tags

    for(int j=0; j<5; j++) {
      h_N0[i][j] = new TH1F(TString::Format("h_N0_%s_%i",methodnames[j].Data(),i),TString::Format("h_N0_%s_%i",methodnames[j].Data(),i),20,0,1);
      h_N1[i][j] = new TH1F(TString::Format("h_N1_%s_%i",methodnames[j].Data(),i),TString::Format("h_N1_%s_%i",methodnames[j].Data(),i),20,0,1);
      h_N2[i][j] = new TH1F(TString::Format("h_N2_%s_%i",methodnames[j].Data(),i),TString::Format("h_N2_%s_%i",methodnames[j].Data(),i),20,0,1);
      h_Charge[i][j] = new TH1F(TString::Format("h_Charge_%s_%i",methodnames[j].Data(),i),TString::Format("h_Charge_%s_%i",methodnames[j].Data(),i),400,-10,10);
      h_Nacc[i][j] = new TH1F(TString::Format("h_Nacc_%s_%i",methodnames[j].Data(),i),TString::Format("h_Nacc_%s_%i",methodnames[j].Data(),i),40,-1,1);
      h_Nrej[i][j] = new TH1F(TString::Format("h_Nrej_%s_%i",methodnames[j].Data(),i),TString::Format("h_Nrej_%s_%i",methodnames[j].Data(),i),40,-1,1);
    }
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

    TVector3 v1(mc_quark_ps_jet_px[0],mc_quark_ps_jet_py[0],mc_quark_ps_jet_pz[0]);
    TVector3 v2(mc_quark_ps_jet_px[1],mc_quark_ps_jet_py[1],mc_quark_ps_jet_pz[1]);
    float acol=GetSinacol(v1,v2);

    int iquark=-1;
    if(bkg==0) {
      if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut && acol<0.3) iquark=0;
      if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut && acol<0.3) iquark=1;
      if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut && acol<0.3) iquark=2;
      if(gamma_e>Kvcut || acol>0.3) iquark=3;
    } else {
      iquark=0;
    }

    //reconsturcet thrust angle
    /*float costheta;
    std::vector<float> p;
    p.push_back(principle_thrust_axis[0]);
    p.push_back(principle_thrust_axis[1]);
    p.push_back(principle_thrust_axis[2]);
    costheta=fabs(GetCostheta(p));
    */
    //jet direction
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta_jet=GetCostheta(p);
    
    //-- jet direction using charged pfos
    std::vector<float> p1;
    std::vector<float> p2;
    float px_pfos[2]={0};
    float py_pfos[2]={0};
    float pz_pfos[2]={0};
    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if((pfo_match[ipfo]==0 || pfo_match[ipfo]==1) && pfo_charge[ipfo]!=0 && pfo_ntracks[ipfo]==1) {
	      px_pfos[pfo_match[ipfo]]+=pfo_px[ipfo];
	      py_pfos[pfo_match[ipfo]]+=pfo_py[ipfo];
	      pz_pfos[pfo_match[ipfo]]+=pfo_pz[ipfo];
      }
    }
    p1.push_back(px_pfos[0]-px_pfos[1]);
    p1.push_back(py_pfos[0]-py_pfos[1]);
    p1.push_back(pz_pfos[0]-pz_pfos[1]);
    float costheta=fabs(GetCostheta(p1));
    
    //h_Ntotal_nocuts->Fill(costheta);
    //h_Ntotal_nocuts2[iquark]->Fill(costheta);

    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //cheat angle
    float costheta_ccbar=1;
    if(bkg==0) {
      std::vector<float> p_bbar;
      p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
      p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
      p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
      costheta_ccbar=GetCostheta(p_bbar);
      costheta_ccbar=  (mc_quark_charge[0] < 0) ? -costheta_ccbar: costheta_ccbar;
      if(fabs(mc_quark_pdg[0])==5 || fabs(mc_quark_pdg[0])==3 || fabs(mc_quark_pdg[0])==1) costheta_ccbar*=-1;
    }
    h_Ntotal_nocuts->Fill(fabs(costheta));
    h_Ntotal_nocuts2[iquark]->Fill(fabs(costheta));

    // costheta=fabs(costheta)*costheta/fabs(costheta);
    //reco level distributions
    float Kv=Kreco();
    bool selection=PreSelection(6,Kvcut);
    if(selection==false) continue;

    //analysis
    h_N0tag[iquark]->Fill(fabs(costheta));  
    h_Nq[iquark]->Fill(fabs(costheta));
    h_Nparton[iquark]->Fill(fabs(costheta));
    if(bkg==0)h_AFB[iquark]->Fill(costheta);

 
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

    if(jettag[0]==true)  h_N1tag[iquark]->Fill(fabs(costheta));
    if(jettag[1]==true)  h_N1tag[iquark]->Fill(fabs(costheta));
    
    if(jettag[0]==false || jettag[1]==false) continue;
    h_N2tag[iquark]->Fill(fabs(costheta));
    
    float charge[2][5]={0};
    for(int ijet=0; ijet<2; ijet++) {
      charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
      charge[ijet][1]=ChargeKJet(0,ijet,pcut,true,false);
      charge[ijet][2]=ChargeKJet(0,ijet,pcut,true,true);
      charge[ijet][3]=ChargeKJet(0,ijet,pcut,false,true);     
      charge[ijet][4]=ChargeVtxJet(0,ijet,pcut);
      if(quark==5) charge[ijet][4]*=-1;
    }

    //Efficiencies && charge purity
    for(int i=0; i<5; i++) {
      //Efficiencies
      h_N0[iquark][i]->Fill(fabs(costheta));
      for(int ijet=0; ijet<2; ijet++) {
	      if(charge[ijet][i]!=0) {
	        h_Charge[iquark][i]->Fill(charge[ijet][i]);
	        h_N1[iquark][i]->Fill(fabs(costheta));
	      }
      }
      if(charge[0][i]!=0 && charge[1][i]!=0) h_N2[iquark][i]->Fill(fabs(costheta));

      float costheta_temp=  (charge[0][i] < 0) ? -costheta_jet: costheta_jet;

      //purities
      if(quark==5) {
	      if(i==4) {
  	      if(charge[0][i]*charge[1][i]<0) h_Nacc[iquark][i]->Fill(fabs(costheta)*costheta_temp/fabs(costheta_temp));
          if(charge[0][i]*charge[1][i]>0) {
	          h_Nrej[iquark][i]->Fill(costheta);
	          h_Nrej[iquark][i]->Fill(-costheta);
	        }
	      } else {
	        if(charge[0][4]==0 && charge[1][4]==0) {
	          if(charge[0][i]*charge[1][i]<0) h_Nacc[iquark][i]->Fill(fabs(costheta)*costheta_temp/fabs(costheta_temp));
	          if(charge[0][i]*charge[1][i]>0) {
	            h_Nrej[iquark][i]->Fill(costheta);
	            h_Nrej[iquark][i]->Fill(-costheta);
	          }
	        }
	      }
      } else {//quark
	      if(charge[0][i]*charge[1][i]<0) h_Nacc[iquark][i]->Fill(fabs(costheta)*costheta_temp/fabs(costheta_temp));
	      if(charge[0][i]*charge[1][i]>0) {
	        h_Nrej[iquark][i]->Fill(costheta);
	        h_Nrej[iquark][i]->Fill(-costheta);
	      }
      }

    }

  }//entries
  
  cout<<filename<<endl;
  
  h_Ntotal_nocuts->Write();
  int maxhisto=1;
  if(bkg==0) maxhisto=4;
  for(int i=0; i<maxhisto; i++) {
    h_Ntotal_nocuts2[i]->Write();
    h_Nparton[i]->Write();
    if(bkg==0)h_AFB[i]->Write();
    h_Nq[i]->Write();
    h_N0tag[i]->Write();
    h_N1tag[i]->Write();
    h_N2tag[i]->Write();

    for(int j=0; j<5; j++) {
      h_N0[i][j]->Write();
      h_N1[i][j]->Write();
      h_N2[i][j]->Write();
      h_Charge[i][j]->Write();
      h_Nacc[i][j]->Write();
      h_Nrej[i][j]->Write();
    }
  }

}


void QQbarAnalysisClass::AFB_energyDependence(int n_entries=-1, int bkg=0, float Kvcut=35, float acol_cut=0.3)
{

  TString filename=TString::Format("AFBEnergyDep_%s_250GeV.root",process.Data());
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  //Ntotal_nocuts
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);

  TH2F * h_acol_vs_K = new TH2F("h_acol_vs_K","h_acol_vs_K",105,5.5,110.5,99,0.005,0.995);
  
  TH1F * h_AFBb_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBb[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBb_K35_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBb_K35[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBb_acol30_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBb_acol30[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);

  TH1F * h_AFBc_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBc[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBc_K35_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBc_K35[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBc_acol30_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBc_acol30[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  
  TH1F * h_AFBuds_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBuds[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBuds_K35_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBuds_K35[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBuds_acol30_com[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  TH1F * h_AFBuds_acol30[150];// = new TH1F("h_AFB","h_AFB",40,-1,1);
  
  for(int i=0;i<150;i++) {
    h_AFBb_com[i] = new TH1F(TString::Format("h_AFBb_COM_KLowerThan%i",i),TString::Format("h_AFBb_COM_KLowerThan%i",i),40,-1,1);
    h_AFBb[i] = new TH1F(TString::Format("h_AFBb_KLowerThan%i",i),TString::Format("h_AFBb_KLowerThan%i",i),40,-1,1);

    h_AFBb_K35_com[i] = new TH1F(TString::Format("h_AFBb_COM_K35_AcolLowerThan%i",i),TString::Format("h_AFBb_COM_K35_AcolLowerThan%i",i),40,-1,1);
    h_AFBb_K35[i] = new TH1F(TString::Format("h_AFBb_K35_AcolLowerThan%i",i),TString::Format("h_AFBb_KLowerThan%i",i),40,-1,1);

    h_AFBb_acol30_com[i] = new TH1F(TString::Format("h_AFBb_COM_acol30_KLowerThan%i",i),TString::Format("h_AFBb_COM_acol30_KLowerThan%i",i),40,-1,1);
    h_AFBb_acol30[i] = new TH1F(TString::Format("h_AFBb_acol30_KLowerThan%i",i),TString::Format("h_AFBb_KLowerThan%i",i),40,-1,1);

    h_AFBc_com[i] = new TH1F(TString::Format("h_AFBc_COM_KLowerThan%i",i),TString::Format("h_AFBc_COM_KLowerThan%i",i),40,-1,1);
    h_AFBc[i] = new TH1F(TString::Format("h_AFBc_KLowerThan%i",i),TString::Format("h_AFBc_KLowerThan%i",i),40,-1,1);

    h_AFBc_K35_com[i] = new TH1F(TString::Format("h_AFBc_COM_K35_KLowerThan%i",i),TString::Format("h_AFBc_COM_K35_AcolLowerThan%i",i),40,-1,1);
    h_AFBc_K35[i] = new TH1F(TString::Format("h_AFBc_K35_AcolLowerThan%i",i),TString::Format("h_AFBc_KLowerThan%i",i),40,-1,1);

    h_AFBc_acol30_com[i] = new TH1F(TString::Format("h_AFBc_COM_acol30_KLowerThan%i",i),TString::Format("h_AFBc_COM_acol30_KLowerThan%i",i),40,-1,1);
    h_AFBc_acol30[i] = new TH1F(TString::Format("h_AFBc_acol30_KLowerThan%i",i),TString::Format("h_AFBc_KLowerThan%i",i),40,-1,1);

    h_AFBuds_com[i] = new TH1F(TString::Format("h_AFBuds_COM_KLowerThan%i",i),TString::Format("h_AFBuds_COM_KLowerThan%i",i),40,-1,1);
    h_AFBuds[i] = new TH1F(TString::Format("h_AFBuds_KLowerThan%i",i),TString::Format("h_AFBuds_KLowerThan%i",i),40,-1,1);

    h_AFBuds_K35_com[i] = new TH1F(TString::Format("h_AFBuds_COM_K35_AcolLowerThan%i",i),TString::Format("h_AFBuds_COM_K35_AcolLowerThan%i",i),40,-1,1);
    h_AFBuds_K35[i] = new TH1F(TString::Format("h_AFBuds_K35_AcolLowerThan%i",i),TString::Format("h_AFBuds_KLowerThan%i",i),40,-1,1);

    h_AFBuds_acol30_com[i] = new TH1F(TString::Format("h_AFBuds_COM_acol30_KLowerThan%i",i),TString::Format("h_AFBuds_COM_acol30_KLowerThan%i",i),40,-1,1);
    h_AFBuds_acol30[i] = new TH1F(TString::Format("h_AFBuds_acol30_KLowerThan%i",i),TString::Format("h_AFBuds_KLowerThan%i",i),40,-1,1);

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


    //if(fabs(mc_quark_pdg[0])<4) continue;
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

    TVector3 v1(mc_quark_ps_jet_px[0],mc_quark_ps_jet_py[0],mc_quark_ps_jet_pz[0]);
    TVector3 v2(mc_quark_ps_jet_px[1],mc_quark_ps_jet_py[1],mc_quark_ps_jet_pz[1]);
    float acol=GetSinacol(v1,v2);

    float costheta_ccbar=1;
    std::vector<float> p_bbar;
    p_bbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_bbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_bbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_ccbar=GetCostheta(p_bbar);
    costheta_ccbar=  (mc_quark_charge[0] < 0) ? -costheta_ccbar: costheta_ccbar;
    if(fabs(mc_quark_pdg[0])==5 || fabs(mc_quark_pdg[0])==3 || fabs(mc_quark_pdg[0])==1) costheta_ccbar*=-1;

    h_Ntotal_nocuts->Fill(fabs(costheta_ccbar));
    //center of mass boost
    TLorentzVector MyParticle1;
    TLorentzVector MyParticle2;
    float e0=sqrt(pow(mc_quark_px[0],2)+ pow(mc_quark_py[0],2)+ pow(mc_quark_pz[0],2));
    float e1=sqrt(pow(mc_quark_px[1],2)+ pow(mc_quark_py[1],2)+ pow(mc_quark_pz[1],2));
    MyParticle1.SetPxPyPzE(mc_quark_px[0],mc_quark_py[0],mc_quark_pz[0],e0);
    MyParticle2.SetPxPyPzE(mc_quark_px[1],mc_quark_py[1],mc_quark_pz[1],e1);
    if( fabs(mc_quark_pdg[0])==4 && mc_quark_charge[0] < 0) {
      MyParticle2.SetPxPyPzE(mc_quark_px[0],mc_quark_py[0],mc_quark_pz[0],e0);
      MyParticle1.SetPxPyPzE(mc_quark_px[1],mc_quark_py[1],mc_quark_pz[1],e1);
    }
    TLorentzVector MyParticleCombi;
    MyParticleCombi=MyParticle1+MyParticle2;

    TVector3 MyParticleCombi_BoostVector = MyParticleCombi.BoostVector();
    TLorentzVector MyParticle1_newSys = MyParticle1;
    MyParticle1_newSys.Boost(-MyParticleCombi_BoostVector);
    TLorentzVector MyParticle2_newSys = MyParticle2;
    MyParticle2_newSys.Boost(-MyParticleCombi_BoostVector);

    float costheta_ccbar_COM=1;
    std::vector<float> p_bbar_COM;
    p_bbar_COM.push_back(MyParticle1_newSys.Px());
    p_bbar_COM.push_back(MyParticle1_newSys.Py());
    p_bbar_COM.push_back(MyParticle1_newSys.Pz());
    costheta_ccbar_COM=GetCostheta(p_bbar_COM);

    h_acol_vs_K->Fill(gamma_e,acol);

    //Fill AFB vs K
    for(int i=0;i<150;i++) {

      if(fabs(mc_quark_pdg[0])==5 && gamma_e<i ) {
	h_AFBb[i]->Fill(costheta_ccbar);
	h_AFBb_com[i]->Fill(costheta_ccbar_COM);
      }
      if(fabs(mc_quark_pdg[0])==4 && gamma_e<i ) {
	h_AFBc[i]->Fill(costheta_ccbar);
	h_AFBc_com[i]->Fill(costheta_ccbar_COM);
      }
     if(fabs(mc_quark_pdg[0])<4 && gamma_e<i ) {
	h_AFBuds[i]->Fill(costheta_ccbar);
	h_AFBuds_com[i]->Fill(costheta_ccbar_COM);
      }

      if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut && acol<i/100.) {
	h_AFBb_K35[i]->Fill(costheta_ccbar);
	h_AFBb_K35_com[i]->Fill(costheta_ccbar_COM);
      }
      if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut && acol<i/100.) {
	h_AFBc_K35[i]->Fill(costheta_ccbar);
	h_AFBc_K35_com[i]->Fill(costheta_ccbar_COM);
      }
      if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut && acol<i/100.) {
	h_AFBuds_K35[i]->Fill(costheta_ccbar);
	h_AFBuds_K35_com[i]->Fill(costheta_ccbar_COM);
      }

      if(fabs(mc_quark_pdg[0])==5 && gamma_e<i && acol<30./100.) {
	h_AFBb_acol30[i]->Fill(costheta_ccbar);
	h_AFBb_acol30_com[i]->Fill(costheta_ccbar_COM);
      }
      if(fabs(mc_quark_pdg[0])==4 && gamma_e<i && acol<30./100.) {
	h_AFBc_acol30[i]->Fill(costheta_ccbar);
	h_AFBc_acol30_com[i]->Fill(costheta_ccbar_COM);
      }
      if(fabs(mc_quark_pdg[0])<4 && gamma_e<i && acol<30./100.) {
	h_AFBuds_acol30[i]->Fill(costheta_ccbar);
	h_AFBuds_acol30_com[i]->Fill(costheta_ccbar_COM);
      }

    }
  }

  MyFile->cd();
  h_Ntotal_nocuts->Write();
  h_acol_vs_K->Write();

  for(int i=0;i<150;i++) {
    h_AFBb_com[i]->Write();
    h_AFBb[i]->Write();

    h_AFBb_K35_com[i]->Write();
    h_AFBb_K35[i]->Write();

    h_AFBb_acol30_com[i]->Write();
    h_AFBb_acol30[i]->Write();
    
    h_AFBc_com[i]->Write();
    h_AFBc[i]->Write();

    h_AFBc_K35_com[i]->Write();
    h_AFBc_K35[i]->Write();

    h_AFBc_acol30_com[i]->Write();
    h_AFBc_acol30[i]->Write();

    h_AFBuds_com[i]->Write();
    h_AFBuds[i]->Write();

    h_AFBuds_K35_com[i]->Write();
    h_AFBuds_K35[i]->Write();

    h_AFBuds_acol30_com[i]->Write();
    h_AFBuds_acol30[i]->Write();
  }


}


void QQbarAnalysisClass::AFBreconstruction(int n_entries=-1, float Kvcut=35, int quark=4, TString polString="eL_pR", int method=0)
{

  //Ntotal_nocuts                                                                                                                    
  TH1F * h_Ntotal_nocuts = new TH1F("h_Ntotal_nocuts","h_Ntotal_nocuts",20,0,1);

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

  //methods 0=Kc, 1=KcCheatdEdx, 2=KcCheatdEdxTOF, 3=KcCheatTOF, 4=Vtx
  TString method_string[4]={"","CheatdEdx","CheatdEdxTOF","CheatTOF"};

   int nsyst=22;


  //variations for systematics

  
  TString syst_variations1[100];
  syst_variations1[0]="";
  syst_variations1[1]="_rho";
  syst_variations1[2]="_bkg_p1";
  syst_variations1[3]="_bkg_m1";
  syst_variations1[4]="_bkg_p5";
  syst_variations1[5]="_bkg_m5";
  syst_variations1[6]="_bkg_p10";
  syst_variations1[7]="_bkg_m10";
  syst_variations1[8]="_Rbup1";
  syst_variations1[9]="_Rbdown1";
  syst_variations1[10]="_Rbup5";
  syst_variations1[11]="_Rbdown5";
  syst_variations1[12]="_uds_p1";
  syst_variations1[13]="_uds_m1";
  syst_variations1[14]="_uds_p5";
  syst_variations1[15]="_uds_m5";
  syst_variations1[16]="_heavy_p1";
  syst_variations1[17]="_heavy_m1";
  syst_variations1[18]="_heavy_p5";
  syst_variations1[19]="_heavy_m5";
  syst_variations1[20]="";//not using rho correction
  syst_variations1[21]="";//using a parametrized eff_pres
  
  
  TString syst_variations2[100];
  syst_variations2[0]="";
  syst_variations2[1]="";
  syst_variations2[2]="_bkg_p1";
  syst_variations2[3]="_bkg_m1";
  syst_variations2[4]="_bkg_p5";
  syst_variations2[5]="_bkg_m5";
  syst_variations2[6]="_bkg_p10";
  syst_variations2[7]="_bkg_m10";
  syst_variations2[8]="";
  syst_variations2[9]="";
  syst_variations2[10]="";
  syst_variations2[11]="";
  syst_variations2[12]="";
  syst_variations2[13]="";
  syst_variations2[14]="";
  syst_variations2[15]="";
  syst_variations2[16]="";
  syst_variations2[17]="";
  syst_variations2[18]="";
  syst_variations2[19]="";
  syst_variations2[20]="";//not using rho correction
  syst_variations2[21]="";//using a parametrized eff_pres
  
  //**************

  //new file
  TString filename=TString::Format("AFBreco_quark%i_%s_250GeV_cheatmethod_%i.root",quark,process.Data(),method);
  
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  //  initialize histograms
  TH1F *h_AFB = new TH1F("h_AFB","h_AFB",40,-1.0,1.0);
  TH1F *h_AFB2 = new TH1F("h_AFB2","h_AFB2",40,-1.0,1.0);

  TH1F *h_AFBcheat = new TH1F("h_AFBcheat","h_AFBcheat",40,-1.0,1.0);
  TH1F *h_samesign = new TH1F("h_samesign","h_samesign",40,-1.0,1.0);

  TH1F *h_AFBreco[3][50];
  TH1F *h_AFBreco_pqcorrected[3][50];
  TH1F *h_AFBreco_chargecheat[3][50];
  TH1F *h_AFBreco_pqcorrected_effcorrected[3][50];
  TH1F *h_AFBreco_chargecheat_effcorrected[3][50];
  TH1F *h_AFBreco_pqcorrected_efftotalcorrected[3][50];
  TH1F *h_AFBreco_chargecheat_efftotalcorrected[3][50];

  for(int j=0; j<3; j++) {
    for(int i=0; i<50; i++) {
      h_AFBreco[j][i] = new TH1F(TString::Format("h_AFBreco_cat%i_syst%i",j,i),TString::Format("h_AFBreco_cat%i_syst%i",j,i),40,-1.0,1.0);
      h_AFBreco_pqcorrected[j][i]= new TH1F(TString::Format("h_AFBreco_pqcorrectedreco_cat%i_syst%i",j,i),TString::Format("h_AFBreco_pqcorrected_cat%i_syst%i",j,i),40,-1.0,1.0);
      h_AFBreco_chargecheat[j][i]= new TH1F(TString::Format("h_AFBreco_chargecheatreco_cat%i_syst%i",j,i),TString::Format("h_AFBreco_chargecheat_cat%i_syst%i",j,i),40,-1.0,1.0);
      h_AFBreco_pqcorrected_effcorrected[j][i]= new TH1F(TString::Format("h_AFBreco_pqcorrectedreco_effcorrected_cat%i_syst%i",j,i),TString::Format("h_AFBreco_pqcorrected_effcorrected_cat%i_syst%i",j,i),40,-1.0,1.0);
      h_AFBreco_chargecheat_effcorrected[j][i]= new TH1F(TString::Format("h_AFBreco_chargecheatreco_effcorrected_cat%i_syst%i",j,i),TString::Format("h_AFBreco_chargecheat_effcorrected_cat%i_syst%i",j,i),40,-1.0,1.0);
      h_AFBreco_pqcorrected_efftotalcorrected[j][i]= new TH1F(TString::Format("h_AFBreco_pqcorrectedreco_efftotalcorrected_cat%i_syst%i",j,i),TString::Format("h_AFBreco_pqcorrected_efftotalcorrected_cat%i_syst%i",j,i),40,-1.0,1.0);
      h_AFBreco_chargecheat_efftotalcorrected[j][i]= new TH1F(TString::Format("h_AFBreco_chargecheatreco_efftotalcorrected_cat%i_syst%i",j,i),TString::Format("h_AFBreco_chargecheat_efftotalcorrected_cat%i_syst%i",j,i),40,-1.0,1.0);
    }
  }

  //----------------------------------------------------
  //open pq's
  TString filenamepq =TString::Format("/lhome/ific/a/airqui/QQbar/AFBhq2021-dev/analysis/AFB/weights/pq_pdg%i_pol%i.root",quark,pol);
  TFile *fpq = new TFile(filenamepq);
  TH1F *purity_0[50];
  TH1F *purity_1[50];
  for(int isyst=0; isyst<nsyst; isyst++) {
    //    cout<<isyst<<endl;
    if(quark==5) {
      //      cout<<TString::Format("purity_Vtx%s",syst_variations2[isyst].Data())<<endl;
      purity_0[isyst]= (TH1F*)fpq->Get(TString::Format("purity_Vtx%s",syst_variations2[isyst].Data()));
      purity_1[isyst] = (TH1F*)fpq->Get(TString::Format("purity_Kc%s%s",method_string[method].Data(),syst_variations2[isyst].Data()));
    }
    if(quark==4) {
      purity_1[isyst]= (TH1F*)fpq->Get(TString::Format("purity_Vtx%s",syst_variations2[isyst].Data()));
      purity_0[isyst] = (TH1F*)fpq->Get(TString::Format("purity_Kc%s%s",method_string[method].Data(),syst_variations2[isyst].Data()));
    }
  }

  //----------------------------------------------------
  //open weights of efficiencies
  TString filenameweight =TString::Format("/lhome/ific/a/airqui/QQbar/AFBhq2021-dev/analysis/AFB/weights/eff_weights_pdg%i_pol%i.root",quark,pol);
  //  cout<<TString::Format("/lhome/ific/a/airqui/QQbar/AFBhq2021-dev/analysis/AFB/weights/eff_weights_pdg%i_pol%i.root",quark,pol)<<endl;
  TFile *fw = new TFile(filenameweight);
  TH1F *eff_preselection[50];
  TH1F *eff_tagging[50];
  TH1F *rho[50];

  for(int isyst=0; isyst<nsyst; isyst++) {
    //cout<<isyst<<endl;
    eff_preselection[isyst]= (TH1F*)fw->Get(TString::Format("eff_pres%s",syst_variations2[isyst].Data()));
    eff_tagging[isyst] = (TH1F*)fw->Get(TString::Format("eff_tagging%s",syst_variations1[isyst].Data()));
    //cout<<TString::Format("eff_tagging%s",syst_variations1[isyst].Data())<<endl;
    rho[isyst] = (TH1F*)fw->Get("rho");
  }

  //----------------------------------------------------
  //open weights of charge masurement efficiencies
  TString filenameweightcharge =TString::Format("/lhome/ific/a/airqui/QQbar/AFBhq2021-dev/analysis/AFB/weights/chargeeff_weights_pdg%i_pol%i.root",quark,pol);
  TFile *fcharge = new TFile(filenameweightcharge);
  TH1F *eff_charge_0[50];
  TH1F *eff_charge_1[50];
  for(int isyst=0; isyst<nsyst; isyst++) {
    //    cout<<isyst<<endl;
    if(quark==5) {
      eff_charge_0[isyst] = (TH1F*)fcharge->Get(TString::Format("eff_charge_Vtx%s",syst_variations2[isyst].Data()));
      eff_charge_1[isyst] = (TH1F*)fcharge->Get(TString::Format("eff_charge_Kc%s%s",method_string[method].Data(),syst_variations2[isyst].Data()));
    }
    if(quark==4) {
      eff_charge_1[isyst] = (TH1F*)fcharge->Get(TString::Format("eff_charge_Vtx%s",syst_variations2[isyst].Data()));
      eff_charge_0[isyst] = (TH1F*)fcharge->Get(TString::Format("eff_charge_Kc%s%s",method_string[method].Data(),syst_variations2[isyst].Data()));
    }
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



    h_Ntotal_nocuts->Fill(0.5);

    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

    TVector3 v1(mc_quark_ps_jet_px[0],mc_quark_ps_jet_py[0],mc_quark_ps_jet_pz[0]);
    TVector3 v2(mc_quark_ps_jet_px[1],mc_quark_ps_jet_py[1],mc_quark_ps_jet_pz[1]);
    float acol=GetSinacol(v1,v2);
    if(fabs(mc_quark_pdg[0])!=quark || gamma_e>Kvcut  ||  acol>0.3) continue;

    //reconsturcet thrust angle
    // float costheta_thrust;
    // std::vector<float> p_thrust;
    // p_thrust.push_back(principle_thrust_axis[0]);
    // p_thrust.push_back(principle_thrust_axis[1]);
    // p_thrust.push_back(principle_thrust_axis[2]);
    // costheta_thrust=fabs(GetCostheta(p_thrust));

    //jet direction
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta_jet=GetCostheta(p);
    //-- jet direction using charged pfos
    std::vector<float> p1;
    std::vector<float> p2;
    float px_pfos[2]={0};
    float py_pfos[2]={0};
    float pz_pfos[2]={0};
    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if((pfo_match[ipfo]==0 || pfo_match[ipfo]==1) && pfo_charge[ipfo]!=0 && pfo_ntracks[ipfo]==1) {
	      px_pfos[pfo_match[ipfo]]+=pfo_px[ipfo];
      	py_pfos[pfo_match[ipfo]]+=pfo_py[ipfo];
	      pz_pfos[pfo_match[ipfo]]+=pfo_pz[ipfo];
      }
    }
    p1.push_back(px_pfos[0]-px_pfos[1]);
    p1.push_back(py_pfos[0]-py_pfos[1]);
    p1.push_back(pz_pfos[0]-pz_pfos[1]);
    float costheta=GetCostheta(p1);

    int abs_value_costheta_bin = int(fabs(costheta)*100./5);

    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //cheat angle
    float costheta_cheat=1;
    std::vector<float> p_cheat;
    p_cheat.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_cheat.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_cheat.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    costheta_cheat=GetCostheta(p_cheat);
    costheta_cheat=  (mc_quark_charge[0] < 0) ? -costheta_cheat: costheta_cheat;
    if(fabs(mc_quark_pdg[0])==5 || fabs(mc_quark_pdg[0])==3 || fabs(mc_quark_pdg[0])==1) costheta_cheat*=-1;

    h_AFB->Fill(fabs(costheta)*costheta_cheat/fabs(costheta_cheat));
    h_AFB2->Fill(costheta_cheat);

    //reco level distributions
    //    float Kv=Kreco();
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

   
    float charge[2][2]={0};
    for(int ijet=0; ijet<2; ijet++) {
      if(quark==5) {
	      // charge[ijet][0]=-ChargeVtxJet(0,ijet,pcut);
	      // if(method==0) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
	      // if(method==1) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
	      // if(method==2) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
	      // if(method==3) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
	      charge[ijet][0]=-ChargeVtxJet(0,ijet,pcut);
	      if(method==0) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
	      if(method==1) charge[ijet][1]=ChargeKJet(0,ijet,pcut,true,false);
	      if(method==2) charge[ijet][1]=ChargeKJet(0,ijet,pcut,true,true);
	      if(method==3) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,true);
      }
      if(quark==4) {
	      charge[ijet][1]=ChargeVtxJet(0,ijet,pcut);
	      // if(method==0) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
	      // if(method==1) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
	      // if(method==2) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
	      // if(method==3) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        if(method==0) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        if(method==1) charge[ijet][0]=ChargeKJet(0,ijet,pcut,true,false);//true,false);
        if(method==2) charge[ijet][0]=ChargeKJet(0,ijet,pcut,true,false);//true,true);
        if(method==3) charge[ijet][0]=ChargeKJet(0,ijet,pcut,true,false);//false,true);
      }
    }


    //HERE LOOP OVER ALL THE SYSTEMATICS
    for(int isyst=0; isyst<nsyst; isyst++) {
      //          cout<<isyst<<endl;

      //START with actual weight calcuation, jet -wise
      float jet_charge[2]={0};
      float prob_charge[2]={0};
      float eff_charge[2]={0};
      float rhovalue=rho[isyst]->GetBinContent(abs_value_costheta_bin+1);
      float eff_tag=eff_tagging[isyst]->GetBinContent(abs_value_costheta_bin+1)*sqrt(rhovalue);
      if(isyst==(nsyst-2)) eff_tag=eff_tagging[isyst]->GetBinContent(abs_value_costheta_bin+1);

      //*************************************************
      //assuming one method with priority
      for(int ijet=0; ijet<2; ijet++) {
	
        if(charge[ijet][0]!=0) {
          jet_charge[ijet] = charge[ijet][0]/fabs(charge[ijet][0]);
          prob_charge[ijet]=purity_0[isyst]->GetBinContent(abs_value_costheta_bin+1);
          eff_charge[ijet]=eff_charge_0[isyst]->GetBinContent(abs_value_costheta_bin+1);
        }
        if(charge[ijet][1]!=0 && charge[ijet][0]==0) {
          jet_charge[ijet] = charge[ijet][1]/fabs(charge[ijet][1]);
          prob_charge[ijet]=purity_1[isyst]->GetBinContent(abs_value_costheta_bin+1);
          // cout<<jentry<<"  k --"<<prob_charge[ijet]<<endl;
          eff_charge[ijet]=(1.-eff_charge_0[isyst]->GetBinContent(abs_value_costheta_bin+1))*eff_charge_1[isyst]->GetBinContent(abs_value_costheta_bin+1);
        } 
	
      }
      if(jet_charge[0]*jet_charge[1]==0  || jet_charge[0]*jet_charge[1]>0 ) continue;
      
      double p1=prob_charge[0];
      double p2=prob_charge[1];
      double q1=1-p1;
      double q2=1-p2;
      double weightpq=(p1*p1+q1*q2)/(pow(p1*p2,2)-pow(q1*q2,2));
      double weighteff=1./(eff_tag*eff_tag*eff_charge[0]*eff_charge[1]*(p1*p2+q1*q2));
      float costheta_reco=  (jet_charge[0] < 0) ? -costheta: costheta;
      float prob_plus=p1*p2*weightpq;// 1./ ( q1*q2-p1*p1*p2*p2/(q1*q1));
      float prob_minus=-q1*q2*weightpq;// prob_minus*p1*p2/(q1*q2);
      
      int indx_cat=-1;

      if(charge[0][0]!=0 && charge[1][0]!=0 )  indx_cat=0;
      else if( (charge[0][0]==0 ||  charge[1][0]==0) &&  (charge[0][0]!=0 ||  charge[1][0]!=0) ) {
        indx_cat=1;
        weighteff*=0.5;
      }
      else if( charge[0][0]==0 && charge[1][0]==0 ) indx_cat=2;
      
      if(indx_cat<0) {
        cout<<"ERROR: cat="<<indx_cat<<" charge-jet0:"<<charge[0][0]<<" "<<charge[0][1]<<" | charge-jet1:"<<charge[1][0]<<" "<<charge[1][1]<<endl;
        continue;
      }
      if(isyst==0)  h_AFBcheat->Fill(costheta_cheat);
      h_AFBreco[indx_cat][isyst]->Fill(costheta_reco);
      h_AFBreco_pqcorrected[indx_cat][isyst]->Fill(costheta_reco,prob_plus);
      h_AFBreco_pqcorrected[indx_cat][isyst]->Fill(-costheta_reco,prob_minus);
      h_AFBreco_pqcorrected_effcorrected[indx_cat][isyst]->Fill(costheta_reco,prob_plus*weighteff);
      h_AFBreco_pqcorrected_effcorrected[indx_cat][isyst]->Fill(-costheta_reco,prob_minus*weighteff);
      
      h_AFBreco_chargecheat[indx_cat][isyst]->Fill(fabs(costheta_reco)*costheta_cheat/fabs(costheta_cheat));
      h_AFBreco_chargecheat_effcorrected[indx_cat][isyst]->Fill(fabs(costheta_reco)*costheta_cheat/fabs(costheta_cheat),weighteff);
    
    }//isyst


  }
    

  MyFile->cd();
  h_Ntotal_nocuts->Write();
  h_AFB->Write();
  h_AFB2->Write();

  h_AFBcheat->Write();
  h_samesign ->Write();
  
  for(int icat=0; icat<3; icat++) {
    for(int isyst=0; isyst<nsyst; isyst++) {
      TF1* func = new TF1("func","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x",0.0,0.9);
      eff_preselection[isyst]->Fit(func,"MER");
      float a=func->GetParameter(0);
      float b=func->GetParameter(1);
      float c=func->GetParameter(2);
      float d=func->GetParameter(3);
      float e=func->GetParameter(4);
      
      for(int j=0; j<40; j++) {
        int abs_value_costheta_bin = int(fabs(h_AFBreco_pqcorrected[icat][isyst]->GetBinCenter(j+1)*100./5));
        float eff_pres_=eff_preselection[isyst]->GetBinContent(abs_value_costheta_bin+1);
        if(isyst==(nsyst-1))  {
          float x=eff_preselection[isyst]->GetBinCenter(abs_value_costheta_bin+1);
          eff_pres_=a+x*b+x*x*c+x*x*x*d+x*x*x*x*e;
        }
        if(eff_pres_>0) 	{
          h_AFBreco_pqcorrected_efftotalcorrected[icat][isyst]->SetBinContent(j+1, h_AFBreco_pqcorrected_effcorrected[icat][isyst]->GetBinContent(j+1)/eff_pres_);
          h_AFBreco_chargecheat_efftotalcorrected[icat][isyst]->SetBinContent(j+1, h_AFBreco_chargecheat_effcorrected[icat][isyst]->GetBinContent(j+1)/eff_pres_);
        }
	
      }
    
      
      h_AFBreco[icat][isyst]->Write();
      h_AFBreco_pqcorrected[icat][isyst]->Write();
      h_AFBreco_chargecheat[icat][isyst]->Write();
      h_AFBreco_pqcorrected_effcorrected[icat][isyst]->Write();
      h_AFBreco_chargecheat_effcorrected[icat][isyst]->Write();
      h_AFBreco_pqcorrected_efftotalcorrected[icat][isyst]->Write();
      h_AFBreco_chargecheat_efftotalcorrected[icat][isyst]->Write();
    }
  }

}



void QQbarAnalysisClass::AFBreconstruction2(int n_entries=-1, float Kvcut=35, int quark=4, TString polString="eL_pR", int method=0, int bkg=0)
{
  //simplistic function to produce suitable distributions for plotting the S/B

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

  //methods 0=Kc, 1=KcCheatdEdx, 2=KcCheatdEdxTOF, 3=KcCheatTOF, 4=Vtx
  TString method_string[4]={"","CheatdEdx","CheatdEdxTOF","CheatTOF"};

  int nsyst=22;


  //variations for systematics
    
  //**************

  //new file
   TString filename=TString::Format("SigBkg_quark%i_%s_250GeV_cheatmethod_%i.root",quark,process.Data(),method);
  
  TFile *MyFile = new TFile(filename,"RECREATE");
  MyFile->cd();

  TH1F *h_AFBreco_cat0[4];
  TH1F *h_AFBreco_cat1[4];
  TH1F *h_AFBreco_cat2[4];

  for(int j=0; j<4; j++) {
    h_AFBreco_cat0[j] = new TH1F(TString::Format("h_AFBreco_cat0_%i",j),TString::Format("h_AFBreco_cat0_%i",j),20,0,1.0);
    h_AFBreco_cat1[j] = new TH1F(TString::Format("h_AFBreco_cat1_%i",j),TString::Format("h_AFBreco_cat1_%i",j),20,0,1.0);
    h_AFBreco_cat2[j] = new TH1F(TString::Format("h_AFBreco_cat2_%i",j),TString::Format("h_AFBreco_cat2_%i",j),20,0,1.0);
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

    TVector3 v1(mc_quark_ps_jet_px[0],mc_quark_ps_jet_py[0],mc_quark_ps_jet_pz[0]);
    TVector3 v2(mc_quark_ps_jet_px[1],mc_quark_ps_jet_py[1],mc_quark_ps_jet_pz[1]);
    float acol=GetSinacol(v1,v2);

    int iquark=-1;
    if(bkg==0) {
      if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut && acol<0.3) iquark=0;
      if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut && acol<0.3) iquark=1;
      if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut && acol<0.3) iquark=2;
      if(gamma_e>Kvcut || acol>0.3) iquark=3;
    } else {
      iquark=0;
    }

    //reconsturcet thrust angle
    // float costheta_thrust;
    // std::vector<float> p_thrust;
    // p_thrust.push_back(principle_thrust_axis[0]);
    // p_thrust.push_back(principle_thrust_axis[1]);
    // p_thrust.push_back(principle_thrust_axis[2]);
    // costheta_thrust=fabs(GetCostheta(p_thrust));

    //jet direction
    std::vector<float> p;
    p.push_back(jet_px[0]-jet_px[1]);
    p.push_back(jet_py[0]-jet_py[1]);
    p.push_back(jet_pz[0]-jet_pz[1]);
    float costheta_jet=GetCostheta(p);
    //-- jet direction using charged pfos
    std::vector<float> p1;
    std::vector<float> p2;
    float px_pfos[2]={0};
    float py_pfos[2]={0};
    float pz_pfos[2]={0};
    for(int ipfo=0; ipfo<pfo_n; ipfo++) {
      if((pfo_match[ipfo]==0 || pfo_match[ipfo]==1) && pfo_charge[ipfo]!=0 && pfo_ntracks[ipfo]==1) {
        px_pfos[pfo_match[ipfo]]+=pfo_px[ipfo];
        py_pfos[pfo_match[ipfo]]+=pfo_py[ipfo];
        pz_pfos[pfo_match[ipfo]]+=pfo_pz[ipfo];
      }
    }
    p1.push_back(px_pfos[0]-px_pfos[1]);
    p1.push_back(py_pfos[0]-py_pfos[1]);
    p1.push_back(pz_pfos[0]-pz_pfos[1]);
    float costheta=GetCostheta(p1);


    if ( jentry > 1000 && jentry % 1000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco level distributions
    //    float Kv=Kreco();
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

   
    float charge[2][2]={0};
    for(int ijet=0; ijet<2; ijet++) {
      if(quark==5) {
        // charge[ijet][0]=-ChargeVtxJet(0,ijet,pcut);
        // if(method==0) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
        // if(method==1) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
        // if(method==2) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
        // if(method==3) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
        charge[ijet][0]=-ChargeVtxJet(0,ijet,pcut);
        if(method==0) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,false);
        if(method==1) charge[ijet][1]=ChargeKJet(0,ijet,pcut,true,false);
        if(method==2) charge[ijet][1]=ChargeKJet(0,ijet,pcut,true,true);
        if(method==3) charge[ijet][1]=ChargeKJet(0,ijet,pcut,false,true);
      }
      if(quark==4) {
        charge[ijet][1]=ChargeVtxJet(0,ijet,pcut);
        // if(method==0) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        // if(method==1) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        // if(method==2) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        // if(method==3) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        if(method==0) charge[ijet][0]=ChargeKJet(0,ijet,pcut,false,false);
        if(method==1) charge[ijet][0]=ChargeKJet(0,ijet,pcut,true,false);//true,false);
        if(method==2) charge[ijet][0]=ChargeKJet(0,ijet,pcut,true,false);//true,true);
        if(method==3) charge[ijet][0]=ChargeKJet(0,ijet,pcut,true,false);//false,true);
      }
    }

    //cat0
    if(charge[0][0]!=0 && charge[1][0]!=0 && charge[0][0]*charge[1][0]<0) 
      h_AFBreco_cat0[iquark]->Fill(fabs(costheta));
    
    if( charge[0][0]!=0 && charge[1][0]==0 && charge[0][0]*charge[1][1]<0 && charge[1][1]!=0) 
      h_AFBreco_cat1[iquark]->Fill(fabs(costheta));
    if( charge[0][0]==0 && charge[1][0]!=0 && charge[0][1]*charge[1][0]<0 && charge[0][1]!=0) 
      h_AFBreco_cat1[iquark]->Fill(fabs(costheta));

    if( charge[0][0]==0 && charge[1][0]==0 && charge[0][1]*charge[1][1]<0 && charge[0][1]!=0 && charge[1][1]!=0) 
      h_AFBreco_cat2[iquark]->Fill(fabs(costheta));

  }
    

  MyFile->cd();
 
  for(int icat=0; icat<4; icat++) {
    h_AFBreco_cat0[icat]->Write();
    h_AFBreco_cat1[icat]->Write();
    h_AFBreco_cat2[icat]->Write();
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

    if(tof==false && momentum<pcut) continue;
    if(tof==true && momentum<pcut && fabs(pfo_pdgcheat[ipfo])==321) {
      charge-=pfo_charge[ipfo];
      continue;
    }
    bool nhits_bool=false;
    if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
    if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
    if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

    if(nhits_bool==true && cheat==true && fabs(pfo_pdgcheat[ipfo])==321 && momentum>pcut) {
      charge-=pfo_charge[ipfo];
      continue;
    }

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

    if(tof==false && momentum<pcut) continue;
    if(tof==true && momentum<pcut && fabs(pfo_pdgcheat[ipfo])==321) {
      charge-=pfo_charge[ipfo]*momentum;
      continue;
    }
    bool nhits_bool=false;
    if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
    if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
    if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

    if(nhits_bool==true && cheat==true && fabs(pfo_pdgcheat[ipfo])==321 && momentum>pcut) {
      charge-=pfo_charge[ipfo]*momentum;
      continue;
    }

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
  
    bool nhits_bool=false;
    if(fabs(costheta)<0.75 && pfo_tpc_hits[ipfo]>210) nhits_bool=true;
    if(fabs(costheta)>0.75 && pfo_tpc_hits[ipfo]> (210 + (210-50)*(fabs(costheta)-0.75)/(0.75-0.9)) ) nhits_bool=true;
    if(fabs(costheta)>0.9 && pfo_tpc_hits[ipfo]>50) nhits_bool=true;

    if(nhits_bool==true && cheat==true && fabs(pfo_pdgcheat[ipfo])==321 && momentum>pcut) {
      if(momentum>mom_max_cheat) {
	ipfo_max_cheat=ipfo;
	mom_max_cheat=momentum;
      }
    }

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
