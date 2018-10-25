/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/TestVar.hpp"

#include <iostream>

//Test out a couple of variables, one int and one float I guess
TestVar::TestVar(){
  _floatVars["SourceNumber"] = 0.;
  _doubleVecs["Flag_cuts"] = {-0.1, 1.9 }; 
}

void TestVar::FillBranches(EventContainer * evtObj){
  _floatVars["SourceNumber"] = evtObj->GetSourceNumber();
  _doubleVecs["Flag_cuts"] = evtObj->Flag_cuts;
}
