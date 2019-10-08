/******************************************************************************
* CutGenLeptonPt1.hpp                                                               *
*                                                                            *
* Cuts on muon Number (can cut on All, UnIsolated, Tight, or Veto Muons)     *
* Must pass All, UnIsolated, Tight, or Veto to constructor                   *
*                                                                            *
* Derived from HistoCut which is in turn derived from BaseCut                *
*                                                                            *
*                                                                            *
* Public Member Functions of CutGenLeptonPt1 class                                  *
*    CutGenLeptonPt1()                     -- Parameterized Constructor             *
*    ~CutGenLeptonPt1()                    -- Destructor                            *
*    BookHistogram()                -- Book histograms                       *
*    Apply()                        -- Apply cuts and fill histograms        *
*    GetCutName()                   -- Returns "CutGenLeptonPt1"                    *
*                                                                            *
* Private Data Members of CutGenLeptonPt1 class                                     *
*    myTH1F* _hMuonNumberBefore;    -- Hist mu Number before cut             *
*    myTH1F* _hMuonNumberAfter;     -- Hist mu Number of jets after cut      *
*                                                                            *
*    Int_t _MuonNumberMin;          -- Minimum Muon Number                   *
*    Int_t _MuonNumberMax;          -- Maximum Muon Number                   *
*                                                                            *
* History                                                                    *
*      15 Jan 2007 - Created by P. Ryan                                      *
*****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutGenLeptonPt1.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
* CutGenLeptonPt1::CutGenLeptonPt1(EventContainer *EventContainerObj, TString muonType)    *
*                                                                            *
* Parameterized Constructor                                                  *
*                                                                            *
* Input:  Event Object class                                                 *
* Output: None                                                               *
******************************************************************************/
CutGenLeptonPt1::CutGenLeptonPt1(EventContainer *EventContainerObj, TString leptonType)
{
  // Check muonType parameter
  if( leptonType.CompareTo("Gen") ){
    std::cout << "ERROR " << "<CutGenLeptonPt1::CutGenLeptonPt1()> " << "Must pass Gen to constructor" << std::endl;
    exit(8);
  } //if
  _leptonType = leptonType;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutGenLeptonPt1


/******************************************************************************
* CutGenLeptonPt1::~CutGenLeptonPt1()                                                *
*                                                                            *
* Destructor                                                                 *
*                                                                            *
* Input:  None                                                               *
* Output: None                                                               *
******************************************************************************/
CutGenLeptonPt1::~CutGenLeptonPt1()
{

}//~CutGenLeptonPt1

/******************************************************************************
* void CutGenLeptonPt1::BookHistogram()                                          *
*                                                                            *
* Book Histograms                                                            *
*                                                                            *
* Input:  None                                                               *
* Output: None                                                               *
******************************************************************************/
void CutGenLeptonPt1::BookHistogram(){

  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << _leptonType << "LeadingLeptonPtBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << _leptonType << "Leading Lepton Pt Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << _leptonType << "LeadingLeptonPtAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << _leptonType << "Leading Lepton Pt After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************

  // Histogram before cut
  _hLeadingLeptonPtBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 100, 0.0, 200.);
  _hLeadingLeptonPtBefore -> SetXAxisTitle("p_{T,leading}");
  _hLeadingLeptonPtBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hLeadingLeptonPtAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 100, 0.0, 200.);
  _hLeadingLeptonPtAfter -> SetXAxisTitle("p_{T,leading}");
  _hLeadingLeptonPtAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Make name in configuration file depending upon muon type
  std::ostringstream configMinMuonStream;
  configMinMuonStream << "Cut.Lepton." << _leptonType.Data() << ".LeadingPt.Min";
  TString configMinMuon = configMinMuonStream.str().c_str();

  // Make name in configuration file depending upon electron type
  std::ostringstream configMinEleStream;
  configMinEleStream << "Cut.Lepton." << _leptonType.Data() << ".LeadingPt.Min";
  TString configMinEle = configMinEleStream.str().c_str();

  // Use configuration to set min/max pt of leptons to cut on
  _LeadingMuonPtCut  = config -> GetValue(configMinMuon.Data(), 999);
  _LeadingElectronPtCut  = config -> GetValue(configMinEle.Data(), 999);

  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  cutFlowTitleStream << _leptonType.Data() << " Leading lepton : P_{T,#mu} > " << _LeadingMuonPtCut << " p_{T,e} > " << _LeadingElectronPtCut;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << _leptonType.Data() << "Lepton.LeadingPt";
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
Bool_t CutGenLeptonPt1::Apply()
{

  // ********************************
  // Get the leading Pt of the leptons
  // ********************************

  // Leading lepton pt
  Float_t LeadingLeptonPt = 0.;

  //Flag
  Bool_t PassesLeadingLetonPt = kFALSE;

  //Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Muon> muonVector;
  std::vector<Electron> electronVector;

  //Assign collections to the above defined vectors
  if(     "Gen"        == _leptonType) {
    muonVector.assign(EventContainerObj -> MCMuons.begin(),           EventContainerObj -> MCMuons.end());
    electronVector.assign(EventContainerObj -> MCElectrons.begin(),           EventContainerObj -> MCElectrons.end());
  }
  else{
    std::cout << "ERROR " << "<HistogramminMuon::Apply()> "
    << "muonType must be Gen" << std::endl;
    exit(8);
  } //else

  // Now go through and see if there's a lepton passing this cut
  for (auto const muon : muonVector){
    if (muon.Pt() > LeadingLeptonPt) LeadingLeptonPt = muon.Pt();
    if (muon.Pt() > _LeadingMuonPtCut) PassesLeadingLetonPt = kTRUE;
  }

  for (auto const electron : electronVector){
    if (electron.Pt() > LeadingLeptonPt) LeadingLeptonPt = electron.Pt();
    if (electron.Pt() > _LeadingElectronPtCut){
      PassesLeadingLetonPt = kTRUE;
    }
  }

  ostringstream cutFlowNameStream;
  TString cutFlowName;

  cutFlowNameStream << _leptonType.Data() << "Lepton.LeadingPt";
  cutFlowName = cutFlowNameStream.str().c_str();

  _hLeadingLeptonPtBefore->Fill(LeadingLeptonPt);
  if (PassesLeadingLetonPt) {
    _hLeadingLeptonPtAfter->Fill(LeadingLeptonPt);
    GetCutFlowTable()->PassCut(cutFlowName.Data());
  }
  else {
    GetCutFlowTable()->FailCut(cutFlowName.Data());
  }

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !PassesLeadingLetonPt ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail PassesLeadingLeptonPt " << _leptonType << " Lep1Pt "<< LeadingLeptonPt <<std::endl;
  }

  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = PassesLeadingLetonPt ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return PassesLeadingLetonPt;
  }


} //Apply
