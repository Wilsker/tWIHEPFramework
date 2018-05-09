/******************************************************************************
 * CutLeptonPt3.hpp                                                               *
 *                                                                            *
 * Cuts on muon Number (can cut on All, UnIsolated, Tight, or Veto Muons)     *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonPt3 class                                  *
 *    CutLeptonPt3()                     -- Parameterized Constructor             *
 *    ~CutLeptonPt3()                    -- Destructor                            *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonPt3"                    *
 *                                                                            *
 * Private Data Members of CutLeptonPt3 class                                     *
 *    myTH1F* _hMuonNumberBefore;    -- Hist mu Number before cut             *
 *    myTH1F* _hMuonNumberAfter;     -- Hist mu Number of jets after cut      *
 *                                                                            *
 *    Int_t _MuonNumberMin;          -- Minimum Muon Number                   *
 *    Int_t _MuonNumberMax;          -- Maximum Muon Number                   *
 *                                                                            *
 * History                                                                    *
 *      11 Dec 2017 - Created by B. Li based on CutLeptonPt1 by P. Ryan       *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutLeptonPt3.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
 * CutLeptonPt3::CutLeptonPt3(EventContainer *EventContainerObj, TString muonType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonPt3::CutLeptonPt3(EventContainer *EventContainerObj, TString leptonType)
{
  // Check muonType parameter
  if( leptonType.CompareTo("All") && leptonType.CompareTo("UnIsolated") && leptonType.CompareTo("Isolated") && 
      leptonType.CompareTo("Tight") && leptonType.CompareTo("PtEtaCut") && leptonType.CompareTo("Veto")
      && leptonType.CompareTo("TTHFake")
       ){
    std::cout << "ERROR " << "<CutLeptonPt3::CutLeptonPt3()> " 
	      << "Must pass All, Tight, PtEtaCut, Veto, Isolated, or UnIsolated, TTHFake to constructor" << std::endl;
    exit(8);
  } //if
  _leptonType = leptonType;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutLeptonPt3


/******************************************************************************
 * CutLeptonPt3::~CutLeptonPt3()                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutLeptonPt3::~CutLeptonPt3()
{
  
}//~CutLeptonPt3

/******************************************************************************
 * void CutLeptonPt3::BookHistogram()                                          *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutLeptonPt3::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << _leptonType << "ThirdLeptonPtBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << _leptonType << "Third Lepton Pt Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << _leptonType << "ThirdLeptonPtAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << _leptonType << "Third Lepton Pt After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hThirdLeptonPtBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 100, 0.0, 200.);
  _hThirdLeptonPtBefore -> SetXAxisTitle("p_{T,third}");
  _hThirdLeptonPtBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hThirdLeptonPtAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 100, 0.0, 200.);
  _hThirdLeptonPtAfter -> SetXAxisTitle("p_{T,third}");
  _hThirdLeptonPtAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Make name in configuration file depending upon muon type (all, veto, tight, unIsolated)
  std::ostringstream configMinStream;
  configMinStream << "Cut.Muon." << _leptonType.Data() << ".ThirdPt";
  TString configMin = configMinStream.str().c_str();

  std::ostringstream configMaxStream;
  configMaxStream << "Cut.Electron." << _leptonType.Data() << ".ThirdPt";
  TString configMax = configMaxStream.str().c_str();

  // Use configuration to set min and max number of jets to cut on
  _ThirdMuonPtCut  = config -> GetValue(configMin.Data(), 999);
  _ThirdElectronPtCut  = config -> GetValue(configMax.Data(), 999);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  cutFlowTitleStream << _leptonType.Data() << " Third lepton : P_{T,#mu} > " << _ThirdMuonPtCut << " p_{T,e} > " << _ThirdElectronPtCut;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << _leptonType.Data() << "Lepton.ThirdPt";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());

}//BookHistograms()

/******************************************************************************
 * Bool_t CutMuonN::Apply()                                                *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutLeptonPt3::Apply()
{

  // ********************************
  // Get the leading Pt of the leptons
  // ********************************

  // Third lepton pt
  Float_t ThirdLeptonPt = 0.;
  
  //Flag
  Bool_t PassesThirdLetonPt = kFALSE;
  
  //Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Muon> muonVector;
  std::vector<Electron> electronVector;
  std::vector<Lepton> leptonVector;

  //Assign collections to the above defined vectors
  if(     "All"        == _leptonType) {
    muonVector.assign(EventContainerObj -> muons.begin(),           EventContainerObj -> muons.end());
    electronVector.assign(EventContainerObj -> electrons.begin(),           EventContainerObj -> electrons.end());
  }
  else if("Veto"       == _leptonType) {
    muonVector.assign(EventContainerObj -> vetoMuons.begin(),       EventContainerObj -> vetoMuons.end());
    electronVector.assign(EventContainerObj -> vetoElectrons.begin(),       EventContainerObj -> vetoElectrons.end());
  }
  else if("PtEtaCut"   == _leptonType) {
    muonVector.assign(EventContainerObj -> ptetaMuons.begin(),      EventContainerObj -> ptetaMuons.end());
    electronVector.assign(EventContainerObj -> ptetaElectrons.begin(),      EventContainerObj -> ptetaElectrons.end());
  }
  else if("Tight"      == _leptonType) {
    muonVector.assign(EventContainerObj -> tightMuons.begin(),      EventContainerObj -> tightMuons.end());
    electronVector.assign(EventContainerObj -> tightElectrons.begin(),      EventContainerObj -> tightElectrons.end());
  }
  else if("Isolated"   == _leptonType) {
    muonVector.assign(EventContainerObj -> isolatedMuons.begin(),   EventContainerObj -> isolatedMuons.end());
    electronVector.assign(EventContainerObj -> isolatedElectrons.begin(),   EventContainerObj -> isolatedElectrons.end());
  }
  else if("UnIsolated" == _leptonType) {
    muonVector.assign(EventContainerObj -> unIsolatedMuons.begin(), EventContainerObj -> unIsolatedMuons.end());
    electronVector.assign(EventContainerObj -> unIsolatedElectrons.begin(), EventContainerObj -> unIsolatedElectrons.end());
  }
  else if("TTHFake" == _leptonType) {
    leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  }
  else{
    std::cout << "ERROR " << "<HistogramminMuon::Apply()> "
	      << "muonType must be All, Tight, Veto, Isolated, or UnIsolated, PtEtaCut, TTHFake" << std::endl;
    exit(8);
  } //else                     

  // Now go through and see if there's a lepton passing this cut
  for (uint mu_en =1; mu_en < muonVector.size(); mu_en++){
    Muon muon = muonVector.at(mu_en);
    if (muon.Pt() > ThirdLeptonPt) ThirdLeptonPt = muon.Pt();  
    if (muon.Pt() > _ThirdMuonPtCut){
      PassesThirdLetonPt = kTRUE;
    }
  }

  for (uint el_en =1; el_en < electronVector.size(); el_en++){
    Electron electron = electronVector.at(el_en);
    if (electron.Pt() > ThirdLeptonPt) ThirdLeptonPt = electron.Pt();  
    if (electron.Pt() > _ThirdElectronPtCut){
      PassesThirdLetonPt = kTRUE;
    }
  }
  
  for (uint lep_en =2; lep_en < leptonVector.size(); lep_en++){
    Lepton lepton = leptonVector.at(lep_en);
    if (lepton.conept() > ThirdLeptonPt) ThirdLeptonPt = lepton.conept();  
    if (fabs(lepton.pdgId())==11 && lepton.conept() > _ThirdElectronPtCut){
      PassesThirdLetonPt = kTRUE;
    }
    if (fabs(lepton.pdgId())==13 && lepton.conept() > _ThirdMuonPtCut){
      PassesThirdLetonPt = kTRUE;
    }
  }

  _hThirdLeptonPtBefore->Fill(ThirdLeptonPt);

  ostringstream cutFlowNameStream;
  TString cutFlowName;

  cutFlowNameStream << _leptonType.Data() << "Lepton.ThirdPt";
  cutFlowName = cutFlowNameStream.str().c_str();
  
  if (PassesThirdLetonPt) {
    _hThirdLeptonPtAfter->Fill(ThirdLeptonPt);
    GetCutFlowTable()->PassCut(cutFlowName.Data());
  }
  else {
    GetCutFlowTable()->FailCut(cutFlowName.Data());
  }

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !PassesThirdLetonPt ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail PassesThirdLetonPt " << _leptonType << " Lep3Pt "<< ThirdLeptonPt<<   std::endl; 
  }
  return PassesThirdLetonPt;

 
} //Apply












