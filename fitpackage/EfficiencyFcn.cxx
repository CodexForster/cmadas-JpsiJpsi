#include "EfficiencyFcn.h"

void EfficiencyFcn() {
  return;
}
double EffFcn(double x) {
  double res = 1.0;
  const double p0 = 4.63295e-02;
  const double p1 = -9.18637e-03;
  const double p2 = 6.37306e-04;
  res = p0 + p1 * x + p2 * x * x;
  return res;
}
