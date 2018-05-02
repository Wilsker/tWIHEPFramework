/******************************************************************************
 * CutMassL.cpp                                                       *
 *                                                                            *
 * Cuts on the requirement of a good primary vertex                           *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutMassL class                              *
 *    CutMassL()                     -- Parameterized Constructor         *
 *    ~CutMassL()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutMassL"                *
 *                                                                            *
 * Private Data Members of CutMassL class                                 *
 *    myTH1F* _hMassLBefore;    -- Hist of PV before cut        *
 *    myTH1F* _hMassLAfter;     -- Hist of PV after cut         *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutMassL.hpp"
#include <iostream>

using namespace std;

/******************************************************************************
 * CutMassL::CutMassL(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutMassL::CutMassL(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutMassL


/******************************************************************************
 * CutMassL::~CutMassL()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutMassL::~CutMassL()
{
  
}//~CutMassL

/******************************************************************************
 * void CutMassL::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutMassL::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << "MassLBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << "MassL Before";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << "MassLAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << "MassL After";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hMassLBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 100, 0.0, 200.);
  _hMassLBefore -> SetXAxisTitle("DiLooseLepton Mass");
  _hMassLBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hMassLAfter=  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 100, 0.0, 200.);
  _hMassLAfter-> SetXAxisTitle("DiLooseLepton Mass");
  _hMassLAfter-> SetYAxisTitle("Events");


  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << "MassL Cut";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << "MassL.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  // ***********************************************
  // Get the PV IDs from the config file. Perhaps these should be included as an object
  // ***********************************************

  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv * config = EventContainerObj->GetConfig();

  //Then set the cuts here.
  _MassLMin = config -> GetValue("Cut.Event.MassLveto.Min",0.0);
  _MassLMax = config -> GetValue("Cut.Event.MassLveto.Max",999.0);


}//BookHistograms()

/******************************************************************************
 * Bool_t CutMassL::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutMassL::Apply()
{

  EventContainer *EventContainerObj = GetEventContainer();

  Bool_t passesMassLCut = kTRUE;

  Float_t MassL = EventContainerObj->massL;

  _hMassLBefore->Fill(MassL);



  ostringstream cutFlowNameStream;
                                
  TString cutFlowName;            

  cutFlowNameStream << "MassL.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  if (MassL > _MassLMin && MassL < _MassLMax){
    passesMassLCut = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowName);
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowName);
    _hMassLAfter->Fill(MassL);
  }

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !passesMassLCut ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail passesMassLCut: MassL is " << MassL  <<  std::endl; 
  }
  return passesMassLCut;

} //Apply












