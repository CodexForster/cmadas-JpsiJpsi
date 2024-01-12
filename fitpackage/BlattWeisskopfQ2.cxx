/*
* Author: Jingqing Zhang, jingqing@cern.ch
* Functions for the fit package 
* with/without interference between resonances (and SPS)
*/
#include "BlattWeisskopfQ2.h"
#include <iostream>
#include "TMath.h"
void BlattWeisskopfQ2() {
  return;
}
double Q2(double sa, double sb, double sc) {
  double res = (sa + sb - sc) * (sa + sb - sc) / 4.0 / sa - sb;
  if (res <= 0) {
    res = 0;
  }
  return res;
}

double BlattWeisskopf(double q2, double d, double L) {
  double res = 1.0;
  if (d < 0) return res;
  double z = q2 * d * d;
  if (L < 0.5) {
    res = 1.0;
  } else if ( L > 0.5 && L < 1.5) {
    res = TMath::Sqrt(2 * z / (z + 1));
  } else if (L > 1.5 && L < 2.5) {
    res = TMath::Sqrt(13 * z * z / ((z - 3) * (z - 3) + 9 * z));
  } else if (L > 2.5 && L < 3.5) {
    res = TMath::Sqrt(277 * z * z * z / (z * (z - 15) * (z - 15) + 9 * (2 * z - 5) * (2 * z - 5)));
  } else if (L > 3.5 && L < 4.5) {
    res = TMath::Sqrt(12746 * z * z * z * z / ((z * z - 45 * z + 105) * (z * z - 45 * z + 105) + 25 * z * (2 * z - 21) * (2 * z - 21)));
  } else {
    std::cout << "WARNING, BlattWeisskopf implementation only for L <= 4, current L is " << L << " !!!" << std::endl;
    res = 0;
  }
  return res;
}
