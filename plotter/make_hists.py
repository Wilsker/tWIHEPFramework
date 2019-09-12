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
        print 'Feature: ', feature
        for syst in systematics:
            if syst == "nominal":
                print 'Nominal'
                hist_name = sample+"_"+feature
                print 'Histogram name: ', hist_name
                if 'MCGenHTall' in feature:
                    Nbins = len(binning['MCGenHTall'])+1
                    binning = array('f',binning['MCGenHTall'])
                    print 'Nbins: %s %s, binning: %s ' % (Nbins,type(Nbins),binning)
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                elif 'MCGenHThad' in feature:
                    Nbins = len(binning['MCGenHThad'])+1
                    binning = array('f',binning['MCGenHThad'])
                    print 'Nbins: %s %s, binning: %s ' % (Nbins,type(Nbins),binning)
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                elif 'MCGenHTlep' in feature:
                    Nbins = len(binning['MCGenHTlep'])+1
                    binning = array('f',binning['MCGenHTlep'])
                    print 'Nbins: %s %s, binning: %s ' % (Nbins,type(Nbins),binning)
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                elif 'MCGenMET' in feature:
                    Nbins = len(binning['MCGenMET'])+1
                    binning = array('f',binning['MCGenMET'])
                    print 'Nbins: %s %s, binning: %s ' % (Nbins,type(Nbins),binning)
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                elif '_lepton_' in feature:
                    Nbins = len(binning['_lepton_'])+1
                    binning = array('f',binning['_lepton_'])
                    print 'Nbins: %s %s, binning: %s ' % (Nbins,type(Nbins),binning)
                    h01 = TH1F(hist_name, feature, Nbins, binning)
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
                    print 'Systematic variation: ', var
                    hist_name = sample+"_"+feature+"_"+syst+var
                    print 'Histogram name: ', hist_name
                    #h01 = TH1F(hist_name, hist_name, values["nbin"], values["min"], values["max"])
                    if 'MCGenHTall' in feature:
                        Nbins = len(binning['MCGenHTall'])+1
                        binning = array('f',binning['MCGenHTall'])
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                    elif 'MCGenHThad' in feature:
                        Nbins = len(binning['MCGenHThad'])+1
                        binning = array('f',binning['MCGenHThad'])
                        print 'Nbins: %s %s, binning: %s ' % (Nbins,type(Nbins),binning)
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                    elif 'MCGenHTlep' in feature:
                        Nbins = len(binning['MCGenHTlep'])+1
                        binning = array('f',binning['MCGenHTlep'])
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                    elif 'MCGenMET' in feature:
                        Nbins = len(binning['MCGenMET'])+1
                        binning = array('f',binning['MCGenMET'])
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                    elif '_lepton_' in feature:
                        Nbins = len(binning['_lepton_'])+1
                        binning = array('f',binning['_lepton_'])
                        h01 = TH1F(hist_name, feature, Nbins, binning)
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
