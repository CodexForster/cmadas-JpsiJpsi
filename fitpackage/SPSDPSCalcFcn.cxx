/*
* Author: Jingqing Zhang, jingqing@cern.ch
* Functions for the fit package 
* with/without interference between resonances (and SPS)
*/
#include "SPSDPSCalcFcn.h"
#include "TMath.h"
void SPSDPSCalcFcn() {
  return;
}
double SqrtExponentPoly(double x, double a, double b,
    double p2, double p1, double p0) {
  const double MJPSI = 3.096900; //PDG 2020
  const double MTH = 3.096900*2;
  double mx = x - MTH;
  double fth = 0;
  if (mx <= 0) return fth;
  if (mx > 0) fth = TMath::Sqrt(mx);
  double exponent = TMath::Exp(-1 * a * mx );
  double poly = p2 * mx * mx + p1 * mx + p0;
  //double scale = 1e20;
  double scale = 1e16;
  double res = scale * fth * exponent * poly;
  return res;
}
