#include "utils.h"
#include "histograms.h"

//pol=0 eLpR
//pol=1 eRpL
//pol=2 eLpR 80/30
//pol=3 eRpL 80/30

std::vector<float> CalculateP(TH1F* h_accepted, TH1F *h_rejected)
{

  for(int i=1; i<40/2+1; i++) {
    float accepted = h_accepted->GetBinContent(40+1-i);
    float rejected = h_rejected->GetBinContent(40+1-i);
    accepted += h_accepted->GetBinContent(i);
    float a=1;
    float b=-1;
    float c= rejected/ (2* (accepted+rejected));
    float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
    float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
  }

  std::vector<float> result_error;
  std::vector<float> result;

  for(int i=1; i<40/2+1; i++) {
    std::vector<float> result_j;
    for(int i1=-1; i1<2; i1+=2) {
      for(int i2=-1; i2<2; i2+=2) {
	for(int i3=-1; i3<2; i3+=2) {
	  float accepted = h_accepted->GetBinContent(40+1-i)+i1*sqrt(h_accepted->GetBinContent(40+1-i));
	  float rejected = h_rejected->GetBinContent(40+1-i)+i2*sqrt(h_rejected->GetBinContent(40+1-i));
	  accepted += h_accepted->GetBinContent(i)+i3*sqrt(h_accepted->GetBinContent(i));
	  
	  float a=1;
	  float b=-1;
	  float c= rejected/ (2* (accepted+rejected));
	  float p= (0.5/a) * (-b + sqrt( b*b-4*a*c));
	  float p2= (0.5/a) * (-b - sqrt( b*b-4*a*c));
	  if(p>0.99) p=0;
	  if(p2>0.99) p2=0;
	  if(p>0 || p2>0 ) result_j.push_back(max(p,p2));
	}
      }
    }
    float average=0;
    float n=0;
    for(unsigned j=0; j<result_j.size(); j++) {
      if(result_j.at(j)>0) {
	average+=result_j.at(j);
	n++;
      }
    }
    average/=n;
 
    if(average!=0) {
      result.push_back(average);
      float std_dev=0;
      for(unsigned j=0; j<result_j.size(); j++) {
	if(result_j.at(j)>0) {
	  std_dev+=pow(result_j.at(j)-average,2);
	}
      }
      std_dev=sqrt(std_dev/(n-1));
      result_error.push_back(std_dev);
    } else {
      result_error.push_back(0);
      result.push_back(0);
    }
  }

  for(unsigned i=0; i<result_error.size(); i++) {
    if(result_error.at(i)>0) 
      result.push_back(result_error.at(i));
    else
      result.push_back(0);
  }


  return result;
   
}

TH1F* PurityHist(std::vector<float> p_vect) {

  int n=p_vect.size()/2;
  TH1F * purity = new TH1F("corrected","corrected",n,0,1);
  for(int i=0; i<n; i++) {
    purity->SetBinContent(i+1,p_vect.at(i));
    purity->SetBinError(i+1,p_vect.at(n+i));
  }

  return purity;

}

TH1F* PurityHist(TH1F* h_accepted, TH1F *h_rejected) {

  std::vector<float> p_vect=CalculateP(h_accepted, h_rejected);

  int n=p_vect.size()/2;
  TH1F * purity = new TH1F("corrected","corrected",n,0,1);
  for(int i=0; i<n; i++) {
    purity->SetBinContent(n-i,p_vect.at(i));
    purity->SetBinError(n-i,p_vect.at(n+i));
  }

  return purity;

}


TH1F* CorrectHistoDoubleTag(TH1F* histo, std::vector<float> p_vect) {
  

  TH1F * corrected = new TH1F("corrected","corrected",40,-1,1);
  corrected->Sumw2();
  for(int i=1; i<40/2+1; i++) {
    float p=p_vect.at(i-1);
    float q=1-p;
    float weight = (p*p+q*q)/(q*q*q*q-p*p*p*p);
    float nm_reco_error = histo->GetBinContent(i);
    float np_reco_error= histo->GetBinContent(40+1-i);
    corrected->SetBinContent(i, (np_reco_error*q*q-nm_reco_error*p*p)*weight );
    corrected->SetBinContent(40+1-i,-(np_reco_error*p*p-nm_reco_error*q*q)*weight );

    //calcualte average
    float av_i=0;
    float av_41i=0;
    float n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(40+1-i)+i2*histo->GetBinError(40+1-i);
	av_i+= (np_reco_error*q*q-nm_reco_error*p*p)*weight ;
	av_41i+= -(np_reco_error*p*p-nm_reco_error*q*q)*weight ;
	n++;
      }
    }
    av_i/=n;
    av_41i/=n;


    //calculate error
    float error_i=0;
    float error_41i=0;
    n=0;
    for(int i1=-1; i1<2; i1+=1) {
      for(int i2=-1; i2<2; i2+=1) {
	float nm_reco_error = histo->GetBinContent(i)+i1*histo->GetBinError(i);
	float np_reco_error= histo->GetBinContent(40+1-i)+i2*histo->GetBinError(40+1-i);
	error_i+=pow( (np_reco_error*q*q-nm_reco_error*p*p)*weight -av_i ,2);
	error_41i+=pow( -(np_reco_error*p*p-nm_reco_error*q*q)*weight  - av_41i, 2);
	n++;
      }
    }
    error_i=sqrt(error_i/(n-1.));
    error_41i=sqrt(error_41i/(n-1.));
    corrected->SetBinError(i,error_i );
    corrected->SetBinError(40+1-i,error_41i );
  }
  
  return corrected;

}


TH1F* MakeCorrection(TH1F* h_reco, TH1F* h_rejected) {
  
  std::vector<float> p_b_vect=CalculateP(h_reco,h_rejected);
  TH1F * p_b = new TH1F("p","p",40/2,0,1);
  p_b->Sumw2();
  for(unsigned i=0; i<p_b_vect.size()/2; i++) {
    p_b->SetBinContent(40/2-i,p_b_vect.at(i));
    p_b->SetBinError(40/2-i,p_b_vect.at(i+40/2));
  }
  TH1F* result=CorrectHistoDoubleTag(h_reco,p_b_vect);
  return result;
  
}
  



