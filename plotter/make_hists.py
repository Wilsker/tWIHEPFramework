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
        Nbins = len(binning[feature])
        if 'MCGenHThad' in feature:
            #Nbins = len(binning[feature])
            binning = array('d',binning[feature])
        for syst in systematics:
            if syst == "nominal":
                hist_name = sample+"_"+feature
                #h01 = TH1F(hist_name, feature, Nbins-1, binning)
                if 'MCGenHThad' in feature:
                    h01 = TH1F(hist_name, feature, Nbins-1, binning)
                else:
                    h01 = TH1F(hist_name, feature, values["nbin"], values["min"], values["max"])
                h01.Sumw2()
                input01 = "%s>>%s"%(feature,hist_name)
                CUT = "%s"%values["cut"]
                #print "Draw command: tree0.Draw(%s,%s)" % (input01,CUT)
                tree0.Draw(input01,CUT)
                #h_tmp = draw_underflow_overflow(h01)
                f_out.cd()
                #h_tmp.Write()
                h01.Write()
            else:
                for var in upDown:
                    hist_name = sample+"_"+feature+"_"+syst+var
                    #h01 = TH1F(hist_name, feature, Nbins-1, binning)
                    if 'MCGenHThad' in feature:
                        h01 = TH1F(hist_name, feature, Nbins-1, binning)
                    else:
                        h01 = TH1F(hist_name, feature, values["nbin"], values["min"], values["max"])
                    h01.Sumw2()
                    input01 = "%s>>%s"%(feature,hist_name)
                    CUT = "%s*%s%s/%s"%(values["cut"],syst,var,nominal_weights[syst])
                    tree0.Draw(input01,CUT)
                    #h_tmp = draw_underflow_overflow(h01)
                    f_out.cd()
                    #h_tmp.Write()
                    h01.Write()

f_out.Close()
