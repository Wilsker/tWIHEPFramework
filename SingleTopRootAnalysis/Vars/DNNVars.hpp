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

#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/PyMethodBase.h"
#include "TMVA/Reader.h"


class DNNVars: public VarBase {
  
public:
  DNNVars( bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
    
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
    void get_DNNResponse(EventContainer* EvtObj);

    std::vector<double> DNN_response;
    Float_t bestDNN;
    Float_t worseDNN;
    Float_t DNN_ttH_output;
    Float_t DNN_ttV_output;
    Float_t DNN_ttJet_output;
    Float_t SubCat_DNN;
};

#endif
