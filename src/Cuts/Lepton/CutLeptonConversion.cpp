/******************************************************************************
 * CutLeptonConversion.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonConversion class                                *
 *    CutLeptonConversion()                     -- Parameterized Constructor           *
 *    ~CutLeptonConversion()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonConversion"                  *
 *                                                                            *
 * Private Data Members of CutLeptonConversion class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B. Li                                        *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonConversion.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonConversion::CutLeptonConversion(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonConversion::CutLeptonConversion(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( 
      leptonTypePassed.CompareTo("TTHTight") && leptonTypePassed.CompareTo("TTHLoose")
      && leptonTypePassed.CompareTo("TTHFake")
       ){
    std::cout << "ERROR " << "<CutLeptonConversion::CutLeptonConversion()> " 
	      << "Must pass TTHLoose, TTHFake, TTHTight to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonConversion


/******************************************************************************
 * CutLeptonConversion::~CutLeptonConversion()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonConversion::~CutLeptonConversion()
{
  
}//~CutLeptonConversion

/******************************************************************************
 * void CutLeptonConversion::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonConversion::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << "DileptonConversionBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << "Dilepton Conversion Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << "DileptonConversionAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << "Dilepton Conversion After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonConversionBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 4, -0.5, 3.5);
  _hLeptonConversionBefore -> SetXAxisTitle("Dilepton Conversion");
  _hLeptonConversionBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonConversionAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 4, -0.5, 3.5);
  _hLeptonConversionAfter -> SetXAxisTitle("Dilepton Conversion");
  _hLeptonConversionAfter -> SetYAxisTitle("Events");

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
  cutFlowTitleStream << leptonType.Data() << " Dilepton conversion ";
  
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "Dilepton.Conversion.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonConversion::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonConversion::Apply()
{

  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t LeptonPairConversion    = 0;       

  // Flags 
  Bool_t LeptonConversionPass = kTRUE; // Event passes sign selection

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
    std::cout << "ERROR " << "<CutLeptonConversion::Apply()> "
	      << "leptonType must be TTHLoose, TTHFake or TTHTight " << std::endl;
    exit(8);
  } //else                                                                                                          

  //Now work out the dilepton mass
  LeptonPairConversion = leptonVector[0].passConversionVeto()+leptonVector[1].passConversionVeto();

  // Fill the histograms before the cuts
  _hLeptonConversionBefore    -> Fill(LeptonPairConversion);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << leptonType.Data() << "Dilepton.Conversion.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if ( LeptonPairConversion !=2 ){//if not both leptons pass conversion veto
    LeptonConversionPass = kFALSE;
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonConversionAfter -> Fill(LeptonPairConversion);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  
  return(LeptonConversionPass);
 
} //Apply












