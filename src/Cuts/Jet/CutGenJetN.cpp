/******************************************************************************
 * CutGenJetN.hpp                                                                *
 *                                                                            *
 * Cuts on number of jets in an event                                         *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutNJet class                                   *
 *    CutGenJetN()                         -- Parameterized Constructor          *
 *    ~CutGenJetN()                        -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutGenJetN"                  *
 *                                                                            *
 * Private Data Members of CutNJet class                                      *
 *    myTH1F* _hJetNumberBefore         -- Hist of Num of jets before cuts    *
 *    myTH1F* _hJetNumberAfter          -- Hist of Num of jets before cuts    *
 *    Int_t _JetNumberMin;              -- Minimum number of jets to require  *
 *    Int_t _JetNumberMax;              -- Maximum number of jets allowed     *
 *                                                                            *
 * History                                                                    *
 *       7 Nov 2006 - Created by R. Schwienhorst for ATLAS                    *
 *      10 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      17 Nov 2006 - RS: add interface to cutFlowTable.                      *
 *      11 Jan 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Jet/CutGenJetN.hpp"
#include <iostream>
#include <sstream>

using namespace std;


/******************************************************************************
 * CutGenJetN::CutGenJetN(EventContainer *EventContainerObj)                      *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutGenJetN::CutGenJetN(EventContainer *EventContainerObj, Int_t nJetsDefault)
{
  SetEventContainer(EventContainerObj);
  _JetNumberMin = nJetsDefault; //Allows for an over-riding of the default nJets option so we can not have hundreds of config files
  _JetNumberMax = nJetsDefault;
} // CutGenJetN


/******************************************************************************
 * CutGenJetN::~CutGenJetN()                                                      *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutGenJetN::~CutGenJetN()
{

}//~CutGenJetN

/******************************************************************************
 * void CutGenJetN::BookHistogram()                                             *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutGenJetN::BookHistogram(){

  // Histogram of events before cut on number of jets
  _hJetNumberBefore =  DeclareTH1F("JetNumberBefore","Number of Jets before the cut",20, 0.0, 20.0);
  _hJetNumberBefore -> SetXAxisTitle("N_{Jet}");
  _hJetNumberBefore -> SetYAxisTitle("Events");

  // Histogram of events after cut on number of jets
  _hJetNumberAfter =  DeclareTH1F("JetNumberAfter","Number of Jets after the cut",20, 0.0, 20.0);
  _hJetNumberAfter -> SetXAxisTitle("N_{Jet}");
  _hJetNumberAfter -> SetYAxisTitle("Events");

  // Get configuration
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  _JetPtCutMin  = config -> GetValue("Cut.Jet.Gen.Pt.Min", 999);
  _JetPtCutMax  = config -> GetValue("Cut.Jet.Gen.Pt.Min", 999);
  _JetEtaCutMax  = config -> GetValue("Cut.Jet.Gen.Eta.Max", 999);
  // Use configuration to set min and max number of jets to cut on, if we haven't over-ridden this from the command line
  if (_JetNumberMax < 0){
    _JetNumberMin = config -> GetValue("Cut.Jet.Gen.Number.Min", 999);
    _JetNumberMax = config -> GetValue("Cut.Jet.Gen.Number.Max", 999);
  }

  //
  // also add these two cuts to the cut flow table
  ostringstream titleStr;
  titleStr <<"Jet : " << "N >=" << _JetNumberMin;
  TString tTitle(titleStr.str().c_str());
  GetCutFlowTable()->AddCutToFlow("Jet.Gen.Number.Min",tTitle);
  titleStr.str("");
  titleStr <<"Jet : N <= "<<_JetNumberMax;
  tTitle=titleStr.str().c_str();
  GetCutFlowTable()->AddCutToFlow("Jet.Gen.Number.Max",tTitle);
  // also add the overal pass rate
  titleStr.str("");
  titleStr <<"Jet : "<< _JetNumberMin<<" <= N <= "<<_JetNumberMax;
  tTitle=titleStr.str().c_str();
  GetCutFlowTable()->AddCutToFlow("Jet.Gen.Number.All",tTitle);

}//BookHistograms()

/******************************************************************************
 * Bool_t CutGenJetN::Apply()                                                   *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutGenJetN::Apply()
{
  //cout<<"Begin of CutGenJetN::Apply()"<<endl;

  // Get Event Tree
  EventContainer *evObj = GetEventContainer();

  Int_t JetNumber = 0;
  double LeadingJetPt = 0;

  // Fill the histogram before the cut
  _hJetNumberBefore -> Fill(JetNumber);

  // Flags
  Bool_t JetNumberMinPass    = kTRUE;   // Event fails min cut
  Bool_t JetNumberMaxPass    = kTRUE;
  Bool_t JetDeltaRPass    = kTRUE;

  // Cut on Min Pt of Jet
  //std::vector<MCJet> jetVector;
  std::vector<Jet> jetVector;
  //jetVector.assign(evObj -> MCJets.begin(), evObj -> MCJets.end());
  jetVector.assign(evObj -> jets.begin(), evObj -> jets.end());
  std::vector<MCElectron> EleVector;
  EleVector.assign(evObj -> MCElectrons.begin(), evObj -> MCElectrons.end());
  std::vector<MCMuon> MuVector;
  MuVector.assign(evObj -> MCMuons.begin(), evObj -> MCMuons.end());

  for (auto const jet : jetVector){
    if (jet.Pt() > LeadingJetPt) LeadingJetPt = jet.Pt();
    if (jet.Pt() > _JetPtCutMin && std::abs(jet.Eta()) < _JetEtaCutMax ){
      for (auto const lep : EleVector){ if (jet.DeltaR(lep)<0.4){ JetDeltaRPass = kFALSE; } }
      for (auto const lep : MuVector){ if (jet.DeltaR(lep)<0.4){ JetDeltaRPass = kFALSE; } }
      if (JetDeltaRPass == kTRUE){JetNumber++;}
      else {continue;}
    }
  }

  // Negative cut value for Min means there is no Min cut
  if( (_JetNumberMin != 999) && (JetNumber < _JetNumberMin) ){
     JetNumberMinPass = kFALSE;
     GetCutFlowTable()->FailCut("Jet.Gen.Number.Min");
  }//if
  else{
    GetCutFlowTable() -> PassCut("Jet.Gen.Number.Min");
  } //else

  // Cut on Min Pt of Jet
  // Negative cut value for Min means there is no Min cut
  if( (_JetNumberMax != 999) && (JetNumber > _JetNumberMax) ){
     JetNumberMaxPass = kFALSE;
     //GetCutFlowTable()->FailCut("Jet.Number.Max");
  } //if
  else{
    GetCutFlowTable() -> PassCut("Jet.Number.Max");
  }//else

  // Fill Histogram after cuts
  if(JetNumberMinPass && JetNumberMaxPass){
    _hJetNumberAfter -> Fill(JetNumber);
    GetCutFlowTable() -> PassCut("Jet.Gen.Number.All");
  } //if
  else GetCutFlowTable() -> FailCut("Jet.Gen.Number.All");

  if( evObj->_sync >= 80  && evObj->_sync != 99 && evObj->_debugEvt == evObj->eventNumber && !(JetNumberMinPass && JetNumberMaxPass)){
    std::cout<< " Event " << evObj->_debugEvt <<" Fail CutGenJetN :  JetNumber Is " << JetNumber << " JetNumberMinPass "<<JetNumberMinPass <<" JetNumberMax " << JetNumberMaxPass<< std::endl;
  }

  if(evObj->_SaveCut ==1 ){
    Double_t flag = JetNumberMinPass && JetNumberMaxPass ? 1:0;
    evObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return(JetNumberMinPass && JetNumberMaxPass);
  }

} //Apply
