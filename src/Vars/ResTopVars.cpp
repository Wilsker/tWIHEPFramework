/******************************************************************************
 * ResTopVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      18 Oct 2018 - Created by Binghuan Li
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/ResTopVars.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
ResTopVars::ResTopVars(bool makeHistos){

  SetName("ResTopVars");
  
  _floatVars["resTop_BDT"] = -1.;
  _floatVars["bjet_resTop_index"] = -1.;
  _floatVars["wjet1_resTop_index"] = -1.;
  _floatVars["wjet2_resTop_index"] = -1.;
  _floatVars["resTop_b_pt"] = -1.;
  _floatVars["resTop_b_mass"] = -1.;
  _floatVars["resTop_b_ptD"] = -1.;
  _floatVars["resTop_b_axis1"] = -1.;
  _floatVars["resTop_b_mult"] = -1.;
  _floatVars["resTop_b_csv"] = -1.;
  _floatVars["resTop_b_cvsb"] = -1.;
  _floatVars["resTop_b_cvsl"] = -1.;

  _floatVars["resTop_wj1_pt"] = -1.;
  _floatVars["resTop_wj1_mass"] = -1.;
  _floatVars["resTop_wj1_ptD"] = -1.;
  _floatVars["resTop_wj1_axis1"] = -1.;
  _floatVars["resTop_wj1_mult"] = -1.;
  _floatVars["resTop_wj1_csv"] = -1.;
  _floatVars["resTop_wj1_cvsb"] = -1.;
  _floatVars["resTop_wj1_cvsl"] = -1.;

  _floatVars["resTop_wj2_pt"] = -1.;
  _floatVars["resTop_wj2_mass"] = -1.;
  _floatVars["resTop_wj2_ptD"] = -1.;
  _floatVars["resTop_wj2_axis1"] = -1.;
  _floatVars["resTop_wj2_mult"] = -1.;
  _floatVars["resTop_wj2_csv"] = -1.;
  _floatVars["resTop_wj2_cvsb"] = -1.;
  _floatVars["resTop_wj2_cvsl"] = -1.;

  _floatVars["resTop_b_wj1_deltaR"] = -1.;
  _floatVars["resTop_b_wj1_mass"] = -1.;
  _floatVars["resTop_b_wj2_deltaR"] = -1.;
  _floatVars["resTop_b_wj2_mass"] = -1.;
  _floatVars["resTop_wcand_deltaR"] = -1.;
  _floatVars["resTop_wcand_mass"] = -1.;
  _floatVars["resTop_b_wcand_deltaR"] = -1.;
  _floatVars["resTop_topcand_mass"] = -1.;
 
  _doubleVecs["Jet25_isResToptag"] = {-0.1, 1.9 }; 

  SetDoHists(makeHistos);

}

void ResTopVars::Clear(){
  Jet25_isResToptag.clear();
  resTop_BDT= -999;
    
  bjet_resTop_index = 999;
  wjet1_resTop_index = 999;
  wjet2_resTop_index = 999;

  resTop_b_pt = -999;
  resTop_b_mass = -999;
  resTop_b_ptD = -999;
  resTop_b_axis1 = -999;
  resTop_b_mult = -999;
  resTop_b_csv = -999;
  resTop_b_cvsb = -999;
  resTop_b_cvsl = -999;

  resTop_wj1_pt = -999;
  resTop_wj1_mass = -999;
  resTop_wj1_ptD = -999;
  resTop_wj1_axis1 = -999;
  resTop_wj1_mult = -999;
  resTop_wj1_csv = -999;
  resTop_wj1_cvsb = -999;
  resTop_wj1_cvsl = -999;

  resTop_wj2_pt = -999;
  resTop_wj2_mass = -999;
  resTop_wj2_ptD = -999;
  resTop_wj2_axis1 = -999;
  resTop_wj2_mult = -999;
  resTop_wj2_csv = -999;
  resTop_wj2_cvsb = -999;
  resTop_wj2_cvsl = -999;

  resTop_b_wj1_deltaR = -999;
  resTop_b_wj1_mass = -999;
  resTop_b_wj2_deltaR = -999;
  resTop_b_wj2_mass = -999;
  resTop_wcand_deltaR = -999;
  resTop_wcand_mass = -999;
  resTop_b_wcand_deltaR = -999;
  resTop_topcand_mass = -999;
}

void ResTopVars::FillBranches(EventContainer * evtObj){

  //Initialise vectors;
  Clear();
  
  Reco_resTop(evtObj);
  
  _floatVars["resTop_BDT"] = resTop_BDT;

  evtObj->ResTop_BDT = resTop_BDT;
  if(evtObj -> _sync == 52){                                                                      
    std::cout << evtObj->eventNumber << " ";
    std::cout <<  evtObj->var_b_pt << " " ;
    std::cout <<  evtObj->var_b_mass << " " ;
    std::cout <<  evtObj->var_b_ptD << " " ;
    std::cout <<  evtObj->var_b_axis1 << " " ;
    std::cout <<  evtObj->var_b_mult << " " ;
    std::cout <<  evtObj->var_b_csv << " " ;
    std::cout <<  evtObj->var_b_cvsb << " " ;
    std::cout <<  evtObj->var_b_cvsl << " " ;

    std::cout <<  evtObj->var_wj1_pt << " " ;
    std::cout <<  evtObj->var_wj1_mass << " " ;
    std::cout <<  evtObj->var_wj1_ptD << " " ;
    std::cout <<  evtObj->var_wj1_axis1 << " " ;
    std::cout <<  evtObj->var_wj1_mult << " " ;
    std::cout <<  evtObj->var_wj1_csv << " " ;
    std::cout <<  evtObj->var_wj1_cvsb << " " ;
    std::cout <<  evtObj->var_wj1_cvsl << " " ;

    std::cout <<  evtObj->var_wj2_pt << " " ;
    std::cout <<  evtObj->var_wj2_mass << " " ;
    std::cout <<  evtObj->var_wj2_ptD << " " ;
    std::cout <<  evtObj->var_wj2_axis1 << " " ;
    std::cout <<  evtObj->var_wj2_mult << " " ;
    std::cout <<  evtObj->var_wj2_csv << " " ;
    std::cout <<  evtObj->var_wj2_cvsb << " " ;
    std::cout <<  evtObj->var_wj2_cvsl << " " ;

    std::cout <<  evtObj->var_b_wj1_deltaR << " " ;
    std::cout <<  evtObj->var_b_wj1_mass << " " ;
    std::cout <<  evtObj->var_b_wj2_deltaR << " " ;
    std::cout <<  evtObj->var_b_wj2_mass << " " ;
    std::cout <<  evtObj->var_wcand_deltaR << " " ;
    std::cout <<  evtObj->var_wcand_mass << " " ;
    std::cout <<  evtObj->var_b_wcand_deltaR << " " ;
    std::cout <<  evtObj->var_topcand_mass << " " << std::endl;
    std::cout << resTop_BDT << std::endl;
  
  }                          

  _floatVars["bjet_resTop_index"] = bjet_resTop_index;
  _floatVars["wjet1_resTop_index"] = wjet1_resTop_index;
  _floatVars["wjet2_resTop_index"] = wjet2_resTop_index;
  _floatVars["resTop_b_pt"] = resTop_b_pt ;
  _floatVars["resTop_b_mass"] = resTop_b_mass ;
  _floatVars["resTop_b_ptD"] = resTop_b_ptD ;
  _floatVars["resTop_b_axis1"] = resTop_b_axis1;
  _floatVars["resTop_b_mult"] = resTop_b_mult;
  _floatVars["resTop_b_csv"] = resTop_b_csv;
  _floatVars["resTop_b_cvsb"] = resTop_b_cvsb;
  _floatVars["resTop_b_cvsl"] = resTop_b_cvsl;

  _floatVars["resTop_wj1_pt"] = resTop_wj1_pt ;
  _floatVars["resTop_wj1_mass"] = resTop_wj1_mass ;
  _floatVars["resTop_wj1_ptD"] = resTop_wj1_ptD ;
  _floatVars["resTop_wj1_axis1"] = resTop_wj1_axis1;
  _floatVars["resTop_wj1_mult"] = resTop_wj1_mult;
  _floatVars["resTop_wj1_csv"] = resTop_wj1_csv;
  _floatVars["resTop_wj1_cvsb"] = resTop_wj1_cvsb;
  _floatVars["resTop_wj1_cvsl"] = resTop_wj1_cvsl;

  _floatVars["resTop_wj2_pt"] = resTop_wj2_pt ;
  _floatVars["resTop_wj2_mass"] = resTop_wj2_mass ;
  _floatVars["resTop_wj2_ptD"] = resTop_wj2_ptD ;
  _floatVars["resTop_wj2_axis1"] = resTop_wj2_axis1;
  _floatVars["resTop_wj2_mult"] = resTop_wj2_mult;
  _floatVars["resTop_wj2_csv"] = resTop_wj2_csv;
  _floatVars["resTop_wj2_cvsb"] = resTop_wj2_cvsb;
  _floatVars["resTop_wj2_cvsl"] = resTop_wj2_cvsl;


  _floatVars["resTop_b_wj1_deltaR"] = resTop_b_wj1_deltaR;
  _floatVars["resTop_b_wj1_mass"] = resTop_b_wj1_mass;
  _floatVars["resTop_b_wj2_deltaR"] = resTop_b_wj2_deltaR;
  _floatVars["resTop_b_wj2_mass"] = resTop_b_wj2_mass;
  _floatVars["resTop_wcand_deltaR"] = resTop_wcand_deltaR;
  _floatVars["resTop_wcand_mass"] = resTop_wcand_mass;
  _floatVars["resTop_b_wcand_deltaR"] = resTop_b_wcand_deltaR ;
  _floatVars["resTop_topcand_mass"] = resTop_topcand_mass ;
  
  Int_t jet_index=-1;
  for(uint jet_en=0; jet_en< evtObj->jets.size();jet_en++){
    jet_index++;
    Double_t isTagged = 0.;
    if(jet_index == bjet_resTop_index || jet_index == wjet1_resTop_index || jet_index == wjet2_resTop_index)isTagged=1.;
    evtObj->jets.at(jet_en).SetisResToptag(isTagged);
    Jet25_isResToptag.push_back(isTagged);
  }

  _doubleVecs["Jet25_isResToptag"] = Jet25_isResToptag; 
  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

/***************************************************************
 * void ResTopVars::Reco_resTop( )              *
 *                                                              * 
 * Calculate ResTop Tagger                                    *
 *                                                              *
 * Input: selected Leptons and Jets                                    *
 * Output: None                                                *
 * **************************************************************/
void ResTopVars::Reco_resTop(EventContainer *EvtObj){
 Int_t bjet_resTop_INDEX= -999;
 Int_t wjet1_resTop_INDEX= -999;
 Int_t wjet2_resTop_INDEX= -999;
 std::vector<Lepton> selectedLeptons = EvtObj->fakeLeptons;
 std::vector<Jet> Jets = EvtObj->jets;
 int njets = Jets.size();
 std::sort(Jets.begin(),Jets.end(),[](const Jet &a, const Jet &b){return a.bDiscriminator() > b.bDiscriminator();});
  for (int i1=0; i1<njets-2; i1++) {
    for (int i2=i1+1; i2<njets-1; i2++){
      for (int i3=i2+1; i3<njets; i3++){
        TLorentzVector bjet={0,0,0,0};
        TLorentzVector w1jet={0,0,0,0};
        TLorentzVector w2jet={0,0,0,0};
        bjet.SetPtEtaPhiE(Jets.at(i1).Pt(), Jets.at(i1).Eta(), Jets.at(i1).Phi(), Jets.at(i1).E());
        w1jet.SetPtEtaPhiE(Jets.at(i2).Pt(), Jets.at(i2).Eta(), Jets.at(i2).Phi(), Jets.at(i2).E());
        w2jet.SetPtEtaPhiE(Jets.at(i3).Pt(), Jets.at(i3).Eta(), Jets.at(i3).Phi(), Jets.at(i3).E());
        if(fabs((bjet+w1jet+w2jet).M()-175)>80) continue;
        EvtObj->var_b_pt = bjet.Pt();
        EvtObj->var_b_mass = bjet.M();
        EvtObj->var_b_ptD = Jets.at(i1).ptD();
        EvtObj->var_b_axis1 = std::exp(-Jets.at(i1).axis2()); // training uses definition of axis1 without -log, I should use axis1 but it is not saved in Ntuple, so axis2 for the moment
        EvtObj->var_b_mult = Jets.at(i1).mult();
        EvtObj->var_b_csv = Jets.at(i1).bDiscriminator();
        EvtObj->var_b_cvsb = Jets.at(i1).pfDeepCSVCvsBJetTags();
        EvtObj->var_b_cvsl = Jets.at(i1).pfDeepCSVCvsLJetTags();
     
        EvtObj->var_wj1_pt = w1jet.Pt();
        EvtObj->var_wj1_mass = w1jet.M();
        EvtObj->var_wj1_ptD = Jets.at(i2).ptD();
        EvtObj->var_wj1_axis1 = std::exp(-Jets.at(i2).axis2()); // training uses definition of axis1 without -log, I should use axis1 but it is not saved in Ntuple, so axis2 for the moment
        EvtObj->var_wj1_mult = Jets.at(i2).mult();
        EvtObj->var_wj1_csv = Jets.at(i2).bDiscriminator();
        EvtObj->var_wj1_cvsb = Jets.at(i2).pfDeepCSVCvsBJetTags();
        EvtObj->var_wj1_cvsl = Jets.at(i2).pfDeepCSVCvsLJetTags();
     
        EvtObj->var_wj2_pt = w2jet.Pt();
        EvtObj->var_wj2_mass = w2jet.M();
        EvtObj->var_wj2_ptD = Jets.at(i3).ptD();
        EvtObj->var_wj2_axis1 = std::exp(-Jets.at(i3).axis2()); // training uses definition of axis1 without -log, I should use axis1 but it is not saved in Ntuple, so axis2 for the moment
        EvtObj->var_wj2_mult = Jets.at(i3).mult();
        EvtObj->var_wj2_csv = Jets.at(i3).bDiscriminator();
        EvtObj->var_wj2_cvsb = Jets.at(i3).pfDeepCSVCvsBJetTags();
        EvtObj->var_wj2_cvsl = Jets.at(i3).pfDeepCSVCvsLJetTags();
     
        EvtObj->var_b_wj1_deltaR = bjet.DeltaR(w1jet);
        EvtObj->var_b_wj1_mass = (bjet+w1jet).M();
        EvtObj->var_b_wj2_deltaR = bjet.DeltaR(w2jet);
        EvtObj->var_b_wj2_mass = (bjet+w2jet).M();
        EvtObj->var_wcand_deltaR = w1jet.DeltaR(w2jet); 
        EvtObj->var_wcand_mass = (w1jet+w2jet).M();
        EvtObj->var_b_wcand_deltaR = bjet.DeltaR(w1jet+w2jet);
        EvtObj->var_topcand_mass = (bjet+w1jet+w2jet).M();

        float score = EvtObj->resTop_reader->EvaluateMVA("BDT");
        if(score > resTop_BDT){
            resTop_BDT = score;
            bjet_resTop_index = Jets.at(i1).index();
            wjet1_resTop_index = Jets.at(i2).index();
            wjet2_resTop_index = Jets.at(i3).index();
            resTop_b_pt = EvtObj->var_b_pt ;
            resTop_b_mass = EvtObj->var_b_mass ;
            resTop_b_ptD = EvtObj->var_b_ptD ;
            resTop_b_axis1 = EvtObj->var_b_axis1;
            resTop_b_mult = EvtObj->var_b_mult;
            resTop_b_csv = EvtObj->var_b_csv;
            resTop_b_cvsb = EvtObj->var_b_cvsb;
            resTop_b_cvsl = EvtObj->var_b_cvsl;

            resTop_wj1_pt = EvtObj->var_wj1_pt ;
            resTop_wj1_mass = EvtObj->var_wj1_mass ;
            resTop_wj1_ptD = EvtObj->var_wj1_ptD ;
            resTop_wj1_axis1 = EvtObj->var_wj1_axis1;
            resTop_wj1_mult = EvtObj->var_wj1_mult;
            resTop_wj1_csv = EvtObj->var_wj1_csv;
            resTop_wj1_cvsb = EvtObj->var_wj1_cvsb;
            resTop_wj1_cvsl = EvtObj->var_wj1_cvsl;

            resTop_wj2_pt = EvtObj->var_wj2_pt ;
            resTop_wj2_mass = EvtObj->var_wj2_mass ;
            resTop_wj2_ptD = EvtObj->var_wj2_ptD ;
            resTop_wj2_axis1 = EvtObj->var_wj2_axis1;
            resTop_wj2_mult = EvtObj->var_wj2_mult;
            resTop_wj2_csv = EvtObj->var_wj2_csv;
            resTop_wj2_cvsb = EvtObj->var_wj2_cvsb;
            resTop_wj2_cvsl = EvtObj->var_wj2_cvsl;


            resTop_b_wj1_deltaR = EvtObj->var_b_wj1_deltaR;
            resTop_b_wj1_mass = EvtObj->var_b_wj1_mass;
            resTop_b_wj2_deltaR = EvtObj->var_b_wj2_deltaR;
            resTop_b_wj2_mass = EvtObj->var_b_wj2_mass;
            resTop_wcand_deltaR = EvtObj->var_wcand_deltaR;
            resTop_wcand_mass = EvtObj->var_wcand_mass;
            resTop_b_wcand_deltaR = EvtObj->var_b_wcand_deltaR ;
            resTop_topcand_mass = EvtObj->var_topcand_mass ;
        }

      }
    }
  }
};

