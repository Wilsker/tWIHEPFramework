/******************************************************************************
 * CutLeptonMCRightCharge.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCRightCharge class                                *
 *    CutLeptonMCRightCharge()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCRightCharge()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCRightCharge"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCRightCharge class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutLeptonMCRightCharge_h
#define CutLeptonMCRightCharge_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonMCRightCharge : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonMCRightCharge(EventContainer *EventContainerObj, Bool_t useMCRightCharge);
  
  // Destructor
  ~CutLeptonMCRightCharge();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonMCRightCharge"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonMCRightChargeBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonMCRightChargeAfter;    // Histogram Lepton Number of jets after the cut

  Int_t _LeptonMCRightCharge;
  Bool_t _useMCRightCharge;
};


#endif







