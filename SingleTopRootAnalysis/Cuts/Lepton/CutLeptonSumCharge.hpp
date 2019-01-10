/******************************************************************************
 * CutLeptonSumCharge.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonSumCharge class                                *
 *    CutLeptonSumCharge()                     -- Parameterized Constructor           *
 *    ~CutLeptonSumCharge()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonSumCharge"                  *
 *                                                                            *
 * Private Data Members of CutLeptonSumCharge class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutLeptonSumCharge_h
#define CutLeptonSumCharge_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonSumCharge : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonSumCharge(EventContainer *EventContainerObj, TString leptonType, Int_t whichTrig);
  
  // Destructor
  ~CutLeptonSumCharge();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonSumCharge"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonSumChargeBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonSumChargeAfter;    // Histogram Lepton Number of jets after the cut

  // Sum of lepton charges ?
  Int_t _LeptonSumCharge;	  //  0: Sum of lepton charges is 1 or -1
  
  Int_t _whichTrig; // 6: 3L; 7 :4L

  // Lepton Type (veto, tight, unIsolated)
  TString leptonType;

};


#endif







