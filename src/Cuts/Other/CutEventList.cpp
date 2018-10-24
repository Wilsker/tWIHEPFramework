/******************************************************************************
 * CutEventList.cpp                                                       *
 *                                                                            *
 * Cuts on the requirement of a good primary vertex                           *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutEventList class                              *
 *    CutEventList()                     -- Parameterized Constructor         *
 *    ~CutEventList()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutEventList"                *
 *                                                                            *
 * Private Data Members of CutEventList class                                 *
 *    myTH1F* _hEventListBefore;    -- Hist of PV before cut        *
 *    myTH1F* _hEventListAfter;     -- Hist of PV after cut         *
 *                                                                            *
 * History                                                                    *
 *      24 Oct 2018 - Created by B.Li                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutEventList.hpp"
#include <iostream>

using namespace std;

/******************************************************************************
 * CutEventList::CutEventList(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutEventList::CutEventList(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutEventList


/******************************************************************************
 * CutEventList::~CutEventList()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutEventList::~CutEventList()
{
  
}//~CutEventList

/******************************************************************************
 * void CutEventList::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutEventList::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << "EventListBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << "EventList Before";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << "EventListAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << "EventList After";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hEventListBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 50, 0.0, 50.);
  _hEventListBefore -> SetXAxisTitle("EventList ");
  _hEventListBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hEventListAfter=  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 50, 0.0, 50.);
  _hEventListAfter-> SetXAxisTitle("EventList ");
  _hEventListAfter-> SetYAxisTitle("Events");


  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << "EventList Cut";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << "EventList.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  // ***********************************************
  // Get the PV IDs from the config file. Perhaps these should be included as an object
  // ***********************************************

  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv * config = EventContainerObj->GetConfig();


}//BookHistograms()

/******************************************************************************
 * Bool_t CutEventList::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutEventList::Apply()
{

  EventContainer *EventContainerObj = GetEventContainer();

  Runs.assign(EventContainerObj -> sync_runs.begin(), EventContainerObj -> sync_runs.end());
  Lumis.assign(EventContainerObj -> sync_lumis.begin(), EventContainerObj -> sync_lumis.end());
  nEvents.assign(EventContainerObj -> sync_nEvts.begin(), EventContainerObj -> sync_nEvts.end());

  Long64_t nEvt = EventContainerObj -> eventNumber ;
  Float_t run = EventContainerObj -> runNumber ;
  Float_t lumi = EventContainerObj -> lumiBlock ;
  
  Bool_t passesEventListCut = kFALSE;

  for(uint i=0; i<nEvents.size(); i++){
    Bool_t isSameEvt = kFALSE;
    Bool_t isSameRun = kFALSE;
    Bool_t isSameLumi = kFALSE;
    Bool_t printInfo = kFALSE;
    //if(71154146==nEvents.at(i) || 2332581828==nEvents.at(i)){ printInfo=kTRUE; std::cout<<" now we print info in CutEventList "<<std::endl;}
    if(nEvents.at(i)>2147483647){ // 2147483647 = 2^31 -1 , this is to fix the Long64_t -> int problem in Ntuple
        if(nEvents.at(i) == nEvt + 4294967296) isSameEvt = kTRUE;
        if(printInfo){
            std::cout<< "found nagative event: run:ls:nEvt " << run <<":" <<lumi<<":"<<nEvt<<std::endl;
        }
    }else if(nEvents.at(i)==nEvt){
        isSameEvt = kTRUE;
        if(printInfo){
            std::cout<< "found positive event: run:ls:nEvt " << run <<":" <<lumi<<":"<<nEvt<<std::endl;
        }
    }
    if(!isSameEvt)continue;
    if(Runs.at(i)==run){
        isSameRun = kTRUE;
        if(printInfo){
            std::cout<< "found same run: run:ls:nEvt " << run <<":" <<lumi<<":"<<nEvt<<std::endl;
        }
    }
    if(!isSameRun)continue;
    if(Lumis.at(i)==lumi){
        isSameLumi = kTRUE;
        if(printInfo){
            std::cout<< "found same lumi: run:ls:nEvt " << run <<":" <<lumi<<":"<<nEvt<<std::endl;
        }
    }
    if(isSameEvt && isSameRun && isSameLumi){
        passesEventListCut = kTRUE;
        if(printInfo){
            std::cout<< "passEventListCut " << std::endl;
        }
        break;
    }
  }
  
  _hEventListBefore->Fill(passesEventListCut);



  ostringstream cutFlowNameStream;
                                
  TString cutFlowName;            

  cutFlowNameStream << "EventList.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  if ( !passesEventListCut ){
    GetCutFlowTable()->FailCut(cutFlowName);
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowName);
    _hEventListAfter->Fill(passesEventListCut);
  }

  return passesEventListCut;

} //Apply












