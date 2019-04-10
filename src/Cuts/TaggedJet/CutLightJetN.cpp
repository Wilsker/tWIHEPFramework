/******************************************************************************
 * CutLightJetN.hpp                                                                *
 *                                                                            *
 * Cuts on number of jets in an event                                         *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutNJet class                                   *
 *    CutLightJetN()                         -- Parameterized Constructor          *
 *    ~CutLightJetN()                        -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutLightJetN"                  *
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

#include "SingleTopRootAnalysis/Cuts/TaggedJet/CutLightJetN.hpp"
#include <iostream>
#include <sstream>

using namespace std;


/******************************************************************************
 * CutLightJetN::CutLightJetN(EventContainer *EventContainerObj)                      *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutLightJetN::CutLightJetN(EventContainer *EventContainerObj, Int_t nJetsDefault)
{
  SetEventContainer(EventContainerObj);
  _JetNumberMin = nJetsDefault; //Allows for an over-riding of the default nJets option so we can not have hundreds of config files
  _JetNumberMax = nJetsDefault;
} // CutLightJetN


/******************************************************************************
 * CutLightJetN::~CutLightJetN()                                                      *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLightJetN::~CutLightJetN()
{
  
}//~CutLightJetN

/******************************************************************************
 * void CutLightJetN::BookHistogram()                                             *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLightJetN::BookHistogram(){
  
  // Histogram of events before cut on number of jets
  _hJetNumberBefore =  DeclareTH1F("LightJetNumberBefore","Number of Light Jets before the cut",20, 0.0, 20.0);
  _hJetNumberBefore -> SetXAxisTitle("N_{LightJet}");
  _hJetNumberBefore -> SetYAxisTitle("Events");

  // Histogram of events after cut on number of jets
  _hJetNumberAfter =  DeclareTH1F("LightJetNumberAfter","Number of Light Jets after the cut",20, 0.0, 20.0);
  _hJetNumberAfter -> SetXAxisTitle("N_{LightJet}");
  _hJetNumberAfter -> SetYAxisTitle("Events");
  
  // Get configuration
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Use configuration to set min and max number of jets to cut on, if we haven't over-ridden this from the command line
  if (_JetNumberMax < 0){
    _JetNumberMin = config -> GetValue("Cut.LightJet.Number.Min", 999);
    _JetNumberMax = config -> GetValue("Cut.LightJet.Number.Max", 999);
  }
  //
  // also add these two cuts to the cut flow table
  ostringstream titleStr;
  titleStr <<"LightJet : " << "N >=" << _JetNumberMin;
  TString tTitle(titleStr.str().c_str());
  GetCutFlowTable()->AddCutToFlow("LightJet.Number.Min",tTitle);
  titleStr.str("");
  titleStr <<"LightJet : N <= "<<_JetNumberMax;
  tTitle=titleStr.str().c_str();
  GetCutFlowTable()->AddCutToFlow("LightJet.Number.Max",tTitle);
  // also add the overal pass rate
  titleStr.str("");
  titleStr <<"LightJet : "<< _JetNumberMin<<" <= N <= "<<_JetNumberMax;
  tTitle=titleStr.str().c_str();
  GetCutFlowTable()->AddCutToFlow("LightJet.Number.All",tTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLightJetN::Apply()                                                   *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLightJetN::Apply()
{
  //cout<<"Begin of CutLightJetN::Apply()"<<endl;

  // Get Event Tree
  EventContainer *evObj = GetEventContainer();

  Int_t JetNumber = evObj->jets.size();
  Int_t NBLoose = std::count_if(evObj->jets.begin(), evObj->jets.end(), [](const Jet& x){return x.isLooseBdisc();});
  Int_t NFwdJet = evObj->forwardjets.size();
  Int_t LightJetNumber = JetNumber - NBLoose + NFwdJet;
  // Fill the histogram before the cut
  _hJetNumberBefore -> Fill(LightJetNumber);

  // Flags 
  Bool_t JetNumberMinPass    = kTRUE;   // Event passes min cut
  Bool_t JetNumberMaxPass    = kTRUE;   // Event passes max cut

  // Cut on Min Pt of Jet
  // Negative cut value for Min means there is no Min cut
  if( (_JetNumberMin != 999) && (LightJetNumber < _JetNumberMin) ){
     JetNumberMinPass = kFALSE;
     GetCutFlowTable()->FailCut("LightJet.Number.Min");
  }//if
  else{
    GetCutFlowTable() -> PassCut("LightJet.Number.Min");
  } //else

  // Cut on Min Pt of Jet
  // Negative cut value for Min means there is no Min cut
  if( (_JetNumberMax != 999) && (LightJetNumber > _JetNumberMax) ){
     JetNumberMaxPass = kFALSE;
     GetCutFlowTable()->FailCut("LightJet.Number.Max");
  } //if
  else{
    GetCutFlowTable() -> PassCut("LightJet.Number.Max");
  } //else

  // Fill Histogram after cuts
  if(JetNumberMinPass && JetNumberMaxPass){
    _hJetNumberAfter -> Fill(LightJetNumber);
    GetCutFlowTable() -> PassCut("LightJet.Number.All");
  } //if
  else GetCutFlowTable() -> FailCut("LightJet.Number.All");
  
  if( evObj->_sync >= 80  && evObj->_sync != 99 && evObj->_debugEvt == evObj->eventNumber && !(JetNumberMinPass && JetNumberMaxPass)){
    std::cout<< " Event " << evObj->_debugEvt <<" Fail CutLightJetN :  LightJetNumber Is " << LightJetNumber << " JetNumberMinPass "<<JetNumberMinPass <<" JetNumberMaxPass " << JetNumberMaxPass<< std::endl; 
  }

  if(evObj->_SaveCut ==1 ){
    Double_t flag = JetNumberMinPass && JetNumberMaxPass ? 1:0;
    evObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return(JetNumberMinPass && JetNumberMaxPass);
  }

} //Apply












