/******************************************************************************
 * CutLeptonMCPromptFS.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonMCPromptFS class                                *
 *    CutLeptonMCPromptFS()                     -- Parameterized Constructor           *
 *    ~CutLeptonMCPromptFS()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonMCPromptFS"                  *
 *                                                                            *
 * Private Data Members of CutLeptonMCPromptFS class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutLeptonMCPromptFS_h
#define CutLeptonMCPromptFS_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonMCPromptFS : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonMCPromptFS(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutLeptonMCPromptFS();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonMCPromptFS"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonMCPromptFSBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonMCPromptFSAfter;    // Histogram Lepton Number of jets after the cut

  Int_t _LeptonMCPromptFS;
};


#endif







