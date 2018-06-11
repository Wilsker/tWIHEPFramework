#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "RDOut_"

DirOfData = "/publicfs/cms/data/TopQuark/cms13TeV/Fall2017_V1/data/"

datasets = [
"SEleBlockB", "SEleBlockC", "SEleBlockD", "SEleBlockE", "SEleBlockF", "SMuBlockB", "SMuBlockC", "SMuBlockD", "SMuBlockE", "SMuBlockF", "DblEGBlockB", "DblEGBlockC", "DblEGBlockD", "DblEGBlockE", "DblEGBlockF", "DblMuBlockB", "DblMuBlockC", "DblMuBlockD", "DblMuBlockE", "DblMuBlockF", "MuEGBlockB", "MuEGBlockC", "MuEGBlockD", "MuEGBlockE", "MuEGBlockF",
]

datasetID = {
"SEleBlockB":201000, "SEleBlockC":201000, "SEleBlockD":201000, "SEleBlockE":201000, "SEleBlockF":201001, "SMuBlockB":202000, "SMuBlockC":202000, "SMuBlockD":202000, "SMuBlockE":202000, "SMuBlockF":202001, "DblMuBlockB":203000, "DblMuBlockC":203000, "DblMuBlockD":203000, "DblMuBlockE":203000, "DblMuBlockF":203001, "DblEGBlockB":204000, "DblEGBlockC":204000, "DblEGBlockD":204000, "DblEGBlockE":204000, "DblEGBlockF":204001, "MuEGBlockB":205000, "MuEGBlockC":205000, "MuEGBlockD":205000, "MuEGBlockE":205000, "MuEGBlockF":205001,
    }

nFilesDataset = {
"DblMuBlockB":807, "SEleBlockF":1949, "MuEGBlockF":1950, "DblMuBlockD":902, "DblEGBlockD":903, "MuEGBlockC":1727, "MuEGBlockB":807, "DblEGBlockC":1727, "MuEGBlockE":1428, "DblMuBlockE":1428, "SMuBlockB":808, "SMuBlockE":1429, "SEleBlockB":808, "DblEGBlockE":1428, "SEleBlockD":902, "SMuBlockF":1950, "SEleBlockC":1725, "SEleBlockE":1428, "DblMuBlockC":1727, "MuEGBlockD":902, "DblEGBlockF":1950, "SMuBlockD":902, "SMuBlockC":1729, "DblEGBlockB":807, "DblMuBlockF":1950,
    }

datasetDirs = {
#'SignleEle'
"SEleBlockB":['SingleElectron/crab_Fall17V1_SEleBlockB/180508_154036/0000/'],
"SEleBlockC":[ 'SingleElectron/crab_Fall17V1_SEleBlockC/180508_154125/0000/','SingleElectron/crab_Fall17V1_SEleBlockC/180508_154125/0001/'],
"SEleBlockD":[ 'SingleElectron/crab_Fall17V1_SEleBlockD/180508_154212/0000/'],
"SEleBlockE":[ 'SingleElectron/crab_Fall17V1_SEleBlockE/180508_153846/0000/','SingleElectron/crab_Fall17V1_SEleBlockE/180508_153846/0001/'],
"SEleBlockF":['SingleElectron/crab_Fall17V2_SEleBlockF/180525_064028/0000/','SingleElectron/crab_Fall17V2_SEleBlockF/180525_064028/0001/'],
#'SingleMuon'
"SMuBlockB":[ 'SingleMuon/crab_Fall17V1_SMuBlockB/180508_154353/0000/'],
"SMuBlockC":[ 'SingleMuon/crab_Fall17V1_SMuBlockC/180508_154442/0000/','SingleMuon/crab_Fall17V1_SMuBlockC/180508_154442/0001/'],
"SMuBlockD":[ 'SingleMuon/crab_Fall17V1_SMuBlockD/180508_154529/0000/'],
"SMuBlockE":[ 'SingleMuon/crab_Fall17V1_SMuBlockE/180508_154618/0000/','SingleMuon/crab_Fall17V1_SMuBlockE/180508_154618/0001/'],
"SMuBlockF":['SingleMuon/crab_Fall17V2_SMuBlockF/180525_064111/0000/','SingleMuon/crab_Fall17V2_SMuBlockF/180525_064111/0001/'],
#'DoubleMuon'
"DblMuBlockB":[ 'DoubleMuon/crab_Fall17V1_DblMuBlockB/180509_090626/0000/'],
"DblMuBlockC":[ 'DoubleMuon/crab_Fall17V1_DblMuBlockC/180509_090705/0000/','DoubleMuon/crab_Fall17V1_DblMuBlockC/180509_090705/0001/'],
"DblMuBlockD":[ 'DoubleMuon/crab_Fall17V1_DblMuBlockD/180509_090748/0000/'],
"DblMuBlockE":[ 'DoubleMuon/crab_Fall17V1_DblMuBlockE/180509_090832/0000/','DoubleMuon/crab_Fall17V1_DblMuBlockE/180509_090832/0001/'],
"DblMuBlockF":[ 'DoubleMuon/crab_Fall17V2_DblMuBlockF/180525_064241/0000/','DoubleMuon/crab_Fall17V2_DblMuBlockF/180525_064241/0001/'],
#'DoubleEG'
"DblEGBlockB":[ 'DoubleEG/crab_Fall17V1_DblEGBlockB/180509_090303/0000/'],
"DblEGBlockC":[ 'DoubleEG/crab_Fall17V1_DblEGBlockC/180509_090343/0000/','DoubleEG/crab_Fall17V1_DblEGBlockC/180509_090343/0001/'],
"DblEGBlockD":[ 'DoubleEG/crab_Fall17V1_DblEGBlockD/180509_090423/0000/'],
"DblEGBlockE":[ 'DoubleEG/crab_Fall17V1_DblEGBlockE/180509_090504/0000/','DoubleEG/crab_Fall17V1_DblEGBlockE/180509_090504/0001/'],
"DblEGBlockF":['DoubleEG/crab_Fall17V2_DblEGBlockF/180525_064157/0000/','DoubleEG/crab_Fall17V2_DblEGBlockF/180525_064157/0001/'],
#'MuonEG'
"MuEGBlockB":[ 'MuonEG/crab_Fall17V1_MuEGBlockB/180509_091002/0000/'],
"MuEGBlockC":[ 'MuonEG/crab_Fall17V1_MuEGBlockC/180509_091043/0000/','MuonEG/crab_Fall17V1_MuEGBlockC/180509_091043/0001/'],
"MuEGBlockD":[ 'MuonEG/crab_Fall17V1_MuEGBlockD/180509_091123/0000/'],
"MuEGBlockE":[ 'MuonEG/crab_Fall17V1_MuEGBlockE/180509_091206/0000/','MuonEG/crab_Fall17V1_MuEGBlockE/180509_091206/0001/'],
"MuEGBlockF":['MuonEG/crab_Fall17V2_MuEGBlockF/180525_064329/0000/','MuonEG/crab_Fall17V2_MuEGBlockF/180525_064329/0001/'],
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
        dataDir = DirOfData+datasetDir
        fileList += [os.path.join(dataDir,f) for f in os.listdir(dataDir) if ".root" in f]
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
