/******************************************************************************
 * CutLeptonTight.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonTight class                                *
 *    CutLeptonTight()                     -- Parameterized Constructor           *
 *    ~CutLeptonTight()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonTight"                  *
 *                                                                            *
 * Private Data Members of CutLeptonTight class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      11 Dec 2017 - Created by B.Li based on CutLeptonCharge by P.Ryan       *
 *****************************************************************************/

#ifndef CutLeptonTight_h
#define CutLeptonTight_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonTight : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonTight(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonTight();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonTight"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonTightBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonTightAfter;    // Histogram Lepton Number of jets after the cut
  
  Int_t _LeptonNumTightMin;
  Int_t _LeptonNumTightMax;

  // Lepton Type (veto, tight, unIsolated)
  TString leptonType;

};


#endif







