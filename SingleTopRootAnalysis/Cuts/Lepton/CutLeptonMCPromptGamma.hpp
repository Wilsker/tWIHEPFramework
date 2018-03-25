/******************************************************************************
 * CutLeptonMCPromptGamma.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCPromptGamma class                                *
 *    CutLeptonMCPromptGamma()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCPromptGamma()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCPromptGamma"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCPromptGamma class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutLeptonMCPromptGamma_h
#define CutLeptonMCPromptGamma_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonMCPromptGamma : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonMCPromptGamma(EventContainer *EventContainerObj, Bool_t useMCPromptGamma);
  
  // Destructor
  ~CutLeptonMCPromptGamma();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonMCPromptGamma"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonMCPromptGammaBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonMCPromptGammaAfter;    // Histogram Lepton Number of jets after the cut

  Int_t _LeptonMCPromptGamma;
  Bool_t _useMCPromptGamma;
};


#endif







