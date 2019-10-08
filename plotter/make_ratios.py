import sys, ROOT
import os
from ROOT import TCanvas, TColor, TGaxis, TH1F, TPad, TString, TFile, TH1, THStack, gROOT, TStyle, TAttFill, TLegend, TGraphAsymmErrors, TLine, TLatex
from ROOT import kBlack, kBlue, kRed, kCyan, kViolet, kGreen, kOrange, kGray, kPink, kTRUE

#### start  user defined variables

inputDirectories = ["/publicfs/cms/data/TopQuark/ttV-modelling/condor/ttH2016All2L/Legacy16V1_TTWJets/skims/"]

treename = "TNT/BOOM";

# Taus?

region_ = {
#"2lss_1bgeq4j":"(NJets>=4 && NBJets==1 && n_gen_tau==0)",
#"2lss_1beeq3j":"(NJets==3 && NBJets==1 && n_gen_tau==0)",
#"2lss_2bgeq4j":"(NJets>=4 && NBJets>=2 && n_gen_tau==0)",
#"2lss_2beeq3j":"(NJets==3 && NBJets>=2 && n_gen_tau==0)"
"2lss_0bgeq3j":"(NJets>=3 && n_gen_tau==0)",
"2lss_0beeq3j":"(NJets==3 && n_gen_tau==0)",
"2lss_0bgeq4j":"(NJets>=4 && n_gen_tau==0)"
}

region_title = {
"2lss_1bgeq4j":"2lss, >= 4 jets, ==1 b",
"2lss_1beeq3j":"2lss, == 3 jets, ==1 b",
"2lss_2bgeq4j":"2lss, >= 4 jets, >=2 b",
"2lss_2beeq3j":"2lss, == 3 jets, >=2 b",
"2lss_0bgeq3j":"2lss, >= 3 jets, >=0 b",
"2lss_0beeq3j":"2lss, == 3 jets, >=0 b",
"2lss_0bgeq4j":"2lss, >= 4 jets, >=0 b"
}

nominal_weights = {'genWeight':'EVENT_genWeight'}
systematics=["nominal","genWeight"]
variation_weight_index={"muR1muF1":0,"muR1muF2":1,"muR1muF0p5":2,"muR2muF1":3,"muR2muF2":4,"muR2muF0p5":5,"muR0p5muF1":6,"muR0p5muF2":7,"muR0p5muF0p5":8}
sixpoint_variations=["muR1muF2","muR1muF0p5","muR2muF1","muR2muF2","muR0p5muF1","muR0p5muF0p5"]
Color={"nominal":1,"muR1muF1":1,"muR1muF2":2,"muR1muF0p5":3,"muR2muF1":4,"muR2muF2":42,"muR2muF0p5":46,"muR0p5muF1":6,"muR0p5muF2":28,"muR0p5muF0p5":7}

# sample name is sampleName+postfix: ex, TTW_DiLepRegion.root
sampleName = ["mergedLegacy16V1_TTWJets"]

sampleTitle = {
"mergedLegacy16V1_TTWJets":"Madgraph"
}

postfix = ".root"

createROOTfile = True  # Set to Truth for the first time

# ATLAS ROOT file
ATLAS_filename = 'ATLAS_TTW_Sherpa_0710_2.root'
ATLAS_scaleUp_filename = 'ATLAS_TTW_SherpaScaleDown_0110.root'
ATLAS_scaleDown_filename = 'ATLAS_TTW_SherpaScaleUp_0110.root'

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
    y.SetTitle("ratio w. MG")
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
    pad1.SetLeftMargin(0.14)
    pad1.SetTicks(0,1)
    pad1.Draw()
    # Lower ratio plot is pad2
    c.cd()  # returns to main canvas before defining pad2
    pad2 = TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
    pad2.SetTopMargin(0)  # joins upper and lower plot
    pad2.SetBottomMargin(0.25)
    pad2.SetLeftMargin(0.14)
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
        filename = "myhist_%s.root" % region
        inputfile = TFile(filename,"read")
        if inputfile.IsZombie():
            print("inputfile is Zombie")
            sys.exit()
        cut_string = "EventWeight*"+cuts_values
        print 'region: %s, cuts_values: %s' % (region,cut_string)


        features={
        "NJets":{"nbin":8,"min":2.5,"max":10.5,"cut":cut_string,"xlabel":"NJets","xtitle":"# jets"},
        "NBJets":{"nbin":10,"min":0.5,"max":10.5,"cut":cut_string,"xlabel":"NBJets","xtitle":"# b-jets"},
        "MCGenHTall":{"nbin":10,"min":0.5,"max":1500.5,"cut":cut_string,"xlabel":"MCGenHTall","xtitle":"HT(all)"},
        "MCGenHThad":{"nbin":10,"min":0.5,"max":1500.5,"cut":cut_string,"xlabel":"MCGenHThad","xtitle":"HT(had)"},
        "MinDRMCGenLep1Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":cut_string,"xlabel":"MinDRMCGenLep1Jet","xtitle":"Min. dR(lep1,j)"},
        "MinDrMCGenLep2Jet":{"nbin":12,"min":0.0,"max":5.5,"cut":cut_string,"xlabel":"MinDrMCGenLep2Jet","xtitle":"Min. dR(lep2,j)"},
        "jet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"jet1_pt","xtitle":"1st jet pT"},
        "jet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"jet2_pt","xtitle":"2nd jet pT"},
        "jet3_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"jet3_pt","xtitle":"3rd jet pT"},
        "jet4_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"jet4_pt","xtitle":"4th jet pT"},
        "jet5_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"jet5_pt","xtitle":"5th jet pT"},
        "jet6_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"jet6_pt","xtitle":"6th jet pT"},
        "gen_lepton1_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":cut_string,"xlabel":"gen_lepton1_pt","xtitle":"leading lepton pT"},
        "gen_lepton2_pt":{"nbin":20,"min":0.5,"max":500.5,"cut":cut_string,"xlabel":"gen_lepton2_pt","xtitle":"subleading lepton pT"},
        "Bjet1_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"Bjet1_pt","xtitle":"leading b-jet pT"},
        "Bjet2_pt":{"nbin":10,"min":0.5,"max":200.5,"cut":cut_string,"xlabel":"Bjet2_pt","xtitle":"subleading b-jet pT"},
        "MinDRMCGenLeps":{"nbin":12,"min":0.0,"max":5.5,"cut":cut_string,"xlabel":"MinDRMCGenLeps","xtitle":"Min. dR(lep1,lep2)"},
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
        if "1tau1beeq3j" in region:
            ATLAS_region_index = '4'
        if "0beeq3j" in region:
            ATLAS_region_index = '5'
        if "0bgeq4j" in region:
            ATLAS_region_index = '6'
        if "0bgeq3j" in region:
            ATLAS_region_index = '7'


        ATLAS_feature_map={
        "NJets":"nJets_"+ATLAS_region_index,
        "NBJets":"nBtagJets_"+ATLAS_region_index,
        "n_gen_lepton":"",
        "MCGenHTall":"HT_"+ATLAS_region_index,
        "MCGenHThad":"HT_jets_"+ATLAS_region_index,
        "MCGenMET":"MET_"+ATLAS_region_index,
        "MinDRMCGenLep1Jet":"min_DRl0j_"+ATLAS_region_index,
        "MinDrMCGenLep2Jet":"min_DRl1j_"+ATLAS_region_index,
        "MinDRMCGenLeps":"DRll01_"+ATLAS_region_index,
        "Bjet1_pt":"Bjet_Pt_0_"+ATLAS_region_index,
        "Bjet2_pt":"Bjet_Pt_1_"+ATLAS_region_index,
        "jet1_pt":"jet_Pt_1_"+ATLAS_region_index,
        "jet2_pt":"jet_Pt_2_"+ATLAS_region_index,
        "jet3_pt":"jet_Pt_3_"+ATLAS_region_index,
        "jet4_pt":"jet_Pt_4_"+ATLAS_region_index,
        "jet5_pt":"jet_Pt_5_"+ATLAS_region_index,
        "jet6_pt":"jet_Pt_6_"+ATLAS_region_index,
        "gen_lepton1_pt":"lep_Pt_0_"+ATLAS_region_index,
        "gen_lepton2_pt":"lep_Pt_1_"+ATLAS_region_index,
        "Jet_hadronFlavour":"nBtagJets_"+ATLAS_region_index
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
                print "hist_nom_name: ", hist_nom_name
                hist_nom = inputfile.Get(hist_nom_name)
                hist_nom.SetFillColor(0)
                hist_nom.SetLineColor(Color["nominal"])
                hist_nom.SetLineWidth(3)
                hist_nom.SetMarkerColor(Color["nominal"])
                hist_title = region_title[region]
                hist_nom.SetTitle(hist_title)
                if hist_nom.Integral() == 0:
                    continue

                hist_eventweights = inputfile.Get("EventWeight")
                hist_nom.Scale(1./7040.32)
                if normalization:
                    hist_nom.Scale(1./hist_nom.Integral())
                #else:
                #    hist_nom.Scale(1./7040.32)

                # Need to scale down to 1/XS*BR*Lumi to match ATLAS fiducial normalisation
                # Scale up to correct ttW inclusive XS = 600.8
                h_ratio = createRatio(hist_nom, hist_nom, values["xtitle"])
                c, pad1, pad2 = createCanvasPads()
                hist_vars = []
                hist_ratio_vars = []
                # set up legend
                legend = TLegend(0.45,0.5,0.88,0.88)
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
                        hist_var.SetLineColor(Color[""])
                        hist_var.SetMarkerColor(1)
                        hist_var.SetLineWidth(3)
                        hist_var.Scale(1./7040.32)
                        if normalization:
                            hist_var.Scale(1./hist_var.Integral())
                        #else:
                            #hist_var.Scale(1./7040.32)

                        hist_vars.append(hist_var)
                        h_ratio_var = createRatio(hist_var, hist_nom ,values["xtitle"])
                        hist_ratio_vars.append(h_ratio_var)
                    else:
                        for sixpoint_index in sixpoint_variations:
                            hist_name = sample+"_"+feature+"_"+syst+"_"+sixpoint_index
                            print 'Getting sixpoint_index: ', sixpoint_index
                            if not inputfile.GetListOfKeys().Contains(hist_name):
                                print ( "make_ratios:: %s doesn't have histogram %s"%(filename, hist_name))
                                continue
                            else:
                                print 'hist_name: %s exists!' % (hist_name)
                            hist_nickname_plus_syst = ''
                            hist_nickname_plus_syst = hist_nickname + ' ' + sixpoint_index
                            hist_var = inputfile.Get(hist_name)
                            hist_var.SetFillColor(0)
                            hist_var.SetLineColor(Color[sixpoint_index])
                            hist_var.SetMarkerColor(Color[sixpoint_index])
                            hist_var.SetLineWidth(2)
                            hist_var.Scale(1./7040.32)
                            if normalization:
                                hist_var.Scale(1./hist_var.Integral())
                            #else:
                            #    hist_var.Scale(1./7040.32)
                            hist_vars.append(hist_var)
                            legend.AddEntry(hist_var,hist_nickname_plus_syst,"l")
                            h_ratio_var = createRatio(hist_var, hist_nom, values["xtitle"])
                            hist_ratio_vars.append(h_ratio_var)

                    print 'make_ratios:: %s: ATLAS feature equivalent = %s ' % (feature,ATLAS_feature_map.get(feature))
                    hist_atlas = ATLASfile.Get(ATLAS_feature_map.get(feature))
                    hist_atlas.SetName(feature+"_nominal")
                    '''hist_atlas_scaleUp = ATLASfile_scaleUp.Get(ATLAS_feature_map.get(feature))
                    hist_atlas_scaleUp.SetName(feature+"_scaleUp")
                    hist_atlas_scaleDown = ATLASfile_scaleDown.Get(ATLAS_feature_map.get(feature))
                    hist_atlas_scaleDown.SetName(feature+"_scaleDown")'''

                    if normalization:
                        hist_atlas.Scale(1./hist_atlas.Integral())
                        #hist_atlas_scaleUp.Scale(1./hist_atlas_scaleUp.Integral())
                        #hist_atlas_scaleDown.Scale(1./hist_atlas_scaleDown.Integral())

                    # Need to scale ATLAS plot by XS = 600.8 fb
                    hist_atlas.SetFillColor(0)
                    hist_atlas.SetLineColor(2)
                    hist_atlas.SetLineStyle(7)
                    hist_atlas.SetMarkerColor(2)
                    hist_atlas.SetLineWidth(3)
                    legend.AddEntry(hist_atlas,"ATLAS Sherpa","l")
                    hist_vars.append(hist_atlas)
                    h_ratio_atlas = createRatio(hist_atlas,hist_nom,values["xtitle"])
                    hist_ratio_vars.append(h_ratio_atlas)
                    '''
                    hist_atlas_scaleUp.SetFillColor(0)
                    hist_atlas_scaleDown.SetFillColor(0)
                    hist_atlas_scaleUp.SetLineColor(3)
                    hist_atlas_scaleDown.SetLineColor(4)
                    hist_atlas_scaleUp.SetLineStyle(7)
                    hist_atlas_scaleDown.SetLineStyle(7)
                    hist_atlas_scaleUp.SetMarkerColor(3)
                    hist_atlas_scaleDown.SetMarkerColor(4)
                    hist_atlas_scaleUp.SetLineWidth(3)
                    hist_atlas_scaleDown.SetLineWidth(3)
                    legend.AddEntry(hist_atlas_scaleUp,"ATLAS Sherpa Scale Up","l")
                    legend.AddEntry(hist_atlas_scaleDown,"ATLAS Sherpa Scale Down","l")
                    hist_vars.append(hist_atlas_scaleUp)
                    hist_vars.append(hist_atlas_scaleDown)
                    h_ratio_atlas_scaleUp = createRatio(hist_atlas_scaleUp,hist_nom,values["xtitle"])
                    h_ratio_atlas_scaleDown = createRatio(hist_atlas_scaleDown,hist_nom,values["xtitle"])
                    hist_ratio_vars.append(h_ratio_atlas_scaleUp)
                    hist_ratio_vars.append(h_ratio_atlas_scaleDown)'''

                    # draw everything
                    pad1.cd()
                    #pad1.SetGridx()
                    #pad1.SetGridy()
                    # set bounds
                    maximum=0
                    for hist in hist_vars:
                        if normalization:
                            hist.Scale(1./hist.Integral())
                        if hist.GetMaximum()>maximum:
                            maximum = hist.GetMaximum()

                    upperbound = 3.0*maximum
                    lowerbound = -maximum/40.

                    if showStats:
                        hist_nom.SetStats(1)

                    print 'upperbound: ', upperbound
                    hist_nom.SetMaximum(upperbound)
                    hist_nom.SetMinimum(lowerbound)
                    # Adjust y-axis settings
                    Y_name = "Arbitrary Units"
                    y = hist_nom.GetYaxis()
                    y.SetTitleSize(20)
                    y.SetTitleFont(43)
                    y.SetTitleOffset(2.3)
                    y.SetLabelFont(43)
                    y.SetLabelSize(17)
                    y.SetTitle(Y_name)
                    # Adjust x-axis settings
                    x = hist_nom.GetXaxis()
                    x.SetTitleSize(20)
                    x.SetTitleFont(43)
                    x.SetTitleOffset(1.57)
                    x.SetLabelFont(43)
                    x.SetLabelSize(17)
                    #x.SetTitle(values["xlabel"])
                    x.SetTitle(values["xtitle"])

                    hist_nom.SetMarkerStyle(20)
                    hist_nom.Draw("HIST")

                    print '# histograms to draw: ', len(hist_vars)
                    for hist in hist_vars:
                        print 'Hist Name: ', hist.GetName()
                        print 'Hist Title: ', hist.GetTitle()
                        hist.SetMarkerStyle(20)
                        hist.Draw("HISTSAME")

                    legend.Draw("same")
                    label = ROOT.TLatex()
                    label.SetTextSize(0.04)
                    label.SetTextAlign(13)
                    label.DrawLatexNDC(.19,.8,"CMS Simulation")
                    label.DrawLatexNDC(.19,.75,"(Work In Progress)")

                    pad2.cd()
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
