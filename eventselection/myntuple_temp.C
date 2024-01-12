#define myntuple_cxx
#include "myntuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

#include "TLorentzVector.h"
#include <iostream> 
#include <fstream>
using namespace std;

struct PairedMuonIdx {
	int p11;
	int p12;
	int p21;
	int p22;
};

void myntuple::Loop()
{
	//   In a ROOT session, you can do:
	//      root> .L myntuple.C
	//      root> myntuple t
	//      root> t.GetEntry(12); // Fill t data members with entry number 12
	//      root> t.Show();       // Show values of entry 12
	//      root> t.Show(16);     // Read and show values of entry 16
	//      root> t.Loop();       // Loop on all entries
	//

	//     This is the loop skeleton where:
	//    jentry is the global entry number in the chain
	//    ientry is the entry number in the current Tree
	//  Note that the argument to GetEntry must be:
	//    jentry for TChain::GetEntry
	//    ientry for TTree::GetEntry and TBranch::GetEntry
	//
	//       To read only selected branches, Insert statements like:
	// METHOD1:
	//    fChain->SetBranchStatus("*",0);  // disable all branches
	//    fChain->SetBranchStatus("branchname",1);  // activate branchname
	// METHOD2: replace line
	//    fChain->GetEntry(jentry);       //read all branches
	//by  b_branchname->GetEntry(ientry); //read only this branch

	//define txt file
	ofstream myoutputfile("mJJDataFull6000_15000.txt");

	//define root file
	TFile* myhbk = new TFile ("myhbk.root","recreate");

	//define histogram
	TH1F* myDiMuon1mass_before = new TH1F("myDiMuon1mass_before","myDiMuon1mass_before",80,2.7,3.5);
	TH1F* myDiMuon2mass_before = new TH1F("myDiMuon2mass_before","myDiMuon2mass_before",80,2.7,3.5);
	TH1F* myFourMuonmass_before = new TH1F("myFourMuonmass_before","myFourMuonmass_before",360,6,15);

	TH1F* noOfMuons_before = new TH1F("noOfMuons_before","Number of muons per event/entry",100,0,10);
	TH1F* vertex_before = new TH1F("vertex_before","Probability of 4-muon from same vertex",1000,0,1);

	TH1F* mu1pt_before = new TH1F("mu1pt_before","mu1pt_before",100,0,100);
	TH1F* mu2pt_before = new TH1F("mu2pt_before","mu2pt_before",100,0,100);
	TH1F* mu3pt_before = new TH1F("mu3pt_before","mu3pt_before",100,0,100);
	TH1F* mu4pt_before = new TH1F("mu4pt_before","mu4pt_before",100,0,100);

	TH1F* mu1E_before = new TH1F("mu1E_before","mu1E_before",100,0,100);
	TH1F* mu2E_before = new TH1F("mu2E_before","mu2E_before",100,0,100);
	TH1F* mu3E_before = new TH1F("mu3E_before","mu3E_before",100,0,100);
	TH1F* mu4E_before = new TH1F("mu4E_before","mu4E_before",100,0,100);

	TH1F* mu1pz_before = new TH1F("mu1pz_before","mu1pz_before",100,0,100);
	TH1F* mu2pz_before = new TH1F("mu2pz_before","mu2pz_before",100,0,100);
	TH1F* mu3pz_before =  new TH1F("mu3pz_before","mu3pz_before",100,0,100);
	TH1F* mu4pz_before =  new TH1F("mu4pz_before","mu4pz_before",100,0,100);

	TH1F* mu1Eta_before =  new TH1F("mu1Eta_before","mu1Eta_before",800,-4, 4);
	TH1F* mu2Eta_before =  new TH1F("mu2Eta_before","mu2Eta_before",800,-4, 4);
	TH1F* mu3Eta_before =  new TH1F("mu3Eta_before","mu3Eta_before",800,-4, 4);
	TH1F* mu4Eta_before =  new TH1F("mu4Eta_before","mu4Eta_before",800,-4, 4);

	TH1F* mu1M_before = new TH1F("mu1M_before","mu1M_before",1000,0,10);
	TH1F* mu2M_before = new TH1F("mu2M_before","mu2M_before",1000,0,10);
	TH1F* mu3M_before = new TH1F("mu3M_before","mu3M_before",1000,0,10);
	TH1F* mu4M_before = new TH1F("mu4M_before","mu4M_before",1000,0,10);

	TH1F* muAllpt_before = new TH1F("muAllpt_before","muAllpt_before",400,0,400);
	TH1F* muAllE_before = new TH1F("muAllE_before","muAllE_before",400,0,400);
	TH1F* muAllpz_before = new TH1F("muAllpz_before","muAllpz_before",400,0,400);
	TH1F* muAllEta_before =  new TH1F("muAllEta_before","muAllEta_before",800,-4, 4);
	TH1F* muAllM_before = new TH1F("muAllM_before","muAllM_before",4000,0,40);


	TH1F* myDiMuon1mass_after = new TH1F("myDiMuon1mass_after","myDiMuon1mass_after",80,2.7,3.5);
	TH1F* myDiMuon2mass_after = new TH1F("myDiMuon2mass_after","myDiMuon2mass_after",80,2.7,3.5);
	TH1F* myFourMuonmass_after = new TH1F("myFourMuonmass_after","myFourMuonmass_after",360,6,15);

	TH1F* noOfMuons_after = new TH1F("noOfMuons_after","Number of muons per event/entry",100,0,10);
	TH1F* vertex_after = new TH1F("vertex_after","Probability of 4-muon from same vertex",1000,0,1);

	TH1F* mu1pt_after = new TH1F("mu1pt_after","mu1pt_after",100,0,100);
	TH1F* mu2pt_after = new TH1F("mu2pt_after","mu2pt_after",100,0,100);
	TH1F* mu3pt_after = new TH1F("mu3pt_after","mu3pt_after",100,0,100);
	TH1F* mu4pt_after = new TH1F("mu4pt_after","mu4pt_after",100,0,100);

	TH1F* mu1E_after = new TH1F("mu1E_after","mu1E_after",100,0,100);
	TH1F* mu2E_after = new TH1F("mu2E_after","mu2E_after",100,0,100);
	TH1F* mu3E_after = new TH1F("mu3E_after","mu3E_after",100,0,100);
	TH1F* mu4E_after = new TH1F("mu4E_after","mu4E_after",100,0,100);

	TH1F* mu1pz_after = new TH1F("mu1pz_after","mu1pz_after",100,0,100);
	TH1F* mu2pz_after = new TH1F("mu2pz_after","mu2pz_after",100,0,100);
	TH1F* mu3pz_after =  new TH1F("mu3pz_after","mu3pz_after",100,0,100);
	TH1F* mu4pz_after =  new TH1F("mu4pz_after","mu4pz_after",100,0,100);

	TH1F* mu1Eta_after =  new TH1F("mu1Eta_after","mu1Eta_after",800,-4, 4);
	TH1F* mu2Eta_after =  new TH1F("mu2Eta_after","mu2Eta_after",800,-4, 4);
	TH1F* mu3Eta_after =  new TH1F("mu3Eta_after","mu3Eta_after",800,-4, 4);
	TH1F* mu4Eta_after =  new TH1F("mu4Eta_after","mu4Eta_after",800,-4, 4);

	TH1F* mu1M_after = new TH1F("mu1M_after","mu1M_after",1000,0,10);
	TH1F* mu2M_after = new TH1F("mu2M_after","mu2M_after",1000,0,10);
	TH1F* mu3M_after = new TH1F("mu3M_after","mu3M_after",1000,0,10);
	TH1F* mu4M_after = new TH1F("mu4M_after","mu4M_after",1000,0,10);

	TH1F* muAllpt_after = new TH1F("muAllpt_after","muAllpt_after",400,0,400);
	TH1F* muAllE_after = new TH1F("muAllE_after","muAllE_after",400,0,400);
	TH1F* muAllpz_after = new TH1F("muAllpz_after","muAllpz_after",400,0,400);
	TH1F* muAllEta_after =  new TH1F("muAllEta_after","muAllEta_after",800,-4, 4);
	TH1F* muAllM_after = new TH1F("muAllM_after","muAllM_after",4000,0,40);



	//define histograms 2
	TH1F* myDiMuon1mass_noPE = new TH1F("myDiMuon1mass_noPE","myDiMuon1mass_noPE",80,2.7,3.5);
	TH1F* myDiMuon2mass_noPE = new TH1F("myDiMuon2mass_noPE","myDiMuon2mass_noPE",80,2.7,3.5);
	TH1F* myFourMuonmass_noPE = new TH1F("myFourMuonmass_noPE","myFourMuonmass_noPE",360,6,15);

	//define histograms 3
	TH1F* myDiMuon1mass_noE = new TH1F("myDiMuon1mass_noE","myDiMuon1mass_noE",80,2.7,3.5);
	TH1F* myDiMuon2mass_noE = new TH1F("myDiMuon2mass_noE","myDiMuon2mass_noE",80,2.7,3.5);
	TH1F* myFourMuonmass_noE = new TH1F("myFourMuonmass_noE","myFourMuonmass_noE",360,6,15);

	const double MUON_MASS = 0.1056583745; //GeV
	const double JPSI_MASS = 3.096900; //GeV

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		if (jentry%10000 == 0) cout << "I am running " << jentry << "th entries out of " << nentries << " total entries" << endl;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		bool TrigThreeMuonJpsi = false;
		bool TrigThreeMuonJpsi3p5mu2 = false;

		for (unsigned int i = 0; i != TrigRes->size(); ++i) { 
			if ((TrigNames->at(i).find("HLT_Dimuon0_Jpsi3p5_Muon2_") != string::npos && TrigRes->at(i) == 1)) {
				TrigThreeMuonJpsi3p5mu2 = true;
			}
			if (TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_") != string::npos && TrigRes->at(i) == 1) {
				TrigThreeMuonJpsi = true;
			}
		} //end of trigger loop

		for (unsigned int myFourMuIdx = 0; myFourMuIdx < nMyFourMuon; myFourMuIdx++) {
			TLorentzVector myFourMuonP4;
			myFourMuonP4.SetXYZM((*MyFourMuonPx)[myFourMuIdx],(*MyFourMuonPy)[myFourMuIdx], (*MyFourMuonPz)[myFourMuIdx], (*MyFourMuonMass)[myFourMuIdx]);

			vector<int> fitMuCharge;
			fitMuCharge.push_back((*muCharge)[(*MyFourMuonMu1Idx)[myFourMuIdx]]);
			fitMuCharge.push_back((*muCharge)[(*MyFourMuonMu2Idx)[myFourMuIdx]]);
			fitMuCharge.push_back((*muCharge)[(*MyFourMuonMu3Idx)[myFourMuIdx]]);
			fitMuCharge.push_back((*muCharge)[(*MyFourMuonMu4Idx)[myFourMuIdx]]);

			vector<TLorentzVector> rawMup4vect, rawMuinFourMuFMp4vect;
			TLorentzVector Rawmu, RawmuinFourMuFM;
			float raw_muPx = (*muPx)[(*MyFourMuonMu1Idx)[myFourMuIdx]];
			float raw_muPy = (*muPy)[(*MyFourMuonMu1Idx)[myFourMuIdx]];
			float raw_muPz = (*muPz)[(*MyFourMuonMu1Idx)[myFourMuIdx]];
			Rawmu.SetXYZM(raw_muPx, raw_muPy,raw_muPz, MUON_MASS);   
			RawmuinFourMuFM = Rawmu; RawmuinFourMuFM.Boost(-myFourMuonP4.BoostVector());
			rawMup4vect.push_back(Rawmu); rawMuinFourMuFMp4vect.push_back(RawmuinFourMuFM);
			raw_muPx = (*muPx)[(*MyFourMuonMu2Idx)[myFourMuIdx]]; raw_muPy = (*muPy)[(*MyFourMuonMu2Idx)[myFourMuIdx]];raw_muPz = (*muPz)[(*MyFourMuonMu2Idx)[myFourMuIdx]];
			Rawmu.SetXYZM(raw_muPx, raw_muPy,raw_muPz, MUON_MASS);  rawMup4vect.push_back(Rawmu);
			RawmuinFourMuFM = Rawmu; RawmuinFourMuFM.Boost(-myFourMuonP4.BoostVector());
			rawMuinFourMuFMp4vect.push_back(RawmuinFourMuFM);
			raw_muPx = (*muPx)[(*MyFourMuonMu3Idx)[myFourMuIdx]]; raw_muPy = (*muPy)[(*MyFourMuonMu3Idx)[myFourMuIdx]];raw_muPz = (*muPz)[(*MyFourMuonMu3Idx)[myFourMuIdx]];
			Rawmu.SetXYZM(raw_muPx, raw_muPy,raw_muPz, MUON_MASS);  rawMup4vect.push_back(Rawmu);
			RawmuinFourMuFM = Rawmu; RawmuinFourMuFM.Boost(-myFourMuonP4.BoostVector());
			rawMuinFourMuFMp4vect.push_back(RawmuinFourMuFM);
			raw_muPx = (*muPx)[(*MyFourMuonMu4Idx)[myFourMuIdx]]; raw_muPy = (*muPy)[(*MyFourMuonMu4Idx)[myFourMuIdx]];raw_muPz = (*muPz)[(*MyFourMuonMu4Idx)[myFourMuIdx]];
			Rawmu.SetXYZM(raw_muPx, raw_muPy,raw_muPz, MUON_MASS);  rawMup4vect.push_back(Rawmu);
			RawmuinFourMuFM = Rawmu; RawmuinFourMuFM.Boost(-myFourMuonP4.BoostVector());
			rawMuinFourMuFMp4vect.push_back(RawmuinFourMuFM);

			vector<TLorentzVector> fitMup4vect;
			TLorentzVector Fitmu;
			//Muon From X Fit:        
			//Fit Muon 1
			float fit_muPx = (*MyFourMuonMu1Px)[myFourMuIdx];
			float fit_muPy = (*MyFourMuonMu1Py)[myFourMuIdx];
			float fit_muPz = (*MyFourMuonMu1Pz)[myFourMuIdx];
			float fit_muM   = MUON_MASS;
			Fitmu.SetXYZM(fit_muPx, fit_muPy,fit_muPz, fit_muM);
			fitMup4vect.push_back(Fitmu);

			fit_muPx = (*MyFourMuonMu2Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu2Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu2Pz)[myFourMuIdx];
			Fitmu.SetXYZM(fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back(Fitmu);
			fit_muPx = (*MyFourMuonMu3Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu3Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu3Pz)[myFourMuIdx];
			Fitmu.SetXYZM(fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back(Fitmu);
			fit_muPx = (*MyFourMuonMu4Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu4Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu4Pz)[myFourMuIdx];
			Fitmu.SetXYZM(fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back(Fitmu);

			// Create combinations of possible muon pairs
			PairedMuonIdx myCombIdx[3];   
			myCombIdx[0].p11 = 0; myCombIdx[0].p12 = 1; myCombIdx[0].p21 = 2; myCombIdx[0].p22 = 3; 
			myCombIdx[1].p11 = 0; myCombIdx[1].p12 = 2; myCombIdx[1].p21 = 1; myCombIdx[1].p22 = 3; 
			myCombIdx[2].p11 = 0; myCombIdx[2].p12 = 3; myCombIdx[2].p21 = 1; myCombIdx[2].p22 = 2; 

			// Conditions to help find 4 muons using different selections (soft, loose, medium, and tight)
			int myNumPatSoftMuon = (*muIsPatSoftMuon)[(*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsPatSoftMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsPatSoftMuon)[(*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsPatSoftMuon)[(*MyFourMuonMu4Idx)[myFourMuIdx]];
			int myNumPatLooseMuon = (*muIsPatLooseMuon)[(*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsPatLooseMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsPatLooseMuon)[(*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsPatLooseMuon)[(*MyFourMuonMu4Idx)[myFourMuIdx]];
			int myNumPatMediumMuon = (*muIsPatMediumMuon)[(*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsPatMediumMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsPatMediumMuon)[(*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsPatMediumMuon)[(*MyFourMuonMu4Idx)[myFourMuIdx]];
			int myNumPatTightMuon = (*muIsPatTightMuon)[(*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsPatTightMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsPatTightMuon)[(*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsPatTightMuon)[(*MyFourMuonMu4Idx)[myFourMuIdx]];
			float DiMuonMass1 = 0.; 
			float DiMuonMass2 = 0.;
            double m4Muon = 0.;
			float DiMuonMass1_noPE = 0.; 
			float DiMuonMass2_noPE = 0.;
            double m4Muon_noPE = 0.;
			float DiMuonMass1_noE = 0.; 
			float DiMuonMass2_noE = 0.;
            double m4Muon_noE = 0.;


			// Minimum selections
			if (1
					// soft muon: tracker muon + 1 hit in the muon system 
					&& myNumPatSoftMuon >= 4 
				) {
				for (int mypidx = 0; mypidx < 3; mypidx++)  {
					int muIdxp11, muIdxp12, muIdxp21, muIdxp22;
					muIdxp11 = myCombIdx[mypidx].p11; muIdxp12 = myCombIdx[mypidx].p12; muIdxp21 = myCombIdx[mypidx].p21; muIdxp22 = myCombIdx[mypidx].p22;
					if(1
                        // Here, require the muon pairs to have muons with opposite charges - which also enables a requirement for total charge = 0
						&& ((fitMuCharge[muIdxp11] + fitMuCharge[muIdxp12]) == 0)
						&& ((fitMuCharge[muIdxp21] + fitMuCharge[muIdxp22]) == 0)
					  )
					{
						// Modify the DiMuonMass expression appropriatly. 
						// Use the fitMup4vect and the muIdxpXY indexes defined above.
						DiMuonMass1 = (fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12]).M(); 
						DiMuonMass2 = (fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).M();
						myDiMuon1mass_before->Fill(DiMuonMass1);
						myDiMuon2mass_before->Fill(DiMuonMass2);

						if (1
								// Here require that each DiMuonMass is in the appropriate mass range [2.95,3.25] GeV
								&& (DiMuonMass1 >= 2.95 && DiMuonMass1 <= 3.25)					   
								&& (DiMuonMass2 >= 2.95 && DiMuonMass2 <= 3.25)					   
							)
						{
							// calculate the 4 muon mass:  M(µ1µ2µ3µ4)-M(µ1µ2)-M(µ3µ4)+2*M(J/psi)  
							m4Muon = (fitMup4vect[muIdxp11]+fitMup4vect[muIdxp12]+fitMup4vect[muIdxp21]+fitMup4vect[muIdxp22]).M() - (DiMuonMass1 + DiMuonMass2) + JPSI_MASS + JPSI_MASS;
							myFourMuonmass_before->Fill(m4Muon);
							noOfMuons_before->Fill(myNumPatSoftMuon);
							vertex_before->Fill((*MyFourMuonVtxCL)[myFourMuIdx]);

							mu1pt_before->Fill(fitMup4vect[muIdxp11].Pt());
							mu2pt_before->Fill(fitMup4vect[muIdxp12].Pt());
							mu3pt_before->Fill(fitMup4vect[muIdxp21].Pt());
							mu4pt_before->Fill(fitMup4vect[muIdxp22].Pt());

							mu1E_before->Fill(fitMup4vect[muIdxp11].E());
							mu2E_before->Fill(fitMup4vect[muIdxp12].E());
							mu3E_before->Fill(fitMup4vect[muIdxp21].E());
							mu4E_before->Fill(fitMup4vect[muIdxp22].E());

							mu1pz_before->Fill(fitMup4vect[muIdxp11].Pz());
							mu2pz_before->Fill(fitMup4vect[muIdxp12].Pz());
							mu3pz_before->Fill(fitMup4vect[muIdxp21].Pz());
							mu4pz_before->Fill(fitMup4vect[muIdxp22].Pz());

							mu1M_before->Fill(fitMup4vect[muIdxp11].M());
							mu2M_before->Fill(fitMup4vect[muIdxp12].M());
							mu3M_before->Fill(fitMup4vect[muIdxp21].M());
							mu4M_before->Fill(fitMup4vect[muIdxp22].M());

							mu1Eta_before->Fill(fitMup4vect[muIdxp11].Eta());
							mu2Eta_before->Fill(fitMup4vect[muIdxp12].Eta());
							mu3Eta_before->Fill(fitMup4vect[muIdxp21].Eta());
							mu4Eta_before->Fill(fitMup4vect[muIdxp22].Eta());

							muAllpt_before->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).Pt());
							muAllE_before->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).E());
							muAllpz_before->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).Pz());
							muAllEta_before->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).Eta());
							muAllM_before->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).M());
							break;
						}
					}

				}
			}


			// All selections applied
			if (1
					// soft muon: tracker muon + 1 hit in the muon system 
					&& myNumPatSoftMuon >= 4 
					// requiring all muons to come from the same vertex
					&& (*MyFourMuonVtxCL)[myFourMuIdx] >= 0.005     
					// Selection on the trigger 
					&& (TrigThreeMuonJpsi3p5mu2 || TrigThreeMuonJpsi)
					// Require a minimum momentum selection
					&& (rawMup4vect[0].Pt()>=2 && rawMup4vect[1].Pt()>=2 && rawMup4vect[2].Pt()>=2 && rawMup4vect[3].Pt()>=2)
					// Provide a selection on the eta
					&& (abs(rawMup4vect[0].Eta())<=2.4 && abs(rawMup4vect[1].Eta())<=2.4 && abs(rawMup4vect[2].Eta())<=2.4 && abs(rawMup4vect[3].Eta())<=2.4)
				) {
				for (int mypidx = 0; mypidx < 3; mypidx++)  {
					int muIdxp11, muIdxp12, muIdxp21, muIdxp22;
					muIdxp11 = myCombIdx[mypidx].p11; muIdxp12 = myCombIdx[mypidx].p12; muIdxp21 = myCombIdx[mypidx].p21; muIdxp22 = myCombIdx[mypidx].p22;
					if(1
                        // Here, require the muon pairs to have muons with opposite charges - which also enables a requirement for total charge = 0
						&& ((fitMuCharge[muIdxp11] + fitMuCharge[muIdxp12]) == 0)
						&& ((fitMuCharge[muIdxp21] + fitMuCharge[muIdxp22]) == 0)
					  )
					{
						// Modify the DiMuonMass expression appropriatly. 
						// Use the fitMup4vect and the muIdxpXY indexes defined above.
						DiMuonMass1 = (fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12]).M(); 
						DiMuonMass2 = (fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).M();
						myDiMuon1mass_after->Fill(DiMuonMass1);
						myDiMuon2mass_after->Fill(DiMuonMass2);

						if (1
								// Here require that each DiMuonMass is in the appropriate mass range [2.95,3.25] GeV
								&& (DiMuonMass1 >= 2.95 && DiMuonMass1 <= 3.25)					   
								&& (DiMuonMass2 >= 2.95 && DiMuonMass2 <= 3.25)					   
							)
						{
							// calculate the 4 muon mass:  M(µ1µ2µ3µ4)-M(µ1µ2)-M(µ3µ4)+2*M(J/psi)  
							m4Muon = (fitMup4vect[muIdxp11]+fitMup4vect[muIdxp12]+fitMup4vect[muIdxp21]+fitMup4vect[muIdxp22]).M() - (DiMuonMass1 + DiMuonMass2) + JPSI_MASS + JPSI_MASS;
							myFourMuonmass_after->Fill(m4Muon);
							noOfMuons_after->Fill(myNumPatSoftMuon);
							vertex_after->Fill((*MyFourMuonVtxCL)[myFourMuIdx]);

							mu1pt_after->Fill(fitMup4vect[muIdxp11].Pt());
							mu2pt_after->Fill(fitMup4vect[muIdxp12].Pt());
							mu3pt_after->Fill(fitMup4vect[muIdxp21].Pt());
							mu4pt_after->Fill(fitMup4vect[muIdxp22].Pt());

							mu1E_after->Fill(fitMup4vect[muIdxp11].E());
							mu2E_after->Fill(fitMup4vect[muIdxp12].E());
							mu3E_after->Fill(fitMup4vect[muIdxp21].E());
							mu4E_after->Fill(fitMup4vect[muIdxp22].E());

							mu1pz_after->Fill(fitMup4vect[muIdxp11].Pz());
							mu2pz_after->Fill(fitMup4vect[muIdxp12].Pz());
							mu3pz_after->Fill(fitMup4vect[muIdxp21].Pz());
							mu4pz_after->Fill(fitMup4vect[muIdxp22].Pz());

							mu1M_after->Fill(fitMup4vect[muIdxp11].M());
							mu2M_after->Fill(fitMup4vect[muIdxp12].M());
							mu3M_after->Fill(fitMup4vect[muIdxp21].M());
							mu4M_after->Fill(fitMup4vect[muIdxp22].M());

							mu1Eta_after->Fill(fitMup4vect[muIdxp11].Eta());
							mu2Eta_after->Fill(fitMup4vect[muIdxp12].Eta());
							mu3Eta_after->Fill(fitMup4vect[muIdxp21].Eta());
							mu4Eta_after->Fill(fitMup4vect[muIdxp22].Eta());

							muAllpt_after->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).Pt());
							muAllE_after->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).E());
							muAllpz_after->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).Pz());
							muAllEta_after->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).Eta());
							muAllM_after->Fill((fitMup4vect[muIdxp11] + fitMup4vect[muIdxp12] + fitMup4vect[muIdxp21] + fitMup4vect[muIdxp22]).M());

							myoutputfile<< std::fixed<< m4Muon<< endl;
							break;
						}
					}

				}
			}
		}

	}

	cout << "I have done " << nentries << " total entries" << endl;
	myhbk->Write();

}
