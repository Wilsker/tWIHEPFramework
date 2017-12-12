/******************************************************************************
 * CutMetLD.cpp                                                       *
 *                                                                            *
 * Cuts on the requirement of a good primary vertex                           *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutMetLD class                              *
 *    CutMetLD()                     -- Parameterized Constructor         *
 *    ~CutMetLD()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutMetLD"                *
 *                                                                            *
 * Private Data Members of CutMetLD class                                 *
 *    myTH1F* _hMetLDBefore;    -- Hist of PV before cut        *
 *    myTH1F* _hMetLDAfter;     -- Hist of PV after cut         *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutMetLD.hpp"
#include <iostream>

using namespace std;

/******************************************************************************
 * CutMetLD::CutMetLD(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutMetLD::CutMetLD(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutMetLD


/******************************************************************************
 * CutMetLD::~CutMetLD()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutMetLD::~CutMetLD()
{
  
}//~CutMetLD

/******************************************************************************
 * void CutMetLD::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutMetLD::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << "MetLDBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << "MetLD Before";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << "MetLDAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << "MetLD After";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hMetLDBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 50, 0.0, 5.);
  _hMetLDBefore -> SetXAxisTitle("MetLD ");
  _hMetLDBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hMetLDAfter=  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 50, 0.0, 5.);
  _hMetLDAfter-> SetXAxisTitle("MetLD ");
  _hMetLDAfter-> SetYAxisTitle("Events");


  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << "MetLD Cut";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << "MetLD.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  // ***********************************************
  // Get the PV IDs from the config file. Perhaps these should be included as an object
  // ***********************************************

  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv * config = EventContainerObj->GetConfig();

  //Then set the cuts here.
  _MetLDMin = config -> GetValue("Cut.Event.MetLD.Min",0.0);
  _MetLDMax = config -> GetValue("Cut.Event.MetLD.Max",999.0);


}//BookHistograms()

/******************************************************************************
 * Bool_t CutMetLD::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutMetLD::Apply()
{

  EventContainer *EventContainerObj = GetEventContainer();

  Bool_t passesMetLDCut = kTRUE;
  
  Bool_t isEE = kFALSE;
  
  std::vector<Lepton> leptonVector;

  leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  
  if(leptonVector.size()>=2 && fabs(leptonVector[0].pdgId())==11 && fabs(leptonVector[1].pdgId())==11)isEE = kTRUE;

  Float_t MetLD = EventContainerObj->metLD;

  _hMetLDBefore->Fill(MetLD);



  ostringstream cutFlowNameStream;
                                
  TString cutFlowName;            

  cutFlowNameStream << "MetLD.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  if (MetLD < _MetLDMin && isEE ){
    passesMetLDCut = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowName);
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowName);
    _hMetLDAfter->Fill(MetLD);
  }

  return passesMetLDCut;

} //Apply












