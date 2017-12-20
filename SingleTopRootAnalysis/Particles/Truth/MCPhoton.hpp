/******************************************************************************
 * MCPhoton.hpp                                                                    *
 *                                                                            *
 * Container for a MCPhoton                                                        *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of MCPhoton class                                       *
 *    MCPhoton()                           -- Default Constructor                  *
 *    MCPhoton()                           -- Parameterized Constructor            *
 *    MCPhoton()                           -- Constructor with Particle            *
 *    ~MCPhoton()                          -- Destructor                           *
 *    Clear()                            -- Set contents to default           *
 *    Fill()                             -- Fill w from event tree            *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const MCPhoton              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of MCPhoton class                                          *
 *                                                                            *
 * History                                                                    *
 *      15 May 2007 - Created by J. Holzbauer                                 *
 *****************************************************************************/
#ifndef MCPhoton_h
#define MCPhoton_h

#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include "SingleTopRootAnalysis/Trees/TruthTree.hpp"

class MCPhoton: public MCParticle
{
public:
  // Default Constructor
  MCPhoton();

  // Copy constructor from MCPhoton
  MCPhoton(const MCPhoton& other);

  // Copy constructor from MCParticle
  MCPhoton(const MCParticle& other);

  // Destructor
  ~MCPhoton();

  // Set all contents to their defaults
  inline void Clear() { MCParticle::Clear();};

  // Fill the MCPhoton from a TruthTree
  void FillW(TruthTree *trtr, Int_t iE);

  // Getters and Setters
  // GenMother
  const MCPhoton GetGenMotherNoFsr(const MCPhoton Ptemp, std::vector<MCParticle>& MCParticles) const;


  // Overloaded operators:
  // +=
  MCPhoton& operator+=(const MCPhoton& other);
  // +
  MCPhoton operator+(const MCPhoton& other);
  // = MCParticle const
  MCPhoton& operator=(const MCParticle& other);
  // = MCPhoton const
  MCPhoton& operator=(const MCPhoton& other);
  // = MCPhoton non-const
  MCPhoton& operator=(MCPhoton& other);
    
private:

  ///////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(MCPhoton,0)
  ///////////////////////////////////////////////////////////////////////////////

};


#endif
