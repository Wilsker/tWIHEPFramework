from ROOT import *

import sys,os,math,weightProcesses

histoGramPerSample = {"tW_top":"tW","tW_antitop":"tW","sChan":"singleTop","tChan":"singleTop","zz":"VV","zPlusJetsLowMass":"zPlusJets","zPlusJetsHighMass":"zPlusJets","wz":"VV","ww":"VV","wPlusJets":"wPlusJets","ttbar":"ttbar","qcd700_1000":"qcd","qcd500_700":"qcd","qcd300_500":"qcd","qcd200_300":"qcd","qcd2000_inf":"qcd","qcd1500_2000":"qcd","qcd100_200":"qcd","qcd1000_1500":"qcd","wPlusJetsMCatNLO":"wPlusJets","tChan_top":"singleTop","tChan_antitop":"singleTop","ttbarBU":"ttbar","tW_top_nfh":"tW","tW_antitop_nfh":"tW","wPlusJetsMadgraph":"wPlusJets","wPlus0Jets":"wPlusJets","wPlus1Jets":"wPlusJets","wPlus2Jets":"wPlusJets"}

samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMCatNLO","ttbar","ttbarBU"]
#samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","wPlusJetsMadgraph","ttbar"]
samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","ttbar","ttbarBU","wPlus0Jets","wPlus1Jets","wPlus2Jets"]
#samples = ["tW_top_nfh","tW_antitop_nfh","tChan_top","tChan_antitop","sChan","zz","zPlusJetsLowMass","zPlusJetsHighMass","wz","ww","ttbar","ttbarBU","wPlus2Jets"]

samplesDataMu = ["SingMuB","SingMuC","SingMuD","SingMuE","SingMuF","SingMuG","SingMuH"]
samplesDataEle = ["SingEleB","SingEleC","SingEleD","SingEleE","SingEleF","SingEleG","SingEleH"]
samplesData = samplesDataMu

colourPerSample = {"tW_top":kGreen+2,"tW_antitop":kGreen+2,"tW_top_nfh":kGreen+2,"tW_antitop_nfh":kGreen+2,"tChan":kYellow,"zPlusJetsLowMass":kBlue,"zPlusJetsHighMass":kBlue,"wz":kPink,"ww":kPink,"zz":kPink,"wPlusJets":kTeal,"ttbar":kRed,"qcd700_1000":kGray,"qcd500_700":kGray,"qcd300_500":kGray,"qcd200_300":kGray,"qcd2000_inf":kGray,"qcd1500_2000":kGray,"qcd100_200":kGray,"qcd1000_1500":kGray,"sChan":kOrange,"VV":kPink,"qcd":kGray,"tW":kGreen+2,"zPlusJets":kBlue,"singleTop":kYellow}

ignoreSystPlots = ["PS","herwig","amcatnlo"]

legendOrder = ["tW","wPlusJets","ttbar","qcd","VV","zPlusJets","singleTop"]

plotLeptonSampleName = "Mu"

includeDataInStack = False

makeStatBins = False

setNegToZero = False

gROOT.SetBatch()

from setTDRStyle import setTDRStyle

setTDRStyle()

latex = TLatex()
latex.SetNDC()
latex.SetTextAlign(31)

cmsTextFont = 61
extraTextFont = 52

latex2 = TLatex();
latex2.SetNDC();
latex2.SetTextSize(0.04);
latex2.SetTextAlign(31);

cmsText = "CMS"
extraText = "Preliminary"

makeSystComps = True #Make a whole bunch of comparison plots if true
makeStackPlots = True #Make some stack plots of the output
reduceBinsToFilled = True #Reduce the histograms to only their filled bins. This might possibly influence the fit, but my tests do not indicate that it does.

mvaNameDef = "MVA_ttbar_"
mvaPostfix = ""

inDir = sys.argv[1]
outDir = sys.argv[2]
doSystDir = True
systDir = inDir+"Systs/"
isEle = False
channeltr = "mu"
if "ele" in sys.argv:
    samplesData = samplesDataEle
    plotLeptonSampleName = "Ele"
    channeltr = "ele"
    isEle = True
#if len(sys.argv) > 3: systDir = sys.argv[3]

weights = weightProcesses.ReweightObject(False,isEle)

if (not os.path.isdir(outDir)):
    os.makedirs(outDir)
if makeSystComps and not os.path.isdir(outDir+"plots/"): os.makedirs(outDir+"plots/")

nominal = {}

systs = [
"LSF","PU","bTag","PDF","Trig","mistag"
]
nStatsBins = 0
systHists = {}

totalYieldsCount = {}

def findMaxAndMinBins(nominalHists,systHist):
    maxBin = 0
    minBin = 50
    returnNominals = {}
    returnSysts = {}
    for key in nominalHists.keys():
        if nominalHists[key].FindFirstBinAbove() < minBin: minBin = nominalHists[key].FindFirstBinAbove()
        if nominalHists[key].FindLastBinAbove() > maxBin: maxBin = nominalHists[key].FindLastBinAbove()
        if key == "data" or key == "qcd":continue
        for key2 in systHist[key].keys():
            if systHist[key][key2].FindFirstBinAbove() < minBin: minBin = systHist[key][key2].FindFirstBinAbove()
            if systHist[key][key2].FindLastBinAbove() > maxBin: maxBin = systHist[key][key2].FindLastBinAbove()
    xLow = nominalHists[key].GetXaxis().GetBinLowEdge(minBin)
    xHigh = nominalHists[key].GetXaxis().GetBinUpEdge(maxBin)
    for key in nominalHists.keys():
        returnNominals[key] = TH1F(nominalHists[key].GetName(),nominalHists[key].GetTitle(),maxBin-minBin+1,xLow,xHigh)
        i = 1
        for j in range(minBin,maxBin+1):
            returnNominals[key].SetBinContent(i,nominalHists[key].GetBinContent(j))
            returnNominals[key].SetBinError(i,nominalHists[key].GetBinError(j))
            i+=1
        if key == "data" or key == "qcd":continue
        returnSysts[key] = {}
        for key2 in systHist[key].keys():
            returnSysts[key][key2] = TH1F(systHist[key][key2].GetName(),systHist[key][key2].GetTitle(),maxBin-minBin+1,xLow,xHigh)
            i = 1
            for j in range(minBin,maxBin+1):
                returnSysts[key][key2].SetBinContent(i,systHist[key][key2].GetBinContent(j))
                returnSysts[key][key2].SetBinError(i,systHist[key][key2].GetBinError(j))
                i+=1
    print "Hists have been rescaled to fit range {0}-{1}".format(xLow,xHigh)
    return (returnNominals,returnSysts)

def setAllNegBinsToZero(hist):
    for i in range(1,hist.GetXaxis().GetNbins()+1):
        if hist.GetBinContent(i) < 0.: hist.SetBinContent(i,0.)

def makeAllSystHists(nominal,systHists,region,savePost=""):
    latexFile = open(outDir+"plots/{0}latexFile{1}.tex".format(region,savePost),"w")
    secondLatexFile = open(outDir+"plots/{0}latexFile{1}NotBeamer.tex".format(region,savePost),"w")
    latexFile.write("\\documentclass{beamer}\n\\usetheme{Warsaw}\n\n\\usepackage{graphicx}\n\\useoutertheme{infolines}\n\\setbeamertemplate{headline}{}\n\n\\begin{document}\n\n")
    for sample in nominal.keys():
        if sample == "data" or sample == "qcd": continue
        for syst in systHists[sample].keys():
            doPlot = True
            for ignore in ignoreSystPlots:
                if ignore in syst: doPlot = False
            if not doPlot: continue
            # To Be Reviewed
            if "Down" in syst or "stat" in syst or "down" in syst: continue
            downSystName = syst.split("Up")[0]+"Down"
            shortenedName = syst.split("Up")[0]
            if "up" in syst: downSystName = syst.split("up")[0]+"down"
            makeSystHist(nominal[sample],systHists[sample][syst],systHists[sample][downSystName],region+sample+shortenedName+savePost)
            latexFile.write("\\frame{{\n\\frametitle{{{0}-{1}-{2}}}\n".format(region,sample,shortenedName))
            latexFile.write("\\includegraphics[width=0.9\\textwidth]{"+region+sample+shortenedName+savePost+".png}")
            secondLatexFile.write("\\includegraphics[width=0.5\\textwidth]{"+region+sample+shortenedName+savePost+".png}\n")
            latexFile.write("\n}\n")
        #Now make one for the statistical uncertainty
        statHists = getStatUpDownHists(nominal[sample])
        makeSystHist(nominal[sample],statHists[0],statHists[1],region+sample+"stats"+savePost)
        latexFile.write("\\frame{{\n\\frametitle{{{0}-{1}-{2}}}\n".format(region,sample,"Stats"))
        latexFile.write("\\includegraphics[width=0.9\\textwidth]{"+region+sample+"stats"+savePost+".png}")
        secondLatexFile.write("\\includegraphics[width=0.5\\textwidth]{"+region+sample+"stats"+savePost+".png}\n")
        latexFile.write("\n}\n")

    latexFile.write("\\frame{{\n\\frametitle{{MVA {0}}}\n".format(region))
    latexFile.write("\\includegraphics[width=0.9\\textwidth]{{mva{0}{1}.png}}".format(region,savePost))
    latexFile.write("\n}\n")                                                                       

    latexFile.write("\\end{document}")
            

def getStatUpDownHists(nominal):
    #get histograms with the bins altered up and down by the bin error
     statsUp = nominal.Clone(nominal.GetName()+"StatsUp")
     statsDown = nominal.Clone(nominal.GetName()+"StatsDown")
     for i in range(1,nominal.GetXaxis().GetNbins()+1):
         statsUp.SetBinContent(i,nominal.GetBinContent(i)+nominal.GetBinError(i))
         statsDown.SetBinContent(i,nominal.GetBinContent(i)-nominal.GetBinError(i))
     return statsUp,statsDown

def makeSystHist(nominalHist,upHist,downHist,canvasName):
#    canvasName = upHist.GetName().split("Up")[0]
    canvy = TCanvas(canvasName,canvasName,1000,800)
    canvy.cd()
    canvy.SetBottomMargin(0.3)
    nominalHist.SetLineColor(kBlack)
    histMax = 0.
    if upHist.GetMaximum() > histMax: histMax = upHist.GetMaximum() 
    if downHist.GetMaximum() > histMax: histMax = downHist.GetMaximum()
    nominalHist.SetMaximum(histMax*1.2)
    nominalHist.Draw("hist")
    upHist.SetLineColor(kRed)
    upHist.Draw("hist same")
    downHist.SetLineColor(kBlue)
    downHist.Draw("hist same")

    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(0.23, 0.95, cmsText )
    
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04*0.76)
    latex.DrawLatex(0.35, 0.95 , extraText )
    
    latex2.DrawLatex(0.95, 0.95, canvasName);
    
    ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
    ratioCanvy.SetTopMargin(0.7)
    ratioCanvy.SetFillColor(0)
    ratioCanvy.SetFillStyle(0)
    ratioCanvy.SetGridy(1)
    ratioCanvy.Draw()
    ratioCanvy.cd(0)
    SetOwnership(ratioCanvy,False)
    

    
#    text2 = TLatex(0.45,0.98, "#mu channel " + canvasName)
#    text2.SetNDC()
#    text2.SetTextAlign(13)
#    text2.SetX(0.18)
#    text2.SetY(0.92)
#    text2.SetTextFont(42)
#    text2.SetTextSize(0.0610687)
#

    upHistRatio = upHist.Clone()
    upHistRatio.Divide(nominalHist)
    upHistRatio.SetMaximum(1.3)
    upHistRatio.SetMinimum(0.7)
    upHistRatio.Draw("hist same")
    downHistRatio = downHist.Clone()
    downHistRatio.Divide(nominalHist)
    downHistRatio.GetXaxis().SetTitle("BDT Discriminant")
    downHistRatio.Draw("hist same")

    canvy.SaveAs(outDir+"plots/"+canvasName+".png")

def makeStackPlot(nominal,systHists,region,savePost = ""):
    stack = THStack("mva_{0}".format(region),"mva_{0}".format(region))
    canvy = TCanvas("MVA_{0}".format(region),"MVA_{0}".format(region),1000,800)
    leggy = TLegend(0.8,0.6,0.95,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    
    canvy.cd()
    if includeDataInStack: canvy.SetBottomMargin(0.3)
    dataHist = 0
    sumHist = nominal[nominal.keys()[0]].Clone()
    sumHist.Reset()
    for i in nominal.keys():
        if i == "data":
            dataHist = nominal["data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
#        stack.Add(nominal[i])
        sumHist.Add(nominal[i])
        #Do systematic estimation here when I get aorund to it)

    if "data" in nominal.keys():
        leggy.AddEntry(nominal['data'],"Data","p")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")

    legendOrder.reverse()
    for entry in legendOrder:
        stack.Add(nominal[entry])

    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack.GetMaximum(): maxi = dataHist.GetMaximum()
    stack.SetMaximum(maxi)
    stack.Draw("hist")
    
    if includeDataInStack: dataHist.Draw("e1x0 same")
    leggy.Draw()

    if includeDataInStack:
        ratioCanvy = TPad("mva_ratio","mva_ratio",0.0,0.0,1.0,1.0)
        ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetFillColor(0)
        ratioCanvy.SetFillStyle(0)
        ratioCanvy.SetGridy(1)
        ratioCanvy.Draw()
        ratioCanvy.cd(0)
        SetOwnership(ratioCanvy,False)

        sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)

        sumHistoData.GetYaxis().SetTitle("Data/MC")
        sumHistoData.GetYaxis().SetTitleOffset(1.3)
        ratioCanvy.cd()
        SetOwnership(sumHistoData,False)
        sumHistoData.SetMinimum(0.8)
        sumHistoData.SetMaximum(1.2)
        sumHistoData.GetXaxis().SetTitleOffset(1.2)
        sumHistoData.GetXaxis().SetLabelSize(0.04)
        sumHistoData.GetYaxis().SetNdivisions(6)
        sumHistoData.GetYaxis().SetTitleSize(0.03)
        sumHistoData.Draw("E1X0")

    canvy.SaveAs(outDir+"plots/mva{0}{1}.png".format(region,savePost))
    canvy.SaveAs(outDir+"plots/mva{0}{1}.root".format(region,savePost))


def getDownHist(upHist,nominalHist):
    downHist = nominalHist.Clone(upHist.GetName().split("Up")[0]+"Down")
    downHist.SetDirectory(0)
    for i in range(1,nominalHist.GetXaxis().GetNbins()+1):
        diffBin = nominalHist.GetBinContent(i) - upHist.GetBinContent(i)
        downHist.SetBinContent(i,nominalHist.GetBinContent(i) + diffBin)
        if downHist.GetBinContent(i) < 0.: downHist.SetBinContent(i,0.)
    return downHist

def makeStatBinVariations(hist, binNumber, region):

    variationHistUp = hist.Clone("{2}_{2}_Mu{1}_statbin{0}Up".format(binNumber,region,hist.GetName()))
    variationHistDown = hist.Clone("{2}_{2}_Mu{1}_statbin{0}Down".format(binNumber,region,hist.GetName()))
    binWeight = hist.GetBinContent(binNumber)
    shift = 0

    shift = hist.GetBinError(binNumber)
    variationHistUp.SetBinContent(binNumber,binWeight+shift)
    variationHistDown.SetBinContent(binNumber,binWeight-shift)
    return (variationHistUp,variationHistDown)


def makeDatacard(mvaName,regions,savePostfix=""):
    for region in regions:
        saveName = "3j1t"
        if not region == "": saveName = region
        outFile = TFile(outDir+"mvaDists_{0}_{1}{2}.root".format(saveName,channeltr,savePostfix),"RECREATE")

        totalYieldsCount[region] = {}
        nominal = {}
        systHists = {}
        if doSystDir: systDir = inDir + "Systs" + region + "/"
        for sample in samples:
            #get input file
            inFile = TFile(inDir+region+"/output_"+sample+".root","READ")
            print sample
            #get nominal plot"
            if histoGramPerSample[sample] in nominal.keys():
                
                nominal[histoGramPerSample[sample]].Add(inFile.Get(mvaName+sample))
                for sys in systs:
                    #print mvaName+sample+"_"+sys+"_up"
                    systHists[histoGramPerSample[sample]][sys+"Up"].Add(inFile.Get(mvaName+sample+"_"+sys+"_up"))
                    systHists[histoGramPerSample[sample]][sys+"Down"].Add(inFile.Get(mvaName+sample+"_"+sys+"_down"))
            else:
                nominal[histoGramPerSample[sample]] = inFile.Get(mvaName+sample).Clone(histoGramPerSample[sample])
                nominal[histoGramPerSample[sample]].Sumw2()
                nominal[histoGramPerSample[sample]].SetDirectory(0)
    #            if nStatsBins == 0:
    #                nStatsBins = nominal[histoGramPerSample[sample]].GetXaxis().GetNbins()
    #                print "nStatsBins: ",nStatsBins
    #                for i in range(1,nStatsBins+1):
    #                    systs.append("statbin"+str(i))
                systHists[histoGramPerSample[sample]] = {}
                for sys in systs:
                    #print sys, mvaName+sample+"_"+sys+"_up"
                    systNameForClone = histoGramPerSample[sample]+"_"+sys
                    if "statbin" in sys: systNameForClone = histoGramPerSample[sample]+"_"+histoGramPerSample[sample]+"_"+plotLeptonSampleName+"_"+sys
                    systHists[histoGramPerSample[sample]][sys+"Up"] = inFile.Get(mvaName+sample+"_"+sys+"_up").Clone(systNameForClone+"Up")
                    systHists[histoGramPerSample[sample]][sys+"Up"].SetDirectory(0)
                    systHists[histoGramPerSample[sample]][sys+"Down"] = inFile.Get(mvaName+sample+"_"+sys+"_down").Clone(systNameForClone+"Down")
                    systHists[histoGramPerSample[sample]][sys+"Down"].SetDirectory(0)
                    systHists[histoGramPerSample[sample]][sys+"Up"].Sumw2()
                    systHists[histoGramPerSample[sample]][sys+"Down"].Sumw2()

        dirSysts = ["JES","JER"]
        upDown = ["Up","Down"]
        if doSystDir:
            for ud in upDown:
                for syst in dirSysts:
                    dirName = syst+ud
                    print "Processing systematic in {0}".format(dirName)
                    for sample in samples:
                        inFile = TFile(inDir+dirName+region+"/output_"+sample+".root","READ")
                        print "Processing sample {0}".format(sample)
                        if dirName not in systHists[histoGramPerSample[sample]]:
                            systHists[histoGramPerSample[sample]][dirName] = inFile.Get(mvaName+sample).Clone(histoGramPerSample[sample]+"_"+syst+ud)
                            systHists[histoGramPerSample[sample]][dirName].SetDirectory(0)
                        else:
                            systHists[histoGramPerSample[sample]][dirName].Add(inFile.Get(mvaName+sample).Clone(histoGramPerSample[sample]+"_"+syst+ud))

        for sample in samplesData:
            print "Dataset: {0}".format(sample)
            inFile = TFile(inDir+region+"/output_"+sample+".root","READ")
            inFileQCD = TFile(inDir+"QCD{0}/output_".format(region)+sample+".root","READ")
            if "data" not in nominal.keys():
                nominal["data"] = inFile.Get(mvaName+sample).Clone("data_obs")
                nominal["data"].SetDirectory(0)
                nominal["qcd"] = inFileQCD.Get(mvaName+sample).Clone("qcd")
                nominal["qcd"].SetDirectory(0)
                print "QCD template has {0}".format(nominal["qcd"].Integral())
            else:
                nominal["data"].Add(inFile.Get(mvaName+sample))
                nominal["qcd"].Add(inFileQCD.Get(mvaName+sample))
                print "QCD template has {0}".format(nominal["qcd"].Integral())

        #Here we should grab the systematic samples if we're doing that.        
        sysDirNamesList = []
        sysNamesToGetDownHist = []
        if doSystDir:
            for fileName in os.listdir(systDir):
                sample = fileName.split("_")[1]
                sample2 = fileName.split("output_")[1].split(".root")[0]
                syst = fileName.split("_")[-1].split(".")[0]
                inFile = TFile(systDir+fileName,"READ")
                if syst in systHists[sample].keys():
                    print "Adding 1 {0},{1},{2}".format( sample, syst, sample2), systHists[sample][syst].Integral(),
                    systHists[sample][syst].Add(inFile.Get(mvaName+sample2))
                    print systHists[sample][syst].Integral()
                elif syst+"Up" in systHists[sample].keys():
                    print "Adding 2 {0},{1},{2}".format( sample, syst, sample2),
                    print systHists[sample][syst+"Up"].Integral(),
                    systHists[sample][syst+"Up"].Add(inFile.Get(mvaName+sample2))
                    print sample2,systHists[sample][syst+"Up"].Integral()
        #            systHists[sample][syst+"Down"].Add(getDownHist(inFile.Get(mvaName+sample2),nominal[sample]))
                else:
                    print "Making new {0},{1},{2}".format( sample, syst, sample2)
                    cloneName = syst
                    sysDirNamesList.append(syst)
                    if "up" in syst:
                        cloneName = syst.split("up")[0]+"Up"
                    elif "down" in syst:
                        cloneName = syst.split("down")[0]+"Down"
                    else:
                        systHists[sample][syst+"Up"] = inFile.Get(mvaName+sample2).Clone(sample+"_"+syst+"Up")
                        systHists[sample][syst+"Up"].SetDirectory(0)
                        sysNamesToGetDownHist.append((sample,syst))
        #                systHists[sample][syst+"Down"] = getDownHist(systHists[sample][syst+"Up"],nominal[sample])
                        continue
                    systHists[sample][syst] = inFile.Get(mvaName+sample2).Clone(sample+"_"+cloneName)
                    systHists[sample][syst].SetDirectory(0)

        for pair in sysNamesToGetDownHist:

            print "Entry: ",pair[0],pair[1]
            #A hack to normalise herwig sample correctly
            if pair[0] == "ttbar" and pair[1] == "herwig":
                systHists[pair[0]][pair[1]+"Up"].Scale(0.5)
            systHists[pair[0]][pair[1]+"Down"] = getDownHist(systHists[pair[0]][pair[1]+"Up"],nominal[pair[0]])

#        halveSize = ["isr","fsr","tune","hdamp"]
        halveSize = []

        for key in nominal.keys():
            if setNegToZero: setAllNegBinsToZero(nominal[key])
            totalYieldsCount[region][key] = nominal[key].Integral()

            nominal[key].Sumw2()
            
            #Make the stat variation histograms
            if "data" in key or "qcd" in key: continue
            if makeStatBins:
                for i in range(1,nominal[key].GetXaxis().GetNbins()+1):
                    systHists[key]["statbin"+str(i)+"up"],systHists[key]["statbin"+str(i)+"down"] = makeStatBinVariations(nominal[key],i,region)

        #Here make a loop to find out the highest and lowest filled bins so get rid of zero occupancy bins?
    #    for key in nominal.keys():

        (nominal,systHists) = findMaxAndMinBins(nominal,systHists)
        outFile.cd()
        print sysDirNamesList
        for key in nominal.keys():
            scaleFactor = weights.getDatasetWeight(key,region)
            nominal[key].Scale(scaleFactor)
            totalYieldsCount[region][key] *= scaleFactor
#            if key in perMCSFs.keys():
#                nominal[key].Scale(perMCSFs[key])
#                totalYieldsCount[region][key] *= perMCSFs[key]
            nominal[key].Write()
            print key, nominal[key].Integral()
            if key == "data" or key == "qcd": continue
            for key2 in systHists[key].keys():
                systHists[key][key2].Scale(scaleFactor)
#                if key in perMCSFs.keys():
#                    for systName in halveSize:
#                        if key == "ttbar" and systName in key2: 
    #                        print "rescaling: ",key,key2
#                            systHists[key][key2].Scale(0.5)
#                    systHists[key][key2].Scale(perMCSFs[key])
                if setNegToZero: setAllNegBinsToZero(systHists[key][key2])
                systHists[key][key2].Write()

        if makeSystComps: 
            makeAllSystHists(nominal,systHists,region,savePostfix)
        if makeStackPlots:
            makeStackPlot(nominal,systHists,region,savePostfix)


    for region in regions:
        print region
        for key in totalYieldsCount[region].keys():
            print key, totalYieldsCount[region][key]

    for j in regions:
        for i in ["VV", "wPlusJets", "zPlusJets", "ttbar", "singleTop", "qcd", "tW"]:
            print totalYieldsCount[j][i],

    print ""

    for j in regions:
        for i in ["VV", "wPlusJets", "zPlusJets", "ttbar", "singleTop", "qcd", "tW"]:
            print "{0} {1}".format(j,i),

    print

    for j in regions:
        print totalYieldsCount[j]["data"],

if __name__ == "__main__":

    regions = ["3j1t","2j1t","3j2t","4j1t","4j2t"]
#    regions = ["3j1t"]
#    for postName in ["bin10_","bin20_","bin30_","bin40_","bin50_","bin80_","bin100_","bin1000_"]:
#    for postName in ["bin10_","bin20_","bin30_","bin40_","bin50_","bin80_"]:
#    for postName in ["bin80_","bin100_"]:
#    for postName in ["bin1000_"]:
    for postName in ["bin30_"]:
        print mvaNameDef+postName, "_"+postName[:-1]
        makeDatacard(mvaNameDef+postName,regions,"_"+postName[:-1])
