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
  
  
  _floatVars["hadTop_BDT"] = -1.;
  _floatVars["hadTop_pt"] = -1.;
  _floatVars["bjet_resTop_index"] = -1.;
  _floatVars["wjet1_resTop_index"] = -1.;
  _floatVars["wjet2_resTop_index"] = -1.;
  _floatVars["hadTop_btagDisc_b"] = -1.;
  _floatVars["hadTop_btagDisc_Wj1"] = -1.;
  _floatVars["hadTop_btagDisc_Wj2"] = -1.;
  _floatVars["hadTop_qg_Wj1"] = -1.;
  _floatVars["hadTop_qg_Wj2"] = -1.;
  _floatVars["hadTop_m_Wj1Wj2_div_m_bWj1Wj2"] = -1.;
  _floatVars["hadTop_pT_Wj1Wj2"] = -1.;
  _floatVars["hadTop_dR_Wj1Wj2"] = -1.;
  _floatVars["hadTop_m_bWj1Wj2"] = -1.;
  _floatVars["hadTop_dR_bW"] = -1.;
  _floatVars["hadTop_m_bWj1"] = -1.;
  _floatVars["hadTop_m_bWj2"] = -1.;
  _floatVars["hadTop_mass_Wj1"] = -1.;
  _floatVars["hadTop_pT_Wj2"] = -1.;
  _floatVars["hadTop_mass_Wj2"] = -1.;
  _floatVars["hadTop_pT_b"] = -1.;
  _floatVars["hadTop_mass_b"] = -1.;
    
 
  _doubleVecs["Jet25_isToptag"] = {-0.1, 1.9 }; 

  SetDoHists(makeHistos);

}

void HadTopVars::Clear(){
  Jet25_isToptag.clear();
  hadTop_BDT= -999;
  hadTop_pt= -999;
  bjet_hadTop_index=-999;
  wjet1_hadTop_index=-999;
  wjet2_hadTop_index=-999;
  hadTop_btagDisc_b=-999;
  hadTop_btagDisc_Wj1=-999;
  hadTop_btagDisc_Wj2=-999;
  hadTop_qg_Wj1=-999;
  hadTop_qg_Wj2=-999;
  hadTop_m_Wj1Wj2_div_m_bWj1Wj2=-999;
  hadTop_pT_Wj1Wj2=-999;
  hadTop_dR_Wj1Wj2=-999;
  hadTop_m_bWj1Wj2=-999;
  hadTop_dR_bW=-999;
  hadTop_m_bWj1=-999;
  hadTop_m_bWj2=-999;
  hadTop_mass_Wj1=-999;
  hadTop_pT_Wj2=-999;
  hadTop_mass_Wj2=-999;
  hadTop_pT_b=-999;
  hadTop_mass_b=-999;
    
}

void HadTopVars::FillBranches(EventContainer * evtObj){

  //Initialise vectors;
  Clear();
  
  Reco_hadTop(evtObj);
  
  _floatVars["hadTop_BDT"] = hadTop_BDT;
  _floatVars["hadTop_pt"] = hadTop_pt;
  _floatVars["bjet_hadTop_index"] = bjet_hadTop_index;
  _floatVars["wjet1_hadTop_index"] = wjet1_hadTop_index;
  _floatVars["wjet2_hadTop_index"] = wjet2_hadTop_index;
  _floatVars["hadTop_btagDisc_b"] = hadTop_btagDisc_b;
  _floatVars["hadTop_btagDisc_Wj1"] = hadTop_btagDisc_Wj1;
  _floatVars["hadTop_btagDisc_Wj2"] = hadTop_btagDisc_Wj2;
  _floatVars["hadTop_qg_Wj1"] = hadTop_qg_Wj1;
  _floatVars["hadTop_qg_Wj2"] = hadTop_qg_Wj2;
  _floatVars["hadTop_m_Wj1Wj2_div_m_bWj1Wj2"] = hadTop_m_Wj1Wj2_div_m_bWj1Wj2;
  _floatVars["hadTop_pT_Wj1Wj2"] = hadTop_pT_Wj1Wj2;
  _floatVars["hadTop_dR_Wj1Wj2"] = hadTop_dR_Wj1Wj2;
  _floatVars["hadTop_m_bWj1Wj2"] = hadTop_m_bWj1Wj2;
  _floatVars["hadTop_dR_bW"] = hadTop_dR_bW;
  _floatVars["hadTop_m_bWj1"] = hadTop_m_bWj1;
  _floatVars["hadTop_m_bWj2"] = hadTop_m_bWj2;
  _floatVars["hadTop_mass_Wj1"] = hadTop_mass_Wj1;
  _floatVars["hadTop_pT_Wj2"] = hadTop_pT_Wj2;
  _floatVars["hadTop_mass_b"] = hadTop_mass_b;

  evtObj->HadTop_BDT = hadTop_BDT;
  if(evtObj -> _sync == 51){                                                                      
    std::cout << " nEvent "<< evtObj->eventNumber << std::endl;
    std::cout << " hadTop_BDT "<< hadTop_BDT << std::endl;
    std::cout << " hadTop_pt "<< hadTop_pt << std::endl;
    std::cout << " bjet_hadTop_index "<< bjet_hadTop_index << std::endl;
    std::cout << " wjet1_hadTop_index "<< wjet1_hadTop_index << std::endl;
    std::cout << " wjet2_hadTop_index "<< wjet2_hadTop_index << std::endl;
    std::cout << " hadTop_btagDisc_b "<< hadTop_btagDisc_b << std::endl;
    std::cout << " hadTop_btagDisc_Wj1 "<< hadTop_btagDisc_Wj1 << std::endl;
    std::cout << " hadTop_btagDisc_Wj2 "<< hadTop_btagDisc_Wj2 << std::endl;
    std::cout << " hadTop_qg_Wj1 "<< hadTop_qg_Wj1 << std::endl;
    std::cout << " hadTop_qg_Wj2 "<< hadTop_qg_Wj2 << std::endl;
    std::cout << " hadTop_m_Wj1Wj2_div_m_bWj1Wj2 "<< hadTop_m_Wj1Wj2_div_m_bWj1Wj2 << std::endl;
    std::cout << " hadTop_pT_Wj1Wj2 "<< hadTop_pT_Wj1Wj2 << std::endl;
    std::cout << " hadTop_dR_Wj1Wj2 "<< hadTop_dR_Wj1Wj2 << std::endl;
    std::cout << " hadTop_m_bWj1Wj2 "<< hadTop_m_bWj1Wj2 << std::endl;
    std::cout << " hadTop_dR_bW "<< hadTop_dR_bW << std::endl;
    std::cout << " hadTop_m_bWj1 "<< hadTop_m_bWj1 << std::endl;
    std::cout << " hadTop_m_bWj2 "<< hadTop_m_bWj2 << std::endl;
    std::cout << " hadTop_mass_Wj1 "<< hadTop_mass_Wj1 << std::endl;
    std::cout << " hadTop_pT_Wj2 "<< hadTop_pT_Wj2 << std::endl;
    std::cout << " hadTop_mass_b "<< hadTop_mass_b << std::endl;
  }                          

  Int_t jet_index=-1;
  for(uint jet_en=0; jet_en< evtObj->jets.size();jet_en++){
    jet_index++;
    Double_t isTagged = 0.;
    if(jet_index == bjet_hadTop_index || jet_index == wjet1_hadTop_index || jet_index == wjet2_hadTop_index)isTagged=1.;
    evtObj->jets.at(jet_en).SetisToptag(isTagged);
    Jet25_isToptag.push_back(isTagged);
  }
  
  _doubleVecs["Jet25_isToptag"] = Jet25_isToptag; 

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
 Int_t bjet_hadTop_INDEX= -999;
 Int_t wjet1_hadTop_INDEX= -999;
 Int_t wjet2_hadTop_INDEX= -999;
 std::vector<Lepton> selectedLeptons = EvtObj->fakeLeptons;
 std::vector<Jet> Jets = EvtObj->jets;
 int njets = Jets.size();
 std::sort(Jets.begin(),Jets.end(),[](const Jet &a, const Jet &b){return a.pfDeepCSVBJetTags() > b.pfDeepCSVBJetTags();});
  for (int i1=0; i1<njets-2; i1++) {
    for (int i2=i1+1; i2<njets-1; i2++){
      for (int i3=i2+1; i3<njets; i3++){
        Jet bjet = Jets.at(i1);
        Jet w1jet = Jets.at(i2);
        Jet w2jet = Jets.at(i3);
        
        EvtObj->var_btagDisc_b = bjet.pfDeepCSVBJetTags();
        EvtObj->var_btagDisc_Wj1 = w1jet.pfDeepCSVBJetTags();
        EvtObj->var_btagDisc_Wj2 = w2jet.pfDeepCSVBJetTags();
        EvtObj->var_qg_Wj1 = w1jet.qg();
        EvtObj->var_qg_Wj2 = w2jet.qg();
        EvtObj->var_m_Wj1Wj2_div_m_bWj1Wj2 = (w1jet + w2jet +bjet).M()>0? (w1jet + w2jet).M()/(w1jet + w2jet +bjet).M() : -1;
        EvtObj->var_pT_Wj1Wj2 = (w1jet + w2jet).Pt(); 
        EvtObj->var_dR_Wj1Wj2 = w1jet.DeltaR(w2jet);
        EvtObj->var_m_bWj1Wj2 = (w1jet + w2jet +bjet).M();
        EvtObj->var_dR_bW = bjet.DeltaR(w1jet + w2jet);
        EvtObj->var_m_bWj1 = (bjet+w1jet).M();
        EvtObj->var_m_bWj2 = (bjet+w2jet).M();
        EvtObj->var_mass_Wj1 = w1jet.M();
        EvtObj->var_pT_Wj2 = w2jet.Pt();
        EvtObj->var_mass_Wj2 = w2jet.M();
        EvtObj->var_pT_b = bjet.Pt();
        EvtObj->var_mass_b = bjet.M();
     
        float xgbOutput = EvtObj->resTop_reader->EvaluateMVA("BDT");
        float score = 1/(1+sqrt((1-xgbOutput)/(1+xgbOutput)));   
        if(score > hadTop_BDT){
            hadTop_BDT = score;
            hadTop_pt = (w1jet + w2jet +bjet).Pt();

            bjet_hadTop_index = bjet.index();
            wjet1_hadTop_index = w1jet.index();
            wjet2_hadTop_index = w2jet.index();
            hadTop_btagDisc_b  = EvtObj->var_btagDisc_b;
            hadTop_btagDisc_Wj1  = EvtObj->var_btagDisc_Wj1;
            hadTop_btagDisc_Wj2  = EvtObj->var_btagDisc_Wj2;
            hadTop_qg_Wj1  = EvtObj->var_qg_Wj1;
            hadTop_qg_Wj2  = EvtObj->var_qg_Wj2;
            hadTop_m_Wj1Wj2_div_m_bWj1Wj2  = EvtObj->var_m_Wj1Wj2_div_m_bWj1Wj2;
            hadTop_pT_Wj1Wj2  = EvtObj->var_pT_Wj1Wj2;
            hadTop_dR_Wj1Wj2  = EvtObj->var_dR_Wj1Wj2;
            hadTop_m_bWj1Wj2  = EvtObj->var_m_bWj1Wj2;
            hadTop_dR_bW  = EvtObj->var_dR_bW;
            hadTop_m_bWj1  = EvtObj->var_m_bWj1;
            hadTop_m_bWj2  = EvtObj->var_m_bWj2;
            hadTop_mass_Wj1  = EvtObj->var_mass_Wj1;
            hadTop_pT_Wj2  = EvtObj->var_pT_Wj2;
            hadTop_mass_b  = EvtObj->var_mass_b;

        }
      }
    }
  }
}
