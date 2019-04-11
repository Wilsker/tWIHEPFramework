/******************************************************************************
 * Jet.hpp                                                                    *
 *                                                                            *
 * Store information about final state jets                                   *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Jet class                                       *
 *    Jet()                              -- Default Constructor               *
 *    Jet()                              -- Parameterized Constructor         *
 *    ~Jet()                             -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill jet from event tree          *
 *    FillFastSim                        -- Fill jet from FastSim tree        *
 *    SetEtM0                            -- Set ET for EM layer 0             *
 *    GetEtM0                            -- Set ET for EM layer 0             *
 *    EtEM0                              -- Set ET for EM layer 0             *
 *    ApplyJESCorrection                 -- Shift jet energy by some amount   *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Jet              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Jet class                                          *
 *                                                                            *
 * History                                                                    *
 *      17 June 2015 - Created by Huaqiao ZHANG                               *
 *****************************************************************************/

#ifndef jet_h
#define jet_h

#include "SingleTopRootAnalysis/Particles/Truth/MCJet.hpp"
#include "SingleTopRootAnalysis/Particles/Truth/MCTau.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Particle.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Electron.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Muon.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Tau.hpp"
#include "SingleTopRootAnalysis/Trees/EventTree.hpp"
#include "SingleTopRootAnalysis/Trees/FastSimTree.hpp"
//#include "SingleTopRootAnalysis/Base/Dictionary/MultijetJESUncertaintyProvider.hpp"
//#include "SingleTopRootAnalysis/Base/Dictionary/JetEfficiencyEstimator.hpp"
//#include "SingleTopRootAnalysis/Base/Dictionary/JERProvider.hpp"
//
#include <TString.h>

#include "TMVA/Reader.h"

//using namespace Analysis;

class Electron;
class Muon;
class Lepton;
class Tau;

class Jet: public Particle
{
 public:
  // Default Constructor
  Jet();

  // Copy Constructor
  Jet(const Jet& other);

  // Construtor using particle
  Jet(const Particle& other);

  // Destructor
  ~Jet();

  // Set all contents to their defaults
  inline void Clear() { Particle::Clear(); _numberOfConstituents=0; _chargedMultiplicity=0;  _bDiscriminator = -999.0; _pileupId = 0.0; _mass = 0.0; _uncorrPt = 0.0; _neutralHadEnergyFraction=0.0; _neutralEmEmEnergyFraction = 0.0; _chargedHadronEnergyFraction =0.0; _chargedEmEnergyFraction=0.0; _muonEnergyFraction=0.0; _electronEnergy=0.0; _photonEnergy=0.0; _tagged = kFALSE;
 _isNormalJet =0.0;
 _isForwardJet =0.0;
 _isLooseBdisc =0.0;
 _isMediumBdisc =0.0;
 _isTightBdisc =0.0;
 _qg =0.0;
 _axis2 =0.0;
 _axis1 =0.0;
 _ptD =0.0;
 _mult =0.0;
 _ele_number =0;
 _tau_number =0;
 _mu_number =0;
 _pfCombinedCvsLJetTags =0.0;
 _pfCombinedCvsBJetTags =0.0;
 _pfCombinedInclusiveSecondaryVertexV2BJetTags =0.0;
 _pfCombinedMVAV2BJetTags =0.0;
 _pfJetProbabilityBJetTags =0.0;
 _pfDeepCSVCvsLJetTags =0.0;
 _pfDeepCSVCvsBJetTags =0.0;
 _pfDeepCSVBJetTags =0.0;
 _pfDeepFlavourBJetTags =0.0;
 _lepdrmax =0.0;
 _lepdrmin =0.0;
 _HjDisc =0.0;
 _L1corrPt = 0.0;
 _uncorrE = 0.0;
 _partonFlavour =0.0;
 _hadronFlavour =0.0;
 _genMother_pdgId =0.0;
 _genGrandMother_pdgId =0.0;
 _matchId =0.0;
 _isFromTop =0.0;
 _isFromH =0.0;
 _matchMother_Id =0.0;
 _matchGrandMother_Id =0.0;
 _isToptag =0.0;
 _isResToptag =0.0;
 _index =0.0;
}

  void SetCuts(TEnv* config);

  // Fill the jet from an EventTree 
  Bool_t Fill( double myJESCorr, double myJERCorr, int& mu_start_index , int& ele_start_index , int& tau_start_index , std::vector<Lepton>& selectedLeptons, std::vector<Tau>& selectedTaus, EventTree *evtr, Int_t iE, TLorentzVector * met, Bool_t useLepAwareJets=false, Bool_t isSimulation=true,int whichtrig =2);
  //  Bool_t Fill( double myJESCorr, double myJERCorr, std::vector<Electron>& selectedElectrons, EventTree *evtr, Int_t iE);
  // Also fill from FastSim tree:
  Bool_t FillFastSim( std::vector<MCJet>& MCBJets, std::vector<MCJet>& MCCJets, std::vector<MCTau>& MCTaus,  std::vector<Electron>& electrons, FastSimTree *tr,Int_t iE,TEnv *config,const TString& tagName="default", Double_t btagCut = 999, Double_t mistagCut = 999, Double_t eshift = 0 );
 
  inline void SetnumberOfConstituents(Int_t numberOfConstituents){_numberOfConstituents = numberOfConstituents;};
  inline Int_t GetnumberOfConstituents() const {return _numberOfConstituents;};
  inline Int_t numberOfConstituents() const {return _numberOfConstituents;};

  inline void SetchargedMultiplicity(Int_t chargedMultiplicity){_chargedMultiplicity = chargedMultiplicity;};
  inline Int_t GetchargedMultiplicity() const {return _chargedMultiplicity;};
  inline Int_t chargedMultiplicity() const {return _chargedMultiplicity;};

  inline void SetbDiscriminator(Double_t bDiscriminator){_bDiscriminator = bDiscriminator;};
  inline Double_t GetbDiscriminator() const {return _bDiscriminator;};
  inline Double_t bDiscriminator() const {return _bDiscriminator;};

  inline void SetpileupId(Double_t pileupId){_pileupId = pileupId;};
  inline Double_t GetpileupId() const {return _pileupId;};
  inline Double_t pileupId() const {return _pileupId;};

  inline void Setmass(Double_t mass){_mass = mass;};
  inline Double_t Getmass() const {return _mass;};
  inline Double_t mass() const {return _mass;};

  inline void SetneutralHadEnergyFraction(Double_t neutralHadEnergyFraction){_neutralHadEnergyFraction = neutralHadEnergyFraction;};
  inline Double_t GetneutralHadEnergyFraction() const {return _neutralHadEnergyFraction;};
  inline Double_t neutralHadEnergyFraction() const {return _neutralHadEnergyFraction;};

  inline void SetneutralEmEmEnergyFraction(Double_t neutralEmEmEnergyFraction){_neutralEmEmEnergyFraction = neutralEmEmEnergyFraction;};
  inline Double_t GetneutralEmEmEnergyFraction() const {return _neutralEmEmEnergyFraction;};
  inline Double_t neutralEmEmEnergyFraction() const {return _neutralEmEmEnergyFraction;};

  inline void SetchargedHadronEnergyFraction(Double_t chargedHadronEnergyFraction){_chargedHadronEnergyFraction = chargedHadronEnergyFraction;};
  inline Double_t GetchargedHadronEnergyFraction() const {return _chargedHadronEnergyFraction;};
  inline Double_t chargedHadronEnergyFraction() const {return _chargedHadronEnergyFraction;};

  inline void SetchargedEmEnergyFraction(Double_t chargedEmEnergyFraction){_chargedEmEnergyFraction = chargedEmEnergyFraction;};
  inline Double_t GetchargedEmEnergyFraction() const {return _chargedEmEnergyFraction;};
  inline Double_t chargedEmEnergyFraction() const {return _chargedEmEnergyFraction;};

  inline void SetmuonEnergyFraction(Double_t muonEnergyFraction){_muonEnergyFraction = muonEnergyFraction;};
  inline Double_t GetmuonEnergyFraction() const {return _muonEnergyFraction;};
  inline Double_t muonEnergyFraction() const {return _muonEnergyFraction;};

  inline void SetelectronEnergy(Double_t electronEnergy){_electronEnergy = electronEnergy;};
  inline Double_t GetelectronEnergy() const {return _electronEnergy;};
  inline Double_t electronEnergy() const {return _electronEnergy;};

  inline void SetphotonEnergy(Double_t photonEnergy){_photonEnergy = photonEnergy;};
  inline Double_t GetphotonEnergy() const {return _photonEnergy;};
  inline Double_t photonEnergy() const {return _photonEnergy;};

  inline void SetuncorrPt(Double_t uncorrPt){_uncorrPt = uncorrPt;};
  inline Double_t GetuncorrPt() const {return _uncorrPt;};
  inline Double_t uncorrPt() const {return _uncorrPt;};

  inline void SetL1corrPt(Double_t L1corrPt){_L1corrPt = L1corrPt;};
  inline Double_t GetL1corrPt() const {return _L1corrPt;};
  inline Double_t L1corrPt() const {return _L1corrPt;};

  inline void SetuncorrE(Double_t uncorrE){_uncorrE = uncorrE;};
  inline Double_t GetuncorrE() const {return _uncorrE;};
  inline Double_t uncorrE() const {return _uncorrE;};

  inline void SetTagged(Bool_t isTagged){_tagged = isTagged;};
  inline Bool_t IsTagged() const {return _tagged;};
  inline Bool_t tagged() const {return _tagged;};

  inline void SetClosestLep(Double_t closestLep){_closestLep = closestLep;};
  inline Double_t GetClosestLep() const {return _closestLep;};
  inline Double_t closestLep() const {return _closestLep;};

  inline void SetisLooseBdisc(Double_t isLooseBdisc){_isLooseBdisc = isLooseBdisc;};
  inline Double_t GetisLooseBdisc() const {return _isLooseBdisc;};
  inline Double_t isLooseBdisc() const {return _isLooseBdisc;};

  inline void SetisNormalJet(Double_t isNormalJet){_isNormalJet = isNormalJet;};
  inline Double_t GetisNormalJet() const {return _isNormalJet;};
  inline Double_t isNormalJet() const {return _isNormalJet;};

  inline void SetisForwardJet(Double_t isForwardJet){_isForwardJet = isForwardJet;};
  inline Double_t GetisForwardJet() const {return _isForwardJet;};
  inline Double_t isForwardJet() const {return _isForwardJet;};

  inline void SetisMediumBdisc(Double_t isMediumBdisc){_isMediumBdisc = isMediumBdisc;};
  inline Double_t GetisMediumBdisc() const {return _isMediumBdisc;};
  inline Double_t isMediumBdisc() const {return _isMediumBdisc;};

  inline void SetisTightBdisc(Double_t isTightBdisc){_isTightBdisc = isTightBdisc;};
  inline Double_t GetisTightBdisc() const {return _isTightBdisc;};
  inline Double_t isTightBdisc() const {return _isTightBdisc;};

  inline void SetHjDisc(Double_t HjDisc){_HjDisc = HjDisc;};
  inline Double_t GetHjDisc() const {return _HjDisc;};
  inline Double_t HjDisc() const {return _HjDisc;};

  inline void Setqg(Double_t qg){_qg = qg;};
  inline Double_t Getqg() const {return _qg;};
  inline Double_t qg() const {return _qg;};

  inline void Setaxis2(Double_t axis2){_axis2 = axis2;};
  inline Double_t Getaxis2() const {return _axis2;};
  inline Double_t axis2() const {return _axis2;};

  inline void Setaxis1(Double_t axis1){_axis1 = axis1;};
  inline Double_t Getaxis1() const {return _axis1;};
  inline Double_t axis1() const {return _axis1;};

  inline void SetptD(Double_t ptD){_ptD = ptD;};
  inline Double_t GetptD() const {return _ptD;};
  inline Double_t ptD() const {return _ptD;};

  inline void Setmult(Double_t mult){_mult = mult;};
  inline Double_t Getmult() const {return _mult;};
  inline Double_t mult() const {return _mult;};

  inline void Setele_number(Int_t ele_number){_ele_number = ele_number;};
  inline Int_t Getele_number() const {return _ele_number;};
  inline Int_t ele_number() const {return _ele_number;};

  inline void Settau_number(Int_t tau_number){_tau_number = tau_number;};
  inline Int_t Gettau_number() const {return _tau_number;};
  inline Int_t tau_number() const {return _tau_number;};

  inline void Setmu_number(Int_t mu_number){_mu_number = mu_number;};
  inline Int_t Getmu_number() const {return _mu_number;};
  inline Int_t mu_number() const {return _mu_number;};

  inline void SetpfCombinedCvsLJetTags(Double_t pfCombinedCvsLJetTags){_pfCombinedCvsLJetTags = pfCombinedCvsLJetTags;};
  inline Double_t GetpfCombinedCvsLJetTags() const {return _pfCombinedCvsLJetTags;};
  inline Double_t pfCombinedCvsLJetTags() const {return _pfCombinedCvsLJetTags;};

  inline void SetpfCombinedCvsBJetTags(Double_t pfCombinedCvsBJetTags){_pfCombinedCvsBJetTags = pfCombinedCvsBJetTags;};
  inline Double_t GetpfCombinedCvsBJetTags() const {return _pfCombinedCvsBJetTags;};
  inline Double_t pfCombinedCvsBJetTags() const {return _pfCombinedCvsBJetTags;};

  inline void SetpfCombinedInclusiveSecondaryVertexV2BJetTags(Double_t pfCombinedInclusiveSecondaryVertexV2BJetTags){_pfCombinedInclusiveSecondaryVertexV2BJetTags = pfCombinedInclusiveSecondaryVertexV2BJetTags;};
  inline Double_t GetpfCombinedInclusiveSecondaryVertexV2BJetTags() const {return _pfCombinedInclusiveSecondaryVertexV2BJetTags;};
  inline Double_t pfCombinedInclusiveSecondaryVertexV2BJetTags() const {return _pfCombinedInclusiveSecondaryVertexV2BJetTags;};

  inline void SetpfCombinedMVAV2BJetTags(Double_t pfCombinedMVAV2BJetTags){_pfCombinedMVAV2BJetTags = pfCombinedMVAV2BJetTags;};
  inline Double_t GetpfCombinedMVAV2BJetTags() const {return _pfCombinedMVAV2BJetTags;};
  inline Double_t pfCombinedMVAV2BJetTags() const {return _pfCombinedMVAV2BJetTags;};

  inline void SetpfJetProbabilityBJetTags(Double_t pfJetProbabilityBJetTags){_pfJetProbabilityBJetTags = pfJetProbabilityBJetTags;};
  inline Double_t GetpfJetProbabilityBJetTags() const {return _pfJetProbabilityBJetTags;};
  inline Double_t pfJetProbabilityBJetTags() const {return _pfJetProbabilityBJetTags;};

  inline void SetpfDeepCSVCvsLJetTags(Double_t pfDeepCSVCvsLJetTags){_pfDeepCSVCvsLJetTags = pfDeepCSVCvsLJetTags;};
  inline Double_t GetpfDeepCSVCvsLJetTags() const {return _pfDeepCSVCvsLJetTags;};
  inline Double_t pfDeepCSVCvsLJetTags() const {return _pfDeepCSVCvsLJetTags;};

  inline void SetpfDeepCSVCvsBJetTags(Double_t pfDeepCSVCvsBJetTags){_pfDeepCSVCvsBJetTags = pfDeepCSVCvsBJetTags;};
  inline Double_t GetpfDeepCSVCvsBJetTags() const {return _pfDeepCSVCvsBJetTags;};
  inline Double_t pfDeepCSVCvsBJetTags() const {return _pfDeepCSVCvsBJetTags;};

  inline void SetpfDeepCSVBJetTags(Double_t pfDeepCSVBJetTags){_pfDeepCSVBJetTags = pfDeepCSVBJetTags;};
  inline Double_t GetpfDeepCSVBJetTags() const {return _pfDeepCSVBJetTags;};
  inline Double_t pfDeepCSVBJetTags() const {return _pfDeepCSVBJetTags;};

  inline void SetpfDeepFlavourBJetTags(Double_t pfDeepFlavourBJetTags){_pfDeepFlavourBJetTags = pfDeepFlavourBJetTags;};
  inline Double_t GetpfDeepFlavourBJetTags() const {return _pfDeepFlavourBJetTags;};
  inline Double_t pfDeepFlavourBJetTags() const {return _pfDeepFlavourBJetTags;};

  inline void Setlepdrmax(Double_t lepdrmax){_lepdrmax = lepdrmax;};
  inline Double_t Getlepdrmax() const {return _lepdrmax;};
  inline Double_t lepdrmax() const {return _lepdrmax;};

  inline void Setlepdrmin(Double_t lepdrmin){_lepdrmin = lepdrmin;};
  inline Double_t Getlepdrmin() const {return _lepdrmin;};
  inline Double_t lepdrmin() const {return _lepdrmin;};

  inline void SetpartonFlavour(Double_t partonFlavour){_partonFlavour = partonFlavour;};
  inline Double_t GetpartonFlavour() const {return _partonFlavour;};
  inline Double_t partonFlavour() const {return _partonFlavour;};

  inline void SethadronFlavour(Double_t hadronFlavour){_hadronFlavour = hadronFlavour;};
  inline Double_t GethadronFlavour() const {return _hadronFlavour;};
  inline Double_t hadronFlavour() const {return _hadronFlavour;};

  inline void SetisToptag(Double_t isToptag){_isToptag = isToptag;};
  inline Double_t GetisToptag() const {return _isToptag;};
  inline Double_t isToptag() const {return _isToptag;};
  
  inline void SetisResToptag(Double_t isResToptag){_isResToptag = isResToptag;};
  inline Double_t GetisResToptag() const {return _isResToptag;};
  inline Double_t isResToptag() const {return _isResToptag;};
  
  inline void Setindex(Double_t index){_index = index;};
  inline Double_t Getindex() const {return _index;};
  inline Double_t index() const {return _index;};
  
  inline void SetgenMother_pdgId(Double_t genMother_pdgId){_genMother_pdgId = genMother_pdgId;};
  inline Double_t GetgenMother_pdgId() const {return _genMother_pdgId;};
  inline Double_t genMother_pdgId() const {return _genMother_pdgId;};

  inline void SetgenGrandMother_pdgId(Double_t genGrandMother_pdgId){_genGrandMother_pdgId = genGrandMother_pdgId;};
  inline Double_t GetgenGrandMother_pdgId() const {return _genGrandMother_pdgId;};
  inline Double_t genGrandMother_pdgId() const {return _genGrandMother_pdgId;};

  inline void SetmatchId(Double_t matchId){_matchId = matchId;};
  inline Double_t GetmatchId() const {return _matchId;};
  inline Double_t matchId() const {return _matchId;};

  inline void SetisFromTop(Double_t isFromTop){_isFromTop = isFromTop;};
  inline Double_t GetisFromTop() const {return _isFromTop;};
  inline Double_t isFromTop() const {return _isFromTop;};

  inline void SetisFromH(Double_t isFromH){_isFromH = isFromH;};
  inline Double_t GetisFromH() const {return _isFromH;};
  inline Double_t isFromH() const {return _isFromH;};

  inline void SetmatchMother_Id(Double_t matchMother_Id){_matchMother_Id = matchMother_Id;};
  inline Double_t GetmatchMother_Id() const {return _matchMother_Id;};
  inline Double_t matchMother_Id() const {return _matchMother_Id;};

  inline void SetmatchGrandMother_Id(Double_t matchGrandMother_Id){_matchGrandMother_Id = matchGrandMother_Id;};
  inline Double_t GetmatchGrandMother_Id() const {return _matchGrandMother_Id;};
  inline Double_t matchGrandMother_Id() const {return _matchGrandMother_Id;};

  // ttH functions
  void set_HjMVAreader(TEnv* config);
  
  
  // Overloaded Operators
  // +=
  Jet& operator+=(const Jet& other);
  // +
  Jet operator+(const Jet& other);
  // = Jet const
  Jet& operator=(const Particle& other);
  // = Particle const
  Jet& operator=(const Jet& other);
  // = Jet non-const
  Jet& operator=(Jet& other);
    

 private:
  Int_t _numberOfConstituents;   
  Int_t _chargedMultiplicity;   
  Double_t _bDiscriminator;   
  Double_t _pileupId;   
  Double_t _mass;   
  Double_t _neutralHadEnergyFraction;   
  Double_t _neutralEmEmEnergyFraction;   
  Double_t _chargedHadronEnergyFraction;   
  Double_t _chargedEmEnergyFraction;   
  Double_t _muonEnergyFraction;   
  Double_t _electronEnergy;   
  Double_t _photonEnergy;   
  Double_t _uncorrPt; 
  Double_t _L1corrPt; 
  Double_t _uncorrE; 
  Bool_t _tagged;
  Double_t _closestLep;
  Double_t _isNormalJet;
  Double_t _isForwardJet;
  Double_t _isLooseBdisc;
  Double_t _isMediumBdisc;
  Double_t _isTightBdisc;
  Double_t _HjDisc;
  Double_t _qg;
  Double_t _axis2;
  Double_t _axis1;
  Double_t _ptD;
  Double_t _mult;
  Int_t _ele_number;
  Int_t _tau_number;
  Int_t _mu_number;
  Double_t _pfCombinedCvsLJetTags;
  Double_t _pfCombinedCvsBJetTags;
  Double_t _pfCombinedInclusiveSecondaryVertexV2BJetTags;
  Double_t _pfCombinedMVAV2BJetTags;
  Double_t _pfJetProbabilityBJetTags;
  Double_t _pfDeepCSVCvsLJetTags;
  Double_t _pfDeepCSVCvsBJetTags;
  Double_t _pfDeepFlavourBJetTags;
  Double_t _pfDeepCSVBJetTags;
  Double_t _lepdrmax;
  Double_t _lepdrmin;
  Double_t _partonFlavour;
  Double_t _hadronFlavour;
  Double_t _isToptag;
  Double_t _isResToptag;
  Double_t _index;
  Double_t _genMother_pdgId;
  Double_t _genGrandMother_pdgId;
  Double_t _matchId;
  Double_t _isFromTop;
  Double_t _isFromH;
  Double_t _matchMother_Id; // only ->mother(0) 
  Double_t _matchGrandMother_Id; // only ->mother(0)->mother(0)

  // Cuts applied to the jet objects
  Double_t _maxEtaCut;
  Double_t _minPtCut;
  Double_t _FWJetEtaCut;
  Double_t _FWJetHighPtCut;
  Double_t _FWJetHighPtMinEta;
  Double_t _FWJetHighPtMaxEta;
  Double_t _bMaxEtaCut;
  Double_t _bMinPtCut;
  Double_t _LWPbTagCut;
  Double_t _MWPbTagCut;
  Double_t _TWPbTagCut;
  Double_t _closestLeptonCut;
  Int_t _dataEra;
  
  // ttH functions
  // Hj tagger mva
    TMVA::Reader *readerjet;
    Float_t jetvarqg;
    Float_t jetvarlepdrmax;
    Float_t jetvarlepdrmin;
    Float_t jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags;
    Float_t jetvarpt;
    double get_JetMVA();

  // Are we running systematic variations?
  Int_t _jesUp;
  Int_t _jesDown;
  Int_t _jerUp;
  Int_t _jerDown;

  // Apply the jet correction systematics
  void SystematicPtShift(EventTree * evtr, Int_t iE, TLorentzVector * met, Bool_t useLepAware);
 
  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(Jet,0)
  ////////////////////////////////////////////////////////////////////////////////
};


#endif
