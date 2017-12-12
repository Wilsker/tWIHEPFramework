/******************************************************************************
 * CutLeptonTight.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonTight class                                *
 *    CutLeptonTight()                     -- Parameterized Constructor           *
 *    ~CutLeptonTight()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonTight"                  *
 *                                                                            *
 * Private Data Members of CutLeptonTight class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      11 Dec 2017 - Created by B.Li Based on CutLeptonCharge by P.Ryan      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonTight.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonTight::CutLeptonTight(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonTight::CutLeptonTight(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( 
      leptonTypePassed.CompareTo("TTHTight") 
      && leptonTypePassed.CompareTo("TTHFake")
       ){
    std::cout << "ERROR " << "<CutLeptonTight::CutLeptonTight()> " 
	      << "Must pass TTHFake, TTHTight to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonTight


/******************************************************************************
 * CutLeptonTight::~CutLeptonTight()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonTight::~CutLeptonTight()
{
  
}//~CutLeptonTight

/******************************************************************************
 * void CutLeptonTight::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonTight::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << "DileptonTightBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << "Dilepton Tight Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << "DileptonTightAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << "Dilepton Tight After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonTightBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -0.5, 2.5);
  _hLeptonTightBefore -> SetXAxisTitle("#Dilepton tight");
  _hLeptonTightBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonTightAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, 0.5, 2.5);
  _hLeptonTightAfter -> SetXAxisTitle("#Dilepton tight");
  _hLeptonTightAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configNumTightMaxStream;
  configNumTightMaxStream << "Cut.Dilepton." << leptonType.Data() << ".NumTightMax";
  TString configNumTightMax = configNumTightMaxStream.str().c_str();

  std::ostringstream configNumTightMinStream;
  configNumTightMinStream << "Cut.Dilepton." << leptonType.Data() << ".NumTightMin";
  TString configNumTightMin = configNumTightMinStream.str().c_str();

  std::ostringstream configNumTightAllStream;
  configNumTightAllStream << "Cut.Dilepton." << leptonType.Data() << ".NumTightAll";
  TString configNumTightAll = configNumTightAllStream.str().c_str();

  //
  _LeptonNumTightMin = config -> GetValue(configNumTightMin.Data(), 0);
  _LeptonNumTightMax = config -> GetValue(configNumTightMax.Data(), 999);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << leptonType.Data() << " Dilepton : " << "N_tight>= " << _LeptonNumTightMin; 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Dilepton.NumberTight.Min";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  // Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << leptonType.Data() << " Dilepton : " << "N_tight<= " << _LeptonNumTightMax; 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Dilepton.NumberTight.Max";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << leptonType.Data() << " Dilepton : "  << _LeptonNumTightMin << " <= N_tight <= "<< _LeptonNumTightMax; 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Dilepton.NumberTight.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonTight::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonTight::Apply()
{

  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Int_t LeptonPairNumTight    = 0;       

  // Flags 
  Bool_t LeptonTightPass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Lepton> leptonVector;


  //Assign collections to the above defined vectors
  if("TTHFake" == leptonType) {
    leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  }
  else if("TTHTight" == leptonType) {
    leptonVector.assign(EventContainerObj -> tightLeptons.begin(), EventContainerObj -> tightLeptons.end());
  }
  else{
    std::cout << "ERROR " << "<CutLeptonTight::Apply()> "
	      << "leptonType must be TTHTight, TTHFake" << std::endl;
    exit(8);
  } //else                                                                                                          

  //Now work out the dilepton mass
  LeptonPairNumTight = leptonVector[0].isTight()+leptonVector[1].isTight();

  // Fill the histograms before the cuts
  _hLeptonTightBefore    -> Fill(LeptonPairNumTight);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  ostringstream cutFlowNameMinStream;
  ostringstream cutFlowNameMaxStream;
  
  TString cutFlowNameAll;
  TString cutFlowNameMax;
  TString cutFlowNameMin;
  
  cutFlowNameAllStream << leptonType.Data() << "Dilepton.NumberTight.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  cutFlowNameMinStream << leptonType.Data() << "Dilepton.NumberTight.Min";
  cutFlowNameMin = cutFlowNameMinStream.str().c_str();
  
  cutFlowNameMaxStream << leptonType.Data() << "Dilepton.NumberTight.Max";
  cutFlowNameMax = cutFlowNameMaxStream.str().c_str();
  
  //Cut on Min 
  if ( _LeptonNumTightMax < LeptonPairNumTight){
    LeptonTightPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameMax.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameMax.Data());
    _hLeptonTightAfter -> Fill(LeptonPairNumTight);
  }

  //Cut on Min 
  if ( _LeptonNumTightMin > LeptonPairNumTight){
    LeptonTightPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameMin.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameMin.Data());
    _hLeptonTightAfter -> Fill(LeptonPairNumTight);
  }

  //Cut on Min and Max 
  if ( _LeptonNumTightMin > LeptonPairNumTight || _LeptonNumTightMax < LeptonPairNumTight){
    LeptonTightPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonTightAfter -> Fill(LeptonPairNumTight);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  
  return(LeptonTightPass);
 
} //Apply












