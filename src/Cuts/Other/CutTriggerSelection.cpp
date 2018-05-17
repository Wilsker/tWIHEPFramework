/******************************************************************************
 * CutTriggerSelection.cpp                                                    *
 *                                                                            *
 * Cuts on the trigger required per channel                                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutTriggerSelection class                              *
 *    CutTriggerSelection()                     -- Parameterized Constructor         *
 *    ~CutTriggerSelection()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutTriggerSelection"                *
 *                                                                            *
 * Private Data Members of CutTriggerSelection class                                 *
 *    myTH1F* _hTriggerBitBefore;    -- Hist of trigger bit before cut        *
 *    myTH1F* _hTriggerBitAfter;     -- Hist of trigger bit after cut         *
 *                                                                            *
 * History                                                                    *
 *      4th July 2016 - Created by Duncan Leggat                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutTriggerSelection.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
 * CutTriggerSelection::CutTriggerSelection(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 *         whichTrigger says which channel to cut on
 *         0 - Electron, 1 - Muon
 * Output: None                                                               *
 ******************************************************************************/
CutTriggerSelection::CutTriggerSelection(EventContainer *EventContainerObj, int whichTrigger)
{
  _whichtrigger = whichTrigger;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutTriggerSelection


/******************************************************************************
 * CutTriggerSelection::~CutTriggerSelection()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutTriggerSelection::~CutTriggerSelection()
{
  
}//~CutTriggerSelection

/******************************************************************************
 * void CutTriggerSelection::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutTriggerSelection::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  
  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv * config = EventContainerObj->GetConfig();
  
  TString triggerConfig = config -> GetValue("Cut.Trigger.Channel","none");

  if (_whichtrigger == 0) _triggerChannel = "Electron";
  else if (_whichtrigger == 1) _triggerChannel = "Muon";
  // overwrite _whichtrigger
  else if (triggerConfig == "TTHLep_2Mu")_whichtrigger =2;
  else if (triggerConfig == "TTHLep_2Ele")_whichtrigger =3;
  else if (triggerConfig == "TTHLep_MuEle")_whichtrigger =4;
  else if (triggerConfig == "TTHLep_2L")_whichtrigger =5;
  else if (triggerConfig == "TTHLep_3L")_whichtrigger =6;
  if (_whichtrigger == 2) _triggerChannel = "TTHLep_2Mu";
  else if (_whichtrigger == 3) _triggerChannel = "TTHLep_2Ele";
  else if (_whichtrigger == 4) _triggerChannel = "TTHLep_MuEle";
  else if (_whichtrigger == 5) _triggerChannel = "TTHLep_2L";
  else if (_whichtrigger == 6) _triggerChannel = "TTHLep_3L";

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << _triggerChannel << "TriggerSelectionBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << _triggerChannel << " Channel Trigger Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << _triggerChannel << "TriggerSelectionAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << _triggerChannel << " Channel Trigger After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hTriggerSelectionBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 2, 0.0, 2.0);
  _hTriggerSelectionBefore -> SetXAxisTitle("TriggerBit");
  _hTriggerSelectionBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hTriggerSelectionAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 2, 0.0, 2.0);
  _hTriggerSelectionAfter -> SetXAxisTitle("TriggerBit");
  _hTriggerSelectionAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << _triggerChannel << " Trigger";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << _triggerChannel << "Trigger";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());

}//BookHistograms()

/******************************************************************************
 * Bool_t CutTriggerSelection::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutTriggerSelection::Apply()
{

  EventTree *EventContainerObj = GetEventContainer()->GetEventTree();
  EventContainer *ContainerObj = GetEventContainer();
  Int_t selectedChannel = -1;
  if(fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())==22)selectedChannel =3; //isEE
  if(fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())==24)selectedChannel =4; //isEM
  if(fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())==26)selectedChannel =2; //isMM
  if(ContainerObj -> fakeLeptons.size()>=3 && _whichtrigger == 6 ){
    if((fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())+fabs(ContainerObj -> fakeLeptons.at(2).pdgId()))==33)selectedChannel =61;//isEEE
    if((fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())+fabs(ContainerObj -> fakeLeptons.at(2).pdgId()))==35)selectedChannel =62;//isEEE
    if((fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())+fabs(ContainerObj -> fakeLeptons.at(2).pdgId()))==37)selectedChannel =63;//isEEE
    if((fabs(ContainerObj -> fakeLeptons.at(0).pdgId())+fabs(ContainerObj -> fakeLeptons.at(1).pdgId())+fabs(ContainerObj -> fakeLeptons.at(2).pdgId()))==39)selectedChannel =64;//isEEE
  }

  Int_t SourceNumber = GetEventContainer()->GetSourceNumber();
  Int_t SampleType = SourceNumber < 200000? 0:(SourceNumber % 10000); //1000/1001 SEle, 2000/2001 SMu, 3000/3001 2Mu, 4000/4001 2EleR, 5000/5001 MuEleR
  
  Bool_t passesTrigger = kFALSE;  //Event passes the trigger selection

  Int_t triggerBit = 0;
  Int_t EEtrigger = 0;
  Int_t EMtrigger = 0;
  Int_t MMtrigger = 0;
  Int_t TriLeptrigger = 0;
  Bool_t TriLeptriggerPath = kFALSE;

  
  Int_t electronTrigger = 0; //I seem to have messed up the electron trigger?
  electronTrigger = EventContainerObj->HLT_Ele32_WPTight_Gsf;
  Int_t muonTrigger = EventContainerObj->HLT_IsoMu24 || EventContainerObj->HLT_IsoTkMu24;
  

  if (_whichtrigger == 0) triggerBit = EventContainerObj->HLT_Ele32_WPTight_Gsf;
  if (_whichtrigger == 1) {//I should really make these customisable, but I'm not gonna do that now.
    //triggerBit = EventContainerObj->HLT_IsoMu18;
    triggerBit = EventContainerObj->HLT_IsoMu24 || EventContainerObj->HLT_IsoTkMu24;
  }
  if (_whichtrigger == 2 || _whichtrigger ==5 ){
    if(SampleType == 3000 || SampleType == 3001){
        //if(selectedChannel ==2 && (EventContainerObj -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1 || EventContainerObj -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8==1))MMtrigger =1; 
        if(selectedChannel ==2 && ContainerObj->Trig_2Mu==1 )MMtrigger =1; 
    }
    else if(SampleType == 2000 || SampleType == 2001){
        //if(selectedChannel==2 && ( !(EventContainerObj -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1 || EventContainerObj -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8==1) && (EventContainerObj -> HLT_IsoMu24 ==1 || EventContainerObj -> HLT_IsoMu27==1)))MMtrigger=1;
        if(selectedChannel==2 && ContainerObj->Trig_2Mu!=1 && ContainerObj->Trig_1Mu ==1 )MMtrigger=1;
    }
    else if(SampleType == 1000 || SampleType == 4000 || SampleType == 5000 || SampleType == 1001 || SampleType == 4001 || SampleType == 5001 ){
        MMtrigger =0;
    }
    else{
        MMtrigger = selectedChannel ==2 && ContainerObj->TTHLep_2Mu==1;
    }
  }
  if (_whichtrigger == 3 || _whichtrigger ==5 ){
    if(SampleType == 4000 || SampleType == 4001){
        //if(selectedChannel ==3 && (EventContainerObj -> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ==1 || EventContainerObj -> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL ==1))EEtrigger =1;
        if(selectedChannel ==3 && ContainerObj->Trig_2Ele ==1 )EEtrigger =1;
    }else if(SampleType == 1000 || SampleType == 1001){
        //if(selectedChannel==3 &&( (EventContainerObj -> HLT_Ele35_WPTight_Gsf ==1 || EventContainerObj -> HLT_Ele32_WPTight_Gsf==1) && !(EventContainerObj -> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ==1 || EventContainerObj -> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL ==1) ))EEtrigger=1;
        if(selectedChannel==3 && ContainerObj->Trig_2Ele !=1 && ContainerObj->Trig_1Ele==1 )EEtrigger=1;
    }
    else if(SampleType == 2000 || SampleType == 3000 || SampleType == 5000 || SampleType == 2001 || SampleType == 3001 || SampleType == 5001 ){
        EEtrigger =0;
    }
    else{
        EEtrigger = selectedChannel ==3 && ContainerObj->TTHLep_2Ele==1 ;
    }
  }
  if (_whichtrigger == 4 || _whichtrigger ==5 ){
    if(SampleType == 5000 || SampleType == 5001){
        //if( selectedChannel ==4 && (EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1 || EventContainerObj -> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1))EMtrigger=1;
        if( selectedChannel ==4 && ContainerObj->Trig_1Mu1Ele ==1 )EMtrigger=1;
    }else if(SampleType == 2000 || SampleType == 2001){
        //if( selectedChannel ==4 && ( !(EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1 || EventContainerObj -> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1) && (EventContainerObj -> HLT_IsoMu27==1 || EventContainerObj -> HLT_IsoMu24 ==1 ))) EMtrigger =1;
        if( selectedChannel ==4 && ContainerObj->Trig_1Mu1Ele!=1 && ContainerObj->Trig_1Mu==1) EMtrigger =1;
    }else if(SampleType == 1000 || SampleType == 1001){
        //if( selectedChannel==4 && ( !(EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1 || EventContainerObj -> HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1 || EventContainerObj -> HLT_IsoMu27==1 || EventContainerObj -> HLT_IsoMu24 ==1) &&
        if( selectedChannel ==4 && ContainerObj->Trig_1Mu1Ele!=1 && ContainerObj->Trig_1Mu!=1 && ContainerObj->Trig_1Ele==1) EMtrigger =1;
    }
    else if(SampleType == 4000 || SampleType == 3000  || SampleType == 4001 || SampleType == 3001 ){
        EMtrigger =0;
    }
    else{
        EMtrigger = selectedChannel ==4 && ContainerObj->TTHLep_MuEle==1;
    }
  }
  if (_whichtrigger ==6 ){
    TriLeptriggerPath = ( (selectedChannel == 61 && (ContainerObj->TTHLep_2Ele==1 || ContainerObj->Trig_3Ele==1 ))
     || (selectedChannel == 62 && (ContainerObj->TTHLep_MuEle==1 || ContainerObj->Trig_1Mu2Ele==1 ))
     || (selectedChannel == 63 && (ContainerObj->TTHLep_MuEle==1 || ContainerObj->Trig_2Mu1Ele==1 ))
     || (selectedChannel == 64 && (ContainerObj->TTHLep_2Mu==1 || ContainerObj->Trig_3Mu==1 )));
    if(SampleType == 4000 || SampleType == 4001){
        if(ContainerObj->Trig_3Ele==1 || ContainerObj->Trig_1Mu2Ele==1 || ContainerObj->Trig_2Ele==1) TriLeptrigger =1;
    }else if(SampleType == 3000 || SampleType == 3001){
        if(ContainerObj->Trig_3Ele!=1 && ContainerObj->Trig_1Mu2Ele!=1 && ContainerObj->Trig_2Ele!=1 && (ContainerObj->Trig_3Mu==1 || ContainerObj->Trig_2Mu1Ele==1 || ContainerObj->Trig_2Mu==1) ) TriLeptrigger =1;
    }else if(SampleType == 5000 || SampleType == 5001){
        if(ContainerObj->Trig_3Ele!=1 && ContainerObj->Trig_1Mu2Ele!=1 && ContainerObj->Trig_2Ele!=1 && ContainerObj->Trig_3Mu!=1 && ContainerObj->Trig_2Mu1Ele!=1 && ContainerObj->Trig_2Mu!=1 && ContainerObj->Trig_1Mu1Ele==1 ) TriLeptrigger =1;
    }else if(SampleType == 1000 || SampleType == 1001){
        if(ContainerObj->Trig_3Ele!=1 && ContainerObj->Trig_1Mu2Ele!=1 && ContainerObj->Trig_2Ele!=1 && ContainerObj->Trig_3Mu!=1 && ContainerObj->Trig_2Mu1Ele!=1 && ContainerObj->Trig_2Mu!=1 && ContainerObj->Trig_1Mu1Ele!=1 && ContainerObj->Trig_1Ele ==1 ) TriLeptrigger =1;
    }else if(SampleType == 2000 || SampleType == 2001){
        if(ContainerObj->Trig_3Ele!=1 && ContainerObj->Trig_1Mu2Ele!=1 && ContainerObj->Trig_2Ele!=1 && ContainerObj->Trig_3Mu!=1 && ContainerObj->Trig_2Mu1Ele!=1 && ContainerObj->Trig_2Mu!=1 && ContainerObj->Trig_1Mu1Ele!=1 && ContainerObj->Trig_1Ele !=1 && ContainerObj->Trig_1Mu ==1 ) TriLeptrigger =1;
    }else{
        TriLeptrigger = ContainerObj->TTHLep_3L;
    }
  }
  if (_whichtrigger == 0) passesTrigger = electronTrigger != 0. and muonTrigger == 0;
  if (_whichtrigger == 1) passesTrigger = electronTrigger == 0. and muonTrigger != 0;
  if ( _whichtrigger == 2) passesTrigger = MMtrigger == 1;
  if ( _whichtrigger == 3) passesTrigger = EEtrigger == 1;
  if ( _whichtrigger == 4) passesTrigger = EMtrigger == 1;
  if ( _whichtrigger == 5) passesTrigger = MMtrigger == 1 || EEtrigger == 1 || EMtrigger == 1;
  if ( _whichtrigger == 6) passesTrigger = TriLeptrigger == 1 && TriLeptriggerPath ;
  triggerBit = passesTrigger;
 
  
  //if (triggerBit != 0.) passesTrigger = kTRUE;

  // Fill the histograms before the cuts
  _hTriggerSelectionBefore -> Fill(triggerBit);
 
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameStream;
  
  TString cutFlowName;
  
  cutFlowNameStream << _triggerChannel << "Trigger";
  cutFlowName = cutFlowNameStream.str().c_str();
  
  if( ContainerObj->_sync >= 80  && ContainerObj->_sync != 99 && ContainerObj->_debugEvt == ContainerObj->eventNumber && !passesTrigger ){
    std::cout<< " Event " << ContainerObj->_debugEvt <<" Fail passesTrigger : _whichtrigger is "<< _whichtrigger << " MMtrigger "<< MMtrigger << " EEtrigger "<< EEtrigger <<" EMtrigger "<< EMtrigger << " TrilepTrigger "<< TriLeptrigger<< " 3l trigger path "<< TriLeptriggerPath<< " selectedChannel 61:EEE/62:EEM/63:EMM/64:MMM "<< selectedChannel<< std::endl; 
  }
  
  if (passesTrigger){
    _hTriggerSelectionAfter -> Fill(triggerBit);
    GetCutFlowTable()->PassCut(cutFlowName.Data());
    return kTRUE;
  }
  else{
    GetCutFlowTable()->FailCut(cutFlowName.Data());
    return kFALSE;
  }

} //Apply












