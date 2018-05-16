/******************************************************************************
 * DNNVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      25 Nov 2016 - Created by D. Leggat
 ******************************************************************************/

#ifndef DNNVars_h
#define DNNVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp" 
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "TLorentzVector.h"
#include <TEnv.h>

#include "TMVA/Reader.h"

class DNNVars: public VarBase {
  
public:
  DNNVars( bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
   
    EventContainer *EvtObj;
    TEnv *config;
    
    // Event mva
    TMVA::Reader *DNNMultiClass_Dilep_reader_;
    Float_t varJet_numLoose;
    Float_t varmaxeta;
    Float_t varSR_InvarMassT;
    Float_t varhadTop_BDT;
    Float_t varmindrlep1jet;
    Float_t varHj1_BDT;
    Float_t varmindrlep2jet;
    Float_t varcorrptlep1;
    Float_t varcorrptlep2;
    Float_t varEVENT_event;
    
    // evaluate mva
    void get_DNNResponse();

    std::vector<double> DNN_response;
};

#endif
