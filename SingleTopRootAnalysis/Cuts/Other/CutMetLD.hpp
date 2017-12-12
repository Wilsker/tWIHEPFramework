/******************************************************************************
 * CutMetLD.hpp                                                               *
 *                                                                            *
 * Cuts on MetLD                                                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutMetLD class                                  *
 *    CutMetLD()                    -- Parameterized Constructor              *
 *    ~CutMetLD()                   -- Destructor                             *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutMetLD"                 *
 *                                                                            *
 * Private Data Members of CutMetLD                                           *
 *    myTH1F* _hMetLDBefore         -- Hist of MetLD before cuts              *
 *    myTH1F* _hMetLDAfter          -- Hist of MetLD after cuts               *
 *    Double_t _MetLDMin;              -- Minimum MetLD window                *
 *    Double_t _MetLDMin;              -- Minimum MetLD window                *
 *                                                                            *
 * History                                                                    *
 *      03 Dec 2010 - Created by H. Zhang                                     *
 *****************************************************************************/

#ifndef CutMetLD_h
#define CutMetLD_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutMetLD : public HistoCut 
{

public:

  // Parameterized Constructor
  CutMetLD(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutMetLD();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutMetLD"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hMetLDBefore;    // Histogram MetLD
  myTH1F* _hMetLDAfter;     // Histogram MetLD

  // Cut parameters
  Double_t _MetLDMin;           // Minimum MetLD
  Double_t _MetLDMax;           // Maximum MetLD

};


#endif







