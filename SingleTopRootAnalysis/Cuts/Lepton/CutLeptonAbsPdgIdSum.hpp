/******************************************************************************
 * CutLeptonAbsPdgIdSum.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonAbsPdgIdSum class                                *
 *    CutLeptonAbsPdgIdSum()                     -- Parameterized Constructor           *
 *    ~CutLeptonAbsPdgIdSum()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonAbsPdgIdSum"                  *
 *                                                                            *
 * Private Data Members of CutLeptonAbsPdgIdSum class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                                        *
 *****************************************************************************/

#ifndef CutLeptonAbsPdgIdSum_h
#define CutLeptonAbsPdgIdSum_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonAbsPdgIdSum : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonAbsPdgIdSum(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonAbsPdgIdSum();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonAbsPdgIdSum"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonAbsPdgIdSumBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonAbsPdgIdSumAfter;    // Histogram Lepton Number of jets after the cut

  Int_t _LeptonAbsPdgIdSum;	  

  TString leptonType;

};


#endif







