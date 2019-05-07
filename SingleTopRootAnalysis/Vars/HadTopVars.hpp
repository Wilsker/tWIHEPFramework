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
    // evaluate mva
    Float_t get_hadTopMVA(EventContainer* EvtObj);

    std::vector<double> Jet25_isToptag;
    Float_t hadTop_BDT;
    Float_t hadTop_pt;
    
    Int_t bjet_hadTop_index;
    Int_t wjet1_hadTop_index;
    Int_t wjet2_hadTop_index;
    
    Float_t hadTop_btagDisc_b ;
    Float_t hadTop_btagDisc_Wj1 ;
    Float_t hadTop_btagDisc_Wj2 ;
    Float_t hadTop_qg_Wj1 ;
    Float_t hadTop_qg_Wj2 ;
    Float_t hadTop_m_Wj1Wj2_div_m_bWj1Wj2 ;
    Float_t hadTop_pT_Wj1Wj2 ;
    Float_t hadTop_dR_Wj1Wj2 ;

    Float_t hadTop_m_bWj1Wj2 ;
    Float_t hadTop_dR_bW ;
    Float_t hadTop_m_bWj1 ;
    Float_t hadTop_m_bWj2 ;
    Float_t hadTop_mass_Wj1 ;
    Float_t hadTop_pT_Wj2 ;
    Float_t hadTop_mass_Wj2 ;
    Float_t hadTop_pT_b ;

    Float_t hadTop_mass_b ;
    

};

#endif
