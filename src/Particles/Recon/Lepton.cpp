/******************************************************************************
 * Lepton.cpp                                                                   *
 *                                                                            *
 * Store information about final state muons                                  *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Lepton class                                      *
 *    Lepton()                             -- Default Constructor               *
 *    Lepton()                             -- Parameterized Constructor         *
 *    Lepton()                             -- Constructor with Particle         *
 *    ~Lepton()                            -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill lepton from event tree         *
 *    FillFastSim                        -- Fill lepton from FastSim tree       *
 *    SetEtCone                          -- Set ET for EM layer 0             *
 *    GetEtCone                          -- Set ET for EM layer 0             *
 *    EtCone                             -- Set ET for EM layer 0             *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Lepton             *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Lepton class                                         *
 *    Double_t _EtCone20                     -- CAL Energy in cone around lepton*
 *    Double_t _EtCone30                     -- CAL Energy in cone around lepton*
 *                                                                            *
 * History                                                                    *
 *      21 Nov 2017 - Created by Binghuan Li                                  *
 *****************************************************************************/
#include "SingleTopRootAnalysis/Particles/Recon/Lepton.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Integrate classes into the Root system
ClassImp(Lepton)

/******************************************************************************
 * Lepton::Lepton()                                                               *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  Lepton::Lepton() : Particle::Particle(), 
  _passTightId(kFALSE), 
  _passLooseId(kFALSE),
  _isSoft     (kFALSE),
  _isHighPt   (kFALSE),
  _isPf       (kFALSE),
  _isoCharged (0.0),
  _isoSum     (0.0),
  _isoCharParPt		(0.0),
  _isoNeutralHadron	(0.0),
  _isoPhoton		(0.0),
  _isoPU		(0.0),
  _chi2			(0.0),
  _dxy			(0.0),
  _dz			(0.0),
  _validHits		(0.0),
  _validHitsInner	(0.0),
  _matchedStat		(0.0),
  _TLayers		(0.0),
  _relIsoR04		(0.0),
  _ndof			(0.0),
  _charge		(0.0),
  _IP3Dsig			(0.0),
  _miniIsoRel			(0.0),
  _jetptratio       (0.0),
  _jetcsv       (0.0),
  _lepjetchtrks       (0.0),
  _miniIsoCh       (0.0),
  _miniIsoPUsub       (0.0),
  _ptrel       (0.0),
  _jetdr       (0.0),
  _pdgId       (0.0),
  _jetpt       (0.0),
  _isGlobal       (0.0),
  _chi2LocalPosition       (0.0),
  _trkKink       (0.0),
  _validFraction       (0.0),
  _segmentCompatibility       (0.0),
  _pTErrOVpT_it       (0.0)
{

} //Lepton

/******************************************************************************
 * Lepton::~Lepton()                                                              *
 *                                                                            *
 * Destructor                                                                 *  
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Lepton::~Lepton()
{
  //cout<<"In muon destructor"<<endl;
} //~Lepton

/******************************************************************************
 * Lepton::Lepton(const Lepton& other)                                              *
 *                                                                            *
 * Copy constructor Lepton const                                                *
 *                                                                            *
 * Input:  Lepton                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Lepton::Lepton(const Lepton& other): Particle(other),
  _passTightId(other.GetpassTightId()),
  _passLooseId(other.GetpassLooseId()),
  _isSoft(other.GetisSoft()),
  _isHighPt(other.GetisHighPt()),
  _isPf(other.GetisPf()),
  _isoCharged(other.GetisoCharged()),
  _isoSum(other.GetisoSum()),
  _isoCharParPt(other.GetisoCharParPt()),
  _isoNeutralHadron(other.GetisoNeutralHadron()),
  _isoPhoton(other.GetisoPhoton()),
  _isoPU(other.GetisoPU()),
  _chi2(other.Getchi2()),
  _dxy(other.Getdxy()),
  _dz(other.Getdz()),
  _validHits(other.GetvalidHits()),
  _validHitsInner(other.GetvalidHitsInner()),
  _matchedStat(other.GetmatchedStat()),
  _TLayers(other.GetTLayers()),
  _relIsoR04(other.GetrelIsoR04()),
  _ndof(other.Getndof()),
  _charge(other.GetCharge()),
  _IP3Dsig(other.GetIP3Dsig()),
  _miniIsoRel(other.GetminiIsoRel()),
  _jetptratio(other.Getjetptratio()),
  _jetcsv(other.Getjetcsv()),
  _lepjetchtrks(other.Getlepjetchtrks()),
  _miniIsoCh(other.GetminiIsoCh()),
  _miniIsoPUsub(other.GetminiIsoPUsub()),
  _ptrel(other.Getptrel()),
  _jetdr(other.Getjetdr()),
  _pdgId(other.GetpdgId()),
  _jetpt(other.Getjetpt()),
  _isGlobal(other.GetisGlobal()),
  _chi2LocalPosition(other.Getchi2LocalPosition()),
  _trkKink(other.GettrkKink()),
  _validFraction(other.GetvalidFraction()),
  _segmentCompatibility(other.GetsegmentCompatibility()),
  _pTErrOVpT_it(other.GetpTErrOVpT_it())
			       
{
} //Lepton()

/******************************************************************************
 * Lepton::Lepton(const Lepton& other)                                              *
 *                                                                            *
 * Copy constructor Particle const                                            *
 *                                                                            *
 * Input:  Lepton                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Lepton::Lepton(const Particle& other): Particle(other),
  _passTightId(kFALSE), 
  _passLooseId(kFALSE),
  _isSoft     (kFALSE),
  _isHighPt   (kFALSE),
  _isPf       (kFALSE),
  _isoCharged (0.0),
  _isoSum     (0.0),
  _isoCharParPt		(0.0),
  _isoNeutralHadron	(0.0),
  _isoPhoton		(0.0),
  _isoPU		(0.0),
  _chi2			(0.0),
  _dxy			(0.0),
  _dz			(0.0),
  _validHits		(0.0),
  _validHitsInner	(0.0),
  _matchedStat		(0.0),
  _TLayers		(0.0),
				   _relIsoR04            (0.0),
				   _ndof (0.0),
				   _charge(0.0),
  _IP3Dsig			(0.0),
  _miniIsoRel			(0.0),
  _jetptratio       (0.0),
  _jetcsv       (0.0),
  _lepjetchtrks       (0.0),
  _miniIsoCh       (0.0),
  _miniIsoPUsub       (0.0),
  _ptrel       (0.0),
  _jetdr       (0.0),
  _pdgId       (0.0),
  _jetpt       (0.0),
  _isGlobal       (0.0),
  _chi2LocalPosition       (0.0),
  _trkKink       (0.0),
  _validFraction       (0.0),
  _segmentCompatibility       (0.0),
  _pTErrOVpT_it       (0.0)
{
} //Lepton

/******************************************************************************
 * Lepton& Lepton::operator+=(const Lepton& other)                                  *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  Lepton                                                               *
 * Output: Lepton                                                               *
 ******************************************************************************/
Lepton& Lepton::operator+=(const Lepton& other)
{
  
  Particle::operator+=(other);
  return *this;
}

/******************************************************************************
 * Lepton& Lepton::operator+(const Lepton& other)                                   *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  Lepton                                                               *
 * Output: Lepton                                                               *
 ******************************************************************************/
Lepton Lepton::operator+(const Lepton& other)
{

  Particle particleTemp = Particle::operator+(other);
  return other;
} //+

/******************************************************************************
 * Lepton& Lepton::operator=(const Lepton& other)                                   *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: Lepton                                                               *
 ******************************************************************************/
Lepton& Lepton::operator=(const Particle& other)
{
  Particle::operator=(other);
  SetpassTightId(kFALSE);
  SetpassLooseId(kFALSE);
  SetisSoft     (kFALSE);
  SetisHighPt   (kFALSE);
  SetisPf       (kFALSE);
  SetisoCharged (0.0);
  SetisoSum     (0.0);
  SetisoCharParPt	(0.0);
  SetisoNeutralHadron	(0.0);
  SetisoPhoton		(0.0);
  SetisoPU		(0.0);
  Setchi2		(0.0);
  Setdxy		(0.0);
  Setdz			(0.0);
  SetvalidHits		(0.0);
  SetvalidHitsInner	(0.0);
  SetmatchedStat	(0.0);
  SetTLayers		(0.0);
  SetrelIsoR04		(0.0);
  Setndof		(0.0);
  SetCharge		(0.0);
  SetIP3Dsig		(0.0);
  SetminiIsoRel		(0.0);
  Setjetptratio       (0.0);
  Setjetcsv       (0.0);
  Setlepjetchtrks       (0.0);
  SetminiIsoCh       (0.0);
  SetminiIsoPUsub       (0.0);
  Setptrel       (0.0);
  Setjetdr       (0.0);
  SetpdgId       (0.0);
  Setjetpt       (0.0);
  SetisGlobal       (0.0);
  Setchi2LocalPosition       (0.0);
  SettrkKink       (0.0);
  SetvalidFraction       (0.0);
  SetsegmentCompatibility       (0.0);
  SetpTErrOVpT_it       (0.0);
  return *this;
} //= Particle

/******************************************************************************
 * Lepton& Lepton::operator=(const Lepton& other)                                   *
 *                                                                            *
 * Overload = const Lepton                                                      *
 *                                                                            *
 * Input:  Lepton                                                               *
 * Output: Lepton                                                               *
 ******************************************************************************/
Lepton& Lepton::operator=(const Lepton& other)
{
  Particle::operator=(other);
  SetpassTightId(other.GetpassTightId());
  SetpassLooseId(other.GetpassLooseId());
  SetisSoft(other.GetisSoft());
  SetisHighPt(other.GetisHighPt());
  SetisPf(other.GetisPf());
  SetisoCharged(other.GetisoCharged());
  SetisoSum(other.GetisoSum());
  SetisoCharParPt(other.GetisoCharParPt());
  SetisoNeutralHadron(other.GetisoNeutralHadron());
  SetisoPhoton(other.GetisoPhoton());
  SetisoPU(other.GetisoPU());
  Setchi2(other.Getchi2());
  Setdxy(other.Getdxy());
  Setdz(other.Getdz());
  SetvalidHits(other.GetvalidHits());
  SetvalidHitsInner(other.GetvalidHitsInner());
  SetmatchedStat(other.GetmatchedStat());
  SetTLayers(other.GetTLayers());
  SetrelIsoR04(other.GetrelIsoR04());
  Setndof(other.Getndof());
  SetCharge(other.GetCharge());
  SetIP3Dsig(other.GetIP3Dsig());
  SetminiIsoRel(other.GetminiIsoRel());
  Setjetptratio(other.Getjetptratio());
  Setjetcsv(other.Getjetcsv());
  Setlepjetchtrks(other.Getlepjetchtrks());
  SetminiIsoCh(other.GetminiIsoCh());
  SetminiIsoPUsub(other.GetminiIsoPUsub());
  Setptrel(other.Getptrel());
  Setjetdr(other.Getjetdr());
  SetpdgId(other.GetpdgId());
  Setjetpt(other.Getjetpt());
  SetisGlobal(other.GetisGlobal());
  Setchi2LocalPosition(other.Getchi2LocalPosition());
  SettrkKink(other.GettrkKink());
  SetvalidFraction(other.GetvalidFraction());
  SetsegmentCompatibility(other.GetsegmentCompatibility());
  SetpTErrOVpT_it(other.GetpTErrOVpT_it());
  return *this;
} //= const muon

/******************************************************************************
 * Lepton& Lepton::operator=(const Lepton& other)                                   *
 *                                                                            *
 * Overload = non-const Lepton                                                  *
 *                                                                            *
 * Input:  Lepton                                                               *
 * Output: Lepton                                                               *
 ******************************************************************************/
Lepton& Lepton::operator=(Lepton& other)
{
  Particle::operator=(other);
  SetpassTightId(other.GetpassTightId());
  SetpassLooseId(other.GetpassLooseId());
  SetisSoft(other.GetisSoft());
  SetisHighPt(other.GetisHighPt());
  SetisPf(other.GetisPf());
  SetisoCharged(other.GetisoCharged());
  SetisoSum(other.GetisoSum());
  SetisoCharParPt(other.GetisoCharParPt());
  SetisoNeutralHadron(other.GetisoNeutralHadron());
  SetisoPhoton(other.GetisoPhoton());
  SetisoPU(other.GetisoPU());
  Setchi2(other.Getchi2());
  Setdxy(other.Getdxy());
  Setdz(other.Getdz());
  SetvalidHits(other.GetvalidHits());
  SetvalidHitsInner(other.GetvalidHitsInner());
  SetmatchedStat(other.GetmatchedStat());
  SetTLayers(other.GetTLayers());
  SetrelIsoR04(other.GetrelIsoR04());
  Setndof(other.Getndof());
  SetCharge(other.GetCharge());
  SetIP3Dsig(other.GetIP3Dsig());
  SetminiIsoRel(other.GetminiIsoRel());
  Setjetptratio(other.Getjetptratio());
  Setjetcsv(other.Getjetcsv());
  Setlepjetchtrks(other.Getlepjetchtrks());
  SetminiIsoCh(other.GetminiIsoCh());
  SetminiIsoPUsub(other.GetminiIsoPUsub());
  Setptrel(other.Getptrel());
  Setjetdr(other.Getjetdr());
  SetpdgId(other.GetpdgId());
  Setjetpt(other.Getjetpt());
  SetisGlobal(other.GetisGlobal());
  Setchi2LocalPosition(other.Getchi2LocalPosition());
  SettrkKink(other.GettrkKink());
  SetvalidFraction(other.GetvalidFraction());
  SetsegmentCompatibility(other.GetsegmentCompatibility());
  SetpTErrOVpT_it(other.GetpTErrOVpT_it());
  return *this;
} //= non-const lepton

/******************************************************************************         
 * void Lepton::SetCuts(TEnv* config, TString leptonType)                         * 
 *                                                                            *         
 * Set up the cuts for leptonType                                               *
 *                                                                            *         
 * Input:  TEnv* config, TString leptonType                                     *
 * Output: None                                                               *
 ******************************************************************************/
void Lepton::SetCuts(TEnv* config, TString leptonType)
{
  _minPtCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MinPt", 100.0);
  _maxEtaCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MaxEta", 0.0);
  _maxRelIsoCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MaxRelIso", 100.0);
  _maxDxyCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MaxDxy", 0.0);
  _maxDzCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MaxDz", 0.0);
  _maxIP3DsigCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MaxIP3Dsig", 0.0);
  _maxMiniIsoRelCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".MaxMiniIsoRel", 0.0);
  _ConePtCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".ConePtCut", 100.0);
  _BDTCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".BDTCut", 100.0);
  _jetptratioCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".jetptratioCut", 100.0);
  _SegmentCompCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".SegmentCompCut", 100.0);
  _jetcsvLCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".jetcsvLCut", 0.0);
  _jetcsvHCuts[leptonType] = config -> GetValue("ObjectID.Lepton."+leptonType+".jetcsvHCut", 0.0);

}

/******************************************************************************         
 * void Lepton::Fill(EventTree *evtr, Int_t iE)                                 *         
 *                                                                            *         
 * Fill Lepton vector from tree                                                 *         
 *                                                                            *         
 * Input:  Event Tree                                                         *         
 * Output: kTRUE if the muon passes object ID cuts                            *         
 ******************************************************************************/
Bool_t Lepton::Fill(EventTree *evtr,int iE,TString leptonType, Bool_t isSimulation, int pdgId)
{
  // **************************************************************
  // Check muon type
  // **************************************************************
  if( (leptonType != "EleLoose") && (leptonType != "EleFake") && (leptonType != "EleTight") && (leptonType != "MuLoose") && (leptonType != "MuFake") && (leptonType != "MuTight") ){
    std::cout << "ERROR: <Lepton::Fill()> " << "Passed variable leptonType of value " << leptonType << " is not valid.  "
	      << "Must be MuLoose, MuFake, MuTight, EleLoose, EleFake, EleTight " << std::endl;
  } //if
  
  Double_t lepPt;
  Double_t lepEta;  
  Double_t lepPhi;
  Double_t lepE;
  
  // **************************************************************
  // Fill muon
  // **************************************************************
  if(pdgId == 13){
    lepPt     = evtr -> Muon_pt       -> operator[](iE);
    lepEta    = evtr -> Muon_eta      -> operator[](iE);
    lepPhi    = evtr -> Muon_phi      -> operator[](iE);
    lepE      = evtr -> Muon_energy   -> operator[](iE);

    SetpassTightId	(evtr -> Muon_tight   		-> operator[](iE));
    SetpassLooseId	(evtr -> Muon_loose   		-> operator[](iE));
    SetisSoft     	(evtr -> Muon_soft    		-> operator[](iE));
    SetisHighPt   	(evtr -> Muon_isHighPt		-> operator[](iE));
    SetisPf       	(evtr -> Muon_pf      		-> operator[](iE));
    SetisoCharged 	(evtr -> Muon_isoR04Charged 	-> operator[](iE));
    SetisoSum     	(evtr -> Muon_isoSum  		-> operator[](iE));
    SetisoCharParPt	(evtr -> Muon_isoR04CharParPt  	-> operator[](iE));
    SetisoNeutralHadron	(evtr -> Muon_isoR04NeutralHadron  -> operator[](iE));
    SetisoPhoton		(evtr -> Muon_isoR04Photon   	-> operator[](iE));
    SetisoPU		(evtr -> Muon_isoR04PU   		-> operator[](iE));
    Setchi2		(evtr -> Muon_chi2   		-> operator[](iE));
    Setdxy		(evtr -> Muon_dxy_pv   		-> operator[](iE));
    Setdz			(evtr -> Muon_dz_pv   		-> operator[](iE));
    SetvalidHits		(evtr -> Muon_validHits   	-> operator[](iE));
    SetvalidHitsInner	(evtr -> Muon_validHitsInner   	-> operator[](iE));
    SetmatchedStat	(evtr -> Muon_matchedStat   	-> operator[](iE));
    SetTLayers		(evtr -> Muon_TLayers   	-> operator[](iE));
    SetrelIsoR04		(evtr -> Muon_relIsoDeltaBetaR04-> operator[](iE));
    Setndof		(evtr -> Muon_ndof		-> operator[](iE));
    SetCharge		(evtr -> Muon_charge		-> operator[](iE));
    SetminiIsoRel		(evtr -> Muon_miniIsoRel   		-> operator[](iE));
    SetIP3Dsig		(evtr -> Muon_IP3Dsig_it   		-> operator[](iE));
    Setjetptratio       (evtr -> Muon_jetptratio      -> operator[](iE));
    Setjetcsv       (evtr -> Muon_jetcsv      -> operator[](iE));
    Setlepjetchtrks       (evtr -> Muon_lepjetchtrks      -> operator[](iE));
    SetminiIsoCh       (evtr -> Muon_miniIsoCh      -> operator[](iE));
    SetminiIsoPUsub       (evtr -> Muon_miniIsoPUsub      -> operator[](iE));
    Setptrel       (evtr -> Muon_ptrel      -> operator[](iE));
    Setjetdr       (evtr -> Muon_jetdr      -> operator[](iE));
    SetpdgId       (evtr -> Muon_pdgId      -> operator[](iE));
    Setjetpt       (evtr -> Muon_jetpt      -> operator[](iE));
    SetisGlobal       (evtr -> Muon_isGlobal      -> operator[](iE));
    Setchi2LocalPosition       (evtr -> Muon_chi2LocalPosition      -> operator[](iE));
    SettrkKink       (evtr -> Muon_trkKink      -> operator[](iE));
    SetvalidFraction       (evtr -> Muon_validFraction      -> operator[](iE));
    SetsegmentCompatibility       (evtr -> Muon_segmentCompatibility      -> operator[](iE));
    SetpTErrOVpT_it       (evtr -> Muon_pTErrOVpT_it      -> operator[](iE));
    
    SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepE);
  }
  // **************************************************************
  // Isolation Cuts
  // **************************************************************
  // Get isolation requirement from config file (default is etcone30)
  //TString isoAlgoQ = "ObjectID.Muon." + leptonType + ".IsoAlgo";
  //TString isoAlgo  = config -> GetValue(isoAlgoQ, "etcone20");
  
  //// The choices for isolation are DeltaR, etcone20, etcone30, and none
  //if( "deltaR" == isoAlgo){
  //  Double_t deltaRMax = config -> GetValue("ObjectID.Muon." + leptonType + ".IsoCut", 0.4);
  //  // In case it's defined, we use the inverse muon isolation cut
  //  if(config -> Defined("ObjectID.Muon." + leptonType + ".InverseIsoCut")) {
  //    deltaRMax = config -> GetValue("ObjectID.Muon." + leptonType + ".InverseIsoCut", deltaRMax);
  //  } //if

  //  // Current Values for calculation of Delta R
  //  double DeltaRCurrent = 0;
  //  Int_t n = 0;
  //  // Iterators
  //  std::vector<Jet>::iterator JetIterator;
  //  // Jet 
  //  for(JetIterator = jets.begin(); JetIterator != jets.end(); JetIterator++){
  //    DeltaRCurrent =  JetIterator->DeltaR(*this);
  //    if(DeltaRCurrent < deltaRMax){
  //      n++; //muon is inside a jet
  //    } //if
  //  } //for
  //  
  //}//if deltaR

  //else if( "etcone20" == isoAlgo ) {
  //  Double_t conecut = config -> GetValue("ObjectID.Muon." + leptonType + ".IsoCut", 6.0);
  //}// if etcone20
  //else{
  //  std::cout << "ERROR " << "<Muon::Fill()>: " << "Insolation level " << isoAlgo
  //            << " is invalid.  Must be deltaR, etcone20, etcone30 or none."
  //            << std::endl;
  //  exit(8);
  //} //else

  // **************************************************************
  // Run 2 relative isolation cuts
  // **************************************************************

  
  // **************************************************************
  // Pt and Eta Cuts
  // **************************************************************
  // If event passes or fails requirements
  Bool_t passMinPt  = kTRUE;
  Bool_t passMaxEta = kTRUE;

  Bool_t passCustomVeto = kTRUE;
  
  Bool_t passFake = kFALSE;
  
  //parts of definition of ttH loose muon
  if (
      TMath::Abs(dxy())		>= _maxDxyCuts[leptonType] ||
      TMath::Abs(dz())		>= _maxDzCuts[leptonType] ||
      IP3Dsig()	>=  _maxIP3DsigCuts[leptonType]   ||
      miniIsoRel()	>=  _maxMiniIsoRelCuts[leptonType])
    passCustomVeto = kFALSE;

  // definition of ttH fake muon
  // this is just a test
  // ConePt and BDT needs to be calculated
  if(
     lepPt > _ConePtCuts[leptonType]
     && (
      (TMath::Abs(lepEta) > _BDTCuts[leptonType] && jetcsv() < _jetcsvHCuts[leptonType]) ||
      (TMath::Abs(lepEta) < _BDTCuts[leptonType] && jetcsv() < _jetcsvLCuts[leptonType] 
       && jetptratio() > _jetptratioCuts[leptonType] && segmentCompatibility() > _SegmentCompCuts[leptonType] )
      )
     )
     passFake = kTRUE;
  
  // Test Requirements
  if(lepPt <= _minPtCuts[leptonType])               passMinPt  = kFALSE;
  if(TMath::Abs(lepEta) >= _maxEtaCuts[leptonType]) passMaxEta = kFALSE;

  //  if(     "Tight"      == leptonType) return( passMinPt && passMaxEta  && IsTight() && Isolation() && !GetOverlapWithJet() && IsCombinedMuon());
  if(     "Tight"      == leptonType) return (passMinPt && passMaxEta  && passTightId());
  else if("MuLoose"       == leptonType) return (passMinPt && passMaxEta && passCustomVeto && passLooseId());
  else if("MuFake" == leptonType) return (passMinPt && passMaxEta  && passCustomVeto && passLooseId() && passFake); 
  //else if("Isolated"   == leptonType) return( GetIsolation()  && !GetOverlapWithJet() && IsCombinedMuon() && OverlapUse());
  //else if("UnIsolated" == leptonType) return( !GetIsolation()  && passMinPt && passMaxEta && IsTight() && !GetOverlapWithJet()&& IsCombinedMuon());
  //else if("All"        == leptonType) return( kTRUE );
  //else return kTRUE;
  return kTRUE;

} //Fill()
 
/******************************************************************************         
 * void Lepton::FillFastSim(FastSimTree *tr, Int_t iE)                          *         
 *                                                                            *         
 * Fill Lepton vector from tree                                                 *         
 *                                                                            *         
 * Input:  FastSim Tree                                                       *         
 * Output: kTRUE if the muon passes object ID cuts                            *         
 ******************************************************************************/
Bool_t Lepton::FillFastSim(TEnv *config,FastSimTree *tr,int iE,TString leptonType)
{

} //FillFastSim()


