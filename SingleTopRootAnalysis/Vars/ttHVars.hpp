/******************************************************************************
 * ttHVars.hpp                                                                *
 *                                                                            *
 * Add the variables we will use in the BDT to the skim tree                  *
 * 
 * History
 *      12 Dec 2017 - Created by B. Li
 ******************************************************************************/

#ifndef ttHVars_h
#define ttHVars_h

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

class ttHVars: public VarBase {
  
public:
  ttHVars(bool makeHistos = false);
  
  //void BookBranches(TTree * skimTree);
  void FillBranches(EventContainer * evtObj);
  
private:
    void Clear();

    void Cal_event_variables(EventContainer* EvtObj);
    double getMTlepmet(double phi1, double phi2, double pt1, double pt2);
    double get_Dilep_ttbarMVA(EventContainer* EvtObj);
    double get_Dilep_ttvMVA(EventContainer* EvtObj);
    
    //utils
    double deltaPhi(double phi1, double phi2);

    //2D BDT binning 
    Int_t get_2DBDTBin(double BDT_ttbar, double BDT_ttV, EventContainer* EvtObj);

    std::vector<Lepton> looseLeptons;
    std::vector<Lepton> fakeLeptons;
    std::vector<Lepton> tightLeptons;
    std::vector<Lepton> looseMuons;
    std::vector<Lepton> looseElectrons;
    std::vector<Jet> Jets;
    std::vector<Tau> Taus;
    
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

    std::vector<double> Jet25_isFromH;
    std::vector<double> Jet25_isFromTop;
    std::vector<double> Jet25_matchId;
    std::vector<double> Jet25_matchIndex;
    std::vector<double> Jet25_pt;
    std::vector<double> Jet25_eta;
    std::vector<double> Jet25_phi;
    std::vector<double> Jet25_energy;

    Int_t Jet_numbLoose;
    Int_t Jet_numLoose;
    Double_t ttbarBDT_2lss;
    Double_t ttvBDT_2lss;
    Int_t Bin2l;
    Double_t leadLep_jetdr;
    Double_t leadLep_corrpt;
    Double_t leadLep_jetcsv;
    Double_t leadLep_BDT;
    Double_t secondLep_jetdr;
    Double_t secondLep_corrpt;
    Double_t secondLep_jetcsv;
    Double_t secondLep_BDT;
    Double_t maxeta;
    Double_t Mt_metleadlep;
    Double_t SubCat2l;
    Double_t massll;
    Double_t Sum2lCharge;
    Double_t Dilep_bestMVA;
    Double_t Dilep_worseMVA;
    Double_t Dilep_pdgId;
    Double_t Dilep_htllv;
    Double_t Dilep_mtWmin;
    Double_t Dilep_nTight;
    Double_t leadJetCSV;
    Double_t secondJetCSV;
    Double_t thirdJetCSV;
    Double_t fourthJetCSV;
    Double_t HighestJetCSV;
    Double_t HtJet;
    Double_t nLepFO;
    Double_t nLepTight;
    Double_t minMllAFAS;
    Double_t minMllAFOS;
    Double_t minMllSFOS;
    Double_t Hj1_BDT;
    Double_t leadLep_isMatchRightCharge;
    Double_t leadLep_mcMatchId;
    Double_t leadLep_isFromTop;
    Double_t leadLep_isFromH;
    Double_t leadLep_isFromB;
    Double_t leadLep_isFromC;
    Double_t leadLep_mcPromptGamma;
    Double_t leadLep_mcPromptFS;
    Double_t secondLep_isMatchRightCharge;
    Double_t secondLep_mcMatchId;
    Double_t secondLep_isFromTop;
    Double_t secondLep_isFromH;
    Double_t secondLep_isFromB;
    Double_t secondLep_isFromC;
    Double_t secondLep_mcPromptGamma;
    Double_t secondLep_mcPromptFS;

  long nEvent;
  bool mu0_mediumID;
  bool mu0_isfakeablesel;
  bool mu0_ismvasel;
  bool mu1_mediumID;
  bool mu1_isfakeablesel;
  bool mu1_ismvasel;
  bool ele0_isfakeablesel;
  bool ele0_ismvasel;
  bool ele0_isChargeConsistent;
  bool ele0_passesConversionVeto;
  bool ele1_isfakeablesel;
  bool ele1_ismvasel;
  bool ele1_isChargeConsistent;
  bool ele1_passesConversionVeto;
  int ls;
  int run;
  int n_presel_mu;
  int n_fakeablesel_mu;
  int n_mvasel_mu;
  int n_presel_ele;
  int n_fakeablesel_ele;
  int n_mvasel_ele;
  int n_presel_tau;
  int n_presel_jet;
  int mu0_charge;
  int mu0_jetNDauChargedMVASel;
  int mu1_charge;
  int mu1_jetNDauChargedMVASel;
  int ele0_charge;
  int ele0_jetNDauChargedMVASel;
  int ele0_nMissingHits;
  int ele1_charge;
  int ele1_jetNDauChargedMVASel;
  int ele1_nMissingHits;
  int tau0_charge;
  int tau0_decayModeFindingOldDMs;
  int tau0_decayModeFindingNewDMs;
  int tau0_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int tau0_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int tau0_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int tau0_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau0_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau0_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau0_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int tau0_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int tau0_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int tau0_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  int tau1_charge;
  int tau1_decayModeFindingOldDMs;
  int tau1_decayModeFindingNewDMs;
  int tau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int tau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int tau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int tau1_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau1_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau1_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau1_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int tau1_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int tau1_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int tau1_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  float mu0_pt;
  float mu0_conept;
  float mu0_eta;
  float mu0_phi;
  float mu0_E;
  float mu0_miniRelIso;
  float mu0_miniIsoCharged;
  float mu0_miniIsoNeutral;
  float mu0_jetPtRel;
  float mu0_jetPtRatio;
  float mu0_jetCSV;
  float mu0_sip3D;
  float mu0_dxyAbs;
  float mu0_dz;
  float mu0_segmentCompatibility;
  float mu0_leptonMVA;
  float mu0_dpt_div_pt;
  float mu1_pt;
  float mu1_conept;
  float mu1_eta;
  float mu1_phi;
  float mu1_E;
  float mu1_miniRelIso;
  float mu1_miniIsoCharged;
  float mu1_miniIsoNeutral;
  float mu1_jetPtRel;
  float mu1_jetPtRatio;
  float mu1_jetCSV;
  float mu1_sip3D;
  float mu1_dxyAbs;
  float mu1_dz;
  float mu1_segmentCompatibility;
  float mu1_leptonMVA;
  float mu1_dpt_div_pt;
  float ele0_pt;
  float ele0_conept;
  float ele0_eta;
  float ele0_phi;
  float ele0_E;
  float ele0_miniRelIso;
  float ele0_miniIsoCharged;
  float ele0_miniIsoNeutral;
  float ele0_jetPtRel;
  float ele0_jetPtRatio;
  float ele0_jetCSV;
  float ele0_sip3D;
  float ele0_dxyAbs;
  float ele0_dz;
  float ele0_ntMVAeleID;
  float ele0_leptonMVA;
  float ele1_pt;
  float ele1_conept;
  float ele1_eta;
  float ele1_phi;
  float ele1_E;
  float ele1_miniRelIso;
  float ele1_miniIsoCharged;
  float ele1_miniIsoNeutral;
  float ele1_jetPtRel;
  float ele1_jetPtRatio;
  float ele1_jetCSV;
  float ele1_sip3D;
  float ele1_dxyAbs;
  float ele1_dz;
  float ele1_ntMVAeleID;
  float ele1_leptonMVA;
  float tau0_pt;
  float tau0_eta;
  float tau0_phi;
  float tau0_E;
  float tau0_dxy;
  float tau0_dz;
  float tau0_byCombinedIsolationDeltaBetaCorr3Hits;
  float tau1_pt;
  float tau1_eta;
  float tau1_phi;
  float tau1_E;
  float tau1_dxy;
  float tau1_dz;
  float tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  float jet0_pt;
  float jet0_eta;
  float jet0_phi;
  float jet0_E;
  float jet0_CSV;
  float jet1_pt;
  float jet1_eta;
  float jet1_phi;
  float jet1_E;
  float jet1_CSV;
  float jet2_pt;
  float jet2_eta;
  float jet2_phi;
  float jet2_E;
  float jet2_CSV;
  float jet3_pt;
  float jet3_eta;
  float jet3_phi;
  float jet3_E;
  float jet3_CSV;
  float PFMET;
  float PFMETphi;
  float MHT;
  float metLD;
  float lep0_conept;
  float lep1_conept;
  float mindr_lep0_jet;
  float mindr_lep1_jet;
  float MT_met_lep0;
  float avg_dr_jet;
  float MVA_2lss_ttV;
  float MVA_2lss_ttbar;

};

#endif
