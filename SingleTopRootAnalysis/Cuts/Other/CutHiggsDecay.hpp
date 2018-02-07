/******************************************************************************
 * CutHiggsDecay.hpp                                                               *
 *                                                                            *
 * Cuts on HiggsDecay                                                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutHiggsDecay class                                  *
 *    CutHiggsDecay()                    -- Parameterized Constructor              *
 *    ~CutHiggsDecay()                   -- Destructor                             *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutHiggsDecay"                 *
 *                                                                            *
 * Private Data Members of CutHiggsDecay                                           *
 *    myTH1F* _hHiggsDecayBefore         -- Hist of HiggsDecay before cuts              *
 *    myTH1F* _hHiggsDecayAfter          -- Hist of HiggsDecay after cuts               *
 *    Double_t _HiggsDecayMin;              -- Minimum HiggsDecay window                *
 *    Double_t _HiggsDecayMin;              -- Minimum HiggsDecay window                *
 *                                                                            *
 * History                                                                    *
 *      03 Dec 2010 - Created by H. Zhang                                     *
 *****************************************************************************/

#ifndef CutHiggsDecay_h
#define CutHiggsDecay_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutHiggsDecay : public HistoCut 
{

public:

  // Parameterized Constructor
  CutHiggsDecay(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutHiggsDecay();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutHiggsDecay"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hHiggsDecayBefore;    // Histogram HiggsDecay
  myTH1F* _hHiggsDecayAfter;     // Histogram HiggsDecay

  // Cut parameters
  Double_t _HiggsDecayType;     //  0: H->WW/ZZ/TauTau; 1: H->WW ; 2: H->TauTau; 3: H->ZZ; 4: H->WW or ZZ; 5: H->WW/TauTau; 6: H->TauTau/ZZ

};


#endif







