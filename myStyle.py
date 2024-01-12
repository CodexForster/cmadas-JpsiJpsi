import ROOT
import os

## Define global variables
marg=0.05
font=43 # Helvetica
tsize=38 #35

### Style functions
def ForceStyle():
    # ## Defining Style
    ROOT.gStyle.SetPadTopMargin(marg)       #0.05
    ROOT.gStyle.SetPadRightMargin(marg)     #0.05
    ROOT.gStyle.SetPadBottomMargin(2*marg)  #0.10
    ROOT.gStyle.SetPadLeftMargin(2*marg)    #0.10

    ROOT.gStyle.SetPadTickX(1)
    ROOT.gStyle.SetPadTickY(1)

    ROOT.gStyle.SetTextFont(font)
    # ROOT.gStyle.SetLabelFont(font,"x")
    ROOT.gStyle.SetTitleFont(font,"x")
    ROOT.gStyle.SetLabelFont(font,"y")
    ROOT.gStyle.SetTitleFont(font,"y")
    ROOT.gStyle.SetLabelFont(font,"z")
    ROOT.gStyle.SetTitleFont(font,"z")

    ROOT.gStyle.SetTextSize(tsize)
    ROOT.gStyle.SetLabelSize(tsize-4,"x")
    ROOT.gStyle.SetTitleSize(tsize,"x")
    ROOT.gStyle.SetLabelSize(tsize-4,"y")
    ROOT.gStyle.SetTitleSize(tsize,"y")
    ROOT.gStyle.SetLabelSize(tsize-4,"z")
    ROOT.gStyle.SetTitleSize(tsize,"z")

    # ROOT.gStyle.SetLegendFont(font)
    # ROOT.gStyle.SetLegendTextSize(tsize)
    # ROOT.gStyle.SetLegendBorderSize(0)
    # ROOT.gStyle.SetLegendFillColor(0)

    ROOT.gStyle.SetTitleXOffset(1.0)
    ROOT.gStyle.SetTitleYOffset(1.0)
    ROOT.gStyle.SetOptTitle(0)
    # ROOT.gStyle.SetOptStat(0)

    ROOT.gStyle.SetHistLineWidth(4)

    ROOT.gStyle.SetGridColor(921)
    ROOT.gStyle.SetGridStyle()

    ROOT.gROOT.ForceStyle()


def DetInfo(mtop=marg, mleft=2*marg):
    text = ROOT.TLatex()
    text.SetTextSize(tsize-4)
    text.DrawLatexNDC(mleft+0.005, 1-mtop+0.01, "#bf{CMS} Internal")

def LumiInfo(data="Name", adjustleft=0, mtop=marg, mright=marg):
    text = ROOT.TLatex()
    text.SetTextSize(tsize-4)
    text.SetTextAlign(31)
    text.DrawLatexNDC(1-mright-0.005-adjustleft, 1-mtop+0.01, data)

### Change global values functions
def ChangeMargins(mtop=marg, mright=marg, mbot=2*marg, mleft=2*marg):
    ROOT.gStyle.SetPadTopMargin(mtop)
    ROOT.gStyle.SetPadRightMargin(mright)
    ROOT.gStyle.SetPadBottomMargin(mbot)
    ROOT.gStyle.SetPadLeftMargin(mleft)

    ROOT.gROOT.ForceStyle()


### Return global values functions
def GetMargin():
    return marg

def GetFont():
    return font

def GetSize():
    return tsize

def GetPadCenter(mleft=2*marg, mright=marg):
    center = 1/2 + mleft/2 - mright/2
    return center


### Colors
def GetColors(color_blind = False):
    strip_colors = [416+2, 432+2, 600, 880, 632, 400+2, 600-5]
    ## [#kGreen+2, #kCyan+2, #kBlue, #kViolet, #kRed, #kYellow+2, #kBlue-3]
    if color_blind:
        color_RGB = [[51,34,136],[51,187,238],[17,119,51],[153,153,51],[204,102,119],[136,34,85],[128,128,128]]
        # [indigo, cyan, green, olive, rose, wine]
        
        for i in range(0,len(strip_colors)):
            strip_colors[i] = ROOT.TColor.GetColor(color_RGB[i][0],color_RGB[i][1],color_RGB[i][2])

    return strip_colors

def GetColorsCompare(n_sensors):
    basic_palette = GetColors(True)
    palette = basic_palette
    if n_sensors == 2:
        palette = [basic_palette[0], basic_palette[2]]
    elif n_sensors == 4:
        palette = [basic_palette[0], basic_palette[2], basic_palette[3], basic_palette[4]]

    return palette
