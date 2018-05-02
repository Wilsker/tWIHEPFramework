/******************************************************************************
 * CutMetFilter.hpp                                                               *
 *                                                                            *
 * Cuts on MetFilter                                                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutMetFilter class                                  *
 *    CutMetFilter()                    -- Parameterized Constructor              *
 *    ~CutMetFilter()                   -- Destructor                             *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutMetFilter"                 *
 *                                                                            *
 * Private Data Members of CutMetFilter                                           *
 *    myTH1F* _hMetFilterBefore         -- Hist of MetFilter before cuts              *
 *    myTH1F* _hMetFilterAfter          -- Hist of MetFilter after cuts               *
 *    Double_t _MetFilterMin;              -- Minimum MetFilter window                *
 *    Double_t _MetFilterMin;              -- Minimum MetFilter window                *
 *                                                                            *
 * History                                                                    *
 *      03 Dec 2010 - Created by H. Zhang                                     *
 *****************************************************************************/

#ifndef CutMetFilter_h
#define CutMetFilter_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutMetFilter : public HistoCut 
{

public:

  // Parameterized Constructor
  CutMetFilter(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutMetFilter();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutMetFilter"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hMetFilterBefore;    // Histogram MetFilter
  myTH1F* _hMetFilterAfter;     // Histogram MetFilter


};


#endif







