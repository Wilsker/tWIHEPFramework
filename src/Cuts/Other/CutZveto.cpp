/******************************************************************************
 * CutZveto.cpp                                                       *
 *                                                                            *
 * Cuts on the requirement of a good primary vertex                           *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutZveto class                              *
 *    CutZveto()                     -- Parameterized Constructor         *
 *    ~CutZveto()                    -- Destructor                        *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutZveto"                *
 *                                                                            *
 * Private Data Members of CutZveto class                                 *
 *    myTH1F* _hZvetoBefore;    -- Hist of PV before cut        *
 *    myTH1F* _hZvetoAfter;     -- Hist of PV after cut         *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                              *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Other/CutZveto.hpp"
#include <iostream>

using namespace std;

/******************************************************************************
 * CutZveto::CutZveto(EventContainer *EventContainerObj, TString electronType)    *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Event Object class                                                 *
 * Output: None                                                               *
 ******************************************************************************/
CutZveto::CutZveto(EventContainer *EventContainerObj, TString LeptonPairType)
{
  // Check leptonType parameter
  if( 
       LeptonPairType.CompareTo("presel_ele")
       && LeptonPairType.CompareTo("presel_SFOSlep")
      ){
    std::cout << "ERROR " << "<CutZveto::CutZveto()> " 
	      << "Must pass presel_ele or presel_SFOSlep to constructor" << std::endl;
    exit(8);
  }
  // Set Event Container
  SetEventContainer(EventContainerObj);
  _LeptonPairType = LeptonPairType;
} // CutZveto


/******************************************************************************
 * CutZveto::~CutZveto()                                              *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
CutZveto::~CutZveto()
{
  
}//~CutZveto

/******************************************************************************
 * void CutZveto::BookHistogram()                                         *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void CutZveto::BookHistogram(){
  
  // ***********************************************
  // Make Strings for histogram titles and labels
  // ***********************************************  

  // Histogram Before Cut
  std::ostringstream histNameBeforeStream;
  histNameBeforeStream << "ZvetoBefore";
  TString histNameBefore = histNameBeforeStream.str().c_str();

  std::ostringstream histTitleBeforeStream;
  histTitleBeforeStream << "Zveto Before";
  TString histTitleBefore = histTitleBeforeStream.str().c_str();

  // Histogram After Cut
  std::ostringstream histNameAfterStream;
  histNameAfterStream << "ZvetoAfter";
  TString histNameAfter = histNameAfterStream.str().c_str();

  std::ostringstream histTitleAfterStream;
  histTitleAfterStream << "Zveto After";
  TString histTitleAfter = histTitleAfterStream.str().c_str();

  // ***********************************************
  // Book Histograms
  // ***********************************************  

  // Histogram before cut
  _hZvetoBefore =  DeclareTH1F(histNameBefore.Data(), histTitleBefore.Data(), 100, 0.0, 200.);
  _hZvetoBefore -> SetXAxisTitle("DiEle Mass");
  _hZvetoBefore -> SetYAxisTitle("Events");

  // Histogram after cut
  _hZvetoAfter=  DeclareTH1F(histNameAfter.Data(), histTitleAfter.Data(), 100, 0.0, 200.);
  _hZvetoAfter-> SetXAxisTitle("DiEle Mass");
  _hZvetoAfter-> SetYAxisTitle("Events");


  // ***********************************************
  // Add these cuts to the cut flow table
  // ***********************************************
  ostringstream cutFlowTitleStream;
  ostringstream cutFlowNameStream;
  TString cutFlowTitle;
  TString cutFlowName;

  // Min cut
  cutFlowTitleStream << "Zveto Cut";
  cutFlowTitle = cutFlowTitleStream.str().c_str();

  cutFlowNameStream << "Zveto.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  GetCutFlowTable()->AddCutToFlow(cutFlowName.Data(), cutFlowTitle.Data());


  // ***********************************************
  // Get the PV IDs from the config file. Perhaps these should be included as an object
  // ***********************************************

  //First, get the config file
  EventContainer *EventContainerObj = GetEventContainer();
  TEnv * config = EventContainerObj->GetConfig();

  //Then set the cuts here.
  _ZvetoMin = config -> GetValue("Cut.Event.Zveto.Min",0.0);
  _ZvetoMax = config -> GetValue("Cut.Event.Zveto.Max",999.0);
  _isOffZ = config -> GetValue("Cut.Event.Zveto.isOffZ",1);

}//BookHistograms()

/******************************************************************************
 * Bool_t CutZveto::Apply()                                               *
 *                                                                            *
 * Apply cuts and fill histograms                                             *
 *                                                                            *
 * Cut on the selected trigger                                                *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t CutZveto::Apply()
{

  EventContainer *EventContainerObj = GetEventContainer();

  Bool_t passesZvetoCut = kTRUE;

  Float_t massZ = 0.;
  
  if(_LeptonPairType =="presel_ele") massZ=EventContainerObj->mass_diele;
  else if(_LeptonPairType =="presel_SFOSlep") massZ=EventContainerObj->massL_SFOS;

  _hZvetoBefore->Fill(massZ);



  ostringstream cutFlowNameStream;
                                
  TString cutFlowName;            

  cutFlowNameStream << "Zveto.All";
  cutFlowName = cutFlowNameStream.str().c_str();

  if(_isOffZ ==1 && massZ > _ZvetoMin && massZ < _ZvetoMax) passesZvetoCut = kFALSE;
  if(_isOffZ ==0 && (massZ < _ZvetoMin || massZ > _ZvetoMax)) passesZvetoCut = kFALSE;

  if (!passesZvetoCut){
    GetCutFlowTable()->FailCut(cutFlowName);
  }
  else{
    GetCutFlowTable()->PassCut(cutFlowName);
    _hZvetoAfter->Fill(massZ);
  }

  if( EventContainerObj->_sync >= 80  && EventContainerObj->_sync != 99 && EventContainerObj->_debugEvt == EventContainerObj->eventNumber && !passesZvetoCut ){
    std::cout<< " Event " << EventContainerObj->_debugEvt <<" Fail passesZvetoCut: massZ is " << massZ  <<  " isOffZ? "<< _isOffZ<<" _ZvetoMin "<< _ZvetoMin << " _ZvetoMax "<<_ZvetoMax << std::endl; 
  }
  return passesZvetoCut;

} //Apply












