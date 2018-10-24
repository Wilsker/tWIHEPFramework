/******************************************************************************
 * CutLeptonSameSign.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonSameSign class                                *
 *    CutLeptonSameSign()                     -- Parameterized Constructor           *
 *    ~CutLeptonSameSign()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonSameSign"                  *
 *                                                                            *
 * Private Data Members of CutLeptonSameSign class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutLeptonSameSign_h
#define CutLeptonSameSign_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonSameSign : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonSameSign(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonSameSign();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonSameSign"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonSameSignBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonSameSignAfter;    // Histogram Lepton Number of jets after the cut

  //Do we want same or opposite sign?
  Int_t _LeptonSameSign;	  // 1: samesign; -1: opp sign; 0: any sign 

  // Lepton Type (veto, tight, unIsolated)
  TString leptonType;

};


#endif







