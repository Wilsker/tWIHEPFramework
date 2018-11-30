/******************************************************************************
 * CutLeptonMCPromptFS.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCPromptFS class                                *
 *    CutLeptonMCPromptFS()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCPromptFS()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCPromptFS"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCPromptFS class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonMCPromptFS.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonMCPromptFS::CutLeptonMCPromptFS(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonMCPromptFS::CutLeptonMCPromptFS(EventContainer *EventContainerObj, Bool_t useMCPromptFS)
{
  // Set Event Container
  SetEventContainer(EventContainerObj);
  _useMCPromptFS = useMCPromptFS;
} // CutLeptonMCPromptFS


/******************************************************************************
 * CutLeptonMCPromptFS::~CutLeptonMCPromptFS()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonMCPromptFS::~CutLeptonMCPromptFS()
{
  
}//~CutLeptonMCPromptFS

/******************************************************************************
 * void CutLeptonMCPromptFS::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonMCPromptFS::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream <<  "DileptonMCPromptFSBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream <<  "Dilepton MCPromptFS Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream <<  "DileptonMCPromptFSAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream <<  "Dilepton MCPromptFS After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonMCPromptFSBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -0.5, 2.5);
  _hLeptonMCPromptFSBefore -> SetXAxisTitle("Sum of MCPromptFS");
  _hLeptonMCPromptFSBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonMCPromptFSAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, -0.5, 2.5);
  _hLeptonMCPromptFSAfter -> SetXAxisTitle("Sum of MCPromptFS");
  _hLeptonMCPromptFSAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configMCPromptFSStream;
  configMCPromptFSStream << "Cut.Gen.MCPromptFS";
  TString configMCPromptFS = configMCPromptFSStream.str().c_str();

  //
  _LeptonMCPromptFS = config -> GetValue(configMCPromptFS.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  cutFlowTitleStream << " MCPromptFS ";
 
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << " MCPromptFS ";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonMCPromptFS::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonMCPromptFS::Apply()
{
  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
 
  // Initialize number of leptons
  Float_t LeptonPairMCPromptFS    = 0;       

  // Flags 
  Bool_t LeptonMCPromptFSPass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();
  

  std::vector<Lepton> leptonVector;


  leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());

  //Now work out the dilepton mass
  LeptonPairMCPromptFS = (leptonVector[0].gen_isPrompt()==1 || leptonVector[0].gen_isPromptTau()==1) + (leptonVector[1].gen_isPrompt()==1 || leptonVector[1].gen_isPromptTau()==1) ;

  // Fill the histograms before the cuts
  _hLeptonMCPromptFSBefore    -> Fill(LeptonPairMCPromptFS);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << " MCPromptFS ";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if (EventContainerObj->isSimulation && _useMCPromptFS &&_LeptonMCPromptFS == 1 && LeptonPairMCPromptFS < 2){
    LeptonMCPromptFSPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonMCPromptFSAfter -> Fill(LeptonPairMCPromptFS);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = LeptonMCPromptFSPass ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    //std::cout<< "in cut LeptonN always return true ";
    return kTRUE;
  }else{
    return(LeptonMCPromptFSPass);
  }
  
 
} //Apply












