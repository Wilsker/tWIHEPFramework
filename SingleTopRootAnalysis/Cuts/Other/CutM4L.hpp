/******************************************************************************
 * CutM4L.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
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
 *    myTH1F* _hM4LumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hM4LumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _M4LumberMin;          -- Minimum Lepton Number               *
 *    Int_t _M4LumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutM4L_h
#define CutM4L_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutM4L : public HistoCut 
{

public:

  // Parameterized Constructor
  CutM4L(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutM4L();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutM4L"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hM4LBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hM4LAfter;    // Histogram Lepton Number of jets after the cut

  // Cut parameters
  Double_t _M4LMin;         

  // Lepton Type (veto, tight, unIsolated)
  TString leptonType;

};


#endif







