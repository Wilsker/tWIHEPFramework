import sys, ROOT
import os
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TString, TFile, TH1, THStack, gROOT, TStyle, TAttFill, TLegend, TGraphAsymmErrors, TLine, TLatex
from ROOT import kBlack, kBlue, kRed, kCyan, kViolet, kGreen, kOrange, kGray, kPink, kTRUE

#### start  user defined variables

#inputDirectories = "/home/binghuan/Work/TMP/DiLepRegion/";
inputDirectories = "/publicfs/cms/data/TopQuark/ttV-modelling/tWIHEPFramework/skims/2LSS/1bgeq4j/"
#treename = "syncTree";
treename = "TNT/BOOM";

features={
"n_gen_jets":{"nbin":8,"min":2.5,"max":10.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"n_gen_jets"},
"n_gen_bjets":{"nbin":10,"min":0.5,"max":10.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"n_gen_bjets"},
"n_gen_lepton":{"nbin":5,"min":0.5,"max":5.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"n_gen_lepton"},
"MCGenHTall":{"nbin":10,"min":0.5,"max":1500.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"MCGenHTall"},
"MCGenHThad":{"nbin":10,"min":0.5,"max":1500.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"MCGenHThad"},
"MCGenMET":{"nbin":10,"min":-200.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"MCGenMET"},
"MinDRMCGenLep1Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"MinDRMCGenLep1Jet"},
"MinDrMCGenLep2Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"MinDrMCGenLep2Jet"},
"MinDRMCGenLeps":{"nbin":12,"min":0.0,"max":5.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"MinDRMCGenLeps"},
"gen_bjet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_bjet1_pt"},
"gen_bjet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_bjet2_pt"},
"gen_jet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_jet1_pt"},
"gen_jet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_jet2_pt"},
"gen_jet3_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_jet3_pt"},
"gen_jet4_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_jet4_pt"},
"gen_lepton1_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_lepton1_pt"},
"gen_lepton2_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":"EVENT_event*(n_gen_jets>=4)","xlabel":"gen_lepton2_pt"}
}

binning={}
binning["MCGenHTall"]=[0,120,180,240,300,360,440,540,680,900,1500]
binning["MCGenHThad"]=[0.,90.,140.,180.,240.,300.,380.,460.,540.,650.,850.,1500.]
binning["MCGenHTlep"]=[0,20,50,80,110,150,200,300,400,550,800]
binning["MCGenMET"]=[0,20,50,80,120,180,300,500,1200]
binning["_lepton_"]=[0,20,25,33,45,60,80,110,160,500]


nominal_weights = {'genWeight':'EVENT_genWeight'}
systematics=["nominal","genWeight"]
upDown=["_muF2","_muF0p5"]
#upDown=["_muR2","_muR0p5"]
Color={"nominal":kBlack,"_muF2":kRed,"_muF0p5":kBlue}

# sample name is sampleName+postfix: ex, TTW_DiLepRegion.root
#sampleName = ["TTW"]
sampleName = ["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2016"]

sampleTitle = {
"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2016":"TTW MG+Pyth8"
}

#postfix = "_DiLepRegion.root"
postfix = ".root"


# the root file saving the histograms
createROOTfile = True  # Set to Truth for the first time
filename = "myhist.root"

# options
normalization = False # Normalize to unit
showStats = False

# directory of output
outputdir = "plots/"


##### end user defined variables
# check outputdir
if not os.path.exists(outputdir):
    print ('mkdir: ', outputdir)
    os.makedirs(outputdir)

# create root file, this will overwrite the root file
if createROOTfile:
    exec(open("make_hists.py").read())

def createRatio(h1, h2, POI):
    print 'createRatio'
    h3 = h1.Clone("h3")
    h3.SetMarkerStyle(1)
    h3.SetTitle("")
    # Set up plot for markers and errors
    h3.Sumw2()
    h3.SetStats(0)
    h3.Divide(h2)
    # Adjust y-axis settings
    y = h3.GetYaxis()
    y.SetTitle("var/nominal")
    y.CenterTitle()
    y.SetNdivisions(505)
    y.SetTitleSize(25)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.55)
    y.SetLabelFont(43)
    y.SetLabelSize(20)
    # Adjust x-axis settings
    x = h3.GetXaxis()
    x.SetTitle(POI)
    x.SetTitleSize(25)
    x.SetTitleFont(43)
    x.SetTitleOffset(3.0)
    x.SetLabelFont(43)
    x.SetLabelSize(20)
    return h3

def createCanvasPads():
    c = TCanvas("c", "canvas", 800, 800)
    # Upper histogram plot is pad1
    pad1 = TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
    pad1.SetBottomMargin(0)  # joins upper and lower plot
    pad1.SetTicks(0,1)
    pad1.Draw()
    # Lower ratio plot is pad2
    c.cd()  # returns to main canvas before defining pad2
    pad2 = TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
    pad2.SetTopMargin(0)  # joins upper and lower plot
    pad2.SetBottomMargin(0.25)
    pad2.SetTicks(0,1)
    pad2.Draw()

    return c, pad1, pad2


def plotSysts():
    inputfile = TFile(filename,"read")
    if inputfile.IsZombie():
        print("inputfile is Zombie")
        sys.exit()
    # loop over samples
    for sample in sampleName:
        # loop over features
        for feature, values in features.items():
            # get nominal histograms
            hist_nom_name = sample+"_"+feature
            if not inputfile.GetListOfKeys().Contains(hist_nom_name):
                print ( "%s doesn't have histogram %s"%(filename, hist_nom_name))
                continue
            hist_nom = inputfile.Get(hist_nom_name)
            hist_nom.SetFillColor(0)
            hist_nom.SetLineColor(Color["nominal"])
            hist_nom.SetMarkerColor(Color["nominal"])
            h_ratio = createRatio(hist_nom, hist_nom, values["xlabel"])
            # loop over variations
            for syst in systematics:
                if syst=="nominal": continue

                # set up legend
                legend = TLegend(0.6,0.6,0.88,0.88)
                legend.SetBorderSize(0)
                hist_nickname = ''
                hist_nickname = sampleTitle[sample]
                legend.AddEntry(hist_nom,hist_nickname,"l")

                c, pad1, pad2 = createCanvasPads()
                hist_vars = []
                hist_ratio_vars = []
                for var in upDown:
                    hist_name = sample+"_"+feature+"_"+syst+var
                    if not inputfile.GetListOfKeys().Contains(hist_name):
                        print ( "%s doesn't have histogram %s"%(filename, hist_name))
                        continue
                    hist_nickname_plus_syst = ''
                    hist_nickname_plus_syst = hist_nickname + ' ' + var[1:]
                    hist_var = inputfile.Get(hist_name)
                    hist_var.SetFillColor(0)
                    hist_var.SetLineColor(Color[var])
                    hist_var.SetMarkerColor(Color[var])
                    hist_vars.append(hist_var)
                    h_ratio_var = createRatio(hist_var, hist_nom,values["xlabel"])
                    hist_ratio_vars.append(h_ratio_var)
                    legend.AddEntry(h_ratio_var,hist_nickname_plus_syst,"l")

                # draw everything
                pad1.cd()
                pad1.SetGridx()
                pad1.SetGridy()
                # set bounds
                maximum=0
                for hist in hist_vars:
                    if normalization:
                        hist.Scale(1./hist.Integral())
                    if hist.GetMaximum()>maximum: maximum = hist.GetMaximum()
                upperbound = 1.8*maximum
                lowerbound = -maximum/40.

                Y_name = "Events"
                if normalization:
                    hist_nom.Scale(1./hist_nom.Integral())
                    Y_name = " Unit "
                if showStats:
                    hist_nom.SetStats(1)

                hist_nom.SetMaximum(upperbound)
                hist_nom.SetMinimum(lowerbound)
                print 'Adjust y-axis settings'
                # Adjust y-axis settings
                y = hist_nom.GetYaxis()
                y.SetTitleSize(25)
                y.SetTitleFont(43)
                y.SetTitleOffset(1.55)
                y.SetLabelFont(43)
                y.SetLabelSize(20)
                y.SetTitle(Y_name)

                print 'Adjust x-axis settings'
                # Adjust x-axis settings
                x = hist_nom.GetXaxis()
                x.SetTitleSize(25)
                x.SetTitleFont(43)
                x.SetTitleOffset(1.55)
                x.SetLabelFont(43)
                x.SetLabelSize(20)
                x.SetTitle(values["xlabel"])

                hist_nom.Draw("HIST")

                for hist in hist_vars:
                    hist.Draw("HISTsame")

                legend.Draw("same")
                label = ROOT.TLatex()
                label.SetTextSize(0.05)
                label.SetTextAlign(13)
                label.DrawLatexNDC(.2,.8,"CMS preliminary")

                pad2.cd()
                pad2.SetGridx()
                pad2.SetGridy()
                bins = h_ratio.GetNbinsX()
                LowEdge = h_ratio.GetBinLowEdge(1)
                print 'LowEdge: ', LowEdge
                HighEdge = h_ratio.GetBinLowEdge(bins+1)
                print 'HighEdge: ', HighEdge
                line = TLine(LowEdge,1,HighEdge,1)
                line.SetLineColor(kBlack)
                for i in range(len(hist_ratio_vars)):
                    if i==0:
                        hist_ratio_vars[i].Draw("hist")
                        hist_ratio_vars[i].SetMinimum(0.5)
                        hist_ratio_vars[i].SetMaximum(1.5)
                    else:
                        hist_ratio_vars[i].Draw("histsame")
                line.Draw("same")

                c.SaveAs("%s%s_%s_isNorm%s_wtStat%s.png"%(outputdir,hist_nom_name,syst,normalization,showStats))

# Draw all canvases
if __name__ == "__main__":
    plotSysts()
