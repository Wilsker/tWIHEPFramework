/******************************************************************************
 * Tau.hpp                                                                    *
 *                                                                            *
 * Store information about final state Taus                                   *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Tau class                                       *
 *    Tau()                              -- Default Constructor               *
 *    Tau()                              -- Parameterized Constructor         *
 *    Tau()                              -- Constructor with Particle         *
 *    ~Tau()                             -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill tau from event tree          *
 *    FillFastSim                        -- Fill tau from FastSim tree        *
 *    SetSetNumTracks                    -- Set Num Tracks                    *
 *    GetSetNumTracks                    -- Set Num Tracks                    *
 *    NumTracks                          -- Set Num Tracks                    *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Tau              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Tau class                                          *
 *    Double_t _NumTracks                -- CAL Energy in cone around Tau     *
 *                                                                            *
 *****************************************************************************/

#ifndef tau_h
#define tau_h

#include "SingleTopRootAnalysis/Particles/Recon/Particle.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include "SingleTopRootAnalysis/Trees/EventTree.hpp"
#include "SingleTopRootAnalysis/Trees/FastSimTree.hpp"

class Lepton;

class Tau: public Particle
{
public:
  // Default Constructor
  Tau();

  // Copy constructor  - Tau
  Tau(const Tau& other);

  // Copy Constructor - Particle
  Tau(const Particle& other);

  // Destructor
  ~Tau();

  // Set all contents to their defaults
  inline void Clear() { 
      Particle::Clear(); _NumTracks = 0.0; 
        _charge =0.0;
        _dz =0.0;
        _dxy =0.0;
        _isLoose =0.0;
        _isMedium =0.0;
        _rawMVA =0.0;
        _decayModeFinding =0.0;
      };

  // Fill the tau from an EventTree
  Bool_t Fill(std::vector<Lepton>& selectedLeptons, EventTree *evtr, Int_t iE, TString tauType);
  // also fill from a fastsim tree
  Bool_t FillFastSim(FastSimTree *tr, Int_t iE, TEnv* config);

  // Get and Set Number of tracks for this tau
  void SetNumTracks(const Double_t& eop) { _NumTracks = eop; };
  Double_t GetNumTracks() const { return _NumTracks; };
  Double_t NumTracks() const { return _NumTracks; };

  // Overloaded operators:
  // +=
  Tau& operator+=(const Tau& other);
  // +
  Tau operator+(const Tau& other);
  // = const Particle
  Tau& operator=(const Particle& other);
  // = const Tau
  Tau& operator=(const Tau& other);
  // = non-const Tau
  Tau& operator=(Tau& other);

  void SetCuts(TEnv *config);

//Inline functions
  inline void Setcharge(Double_t charge){_charge = charge;};
  inline Double_t Getcharge() const {return _charge;};
  inline Double_t charge() const {return _charge;};

  inline void Setdz(Double_t dz){_dz = dz;};
  inline Double_t Getdz() const {return _dz;};
  inline Double_t dz() const {return _dz;};

  inline void Setdxy(Double_t dxy){_dxy = dxy;};
  inline Double_t Getdxy() const {return _dxy;};
  inline Double_t dxy() const {return _dxy;};

  inline void SetisLoose(Double_t isLoose){_isLoose = isLoose;};
  inline Double_t GetisLoose() const {return _isLoose;};
  inline Double_t isLoose() const {return _isLoose;};

  inline void SetisMedium(Double_t isMedium){_isMedium = isMedium;};
  inline Double_t GetisMedium() const {return _isMedium;};
  inline Double_t isMedium() const {return _isMedium;};

  inline void SetrawMVA(Double_t rawMVA){_rawMVA = rawMVA;};
  inline Double_t GetrawMVA() const {return _rawMVA;};
  inline Double_t rawMVA() const {return _rawMVA;};

  inline void SetdecayModeFinding(Double_t decayModeFinding){_decayModeFinding = decayModeFinding;};
  inline Double_t GetdecayModeFinding() const {return _decayModeFinding;};
  inline Double_t decayModeFinding() const {return _decayModeFinding;};


private:
  Double_t _NumTracks;   // number of tracks
  Double_t _charge;
  Double_t _dz;
  Double_t _dxy;
  Double_t _isLoose;
  Double_t _isMedium;
  Double_t _rawMVA;
  Double_t _decayModeFinding;
  
  /// cuts reading from config
  Double_t _closestLeptonCut;
  Double_t _minPtCut;
  Double_t _maxEtaCut;
  Double_t _maxDxyCut;
  Double_t _maxDzCut;

  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(Tau,0)
  ////////////////////////////////////////////////////////////////////////////////    

};


#endif
