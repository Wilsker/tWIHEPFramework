/******************************************************************************
 * CutMassL.hpp                                                               *
 *                                                                            *
 * Cuts on MassL                                                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of CutMassL class                                  *
 *    CutMassL()                    -- Parameterized Constructor              *
 *    ~CutMassL()                   -- Destructor                             *
 *    BookHistogram()                   -- Book histograms                    *
 *    Apply()                           -- Apply cuts and fill histograms     *
 *    GetCutName()                      -- Returns "CutMassL"                 *
 *                                                                            *
 * Private Data Members of CutMassL                                           *
 *    myTH1F* _hMassLBefore         -- Hist of MassL before cuts              *
 *    myTH1F* _hMassLAfter          -- Hist of MassL after cuts               *
 *    Double_t _MassLMin;              -- Minimum MassL window                *
 *    Double_t _MassLMin;              -- Minimum MassL window                *
 *                                                                            *
 * History                                                                    *
 *      03 Dec 2010 - Created by H. Zhang                                     *
 *****************************************************************************/

#ifndef CutMassL_h
#define CutMassL_h

#include "SingleTopRootAnalysis/Base/Dictionary/HistoCut.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"


class CutMassL : public HistoCut 
{

public:

  // Parameterized Constructor
  CutMassL(EventContainer *EventContainerObj);
  
  // Destructor
  ~CutMassL();

  // Get the name of describing the cut
  inline std::string GetCutName() { return "CutMassL"; };

  // Book Histograms
  void BookHistogram();

  // Apply cut and fill histogram
  Bool_t Apply();


private:

  // Histograms
  myTH1F* _hMassLBefore;    // Histogram MassL
  myTH1F* _hMassLAfter;     // Histogram MassL

  // Cut parameters
  Double_t _MassLMin;           // Minimum MassL
  Double_t _MassLMax;           // Maximum MassL

};


#endif







