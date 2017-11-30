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
 _isLooseBdisc =0.0;
 _isMediumBdisc =0.0;
 _isTightBdisc =0.0;
 _qg =0.0;
 _lepdrmax =0.0;
 _lepdrmin =0.0;
 _HjDisc =0.0;
}

  void SetCuts(TEnv* config);

  // Fill the jet from an EventTree 
  Bool_t Fill( double myJESCorr, double myJERCorr, std::vector<Lepton>& selectedLeptons, std::vector<Tau>& selectedTaus, EventTree *evtr, Int_t iE, TLorentzVector * met);
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

  inline void SetTagged(Bool_t isTagged){_tagged = isTagged;};
  inline Bool_t IsTagged() const {return _tagged;};
  inline Bool_t tagged() const {return _tagged;};

  inline void SetClosestLep(Double_t closestLep){_closestLep = closestLep;};
  inline Double_t GetClosestLep() const {return _closestLep;};
  inline Double_t closestLep() const {return _closestLep;};

  inline void SetisLooseBdisc(Double_t isLooseBdisc){_isLooseBdisc = isLooseBdisc;};
  inline Double_t GetisLooseBdisc() const {return _isLooseBdisc;};
  inline Double_t isLooseBdisc() const {return _isLooseBdisc;};

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

  inline void Setlepdrmax(Double_t lepdrmax){_lepdrmax = lepdrmax;};
  inline Double_t Getlepdrmax() const {return _lepdrmax;};
  inline Double_t lepdrmax() const {return _lepdrmax;};

  inline void Setlepdrmin(Double_t lepdrmin){_lepdrmin = lepdrmin;};
  inline Double_t Getlepdrmin() const {return _lepdrmin;};
  inline Double_t lepdrmin() const {return _lepdrmin;};

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
  Bool_t _tagged;
  Double_t _closestLep;
  Double_t _isLooseBdisc;
  Double_t _isMediumBdisc;
  Double_t _isTightBdisc;
  Double_t _HjDisc;
  Double_t _qg;
  Double_t _lepdrmax;
  Double_t _lepdrmin;

  // Cuts applied to the jet objects
  Double_t _maxEtaCut;
  Double_t _minPtCut;
  Double_t _bMaxEtaCut;
  Double_t _bMinPtCut;
  Double_t _LWPbTagCut;
  Double_t _MWPbTagCut;
  Double_t _TWPbTagCut;
  Double_t _closestLeptonCut;
  
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
  void SystematicPtShift(EventTree * evtr, Int_t iE, TLorentzVector * met);
 
  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(Jet,0)
  ////////////////////////////////////////////////////////////////////////////////
};


#endif
