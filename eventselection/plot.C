#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>

void plot()
{
    // Open the ROOT file
    const char* fileName = "./myhbk.root";
    const char* histogramName = "myFourMuonmass";
    const char* histogramName2 = "myFourMuonmass_noE";
    const char* histogramName3 = "myFourMuonmass_noPE";
    
    TFile* file = TFile::Open(fileName);
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }
    
    // Access the histogram
    TH1F* histogram = (TH1F*)file->Get(histogramName);
    TH1F* histogram2 = (TH1F*)file->Get(histogramName2);
    TH1F* histogram3 = (TH1F*)file->Get(histogramName3);

    if (!histogram) {
        std::cerr << "Error accessing histogram: " << histogramName << " in file: " << fileName << std::endl;
        file->Close();
        return;
    }
    
    TCanvas* canvas = new TCanvas("canvas", "Plot of JpsiJpsi", 1200, 600);
	
	
	histogram3->Draw("hist ");
    histogram3->SetLineColor(kBlack);
    histogram2->Draw("hist same");
    histogram2->SetLineColor(kBlue);
    histogram->Draw("hist same");
    histogram->SetLineColor(kRed);
    histogram3->SetStats(0);
    histogram2->SetStats(0);
    histogram->SetStats(0);

    float num1 = histogram->GetEntries();
    float num2 = histogram2->GetEntries();
    float num3 = histogram3->GetEntries();

    std::cout<<"all selections = "<<num1<<std::endl;
    std::cout<<"all selections  w/o Eta cut = "<<num2<<std::endl;
    std::cout<<"all selections w/o P and Eta cuts = "<<num3<<std::endl;    

	TLegend* legend = new TLegend(0.3, 0.6, 0.7, 0.9);

    TString legendEntry1 = Form("All selections, evts=%.2f", num1);
    TString legendEntry2 = Form("All selections w/o Eta cut, evts=%.2f", num2);
    TString legendEntry3 = Form("All selections w/o P and Eta cuts, evts=%.2f", num3);
    
    legend->AddEntry(histogram, legendEntry1, "l");
    legend->AddEntry(histogram2, legendEntry2, "l");
    legend->AddEntry(histogram3, legendEntry3, "l");
    legend->SetTextSize(0.03);
    legend->Draw();
	canvas->SaveAs("Final_comparison.png");
        
    // Clean up
    // file->Close();
    delete canvas;

    // TCanvas* canvas = new TCanvas("canvas", "Plot of JpsiJpsi", 1200, 600);
    
    // TH1F* noOfMuons
	// TH1F* vertex

	// TH1F* mu1px
	// TH1F* mu2px
	// TH1F* mu3px
	// TH1F* mu4px

	// TH1F* mu1py
	// TH1F* mu2py
	// TH1F* mu3py
	// TH1F* mu4py

	// TH1F* mu1pz
	// TH1F* mu2pz
	// TH1F* mu3pz
	// TH1F* mu4pz

	// TH1F* mu1Eta
	// TH1F* mu2Eta
	// TH1F* mu3Eta
	// TH1F* mu4Eta

	// TH1F* mu1M
	// TH1F* mu2M
	// TH1F* mu3M
	// TH1F* mu4M
}