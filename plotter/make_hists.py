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

region_ = {
"2lss_1bgeq4j":"(n_gen_jets>=4 && n_gen_bjets==1)"
#"2lss_1beeq3j":"(n_gen_jets==3 && n_gen_bjets==1)",
#"2lss_2bgeq4j":"(n_gen_jets>=4 && n_gen_bjets>=2)",
#"2lss_2beeq3j":"(n_gen_jets==3 && n_gen_bjets>=2)"
}

# ATLAS ROOT file
ATLAS_filename = 'ATLAS_TTW_Sherpa_2609.root'

def draw_underflow_overflow(h1):
    h1.GetXaxis().SetRange(0, h1.GetNbinsX() + 1)
    h1.Draw()
    return h1

Canv = TCanvas("c1","c1",0,0,800,600)
#f_out = TFile(filename,"recreate")

ATLASfile = TFile(ATLAS_filename,"read")
if ATLASfile.IsZombie():
    print("ATLASfile is Zombie")
    sys.exit()

for sample in sampleName:
    for region, cuts_values in region_.items():
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

        filename = "myhist_%s.root" % region
        f_out = TFile(filename,"recreate")
        print 'make_hists:: Reading file: %s , tree: %s' % (inputDirectories[0]+sample+postfix,treename)
        file0 = TFile(inputDirectories[0]+sample+postfix,"read")
        tree0 = file0.Get(treename)
        f_out.cd()
        cut_string = "EventWeight*"+cuts_values
        print 'Region: %s , cut: %s' % (region,cut_string)
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

        for feature, values in features.items():
            hEventWeight = TH1F("EventWeight", "EventWeights", 10, -100,100)
            hEventWeight.Sumw2()
            inputEventWeight = "%s>>%s"%("EventWeight","EventWeight")
            CUT = "%s"%values["cut"]
            print 'CUT: ', CUT
            tree0.Draw(inputEventWeight,CUT)
            f_out.cd()
            hEventWeight.Write()

            print 'make_hists:: Feature = ', feature
            hist_atlas = ATLASfile.Get(ATLAS_feature_map.get(feature))
            atlas_binning = []
            for bin_index in xrange(1,hist_atlas.GetNbinsX()+1):
                atlas_binning.append(hist_atlas.GetBinLowEdge(bin_index))
                if bin_index == hist_atlas.GetNbinsX():
                    atlas_binning.append(hist_atlas.GetBinLowEdge(bin_index)+hist_atlas.GetBinWidth(bin_index))

            Nbins = 0
            Nbins = len(atlas_binning)
            bins_ = array('d',atlas_binning)

            f_out.cd()

            for syst in systematics:
                if syst == "nominal":
                    hist_name = sample+"_"+feature
                    h01 = TH1F(hist_name, feature, Nbins-1, bins_)
                    h01.Sumw2()
                    input01 = "%s>>%s"%(feature,hist_name)
                    CUT = "%s"%values["cut"]
                    print 'CUT: ', CUT
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
