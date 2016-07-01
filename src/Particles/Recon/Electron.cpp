/******************************************************************************
 * Electron.hpp                                                               *
 *                                                                            *
 * Store information about final state electrons                              *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Electron class                                  *
 *    Electron()                         -- Default Constructor               *
 *    Electron()                         -- Parameterized Constructor         *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill electron from event tree     *
 *    FillFastSim                        -- Fill electron from FastSim tree   *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Electron         *
 *    operator =                         -- Overload =                        *
 *                                                                            *
 * Private Data Members of Electron class                                     *
 *                                                                            *
 * History                                                                    *
 *      16 June 2015 - Created by Huaqiao ZHANG                               *
 *****************************************************************************/
#include "SingleTopRootAnalysis/Particles/Recon/Electron.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Integrate classes into the Root system
ClassImp(Electron)


/******************************************************************************
 * Electon::Electron()                                                        *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  Electron::Electron() : Particle::Particle(),_passVetoId(0), _passLooseId(0), _passMediumId(0), _passTightId(0), _passHEEPId(0), _passConversionVeto(0), _expectedMissingInnerHits(0), _patElectron_d0(0.0),  _patElectron_dz(0.0),  _isoChargedHadrons(0.0),  _isoNeutralHadrons(0.0), _isoPhotons(0.0),  _isoPU(0.0)
{
} //Electron()

/******************************************************************************
 * Electon::~Electron()                                                       *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Electron::~Electron()
{

} //~Electron


/******************************************************************************
 * Electon::Electron(const Electron& other)                                   *
 *                                                                            *
 * Copy constructor Electron const                                            *
 *                                                                            *
 * Input:  Electron                                                           *
 * Output: None                                                               *
 ******************************************************************************/
Electron::Electron(const Electron& other): Particle(other),
_passVetoId(other.GetpassVetoId()), 
_passLooseId(other.GetpassLooseId()), 
_passMediumId(other.GetpassMediumId()), 
_passTightId(other.GetpassTightId()), 
_passHEEPId(other.GetpassHEEPId()), 
_passConversionVeto(other.GetpassConversionVeto()), 
_expectedMissingInnerHits(other.GetexpectedMissingInnerHits()), 
_patElectron_d0(other.GetpatElectron_d0()), 
_patElectron_dz(other.GetpatElectron_dz()), 
_isoChargedHadrons(other.GetisoChargedHadrons()), 
_isoNeutralHadrons(other.GetisoNeutralHadrons()), 
_isoPhotons(other.GetisoPhotons()), 
_isoPU(other.GetisoPU())
{
} //Electron()

/******************************************************************************
 * Electon::Electron(const Particle& other)                                   *
 *                                                                            *
 * Copy constructor Particle const                                            *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: None                                                               *
 ******************************************************************************/
  Electron::Electron(const Particle& other) : Particle(other),_passVetoId(0), _passLooseId(0), _passMediumId(0), _passTightId(0), _passHEEPId(0), _passConversionVeto(0), _expectedMissingInnerHits(0), _patElectron_d0(0.0),  _patElectron_dz(0.0),  _isoChargedHadrons(0.0),  _isoNeutralHadrons(0.0), _isoPhotons(0.0),  _isoPU(0.0)
{ 
} //Electron()


/******************************************************************************
 * Electron& Electron::operator+=(const Electron& other)                      *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  Electron                                                           *
 * Output: Electron                                                           *
 ******************************************************************************/
Electron& Electron::operator+=(const Electron& other)
{
  
  Particle::operator+=(other);
  return *this;
} //Electron +=

/******************************************************************************
 * Electron& Electron::operator+(const Electron& other)                       *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  Electron                                                           *
 * Output: Electron                                                           *
 ******************************************************************************/
Electron Electron::operator+(const Electron& other)
{

  Particle particleTemp = Particle::operator+(other);
  Electron electronTemp = particleTemp;
  return electronTemp;

} //+

/******************************************************************************
 * Electron& Electron::operator=(const Electron& other)                       *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Electron                                                           *
 * Output: Electron                                                           *
 ******************************************************************************/
Electron& Electron::operator=(const Particle& other)
{
  
  Particle::operator = (other);
  SetpassVetoId(0.0);
  SetpassLooseId(0.0);
  SetpassMediumId(0.0);
  SetpassTightId(0.0);
  SetpassHEEPId(0.0);
  SetpassConversionVeto(0.0);
  SetexpectedMissingInnerHits(0.0);
  SetpatElectron_d0(0.0);
  SetpatElectron_dz(0.0);
  SetisoChargedHadrons(0.0);
  SetisoNeutralHadrons(0.0);
  SetisoPhotons(0.0);
  SetisoPU(0.0);

  return *this;
} // = Particle

/******************************************************************************
 * Electron& Electron::operator+(const Electron& other)                       *
 *                                                                            *
 * Overload = for const Electron                                              *
 *                                                                            *
 * Input:  Electron                                                           *
 * Output: Electron                                                           *
 ******************************************************************************/
Electron& Electron::operator=(const Electron& other)
{
  
  Particle::operator=(other);
  SetpassVetoId(other.GetpassVetoId());
  SetpassLooseId(other.GetpassLooseId());
  SetpassMediumId(other.GetpassMediumId());
  SetpassTightId(other.GetpassTightId());
  SetpassHEEPId(other.GetpassHEEPId());
  SetpassConversionVeto(other.GetpassConversionVeto());
  SetexpectedMissingInnerHits(other.GetexpectedMissingInnerHits());
  SetpatElectron_d0(other.GetpatElectron_d0());
  SetpatElectron_dz(other.GetpatElectron_dz());
  SetisoChargedHadrons(other.GetisoChargedHadrons());
  SetisoNeutralHadrons(other.GetisoNeutralHadrons());
  SetisoPhotons(other.GetisoPhotons());
  SetisoPU(other.GetisoPU());
  return *this;
} //= const Electron

/******************************************************************************
 * Electron& Electron::operator+(const Electron& other)                       *
 *                                                                            *
 * Overload = for non-const Electron                                          *
 *                                                                            *
 * Input:  Electron                                                           *
 * Output: Electron                                                           *
 ******************************************************************************/
Electron& Electron::operator=(Electron& other)
{
  
  Particle::operator=(other);
  SetpassVetoId(other.GetpassVetoId());
  SetpassLooseId(other.GetpassLooseId());
  SetpassMediumId(other.GetpassMediumId());
  SetpassTightId(other.GetpassTightId());
  SetpassHEEPId(other.GetpassHEEPId());
  SetpassConversionVeto(other.GetpassConversionVeto());
  SetexpectedMissingInnerHits(other.GetexpectedMissingInnerHits());
  SetpatElectron_d0(other.GetpatElectron_d0());
  SetpatElectron_dz(other.GetpatElectron_dz());
  SetisoChargedHadrons(other.GetisoChargedHadrons());
  SetisoNeutralHadrons(other.GetisoNeutralHadrons());
  SetisoPhotons(other.GetisoPhotons());
  SetisoPU(other.GetisoPU());
  return *this;
} //= non-const Electron

/******************************************************************************
 * void Electron::SetCuts(TEnv* config, TString electron)                     *
 *                                                                            *
 * Set up the cuts to be made on the different types of electron              *
 *                                                                            *
 * Input:  config with cuts                                                   *
 *         string of what type of electron, Veto, Tight etc                   *
 * Output: kTRUE if this electron passes electron ID cuts                     *
 ******************************************************************************/
void Electron::SetCuts(TEnv* config, TString electronType)
{
  _maxEtaCuts[electronType] =    config -> GetValue("ObjectID.Electron." + electronType + ".MaxEta", 100.);
  _minPtCuts[electronType] =   	 config -> GetValue("ObjectID.Electron." + electronType + ".MinPt", 0.);
  _minEtaGapCuts[electronType] = config -> GetValue("ObjectID.Electron." + electronType + ".MinEtaGap", 100.);
  _maxEtaGapCuts[electronType] = config -> GetValue("ObjectID.Electron." + electronType + ".MaxEtaGap", -100.);


} // End SetCuts


/******************************************************************************
 * void Electron::Fill(EventTree *evtr,int iE)                                *
 *                                                                            *
 * Fill electron vector from tree                                             *
 *                                                                            *
 * Input:  Event Tree                                                         *
 * Output: kTRUE if this electron passes electron ID cuts                     *
 ******************************************************************************/
Bool_t Electron::Fill(EventTree *evtr, Int_t iE, TString electronType, Bool_t isSimulation)
{

  // **************************************************************
  // Check electron type
  // **************************************************************
  if( (electronType != "All") && (electronType != "Veto") && (electronType != "Tight") && (electronType != "Isolated") && (electronType != "UnIsolated") && (electronType != "PtEtaCut") ){
    std::cout << "ERROR: <Electron::Fill()> " << "Passed variable electronType of value " << electronType << " is not valid.  "
	      << "Must be All, Veto, Tight, Isolated, UnIsolated, PtEtaCut" << std::endl;
  } 

  // ******************************  Set up electron candidate ********************************
  Double_t elPt        = evtr -> patElectron_pt     -> operator[](iE);
  Double_t elEta       = evtr -> patElectron_eta    -> operator[](iE);
  Double_t elPhi       = evtr -> patElectron_phi    -> operator[](iE);
  Double_t elE         = evtr -> patElectron_energy -> operator[](iE);

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  SetPtEtaPhiE(elPt, elEta, elPhi, elE);

  SetCharge             ( evtr -> patElectron_charge              -> operator[](iE) );
  SetpassVetoId         ( evtr -> patElectron_isPassVeto          -> operator[](iE) );
  SetpassLooseId        ( evtr -> patElectron_isPassLoose         -> operator[](iE) );
  SetpassMediumId       ( evtr -> patElectron_isPassMedium        -> operator[](iE) );
  SetpassTightId        ( evtr -> patElectron_isPassTight         -> operator[](iE) );
  SetpassHEEPId         ( evtr -> patElectron_isPassHEEPId        -> operator[](iE) );
  SetpassConversionVeto ( evtr -> patElectron_passConversionVeto  -> operator[](iE) );
  SetisoChargedHadrons  ( evtr -> patElectron_isoChargedHadrons   -> operator[](iE) );
  SetisoNeutralHadrons  ( evtr -> patElectron_isoNeutralHadrons   -> operator[](iE) );
  SetisoPhotons         ( evtr -> patElectron_isoPhotons          -> operator[](iE) );
  SetisoPU              ( evtr -> patElectron_isoPU               -> operator[](iE) );

  // **************************************************************
  // **************************************************************
  // **************************************************************
  // Calcualte Minimum DeltaR between Electron and Jet
  //Double_t DeltaRCurrent = 0;
  //std::vector<Jet>::iterator JetIterator;
  //for(JetIterator = jets.begin(); JetIterator != jets.end(); JetIterator++){
  //  DeltaRCurrent =  JetIterator->DeltaR(*this);
  //  if( (GetDeltaRElectronJet() == 0) || (DeltaRCurrent < GetDeltaRElectronJet()) ) SetDeltaRElectronJet(DeltaRCurrent); 
  //} //for


  // Get isolation requirement from config file (default is etcone20)
  //  TString isoAlgoQ = "ObjectID.Electron." + electronType + ".IsoAlgo";
  //TString isoAlgo  = config -> GetValue(isoAlgoQ, "ptetcone30");
/*  
  // The only choices for isolation are currently etcone20 and none
  if( "etcone20" == isoAlgo ) {
    Double_t coneCut = config -> GetValue("ObjectID.Electron." + electronType + ".IsoCut", 6.0);
    if(_EtCone20 < coneCut) SetIsolation(kTRUE); // electron isolated  
    //      if( coneCut < _EtCone20 ) SetIsolation(kTRUE); // electron isolated // old
    else SetIsolation(kFALSE);
  }// if etcone20
  else if( "etcone30" == isoAlgo ) {
    Double_t coneCut = config -> GetValue("ObjectID.Electron." + electronType + ".IsoCut", 6.0);
    if(_EtCone30 < coneCut) SetIsolation(kTRUE); // electron isolated  
    //      if( coneCut < _EtCone20 ) SetIsolation(kTRUE); // electron isolated // old
    else SetIsolation(kFALSE);
    cout<<"ARE YOU SURE YOU DON'T WANT THE PTCONE, ETCONE ISOLATION, ptetcone?"<<endl;
  }// if etcone30
  else if( "ptetcone30" == isoAlgo ) {
    Double_t conecut1 = config -> GetValue("ObjectID.Electron." + electronType + ".IsoCutEt", 0.0);
    Double_t conecut2 = config -> GetValue("ObjectID.Electron." + electronType + ".IsoCutPt", 0.0);
    if(((_EtCone30/elPt) < conecut1) &&((_PtCone30/elPt) < conecut2)) SetIsolation(kTRUE); // electron isolated  
    else SetIsolation(kFALSE);
  }// if ptetcone30
  else if("none" == isoAlgo) SetIsolation(kTRUE);
  else{
    std::cout << "ERROR " << "<Electron::Fill()>: " << "Insolation level " << isoAlgo
	      << " is invalid.  Must be etcone20, etcone30, or none."
	      << std::endl;
    exit(8);
  } //else
*/ 
  // **************************************************************
  // Pt and Eta Cuts
  // **************************************************************
  // If event passes or fails requirements
  Bool_t passMinPt  = kTRUE;
  Bool_t passMaxEta = kTRUE;
  
  // Test requirements
  if(elPt <= _minPtCuts[electronType])               passMinPt  = kFALSE;
  if(TMath::Abs(elEta) >= _maxEtaCuts[electronType]) passMaxEta = kFALSE;
  
  // **************************************************************
  // Gap Electrons
  // **************************************************************
  // If event passes or fails requirements
  Bool_t passNoGapElectron  = kTRUE;
  
  // Test requirements and set variable
  if( (TMath::Abs(elEta) >= _minEtaGapCuts[electronType]) && (TMath::Abs(elEta) <= _maxEtaGapCuts[electronType]) ) passNoGapElectron = kFALSE;
  //SetNoGapElectron(passNoGapElectron);
  
  // **************************************************************
  // Return value according to electron type passed to Fill
  // **************************************************************
  //if(     "Tight"      == electronType) return(GetIsRobusterTight() && passMinPt && passMaxEta && GetNoGapElectron() && Isolation());
  if(     "Tight"      == electronType) return( passMinPt && passMaxEta);
  //if(     "PtEtaCut"   == electronType) return(passMinPt && passMaxEta && IsRobusterTight());
  else if("Veto"       == electronType) return( passMinPt && passMaxEta);//no tight or isolation req.
  //else if("Isolated"   == electronType) return(GetIsolation()  && GetNoGapElectron()&& OverlapUse());
  //else if("UnIsolated" == electronType) return(!GetIsolation() && GetIsRobusterTight() && passMinPt && passMaxEta && GetNoGapElectron());
  //else if("All"        == electronType) return(kTRUE);
  //else return kTRUE;
  return kTRUE;
  
} //Fill

/******************************************************************************
 * void Electron::FillFastSim(FastSimTree *evtr,int iE)                       *
 *                                                                            *
 * Fill electron vector from tree                                             *
 *                                                                            *
 * Input:  FastSim Tree                                                       *
 * Output: kTRUE if this electron passes electron ID cuts                     *
 ******************************************************************************/
Bool_t Electron::FillFastSim(FastSimTree *tr, Int_t iE,TEnv* config,TString electronType)
{
} //FillFastSim


