/******************************************************************************
 * CutLeptonMissHit.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMissHit class                                *
 *    CutLeptonMissHit()                     -- Parameterized Constructor           *
 *    ~CutLeptonMissHit()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMissHit"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMissHit class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                                        *
 *****************************************************************************/

#ifndef CutLeptonMissHit_h
#define CutLeptonMissHit_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonMissHit : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonMissHit(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonMissHit();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonMissHit"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonMissHitBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonMissHitAfter;    // Histogram Lepton Number of jets after the cut

  TString leptonType;

};


#endif







