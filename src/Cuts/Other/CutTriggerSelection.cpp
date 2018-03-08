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
  else if (_whichtrigger == 2) _triggerChannel = "TTHLep_2Mu";
  else if (_whichtrigger == 3) _triggerChannel = "TTHLep_2Ele";
  else if (_whichtrigger == 4) _triggerChannel = "TTHLep_MuEle";
  else if (_whichtrigger == 5) _triggerChannel = "TTHLep_2L";

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

  Int_t SourceNumber = GetEventContainer()->GetSourceNumber();
  Int_t SampleType = SourceNumber < 200000? 0:(SourceNumber % 10000); //1000/1001 SEle, 2000/2001 SMu, 3000/3001 2Mu, 4000/4001 2EleR, 5000/5001 MuEleR
  
  Bool_t passesTrigger = kFALSE;  //Event passes the trigger selection

  Int_t triggerBit = 0;

  Int_t electronTrigger = 0; //I seem to have messed up the electron trigger?
  electronTrigger = EventContainerObj->HLT_Ele32_eta2p1_WPTight_Gsf;
  Int_t muonTrigger = EventContainerObj->HLT_IsoMu24 || EventContainerObj->HLT_IsoTkMu24;
  

  if (_whichtrigger == 0) triggerBit = EventContainerObj->HLT_Ele32_eta2p1_WPTight_Gsf;
  if (_whichtrigger == 1) {//I should really make these customisable, but I'm not gonna do that now.
    //triggerBit = EventContainerObj->HLT_IsoMu18;
    triggerBit = EventContainerObj->HLT_IsoMu24 || EventContainerObj->HLT_IsoTkMu24;
  }
  if (_whichtrigger == 2){
    if(SampleType == 3000 || SampleType == 3001){
        if( EventContainerObj -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1 || EventContainerObj -> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ==1)triggerBit =1; 
    }
    else if(SampleType == 2000 || SampleType == 2001){
        if( !(EventContainerObj -> HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1 || EventContainerObj -> HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ==1) && (EventContainerObj -> HLT_IsoMu22==1 || EventContainerObj -> HLT_IsoTkMu22==1 || EventContainerObj -> HLT_IsoMu22_eta2p1==1 || EventContainerObj -> HLT_IsoTkMu22_eta2p1 ==1||EventContainerObj -> HLT_IsoMu24 ==1 || EventContainerObj -> HLT_IsoTkMu24==1))triggerBit=1;
    }
    else{
        triggerBit = GetEventContainer()->TTHLep_2Mu;
    }
  }
  if (_whichtrigger == 3){
    if(SampleType == 4000 || SampleType == 4001){
        if(EventContainerObj -> HLT_Ele27_WPTight_Gsf==1 || EventContainerObj -> HLT_Ele25_eta2p1_WPTight_Gsf==1)triggerBit =1;
    }else if(SampleType == 1000 || SampleType == 1001){
        if( !(EventContainerObj -> HLT_Ele27_WPTight_Gsf==1 || EventContainerObj -> HLT_Ele25_eta2p1_WPTight_Gsf==1) && (EventContainerObj -> HLT_Ele27_eta2p1_WPLoose_Gsf==1 || EventContainerObj -> HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ==1) )triggerBit=1;
    }else{
        triggerBit = GetEventContainer()->TTHLep_2Ele;
    }
  }
  if (_whichtrigger == 4){
    if(SampleType == 5000 || SampleType == 5001){
        if(EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ==1 || EventContainerObj -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1)triggerBit=1;
    }else if(SampleType == 2000 || SampleType == 2001){
        if( !(EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ==1 || EventContainerObj -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1) && (EventContainerObj -> HLT_IsoMu22==1 || EventContainerObj -> HLT_IsoTkMu22==1 || EventContainerObj -> HLT_IsoMu22_eta2p1==1 || EventContainerObj -> HLT_IsoTkMu22_eta2p1 ==1||EventContainerObj -> HLT_IsoMu24 ==1 || EventContainerObj -> HLT_IsoTkMu24==1)) triggerBit =1;
    }else if(SampleType == 1000 || SampleType == 1001){
        if(!(EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ==1 || EventContainerObj -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL ==1 || EventContainerObj -> HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ==1 
        || EventContainerObj -> HLT_IsoMu22==1 || EventContainerObj -> HLT_IsoTkMu22==1 || EventContainerObj -> HLT_IsoMu22_eta2p1==1 || EventContainerObj -> HLT_IsoTkMu22_eta2p1 ==1||EventContainerObj -> HLT_IsoMu24 ==1 || EventContainerObj -> HLT_IsoTkMu24==1 ) &&
       ( EventContainerObj -> HLT_Ele27_WPTight_Gsf==1 || EventContainerObj -> HLT_Ele25_eta2p1_WPTight_Gsf==1 || EventContainerObj -> HLT_Ele27_eta2p1_WPLoose_Gsf==1)) triggerBit =1;
    }else{
        triggerBit = GetEventContainer()->TTHLep_MuEle;
    }
  }
  if (_whichtrigger == 5) triggerBit = GetEventContainer()->TTHLep_2L;
  
  if (_whichtrigger == 0) passesTrigger = electronTrigger != 0. and muonTrigger == 0;
  if (_whichtrigger == 1) passesTrigger = electronTrigger == 0. and muonTrigger != 0;
  if ( _whichtrigger == 2 || _whichtrigger == 3 || _whichtrigger == 4 || _whichtrigger == 5 ) passesTrigger = triggerBit == 1 ;
  
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












