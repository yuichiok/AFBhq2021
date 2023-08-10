#include "AFB.C"


Double_t asymmetry_plotting(Double_t *x, Double_t *par)
{

  Double_t fitval = par[0]+par[1]*x[0]+par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0] + par[4]*x[0]*x[0]*x[0]*x[0];
  return fitval;
}



Double_t asymmetry_f(Double_t *x, Double_t *par)
{
  
  Double_t fitval = par[0]*(1+x[0]*x[0]) + par[1]*x[0];
  return fitval;
}

float Afb_v(float plus, float minus) {
  if(plus>0 && minus>0) 
    return (plus-minus)/(plus+minus);
  else return 0;

}

float dAfb_v(float plus, float minus, float plus_e, float minus_e) {
  
  if(plus>0 && minus>0) 
    return 2 / ((plus+minus)*(plus+minus)) * sqrt(plus*plus*plus_e*plus_e + minus*minus*minus_e*minus_e);
  else return 0;

}



TF1 * fit_histo(TH1F * histo, float range_down=-0.8, float range_up=0.8, bool draw=false) {

double x[40], ex[40], y[40], ey[40];
for(int i=0; i<40; i++) {
  x[i]=0;
  ex[i]=0;
  y[i]=0;
  ey[i]=0;
  x[i]=histo->GetBinCenter(i+1);

  y[i]=histo->GetBinContent(i+1);
  ey[i]=histo->GetBinError(i+1);
 }

TGraphErrors * g_histo = new TGraphErrors(40,x,y,ex,ey);

TF1 *func_fit = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
func_fit->SetParNames("S","A");

TFitResultPtr r = g_histo->Fit("asymmetry_f", "QRS");
// r->Print("V");                                                                                                                                                                                        

if(draw==true)   g_histo->Draw("alp");
TF1 *func = new TF1("asymmetry_f",asymmetry_f,-1,1,2);
func->SetParNames("S","A");
func->SetParameter(0,func_fit->GetParameter(0));
func->SetParameter(1,func_fit->GetParameter(1));
func->SetParError(0,func_fit->GetParError(0));
func->SetParError(1,func_fit->GetParError(1));

// results                                                                                                                                                                                               

float plus = func->Integral(0,1);
float minus = func->Integral(-1,0);
float plus_e = func->IntegralError(0,1);
float minus_e = func->IntegralError(1,0);


float Afb=Afb_v(plus,minus);
float dAfb=dAfb_v(plus,minus, plus_e, minus_e);

cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
float S=func_fit->GetParameter(0);
float dS=func_fit->GetParError(0);
cout << "S/bin_size = "<< S*2./40<< " +- " << dS*2./40 << "  ( "<<100.*dS/S<<" %)"<< endl;
float A=func_fit->GetParameter(1);
float dA=func_fit->GetParError(1);
cout << "A/bin_size = "<< A*2./40<< " +- " << dA*2./40 << "  ( "<<100.*dA/A<<" %)"<< endl;
cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;


TF1 *func_return = new TF1("asymmetry_f",asymmetry_f,range_down,range_up,2);
func_return->SetParNames("S","A");
func_return->SetParameter(0,func_fit->GetParameter(0));
func_return->SetParameter(1,func_fit->GetParameter(1));
func_return->SetParError(0,func_fit->GetParError(0));
func_return->SetParError(1,func_fit->GetParError(1));
return func_return;


}


TF1 * fit_histo2(TH1F * histo, float range_down=-0.8, float range_up=0.8, bool draw=false) {

  double x[40], ex[40], y[40], ey[40];
  for(int i=0; i<40; i++) {
    x[i]=0;
    ex[i]=0;
    y[i]=0;
    ey[i]=0;
    x[i]=histo->GetBinCenter(i+1);

    y[i]=histo->GetBinContent(i+1);
    ey[i]=histo->GetBinError(i+1);
  }
 
  TGraphErrors * g_histo = new TGraphErrors(40,x,y,ex,ey);

  TF1 *func_fit = new TF1("asymmetry_plotting",asymmetry_plotting,range_down,range_up,5);
  func_fit->SetParNames("S","A");
 
  TFitResultPtr r = g_histo->Fit("asymmetry_plotting", "QRS");
  // r->Print("V");

  if(draw==true)   g_histo->Draw("alp");
  TF1 *func = new TF1("asymmetry_plotting",asymmetry_plotting,-1,1,5);
  for(int i=0; i<5; i++ ) {
    func->SetParameter(i,func_fit->GetParameter(i));
    func->SetParError(i,func_fit->GetParError(i));
  }

  // results

  float plus = func->Integral(0,1);
  float minus = func->Integral(-1,0);
  float plus_e = func->IntegralError(0,1);
  float minus_e = func->IntegralError(1,0);
  

  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);
 
  cout << "Afb = "<< Afb<< " +- " << dAfb << "  ( "<<100.*dAfb/Afb<<" %)"<< endl;
  cout << "Correl = "<<r->GetCorrelationMatrix()[0][1]<< endl;
  cout << "Chi2 = "<<func_fit->GetChisquare()<<", NDF ="<<func_fit->GetNDF()<<" Chi2/NDF= "<<func_fit->GetChisquare()/func_fit->GetNDF()<<endl;


  TF1 *func_return = new TF1("asymmetry_plotting",asymmetry_plotting,range_down,range_up,5);
  func_return->SetParNames("a","b","c","d","e");
  for(int i=0; i<5; i++ ) {
    func_return->SetParameter(i,func_fit->GetParameter(i));
    func_return->SetParError(i,func_fit->GetParError(i));
  }
  return func_return;


}



std::vector<double> fit_histo_value(TH1F * histo, TH1F * histo_eR, float range_down=-0.8, float range_up=0.8, bool draw=false,int pol=0) {

  //  if(pol==0) histo_eR->Scale(0.);
  // if(pol==1) histo->Scale(0.);

  TH1F * h = (TH1F*)histo->Clone("h");
  TH1F * h_eR = (TH1F*)histo_eR->Clone("h_eR");

  if(pol==2) {
    h->Scale(0.58);
    h_eR->Scale(0.035);
  }
  if(pol==3) {
    h_eR->Scale(0.58);
    h->Scale(0.035);
  }
  
  TF1 *func;
  if(pol==0) func=fit_histo(h, range_down, range_up, draw);
  else if(pol==1) func=fit_histo(h_eR, range_down, range_up, draw);
  else {
    if(pol==2) {
      h->Add(h_eR);
      func=fit_histo(h, range_down, range_up, draw);
    }
    if(pol==3) {
      h_eR->Add(h);
      func=fit_histo(h_eR, range_down, range_up, draw);
    }
  }

  delete h;
  delete h_eR;
  
  float plus = func->Integral(0,1);
  float minus = func->Integral(-1,0);
  float plus_e = func->IntegralError(0,1);
  float minus_e = func->IntegralError(1,0);
  

  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);
  std::vector<double>  result;
  result.push_back(Afb);
  result.push_back(dAfb);

  return result;

}


std::vector<double> fit_histo_value(TH1F * histo, float range_down=-0.8, float range_up=0.8, bool draw=false) {

  

  TF1 *func=fit_histo(histo, range_down, range_up, draw);
 
  float plus = func->Integral(0,1);
  float minus = func->Integral(-1,0);
  float plus_e = func->IntegralError(0,1);
  float minus_e = func->IntegralError(1,0);
  

  float Afb=Afb_v(plus,minus);
  float dAfb=dAfb_v(plus,minus, plus_e, minus_e);
  std::vector<double>  result;
  result.push_back(Afb);
  result.push_back(dAfb);

  return result;

}
