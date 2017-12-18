/******************************************************************************
 * MCH.hpp                                                                    *
 *                                                                            *
 * Container for a MCH                                                        *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of MCH class                                       *
 *    MCH()                           -- Default Constructor                  *
 *    MCH()                           -- Parameterized Constructor            *
 *    MCH()                           -- Constructor with Particle            *
 *    ~MCH()                          -- Destructor                           *
 *    Clear()                            -- Set contents to default           *
 *    Fill()                             -- Fill w from event tree            *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const MCH              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of MCH class                                          *
 *                                                                            *
 * History                                                                    *
 *      15 May 2007 - Created by J. Holzbauer                                 *
 *****************************************************************************/
#ifndef MCH_h
#define MCH_h

#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include "SingleTopRootAnalysis/Trees/TruthTree.hpp"

class MCH: public MCParticle
{
public:
  // Default Constructor
  MCH();

  // Copy constructor from MCH
  MCH(const MCH& other);

  // Copy constructor from MCParticle
  MCH(const MCParticle& other);

  // Destructor
  ~MCH();

  // Set all contents to their defaults
  inline void Clear() { MCParticle::Clear();};

  // Fill the MCH from a TruthTree
  void FillW(TruthTree *trtr, Int_t iE);

  // Getters and Setters


  // Overloaded operators:
  // +=
  MCH& operator+=(const MCH& other);
  // +
  MCH operator+(const MCH& other);
  // = MCParticle const
  MCH& operator=(const MCParticle& other);
  // = MCH const
  MCH& operator=(const MCH& other);
  // = MCH non-const
  MCH& operator=(MCH& other);
    
private:

  ///////////////////////////////////////////////////////////////////////////////
  // Integrate classes into the Root system
  // Must come at end of class definition
  ClassDef(MCH,0)
  ///////////////////////////////////////////////////////////////////////////////

};


#endif
