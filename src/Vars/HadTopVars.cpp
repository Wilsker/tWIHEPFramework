/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/HadTopVars.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
HadTopVars::HadTopVars(bool makeHistos){

  SetName("HadTopVars");
  
  _intVars["Jet_numLoose"] = 0;
  _intVars["Jet_numbMedium"] = 0;
  
  _floatVars["hadTop_BDT"] = -1.;
 
  _doubleVecs["Jet_isToptag"] = {-0.1, 1.9 }; 

  SetDoHists(makeHistos);

}

void HadTopVars::Clear(){
  Jet_isToptag.clear();
  Jet_null_pt.clear();
  Jet_null_eta.clear();
  Jet_null_phi.clear();
  Jet_null_energy.clear();
  Jet_null_csv.clear();
  Jet_numLoose =-999;
  Jet_numbMedium =-999;
  bjet_lepTop_index= 999;
  bjet_hadTop_index= 999;
  wjet1_hadTop_index= 999;
  wjet2_hadTop_index= 999;
  lep_Top_index= 999;
  lep_H_index= 999;
  bjet_lepTop_pt= -999;
  bjet_hadTop_pt= -999;
  wjet1_hadTop_pt= -999;
  wjet2_hadTop_pt= -999;
  lep_Top_pt= -999;
  lep_H_pt= -999;
  bjet_lepTop_eta= -999;
  bjet_hadTop_eta= -999;
  wjet1_hadTop_eta= -999;
  wjet2_hadTop_eta= -999;
  lep_Top_eta= -999;
  lep_H_eta= -999;
  bjet_lepTop_phi= -999;
  bjet_hadTop_phi= -999;
  wjet1_hadTop_phi= -999;
  wjet2_hadTop_phi= -999;
  lep_Top_phi= -999;
  lep_H_phi= -999;
  bjet_lepTop_energy= -999;
  bjet_hadTop_energy= -999;
  wjet1_hadTop_energy= -999;
  wjet2_hadTop_energy= -999;
  lep_Top_energy= -999;
  lep_H_energy= -999;
  bjet_lepTop_csv= -999;
  bjet_hadTop_csv= -999;
  reco_hadTop_pt= -999;
  reco_hadTop_mass= -999;
  reco_WhadTop_mass= -999;
  PtRatio_leptOverleph= -999;
  Dr_lept_bfromlTop= -999;
  Dr_lept_bfromhTop= -999;
  Dr_leph_bfromlTop= -999;
  hadTop_BDT= -999;
}

void HadTopVars::FillBranches(EventContainer * evtObj){

  //Initialise vectors;
  Clear();
  
  _MWPbTagCut = evtObj-> GetConfig() -> GetValue("ObjectID.BJet.MWPBTagCut",0.0);
  
  Jet_numbMedium = Add_nullJet(evtObj->jets);
  Reco_hadTop(evtObj);
  
  _intVars["Jet_numLoose"] = Jet_numLoose;
  _intVars["Jet_numbMedium"] = Jet_numbMedium;
  
  _floatVars["hadTop_BDT"] = hadTop_BDT;

  if(evtObj -> _sync == 51){                                                                      
        std::cout<< evtObj->eventNumber<<" "<< bjet_hadTop_pt << " "<< wjet1_hadTop_pt<<" "<< wjet2_hadTop_pt<<" "<<bjet_hadTop_csv <<" "<< bjet_lepTop_csv << " "<< reco_hadTop_mass<< " "<< reco_hadTop_pt << " " << reco_WhadTop_mass << " " << PtRatio_leptOverleph << " " << Dr_lept_bfromlTop << " "<< Dr_lept_bfromhTop<< " "<<Dr_leph_bfromlTop <<" "<< hadTop_BDT<< endl;
  }                          

  Int_t jet_index=-1;
  for(uint jet_en=0; jet_en< evtObj->jets.size();jet_en++){
    jet_index++;
    Double_t isTagged = 0.;
    if(jet_index == bjet_hadTop_index || jet_index == wjet1_hadTop_index || jet_index == wjet2_hadTop_index)isTagged=1.;
    evtObj->jets.at(jet_en).SetisToptag(isTagged);
    Jet_isToptag.push_back(isTagged);
  }

  _doubleVecs["Jet_isToptag"] = Jet_isToptag; 
  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

/***************************************************************
 * void HadTopVars::Reco_hadTop( )              *
 *                                                              * 
 * Calculate HadTop Tagger                                    *
 *                                                              *
 * Input: selected Leptons and Jets                                    *
 * Output: None                                                *
 * **************************************************************/
void HadTopVars::Reco_hadTop(EventContainer *EvtObj){
 Int_t bjet_lepTop_INDEX= -999;
 Int_t bjet_hadTop_INDEX= -999;
 Int_t wjet1_hadTop_INDEX= -999;
 Int_t wjet2_hadTop_INDEX= -999;
 Int_t lep_Top_INDEX= -999;
 Int_t lep_H_INDEX= -999;
 std::vector<Lepton> selectedLeptons = EvtObj->fakeLeptons;
 TLorentzVector bjet_fromHadTop_tlv={0,0,0,0};
 TLorentzVector bjet_fromLepTop_tlv={0,0,0,0};
 TLorentzVector wjet1_fromHadTop_tlv={0,0,0,0};
 TLorentzVector wjet2_fromHadTop_tlv={0,0,0,0};
 TLorentzVector w_fromHadTop_tlv={0,0,0,0};
 TLorentzVector lep_fromTop_tlv={0,0,0,0};
 TLorentzVector lep_fromHiggs_tlv={0,0,0,0};
 TLorentzVector lepTop_tlv={0,0,0,0};
 TLorentzVector hadTop_tlv={0,0,0,0};
 bjet_hadTop_INDEX = -1;
 for(uint bhad_en=0; bhad_en < Jet_null_pt.size(); bhad_en++){
  bjet_hadTop_INDEX +=1;
  if(bhad_en!=0&& Jet_null_pt.at(bhad_en)==0 && Jet_null_pt.at(bhad_en-1)==0)continue;//skip useless empty b-jet iterations (skip all perms with 2 null bjets)
  //if(Jet_null_pt.at(bhad_en)==0 && Jet_null_pt.at(bhad_en-1)==0)continue;//skip useless empty b-jet iterations (skip all perms with 2 null bjets)
  if(Jet_numbMedium>=2 && Jet_null_csv.at(bhad_en)<0.8)continue;//speed improvement
  if(Jet_null_csv.at(bhad_en)>0 && Jet_null_csv.at(bhad_en)<0.46)continue; //speed improvement
  

  bjet_lepTop_INDEX = -1;
  for(uint blep_en=0; blep_en < Jet_null_pt.size();blep_en++){
   bjet_lepTop_INDEX +=1;
   if(bjet_lepTop_INDEX==bjet_hadTop_INDEX)continue;
   if(Jet_null_pt.at(blep_en)==0 && Jet_null_pt.at(blep_en-1)==0)continue;//skip useless empty b-jet iterations (skip all perms with 2 null bjets)
   if(Jet_numbMedium>=2 && Jet_null_csv.at(blep_en)<0.8)continue;//speed improvement
   if(Jet_null_csv.at(blep_en)>0 && Jet_null_csv.at(blep_en)<0.46)continue; //speed improvement
   if(!((Jet_null_csv.at(blep_en)>0.8||Jet_null_csv.at(bhad_en)>0.8)||(Jet_null_csv.at(blep_en)>0.46 && Jet_null_csv.at(bhad_en)>0.46)))continue;
    
   wjet1_hadTop_INDEX = -1;
   for(uint wjet1_en=0; wjet1_en < Jet_null_pt.size(); wjet1_en++){
    wjet1_hadTop_INDEX += 1;
    if(wjet1_hadTop_INDEX==bjet_lepTop_INDEX)continue;
    if(wjet1_hadTop_INDEX==bjet_hadTop_INDEX)continue;
    
    
    wjet2_hadTop_INDEX = -1;
    for(uint wjet2_en=0; wjet2_en < Jet_null_pt.size(); wjet2_en++){
     wjet2_hadTop_INDEX += 1;
     if(wjet2_hadTop_INDEX==bjet_lepTop_INDEX)continue;
     if(wjet2_hadTop_INDEX==bjet_hadTop_INDEX)continue;
     if(wjet2_hadTop_INDEX<=wjet1_hadTop_INDEX)continue;//skip duplicates
     bjet_fromHadTop_tlv.SetPtEtaPhiE(Jet_null_pt.at(bhad_en),Jet_null_eta.at(bhad_en),Jet_null_phi.at(bhad_en),Jet_null_energy.at(bhad_en));
     bjet_fromLepTop_tlv.SetPtEtaPhiE(Jet_null_pt.at(blep_en),Jet_null_eta.at(blep_en),Jet_null_phi.at(blep_en),Jet_null_energy.at(blep_en));
     wjet1_fromHadTop_tlv.SetPtEtaPhiE(Jet_null_pt.at(wjet1_en),Jet_null_eta.at(wjet1_en),Jet_null_phi.at(wjet1_en),Jet_null_energy.at(wjet1_en));
     wjet2_fromHadTop_tlv.SetPtEtaPhiE(Jet_null_pt.at(wjet2_en),Jet_null_eta.at(wjet2_en),Jet_null_phi.at(wjet2_en),Jet_null_energy.at(wjet2_en));
     w_fromHadTop_tlv = wjet1_fromHadTop_tlv + wjet2_fromHadTop_tlv;
     if (w_fromHadTop_tlv.M() > 120 ) continue; 
     hadTop_tlv = w_fromHadTop_tlv + bjet_fromHadTop_tlv;
     if ( hadTop_tlv.M() > 220 ) continue;

     lep_Top_INDEX= -1;
     for(uint ltop_en=0; ltop_en<2; ltop_en++){
      lep_Top_INDEX += 1;
     
      lep_H_INDEX= -1;
      for(uint lhig_en=0; lhig_en<2; lhig_en++){
       lep_H_INDEX += 1;
       if(lep_Top_INDEX==lep_H_INDEX)continue;
       if(selectedLeptons.size()>=2){
        lep_fromTop_tlv.SetPtEtaPhiE(selectedLeptons.at(ltop_en).conept(),selectedLeptons.at(ltop_en).Eta(),selectedLeptons.at(ltop_en).Phi(),selectedLeptons.at(ltop_en).E());
        lep_fromHiggs_tlv.SetPtEtaPhiE(selectedLeptons.at(lhig_en).conept(),selectedLeptons.at(lhig_en).Eta(),selectedLeptons.at(lhig_en).Phi(),selectedLeptons.at(lhig_en).E());
       }else{
        lep_fromTop_tlv.SetPtEtaPhiE(1,1,1,2);//set to 1,1,1,2 to avoid null at denominator
        lep_fromHiggs_tlv.SetPtEtaPhiE(1,1,1,2); // set to 1,1,1,2 to avoid null at denominator
       }
       lepTop_tlv = lep_fromTop_tlv + bjet_fromLepTop_tlv;
       if ( lepTop_tlv.M() > 180 ) continue;
       //calculate all variables       
       EvtObj->varbjet_lepTop_csv = Jet_null_csv.at(blep_en);
       EvtObj->varbjet_hadTop_csv = Jet_null_csv.at(bhad_en);
       EvtObj->varreco_hadTop_pt = hadTop_tlv.Pt();
       EvtObj->varreco_hadTop_mass = hadTop_tlv.M();
       EvtObj->varreco_WhadTop_mass = w_fromHadTop_tlv.M();
       EvtObj->varPtRatio_leptOverleph = lep_fromTop_tlv.Pt()/lep_fromHiggs_tlv.Pt();
       EvtObj->varDr_lept_bfromlTop = bjet_fromLepTop_tlv.Pt()==0 ? -1: lep_fromTop_tlv.DeltaR(bjet_fromLepTop_tlv);
       EvtObj->varDr_lept_bfromhTop = bjet_fromHadTop_tlv.Pt()==0? -1: lep_fromTop_tlv.DeltaR(bjet_fromHadTop_tlv);
       EvtObj->varDr_leph_bfromlTop = bjet_fromLepTop_tlv.Pt()==0? -1: lep_fromHiggs_tlv.DeltaR(bjet_fromLepTop_tlv);
       Float_t mva_value= get_hadTopMVA(Jet_numbMedium, EvtObj);
       if(mva_value > hadTop_BDT){
        hadTop_BDT = mva_value;
        bjet_lepTop_index = bjet_lepTop_INDEX;
        bjet_hadTop_index = bjet_hadTop_INDEX;
        wjet1_hadTop_index = wjet1_hadTop_INDEX;
        wjet2_hadTop_index = wjet2_hadTop_INDEX;
        lep_Top_index = lep_Top_INDEX;
        lep_H_index = lep_H_INDEX;
        bjet_lepTop_pt = bjet_fromLepTop_tlv.Pt();
        bjet_hadTop_pt = bjet_fromHadTop_tlv.Pt();
        wjet1_hadTop_pt = wjet1_fromHadTop_tlv.Pt();
        wjet2_hadTop_pt = wjet2_fromHadTop_tlv.Pt();
        lep_Top_pt = lep_fromTop_tlv.Pt();
        lep_H_pt = lep_fromHiggs_tlv.Pt();
        bjet_lepTop_eta = bjet_fromLepTop_tlv.Eta();
        bjet_hadTop_eta = bjet_fromHadTop_tlv.Eta();
        wjet1_hadTop_eta = wjet1_fromHadTop_tlv.Eta();
        wjet2_hadTop_eta = wjet2_fromHadTop_tlv.Eta();
        lep_Top_eta = lep_fromTop_tlv.Eta();
        lep_H_eta = lep_fromHiggs_tlv.Eta();
        bjet_lepTop_phi = bjet_fromLepTop_tlv.Phi();
        bjet_hadTop_phi = bjet_fromHadTop_tlv.Phi();
        wjet1_hadTop_phi = wjet1_fromHadTop_tlv.Phi();
        wjet2_hadTop_phi = wjet2_fromHadTop_tlv.Phi();
        lep_Top_phi = lep_fromTop_tlv.Phi();
        lep_H_phi = lep_fromHiggs_tlv.Phi();
        bjet_lepTop_energy = bjet_fromLepTop_tlv.E();
        bjet_hadTop_energy = bjet_fromHadTop_tlv.E();
        wjet1_hadTop_energy = wjet1_fromHadTop_tlv.E();
        wjet2_hadTop_energy = wjet2_fromHadTop_tlv.E();
        lep_Top_energy = lep_fromTop_tlv.E();
        lep_H_energy = lep_fromHiggs_tlv.E();
        bjet_lepTop_csv = EvtObj->varbjet_lepTop_csv;
        bjet_hadTop_csv = EvtObj->varbjet_hadTop_csv;
        reco_hadTop_pt = EvtObj->varreco_hadTop_pt;
        reco_hadTop_mass = EvtObj->varreco_hadTop_mass;
        reco_WhadTop_mass = EvtObj->varreco_WhadTop_mass;
        PtRatio_leptOverleph = EvtObj->varPtRatio_leptOverleph;
        Dr_lept_bfromlTop = EvtObj->varDr_lept_bfromlTop;
        Dr_lept_bfromhTop = EvtObj->varDr_lept_bfromhTop;
        Dr_leph_bfromlTop = EvtObj->varDr_leph_bfromlTop;
       }
      }
     }
    }
   }
  }
 }
};

/***************************************************************
 * Int_t  HadTopVars::Add_nullJet(std::vector<Jet>& selectedJets)*
 *                                                              * 
 * Set up the null Jets                                         *
 *                                                              *
 * Input: selected Jets                                         *
 * Output: number of bjet                                                 *
 * **************************************************************/
int HadTopVars::Add_nullJet(std::vector<Jet>& selectedJets){
    Int_t num_bjet =0;
    Jet_numLoose = selectedJets.size();
    for(uint jet_en=0; jet_en<selectedJets.size();jet_en++){
        Jet_null_pt.push_back(selectedJets.at(jet_en).Pt());
        Jet_null_eta.push_back(selectedJets.at(jet_en).Eta());
        Jet_null_phi.push_back(selectedJets.at(jet_en).Phi());
        Jet_null_energy.push_back(selectedJets.at(jet_en).E());
        Jet_null_csv.push_back(selectedJets.at(jet_en).bDiscriminator());
        if(selectedJets.at(jet_en).bDiscriminator() > _MWPbTagCut )num_bjet++;
    }
    if(Jet_numLoose<=7){
        Jet_null_pt.push_back(0);
        Jet_null_eta.push_back(0);
        Jet_null_phi.push_back(0);
        Jet_null_energy.push_back(0);
        Jet_null_csv.push_back(-0.2);

        Jet_null_pt.push_back(0);
        Jet_null_eta.push_back(0);
        Jet_null_phi.push_back(0);
        Jet_null_energy.push_back(0);
        Jet_null_csv.push_back(-0.2);

        Jet_null_pt.push_back(0);
        Jet_null_eta.push_back(0);
        Jet_null_phi.push_back(0);
        Jet_null_energy.push_back(0);
        Jet_null_csv.push_back(-0.2);
    }
    else if(Jet_numLoose==8){
        Jet_null_pt.push_back(0);
        Jet_null_eta.push_back(0);
        Jet_null_phi.push_back(0);
        Jet_null_energy.push_back(0);
        Jet_null_csv.push_back(-0.2);

        Jet_null_pt.push_back(0);
        Jet_null_eta.push_back(0);
        Jet_null_phi.push_back(0);
        Jet_null_energy.push_back(0);
        Jet_null_csv.push_back(-0.2);
    }
    else{
        Jet_null_pt.push_back(0);
        Jet_null_eta.push_back(0);
        Jet_null_phi.push_back(0);
        Jet_null_energy.push_back(0);
        Jet_null_csv.push_back(-0.2);
    }   
    return num_bjet; 
};

/***************************************************************
 * void HadTopVars::get_hadTopMVA(int numbJet)              *
 *                                                              * 
 * Evaluate HadTop MVA                                        *
 *                                                              *
 * Input: number of bjet                                      *
 * Output: BDT value                                                 *
 * **************************************************************/
Float_t HadTopVars::get_hadTopMVA(int numbJet, EventContainer *EvtObj){ 
    Float_t BDToutput=0.;
    if(numbJet<2){
        BDToutput = EvtObj->hadTop_reader_loose->EvaluateMVA("BDTG method");
    }else{
        BDToutput = EvtObj->hadTop_reader_tight->EvaluateMVA("BDTG method");
    }
    return BDToutput; 
}
