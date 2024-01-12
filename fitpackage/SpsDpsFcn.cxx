#include "SpsDpsFcn.h"
#include "TMath.h"
#include <cmath>

void SpsDpsFcn() {
  return;
}
double SqrtExpPoly(double x, double mth, double a,
    double p0, double p1, double p2, double p3, double p4) {
  double mx = x - mth;
  double fth = 0;
  if (mx <= 0) return fth;
  if (mx > 0) fth = TMath::Sqrt(mx);
  double exponent = TMath::Exp(-1 * a * mx);
  double poly = p0 + p1 * mx + p2 * mx * mx + p3 * mx * mx * mx + p4 * mx * mx * mx * mx;
  double res = fth * exponent * poly;
  return res;
}
double SqrtPoly(double x, double mth,
    double p0, double p1, double p2, double p3, double p4) {
  double mx = x - mth;
  double fth = 0;
  if (mx <= 0) return fth;
  if (mx > 0) fth = TMath::Sqrt(mx);
  double poly = p0 + p1 * mx + p2 * mx * mx + p3 * mx * mx * mx + p4 * mx * mx * mx * mx;
  double res = fth * poly;
  return res;
}
double MiptSps(double x, double mth, double mup, 
    double alpha, double p1, double p2, double p3) {
  double mx = x - mth;
  if (mx <= 0) return 0;
  double range = mup - mth;
  double powTerm = TMath::Power(mx, alpha);
  double polyTerm = 1 - (1.0 / range / range - p1 / 10.0) * (mup - x) * (mup - x);
  double expTerm = TMath::Exp(-1.0 * TMath::Power(mx, p3) / 2.0 / TMath::Power(p2, p3));
  double res = powTerm * polyTerm * expTerm;
  return res;
}
