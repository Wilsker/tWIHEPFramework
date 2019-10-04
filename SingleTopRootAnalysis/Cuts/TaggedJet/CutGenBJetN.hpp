/******************************************************************************
 * CutGenBJetN.hpp                                                          *
 *                                                                            *
 * Cuts on number of tagged jets in an event                                  *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutGenBJetN class                             *
 *    CutGenBJetN()                   -- Parameterized Constructor          *
 *    ~CutGenBJetN()                  -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutGenBJetN"            *
 *                                                                            *
 * Private Data Members of CutGenBJetN                                      *
 *    myTH1F* _hJetNumberBefore         -- Hist of Num of jets before cuts    *
 *    myTH1F* _hJetNumberAfter          -- Hist of Num of jets before cuts    *
 *    Int_t _JetNumberMin;              -- Minimum number of jets to require  *
 *    Int_t _JetNumberMax;              -- Maximum number of jets allowed     *
 *                                                                            *
 * History                                                                    *
 *      23 Feb 2007 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutGenBJetN_h
#define CutGenBJetN_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutGenBJetN : public HistoCut
{

public:

  // Parameterized Constructor
  CutGenBJetN(EventContainer *EventContainerObj, Int_t nJetsDefault = -1);

  // Destructor
  ~CutGenBJetN();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutGenBJetN"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hbJetNumberBefore;    // Histogram number of jets before the cut
  myTH1F* _hbJetNumberAfter;     // Histogram number of jets after the cut

  // Cut parameters
  Int_t _bJetNumberMin;           // Minimum number of b-jets to require
  Int_t _bJetNumberMax;           // Maximum number of b-jets allowed
};


#endif
