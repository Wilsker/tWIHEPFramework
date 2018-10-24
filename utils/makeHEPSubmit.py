import sys
import os
import glob
import string
import subprocess
#####
##   Parameters to be specified by the user
#####
#analysis and task
analysis = "ttH"
taskname = "EvtSel"
frameworkDir = "/publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/"
executable = "bin/ttH/ttH_generic.x"
#executable = "Wt_nVertOnly.x"
configFile = "config/overall/ttH.MultiLeptons.DiLepton.SR.config"
#invPostfix = " -MCatNLO -mc -lepSFs -bTagReshape -PileUpWgt -ReCalPU -TriggerSFs"
invPostfix = " -MCatNLO -mc -bTagReshape -PileUpWgt -ReCalPU -TriggerSFs -lepSFs"
#mcPostfix = " -mcPromptFS -mcPromptGamma -FakeRate -mcPromptFS -chargeMis" 
mcPostfix = " "
triggerName = "TTHLep_2L "
nJets = 3
nbJets = 1
fileListDirectory = "config/files/ttH_2018/SmallJobs/mc/"
makeSkims = True
samplesMC76=[
"qcd1000_1500",
"qcd100_200",
"qcd1500_2000",
"qcd2000_inf",
"qcd200_300",
"qcd300_500",
"qcd500_700",
"qcd700_1000",
"sChan",
"tChan",
"ttbar",
"tW_top",
"tW_antitop",
"wPlusJets",
"ww",
"wz",
"zz",
"zPlusJetsLowMass",
"zPlusJetsHighMass",
"wPlusJetsMCatNLO"
]
samples94XData = [
"SEleBlockB", "SEleBlockC", "SEleBlockD", "SEleBlockE", "SEleBlockF", "SMuBlockB", "SMuBlockC", "SMuBlockD", "SMuBlockE", "SMuBlockF", "DblEGBlockB", "DblEGBlockC", "DblEGBlockD", "DblEGBlockE", "DblEGBlockF", "DblMuBlockB", "DblMuBlockC", "DblMuBlockD", "DblMuBlockE", "DblMuBlockF", "MuEGBlockB", "MuEGBlockC", "MuEGBlockD", "MuEGBlockE", "MuEGBlockF",
]
#samples94XData = [
#"SEleBlockF", "SMuBlockF", "DblEGBlockF", "DblMuBlockF", "MuEGBlockF",
#]
#samples94MC=[
#"TTHnobb", "ttH_powheg_ToNonbb", "TTWToLNu", "TTW_PSwgt_ToLNu", "TTZToLLNuNu_M10", "TTZToLL_M1to10", "TTWW", "DY_M10to50", "DY_M50", "DY_ext_M50", "WJets", "WWTo2L2Nu", "WZTo3LNu", "ZZTo4L", "ZZ_ext_To4L", "TT_PSwgt_To2L2Nu", "TTTo2L2Nu", "TT_PSwgt_ToSemiLep", "TTToSemiLep", "TT_PSwgt_ToHadron", "TTToHadron", "ST_tW_top", "ST_tW_antitop", "STt_top", "STt_antitop", "STs", "TTGJets", "tZq", "WW_DoubleScatter", "WW_DS_To2L2Nu", "WWW", "WWZ", "WZZ", "ZZZ", "TTTT_Tune"
#]
samplesMC=[
"TTHnobb", "TTWToLNu", "TTZToLLNuNu_M10", "TTZToLL_M1to10", "TTWW", "DY_M10to50", "DY_ext_M50", "WJets", "WZTo3LNu", "ZZ_ext_To4L", "TT_PSwgt_To2L2Nu", "TT_PSwgt_ToSemiLep", "TT_PSwgt_ToHadron", "TTGJets", "tZq", "WW_DoubleScatter","WWW", "WWZ", "WZZ", "ZZZ", "TTTT_Tune",
"THQ","THW","VHToNobb","tWll","WpWpJJ",
"GGH_ext_ToZZ4L", "TTWH", "WZG", "TTTW", "TGJets_Lep", "W1JetsToLNu", "W2JetsToLNu", "W3JetsToLNu", "W4JetsToLNu", "DY1JetsToLL_M50","DY2JetsToLL_M50", "DY3JetsToLL_M50", "DY4JetsToLL_M50", "DYJetsToLL_M4to50_HT70to100","DYJetsToLL_M4to50_HT100to200", "DYJetsToLL_M4to50_HT200to400", "DYJetsToLL_M4to50_HT400to600", "DYJetsToLL_M4to50_HT600toInf"
]
samplesMVA = [
"TTHnobb","ttH_powheg_ToNonbb","TTW_PSwgt_ToLNu","TTWToLNu","TTZToLLNuNu_M10","TTZToLL_M1to10","TT_PSwgt_To2L2Nu", "TTTo2L2Nu", "TT_PSwgt_ToSemiLep", "TTToSemiLep", "TT_PSwgt_ToHadron", "TTToHadron"
]
samplesClos = [
"TT_PSwgt_To2L2Nu", "TTTo2L2Nu", "TT_PSwgt_ToSemiLep", "TTToSemiLep", "TT_PSwgt_ToHadron", "TTToHadron"
]
samplesConv = [
"TTGToJets_ext1","WGToLNuG_ext2","TGJets_v1","WGToLNuG_ext1","ZGTo2LG","TGJets_ext1"
]

samplesDataMuEle=[
"SEleBlockB", "SEleBlockC", "SEleBlockD", "SEleBlockE", "SEleBlockF", "SMuBlockB", "SMuBlockC", "SMuBlockD", "SMuBlockE", "SMuBlockF", "DblEGBlockB", "DblEGBlockC", "DblEGBlockD", "DblEGBlockE", "DblEGBlockF", "DblMuBlockB", "DblMuBlockC", "DblMuBlockD", "DblMuBlockE", "DblMuBlockF", "MuEGBlockB", "MuEGBlockC", "MuEGBlockD", "MuEGBlockE", "MuEGBlockF",
]

samplesDataDiMu=[
 "SMuBlockB", "SMuBlockC", "SMuBlockD", "SMuBlockE", "SMuBlockF", "DblMuBlockB", "DblMuBlockC", "DblMuBlockD", "DblMuBlockE", "DblMuBlockF", "MuEGBlockB", "MuEGBlockC", "MuEGBlockD", "MuEGBlockE", "MuEGBlockF",
]

samplesDataDiEle=[
"SEleBlockB", "SEleBlockC", "SEleBlockD", "SEleBlockE", "SEleBlockF", "DblEGBlockB", "DblEGBlockC", "DblEGBlockD", "DblEGBlockE", "DblEGBlockF", "MuEGBlockB", "MuEGBlockC", "MuEGBlockD", "MuEGBlockE", "MuEGBlockF",
]

samplesSyst = [
"tW_antitop_DS",
"tW_antitop_isrup",
"tW_antitop_isrdown",
"tW_antitop_fsrup",
"tW_antitop_fsrdown",
"tW_antitop_herwig",
"tW_antitop_MEup",
"tW_antitop_MEdown",
"tW_antitop_PSup",
"tW_antitop_PSdown",
"tW_top_DS",
"tW_top_isrup",
"tW_top_isrdown",
"tW_top_fsrup",
"tW_top_fsrdown",
"tW_top_herwig",
"tW_top_MEup",
"tW_top_MEdown",
"tW_top_PSup",
"tW_top_PSdown",
"ttbar_isrup",
"ttbar_isrdown",
"ttbar_fsrup",
"ttbar_fsrdown",
"ttbar_tuneup",
"ttbar_tunedown",
"ttbar_herwig",
"ttbar_amcatnlo",
"ttbar_hdampup",
"ttbar_hdampdown"
]
jesTestSamples = ["JESTest"]
#systSamples = ["ttbar_hdampdown"]
#mcSamples = []
#samplesData = []
sample = samplesMC
if "inv" in sys.argv:
    invPostfix = " -InvertIsolation"
    analysis += "Inv"
if "wJetsReg" in sys.argv:
    nJets = 3
    nbJets = 0
    analysis += "3j0t"
if "ttbarReg" in sys.argv:
    nJets = 3
    nbJets = 2
    analysis += "3j2t"
if "wJets2" in sys.argv:
    nJets = 2
    nbJets = 1
    analysis += "2j1t"
if "ttbar2" in sys.argv:
    nJets = 4
    nbJets = 2
    analysis += "4j2t"
if "sig2" in sys.argv:
    nJets = 4
    nbJets = 1
    analysis += "4j1t"
if triggerName == "TTHLep_MuEle ":
    analysis += "MuEle"
if triggerName == "TTHLep_2Ele ":
    analysis += "2Ele"
if triggerName == "TTHLep_2Mu ":
    analysis += "2Mu"
if "jesUp" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.DiLepJESup.config"
    analysis += "JESUp"
if "jesDown" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.DiLepJESdown.config"
    analysis += "JESDown"
if "jerUp" in sys.argv:
    if triggerName == "TTHLep_MuEle ":
        configFile = "config/overall/ttH.MultiLeptons.EleMuJERup.config"
    if triggerName == "TTHLep_2Mu ":
        configFile = "config/overall/ttH.MultiLeptons.DiMuJERup.config"
    if triggerName == "TTHLep_2Ele ":
        configFile = "config/overall/ttH.MultiLeptons.DiEleJERup.config"
    analysis += "JERUp"
if "jerDown" in sys.argv:
    if triggerName == "TTHLep_MuEle ":
        configFile = "config/overall/ttH.MultiLeptons.EleMuJERdown.config"
    if triggerName == "TTHLep_2Mu ":
        configFile = "config/overall/ttH.MultiLeptons.DiMuJERdown.config"
    if triggerName == "TTHLep_2Ele ":
        configFile = "config/overall/ttH.MultiLeptons.DiEleJERdown.config"
    analysis += "JERDown"
if "wJetsReg" in sys.argv and "ttbarReg" in sys.argv:
    print "Please only use one of ttbar and wJets -Reg! Exiting..."
    sys.exit()
if "mva" in sys.argv:
    mcPostfix = " -isTrainMVA"
    configFile = "config/overall/ttH.MultiLeptons.DiLepTrainMVA.config"
    analysis += "TrainMVA"
    sample = samplesMVA
elif "ttZctrl" in sys.argv:
    triggerName = "TTHLep_3L "
    configFile = "config/overall/ttH.MultiLeptons.ttZControl.config"
    analysis += "ttZctrl"
elif "ttWctrl" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.ttWControl.config"
    analysis += "ttWctrl"
elif "lepSB" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.LeptonSideband.config"
    analysis += "lepSB"
elif "convs" in sys.argv:
    mcPostfix = " -mcPromptGamma"
    analysis += "Conv"
    sample = samplesConv
elif "clos" in sys.argv:
    sample = samplesClos
    configFile = "config/overall/ttH.MultiLeptons.DiLepFakes.GT3J.config"
    mcPostfix = "  -FakeRate"
else :
    mcPostfix = " -mcPromptFS"
if "data" in sys.argv:
    mcPostfix = "  -FakeRate -chargeMis"
    invPostfix = " "
    analysis = "ttHData"
    sample = samples94XData
    fileListDirectory = "config/files/ttH_2018/SmallJobs/data/"
    if "ttZctrl" in sys.argv:
        analysis += "ttZctrl"
        triggerName = "TTHLep_3L "
        configFile = "config/overall/ttH.MultiLeptons.ttZControl.config"
    elif "ttWctrl" in sys.argv:
        analysis += "ttWctrl"
        configFile = "config/overall/ttH.MultiLeptons.ttWControl.config"
    elif "lepSB" in sys.argv:
        analysis += "lepSB"
        configFile = "config/overall/ttH.MultiLeptons.LeptonSideband.config"
    elif triggerName == "TTHLep_2L ":
        configFile = "config/overall/ttH.MultiLeptons.DiLepton.SR.config"
    elif triggerName == "TTHLep_MuEle ":
        sample = samplesDataMuEle
        configFile = "config/overall/ttH.MultiLeptons.EleMuSR.config"
    elif triggerName == "TTHLep_2Mu ":
        sample = samplesDataDiMu
        configFile = "config/overall/ttH.MultiLeptons.DiMuSR.config"
    elif triggerName == "TTHLep_2Ele ":
        sample = samplesDataDiEle
        configFile = "config/overall/ttH.MultiLeptons.DiEleSR.config"
    elif "electron" in sys.argv:
        sample = samplesDataElectron
if "fakes" in sys.argv:
    mcPostfix = " -FakeRate"
    invPostfix = " "
    analysis = "ttHfakes"
    sample = samples94XData
    fileListDirectory = "config/files/ttH_2018/SmallJobs/data/"
    if "ttZctrl" in sys.argv:
        analysis += "ttZctrl"
        triggerName = "TTHLep_3L "
        configFile = "config/overall/ttH.MultiLeptons.ttZControlFakes.config"
    elif "ttWctrl" in sys.argv:
        analysis += "ttWctrl"
        configFile = "config/overall/ttH.MultiLeptons.ttWControlFakes.config"
    elif triggerName == "TTHLep_2L ":
        configFile = "config/overall/ttH.MultiLeptons.DiLepFakes.config"
    elif triggerName == "TTHLep_MuEle ":
        sample = samplesDataMuEle
        configFile = "config/overall/ttH.MultiLeptons.EleMuFakes.config"
    if triggerName == "TTHLep_2Mu ":
        sample = samplesDataDiMu
        configFile = "config/overall/ttH.MultiLeptons.DiMuFakes.config"
    if triggerName == "TTHLep_2Ele ":
        sample = samplesDataDiEle
        configFile = "config/overall/ttH.MultiLeptons.DiEleFakes.config"
if "flips" in sys.argv:
    mcPostfix = " -chargeMis"
    invPostfix = " "
    analysis = "ttHflips"
    sample = samples94XData
    fileListDirectory = "config/files/ttH_2018/SmallJobs/data/"
    if "ttWctrl" in sys.argv:
        analysis += "ttWctrl"
        configFile = "config/overall/ttH.MultiLeptons.ttWControlFlips.config"
    elif triggerName == "TTHLep_2L ":
        configFile = "config/overall/ttH.MultiLeptons.DiLepFlips.config"
    if triggerName == "TTHLep_MuEle ":
        sample = samplesDataMuEle
        configFile = "config/overall/ttH.MultiLeptons.EleMuFlips.config"
    if triggerName == "TTHLep_2Mu ":
        sample = samplesDataDiMu
        configFile = "config/overall/ttH.MultiLeptons.DiMuFlips.config"
    if triggerName == "TTHLep_2Ele ":
        sample = samplesDataDiEle
        configFile = "config/overall/ttH.MultiLeptons.DiEleFlips.config"
if triggerName == "TTHLep_2L ":
    analysis += "2L"
if triggerName == "TTHLep_3L ":
    analysis += "3L"
if "systs" in sys.argv:
    analysis += "Systs"
    sample = samplesSyst
    fileListDirectory = "config/files/systSamples/"
if "skims" in sys.argv:
    makeSkims = True 
if "electron" in sys.argv:
    configFile = configFile.split("overall/")[0] + "overall/electron" + configFile.split("overall/")[-1]
    triggerName = "Electron "
#   if not "data" in sys.argv:
    analysis += "Ele"
if "jesTest" in sys.argv:
    sample = jesTestSamples
    analysis += "JESTest"
if "All2L" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.DiLepton.All.config"
    analysis += "All2L"
if "All3L" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.TriLepton.All.config"
    analysis += "All3L"
    triggerName = "TTHLep_3L "
if "AlljesUp" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.DiLeptonJESUp.All.config"
    analysis += "AllJESUp"
if "AlljesDown" in sys.argv:
    configFile = "config/overall/ttH.MultiLeptons.DiLeptonJESDown.All.config"
    analysis += "AllJESDown"
#executable = "Wt_generic.x"
#for the queue
workpath    = os.getcwd()+"/"+analysis +"/"
jobDir      = workpath+"/"+"Jobs"
smallerJobs = True
AnalyzerDir = workpath+"/"+"Analyzer"
task        = analysis+"_"+taskname
rootplizer  = "Rootplizer_"+task+".cc"
headplizer  = "Rootplizer_"+task+".h"
#Directory of input files
nJobs = {
"TTHnobb":22,
"TTWToLNu":11,
"TTZToLL":22,
"TTJets":282
}

nJobsSum16 = {
"qcd1000_1500":12,
"qcd100_200":54,
"qcd1500_2000":9,
"qcd2000_inf":5,
"qcd200_300":14,
"qcd300_500":41,
"qcd500_700":44,
"qcd700_1000":36,
"sChan":3,
"tChan_top":33,
"tChan_antitop":152,
"ttbar":34,
"tW_top":3,
"tW_antitop":3,
"ww":3,
"wz":3,
"zz":3,
"zPlusJetsLowMass":74,
"zPlusJetsHighMass":72,
"wPlusJetsMCatNLO":24,
"wPlusJetsMadgraph":43,
"SingMuB":174,
"SingMuC":58,
"SingMuD":98,
"SingMuE":83,
"SingMuF":61,
"SingMuG":132
}

nJobs76X = {
"qcd1000_1500":13,
"qcd100_200":193,
"qcd1500_2000":10,
"qcd2000_inf":6,
"qcd200_300":46,
"qcd300_500":50,
"qcd500_700":48,
"qcd700_1000":36,
"sChan":3,
"tChan":48,
"ttbar":242,
"tW_top":3,
"tW_antitop":3,
"wPlusJets":115,
"ww":3,
"wz":3,
"zz":3,
"zPlusJetsLowMass":76,
"zPlusJetsHighMass":69,
"wPlusJetsMCatNLO":60,
"singleMuon":108
}
#####
##   The script itsself
#####
#cshFilePath = jobDir+"/"+"sh"
#logFilePath = jobDir+"/"+"log"
if os.path.exists(jobDir):
    os.popen('rm -fr '+jobDir)
if os.path.exists(AnalyzerDir):
        os.popen('rm -fr '+AnalyzerDir)
#os.popen('mkdir -p '+cshFilePath)
#os.popen('mkdir -p '+logFilePath)
allSubmit = 0
allMerge = 0
if os.path.exists(os.getcwd()+"/all.sh"):
    allSubmit = open(os.getcwd()+"/all.sh","a")
    allMerge = open(os.getcwd()+"/mergeAll.sh","a")
else:
    allSubmit = open(os.getcwd()+"/all.sh","w")
    allMerge = open(os.getcwd()+"/mergeAll.sh","w")
    allSubmit.write("#!/bin/bash\n")
    allMerge.write("#!/bin/bash\n")
allSubmit.write("bash "+analysis+"Submit.sh\n")
allMerge.write("bash "+analysis+"merge.sh\n")
allSubmit.close()
allMerge.close()

allJobFileName = analysis+"Submit.sh"
allJobFile      = file(allJobFileName,"w")
print >> allJobFile, "#!/bin/bash"
print >> allJobFile, "cd ",analysis

MergeFileName = analysis+"merge.sh"
MergeFile      = file(MergeFileName,"w")
MergeSourceFile = " "
def prepareSubmitJob(submitFileName,cshFileName, outPutFileName, errorFileName):
    cshFile      = file(submitFileName,"w")
    print >> cshFile, "Universe     = vanilla"
    print >> cshFile, "getenv       = true"
    print >> cshFile, "Executable   = ",cshFileName
    print >> cshFile, "Output       = ",outPutFileName
    print >> cshFile, "Error        = ",errorFileName
    print >> cshFile, "Queue"

def prepareCshJob(sample,shFile,frameworkDir,workpath,samplePost=""):
        subFile      = file(shFile,"w")
        print >> subFile, "#!/bin/bash"
        print >> subFile, "/bin/hostname"
        print >> subFile, "source /cvmfs/sft.cern.ch/lcg/views/LCG_93/x86_64-slc6-gcc62-opt/setup.sh"
        print >> subFile, "gcc -v"
        print >> subFile, "pwd"
    #print >> subFile, "cd /publicfs/cms/data/TopQuark/cms13TeV/software/root/bin/"
    #print >> subFile, "source thisroot.csh"
    #print >> subFile, "cd /publicfs/cms/user/libh/CMSSW_5_3_9/src/ttH_13Tev"
    #print >> subFile, "setenv SCRAM_ARCH slc5_amd64_gcc462"
    #print >> subFile, "source /cvmfs/cms.cern.ch/cmsset_default.csh"
    #print >> subFile, "source  /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 5.34.18"
    #print >> subFile, "source  source /afs/ihep.ac.cn/soft/CMS/64bit/root/profile/rootenv-entry 6.08.02"
        #print >> subFile, "source /cvmfs/cms.cern.ch/cmsset_default.sh"
        #print >> subFile, "cd /cvmfs/cms.cern.ch/slc6_amd64_gcc493/cms/cmssw/CMSSW_7_6_3/src/"
        #print >> subFile, "cmsenv"
        #print >> subFile, "cd -"

        #print >> subFile, "eval \`scramv1 runtime -sh\`"
        print >> subFile, "cd "+frameworkDir
    #print >> subFile, "cp ${jobDir}/getAhist.C ."
#   print >> subFile, frameworkDir+"bin/Wt/Wt_generic.x -config "+frameworkDir+"SingleTop.Wt.LP.mm1+j.muonMSSmeardown.config -inlist "+frameworkDir+"config/files/"+fileListDirectory+sample+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -skimfile "+workpath+"/"+sample+"/skims/"+sample+samplePost+"Skim.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger Muon -PileUpWgt -BWgt"
        skimString =""
        if makeSkims: skimString = " -skimfile "+workpath+"/"+sample+"/skims/"+sample+samplePost+"Skim.root "
    #print >> subFile, frameworkDir+executable+" -config "+frameworkDir+configFile+" -inlist "+frameworkDir+fileListDirectory+sample+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger " + triggerName + invPostfix + mcPostfix + skimString + " -nJets {0} -nbJets {1}".format(nJets,nbJets)
        print >> subFile, frameworkDir+executable+" -config "+frameworkDir+configFile+" -inlist "+frameworkDir+fileListDirectory+sample+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger " + triggerName + invPostfix + mcPostfix + skimString
        #print >> subFile, "root -b -q -l "+rootplizer+"'(\""+input+"\",\""+output+"\")'"
        subprocess.call("chmod 777 "+shFile, shell=True)

#for iroot in range(nroot):
for k in sample:
    print k
    sampleName = k
    
    #First, let's get rid of any 

    os.popen('mkdir -p '+workpath + sampleName)
    os.popen('mkdir -p '+workpath + sampleName + "/scripts")
    os.popen('mkdir -p '+workpath + sampleName + "/hists")
    os.popen('mkdir -p '+workpath + sampleName + "/skims")
    os.popen('mkdir -p '+workpath + sampleName + "/logs")

    if not smallerJobs:

        submitFileName = workpath + sampleName + "/scripts/" + sampleName + ".submit"
        shFileName = workpath + sampleName + "/scripts/" + sampleName +  ".sh"
        logFileName = workpath + sampleName + "/logs/" + sampleName + ".log"
        errorFileName = workpath + sampleName + "/logs/" + sampleName + ".error"
        
#       prepareSubmitJob(submitFileName, shFileName, logFileName, errorFileName)
        prepareCshJob(sampleName,shFileName,frameworkDir,workpath)
        
        submitPath = sampleName + "/scripts/" + sampleName + ".submit"
        
        #print >> allJobFile, "condor_submit "+ submitPath + " -group cms -name job@schedd01.ihep.ac.cn"
        print >> allJobFile, "hep_sub "+ shFileName + " -o "+logFileName+ " -e "+errorFileName

    else:
        inputFiles  = [f for f in os.listdir(frameworkDir+fileListDirectory) if sampleName in f]
        for j in range(len(inputFiles)):
#           submitFileName = workpath + sampleName + "/scripts/" + sampleName + str(j) + ".submit"
            shFileName = workpath + sampleName + "/scripts/" + sampleName + str(j) + ".sh"
            logFileName = workpath + sampleName + "/logs/" + sampleName + str(j) + ".log"
            errorFileName = workpath + sampleName + "/logs/" + sampleName + str(j) + ".error"
            
#           prepareSubmitJob(submitFileName, shFileName, logFileName, errorFileName)
            prepareCshJob(sampleName,shFileName,frameworkDir,workpath,str(j))

            submitPath = sampleName + "/scripts/" + sampleName + str(j) + ".submit"
            
#           print >> allJobFile, "hep_sub "+ submitPath + " -name job@schedd01.ihep.ac.cn"
            print >> allJobFile, "hep_sub "+ shFileName + " -o "+logFileName+ " -e "+errorFileName
#           print >> allJobFile, "condor_submit "+ submitPath + " -group cms -name job@schedd01.ihep.ac.cn"

    print >> MergeFile, "hadd -f "+analysis+"/"+sampleName + "/hists/merged"+sampleName+".root  "+analysis+"/"+sampleName + "/hists/"+sampleName+"*hists.root"
    print >> MergeFile, "hadd -f "+analysis+"/"+sampleName + "/skims/merged"+sampleName+".root  "+analysis+"/"+sampleName + "/skims/"+sampleName+"*Skim.root"

#print >> MergeFile, "cd",outputDirectory
#print >> MergeFile, "hadd Merged_rootplas.root",MergeSourceFile


#if mcPostfix == "":
#   lepton = "Mu"
#   if "electron" in sys.argv: lepton = "Ele"
#   print >> MergeFile, "mkdir -p "+analysis+"/single{0}/hists/".format(lepton)
#   print >> MergeFile, "hadd -f "+analysis+"/single{0}/hists/mergedsingle{0}.root ".format(lepton) + analysis+"/Sing{0}*/hists/merged*".format(lepton)
#   print >> MergeFile, "mkdir -p "+analysis+"/single{0}/skims/".format(lepton)
#   print >> MergeFile, "hadd -f "+analysis+"/single{0}/skims/mergedsingle{0}.root ".format(lepton) + analysis+"/Sing{0}*/skims/merged*".format(lepton)

print >> allJobFile, "cd -"
print "Finished",analysis
