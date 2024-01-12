#!/bin/bash

#for x in *.cxx; do
#  root -l -b -q "x+"
#  echo "$x OK"
#done

root -l -b -q "BlattWeisskopfQ2.cxx+"
root -l -b -q "ComplexRelBWFcn.cxx+"
root -l -b -q "MyRelBWSquare.cxx+" #roofit pdf
root -l -b -q "MyRelBWSquareFcn.cxx+" #roofit function

root -l -b -q "SpsDpsFcn.cxx+"
root -l -b -q "MyNnuSpsSquare.cxx+" #roofit pdf
root -l -b -q "MyNnuSpsSquareFcn.cxx+" #roofit function
root -l -b -q "MyMiptSpsSquare.cxx+" #roofit pdf
root -l -b -q "MyMiptSpsSquareFcn.cxx+" #roofit function

root -l -b -q "EfficiencyFcn.cxx+" 
root -l -b -q "MyEffFcn.cxx+" #roofit function

root -l -b -q "MyRelBWNnuSpsSquare.cxx+" #roofit pdf
root -l -b -q "MyRelBWNnuSpsInterfFcn.cxx+" #roofit function
#pdf in morepdf/
#root -l -b -q "MyRelBW1BW2NnuSpsSquare.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3NnuSpsSquare.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3BW4NnuSpsSquare.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3BW4BW5NnuSpsSquare.cxx+" #roofit pdf

root -l -b -q "MyRelBWMiptSpsSquare.cxx+" #roofit pdf
root -l -b -q "MyRelBWMiptSpsInterfFcn.cxx+" #roofit function
#pdf in morepdf/
#root -l -b -q "MyRelBW1BW2MiptSpsSquare.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3MiptSpsSquare.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3BW4MiptSpsSquare.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3BW4BW5MiptSpsSquare.cxx+" #roofit pdf

root -l -b -q "MyRelBW1BW2Square.cxx+" #roofit pdf
root -l -b -q "MyRelBW1BW2InterfFcn.cxx+" #roofit function
#pdf in morepdf/
#root -l -b -q "MyRelBW1BW2BW3Square.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3BW4Square.cxx+" #roofit pdf
#root -l -b -q "MyRelBW1BW2BW3BW4BW5Square.cxx+" #roofit pdf

root -l -b -q "SigmaFcn.cxx+"
root -l -b -q "NnuDoubleGaussian.cxx+" #roofit pdf
root -l -b -q "NnuDoubleGaussian2.cxx+" #roofit pdf
root -l -b -q "MiptDoubleGaussian.cxx+" #roofit pdf
root -l -b -q "MiptDoubleGaussian2.cxx+" #roofit pdf
root -l -b -q "MyRelBW1BW2MiptSpsSquare.cxx+"
#pdf in morepdf/
#root -l -b -q "MiptDoubleGaussian2.cxx+" #roofit pdf
