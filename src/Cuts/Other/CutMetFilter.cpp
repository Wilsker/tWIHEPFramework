/******************************************************************************
 * CutMetFilter.cpp                                                       *
 *                                                                            *
 * Cuts on the requirement of a good primary vertex                           *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutMetFilter class                              *
 *    CutMetFilter()                     -- Parameterized Constructor         *
 *    ~CutMetFilter()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutMetFilter"                *
 *                                                                            *
 * Private Data Members of CutMetFilter class                                 *
 *    myTH1F* _hMetFilterBefore;    -- Hist of PV before cut        *
 *    myTH1F* _hMetFilterAfter;     -- Hist of PV after cut         *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutMetFilter.hpp"
#include <iostream>

using namespace std;

/******************************************************************************
 * CutMetFilter::CutMetFilter(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutMetFilter::CutMetFilter(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutMetFilter


/******************************************************************************
 * CutMetFilter::~CutMetFilter()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutMetFilter::~CutMetFilter()
{
  
}//~CutMetFilter

/******************************************************************************
 * void CutMetFilter::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutMetFilter::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << "MetFilterBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << "MetFilter Before";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << "MetFilterAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << "MetFilter After";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hMetFilterBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 50, 0.0, 5.);
  _hMetFilterBefore -> SetXAxisTitle("MetFilter ");
  _hMetFilterBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hMetFilterAfter=  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 50, 0.0, 5.);
  _hMetFilterAfter-> SetXAxisTitle("MetFilter ");
  _hMetFilterAfter-> SetYAxisTitle("Events");


  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << "MetFilter Cut";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << "MetFilter.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  // ***********************************************
  // ***********************************************

  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();


}//BookHistograms()

/******************************************************************************
 * Bool_t CutMetFilter::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutMetFilter::Apply()
{

  EventContainer *EventContainerObj = GetEventContainer();
  
  EventTree *EvtTree = GetEventContainer()->GetEventTree();

  Bool_t passesMetFilterCut = kTRUE;

  Bool_t isMC = EventContainerObj->isSimulation;
  
  Int_t MetFilter = -1 ;
  if(!isMC && !(EvtTree->Flag_goodVertices && EvtTree-> Flag_globalSuperTightHalo2016Filter && EvtTree->Flag_HBHENoiseFilter && EvtTree-> Flag_HBHENoiseIsoFilter && EvtTree-> Flag_EcalDeadCellTriggerPrimitiveFilter && EvtTree-> Flag_BadPFMuonFilter && EvtTree-> Flag_BadChargedCandidateFilter && EvtTree->Flag_ecalBadCalibFilter && EvtTree-> Flag_eeBadScFilter))MetFilter = 0; 
  else MetFilter =1;
  if(isMC && !(EvtTree->Flag_goodVertices && EvtTree-> Flag_globalSuperTightHalo2016Filter && EvtTree->Flag_HBHENoiseFilter && EvtTree-> Flag_HBHENoiseIsoFilter && EvtTree-> Flag_EcalDeadCellTriggerPrimitiveFilter && EvtTree-> Flag_BadPFMuonFilter && EvtTree-> Flag_BadChargedCandidateFilter && EvtTree->Flag_ecalBadCalibFilter))MetFilter = 0; 
  else MetFilter =1;
  _hMetFilterBefore->Fill(MetFilter);

  ostringstream cutFlowNameStream;
                                
  TString cutFlowName;            

  cutFlowNameStream << "MetFilter.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  if (MetFilter ==0 ){
    passesMetFilterCut = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowName);
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowName);
    _hMetFilterAfter->Fill(MetFilter);
  }

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !passesMetFilterCut ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail passesMetFilterCut: MetFilter is " << MetFilter  << std::endl; 
  }
  return passesMetFilterCut;

} //Apply












