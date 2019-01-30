/******************************************************************************
 * HmassVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the Hmass study to the skim tree                  *
 * 
 * History
 *      25 Jan 2019 - Created by D. Leggat
 ******************************************************************************/

#ifndef HmassVars_h
#define HmassVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp" 
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCNeutrino.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCW.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCZ.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCTau.hpp"
#include "TLorentzVector.h"
#include <TEnv.h>

class HmassVars: public VarBase {
  
public:
  HmassVars( bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
    
    std::vector<Lepton> fakeLeptons;
    std::vector<Jet> Jets;
    std::vector<MCParticle> MCParticles;
    std::vector<MCNeutrino> MCNeutrinos;
    std::vector<MCW> MCWs;                  // MC Zs
    std::vector<MCZ> MCZs;                  // MC Zs
    std::vector<MCTau> MCTaus;              // MC Taus
    std::vector<MCParticle> * mcParticlesPtr;

    float gen_lvTop_px;
    float gen_lvTop_py;
    float gen_lvTop_pz;
    float gen_lvTop_E;
    float gen_lvTop_Index;
    float gen_lvH_px;
    float gen_lvH_py;
    float gen_lvH_pz;
    float gen_lvH_E;
    float gen_lvH_Index;
    float gen_miss_px;
    float gen_miss_py;
    float Met_Fake_px;
    float Met_Fake_py;
    float Met_missFake_px;
    float Met_missFake_py;
    float n_leptons_fromH;
    float n_leptons_fromTop;
    float n_leptons_fromB;
    float n_jets_fromH;
    float n_jets_fromTop;
    float jjl_fromH_lvH_mass;
    std::vector<double> genWs_fromH_index;
    std::vector<double> genWs_fromTop_index;
    std::vector<double> genZs_fromH_index;
    std::vector<double> genTaus_fromH_index;
    std::vector<double> genWs_fromH_pt;
    std::vector<double> genWs_fromTop_pt;
    std::vector<double> genZs_fromH_pt;
    std::vector<double> genTaus_fromH_pt;
    std::vector<double> genWs_fromH_eta;
    std::vector<double> genWs_fromTop_eta;
    std::vector<double> genZs_fromH_eta;
    std::vector<double> genTaus_fromH_eta;
    std::vector<double> genWs_fromH_phi;
    std::vector<double> genWs_fromTop_phi;
    std::vector<double> genZs_fromH_phi;
    std::vector<double> genTaus_fromH_phi;
    std::vector<double> genWs_fromH_mass;
    std::vector<double> genWs_fromTop_mass;
    std::vector<double> genZs_fromH_mass;
    std::vector<double> genTaus_fromH_mass;

        
};

#endif
