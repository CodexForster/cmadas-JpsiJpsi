/*
* Author: Jingqing Zhang, jingqing@cern.ch
* Fit package with/without interference between resonances (and Sps)
* Note when interference is included in the fit,
* the indication lines in the fit projection plot of components
* which is involved in the interference are not included
* the resolution effects.
* The component fractions of individual interference parts
* are only indicative and not precise.
* In the global fit, both resolution and efficiency are considered correctly.
*/
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooHistFunc.h"
#include "RooAddPdf.h"
#include "RooEffProd.h"
#include "RooProdPdf.h"
#include "RooFFTConvPdf.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooArgList.h"
#include "RooArgSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooProduct.h"
#include "RooRandom.h"
#include "RooHist.h"
#include "TLine.h"
#include "RooCBShape.h"

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TMath.h"
#include "TStyle.h"
#include "TString.h"
#include "TRandom3.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "BlattWeisskopfQ2.h"
#include "ComplexRelBWFcn.h"
#include "MyRelBWSquare.h"
#include "MyRelBWSquareFcn.h"

#include "SpsDpsFcn.h"
#include "MyNnuSpsSquare.h"
#include "MyNnuSpsSquareFcn.h"
#include "MyMiptSpsSquare.h"
#include "MyMiptSpsSquareFcn.h"

#include "EfficiencyFcn.h"
#include "MyEffFcn.h"

#include "SigmaFcn.h"
#include "MiptDoubleGaussian2.h"

#include "tdrstyle.C"
#include "CMS_lumi.C"

using namespace RooFit;

double effectiveBins(double mth, double mLow, double mUp, double mBins) {
  double mBin0 = 0;
  double binWidth = (mUp - mLow) / mBins;
  while (mBin0 < mBins) {
    double mx = mLow + (mBin0 + 1) * binWidth;
    if (mx > mth) break;
    mBin0 += 1;
  }
  double effBins = mBins - mBin0;
  return effBins;
}

void null_BW0(){
  setTDRStyle();
  writeExtraText = true;
  lumi_13TeV = "135 fb^{-1}";
  lumi_8TeV = "20.6 fb^{-1}";
  lumi_7TeV = "4.9 fb^{-1}";
  int iPos = 33;
  gSystem->Load("BlattWeisskopfQ2_cxx.so");
  gSystem->Load("ComplexRelBWFcn_cxx.so");
  gSystem->Load("MyRelBWSquare_cxx.so");
  gSystem->Load("MyRelBWSquareFcn_cxx.so");

  gSystem->Load("SpsDpsFcn_cxx.so");
  gSystem->Load("MyNnuSpsSquare_cxx.so");
  gSystem->Load("MyNnuSpsSquareFcn_cxx.so");
  gSystem->Load("MyMiptSpsSquare_cxx.so");
  gSystem->Load("MyMiptSpsSquareFcn_cxx.so");

  gSystem->Load("EfficiencyFcn_cxx.so");
  gSystem->Load("MyEffFcn_cxx.so");

  gSystem->Load("SigmaFcn_cxx.so");
  gSystem->Load("MiptDoubleGaussian2_cxx.so");

  int NPARS = 15;

  const double PI = TMath::Pi();
  double mxMin = 6.0, mxMax = 15.0;
  int mxBins = 180; 
  double mxBinWidth = (mxMax - mxMin) / mxBins;
  TString YTitle, XTitle;
  YTitle.Form("Candidates / %d MeV", int(mxBinWidth * 1000 + 0.5));
  XTitle.Form("m_{J/#psiJ/#psi} [GeV]");
  double center = (mxMin + mxMax)/2.0;
  double shift = -center;
  int STRATEGY = 1; //0, 1, 2
  int NCPU = 4; //num of cpus
  int FFT_BINS = 10000;
  bool MINOS = false;
  const int COUT_PRECISION = 6;
  double effectiveBins(double mth, double mLow, double mUp, double mBins);
  const double MTH = 2 * 3.096900;
  RooRealVar R_MTH("R_MTH", "R_MTH", MTH);
  RooRealVar R_MUP("R_MUP", "R_MUP", 15.0);
  RooRealVar mx("mx", "mx", mxMin, mxMax);
  RooDataSet data = *RooDataSet::read("../fullrun2data/mJJDataFull6000_15000.txt", RooArgList(mx), "Q");

  // Here we introduce the normalization factors
  double numDpsInit = 3.51582e+03, numDpsMin = 0, numDpsMax = 100000;
  RooRealVar numDps("numDps", "numDps", numDpsInit, numDpsMin, numDpsMax);
  numDps.setConstant(kFALSE);
  double numSpsInit = 8.19119e+03, numSpsMin = 0, numSpsMax = 100000;
  RooRealVar numSps("numSps", "numSps", numSpsInit, numSpsMin, numSpsMax);
  numSps.setConstant(kFALSE);
  // This will be the normalization of our first peak
  double numTh1Init = 1.27056e+03, numTh1Min = 0, numTh1Max = 10000;
  RooRealVar numTh1("numTh1", "numTh1", numTh1Init, numTh1Min, numTh1Max);
  numTh1.setConstant(kFALSE);


  RooRealVar R_ZERO("R_ZERO", "R_ZERO", 0);
  RooRealVar R_ONE("R_ONE", "R_ONE", 1);

  RooRealVar alpha("alpha", "alpha", 0.80567);
  RooRealVar p1("p1", "p1", 0.32647);
  double p2Init = 9.78655e-02, p2Min = 0, p2Max = 1.0;
  RooRealVar p2("p2", "p2", p2Init, p2Min, p2Max);
  RooRealVar p3("p3", "p3", 0.53968);
  MyMiptSpsSquare spsPdf("spsPdf", "spsPdf", mx, R_MTH, R_MUP,
      alpha, p1, p2, p3, R_ONE, R_ZERO);

  RooRealVar dpsA("dpsA", "dpsA", 0.24358);
  RooRealVar dpsP0("dpsP0", "dpsP0", 0.23137);
  RooRealVar dpsP1("dpsP1", "dpsP1", -0.041952);
  RooRealVar dpsP2("dpsP2", "dpsP2", 0.012206);
  MyNnuSpsSquare dpsPdf("dpsPdf", "dpsPdf", mx, R_MTH,
      dpsA, dpsP0, dpsP1, dpsP2, R_ZERO, R_ZERO, R_ONE, R_ZERO);

  mx.setBins(FFT_BINS, "cache");
  
  // Parameters for Breit-Wigner (BW) - see formula in Twiki
  // and note that some of the parameters are floating while others are fixed
  double massTh1Init = 6.33936e+00, massTh1Min = 6.20, massTh1Max = 6.50;
  RooRealVar massTh1("massTh1", "massTh1", massTh1Init, massTh1Min, massTh1Max);
  massTh1.setConstant(kFALSE); //m_0
  double widthTh1Init = 3.53406e-01, widthTh1Min = 0.00, widthTh1Max = 1.50;
  RooRealVar widthTh1("widthTh1", "widthTh1", widthTh1Init, widthTh1Min, widthTh1Max);
  widthTh1.setConstant(kFALSE); //Gamma_0
  double LTh1Init = 0; // We assume S-wave
  RooRealVar LTh1("LTh1", "LTh1", LTh1Init);
  LTh1.setConstant(kTRUE);
  double dTh1Init = 3.00, dTh1Min = 1.00, dTh1Max = 5.00;
  RooRealVar dTh1("dTh1", "dTh1", dTh1Init, dTh1Min, dTh1Max);
  dTh1.setConstant(kTRUE); 
  // the parameters below are related to interference terms. 
  // We set them to a constant value as we are not considering interference
  double coefTh1Init = 1, coefTh1Min = 0, coefTh1Max = 1000;
  RooRealVar coefTh1("coefTh1", "coefTh1", coefTh1Init, coefTh1Min, coefTh1Max);
  coefTh1.setConstant(kTRUE);
  double phiTh1Init = 0, phiTh1Min = -PI, phiTh1Max = PI;
  RooRealVar phiTh1("phiTh1", "phiTh1", phiTh1Init, phiTh1Min, phiTh1Max);
  phiTh1.setConstant(kTRUE);

  // To take into account detectors effect that affect the resolution of our peak
  // we introduce a smearing function with the below parameters
  RooRealVar R_SHIFT("R_SHIFT", "R_SHIFT", shift);
  RooRealVar frac_g2("frac_g2", "frac_g2", 0.52357);
  RooRealVar w_g1("w_g1", "w_g1", 0.024467);
  RooRealVar w_g2("w_g2", "w_g2", 0.010042);
  RooRealVar beta("beta", "beta", 0.50989);

  // Here we construct our function with the parameters defined above
  MyRelBWSquare Th1("Th1", "Th1", mx,
      massTh1, widthTh1, LTh1, dTh1, coefTh1, phiTh1);
  // We also need to take into account detector smearing which affect the resolution of the peak
  MiptDoubleGaussian2 resoTh1("resoTh1", "resoTh1", mx, R_ZERO, frac_g2,
      massTh1, R_MTH, w_g1, w_g2, beta);
  // we do a numerical convolution as we do not have an analytical function
  // This is the final formula for the peak    
  RooFFTConvPdf Th1Reso("Th1Reso", "Th1Reso",
      mx, Th1, resoTh1);

  // dps and sps are backgrounds and Th1Reso is our signal
  RooArgList pdfList(dpsPdf, spsPdf, Th1Reso);
  // we want to normalize them 
  RooArgList numList(numDps, numSps, numTh1);

  RooAddPdf model("model", "model", pdfList, numList);

  // here is where the actual fitting happens
  RooFitResult *fitRes = model.fitTo(data, Save(kTRUE), 
      Minos(MINOS), Strategy(STRATEGY), NumCPU(NCPU));
  double edm = fitRes->edm();
  double minNll = fitRes->minNll(); //Return minimized -log(L) value. 
  int status = fitRes->status(); //MINUIT status code
  /* TMinuit execution status code, hope TMinuit2 keeps same convention
  * 0: command executed normally (converge)
  * 1: command is blank, ignored
  * 2: command line unreadable, ignored
  * 3: unknown command, ignored
  * 4: abnormal termination (e.g., MIGRAD not converged)
  * 5: command is a request to read PARAMETER definitions
  * 6: 'SET INPUT' command
  * 7: 'SET TITLE' command
  * 8: 'SET COVAR' command
  * 9: reserved
  * 10: END command
  * 11: EXIT or STOP command
  * 12: RETURN command
  */
  int covQual = fitRes->covQual(); //MINUIT quality code of covariance matrix
  /*
  *ISTAT: a status integer indicating how good is the covariance matrix:
  *0= not calculated at all
  *1= approximation only, not accurate
  *2= full matrix, but forced positive-definite
  *3= full accurate covariance matrix
  */

  // now we want to plot the fit results
  RooPlot *frame = mx.frame(Range(mxMin, mxMax), Bins(mxBins));
  data.plotOn(frame, Name("data"));
  model.plotOn(frame, Name("model"), LineColor(4));
  double effBins615 = effectiveBins(MTH, mxMin, mxMax, mxBins);
  double chi2Dof615 = frame->chiSquare() * mxBins / (effBins615 - NPARS);
  double prob615 = TMath::Prob(frame->chiSquare() * mxBins , (effBins615 - NPARS));
  model.plotOn(frame, Components(dpsPdf), Name("Dps"), LineColor(kGreen), LineStyle(1));
  model.plotOn(frame, Components(spsPdf), Name("Sps"), LineColor(kViolet), LineStyle(1));
  model.plotOn(frame, Components(Th1Reso), Name("Th1"), LineColor(kMagenta), LineStyle(kDashDotted));

  frame->GetXaxis()->SetTitle(XTitle.Data());
  frame->GetXaxis()->SetLabelColor(0, 0);
  frame->GetYaxis()->SetTitle(YTitle.Data());
  frame->GetYaxis()->SetTitleOffset(0.7);

  TLegend leg(0.6, 0.45, 0.9, 0.75);
  leg.AddEntry(frame->findObject("data"), "Data", "pe");
  leg.AddEntry(frame->findObject("model"), "Fit", "l");
  leg.AddEntry(frame->findObject("Th1"), "BW0", "l");
  leg.AddEntry(frame->findObject("Sps"), "SPS", "l");
  leg.AddEntry(frame->findObject("Dps"), "DPS", "l");

  RooPlot *pullFrame = mx.frame(Range(mxMin, mxMax), Bins(mxBins));
  RooHist *pull = frame->pullHist("data", "model");
  pullFrame->addPlotable(pull, "p");
  pullFrame->GetXaxis()->SetTitle(XTitle.Data());
  pullFrame->GetXaxis()->SetTitleSize(0.15);
  pullFrame->GetXaxis()->SetLabelSize(0.12);
  pullFrame->GetYaxis()->SetTitle("Pull");
  pullFrame->GetYaxis()->SetTitleSize(0.15);
  pullFrame->GetYaxis()->SetLabelSize(0.1);
  pullFrame->GetYaxis()->SetTitleOffset(0.2);

  TCanvas c1("c1", "c1", 800, 600);
  c1.cd();
  TPad pad11("pad11", "pad11", 0, 0.3, 1, 1.0);
  pad11.SetTopMargin(0.08);
  pad11.SetBottomMargin(0.017);
  pad11.Draw();
  pad11.cd();
  frame->Draw();
  CMS_lumi(&pad11, 4, iPos);
  leg.Draw();

  c1.cd();
  TPad pad12("pad12", "pad12", 0.0, 0.0, 1, 0.3);
  pad12.SetTopMargin(0.03);
  pad12.SetBottomMargin(0.325);
  pad12.SetGridx();
  pad12.SetGridy(2);
  pad12.Draw();
  pad12.cd();
  pullFrame->Draw();
  c1.Update();
  c1.SaveAs("figure/fit_null_BW0.pdf");
      
  fitRes->Print();
  fitRes->Delete();
  frame->Delete();
}
