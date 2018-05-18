import os
import re
import sys
import commands
import subprocess

#########################
############### Information provided by user
#################################
# Path you run this script
workpath = "/publicfs/cms/user/libh/Test/Rootplizer/analyzer"
#Specify needed variables
#  Type   Reading  Saving  Example
#  CaseA   Yes      Yes     Jet_pt: you want to save it and need also to read it (using SetBranchStatus+CopyEntries would require more processing time) 
#  CaseB   Yes      No      Jet_muonEnergyFraction: you want to read it to define jet ID, but may not want to save it  
#  CaseC   No       Yes     Jet_LooseID: you can not read it from ntuplas if there is not, but you want to save in rootplas 

# Variable Case
#Case = "CaseA"
#Case = "CaseB"
#Case = "CaseC"
Case = "CaseD"
# Variable Definition

rObject = "double"
wObject = "Lepton"

VariableType  = "Double_t"
VariableNames = [
# CaseA Variables
#"pt","eta","phi","energy",
#"charge",
#"IP3Dsig","miniIsoRel","pdgId",
#"gsfTrack_dxy_pv","gsfTrack_dz_pv",


#"jetptratio","jetcsv","lepjetchtrks","miniIsoCh","miniIsoPUsub","ptrel",
#"jetdr","jetpt",

#"px","py","pz",
#"gen_pt","gen_eta","gen_phi","gen_en","gen_pdgId",
#"genMother_pt","genMother_eta","genMother_phi","genMother_en",
#"genMother_pdgId",
#"genGrandMother_pt","genGrandMother_eta","genGrandMother_phi","genGrandMother_en",
#"genGrandMother_pdgId",
#"gen_isPromptFinalState","gen_isDirectPromptTauDecayProductFinalState",
#"mcPromptFS","mcMatchId","mcPromptGamma"

# Electron only
#"SCeta","expectedMissingInnerHits","full5x5_sigmaIetaIeta","hOverE","dEtaIn","dPhiIn","ooEmooP","mvaValue_HZZ", 
#"isGsfCtfScPixChargeConsistent","isGsfScPixChargeConsistent",

#"isGlobal","chi2LocalPosition","trkKink","validFraction","segmentCompatibility","pTErrOVpT_it", # Muon only

#"BDT","conept",
#"isLooseBdisc","isMediumBdisc","isTightBdisc",
#"qg","lepdrmax","lepdrmin"

#Taus
#"dz","dxy","isLoose","isMedium","decayModeFinding"
#"packedLeadTauCand_dz","packedLeadTauCand_dxy","byLooseIsolationMVArun2v1DBdR03oldDMwLT","decayModeFinding"
#"byMediumIsolationMVArun2v1DBdR03oldDMwLT",

#Jets
#"Uncorr_pt",
#"pfCombinedInclusiveSecondaryVertexV2BJetTags","pfCombinedMVAV2BJetTags",
#"px","py","pz","mass",
#"qg","axis2","ptD","mult",
#"partonFlavour","hadronFlavour",
#"genpt","geneta","genphi","genenergy",
#"BDT","lepdrmin","lepdrmax",
#"isToptag"

#"JesSF","JesSFup","JesSFdown","JerSF","JerSFup","JerSFdown",
#"neutralHadEnergyFraction","neutralEmEnergyFraction","chargedMultiplicity","numberOfConstituents","chargedHadronEnergyFraction", "chargedEmEnergyFraction",
#"btag_sf",
#"btag_jesup","btag_jesdown",
#"btag_hfup","btag_hfdown",
#"btag_hfstat1up","btag_hfstat1down",
#"btag_hfstat2up","btag_hfstat2down",
#"btag_lfup","btag_lfdown",
#"btag_lfstat1up","btag_lfstat1down",
#"btag_lfstat2up","btag_lfstat2down",
#"btag_cerr1up","btag_cerr1down",
#"btag_cerr2up","btag_cerr2down",

#BoostedJet
#"tau1","tau2","tau3",
#"softdrop_mass","pruned_mass",
#"SDsubjet1_pt","SDsubjet1_eta","SDsubjet1_phi","SDsubjet1_energy","SDsubjet1_pfCSV2Bdisc",
#"SDsubjet2_pt","SDsubjet2_eta","SDsubjet2_phi","SDsubjet2_energy","SDsubjet2_pfCSV2Bdisc",
#"tau21","tau32",
#"matchW_pt","matchW_eta","matchW_phi","matchW_energy","matchW_mass","matchW_mother_pdgId",
#Case B

# Case C

#"cut",

#"BDT","isMedium_ST","corrpt","FR","CF",
#"passConversionVeto","passTightCharge","passMissHit",
#"isMatchRightCharge",
#"isTight",

######Triggers############
#"HLT_Ele25_eta2p1_WPTight_Gsf","HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ","HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL",
#"HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL","HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",

#"ttbarBDT_2lss","ttvBDT_2lss","Bin2l",
#"leadLep_jetdr","leadLep_corrpt","leadLep_jetcsv","leadLep_BDT",
#"secondLep_jetdr","secondLep_corrpt","secondLep_jetcsv","secondLep_BDT",
#"maxeta","Mt_metleadlep","SubCat2l","massll","Sum2lCharge","Dilep_bestMVA",
#"Dilep_worseMVA","Dilep_pdgId","Dilep_htllv","Dilep_mtWmin","Dilep_nTight",
#"leadJetCSV","secondJetCSV","thirdJetCSV","fourthJetCSV","HighestJetCSV",
#"HtJet","nLepFO","nLepTight","minMllAFAS","minMllAFOS","minMllSFOS",
#"Hj1_BDT",

###########Gen Info##################
#"gen_pt","gen_eta","gen_phi","gen_en",
#"gen_pdgId",

#"numMother","numDaught","BmotherIndex","motherpdg_id",
#"BmotherIndices","BdaughtIndices",

#"leadLep_isMatchRightCharge","leadLep_mcMatchId","leadLep_MatchMother_Id","leadLep_MatchGrandMother_Id",
#"leadLep_isFromTop","leadLep_isFromH","leadLep_isFromB","leadLep_isFromC",
#"leadLep_mcPromptGamma","leadLep_mcPromptFS",
#"subleadLep_isMatchRightCharge","subleadLep_mcMatchId","subleadLep_MatchMother_Id","subleadLep_MatchGrandMother_Id",
#"subleadLep_isFromTop","subleadLep_isFromH","subleadLep_isFromB","subleadLep_isFromC",
#"subleadLep_mcPromptGamma","subleadLep_mcPromptFS",

#"Jet25_axis2","Jet25_ptD","Jet25_mult","Jet25_pfCombinedCvsLJetTags","Jet25_pfCombinedCvsBJetTags",
#
#"Jet25_pt","Jet25_eta","Jet25_phi","Jet25_energy","Jet25_px",
#"Jet25_py","Jet25_pz","Jet25_mass",
#
#"Jet25_isFromH","Jet25_isFromTop","Jet25_matchId","Jet25_isToptag",
#
#"Jet25_neutralHadEnergyFraction","Jet25_neutralEmEnergyFraction","Jet25_chargedHadronEnergyFraction","Jet25_chargedEmEnergyFraction",
#"Jet25_muonEnergyFraction","Jet25_electronEnergy","Jet25_photonEnergy","Jet25_emEnergyFraction","Jet25_numberOfConstituents","Jet25_chargedMultiplicity",
# "Jet25_metptratio","Jet25_dilepmetptratio",
#"Jet25_nonjdr","Jet25_nonjdilepdr","Jet25_lepdrmin","Jet25_lepdrmax","Jet25_dilepdr","Jet25_bjdr", 
#"Jet25_nonjdeta","Jet25_nonjdilepdeta","Jet25_lepdetamin","Jet25_lepdetamax","Jet25_dilepdeta","Jet25_bjdeta", 
#"Jet25_nonjdphi","Jet25_nonjdilepdphi","Jet25_lepdphimin","Jet25_lepdphimax","Jet25_dilepdphi","Jet25_bjdphi",
#"Jet25_nonjptratio","Jet25_nonjdilepptratio","Jet25_lepptratiomin","Jet25_lepptratiomax","Jet25_dilepptratio","Jet25_bjptratio", 

#"Jet25_pfCombinedInclusiveSecondaryVertexV2BJet25Tags", "Jet25_pfCombinedMVAV2BJet25Tags", "Jet25_pfJet25ProbabilityBJet25Tags", "Jet25_pfDeepCSVCvsLJet25Tags", "Jet25_pfDeepCSVCvsBJet25Tags",

#"TTHLep_3L", "Trig_1Ele", "Trig_2Ele", "Trig_3Ele", "Trig_1Mu", "Trig_1Mu1Ele", "Trig_1Mu2Ele", "Trig_2Mu", "Trig_2Mu1Ele", "Trig_3Mu",

"HadTop_bjet_lepTop_csv","HadTop_bjet_hadTop_csv",
"HadTop_reco_hadTop_pt","HadTop_reco_hadTop_mass",
"HadTop_reco_WhadTop_mass","HadTop_PtRatio_leptOverleph",
"HadTop_Dr_lept_bfromlTop","HadTop_Dr_lept_bfromhTop",
"HadTop_Dr_leph_bfromlTop",

]

#VariableType  = "int"
#VariableNames = [
# CaseA Variables
#"Muon_soft","Muon_loose","Muon_medium","Muon_tight","Muon_isHighPt",
#"Muon_POGisGood","Muon_pdgId","Muon_pf","Muon_isGlobal","Muon_isTrackerMuon",
#"Muon_tunePBestTrackType","Muon_gen_pdgId","Muon_gen_isPromptFinalState","Muon_gen_isDirectPromptTauDecayProductFinalState"

# CaseB Variables

# CaseC Variables
#]

# Create the variable file
Vectorname = VariableType+Case+"_Class.cc"
vector     = file (Vectorname,"w")

#ReadTreeptr & WriteTreeptr
RTreeptr = "readingtree"
WTreeptr = "newtree"

#Name of Current Entry
ParEntry = "tentry"
#Name of index in Push_back
ParSel = "lep_en"
ParWrite = "lep_en"

###################
### Script itself
#################
if Case == "CaseA":
 print >> vector, "//This is CaseA"
 print >> vector, "//Head file declaration"
 print >> vector, "//initialization"
 for Variable in VariableNames:
     print >> vector, " _"+Variable+" =0.0;"
 
 print >> vector, "//Inline functions"
 for Variable in VariableNames:
     print >> vector, "  inline void Set"+Variable+"(" + VariableType+" "+Variable+"){_"+Variable+" = "+Variable+";};"
     print >> vector, "  inline "+VariableType+" Get" +Variable+"() const {return _"+Variable+";};"
     print >> vector, "  inline "+VariableType+" " +Variable+"() const {return _"+Variable+";};\n"
 
 print >> vector, "//attribute declaration "
 for Variable in VariableNames:
     print >> vector, "  " + VariableType+" _"+Variable+";"
 
 print >> vector, "//source file definition"
 print >> vector, "//initialization"
 for Variable in VariableNames:
     print >> vector, "  _"+Variable+"       (0.0),"
 
 print >> vector, "//initialization Copy Lepton"
 for Variable in VariableNames:
     print >> vector, "  _"+Variable+"(other.Get"+Variable+"()),"
 
 print >> vector, "//initialization Copy Particle"
 for Variable in VariableNames:
     print >> vector, "  _"+Variable+"       (0.0),"
 
 print >> vector, "//Overload Particle"
 for Variable in VariableNames:
     print >> vector, "  Set"+Variable+"       (0.0);"
 
 print >> vector, "//Overload Const Lepton"
 for Variable in VariableNames:
     print >> vector, "  Set"+Variable+"(other.Get"+Variable+"());"
 
 print >> vector, "//Overload Non-Const Lepton"
 for Variable in VariableNames:
     print >> vector, "  Set"+Variable+"(other.Get"+Variable+"());"
 
 print >> vector, "//Read Value"
 for Variable in VariableNames:
     print >> vector, "  Set"+Variable+"       (evtr -> " + rObject+"_"+Variable+"      -> operator[](iE));"
 
elif Case == "CaseB":
 print >> vector, "//This is CaseB"
 print >> vector, "//Head file declaration"
 print >> vector, "//variables to be read"
 for Variable in VariableNames:
     print >> vector,"   "+ VariableType+"           "+Variable+";"
 
 print >> vector, "//source file definition"
 print >> vector, "//read setbranchaddress"
 for Variable in VariableNames:
     print >> vector,"   TBranch           *b_"+Variable+";"
 
 print >> vector, "   //class member"
 for Variable in VariableNames:
     print >> vector,'   fChain->SetBranchAddress("'+Variable+'", &'+Variable+", &b_"+Variable+");"
 

elif Case == "CaseC":
 print >> vector, "//This is CaseC"
 print >> vector, "//Head file declaration"
 print >> vector, "//variables to be written"
 for Variable in VariableNames:
     print >> vector, "    "+VariableType+" "+Variable+";"
 
 print >> vector, "//source file definition"
 
 print >> vector, "   //Write setbranchaddress"
 for Variable in VariableNames:
     print >> vector, "  _"+rObject+'Vars["'+Variable+'"] = -999;'
 
 print >> vector, "   //Clear vector"
 for Variable in VariableNames:
     print >> vector, "  _"+rObject+'Vars["'+Variable+'"] = '+Variable+";"
 
 print >> vector, "   //class member"
 for Variable in VariableNames:
     print >> vector, "  "+Variable+" = -999;"
 
elif Case == "CaseD":
 print >> vector, "//This is CaseD"
 print >> vector, "//Head file declaration"
 print >> vector, "//variables to be written"
 for Variable in VariableNames:
     print >> vector, "    std::vector<double> "+Variable+";"
 
 print >> vector, "//source file definition"
 
 print >> vector, "   //Write setbranchaddress"
 for Variable in VariableNames:
     print >> vector, '  _doubleVecs["'+Variable+'"] = {-0.1,100};'
 
 print >> vector, "   //Clear vector"
 for Variable in VariableNames:
     print >> vector, "  "+Variable+".clear();"
 
 print >> vector, "   //class member"
 for Variable in VariableNames:
     print >> vector, "  "+Variable+".push_back(-999);"
 
 print >> vector, "   //class member"
 for Variable in VariableNames:
     print >> vector, '  _doubleVecs["'+Variable+'"] = '+Variable+";"
