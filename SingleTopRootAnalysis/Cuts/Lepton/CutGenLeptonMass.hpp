/******************************************************************************
 * CutGenLeptonMass.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutGenLeptonMass class                                *
 *    CutGenLeptonMass()                     -- Parameterized Constructor           *
 *    ~CutGenLeptonMass()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutGenLeptonMass"                  *
 *                                                                            *
 * Private Data Members of CutGenLeptonMass class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      24 Mar 2009 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutGenLeptonMass_h
#define CutGenLeptonMass_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutGenLeptonMass : public HistoCut
{

public:

  // Parameterized Constructor
  CutGenLeptonMass(EventContainer *EventContainerObj, TString leptonType, TString massCutPostfix = "");

  // Destructor
  ~CutGenLeptonMass();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutGenLeptonMass"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonMassBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonMassAfter;    // Histogram Lepton Number of jets after the cut

  // Cut parameters
  Float_t _LeptonMassMin;         // Minimum Dilepton mass
  Float_t _LeptonMassMax;         // Maximum Dilepton mass

  bool _LeptonMassReject;	  // true to accept only within the region, false to reject region

  // Lepton Type (veto, tight, unIsolated)
  TString leptonType;
  TString massCutPostfix;

};


#endif
