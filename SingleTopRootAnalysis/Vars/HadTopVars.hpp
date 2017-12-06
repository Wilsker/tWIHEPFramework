/******************************************************************************
 * HadTopVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      25 Nov 2016 - Created by D. Leggat
 ******************************************************************************/

#ifndef HadTopVars_h
#define HadTopVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp" 
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "TLorentzVector.h"
#include <TEnv.h>

#include "TMVA/Reader.h"

class HadTopVars: public VarBase {
  
public:
  HadTopVars(bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
    // hadronic top tagger
    // hadTop algorithm 
    void Reco_hadTop(EventContainer * EvtObj);
    // add null jets
    Int_t Add_nullJet(std::vector<Jet>& selectedJets);
    // evaluate mva
    Float_t get_hadTopMVA(int numbJet, EventContainer* EvtObj);

    std::vector<double> Jet_isToptag;
    std::vector<Float_t> Jet_null_pt; 
    std::vector<Float_t> Jet_null_eta; 
    std::vector<Float_t> Jet_null_phi;
    std::vector<Float_t> Jet_null_energy; 
    std::vector<Float_t> Jet_null_csv;
    Int_t Jet_numLoose ;
    Int_t Jet_numbMedium ;
  
    Float_t bjet_lepTop_pt;
    Float_t lep_Top_pt;
    Float_t lep_H_pt;
    Float_t bjet_lepTop_eta;
    Float_t bjet_hadTop_eta;
    Float_t wjet1_hadTop_eta;
    Float_t wjet2_hadTop_eta;
    Float_t lep_Top_eta;
    Float_t lep_H_eta;
    Float_t bjet_lepTop_phi;
    Float_t bjet_hadTop_phi;
    Float_t wjet1_hadTop_phi;
    Float_t wjet2_hadTop_phi;
    Float_t lep_Top_phi;
    Float_t lep_H_phi;
    Float_t bjet_lepTop_energy;
    Float_t bjet_hadTop_energy;
    Float_t wjet1_hadTop_energy;
    Float_t wjet2_hadTop_energy;
    Float_t lep_Top_energy;
    Float_t lep_H_energy;
    Int_t bjet_lepTop_index;
    Int_t bjet_hadTop_index;
    Int_t wjet1_hadTop_index;
    Int_t wjet2_hadTop_index;
    Int_t lep_Top_index;
    Int_t lep_H_index;
    Float_t hadTop_BDT;
    Float_t bjet_hadTop_pt;
    Float_t wjet1_hadTop_pt;
    Float_t wjet2_hadTop_pt;
    Float_t bjet_hadTop_csv;
    Float_t bjet_lepTop_csv;
    Float_t reco_hadTop_pt;
    Float_t reco_hadTop_mass;
    Float_t reco_WhadTop_mass;
    Float_t PtRatio_leptOverleph;
    Float_t Dr_lept_bfromlTop;
    Float_t Dr_lept_bfromhTop;
    Float_t Dr_leph_bfromlTop;

    Double_t _MWPbTagCut;
};

#endif
