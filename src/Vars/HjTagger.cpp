/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      12 Dec 2017 - Created by B. Li.
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/HjTagger.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
HjTagger::HjTagger(bool makeHistos){

  SetName("HjTagger");

  _doubleVecs["Jet25_qg"] = {-0.1,100};
  _doubleVecs["Jet25_axis2"] = {-0.1,100};
  _doubleVecs["Jet25_bDiscriminator"] = {-0.1,100};
  _doubleVecs["Jet25_HjBDT"] = {-0.1,100};
  _doubleVecs["Jet25_isFromLepTop"] = {-0.1,100};
  _doubleVecs["Jet25_isLooseBdisc"] = {-0.1,100};
  _doubleVecs["Jet25_isMediumBdisc"] = {-0.1,100};
  _doubleVecs["Jet25_isTightBdisc"] = {-0.1,100};
  _doubleVecs["Jet25_ptD"] = {-0.1,100};
  _doubleVecs["Jet25_mult"] = {-0.1,100};
  _doubleVecs["Jet25_pfCombinedCvsLJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfCombinedCvsBJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfCombinedInclusiveSecondaryVertexV2BJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfCombinedMVAV2BJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfJetProbabilityBJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfDeepCSVCvsLJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfDeepCSVCvsBJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pfDeepFlavourBJetTags"] = {-0.1,100};
  _doubleVecs["Jet25_pt"] = {-0.1,100};
  _doubleVecs["Jet25_eta"] = {-0.1,100};
  _doubleVecs["Jet25_phi"] = {-0.1,100};
  _doubleVecs["Jet25_energy"] = {-0.1,100};
  _doubleVecs["Jet25_px"] = {-0.1,100};
  _doubleVecs["Jet25_py"] = {-0.1,100};
  _doubleVecs["Jet25_pz"] = {-0.1,100};
  _doubleVecs["Jet25_mass"] = {-0.1,100};
  _doubleVecs["Jet25_isFromH"] = {-0.1,100};
  _doubleVecs["Jet25_isFromTop"] = {-0.1,100};
  _doubleVecs["Jet25_matchId"] = {-0.1,100};
  _doubleVecs["Jet25_matchIndex"] = {-0.1,100};
  _doubleVecs["Jet25_neutralHadEnergyFraction"] = {-0.1,100};
  _doubleVecs["Jet25_chargedHadronEnergyFraction"] = {-0.1,100};
  _doubleVecs["Jet25_chargedEmEnergyFraction"] = {-0.1,100};
  _doubleVecs["Jet25_muonEnergyFraction"] = {-0.1,100};
  _doubleVecs["Jet25_electronEnergy"] = {-0.1,100};
  _doubleVecs["Jet25_photonEnergy"] = {-0.1,100};
  _doubleVecs["Jet25_numberOfConstituents"] = {-0.1,100};
  _doubleVecs["Jet25_chargedMultiplicity"] = {-0.1,100};
  _doubleVecs["Jet25_metptratio"] = {-0.1,100};
  _doubleVecs["Jet25_dilepmetptratio"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdr"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdilepdr"] = {-0.1,100};
  _doubleVecs["Jet25_lepdrmin"] = {-0.1,100};
  _doubleVecs["Jet25_lepdrmax"] = {-0.1,100};
  _doubleVecs["Jet25_dilepdr"] = {-0.1,100};
  _doubleVecs["Jet25_bjdr"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdeta"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdilepdeta"] = {-0.1,100};
  _doubleVecs["Jet25_lepdetamin"] = {-0.1,100};
  _doubleVecs["Jet25_lepdetamax"] = {-0.1,100};
  _doubleVecs["Jet25_dilepdeta"] = {-0.1,100};
  _doubleVecs["Jet25_bjdeta"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdphi"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdilepdphi"] = {-0.1,100};
  _doubleVecs["Jet25_lepdphimin"] = {-0.1,100};
  _doubleVecs["Jet25_lepdphimax"] = {-0.1,100};
  _doubleVecs["Jet25_dilepdphi"] = {-0.1,100};
  _doubleVecs["Jet25_bjdphi"] = {-0.1,100};
  _doubleVecs["Jet25_nonjptratio"] = {-0.1,100};
  _doubleVecs["Jet25_nonjdilepptratio"] = {-0.1,100};
  _doubleVecs["Jet25_lepptratiomin"] = {-0.1,100};
  _doubleVecs["Jet25_lepptratiomax"] = {-0.1,100};
  _doubleVecs["Jet25_dilepptratio"] = {-0.1,100};
  _doubleVecs["Jet25_bjptratio"] = {-0.1,100};

  _doubleVecs["FakeLep_isFromB"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromC"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromH"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromZ"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromW"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_isFromTop"] = {-0.1, 1.9 }; 
  _doubleVecs["FakeLep_matchId"] = {-25., 25. }; 
  _doubleVecs["FakeLep_PdgId"] = {-25., 25. }; 
  _doubleVecs["FakeLep_matchIndex"] = {-0.1, 9999. }; 
  _doubleVecs["FakeLep_pt"] = {-0.1, 999. }; 
  _doubleVecs["FakeLep_eta"] = {0, 9.9 }; 
  _doubleVecs["FakeLep_phi"] = {-5., 5. }; 
  _doubleVecs["FakeLep_energy"] = {-0.1, 999. }; 
  _doubleVecs["FakeLep_corrpt"] = {-0.1,100};
  _doubleVecs["FakeLep_ismvasel"] = {-0.1,100};
  _doubleVecs["FakeLep_charge"] = {-0.1,100};
  _doubleVecs["FakeLep_mvaId"] = {-0.1,100};
  _doubleVecs["FakeLep_minIso"] = {-0.1,100};
  _doubleVecs["FakeLep_minIsoCh"] = {-0.1,100};
  _doubleVecs["FakeLep_minIsoNeu"] = {-0.1,100};
  _doubleVecs["FakeLep_ptratio"] = {-0.1,100};
  _doubleVecs["FakeLep_ptrel"] = {-0.1,100};
  _doubleVecs["FakeLep_sig3d"] = {-0.1,100};
  _doubleVecs["FakeLep_segment"] = {-0.1,100};
  _doubleVecs["FakeLep_lostHits"] = {-0.1,100};
  _doubleVecs["FakeLep_relIso04"] = {-0.1,100};
  _doubleVecs["FakeLep_relIsoRhoEA"] = {-0.1,100};
  _doubleVecs["FakeLep_TightCharge"] = {-0.1,100};
  _doubleVecs["FakeLep_passConv"] = {-0.1,100};
  _doubleVecs["FakeLep_jetdr"] = {-0.1,100};
  _doubleVecs["FakeLep_jetCSV"] = {-0.1,100};
  _doubleVecs["FakeLep_dxyAbs"] = {-0.1,100};
  _doubleVecs["FakeLep_dz"] = {-0.1,100};
  _doubleVecs["FakeLep_leptonMVA"] = {-0.1,100};
  _doubleVecs["FakeLep_jetNDauChargedMVASel"] = {-0.1,100};

  SetDoHists(makeHistos);

}

void HjTagger::Clear(){
    fakeLeptons.clear();
    Jets.clear();
    FakeLep_isFromB.clear();
    FakeLep_isFromC.clear();
    FakeLep_isFromH.clear();
    FakeLep_isFromZ.clear();
    FakeLep_isFromW.clear();
    FakeLep_isFromTop.clear();
    FakeLep_PdgId.clear();
    FakeLep_matchId.clear();
    FakeLep_matchIndex.clear();
    FakeLep_pt.clear();
    FakeLep_eta.clear();
    FakeLep_phi.clear();
    FakeLep_energy.clear();
    FakeLep_corrpt.clear();
    FakeLep_ismvasel.clear();
    FakeLep_charge.clear();
    FakeLep_mvaId.clear();
    FakeLep_minIso.clear();
    FakeLep_minIsoCh.clear();
    FakeLep_minIsoNeu.clear();
    FakeLep_ptratio.clear();
    FakeLep_ptrel.clear();
    FakeLep_sig3d.clear();
    FakeLep_segment.clear();
    FakeLep_lostHits.clear();
    FakeLep_relIso04.clear();
    FakeLep_relIsoRhoEA.clear();
    FakeLep_TightCharge.clear();
    FakeLep_passConv.clear();
    FakeLep_jetdr.clear();
    FakeLep_jetCSV.clear();
    FakeLep_dxyAbs.clear();
    FakeLep_dz.clear();
    FakeLep_leptonMVA.clear();
    FakeLep_jetNDauChargedMVASel.clear();
    Jet25_axis2.clear();
    Jet25_bDiscriminator.clear();
    Jet25_HjBDT.clear();
    Jet25_isFromLepTop.clear();
    Jet25_isLooseBdisc.clear();
    Jet25_isMediumBdisc.clear();
    Jet25_isTightBdisc.clear();
    Jet25_qg.clear();
    Jet25_ptD.clear();
    Jet25_mult.clear();
    Jet25_pfCombinedCvsLJetTags.clear();
    Jet25_pfCombinedCvsBJetTags.clear();
    Jet25_pfCombinedInclusiveSecondaryVertexV2BJetTags.clear();
    Jet25_pfCombinedMVAV2BJetTags.clear();
    Jet25_pfJetProbabilityBJetTags.clear();
    Jet25_pfDeepCSVCvsLJetTags.clear();
    Jet25_pfDeepCSVCvsBJetTags.clear();
    Jet25_pfDeepFlavourBJetTags.clear();
    Jet25_pt.clear();
    Jet25_eta.clear();
    Jet25_phi.clear();
    Jet25_energy.clear();
    Jet25_px.clear();
    Jet25_py.clear();
    Jet25_pz.clear();
    Jet25_mass.clear();
    Jet25_isFromH.clear();
    Jet25_isFromTop.clear();
    Jet25_matchId.clear();
    Jet25_matchIndex.clear();
    Jet25_neutralHadEnergyFraction.clear();
    Jet25_chargedHadronEnergyFraction.clear();
    Jet25_chargedEmEnergyFraction.clear();
    Jet25_muonEnergyFraction.clear();
    Jet25_electronEnergy.clear();
    Jet25_photonEnergy.clear();
    Jet25_numberOfConstituents.clear();
    Jet25_chargedMultiplicity.clear();
    Jet25_metptratio.clear();
    Jet25_dilepmetptratio.clear();
    Jet25_nonjdr.clear();
    Jet25_nonjdilepdr.clear();
    Jet25_lepdrmin.clear();
    Jet25_lepdrmax.clear();
    Jet25_dilepdr.clear();
    Jet25_bjdr.clear();
    Jet25_nonjdeta.clear();
    Jet25_nonjdilepdeta.clear();
    Jet25_lepdetamin.clear();
    Jet25_lepdetamax.clear();
    Jet25_dilepdeta.clear();
    Jet25_bjdeta.clear();
    Jet25_nonjdphi.clear();
    Jet25_nonjdilepdphi.clear();
    Jet25_lepdphimin.clear();
    Jet25_lepdphimax.clear();
    Jet25_dilepdphi.clear();
    Jet25_bjdphi.clear();
    Jet25_nonjptratio.clear();
    Jet25_nonjdilepptratio.clear();
    Jet25_lepptratiomin.clear();
    Jet25_lepptratiomax.clear();
    Jet25_dilepptratio.clear();
    Jet25_bjptratio.clear();
}

void HjTagger::FillBranches(EventContainer * evtObj){

    //Initialise vectors;
    Clear();
    
    fakeLeptons.assign(evtObj -> fakeLeptons.begin(), evtObj -> fakeLeptons.end());
    Jets.assign(evtObj -> jets.begin(), evtObj -> jets.end());
 
    if(Jets.size()<1 ) return; 
    
    Jet bJet;
    double bTag = -9999;
    for(auto jet: Jets){
        if(jet.bDiscriminator() > bTag ){
         bTag = jet.bDiscriminator();
         bJet = jet;
        }
    }

    Lepton FirstLepton, SecondLepton;
    
    TLorentzVector MET = evtObj -> missingEtVec;
    TLorentzVector BJetVec = {0,0,0,0};
    BJetVec.SetPtEtaPhiE(bJet.Pt(),bJet.Eta(),bJet.Phi(),bJet.E());

    Jet25_isFromH.assign(evtObj -> Jet25_isFromH.begin(), evtObj -> Jet25_isFromH.end());
    Jet25_isFromTop.assign(evtObj -> Jet25_isFromTop.begin(), evtObj -> Jet25_isFromTop.end());
    Jet25_matchId.assign(evtObj -> Jet25_matchId.begin(), evtObj -> Jet25_matchId.end());
    Jet25_matchIndex.assign(evtObj -> Jet25_matchIndex.begin(), evtObj -> Jet25_matchIndex.end());
    for(auto jet: Jets){
      TLorentzVector CurrentJet = {0,0,0,0};
      CurrentJet.SetPtEtaPhiE(jet.Pt(),jet.Eta(),jet.Phi(),jet.E());
      TLorentzVector Lepmin = {0,0,0,0};
      TLorentzVector Lepmax = {0,0,0,0};
      TLorentzVector DiLep = {0,0,0,0};
      TLorentzVector NonJetVec = {0,0,0,0};
      int isFromLepTop = -999;
      if(fakeLeptons.size()==1){
          FirstLepton = fakeLeptons.at(0);
          Lepmin.SetPtEtaPhiE(FirstLepton.conept(),FirstLepton.Eta(),FirstLepton.Phi(),FirstLepton.E());
          Lepmax = Lepmin;
      }else if(fakeLeptons.size()>=2){
          FirstLepton = fakeLeptons.at(0);
          SecondLepton = fakeLeptons.at(1);
          if(jet.DeltaR(FirstLepton) < jet.DeltaR(SecondLepton)){
            Lepmin.SetPtEtaPhiE(FirstLepton.conept(),FirstLepton.Eta(),FirstLepton.Phi(),FirstLepton.E());
            Lepmax.SetPtEtaPhiE(SecondLepton.conept(),SecondLepton.Eta(),SecondLepton.Phi(),SecondLepton.E());
          }else{
            Lepmin.SetPtEtaPhiE(SecondLepton.conept(),SecondLepton.Eta(),SecondLepton.Phi(),SecondLepton.E());
            Lepmax.SetPtEtaPhiE(FirstLepton.conept(),FirstLepton.Eta(),FirstLepton.Phi(),FirstLepton.E());
          }
          DiLep = Lepmin + Lepmax;
      }
      Jet NonJet;
      double mindr = 9999;
      for(auto njet : Jets){
          if(njet.Pt()==jet.Pt())continue;
          if(jet.DeltaR(njet)<mindr ){
            mindr = jet.DeltaR(njet);
            NonJet = njet;
          }
      }
      NonJetVec.SetPtEtaPhiE(NonJet.Pt(),NonJet.Eta(),NonJet.Phi(),NonJet.E());
     
      // check whether is jets coming from a leptonically decayed top
      if(jet.isFromTop()==1){
        Lepton lepFromTop;
        if(FirstLepton.isFromTop() ==1)lepFromTop=FirstLepton;
        else if(SecondLepton.isFromTop() ==1)lepFromTop=SecondLepton;
        // using charge information 
        if( (jet.matchId() * lepFromTop.matchId()) <0 && abs(jet.matchId())>=5) isFromLepTop =1;
        else isFromLepTop =0;
      }
      
      Jet25_axis2.push_back(jet.axis2());
      Jet25_bDiscriminator.push_back(jet.bDiscriminator());
      Jet25_HjBDT.push_back(jet.HjDisc());
      Jet25_isLooseBdisc.push_back(jet.isLooseBdisc());
      Jet25_isMediumBdisc.push_back(jet.isMediumBdisc());
      Jet25_isTightBdisc.push_back(jet.isTightBdisc());
      Jet25_isFromLepTop.push_back(isFromLepTop);
      Jet25_qg.push_back(jet.qg());
      Jet25_ptD.push_back(jet.ptD());
      Jet25_mult.push_back(jet.mult());
      Jet25_pfCombinedCvsLJetTags.push_back(jet.pfCombinedCvsLJetTags());
      Jet25_pfCombinedCvsBJetTags.push_back(jet.pfCombinedCvsBJetTags());
      Jet25_pfCombinedInclusiveSecondaryVertexV2BJetTags.push_back(jet.pfCombinedInclusiveSecondaryVertexV2BJetTags());
      Jet25_pfCombinedMVAV2BJetTags.push_back(jet.pfCombinedMVAV2BJetTags());
      Jet25_pfJetProbabilityBJetTags.push_back(jet.pfJetProbabilityBJetTags());
      Jet25_pfDeepCSVCvsLJetTags.push_back(jet.pfDeepCSVCvsLJetTags());
      Jet25_pfDeepCSVCvsBJetTags.push_back(jet.pfDeepCSVCvsBJetTags());
      Jet25_pfDeepFlavourBJetTags.push_back(jet.pfDeepFlavourBJetTags());
      Jet25_pt.push_back(jet.Pt());
      Jet25_eta.push_back(jet.Eta());
      Jet25_phi.push_back(jet.Phi());
      Jet25_energy.push_back(jet.E());
      Jet25_px.push_back(jet.Px());
      Jet25_py.push_back(jet.Py());
      Jet25_pz.push_back(jet.Pz());
      Jet25_mass.push_back(jet.M());
      Jet25_neutralHadEnergyFraction.push_back(jet.neutralHadEnergyFraction());
      Jet25_chargedHadronEnergyFraction.push_back(jet.chargedHadronEnergyFraction());
      Jet25_chargedEmEnergyFraction.push_back(jet.chargedEmEnergyFraction());
      Jet25_muonEnergyFraction.push_back(jet.muonEnergyFraction());
      Jet25_electronEnergy.push_back(jet.electronEnergy());
      Jet25_photonEnergy.push_back(jet.photonEnergy());
      Jet25_numberOfConstituents.push_back(jet.numberOfConstituents());
      Jet25_chargedMultiplicity.push_back(jet.chargedMultiplicity());
      
      Jet25_metptratio.push_back(MET.Pt()/jet.Pt());
      float ptratio(-999), dr(-999), dphi(-999),deta(-999);
      TLorentzVector DiLepMET= DiLep+MET;  
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, DiLepMET);
      Jet25_dilepmetptratio.push_back(ptratio);
      
      TLorentzVector DiLepNonJet= DiLep+NonJetVec;  
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, DiLepNonJet);
      Jet25_nonjdilepdr.push_back(dr);
      Jet25_nonjdilepdeta.push_back(deta);
      Jet25_nonjdilepdphi.push_back(dphi);
      Jet25_nonjdilepptratio.push_back(ptratio);
      
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, NonJetVec);
      Jet25_nonjdr.push_back(dr);
      Jet25_nonjdeta.push_back(deta);
      Jet25_nonjdphi.push_back(dphi);
      Jet25_nonjptratio.push_back(ptratio);
      
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, Lepmin);
      Jet25_lepdrmin.push_back(dr);
      Jet25_lepdetamin.push_back(deta);
      Jet25_lepdphimin.push_back(dphi);
      Jet25_lepptratiomin.push_back(ptratio);
      
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, Lepmax);
      Jet25_lepdrmax.push_back(dr);
      Jet25_lepdetamax.push_back(deta);
      Jet25_lepdphimax.push_back(dphi);
      Jet25_lepptratiomax.push_back(ptratio);
      
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, BJetVec);
      Jet25_bjdr.push_back(dr);
      Jet25_bjdeta.push_back(deta);
      Jet25_bjdphi.push_back(dphi);
      Jet25_bjptratio.push_back(ptratio);
      
      std::tie(ptratio,dr,dphi,deta) = getRelKinAndGeo(CurrentJet, DiLep);
      Jet25_dilepdr.push_back(dr);
      Jet25_dilepdeta.push_back(deta);
      Jet25_dilepdphi.push_back(dphi);
      Jet25_dilepptratio.push_back(ptratio);
    }
    
    
    FakeLep_isFromB.assign(evtObj -> FakeLep_isFromB.begin(), evtObj -> FakeLep_isFromB.end());
    FakeLep_isFromC.assign(evtObj -> FakeLep_isFromC.begin(), evtObj -> FakeLep_isFromC.end());
    FakeLep_isFromH.assign(evtObj -> FakeLep_isFromH.begin(), evtObj -> FakeLep_isFromH.end());
    FakeLep_isFromZ.assign(evtObj -> FakeLep_isFromZ.begin(), evtObj -> FakeLep_isFromZ.end());
    FakeLep_isFromW.assign(evtObj -> FakeLep_isFromW.begin(), evtObj -> FakeLep_isFromW.end());
    FakeLep_isFromTop.assign(evtObj -> FakeLep_isFromTop.begin(), evtObj -> FakeLep_isFromTop.end());
    FakeLep_matchId.assign(evtObj -> FakeLep_matchId.begin(), evtObj -> FakeLep_matchId.end());
    FakeLep_matchIndex.assign(evtObj -> FakeLep_matchIndex.begin(), evtObj -> FakeLep_matchIndex.end());
    FakeLep_pt.assign(evtObj -> FakeLep_pt.begin(), evtObj -> FakeLep_pt.end());
    FakeLep_eta.assign(evtObj -> FakeLep_eta.begin(), evtObj -> FakeLep_eta.end());
    FakeLep_phi.assign(evtObj -> FakeLep_phi.begin(), evtObj -> FakeLep_phi.end());
    FakeLep_energy.assign(evtObj -> FakeLep_energy.begin(), evtObj -> FakeLep_energy.end());
    FakeLep_PdgId.assign(evtObj -> FakeLep_PdgId.begin(), evtObj -> FakeLep_PdgId.end());
    
    for(auto lep: fakeLeptons){
        FakeLep_corrpt.push_back(lep.conept());
        FakeLep_ismvasel.push_back(lep.isMVASel());
        FakeLep_charge.push_back(lep.charge());
        FakeLep_mvaId.push_back(lep.ntMVAeleID());
        FakeLep_minIso.push_back(lep.miniIsoRel());
        FakeLep_minIsoCh.push_back(lep.miniIsoCh());
        FakeLep_minIsoNeu.push_back(lep.miniIsoPUsub());
        FakeLep_ptratio.push_back(lep.jetptratioV2());
        FakeLep_ptrel.push_back(lep.ptrel());
        FakeLep_sig3d.push_back(lep.IP3Dsig());
        FakeLep_segment.push_back(lep.segmentCompatibility());
        FakeLep_lostHits.push_back(lep.expectedMissingInnerHits());
        FakeLep_relIso04.push_back(lep.relIsoR04());
        FakeLep_relIsoRhoEA.push_back(lep.relIsoRhoEA());
        FakeLep_TightCharge.push_back(lep.passTightCharge());
        FakeLep_passConv.push_back(lep.passConversionVeto());
        FakeLep_jetdr.push_back(-999);
        FakeLep_jetCSV.push_back(lep.jetdeepcsv());
        FakeLep_dxyAbs.push_back(TMath::Abs(lep.dxy()));
        FakeLep_dz.push_back(lep.dz());
        FakeLep_leptonMVA.push_back(lep.BDT());
        FakeLep_jetNDauChargedMVASel.push_back(lep.lepjetchtrks());
    }
    // Fill the variables in event container

    // Fill the branches
    
    _doubleVecs["FakeLep_isFromB"] = FakeLep_isFromB; 
    _doubleVecs["FakeLep_isFromC"] = FakeLep_isFromC; 
    _doubleVecs["FakeLep_isFromH"] = FakeLep_isFromH; 
    _doubleVecs["FakeLep_isFromZ"] = FakeLep_isFromZ; 
    _doubleVecs["FakeLep_isFromW"] = FakeLep_isFromW; 
    _doubleVecs["FakeLep_isFromTop"] = FakeLep_isFromTop; 
    _doubleVecs["FakeLep_PdgId"] = FakeLep_PdgId; 
    _doubleVecs["FakeLep_matchId"] = FakeLep_matchId; 
    _doubleVecs["FakeLep_matchIndex"] = FakeLep_matchIndex; 
    _doubleVecs["FakeLep_pt"] = FakeLep_pt; 
    _doubleVecs["FakeLep_eta"] = FakeLep_eta; 
    _doubleVecs["FakeLep_phi"] = FakeLep_phi; 
    _doubleVecs["FakeLep_energy"] = FakeLep_energy; 
    _doubleVecs["FakeLep_corrpt"] = FakeLep_corrpt;
    _doubleVecs["FakeLep_ismvasel"] = FakeLep_ismvasel;
    _doubleVecs["FakeLep_charge"] = FakeLep_charge;
    _doubleVecs["FakeLep_mvaId"] = FakeLep_mvaId;
    _doubleVecs["FakeLep_minIso"] = FakeLep_minIso;
    _doubleVecs["FakeLep_minIsoCh"] = FakeLep_minIsoCh;
    _doubleVecs["FakeLep_minIsoNeu"] = FakeLep_minIsoNeu;
    _doubleVecs["FakeLep_ptratio"] = FakeLep_ptratio;
    _doubleVecs["FakeLep_ptrel"] = FakeLep_ptrel;
    _doubleVecs["FakeLep_sig3d"] = FakeLep_sig3d;
    _doubleVecs["FakeLep_segment"] = FakeLep_segment;
    _doubleVecs["FakeLep_lostHits"] = FakeLep_lostHits;
    _doubleVecs["FakeLep_relIso04"] = FakeLep_relIso04;
    _doubleVecs["FakeLep_relIsoRhoEA"] = FakeLep_relIsoRhoEA;
    _doubleVecs["FakeLep_TightCharge"] = FakeLep_TightCharge;
    _doubleVecs["FakeLep_passConv"] = FakeLep_passConv;
    _doubleVecs["FakeLep_jetdr"] = FakeLep_jetdr;
    _doubleVecs["FakeLep_jetCSV"] = FakeLep_jetCSV;
    _doubleVecs["FakeLep_dxyAbs"] = FakeLep_dxyAbs;
    _doubleVecs["FakeLep_dz"] = FakeLep_dz;
    _doubleVecs["FakeLep_leptonMVA"] = FakeLep_leptonMVA;
    _doubleVecs["FakeLep_jetNDauChargedMVASel"] = FakeLep_jetNDauChargedMVASel;
    
    _doubleVecs["Jet25_axis2"] = Jet25_axis2;
    _doubleVecs["Jet25_bDiscriminator"] = Jet25_bDiscriminator;
    _doubleVecs["Jet25_HjBDT"] = Jet25_HjBDT;
    _doubleVecs["Jet25_isFromLepTop"] = Jet25_isFromLepTop;
    _doubleVecs["Jet25_isLooseBdisc"] = Jet25_isLooseBdisc;
    _doubleVecs["Jet25_isMediumBdisc"] = Jet25_isMediumBdisc;
    _doubleVecs["Jet25_isTightBdisc"] = Jet25_isTightBdisc;
    _doubleVecs["Jet25_qg"] = Jet25_qg;
    _doubleVecs["Jet25_ptD"] = Jet25_ptD;
    _doubleVecs["Jet25_mult"] = Jet25_mult;
    _doubleVecs["Jet25_pfCombinedCvsLJetTags"] = Jet25_pfCombinedCvsLJetTags;
    _doubleVecs["Jet25_pfCombinedCvsBJetTags"] = Jet25_pfCombinedCvsBJetTags;
    _doubleVecs["Jet25_pfCombinedInclusiveSecondaryVertexV2BJetTags"] = Jet25_pfCombinedInclusiveSecondaryVertexV2BJetTags;
    _doubleVecs["Jet25_pfCombinedMVAV2BJetTags"] = Jet25_pfCombinedMVAV2BJetTags;
    _doubleVecs["Jet25_pfJetProbabilityBJetTags"] = Jet25_pfJetProbabilityBJetTags;
    _doubleVecs["Jet25_pfDeepCSVCvsLJetTags"] = Jet25_pfDeepCSVCvsLJetTags;
    _doubleVecs["Jet25_pfDeepCSVCvsBJetTags"] = Jet25_pfDeepCSVCvsBJetTags;
    _doubleVecs["Jet25_pfDeepFlavourBJetTags"] = Jet25_pfDeepFlavourBJetTags;
    _doubleVecs["Jet25_pt"] = Jet25_pt;
    _doubleVecs["Jet25_eta"] = Jet25_eta;
    _doubleVecs["Jet25_phi"] = Jet25_phi;
    _doubleVecs["Jet25_energy"] = Jet25_energy;
    _doubleVecs["Jet25_px"] = Jet25_px;
    _doubleVecs["Jet25_py"] = Jet25_py;
    _doubleVecs["Jet25_pz"] = Jet25_pz;
    _doubleVecs["Jet25_mass"] = Jet25_mass;
    _doubleVecs["Jet25_isFromH"] = Jet25_isFromH;
    _doubleVecs["Jet25_isFromTop"] = Jet25_isFromTop;
    _doubleVecs["Jet25_matchId"] = Jet25_matchId;
    _doubleVecs["Jet25_matchIndex"] = Jet25_matchIndex;
    _doubleVecs["Jet25_neutralHadEnergyFraction"] = Jet25_neutralHadEnergyFraction;
    _doubleVecs["Jet25_chargedHadronEnergyFraction"] = Jet25_chargedHadronEnergyFraction;
    _doubleVecs["Jet25_chargedEmEnergyFraction"] = Jet25_chargedEmEnergyFraction;
    _doubleVecs["Jet25_muonEnergyFraction"] = Jet25_muonEnergyFraction;
    _doubleVecs["Jet25_electronEnergy"] = Jet25_electronEnergy;
    _doubleVecs["Jet25_photonEnergy"] = Jet25_photonEnergy;
    _doubleVecs["Jet25_numberOfConstituents"] = Jet25_numberOfConstituents;
    _doubleVecs["Jet25_chargedMultiplicity"] = Jet25_chargedMultiplicity;
    _doubleVecs["Jet25_metptratio"] = Jet25_metptratio;
    _doubleVecs["Jet25_dilepmetptratio"] = Jet25_dilepmetptratio;
    _doubleVecs["Jet25_nonjdr"] = Jet25_nonjdr;
    _doubleVecs["Jet25_nonjdilepdr"] = Jet25_nonjdilepdr;
    _doubleVecs["Jet25_lepdrmin"] = Jet25_lepdrmin;
    _doubleVecs["Jet25_lepdrmax"] = Jet25_lepdrmax;
    _doubleVecs["Jet25_dilepdr"] = Jet25_dilepdr;
    _doubleVecs["Jet25_bjdr"] = Jet25_bjdr;
    _doubleVecs["Jet25_nonjdeta"] = Jet25_nonjdeta;
    _doubleVecs["Jet25_nonjdilepdeta"] = Jet25_nonjdilepdeta;
    _doubleVecs["Jet25_lepdetamin"] = Jet25_lepdetamin;
    _doubleVecs["Jet25_lepdetamax"] = Jet25_lepdetamax;
    _doubleVecs["Jet25_dilepdeta"] = Jet25_dilepdeta;
    _doubleVecs["Jet25_bjdeta"] = Jet25_bjdeta;
    _doubleVecs["Jet25_nonjdphi"] = Jet25_nonjdphi;
    _doubleVecs["Jet25_nonjdilepdphi"] = Jet25_nonjdilepdphi;
    _doubleVecs["Jet25_lepdphimin"] = Jet25_lepdphimin;
    _doubleVecs["Jet25_lepdphimax"] = Jet25_lepdphimax;
    _doubleVecs["Jet25_dilepdphi"] = Jet25_dilepdphi;
    _doubleVecs["Jet25_bjdphi"] = Jet25_bjdphi;
    _doubleVecs["Jet25_nonjptratio"] = Jet25_nonjptratio;
    _doubleVecs["Jet25_nonjdilepptratio"] = Jet25_nonjdilepptratio;
    _doubleVecs["Jet25_lepptratiomin"] = Jet25_lepptratiomin;
    _doubleVecs["Jet25_lepptratiomax"] = Jet25_lepptratiomax;
    _doubleVecs["Jet25_dilepptratio"] = Jet25_dilepptratio;
    _doubleVecs["Jet25_bjptratio"] = Jet25_bjptratio;
    
    if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

// utils

std::tuple<Float_t,Float_t,Float_t,Float_t> HjTagger::getRelKinAndGeo(TLorentzVector currJet, TLorentzVector currPart){
  Float_t ptRatio = -999, dR = -999, dPhi = -999, dEta = -999.;
  ptRatio = currPart.Pt()/currJet.Pt();
  dR = currJet.DeltaR(currPart);
  dPhi = currJet.DeltaPhi(currPart);
  dEta = currJet.Eta() - currPart.Eta();
  return std::make_tuple(ptRatio, dR, dPhi, dEta);
}
