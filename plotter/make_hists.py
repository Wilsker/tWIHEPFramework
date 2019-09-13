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
    print 'Reading file: %s , tree: %s' % (inputDirectories+sample+postfix,treename)
    file0 = TFile(inputDirectories+sample+postfix,"read")
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
                print 'Draw command: tree0.Draw(%s,%s)' % (input01,CUT)
                tree0.Draw(input01,CUT)
                f_out.cd()
                h01.Write()
            else:
                for sixpoint_index in sixpoint_variations:
                    hist_name = sample+"_"+feature+"_"+syst+sixpoint_index
                    if sixpoint_index == "muR2":
                        syst_weight = "%s%s/%s" % (syst,muR_vars[0],nominal_weights[syst])
                    elif sixpoint_index == "muR0p5":
                        syst_weight = "%s%s/%s" % (syst,muR_vars[1],nominal_weights[syst])
                    elif sixpoint_index == "muR2muF2":
                        syst_weight = "(%s%s/%s)*(%s%s/%s)" % (syst,muR_vars[0],nominal_weights[syst],syst,muF_vars[0],nominal_weights[syst])
                    elif sixpoint_index == "muF2":
                        syst_weight = "%s%s/%s" % (syst,muF_vars[0],nominal_weights[syst])
                    elif sixpoint_index == "muR0p5muF0p5":
                        syst_weight = "(%s%s/%s)*(%s%s/%s)" % (syst,muR_vars[1],nominal_weights[syst],syst,muF_vars[1],nominal_weights[syst])
                    elif sixpoint_index == "muF0p5":
                        syst_weight = "%s%s/%s" % (syst,muF_vars[1],nominal_weights[syst])

                    h01 = TH1F(hist_name, feature, Nbins-1, bins_)
                    h01.Sumw2()
                    input01 = "%s>>%s"%(feature,hist_name)
                    CUT = "%s*%s"%(values["cut"],syst_weight)
                    print 'Draw command: tree0.Draw(%s,%s)' % (input01,CUT)
                    tree0.Draw(input01,CUT)
                    f_out.cd()
                    h01.Write()

f_out.Close()
