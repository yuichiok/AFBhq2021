#include "fit.C"

void AFBplots( int pol=0, float lum=-1, int quark=4) {

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);

  TString chargemethod_string[4]={"K-method","K_{cheat-dEdx}-method","K_{cheat-dEdx&TOF}-method","Vtx-method"};

  TString method_string[3]={"Default","Averaged","Leading"};
  
  for(int i=0; i<4; i++) {

    TCanvas* c_f1_MC = new TCanvas("Purity-"+chargemethod_string[i],"Purity-"+chargemethod_string[i],800,800);
    c_f1_MC->cd(1);
    c_f1_MC->SetGrid();

    TH1F *corrected[3];
    TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);
    leg->SetHeader(chargemethod_string[i]);

    for(int j=0; j<1;j++) {
      TH1F *hacc=GetHisto(4,TString::Format("h_Nacc_%i",i),pol,j,lum,1,quark);
      TH1F *hrej=GetHisto(4,TString::Format("h_Nrej_%i",i),pol,j,lum,1,quark);

      //  corrected[j] = MakeCorrection(hacc,hrej);
      corrected[j]=GetHisto(3,"h_AFB",pol,j,lum,1,quark);

      if(j==0) {
	corrected[j]->GetXaxis()->SetTitle("cos #theta_{thr.}");
	corrected[j]->GetYaxis()->SetTitle("Entries");
	//	corrected[j]->GetYaxis()->SetRangeUser(0,1);
      }
      
      corrected[j]->SetLineColor(j+1);
      corrected[j]->SetLineWidth(j+1);
      corrected[j]->SetMarkerColor(j+1);
      corrected[j]->SetMarkerStyle(20+j);
      
      corrected[j]->Draw("histoesame");
      leg->AddEntry(corrected[j],method_string[j],"lpe");

      c_f1_MC->Update();

      TF1 * fitresult3 = fit_histo(corrected[j],-0.9,0.9);

      
      Labels(pol,quark,lum);
    }
    
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->Draw();
    //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
  }
  
}


void AFB2() {


  for(int pol=3; pol<4; pol++) {
    AFBplots(pol,900*0.03,4);
  }
}
