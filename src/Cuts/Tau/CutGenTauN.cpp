/******************************************************************************
 * CutGenTauN.hpp                                                                *
 *                                                                            *
 * Cuts on tau Number                                                         *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutGenTauN class                                   *
 *    CutGenTauN()                     -- Parameterized Constructor              *
 *    ~CutGenTauN()                    -- Destructor                             *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutGenTauN"                     *
 *                                                                            *
 * Private Data Members of CutGenTauN class                                      *
 *    myTH1F* _hTauNumberBefore;    -- Hist mu Number before cut              *
 *    myTH1F* _hTauNumberAfter;     -- Hist mu Number of jets after cut       *
 *                                                                            *
 *    Int_t _TauNumberMin;          -- Minimum Tau Number                     *
 *    Int_t _TauNumberMax;          -- Maximum Tau Number                     *
 *                                                                            *
 * History                                                                    *
 *      22 Aug 2007 - Created by P. Ryan                                      *
 *****************************************************************************/


#include "SingleTopRootAnalysis/Cuts/Tau/CutGenTauN.hpp"
#include<iostream>

using namespace std;


/******************************************************************************
 * CutGenTauN::CutGenTauN(EventContainer *EventContainerObj)                        *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutGenTauN::CutGenTauN(EventContainer *EventContainerObj, TString tauTypePassed)
{
  if(
      tauTypePassed.CompareTo("Gen")
     ){
    std::cout << "ERROR " << "<CutGenTauN::CutGenTauN()> "
	      << "Must Gen to constructor" << std::endl;
    exit(8);
  } //if
  tauType = tauTypePassed;

  SetEventContainer(EventContainerObj);
} // CutGenTauN


/******************************************************************************
 * CutGenTauN::~CutGenTauN()                                                        *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutGenTauN::~CutGenTauN()
{

}//~CutGenTauN

/******************************************************************************
 * void CutGenTauN::BookHistogram()                                              *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutGenTauN::BookHistogram(){

  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << tauType << "TauNumberBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << tauType << "Tau Number Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << tauType << "TauNumberAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << tauType << "Tau Number After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();



  // Number of Taus
  _hTauNumberBefore =  DeclareTH1F(histNameBefore.Data(),histTitleBefore.Data(),10, 0, 10.0);
  _hTauNumberBefore -> SetXAxisTitle("N_{#tau}");
  _hTauNumberBefore -> SetYAxisTitle("Events");


  // Number of Taus
  _hTauNumberAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 10, 0, 10);
  _hTauNumberAfter -> SetXAxisTitle("N_{#tau}");
  _hTauNumberAfter -> SetYAxisTitle("Events");

  // Get configuration
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Make name in configuration file depending upon tau type
  std::ostringstream configMinStream;
  configMinStream << "Cut.Tau." << tauType.Data() << ".Number.Min";
  TString configMin = configMinStream.str().c_str();

  std::ostringstream configMaxStream;
  configMaxStream << "Cut.Tau." << tauType.Data() << ".Number.Max";
  TString configMax = configMaxStream.str().c_str();

  // Use configuration to set min/max number of taus to cut on
  _TauNumberMin  = config -> GetValue(configMin.Data(), 999);
  _TauNumberMax  = config -> GetValue(configMax.Data(), 999);

  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << tauType.Data() << " Tau : " << "N >= " << _TauNumberMin;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << tauType.Data() << "Tau.Number.Min";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());

  // Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << tauType.Data() << " Tau : " << "N <= " << _TauNumberMax;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << tauType.Data() << "Tau.Number.Max";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << tauType.Data() << " Tau : " << _TauNumberMin << " <= N <= " << _TauNumberMax;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << tauType.Data() << "Tau.Number.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

}//BookHistograms()

/******************************************************************************
 * Bool_t CutGenTauN::Apply()                                                    *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of taus                                                  *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutGenTauN::Apply()
{

  Int_t TauNumber  = 0;

  // Flags
  Bool_t TauNumberMinPass    = kTRUE;
  Bool_t TauNumberMaxPass    = kTRUE;

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();


  if(tauType=="Gen" )TauNumber = EventContainerObj -> MCTaus.size();

  // Fill the histograms before the cuts
  _hTauNumberBefore    -> Fill(TauNumber);

  // ***********************************************
  // Fill cut flow table
  // ***********************************************

  // Names for Cut Flow Table
  ostringstream cutFlowNameMinStream;
  ostringstream cutFlowNameMaxStream;
  ostringstream cutFlowNameAllStream;

  TString cutFlowNameMin;
  TString cutFlowNameMax;
  TString cutFlowNameAll;

  cutFlowNameMinStream << tauType.Data() << "Tau.Number.Min";
  cutFlowNameMin = cutFlowNameMinStream.str().c_str();

  cutFlowNameMaxStream << tauType.Data() << "Tau.Number.Max";
  cutFlowNameMax = cutFlowNameMaxStream.str().c_str();

  cutFlowNameAllStream << tauType.Data() << "Tau.Number.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();

  // Cut on Min Number of taus
  // 999 value for Min means there is no Min cut
  if( (_TauNumberMin != 999) && (TauNumber < _TauNumberMin) ){
     TauNumberMinPass = kFALSE;
     GetCutFlowTable()->FailCut(cutFlowNameMin.Data());
  }//if
  else{
    GetCutFlowTable() -> PassCut(cutFlowNameMin.Data());
  } //else

  // Cut on Max number of taus
  // 999 value for Min means there is no Min cut
  if( (_TauNumberMax != 999) && (TauNumber > _TauNumberMax) ){
     TauNumberMaxPass = kFALSE;
     GetCutFlowTable()->FailCut(cutFlowNameMax.Data());
  } //if
  else{
    GetCutFlowTable() -> PassCut(cutFlowNameMax.Data());
  } //else

  // Fill Histogram after cuts
  if(TauNumberMinPass && TauNumberMaxPass){
    _hTauNumberAfter -> Fill(TauNumber);
    GetCutFlowTable() -> PassCut(cutFlowNameAll.Data());
  } //if
  else GetCutFlowTable() -> FailCut(cutFlowNameAll.Data());

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !(TauNumberMinPass && TauNumberMaxPass)){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail CutGenTauN " << tauType <<" TauNumber is "<<TauNumber <<" TauNumberMin " << TauNumberMinPass <<" TauNumberMax " << TauNumberMaxPass<< std::endl;
  }
  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = TauNumberMinPass && TauNumberMaxPass ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return(TauNumberMinPass && TauNumberMaxPass);
  }


} //Apply
