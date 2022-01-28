#include "AFB.C"
//macros to study the quality andd performance of the different version of charge measurement
//vtx and K with and withou cheat.
// leading particle, or sum, or average...
void ChargePlots( int pol=0, float lum=-1,int quark=4) {

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

  TString method_string[3]={"Default","Weighted","Leading"};
  
  for(int i=0; i<4; i++) {

    TCanvas* c_f1_MC = new TCanvas("Charge-"+chargemethod_string[i],"Charge-"+chargemethod_string[i],800,800);
    c_f1_MC->cd(1);
    c_f1_MC->SetGrid();

    TH1F *charge[3];
    TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);
    leg->SetHeader(chargemethod_string[i]);

    for(int j=0; j<3;j++) {
      charge[j]=GetHistoMethod(3,TString::Format("h_Charge_%i",i),pol,j,lum,1,quark);
     
      if(j==0) {
	charge[j]->GetXaxis()->SetTitle("Q_{jet}");
	charge[j]->GetYaxis()->SetTitle("entries");
	//charge[j]->GetYaxis()->SetRangeUser(0,1);
      }
      
      charge[j]->SetLineColor(j+1);
      charge[j]->SetLineWidth(j+1);
      charge[j]->SetMarkerColor(j+1);
      charge[j]->SetMarkerStyle(20+j);
      
      charge[j]->Draw("histoesame");
      leg->AddEntry(charge[j],method_string[j],"lpe");

      c_f1_MC->Update();
      
      Labels(pol,quark,lum);
    }
    
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->Draw();
    //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
  }
  
}

void PurityPlots( int pol=0, float lum=-1, int quark=4) {

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

  TString method_string[3]={"Default","Weighted","Leading"};
  
  for(int i=0; i<4; i++) {

    TCanvas* c_f1_MC = new TCanvas("Purity-"+chargemethod_string[i],"Purity-"+chargemethod_string[i],800,800);
    c_f1_MC->cd(1);
    c_f1_MC->SetGrid();

    TH1F *purity[3];
    TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);
    leg->SetHeader(chargemethod_string[i]);

    for(int j=0; j<3;j++) {
      TH1F *hacc=GetHistoMethod(3,TString::Format("h_Nacc_%i",i),pol,j,lum,1,quark);
      TH1F *hrej=GetHistoMethod(3,TString::Format("h_Nrej_%i",i),pol,j,lum,1,quark);
      purity [j]= PurityHist(hacc,hrej);
     
      if(j==0) {
	purity[j]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
	purity[j]->GetYaxis()->SetTitle("Purity Jet-Charge");
	purity[j]->GetYaxis()->SetRangeUser(0,1);
      }
      
      purity[j]->SetLineColor(j+1);
      purity[j]->SetLineWidth(j+1);
      purity[j]->SetMarkerColor(j+1);
      purity[j]->SetMarkerStyle(20+j);
      
      purity[j]->Draw("histoesame");
      leg->AddEntry(purity[j],method_string[j],"lpe");

      c_f1_MC->Update();
      
      Labels(pol,quark,lum);
    }
    
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->Draw();
    //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
  }
  
}

void PurityPlots2( int pol=0, float lum=-1, int quark=4) {

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

  TString method_string[5]={"Default","Weighted","Leading","K_{cheat-dEdx}","K_{cheat-dEdx&TOF}"};
  
  int i=0;

  TCanvas* c_f1_MC = new TCanvas("Purity-"+chargemethod_string[i],"Purity-"+chargemethod_string[i],800,800);
  c_f1_MC->cd(1);
  c_f1_MC->SetGrid();

  TH1F *purity[5];
  TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);
  leg->SetHeader(chargemethod_string[i]);
  
  for(int j=0; j<3;j++) {
    TH1F *hacc=GetHistoMethod(3,TString::Format("h_Nacc_%i",i),pol,j,lum,1,quark);
    TH1F *hrej=GetHistoMethod(3,TString::Format("h_Nrej_%i",i),pol,j,lum,1,quark);
    purity [j]= PurityHist(hacc,hrej);
  }
  i=2;
  TH1F *hacc=GetHistoMethod(3,TString::Format("h_Nacc_%i",i),pol,0,lum,1,quark);
  TH1F *hrej=GetHistoMethod(3,TString::Format("h_Nrej_%i",i),pol,0,lum,1,quark);
  purity [3]= PurityHist(hacc,hrej);
  i=1;
  TH1F *hacc2=GetHistoMethod(3,TString::Format("h_Nacc_%i",i),pol,0,lum,1,quark);
  TH1F *hrej2=GetHistoMethod(3,TString::Format("h_Nrej_%i",i),pol,0,lum,1,quark);
  purity [4]= PurityHist(hacc2,hrej2);
  

  for(int j=0; j<5;j++) {
    if(j==0) {
      purity[j]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
      purity[j]->GetYaxis()->SetTitle("Purity Jet-Charge");
	purity[j]->GetYaxis()->SetRangeUser(0,1);
      }
      
      purity[j]->SetLineColor(j+1);
      purity[j]->SetLineWidth(j+1);
      purity[j]->SetMarkerColor(j+1);
      purity[j]->SetMarkerStyle(20+j);

      purity[j]->Draw("histoesame");
      leg->AddEntry(purity[j],method_string[j],"lpe");

      c_f1_MC->Update();
      
      Labels(pol,quark,lum);
    }
    
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->Draw();
    //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
}
  



void EffPlots( int pol=0, float lum=-1, int quark=4) {

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

  TString method_string[3]={"Default","Weighted","Leading"};
  
  for(int i=0; i<4; i++) {

    TCanvas* c_f1_MC = new TCanvas("Purity-"+chargemethod_string[i],"Purity-"+chargemethod_string[i],800,800);
    c_f1_MC->cd(1);
    c_f1_MC->SetGrid();

    TH1F *eff[3];
    TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);
    leg->SetHeader(chargemethod_string[i]);

    for(int j=0; j<3;j++) {
      cout<<quark<<endl;
      eff[j]=GetHistoMethod(3,TString::Format("h_N2c_%i",i),pol,j,lum,1,quark);
      TH1F *h0=GetHistoMethod(3,"h_Nparton",pol,j,lum,1,quark);
      //TH1F *h0=GetHistoMethod(3,TString::Format("h_N0c_%i",i),pol,j,lum,1,quark);
      eff[j]->Divide(h0);
      eff[j]->Scale(100);

      if(j==0) {
	eff[j]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
	eff[j]->GetYaxis()->SetTitle("Final Selection Eff [%]");
	eff[j]->GetYaxis()->SetRangeUser(0,50);
      }
      
      eff[j]->SetLineColor(j+1);
      eff[j]->SetLineWidth(j+1);
      eff[j]->SetMarkerColor(j+1);
      eff[j]->SetMarkerStyle(20+j);
      
      eff[j]->Draw("histoesame");
      leg->AddEntry(eff[j],method_string[j],"lpe");

      c_f1_MC->Update();
      
      Labels(pol,quark,lum);
    }
    
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetShadowColor(0);
    leg->Draw();
    //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
  }
  
}

void EffPlots2( int pol=0, float lum=-1, int quark=4) {

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

  TString method_string[5]={"Default","Weighted","Leading","K_{cheat-dEdx}","K_{cheat-dEdx&TOF}"};
  

  TCanvas* c_f1_MC = new TCanvas("Eff-"+chargemethod_string[0],"Eff-"+chargemethod_string[0],800,800);
  c_f1_MC->cd(1);
  c_f1_MC->SetGrid();
  
  TH1F *eff[5];
  TLegend *leg = new TLegend(0.2,0.3,0.55,0.45);
  leg->SetHeader(chargemethod_string[0]);

  int i=0;
  for(int j=0; j<3;j++) {
    eff[j]=GetHistoMethod(3,TString::Format("h_N2c_%i",i),pol,j,lum,1,quark);
    TH1F *h0=GetHistoMethod(3,"h_Nparton",pol,j,lum,1,quark);
    //TH1F *h0=GetHistoMethod(3,TString::Format("h_N0_%i",i),pol,j,lum,1,quark);
    eff[j]->Divide(h0);
    eff[j]->Scale(100);
  }
  i=1;
  eff[3]=GetHistoMethod(3,TString::Format("h_N2c_%i",i),pol,0,lum,1,quark);
  TH1F *h0=GetHistoMethod(3,"h_Nparton",pol,0,lum,1,quark);
  //TH1F *h0=GetHistoMethod(3,TString::Format("h_N0_%i",i),pol,j,lum,1,quark);
  eff[3]->Divide(h0);
  eff[3]->Scale(100);
  i=2;
  eff[4]=GetHistoMethod(3,TString::Format("h_N2c_%i",i),pol,0,lum,1,quark);
  TH1F *h02=GetHistoMethod(3,"h_Nparton",pol,0,lum,1,quark);
  //TH1F *h0=GetHistoMethod(3,TString::Format("h_N0_%i",i),pol,j,lum,1,quark);
  eff[4]->Divide(h02);
  eff[4]->Scale(100);

  for(int j=0; j<5;j++) {
    
    if(j==0) {
      eff[j]->GetXaxis()->SetTitle("|cos #theta_{thr.}|");
      eff[j]->GetYaxis()->SetTitle("Final Selection Eff [%]");
      eff[j]->GetYaxis()->SetRangeUser(0,20);
    }
    
    eff[j]->SetLineColor(j+1);
    eff[j]->SetLineWidth(j+1);
    eff[j]->SetLineStyle(j+1);
    eff[j]->SetMarkerColor(j+1);
    eff[j]->SetMarkerStyle(20+j);
    
    eff[j]->Draw("histoesame");
    leg->AddEntry(eff[j],method_string[j],"lpe");
    
    c_f1_MC->Update();
    
    Labels(pol,quark,lum);
  }
  
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetShadowColor(0);
  leg->Draw();
  //    c_f1_MC->Print(TString::Format("summaryplots/Rparton_pol_%i.eps",pol));
 
  
}

void AFB1() {

  folder="../results/AFB";
  for(int pol=0; pol<1; pol++) {
    EffPlots2(pol,-1,5);
    PurityPlots2(pol,-1,5);
    ChargePlots(pol,-1,5);
  }
}
