# from CMSPLOTS.myFunction import DrawHistos
import ROOT
import os
ROOT.gROOT.SetBatch(True)
import myStyle

# # change this input address
# finput = "../myhbk.root"

# f = ROOT.TFile(finput)

# hname = "myFourMuonmass"
# h = f.Get(hname)
# h.SetLineColor(1)
# h.SetMarkerStyle(20)

# DrawHistos(num_events, ["Data"], 0, len(cut_names), "m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV/c^{2}]", 0, 50, "Number of Events", outputname = "cutFlow", dology=False, nMaxDigits=3)

# DrawHistos([h1, h2], ["1st J/psi", "2nd J/psi"], 2.5, 3.5, "m(#mu^{+}#mu^{-}) [GeV/c^{2}]", 0, 2000, "Events / (0.1 GeV/c^{2})", outputname = "dimuon_mass", dology=False, legendoptions=["ep", "ep"], addOverflow=True, addUnderflow=True, nMaxDigits=3)


ROOT.gStyle.SetOptTitle(0)  # Turn off the default histogram title
ROOT.gStyle.SetOptStat(0)   # Turn off the statistics box

# myStyle.ForceStyle()

# Create a list of cut names
cut_names = ["No cuts", "#mu number > 4", "Vertex probability", "Trigger", "p_{T}", "#eta", "Q(#mu^{+}#mu^{-})", "m(#mu^{+}#mu^{-})"]
num_events = [7617771, 7584500, 311677, 185361, 170416, 165594, 165594, 9769]

# Create a histogram to store the number of events after each cut
histogram = ROOT.TH1F("histogram", "Cut flow histogram", len(cut_names), 0, len(cut_names))

# Fill the histogram with some example data (replace this with your actual data)
# Here, I'm filling it with random numbers for illustration purposes.
for i in range(1,len(cut_names)+1):
    histogram.SetBinContent(i, num_events[i-1])
    histogram.GetXaxis().SetBinLabel(i, cut_names[i-1])
# Create a canvas and draw the histogram
# canvas = ROOT.TCanvas("canvas", "Cut Efficiency", 1200, 1200)
canvas = ROOT.TCanvas("cv","cv",1000,800)
canvas.SetGrid(0,1)
canvas.SetBottomMargin(0.2)
canvas.SetLogy()
# Set gridlines
canvas.SetGrid()
histogram.SetStats(0)  # Turn off the statistics box
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.SetFillColorAlpha(ROOT.kBlue,0.5)
histogram.GetYaxis().SetRangeUser(1, 100000000)
histogram.Draw("HIST TEXT30 SAME")  # Draw as a bar chart

# Set axis titles and labels
histogram.GetXaxis().SetTitle("Selections applied")
histogram.GetYaxis().SetTitle("Number of Events")

# # Set axis title offsets
histogram.GetXaxis().SetLabelOffset(0.01)
histogram.GetXaxis().SetTitleOffset(1.4)

myStyle.DetInfo()
myStyle.LumiInfo("137 fb^{-1} (13 TeV)")

# histogram.GetXaxis().SetLabelSize(0.04)  # Set X-axis label font size
# histogram.GetXaxis().SetTitleOffset(2)  # Adjust the vertical position of the Y-axis title


# Show the canvas
canvas.Update()
canvas.SaveAs("./CutFlow_Danush.png")