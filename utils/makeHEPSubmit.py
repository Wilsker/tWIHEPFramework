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
configFile = "config/overall/ttH.MultiLeptons.EleMuSR.config"
invPostfix = ""
#mcPostfix = " -MCatNLO -mc -bTagReshape -lepSFs -PileUpWgt -chargeMis -FakeRate -TriggerSFs"
#mcPostfix = " -MCatNLO -mc -lepSFs -chargeMis -FakeRate -TriggerSFs -bTagReshape"
mcPostfix = " -chargeMis -FakeRate"
triggerName = "TTHLep_2Ele "
nJets = 3
nbJets = 1
fileListDirectory = "config/files/ttH_Mor17/"
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
#samplesMC=[
#"TTHnobb","TTWToLNuext2","TTWToLNuext1","TTZToLLNuNu","TTZToLL_M1to10","TTJets_sinLepTbar_v1","TTJets_sinLepTbar_ext1","TTJets_sinLepT_v1","TTJets_sinLepT_ext1","TTJets_diLep_v1","TTJets_diLep_ext1","TTGToJets_ext1","WGToLNuG_ext2","TGJets_v1","WGToLNuG_ext1","ZGTo2LG","TGJets_ext1","WpWpJJ","WW_DS_To2L2Nu","WWW_4F","WWZ","WZZ","ZZZ","tZq","TTTT","tWll","amcWJets","WZTo3LNu","WWTo2L2Nu","ZZTo4L"
#]
samplesMC=[
"TTHnobb","TTWToLNuext2","TTWToLNuext1","TTZToLLNuNu","TTZToLL_M1to10","TTJets_sinLepTbar_v1","TTJets_sinLepTbar_ext1","TTJets_sinLepT_v1","TTJets_sinLepT_ext1","TTJets_diLep_v1","TTJets_diLep_ext1","WpWpJJ","WW_DS_To2L2Nu","WWW_4F","WWZ","WZZ","ZZZ","tZq","TTTT","tWll","amcWJets","WZTo3LNu","WWTo2L2Nu","ZZTo4L"
]
#samplesMC = [
#"TTHnobb","TTWToLNuext2","TTWToLNuext1"
#]
samplesConv = [
"TTGToJets_ext1","WGToLNuG_ext2","TGJets_v1","WGToLNuG_ext1","ZGTo2LG","TGJets_ext1"
]

samplesDataMuEle=[
"MuEleGmRecoverB1","MuEleGmRecoverC1","MuEleGmRecoverD1","MuEleGmRecoverE1","MuEleGmRecoverF1","MuEleGmRecoverF2","MuEleGmRecoverG1","MuEleGmRecoverH1","MuEleGmRecoverH2",
"SEleRecoverB1","SEleRecoverC1","SEleRecoverD1","SEleRecoverE1","SEleRecoverF1","SEleRecoverF2","SEleRecoverG1","SEleRecoverH1",
"SMuRecoverB1","SMuRecoverC1","SMuRecoverD1","SMuRecoverE1","SMuRecoverF1","SMuRecoverF2","SMuRecoverG1","SMuRecoverH1","SMuRecoverH2",
"MuEleGmB1","MuEleGmC1","MuEleGmD1","MuEleGmE1","MuEleGmF1","MuEleGmF2","MuEleGmG1","MuEleGmH1","MuEleGmH2",
"SEleB1","SEleC1","SEleD1","SEleE1","SEleF1","SEleF2","SEleG1","SEleH1","SEleH2",
"SMuB1","SMuC1","SMuD1","SMuE1","SMuF1","SMuF2","SMuG1","SMuH1","SMuH2"
]

samplesDataDiMu=[
"DMuRecoverB1","DMuRecoverC1","DMuRecoverD1","DMuRecoverE1","DMuRecoverF1","DMuRecoverF2","DMuRecoverG1","DMuRecoverH1","DMuRecoverH2",
"SEleRecoverB1","SEleRecoverC1","SEleRecoverD1","SEleRecoverE1","SEleRecoverF1","SEleRecoverF2","SEleRecoverG1","SEleRecoverH1",
"SMuRecoverB1","SMuRecoverC1","SMuRecoverD1","SMuRecoverE1","SMuRecoverF1","SMuRecoverF2","SMuRecoverG1","SMuRecoverH1","SMuRecoverH2",
"DMuB1","DMuC1","DMuD1","DMuE1","DMuF1","DMuF2","DMuG1","DMuH1","DMuH2",
"SEleB1","SEleC1","SEleD1","SEleE1","SEleF1","SEleF2","SEleG1","SEleH1","SEleH2",
"SMuB1","SMuC1","SMuD1","SMuE1","SMuF1","SMuF2","SMuG1","SMuH1","SMuH2"
]

samplesDataDiEle=[
"DEleGmRecoverB1","DEleGmRecoverC1","DEleGmRecoverD1","DEleGmRecoverE1","DEleGmRecoverF1","DEleGmRecoverF2","DEleGmRecoverG1","DEleGmRecoverH1","DEleGmRecoverH2",
"SEleRecoverB1","SEleRecoverC1","SEleRecoverD1","SEleRecoverE1","SEleRecoverF1","SEleRecoverF2","SEleRecoverG1","SEleRecoverH1",
"SMuRecoverB1","SMuRecoverC1","SMuRecoverD1","SMuRecoverE1","SMuRecoverF1","SMuRecoverF2","SMuRecoverG1","SMuRecoverH1","SMuRecoverH2",
"DEleGmB1","DEleGmC1","DEleGmD1","DEleGmE1","DEleGmF1","DEleGmF2","DEleGmG1","DEleGmH1","DEleGmH2",
"SEleB1","SEleC1","SEleD1","SEleE1","SEleF1","SEleF2","SEleG1","SEleH1","SEleH2",
"SMuB1","SMuC1","SMuD1","SMuE1","SMuF1","SMuF2","SMuG1","SMuH1","SMuH2"
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
    if triggerName == "TTHLep_MuEle ":
        configFile = "config/overall/ttH.MultiLeptons.EleMuJESup.config"
    if triggerName == "TTHLep_2Mu ":
        configFile = "config/overall/ttH.MultiLeptons.DiMuJESup.config"
    if triggerName == "TTHLep_2Ele ":
        configFile = "config/overall/ttH.MultiLeptons.DiEleJESup.config"
    analysis += "JESUp"
if "jesDown" in sys.argv:
    if triggerName == "TTHLep_MuEle ":
        configFile = "config/overall/ttH.MultiLeptons.EleMuJESdown.config"
    if triggerName == "TTHLep_2Mu ":
        configFile = "config/overall/ttH.MultiLeptons.DiMuJESdown.config"
    if triggerName == "TTHLep_2Ele ":
        configFile = "config/overall/ttH.MultiLeptons.DiEleJESdown.config"
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
if "convs" in sys.argv:
    mcPostfix = " -mcPromptGamma"
    analysis += "Conv"
    sample = samplesConv
else :
    mcPostfix = " -mcPromptFS"
if "data" in sys.argv:
    mcPostfix = ""
    analysis += "Data"
    if triggerName == "TTHLep_MuEle ":
        sample = samplesDataMuEle
        configFile = "config/overall/ttH.MultiLeptons.EleMuSR.config"
    if triggerName == "TTHLep_2Mu ":
        sample = samplesDataDiMu
        configFile = "config/overall/ttH.MultiLeptons.DiMuSR.config"
    if triggerName == "TTHLep_2Ele ":
        sample = samplesDataDiEle
        configFile = "config/overall/ttH.MultiLeptons.DiEleSR.config"
    if "electron" in sys.argv:
        sample = samplesDataElectron
if "fakes" in sys.argv:
    mcPostfix = "-FakeRate"
    analysis += "fakes"
    if triggerName == "TTHLep_MuEle ":
        sample = samplesDataMuEle
        configFile = "config/overall/ttH.MultiLeptons.EleMuFakes.config"
    if triggerName == "TTHLep_2Mu ":
        sample = samplesDataDiMu
        configFile = "config/overall/ttH.MultiLeptons.DiMuFakes.config"
    if triggerName == "TTHLep_2Ele ":
        sample = samplesDataDiEle
        configFile = "config/overall/ttH.MultiLeptons.DiEleFakes.config"
if "flips" in sys.argv:
    mcPostfix = "-chargeMis"
    analysis += "flips"
    if triggerName == "TTHLep_MuEle ":
        sample = samplesDataMuEle
        configFile = "config/overall/ttH.MultiLeptons.EleMuFlips.config"
    if triggerName == "TTHLep_2Mu ":
        sample = samplesDataDiMu
        configFile = "config/overall/ttH.MultiLeptons.DiMuFlips.config"
    if triggerName == "TTHLep_2Ele ":
        sample = samplesDataDiEle
        configFile = "config/overall/ttH.MultiLeptons.DiEleFlips.config"
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
"TTHnobb":11,
"TTWToLNuext2":4,
"TTWToLNuext1":3,
"TTZToLLNuNu":3,
"TTZToLL_M1to10":2,
"TTJets_sinLepTbar_v1":19,
"TTJets_sinLepTbar_ext1":45,
"TTJets_sinLepT_v1":14,
"TTJets_sinLepT_ext1":48,
"TTJets_diLep_v1":6,
"TTJets_diLep_ext1":26,
"TTGToJets_ext1":24,
"WGToLNuG_ext2":13,
"TGJets_v1":2,
"WGToLNuG_ext1":15,
"ZGTo2LG":21,
"TGJets_ext1":4,
"WpWpJJ":1,
"WW_DS_To2L2Nu":2,
"WWW_4F":1,
"WWZ":1,
"WZZ":1,
"ZZZ":1,
"tZq":31,
"TTTT":2,
"tWll":1,
"amcWJets":30,
"WZTo3LNu":4,
"WWTo2L2Nu":3,
"ZZTo4L":10,
"DEleGmRecoverB1":47,
"DEleGmRecoverC1":14,
"DEleGmRecoverD1":21,
"DEleGmRecoverE1":10,
"DEleGmRecoverF1":7,
"DEleGmRecoverF2":1,
"DEleGmRecoverG1":31,
"DEleGmRecoverH1":38,
"DEleGmRecoverH2":1,
"MuEleGmRecoverB1":32,
"MuEleGmRecoverC1":17,
"MuEleGmRecoverD1":16,
"MuEleGmRecoverE1":23,
"MuEleGmRecoverF1":15,
"MuEleGmRecoverF2":3,
"MuEleGmRecoverG1":27,
"MuEleGmRecoverH1":36,
"MuEleGmRecoverH2":1,
"DMuRecoverB1":58,
"DMuRecoverC1":12,
"DMuRecoverD1":13,
"DMuRecoverE1":20,
"DMuRecoverF1":13,
"DMuRecoverF2":3,
"DMuRecoverG1":38,
"DMuRecoverH1":23,
"DMuRecoverH2":1,
"SEleRecoverB1":29,
"SEleRecoverC1":12,
"SEleRecoverD1":23,
"SEleRecoverE1":20,
"SEleRecoverF1":16,
"SEleRecoverF2":1,
"SEleRecoverG1":39,
"SEleRecoverH1":25,
"SMuRecoverB1":30,
"SMuRecoverC1":14,
"SMuRecoverD1":25,
"SMuRecoverE1":20,
"SMuRecoverF1":13,
"SMuRecoverF2":2,
"SMuRecoverG1":29,
"SMuRecoverH1":36,
"SMuRecoverH2":1,
"DEleGmB1":128,
"DEleGmC1":44,
"DEleGmD1":76,
"DEleGmE1":74,
"DEleGmF1":46,
"DEleGmF2":8,
"DEleGmG1":110,
"DEleGmH1":114,
"DEleGmH2":4,
"MuEleGmB1":144,
"MuEleGmC1":41,
"MuEleGmD1":82,
"MuEleGmE1":59,
"MuEleGmF1":38,
"MuEleGmF2":6,
"MuEleGmG1":116,
"MuEleGmH1":118,
"MuEleGmH2":4,
"DMuB1":116,
"DMuC1":47,
"DMuD1":85,
"DMuE1":62,
"DMuF1":40,
"DMuF2":6,
"DMuG1":104,
"DMuH1":131,
"DMuH2":4,
"SEleB1":146,
"SEleC1":46,
"SEleD1":75,
"SEleE1":62,
"SEleF1":36,
"SEleF2":8,
"SEleG1":103,
"SEleH1":129,
"SEleH2":5,
"SMuB1":145,
"SMuC1":44,
"SMuD1":73,
"SMuE1":63,
"SMuF1":40,
"SMuF2":7,
"SMuG1":113,
"SMuH1":117,
"SMuH2":4
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
