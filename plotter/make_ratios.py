import sys, ROOT
import os
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TString, TFile, TH1, THStack, gROOT, TStyle, TAttFill, TLegend, TGraphAsymmErrors, TLine, TLatex
from ROOT import kBlack, kBlue, kRed, kCyan, kViolet, kGreen, kOrange, kGray, kPink, kTRUE

#### start  user defined variables

#inputDirectories = ["/publicfs/cms/data/TopQuark/ttV-modelling/tWIHEPFramework/skims/2LSS/1bgeq4j/"]
inputDirectories = ["/publicfs/cms/data/TopQuark/ttV-modelling/condor/ttH2016All2L/Legacy16V1_TTWJets/skims/"]
region_ = ""
treename = "TNT/BOOM";

#"genWeight_muR1muF2":{"nbin":20,"min":-5.5,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4)","xlabel":"muR1muF2"}
features={
"n_gen_jets":{"nbin":8,"min":2.5,"max":10.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"n_gen_jets"},
"n_gen_bjets":{"nbin":10,"min":0.5,"max":10.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"n_gen_bjets"},
#"n_gen_lepton":{"nbin":5,"min":0.5,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"n_gen_lepton"},
"MCGenHTall":{"nbin":10,"min":0.5,"max":1500.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"MCGenHTall"},
"MCGenHThad":{"nbin":10,"min":0.5,"max":1500.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"MCGenHThad"},
#"MCGenMET":{"nbin":10,"min":-200.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"MCGenMET"},
"MinDRMCGenLep1Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"MinDRMCGenLep1Jet"},
"MinDrMCGenLep2Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"MinDrMCGenLep2Jet"},
#"MinDRMCGenLeps":{"nbin":12,"min":0.0,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"MinDRMCGenLeps"},
#"gen_bjet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_bjet1_pt"},
#"gen_bjet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_bjet2_pt"},
#"gen_jet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_jet1_pt"},
#"gen_jet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_jet2_pt"},
#"gen_jet3_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_jet3_pt"},
"gen_jet4_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_jet4_pt"},
"gen_lepton1_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_lepton1_pt"},
"gen_lepton2_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"gen_lepton2_pt"}
#"Bin2l":{"nbin":20,"min":0.5,"max":500.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"Bin2l"},
#"genWeight_muR1muF1":{"nbin":20,"min":-5.5,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"muR1muF1"},
#"genWeight_muR2muF2":{"nbin":20,"min":-5.5,"max":5.5,"cut":"EventWeight*(n_gen_jets>=4 && n_gen_bjets==1)","xlabel":"muR2muF2"}
}

ATLAS_feature_map={
"n_gen_jets":"nJets_0",
"n_gen_bjets":"nBtagJets_0",
"n_gen_lepton":"",
"MCGenHTall":"HT_0",
"MCGenHThad":"HT_jets_0",
"MCGenMET":"MET",
"MinDRMCGenLep1Jet":"min_DRl0j_0",
"MinDrMCGenLep2Jet":"min_DRl1j_0",
"MinDRMCGenLeps":"DRll01_0",
"gen_bjet1_pt":"Bjet_Pt_0_0",
"gen_bjet2_pt":"Bjet_Pt_1_0",
#"gen_jet1_pt":"jet_Pt_0_0",
#"gen_jet2_pt":"jet_Pt_2_0",
#"gen_jet3_pt":"jet_Pt_3_0",
"gen_jet4_pt":"jet_Pt_4_0",
"gen_lepton1_pt":"lep_Pt_0_0",
"gen_lepton2_pt":"lep_Pt_1_0"
}

binning={}
binning["MCGenHTall"]=[0,120,180,240,300,360,440,540,680,900,1500]
binning["MCGenHThad"]=[0,90,140,180,240,300,380,460,540,650,850,1500]
binning["MCGenHTlep"]=[0,20,50,80,110,150,200,300,400,550,800]
binning["MCGenMET"]=[0,20,50,80,120,180,300,500,1200]
binning["gen_lepton1_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_lepton2_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_bjet1_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_bjet2_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_jet1_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_jet2_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_jet3_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["gen_jet4_pt"]=[0,20,25,33,45,60,80,110,160,500]
binning["n_gen_jets"]=[0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5]
binning["n_gen_bjets"]=[0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5]
binning["n_gen_lepton"]=[0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5]
binning["Bin2l"]=[0,1,2,3,4,5,6,7,8,9,10,11]
binning["MinDRMCGenLep1Jet"]=[0,0.4,0.8,1.2,1.6,2.,2.4,2.8,3.2,3.6,4.,4.0,4.8]
binning["MinDrMCGenLep2Jet"]=[0,0.4,0.8,1.2,1.6,2.,2.4,2.8,3.2,3.6,4.,4.0,4.8]
binning["MinDRMCGenLeps"]=[0,0.4,0.8,1.2,1.6,2.,2.4,2.8,3.2,3.6,4.,4.0,4.8]
binning["genWeight_muR1muF1"]=[-2.,-1.8,-1.6,-1.4,-1.2,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2.]
binning["genWeight_muR2muF2"]=[-5.5,-4.5,-3.5,-2.5,-1.5,-0.5,0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5]

nominal_weights = {'genWeight':'EVENT_genWeight'}
systematics=["nominal","genWeight"]
sixpoint_variations=["muR1muF2","muR1muF0p5","muR2muF1","muR2muF2","muR2muF0p5","muR0p5muF1","muR0p5muF2","muR0p5muF0p5"]
Color={"nominal":1,"muR1muF1":2,"muR1muF2":3,"muR1muF0p5":4,"muR2muF1":5,"muR2muF2":6,"muR2muF0p5":7,"muR0p5muF1":8,"muR0p5muF2":9,"muR0p5muF0p5":15}

# sample name is sampleName+postfix: ex, TTW_DiLepRegion.root
#sampleName = ["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2016"]
sampleName = ["mergedLegacy16V1_TTWJets"]

sampleTitle = {
#"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2016":"TTW MG+Pyth8"
"mergedLegacy16V1_TTWJets":"TTW MG+Pyth8"
}

postfix = ".root"

# the root file saving the histograms
createROOTfile = True  # Set to Truth for the first time
filename = "myhist.root"

# ATLAS ROOT file
ATLAS_filename = 'ATLAS_TTW_Sherpa_2509.root'

# options
normalization = True # Normalize to unit
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
    h3 = h1.Clone("h3")
    h3.SetMarkerStyle(1)
    h3.SetTitle("")
    # Set up plot for markers and errors
    #h3.Sumw2()
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
    ATLASfile = TFile(ATLAS_filename,"read")
    if inputfile.IsZombie():
        print("inputfile is Zombie")
        sys.exit()
    # loop over samples
    for region in inputDirectories:
        region_ = region
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

                c, pad1, pad2 = createCanvasPads()
                hist_vars = []
                hist_ratio_vars = []
                # set up legend
                legend = TLegend(0.6,0.6,0.88,0.88)
                legend.SetBorderSize(0)
                hist_nickname = ''
                hist_nickname = sampleTitle[sample]
                legend.AddEntry(hist_nom,hist_nickname,"l")

                # loop over variations
                syst_counter = 0
                for syst in systematics:
                    print 'syst = ', syst
                    if syst=="nominal":
                        continue
                    syst_counter = syst_counter + 1
                    if 'genWeight_' in feature:
                        hist_name = sample+"_"+feature
                        if not inputfile.GetListOfKeys().Contains(hist_name):
                            print ( "%s doesn't have histogram %s"%(filename, hist_name))
                            continue
                        hist_var = inputfile.Get(hist_name)
                        hist_var.SetFillColor(0)
                        hist_var.SetLineColor(1)
                        hist_var.SetMarkerColor(1)
                        hist_vars.append(hist_var)
                        h_ratio_var = createRatio(hist_var, hist_nom ,values["xlabel"])
                        hist_ratio_vars.append(h_ratio_var)
                    else:
                        for sixpoint_index in sixpoint_variations:
                            hist_name = sample+"_"+feature+"_"+syst+"_"+sixpoint_index
                            if not inputfile.GetListOfKeys().Contains(hist_name):
                                print ( "%s doesn't have histogram %s"%(filename, hist_name))
                                continue
                            hist_nickname_plus_syst = ''
                            hist_nickname_plus_syst = hist_nickname + ' ' + sixpoint_index
                            hist_var = inputfile.Get(hist_name)
                            hist_var.SetFillColor(0)
                            hist_var.SetLineColor(Color[sixpoint_index])
                            hist_var.SetMarkerColor(Color[sixpoint_index])
                            hist_vars.append(hist_var)
                            h_ratio_var = createRatio(hist_var, hist_nom,values["xlabel"])
                            print 'append %s hist to hist_ratio_vars' % (sixpoint_index)
                            hist_ratio_vars.append(h_ratio_var)
                            legend.AddEntry(h_ratio_var,hist_nickname_plus_syst,"l")


                    print '%s: ATLAS feature equivalent = %s ' % (feature,ATLAS_feature_map.get(feature))
                    hist_atlas = ATLASfile.Get(ATLAS_feature_map.get(feature))
                    hist_atlas.SetFillColor(0)
                    hist_atlas.SetLineColor(46)
                    hist_atlas.SetMarkerColor(46)
                    legend.AddEntry(hist_atlas,"ATLAS Sherpa","l")
                    hist_vars.append(hist_atlas)
                    h_ratio_atlas = createRatio(hist_atlas,hist_nom,values["xlabel"])
                    hist_ratio_vars.append(h_ratio_atlas)

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
                    # Adjust y-axis settings
                    y = hist_nom.GetYaxis()
                    y.SetTitleSize(25)
                    y.SetTitleFont(43)
                    y.SetTitleOffset(1.55)
                    y.SetLabelFont(43)
                    y.SetLabelSize(20)
                    y.SetTitle(Y_name)
                    # Adjust x-axis settings
                    x = hist_nom.GetXaxis()
                    x.SetTitleSize(25)
                    x.SetTitleFont(43)
                    x.SetTitleOffset(1.55)
                    x.SetLabelFont(43)
                    x.SetLabelSize(20)
                    x.SetTitle(values["xlabel"])

                    hist_nom.SetMarkerStyle(20)
                    hist_nom.Draw("HIST")
                    hist_atlas.SetMarkerStyle(20)
                    hist_atlas.Draw("HIST SAME")

                    for hist in hist_vars:
                        hist.SetMarkerStyle(20)
                        hist.Draw("HIST SAME")

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
                    HighEdge = h_ratio.GetBinLowEdge(bins+1)
                    line = TLine(LowEdge,1,HighEdge,1)
                    line.SetLineColor(kBlack)

                    print "Number of variations: ", len(hist_ratio_vars)
                    for i in range(len(hist_ratio_vars)):
                        print 'i: ', i
                        if i==0:
                            hist_ratio_vars[i].Draw("hist")
                            hist_ratio_vars[i].SetMinimum(0.4)
                            hist_ratio_vars[i].SetMaximum(1.6)
                        else:
                            hist_ratio_vars[i].Draw("histsame")
                    if 'genWeight_' not in feature:
                        line.Draw("same")

                    c.SaveAs("%s%s_%s_isNorm%s_wtStat%s.png"%(outputdir,hist_nom_name,syst,normalization,showStats))

# Draw all canvases
if __name__ == "__main__":
    plotSysts()
