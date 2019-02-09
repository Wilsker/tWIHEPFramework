/******************************************************************************
 * testVar.cpp                                                                *
 *
 * Testing out some variables being added to the skim tree.
 *
 * History
 *      10th Nov 2016 - Created by D. Leggat. Just a test, so probably not that important
 ******************************************************************************/

#include "SingleTopRootAnalysis/Vars/HmassVars.hpp"

#include <iostream>


//Test out a couple of variables, one Int_t and one float I guess
HmassVars::HmassVars(bool makeHistos){

  SetName("HmassVars");
  
  _floatVars["gen_lvTop_px"] = 999.;
  _floatVars["gen_lvTop_py"] = 999.;
  _floatVars["gen_lvTop_pz"] = 999.;
  _floatVars["gen_lvTop_E"] = 999.;
  _floatVars["gen_lvTop_Index"] = 999.;
  _floatVars["gen_lvH_px"] = 999.;
  _floatVars["gen_lvH_py"] = 999.;
  _floatVars["gen_lvH_pz"] = 999.;
  _floatVars["gen_lvH_E"] = 999.;
  _floatVars["gen_lvH_Index"] = 999.;
  _floatVars["gen_miss_px"] = 999.;
  _floatVars["gen_miss_py"] = 999.;
  _floatVars["Met_Fake_px"] = 999.;
  _floatVars["Met_Fake_py"] = 999.;
  _floatVars["Met_missFake_px"] = 999.;
  _floatVars["Met_missFake_py"] = 999.;
  _floatVars["n_leptons_fromH"] = 999.;
  _floatVars["n_leptons_fromTop"] = 999.;
  _floatVars["n_leptons_fromB"] = 999.;
  _floatVars["n_jets_fromH"] = 999.;
  _floatVars["n_jets_fromTop"] = 999.;
  _floatVars["jjl_fromH_lvH_mass"] = 999.;
  _doubleVecs["genWs_fromH_index"] = {-0.5, 1000. }; 
  _doubleVecs["genWs_fromTop_index"] = {-0.5, 1000. }; 
  _doubleVecs["genZs_fromH_index"] = {-0.5, 1000. }; 
  _doubleVecs["genTaus_fromH_index"] = {-0.5, 1000 }; 
  _doubleVecs["genWs_fromH_pt"] = {0, 200. }; 
  _doubleVecs["genWs_fromTop_pt"] = {0, 200. }; 
  _doubleVecs["genZs_fromH_pt"] = {0, 200. }; 
  _doubleVecs["genTaus_fromH_pt"] = {0, 200 }; 
  _doubleVecs["genWs_fromH_eta"] = {-8, 8. }; 
  _doubleVecs["genWs_fromTop_eta"] = {-8, 8. }; 
  _doubleVecs["genZs_fromH_eta"] = {-8, 8. }; 
  _doubleVecs["genTaus_fromH_eta"] = {-8, 8 }; 
  _doubleVecs["genWs_fromH_phi"] = {-4, 4. }; 
  _doubleVecs["genWs_fromTop_phi"] = {-4, 4. }; 
  _doubleVecs["genZs_fromH_phi"] = {-4, 4. }; 
  _doubleVecs["genTaus_fromH_phi"] = {-4, 4 }; 
  _doubleVecs["genWs_fromH_mass"] = {-0, 200. }; 
  _doubleVecs["genWs_fromTop_mass"] = {-0, 200. }; 
  _doubleVecs["genZs_fromH_mass"] = {-0, 200. }; 
  _doubleVecs["genTaus_fromH_mass"] = {-0, 5 }; 
  
  SetDoHists(makeHistos);

}

void HmassVars::Clear(){
    fakeLeptons.clear();
    Jets.clear();
    MCParticles.clear();
    MCNeutrinos.clear();
    genWs_fromH_index.clear();
    genWs_fromTop_index.clear();
    genZs_fromH_index.clear();
    genTaus_fromH_index.clear();
    genWs_fromH_pt.clear();
    genWs_fromTop_pt.clear();
    genZs_fromH_pt.clear();
    genTaus_fromH_pt.clear();
    genWs_fromH_eta.clear();
    genWs_fromTop_eta.clear();
    genZs_fromH_eta.clear();
    genTaus_fromH_eta.clear();
    genWs_fromH_phi.clear();
    genWs_fromTop_phi.clear();
    genZs_fromH_phi.clear();
    genTaus_fromH_phi.clear();
    genWs_fromH_mass.clear();
    genWs_fromTop_mass.clear();
    genZs_fromH_mass.clear();
    genTaus_fromH_mass.clear();
    gen_lvTop_px = -999;
    gen_lvTop_py = -999;
    gen_lvTop_pz = -999;
    gen_lvTop_E = -999;
    gen_lvTop_Index = -999;
    gen_lvH_px = -999;
    gen_lvH_py = -999;
    gen_lvH_pz = -999;
    gen_lvH_E = -999;
    gen_lvH_Index = -999;
    gen_miss_px = -999;
    gen_miss_py = -999;
    Met_Fake_px = -999;
    Met_Fake_py = -999;
    Met_missFake_px = -999;
    Met_missFake_py = -999;
    n_leptons_fromH = -999;
    n_leptons_fromTop = -999;
    n_leptons_fromB = -999;
    n_jets_fromH = -999;
    n_jets_fromTop = -999;
    jjl_fromH_lvH_mass = -999;
}

void HmassVars::FillBranches(EventContainer* evtObj){

  //Initialise vectors;
  Clear();
    
    fakeLeptons.assign(evtObj -> fakeLeptons.begin(), evtObj -> fakeLeptons.end());
    Jets.assign(evtObj -> jets.begin(), evtObj -> jets.end());
    MCParticles.assign(evtObj -> MCParticles.begin(), evtObj -> MCParticles.end());
    MCWs.assign(evtObj -> MCWs.begin(), evtObj -> MCWs.end());
    MCZs.assign(evtObj -> MCZs.begin(), evtObj -> MCZs.end());
    MCTaus.assign(evtObj -> MCTaus.begin(), evtObj -> MCTaus.end());
    MCNeutrinos.assign(evtObj -> MCNeutrinos.begin(), evtObj -> MCNeutrinos.end());
    mcParticlesPtr = &MCParticles;
   
    // prepare h - decay products
    TLorentzVector h1jet={0,0,0,0};
    TLorentzVector h2jet={0,0,0,0};
    TLorentzVector hlep={0,0,0,0};
    TLorentzVector hlv={0,0,0,0};
     
    // loop over jets
    int n_jets_H = 0;
    int n_jets_Top = 0;
    for (auto jet: Jets){
        if(jet.isFromH()==1){
            n_jets_H++;
            if(n_jets_H ==1) h1jet.SetPtEtaPhiE(jet.Pt(),jet.Eta(),jet.Phi(),jet.E());
            if(n_jets_H ==2) h2jet.SetPtEtaPhiE(jet.Pt(),jet.Eta(),jet.Phi(),jet.E());
        }
        if(jet.isFromTop()==1)n_jets_Top++;
    }
    n_jets_fromH = n_jets_H;
    n_jets_fromTop = n_jets_Top;
  
    // loop over leptons
    int n_leps_H = 0;
    int n_leps_Top = 0;
    int n_leps_B = 0;
    int n_lep = 1;
    for (auto lep: fakeLeptons){
        if(n_lep>2)continue;
        if(lep.isFromH()==1){
            n_leps_H++;
            for(auto gen : MCNeutrinos){
                if(gen.motherpdg_id()==gen.PdgId()) continue;
                if(gen.BmotherIndex() == lep.matchMother_Index()){// found the asscociated lv
                    gen_lvH_px = gen.Px();
                    gen_lvH_py = gen.Py();
                    gen_lvH_pz = gen.Pz();
                    gen_lvH_E = gen.E();
                    gen_lvH_Index = gen.Index();
                    hlep.SetPtEtaPhiE(lep.Pt(),lep.Eta(),lep.Phi(),lep.E());
                    hlv.SetPtEtaPhiE(gen.Pt(),gen.Eta(),gen.Phi(),gen.E());
                    break;
                }
            }
        }
        if(lep.isFromTop()==1){
            n_leps_Top++;
            for(auto gen : MCNeutrinos){
                if(gen.motherpdg_id()==gen.PdgId()) continue;
                if(gen.BmotherIndex() == lep.matchMother_Index()){// found the asscociated lv
                    gen_lvTop_px = gen.Px();
                    gen_lvTop_py = gen.Py();
                    gen_lvTop_pz = gen.Pz();
                    gen_lvTop_E = gen.E();
                    gen_lvTop_Index = gen.Index();
                    break;
                }
            }
        }
        if(lep.isFromB()==1)n_leps_B++;
        n_lep++;
    }
    n_leptons_fromH = n_leps_H;
    n_leptons_fromTop = n_leps_Top;
    n_leptons_fromB = n_leps_B;
    
    // loop over gen Ws  
    for (auto gen: MCWs){
       if(gen.motherpdg_id()==gen.PdgId()) continue;
       MCParticle genMother = gen.GetGenMotherNoFsr(gen, *mcParticlesPtr);
       MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *mcParticlesPtr);
       MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *mcParticlesPtr);
       if(fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId()) == 25){
          genWs_fromH_index.push_back(gen.Index()); 
          genWs_fromH_pt.push_back(gen.Pt()); 
          genWs_fromH_eta.push_back(gen.Eta()); 
          genWs_fromH_phi.push_back(gen.Phi()); 
          genWs_fromH_mass.push_back(gen.M()); 
       }else if(fabs(genMother.PdgId()) == 6 || fabs(genGMother.PdgId()) == 6 || fabs(genGGMother.PdgId()) == 6){
          genWs_fromTop_index.push_back(gen.Index()); 
          genWs_fromTop_pt.push_back(gen.Pt()); 
          genWs_fromTop_eta.push_back(gen.Eta()); 
          genWs_fromTop_phi.push_back(gen.Phi()); 
          genWs_fromTop_mass.push_back(gen.M()); 
       }
    }
    
    // loop over gen Zs  
    for (auto gen: MCZs){
       if(gen.motherpdg_id()==gen.PdgId()) continue;
       MCParticle genMother = gen.GetGenMotherNoFsr(gen, *mcParticlesPtr);
       MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *mcParticlesPtr);
       MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *mcParticlesPtr);
       if(fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId()) == 25){
          genZs_fromH_index.push_back(gen.Index()); 
          genZs_fromH_pt.push_back(gen.Pt()); 
          genZs_fromH_eta.push_back(gen.Eta()); 
          genZs_fromH_phi.push_back(gen.Phi()); 
          genZs_fromH_mass.push_back(gen.M()); 
       }
    }
    
    // loop over gen Taus  
    for (auto gen: MCTaus){
       if(gen.motherpdg_id()==gen.PdgId()) continue;
       MCParticle genMother = gen.GetGenMotherNoFsr(gen, *mcParticlesPtr);
       MCParticle genGMother = genMother.GetGenMotherNoFsr(genMother, *mcParticlesPtr);
       MCParticle genGGMother = genGMother.GetGenMotherNoFsr(genGMother, *mcParticlesPtr);
       if(fabs(genMother.PdgId()) == 25 || fabs(genGMother.PdgId()) == 25 || fabs(genGGMother.PdgId()) == 25){
          genTaus_fromH_index.push_back(gen.Index()); 
          genTaus_fromH_pt.push_back(gen.Pt()); 
          genTaus_fromH_eta.push_back(gen.Eta()); 
          genTaus_fromH_phi.push_back(gen.Phi()); 
          genTaus_fromH_mass.push_back(gen.M()); 
       }
    }
   
    // calculate miss ETs 
    if(gen_lvTop_E > 0 &&  gen_lvH_E > 0 ){
        // if found 2 lvs, calculate the difference between gen_Met and lv1+lv2
        gen_miss_px =  evtObj->Gen_type1PF_px - gen_lvTop_px - gen_lvH_px ;
        gen_miss_py =  evtObj->Gen_type1PF_py - gen_lvTop_py - gen_lvH_py ;
        Met_missFake_px =  evtObj->missingEx - gen_lvTop_px - gen_lvH_px ;
        Met_missFake_py =  evtObj->missingEy - gen_lvTop_py - gen_lvH_py ;
    }
    // calculate the missing ET due to detector resolutions
    Met_Fake_px = evtObj->missingEx - evtObj->Gen_type1PF_px;
    Met_Fake_py = evtObj->missingEy - evtObj->Gen_type1PF_py;
 
   // calculate jjl_lvH mass when we found 2 hj and 1 hlep:
   if(gen_lvH_E>0  && n_leptons_fromH >=1 && n_jets_fromH>=2 ){
    jjl_fromH_lvH_mass = (h1jet + h2jet + hlep + hlv).M();
   }
  
  _floatVars["gen_lvTop_px"] = gen_lvTop_px;
  _floatVars["gen_lvTop_py"] = gen_lvTop_py;
  _floatVars["gen_lvTop_pz"] = gen_lvTop_pz;
  _floatVars["gen_lvTop_E"] = gen_lvTop_E;
  _floatVars["gen_lvTop_Index"] = gen_lvTop_Index;
  _floatVars["gen_lvH_px"] = gen_lvH_px;
  _floatVars["gen_lvH_py"] = gen_lvH_py;
  _floatVars["gen_lvH_pz"] = gen_lvH_pz;
  _floatVars["gen_lvH_E"] = gen_lvH_E;
  _floatVars["gen_lvH_Index"] = gen_lvH_Index;
  _floatVars["gen_miss_px"] = gen_miss_px;
  _floatVars["gen_miss_py"] = gen_miss_py;
  _floatVars["Met_Fake_px"] = Met_Fake_px;
  _floatVars["Met_Fake_py"] = Met_Fake_py;
  _floatVars["Met_missFake_px"] = Met_missFake_px;
  _floatVars["Met_missFake_py"] = Met_missFake_py;
  _floatVars["n_leptons_fromH"] = n_leptons_fromH;
  _floatVars["n_leptons_fromTop"] = n_leptons_fromTop;
  _floatVars["n_leptons_fromB"] = n_leptons_fromB;
  _floatVars["n_jets_fromH"] = n_jets_fromH;
  _floatVars["n_jets_fromTop"] = n_jets_fromTop;
  _floatVars["jjl_fromH_lvH_mass"] = jjl_fromH_lvH_mass;
  _doubleVecs["genWs_fromH_index"] = genWs_fromH_index;
  _doubleVecs["genWs_fromTop_index"] = genWs_fromTop_index;
  _doubleVecs["genZs_fromH_index"] = genZs_fromH_index;
  _doubleVecs["genTaus_fromH_index"] = genTaus_fromH_index;
  _doubleVecs["genWs_fromH_pt"] = genWs_fromH_pt;
  _doubleVecs["genWs_fromTop_pt"] = genWs_fromTop_pt;
  _doubleVecs["genZs_fromH_pt"] = genZs_fromH_pt;
  _doubleVecs["genTaus_fromH_pt"] = genTaus_fromH_pt;
  _doubleVecs["genWs_fromH_eta"] = genWs_fromH_eta;
  _doubleVecs["genWs_fromTop_eta"] = genWs_fromTop_eta;
  _doubleVecs["genZs_fromH_eta"] = genZs_fromH_eta;
  _doubleVecs["genTaus_fromH_eta"] = genTaus_fromH_eta;
  _doubleVecs["genWs_fromH_phi"] = genWs_fromH_phi;
  _doubleVecs["genWs_fromTop_phi"] = genWs_fromTop_phi;
  _doubleVecs["genZs_fromH_phi"] = genZs_fromH_phi;
  _doubleVecs["genTaus_fromH_phi"] = genTaus_fromH_phi;
  _doubleVecs["genWs_fromH_mass"] = genWs_fromH_mass;
  _doubleVecs["genWs_fromTop_mass"] = genWs_fromTop_mass;
  _doubleVecs["genZs_fromH_mass"] = genZs_fromH_mass;
  _doubleVecs["genTaus_fromH_mass"] = genTaus_fromH_mass;
  
  if (DoHists()) FillHistograms(evtObj->GetEventWeight());

}

