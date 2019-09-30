import sys, ROOT
import os
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TString, TFile, TH1, THStack, gROOT, TStyle, TAttFill, TLegend, TGraphAsymmErrors, TLine, TLatex
from ROOT import kBlack, kBlue, kRed, kCyan, kViolet, kGreen, kOrange, kGray, kPink, kTRUE

#### start  user defined variables

inputDirectories = ["/publicfs/cms/data/TopQuark/ttV-modelling/condor/ttH2016All2L/Legacy16V1_TTWJets/skims/"]

treename = "TNT/BOOM";

region_ = {
"2lss_1bgeq4j":"(n_gen_jets>=4 && n_gen_bjets==1)",
"2lss_1beeq3j":"(n_gen_jets==3 && n_gen_bjets==1)",
"2lss_2bgeq4j":"(n_gen_jets>=4 && n_gen_bjets>=2)",
"2lss_2beeq3j":"(n_gen_jets==3 && n_gen_bjets>=2)"
}

nominal_weights = {'genWeight':'EVENT_genWeight'}
systematics=["nominal","genWeight"]
#sixpoint_variations=["muR1muF2","muR1muF0p5","muR2muF1","muR2muF2","muR2muF0p5","muR0p5muF1","muR0p5muF2","muR0p5muF0p5"]
sixpoint_variations=["muR2muF2","muR0p5muF0p5"]
Color={"nominal":1,"muR1muF1":2,"muR1muF2":3,"muR1muF0p5":4,"muR2muF1":5,"muR2muF2":6,"muR2muF0p5":7,"muR0p5muF1":8,"muR0p5muF2":9,"muR0p5muF0p5":15}

# sample name is sampleName+postfix: ex, TTW_DiLepRegion.root
sampleName = ["mergedLegacy16V1_TTWJets"]

sampleTitle = {
"mergedLegacy16V1_TTWJets":"TTW MG+Pyth8"
}

postfix = ".root"

createROOTfile = True  # Set to Truth for the first time

# ATLAS ROOT file
ATLAS_filename = 'ATLAS_TTW_Sherpa_2609.root'
ATLAS_scaleUp_filename = 'ATLAS_TTW_Sherpa_ScaleUp_2609.root'
ATLAS_scaleDown_filename = 'ATLAS_TTW_Sherpa_ScaleDown_2609.root'

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

    ATLASfile = TFile(ATLAS_filename,"read")
    ATLASfile_scaleUp = TFile(ATLAS_scaleUp_filename,"read")
    ATLASfile_scaleDown = TFile(ATLAS_scaleDown_filename,"read")

    if ATLASfile.IsZombie():
        print("ATLASfile is Zombie")
        sys.exit()
    if ATLASfile_scaleUp.IsZombie():
        print("ATLASfile_scaleUp is Zombie")
        sys.exit()
    if ATLASfile_scaleDown.IsZombie():
        print("ATLASfile_scaleDown is Zombie")
        sys.exit()
    # loop over samples
    for region, cuts_values in region_.items():
        # the root file saving the histograms
        print 'region: %s, cuts_values: %s' % (region,cuts_values)
        filename = "myhist_%s.root" % region
        inputfile = TFile(filename,"read")
        if inputfile.IsZombie():
            print("inputfile is Zombie")
            sys.exit()
        cut_string = "EventWeight*"+cuts_values
        features={
        "n_gen_jets":{"nbin":8,"min":2.5,"max":10.5,"cut":cut_string,"xlabel":"n_gen_jets"},
        "n_gen_bjets":{"nbin":10,"min":0.5,"max":10.5,"cut":cut_string,"xlabel":"n_gen_bjets"},
        "MCGenHTall":{"nbin":10,"min":0.5,"max":1500.5,"cut":cut_string,"xlabel":"MCGenHTall"},
        "MCGenHThad":{"nbin":10,"min":0.5,"max":1500.5,"cut":cut_string,"xlabel":"MCGenHThad"},
        "MinDRMCGenLep1Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":cut_string,"xlabel":"MinDRMCGenLep1Jet"},
        "MinDrMCGenLep2Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":cut_string,"xlabel":"MinDrMCGenLep2Jet"},
        "gen_jet4_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"gen_jet4_pt"},
        "gen_jet5_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"gen_jet5_pt"},
        "gen_jet6_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"gen_jet6_pt"},
        "gen_lepton1_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":cut_string,"xlabel":"gen_lepton1_pt"},
        "gen_lepton2_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":cut_string,"xlabel":"gen_lepton2_pt"},
        "gen_bjet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"gen_bjet1_pt"},
        "gen_bjet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"gen_bjet2_pt"},
        "MinDRMCGenLeps":{"nbin":12,"min":0.0,"max":5.5,"cut":cut_string,"xlabel":"MinDRMCGenLeps"}
        }

        ATLAS_region_index='0'
        if "1bgeq4j" in region:
            ATLAS_region_index = '0'
        if "2bgeq4j" in region:
            ATLAS_region_index = '1'
        if "1beeq3j" in region:
            ATLAS_region_index = '2'
        if "2beeq3j" in region:
            ATLAS_region_index = '3'

        ATLAS_feature_map={
        "n_gen_jets":"nJets_"+ATLAS_region_index,
        "n_gen_bjets":"nBtagJets_"+ATLAS_region_index,
        "n_gen_lepton":"",
        "MCGenHTall":"HT_"+ATLAS_region_index,
        "MCGenHThad":"HT_jets_"+ATLAS_region_index,
        "MCGenMET":"MET_"+ATLAS_region_index,
        "MinDRMCGenLep1Jet":"min_DRl0j_"+ATLAS_region_index,
        "MinDrMCGenLep2Jet":"min_DRl1j_"+ATLAS_region_index,
        "MinDRMCGenLeps":"DRll01_"+ATLAS_region_index,
        "gen_bjet1_pt":"Bjet_Pt_0_"+ATLAS_region_index,
        "gen_bjet2_pt":"Bjet_Pt_1_"+ATLAS_region_index,
        "gen_jet4_pt":"jet_Pt_4_"+ATLAS_region_index,
        "gen_jet5_pt":"jet_Pt_5_"+ATLAS_region_index,
        "gen_jet6_pt":"jet_Pt_6_"+ATLAS_region_index,
        "gen_lepton1_pt":"lep_Pt_0_"+ATLAS_region_index,
        "gen_lepton2_pt":"lep_Pt_1_"+ATLAS_region_index
        }

        for sample in sampleName:
            print 'sample: ', sample
            # loop over features
            for feature, values in features.items():
                print 'make_ratios:: feature: %s , values: %s' % (feature, values)
                # get nominal histograms
                hist_nom_name = sample+"_"+feature
                if not inputfile.GetListOfKeys().Contains(hist_nom_name):
                    print ( "make_ratios:: %s doesn't have histogram %s"%(filename, hist_nom_name))
                    continue
                hist_nom = inputfile.Get(hist_nom_name)
                hist_nom.SetFillColor(0)
                hist_nom.SetLineColor(Color["nominal"])
                hist_nom.SetLineWidth(3)
                hist_nom.SetMarkerColor(Color["nominal"])
                if normalization:
                    hist_nom.Scale(1./hist_nom.Integral())
                # Need to scale down to 1/XS*BR*Lumi = 7040.32 to match ATLAS fiducial normalisation
                # Scale up to correct ttW inclusive XS = 600.8
                hist_nom.Scale(600.8/7040.32)
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
                    print 'make_ratios:: syst = ', syst
                    if syst=="nominal":
                        continue
                    syst_counter = syst_counter + 1
                    if 'genWeight_' in feature:
                        hist_name = sample+"_"+feature
                        if not inputfile.GetListOfKeys().Contains(hist_name):
                            print ( "make_ratios:: %s doesn't have histogram %s"%(filename, hist_name))
                            continue
                        hist_var = inputfile.Get(hist_name)
                        hist_var.SetFillColor(0)
                        hist_var.SetLineColor(1)
                        hist_var.SetMarkerColor(1)
                        hist_var.SetLineWidth(3)
                        if normalization:
                            hist_var.Scale(1./hist_var.Integral())
                        hist_var.Scale(600.8/7040.32)
                        hist_vars.append(hist_var)
                        h_ratio_var = createRatio(hist_var, hist_nom ,values["xlabel"])
                        hist_ratio_vars.append(h_ratio_var)
                    else:
                        for sixpoint_index in sixpoint_variations:
                            hist_name = sample+"_"+feature+"_"+syst+"_"+sixpoint_index
                            if not inputfile.GetListOfKeys().Contains(hist_name):
                                print ( "make_ratios:: %s doesn't have histogram %s"%(filename, hist_name))
                                continue
                            hist_nickname_plus_syst = ''
                            hist_nickname_plus_syst = hist_nickname + ' ' + sixpoint_index
                            hist_var = inputfile.Get(hist_name)
                            hist_var.SetFillColor(0)
                            hist_var.SetLineColor(Color[sixpoint_index])
                            hist_var.SetMarkerColor(Color[sixpoint_index])
                            hist_var.SetLineWidth(3)
                            if normalization:
                                hist_var.Scale(1./hist_var.Integral())
                            hist_var.Scale(600.8/7040.32)
                            hist_vars.append(hist_var)
                            h_ratio_var = createRatio(hist_var, hist_nom,values["xlabel"])
                            hist_ratio_vars.append(h_ratio_var)
                            legend.AddEntry(h_ratio_var,hist_nickname_plus_syst,"l")


                    print 'make_ratios:: %s: ATLAS feature equivalent = %s ' % (feature,ATLAS_feature_map.get(feature))
                    hist_atlas = ATLASfile.Get(ATLAS_feature_map.get(feature))
                    hist_atlas.SetName(feature+"_nominal")
                    hist_atlas_scaleUp = ATLASfile_scaleUp.Get(ATLAS_feature_map.get(feature))
                    hist_atlas.SetName(feature+"_scaleUp")
                    hist_atlas_scaleDown = ATLASfile_scaleDown.Get(ATLAS_feature_map.get(feature))
                    hist_atlas.SetName(feature+"_scaleDown")
                    # Need to scale ATLAS plot by XS = 600.8 fb
                    hist_atlas.Scale(600.8)
                    hist_atlas_scaleUp.Scale(600.8)
                    hist_atlas_scaleDown.Scale(600.8)
                    hist_atlas.SetFillColor(0)
                    hist_atlas_scaleUp.SetFillColor(0)
                    hist_atlas_scaleDown.SetFillColor(0)
                    hist_atlas.SetLineColor(46)
                    hist_atlas_scaleUp.SetLineColor(40)
                    hist_atlas_scaleDown.SetLineColor(30)
                    hist_atlas.SetMarkerColor(46)
                    hist_atlas_scaleUp.SetMarkerColor(40)
                    hist_atlas_scaleDown.SetMarkerColor(30)
                    hist_atlas.SetLineWidth(3)
                    hist_atlas_scaleUp.SetLineWidth(3)
                    hist_atlas_scaleDown.SetLineWidth(3)

                    legend.AddEntry(hist_atlas,"ATLAS Sherpa","l")
                    legend.AddEntry(hist_atlas_scaleUp,"ATLAS Sherpa Scale Up","l")
                    legend.AddEntry(hist_atlas_scaleDown,"ATLAS Sherpa Scale Down","l")

                    if normalization:
                        hist_atlas.Scale(1./hist_atlas.Integral())
                        hist_atlas_scaleUp.Scale(1./hist_atlas_scaleUp.Integral())
                        hist_atlas_scaleDown.Scale(1./hist_atlas_scaleDown.Integral())

                    hist_vars.append(hist_atlas)
                    hist_vars.append(hist_atlas_scaleUp)
                    hist_vars.append(hist_atlas_scaleDown)
                    h_ratio_atlas = createRatio(hist_atlas,hist_nom,values["xlabel"])
                    h_ratio_atlas_scaleUp = createRatio(hist_atlas_scaleUp,hist_nom,values["xlabel"])
                    h_ratio_atlas_scaleDown = createRatio(hist_atlas_scaleDown,hist_nom,values["xlabel"])
                    hist_ratio_vars.append(h_ratio_atlas)
                    hist_ratio_vars.append(h_ratio_atlas_scaleUp)
                    hist_ratio_vars.append(h_ratio_atlas_scaleDown)

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
                    hist_atlas.SetMarkerStyle(20)
                    hist_atlas_scaleUp.SetMarkerStyle(20)
                    hist_atlas_scaleDown.SetMarkerStyle(20)
                    hist_nom.Draw("HIST")
                    hist_atlas.Draw("HIST SAME")
                    hist_atlas_scaleUp.Draw("HIST SAME")
                    hist_atlas_scaleDown.Draw("HIST SAME")

                    for hist in hist_vars:
                        print 'Drawing: ', hist.GetTitle()
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

                    for i in range(len(hist_ratio_vars)):
                        if i==0:
                            hist_ratio_vars[i].Draw("hist")
                            hist_ratio_vars[i].SetMinimum(0.4)
                            hist_ratio_vars[i].SetMaximum(1.6)
                        else:
                            hist_ratio_vars[i].Draw("histsame")
                    if 'genWeight_' not in feature:
                        line.Draw("same")
                    c.SaveAs("%s%s_%s_isNorm%s_wtStat%s_%s.png"%(outputdir,hist_nom_name,syst,normalization,showStats,region))

# Draw all canvases
if __name__ == "__main__":
    plotSysts()
