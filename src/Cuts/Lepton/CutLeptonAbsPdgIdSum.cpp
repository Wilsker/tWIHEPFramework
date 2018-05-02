/******************************************************************************
 * CutLeptonAbsPdgIdSum.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonAbsPdgIdSum class                                *
 *    CutLeptonAbsPdgIdSum()                     -- Parameterized Constructor           *
 *    ~CutLeptonAbsPdgIdSum()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonAbsPdgIdSum"                  *
 *                                                                            *
 * Private Data Members of CutLeptonAbsPdgIdSum class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B. Li                                        *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonAbsPdgIdSum.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonAbsPdgIdSum::CutLeptonAbsPdgIdSum(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonAbsPdgIdSum::CutLeptonAbsPdgIdSum(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( leptonTypePassed.CompareTo("All") && leptonTypePassed.CompareTo("UnIsolated") && leptonTypePassed.CompareTo("Isolated") && 
      leptonTypePassed.CompareTo("Tight") && leptonTypePassed.CompareTo("Veto")
      && leptonTypePassed.CompareTo("TTHFake")
       ){
    std::cout << "ERROR " << "<CutLeptonAbsPdgIdSum::CutLeptonAbsPdgIdSum()> " 
	      << "Must pass All, Tight, Veto, Isolated, TTHFake or UnIsolated to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonAbsPdgIdSum


/******************************************************************************
 * CutLeptonAbsPdgIdSum::~CutLeptonAbsPdgIdSum()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonAbsPdgIdSum::~CutLeptonAbsPdgIdSum()
{
  
}//~CutLeptonAbsPdgIdSum

/******************************************************************************
 * void CutLeptonAbsPdgIdSum::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonAbsPdgIdSum::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << "DileptonAbsPdgIdSumBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << "Dilepton AbsPdgIdSum Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << "DileptonAbsPdgIdSumAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << "Dilepton AbsPdgIdSum After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonAbsPdgIdSumBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 10, 20.5, 31.5);
  _hLeptonAbsPdgIdSumBefore -> SetXAxisTitle("Dilepton SumAbsPdgId");
  _hLeptonAbsPdgIdSumBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonAbsPdgIdSumAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 10, 20.5, 31.5);
  _hLeptonAbsPdgIdSumAfter -> SetXAxisTitle("Dilepton SumAbsPdgId");
  _hLeptonAbsPdgIdSumAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configSameSignStream;
  configSameSignStream << "Cut.Dilepton." << leptonType.Data() << ".AbsPdgIdSum";
  TString configSameSign = configSameSignStream.str().c_str();

  //
  _LeptonAbsPdgIdSum = config -> GetValue(configSameSign.Data(), 999);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
 if(_LeptonAbsPdgIdSum ==22 ){
   cutFlowTitleStream << leptonType.Data() << " Dilepton : ee? ";
  } else if(_LeptonAbsPdgIdSum ==24 ){
   cutFlowTitleStream << leptonType.Data() << " Dilepton : em? ";
  } else if(_LeptonAbsPdgIdSum ==26 ){
   cutFlowTitleStream << leptonType.Data() << " Dilepton : mm? ";
  }else{
   cutFlowTitleStream << leptonType.Data() << " Dilepton : any flavor ";
  }
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Dilepton.AbsPdgIdSum.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonAbsPdgIdSum::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonAbsPdgIdSum::Apply()
{

  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t LeptonPairAbsPdgIdSum    = 0;       

  // Flags 
  Bool_t LeptonAbsPdgIdSumPass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Muon> muonVector;
  std::vector<Electron> electronVector;
  std::vector<Lepton> leptonVector;


  //Assign collections to the above defined vectors
  if(     "All"        == leptonType) {
    muonVector.assign(EventContainerObj -> muons.begin(),           EventContainerObj -> muons.end());
    electronVector.assign(EventContainerObj -> electrons.begin(),           EventContainerObj -> electrons.end());
  }
  else if("Veto"       == leptonType) {
    muonVector.assign(EventContainerObj -> vetoMuons.begin(),       EventContainerObj -> vetoMuons.end());
    electronVector.assign(EventContainerObj -> vetoElectrons.begin(),       EventContainerObj -> vetoElectrons.end());
  }
  else if("PtEtaCut"   == leptonType) {
    muonVector.assign(EventContainerObj -> ptetaMuons.begin(),      EventContainerObj -> ptetaMuons.end());
    electronVector.assign(EventContainerObj -> ptetaElectrons.begin(),      EventContainerObj -> ptetaElectrons.end());
  }
  else if("Tight"      == leptonType) {
    muonVector.assign(EventContainerObj -> tightMuons.begin(),      EventContainerObj -> tightMuons.end());
    electronVector.assign(EventContainerObj -> tightElectrons.begin(),      EventContainerObj -> tightElectrons.end());
  }
  else if("Isolated"   == leptonType) {
    muonVector.assign(EventContainerObj -> isolatedMuons.begin(),   EventContainerObj -> isolatedMuons.end());
    electronVector.assign(EventContainerObj -> isolatedElectrons.begin(),   EventContainerObj -> isolatedElectrons.end());
  }
  else if("UnIsolated" == leptonType) {
    muonVector.assign(EventContainerObj -> unIsolatedMuons.begin(), EventContainerObj -> unIsolatedMuons.end());
    electronVector.assign(EventContainerObj -> unIsolatedElectrons.begin(), EventContainerObj -> unIsolatedElectrons.end());
  }
  else if("TTHFake" == leptonType) {
    leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  }
  else{
    std::cout << "ERROR " << "<CutLeptonAbsPdgIdSum::Apply()> "
	      << "leptonType must be All, Tight, Veto, Isolated, or UnIsolated, PtEtaCut, TTHFake" << std::endl;
    exit(8);
  } //else                                                                                                          

  //Now work out the dilepton mass
  if("TTHFake" == leptonType ) LeptonPairAbsPdgIdSum = fabs(leptonVector[0].pdgId())+fabs(leptonVector[1].pdgId());
  else if (EventContainerObj->GetChannelName() == "mumu") LeptonPairAbsPdgIdSum = 26;
  else if (EventContainerObj->GetChannelName() == "ee") LeptonPairAbsPdgIdSum = 22;
  else if (EventContainerObj->GetChannelName() == "emu") LeptonPairAbsPdgIdSum = 24;

  // Fill the histograms before the cuts
  _hLeptonAbsPdgIdSumBefore    -> Fill(LeptonPairAbsPdgIdSum);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << leptonType.Data() << "Dilepton.AbsPdgIdSum.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if ( _LeptonAbsPdgIdSum != LeptonPairAbsPdgIdSum && _LeptonAbsPdgIdSum != 999 ){
    LeptonAbsPdgIdSumPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonAbsPdgIdSumAfter -> Fill(LeptonPairAbsPdgIdSum);
  }

  // ***********************************************
  // Return if it passes
  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !LeptonAbsPdgIdSumPass ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail LeptonAbsPdgIdSumPass " << leptonType << " LeptonPairAbsPdgIdSum "<< LeptonPairAbsPdgIdSum   <<  std::endl; 
  }
  // ***********************************************
  
  return(LeptonAbsPdgIdSumPass);
 
} //Apply












