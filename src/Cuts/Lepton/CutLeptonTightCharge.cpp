/******************************************************************************
 * CutLeptonTightCharge.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonTightCharge class                                *
 *    CutLeptonTightCharge()                     -- Parameterized Constructor           *
 *    ~CutLeptonTightCharge()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonTightCharge"                  *
 *                                                                            *
 * Private Data Members of CutLeptonTightCharge class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B. Li                                        *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonTightCharge.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonTightCharge::CutLeptonTightCharge(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonTightCharge::CutLeptonTightCharge(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( 
      leptonTypePassed.CompareTo("TTHTight") && leptonTypePassed.CompareTo("TTHLoose")
      && leptonTypePassed.CompareTo("TTHFake")
       ){
    std::cout << "ERROR " << "<CutLeptonTightCharge::CutLeptonTightCharge()> " 
	      << "Must pass TTHLoose, TTHFake, TTHTight to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonTightCharge


/******************************************************************************
 * CutLeptonTightCharge::~CutLeptonTightCharge()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonTightCharge::~CutLeptonTightCharge()
{
  
}//~CutLeptonTightCharge

/******************************************************************************
 * void CutLeptonTightCharge::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonTightCharge::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << "DileptonTightChargeBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << "Dilepton TightCharge Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << "DileptonTightChargeAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << "Dilepton TightCharge After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonTightChargeBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 4, -0.5, 3.5);
  _hLeptonTightChargeBefore -> SetXAxisTitle("Dilepton TightCharge");
  _hLeptonTightChargeBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonTightChargeAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 4, -0.5, 3.5);
  _hLeptonTightChargeAfter -> SetXAxisTitle("Dilepton TightCharge");
  _hLeptonTightChargeAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << leptonType.Data() << " Dilepton TightCharge ";
  
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Dilepton.TightCharge.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonTightCharge::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonTightCharge::Apply()
{

  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t LeptonPairTightCharge    = 0;       

  // Flags 
  Bool_t LeptonTightChargePass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Muon> muonVector;
  std::vector<Electron> electronVector;
  std::vector<Lepton> leptonVector;


  //Assign collections to the above defined vectors
  if("TTHFake" == leptonType) {
    leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  }
  else if("TTHLoose" == leptonType) {
    leptonVector.assign(EventContainerObj -> looseLeptons.begin(), EventContainerObj -> looseLeptons.end());
  }
  else if("TTHTight" == leptonType) {
    leptonVector.assign(EventContainerObj -> tightLeptons.begin(), EventContainerObj -> tightLeptons.end());
  }
  else{
    std::cout << "ERROR " << "<CutLeptonTightCharge::Apply()> "
	      << "leptonType must be TTHLoose, TTHFake or TTHTight " << std::endl;
    exit(8);
  } //else                                                                                                          

  //Now work out the dilepton mass
  LeptonPairTightCharge = leptonVector[0].passTightCharge()+leptonVector[1].passTightCharge();

  // Fill the histograms before the cuts
  _hLeptonTightChargeBefore    -> Fill(LeptonPairTightCharge);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << leptonType.Data() << "Dilepton.TightCharge.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if ( LeptonPairTightCharge !=2 ){//if not both leptons pass TightCharge
    LeptonTightChargePass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonTightChargeAfter -> Fill(LeptonPairTightCharge);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !LeptonTightChargePass ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail LeptonTightChargePass " << leptonType << " lep1PassTightCharge " << leptonVector[0].passTightCharge()<< " lep2PassTightCharge "<< leptonVector[1].passTightCharge() << std::endl; 
  }
  
  return(LeptonTightChargePass);
 
} //Apply












