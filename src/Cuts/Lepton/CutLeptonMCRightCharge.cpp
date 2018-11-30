/******************************************************************************
 * CutLeptonMCRightCharge.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCRightCharge class                                *
 *    CutLeptonMCRightCharge()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCRightCharge()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCRightCharge"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCRightCharge class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonMCRightCharge.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonMCRightCharge::CutLeptonMCRightCharge(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonMCRightCharge::CutLeptonMCRightCharge(EventContainer *EventContainerObj, Bool_t useMCRightCharge)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
  _useMCRightCharge = useMCRightCharge;
} // CutLeptonMCRightCharge


/******************************************************************************
 * CutLeptonMCRightCharge::~CutLeptonMCRightCharge()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonMCRightCharge::~CutLeptonMCRightCharge()
{
  
}//~CutLeptonMCRightCharge

/******************************************************************************
 * void CutLeptonMCRightCharge::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonMCRightCharge::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream <<  "DileptonMCRightChargeBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream <<  "Dilepton MCRightCharge Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream <<  "DileptonMCRightChargeAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream <<  "Dilepton MCRightCharge After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonMCRightChargeBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -0.5, 2.5);
  _hLeptonMCRightChargeBefore -> SetXAxisTitle("Sum of MCRightCharge");
  _hLeptonMCRightChargeBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonMCRightChargeAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, -0.5, 2.5);
  _hLeptonMCRightChargeAfter -> SetXAxisTitle("Sum of MCRightCharge");
  _hLeptonMCRightChargeAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configMCRightChargeStream;
  configMCRightChargeStream << "Cut.Gen.MCRightCharge";
  TString configMCRightCharge = configMCRightChargeStream.str().c_str();

  //
  _LeptonMCRightCharge = config -> GetValue(configMCRightCharge.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << " MCRightCharge ";
 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << " MCRightCharge ";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonMCRightCharge::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonMCRightCharge::Apply()
{
  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t LeptonPairMCRightCharge    = 0;       

  // Flags 
  Bool_t LeptonMCRightChargePass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();
  

  std::vector<double> leptonMatchId;
  std::vector<double> leptonPdgId;


  leptonMatchId.assign(EventContainerObj -> FakeLep_matchId.begin(), EventContainerObj -> FakeLep_matchId.end());
  leptonPdgId.assign(EventContainerObj -> FakeLep_PdgId.begin(), EventContainerObj -> FakeLep_PdgId.end());

  //Now work out the dilepton mass
  LeptonPairMCRightCharge = (leptonMatchId[0]==leptonPdgId[0]? 1:0) + (leptonMatchId[1]==leptonPdgId[1]? 1:0);

  // Fill the histograms before the cuts
  _hLeptonMCRightChargeBefore    -> Fill(LeptonPairMCRightCharge);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << " MCRightCharge ";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if (EventContainerObj->isSimulation && _useMCRightCharge && _LeptonMCRightCharge == 1 && LeptonPairMCRightCharge < 2){
    LeptonMCRightChargePass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonMCRightChargeAfter -> Fill(LeptonPairMCRightCharge);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = LeptonMCRightChargePass ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    //std::cout<< "in cut LeptonN always return true ";
    return kTRUE;
  }else{
    return(LeptonMCRightChargePass);
  }
 
} //Apply












