/******************************************************************************
 * CutLeptonSameSign.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonSameSign class                                *
 *    CutLeptonSameSign()                     -- Parameterized Constructor           *
 *    ~CutLeptonSameSign()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonSameSign"                  *
 *                                                                            *
 * Private Data Members of CutLeptonSameSign class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      23 Oct 2018 - Created by Binghuan Li                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonSameSign.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutLeptonSameSign::CutLeptonSameSign(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutLeptonSameSign::CutLeptonSameSign(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( leptonTypePassed.CompareTo("All") && leptonTypePassed.CompareTo("UnIsolated") && leptonTypePassed.CompareTo("Isolated") && 
      leptonTypePassed.CompareTo("Tight") && leptonTypePassed.CompareTo("Veto")
      && leptonTypePassed.CompareTo("TTHFake")
      && leptonTypePassed.CompareTo("TTHLoose")
       ){
    std::cout << "ERROR " << "<CutLeptonSameSign::CutLeptonSameSign()> " 
	      << "Must pass All, Tight, Veto, Isolated, TTHLoose, TTHFake or UnIsolated to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonSameSign


/******************************************************************************
 * CutLeptonSameSign::~CutLeptonSameSign()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonSameSign::~CutLeptonSameSign()
{
  
}//~CutLeptonSameSign

/******************************************************************************
 * void CutLeptonSameSign::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonSameSign::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << "DilepSkimChargeBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << "DilepSkim Charge Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << "DilepSkimChargeAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << "DilepSkim Charge After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hLeptonSameSignBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -1.5, 1.5);
  _hLeptonSameSignBefore -> SetXAxisTitle("DilepSkim charge");
  _hLeptonSameSignBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeptonSameSignAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, -1.5, 1.5);
  _hLeptonSameSignAfter -> SetXAxisTitle("DilepSkim charge");
  _hLeptonSameSignAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configSameSignStream;
  configSameSignStream << "Cut.Dilepton." << leptonType.Data() << ".SameSign";
  TString configSameSign = configSameSignStream.str().c_str();

  //
  //_LeptonSameSign = config -> GetValue(configSameSign.Data(), false);
  _LeptonSameSign = config -> GetValue(configSameSign.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  if(_LeptonSameSign !=0 ){
   cutFlowTitleStream << leptonType.Data() << " DilepSkim : " << (_LeptonSameSign > 0 ? "Same sign " : "Opposite sign ");
  }else{
   cutFlowTitleStream << leptonType.Data() << " DilepSkim : " << "Any sign ";
  }
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << leptonType.Data() << "DilepSkim.Charge.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutLeptonSameSign::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonSameSign::Apply()
{

  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  Float_t FoundSameSign    = 0;       

  // Flags 
  Bool_t LeptonSameSignPass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Muon> muonVector;
  std::vector<Electron> electronVector;
  std::vector<Lepton> leptonVector;
  std::vector<double> chargeVector;

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
    for(auto lep: leptonVector){
        chargeVector.push_back(lep.charge());
    }
  }
  else if("TTHLoose" == leptonType) {
    leptonVector.assign(EventContainerObj -> looseLeptons.begin(), EventContainerObj -> looseLeptons.end());
    for(auto lep: leptonVector){
        chargeVector.push_back(lep.charge());
    }
  }
  else{
    std::cout << "ERROR " << "<CutLeptonSameSign::Apply()> "
	      << "leptonType must be All, Tight, Veto, Isolated, or UnIsolated, PtEtaCut, TTHFake, TTHLoose" << std::endl;
    exit(8);
  } //else                                                                                                          

  //Now work out the dilepton mass
  if("TTHFake" == leptonType || "TTHLoose" == leptonType ){
      std::sort( chargeVector.begin(), chargeVector.end() );
      chargeVector.erase( unique( chargeVector.begin(), chargeVector.end() ), chargeVector.end() );
      if(leptonVector.size()>chargeVector.size()) FoundSameSign=1;  // we found a same sign , notice this doesn't exclude we found a opposite sign
  }
  else if (EventContainerObj->GetChannelName() == "mumu") FoundSameSign = muonVector[0].charge()*muonVector[1].charge();
  else if (EventContainerObj->GetChannelName() == "ee") FoundSameSign = electronVector[0].charge() * electronVector[1].charge();
  else if (EventContainerObj->GetChannelName() == "emu") FoundSameSign = muonVector[0].charge() * electronVector[0].charge();

  // Fill the histograms before the cuts
  _hLeptonSameSignBefore    -> Fill(FoundSameSign);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << leptonType.Data() << "DilepSkim.Charge.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();

  if(_LeptonSameSign > 0 && FoundSameSign <=0)LeptonSameSignPass = kFALSE; // ask same sign but not found same sign
  if(_LeptonSameSign < 0 && chargeVector.size()<=1)LeptonSameSignPass = kFALSE; // ask opposite sign but chargeVector.size <=1 which means all same sign

  
  if ( !LeptonSameSignPass){
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hLeptonSameSignAfter -> Fill(FoundSameSign);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !LeptonSameSignPass ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail LeptonSameSignPass " << leptonType << " FoundSameSign? "<< FoundSameSign<<" Number of Different Charges " << chargeVector.size()<< std::endl; 
  }
  
  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = LeptonSameSignPass ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return(LeptonSameSignPass);
  }
 
} //Apply












