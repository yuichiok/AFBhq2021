#include "Rq.C"

TString energy="250GeV";

void pq_weigths_tagging( int quark=4, int pol=0, float lum=-1) {

  TFile *MyFile = new TFile(TString::Format("pq_pdg%i_pol%i.root",quark,pol),"RECREATE");


  //P-Q factors
  TString chargemethod_string[5]={"KcCheatTOF","KcCheatdEdxTOF","KcCheatdEdx","Vtx","Kc"};
  for(int j=0; j<4; j++) {
    int error_bkg=0;//percent
    if(j==1) error_bkg=1;
    if(j==2) error_bkg=5;//1%
    if(j==3) error_bkg=10;//1%

    for(int i=0; i<5; i++) {
      int jhisto=0;
      if(quark==4) jhisto=1;
     if(j>0) {
      TH1F *hacc=N_PQ_HistoBKG(TString::Format("Nacc_%s",chargemethod_string[i].Data()),pol,quark,lum,float(error_bkg/100.));
      TH1F *hrej=N_PQ_HistoBKG(TString::Format("Nrej_%s",chargemethod_string[i].Data()),pol,quark,lum,float(error_bkg/100.));			     
      TH1F * purity=PurityHist(hacc,hrej);
      purity->SetName(TString::Format("purity_%s_bkg_p%i",chargemethod_string[i].Data(),error_bkg));
      MyFile->cd();
      purity->Write();

      TH1F *hacc2=N_PQ_HistoBKG(TString::Format("Nacc_%s",chargemethod_string[i].Data()),pol,quark,lum,-float(error_bkg/100.));
      TH1F *hrej2=N_PQ_HistoBKG(TString::Format("Nrej_%s",chargemethod_string[i].Data()),pol,quark,lum,-float(error_bkg/100.));			     
      TH1F * purity2=PurityHist(hacc2,hrej2);
      purity2->SetName(TString::Format("purity_%s_bkg_m%i",chargemethod_string[i].Data(),error_bkg));
      MyFile->cd();
      purity2->Write();
     } else {
       TH1F *hacc=N_PQ_HistoBKG(TString::Format("Nacc_%s",chargemethod_string[i].Data()),pol,quark,lum,0);
       TH1F *hrej=N_PQ_HistoBKG(TString::Format("Nrej_%s",chargemethod_string[i].Data()),pol,quark,lum,0);			     
       TH1F * purity=PurityHist(hacc,hrej);
       purity->SetName(TString::Format("purity_%s",chargemethod_string[i].Data()));
       MyFile->cd();
       purity->Write();
     }
    }//methods
  }//error
  
  MyFile->Close();

}

void weigths_tagging( int quark=4, int pol=0, float lum=-1) {

  TFile *MyFile = new TFile(TString::Format("eff_weights_pdg%i_pol%i.root",quark,pol),"RECREATE");

  // PRESELECTION
  for(int i=0; i<5; i++) {
    int error_bkg=0;//percent
    if(i==1) error_bkg=1;
    if(i==2) error_bkg=2;//1%
    if(i==3) error_bkg=5;//5%
    if(i==4) error_bkg=10;//10%
    
    if(i>0) {
      TH1F* eff_preselection=N0HistoBKG(pol, quark,  lum, float(error_bkg/100.));
      MyFile->cd();
      eff_preselection->SetName(TString::Format("eff_pres_bkg_p%i",error_bkg));
      eff_preselection->Write();
      TH1F* eff_preselection2=N0HistoBKG(pol, quark,  lum, -float(error_bkg/100.));
      MyFile->cd();
      eff_preselection2->SetName(TString::Format("eff_pres_bkg_m%i",error_bkg));
      eff_preselection2->Write();
    } else {
      TH1F* eff_preselection=N0HistoBKG(pol, quark,  lum, float(error_bkg/100.));
      MyFile->cd();
      eff_preselection->SetName("eff_pres");
      eff_preselection->Write();
    }
  }
  

  //R theory
  double d_Rparton[3];
  int quark_parton0=5;
  int quark_parton1=4;
  if(quark==5) {
    quark_parton0=4;
    quark_parton1=5;
  }
  cout<<"1"<<endl;
  d_Rparton[0]=RParton_value(pol, quark_parton0, -1);
  d_Rparton[1]=RParton_value(pol, quark_parton1, -1);
  d_Rparton[2]=RParton_value(pol, 3, -1);

  cout<<"2"<<endl;
  //F fractions
  TH1F *h_Fhisto[2];
  h_Fhisto[0]=FHisto(pol, 1, quark, lum);
  h_Fhisto[1]=FHisto(pol, 2, quark, lum);
  
  cout<<"3"<<endl;
  //MC mistagging efficiencies
  TH1F *h_mistag_b= epsilon_mistag(pol, quark, quark_parton0,-1);
  cout<<"3.1"<<endl;
  TH1F *h_mistag_b_truth= epsilon_mistag_truth(pol, quark, quark_parton0,-1);
  cout<<"3.2"<<endl;
  TH1F *h_mistag_uds= epsilon_mistag(pol, quark, 3,-1);
  cout<<"3.3"<<endl;
  TH1F *h_mistag_uds_truth= epsilon_mistag_truth(pol, quark, 3,-1);
  cout<<"3.4"<<endl;

  cout<<"4"<<endl;
  //varying the mistagging efficiencies up and down by relative 5% unc
  TH1F *h_Fhisto_effheavy_p5[2];
  h_Fhisto_effheavy_p5[0]=FHistoEffErr(pol, 1, quark, lum,0.05);
  h_Fhisto_effheavy_p5[1]=FHistoEffErr(pol, 2, quark, lum,0.05);
  TH1F *h_Fhisto_effheavy_m5[2];
  h_Fhisto_effheavy_m5[0]=FHistoEffErr(pol, 1, quark, lum,-0.05);
  h_Fhisto_effheavy_m5[1]=FHistoEffErr(pol, 2, quark, lum,-0.05);
  TH1F *h_Fhisto_effuds_p5[2];
  h_Fhisto_effuds_p5[0]=FHistoEffErr(pol, 1, quark, lum,0.,0.05);
  h_Fhisto_effuds_p5[1]=FHistoEffErr(pol, 2, quark, lum,0.,0.05);
  TH1F *h_Fhisto_effuds_m5[2];
  h_Fhisto_effuds_m5[0]=FHistoEffErr(pol, 1, quark, lum,0.,-0.05);
  h_Fhisto_effuds_m5[1]=FHistoEffErr(pol, 2, quark, lum,0.,-0.05);
  //varying the mistagging efficiencies up and down by relative 1% unc
  TH1F *h_Fhisto_effheavy_p1[2];
  h_Fhisto_effheavy_p1[0]=FHistoEffErr(pol, 1, quark, lum,0.01);
  h_Fhisto_effheavy_p1[1]=FHistoEffErr(pol, 2, quark, lum,0.01);
  TH1F *h_Fhisto_effheavy_m1[2];
  h_Fhisto_effheavy_m1[0]=FHistoEffErr(pol, 1, quark, lum,-0.01);
  h_Fhisto_effheavy_m1[1]=FHistoEffErr(pol, 2, quark, lum,-0.01);
  TH1F *h_Fhisto_effuds_p1[2];
  h_Fhisto_effuds_p1[0]=FHistoEffErr(pol, 1, quark, lum,0.,0.01);
  h_Fhisto_effuds_p1[1]=FHistoEffErr(pol, 2, quark, lum,0.,0.01);
  TH1F *h_Fhisto_effuds_m1[2];
  h_Fhisto_effuds_m1[0]=FHistoEffErr(pol, 1, quark, lum,0.,-0.01);
  h_Fhisto_effuds_m1[1]=FHistoEffErr(pol, 2, quark, lum,0.,-0.01);
  
  cout<<"5"<<endl;
  //MC eff quark calculation
  TH1F *eff_MC;
  eff_MC=DTeff_cheat(1,pol,quark,-1).first;
  TH1F *rho_MC;
  rho_MC=DTeff_cheat(1,pol,quark,-1).second;
  
  //double tag eff quark estimation
  //default tagging efficiency
  TH1F* h_eff_quark_onlystats = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  //including rho errors (assuming no knowledge of rho)
  TH1F* h_eff_quark_rho = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC);
  //assuming uncertainties on theory Rb
  TH1F* h_eff_quark_Rbup1 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1+0.01), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC,true);
  TH1F* h_eff_quark_Rbdown1 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1-0.01), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b,h_mistag_uds, rho_MC,true);
  TH1F* h_eff_quark_Rbup5 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1+0.05), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_Rbdown5 = epsilon_tag(d_Rparton[1], d_Rparton[0]*(1-0.05), h_Fhisto[0] , h_Fhisto[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  //mistagging efficiencies 5%
  TH1F* h_eff_quark_heavy_p5= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effheavy_p5[0] , h_Fhisto_effheavy_p5[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_uds_p5= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effuds_p5[0] , h_Fhisto_effuds_p5[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_heavy_m5= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effheavy_m5[0] , h_Fhisto_effheavy_m5[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_uds_m5= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effuds_m5[0] , h_Fhisto_effuds_m5[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  //mistagging efficiencies 1%
  TH1F* h_eff_quark_heavy_p1= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effheavy_p1[0] , h_Fhisto_effheavy_p1[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_uds_p1= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effuds_p1[0] , h_Fhisto_effuds_p1[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_heavy_m1= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effheavy_m1[0] , h_Fhisto_effuds_m1[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
  TH1F* h_eff_quark_uds_m1= epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_effuds_m1[0] , h_Fhisto_effuds_m1[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);

  //
  MyFile->cd();
  // h_mistag_b->SetName("mistag_b");
  // h_mistag_uds->SetName("mistag_uds");
  rho_MC->SetName("rho");
  h_eff_quark_onlystats->SetName("eff_tagging");
  h_eff_quark_rho->SetName("eff_tagging_rho");
  h_eff_quark_Rbup1->SetName("eff_tagging_Rbup1");
  h_eff_quark_Rbdown1->SetName("eff_tagging_Rbdown1");
  h_eff_quark_Rbup5->SetName("eff_tagging_Rbup5");
  h_eff_quark_Rbdown5->SetName("eff_tagging_Rbdown5");
  h_eff_quark_heavy_p5->SetName("eff_tagging_heavy_p5");
  h_eff_quark_uds_p5->SetName("eff_tagging_uds_p5");
  h_eff_quark_heavy_m5->SetName("eff_tagging_heavy_m5");
  h_eff_quark_uds_m5->SetName("eff_tagging_uds_m5");
  h_eff_quark_heavy_p1->SetName("eff_tagging_heavy_p1");
  h_eff_quark_uds_p1->SetName("eff_tagging_uds_p1");
  h_eff_quark_heavy_m1->SetName("eff_tagging_heavy_m1");
  h_eff_quark_uds_m1->SetName("eff_tagging_uds_m1");
  //
  // h_mistag_b->Write();
  // h_mistag_uds->Write();
  rho_MC->Write();
  h_eff_quark_onlystats->Write();
  h_eff_quark_rho->Write();
  h_eff_quark_Rbup1->Write();
  h_eff_quark_Rbdown1->Write();
  h_eff_quark_Rbup5->Write();
  h_eff_quark_Rbdown5->Write();
  h_eff_quark_heavy_p5->Write();
  h_eff_quark_uds_p5->Write();
  h_eff_quark_heavy_m5->Write();
  h_eff_quark_uds_m5->Write();
  h_eff_quark_heavy_p1->Write();
  h_eff_quark_uds_p1->Write();
  h_eff_quark_heavy_m1->Write();
  h_eff_quark_uds_m1->Write();


  // BKG VARIATIONS
  for(int i=1; i<5; i++) {
    int error_bkg=0;//percent
    if(i==1) error_bkg=1;
    if(i==2) error_bkg=2;//1%
    if(i==3) error_bkg=5;//5%
    if(i==4) error_bkg=10;//10%

    // for(int isign=-1; isign<2; isign++) {
    //F fractions
    TH1F *h_Fhisto_bkg[2];
    h_Fhisto_bkg[0]=FHistoBKG(pol, 1, quark, lum,float(error_bkg/100.));
    h_Fhisto_bkg[1]=FHistoBKG(pol, 2, quark, lum,float(error_bkg/100.));
    
    //double tag eff quark estimation
    TH1F* h_eff_quark_bkg = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_bkg[0] , h_Fhisto_bkg[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
    h_eff_quark_bkg->SetName(TString::Format("eff_tagging_bkg_p%i",error_bkg));
    MyFile->cd();
    h_eff_quark_bkg->Write();

    TH1F *h_Fhisto_bkg2[2];
    h_Fhisto_bkg2[0]=FHistoBKG(pol, 1, quark, lum,-float(error_bkg/100.));
    h_Fhisto_bkg2[1]=FHistoBKG(pol, 2, quark, lum,-float(error_bkg/100.));
    
    //double tag eff quark estimation
    TH1F* h_eff_quark_bkg2 = epsilon_tag(d_Rparton[1], d_Rparton[0], h_Fhisto_bkg2[0] , h_Fhisto_bkg2[1] , h_mistag_b_truth,h_mistag_uds_truth, rho_MC,true);
    h_eff_quark_bkg2->SetName(TString::Format("eff_tagging_bkg_m%i",error_bkg));
    MyFile->cd();
    h_eff_quark_bkg2->Write();
    
  }


  MyFile->Close();
  
}


void weigths_charge( int quark=4, int pol=0, float lum=-1, int lastit=4) {

  TString chargemethod_string[5]={"KcCheatTOF","KcCheatdEdxTOF","KcCheatdEdx","Vtx","Kc"};

  for(int imethod=lastit-1; imethod<lastit; imethod++) {
    TString filemode="RECREATE";
    if(imethod>0) filemode="UPDATE";
    TFile *MyFile = new TFile(TString::Format("chargeeff_weights_pdg%i_pol%i.root",quark,pol),filemode);
    TH1F* eff_charge=FHistoChargeBKG(chargemethod_string[imethod],pol, 1,quark,  lum,0);

    MyFile->cd();
    eff_charge->SetName(TString::Format("eff_charge_%s",chargemethod_string[imethod].Data()));
    eff_charge->Write();
      for(int i=1; i<5; i++) {

   
	int error_bkg=0;//percent
	if(i==1) error_bkg=1;
	if(i==2) error_bkg=2;//1%
	if(i==3) error_bkg=5;//5%
	if(i==4) error_bkg=10;//10%
	
	TH1F* eff_charge2=FHistoChargeBKG(chargemethod_string[imethod],pol, 1,quark,  lum,float(error_bkg/100.));
	MyFile->cd();
	eff_charge2->SetName(TString::Format("eff_charge_%s_bkg_p%i",chargemethod_string[imethod].Data(),error_bkg));
	eff_charge2->Write();

	TH1F* eff_charge2_bis=FHistoChargeBKG(chargemethod_string[imethod],pol, 2,quark,  lum,float(error_bkg/100.));
	eff_charge2_bis->Divide(eff_charge2);
	eff_charge2_bis->Divide(eff_charge2);
	MyFile->cd();
	eff_charge2_bis->SetName(TString::Format("rho_charge_%s_bkg_p%i",chargemethod_string[imethod].Data(),error_bkg));
	eff_charge2_bis->Write();
	
	TH1F* eff_charge3=FHistoChargeBKG(chargemethod_string[imethod],pol, 1,quark,  lum,-float(error_bkg/100.));
	MyFile->cd();
	eff_charge3->SetName(TString::Format("eff_charge_%s_bkg_m%i",chargemethod_string[imethod].Data(),error_bkg));
	eff_charge3->Write();

      }
      MyFile->Close();
  }
  
  
}



void Weights_c(int pol=2, int quark=4, int type=2, int otherparam=5) {

  folder="../results_"+energy+"/AFB_PQ_";

  cout<<"  ------------------------------------------ "<<endl;
  if(type==1) pq_weigths_tagging(quark,pol,900);
  if(type==0) weigths_tagging(quark,pol,900);
  if(type==2) weigths_charge(quark,pol,900,otherparam);
}

