/******************************************************************************
 * CutM4L.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on All, UnIsolated, Tight, or Veto Leptons) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutM4L class                                *
 *    CutM4L()                     -- Parameterized Constructor           *
 *    ~CutM4L()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutM4L"                  *
 *                                                                            *
 * Private Data Members of CutM4L class                                   *
 *    myTH1F* _hM4LBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hM4LAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _M4LMin;          -- Minimum Lepton Number               *
 *    Int_t _M4LMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutM4L.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutM4L::CutM4L(EventContainer *EventContainerObj, TString leptonType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutM4L::CutM4L(EventContainer *EventContainerObj, TString leptonTypePassed)
{
  // Check leptonType parameter
  if( 
      leptonTypePassed.CompareTo("TTHLoose")
       && leptonTypePassed.CompareTo("TTHTight")
       && leptonTypePassed.CompareTo("TTHFake")
      ){
    std::cout << "ERROR " << "<CutM4L::CutM4L()> " 
	      << "Must pass TTHLoose, TTHTight, TTHFake to constructor" << std::endl;
    exit(8);
  } //if
  leptonType = leptonTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutM4L


/******************************************************************************
 * CutM4L::~CutM4L()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutM4L::~CutM4L()
{
  
}//~CutM4L

/******************************************************************************
 * void CutM4L::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutM4L::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << leptonType << ".M4LBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << leptonType << ".M4LBefore";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << leptonType << ".M4LAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << leptonType << ".M4LAfter";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hM4LBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 100, 0.0, 300);
  _hM4LBefore -> SetXAxisTitle("Mass_4L");
  _hM4LBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hM4LAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 100, 0.0, 30);
  _hM4LAfter -> SetXAxisTitle("Mass_4L");
  _hM4LAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  // Make name in configuration file depending upon lepton type (all, veto, tight, unIsolated)
  std::ostringstream configMinStream;
  configMinStream << "Cut.Event." << leptonType.Data() << ".Mass4L.Min";
  TString configMin = configMinStream.str().c_str();


  // Use configuration to set min and max number of jets to cut on
  _M4LMin  = config -> GetValue(configMin.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << leptonType.Data() << " Lepton: M_4l >= " << _M4LMin;
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << leptonType.Data() << "M4L.Min";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutM4L::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutM4L::Apply()
{

  // ***********************************************
  // Get Number of Leptons and fill histograms
  // ***********************************************
  
  // Initialize number of leptons
  std::vector<Lepton> leptonVector;
  Double_t Mass_4L    = 999.;       
  
  Bool_t PassedM4L = kTRUE;

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();
  if(     "TTHLoose"        == leptonType) {
    leptonVector.assign(EventContainerObj -> looseLeptons.begin(), EventContainerObj -> looseLeptons.end());
  }else if("TTHFake" == leptonType) {
    leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  }else if("TTHTight" == leptonType) {
    leptonVector.assign(EventContainerObj -> tightLeptons.begin(), EventContainerObj -> tightLeptons.end());
  }
  else{
    std::cout << "ERROR " << "<CutLeptonCharge::Apply()> "
	      << "leptonType must be TTHLoose, TTHTight, TTHFake" << std::endl;
    exit(8);
  } //else                                                                                                          

  for(uint lep1_en=0; lep1_en< leptonVector.size(); lep1_en++){
    Double_t lep1_pdg = leptonVector.at(lep1_en).pdgId();
    for(uint lep2_en=lep1_en+1; lep2_en< leptonVector.size(); lep2_en++){
        if(lep2_en == lep1_en)continue;
        Double_t lep2_pdg = leptonVector.at(lep2_en).pdgId();
        for(uint lep3_en=lep2_en+1; lep3_en< leptonVector.size(); lep3_en++){
            if(lep3_en == lep1_en || lep3_en == lep2_en)continue;
            Double_t lep3_pdg = leptonVector.at(lep3_en).pdgId();
            for(uint lep4_en=lep3_en+1; lep4_en< leptonVector.size(); lep4_en++){
                if(lep4_en == lep1_en || lep4_en == lep2_en || lep4_en == lep3_en)continue;
                Double_t lep4_pdg = leptonVector.at(lep4_en).pdgId();
                if((lep1_pdg + lep2_pdg + lep3_pdg + lep4_pdg)==0){
                    TLorentzVector Lep1(0,0,0,0); 
                    TLorentzVector Lep2(0,0,0,0); 
                    TLorentzVector Lep3(0,0,0,0); 
                    TLorentzVector Lep4(0,0,0,0);
                    Lep1.SetPtEtaPhiE(leptonVector[lep1_en].Pt(),leptonVector[lep1_en].Eta(),leptonVector[lep1_en].Phi(),leptonVector[lep1_en].E()); 
                    Lep2.SetPtEtaPhiE(leptonVector[lep2_en].Pt(),leptonVector[lep2_en].Eta(),leptonVector[lep2_en].Phi(),leptonVector[lep2_en].E()); 
                    Lep3.SetPtEtaPhiE(leptonVector[lep3_en].Pt(),leptonVector[lep3_en].Eta(),leptonVector[lep3_en].Phi(),leptonVector[lep3_en].E()); 
                    Lep4.SetPtEtaPhiE(leptonVector[lep4_en].Pt(),leptonVector[lep4_en].Eta(),leptonVector[lep4_en].Phi(),leptonVector[lep4_en].E()); 
                    Mass_4L = (Lep4+Lep1+Lep2+Lep3).M();
                }
                if(Mass_4L < _M4LMin){
                    PassedM4L = kFALSE;
                    break;   
                }
            }
        }
    }
  }

  // Fill the histograms before the cuts
  _hM4LBefore    -> Fill(Mass_4L);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameMinStream;
  
  TString cutFlowNameMin;
  
  cutFlowNameMinStream << leptonType.Data() << "M4L.Min";
  cutFlowNameMin = cutFlowNameMinStream.str().c_str();
  
  // Cut on Min Number of Leptons
  if(PassedM4L){
    _hM4LAfter -> Fill(Mass_4L);
    GetCutFlowTable() -> PassCut(cutFlowNameMin.Data());
  } //if
  else GetCutFlowTable() -> FailCut(cutFlowNameMin.Data());

  // ***********************************************
  // Return result of Min and Max Cut
  // ***********************************************
 
  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !PassedM4L ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail CutM4L " << leptonType << " M4L "<< Mass_4L << " > M4LMin? " << _M4LMin << std::endl; 
  }
  
  if(EventContainerObj->_SaveCut ==1 ){
    Double_t flag = PassedM4L ? 1:0;
    EventContainerObj->Flag_cuts.push_back(flag);
    return kTRUE;
  }else{
    return(PassedM4L);
  }
 
} //Apply












