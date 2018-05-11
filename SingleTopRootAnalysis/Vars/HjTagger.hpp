/******************************************************************************
 * HjTagger.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      12 Dec 2017 - Created by B. Li
 ******************************************************************************/

#ifndef HjTagger_h
#define HjTagger_h

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
#include "TLorentzVector.h"
#include <TEnv.h>

#include "TMVA/Reader.h"
#include "TH2F.h"

class HjTagger: public VarBase {
  
public:
  HjTagger(bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();
    
    //utils
    std::tuple<Float_t,Float_t,Float_t,Float_t>getRelKinAndGeo(TLorentzVector currJet, TLorentzVector currPart);

    std::vector<Lepton> fakeLeptons;
    std::vector<Jet> Jets;
    
    std::vector<double> FakeLep_isFromB;
    std::vector<double> FakeLep_isFromC;
    std::vector<double> FakeLep_isFromH;
    std::vector<double> FakeLep_isFromTop;
    std::vector<double> FakeLep_matchId;
    std::vector<double> FakeLep_PdgId;
    std::vector<double> FakeLep_matchIndex;
    std::vector<double> FakeLep_pt;
    std::vector<double> FakeLep_eta;
    std::vector<double> FakeLep_phi;
    std::vector<double> FakeLep_energy;

    std::vector<double>  Jet25_pfCombinedInclusiveSecondaryVertexV2BJetTags;
    std::vector<double>  Jet25_pfCombinedMVAV2BJetTags;
    std::vector<double>  Jet25_pfJetProbabilityBJetTags;
    std::vector<double>  Jet25_pfDeepCSVCvsLJetTags;
    std::vector<double>  Jet25_pfDeepCSVCvsBJetTags;
    std::vector<double> Jet25_bDiscriminator;
    std::vector<double> Jet25_pfCombinedCvsLJetTags;
    std::vector<double> Jet25_pfCombinedCvsBJetTags;
    std::vector<double> Jet25_qg;
    std::vector<double> Jet25_axis2;
    std::vector<double> Jet25_ptD;
    std::vector<double> Jet25_mult;
    std::vector<double> Jet25_pt;
    std::vector<double> Jet25_eta;
    std::vector<double> Jet25_phi;
    std::vector<double> Jet25_energy;
    std::vector<double> Jet25_px;
    std::vector<double> Jet25_py;
    std::vector<double> Jet25_pz;
    std::vector<double> Jet25_mass;
    std::vector<double> Jet25_isFromH;
    std::vector<double> Jet25_isFromTop;
    std::vector<double> Jet25_matchId;
    std::vector<double> Jet25_neutralHadEnergyFraction;
    std::vector<double> Jet25_chargedHadronEnergyFraction;
    std::vector<double> Jet25_chargedEmEnergyFraction;
    std::vector<double> Jet25_muonEnergyFraction;
    std::vector<double> Jet25_electronEnergy;
    std::vector<double> Jet25_photonEnergy;
    std::vector<double> Jet25_numberOfConstituents;
    std::vector<double> Jet25_chargedMultiplicity;
    std::vector<double> Jet25_metptratio;
    std::vector<double> Jet25_dilepmetptratio;
    std::vector<double> Jet25_nonjdr;
    std::vector<double> Jet25_nonjdilepdr;
    std::vector<double> Jet25_lepdrmin;
    std::vector<double> Jet25_lepdrmax;
    std::vector<double> Jet25_dilepdr;
    std::vector<double> Jet25_bjdr;
    std::vector<double> Jet25_nonjdeta;
    std::vector<double> Jet25_nonjdilepdeta;
    std::vector<double> Jet25_lepdetamin;
    std::vector<double> Jet25_lepdetamax;
    std::vector<double> Jet25_dilepdeta;
    std::vector<double> Jet25_bjdeta;
    std::vector<double> Jet25_nonjdphi;
    std::vector<double> Jet25_nonjdilepdphi;
    std::vector<double> Jet25_lepdphimin;
    std::vector<double> Jet25_lepdphimax;
    std::vector<double> Jet25_dilepdphi;
    std::vector<double> Jet25_bjdphi;
    std::vector<double> Jet25_nonjptratio;
    std::vector<double> Jet25_nonjdilepptratio;
    std::vector<double> Jet25_lepptratiomin;
    std::vector<double> Jet25_lepptratiomax;
    std::vector<double> Jet25_dilepptratio;
    std::vector<double> Jet25_bjptratio;

};

#endif
