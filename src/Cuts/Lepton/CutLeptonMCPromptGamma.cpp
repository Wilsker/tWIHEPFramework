/******************************************************************************
 * CutLeptonMCPromptGamma.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCPromptGamma class                                *
 *    CutLeptonMCPromptGamma()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCPromptGamma()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCPromptGamma"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCPromptGamma class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonMCPromptGamma.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonMCPromptGamma::CutLeptonMCPromptGamma(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonMCPromptGamma::CutLeptonMCPromptGamma(EventContainer *EventContainerObj)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonMCPromptGamma


/******************************************************************************
 * CutLeptonMCPromptGamma::~CutLeptonMCPromptGamma()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonMCPromptGamma::~CutLeptonMCPromptGamma()
{
  
}//~CutLeptonMCPromptGamma

/******************************************************************************
 * void CutLeptonMCPromptGamma::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonMCPromptGamma::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream <<  "DileptonMCPromptGammaBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream <<  "Dilepton MCPromptGamma Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream <<  "DileptonMCPromptGammaAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream <<  "Dilepton MCPromptGamma After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonMCPromptGammaBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -0.5, 2.5);
  _hLeptonMCPromptGammaBefore -> SetXAxisTitle("Sum of MCPromptGamma");
  _hLeptonMCPromptGammaBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonMCPromptGammaAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, -0.5, 2.5);
  _hLeptonMCPromptGammaAfter -> SetXAxisTitle("Sum of MCPromptGamma");
  _hLeptonMCPromptGammaAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configMCPromptGammaStream;
  configMCPromptGammaStream << "Cut.Gen.MCPromptGamma";
  TString configMCPromptGamma = configMCPromptGammaStream.str().c_str();

  //
  _LeptonMCPromptGamma = config -> GetValue(configMCPromptGamma.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << " MCPromptGamma ";
 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << " MCPromptGamma ";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonMCPromptGamma::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonMCPromptGamma::Apply()
{
  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t LeptonPairMCPromptGamma    = 0;       

  // Flags 
  Bool_t LeptonMCPromptGammaPass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();
 
  Bool_t isCorrectSample = true; 
  if(!EventContainerObj->isSimulation || !(EventContainerObj->GetSourceName().Contains("WGToLNuG")
      || EventContainerObj->GetSourceName().Contains("ZGTo2LG")
      || EventContainerObj->GetSourceName().Contains("TGJets_")
      || EventContainerObj->GetSourceName().Contains("TTGJets_ext1")
      )) isCorrectSample = false; // prompt Gamma only apply for Conversion samples

  std::vector<double> leptonPromptGamma;
  std::vector<Lepton> leptonVector;


  leptonPromptGamma.assign(EventContainerObj -> FakeLep_matchId.begin(), EventContainerObj -> FakeLep_matchId.end());
  leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());

  //Now work out the dilepton mass
  LeptonPairMCPromptGamma = (leptonPromptGamma[0]==22 && fabs(leptonVector[0].pdgId())==11 ? 1:0) + (leptonPromptGamma[1]==22 && fabs(leptonVector[1].pdgId())==11 ? 1:0);

  // Fill the histograms before the cuts
  _hLeptonMCPromptGammaBefore    -> Fill(LeptonPairMCPromptGamma);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << " MCPromptGamma ";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if ( isCorrectSample && _LeptonMCPromptGamma == 1 && LeptonPairMCPromptGamma < 2){
    LeptonMCPromptGammaPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonMCPromptGammaAfter -> Fill(LeptonPairMCPromptGamma);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  
  return(LeptonMCPromptGammaPass);
 
} //Apply












