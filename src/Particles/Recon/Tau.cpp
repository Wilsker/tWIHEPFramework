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
 * History                                                                    *
 *      14 Nov 2006 - Created by R. Schwienhorst                              *
 *      20 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      20 Mar 2007 - RS: Add filling from fastsim tree                       *
 *      11 Jan 2008 - RS: Fill only if object passes ID cuts                  *
 *****************************************************************************/
#include "SingleTopRootAnalysis/Particles/Recon/Tau.hpp"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

// Integrate classes into the Root system
ClassImp(Tau)
/******************************************************************************
 * Tau::Tau()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Tau::Tau() : Particle::Particle(),
  _charge       (0.0),
  _dz       (0.0),
  _dxy       (0.0),
  _isLoose       (0.0),
  _isMedium       (0.0),
  _rawMVA       (0.0),
  _decayModeFinding       (0.0),
  _NumTracks(0.0)
{

} //Tau()

/******************************************************************************
 * Tau::~Tau()                                                              *
 *                                                                            *
 * Destructor                                                                 *  
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Tau::~Tau()
{

} //~Tau()


/******************************************************************************
 * Tau::Tau(const Tau& other)                                              *
 *                                                                            *
 * Copy constructor Tau const                                                *
 *                                                                            *
 * Input:  Tau                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Tau::Tau(const Tau& other): Particle(other),
  _charge(other.Getcharge()),
  _dz(other.Getdz()),
  _dxy(other.Getdxy()),
  _isLoose(other.GetisLoose()),
  _isMedium(other.GetisMedium()),
  _rawMVA(other.GetrawMVA()),
  _decayModeFinding(other.GetdecayModeFinding()),
  _NumTracks(other.GetNumTracks())
{

} //Tau()

/******************************************************************************
 * Tau::Tau(const Tau& other)                                                 *
 *                                                                            *
 * Copy constructor Particle const                                            *
 *                                                                            *
 * Input:  Tau                                                                *
 * Output: None                                                               *
 ******************************************************************************/
Tau::Tau(const Particle& other): Particle(other),
  _charge       (0.0),
  _dz       (0.0),
  _dxy       (0.0),
  _isLoose       (0.0),
  _isMedium       (0.0),
  _rawMVA       (0.0),
  _decayModeFinding       (0.0),
  _NumTracks(0.0)
{

} //Tau() particle

/******************************************************************************
 * Tau& Tau::operator+=(const Tau& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  Tau                                                                *
 * Output: Tau                                                                *
 ******************************************************************************/
Tau& Tau::operator+=(const Tau& other)
{
  Particle::operator+=(other);
  // Also add NumTracks
  SetNumTracks(GetNumTracks() + other.GetNumTracks());
  return *this;
} //+=

/******************************************************************************
 * Tau& Tau::operator+(const Tau& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  Tau                                                                *
 * Output: Tau                                                                *
 ******************************************************************************/
Tau Tau::operator+(const Tau& other)
{

  Particle particleTemp = Particle::operator+(other);
  Tau tauTemp = particleTemp;
  
  // I don't know how to add the NumTracks for two different taus.
  // For now, add them
  _NumTracks += other.GetNumTracks();
  tauTemp.SetNumTracks( _NumTracks );

  // Return the temp particle
  return tauTemp;
} //+

/******************************************************************************
 * Tau& Tau::operator=(const Particle& other)                                 *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: Tau                                                                *
 ******************************************************************************/
Tau& Tau::operator=(const Particle& other)
{
  Particle::operator=(other);
  Setcharge       (0.0);
  Setdz       (0.0);
  Setdxy       (0.0);
  SetisLoose       (0.0);
  SetisMedium       (0.0);
  SetrawMVA       (0.0);
  SetdecayModeFinding       (0.0);
  SetNumTracks(0.0);
  return *this;
} // = Particle

/******************************************************************************
 * Tau& Tau::operator=(const Tau& other)                                      *
 *                                                                            *
 * Overload = const Tau                                                       *
 *                                                                            *
 * Input:  Tau                                                                *
 * Output: Tau                                                                *
 ******************************************************************************/
Tau& Tau::operator=(const Tau& other)
{
  
  Particle::operator=(other);
  Setcharge(other.Getcharge());
  Setdz(other.Getdz());
  Setdxy(other.Getdxy());
  SetisLoose(other.GetisLoose());
  SetisMedium(other.GetisMedium());
  SetrawMVA(other.GetrawMVA());
  SetdecayModeFinding(other.GetdecayModeFinding());
  SetNumTracks(other.GetNumTracks());
  return *this;
} //= const tau

/******************************************************************************
 * Tau& Tau::operator=(const Tau& other)                                      *
 *                                                                            *
 * Overload = non-const Tau                                                   *
 *                                                                            *
 * Input:  Tau                                                                *
 * Output: Tau                                                                *
 ******************************************************************************/
Tau& Tau::operator=(Tau& other)
{
  
  Particle::operator=(other);
  Setcharge(other.Getcharge());
  Setdz(other.Getdz());
  Setdxy(other.Getdxy());
  SetisLoose(other.GetisLoose());
  SetisMedium(other.GetisMedium());
  SetrawMVA(other.GetrawMVA());
  SetdecayModeFinding(other.GetdecayModeFinding());
  SetNumTracks(other.GetNumTracks());
  return *this;
} //= tau non-const

/******************************************************************************         
 * void Tau::SetCuts(TEnv* config)                                            * 
 *                                                                            *         
 * Set up the cuts                                                            *
 *                                                                            *         
 * Input:  TEnv* config                                                       *
 * Output: None                                                               *
 ******************************************************************************/
void Tau::SetCuts(TEnv* config)
{
  _closestLeptonCut = config -> GetValue("ObjectID.Tau.LeptonCleanR",0.);
  _maxEtaCut=config->GetValue("ObjectID.Tau.MaxEta",100.);
  _minPtCut=config->GetValue("ObjectID.Tau.MinPt",0.);
  _maxDxyCut=config->GetValue("ObjectID.Tau.MaxDxy",10000.);
  _maxDzCut=config->GetValue("ObjectID.Tau.MaxDz",10000.);
}

/******************************************************************************         
 * void Tau::Fill(EventTree *evtr, Int_t iE)                                  *         
 *                                                                            *         
 * Fill Tau vector from tree                                                  *         
 *                                                                            *         
 * Input:  Event Tree                                                         *         
 * Output: kTRUE if object passes ID cuts                                     *         
 ******************************************************************************/
Bool_t Tau::Fill(std::vector<Lepton>& selectedLeptons, EventTree *evtr,int iE, TString tauType)
{
  // **************************************************************
  // Check Tau type
  // **************************************************************
  if( (tauType != "Loose") && (tauType != "Medium")){
    std::cout << "ERROR: <Tau::Fill()> " << "Passed variable tauType of value " << tauType << " is not valid.  "
	      << "Must be Loose, Medium " << std::endl;
  } //if
    Double_t tauPt     = evtr -> Tau_pt       -> operator[](iE) ;
    Double_t tauEta    = evtr -> Tau_eta      -> operator[](iE);
    Double_t tauPhi    = evtr -> Tau_phi      -> operator[](iE);
    Double_t tauE      = evtr -> Tau_energy       -> operator[](iE);
    _NumTracks         = 0.;
    Double_t tauCharge = evtr -> Tau_charge   -> operator[](iE);
    Setdz       (evtr -> Tau_packedLeadTauCand_dz      -> operator[](iE));
    Setdxy       (evtr -> Tau_packedLeadTauCand_dxy      -> operator[](iE));
    SetisLoose       (evtr -> Tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017      -> operator[](iE));
    SetisMedium       (evtr -> Tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017      -> operator[](iE));
    SetrawMVA      (evtr  -> Tau_byIsolationMVArun2017v2DBoldDMdR0p3wLTraw2017     -> operator[](iE));
    SetdecayModeFinding       (evtr -> Tau_decayModeFinding      -> operator[](iE));

    SetPtEtaPhiE(tauPt, tauEta, tauPhi, tauE);
    Setcharge(tauCharge);
    //

    ////////////////////////////////
    /// Lepton Cleaning
    ////////////////////////////////
  
    Bool_t passesCleaning = kTRUE;
 
    Double_t closestLepton = 999.;

    for (auto const & lep : selectedLeptons){
        if (lep.DeltaR(*this) < closestLepton) closestLepton = lep.DeltaR(*this);
    }
    if (closestLepton < _closestLeptonCut) passesCleaning = kFALSE;
  
    Bool_t passeCommonCuts = kFALSE;
    if(tauPt > _minPtCut 
        && TMath::Abs(tauEta)< _maxEtaCut 
        && TMath::Abs(dz())<= _maxDzCut
        && TMath::Abs(dxy())<= _maxDxyCut
        && decayModeFinding()) passeCommonCuts = kTRUE;

    //std::cout <<tauPt << " > pt 20? "<<tauEta<< " < eta 2.3? " << dxy() << " < 1000?  " << dz() << " < 0.2 ? " << decayModeFinding() << " " <<isMedium() << " ispassCommonCuts?: "<< passeCommonCuts << " isLoose()?: " << isLoose()<< " isMedium()?: "<< isMedium()<< std::endl;
    if(     "Loose"      == tauType) return (passesCleaning && passeCommonCuts && isLoose());
    else if(     "Medium"      == tauType) return (passesCleaning && passeCommonCuts && isMedium());

    return kTRUE;
} //Fill()

/******************************************************************************         
 * void Tau::FillFastSim(FastSimTree *evtr, Int_t iE)                         *         
 *                                                                            *         
 * Fill Tau vector from tree                                                  *         
 *                                                                            *         
 * Input:  FastSim Tree                                                       *         
 * Output: kTRUE if object passes ID cuts                                     *         
 ******************************************************************************/
Bool_t Tau::FillFastSim(FastSimTree *tr,int iE,TEnv* config)
{

    /*
    Double_t tauPt     = tr -> Tau_pt      -> operator[](iE) ;
    Double_t tauEta    = tr -> Tau_eta      -> operator[](iE);
    Double_t tauPhi    = tr -> Tau_phi      -> operator[](iE);
    Double_t tauE      = tr -> Tau_energy        -> operator[](iE);
    _NumTracks         = 0; // not available in fast sim
    Double_t tauCharge = tr -> Tau_charge   -> operator[](iE);

    SetPtEtaPhiE(tauPt, tauEta, tauPhi, tauE);
    Setcharge(tauCharge);
    //
    // now check electron object ID cuts
    double maxEta=config->GetValue("ObjectID.Tau.MaxEta",100.);
    double minPt=config->GetValue("ObjectID.Tau.MinPt",0.);

    if(tauPt<minPt) return kFALSE;
    if(TMath::Abs(tauEta)>maxEta) return kFALSE;
    */
    return kTRUE;
} //FillFastSim()


