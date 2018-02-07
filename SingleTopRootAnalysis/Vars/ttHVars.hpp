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

};

#endif
