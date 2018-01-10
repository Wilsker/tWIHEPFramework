/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      12 Dec 2017 - Created by B. Li.
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/ttHVars.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
ttHVars::ttHVars(bool makeHistos){

  SetName("ttHVars");

  _doubleVecs["Jet25_isFromH"] = {-0.1, 1.9 }; 
  _doubleVecs["Jet25_isFromTop"] = {-0.1, 1.9 }; 
  _doubleVecs["Jet25_matchId"] = {-25., 25. }; 
  _doubleVecs["Jet25_matchIndex"] = {-0.1, 9999. }; 
  _doubleVecs["Jet25_pt"] = {-0.1, 999. }; 
  _doubleVecs["Jet25_eta"] = {0, 9.9 }; 
  _doubleVecs["Jet25_phi"] = {-5., 5. }; 
  _doubleVecs["Jet25_energy"] = {-0.1, 999. }; 

  _doubleVecs["FakeLep_isFromB"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromC"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromH"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromTop"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_matchId"] = {-25., 25. }; 
  _doubleVecs["FakeLep_PdgId"] = {-25., 25. }; 
  _doubleVecs["FakeLep_matchIndex"] = {-0.1, 9999. }; 
  _doubleVecs["FakeLep_pt"] = {-0.1, 999. }; 
  _doubleVecs["FakeLep_eta"] = {0, 9.9 }; 
  _doubleVecs["FakeLep_phi"] = {-5., 5. }; 
  _doubleVecs["FakeLep_energy"] = {-0.1, 999. }; 

  _intVars["Jet_numbLoose"] = -999;
    
  _floatVars["massL"] = -999.;
  _floatVars["massL_SFOS"] = -999.;
  _floatVars["mass_diele"] = -999.;
  
  _floatVars["metLD"] = -999.;
  _floatVars["mht"] = -999.;
  _floatVars["mhtT"] = -999.;
  _floatVars["mht_met"] = -999.;
  _floatVars["mhtT_met"] = -999.;
 
  _floatVars["ttbarBDT_2lss"] = -999;
  _floatVars["ttvBDT_2lss"] = -999;
  _floatVars["Bin2l"] = -999;
  _floatVars["leadLep_jetdr"] = -999;
  _floatVars["leadLep_corrpt"] = -999;
  _floatVars["leadLep_jetcsv"] = -999;
  _floatVars["leadLep_BDT"] = -999;
  _floatVars["secondLep_jetdr"] = -999;
  _floatVars["secondLep_corrpt"] = -999;
  _floatVars["secondLep_jetcsv"] = -999;
  _floatVars["secondLep_BDT"] = -999;
  _floatVars["maxeta"] = -999;
  _floatVars["Mt_metleadlep"] = -999;
  _floatVars["SubCat2l"] = -999;
  _floatVars["massll"] = -999;
  _floatVars["Sum2lCharge"] = -999;
  _floatVars["Dilep_bestMVA"] = -999;
  _floatVars["Dilep_worseMVA"] = -999;
  _floatVars["Dilep_pdgId"] = -999;
  _floatVars["Dilep_htllv"] = -999;
  _floatVars["Dilep_mtWmin"] = -999;
  _floatVars["Dilep_nTight"] = -999;
  _floatVars["leadJetCSV"] = -999;
  _floatVars["secondJetCSV"] = -999;
  _floatVars["thirdJetCSV"] = -999;
  _floatVars["fourthJetCSV"] = -999;
  _floatVars["HighestJetCSV"] = -999;
  _floatVars["HtJet"] = -999;
  _floatVars["nLepFO"] = -999;
  _floatVars["nLepTight"] = -999;
  _floatVars["minMllAFAS"] = -999;
  _floatVars["minMllAFOS"] = -999;
  _floatVars["minMllSFOS"] = -999;
  _floatVars["Hj1_BDT"] = -999;
  _floatVars["leadLep_isMatchRightCharge"] = -999;
  _floatVars["leadLep_mcMatchId"] = -999;
  _floatVars["leadLep_isFromTop"] = -999;
  _floatVars["leadLep_isFromH"] = -999;
  _floatVars["leadLep_isFromB"] = -999;
  _floatVars["leadLep_isFromC"] = -999;
  _floatVars["leadLep_mcPromptGamma"] = -999;
  _floatVars["leadLep_mcPromptFS"] = -999;
  _floatVars["secondLep_isMatchRightCharge"] = -999;
  _floatVars["secondLep_mcMatchId"] = -999;
  _floatVars["secondLep_isFromTop"] = -999;
  _floatVars["secondLep_isFromH"] = -999;
  _floatVars["secondLep_isFromB"] = -999;
  _floatVars["secondLep_isFromC"] = -999;
  _floatVars["secondLep_mcPromptGamma"] = -999;
  _floatVars["secondLep_mcPromptFS"] = -999;

  SetDoHists(makeHistos);

}

void ttHVars::Clear(){
    looseLeptons.clear();
    fakeLeptons.clear();
    tightLeptons.clear();
    Jets.clear();
    MCBJets.clear();
    MCCJets.clear();
    MCLightJets.clear();
    FakeLep_isFromB.clear();
    FakeLep_isFromC.clear();
    FakeLep_isFromH.clear();
    FakeLep_isFromTop.clear();
    FakeLep_PdgId.clear();
    FakeLep_matchId.clear();
    FakeLep_matchIndex.clear();
    FakeLep_pt.clear();
    FakeLep_eta.clear();
    FakeLep_phi.clear();
    FakeLep_energy.clear();
    Jet25_isFromH.clear();
    Jet25_isFromTop.clear();
    Jet25_matchId.clear();
    Jet25_matchIndex.clear();
    Jet25_pt.clear();
    Jet25_eta.clear();
    Jet25_phi.clear();
    Jet25_energy.clear();
    Jet_numbLoose = -999;
    ttbarBDT_2lss = -999;
    ttvBDT_2lss = -999;
    Bin2l = -999;
    leadLep_jetdr = -999;
    leadLep_corrpt = -999;
    leadLep_jetcsv = -999;
    leadLep_BDT = -999;
    secondLep_jetdr = -999;
    secondLep_corrpt = -999;
    secondLep_jetcsv = -999;
    secondLep_BDT = -999;
    maxeta = -999;
    Mt_metleadlep = -999;
    SubCat2l = -999;
    massll = -999;
    Sum2lCharge = -999;
    Dilep_bestMVA = -999;
    Dilep_worseMVA = -999;
    Dilep_pdgId = -999;
    Dilep_htllv = -999;
    Dilep_mtWmin = -999;
    Dilep_nTight = -999;
    leadJetCSV = -999;
    secondJetCSV = -999;
    thirdJetCSV = -999;
    fourthJetCSV = -999;
    HighestJetCSV = -999;
    HtJet = -999;
    nLepFO = -999;
    nLepTight = -999;
    minMllAFAS = -999;
    minMllAFOS = -999;
    minMllSFOS = -999;
    Hj1_BDT = -999;
    leadLep_isMatchRightCharge = -999;
    leadLep_mcMatchId = -999;
    leadLep_isFromTop = -999;
    leadLep_isFromH = -999;
    leadLep_isFromB = -999;
    leadLep_isFromC = -999;
    leadLep_mcPromptGamma = -999;
    leadLep_mcPromptFS = -999;
    secondLep_isMatchRightCharge = -999;
    secondLep_mcMatchId = -999;
    secondLep_isFromTop = -999;
    secondLep_isFromH = -999;
    secondLep_isFromB = -999;
    secondLep_isFromC = -999;
    secondLep_mcPromptGamma = -999;
    secondLep_mcPromptFS = -999;

}

void ttHVars::FillBranches(EventContainer * evtObj){

    //Initialise vectors;
    Clear();
    
    looseLeptons.assign(evtObj -> looseLeptons.begin(), evtObj -> looseLeptons.end());
    fakeLeptons.assign(evtObj -> fakeLeptons.begin(), evtObj -> fakeLeptons.end());
    tightLeptons.assign(evtObj -> tightLeptons.begin(), evtObj -> tightLeptons.end());
    
    Jets.assign(evtObj -> jets.begin(), evtObj -> jets.end());
    
    MCBJets.assign(evtObj -> MCBJets.begin(), evtObj -> MCBJets.end());
    MCCJets.assign(evtObj -> MCCJets.begin(), evtObj -> MCCJets.end());
    MCLightJets.assign(evtObj -> MCLightJets.begin(), evtObj -> MCLightJets.end());
   
    MCPhotons.assign(evtObj -> MCPhotons.begin(), evtObj -> MCPhotons.end());
    MCElectrons.assign(evtObj -> MCElectrons.begin(), evtObj -> MCElectrons.end());
    MCMuons.assign(evtObj -> MCMuons.begin(), evtObj -> MCMuons.end());
    mcParticlesPtr = &(evtObj->MCParticles);
    //Jet matching 
    for(auto jet: Jets){
        Do_Jet_Match(jet, MCBJets, MCCJets, MCLightJets);
    }
    
    //Lep matching 
    for(auto lep: fakeLeptons){
        Do_Lepton_Match(lep, MCElectrons, MCMuons,MCPhotons);
    }
    
    Cal_event_variables(evtObj);
   
   
    // Fill the variables in event container

    // Fill the branches
    
    _doubleVecs["FakeLep_isFromB"] = FakeLep_isFromB; 
    _doubleVecs["FakeLep_isFromC"] = FakeLep_isFromC; 
    _doubleVecs["FakeLep_isFromH"] = FakeLep_isFromH; 
    _doubleVecs["FakeLep_isFromTop"] = FakeLep_isFromTop; 
    _doubleVecs["FakeLep_PdgId"] = FakeLep_PdgId; 
    _doubleVecs["FakeLep_matchId"] = FakeLep_matchId; 
    _doubleVecs["FakeLep_matchIndex"] = FakeLep_matchIndex; 
    _doubleVecs["FakeLep_pt"] = FakeLep_pt; 
    _doubleVecs["FakeLep_eta"] = FakeLep_eta; 
    _doubleVecs["FakeLep_phi"] = FakeLep_phi; 
    _doubleVecs["FakeLep_energy"] = FakeLep_energy; 
    
    _doubleVecs["Jet25_isFromH"] = Jet25_isFromH; 
    _doubleVecs["Jet25_isFromTop"] = Jet25_isFromTop; 
    _doubleVecs["Jet25_matchId"] = Jet25_matchId; 
    _doubleVecs["Jet25_matchIndex"] = Jet25_matchIndex; 
    _doubleVecs["Jet25_pt"] = Jet25_pt; 
    _doubleVecs["Jet25_eta"] = Jet25_eta; 
    _doubleVecs["Jet25_phi"] = Jet25_phi; 
    _doubleVecs["Jet25_energy"] = Jet25_energy; 
    
    _floatVars["massL"] = evtObj->massL;
    _floatVars["massL_SFOS"] = evtObj->massL_SFOS;
    _floatVars["mass_diele"] = evtObj->mass_diele;
  
    _floatVars["metLD"] = evtObj->metLD;
    _floatVars["mht"] = evtObj->mht;
    _floatVars["mhtT"] = evtObj->mhtT;
    _floatVars["mht_met"] = evtObj->mht_met;
    _floatVars["mhtT_met"] = evtObj->mhtT_met;
     
    _intVars["Jet_numbLoose"] = Jet_numbLoose;
    _floatVars["ttbarBDT_2lss"] = ttbarBDT_2lss;
    _floatVars["ttvBDT_2lss"] = ttvBDT_2lss;
    _floatVars["Bin2l"] = Bin2l;
    _floatVars["leadLep_jetdr"] = leadLep_jetdr;
    _floatVars["leadLep_corrpt"] = leadLep_corrpt;
    _floatVars["leadLep_jetcsv"] = leadLep_jetcsv;
    _floatVars["leadLep_BDT"] = leadLep_BDT;
    _floatVars["secondLep_jetdr"] = secondLep_jetdr;
    _floatVars["secondLep_corrpt"] = secondLep_corrpt;
    _floatVars["secondLep_jetcsv"] = secondLep_jetcsv;
    _floatVars["secondLep_BDT"] = secondLep_BDT;
    _floatVars["maxeta"] = maxeta;
    _floatVars["Mt_metleadlep"] = Mt_metleadlep;
    _floatVars["SubCat2l"] = SubCat2l;
    _floatVars["massll"] = massll;
    _floatVars["Sum2lCharge"] = Sum2lCharge;
    _floatVars["Dilep_bestMVA"] = Dilep_bestMVA;
    _floatVars["Dilep_worseMVA"] = Dilep_worseMVA;
    _floatVars["Dilep_pdgId"] = Dilep_pdgId;
    _floatVars["Dilep_htllv"] = Dilep_htllv;
    _floatVars["Dilep_mtWmin"] = Dilep_mtWmin;
    _floatVars["Dilep_nTight"] = Dilep_nTight;
    _floatVars["leadJetCSV"] = leadJetCSV;
    _floatVars["secondJetCSV"] = secondJetCSV;
    _floatVars["thirdJetCSV"] = thirdJetCSV;
    _floatVars["fourthJetCSV"] = fourthJetCSV;
    _floatVars["HighestJetCSV"] = HighestJetCSV;
    _floatVars["HtJet"] = HtJet;
    _floatVars["nLepFO"] = nLepFO;
    _floatVars["nLepTight"] = nLepTight;
    _floatVars["minMllAFAS"] = minMllAFAS;
    _floatVars["minMllAFOS"] = minMllAFOS;
    _floatVars["minMllSFOS"] = minMllSFOS;
    _floatVars["Hj1_BDT"] = Hj1_BDT;
  
    _floatVars["leadLep_isMatchRightCharge"] = leadLep_isMatchRightCharge;
    _floatVars["leadLep_mcMatchId"] = leadLep_mcMatchId;
    _floatVars["leadLep_isFromTop"] = leadLep_isFromTop;
    _floatVars["leadLep_isFromH"] = leadLep_isFromH;
    _floatVars["leadLep_isFromB"] = leadLep_isFromB;
    _floatVars["leadLep_isFromC"] = leadLep_isFromC;
    _floatVars["leadLep_mcPromptGamma"] = leadLep_mcPromptGamma;
    _floatVars["leadLep_mcPromptFS"] = leadLep_mcPromptFS;
    _floatVars["secondLep_isMatchRightCharge"] = secondLep_isMatchRightCharge;
    _floatVars["secondLep_mcMatchId"] = secondLep_mcMatchId;
    _floatVars["secondLep_isFromTop"] = secondLep_isFromTop;
    _floatVars["secondLep_isFromH"] = secondLep_isFromH;
    _floatVars["secondLep_isFromB"] = secondLep_isFromB;
    _floatVars["secondLep_isFromC"] = secondLep_isFromC;
    _floatVars["secondLep_mcPromptGamma"] = secondLep_mcPromptGamma;
    _floatVars["secondLep_mcPromptFS"] = secondLep_mcPromptFS;
  
    if(evtObj -> _sync == 52){     
        std::cout << " " <<  evtObj-> eventNumber <<" "<<maxeta<< " " << Jet_numLoose << " "<< Mt_metleadlep << " "<< leadLep_jetdr << " "<< secondLep_jetdr <<" "<< leadLep_corrpt <<" "<< secondLep_corrpt << " " << Hj1_BDT <<" " << evtObj->HadTop_BDT << " " << ttbarBDT_2lss << " " << ttvBDT_2lss << " " << Bin2l <<std::endl;         
    }                          

    if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

// Calculate event variables for plots 
void ttHVars::Cal_event_variables(EventContainer* EvtObj){
    TLorentzVector FakeLep1{0,0,0,0};
    TLorentzVector FakeLep2{0,0,0,0};
    TLorentzVector Lep1{0,0,0,0};
    TLorentzVector Lep2{0,0,0,0};
    double minMass_AFAS =999;
    double minMass_AFOS =999;
    double minMass_SFOS =999;
    for(uint lep1_en=0; lep1_en<looseLeptons.size();lep1_en++){
        for(uint lep2_en=lep1_en+1; lep2_en<looseLeptons.size();lep2_en++){
            Lepton firstLepton = looseLeptons.at(lep1_en);
            Lepton secondLepton = looseLeptons.at(lep2_en);
            Lep1.SetPtEtaPhiE(firstLepton.Pt(),firstLepton.Eta(),firstLepton.Phi(),firstLepton.E());
            Lep2.SetPtEtaPhiE(secondLepton.Pt(),secondLepton.Eta(),secondLepton.Phi(),secondLepton.E());
            double curr_mass = (Lep1+Lep2).M();
            if(curr_mass < minMass_AFAS )minMass_AFAS=curr_mass; 
            if(curr_mass < minMass_AFOS && firstLepton.charge()*secondLepton.charge() < 0)minMass_AFOS=curr_mass; 
            if(curr_mass < minMass_SFOS && firstLepton.charge()*secondLepton.charge() < 0 && fabs(firstLepton.pdgId())== fabs(secondLepton.pdgId()))minMass_SFOS=curr_mass; 
        }
    }
    minMllAFOS = minMass_AFOS;
    minMllAFAS = minMass_AFAS;
    minMllSFOS = minMass_SFOS;
    nLepFO = fakeLeptons.size();
    nLepTight = tightLeptons.size();
    double maxCSV = -999;
    double SumPt =0;
    double maxHj = -999;
    int jet_numbLoose = 0;
    int jet_numbMedium = 0;
    for(uint jet_en=0; jet_en < Jets.size(); jet_en++){
        Jet jet = Jets.at(jet_en);
        if(jet.isMediumBdisc())jet_numbMedium++;
        if(jet.isLooseBdisc())jet_numbLoose++;
        SumPt = jet.Pt() + SumPt;
        if(jet_en == 0)leadJetCSV = jet.bDiscriminator();
        if(jet_en == 1)secondJetCSV = jet.bDiscriminator(); 
        if(jet_en == 2)thirdJetCSV = jet.bDiscriminator(); 
        if(jet_en == 3)fourthJetCSV = jet.bDiscriminator();
        if( maxCSV < jet.bDiscriminator()) maxCSV = jet.bDiscriminator();
        if( jet.isToptag()!=1 && jet.HjDisc() > maxHj) maxHj = jet.HjDisc();
    }
    Jet_numLoose = Jets.size();
    Jet_numbLoose = jet_numbLoose;
    Hj1_BDT = maxHj;
    HighestJetCSV = maxCSV;
    HtJet = SumPt;
    if(fakeLeptons.size()>=2){
        Lepton firstLepton = fakeLeptons.at(0);
        Lepton secondLepton = fakeLeptons.at(1);
        double leadLep_closedr =999.;
        double secondLep_closedr =999.;
        for(uint jet_en=0; jet_en < Jets.size(); jet_en++){
            Jet jet = Jets.at(jet_en);
            double lead_dr = firstLepton.DeltaR(jet);
            double second_dr = secondLepton.DeltaR(jet);
            double csv = jet.bDiscriminator();
            if(lead_dr>0.4 && leadLep_closedr > lead_dr){
                leadLep_closedr = lead_dr;
                leadLep_jetcsv = csv; 
            }
            if(second_dr>0.4 && secondLep_closedr > second_dr){
                secondLep_closedr = second_dr;
                secondLep_jetcsv = csv; 
            }
        }
        leadLep_isMatchRightCharge = FakeLep_matchId.at(0) == FakeLep_PdgId.at(0)? 1 : 0;
        leadLep_mcMatchId = FakeLep_matchId.at(0);
        leadLep_isFromTop = FakeLep_isFromTop.at(0);
        leadLep_isFromH = FakeLep_isFromH.at(0);
        leadLep_isFromB = FakeLep_isFromB.at(0);
        leadLep_isFromC = FakeLep_isFromC.at(0);
        leadLep_mcPromptGamma = FakeLep_matchId.at(0) == 22 ? 1 : 0;
        leadLep_mcPromptFS = (firstLepton.gen_isPrompt() ==1 || firstLepton.gen_isPromptTau()==1)? 1 : 0;
        secondLep_isMatchRightCharge = FakeLep_matchId.at(1) == FakeLep_PdgId.at(1)? 1 : 0;
        secondLep_mcMatchId = FakeLep_matchId.at(1);
        secondLep_isFromTop = FakeLep_isFromTop.at(1);
        secondLep_isFromH = FakeLep_isFromH.at(1);
        secondLep_isFromB = FakeLep_isFromB.at(1);
        secondLep_isFromC = FakeLep_isFromC.at(1);
        secondLep_mcPromptGamma = FakeLep_matchId.at(1) == 22 ? 1 : 0;
        secondLep_mcPromptFS = (secondLepton.gen_isPrompt() ==1 || secondLepton.gen_isPromptTau()==1)? 1 : 0;
        leadLep_jetdr= leadLep_closedr; 
        secondLep_jetdr= secondLep_closedr;
        FakeLep1.SetPtEtaPhiE(firstLepton.conept(),firstLepton.Eta(),firstLepton.Phi(),firstLepton.E());
        FakeLep2.SetPtEtaPhiE(secondLepton.conept(),secondLepton.Eta(),secondLepton.Phi(),secondLepton.E());
        massll = (FakeLep1+FakeLep2).M();
        leadLep_corrpt= firstLepton.conept();
        secondLep_corrpt= secondLepton.conept();
        leadLep_BDT = firstLepton.BDT();
        secondLep_BDT = secondLepton.BDT();
        Sum2lCharge= firstLepton.charge()+secondLepton.charge();
        Dilep_bestMVA = std::max(firstLepton.BDT(),secondLepton.BDT());
        Dilep_worseMVA = std::min(firstLepton.BDT(),secondLepton.BDT());
        Dilep_pdgId = 26 - fabs((firstLepton.pdgId() + secondLepton.pdgId()))/2;
        Dilep_htllv = firstLepton.conept() + secondLepton.conept() + EvtObj->missingEt; 
        if((firstLepton.isTight() + secondLepton.isTight()) ==2) Dilep_nTight = 2 ;
        else if((firstLepton.isTight() + secondLepton.isTight()) ==1) Dilep_nTight = 1 ;
        else Dilep_nTight = 0 ;
        Mt_metleadlep = getMTlepmet(firstLepton.Phi(),EvtObj->missingPhi,firstLepton.conept(),EvtObj->missingEt); 
        maxeta = max(fabs(firstLepton.Eta()),fabs(secondLepton.Eta()));
        
        Dilep_mtWmin = std::min(getMTlepmet(secondLepton.Phi(),EvtObj->missingPhi,secondLepton.conept(),EvtObj->missingEt), Mt_metleadlep); 
        ttbarBDT_2lss = get_Dilep_ttbarMVA(EvtObj);
        ttvBDT_2lss = get_Dilep_ttvMVA(EvtObj);
        Bin2l = get_2DBDTBin(ttbarBDT_2lss, ttvBDT_2lss, EvtObj);
    }
    //2l sub category
    if(fakeLeptons.size()>=2){
        Lepton firstLepton = fakeLeptons.at(0);
        Lepton secondLepton = fakeLeptons.at(1);
        if(firstLepton.charge()== -1 && (fabs(firstLepton.pdgId())+fabs(secondLepton.pdgId()))== 22) SubCat2l=1; // ee-
        if(firstLepton.charge()== 1 && (fabs(firstLepton.pdgId())+fabs(secondLepton.pdgId()))== 22) SubCat2l=2; // ee+
        if((fabs(firstLepton.pdgId())+fabs(secondLepton.pdgId()))== 24){ // eu
            if(jet_numbMedium<2){ //bl
                if(firstLepton.charge()==-1)SubCat2l=3; // eubl-
                if(firstLepton.charge()==1)SubCat2l=4; // eubl+
            }else{//bt
                if(firstLepton.charge()==-1)SubCat2l=5; // eubt-
                if(firstLepton.charge()==1)SubCat2l=6; // eubt+
            }
        }
        if((fabs(firstLepton.pdgId())+fabs(secondLepton.pdgId()))== 26){ // eu
            if(jet_numbMedium<2){ //bl
                if(firstLepton.charge()==-1)SubCat2l=7; // uubl-
                if(firstLepton.charge()==1)SubCat2l=8; // uubl+
            }else{//bt
                if(firstLepton.charge()==-1)SubCat2l=9; // uubt-
                if(firstLepton.charge()==1)SubCat2l=10; // uubt+
            }
        }
    }else{
        SubCat2l=0;//others
    }
};

double ttHVars::getMTlepmet(double phi1, double phi2, double pt1, double pt2){
    double Mass =0;
    Mass = sqrt(2*pt1*pt2*(1-cos(deltaPhi(phi1,phi2))));
    return Mass;
};

//2D Binning
Int_t ttHVars::get_2DBDTBin(double BDT_ttbar, double BDT_ttV, EventContainer* EvtObj){
    int BDTBin=0;
    BDTBin = 1 + EvtObj->hBinning2l->GetBinContent(EvtObj-> hBinning2l->FindBin(BDT_ttbar,BDT_ttV));
    return BDTBin;
};

// 2l ttbar MVA
double ttHVars::get_Dilep_ttbarMVA(EventContainer* EvtObj){
    EvtObj->Dilepttbar_maxlepeta =maxeta;
    EvtObj->Dilepttbar_numJets =Jet_numLoose;
    EvtObj->Dilepttbar_mindrlep1jet= leadLep_jetdr;
    EvtObj->Dilepttbar_mindrlep2jet= secondLep_jetdr;
    EvtObj->Dilepttbar_Mtmetlep1=Mt_metleadlep;
    EvtObj->Dilepttbar_HadTopBDT = max(-1.1, EvtObj->HadTop_BDT) ;
    //cout << "get_EleMVA end" << endl;
    return EvtObj->Dilepttbar_reader_->EvaluateMVA("BDTG method");
};


//2l ttv mva
double ttHVars::get_Dilep_ttvMVA(EventContainer* EvtObj){
    EvtObj->Dilepttv_maxlepeta =maxeta;
    EvtObj->Dilepttv_Mtmetlep1= Mt_metleadlep;
    EvtObj->Dilepttv_numJets = Jet_numLoose;
    EvtObj->Dilepttv_mindrlep1jet= leadLep_jetdr;
    EvtObj->Dilepttv_mindrlep2jet= secondLep_jetdr;
    EvtObj->Dilepttv_ptlep1= leadLep_corrpt;
    EvtObj->Dilepttv_ptlep2= secondLep_corrpt;
    EvtObj->Dilepttv_Hj1BDT = max(-1.1,Hj1_BDT);
    return EvtObj->Dilepttv_reader_->EvaluateMVA("BDTG method");
};
// utils
double ttHVars::deltaPhi(double phi1, double phi2){
    double result = phi1 - phi2;
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
}
// Jet matching
void ttHVars::Do_Jet_Match(Jet reco, std::vector<MCJet>& BJets, std::vector<MCJet>& CJets, std::vector<MCJet>& LightJets){
    double isFromH = -999.;
    double isFromTop = -999.;
    double matchId = -999.;
    double matchIndex = -999.;
    MCParticle gen;
    Bool_t ismatch = false;
    double min_dpho_bc = 999.;
    double min_dpho_light = 999.;
    for(auto bjet: BJets){
        if(bjet.numDaught()>1)continue;
        double dr = reco.DeltaR(bjet);
        if(dr < 0.3){
            double dpho = dr + 0.2*fabs((reco.Pt()-bjet.Pt())/bjet.Pt());
            if(dpho < min_dpho_bc){
                gen = bjet;
                min_dpho_bc = dpho;
                ismatch = true;
            }
        }
    }
    for(auto cjet: CJets){
        if(cjet.numDaught()>1)continue;
        double dr = reco.DeltaR(cjet);
        if(dr < 0.3){
            double dpho = dr + 0.2*fabs((reco.Pt()-cjet.Pt())/cjet.Pt());
            if(dpho < min_dpho_bc){
                gen = cjet;
                min_dpho_bc = dpho;
                ismatch = true;
            }
        }
    }
    // if we fail to find a b or c
    if(min_dpho_bc == 999.){
        for(auto lightjet: LightJets){
            if(lightjet.numDaught()>1)continue;
            double dr = reco.DeltaR(lightjet);
            if(dr < 0.3){
                double dpho = dr + 0.2*fabs((reco.Pt()-lightjet.Pt())/lightjet.Pt());
                if(dpho < min_dpho_light ){
                    gen = lightjet;
                    min_dpho_light = dpho;
                    ismatch = true;
                }
            }
        }
    }
    // if we do find a gen matched particle
    if(ismatch){
        matchId = gen.PdgId();
        matchIndex = gen.Index();
        MCParticle genMother = gen.GetGenMotherNoFsr(gen, *mcParticlesPtr);
        MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *mcParticlesPtr);
        MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *mcParticlesPtr);
        if(fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId()) == 25) isFromH = 1;
        else isFromH = 0;
        if(fabs(genMother.PdgId()) == 6 || fabs(genGMother.PdgId()) == 6 || fabs(genGGMother.PdgId()) == 6) isFromTop = 1;
        else isFromTop = 0;
    }
    Jet25_isFromH.push_back(isFromH); 
    Jet25_isFromTop.push_back(isFromTop); 
    Jet25_matchId.push_back(matchId); 
    Jet25_matchIndex.push_back(matchIndex); 
    Jet25_pt.push_back(reco.Pt()); 
    Jet25_eta.push_back(reco.Eta()); 
    Jet25_phi.push_back(reco.Phi()); 
    Jet25_energy.push_back(reco.E()); 
};
    
//Lepton matching
void ttHVars::Do_Lepton_Match(Lepton reco, std::vector<MCElectron>& MCElectrons, std::vector<MCMuon>& MCMuons, std::vector<MCPhoton>& MCPhotons){
    MCParticle gen;
    double min_dpho =999.;
    double isFromH = -999.;
    double isFromB = -999.;
    double isFromC = -999.;
    double isFromTop = -999.;
    double matchId = -999.;
    double matchIndex = -999.;
    Bool_t ismatch = false;
    for(auto MCEle: MCElectrons){
        if(MCEle.Status()!=1 || fabs(MCEle.PdgId())!= fabs(reco.pdgId()) || MCEle.Pt()<1.0)continue;
        double dr = reco.DeltaR(MCEle);
        if(dr < 0.3){
            double dpho = dr + 0.2*fabs((reco.Pt()-MCEle.Pt())/MCEle.Pt());
            if(dpho < min_dpho){
                gen = MCEle;
                min_dpho = dpho;
                ismatch = true;
            }
        }
    }
    for(auto MCMu: MCMuons){
        if(MCMu.Status()!=1 || fabs(MCMu.PdgId())!= fabs(reco.pdgId()) || MCMu.Pt()<1.0)continue;
        double dr = reco.DeltaR(MCMu);
        if(dr < 0.3){
            double dpho = dr + 0.2*fabs((reco.Pt()-MCMu.Pt())/MCMu.Pt());
            if(dpho < min_dpho){
                gen = MCMu;
                min_dpho = dpho;
                ismatch = true;
            }
        }
    }
    // do photon matching for electron
    if(fabs(reco.pdgId())==11){
        for(auto MCPhoton: MCPhotons){
            if(MCPhoton.Status()!=1 || MCPhoton.Pt()<1.0)continue;
            double dr = reco.DeltaR(MCPhoton);
            if(dr < 0.3 && reco.Pt() > 0.3 * MCPhoton.Pt() && reco.Pt()< 1.5 * MCPhoton.Pt()){
                double dpho = dr + 0.2*fabs((reco.Pt()-MCPhoton.Pt())/MCPhoton.Pt());
                if(dpho < min_dpho){
                    gen = MCPhoton;
                    min_dpho = dpho;
                    ismatch = true;
                }
            }
        }
    }
    
    if(ismatch){
        matchId = gen.PdgId();
        matchIndex = gen.Index();
        MCParticle genMother = gen.GetGenMotherNoFsr(gen, *mcParticlesPtr);
        MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *mcParticlesPtr);
        MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *mcParticlesPtr);
        if(fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId()) == 25) isFromH = 1;
        else isFromH = 0;
        if(fabs(genMother.PdgId()) == 6 || fabs(genGMother.PdgId()) == 6 || fabs(genGGMother.PdgId()) == 6) isFromTop = 1;
        else isFromTop = 0;
        if(gen.isFromB(gen, *mcParticlesPtr)){
            isFromB =1;
            isFromC =0;
        }
        else if (gen.isFromB(gen, *mcParticlesPtr, 4)){
            isFromC =1;
            isFromB =0;
        }else{
            isFromC =0;
            isFromB =0;
        }
    }
    FakeLep_isFromB.push_back(isFromB); 
    FakeLep_isFromC.push_back(isFromC); 
    FakeLep_isFromH.push_back(isFromH); 
    FakeLep_isFromTop.push_back(isFromTop); 
    FakeLep_matchId.push_back(matchId); 
    FakeLep_matchIndex.push_back(matchIndex); 
    FakeLep_PdgId.push_back(reco.pdgId()); 
    FakeLep_pt.push_back(reco.Pt()); 
    FakeLep_eta.push_back(reco.Eta()); 
    FakeLep_phi.push_back(reco.Phi()); 
    FakeLep_energy.push_back(reco.E()); 
};
