/******************************************************************************
 * ttVModellingVars.hpp
 *                                                                            *
 * Add the variables for ttV modelling studies
 *
 * Author
 *      Joshuha Thomas-Wilsker
 ******************************************************************************/

#ifndef ttVModellingVars_h
#define ttVModellingVars_h

#include "SingleTopRootAnalysis/Base/Dictionary/VarBase.hpp"
#include "SingleTopRootAnalysis/Base/Dictionary/EventContainer.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Tau.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCJet.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCMuon.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCElectron.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCPhoton.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCTau.hpp"
#include "TLorentzVector.h"
#include <TEnv.h>

//#include "TMVA/Reader.h"
#include "TH2F.h"

class ttVModellingVars: public VarBase {

public:
  ttVModellingVars(bool makeHistos = false);

  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);

private:
    void Clear();

    std::vector<MCElectron> genElectrons;
    std::vector<MCMuon> genMuons;
    std::vector<Lepton> genLeptons;
    std::vector<MCJet> genJets;
    std::vector<MCJet> genBJets;
    std::vector<MCTau> genTau;
    std::vector<MCParticle> genParticles;
    long nEvent;
    int ls;
    int run;
    int n_presel_mu;
    int n_gen_ele;
    int n_gen_mu;
    int n_gen_lepton;
    int n_gen_jets;
    int n_gen_bjets;
    int n_gen_tau;
    double gen_lepton1_pt;
    double gen_lepton2_pt;
    double gen_jet1_pt;
    double gen_jet2_pt;
    double gen_jet3_pt;
    double gen_jet4_pt;
    double gen_jet5_pt;
    double gen_jet6_pt;
    double gen_bjet1_pt;
    double gen_bjet2_pt;
    double MinDeltaR_MCGenLeps;
    double MinDeltaR_MCGenLep1Jet;
    double MinDeltaR_MCGenLep2Jet;
    double MCGen_MET;
    double MCGen_HTall;
    double MCGen_HThad;
    float genWeight_muF2;
    float genWeight_muF0p5;
    float genWeight_muR2;
    float genWeight_muR0p5;
    Int_t SourceNumber;
    Int_t count_leps_from_bmeson;
    Int_t count_leps_from_bmeson_gt005;


};

#endif
