/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef MYMIPTSPSSQUAREFCN
#define MYMIPTSPSSQUAREFCN

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class MyMiptSpsSquareFcn : public RooAbsReal {
public:
  MyMiptSpsSquareFcn() {} ; 
  MyMiptSpsSquareFcn(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _mth,
	      RooAbsReal& _mup,
	      RooAbsReal& _alpha,
	      RooAbsReal& _p1,
	      RooAbsReal& _p2,
	      RooAbsReal& _p3,
	      RooAbsReal& _coef,
	      RooAbsReal& _phi);
  MyMiptSpsSquareFcn(const MyMiptSpsSquareFcn& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new MyMiptSpsSquareFcn(*this,newname); }
  inline virtual ~MyMiptSpsSquareFcn() { }

protected:

  RooRealProxy x ;
  RooRealProxy mth ;
  RooRealProxy mup ;
  RooRealProxy alpha ;
  RooRealProxy p1 ;
  RooRealProxy p2 ;
  RooRealProxy p3 ;
  RooRealProxy coef ;
  RooRealProxy phi ;
  
  Double_t evaluate() const ;

private:

  ClassDef(MyMiptSpsSquareFcn,1) // Your description goes here...
};
 
#endif