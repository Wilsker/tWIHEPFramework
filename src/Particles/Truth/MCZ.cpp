/******************************************************************************
 * MCZ.cpp                                                                    *
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

#include "SingleTopRootAnalysis/Particles/Truth/MCZ.hpp"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

// Integrate classes into the Root system
ClassImp(MCZ)

/******************************************************************************
 * MCZ::MCZ()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  MCZ::MCZ()
{

} //MCZ()

/******************************************************************************
 * MCZ::~MCZ()                                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
MCZ::~MCZ()
{

} //~MCZ()


/******************************************************************************
 * MCZ::MCZ(const MCZ& other)                                                 *
 *                                                                            *
 * Copy constructor MCZ const                                                 *
 *                                                                            *
 * Input:  MCZ                                                                *
 * Output: None                                                               *
 ******************************************************************************/
MCZ::MCZ(const MCZ& other): MCParticle(other)
{

} //MCZ()

/******************************************************************************
 * MCZ::MCZ(const MCZ& other)                                                 *
 *                                                                            *
 * Copy constructor MCParticle const                                          *
 *                                                                            *
 * Input:  MCZ                                                                *
 * Output: None                                                               *
 ******************************************************************************/
MCZ::MCZ(const MCParticle& other): MCParticle(other)
{ 

} //MCZ

/******************************************************************************
 * MCZ& MCZ::operator+=(const MCZ& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  MCZ                                                                *
 * Output: MCZ                                                                *
 ******************************************************************************/
MCZ& MCZ::operator+=(const MCZ& other)
{
  
  MCParticle::operator+=(other);
   return *this;
} //+=

/******************************************************************************
 * MCZ& MCZ::operator+(const MCZ& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  MCZ                                                                *
 * Output: MCZ                                                                *
 ******************************************************************************/
MCZ MCZ::operator+(const MCZ& other)
{

  MCParticle::operator+(other);
  return *this;
} //+

/******************************************************************************
 * MCZ& MCZ::operator=(const W& other)                                        *
 *                                                                            *
 * Overload = MCParticle                                                      *
 *                                                                            *
 * Input:  MCParticleicle::Clear();                                           *
 * Output: MCZ                                                                *
 ******************************************************************************/
MCZ& MCZ::operator=(const MCParticle& other)
{
  
  MCParticle::operator=(other);
  return *this;
} // MCParticle

/******************************************************************************
 * MCZ& MCZ::operator=(const MCZ& other)                                      *
 *                                                                            *
 * Overload = const MCZ                                                       *
 *                                                                            *
 * Input:  MCZ                                                                *
 * Output: MCZ                                                                *
 ******************************************************************************/
MCZ& MCZ::operator=(const MCZ& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCZ

/******************************************************************************
 * MCZ& MCZ::operator=(MCZ& other)                                            *
 *                                                                            *
 * Overload = non-const MCZ                                                   *
 *                                                                            *
 * Input:  MCZ                                                                *
 * Output: MCZ                                                                *
 ******************************************************************************/
MCZ& MCZ::operator=(MCZ& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCZ()

/******************************************************************************
 * void MCZ::Fill(TruthTree *truthTree, Int_t iE)                             *
 *                                                                            *
 * Fill MCZ vector from tree                                                  *
 *                                                                            *
 * Input:  Event Tree                                                         *
 * Output: None                                                               *
 ******************************************************************************/
void MCZ::FillW(TruthTree *trtr, int iE)
{

  MCParticle::Fill(trtr, iE);

} //Fill()

const MCZ MCZ::GetGenMotherNoFsr(const MCZ Ptemp, std::vector<MCParticle>& MCParticles) const
{
  if (Ptemp.numMother() > 0)
    {
      const MCZ mother = MCParticles.at(Ptemp.BmotherIndex());
      if ( Ptemp.motherpdg_id() != Ptemp.PdgId() ) return mother;
      else return GetGenMotherNoFsr(mother, MCParticles);
    }
  else 
    {
      return Ptemp;
    }
}

