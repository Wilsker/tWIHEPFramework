/******************************************************************************
 * CutGenTauN.hpp                                                                *
 *                                                                            *
 * Cuts on electron Number                                                    *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutGenTauN class                                   *
 *    CutGenTauN()                     -- Parameterized Constructor              *
 *    ~CutGenTauN()                    -- Destructor                             *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutGenTauN"                     *
 *                                                                            *
 * Private Data Members of CutGenTauN class                                      *
 *    myTH1F* _hTauNumberBefore;    -- Hist e Number before cut               *
 *    myTH1F* _hTauNumberAfter;     -- Hist e Number of jets after cut        *
 *                                                                            *
 *    Int_t _TauNumberMin;          -- Minimum Electron Number                *
 *    Int_t _TauNumberMax;          -- Maximum Electron Number                *
 *                                                                            *
 * History                                                                    *
 *      22 Aug 2007 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutGenTauN_h
#define CutGenTauN_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutGenTauN : public HistoCut
{

public:

  // Parameterized Constructor
  CutGenTauN(EventContainer *EventContainerObj, TString tauType);

  // Destructor
  ~CutGenTauN();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutGenTauN"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hTauNumberBefore;   // Histogram Tau Number before the cut
  myTH1F* _hTauNumberAfter;    // Histogram Tau Number of jets after the cut

  // Cut parameters
  Int_t _TauNumberMin;         // Minimum Tau Number
  Int_t _TauNumberMax;         // Maximum Tau Number

  // Tau Type (veto, tight)
  TString tauType;
};


#endif
