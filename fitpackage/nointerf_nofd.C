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
//#include "CMS_lumi.h"
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

void nointerf_nofd(){
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

  double numDpsInit = 3.51582e+03, numDpsMin = 0, numDpsMax = 100000;
  RooRealVar numDps("numDps", "numDps", numDpsInit, numDpsMin, numDpsMax);
  numDps.setConstant(kFALSE);
  double numSpsInit = 8.19119e+03, numSpsMin = 0, numSpsMax = 100000;
  RooRealVar numSps("numSps", "numSps", numSpsInit, numSpsMin, numSpsMax);
  numSps.setConstant(kFALSE);
  double numX6900Init = 4.86688e+02, numX6900Min = 0, numX6900Max = 10000;
  RooRealVar numX6900("numX6900", "numX6900", numX6900Init, numX6900Min, numX6900Max);
  numX6900.setConstant(kFALSE);
  double numTh1Init = 1.27056e+03, numTh1Min = 0, numTh1Max = 10000;
  RooRealVar numTh1("numTh1", "numTh1", numTh1Init, numTh1Min, numTh1Max);
  numTh1.setConstant(kFALSE);
  double numX6500Init = 4.70494e+02, numX6500Min = 0, numX6500Max = 10000;
  RooRealVar numX6500("numX6500", "numX6500", numX6500Init, numX6500Min, numX6500Max);
  numX6500.setConstant(kFALSE);
  double numX7300Init = 1.55263e+02, numX7300Min = 0, numX7300Max = 10000;
  RooRealVar numX7300("numX7300", "numX7300", numX7300Init, numX7300Min, numX7300Max);
  numX7300.setConstant(kFALSE);


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

  //resolution
  RooRealVar R_SHIFT("R_SHIFT", "R_SHIFT", shift);
  RooRealVar frac_g2("frac_g2", "frac_g2", 0.52357);
  RooRealVar w_g1("w_g1", "w_g1", 0.024467);
  RooRealVar w_g2("w_g2", "w_g2", 0.010042);
  RooRealVar beta("beta", "beta", 0.50989);

  double massTh1Init = 6.33936e+00, massTh1Min = 6.20, massTh1Max = 6.50;
  RooRealVar massTh1("massTh1", "massTh1", massTh1Init, massTh1Min, massTh1Max);
  massTh1.setConstant(kFALSE);
  double widthTh1Init = 3.53406e-01, widthTh1Min = 0.00, widthTh1Max = 1.50;
  RooRealVar widthTh1("widthTh1", "widthTh1", widthTh1Init, widthTh1Min, widthTh1Max);
  widthTh1.setConstant(kFALSE);
  double LTh1Init = 0;
  RooRealVar LTh1("LTh1", "LTh1", LTh1Init);
  LTh1.setConstant(kTRUE);
  double dTh1Init = 3.00, dTh1Min = 1.00, dTh1Max = 5.00;
  RooRealVar dTh1("dTh1", "dTh1", dTh1Init, dTh1Min, dTh1Max);
  dTh1.setConstant(kTRUE);
  double coefTh1Init = 1, coefTh1Min = 0, coefTh1Max = 1000;
  RooRealVar coefTh1("coefTh1", "coefTh1", coefTh1Init, coefTh1Min, coefTh1Max);
  coefTh1.setConstant(kTRUE);
  double phiTh1Init = 0, phiTh1Min = -PI, phiTh1Max = PI;
  RooRealVar phiTh1("phiTh1", "phiTh1", phiTh1Init, phiTh1Min, phiTh1Max);
  phiTh1.setConstant(kTRUE);
  MyRelBWSquare Th1("Th1", "Th1", mx,
      massTh1, widthTh1, LTh1, dTh1, coefTh1, phiTh1);
  MiptDoubleGaussian2 resoTh1("resoTh1", "resoTh1", mx, R_ZERO, frac_g2,
      massTh1, R_MTH, w_g1, w_g2, beta);
  RooFFTConvPdf Th1Reso("Th1Reso", "Th1Reso",
      mx, Th1, resoTh1);

  double massX6500Init = 6.55258e+00, massX6500Min = 6.40, massX6500Max = 6.80;
  RooRealVar massX6500("massX6500", "massX6500", massX6500Init, massX6500Min, massX6500Max);
  massX6500.setConstant(kFALSE);
  double widthX6500Init = 1.24095e-01, widthX6500Min = 0.00, widthX6500Max = 0.50;
  RooRealVar widthX6500("widthX6500", "widthX6500", widthX6500Init, widthX6500Min, widthX6500Max);
  widthX6500.setConstant(kFALSE);
  double LX6500Init = 0;
  RooRealVar LX6500("LX6500", "LX6500", LX6500Init);
  LX6500.setConstant(kTRUE);
  double dX6500Init = 3.00, dX6500Min = 1.00, dX6500Max = 5.00;
  RooRealVar dX6500("dX6500", "dX6500", dX6500Init, dX6500Min, dX6500Max);
  dX6500.setConstant(kTRUE);
  double coefX6500Init = 1, coefX6500Min = 0, coefX6500Max = 1000;
  RooRealVar coefX6500("coefX6500", "coefX6500", coefX6500Init, coefX6500Min, coefX6500Max);
  coefX6500.setConstant(kTRUE);
  double phiX6500Init = 0, phiX6500Min = -PI, phiX6500Max = PI;
  RooRealVar phiX6500("phiX6500", "phiX6500", phiX6500Init, phiX6500Min, phiX6500Max);
  phiX6500.setConstant(kTRUE);
  MyRelBWSquare X6500("X6500", "X6500", mx,
      massX6500, widthX6500, LX6500, dX6500, coefX6500, phiX6500);
  MiptDoubleGaussian2 resoX6500("resoX6500", "resoX6500", mx, R_ZERO, frac_g2,
      massX6500, R_MTH, w_g1, w_g2, beta);
  RooFFTConvPdf X6500Reso("X6500Reso", "X6500Reso",
      mx, X6500, resoX6500);

  double massX6900Init = 6.92586e+00, massX6900Min = 6.80, massX6900Max = 7.00;
  RooRealVar massX6900("massX6900", "massX6900", massX6900Init, massX6900Min, massX6900Max);
  massX6900.setConstant(kFALSE);
  double widthX6900Init = 1.20864e-01, widthX6900Min = 0.00, widthX6900Max = 0.50;
  RooRealVar widthX6900("widthX6900", "widthX6900", widthX6900Init, widthX6900Min, widthX6900Max);
  widthX6900.setConstant(kFALSE);
  double LX6900Init = 0;
  RooRealVar LX6900("LX6900", "LX6900", LX6900Init);
  LX6900.setConstant(kTRUE);
  double dX6900Init = 3.00, dX6900Min = 1.00, dX6900Max = 5.00;
  RooRealVar dX6900("dX6900", "dX6900", dX6900Init, dX6900Min, dX6900Max);
  dX6900.setConstant(kTRUE);
  double coefX6900Init = 1, coefX6900Min = 0, coefX6900Max = 1000;
  RooRealVar coefX6900("coefX6900", "coefX6900", coefX6900Init, coefX6900Min, coefX6900Max);
  coefX6900.setConstant(kTRUE);
  double phiX6900Init = 0, phiX6900Min = -PI, phiX6900Max = PI;
  RooRealVar phiX6900("phiX6900", "phiX6900", phiX6900Init, phiX6900Min, phiX6900Max);
  phiX6900.setConstant(kTRUE);
  MyRelBWSquare X6900("X6900", "X6900", mx,
      massX6900, widthX6900, LX6900, dX6900, coefX6900, phiX6900);
  MiptDoubleGaussian2 resoX6900("resoX6900", "resoX6900", mx, R_ZERO, frac_g2,
      massX6900, R_MTH, w_g1, w_g2, beta);
  RooFFTConvPdf X6900Reso("X6900Reso", "X6900Reso",
      mx, X6900, resoX6900);
  RooGaussian massX6900Constr("massX6900Constr", "massX6900Constr", massX6900,
      RooConst(6.905), RooConst(sqrt(0.011*0.011+0.007*0.007)));
  RooGaussian widthX6900Constr("widthX6900Constr", "widthX6900Constr", widthX6900,
      RooConst(0.080), RooConst(sqrt(0.019*0.019+0.033*0.033)));

  double massX7300Init = 7.28734e+00, massX7300Min = 7.00, massX7300Max = 7.50;
  RooRealVar massX7300("massX7300", "massX7300", massX7300Init, massX7300Min, massX7300Max);
  massX7300.setConstant(kFALSE);
  double widthX7300Init = 9.32169e-02, widthX7300Min = 0.00, widthX7300Max = 0.50;
  RooRealVar widthX7300("widthX7300", "widthX7300", widthX7300Init, widthX7300Min, widthX7300Max);
  widthX7300.setConstant(kFALSE);
  double LX7300Init = 0;
  RooRealVar LX7300("LX7300", "LX7300", LX7300Init);
  LX7300.setConstant(kTRUE);
  double dX7300Init = 3.00, dX7300Min = 1.00, dX7300Max = 5.00;
  RooRealVar dX7300("dX7300", "dX7300", dX7300Init, dX7300Min, dX7300Max);
  dX7300.setConstant(kTRUE);
  double coefX7300Init = 1, coefX7300Min = 0, coefX7300Max = 1000;
  RooRealVar coefX7300("coefX7300", "coefX7300", coefX7300Init, coefX7300Min, coefX7300Max);
  coefX7300.setConstant(kTRUE);
  double phiX7300Init = 0, phiX7300Min = -PI, phiX7300Max = PI;
  RooRealVar phiX7300("phiX7300", "phiX7300", phiX7300Init, phiX7300Min, phiX7300Max);
  phiX7300.setConstant(kTRUE);
  MyRelBWSquare X7300("X7300", "X7300", mx,
      massX7300, widthX7300, LX7300, dX7300, coefX7300, phiX7300);
  MiptDoubleGaussian2 resoX7300("resoX7300", "resoX7300", mx, R_ZERO, frac_g2,
      massX7300, R_MTH, w_g1, w_g2, beta);
  RooFFTConvPdf X7300Reso("X7300Reso", "X7300Reso",
      mx, X7300, resoX7300);

  RooArgList pdfList(dpsPdf, spsPdf, Th1Reso, X6500Reso, X6900Reso, X7300Reso);
  RooArgList numList(numDps, numSps, numTh1, numX6500, numX6900, numX7300);

  RooAddPdf model("model", "model", pdfList, numList);

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

  RooPlot *frame = mx.frame(Range(mxMin, mxMax), Bins(mxBins));
  data.plotOn(frame, Name("data"));
  model.plotOn(frame, Name("model"), LineColor(4));
  double effBins615 = effectiveBins(MTH, mxMin, mxMax, mxBins);
  double chi2Dof615 = frame->chiSquare() * mxBins / (effBins615 - NPARS);
  double prob615 = TMath::Prob(frame->chiSquare() * mxBins , (effBins615 - NPARS));
  model.plotOn(frame, Components(dpsPdf), Name("Dps"), LineColor(kGreen), LineStyle(1));
  model.plotOn(frame, Components(spsPdf), Name("Sps"), LineColor(kViolet), LineStyle(1));
  model.plotOn(frame, Components(X6900Reso), Name("X6900"), LineColor(kRed), LineStyle(kSolid));
  model.plotOn(frame, Components(Th1Reso), Name("Th1"), LineColor(kMagenta), LineStyle(kDashDotted));
  model.plotOn(frame, Components(X6500Reso), Name("X6500"), LineColor(kRed), LineStyle(kDotted));
  model.plotOn(frame, Components(X7300Reso), Name("X7300"), LineColor(kRed), LineStyle(kDashed));

  frame->GetXaxis()->SetTitle(XTitle.Data());
  frame->GetXaxis()->SetLabelColor(0, 0);
  frame->GetYaxis()->SetTitle(YTitle.Data());
  frame->GetYaxis()->SetTitleOffset(0.7);

  TLegend leg(0.6, 0.45, 0.9, 0.75);
  leg.AddEntry(frame->findObject("data"), "Data", "pe");
  leg.AddEntry(frame->findObject("model"), "Fit", "l");
  leg.AddEntry(frame->findObject("Th1"), "BW0", "l");
  leg.AddEntry(frame->findObject("X6500"), "BW1", "l");
  leg.AddEntry(frame->findObject("X6900"), "X(6900)", "l");
  leg.AddEntry(frame->findObject("X7300"), "BW3", "l");
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
  c1.SaveAs("figure/fit.pdf");
      
  fitRes->Print();
  fitRes->Delete();
  frame->Delete();
}
