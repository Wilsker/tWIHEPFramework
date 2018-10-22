/******************************************************************************
 * CutLeptonPt3.hpp                                                           *
 *                                                                            *
 * Cuts on lepton pT                                                          *
 * Cut on Electron pT *OR* Muon pT                                            *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutLeptonPt3 class                              *
 *    CutLeptonPt3()                    -- Parameterized Constructor          *
 *    ~CutLeptonPt3()                   -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutLeptonPt3"             *
 *                                                                            *
 * Private Data Members of CutLeptonPt3 class                                 *
 *    myTH1F* _hElectronPt2Before;      // Hist Ele 1 p_T before cut          *
 *    myTH1F* _hElectronPt2After;       // Hist Ele1 p_T of jets after cut    *
 *                                                                            *
 *    myTH1F* _hMuonPt2Before;          // Hist Muon 1 p_T before cut         *
 *    myTH1F* _hMuonPt2After;           // Hist Muon 1 p_T of jets after cut  *
 *                                                                            *
 *    Int_t _ElectronNumberMin;         // Minimum Electron Number            *
 *    Int_t _ElectronNumberMax;         // Maximum Electron Number            *
 *                                                                            *
 *    Int_t _MuonNumberMin;             // Minimum Muon Number                *
 *    Int_t _MuonNumberMax;             // Maximum Muon Number                *
 *                                                                            *
 *    Double_t _ElectronPt2Min;         // Minimum Electron 1 p_T             *
 *    Double_t _ElectronPt2Max;         // Maximum Electron 1 p_T             *
 *                                                                            *
 *    Double_t _MuonPt2Min;             // Minimum Muon 1 p_T                 *
 *    Double_t _MuonPt2Max;             // Maximum Muon 1 p_T                 *
 *                                                                            *
 * History                                                                    *
 *      11 Dec 2017 - Created by B. Li based on CutLeptonPt3 by P. Ryan       *
 *****************************************************************************/

#ifndef CutLeptonPt3_h
#define CutLeptonPt3_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonPt3 : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonPt3(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonPt3();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonPt3"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  //  myTH1F* _hElectronPt2Before;      // Histogram Electron 1 p_T before the cut
  //myTH1F* _hElectronPt2After;       // Histogram Electron 1 p_T of jets after the cut

  //myTH1F* _hMuonPt2Before;          // Histogram Muon 1 p_T before the cut
  //  myTH1F* _hMuonPt2After;           // Histogram Muon 1 p_T of jets after the cut

  // The type of lepton we are using
  TString _leptonType;

  myTH1F* _hThirdLeptonPtBefore;  // Histogram of leading pt before cut
  myTH1F* _hThirdLeptonPtAfter;   // Histogram of leading pt after cut

  // Cut parameters
  Double_t _ThirdMuonPtCut;
  Double_t _ThirdElectronPtCut;

  /*Int_t _ElectronNumberMin;         // Minimum Electron Number
  Int_t _ElectronNumberMax;         // Maximum Electron Number

  Int_t _MuonNumberMin;             // Minimum Muon Number
  Int_t _MuonNumberMax;             // Maximum Muon Number

  Double_t _ElectronPt2Min;         // Minimum Electron 1 p_T
  Double_t _ElectronPt2Max;         // Maximum Electron 1 p_T

  Double_t _MuonPt2Min;             // Minimum Muon 1 p_T
  Double_t _MuonPt2Max;             // Maximum Muon 1 p_T
  */

};


#endif






