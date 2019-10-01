/******************************************************************************
 * CutGenBJetN.hpp                                                          *
 *                                                                            *
 * Cuts on number of tagged jets in an event                                  *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutGenBJetN class                             *
 *    CutGenBJetN()                   -- Parameterized Constructor          *
 *    ~CutGenBJetN()                  -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutGenBJetN"            *
 *                                                                            *
 * Private Data Members of CutGenBJetN                                      *
 *    myTH1F* _hbLooseJetNumberBefore         -- Hist of Num of jets before cuts    *
 *    myTH1F* _hbLooseJetNumberAfter          -- Hist of Num of jets before cuts    *
 *    Int_t _bJetNumberMin;              -- Minimum number of jets to require  *
 *    Int_t _bJetNumberMax;              -- Maximum number of jets allowed     *
 *                                                                            *
 * History                                                                    *
 *      23 Feb 2007 - Created by P. Ryan                                      *
 *****************************************************************************/


#include "SingleTopRootAnalysis/Cuts/TaggedJet/CutGenBJetN.hpp"
#include <iostream>
#include <sstream>

using namespace std;


/******************************************************************************
 * CutGenBJetN::CutGenBJetN(EventContainer *EventContainerObj)            *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutGenBJetN::CutGenBJetN(EventContainer *EventContainerObj)
{
  SetEventContainer(EventContainerObj);
}

/******************************************************************************
 * CutGenBJetN::~CutGenBJetN()                                            *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutGenBJetN::~CutGenBJetN()
{

}//~CutGenBJetN

/******************************************************************************
 * void CutGenBJetN::BookHistogram()                                        *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutGenBJetN::BookHistogram(){

  // Histogram of events before cut on number of jets
  _hbJetNumberBefore =  DeclareTH1F("bJetNumberBefore","Number of B Jets before the cut",10, 0.0, 10.0);
  _hbJetNumberBefore -> SetXAxisTitle("N_{Jet}^{B}");
  _hbJetNumberBefore -> SetYAxisTitle("Events");

  // Histogram of events after cut on number of jets
  _hbJetNumberAfter =  DeclareTH1F("bJetNumberAfter","Number of B Jets after the cut",10, 0.0, 10.0);
  _hbJetNumberAfter -> SetXAxisTitle("N_{Jet}^{B}");
  _hbJetNumberAfter -> SetYAxisTitle("Events");

  // Get configuration
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Use configuration to set min and max number of jets to cut on if default value used
  if (_bJetNumberMax < 0.){
    _bJetNumberMin = config -> GetValue("Cut.BJet.Gen.Number.Min", 999);
    _bJetNumberMax = config -> GetValue("Cut.BJet.Gen.Number.Max", 999);
  }

  //
  // also add these two cuts to the cut flow table
  ostringstream titleStr;
  titleStr <<"BJet : " << "N >=" << _bJetNumberMin;
  TString tTitle(titleStr.str().c_str());
  GetCutFlowTable()->AddCutToFlow("BJet.Gen.Number.Min",tTitle);
  titleStr.str("");
  titleStr <<"BJet : N <= "<<_bJetNumberMax;
  tTitle=titleStr.str().c_str();
  GetCutFlowTable()->AddCutToFlow("BJet.Gen.Number.Max",tTitle);

  // also add the overal pass rate
  titleStr.str("");
  titleStr <<"B Jet : "<< _bJetNumberMin<<" <= N <= "<<_bJetNumberMax;
  tTitle=titleStr.str().c_str();
  GetCutFlowTable()->AddCutToFlow("BJet.Gen.Number.All",tTitle);

}//BookHistograms()

/******************************************************************************
 * Bool_t CutGenBJetN::Apply()                                              *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutGenBJetN::Apply()
{
  //cout<<"Begin of CutGenBJetN::Apply()"<<endl;

  // Get Event Tree
  EventContainer *evObj = GetEventContainer();

  Int_t bJetNumber = 0;

  // Fill the histogram before the cut
  _hbJetNumberBefore -> Fill(bJetNumber);

  // Flags
  Bool_t bJetNumberMinPass    = kTRUE;   // Event passes min cut
  Bool_t bJetNumberMaxPass    = kTRUE;   // Event passes max cut

  //std::vector<MCJet> bjetVector;
  //bjetVector.assign(evObj -> MCBJets.begin(), evObj -> MCBJets.end() );
  //for ( auto const jet : bjetVector) {
  for ( auto const jet : evObj->jets) {
    if ( jet.Pt() > 25 && std::abs(jet.Eta()) < 2.5 && jet.hadronFlavour()==5){
      bJetNumber++;
    }
  }

  // Negative cut value for Min means there is no Min cut
  if( (_bJetNumberMin != 999) && (bJetNumber < _bJetNumberMin) ){
     bJetNumberMinPass = kFALSE;
     GetCutFlowTable()->FailCut("BJet.Gen.Number.Min");
  }//if
  else{
    GetCutFlowTable() -> PassCut("BJet.Gen.Number.Min");
  } //else

  // Cut on bLoose Max
  // Negative cut value for Min means there is no Min cut
  if( (_bJetNumberMax != 999) && (bJetNumber > _bJetNumberMax) ){
     bJetNumberMaxPass = kFALSE;
     GetCutFlowTable()->FailCut("BJet.Gen.Number.Max");
  } //if
  else{
    GetCutFlowTable() -> PassCut("BJet.Gen.Number.Max");
  } //else

  // Fill Histogram after cuts
  if((bJetNumberMinPass && bJetNumberMaxPass) ) {
        _hbJetNumberAfter -> Fill(bJetNumber);
        GetCutFlowTable() -> PassCut("BJet.Gen.Number.All");
  } //if
  else GetCutFlowTable() -> FailCut("BJet.Gen.Number.All");

  if( evObj->_sync >= 80  && evObj->_sync != 99 && evObj->_debugEvt == evObj->eventNumber && !(bJetNumberMinPass && bJetNumberMaxPass) ) {
      std::cout<< " Event " << evObj->_debugEvt <<" Fail CutGenBJetN : bJetLooseN "<< bJetNumber << " bJetNumberMin " << bJetNumberMinPass <<" bJetNumberMax " << bJetNumberMaxPass << std::endl;
  }
  if(evObj->_SaveCut ==1 ){
      Double_t flag = (bJetNumberMinPass && bJetNumberMaxPass) ? 1:0;
      evObj->Flag_cuts.push_back(flag);
      return kTRUE;
  }else{
      return(bJetNumberMinPass && bJetNumberMaxPass);
  }


} //Apply
