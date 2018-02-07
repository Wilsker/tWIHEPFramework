/******************************************************************************
 * CutLeptonMCMatchId.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCMatchId class                                *
 *    CutLeptonMCMatchId()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCMatchId()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCMatchId"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCMatchId class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonMCMatchId.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonMCMatchId::CutLeptonMCMatchId(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonMCMatchId::CutLeptonMCMatchId(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonMCMatchId


/******************************************************************************
 * CutLeptonMCMatchId::~CutLeptonMCMatchId()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonMCMatchId::~CutLeptonMCMatchId()
{
  
}//~CutLeptonMCMatchId

/******************************************************************************
 * void CutLeptonMCMatchId::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonMCMatchId::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream <<  "DileptonMCMatchIdBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream <<  "Dilepton MCMatchId Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream <<  "DileptonMCMatchIdAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream <<  "Dilepton MCMatchId After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonMCMatchIdBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -0.5, 2.5);
  _hLeptonMCMatchIdBefore -> SetXAxisTitle("Sum of MCMatchId");
  _hLeptonMCMatchIdBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonMCMatchIdAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, -0.5, 2.5);
  _hLeptonMCMatchIdAfter -> SetXAxisTitle("Sum of MCMatchId");
  _hLeptonMCMatchIdAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configMCMatchIdStream;
  configMCMatchIdStream << "Cut.Gen.MCMatchId";
  TString configMCMatchId = configMCMatchIdStream.str().c_str();

  //
  _LeptonMCMatchId = config -> GetValue(configMCMatchId.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << " MCMatchId ";
 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << " MCMatchId ";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonMCMatchId::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonMCMatchId::Apply()
{
  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t LeptonPairMCMatchId    = 0;       

  // Flags 
  Bool_t LeptonMCMatchIdPass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();
  
  if(!EventContainerObj->isSimulation)return true;

  std::vector<double> leptonMatchId;


  leptonMatchId.assign(EventContainerObj -> FakeLep_matchId.begin(), EventContainerObj -> FakeLep_matchId.end());

  //Now work out the dilepton mass
  LeptonPairMCMatchId = (leptonMatchId[0]==-999? 0:1) + (leptonMatchId[1]==-999? 0:1);

  // Fill the histograms before the cuts
  _hLeptonMCMatchIdBefore    -> Fill(LeptonPairMCMatchId);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << " MCMatchId ";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if (_LeptonMCMatchId == 1 && LeptonPairMCMatchId < 2){
    LeptonMCMatchIdPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonMCMatchIdAfter -> Fill(LeptonPairMCMatchId);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  
  return(LeptonMCMatchIdPass);
 
} //Apply












