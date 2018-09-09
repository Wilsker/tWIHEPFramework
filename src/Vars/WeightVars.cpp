/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/WeightVars.hpp"

#include <iostream>

//Test out a couple of variables, one int and one float I guess
WeightVars::WeightVars(){
  _floatVars["EventWeight"] = 0.;
  _floatVars["bWeight"] = 0.;
  _floatVars["puWeight"] = 0.;
  _floatVars["lepSF"] = 0.;
  _floatVars["elelooseSF"] = 0.;
  _floatVars["eletightSF"] = 0.;
  _floatVars["mulooseSF"] = 0.;
  _floatVars["mutightSF"] = 0.;
  _floatVars["ChargeMis"] = 0.;
  _floatVars["FakeRate"] = 0.;
  _floatVars["TriggerSF"] = 0.;
  _floatVars["LHEWeight"] = 0.;

  _bTagSystNames = {"central","up_jes","down_jes","up_lf","down_lf","up_hfstats1","down_hfstats1","up_hfstats2","down_hfstats2","up_cferr1","down_cferr1","up_cferr2","down_cferr2","up_hf","down_hf","up_lfstats1","down_lfstats1","up_lfstats2","down_lfstats2" };
  _frReWeightNames = {"central","pt1","pt2","up","down","be1","be2","QCD","TT"};

  //Systematic variations
  for (auto const bSystName: _bTagSystNames) _floatVars["bWeight_"+bSystName] = 0.;
  for (auto const frReWeightName: _frReWeightNames) _floatVars["FakeRate_m_"+frReWeightName] = 0.;
  for (auto const frReWeightName: _frReWeightNames) _floatVars["FakeRate_e_"+frReWeightName] = 0.;
  _floatVars["puWeight_SysUp"] = 0.;
  _floatVars["puWeight_SysDown"] = 0.;
  _floatVars["lepSF_SysUp"] = 0.;
  _floatVars["lepSF_SysDown"] = 0.;
  _floatVars["elelooseSF_SysUp"] = 0.;
  _floatVars["elelooseSF_SysDown"] = 0.;
  _floatVars["mulooseSF_SysUp"] = 0.;
  _floatVars["mulooseSF_SysDown"] = 0.;
  _floatVars["eletightSF_SysUp"] = 0.;
  _floatVars["eletightSF_SysDown"] = 0.;
  _floatVars["mutightSF_SysUp"] = 0.;
  _floatVars["mutightSF_SysDown"] = 0.;
  _floatVars["ChargeMis_SysUp"] = 0.;
  _floatVars["ChargeMis_SysDown"] = 0.;
  _floatVars["TriggerSF_SysUp"] = 0.;
  _floatVars["TriggerSF_SysDown"] = 0.;
  
  _floatVars["FR_weight"] = 0.;
  _floatVars["triggerSF_weight"] = 0.;
  _floatVars["leptonSF_weight"] = 0.;
  _floatVars["bTagSF_weight"] = 0.;
  _floatVars["PU_weight"] = 0.;
  _floatVars["MC_weight"] = 0.;
  
}

void WeightVars::FillBranches(EventContainer * evtObj){

  //Fill the nominal event weight variables
  _floatVars["EventWeight"] = evtObj->GetOutputEventWeight();
  _floatVars["bWeight"] = evtObj->GetEventbTagReshape();
  _floatVars["puWeight"] = evtObj->GetEventPileupWeight();
  _floatVars["lepSF"] = evtObj->GetEventLepSFWeight();
  _floatVars["elelooseSF"] = evtObj->GetEventelelooseSFWeight();
  _floatVars["eletightSF"] = evtObj->GetEventeletightSFWeight();
  _floatVars["mulooseSF"] = evtObj->GetEventmulooseSFWeight();
  _floatVars["mutightSF"] = evtObj->GetEventmutightSFWeight();
  _floatVars["ChargeMis"] = evtObj->GetEventChargeMisWeight();
  _floatVars["FakeRate"] = evtObj->GetEventFakeRateWeight();
  _floatVars["TriggerSF"] = evtObj->GetEventTriggerWeight();
  _floatVars["LHEWeight"] = evtObj->GetEventTriggerWeight();

  _floatVars["MC_weight"] = evtObj->GetGlobalEventWeight();
  _floatVars["bTagSF_weight"] = evtObj->GetEventbTagReshape();
  _floatVars["PU_weight"] = evtObj->GetEventPileupWeight();
  _floatVars["leptonSF_weight"] = evtObj->GetEventLepSFWeight();
  _floatVars["FR_weight"] = evtObj->GetEventFakeRateWeight();
  _floatVars["triggerSF_weight"] = evtObj->GetEventTriggerWeight();
/*
  _floatVars["FR_weight"] = -9999.;
  _floatVars["triggerSF_weight"] = -9999.;
  _floatVars["leptonSF_weight"] = -9999.;
  _floatVars["bTagSF_weight"] = -9999.;
  _floatVars["PU_weight"] = -9999.;
  _floatVars["MC_weight"] = -9999.;
  */

  //Get the systematic variations
  _floatVars["lepSF_SysUp"] = evtObj->GetEventLepSFWeightUp();
  _floatVars["lepSF_SysDown"] = evtObj->GetEventLepSFWeightDown();
  _floatVars["elelooseSF_SysUp"] = evtObj->GetEventelelooseSFWeightUp();
  _floatVars["elelooseSF_SysDown"] = evtObj->GetEventelelooseSFWeightDown();
  _floatVars["eletightSF_SysUp"] = evtObj->GetEventeletightSFWeightUp();
  _floatVars["eletightSF_SysDown"] = evtObj->GetEventeletightSFWeightDown();
  _floatVars["mulooseSF_SysUp"] = evtObj->GetEventmulooseSFWeightUp();
  _floatVars["mulooseSF_SysDown"] = evtObj->GetEventmulooseSFWeightDown();
  _floatVars["mutightSF_SysUp"] = evtObj->GetEventmutightSFWeightUp();
  _floatVars["mutightSF_SysDown"] = evtObj->GetEventmutightSFWeightDown();
  _floatVars["ChargeMis_SysUp"] = evtObj->GetEventChargeMisWeightUp();
  _floatVars["ChargeMis_SysDown"] = evtObj->GetEventChargeMisWeightDown();
  _floatVars["TriggerSF_SysUp"] = evtObj->GetEventTriggerWeightUp();
  _floatVars["TriggerSF_SysDown"] = evtObj->GetEventTriggerWeightDown();
  
  //Pileup variations
  _floatVars["puWeight_SysUp"] = evtObj->GetEventPileupMinBiasUpWeight();
  _floatVars["puWeight_SysDown"] = evtObj->GetEventPileupMinBiasDownWeight();

  for (auto const bSystName: _bTagSystNames) _floatVars["bWeight_"+bSystName] = evtObj->GetEventbTagReshape(bSystName);
  for (auto const frReWeightName: _frReWeightNames) _floatVars["FakeRate_m_"+frReWeightName] = evtObj->GetEventmfrReweight(frReWeightName);
  for (auto const frReWeightName: _frReWeightNames) _floatVars["FakeRate_e_"+frReWeightName] = evtObj->GetEventefrReweight(frReWeightName);

}
