/******************************************************************************
 * ttVModellingVars.cpp                                                                *
 *
 * Generator level variables.
 *
 * History
 *      25th July 2018 - Joshuha Thomas-Wilsker
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/ttVModellingVars.hpp"
#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
ttVModellingVars::ttVModellingVars(bool makeHistos){

  SetName("ttVModelling");

  _floatVars["genWeight_muF2"] = 999;
  _floatVars["genWeight_muF0p5"] = 999;
  _floatVars["genWeight_muR2"] = 999;
  _floatVars["genWeight_muR0p5"] = 999;
  _floatVars["n_gen_ele"] = 999;
  _floatVars["n_gen_mu"] = 999;
  _floatVars["n_gen_lepton"] = 999;
  _floatVars["n_gen_jets"] = 999;
  _floatVars["n_gen_bjets"] = 999;
  _floatVars["n_gen_tau"] = 999;
  _floatVars["gen_lepton1_pt"] = 999;
  _floatVars["gen_lepton2_pt"] = 999;
  _floatVars["gen_jet1_pt"] = 999;
  _floatVars["gen_jet2_pt"] = 999;
  _floatVars["gen_jet3_pt"] = 999;
  _floatVars["gen_jet4_pt"] = 999;
  _floatVars["gen_jet5_pt"] = 999;
  _floatVars["gen_jet6_pt"] = 999;
  _floatVars["gen_bjet1_pt"] = 999;
  _floatVars["gen_bjet2_pt"] = 999;

  _floatVars["MinDRMCGenLeps"] = 999;
  _floatVars["MinDRMCGenLep1Jet"] = 999;
  _floatVars["MinDrMCGenLep2Jet"] = 999;
  _floatVars["MCGenMET"] = 999;
  _floatVars["MCGenHTall"] = 999;
  _floatVars["MCGenHThad"] = 999;

  SetDoHists(makeHistos);
}

void ttVModellingVars::Clear(){

    genElectrons.clear();
    genMuons.clear();
    genLeptons.clear();
    genJets.clear();
    genBJets.clear();
    genTau.clear();
    genParticles.clear();
    n_gen_ele = -9999;
    n_gen_mu = -9999;
    n_gen_lepton = -9999;
    n_gen_jets = -9999;
    n_gen_bjets = -9999;
    n_gen_tau = -9999;
    gen_lepton1_pt = -9999;
    gen_lepton2_pt = -9999;
    gen_jet1_pt = -9999;
    gen_jet2_pt = -9999;
    gen_jet3_pt = -9999;
    gen_jet4_pt = -9999;
    gen_jet5_pt = -9999;
    gen_jet6_pt = -9999;
    gen_bjet1_pt = -9999;
    gen_bjet2_pt = -9999;
    MinDeltaR_MCGenLeps = 9999;
    MinDeltaR_MCGenLep1Jet = 9999;
    MinDeltaR_MCGenLep2Jet = 9999;
    MCGen_MET = 0;
    MCGen_HTall = 0;
    MCGen_HThad = 0;
}

void ttVModellingVars::FillBranches(EventContainer * evtObj){

    //Initialise vectors;
    Clear();

    genElectrons.assign(evtObj -> MCElectrons.begin(), evtObj -> MCElectrons.end());
    genMuons.assign(evtObj -> MCMuons.begin(), evtObj -> MCMuons.end());
    genJets.assign(evtObj -> MCJets.begin(), evtObj -> MCJets.end());
    genTau.assign(evtObj -> MCTaus.begin(), evtObj -> MCTaus.end());
    genBJets.assign(evtObj -> MCBJets.begin(), evtObj -> MCBJets.end() );
    genParticles.assign(evtObj -> MCParticles.begin(), evtObj -> MCParticles.end() );

   int n_genEle =-9;
   int n_genMu =-9;
   int n_genLep =-9;
   int n_genJet =-9;
   int n_genBJet =-9;
   int n_genTau =-9;
   double leadbjetpt =-9;
   double subleadbjetpt =-9;
   double leadjetpt =-9;
   double subleadjetpt =-9;
   double jet3pt =-9;
   double jet4pt =-9;
   double jet5pt =-9;
   double jet6pt =-9;
   double leadele_pt =-9;
   double subleadele_pt =-9;
   double leadmu_pt =-9;
   double subleadmu_pt =-9;
   double genlep1_pt =-9;
   double genlep2_pt =-9;
   double genjet1_pt =-9;
   double genjet2_pt =-9;
   double genjet3_pt =-9;
   double genjet4_pt =-9;
   double genjet5_pt =-9;
   double genjet6_pt =-9;

   double MinDRMCGenLeps =-9;
   double MinDRMCGenLep1Jet =-9;
   double MinDrMCGenLep2Jet=-9;
   double MCGenMET =-9;
   double MCGenHTall =-9;
   double MCGenHThad =-9;

   SourceNumber = evtObj->GetSourceNumber();

   n_genEle = genElectrons.size();
   n_genMu = genMuons.size();
   n_genLep = n_genEle + n_genMu;
   n_genJet = genJets.size();
   n_genBJet = genBJets.size();
   n_genTau = genTau.size();

   // calculate variables
   nEvent = evtObj->eventNumber;

   EventTree* tree = evtObj->GetEventTree();
   if(tree->EVENT_genWeights->size()>6){
       genWeight_muF2 = tree->EVENT_genWeights -> operator[](1);
       genWeight_muF0p5 = tree->EVENT_genWeights -> operator[](2);
       genWeight_muR2 = tree->EVENT_genWeights -> operator[](3);
       genWeight_muR0p5 = tree->EVENT_genWeights -> operator[](6);
   }else{
       genWeight_muF2 = tree->EVENT_genWeight;
       genWeight_muF0p5 = tree->EVENT_genWeight;
       genWeight_muR2 = tree->EVENT_genWeight;
       genWeight_muR0p5 = tree->EVENT_genWeight;
   }
   ls = evtObj-> lumiBlock;
   run = evtObj->runNumber;
   n_gen_ele = n_genEle;
   n_gen_mu = n_genMu;
   n_gen_lepton = n_genLep;
   n_gen_jets = n_genJet;
   n_gen_bjets = n_genBJet;
   n_gen_tau = n_genTau;

   MCParticle leading_MCLepton;
   MCParticle subleading_MCLepton;
   vector<MCParticle> MCGenLeptons;
   MCParticle jet1_MCGen;
   MCParticle jet2_MCGen;
   MCParticle jet3_MCGen;
   MCParticle jet4_MCGen;
   MCParticle jet5_MCGen;
   MCParticle jet6_MCGen;
   vector<MCParticle> MCGenJets;

   for (auto const lep : genElectrons){
     MCGenLeptons.push_back(lep);
     if (lep.Pt() > leadele_pt) leadele_pt = lep.Pt();
     if (lep.Pt() > genlep1_pt) {genlep1_pt = lep.Pt(); leading_MCLepton=lep;}
   }
   for (auto const lep : genMuons){
     MCGenLeptons.push_back(lep);
     if (lep.Pt() > leadmu_pt) leadmu_pt = lep.Pt();
     if (lep.Pt() > genlep1_pt) {genlep1_pt = lep.Pt(); leading_MCLepton=lep;}
   }
   for (auto const lep : genMuons){
     if (lep.Pt() > subleadmu_pt && lep.Pt() < leadmu_pt) subleadmu_pt = lep.Pt();
     if (lep.Pt() > genlep2_pt && lep.Pt() < genlep1_pt){genlep2_pt = lep.Pt(); subleading_MCLepton=lep;}
   }
   for (auto const lep : genElectrons){
     if (lep.Pt() > subleadele_pt && lep.Pt() < leadele_pt) subleadele_pt = lep.Pt();
     if (lep.Pt() > genlep2_pt && lep.Pt() < genlep1_pt){genlep2_pt = lep.Pt(); subleading_MCLepton=lep;}
   }

   gen_lepton1_pt = genlep1_pt;
   gen_lepton2_pt = genlep2_pt;


   for ( auto const jet : genBJets) {
     if (jet.Pt() > leadbjetpt) leadbjetpt = jet.Pt();
   }
   for ( auto const jet : genBJets) {
     if (jet.Pt() < leadbjetpt && jet.Pt() > subleadbjetpt) subleadbjetpt = jet.Pt();
   }
   gen_bjet1_pt = leadbjetpt;
   gen_bjet2_pt = subleadbjetpt;


   for (auto const jet : genJets){
     MCGenJets.push_back(jet);
     if (jet.Pt() > leadjetpt) {leadjetpt = jet.Pt(); jet1_MCGen = jet;}
   }
   for (auto const jet : genJets){
     if (jet.Pt() < leadjetpt && jet.Pt() > subleadjetpt) {subleadjetpt = jet.Pt(); jet2_MCGen = jet;}
   }
   for (auto const jet : genJets){
     if (jet.Pt() < subleadjetpt && jet.Pt() > jet3pt) {jet3pt = jet.Pt(); jet3_MCGen = jet;}
   }
   for (auto const jet : genJets){
     if (jet.Pt() < jet3pt && jet.Pt() > jet4pt) {jet4pt = jet.Pt(); jet4_MCGen = jet;}
   }
   for (auto const jet : genJets){
     if (jet.Pt() < jet4pt && jet.Pt() > jet5pt) {jet5pt = jet.Pt(); jet5_MCGen = jet;}
   }
   for (auto const jet : genJets){
     if (jet.Pt() < jet5pt && jet.Pt() > jet6pt) {jet6pt = jet.Pt(); jet6_MCGen = jet;}
   }

   if (genJets.size()>0){genjet1_pt = leadjetpt;}
   if (genJets.size()>1){genjet2_pt = subleadjetpt;}
   if (genJets.size()>2){genjet3_pt = jet3pt;}
   if (genJets.size()>3){genjet4_pt = jet4pt;}
   if (genJets.size()>4){genjet5_pt = jet5pt;}
   if (genJets.size()>5){genjet6_pt = jet6pt;}

   gen_jet1_pt = genjet1_pt;
   gen_jet2_pt = genjet2_pt;
   gen_jet3_pt = genjet3_pt;
   gen_jet4_pt = genjet4_pt;
   gen_jet5_pt = genjet5_pt;
   gen_jet6_pt = genjet6_pt;


   for (int i = 0; i<MCGenLeptons.size()-1; i++){
     MCGen_HTall = MCGen_HTall+MCGenLeptons.at(i).Pt();
     if ( MCGenLeptons.at(i).DeltaR(MCGenLeptons.at(i+1)) < MinDeltaR_MCGenLeps ){
       MinDeltaR_MCGenLeps = MCGenLeptons.at(i).DeltaR(MCGenLeptons.at(i+1));
     }
   }
   MinDRMCGenLeps = MinDeltaR_MCGenLeps;

   for (int i = 0; i<MCGenJets.size()-1; i++){
     MCGen_HTall = MCGen_HTall+MCGenJets.at(i).Pt();
     MCGen_HThad = MCGen_HThad+MCGenJets.at(i).Pt();
    if (leading_MCLepton.DeltaR(MCGenJets.at(i)) < MinDeltaR_MCGenLep1Jet){
       MinDeltaR_MCGenLep1Jet = leading_MCLepton.DeltaR(MCGenJets.at(i));
     }
     if (subleading_MCLepton.DeltaR(MCGenJets.at(i)) < MinDeltaR_MCGenLep2Jet){
        MinDeltaR_MCGenLep2Jet = subleading_MCLepton.DeltaR(MCGenJets.at(i));
      }
   }
   MinDRMCGenLep1Jet = MinDeltaR_MCGenLep1Jet;
   MinDrMCGenLep2Jet = MinDeltaR_MCGenLep2Jet;
   MCGenMET = MCGen_MET;
   MCGenHTall = MCGen_HTall;
   MCGenHThad = MCGen_HThad;

   /*MCParticle temp = leading_MCLepton.GetGenMotherNoFsr(leading_MCLepton,genParticles);
   if (MinDeltaR_MCGenLep1Jet<0.04 && temp.PdgId() > 500 && temp.PdgId() < 540){
     cout << "MinDeltaR_MCGenLep1Jet less than 0.05. Mothers PdgId(): " << temp.PdgId() << endl;
   }
   if (MinDeltaR_MCGenLep1Jet>0.04 && temp.PdgId() > 500 && temp.PdgId() < 540){
     cout << "MinDeltaR_MCGenLep1Jet greater than 0.05. Mothers PdgId(): " << temp.PdgId() << endl;
   }*/


    // Fill the variables in event container

    // Fill the branches

  //save variables
  _intVars["nEvent"] = nEvent;
  _intVars["ls"] = ls;
  _intVars["run"] = run;
  _floatVars["n_gen_ele"] = n_gen_ele;
  _floatVars["n_gen_mu"] = n_gen_mu;
  _floatVars["n_gen_lepton"] = n_gen_lepton;
  _floatVars["n_gen_jets"] = n_gen_jets;
  _floatVars["n_gen_bjets"] = n_gen_bjets;
  _floatVars["n_gen_tau"] = n_gen_tau;

  _floatVars["gen_lepton1_pt"] = gen_lepton1_pt;
  _floatVars["gen_lepton2_pt"] = gen_lepton2_pt;
  _floatVars["gen_jet1_pt"] = gen_jet1_pt;
  _floatVars["gen_jet2_pt"] = gen_jet2_pt;
  _floatVars["gen_jet3_pt"] = gen_jet3_pt;
  _floatVars["gen_jet4_pt"] = gen_jet4_pt;
  _floatVars["gen_jet5_pt"] = gen_jet5_pt;
  _floatVars["gen_jet6_pt"] = gen_jet6_pt;
  _floatVars["gen_bjet1_pt"] = gen_bjet1_pt;
  _floatVars["gen_bjet2_pt"] = gen_bjet2_pt;

  _floatVars["MinDRMCGenLeps"] = MinDRMCGenLeps;
  _floatVars["MinDRMCGenLep1Jet"] = MinDRMCGenLep1Jet;
  _floatVars["MinDrMCGenLep2Jet"] = MinDrMCGenLep2Jet;
  _floatVars["MCGenMET"] = MCGenMET;
  _floatVars["MCGenHTall"] = MCGenHTall;
  _floatVars["MCGenHThad"] = MCGenHThad;

  _floatVars["genWeight_muF2"] = genWeight_muF2;
  _floatVars["genWeight_muF0p5"] = genWeight_muF0p5;
  _floatVars["genWeight_muR2"] = genWeight_muR2;
  _floatVars["genWeight_muR0p5"] = genWeight_muR0p5;
  _floatVars["genWeight_muR0p5"] = genWeight_muR0p5;

  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

};
