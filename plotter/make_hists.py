from ROOT import TH1F, TH2F, TFile, TTree
from ROOT import gROOT, gStyle
from ROOT import TCanvas
from array import array

gROOT.SetBatch(1)
gROOT.Reset()
gStyle.SetCanvasColor(0)
gStyle.SetFrameBorderMode(0)
gStyle.SetOptStat(0)
gStyle.SetTitleX(0.5) # title X location
gStyle.SetTitleY(0.96) # title Y location
gStyle.SetPaintTextFormat(".2f")

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
"gen_jet4_pt":"jet_Pt_4_0",
"gen_jet5_pt":"jet_Pt_5_0",
"gen_jet6_pt":"jet_Pt_6_0",
"gen_lepton1_pt":"lep_Pt_0_0",
"gen_lepton2_pt":"lep_Pt_1_0"
}

# ATLAS ROOT file
ATLAS_filename = 'ATLAS_TTW_Sherpa_2609.root'

def draw_underflow_overflow(h1):
    h1.GetXaxis().SetRange(0, h1.GetNbinsX() + 1)
    h1.Draw()
    return h1

Canv = TCanvas("c1","c1",0,0,800,600)
f_out = TFile(filename,"recreate")

for sample in sampleName:
    print 'make_hists:: Reading file: %s , tree: %s' % (inputDirectories[0]+region_+sample+postfix,treename)
    file0 = TFile(inputDirectories[0]+region_+sample+postfix,"read")
    tree0 = file0.Get(treename)
    hist_eventWeights_name = "hist_eventWeights"
    hist_eventWeights = TH1F(hist_eventWeights_name, "EventNBeforePresel", 1,0,1)
    input00 = "%s>>%s"%("EventNBeforePresel",hist_eventWeights_name)
    tree0.Draw(input00,"EventWeight")
    f_out.cd()
    hist_eventWeights.Write()
    ATLASfile = TFile(ATLAS_filename,"read")
    if ATLASfile.IsZombie():
        print("ATLASfile is Zombie")
        sys.exit()
    for feature, values in features.items():
        print 'make_hists:: Feature = ', feature
        hist_atlas = ATLASfile.Get(ATLAS_feature_map.get(feature))
        atlas_binning = []
        for bin_index in xrange(1,hist_atlas.GetNbinsX()+1):
            atlas_binning.append(hist_atlas.GetBinLowEdge(bin_index))
            if bin_index == hist_atlas.GetNbinsX():
                atlas_binning.append(hist_atlas.GetBinLowEdge(bin_index)+hist_atlas.GetBinWidth(bin_index))
        print 'atlas_binning: ', atlas_binning

        Nbins = 0
        #Nbins = len(binning[feature])
        #bins_ = array('d',binning[feature])
        Nbins = len(atlas_binning)
        bins_ = array('d',atlas_binning)

        for syst in systematics:
            if syst == "nominal":
                hist_name = sample+"_"+feature
                h01 = TH1F(hist_name, feature, Nbins-1, bins_)
                h01.Sumw2()
                input01 = "%s>>%s"%(feature,hist_name)
                CUT = "%s"%values["cut"]
                tree0.Draw(input01,CUT)
                f_out.cd()
                h01.Write()
            else:
                systindex=1
                for sixpoint_index in sixpoint_variations:
                    hist_name = sample+"_"+feature+"_"+syst+"_"+sixpoint_index
                    syst_weight = "EVENT_genWeights[%i]/%s" % (systindex,nominal_weights[syst])
                    h01 = TH1F(hist_name, feature, Nbins-1, bins_)
                    h01.Sumw2()
                    input01 = "%s>>%s"%(feature,hist_name)
                    CUT = "%s*%s"%(values["cut"],syst_weight)
                    tree0.Draw(input01,CUT)
                    f_out.cd()
                    h01.Write()
                    systindex = systindex+1

f_out.Close()
