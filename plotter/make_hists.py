from ROOT import TH1F, TH2F, TFile, TTree
from ROOT import gROOT, gStyle
from ROOT import TCanvas
from ROOT import *

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
        for syst in systematics:
            print 'syst: ', syst
            if syst == "nominal":
                hist_name = sample+"_"+feature
                if 'MCGenHTall' in feature:
                    Nbins = len(binning['MCGenHTall'])+1
                    binning = binning['MCGenHTall']
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                    print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                elif 'MCGenHThad' in feature:
                    Nbins = len(binning['MCGenHThad'])+1
                    binning = binning['MCGenHThad']
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                    print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                elif 'MCGenHTlep' in feature:
                    Nbins = len(binning['MCGenHTlep'])+1
                    binning = binning['MCGenHTlep']
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                    print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                elif 'MCGenMET' in feature:
                    Nbins = len(binning['MCGenMET'])+1
                    binning = binning['MCGenMET']
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                    print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                elif '_lepton_' in feature:
                    Nbins = len(binning['_lepton_'])+1
                    binning = binning['_lepton_']
                    h01 = TH1F(hist_name, feature, Nbins, binning)
                    print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                else:
                    h01 = TH1F(hist_name, feature, values["nbin"], values["min"], values["max"])
                h01.Sumw2()
                input01 = "%s>>%s"%(feature,hist_name)
                CUT = "%s"%values["cut"]
                print "Draw command: tree0.Draw(%s,%s)" % (input01,CUT)
                tree0.Draw(input01,CUT)
                #h_tmp = draw_underflow_overflow(h01)
                f_out.cd()
                #h_tmp.Write()
                h01.Write()
            else:
                for var in upDown:
                    hist_name = sample+"_"+feature+"_"+syst+var
                    #h01 = TH1F(hist_name, hist_name, values["nbin"], values["min"], values["max"])
                    if 'MCGenHTall' in feature:
                        print 'type binning[MCGenHThad]: ', type(binning['MCGenHThad'])
                        print 'type binning[MCGenHThad][0]: ', type(binning['MCGenHThad'][0])
                        Nbins = len(binning['MCGenHThad'])+1
                        binning = binning['MCGenHThad']
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                        print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                    elif 'MCGenHThad' in feature:
                        Nbins = len(binning['MCGenHThad'])+1
                        binning = binning['MCGenHThad']
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                        print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                    elif 'MCGenHTlep' in feature:
                        Nbins = len(binning['MCGenHTlep'])+1
                        binning = binning['MCGenHTlep']
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                        print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                    elif 'MCGenMET' in feature:
                        Nbins = len(binning['MCGenMET'])+1
                        binning = binning['MCGenMET']
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                        print 'Nbins: %s , binning: %s ' % (Nbins,binning)
                    elif '_lepton_' in feature:
                        Nbins = len(binning['_lepton_'])+1
                        binning = binning['_lepton_']
                        h01 = TH1F(hist_name, feature, Nbins, binning)
                        print 'Nbins: %s , binning: %s ' % (Nbins,binning)
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
