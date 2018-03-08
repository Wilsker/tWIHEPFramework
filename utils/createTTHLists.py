#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "OutTree_"

#datasets = ["TTHnobb","TTWToLNuext2","TTWToLNuext1","TTZToLLNuNu","TTZToLL_M1to10","TTJets_sinLepTbar_v1","TTJets_sinLepTbar_ext1","TTJets_sinLepT_v1","TTJets_sinLepT_ext1","TTJets_diLep_v1","TTJets_diLep_ext1","TTGToJets_ext1","WGToLNuG_ext2","TGJets_v1","WGToLNuG_ext1","ZGTo2LG","TGJets_ext1","WpWpJJ","WW_DS_To2L2Nu","WWW_4F","WWZ","WZZ","ZZZ","tZq","TTTT","tWll","amcWJets","WZTo3LNu","WWTo2L2Nu","ZZTo4L"]
datasets = ["TTGToJets_ext1","WW_DS_To2L2Nu","WGToLNuG_ext1"]
#datasets = ["tW_top_nfh","tW_antitop_nfh","SingMuH"]
#datasets = ["SingEleB","SingEleC","SingEleD","SingEleF","SingEleG","SingEleH"]
datasetID = {"TTHnobb":100000,"TTWToLNuext2":100001,"TTWToLNuext1":100002,"TTZToLLNuNu":100003,"TTZToLL_M1to10":100004,"TTJets_sinLepTbar_v1":100005,"TTJets_sinLepTbar_ext1":100006,"TTJets_sinLepT_v1":100007,"TTJets_sinLepT_ext1":100008,"TTJets_diLep_v1":100009,"TTJets_diLep_ext1":100010,"TTGToJets_ext1":100011,"WGToLNuG_ext2":100012,"TGJets_v1":100013,"WGToLNuG_ext1":100014,"ZGTo2LG":100015,"TGJets_ext1":100016,"WpWpJJ":100017,"WW_DS_To2L2Nu":100018,"WWW_4F":100019,"WWZ":100020,"WZZ":100021,"ZZZ":100022,"tZq":100023,"TTTT":100024,"tWll":100025,"amcWJets":100026,"WZTo3LNu":100027,"WWTo2L2Nu":100028,"ZZTo4L":100029}
#datasetID = {"TTHnobb":100000,"TTWToLNuext2":100001}
nFilesDataset = {"TTHnobb":107,"TTWToLNuext2":39,"TTWToLNuext1":28,"TTZToLLNuNu":30,"TTZToLL_M1to10":14,"TTJets_sinLepTbar_v1":186,"TTJets_sinLepTbar_ext1":450,"TTJets_sinLepT_v1":133,"TTJets_sinLepT_ext1":478,"TTJets_diLep_v1":60,"TTJets_diLep_ext1":252,"TTGToJets_ext1":239,"WGToLNuG_ext2":124,"TGJets_v1":17,"WGToLNuG_ext1":144,"ZGTo2LG":210,"TGJets_ext1":37,"WpWpJJ":4,"WW_DS_To2L2Nu":13,"WWW_4F":4,"WWZ":4,"WZZ":5,"ZZZ":4,"tZq":303,"TTTT":18,"tWll":1,"amcWJets":298,"WZTo3LNu":39,"WWTo2L2Nu":24,"ZZTo4L":96}
#nFilesDataset = {"TTHnobb":107,"TTWToLNuext2":39}
datasetDirs = {"TTHnobb":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8/FullMorV2_ttHnobb/170530_161519/0000/"],
"TTWToLNuext2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/FullMorV2_amcTTWJetsToLNuext2/170531_182459/0000/"],
"TTWToLNuext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/FullMorV2_amcTTWJetsToLNuext1/170531_182712/0000/"],
"TTZToLLNuNu":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/FullMorV2_amcTTZToLLNuNu_M-10_ext1/170531_182920/0000/"],
"TTZToLL_M1to10":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTZToLL_M1to10/170531_183129/0000/"],
"TTJets_sinLepTbar_v1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTJets_sinLepTbar/170531_190717/0000/"],
"TTJets_sinLepTbar_ext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTJets_sinLepTbar_ext1/170531_190925/0000/"],
"TTJets_sinLepT_v1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTJets_sinLepT/170531_191441/0000/"],
"TTJets_sinLepT_ext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTJets_sinLepT_ext1/170531_191648/0000/"],
"TTJets_diLep_v1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTJets_diLep/170531_191854/0000/"],
"TTJets_diLep_ext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/FullMorV2_TTJets_diLep_ext1/170531_192103/0000/"],
"TTGToJets_ext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/FullMorV2_TTGJets_ext1/170621_150600/0000/"],
"WGToLNuG_ext2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/FullMorV2_WGToLNuG_ext2/170621_150118/0000/"],
"TGJets_v1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/FullMorV2_TGJets/170531_184103/0000/"],
"WGToLNuG_ext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/FullMorV2_WGToLNuG_ext1/170614_105550/0000/"],
"ZGTo2LG":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/FullMorV2_ZGTo2LG_ext1/170614_105812/0000/"],
"TGJets_ext1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/FullMorV2_TGJets_ext1/170614_110340/0000/"],
"WpWpJJ":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WpWpJJ_EWK-QCD_TuneCUETP8M1_13TeV-madgraph-pythia8/FullMorV2_WpWpJJ_EWK-QCD/170614_110838/0000/"],
"WW_DS_To2L2Nu":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WWTo2L2Nu_DoubleScattering_13TeV-pythia8/FullMorV2_WWTo2L2Nu_DS/170614_111109/0000/"],
"WWW_4F":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8/FullMorV2_WWW_4F/170614_111337/0000/"],
"WWZ":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/FullMorV2_WWZ/170614_111630/0000/"],
"WZZ":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/FullMorV2_WZZ/170614_111852/0000/"],
"ZZZ":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/FullMorV2_ZZZ/170614_112130/0000/"],
"tZq":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/tZq_ll_4f_13TeV-amcatnlo-pythia8/FullMorV2_tZq_ext1/170614_112447/0000/"],
"TTTT":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/FullMorV2_TTTT/170614_112737/0000/"],
"tWll":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ST_tWll_5f_LO_13TeV-MadGraph-pythia8/FullMorV2_tWll/170614_112953/0000/"],
"amcWJets":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/FullMorV2_amcWJets/170614_113235/0000/"],
"WZTo3LNu":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/FullMorV2_WZTo3LNu/170614_113533/0000/"],
"WWTo2L2Nu":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/WWTo2L2Nu_13TeV-powheg/FullMorV2_WWTo2L2Nu/170614_113820/0000/"],
"ZZTo4L":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/mc/ZZTo4L_13TeV_powheg_pythia8/FullMorV2_ZZTo4L/170614_114133/0000/"]
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
