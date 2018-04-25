/******************************************************************************
 * CutTauCharge.hpp                                                             *
 *                                                                            *
 * Cuts on tau Number (can cut on unIsolated, tight, or veto Taus)      *
 * Must pass unisolated, tight, or veto to constructor                        *
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
 *    myTH1F* _hTauMassumberBefore;    -- Hist tau Number before cut       *
 *    myTH1F* _hTauMassumberAfter;     -- Hist tau Number of jets after cut*
 *                                                                            *
 *    Int_t _TauNumberMin;          -- Minimum Tau Number               *
 *    Int_t _TauNumberMax;          -- Maximum Tau Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutTauCharge_h
#define CutTauCharge_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutTauCharge : public HistoCut 
{

public:

  // Parameterized Constructor
  CutTauCharge(EventContainer *EventContainerObj, TString tauType);
  
  // Destructor
  ~CutTauCharge();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutTauCharge"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hTauChargeBefore;   // Histogram Tau Number before the cut
  myTH1F* _hTauChargeAfter;    // Histogram Tau Number of jets after the cut

  //Do we want same or opposite sign?
  Int_t _TauSameSign;	  // 1: samesign; -1: opp sign; 0: any sign 

  // Tau Type (veto, tight, unIsolated)
  TString tauType;

};


#endif







