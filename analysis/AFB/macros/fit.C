#include "AFB.C"

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
