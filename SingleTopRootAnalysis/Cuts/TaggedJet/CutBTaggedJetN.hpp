/******************************************************************************
 * CutBTaggedJetN.hpp                                                          *
 *                                                                            *
 * Cuts on number of tagged jets in an event                                  *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutBTaggedJetN class                             *
 *    CutBTaggedJetN()                   -- Parameterized Constructor          *
 *    ~CutBTaggedJetN()                  -- Destructor                         *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutBTaggedJetN"            *
 *                                                                            *
 * Private Data Members of CutBTaggedJetN                                      *
 *    myTH1F* _hJetNumberBefore         -- Hist of Num of jets before cuts    *
 *    myTH1F* _hJetNumberAfter          -- Hist of Num of jets before cuts    *
 *    Int_t _JetNumberMin;              -- Minimum number of jets to require  *
 *    Int_t _JetNumberMax;              -- Maximum number of jets allowed     *
 *                                                                            *
 * History                                                                    *
 *      23 Feb 2007 - Created by P. Ryan                                      *
 *****************************************************************************/

#ifndef CutBTaggedJetN_h
#define CutBTaggedJetN_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutBTaggedJetN : public HistoCut 
{

public:

  // Parameterized Constructor
  CutBTaggedJetN(EventContainer *EventContainerObj, Int_t nbJetsDefault, Int_t nbMediumJetsDefault);
  
  // Destructor
  ~CutBTaggedJetN();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutBTaggedJetN"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hbLooseJetNumberBefore;    // Histogram number of jets before the cut
  myTH1F* _hbLooseJetNumberAfter;     // Histogram number of jets after the cut

  // Cut parameters
  Int_t _isAndLogic;           //  default 0 : use or logic
  Int_t _bLooseJetNumberMin;           // Minimum number of loose-b-jets to require
  Int_t _bLooseJetNumberMax;           // Maximum number of loose-b-jets allowed
  Int_t _bMediumJetNumberMin;           // Minimum number of medium-b-jets to require
  Int_t _bMediumJetNumberMax;           // Maximum number of medium-b-jets allowed

  Double_t _bLooseCut;
  Double_t _bMediumCut;
};


#endif







