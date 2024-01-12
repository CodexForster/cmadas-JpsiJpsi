/*
* Author: Jingqing Zhang, jingqing@cern.ch
* Functions for the fit package 
* with/without interference between resonances (and SPS)
*/
#ifndef COMPLEX_RELBW_FCN_H
#define COMPLEX_RELBW_FCN_H

#include <iostream>
#include <complex>
#include "TMath.h"

void ComplexRelBWFcn();
std::complex<double> ComplexRelBW(double x, double mass, double width,
    double L, double d, double coef, double phi);
#endif
