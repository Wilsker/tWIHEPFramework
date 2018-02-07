/******************************************************************************
 * CutLeptonMCMatchId.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCMatchId class                                *
 *    CutLeptonMCMatchId()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCMatchId()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCMatchId"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCMatchId class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutLeptonMCMatchId_h
#define CutLeptonMCMatchId_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonMCMatchId : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonMCMatchId(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutLeptonMCMatchId();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonMCMatchId"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonMCMatchIdBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonMCMatchIdAfter;    // Histogram Lepton Number of jets after the cut

  Int_t _LeptonMCMatchId;
};


#endif







