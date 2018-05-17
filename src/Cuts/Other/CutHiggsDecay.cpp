/******************************************************************************
 * CutHiggsDecay.cpp                                                       *
 *                                                                            *
 * Cuts on the requirement of a good primary vertex                           *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutHiggsDecay class                              *
 *    CutHiggsDecay()                     -- Parameterized Constructor         *
 *    ~CutHiggsDecay()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutHiggsDecay"                *
 *                                                                            *
 * Private Data Members of CutHiggsDecay class                                 *
 *    myTH1F* _hHiggsDecayBefore;    -- Hist of PV before cut        *
 *    myTH1F* _hHiggsDecayAfter;     -- Hist of PV after cut         *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutHiggsDecay.hpp"
#include <iostream>

using namespace std;

/******************************************************************************
 * CutHiggsDecay::CutHiggsDecay(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutHiggsDecay::CutHiggsDecay(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutHiggsDecay


/******************************************************************************
 * CutHiggsDecay::~CutHiggsDecay()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutHiggsDecay::~CutHiggsDecay()
{
  
}//~CutHiggsDecay

/******************************************************************************
 * void CutHiggsDecay::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutHiggsDecay::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << "HiggsDecayBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << "HiggsDecay Before";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << "HiggsDecayAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << "HiggsDecay After";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hHiggsDecayBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 50, 0.0, 50.);
  _hHiggsDecayBefore -> SetXAxisTitle("HiggsDecay ");
  _hHiggsDecayBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hHiggsDecayAfter=  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 50, 0.0, 50.);
  _hHiggsDecayAfter-> SetXAxisTitle("HiggsDecay ");
  _hHiggsDecayAfter-> SetYAxisTitle("Events");


  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << "HiggsDecay Cut";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << "HiggsDecay.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  // ***********************************************
  // Get the PV IDs from the config file. Perhaps these should be included as an object
  // ***********************************************

  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv * config = EventContainerObj->GetConfig();

  //Then set the cuts here.
  _HiggsDecayType = config -> GetValue("Cut.Event.HiggsDecayType",999);


}//BookHistograms()

/******************************************************************************
 * Bool_t CutHiggsDecay::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutHiggsDecay::Apply()
{

  EventContainer *EventContainerObj = GetEventContainer();

  Double_t higgsDecay = EventContainerObj -> HiggsDecay;
 
  Bool_t passesHiggsDecayCut = kTRUE;
  
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==0 && !(higgsDecay == 2 || higgsDecay ==3 || higgsDecay ==6))passesHiggsDecayCut = kFALSE;  
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==1 && !(higgsDecay == 2 ))passesHiggsDecayCut = kFALSE; // WW 
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==2 && !(higgsDecay == 3 ))passesHiggsDecayCut = kFALSE;  // TauTau
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==3 && !(higgsDecay == 6 ))passesHiggsDecayCut = kFALSE;  // ZZ
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==4 && !(higgsDecay == 2 ||  higgsDecay ==6 ))passesHiggsDecayCut = kFALSE;  
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==5 && !(higgsDecay == 2 || higgsDecay ==3 ))passesHiggsDecayCut = kFALSE;  
  if(EventContainerObj->GetSourceName().Contains("TTH") && _HiggsDecayType ==6 && !(higgsDecay == 2 || higgsDecay ==6 ))passesHiggsDecayCut = kFALSE;  

  //std::cout << " SourceName is " << EventContainerObj->GetSourceName() << " _HiggsDecayType is " << _HiggsDecayType << " HiggsDecay is " << higgsDecay << " pass Cut ? "<< passesHiggsDecayCut << std::endl;
  _hHiggsDecayBefore->Fill(higgsDecay);



  ostringstream cutFlowNameStream;
                                
  TString cutFlowName;            

  cutFlowNameStream << "HiggsDecay.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  if ( !passesHiggsDecayCut ){
    GetCutFlowTable()->FailCut(cutFlowName);
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowName);
    _hHiggsDecayAfter->Fill(higgsDecay);
  }

  return passesHiggsDecayCut;

} //Apply












