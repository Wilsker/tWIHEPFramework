/******************************************************************************
 * MCParticle.hpp                                                             *
 *                                                                            *
 * Container for a MCParticle                                                 *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of MCParticle class                                *
 *    MCParticle()                       -- Default Constructor               *
 *    MCParticle()                       -- Parameterized Constructor         *
 *    MCParticle()                       -- Constructor with Particle         *
 *    ~MCParticle()                      -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill electron from event tree     *
 *    SetPdgId                           -- Set Particle Data Group ID        *
 *    SetStatus                          -- Set Status                        *
 *    SetBarCode                         -- Set Bar Code                      *
 *    GetPdgId                           -- Get Particle Data Group ID        *
 *    PdgId                              -- Get Particle Data Group ID        *
 *    GetAbsPdgId                        -- Get abs Particle Data Group ID    *
 *    AbsPdgId                           -- Get abs Particle Data Group ID    *
 *    GetStatus                          -- Get Status                        *
 *    Status                             -- Get Status                        *
 *    GetBarCode                         -- Get Bar Code                      *
 *    BarCode                            -- Get Bar Code                      *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const MCParticle       *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of MCParticle class                                   *
 *    Int_t _PdgId                       -- PDG ID for this particle          *
 *    Int_t _Status                      -- Status flag for this particle     *
 *    Int_t _BarCode                     -- BarCode flag for this particle    *
 *                                                                            *
 * History                                                                    *
 *      15 Nov 2006 - Created by R. Schwienhorst                              *
 *      20 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      23 Apr 2007 - Modified by J. Holzbauer - Added more PDGID requirements*
 *      08 May 2007 - Modified by J. Holzbauer- added FillDeltaR              *
 *      17 Jul 2007 - Modified by J. Holzbauer- added more jet class tags     *
 *      19 Jul 2007 - RS: Make all "is..." methods return a bool.             *
 *****************************************************************************/

#ifndef MCParticle_h
#define MCParticle_h

#include "SingleTopRootAnalysis/Particles/Recon/Particle.hpp"
#include "SingleTopRootAnalysis/Trees/TruthTree.hpp"
#include "SingleTopRootAnalysis/Trees/EventTree.hpp"
//

class MCParticle: public Particle
{
public:
  // Default constructor
  MCParticle();

  // Copy constructor
  MCParticle(const MCParticle& other);

  // Copy Constructor - Particle
  MCParticle(const Particle& other);

  // Destructor
  ~MCParticle();

  // Set all contents to their defaults
  inline void Clear() { Particle::Clear(); _PdgId = 0; _Status = 0; _BarCode = 0;  _numMother = 0;
 _numDaught =0;
 _BmotherIndex =0;
 _Index =0;
 _motherpdg_id =0;
 _isPromptFinalState =0;
 _isDirectPromptTauDecayProductFinalState =0;
 _BmotherIndices.clear();
 _BdaughtIndices.clear();
  };

  // Fill the MCParticle from a TruthTree
  void Fill(TruthTree *trtr, Int_t iE);
  void Fill(EventTree *evtr, Int_t iE, Int_t& motherIndex, Int_t& daughtIndex);

 
  // Setters PDG ID
  inline void SetPdgId(Double_t pdgId)  { _PdgId   = pdgId;   };
  inline void SetStatus(Int_t status)   { _Status  = status;  };
  inline void SetnumMother(Int_t nparents)   { _numMother  = nparents;  };
  inline void SetBarCode(Int_t barCode) { _BarCode = barCode; };


  // Getters PDG ID
  inline Double_t GetPdgId() const { return _PdgId; };
  inline Double_t PdgId() const { return GetPdgId(); };
  inline Double_t GetAbsPdgId() const { return(_PdgId>0 ? _PdgId : -_PdgId) ; };
  inline Double_t AbsPdgId() const { return GetAbsPdgId(); };
  


  // Particles ID check functions
  inline bool isMuon() const {return(AbsPdgId()==13); };
  inline bool isElectron() const {return(AbsPdgId()==11); };
  inline bool isTau() const {return(AbsPdgId()==15); };
  inline bool isTop() const {return(AbsPdgId()==6); };
  inline bool isPhoton() const {return(AbsPdgId()==22); };
  inline bool isW() const {return(AbsPdgId()==24); };
  inline bool isH() const {return(AbsPdgId()==25); };
  inline bool isZ() const {return(AbsPdgId()==23); };
  inline bool isChargedPion() const {return(AbsPdgId()==211); };
  inline bool isChargedK() const {return(AbsPdgId()==321); };
  inline bool isBJet() const {return(AbsPdgId()==5); };
  inline bool isCJet() const {return(AbsPdgId()==4); };
  inline bool isLightQuarkJet() const {return((AbsPdgId()>=1 && AbsPdgId()<=3)); };
  inline bool isLightJet() const {return(AbsPdgId()==21 || (AbsPdgId()>=1 && AbsPdgId()<=3)); };
  inline bool isJet() const {return(AbsPdgId()>=1 && AbsPdgId()<=5); };
  inline bool isQuark() const {return(AbsPdgId()>=1 && AbsPdgId()<=6); };
  inline bool isNeutrino() const {return(AbsPdgId()==12 || AbsPdgId()==14|| AbsPdgId()==16); };

  // Status flag
  inline Int_t GetStatus() const { return _Status; };
  inline Int_t Status() const { return GetStatus(); };
 
  // numMother flag
  inline Int_t GetnumMother() const { return _numMother; };
  inline Int_t numMother() const { return GetnumMother(); };

  // GenMother
  const MCParticle GetGenMotherNoFsr(const MCParticle Ptemp, std::vector<MCParticle>& MCParticles) const;
  Bool_t isFromB(const MCParticle Ptemp, std::vector<MCParticle>& MCParticles, int bid =5)const;

  // Stable flag
  inline Int_t GetBarCode() const { return _BarCode; };
  inline Int_t BarCode() const { return GetBarCode(); };


  inline void SetnumDaught(Int_t numDaught){_numDaught = numDaught;};
  inline Int_t GetnumDaught() const {return _numDaught;};
  inline Int_t numDaught() const {return _numDaught;};

  inline void SetBmotherIndex(Int_t BmotherIndex){_BmotherIndex = BmotherIndex;};
  inline Int_t GetBmotherIndex() const {return _BmotherIndex;};
  inline Int_t BmotherIndex() const {return _BmotherIndex;};

  inline void SetIndex(Int_t Index){_Index = Index;};
  inline Int_t GetIndex() const {return _Index;};
  inline Int_t Index() const {return _Index;};

  inline void Setmotherpdg_id(Int_t motherpdg_id){_motherpdg_id = motherpdg_id;};
  inline Int_t Getmotherpdg_id() const {return _motherpdg_id;};
  inline Int_t motherpdg_id() const {return _motherpdg_id;};

  inline void SetisPromptFinalState(Int_t isPromptFinalState){_isPromptFinalState = isPromptFinalState;};
  inline Int_t GetisPromptFinalState() const {return _isPromptFinalState;};
  inline Int_t isPromptFinalState() const {return _isPromptFinalState;};

  inline void SetisDirectPromptTauDecayProductFinalState(Int_t isDirectPromptTauDecayProductFinalState){_isDirectPromptTauDecayProductFinalState = isDirectPromptTauDecayProductFinalState;};
  inline Int_t GetisDirectPromptTauDecayProductFinalState() const {return _isDirectPromptTauDecayProductFinalState;};
  inline Int_t isDirectPromptTauDecayProductFinalState() const {return _isDirectPromptTauDecayProductFinalState;};

  inline void SetBmotherIndices(std::vector<Int_t> BmotherIndices){_BmotherIndices = BmotherIndices;};
  inline std::vector<Int_t> GetBmotherIndices() const {return _BmotherIndices;};
  inline std::vector<Int_t> BmotherIndices() const {return _BmotherIndices;};

  inline void SetBdaughtIndices(std::vector<Int_t> BdaughtIndices){_BdaughtIndices = BdaughtIndices;};
  inline std::vector<Int_t> GetBdaughtIndices() const {return _BdaughtIndices;};
  inline std::vector<Int_t> BdaughtIndices() const {return _BdaughtIndices;};

  // Overloaded operators:
  // +=
  MCParticle& operator+=(const MCParticle& other);
  // +
  MCParticle operator+(const MCParticle& other);
  // = const Particle
  MCParticle& operator=(const Particle& other);
  // = MCParticle const
  MCParticle& operator=(const MCParticle& other);
  // = MC Particle const
  MCParticle& operator=(MCParticle& other);

protected:
  Double_t _PdgId;   // PDG ID for this particle
  Int_t _Status;     // Status flag for this particle
  Int_t _numMother;     // Status flag for this particle
  Int_t _BarCode;    // BarCode flag for this particle
  Int_t _numDaught;
  Int_t _BmotherIndex;
  Int_t _Index;
  Int_t _motherpdg_id;
  Int_t _isPromptFinalState;
  Int_t _isDirectPromptTauDecayProductFinalState;
  std::vector<Int_t> _BmotherIndices;
  std::vector<Int_t> _BdaughtIndices;
 
  ////////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(MCParticle,0)
  ////////////////////////////////////////////////////////////////////////////////

};

#endif
