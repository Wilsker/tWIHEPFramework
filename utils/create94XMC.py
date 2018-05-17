#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "OutTree_"

datasets = [
"TTHnobb", "ttH_powheg_ToNonbb", "TTWToLNu", "TTW_PSwgt_ToLNu", "TTZToLLNuNu_M10", "TTZToLL_M1to10", "TTWW", "DY_M10to50", "DY_M50", "DY_ext_M50", "WJets", "WWTo2L2Nu", "WZTo3LNu", "ZZTo4L", "ZZ_ext_To4L", "TT_PSwgt_To2L2Nu", "TTTo2L2Nu", "TT_PSwgt_ToSemiLep", "TTToSemiLep", "TT_PSwgt_ToHadron", "TTToHadron", "ST_tW_top", "ST_tW_antitop", "STt_top", "STt_antitop", "STs", "TTGJets", "tZq", "WW_DoubleScatter", "WW_DS_To2L2Nu", "WWW", "WWZ", "WZZ", "ZZZ", "TTTT_Tune"
]
datasetID = {
    "TTHnobb":100000, "ttH_powheg_ToNonbb":100001, "DY_M10to50":100002, "DY_M50":100003, "DY_ext_M50":100004, "ST_tW_antitop":100005, "ST_tW_top":100006, "STs":100007, "STt_antitop":100008, "STt_top":100009, "TTGJets":100010, "TTTT_Tune":100011, "TTTo2L2Nu":100012, "TTToHadron":100013, "TTToSemiLep":100014, "TTWToLNu":100015, "TTWW":100016, "TTW_PSwgt_ToLNu":100017, "TTZToLLNuNu_M10":100018, "TTZToLL_M1to10":100019, "TT_PSwgt_To2L2Nu":100020, "TT_PSwgt_ToHadron":100021, "TT_PSwgt_ToSemiLep":100022, "WJets":100023, "WWTo2L2Nu":100024, "WWW":100025, "WWZ":100026, "WW_DS_To2L2Nu":100027, "WW_DoubleScatter":100028, "WZTo3LNu":100029, "WZZ":100030, "ZZTo4L":100031, "ZZZ":100032, "ZZ_ext_To4L":100033, "tZq":100034 
}
nFilesDataset = {
"WW_DS_To2L2Nu":23, "TTTo2L2Nu":164, "TTZToLL_M1to10":17, "TTToHadron":762, "WW_DoubleScatter":35, "tZq":291, "ST_tW_top":183, "DY_M50":371, "WZZ":18, "DY_M10to50":508, "ZZZ":17, "WZTo3LNu":212, "WWTo2L2Nu":50, "TTHnobb":282, "STt_antitop":116, "TTZToLLNuNu_M10":198, "TTToSemiLep":742, "TTW_PSwgt_ToLNu":121, "ZZTo4L":204, "TTWW":11, "TTGJets":138, "ST_tW_antitop":155, "WJets":382, "TTWToLNu":108, "ttH_powheg_ToNonbb":218, "TTTT_Tune":29, "TT_PSwgt_To2L2Nu":1227, "ZZ_ext_To4L":1489, "TT_PSwgt_ToHadron":2492, "TT_PSwgt_ToSemiLep":2028, "DY_ext_M50":2746, "STt_top":186, "WWW":21, "WWZ":14, "STs":217
}
datasetDirs = {
"TTHnobb":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ttHJetToNonbb_M125_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/Fall17V1_TTHnobb/180505_043712/0000/"],
"ttH_powheg_ToNonbb":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/Fall17V1_ttH_powheg_ToNonbb/180515_080402/0000/"],
"TTWToLNu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Fall17V1_TTWToLNu/180504_071311/0000/"],
"TTW_PSwgt_ToLNu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8/Fall17V1_TTW_PSwgt_ToLNu/180504_071429/0000/"],
"TTZToLLNuNu_M10":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_TTZToLLNuNu_M10/180504_071553/0000/"],
"TTZToLL_M1to10":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_TTZToLL_M1to10/180504_071717/0000/"],
"TTWW":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTWW_TuneCP5_13TeV-madgraph-pythia8/Fall17V1_TTWW/180505_044015/0000/"],
"DY_M10to50":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V1_DY_M10to50/180504_072008/0000/"],
"DY_M50":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/Fall17V1_DY_M50/180504_072129/0000/"],
"DY_ext_M50":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/Fall17V1_DY_ext_M50/180504_072251/0000/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/Fall17V1_DY_ext_M50/180504_072251/0001/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/Fall17V1_DY_ext_M50/180504_072251/0002/"],
"WJets":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V1_WJets/180506_023229/0000/"],
"WWTo2L2Nu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/Fall17V1_WWTo2L2Nu/180504_072541/0000/"],
"WZTo3LNu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/Fall17V1_WZTo3LNu/180505_044234/0000/"],
"ZZTo4L":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ZZTo4L_13TeV_powheg_pythia8/Fall17V1_ZZTo4L/180504_072841/0000/"],
"ZZ_ext_To4L":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ZZTo4L_13TeV_powheg_pythia8/Fall17V1_ZZ_ext_To4L/180504_073009/0000/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ZZTo4L_13TeV_powheg_pythia8/Fall17V1_ZZ_ext_To4L/180504_073009/0001/"],
"TT_PSwgt_To2L2Nu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_To2L2Nu/180505_044345/0000/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_To2L2Nu/180505_044345/0001/"],
"TTTo2L2Nu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/Fall17V1_TTTo2L2Nu/180504_073253/0000/"],
"TT_PSwgt_ToSemiLep":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_ToSemiLep/180504_073416/0000/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_ToSemiLep/180504_073416/0001/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_ToSemiLep/180504_073416/0002/"],
"TTToSemiLep":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/Fall17V1_TTToSemiLep/180504_073535/0000/"],
"TT_PSwgt_ToHadron":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_ToHadron/180504_073656/0000/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_ToHadron/180504_073656/0001/","/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/Fall17V1_TT_PSwgt_ToHadron/180504_073656/0002/"],
"TTToHadron":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/Fall17V1_TTToHadron/180504_073816/0000/"],
"ST_tW_top":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Fall17V1_ST_tW_top/180504_073934/0000/"],
"ST_tW_antitop":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Fall17V1_ST_tW_antitop/180505_043144/0000/"],
"STt_top":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/Fall17V1_STt_top/180505_043256/0000/"],
"STt_antitop":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/Fall17V1_STt_antitop/180505_043406/0000/"],
"STs":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_STs/180504_074431/0000/"],
"TTGJets":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/Fall17V1_TTGJets/180505_044456/0000/"],
"tZq":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/Fall17V1_tZq/180504_074700/0000/"],
"WW_DoubleScatter":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WW_DoubleScattering_13TeV-pythia8_TuneCP5/Fall17V1_WW_DoubleScatter/180504_074816/0000/"],
"WW_DS_To2L2Nu":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WWTo2L2Nu_DoubleScattering_13TeV-herwigpp/Fall17V1_WW_DS_To2L2Nu/180504_074940/0000/"],
"WWW":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_WWW/180504_075055/0000/"],
"WWZ":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_WWZ/180504_075211/0000/"],
"WZZ":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_WZZ/180504_080748/0000/"],
"ZZZ":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_ZZZ/180505_044609/0000/"],
"TTTT_Tune":["/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/mc/TTTT_TuneCP5_13TeV-amcatnlo-pythia8/Fall17V1_TTTT_Tune/180504_081348/0000/"]
}
#datasetDirs = {"TTHnobb":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/FullMorV2_ttHnobb/170530_161519/0000/"],
#"TTWToLNuext2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/FullMorV2_amcTTWJetsToLNuext2/170531_182459/0000/"]
#}

import sys, math, mmap, subprocess

namesPerFile = float(raw_input("How many files to run over per job? "))
if namesPerFile == 0:
    print "You idiot, we can't divide by 0"
    sys.exit()
outputDirectory = raw_input("Output directory: ")

finishCopyScripts = raw_input("File for additional copies: ")
copyScript = 0
if finishCopyScripts:
    copyScript = file(finishCopyScripts,"w")
    print copyScript.write("#!/bin/bash\n")

for dataset in datasets:
    
    fileList = []
    for datasetDir in datasetDirs[dataset]:
        fileList += [os.path.join(datasetDir,f) for f in os.listdir(datasetDir) if ".root" in f]
    nJobs = int(math.ceil(len(fileList)/namesPerFile))
    print ("Dataset: {0}, ID: {1}. Number of jobs created = {2}".format(dataset,datasetID[dataset],nJobs))
    nFile = 0
    for i in range(nJobs):
        currentFile = open(outputDirectory + dataset + str(i) + ".list","w")
        currentFile.write("Name: " + dataset)
        currentFile.write("\nNumber: " + str(datasetID[dataset]) + "_1\n")
        for j in range(int(namesPerFile)):
            if nFile >= len(fileList): continue
            currentFile.write(fileList[nFile]+"\n")
            nFile+=1
        currentFile.close()
        
    continue

    nJobs = int(math.ceil(nFilesDataset[dataset]/namesPerFile))
    print ("Dataset: {0}, ID: {1}. Number of jobs created = {2}".format(dataset,datasetID[dataset],nJobs))
#    if os.path.exists("config/files/full80X/"+dataset+".list"): subprocess.call("rm config/files/full80X/"+dataset+".list",shell=True)
#    for dirName in datasetDirs[dataset]:
#        subprocess.call("\"ls\" "+dirName + "* >> config/files/full80X/"+dataset+".list",shell=True)
#    bigDatasetFile = open("config/files/full80X/"+dataset+".list")
#    s = mmap.mmap(bigDatasetFile.fileno(), 0, access=mmap.ACCESS_READ)
    for i in range(nJobs):
        currentFile = open(outputDirectory + dataset + str(i) + ".list","w")
        currentFile.write("Name: " + dataset)
        currentFile.write("\nNumber: " + str(datasetID[dataset]) + "_1\n")
        maxFiles = (i+1)*namesPerFile+1
        if nFilesDataset[dataset]+1 < maxFiles: maxFiles = nFilesDataset[dataset]+1
        for j in range(i*namesPerFile+1,maxFiles):
            line = treeName + str(j) + ".root"
            fileLocation = ""
            fileSize = 0.
            for dataDir in datasetDirs[dataset]:
                if os.path.exists(dataDir+treeName+str(j)+".root"):
                    statinfo = os.stat(dataDir+treeName+str(j)+".root")
                    if statinfo.st_size > fileSize:
                        fileLocation = dataDir+treeName+str(j)+".root"
                        fileSize = statinfo.st_size
            if not fileLocation == "" and fileSize > 0:
                currentFile.write(fileLocation+"\n")
            elif copyScript: 
                fileNameForCopy = dataDir.split("tWlJetSamples/moriond17/")[-1]
                if "mc/" in fileNameForCopy: fileNameForCopy = "mcMoriond17/" + fileNameForCopy.split("mc/")[-1]
                else: fileNameForCopy = "reRecoData/"+fileNameForCopy.split("data/")[-1]
                copyScript.write("srmcp --debug srm://srm.ihep.ac.cn/pnfs/ihep.ac.cn/data/cms/store/user/leggat/tWSamples/"+ fileNameForCopy + treeName+str(j) +".root file:///" + dataDir+"\n")
                print "Couldn't find file " + str(j)
#            if s.find(line) != -1:
#                currentFile.write(datasetDirs[dataset] + line + "")
#                print line
        

while False:
    datasetName = raw_input("Dataset name: ")
    if datasetName == "end" or datasetName == "stop": break
    datasetNum = raw_input("Corresponds to the number: ")
    totalDatasetFiles = float(raw_input("Total number of files in this dataset: "))
    nJobs = int(math.ceil(totalDatasetFiles/namesPerFile))
    print "That means we will make " + str(nJobs) + " jobs"
    remoteDir = raw_input("Remote directory: ")
    bigDatasetFile = open("config/files/full/"+datasetName+".list")
    s = mmap.mmap(bigDatasetFile.fileno(), 0, access=mmap.ACCESS_READ)
    for i in range(nJobs):
        currentFile = open(outputDirectory + datasetName + str(i) + ".list","w")
        currentFile.write("Name: "+datasetName)
        currentFile.write("\nNumber: " + datasetNum + "_1\n")
        maxFiles = (i+1)*namesPerFile+1
        if totalDatasetFiles+1 < maxFiles: maxFiles = totalDatasetFiles+1
        for j in range(i*namesPerFile+1,maxFiles):
            line = treeName + str(j) + ".root"
            if s.find(line) != -1:
                currentFile.write(remoteDir + line + "\n")
#                print line
#            currentFile.write(remoteDir + "
        
        
    
print "Thank you for using the create jobs program. Have a nice day"
