/******************************************************************************
 * ResTopVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      18 Oct 2018 - Created by Binghuan Li
 ******************************************************************************/

#ifndef ResTopVars_h
#define ResTopVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp" 
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "TLorentzVector.h"
#include <TEnv.h>

#include "TMVA/Reader.h"

class ResTopVars: public VarBase {
  
public:
  ResTopVars(bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
    // resolved top tagger
    // resolved top tagger algorithm 
    void Reco_resTop(EventContainer * EvtObj);
    // evaluate mva
    Float_t get_resTopMVA(EventContainer* EvtObj);

    std::vector<double> Jet25_isResToptag;
    Float_t resTop_BDT;
  
    Int_t bjet_resTop_index;
    Int_t wjet1_resTop_index;
    Int_t wjet2_resTop_index;

    Float_t resTop_b_pt ;
    Float_t resTop_b_mass ;
    Float_t resTop_b_ptD ;
    Float_t resTop_b_axis1 ;
    Float_t resTop_b_mult ;
    Float_t resTop_b_csv ;
    Float_t resTop_b_cvsb ;
    Float_t resTop_b_cvsl ;

    Float_t resTop_wj1_pt ;
    Float_t resTop_wj1_mass ;
    Float_t resTop_wj1_ptD ;
    Float_t resTop_wj1_axis1 ;
    Float_t resTop_wj1_mult ;
    Float_t resTop_wj1_csv ;
    Float_t resTop_wj1_cvsb ;
    Float_t resTop_wj1_cvsl ;

    Float_t resTop_wj2_pt ;
    Float_t resTop_wj2_mass ;
    Float_t resTop_wj2_ptD ;
    Float_t resTop_wj2_axis1 ;
    Float_t resTop_wj2_mult ;
    Float_t resTop_wj2_csv ;
    Float_t resTop_wj2_cvsb ;
    Float_t resTop_wj2_cvsl ;

    Float_t resTop_b_wj1_deltaR ;
    Float_t resTop_b_wj1_mass ;
    Float_t resTop_b_wj2_deltaR ;
    Float_t resTop_b_wj2_mass ;
    Float_t resTop_wcand_deltaR ;
    Float_t resTop_wcand_mass ;
    Float_t resTop_b_wcand_deltaR ;
    Float_t resTop_topcand_mass ;
};

#endif
