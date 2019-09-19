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

def draw_underflow_overflow(h1):
    h1.GetXaxis().SetRange(0, h1.GetNbinsX() + 1)
    h1.Draw()
    return h1

Canv = TCanvas("c1","c1",0,0,800,600)
f_out = TFile(filename,"recreate")

for sample in sampleName:
    print 'Reading file: %s , tree: %s' % (inputDirectories[0]+region_+sample+postfix,treename)
    file0 = TFile(inputDirectories[0]+region_+sample+postfix,"read")
    tree0 = file0.Get(treename)
    for feature, values in features.items():
        print 'Feature = ', feature
        Nbins = 0
        Nbins = len(binning[feature])
        bins_ = array('d',binning[feature])
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
                systindex=0
                for sixpoint_index in sixpoint_variations:
                    hist_name = sample+"_"+feature+"_"+syst+"_"+sixpoint_index
                    #syst_weight = "%s_%s/%s" % (syst,sixpoint_index,nominal_weights[syst])
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
