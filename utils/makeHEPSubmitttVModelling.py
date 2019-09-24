import sys
import os
import optparse
import glob
import string
import subprocess
#####
##   Parameters to be specified by the user
#####
# options
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-s', '--sample',        dest='sampleType'  ,      help='sample types, isSigExt, isDNN, isData or isHjtagger',      default='isSigExt',        type='string')
parser.add_option('-j', '--jec',        dest='jec'  ,      help='jec types, nominal, JESUp, JESDown, JERUp, or JERDown',      default='nominal',        type='string')
parser.add_option('-y', '--year',        dest='year'  ,      help='data taking period 2016, 2017, or 2018',      default='2018',        type='int')
parser.add_option('-n', '--nlep',        dest='nlep'  ,      help='number of selected leptons 2, 3 or 4',      default='2',        type='int')


#analysis and task
analysis = "ttH"
taskname = "EvtSel"
frameworkDir = "/publicfs/cms/data/TopQuark/cms13TeV/Binghuan/tWIHEPFramework/"
executable = "bin/ttH/ttH_generic.x"
configFile = "config/overall/ttV-modelling/ttH.Multilepton.2lss_1bgeq4j.gencuts.config"
#invPostfix = " -MCatNLO -mc -bTagReshape -PileUpWgt -ReCalPU -TriggerSFs -lepSFs -FakeRate -chargeMis"
#invPostfix = " -MCatNLO -mc -bTagReshape -PileUpWgt"
invPostfix = " -MCatNLO -mc -PileUpWgt"
mcPostfix = " "
triggerName = "TTHLep_2L "
fileListDirectory = "config/files/ttVmodelling_studies/"
makeSkims = True

samples2016Data = [
'Legacy16V1_SEleBlockB', 'Legacy16V1_SEleBlockC', 'Legacy16V1_SEleBlockD', 'Legacy16V1_SEleBlockE', 'Legacy16V1_SEleBlockF', 'Legacy16V1_SEleBlockG', 'Legacy16V1_SEleBlockH', 'Legacy16V1_SMuBlockB', 'Legacy16V1_SMuBlockC', 'Legacy16V1_SMuBlockD',
'Legacy16V1_SMuBlockE', 'Legacy16V1_SMuBlockF', 'Legacy16V1_SMuBlockG', 'Legacy16V1_SMuBlockH', 'Legacy16V1_DblEGBlockB', 'Legacy16V1_DblEGBlockC', 'Legacy16V1_DblEGBlockD', 'Legacy16V1_DblEGBlockE', 'Legacy16V1_DblEGBlockF', 'Legacy16V1_DblEGBlockG',
'Legacy16V1_DblEGBlockH', 'Legacy16V1_DblMuBlockB', 'Legacy16V1_DblMuBlockC', 'Legacy16V1_DblMuBlockD', 'Legacy16V1_DblMuBlockE', 'Legacy16V1_DblMuBlockF', 'Legacy16V1_DblMuBlockG', 'Legacy16V1_DblMuBlockH', 'Legacy16V1_MuEGBlockB', 'Legacy16V1_MuEGBlockC',
'Legacy16V1_MuEGBlockD', 'Legacy16V1_MuEGBlockE', 'Legacy16V1_MuEGBlockF', 'Legacy16V1_MuEGBlockG', 'Legacy16V1_MuEGBlockH',
]

samples2017Data = [
'Legacy17V1_SEleBlockB', 'Legacy17V1_SEleBlockC', 'Legacy17V1_SEleBlockD', 'Legacy17V1_SEleBlockE', 'Legacy17V1_SEleBlockF', 'Legacy17V1_SMuBlockB', 'Legacy17V1_SMuBlockC', 'Legacy17V1_SMuBlockD', 'Legacy17V1_SMuBlockE', 'Legacy17V1_SMuBlockF',
'Legacy17V1_DblEGBlockB', 'Legacy17V1_DblEGBlockC', 'Legacy17V1_DblEGBlockD', 'Legacy17V1_DblEGBlockE', 'Legacy17V1_DblEGBlockF', 'Legacy17V1_DblMuBlockB', 'Legacy17V1_DblMuBlockC', 'Legacy17V1_DblMuBlockD', 'Legacy17V1_DblMuBlockE', 'Legacy17V1_DblMuBlockF',
'Legacy17V1_MuEGBlockB', 'Legacy17V1_MuEGBlockC', 'Legacy17V1_MuEGBlockD', 'Legacy17V1_MuEGBlockE', 'Legacy17V1_MuEGBlockF',
]

samples2018Data = [
'Legacy18V1_SMuBlockA', 'Legacy18V1_SMuBlockB', 'Legacy18V1_SMuBlockC', 'Legacy18V1_SMuBlockD', 'Legacy18V1_EleGBlockA', 'Legacy18V1_EleGBlockB', 'Legacy18V1_EleGBlockC', 'Legacy18V1_EleGBlockD', 'Legacy18V1_DblMuBlockA', 'Legacy18V1_DblMuBlockB',
'Legacy18V1_DblMuBlockC', 'Legacy18V1_DblMuBlockD', 'Legacy18V1_MuEGBlockA', 'Legacy18V1_MuEGBlockB', 'Legacy18V1_MuEGBlockC', 'Legacy18V1_MuEGBlockD',
]

samples2016MC=[
"Legacy16V1_ttHnobb", "Legacy16V1_THQ_TuneCP5_ctcvcp", "Legacy16V1_THW_TuneCP5_ctcvcp", "Legacy16V1_TTWJets", "Legacy16V1_TTWW",
"Legacy16V1_TTZ_M1to10", "Legacy16V1_TTZ_M10_ext1", "Legacy16V1_TTZ_M10_ext2", "Legacy16V1_ST_sCh_lepDecay", "Legacy16V1_ST_sCh_lepDecay_PS", "Legacy16V1_ST_tCh_top", "Legacy16V1_ST_tCh_antitop", "Legacy16V1_ST_tCh_antitop_PS", "Legacy16V1_ST_tW_top", "Legacy16V1_ST_tW_antitop",
"Legacy16V1_tWll", "Legacy16V1_TTGJets_v1", "Legacy16V1_TTGJets_ext", "Legacy16V1_TGJetsLep", "Legacy16V1_WGToLNuG_ext1", "Legacy16V1_WGToLNuG_ext2", "Legacy16V1_WGToLNuG_ext3",
"Legacy16V1_ZGToLLG", "Legacy16V1_DYJets_M10to50", "Legacy16V1_DYJets_M50", "Legacy16V1_WZG", "Legacy16V1_WWTo2LNu", "Legacy16V1_WZTo3LNu", "Legacy16V1_ZZTo4L", "Legacy16V1_WJets_v1", "Legacy16V1_WJets_ext", "Legacy16V1_WW_DS",
"Legacy16V1_WWW", "Legacy16V1_WWZ", "Legacy16V1_WZZ", "Legacy16V1_ZZZ", "Legacy16V1_TTTT", "Legacy16V1_tZq_ext", "Legacy16V1_tZq_PS", "Legacy16V1_WpWpJJ", "Legacy16V1_GGHToTauTau", "Legacy16V1_VBFHToTauTau",
"Legacy16V1_VHToNonbb", "Legacy16V1_ZHTobb", "Legacy16V1_ZHToTauTau", "Legacy16V1_TTJets_DiLep_v1", "Legacy16V1_TTJets_DiLep_ext", "Legacy16V1_TTJets_TToSingleLep_v1", "Legacy16V1_TTJets_TToSingleLep_ext", "Legacy16V1_TTJets_TbarToSingleLep_v1",
"Legacy16V1_TTJets_TbarToSingleLep_ext","Legacy16V1_TTH_ctcvcp", "Legacy16V1_ggHToTauTau_v3", "Legacy16V1_ggHToZZTo4L", "Legacy16V1_ggHToWWToLNuQQ", "Legacy16V1_ggHToWWTo2L2Nu", "Legacy16V1_ggHToMuMu", "Legacy16V1_ggHToBB_v2", "Legacy16V1_ggHToBB_ext1", "Legacy16V1_ggHToGG",
"Legacy16V1_VBFHToZZTo4L","Legacy16V1_VBFHToWWToLNuQQ", "Legacy16V1_VBFHToWWTo2L2Nu", "Legacy16V1_VBFHToMuMu", "Legacy16V1_VBFHToBB_v1", "Legacy16V1_VBFHToBB_ext1", "Legacy16V1_VBFHToGG_ext1", "Legacy16V1_VBFHToGG_ext2",
]

samples2016MVA=[
"Legacy16V1_TTHnobb","Legacy16V1_THQ_Tune8M1_ctcvcp","Legacy16V1_THQ","Legacy16V1_THW_Tune8M1_ctcvcp","Legacy16V1_THW","Legacy16V1_TTTo2L_PS","Legacy16V1_TTToSemiLep_PS","Legacy16V1_TTToHad_PS","Legacy16V1_ttZ",
"Legacy16V1_ttW",
]

samples2017MC=[
"Legacy17V1_ttHnobb", "Legacy17V1_THQ_ctcvcp", "Legacy17V1_THW_ctcvcp", "Legacy17V1_TTWJets", "Legacy17V1_TTW_PS", "Legacy17V1_TTWW", "Legacy17V1_TTZ_M1to10", "Legacy17V1_TTZ_M10",
"Legacy17V1_TTZ_M10_PS", "Legacy17V1_ST_sCh_lepDecay", "Legacy17V1_ST_sCh_lepDecay_PS", "Legacy17V1_ST_tCh_top", "Legacy17V1_ST_tCh_top_PS", "Legacy17V1_ST_tCh_antitop", "Legacy17V1_ST_tCh_antitop_PS", "Legacy17V1_ST_tW_top", "Legacy17V1_ST_tW_top_PS", "Legacy17V1_ST_tW_antitop",
"Legacy17V1_ST_tW_antitop_PS", "Legacy17V1_tWll", "Legacy17V1_TTGJets_v1", "Legacy17V1_TTGJets_ext",
"Legacy17V1_TGJetsLep", "Legacy17V1_WGToLNuG_Tune", "Legacy17V1_ZGToLLG_01J", "Legacy17V1_W1JetsToLNu", "Legacy17V1_W2JetsToLNu", "Legacy17V1_W3JetsToLNu", "Legacy17V1_W4JetsToLNu", "Legacy17V1_DYJets_M10to50_v1", "Legacy17V1_DYJets_M10to50_ext", "Legacy17V1_DYJets_M50_v1",
"Legacy17V1_DYJets_M50_ext", "Legacy17V1_WZG", "Legacy17V1_WWTo2LNu_v1", "Legacy17V1_WWTo2LNu_ext", "Legacy17V1_WZTo3LNu", "Legacy17V1_ZZTo4L_v1", "Legacy17V1_ZZTo4L_ext1", "Legacy17V1_ZZTo4L_ext2", "Legacy17V1_WJets_v1", "Legacy17V1_WJets_ext",
"Legacy17V1_WW_DS", "Legacy17V1_WWW", "Legacy17V1_WWZ", "Legacy17V1_WZZ", "Legacy17V1_ZZZ", "Legacy17V1_TTTT", "Legacy17V1_TTTT_PS", "Legacy17V1_tZq", "Legacy17V1_WpWpJJ", "Legacy17V1_GGHToTauTau_v1",
"Legacy17V1_GGHToTauTau_ext", "Legacy17V1_VBFHToTauTau", "Legacy17V1_VHToNonbb", "Legacy17V1_ZHTobb", "Legacy17V1_ZHToTauTau", "Legacy17V1_TTJets_DiLep",
"Legacy17V1_TTJets_TToSingleLep", "Legacy17V1_TTJets_TbarToSingleLep",
"Legacy17V1_TTH_ctcvcp", "Legacy17V1_ggHToZZTo4L_ext1", "Legacy17V1_ggHToZZTo4L_ext3", "Legacy17V1_ggHToZZTo4L_ext4", "Legacy17V1_ggHToZZTo2L2Q", "Legacy17V1_ggHToWWToLNuQQ", "Legacy17V1_ggHToWWTo2L2Nu", "Legacy17V1_ggHToMuMu_v1", "Legacy17V1_ggHToMuMu_ext1", "Legacy17V1_ggHToBB",
"Legacy17V1_ggHToGG", "Legacy17V1_VBFHToZZTo4L_ext2", "Legacy17V1_VBFHToZZTo4L_ext1", "Legacy17V1_VBFHToZZTo4L_v1", "Legacy17V1_VBFHToWWToLNuQQ", "Legacy17V1_VBFHToWWTo2L2Nu", "Legacy17V1_VBFHToMuMu", "Legacy17V1_VBFHToBB", "Legacy17V1_VBFHToGG",
]

samples2017MVA=[
"Legacy17V1_TTHnobb_v1","Legacy17V1_TTHnobb_ext","Legacy17V1_TTTo2L","Legacy17V1_TTTo2L_PS","Legacy17V1_TTToSemiLep","Legacy17V1_TTToSemiLep_PS","Legacy17V1_TTToHad","Legacy17V1_TTToHad_PS","Legacy17V1_ttZ_v1","Legacy17V1_ttZ_ext","Legacy17V1_ttW_v1","Legacy17V1_ttW_ext",
]

samples2018MC=[
"Legacy18V1_TTH_ctcvcp", "Legacy18V1_THQ_ctcvcp", "Legacy18V1_THW_ctcvcp", "Legacy18V1_TTWJets", "Legacy18V1_TTWW_v1", "Legacy18V1_TTWW_ext1", "Legacy18V1_TTZ_M1to10", "Legacy18V1_TTZ_M10", "Legacy18V1_ST_sCh_lepDecay",
"Legacy18V1_ST_tCh_top", "Legacy18V1_ST_tCh_antitop", "Legacy18V1_ST_tW_top", "Legacy18V1_ST_tW_antitop", "Legacy18V1_tWll", "Legacy18V1_TTGJets", "Legacy18V1_TGJetsLep",
"Legacy18V1_WGToLNuG_Tune", "Legacy18V1_ZGToLLG_01J", "Legacy18V1_W1JetsToLNu", "Legacy18V1_W2JetsToLNu", "Legacy18V1_W3JetsToLNu", "Legacy18V1_W4JetsToLNu", "Legacy18V1_DYJets_M10to50", "Legacy18V1_DYJets_M50_v1", "Legacy18V1_DYJets_M50_ext", "Legacy18V1_WZG",
"Legacy18V1_WWTo2LNu", "Legacy18V1_WZTo3LNu", "Legacy18V1_ZZTo4L_v1", "Legacy18V1_ZZTo4L_ext", "Legacy18V1_WJets", "Legacy18V1_WW_DS", "Legacy18V1_WWW", "Legacy18V1_WWZ", "Legacy18V1_WZZ", "Legacy18V1_ZZZ",
"Legacy18V1_TTTT", "Legacy18V1_tZq", "Legacy18V1_WpWpJJ", "Legacy18V1_GGHToTauTau", "Legacy18V1_VBFHToTauTau", "Legacy18V1_VHToNonbb", "Legacy18V1_ZHTobb_v2", "Legacy18V1_ZHTobb_ext", "Legacy18V1_ZHToTauTau",
"Legacy18V1_TTJets_TbarToSingleLep", "Legacy18V1_TTJets_TToSingleLep", "Legacy18V1_TTJets_DiLep",
"Legacy18V1_ttHToNonbb", "Legacy18V1_ggHToZZTo4L", "Legacy18V1_ggHToZZTo2L2Q", "Legacy18V1_ggHToWWToLNuQQ", "Legacy18V1_ggHToWWTo2L2Nu", "Legacy18V1_ggHToMuMu_v2", "Legacy18V1_ggHToMuMu_ext1", "Legacy18V1_ggHToBB", "Legacy18V1_ggHToGG", "Legacy18V1_VBFHToZZTo4L",
"Legacy18V1_VBFHToWWToLNuQQ", "Legacy18V1_VBFHToWWTo2L2Nu", "Legacy18V1_VBFHToMuMu", "Legacy18V1_VBFHToBB", "Legacy18V1_VBFHToGG",
]

samples2018MVA=[
"Legacy18V1_TTHnobb","Legacy18V1_TTTo2L","Legacy18V1_TTToSemiLep","Legacy18V1_TTToHad","Legacy18V1_ttW_Tune","Legacy18V1_ttZ_Tune","Legacy18V1_TTJets_mad","Legacy18V1_TTJets_amc",
# the following sample should be split into 2/3 for training , 1/3 for signal extraction based on nEvent % 3 == 0 or not
"Legacy18V1_THQ_ctcvcp","Legacy18V1_THW_ctcvcp",
]

(opt, args) = parser.parse_args()
sampleType = opt.sampleType
jec = opt.jec
year = opt.year
nlep = opt.nlep


SamplesAll = {
"2016":{"isDNN":samples2016MVA,"isHjtagger":samples2016MVA,"isSigExt":samples2016MC,"isData":samples2016Data},
"2017":{"isDNN":samples2017MVA,"isHjtagger":samples2017MVA,"isSigExt":samples2017MC,"isData":samples2017Data},
"2018":{"isDNN":samples2018MVA,"isHjtagger":samples2018MVA,"isSigExt":samples2018MC,"isData":samples2018Data},
}

def SetPars(YEAR, JEC, SampleType, NLEP):
    InvPostfix = invPostfix
    Analysis = analysis
    TriggerName = triggerName
    ConfigFile = configFile
    FileListDirectory = fileListDirectory
    sYear = str(YEAR)
    Analysis +=  sYear
    if SampleType == "isDNN":
        Analysis += "TrainDNN"
        Sample = SamplesAll[sYear][SampleType]
        InvPostfix += " -isTrainMVA"
        if JEC == "nominal" and NLEP==2:
            Analysis +=  "2L"
            TriggerName = "TTHLep_2L"
            ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.TrainMVA.config"
        else:
            print (" SampleType isDNN, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    elif SampleType == "isHjtagger":
        Analysis += "TrainHj"
        Sample = SamplesAll[sYear][SampleType]
        if JEC == "nominal" and NLEP==2:
            Analysis +=  "2L"
            TriggerName = "TTHLep_2L"
            ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.All.config"
        else:
            print (" SampleType isHjtagger, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    elif SampleType == "isSigExt":
        Analysis += "All"
        Sample = SamplesAll[sYear][SampleType]
        if JEC == "nominal":
            if NLEP==2:
                Analysis +=  "2L"
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.All.config"
            elif NLEP==3:
                Analysis +=  "3L"
                TriggerName = "TTHLep_3L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.TriLepton.All.config"
            elif NLEP==4:
                Analysis +=  "4L"
                TriggerName = "TTHLep_4L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.QuaLepton.All.config"
            else:
                print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        elif JEC in [ "JESUp", "JESDown", "JERUp", "JERDown"]:
            if NLEP==2:
                Analysis +=  "2L%s"%JEC
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton%s.All.config"%JEC
            else:
                print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        elif SampleType == "1bgeq4j":
            Analysis += "All"
            Sample = SamplesAll[sYear][SampleType]
            if NLEP==2:
                Analysis +=  "2L"
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.Multilepton.2lss_"+SampleType+".gencuts.config"
            elif NLEP==3:
                Analysis +=  "3L"
                TriggerName = "TTHLep_3L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.3l_"+SampleType+".gencuts.config"
            else:
                print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        else:
            print (" SampleType isSigExt, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    elif SampleType == "isData":
        InvPostfix = " -FakeRate -chargeMis"
        Analysis += "Data"
        Sample = SamplesAll[sYear][SampleType]
        FileListDirectory = "config/files/ttH_Legacy/SmallJobs/data/"
        if JEC == "nominal":
            if NLEP==2:
                Analysis +=  "2L"
                TriggerName = "TTHLep_2L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.DiLepton.All.config"
            elif NLEP==3:
                Analysis +=  "3L"
                TriggerName = "TTHLep_3L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.TriLepton.All.config"
            elif NLEP==4:
                Analysis +=  "4L"
                TriggerName = "TTHLep_4L"
                ConfigFile = "config/overall/ttHRunII/"+sYear+"/ttH.MultiLeptons.QuaLepton.All.config"
            else:
                print (" SampleType isData, skip JEC type %s with NLEP %i"%(JEC,NLEP))
                sys.exit()
        else:
            print (" SampleType isData, skip JEC type %s with NLEP %i"%(JEC,NLEP))
            sys.exit()
    else:
        print (" SampleType %s, skip "%SampleType)
        sys.exit()
    return Analysis, Sample, TriggerName, ConfigFile, InvPostfix, FileListDirectory


analysis, sample, triggerName, configFile, invPostfix, fileListDirectory =  SetPars(year, jec, sampleType, nlep)

#for the queue
workpath    = os.getcwd()+"/"+analysis +"/"
jobDir      = workpath+"/"+"Jobs"
smallerJobs = True
AnalyzerDir = workpath+"/"+"Analyzer"

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
        print >> subFile, frameworkDir+executable+" -config "+frameworkDir+configFile+" -inlist "+frameworkDir+fileListDirectory+sample+"_"+samplePost+".list -hfile "+workpath+"/"+sample+"/hists/"+sample+samplePost+"hists.root -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -SelectTrigger " + triggerName + invPostfix + mcPostfix + skimString
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
        inputFiles  = [f for f in os.listdir(frameworkDir+fileListDirectory) if sampleName==f[:f.rfind('_')]]
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
