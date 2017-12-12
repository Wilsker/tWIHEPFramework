/******************************************************************************
 * CutLeptonConversion.hpp                                                             *
 *                                                                            *
 * Cuts on lepton Number (can cut on unIsolated, tight, or veto Leptons)      *
 * Must pass unisolated, tight, or veto to constructor                        *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 *                                                                            *
 * Public Member Functions of CutLeptonConversion class                                *
 *    CutLeptonConversion()                     -- Parameterized Constructor           *
 *    ~CutLeptonConversion()                    -- Destructor                          *
 *    BookHistogram()                -- Book histograms                       *
 *    Apply()                        -- Apply cuts and fill histograms        *
 *    GetCutName()                   -- Returns "CutLeptonConversion"                  *
 *                                                                            *
 * Private Data Members of CutLeptonConversion class                                   *
 *    myTH1F* _hLeptonMassumberBefore;    -- Hist lepton Number before cut       *
 *    myTH1F* _hLeptonMassumberAfter;     -- Hist lepton Number of jets after cut*
 *                                                                            *
 *    Int_t _LeptonNumberMin;          -- Minimum Lepton Number               *
 *    Int_t _LeptonNumberMax;          -- Maximum Lepton Number               *
 *                                                                            *
 * History                                                                    *
 *      12 Dec 2017 - Created by B.Li                                        *
 *****************************************************************************/

#ifndef CutLeptonConversion_h
#define CutLeptonConversion_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class CutLeptonConversion : public HistoCut 
{

public:

  // Parameterized Constructor
  CutLeptonConversion(EventContainer *EventContainerObj, TString leptonType);
  
  // Destructor
  ~CutLeptonConversion();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutLeptonConversion"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hLeptonConversionBefore;   // Histogram Lepton Number before the cut
  myTH1F* _hLeptonConversionAfter;    // Histogram Lepton Number of jets after the cut

  TString leptonType;

};


#endif







