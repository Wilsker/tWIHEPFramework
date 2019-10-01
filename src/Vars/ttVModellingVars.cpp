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

  _floatVars["genWeight_muR1muF1"] = 999;
  _floatVars["genWeight_muR1muF2"] = 999;
  _floatVars["genWeight_muR1muF0p5"] = 999;
  _floatVars["genWeight_muR2muF1"] = 999;
  _floatVars["genWeight_muR2muF2"] = 999;
  _floatVars["genWeight_muR2muF0p5"] = 999;
  _floatVars["genWeight_muR0p5muF1"] = 999;
  _floatVars["genWeight_muR0p5muF2"] = 999;
  _floatVars["genWeight_muR0p5muF0p5"] = 999;
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

  _floatVars["NBJets"] = 10;
  _floatVars["NJets"] = 10;
  _floatVars["jet1_pt"] = 999.;
  _floatVars["jet2_pt"] = 999.;
  _floatVars["jet3_pt"] = 999.;
  _floatVars["jet4_pt"] = 999.;
  _floatVars["jet5_pt"] = 999.;
  _floatVars["jet6_pt"] = 999.;
  _floatVars["jet7_pt"] = 999.;
  _floatVars["jet8_pt"] = 999.;
  _floatVars["Bjet1_pt"] = 999.;
  _floatVars["Bjet2_pt"] = 999.;

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
    Jets.clear();
    all_jets.clear();
    light_jets.clear();
    b_jets.clear();
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
    NBJets=-9999;
    NJets=-9999;
    jet1_pt=-9999;
    jet2_pt=-9999;
    jet3_pt=-9999;
    jet4_pt=-9999;
    jet5_pt=-9999;
    jet6_pt=-9999;
    jet7_pt=-9999;
    jet8_pt=-9999;
    Bjet1_pt=-9999;
    Bjet2_pt=-9999;
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
    Jets.assign(evtObj -> jets.begin(), evtObj -> jets.end());

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

   int nRecoJets=-9;
   int nRecoBJets=-9;
   double reco_jet1pt =-9;
   double reco_jet2pt =-9;
   double reco_jet3pt =-9;
   double reco_jet4pt =-9;
   double reco_jet5pt =-9;
   double reco_jet6pt =-9;
   double reco_jet7pt =-9;
   double reco_jet8pt =-9;
   double reco_bjet1pt=-9;
   double reco_bjet2pt=-9;


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
   /*
   <weight id="1001"> muR=1 muF=1 </weight>
    <weight id="1002"> muR=1 muF=2 </weight>
    <weight id="1003"> muR=1 muF=0.5 </weight>
    <weight id="1004"> muR=2 muF=1 </weight>
    <weight id="1005"> muR=2 muF=2 </weight>
    <weight id="1006"> muR=2 muF=0.5 </weight>
    <weight id="1007"> muR=0.5 muF=1 </weight>
    <weight id="1008"> muR=0.5 muF=2 </weight>
    <weight id="1009"> muR=0.5 muF=0.5 </weight>*/
   EventTree* tree = evtObj->GetEventTree();
   if(tree->EVENT_genWeights->size()>8){
       genWeight_muR1muF1 = tree->EVENT_genWeights -> operator[](0);
     genWeight_muR1muF2 = tree->EVENT_genWeights -> operator[](1);
     genWeight_muR1muF0p5 = tree->EVENT_genWeights -> operator[](2);
     genWeight_muR2muF1 = tree->EVENT_genWeights -> operator[](3);
     genWeight_muR2muF2 = tree->EVENT_genWeights -> operator[](4);
     genWeight_muR2muF0p5 = tree->EVENT_genWeights -> operator[](5);
     genWeight_muR0p5muF1 = tree->EVENT_genWeights -> operator[](6);
     genWeight_muR0p5muF2 = tree->EVENT_genWeights -> operator[](7);
     genWeight_muR0p5muF0p5 = tree->EVENT_genWeights -> operator[](8);
   }else{
      genWeight_muR1muF1 = tree->EVENT_genWeight;
      genWeight_muR1muF2 = tree->EVENT_genWeight;
      genWeight_muR1muF0p5 = tree->EVENT_genWeight;
      genWeight_muR2muF1 = tree->EVENT_genWeight;
      genWeight_muR2muF2 = tree->EVENT_genWeight;
      genWeight_muR2muF0p5 = tree->EVENT_genWeight;
      genWeight_muR0p5muF1 = tree->EVENT_genWeight;
      genWeight_muR0p5muF2 = tree->EVENT_genWeight;
      genWeight_muR0p5muF0p5 = tree->EVENT_genWeight;
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







   for(uint jet_in=0;jet_in<Jets.size();jet_in++){
     if(Jets.at(jet_in).Pt() >= 25 && abs(Jets.at(jet_in).Eta()) < 2.5){
       cout << "hadronFlavour: " << Jets.at(jet_in).hadronFlavour() << " , Pt: " << Jets.at(jet_in).Pt() << " , Eta: " << abs(Jets.at(jet_in).Eta() << endl;
       all_jets.push_back(Jets.at(jet_in));
     }
   }
   for(uint jet_in=0;jet_in<Jets.size();jet_in++){
     if(Jets.at(jet_in).hadronFlavour() != 5 && Jets.at(jet_in).Pt() >= 25 && abs(Jets.at(jet_in).Eta()) < 2.5){
       light_jets.push_back(Jets.at(jet_in));
     }
   }
   for(uint jet_in=0;jet_in<Jets.size();jet_in++){
     if(Jets.at(jet_in).hadronFlavour() == 5 && Jets.at(jet_in).Pt() >= 25 && abs(Jets.at(jet_in).Eta()) < 2.5){
       b_jets.push_back(Jets.at(jet_in));
     }
   }


   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() > reco_jet1pt) {reco_jet1pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet1pt && all_jets.at(jet_in).Pt() > reco_jet2pt) {reco_jet2pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet2pt && all_jets.at(jet_in).Pt() > reco_jet3pt) {reco_jet3pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet3pt && all_jets.at(jet_in).Pt() > reco_jet4pt) {reco_jet4pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet4pt && all_jets.at(jet_in).Pt() > reco_jet5pt) {reco_jet5pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet5pt && all_jets.at(jet_in).Pt() > reco_jet6pt) {reco_jet6pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet6pt && all_jets.at(jet_in).Pt() > reco_jet7pt) {reco_jet7pt = all_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<all_jets.size();jet_in++){
     if (all_jets.at(jet_in).Pt() < reco_jet7pt && all_jets.at(jet_in).Pt() > reco_jet8pt) {reco_jet8pt = all_jets.at(jet_in).Pt();}
   }

   for (uint jet_in=0;jet_in<b_jets.size();jet_in++){
     if (b_jets.at(jet_in).Pt() > reco_bjet1pt) {reco_bjet1pt = b_jets.at(jet_in).Pt();}
   }
   for (uint jet_in=0;jet_in<b_jets.size();jet_in++){
     if (b_jets.at(jet_in).Pt() < reco_bjet1pt && b_jets.at(jet_in).Pt() > reco_bjet2pt) {reco_bjet2pt = b_jets.at(jet_in).Pt();}
   }

   nRecoJets=all_jets.size();
   nRecoBJets=b_jets.size();

   NJets = nRecoJets;
   jet1_pt = reco_jet1pt;
   jet2_pt= reco_jet2pt;
   jet3_pt= reco_jet3pt;
   jet4_pt= reco_jet4pt;
   jet5_pt= reco_jet5pt;
   jet6_pt= reco_jet6pt;
   jet7_pt= reco_jet7pt;
   jet8_pt= reco_jet8pt;
   NBJets = nRecoBJets;
   Bjet1_pt=reco_bjet1pt;
   Bjet2_pt=reco_bjet2pt;







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

  _floatVars["genWeight_muR1muF1"] = genWeight_muR1muF1;
  _floatVars["genWeight_muR1muF2"] = genWeight_muR1muF2;
  _floatVars["genWeight_muR1muF0p5"] = genWeight_muR1muF0p5;
  _floatVars["genWeight_muR2muF1"] = genWeight_muR2muF1;
  _floatVars["genWeight_muR2muF2"] = genWeight_muR2muF2;
  _floatVars["genWeight_muR2muF0p5"] = genWeight_muR2muF0p5;
  _floatVars["genWeight_muR0p5muF1"] = genWeight_muR0p5muF1;
  _floatVars["genWeight_muR0p5muF2"] = genWeight_muR0p5muF2;
  _floatVars["genWeight_muR0p5muF0p5"] = genWeight_muR0p5muF0p5;

  _floatVars["NBJets"]=NBJets;
  _floatVars["NJets"]=NJets;
  _floatVars["jet1_pt"]=jet1_pt;
  _floatVars["jet2_pt"]=jet2_pt;
  _floatVars["jet3_pt"]=jet3_pt;
  _floatVars["jet4_pt"]=jet4_pt;
  _floatVars["jet5_pt"]=jet5_pt;
  _floatVars["jet6_pt"]=jet6_pt;
  _floatVars["jet7_pt"]=jet7_pt;
  _floatVars["jet8_pt"]=jet8_pt;
  _floatVars["Bjet1_pt"]=Bjet1_pt;
  _floatVars["Bjet2_pt"]=Bjet2_pt;



  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

};
