This analysis is divided in two steps, the event selection and the fitting part. The code for the two different parts is in two separate directories.

Setup:
```
ssh -Y USERNAME@cmslpc-sl7.fnal.gov
cd ~/nobackup/
mkdir CMSDAS2024
cd CMSDAS2024
git clone https://github.com/IreneZoi/DAS2024JpsiJpsi.git
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsrel CMSSW_10_2_5
cmsrel CMSSW_11_1_1
```

For the event selection part:
```
cd ~/nobackup/CMSDAS2024JpsiJpsi/CMSSW_10_2_5/src
cmsenv
cd ../../eventselection/
root -l
root [0] .L myntuple.C++
root [1] .x runJobs_0.C
root [2] .q

root -l myhbk.root
root [1] .ls
root [2] myFourMuonmass->Draw()
```

For the fit part:
```
cd ~/nobackup/CMSDAS2024JpsiJpsi/CMSSW_11_1_1/src/
cmsenv
cd ../../fitpackage/
source makeLibSo.sh
root -l nointerf_nofd.C
```


