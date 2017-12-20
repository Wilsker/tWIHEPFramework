/******************************************************************************
 * MCZ.hpp                                                                    *
 *                                                                            *
 * Container for a MCZ                                                        *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of MCZ class                                       *
 *    MCZ()                           -- Default Constructor                  *
 *    MCZ()                           -- Parameterized Constructor            *
 *    MCZ()                           -- Constructor with Particle            *
 *    ~MCZ()                          -- Destructor                           *
 *    Clear()                            -- Set contents to default           *
 *    Fill()                             -- Fill w from event tree            *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const MCZ              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of MCZ class                                          *
 *                                                                            *
 * History                                                                    *
 *      15 May 2007 - Created by J. Holzbauer                                 *
 *****************************************************************************/
#ifndef MCZ_h
#define MCZ_h

#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include "SingleTopRootAnalysis/Trees/TruthTree.hpp"

class MCZ: public MCParticle
{
public:
  // Default Constructor
  MCZ();

  // Copy constructor from MCZ
  MCZ(const MCZ& other);

  // Copy constructor from MCParticle
  MCZ(const MCParticle& other);

  // Destructor
  ~MCZ();

  // Set all contents to their defaults
  inline void Clear() { MCParticle::Clear();};

  // Fill the MCZ from a TruthTree
  void FillW(TruthTree *trtr, Int_t iE);

  // Getters and Setters
  // GenMother
  const MCZ GetGenMotherNoFsr(const MCZ Ptemp, std::vector<MCParticle>& MCParticles) const;


  // Overloaded operators:
  // +=
  MCZ& operator+=(const MCZ& other);
  // +
  MCZ operator+(const MCZ& other);
  // = MCParticle const
  MCZ& operator=(const MCParticle& other);
  // = MCZ const
  MCZ& operator=(const MCZ& other);
  // = MCZ non-const
  MCZ& operator=(MCZ& other);
    
private:

  ///////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(MCZ,0)
  ///////////////////////////////////////////////////////////////////////////////

};


#endif
