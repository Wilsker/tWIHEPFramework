/******************************************************************************
 * CutGenLeptonN.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutGenLeptonN class                                *
 *    CutGenLeptonN()                     -- Parameterized Constructor           *
 *    ~CutGenLeptonN()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutGenLeptonN"                  *
 *                                                                            *
 * Private Data Members of CutGenLeptonN class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutGenLeptonN.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutGenLeptonN::CutGenLeptonN(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutGenLeptonN::CutGenLeptonN(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( leptonTypePassed.CompareTo("Gen") ){
    std::cout << "ERROR " << "<CutGenLeptonN::CutGenLeptonN()> "
	      << "Must pass Gen to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutGenLeptonN


/******************************************************************************
 * CutGenLeptonN::~CutGenLeptonN()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutGenLeptonN::~CutGenLeptonN()
{

}//~CutGenLeptonN

/******************************************************************************
 * void CutGenLeptonN::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutGenLeptonN::BookHistogram(){

  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << "LeptonNumberBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << "Lepton Number Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << "LeptonNumberAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << "Lepton Number After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************

  // Histogram before cut
  _hLeptonNumberBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 10, 0.0, 10.0);
  _hLeptonNumberBefore -> SetXAxisTitle("N_{#lep}");
  _hLeptonNumberBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonNumberAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 10, 0.0, 10);
  _hLeptonNumberAfter -> SetXAxisTitle("N_{#mu}");
  _hLeptonNumberAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Make name in configuration file depending upon lepton type (all, Gen)
  std::ostringstream configMinStream;
  configMinStream << "Cut.Lepton." << leptonType.Data() << ".Number.Min";
  TString configMin = configMinStream.str().c_str();

  std::ostringstream configMaxStream;
  configMaxStream << "Cut.Lepton." << leptonType.Data() << ".Number.Max";
  TString configMax = configMaxStream.str().c_str();

  // Use configuration to set min and max number of leptons to cut on
  _LeptonNumberMin  = config -> GetValue(configMin.Data(), 999);
  _LeptonNumberMax  = config -> GetValue(configMax.Data(), 999);

  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << leptonType.Data() << " Lepton : " << "N >= " << _LeptonNumberMin;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << leptonType.Data() << "Lepton.Number.Min";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());

  // Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << leptonType.Data() << " Lepton : " << "N <= " << _LeptonNumberMax;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Lepton.Number.Max";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << leptonType.Data() << " Lepton : " << _LeptonNumberMin << " <= N <= " << _LeptonNumberMax;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Lepton.Number.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);


}//BookHistograms()

/******************************************************************************
 * Bool_t CutGenLeptonN::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutGenLeptonN::Apply()
{

  // ***********************************************
  // Get Number of Gen Leptons and fill histograms
  // ***********************************************

  // Initialize number of leptons
  Int_t MuonNumber      = 0;
  Int_t ElectronNumber  = 0;
  Int_t LeptonNumber    = 0;

  // Flags
  Bool_t LeptonNumberMinPass = kTRUE;   // Event passes min pT lepton cuts
  Bool_t LeptonNumberMaxPass = kTRUE;   // Event passes max pT lepton cuts

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  // Get variables from EventContainerObj - Depends on lepton Type
  if(      ! leptonType.CompareTo("Gen") ){

    //genElectrons.assign(evtObj -> MCElectrons.begin(), evtObj -> MCElectrons.end());
    //genMuons.assign(evtObj -> MCMuons.begin(), evtObj -> MCMuons.end());

    MuonNumber     = EventContainerObj -> MCMuons.size();
    ElectronNumber = EventContainerObj -> MCElectrons.size();

  }
  else{
    std::cout << "ERROR " << "<CutGenLeptonN::Apply()> " << "leptonType has an incorrect value of: " << leptonType.Data() << std::endl;
    exit(8);
  }

  // Add muons and electrons to get lepton number
  if( ! leptonType.CompareTo("Gen") )
    LeptonNumber = MuonNumber + ElectronNumber;

  // Fill the histograms before the cuts
  _hLeptonNumberBefore    -> Fill(LeptonNumber);

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

  cutFlowNameMinStream << leptonType.Data() << "Lepton.Number.Min";
  cutFlowNameMin = cutFlowNameMinStream.str().c_str();

  cutFlowNameMaxStream << leptonType.Data() << "Lepton.Number.Max";
  cutFlowNameMax = cutFlowNameMaxStream.str().c_str();

  cutFlowNameAllStream << leptonType.Data() << "Lepton.Number.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();

  // Cut on Min Number of Leptons
  // 999 value for Min means there is no Min cut
  if( (_LeptonNumberMin != 999) && (LeptonNumber < _LeptonNumberMin) ){
    LeptonNumberMinPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameMin.Data());
  }//if
  else{
    GetCutFlowTable() -> PassCut(cutFlowNameMin.Data());
  } //else

  // Cut on Max Number Leptons
  // 999 value for Max means there is no Max cut
  if( (_LeptonNumberMax != 999) && (LeptonNumber > _LeptonNumberMax) ){
    LeptonNumberMaxPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameMax.Data());
  } //if
  else{
    GetCutFlowTable() -> PassCut(cutFlowNameMax.Data());
  } //else

  // Cut on Min and Max Number of Leptons
  if(LeptonNumberMinPass && LeptonNumberMaxPass){
    _hLeptonNumberAfter -> Fill(LeptonNumber);
    GetCutFlowTable() -> PassCut(cutFlowNameAll.Data());
  } //if
  else GetCutFlowTable() -> FailCut(cutFlowNameAll.Data());

  // ***********************************************
  // Return result of Min and Max Cut
  // ***********************************************

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !(LeptonNumberMinPass && LeptonNumberMaxPass)){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail CutGenLeptonN " << leptonType << " LeptonNumber "<< LeptonNumber << " LeptonNumberMin " << LeptonNumberMinPass <<" LeptonNumberMax " << LeptonNumberMaxPass<< std::endl;
  }

  //std::cout<< "_SaveCut is " << EventContainerObj->_SaveCut << std::endl;
  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = LeptonNumberMinPass && LeptonNumberMaxPass ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    //std::cout<< "in cut LeptonN always return true ";
    return kTRUE;
  }else{
    return(LeptonNumberMinPass && LeptonNumberMaxPass);
  }

} //Apply
