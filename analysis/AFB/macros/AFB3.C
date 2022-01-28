#include "fit.C"


//macros to draw the real AFB distributions, without cuts
void AFBplots( int pol=0, float lum=-1) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  TString chargemethod_string[5]={"KcCheatTOF","KcCheatdEdxTOF","KcCheatdEdx","Vtx","Kc"};

  TCanvas* c_f1_reco = new TCanvas("Reco-nocorrections","Reco-nocorrections",1600,800);
  c_f1_reco->Divide(2,1);
  c_f1_reco->SetGrid();


  for(int quark=4; quark<6; quark++) {
  c_f1_reco->cd(quark-3);

  TH1F *corrected[4];
  //  leg->SetHeader();
  TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);

  for(int i=0; i<5; i++) {

    int jhisto=0;
    if(quark==4) jhisto=1;
    TH1F *hacc=GetHisto(4,TString::Format("h_Nacc_%s_%i",chargemethod_string[i].Data(),jhisto),pol,quark,lum,1);
    TH1F *hrej=GetHisto(4,TString::Format("h_Nrej_%s_%i",chargemethod_string[i].Data(),jhisto),pol,quark,lum,1);
    
      corrected[i] = MakeCorrection(hacc,hrej);
      //corrected[i]=GetHisto(3,"h_AFB",pol,j,lum,1,quark);

      if(i==0) {
	corrected[i]->GetXaxis()->SetTitle("cos #theta_{thr.}");
	corrected[i]->GetYaxis()->SetTitle("Entries");
	//	corrected[i]->GetYaxis()->SetRangeUser(0,1);
      }
      
      corrected[i]->SetLineColor(i+1);
      corrected[i]->SetLineWidth(i+1);
      corrected[i]->SetMarkerColor(i+1);
      corrected[i]->SetMarkerStyle(20+i);
      
      corrected[i]->Draw("histoesame");
      leg->AddEntry(corrected[i],chargemethod_string[i],"lpe");
      
      c_f1_reco->Update();
      
      //TF1 * fitresult3 = fit_histo(corrected[i],-0.9,0.9);

  }      
  Labels(pol,quark,lum);
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetShadowColor(0);
  leg->Draw();
    
  }
    //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
  
  
}


void AFB3() {

  folder="../results/AFB_PQ_";
  for(int pol=2; pol<3; pol++) {
    AFBplots(pol,900);
  }
}
