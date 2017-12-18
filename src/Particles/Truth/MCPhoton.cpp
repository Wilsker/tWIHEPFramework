/******************************************************************************
 * MCPhoton.cpp                                                                    *
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

#include "SingleTopRootAnalysis/Particles/Truth/MCPhoton.hpp"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

// Integrate classes into the Root system
ClassImp(MCPhoton)

/******************************************************************************
 * MCPhoton::MCPhoton()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  MCPhoton::MCPhoton()
{

} //MCPhoton()

/******************************************************************************
 * MCPhoton::~MCPhoton()                                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
MCPhoton::~MCPhoton()
{

} //~MCPhoton()


/******************************************************************************
 * MCPhoton::MCPhoton(const MCPhoton& other)                                                 *
 *                                                                            *
 * Copy constructor MCPhoton const                                                 *
 *                                                                            *
 * Input:  MCPhoton                                                                *
 * Output: None                                                               *
 ******************************************************************************/
MCPhoton::MCPhoton(const MCPhoton& other): MCParticle(other)
{

} //MCPhoton()

/******************************************************************************
 * MCPhoton::MCPhoton(const MCPhoton& other)                                                 *
 *                                                                            *
 * Copy constructor MCParticle const                                          *
 *                                                                            *
 * Input:  MCPhoton                                                                *
 * Output: None                                                               *
 ******************************************************************************/
MCPhoton::MCPhoton(const MCParticle& other): MCParticle(other)
{ 

} //MCPhoton

/******************************************************************************
 * MCPhoton& MCPhoton::operator+=(const MCPhoton& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  MCPhoton                                                                *
 * Output: MCPhoton                                                                *
 ******************************************************************************/
MCPhoton& MCPhoton::operator+=(const MCPhoton& other)
{
  
  MCParticle::operator+=(other);
   return *this;
} //+=

/******************************************************************************
 * MCPhoton& MCPhoton::operator+(const MCPhoton& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  MCPhoton                                                                *
 * Output: MCPhoton                                                                *
 ******************************************************************************/
MCPhoton MCPhoton::operator+(const MCPhoton& other)
{

  MCParticle::operator+(other);
  return *this;
} //+

/******************************************************************************
 * MCPhoton& MCPhoton::operator=(const W& other)                                        *
 *                                                                            *
 * Overload = MCParticle                                                      *
 *                                                                            *
 * Input:  MCParticleicle::Clear();                                           *
 * Output: MCPhoton                                                                *
 ******************************************************************************/
MCPhoton& MCPhoton::operator=(const MCParticle& other)
{
  
  MCParticle::operator=(other);
  return *this;
} // MCParticle

/******************************************************************************
 * MCPhoton& MCPhoton::operator=(const MCPhoton& other)                                      *
 *                                                                            *
 * Overload = const MCPhoton                                                       *
 *                                                                            *
 * Input:  MCPhoton                                                                *
 * Output: MCPhoton                                                                *
 ******************************************************************************/
MCPhoton& MCPhoton::operator=(const MCPhoton& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCPhoton

/******************************************************************************
 * MCPhoton& MCPhoton::operator=(MCPhoton& other)                                            *
 *                                                                            *
 * Overload = non-const MCPhoton                                                   *
 *                                                                            *
 * Input:  MCPhoton                                                                *
 * Output: MCPhoton                                                                *
 ******************************************************************************/
MCPhoton& MCPhoton::operator=(MCPhoton& other)
{
  MCParticle::operator=(other);
  return *this;
} //MCPhoton()

/******************************************************************************
 * void MCPhoton::Fill(TruthTree *truthTree, Int_t iE)                             *
 *                                                                            *
 * Fill MCPhoton vector from tree                                                  *
 *                                                                            *
 * Input:  Event Tree                                                         *
 * Output: None                                                               *
 ******************************************************************************/
void MCPhoton::FillW(TruthTree *trtr, int iE)
{

  MCParticle::Fill(trtr, iE);

} //Fill()
