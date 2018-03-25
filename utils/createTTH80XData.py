#A short script that takes input from the user to create a set of file lists to run on condor. the inputs are:
# Number of files per job - how many files to put in each file list
# Name of dataset
# Total number of files in dataset
# Dataset's designated number according to the configuration file in configs

import sys,os

treeName = "OutTree_"

datasets = [
"DEleGmRecoverB1","DEleGmRecoverC1","DEleGmRecoverD1","DEleGmRecoverE1","DEleGmRecoverF1","DEleGmRecoverF2","DEleGmRecoverG1","DEleGmRecoverH1","DEleGmRecoverH2",
"MuEleGmRecoverB1","MuEleGmRecoverC1","MuEleGmRecoverD1","MuEleGmRecoverE1","MuEleGmRecoverF1","MuEleGmRecoverF2","MuEleGmRecoverG1","MuEleGmRecoverH1","MuEleGmRecoverH2",
"DMuRecoverB1","DMuRecoverC1","DMuRecoverD1","DMuRecoverE1","DMuRecoverF1","DMuRecoverF2","DMuRecoverG1","DMuRecoverH1","DMuRecoverH2",
"SEleRecoverB1","SEleRecoverC1","SEleRecoverD1","SEleRecoverE1","SEleRecoverF1","SEleRecoverF2","SEleRecoverG1","SEleRecoverH1",
"SMuRecoverB1","SMuRecoverC1","SMuRecoverD1","SMuRecoverE1","SMuRecoverF1","SMuRecoverF2","SMuRecoverG1","SMuRecoverH1","SMuRecoverH2",
"DEleGmB1","DEleGmC1","DEleGmD1","DEleGmE1","DEleGmF1","DEleGmF2","DEleGmG1","DEleGmH1","DEleGmH2",
"MuEleGmB1","MuEleGmC1","MuEleGmD1","MuEleGmE1","MuEleGmF1","MuEleGmF2","MuEleGmG1","MuEleGmH1","MuEleGmH2",
"DMuB1","DMuC1","DMuD1","DMuE1","DMuF1","DMuF2","DMuG1","DMuH1","DMuH2",
"SEleB1","SEleC1","SEleD1","SEleE1","SEleF1","SEleF2","SEleG1","SEleH1","SEleH2",
"SMuB1","SMuC1","SMuD1","SMuE1","SMuF1","SMuF2","SMuG1","SMuH1","SMuH2"
]

datasetID = {
"DEleGmRecoverB1":204001,"DEleGmRecoverC1":204001,"DEleGmRecoverD1":204001,"DEleGmRecoverE1":204001,"DEleGmRecoverF1":204001,"DEleGmRecoverF2":204001,"DEleGmRecoverG1":214001,"DEleGmRecoverH1":214001,"DEleGmRecoverH2":214001,
"MuEleGmRecoverB1":205001,"MuEleGmRecoverC1":205001,"MuEleGmRecoverD1":205001,"MuEleGmRecoverE1":205001,"MuEleGmRecoverF1":205001,"MuEleGmRecoverF2":205001,"MuEleGmRecoverG1":215001,"MuEleGmRecoverH1":215001,"MuEleGmRecoverH2":215001,
"DMuRecoverB1":203001,"DMuRecoverC1":203001,"DMuRecoverD1":203001,"DMuRecoverE1":203001,"DMuRecoverF1":203001,"DMuRecoverF2":203001,"DMuRecoverG1":213001,"DMuRecoverH1":213001,"DMuRecoverH2":213001,
"SEleRecoverB1":201001,"SEleRecoverC1":201001,"SEleRecoverD1":201001,"SEleRecoverE1":201001,"SEleRecoverF1":201001,"SEleRecoverF2":201001,"SEleRecoverG1":211001,"SEleRecoverH1":211001,
"SMuRecoverB1":202001,"SMuRecoverC1":202001,"SMuRecoverD1":202001,"SMuRecoverE1":202001,"SMuRecoverF1":202001,"SMuRecoverF2":202001,"SMuRecoverG1":212001,"SMuRecoverH1":212001,"SMuRecoverH2":212001,
"DEleGmB1":204000,"DEleGmC1":204000,"DEleGmD1":204000,"DEleGmE1":204000,"DEleGmF1":204000,"DEleGmF2":204000,"DEleGmG1":214000,"DEleGmH1":214000,"DEleGmH2":214000,
"MuEleGmB1":205000,"MuEleGmC1":205000,"MuEleGmD1":205000,"MuEleGmE1":205000,"MuEleGmF1":205000,"MuEleGmF2":205000,"MuEleGmG1":215000,"MuEleGmH1":215000,"MuEleGmH2":215000,
"DMuB1":203000,"DMuC1":203000,"DMuD1":203000,"DMuE1":203000,"DMuF1":203000,"DMuF2":203000,"DMuG1":213000,"DMuH1":213000,"DMuH2":213000,
"SEleB1":201000,"SEleC1":201000,"SEleD1":201000,"SEleE1":201000,"SEleF1":201000,"SEleF2":201000,"SEleG1":211000,"SEleH1":211000,"SEleH2":211000,
"SMuB1":202000,"SMuC1":202000,"SMuD1":202000,"SMuE1":202000,"SMuF1":202000,"SMuF2":202000,"SMuG1":212000,"SMuH1":212000,"SMuH2":212000
    }

nFilesDataset = {
"DEleGmRecoverB1":461,"DEleGmRecoverC1":137,"DEleGmRecoverD1":206,"DEleGmRecoverE1":91,"DEleGmRecoverF1":63,"DEleGmRecoverF2":1,"DEleGmRecoverG1":302,"DEleGmRecoverH1":380,"DEleGmRecoverH2":1,
"MuEleGmRecoverB1":314,"MuEleGmRecoverC1":167,"MuEleGmRecoverD1":153,"MuEleGmRecoverE1":230,"MuEleGmRecoverF1":147,"MuEleGmRecoverF2":26,"MuEleGmRecoverG1":262,"MuEleGmRecoverH1":353,"MuEleGmRecoverH2":5,
"DMuRecoverB1":575,"DMuRecoverC1":116,"DMuRecoverD1":129,"DMuRecoverE1":197,"DMuRecoverF1":121,"DMuRecoverF2":27,"DMuRecoverG1":376,"DMuRecoverH1":224,"DMuRecoverH2":2,
"SEleRecoverB1":289,"SEleRecoverC1":120,"SEleRecoverD1":222,"SEleRecoverE1":195,"SEleRecoverF1":160,"SEleRecoverF2":9,"SEleRecoverG1":383,"SEleRecoverH1":245,
"SMuRecoverB1":293,"SMuRecoverC1":136,"SMuRecoverD1":246,"SMuRecoverE1":197,"SMuRecoverF1":121,"SMuRecoverF2":14,"SMuRecoverG1":290,"SMuRecoverH1":353,"SMuRecoverH2":7,
"DEleGmB1":1274,"DEleGmC1":435,"DEleGmD1":756,"DEleGmE1":732,"DEleGmF1":460,"DEleGmF2":80,"DEleGmG1":1097,"DEleGmH1":1137,"DEleGmH2":40,
"MuEleGmB1":1440,"MuEleGmC1":406,"MuEleGmD1":813,"MuEleGmE1":588,"MuEleGmF1":371,"MuEleGmF2":54,"MuEleGmG1":1160,"MuEleGmH1":1176,"MuEleGmH2":36,
"DMuB1":1154,"DMuC1":461,"DMuD1":841,"DMuE1":620,"DMuF1":399,"DMuF2":54,"DMuG1":1033,"DMuH1":1310,"DMuH2":36,
"SEleB1":1458,"SEleC1":453,"SEleD1":745,"SEleE1":617,"SEleF1":360,"SEleF2":71,"SEleG1":1029,"SEleH1":1282,"SEleH2":41,
"SMuB1":1450,"SMuC1":440,"SMuD1":724,"SMuE1":626,"SMuF1":399,"SMuF2":68,"SMuG1":1122,"SMuH1":1168,"SMuH2":33
    }

datasetDirs = {
"SEleB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockB1/170531_111453/0000/"],#1758
#"SEleB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockB1/170531_111453/0001/"],#1758
"SEleC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockC1/170531_112614/0000/"],#580
"SEleD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockD1/170531_112857/0000/"],#972
"SEleE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockE1/170531_113137/0000/"],#826
"SEleF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockF1/170531_113418/0000/"],
"SEleF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockF2/170531_113728/0000/"],
"SEleG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockG1/170531_114004/0000/"],
#"SEleG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockG1/170531_114004/0001/"],
"SEleH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockH1/170531_114244/0000/"],
#"SEleH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockH1/170531_114244/0001/"],
"SEleH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockH2/170530_164040/0000/"],#41

"SMuB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockB1/170531_114536/0000/"],
#"SMuB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockB1/170531_114536/0001/"],
"SMuC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockC1/170531_114815/0000/"],
"SMuD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockD1/170531_115112/0000/"],
"SMuE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockE1/170531_115354/0000/"],
"SMuF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockF1/170531_115635/0000/"],
"SMuF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockF2/170531_115917/0000/"],
"SMuG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockG1/170531_120200/0000/"],
#"SMuG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockG1/170531_120200/0001/"],
"SMuH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockH1/170531_120434/0000/"],
#"SMuH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockH1/170531_120434/0001/"],
"SMuH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockH2/170531_120710/0000/"],

"DEleGmB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockB1/170531_120945/0000/"],
#"DEleGmB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockB1/170531_120945/0001/"],
"DEleGmC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockC1/170531_121222/0000/"],
"DEleGmD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockD1/170531_121509/0000/"],
"DEleGmE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockE1/170531_121746/0000/"],
"DEleGmF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockF1/170531_122029/0000/"],
"DEleGmF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockF2/170531_122307/0000/"],
"DEleGmG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockG1/170531_122559/0000/"],
#"DEleGmG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockG1/170531_122559/0001/"],
"DEleGmH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockH1/170531_122837/0000/"],
#"DEleGmH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockH1/170531_122837/0001/"],
"DEleGmH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockH2/170531_123117/0000/"],

############### There is a mis assign in multicrab_DATA between DoubleMuon and MuonEG #############
"DMuB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockB1/170531_125358/0000/"],
#"DMuB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockB1/170531_125358/0001/"],
"DMuC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockC1/170531_125627/0000/"],
"DMuD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockD1/170531_125857/0000/"],
"DMuE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockE1/170531_130126/0000/"],
"DMuF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockF1/170531_130344/0000/"],
"DMuF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockF2/170531_130606/0000/"],
"DMuG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockG1/170531_130824/0000/"],
#"DMuG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockG1/170531_130824/0001/"],
"DMuH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockH1/170531_131041/0000/"],
#"DMuH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockH1/170531_131041/0001/"],
"DMuH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockH2/170531_131302/0000/"],

"MuEleGmB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockB1/170531_123341/0000/"],
#"MuEleGmB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockB1/170531_123341/0001/"],
"MuEleGmC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockC1/170531_123555/0000/"],
"MuEleGmD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockD1/170531_123810/0000/"],
"MuEleGmE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockE1/170531_124023/0000/"],
"MuEleGmF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockF1/170531_124239/0000/"],
"MuEleGmF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockF2/170531_124449/0000/"],
"MuEleGmG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockG1/170531_124700/0000/"],
#"MuEleGmG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockG1/170531_124700/0001/"],
"MuEleGmH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockH1/170531_124911/0000/"],
#"MuEleGmH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockH1/170531_124911/0001/"],
"MuEleGmH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockH2/170531_125134/0000/"],

### Data Recover ####
"SEleRecoverB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockB1_recover/170607_125832/0000/"], #290
"SEleRecoverC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockC1_recover/170607_130129/0000/"], #120
"SEleRecoverD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockD1_recover/170607_130415/0000/"], #222
"SEleRecoverE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockE1_recover/170607_130651/0000/"], #195
"SEleRecoverF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockF1_recover/170607_130939/0000/"], #160
"SEleRecoverF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockF2_recover/170607_131218/0000/"], #9
"SEleRecoverG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockG1_recover/170607_131452/0000/"], #383
"SEleRecoverH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleElectron/crab_FullMorV2_SEleBlockH1_recover/170607_131714/0000/"], #245

"SMuRecoverB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockB1_recover/170607_131929/0000/"], 
"SMuRecoverC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockC1_recover/170607_132148/0000/"],
"SMuRecoverD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockD1_recover/170607_132411/0000/"],
"SMuRecoverE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockE1_recover/170607_132644/0000/"],
"SMuRecoverF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockF1_recover/170607_132915/0000/"],
"SMuRecoverF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockF2_recover/170607_133134/0000/"],
"SMuRecoverG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockG1_recover/170607_133354/0000/"],
"SMuRecoverH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockH1_recover/170607_133623/0000/"],
"SMuRecoverH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/SingleMuon/crab_FullMorV2_SMuBlockH2_recover/170607_133844/0000/"],

"DEleGmRecoverB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockB1_recover/170607_134111/0000/"],
"DEleGmRecoverC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockC1_recover/170607_134332/0000/"],
"DEleGmRecoverD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockD1_recover/170607_134624/0000/"],
"DEleGmRecoverE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockE1_recover/170607_134958/0000/"],
"DEleGmRecoverF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockF1_recover/170607_182838/0000/"],
"DEleGmRecoverF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockF2_recover/170607_140245/0000/"],
"DEleGmRecoverG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockG1_recover/170607_140855/0000/"],
"DEleGmRecoverH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockH1_recover/170607_141422/0000/"],
"DEleGmRecoverH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleEG/crab_FullMorV2_DblEGBlockH2_recover/170607_142119/0000/"],

"DMuRecoverB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockB1_recover/170607_145709/0000/"],
"DMuRecoverC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockC1_recover/170607_145932/0000/"],
"DMuRecoverD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockD1_recover/170607_150245/0000/"],
"DMuRecoverE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockE1_recover/170607_150602/0000/"],
"DMuRecoverF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockF1_recover/170607_150850/0000/"],
"DMuRecoverF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockF2_recover/170607_151148/0000/"],
"DMuRecoverG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockG1_recover/170607_151446/0000/"],
"DMuRecoverH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockH1_recover/170607_151806/0000/"],
"DMuRecoverH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/DoubleMuon/crab_FullMorV2_MuEGBlockH2_recover/170607_152113/0000/"],

"MuEleGmRecoverB1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockB1_recover/170607_142447/0000/"],
"MuEleGmRecoverC1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockC1_recover/170607_143737/0000/"],
"MuEleGmRecoverD1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockD1_recover/170607_144007/0000/"],
"MuEleGmRecoverE1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockE1_recover/170607_144236/0000/"],
"MuEleGmRecoverF1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockF1_recover/170607_144503/0000/"],
"MuEleGmRecoverF2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockF2_recover/170607_144730/0000/"],
"MuEleGmRecoverG1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockG1_recover/170607_144953/0000/"],
"MuEleGmRecoverH1":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockH1_recover/170607_145205/0000/"],
"MuEleGmRecoverH2":["/publicfs/cms/data/TopQuark/cms13TeV/FullMorV2/data/MuonEG/crab_FullMorV2_DblMuBlockH2_recover/170607_145442/0000/"]

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
