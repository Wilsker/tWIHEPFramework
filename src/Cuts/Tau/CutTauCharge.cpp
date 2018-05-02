/******************************************************************************
 * CutTauCharge.hpp                                                             *
 *                                                                            *
 * Cuts on tau Number (can cut on All, UnIsolated, Tight, or Veto Taus) *
 * Must pass All, UnIsolated, Tight, or Veto to constructor                   *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutTauCharge class                                *
 *    CutTauCharge()                     -- Parameterized Constructor           *
 *    ~CutTauCharge()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutTauCharge"                  *
 *                                                                            *
 * Private Data Members of CutTauCharge class                                   *
 *    myTH1F* _hTauNumberBefore;    -- Hist tau Number before cut       *
 *    myTH1F* _hTauNumberAfter;     -- Hist tau Number of jets after cut*
 *                                                                            *
 *    Int_t _TauNumberMin;          -- Minimum Tau Number               *
 *    Int_t _TauNumberMax;          -- Maximum Tau Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Tau/CutTauCharge.hpp"
#include<iostream>

using namespace std;

/*********************************************************************************
 * CutTauCharge::CutTauCharge(EventContainer *EventContainerObj, TString tauType) *
 *                                                                               *
 * Parameterized Constructor                                                     *
 *                                                                               *
 * Input:  Event Object class                                                    *
 * Output: None                                                                  *
 ******************************************************************************/
CutTauCharge::CutTauCharge(EventContainer *EventContainerObj, TString tauTypePassed)
{
  // Check tauType parameter
  if( tauTypePassed.CompareTo("VLoose") && tauTypePassed.CompareTo("Loose") && tauTypePassed.CompareTo("Medium") && 
      tauTypePassed.CompareTo("Tight") && tauTypePassed.CompareTo("VTight")
       ){
    std::cout << "ERROR " << "<CutTauCharge::CutTauCharge()> " 
	      << "Must pass VLoose, Loose, Medium, Tight, VTight  to constructor" << std::endl;
    exit(8);
  } //if
  tauType = tauTypePassed;

  // Set Event Container
  SetEventContainer(EventContainerObj);
} // CutTauCharge


/******************************************************************************
 * CutTauCharge::~CutTauCharge()                                                  *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutTauCharge::~CutTauCharge()
{
  
}//~CutTauCharge

/******************************************************************************
 * void CutTauCharge::BookHistogram()                                           *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutTauCharge::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << tauType << "TauChargeBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << tauType << "Tau Charge Before Cut";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << tauType << "TauChargeAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << tauType << "Tau Charge After Cut";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hTauChargeBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 3, -1.5, 1.5);
  _hTauChargeBefore -> SetXAxisTitle("Tau charge");
  _hTauChargeBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hTauChargeAfter =  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 3, -1.5, 1.5);
  _hTauChargeAfter -> SetXAxisTitle("Tau charge");
  _hTauChargeAfter -> SetYAxisTitle("Events");

  // ***********************************************
  // Get cuts from configuration file
  // ***********************************************  

  // Get configuration file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv *config = EventContainerObj -> GetConfig();

  std::ostringstream configSameSignStream;
  configSameSignStream << "Cut.Dilepton.TTHFake.SameSign";
  TString configSameSign = configSameSignStream.str().c_str();

  //
  //_TauSameSign = config -> GetValue(configSameSign.Data(), false);
  _TauSameSign = config -> GetValue(configSameSign.Data(), 0);
  
  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min + Max cut
  cutFlowTitleStream.str("");
  if(_TauSameSign !=0 ){
   cutFlowTitleStream << tauType.Data() << " Tau : " << (_TauSameSign < 0 ? "Same sign " : "Opposite sign ");
  }else{
   cutFlowTitleStream << tauType.Data() << " Tau : " << "Any sign ";
  }
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream.str("");
  cutFlowNameStream << tauType.Data() << "Tau.Charge.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName, cutFlowTitle);

  
}//BookHistograms()

/******************************************************************************
 * Bool_t CutTauCharge::Apply()                                                 *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the number of electrons and the p_T of these electrons              *
 * Apply separate p_T cuts to the first and second (don't worry about others) *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutTauCharge::Apply()
{

  // ***********************************************
  // Get Number of Taus and fill histograms
  // ***********************************************
  
  // Initialize number of taus
  Float_t TauCharge    = 0;       

  // Flags 
  Bool_t TauChargePass = kTRUE; // Event passes sign selection

  // Get Event Container
  EventContainer *EventContainerObj = GetEventContainer();

  std::vector<Lepton> leptonVector;
  std::vector<Tau> tauVector;


  leptonVector.assign(EventContainerObj -> fakeLeptons.begin(), EventContainerObj -> fakeLeptons.end());
  tauVector.assign(EventContainerObj -> looseTaus.begin(), EventContainerObj -> looseTaus.end());


  //Assign collections to the above defined vectors
  Tau selectedTau;
  for(uint tau_en=0; tau_en< tauVector.size(); tau_en++){
    if(     "VLoose"        == tauType){
        selectedTau = tauVector[0];
        break;
    }
    else if(     "Loose"        == tauType){ 
        if(tauVector.at(tau_en).isLoose()>0.5){
            selectedTau = tauVector.at(tau_en);
            break;
        }
    }
    else if(     "Medium"        == tauType){
        if(tauVector.at(tau_en).isMedium()>0.5){
            selectedTau = tauVector.at(tau_en);
            break;
        }
    }
    else if(     "Tight"        == tauType ){
        if(tauVector.at(tau_en).isTight()>0.5){
            selectedTau = tauVector.at(tau_en);
            break;
        }
    }
    else if(     "VTight"        == tauType ){
        if(tauVector.at(tau_en).isVTight()>0.5){
            selectedTau = tauVector.at(tau_en);
            break;
        }
    }
    else{
        std::cout << "ERROR " << "<CutTauCharge::Apply()> "
	      << "tauType must be VLoose, Loose, Medium, Tight, VTight" << std::endl;
        exit(8);
    } //else                                                                                                          
  }
  TauCharge = selectedTau.charge();

  if(leptonVector[0].charge()*leptonVector[1].charge()>0){//if same sign
    TauChargePass = TauCharge *leptonVector[0].charge() < 0;// tau is opposite to leptons
  }else if(fabs(leptonVector[0].pdgId())+fabs(leptonVector[1].pdgId())==24){// if emu opposite sign
    TauChargePass = (fabs(leptonVector[0].pdgId())==11? TauCharge*leptonVector[0].charge()>0 : TauCharge*leptonVector[1].charge()>0 );// tau is same sign as electron
  }else if(fabs(leptonVector[0].pdgId())+fabs(leptonVector[1].pdgId())==22){// if ee opposite sign
    TauChargePass = true;
  }else{
    TauChargePass = false;
  }


  // Fill the histograms before the cuts
  _hTauChargeBefore    -> Fill(TauCharge);
  
  // ***********************************************
  // Fill cut flow table
  // ***********************************************
  
  // Names for Cut Flow Table
  ostringstream cutFlowNameAllStream;
  
  TString cutFlowNameAll;
  
  cutFlowNameAllStream << tauType.Data() << "Tau.Charge.All";
  cutFlowNameAll = cutFlowNameAllStream.str().c_str();
  
  if ( !TauChargePass){
    GetCutFlowTable()->FailCut(cutFlowNameAll.Data());
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowNameAll.Data());
    _hTauChargeAfter -> Fill(TauCharge);
  }

  // ***********************************************
  // Return if it passes
  // ***********************************************
  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !TauChargePass ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail TauChargePass " << tauType << " TauCharge "<< TauCharge <<" lep1pdg "<< leptonVector[0].pdgId()<< " lep2pdg "<<leptonVector[1].pdgId() << std::endl; 
  }
  
  return(TauChargePass);
 
} //Apply












