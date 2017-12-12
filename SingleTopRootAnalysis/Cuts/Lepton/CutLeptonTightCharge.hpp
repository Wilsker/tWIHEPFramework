/******************************************************************************
 * CutLeptonTightCharge.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonTightCharge class                                *
 *    CutLeptonTightCharge()                     -- Parameterized Constructor           *
 *    ~CutLeptonTightCharge()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonTightCharge"                  *
 *                                                                            *
 * Private Data Members of CutLeptonTightCharge class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                                        *
 *****************************************************************************/

#ifndef CutLeptonTightCharge_h
#define CutLeptonTightCharge_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonTightCharge : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonTightCharge(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonTightCharge();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonTightCharge"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonTightChargeBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonTightChargeAfter;    // Histogram Lepton Number of jets after the cut

  TString leptonType;

};


#endif







