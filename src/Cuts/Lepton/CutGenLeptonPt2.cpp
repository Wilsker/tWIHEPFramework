/******************************************************************************
* CutGenLeptonPt2.hpp                                                               *
*                                                                            *
* Cuts on muon Number (can cut on All, UnIsolated, Tight, or Veto Muons)     *
* Must pass All, UnIsolated, Tight, or Veto to constructor                   *
*                                                                            *
* Derived from HistoCut which is in turn derived from BaseCut                *
*                                                                            *
*                                                                            *
* Public Member Functions of CutGenLeptonPt2 class                                  *
*    CutGenLeptonPt2()                     -- Parameterized Constructor             *
*    ~CutGenLeptonPt2()                    -- Destructor                            *
*    BookHistogram()                -- Book histograms                       *
*    Apply()                        -- Apply cuts and fill histograms        *
*    GetCutName()                   -- Returns "CutGenLeptonPt2"                    *
*                                                                            *
* Private Data Members of CutGenLeptonPt2 class                                     *
*    myTH1F* _hMuonNumberBefore;    -- Hist mu Number before cut             *
*    myTH1F* _hMuonNumberAfter;     -- Hist mu Number of jets after cut      *
*                                                                            *
*    Int_t _MuonNumberMin;          -- Minimum Muon Number                   *
*    Int_t _MuonNumberMax;          -- Maximum Muon Number                   *
*                                                                            *
* History                                                                    *
*      11 Dec 2017 - Created by B. Li based on CutLeptonPt1 by P. Ryan       *
*****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Lepton/CutGenLeptonPt2.hpp"
#include<iostream>

using namespace std;

/******************************************************************************
* CutGenLeptonPt2::CutGenLeptonPt2(EventContainer *EventContainerObj, TString muonType)    *
*                                                                            *
* Parameterized Constructor                                                  *
*                                                                            *
* Input:  Event Object class                                                 *
* Output: None                                                               *
******************************************************************************/
CutGenLeptonPt2::CutGenLeptonPt2(EventContainer *EventContainerObj, TString leptonType)
{
  // Check muonType parameter
  if( leptonType.CompareTo("Gen")
){
  std::cout << "ERROR " << "<CutGenLeptonPt2::CutGenLeptonPt2()> "
  << "Must pass Gen to constructor" << std::endl;
  exit(8);
} //if
_leptonType = leptonType;

// Set Event Container
SetEventContainer(EventContainerObj);
} // CutGenLeptonPt2


/******************************************************************************
* CutGenLeptonPt2::~CutGenLeptonPt2()                                                *
*                                                                            *
* Destructor                                                                 *
*                                                                            *
* Input:  None                                                               *
* Output: None                                                               *
******************************************************************************/
CutGenLeptonPt2::~CutGenLeptonPt2()
{

}//~CutGenLeptonPt2

/******************************************************************************
* void CutGenLeptonPt2::BookHistogram()                                          *
*                                                                            *
* Book Histograms                                                            *
*                                                                            *
* Input:  None                                                               *
* Output: None                                                               *
******************************************************************************/
void CutGenLeptonPt2::BookHistogram(){

  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << _leptonType << "SubLeadingLeptonPtBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << _leptonType << "SubLeading Lepton Pt Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << _leptonType << "SubLeadingLeptonPtAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << _leptonType << "SubLeading Lepton Pt After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************

  // Histogram before cut
  _hSubLeadingLeptonPtBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 100, 0.0, 200.);
  _hSubLeadingLeptonPtBefore -> SetXAxisTitle("p_{T,subleading}");
  _hSubLeadingLeptonPtBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hSubLeadingLeptonPtAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 100, 0.0, 200.);
  _hSubLeadingLeptonPtAfter -> SetXAxisTitle("p_{T,subleading}");
  _hSubLeadingLeptonPtAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Make name in configuration file depending upon muon type (all, veto, tight, unIsolated)
  std::ostringstream configMinLeptonStream;
  configMinLeptonStream << "Cut.Lepton." << _leptonType.Data() << ".SubLeadingPt.Min";
  TString configMinLepton = configMinLeptonStream.str().c_str();

  // Use configuration to set min and max number of jets to cut on
  _SubLeadingLeptonPtCut  = config -> GetValue(configMinLepton.Data(), 999);

  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  cutFlowTitleStream << _leptonType.Data() << " SubLeading lepton : P_{T,l} > " << _SubLeadingLeptonPtCut;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << _leptonType.Data() << "Lepton.SubLeadingPt";
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
Bool_t CutGenLeptonPt2::Apply()
{

  // ********************************
  // Get the leading Pt of the leptons
  // ********************************

  // SubLeading lepton pt
  Float_t SubLeadingLeptonPt = 0.;
  Float_t LeadingLeptonPt = 0.;

  //Flag
  Bool_t PassesSubLeadingLetonPt = kFALSE;

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

  std::sort(muonVector.begin(),muonVector.end());
  std::sort(electronVector.begin(),electronVector.end());

  // Now go through and see if there's a lepton passing this cut
  for (auto const muon : muonVector){
    if (muon.Pt() > LeadingLeptonPt) LeadingLeptonPt = muon.Pt();
  }

  for (auto const electron : electronVector){
    if (electron.Pt() > LeadingLeptonPt) LeadingLeptonPt = electron.Pt();
  }

  // Now go through and see if there's a lepton passing this cut
  // Note: for the subleading leptons we start from index 1.
  cout << "Total # muons : " << muonVector.size() << endl;
  for (auto const muon : muonVector){
    Muon muon = muonVector.at(mu_en);
    cout << "muon.Pt()= " << muon.Pt() << endl;
    if (muon.Pt() > SubLeadingLeptonPt && muon.Pt()!=LeadingLeptonPt) SubLeadingLeptonPt = muon.Pt();
    if (muon.Pt() > _SubLeadingLeptonPtCut){
      PassesSubLeadingLetonPt = kTRUE;
    }
  }

  for (auto const electron : electronVector){
    Electron electron = electronVector.at(el_en);
    if (electron.Pt() > SubLeadingLeptonPt && electron.Pt()!=LeadingLeptonPt) SubLeadingLeptonPt = electron.Pt();
    if (electron.Pt() > _SubLeadingLeptonPtCut){
      PassesSubLeadingLetonPt = kTRUE;
    }
  }

  _hSubLeadingLeptonPtBefore->Fill(SubLeadingLeptonPt);

  ostringstream cutFlowNameStream;
  TString cutFlowName;

  cutFlowNameStream << _leptonType.Data() << "Lepton.SubLeadingPt";
  cutFlowName = cutFlowNameStream.str().c_str();

  if (PassesSubLeadingLetonPt) {
    _hSubLeadingLeptonPtAfter->Fill(SubLeadingLeptonPt);
    GetCutFlowTable()->PassCut(cutFlowName.Data());
  }
  else {
    GetCutFlowTable()->FailCut(cutFlowName.Data());
  }

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !PassesSubLeadingLetonPt ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail PassesSubLeadingLetonPt " << _leptonType << " Lep2Pt "<< SubLeadingLeptonPt<<   std::endl;
  }

  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = PassesSubLeadingLetonPt ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return PassesSubLeadingLetonPt;
  }


} //Apply
