/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      12 Dec 2017 - Created by B. Li.
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/ttHVars.hpp"

#include <iostream>

//Test out a couple of variables, one Int_t and one float I guess
ttHVars::ttHVars(bool makeHistos){

  SetName("ttHVars");
  
  _floatVars["massL"] = -999.;
  _floatVars["massL_SFOS"] = -999.;
  _floatVars["mass_diele"] = -999.;
  
  _floatVars["metLD"] = -999.;
  _floatVars["mht"] = -999.;
  _floatVars["mhtT"] = -999.;
  _floatVars["mht_met"] = -999.;
  _floatVars["mhtT_met"] = -999.;
 

  SetDoHists(makeHistos);

}

void ttHVars::Clear(){
    looseLeptons.clear();
    fakeLeptons.clear();
    tightLeptons.clear();
    Taus.clear();
    Jets.clear();
}

void ttHVars::FillBranches(EventContainer * evtObj){

    //Initialise vectors;
    Clear();
  
    std::vector<Lepton> looseLeptons;
    std::vector<Lepton> fakeLeptons;
    std::vector<Lepton> tightLeptons;
    std::vector<Tau> Taus;
    std::vector<Jet> Jets;
    
    looseLeptons.assign(evtObj -> looseLeptons.begin(), evtObj -> looseLeptons.end());
    fakeLeptons.assign(evtObj -> fakeLeptons.begin(), evtObj -> fakeLeptons.end());
    tightLeptons.assign(evtObj -> tightLeptons.begin(), evtObj -> tightLeptons.end());
    
    Taus.assign(evtObj -> looseTaus.begin(), evtObj -> looseTaus.end());
    Jets.assign(evtObj -> jets.begin(), evtObj -> jets.end());
    
    // Fill the variables in event container for ttH cuts

    // Fill the branches
    _floatVars["massL"] = evtObj->massL;
    _floatVars["massL_SFOS"] = evtObj->massL_SFOS;
    _floatVars["mass_diele"] = evtObj->mass_diele;
  
    _floatVars["metLD"] = evtObj->metLD;
    _floatVars["mht"] = evtObj->mht;
    _floatVars["mhtT"] = evtObj->mhtT;
    _floatVars["mht_met"] = evtObj->mht_met;
    _floatVars["mhtT_met"] = evtObj->mhtT_met;
     
  
    if(evtObj -> _sync == 52){     
        std::cout << "Synchronization in ttHVars.cpp " << std::endl;                                                              
    }                          

    if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

