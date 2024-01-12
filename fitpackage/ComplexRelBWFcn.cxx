/*
* Author: Jingqing Zhang, jingqing@cern.ch
* Functions for the fit package 
* with/without interference between resonances (and SPS)
*/
#include "ComplexRelBWFcn.h"
#include "BlattWeisskopfQ2.h"
#include "TMath.h"

void ComplexRelBWFcn() {
  return;
}
std::complex<double> ComplexRelBW(double x, double mass, double width,
    double L, double d, double coef, double phi) {
  // // arxiv:1507.03414, eq. 6,7 and PRL102.242002 ref22
  // BlattWeisskopf PhysReVD48.1225
  // blattWeisskopf in BW, https://pdg.lbl.gov/2012/reviews/rpp2012-rev-dalitz-analysis-formalism.pdf
  const double M = 3.096900; //mass of jpsi in pdg2020
  if (x <= M * 2) return std::complex<double>(0, 0);
  std::complex<double> i(0, 1);

  std::complex<double> cpl = std::polar<double>(coef, phi);
  double qq = Q2(x * x, M * M, M * M);
  double q0q0 = Q2(mass * mass, M * M, M * M);
  double BL = BlattWeisskopf(qq, d, L);
  double BL10 = BlattWeisskopf(q0q0, d, L);
  double Gamma = width * TMath::Sqrt(qq / q0q0) * mass / x * TMath::Power(BL / BL10, 2.0);
  double num = TMath::Sqrt(x * Gamma);
  std::complex<double> denom = mass * mass - x * x - i * x * Gamma;
  std::complex<double> bw = num / denom;

  std::complex<double> res = cpl * bw;
  return res;
}
