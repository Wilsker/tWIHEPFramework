/******************************************************************************
 * CutGenLeptonN.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutGenLeptonN class                                *
 *    CutGenLeptonN()                     -- Parameterized Constructor           *
 *    ~CutGenLeptonN()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutGenLeptonN"                  *
 *                                                                            *
 * Private Data Members of CutGenLeptonN class                                   *
 *    myTH1F* _hLeptonNumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonNumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutGenLeptonN_h
#define CutGenLeptonN_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutGenLeptonN : public HistoCut
{

public:

  // Parameterized Constructor
  CutGenLeptonN(EventContainer *EventContainerObj, TString leptonType);

  // Destructor
  ~CutGenLeptonN();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutGenLeptonN"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonNumberBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonNumberAfter;    // Histogram Lepton Number of jets after the cut

  // Cut parameters
  Int_t _LeptonNumberMin;         // Minimum Lepton Number
  Int_t _LeptonNumberMax;         // Maximum Lepton Number

  // Lepton Type (veto, tight, unIsolated)
  TString leptonType;

};


#endif
