/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/DNNVars.hpp"

#include <iostream>


//Test out a couple of variables, one Int_t and one float I guess
DNNVars::DNNVars(bool makeHistos){

  SetName("DNNVars");
  
  _doubleVecs["DNN_response"] = {-2., 2. }; 

    TMVA::Tools::Instance();
    // DNN MultiClass
    DNNMultiClass_Dilep_reader_ = new TMVA::Reader("!Color:!Silent");
    DNNMultiClass_Dilep_reader_->AddVariable("Jet_numLoose",&varJet_numLoose);
    DNNMultiClass_Dilep_reader_->AddVariable("maxeta",&varmaxeta);
    DNNMultiClass_Dilep_reader_->AddVariable("SR_InvarMassT",&varSR_InvarMassT);
    DNNMultiClass_Dilep_reader_->AddVariable("max(hadTop_BDT,-1.)",&varhadTop_BDT);
    DNNMultiClass_Dilep_reader_->AddVariable("mindrlep1jet",&varmindrlep1jet);
    DNNMultiClass_Dilep_reader_->AddVariable("max(Hj1_BDT,-1.)",&varHj1_BDT);
    DNNMultiClass_Dilep_reader_->AddVariable("mindrlep2jet",&varmindrlep2jet);
    DNNMultiClass_Dilep_reader_->AddVariable("corrptlep1",&varcorrptlep1);
    DNNMultiClass_Dilep_reader_->AddVariable("corrptlep2",&varcorrptlep2);
    DNNMultiClass_Dilep_reader_->AddSpectator("EVENT_event",&varEVENT_event);
    DNNMultiClass_Dilep_reader_->BookMVA("DNN", "config/weights/DNN/Factory_MultiClass_DNN_10HLs_relu_D+G-VarTrans_0.008-learnRate_10-epochs_DNN.weights.xml"); 
  
  SetDoHists(makeHistos);

}

void DNNVars::Clear(){
  DNN_response.clear();
}

void DNNVars::FillBranches(EventContainer* evtObj){

  //Initialise vectors;
  Clear();
  
  get_DNNResponse(evtObj); 
  _doubleVecs["DNN_response"] = DNN_response;
  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

void DNNVars::get_DNNResponse(EventContainer* EvtObj){
   Float_t minus = -1.0;
   varJet_numLoose = EvtObj->Dilepttbar_numJets;
   varmaxeta = EvtObj->Dilepttbar_maxlepeta;
   varSR_InvarMassT = EvtObj->Dilepttbar_Mtmetlep1;
   varhadTop_BDT = max(minus, EvtObj->Dilepttbar_HadTopBDT);
   varmindrlep1jet = EvtObj-> Dilepttbar_mindrlep1jet;
   varHj1_BDT= max(minus, EvtObj-> Dilepttv_Hj1BDT) ;
   varmindrlep2jet = EvtObj->Dilepttbar_mindrlep2jet;
   varcorrptlep1 = EvtObj-> Dilepttv_ptlep1;
   varcorrptlep2 = EvtObj-> Dilepttv_ptlep2;
   varEVENT_event = EvtObj-> eventNumber;
   DNN_response.push_back(DNNMultiClass_Dilep_reader_->EvaluateMulticlass("DNN")[0]);
   DNN_response.push_back(DNNMultiClass_Dilep_reader_->EvaluateMulticlass("DNN")[1]);
   DNN_response.push_back(DNNMultiClass_Dilep_reader_->EvaluateMulticlass("DNN")[2]);
};
