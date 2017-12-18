/******************************************************************************
 * MCH.cpp                                                                    *
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

#include "SingleTopRootAnalysis/Particles/Truth/MCH.hpp"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

// Integrate classes into the Root system
ClassImp(MCH)

/******************************************************************************
 * MCH::MCH()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  MCH::MCH()
{

} //MCH()

/******************************************************************************
 * MCH::~MCH()                                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
MCH::~MCH()
{

} //~MCH()


/******************************************************************************
 * MCH::MCH(const MCH& other)                                                 *
 *                                                                            *
 * Copy constructor MCH const                                                 *
 *                                                                            *
 * Input:  MCH                                                                *
 * Output: None                                                               *
 ******************************************************************************/
MCH::MCH(const MCH& other): MCParticle(other)
{

} //MCH()

/******************************************************************************
 * MCH::MCH(const MCH& other)                                                 *
 *                                                                            *
 * Copy constructor MCParticle const                                          *
 *                                                                            *
 * Input:  MCH                                                                *
 * Output: None                                                               *
 ******************************************************************************/
MCH::MCH(const MCParticle& other): MCParticle(other)
{ 

} //MCH

/******************************************************************************
 * MCH& MCH::operator+=(const MCH& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  MCH                                                                *
 * Output: MCH                                                                *
 ******************************************************************************/
MCH& MCH::operator+=(const MCH& other)
{
  
  MCParticle::operator+=(other);
   return *this;
} //+=

/******************************************************************************
 * MCH& MCH::operator+(const MCH& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  MCH                                                                *
 * Output: MCH                                                                *
 ******************************************************************************/
MCH MCH::operator+(const MCH& other)
{

  MCParticle::operator+(other);
  return *this;
} //+

/******************************************************************************
 * MCH& MCH::operator=(const W& other)                                        *
 *                                                                            *
 * Overload = MCParticle                                                      *
 *                                                                            *
 * Input:  MCParticleicle::Clear();                                           *
 * Output: MCH                                                                *
 ******************************************************************************/
MCH& MCH::operator=(const MCParticle& other)
{
  
  MCParticle::operator=(other);
  return *this;
} // MCParticle

/******************************************************************************
 * MCH& MCH::operator=(const MCH& other)                                      *
 *                                                                            *
 * Overload = const MCH                                                       *
 *                                                                            *
 * Input:  MCH                                                                *
 * Output: MCH                                                                *
 ******************************************************************************/
MCH& MCH::operator=(const MCH& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCH

/******************************************************************************
 * MCH& MCH::operator=(MCH& other)                                            *
 *                                                                            *
 * Overload = non-const MCH                                                   *
 *                                                                            *
 * Input:  MCH                                                                *
 * Output: MCH                                                                *
 ******************************************************************************/
MCH& MCH::operator=(MCH& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCH()

/******************************************************************************
 * void MCH::Fill(TruthTree *truthTree, Int_t iE)                             *
 *                                                                            *
 * Fill MCH vector from tree                                                  *
 *                                                                            *
 * Input:  Event Tree                                                         *
 * Output: None                                                               *
 ******************************************************************************/
void MCH::FillW(TruthTree *trtr, int iE)
{

  MCParticle::Fill(trtr, iE);

} //Fill()
