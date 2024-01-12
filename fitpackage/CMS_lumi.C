#include "CMS_lumi.h"
#include <iostream>

void 
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{            
  bool outOfFrame    = false;
  int alignY_=3;
  int alignX_=3;
  int align_ = 33;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  //  float e = 0.025;

  pad->cd();

  TString lumiText;
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(0.9*t);//0.6*t 
  latex.DrawLatex(1-r,1-0.8*t,lumiText);
  
  pad->cd();

  float posX_ = l + 0.045*(1-l-r);
  float posY_ = 1-t - 0.035*(1-t-b);
	  latex.SetTextFont(61);//// default is helvetic-bold
	  latex.SetTextSize(1.1*t);//0.75*t
	  latex.SetTextAlign(33);
latex.DrawLatex(l+0.119, 1.005, "CMS");//0.25,posY_
	      latex.SetTextFont(52);//default is helvetica-italics
	      latex.SetTextAlign(33);
	      latex.SetTextSize(1*t);//0.57*t
//latex.DrawLatex(l+0.40, 1-0.09*t, "Preliminary");
  return;
}
void CMS_lumi() {
  return;
}
