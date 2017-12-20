//////////////////////////////////////////////////////////////////
//
// file: MCParticle.cpp
// Description: Create a container for an MCParticle. 
//
// Author: Reinhard Schwienhorst
// Created: 11/15/2006
//
// Modifications:
//    19 Jan 2007 - Modified by R. Schwienhorst: Adapt for change in truth    *
//                  tree used for MC truth information to "Tru_".             *
//
//
//////////////////////////////////////////////////////////////////
#include "SingleTopRootAnalysis/Particles/Truth/MCParticle.hpp"
#include <iostream>
#include <string>
#include <fstream>

 
using namespace std;

// needed to run with compiled Root:
ClassImp(MCParticle)

//-------------------------------------------------------------------------
// default constructor 
// 
  MCParticle::MCParticle() : Particle::Particle(),_PdgId(0),
					       _Status(0),
  _numMother       (0),
  _numDaught       (0),
  _BmotherIndex       (0),
  _Index       (0),
  _motherpdg_id       (0),
  _BmotherIndices       (0,0),
  _BdaughtIndices       (0,0),
                           _BarCode(0)
{
}

//-------------------------------------------------------------------------
// default destructor 
// 
MCParticle::~MCParticle()
{
  //cout<<"In MCParticle destructor"<<endl;
}

//-------------------------------------------------------------------------
// constructor from other MCParticle 
// 
MCParticle::MCParticle(const MCParticle& other): Particle(other),
						 _PdgId(other.PdgId()),
  _numMother(other.numMother()),
  _numDaught(other.numDaught()),
  _BmotherIndex(other.BmotherIndex()),
  _Index(other.Index()),
  _motherpdg_id(other.motherpdg_id()),
                         _BarCode(other.BarCode()),
  _BmotherIndices(other.BmotherIndices()),
  _BdaughtIndices(other.BdaughtIndices()),
						 _Status(other.Status())
{
}

//-------------------------------------------------------------------------
// constructor from other particle
// 
MCParticle::MCParticle(const Particle& other): Particle(other),_PdgId(0),
					       _Status(0),
  _numMother       (0),
  _numDaught       (0),
  _BmotherIndex       (0),
  _Index       (0),
  _motherpdg_id       (0),
  _BmotherIndices       (0,0),
  _BdaughtIndices       (0,0),
                           _BarCode(0)
{
}

//-------------------------------------------------------------------------
// operator overloading
// 
// +=
MCParticle& MCParticle::operator+=(const MCParticle& other)
{
  
  Particle::operator+=(other);
  // don't change pdgid or status or stable flags.

  return *this;
}

//-------------------------------------------------------------------------
// 
// addition operator overloading
MCParticle MCParticle::operator+(const MCParticle& other)
{
  //cout<<"beginning of  MCParticle::operator+"<<endl;
  Particle tltemp=Particle::operator+(other);
  MCParticle ptemp=tltemp;

  // I don't know how to add PDG IDs or flags, so for now simply don't modify
  // anything from the first one.
  ptemp.SetPdgId( _PdgId );
  ptemp.SetStatus( _Status );
  ptemp.SetBarCode( _BarCode );
  ptemp.SetnumMother(_numMother);
  ptemp.SetnumDaught(_numDaught);
  ptemp.SetBmotherIndex(_BmotherIndex);
  ptemp.Setmotherpdg_id(_motherpdg_id);
  ptemp.SetBmotherIndices(other.BmotherIndices());
  ptemp.SetBdaughtIndices(other.BdaughtIndices());


  // done! return the temp particle
  //cout<<"returning from  MCParticle::operator+"<<endl;
  return ptemp;
}

//-------------------------------------------------------------------------
// assignment operator overloading from another MCParticle
// 
MCParticle& MCParticle::operator=(const Particle& other)
{
  
  Particle::operator=(other);
  SetPdgId(0);
  SetStatus(0);
  SetnumMother       (0);
  SetnumDaught       (0);
  SetBmotherIndex       (0);
  Setmotherpdg_id       (0);
  SetBarCode(0);
  SetBmotherIndices       (std::vector<Int_t>(0));
  SetBdaughtIndices       (std::vector<Int_t>(0));
  return *this;
}

//-------------------------------------------------------------------------
// assignment operator overloading from another MCParticle
// (const version)
MCParticle& MCParticle::operator=(const MCParticle& other)
{
  
  Particle::operator=(other);
  SetPdgId(other.PdgId());
  SetStatus(other.Status());
  SetBarCode(other.BarCode());
  SetnumMother(other.numMother());
  SetnumDaught(other.numDaught());
  SetBmotherIndex(other.BmotherIndex());
  Setmotherpdg_id(other.motherpdg_id());
  SetBmotherIndices(other.BmotherIndices());
  SetBdaughtIndices(other.BdaughtIndices());
  return *this;
}

//-------------------------------------------------------------------------
// assignment operator overloading from another MCParticle
// (non-const version)
MCParticle& MCParticle::operator=(MCParticle& other)
{
  
  Particle::operator=(other);
  SetPdgId(other.PdgId());
  SetStatus(other.Status());
  SetBarCode(other.BarCode());
  SetnumMother(other.numMother());
  SetnumDaught(other.numDaught());
  SetBmotherIndex(other.BmotherIndex());
  Setmotherpdg_id(other.motherpdg_id());
  SetBmotherIndices(other.BmotherIndices());
  SetBdaughtIndices(other.BdaughtIndices());
  return *this;
}

//-------------------------------------------------------------------------
// initialize this MCParticle from the truth tree
// 
void MCParticle::Fill(TruthTree*trtr,int iE){
  // Not in current version
  /*
  Double_t pPt  = trtr->Tru_p_T->operator[](iE)/1000.;
  Double_t pEta = trtr->Tru_eta->operator[](iE);
  Double_t pPhi = trtr->Tru_phi->operator[](iE);
  Double_t pM   = trtr->Tru_m->operator[](iE)/1000.;
  Double_t pCharge= trtr->Tru_charge->operator[](iE);
  
  _PdgId = static_cast<Int_t>(trtr->Tru_pdgId->operator[](iE));
  _Status= static_cast<Int_t>(trtr->Tru_status->operator[](iE));
  _BarCode= trtr->Tru_barcode->operator[](iE);
  SetPtEtaPhiE(pPt,pEta,pPhi,pE);
  SetCharge(pCharge);
  */
}

void MCParticle::Fill(EventTree*evtr,int iE, int& motherIndex, int& daughtIndex)
{

  // Not in current version
  /*
  Double_t pPt  = trtr->Tru_p_T->operator[](iE)/1000.;
  Double_t pEta = trtr->Tru_eta->operator[](iE);
  Double_t pPhi = trtr->Tru_phi->operator[](iE);
  Double_t pM   = trtr->Tru_m->operator[](iE)/1000.;
  Double_t pCharge= trtr->Tru_charge->operator[](iE);
  
  _PdgId = static_cast<Int_t>(trtr->Tru_pdgId->operator[](iE));
  _Status= static_cast<Int_t>(trtr->Tru_status->operator[](iE));
  _BarCode= trtr->Tru_barcode->operator[](iE);
  */

  
  Double_t pPt     = evtr-> Gen_pt->operator[](iE);
  Double_t pEta    = evtr-> Gen_eta->operator[](iE);
  Double_t pPhi    = evtr-> Gen_phi->operator[](iE);
  Double_t pE = evtr-> Gen_energy->operator[](iE);

  SetnumMother       (evtr -> Gen_numMother      -> operator[](iE));
  SetnumDaught       (evtr -> Gen_numDaught      -> operator[](iE));
  SetBmotherIndex       (evtr -> Gen_BmotherIndex      -> operator[](iE));
  Setmotherpdg_id       (evtr -> Gen_motherpdg_id      -> operator[](iE));
  SetCharge         (evtr->Gen_charge -> operator[](iE));
  
  SetPdgId          (evtr -> Gen_pdg_id      -> operator[](iE));
  SetStatus         (evtr -> Gen_status      -> operator[](iE));
  
  SetIndex       (iE);
 
  _BarCode= 0;
  
  SetPtEtaPhiE(pPt,pEta,pPhi,pE);

  for(int m_index=0; m_index< _numMother; m_index++){
    _BmotherIndices.push_back(evtr -> Gen_BmotherIndices -> operator[](motherIndex+m_index));
  }
  for(int d_index=0; d_index< _numDaught; d_index++){
    _BdaughtIndices.push_back(evtr -> Gen_BdaughtIndices -> operator[](daughtIndex+d_index));
  }

  motherIndex += _numMother;
  daughtIndex += _numDaught;

}


const MCParticle MCParticle::GetGenMotherNoFsr(const MCParticle Ptemp, std::vector<MCParticle>& MCParticles) const
{
  if (Ptemp.numMother() > 0)
    {
      const MCParticle mother = MCParticles.at(Ptemp.BmotherIndex());
      if ( Ptemp.motherpdg_id() != Ptemp.PdgId() ) return mother;
      else return GetGenMotherNoFsr(mother, MCParticles);
    }
  else 
    {
      return Ptemp;
    }
}

Bool_t MCParticle::isFromB(const MCParticle Ptemp, std::vector<MCParticle>& MCParticles, int bid) const{
  for(int m_index=0; m_index< Ptemp.BmotherIndices().size(); m_index++){
    const MCParticle mother = MCParticles.at(Ptemp.BmotherIndices().at(m_index));
    int momid = mother.AbsPdgId();
    if (momid / 1000 == bid ||  momid/100 == bid || momid == bid)return true;
    else if (mother.Status()==2 && isFromB(mother, MCParticles, bid))return true;
  }
  return false;
};

