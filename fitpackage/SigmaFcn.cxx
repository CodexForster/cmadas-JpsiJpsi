#include "SigmaFcn.h"
#include "TMath.h"

void SigmaFcn() {
  return;
}
double NnuSigma(double x, double mth, double a, double b, double c, double d, double e) {
  double res = 0;
  double mx = x - mth;
  if (mx > 0) {
    res = TMath::Exp(-1 * a * mx) * (b * mx * mx + c * mx + d) + e;
  }
  return res;
}
double MiptSigma(double x, double mth, double w, double beta) {
  double mx = x - mth;
  double res = 0;
  if (mx > 0.000001) {
    res = w * TMath::Power(mx, beta);
  }
  return res;
}
