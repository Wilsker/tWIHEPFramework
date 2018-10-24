/******************************************************************************
 * CutEventList.hpp                                                               *
 *                                                                            *
 * Cuts on EventList                                                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutEventList class                                  *
 *    CutEventList()                    -- Parameterized Constructor              *
 *    ~CutEventList()                   -- Destructor                             *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutEventList"                 *
 *                                                                            *
 * Private Data Members of CutEventList                                           *
 *    myTH1F* _hEventListBefore         -- Hist of EventList before cuts              *
 *    myTH1F* _hEventListAfter          -- Hist of EventList after cuts               *
 *    Double_t _EventListMin;              -- Minimum EventList window                *
 *    Double_t _EventListMin;              -- Minimum EventList window                *
 *                                                                            *
 * History                                                                    *
 *      24 Oct 2018 - Created by B.Li                                   *
 *****************************************************************************/

#ifndef CutEventList_h
#define CutEventList_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutEventList : public HistoCut 
{

public:

  // Parameterized Constructor
  CutEventList(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutEventList();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutEventList"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hEventListBefore;    // Histogram EventList
  myTH1F* _hEventListAfter;     // Histogram EventList

  // Cut parameters
  std::vector<Float_t> Runs; 
  std::vector<Float_t> Lumis; 
  std::vector<Long64_t> nEvents; 

};


#endif







