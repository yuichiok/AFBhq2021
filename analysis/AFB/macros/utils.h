#include "../../../style/Style.C"
#include "../../../style/Labels.C"




void Labels(int ipol, int iquark, int lum, int color=920){
  //QQBARLabel(0.86,0.954," work in progress");
  QQBARLabel(0.86,0.954,"");
  TString quark= "c#bar{c}";
  if(iquark==5) quark="b#bar{b}";
  if(iquark==0) quark="q#bar{q}";
  

  //String pol[]={"e_{L}^{-}e_{R}^{+}","e_{R}^{-}e_{L}^{+}","e_{L,80%}^{-}e_{R,30%}^{+}","e_{R,80%}^{-}e_{L,30%}^{+}","e^{-}e^{+}"};
  TString pol[]={"(-1,+1)","(+1,-1)","(-0.8,+0.3)","(+0.8,-0.3)"};//                  ","e_{R}^{-}e_{L}^{+}","e_{L,80%}^{-}e_{R,30%}^{+}","e_{R,80%}^{-}e_{L,30%}^{+}","e^{-}e^{+}"};

  if(color==920) {
    QQBARLabel2(0.1,0.05, "e^{-}e^{+} #rightarrow "+quark,color+2);
    if(ipol>-1) QQBARLabel2(0.1,0.02, "P_{e^{-}e^{+}}="+pol[ipol]+ TString::Format(" | Lum = %i fb^{-1}",lum),color+1);
    else  if(lum>0) QQBARLabel2(0.1,0.02, TString::Format("Lum = %i fb^{-1}",lum),color+1);
  }else {
    QQBARLabel2(0.1,0.05, TString::Format("#bf{e^{-}e^{+} #rightarrow %s}",quark.Data()),color+2);
    if(ipol>-1) QQBARLabel2(0.1,0.02, TString::Format("#bf{P_{e^{-}e^{+}}=%s | Lum = %i fb^{-1}}",pol[ipol].Data(),lum),color+1);
  }

  //  kWhite  = 0,   kBlack  = 1,   kGray    = 920,  kRed    = 632,  kGreen  = 416,
  //kBlue   = 600, kYellow = 400, kMagenta = 616,  kCyan   = 432,  kOrange = 800,
  //kSpring = 820, kTeal   = 840, kAzure   =  860, kViolet = 880,  kPink   = 900
}

