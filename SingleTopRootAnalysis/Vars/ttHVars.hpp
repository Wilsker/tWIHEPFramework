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
    Int_t Jet_numbMedium;
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
  bool mu1_mediumID;
  bool mu1_isfakeablesel;
  bool mu1_ismvasel;
  bool mu2_mediumID;
  bool mu2_isfakeablesel;
  bool mu2_ismvasel;
  bool ele1_isfakeablesel;
  bool ele1_ismvasel;
  bool ele1_isChargeConsistent;
  bool ele1_passesConversionVeto;
  bool ele2_isfakeablesel;
  bool ele2_ismvasel;
  bool ele2_isChargeConsistent;
  bool ele2_passesConversionVeto;
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
  int mu1_charge;
  int mu1_jetNDauChargedMVASel;
  int mu2_charge;
  int mu2_jetNDauChargedMVASel;
  int ele1_charge;
  int ele1_jetNDauChargedMVASel;
  int ele1_nMissingHits;
  int ele2_charge;
  int ele2_jetNDauChargedMVASel;
  int ele2_nMissingHits;
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
  int tau2_charge;
  int tau2_decayModeFindingOldDMs;
  int tau2_decayModeFindingNewDMs;
  int tau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  int tau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  int tau2_byTightCombinedIsolationDeltaBetaCorr3Hits;
  int tau2_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau2_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau2_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  int tau2_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  int tau2_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  int tau2_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int tau2_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
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
  float mu2_pt;
  float mu2_conept;
  float mu2_eta;
  float mu2_phi;
  float mu2_E;
  float mu2_miniRelIso;
  float mu2_miniIsoCharged;
  float mu2_miniIsoNeutral;
  float mu2_jetPtRel;
  float mu2_jetPtRatio;
  float mu2_jetCSV;
  float mu2_sip3D;
  float mu2_dxyAbs;
  float mu2_dz;
  float mu2_segmentCompatibility;
  float mu2_leptonMVA;
  float mu2_dpt_div_pt;
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
  float ele2_pt;
  float ele2_conept;
  float ele2_eta;
  float ele2_phi;
  float ele2_E;
  float ele2_miniRelIso;
  float ele2_miniIsoCharged;
  float ele2_miniIsoNeutral;
  float ele2_jetPtRel;
  float ele2_jetPtRatio;
  float ele2_jetCSV;
  float ele2_sip3D;
  float ele2_dxyAbs;
  float ele2_dz;
  float ele2_ntMVAeleID;
  float ele2_leptonMVA;
  float tau1_pt;
  float tau1_eta;
  float tau1_phi;
  float tau1_E;
  float tau1_dxy;
  float tau1_dz;
  float tau1_byCombinedIsolationDeltaBetaCorr3Hits;
  float tau2_pt;
  float tau2_eta;
  float tau2_phi;
  float tau2_E;
  float tau2_dxy;
  float tau2_dz;
  float tau2_byCombinedIsolationDeltaBetaCorr3Hits;
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
  float jet4_pt;
  float jet4_eta;
  float jet4_phi;
  float jet4_E;
  float jet4_CSV;
  float PFMET;
  float PFMETphi;
  float MHT;
  float metLD;
  float lep1_conePt;
  float lep2_conePt;
  float mindr_lep1_jet;
  float mindr_lep2_jet;
  float mT_lep1;
  float avg_dr_jet;
  float mvaOutput_2lss_ttV;
  float mvaOutput_2lss_ttbar;
  float lep3_conePt;
  float mindr_lep3_jet;
  float min_dr_lep_jet;
  float dr_leps;
  float max_lep_eta;
  float mT_lep2;
  float mbb;
  float mbb_loose;
  float Hj_tagger;
  float HTT;
  int nBJetLoose;
  int nBJetMedium;

};

#endif
