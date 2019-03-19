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
  _passMediumId(kFALSE),
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
  _jetptratioV2       (0.0),
  _jetcsv       (0.0),
  _jetdeepcsv       (0.0),
  _jetdeepflavour       (0.0),
  _lepjetchtrks       (0.0),
  _miniIsoCh       (0.0),
  _miniIsoPUsub       (0.0),
  _ptrel       (0.0),
  _relIsoRhoEA       (0.0),
  _jetdr       (0.0),
  _jetl1corr       (0.0),
  _jetislep       (0.0),
  _jetidx       (0),
  _pdgId       (0.0),
  _jetpt       (0.0),
  _isGlobal       (0.0),
  _chi2LocalPosition       (0.0),
  _trkKink       (0.0),
  _validFraction       (0.0),
  _segmentCompatibility       (0.0),
  _BDT       (0.0),
  _conept       (0.0),
  _isGsfCtfScPixChargeConsistent       (0.0),
  _isGsfScPixChargeConsistent       (0.0),
  _passConversionVeto       (0.0),
  _passTightCharge       (0.0),
  _passMissHit       (0.0),
  _isTight       (0.0),
  _isMVASel       (0.0),
  _ntMVAeleID       (0.0),
  _isPassMvanonIsowpLoose       (0.0),
  _isFake       (0.0),
  _pTErrOVpT_bt       (0.0),
  _SCeta       (0.0),
  _expectedMissingInnerHits       (0.0),
  _full5x5_sigmaIetaIeta       (0.0),
  _hOverE       (0.0),
  _dEtaIn       (0.0),
  _dPhiIn       (0.0),
  _ooEmooP       (0.0),
  _gen_pt       (0.0),
  _gen_eta       (0.0),
  _gen_phi       (0.0),
  _gen_en       (0.0),
  _gen_pdgId       (0.0),
  _gen_isPrompt       (0.0),
  _gen_isPromptTau       (0.0),
  _genMother_pdgId       (0.0),
  _genGrandMother_pdgId       (0.0),
  _matchId       (0.0),
  _matchIndex       (0.0),
  _isFromTop       (0.0),
  _isFromH       (0.0),
  _matchMother_Id       (0.0),
  _matchGrandMother_Id       (0.0),
  _matchMother_Index       (0.0),
  _matchGrandMother_Index       (0.0),
  _isFromB       (0.0),
  _isFromC       (0.0),
  _mcPromptGamma       (0.0),
  _mvaValue_nonIso       (0.0),
  _mvaValue_HZZ       (0.0)
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
  _passMediumId(other.GetpassMediumId()),
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
  _jetptratioV2(other.GetjetptratioV2()),
  _jetcsv(other.Getjetcsv()),
  _jetdeepcsv(other.Getjetdeepcsv()),
  _jetdeepflavour(other.Getjetdeepflavour()),
  _lepjetchtrks(other.Getlepjetchtrks()),
  _miniIsoCh(other.GetminiIsoCh()),
  _miniIsoPUsub(other.GetminiIsoPUsub()),
  _ptrel(other.Getptrel()),
  _relIsoRhoEA(other.GetrelIsoRhoEA()),
  _jetdr(other.Getjetdr()),
  _jetl1corr(other.Getjetl1corr()),
  _jetislep(other.Getjetislep()),
  _jetidx(other.Getjetidx()),
  _pdgId(other.GetpdgId()),
  _jetpt(other.Getjetpt()),
  _isGlobal(other.GetisGlobal()),
  _chi2LocalPosition(other.Getchi2LocalPosition()),
  _trkKink(other.GettrkKink()),
  _validFraction(other.GetvalidFraction()),
  _segmentCompatibility(other.GetsegmentCompatibility()),
  _BDT(other.GetBDT()),
  _conept(other.Getconept()),
  _isGsfCtfScPixChargeConsistent(other.GetisGsfCtfScPixChargeConsistent()),
  _isGsfScPixChargeConsistent(other.GetisGsfScPixChargeConsistent()),
  _passConversionVeto(other.GetpassConversionVeto()),
  _passTightCharge(other.GetpassTightCharge()),
  _passMissHit(other.GetpassMissHit()),
  _isTight(other.GetisTight()),
  _isMVASel(other.GetisMVASel()),
  _ntMVAeleID(other.GetntMVAeleID()),
  _isPassMvanonIsowpLoose(other.GetisPassMvanonIsowpLoose()),
  _isFake(other.GetisFake()),
  _SCeta(other.GetSCeta()),
  _expectedMissingInnerHits(other.GetexpectedMissingInnerHits()),
  _full5x5_sigmaIetaIeta(other.Getfull5x5_sigmaIetaIeta()),
  _hOverE(other.GethOverE()),
  _dEtaIn(other.GetdEtaIn()),
  _dPhiIn(other.GetdPhiIn()),
  _ooEmooP(other.GetooEmooP()),
  _mvaValue_HZZ(other.GetmvaValue_HZZ()),
  _mvaValue_nonIso(other.GetmvaValue_nonIso()),
  _gen_pt(other.Getgen_pt()),
  _gen_eta(other.Getgen_eta()),
  _gen_phi(other.Getgen_phi()),
  _gen_en(other.Getgen_en()),
  _gen_pdgId(other.Getgen_pdgId()),
  _gen_isPrompt(other.Getgen_isPrompt()),
  _gen_isPromptTau(other.Getgen_isPromptTau()),
  _genMother_pdgId(other.GetgenMother_pdgId()),
  _genGrandMother_pdgId(other.GetgenGrandMother_pdgId()),
  _matchId(other.GetmatchId()),
  _matchIndex(other.GetmatchIndex()),
  _isFromTop(other.GetisFromTop()),
  _isFromH(other.GetisFromH()),
  _matchMother_Id(other.GetmatchMother_Id()),
  _matchGrandMother_Id(other.GetmatchGrandMother_Id()),
  _matchMother_Index(other.GetmatchMother_Index()),
  _matchGrandMother_Index(other.GetmatchGrandMother_Index()),
  _isFromB(other.GetisFromB()),
  _isFromC(other.GetisFromC()),
  _mcPromptGamma(other.GetmcPromptGamma()),
  _pTErrOVpT_bt(other.GetpTErrOVpT_bt())
			       
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
  _passMediumId(kFALSE),
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
  _jetptratioV2       (0.0),
  _jetcsv       (0.0),
  _jetdeepcsv       (0.0),
  _jetdeepflavour       (0.0),
  _lepjetchtrks       (0.0),
  _miniIsoCh       (0.0),
  _miniIsoPUsub       (0.0),
  _ptrel       (0.0),
  _relIsoRhoEA       (0.0),
  _jetdr       (0.0),
  _jetl1corr       (0.0),
  _jetislep       (0.0),
  _jetidx       (0),
  _pdgId       (0.0),
  _jetpt       (0.0),
  _isGlobal       (0.0),
  _chi2LocalPosition       (0.0),
  _trkKink       (0.0),
  _validFraction       (0.0),
  _segmentCompatibility       (0.0),
  _BDT       (0.0),
  _conept       (0.0),
  _isGsfCtfScPixChargeConsistent       (0.0),
  _isGsfScPixChargeConsistent       (0.0),
  _passConversionVeto       (0.0),
  _passTightCharge       (0.0),
  _passMissHit       (0.0),
  _isTight       (0.0),
  _isMVASel       (0.0),
  _ntMVAeleID       (0.0),
  _isPassMvanonIsowpLoose       (0.0),
  _isFake       (0.0),
  _SCeta       (0.0),
  _expectedMissingInnerHits       (0.0),
  _full5x5_sigmaIetaIeta       (0.0),
  _hOverE       (0.0),
  _dEtaIn       (0.0),
  _dPhiIn       (0.0),
  _ooEmooP       (0.0),
  _mvaValue_HZZ       (0.0),
  _mvaValue_nonIso       (0.0),
  _gen_pt       (0.0),
  _gen_eta       (0.0),
  _gen_phi       (0.0),
  _gen_en       (0.0),
  _gen_pdgId       (0.0),
  _gen_isPrompt       (0.0),
  _gen_isPromptTau       (0.0),
  _genMother_pdgId       (0.0),
  _genGrandMother_pdgId       (0.0),
  _matchId       (0.0),
  _matchIndex       (0.0),
  _isFromTop       (0.0),
  _isFromH       (0.0),
  _matchMother_Id       (0.0),
  _matchGrandMother_Id       (0.0),
  _matchMother_Index       (0.0),
  _matchGrandMother_Index       (0.0),
  _isFromB       (0.0),
  _isFromC       (0.0),
  _mcPromptGamma       (0.0),
  _pTErrOVpT_bt       (0.0)
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
  SetpassMediumId(kFALSE);
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
  SetjetptratioV2       (0.0);
  Setjetcsv       (0.0);
  Setjetdeepcsv       (0.0);
  Setjetdeepflavour       (0.0);
  Setlepjetchtrks       (0.0);
  SetminiIsoCh       (0.0);
  SetminiIsoPUsub       (0.0);
  Setptrel       (0.0);
  SetrelIsoRhoEA       (0.0);
  Setjetdr       (0.0);
  Setjetl1corr       (0.0);
  Setjetislep       (0.0);
  Setjetidx       (0);
  SetpdgId       (0.0);
  Setjetpt       (0.0);
  SetisGlobal       (0.0);
  Setchi2LocalPosition       (0.0);
  SettrkKink       (0.0);
  SetvalidFraction       (0.0);
  SetsegmentCompatibility       (0.0);
  SetBDT       (0.0);
  Setconept       (0.0);
  SetisGsfCtfScPixChargeConsistent       (0.0);
  SetisGsfScPixChargeConsistent       (0.0);
  SetpassConversionVeto       (0.0);
  SetpassTightCharge       (0.0);
  SetpassMissHit       (0.0);
  SetisTight       (0.0);
  SetisMVASel       (0.0);
  SetntMVAeleID       (0.0);
  SetisPassMvanonIsowpLoose       (0.0);
  SetisFake       (0.0);
  SetpTErrOVpT_bt       (0.0);
  SetSCeta       (0.0);
  SetexpectedMissingInnerHits       (0.0);
  Setfull5x5_sigmaIetaIeta       (0.0);
  SethOverE       (0.0);
  SetdEtaIn       (0.0);
  SetdPhiIn       (0.0);
  SetooEmooP       (0.0);
  Setgen_pt       (0.0);
  Setgen_eta       (0.0);
  Setgen_phi       (0.0);
  Setgen_en       (0.0);
  Setgen_pdgId       (0.0);
  Setgen_isPrompt       (0.0);
  Setgen_isPromptTau       (0.0);
  SetgenMother_pdgId       (0.0);
  SetgenGrandMother_pdgId       (0.0);
  SetmatchId       (0.0);
  SetmatchIndex       (0.0);
  SetisFromTop       (0.0);
  SetisFromH       (0.0);
  SetmatchMother_Id       (0.0);
  SetmatchGrandMother_Id       (0.0);
  SetmatchMother_Index       (0.0);
  SetmatchGrandMother_Index       (0.0);
  SetisFromB       (0.0);
  SetisFromC       (0.0);
  SetmcPromptGamma       (0.0);
  SetmvaValue_HZZ       (0.0);
  SetmvaValue_nonIso       (0.0);
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
  SetpassMediumId(other.GetpassMediumId());
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
  SetjetptratioV2(other.GetjetptratioV2());
  Setjetcsv(other.Getjetcsv());
  Setjetdeepcsv(other.Getjetdeepcsv());
  Setjetdeepflavour(other.Getjetdeepflavour());
  Setlepjetchtrks(other.Getlepjetchtrks());
  SetminiIsoCh(other.GetminiIsoCh());
  SetminiIsoPUsub(other.GetminiIsoPUsub());
  Setptrel(other.Getptrel());
  SetrelIsoRhoEA(other.GetrelIsoRhoEA());
  Setjetdr(other.Getjetdr());
  Setjetl1corr(other.Getjetl1corr());
  Setjetislep(other.Getjetislep());
  Setjetidx(other.Getjetidx());
  SetpdgId(other.GetpdgId());
  Setjetpt(other.Getjetpt());
  SetisGlobal(other.GetisGlobal());
  Setchi2LocalPosition(other.Getchi2LocalPosition());
  SettrkKink(other.GettrkKink());
  SetvalidFraction(other.GetvalidFraction());
  SetsegmentCompatibility(other.GetsegmentCompatibility());
  SetBDT(other.GetBDT());
  Setconept(other.Getconept());
  SetisGsfCtfScPixChargeConsistent(other.GetisGsfCtfScPixChargeConsistent());
  SetisGsfScPixChargeConsistent(other.GetisGsfScPixChargeConsistent());
  SetpassConversionVeto(other.GetpassConversionVeto());
  SetpassTightCharge(other.GetpassTightCharge());
  SetpassMissHit(other.GetpassMissHit());
  SetisTight(other.GetisTight());
  SetisMVASel(other.GetisMVASel());
  SetntMVAeleID(other.GetntMVAeleID());
  SetisPassMvanonIsowpLoose(other.GetisPassMvanonIsowpLoose());
  SetisFake(other.GetisFake());
  SetpTErrOVpT_bt(other.GetpTErrOVpT_bt());
  SetSCeta(other.GetSCeta());
  SetexpectedMissingInnerHits(other.GetexpectedMissingInnerHits());
  Setfull5x5_sigmaIetaIeta(other.Getfull5x5_sigmaIetaIeta());
  SethOverE(other.GethOverE());
  SetdEtaIn(other.GetdEtaIn());
  SetdPhiIn(other.GetdPhiIn());
  SetooEmooP(other.GetooEmooP());
  Setgen_pt(other.Getgen_pt());
  Setgen_eta(other.Getgen_eta());
  Setgen_phi(other.Getgen_phi());
  Setgen_en(other.Getgen_en());
  Setgen_pdgId(other.Getgen_pdgId());
  Setgen_isPrompt(other.Getgen_isPrompt());
  Setgen_isPromptTau(other.Getgen_isPromptTau());
  SetgenMother_pdgId(other.GetgenMother_pdgId());
  SetgenGrandMother_pdgId(other.GetgenGrandMother_pdgId());
  SetmatchId(other.GetmatchId());
  SetmatchIndex(other.GetmatchIndex());
  SetisFromTop(other.GetisFromTop());
  SetisFromH(other.GetisFromH());
  SetmatchMother_Id(other.GetmatchMother_Id());
  SetmatchGrandMother_Id(other.GetmatchGrandMother_Id());
  SetmatchMother_Index(other.GetmatchMother_Index());
  SetmatchGrandMother_Index(other.GetmatchGrandMother_Index());
  SetisFromB(other.GetisFromB());
  SetisFromC(other.GetisFromC());
  SetmcPromptGamma(other.GetmcPromptGamma());
  SetmvaValue_HZZ(other.GetmvaValue_HZZ());
  SetmvaValue_nonIso(other.GetmvaValue_nonIso());
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
  SetpassMediumId(other.GetpassMediumId());
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
  SetjetptratioV2(other.GetjetptratioV2());
  Setjetcsv(other.Getjetcsv());
  Setjetdeepcsv(other.Getjetdeepcsv());
  Setjetdeepflavour(other.Getjetdeepflavour());
  Setlepjetchtrks(other.Getlepjetchtrks());
  SetminiIsoCh(other.GetminiIsoCh());
  SetminiIsoPUsub(other.GetminiIsoPUsub());
  Setptrel(other.Getptrel());
  SetrelIsoRhoEA(other.GetrelIsoRhoEA());
  Setjetdr(other.Getjetdr());
  Setjetl1corr(other.Getjetl1corr());
  Setjetislep(other.Getjetislep());
  Setjetidx(other.Getjetidx());
  SetpdgId(other.GetpdgId());
  Setjetpt(other.Getjetpt());
  SetisGlobal(other.GetisGlobal());
  Setchi2LocalPosition(other.Getchi2LocalPosition());
  SettrkKink(other.GettrkKink());
  SetvalidFraction(other.GetvalidFraction());
  SetsegmentCompatibility(other.GetsegmentCompatibility());
  SetBDT(other.GetBDT());
  Setconept(other.Getconept());
  SetisGsfCtfScPixChargeConsistent(other.GetisGsfCtfScPixChargeConsistent());
  SetisGsfScPixChargeConsistent(other.GetisGsfScPixChargeConsistent());
  SetpassConversionVeto(other.GetpassConversionVeto());
  SetpassTightCharge(other.GetpassTightCharge());
  SetpassMissHit(other.GetpassMissHit());
  SetisTight(other.GetisTight());
  SetisMVASel(other.GetisMVASel());
  SetntMVAeleID(other.GetntMVAeleID());
  SetisPassMvanonIsowpLoose(other.GetisPassMvanonIsowpLoose());
  SetisFake(other.GetisFake());
  SetpTErrOVpT_bt(other.GetpTErrOVpT_bt());
  SetSCeta(other.GetSCeta());
  SetexpectedMissingInnerHits(other.GetexpectedMissingInnerHits());
  Setfull5x5_sigmaIetaIeta(other.Getfull5x5_sigmaIetaIeta());
  SethOverE(other.GethOverE());
  SetdEtaIn(other.GetdEtaIn());
  SetdPhiIn(other.GetdPhiIn());
  SetooEmooP(other.GetooEmooP());
  Setgen_pt(other.Getgen_pt());
  Setgen_eta(other.Getgen_eta());
  Setgen_phi(other.Getgen_phi());
  Setgen_en(other.Getgen_en());
  Setgen_pdgId(other.Getgen_pdgId());
  Setgen_isPrompt(other.Getgen_isPrompt());
  Setgen_isPromptTau(other.Getgen_isPromptTau());
  SetgenMother_pdgId(other.GetgenMother_pdgId());
  SetgenGrandMother_pdgId(other.GetgenGrandMother_pdgId());
  SetmatchId(other.GetmatchId());
  SetmatchIndex(other.GetmatchIndex());
  SetisFromTop(other.GetisFromTop());
  SetisFromH(other.GetisFromH());
  SetmatchMother_Id(other.GetmatchMother_Id());
  SetmatchGrandMother_Id(other.GetmatchGrandMother_Id());
  SetmatchMother_Index(other.GetmatchMother_Index());
  SetmatchGrandMother_Index(other.GetmatchGrandMother_Index());
  SetisFromB(other.GetisFromB());
  SetisFromC(other.GetisFromC());
  SetmcPromptGamma(other.GetmcPromptGamma());
  SetmvaValue_HZZ(other.GetmvaValue_HZZ());
  SetmvaValue_nonIso(other.GetmvaValue_nonIso());
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
  _dataEra = config -> GetValue("DataEra",2017);
  _closestMuonCut = config -> GetValue("ObjectID.Electron.MuonCleanR",0.);
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

/***************************************************************
 * void Lepton Lepton::set_lepMVAreader()                       *
 *                                                              * 
 * Set up the MVA xml file                                      *
 *                                                              *
 * Input: TEnv* config                                          *
 * Output: None                                                 *
 * **************************************************************/
 
void Lepton::set_lepMVAreader(TEnv* config)
{
    mu_reader_ = new TMVA::Reader("!Color:!Silent");
    ele_reader_ = new TMVA::Reader("!Color:!Silent");
    std::vector<TMVA::Reader *> mvas = { ele_reader_, mu_reader_ };
    if(_dataEra==2017){
      for (auto &m : mvas) {
        m->AddVariable("LepGood_pt", &varpt);
        m->AddVariable("LepGood_eta", &vareta);
        m->AddVariable("LepGood_jetNDauChargedMVASel", &varjetNDauCharged_in);
        m->AddVariable("LepGood_miniRelIsoCharged", &varchRelIso);
        m->AddVariable("LepGood_miniRelIsoNeutral", &varneuRelIso);
        m->AddVariable("LepGood_jetPtRelv2", &varjetPtRel_in);
        m->AddVariable("LepGood_jetBTagCSV := max(LepGood_jetBTagCSV,0)", &varjetBTagCSV_in);
        m->AddVariable("LepGood_jetPtRatiov2 := (LepGood_jetBTagCSV>-5)*min(LepGood_jetPtRatiov2,1.5)+(LepGood_jetBTagCSV<-5)/(1+LepGood_relIso04)", &varjetPtRatio_in);
        m->AddVariable("LepGood_sip3d", &varsip3d);
        m->AddVariable("LepGood_dxy := log(abs(LepGood_dxy))", &vardxy);
        m->AddVariable("LepGood_dz := log(abs(LepGood_dz))", &vardz);
      }
      ele_reader_->AddVariable("LepGood_mvaIdFall17noIso", &varmvaId);
      mu_reader_->AddVariable("LepGood_segmentCompatibility", &varSegCompat);
    }else if(_dataEra==2016){
      for (auto &m : mvas) {
        m->AddVariable("LepGood_pt", &varpt);
        m->AddVariable("LepGood_eta", &vareta);
        m->AddVariable("LepGood_jetNDauChargedMVASel", &varjetNDauCharged_in);
        m->AddVariable("LepGood_miniRelIsoCharged", &varchRelIso);
        m->AddVariable("LepGood_miniRelIsoNeutral", &varneuRelIso);
        m->AddVariable("LepGood_jetPtRelv2", &varjetPtRel_in);
        m->AddVariable("LepGood_jetPtRatiov2 := min(LepGood_jetPtRatiov2,1.5)", &varjetPtRatio_in);
        m->AddVariable("LepGood_jetBTagCSV := max(LepGood_jetBTagCSV,0)", &varjetBTagCSV_in);
        m->AddVariable("LepGood_sip3d", &varsip3d);
        m->AddVariable("LepGood_dxy := log(abs(LepGood_dxy))", &vardxy);
        m->AddVariable("LepGood_dz := log(abs(LepGood_dz))", &vardz);
      }
      ele_reader_->AddVariable("LepGood_mvaIdSpring16HZZ", &varmvaId);
      mu_reader_->AddVariable("LepGood_segmentCompatibility", &varSegCompat);
    }else{
        std::cout<< " ERROR dataEra in lepton mva reading "<<std::endl;
    }
    ele_reader_->BookMVA("BDTG method",config -> GetValue("Include.ElectronMVAFile","null")); 
    mu_reader_->BookMVA("BDTG method",config -> GetValue("Include.MuonMVAFile","null")); 
}

/***************************************************************
 * double Lepton Lepton::get_LeptonMVA()                *
 *                                                              * 
 * Read the lepton MVA value                                      *
 *                                                              *
 * Input: None                                          *
 * Output: lepton MVA value                                     *
 * **************************************************************/
 
double Lepton::get_LeptonMVA(int EventNumber)
{
    varpt = unCorrPt();
    vareta = Eta();
    varchRelIso = miniIsoCh(); // It's already setted to be miniIsoCh/Pt
    varneuRelIso = miniIsoPUsub(); // It's already setted to be miniIsoPUsub/Pt
    varjetPtRel_in = ptrel();
    varjetPtRatio_in = min(jetptratioV2(),1.5);
    varjetBTagCSV_in = max(jetcsv(),0.); 
    varjetNDauCharged_in =lepjetchtrks(); 
    varsip3d = IP3Dsig();
    vardxy = log(TMath::Abs(dxy())); 
    vardz =  log(TMath::Abs(dz())); 
    varSegCompat = segmentCompatibility(); 
    if(_dataEra==2016){
        varmvaId = mvaValue_HZZ();
    }else{
        varmvaId = mvaValue_nonIso();
    }
    if(EventNumber == 13579661 ){
        std::cout << " varpt "<< varpt<< " vareta "<< vareta << " varchRelIso " << varchRelIso << " varneuRelIso " << varneuRelIso << " varjetPtRel " << varjetPtRel_in <<" varjetptRatio_in"<< varjetPtRatio_in <<" varjetBTagCSV_in " << varjetBTagCSV_in << " varjetNDauCharged_in " << varjetNDauCharged_in  <<" varsip3d "<< varsip3d << " vardxy "<< vardxy << " vardz " << vardz<<" varSegCompa "<< varSegCompat << " varmvaId "<< varmvaId << std::endl;
    }
    if( TMath::Abs(pdgId()) == 13) return mu_reader_->EvaluateMVA("BDTG method");
    else if( TMath::Abs(pdgId()) == 11) return ele_reader_->EvaluateMVA("BDTG method");
    else{
        std::cout<< "ERROR: Lepton::get_LeptonMVA "<<"Passed lepton pdgId is not valid "<<std::endl;
        return -1.;
    }
}



/******************************************************************************         
 * void Lepton::Fill(EventTree *evtr, Int_t iE)                                 *         
 *                                                                            *         
 * Fill Lepton vector from tree                                                 *         
 *                                                                            *         
 * Input:  Event Tree                                                         *         
 * Output: kTRUE if the muon passes object ID cuts                            *         
 ******************************************************************************/
Bool_t Lepton::Fill(std::vector<Muon>& selectedMuons,  std::vector<Jet>& lepAwareJets, EventTree *evtr,int iE,TString leptonType, Bool_t isSimulation, int sNumber ,int pdgid)
{
   //std::cout << "Debug: <Lepton::Fill()>  Read Leptons from Tree : Just Enter Lepton::Fill " << std::endl;
  // **************************************************************
  // Check lepton type
  // **************************************************************
  if( (leptonType != "EleLoose") && (leptonType != "EleFake") && (leptonType != "EleTight") && (leptonType != "MuLoose") && (leptonType != "MuFake") && (leptonType != "MuTight") ){
    std::cout << "ERROR: <Lepton::Fill()> " << "Passed variable leptonType of value " << leptonType << " is not valid.  "
	      << "Must be MuLoose, MuFake, MuTight, EleLoose, EleFake, EleTight " << std::endl;
  } //if
  int eventNumber = evtr -> EVENT_event; 
  Double_t lepPt;
  Double_t lepEta;  
  Double_t lepPhi;
  Double_t lepE;
  
  // **************************************************************
  // Fill muon
  // **************************************************************
  if(pdgid == 13){
   // std::cout << "Debug: <Lepton::Fill()>  Read Muon from Tree : Just Before 4Momentum Fill " << std::endl;
    lepPt     = evtr -> Muon_pt       -> operator[](iE);
    lepEta    = evtr -> Muon_eta      -> operator[](iE);
    lepPhi    = evtr -> Muon_phi      -> operator[](iE);
    lepE      = evtr -> Muon_energy   -> operator[](iE);
    
    //std::cout << "Debug: <Lepton::Fill()>  Read Muon from Tree : Just after 4Momentum Fill " << std::endl;

    SetpassTightId	(evtr -> Muon_tight   		-> operator[](iE));
    SetpassLooseId	(evtr -> Muon_loose   		-> operator[](iE));
    SetpassMediumId	(evtr -> Muon_medium   		-> operator[](iE));
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
    Setdxy		(evtr -> Muon_dxy_bt   		-> operator[](iE));
    Setdz			(evtr -> Muon_dz_bt   		-> operator[](iE));
    SetunCorrPt			(evtr -> Muon_pt   		-> operator[](iE));
    //std::cout << "Debug: <Lepton::Fill()>  Read Muon from Tree : Just after Muon_dz Fill " << std::endl;
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
    Setjetdeepcsv       (evtr -> Muon_jetdeepcsv      -> operator[](iE));
    Setjetdeepflavour       (evtr -> Muon_jetdeepflavour      -> operator[](iE));
    //std::cout << "Debug: <Lepton::Fill()>  Read Muon from Tree : Just after Muon_jetcsv Fill " << std::endl;
    Setlepjetchtrks       (evtr -> Muon_lepjetchtrks      -> operator[](iE));
    SetminiIsoCh       (evtr -> Muon_miniIsoCh      -> operator[](iE)/evtr -> Muon_pt      -> operator[](iE));
    SetminiIsoPUsub       (evtr -> Muon_miniIsoPUsub      -> operator[](iE)/evtr -> Muon_pt      -> operator[](iE));
    Setptrel       (evtr -> Muon_ptrel      -> operator[](iE));
    SetjetptratioV2       (evtr -> Muon_jetptratioV2      -> operator[](iE));
    Setjetdr       (evtr -> Muon_jetdr      -> operator[](iE));
    Setjetl1corr       (evtr -> Muon_jetl1corr      -> operator[](iE));
    Setjetislep       (evtr -> Muon_jetislep      -> operator[](iE));
    Setjetidx       (evtr -> Muon_jetidx      -> operator[](iE));
    SetpdgId       (evtr -> Muon_pdgId      -> operator[](iE));
    Setjetpt       (evtr -> Muon_jetpt      -> operator[](iE));
    SetisGlobal       (evtr -> Muon_isGlobal      -> operator[](iE));
    Setchi2LocalPosition       (evtr -> Muon_chi2LocalPosition      -> operator[](iE));
    SettrkKink       (evtr -> Muon_trkKink      -> operator[](iE));
    SetvalidFraction       (evtr -> Muon_validFraction      -> operator[](iE));
    SetsegmentCompatibility       (evtr -> Muon_segmentCompatibility      -> operator[](iE));
    SetpTErrOVpT_bt       (evtr -> Muon_pTErrOVpT_bt      -> operator[](iE));
//    std::cout << "Debug: <Lepton::Fill()>  Read Muon from Tree : Just Before Muon_gen_pt Fill " << std::endl;
    if(isSimulation){
        Setgen_pt       (evtr -> Muon_gen_pt      -> operator[](iE));
        Setgen_eta       (evtr -> Muon_gen_eta      -> operator[](iE));
        Setgen_phi       (evtr -> Muon_gen_phi      -> operator[](iE));
        Setgen_en       (evtr -> Muon_gen_en      -> operator[](iE));
        Setgen_pdgId       (evtr -> Muon_gen_pdgId      -> operator[](iE));
        Setgen_isPrompt       (evtr -> Muon_gen_isPromptFinalState      -> operator[](iE));
        Setgen_isPromptTau       (evtr -> Muon_gen_isDirectPromptTauDecayProductFinalState      -> operator[](iE));
    }else{
        Setgen_pt       (-999.);
        Setgen_eta       (-999.);
        Setgen_phi       (-999.);
        Setgen_en       (-999.);
        Setgen_pdgId       (-999.);
        Setgen_isPrompt       (-999.);
        Setgen_isPromptTau       (-999.);
    }
    //SetgenMother_pdgId       (evtr -> Muon_genMother_pdgId      -> operator[](iE));
    //SetgenGrandMother_pdgId       (evtr -> Muon_genGrandMother_pdgId      -> operator[](iE));
    SetgenMother_pdgId       (-999.);
    SetgenGrandMother_pdgId       (-999.);
    SetmatchId       (-999.);
    SetmatchIndex       (-999.);
    SetisFromTop       (-999.);
    SetisFromH       (-999.);
    SetmatchMother_Id       (-999.);
    SetmatchGrandMother_Id       (-999.);
    SetmatchMother_Index       (-999.);
    SetmatchGrandMother_Index       (-999.);
    SetisFromB       (-999);
    SetisFromC       (-999);
    SetmcPromptGamma       (0.);
    SetpassConversionVeto       (1.);
  }

  // **************************************************************
  // Fill electron
  // **************************************************************
  if(pdgid == 11){
//    std::cout << "Debug: <Lepton::Fill()>  Read Electron from Tree : Just Before 4Momentum Fill " << std::endl;
    lepEta    = evtr -> patElectron_eta      -> operator[](iE);
    lepPhi    = evtr -> patElectron_phi      -> operator[](iE);
    // currently MC is not reMiniAOD, data is reMiniAOD
    // for MC , the pt is already smear and scaled
    // for Data , the pt is not scaled and smeared yet
    // this needs to be updated when new samples comes
    //if(isSimulation){
        lepPt        = evtr -> patElectron_pt     -> operator[](iE) * evtr -> patElectron_energySF -> operator[](iE);
        lepE         = evtr -> patElectron_energy     -> operator[](iE) * evtr -> patElectron_energySF -> operator[](iE);
    /*
    }else{
    }
    */
//   
//    std::cout << "Debug: <Lepton::Fill()>  Read Electron from Tree : Just Before 4Momentum Fill " << std::endl;
    SetCharge       (evtr -> patElectron_charge      -> operator[](iE));
    SetIP3Dsig       (evtr -> patElectron_IP3Dsig      -> operator[](iE));
    SetminiIsoRel       (evtr -> patElectron_miniIsoRel      -> operator[](iE));
    SetpdgId       (evtr -> patElectron_pdgId      -> operator[](iE));
    Setdxy       (evtr -> patElectron_gsfTrack_dxy_pv      -> operator[](iE));
    Setdz       (evtr -> patElectron_gsfTrack_dz_pv      -> operator[](iE));
    SetunCorrPt       (evtr -> patElectron_pt      -> operator[](iE));
//    std::cout << "Debug: <Lepton::Fill()>  Read Electron from Tree : Just after Electron_dz Fill " << std::endl;
    Setjetptratio       (evtr -> patElectron_jetptratio      -> operator[](iE));
    SetrelIsoR04		(evtr -> patElectron_relIsoDeltaBeta-> operator[](iE));
    SetrelIsoRhoEA       (evtr -> patElectron_relIsoRhoEA      -> operator[](iE));
    Setjetcsv       (evtr -> patElectron_jetcsv      -> operator[](iE));
    Setjetdeepcsv       (evtr -> patElectron_jetdeepcsv      -> operator[](iE));
    Setjetdeepflavour       (evtr -> patElectron_jetdeepflavour      -> operator[](iE));
//    std::cout << "Debug: <Lepton::Fill()>  Read Electron from Tree : Just after Electron_jetcsv Fill " << std::endl;
    Setlepjetchtrks       (evtr -> patElectron_lepjetchtrks      -> operator[](iE));
    SetminiIsoCh       (evtr -> patElectron_miniIsoCh      -> operator[](iE)/evtr -> patElectron_pt     -> operator[](iE));
    SetminiIsoPUsub       (evtr -> patElectron_miniIsoPUsub      -> operator[](iE)/evtr -> patElectron_pt     -> operator[](iE));
    Setptrel       (evtr -> patElectron_ptrel      -> operator[](iE));
    SetjetptratioV2       (evtr -> patElectron_jetptratioV2      -> operator[](iE));
    Setjetdr       (evtr -> patElectron_jetdr      -> operator[](iE));
    Setjetl1corr       (evtr -> patElectron_jetl1corr      -> operator[](iE));
    Setjetislep       (evtr -> patElectron_jetislep      -> operator[](iE));
    Setjetidx       (evtr -> patElectron_jetidx      -> operator[](iE));
    Setjetpt       (evtr -> patElectron_jetpt      -> operator[](iE));
    SetSCeta       (evtr -> patElectron_SCeta      -> operator[](iE));
    SetexpectedMissingInnerHits       (evtr -> patElectron_expectedMissingInnerHits      -> operator[](iE));
    Setfull5x5_sigmaIetaIeta       (evtr -> patElectron_full5x5_sigmaIetaIeta      -> operator[](iE));
    SethOverE       (evtr -> patElectron_hOverE      -> operator[](iE));
    SetdEtaIn       (evtr -> patElectron_dEtaIn      -> operator[](iE));
    SetdPhiIn       (evtr -> patElectron_dPhiIn      -> operator[](iE));
    SetooEmooP       (evtr -> patElectron_ooEmooP      -> operator[](iE));
    SetmvaValue_HZZ       (evtr -> patElectron_mvaValue_HZZ      -> operator[](iE));
    // This is Fall17V2 IDs 
    SetisPassMvanonIsowpLoose		(evtr -> patElectron_isPassMvanonIsowpLoose   		-> operator[](iE));
    SetmvaValue_nonIso       (evtr -> patElectron_mvaValue_nonIso      -> operator[](iE));
    SetntMVAeleID		(evtr -> patElectron_mvaValue_nonIso   		-> operator[](iE));
    // This is Fall17V1 IDs 
    /*
    SetisPassMvanonIsowpLoose		(evtr -> patElectron_isPassOldMvanonIsowpLoose   		-> operator[](iE));
    SetmvaValue_nonIso       (evtr -> patElectron_OldmvaValue_nonIso      -> operator[](iE));
    SetntMVAeleID		(evtr -> patElectron_OldmvaValue_nonIso   		-> operator[](iE));
    */
    SetisGsfCtfScPixChargeConsistent       (evtr -> patElectron_isGsfCtfScPixChargeConsistent      -> operator[](iE));
    SetisGsfScPixChargeConsistent       (evtr -> patElectron_isGsfScPixChargeConsistent      -> operator[](iE));
//    std::cout << "Debug: <Lepton::Fill()>  Read Electron from Tree : Just Before Electron_gen_pt Fill " << std::endl;
    if(isSimulation){
        Setgen_pt       (evtr -> patElectron_gen_pt      -> operator[](iE));
        Setgen_eta       (evtr -> patElectron_gen_eta      -> operator[](iE));
        Setgen_phi       (evtr -> patElectron_gen_phi      -> operator[](iE));
        Setgen_en       (evtr -> patElectron_gen_en      -> operator[](iE));
        Setgen_pdgId       (evtr -> patElectron_gen_pdgId      -> operator[](iE));
        Setgen_isPrompt       (evtr -> patElectron_gen_isPromptFinalState      -> operator[](iE));
        Setgen_isPromptTau       (evtr -> patElectron_gen_isDirectPromptTauDecayProductFinalState      -> operator[](iE));
    }else{
        Setgen_pt       (-999.);
        Setgen_eta       (-999.);
        Setgen_phi       (-999.);
        Setgen_en       (-999.);
        Setgen_pdgId       (-999.);
        Setgen_isPrompt       (-999.);
        Setgen_isPromptTau       (-999.);
    }
    //SetgenMother_pdgId       (evtr -> patElectron_genMother_pdgId      -> operator[](iE));
    //SetgenGrandMother_pdgId       (evtr -> patElectron_genGrandMother_pdgId      -> operator[](iE));
    SetgenMother_pdgId       (-999.);
    SetgenGrandMother_pdgId       (-999.);
    SetmatchId       (-999.);
    SetmatchIndex       (-999.);
    SetisFromTop       (-999.);
    SetisFromH       (-999.);
    SetmatchMother_Id       (-999.);
    SetmatchGrandMother_Id       (-999.);
    SetmatchMother_Index       (-999.);
    SetmatchGrandMother_Index       (-999.);
    SetisFromB       (-999);
    SetisFromC       (-999);
    SetmcPromptGamma       (-999);
    SetpassConversionVeto       (evtr -> patElectron_passConversionVeto      -> operator[](iE));
  }
  SetPtEtaPhiE(lepPt, lepEta, lepPhi, lepE);

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
  // Run 2 lep-jet related variables 
  // **************************************************************
  /*
  Jet lepJet;
  Double_t closestJet = 999.; // please keep this to 999, because if closest jet is not found, jetdr() == 999
  for (auto const & jet : lepAwareJets){
    //if( eventNumber==13583222 ){
    //    std::cout<< " lepJet pt "<< jet.Pt()<< " lepJet eta" << jet.Eta()<< " lepJet phi "<< jet.Phi()<< " lepJet E "<< jet.E() << " deltaR " << jet.DeltaR(*this) << " closetDR "<< closestJet << std::endl; 
    //} 
    //jet idx can be wrong because the jet is sorted by raw pt in miniAOD
    if(fabs(jet.DeltaR(*this) - jetdr())<closestJet){ // should be enough, because jet is ak4
        closestJet = fabs(jet.DeltaR(*this) - jetdr());
        lepJet = jet;
    }
  }
  Double_t lepptratio = 1.; 
  Double_t lepptrel = 0.; 
  if(lepJet.Pt()==0.){
    if(TMath::Abs(pdgId())==11)lepptratio = min(Pt()/(1+relIsoRhoEA()),1.5);
    if(TMath::Abs(pdgId())==13)lepptratio = min(Pt()/(1+relIsoR04()),1.5);
  }else{
    Double_t L1Factor = jetl1corr();
    TLorentzVector UncorrJet={0,0,0,0};
    UncorrJet.SetPtEtaPhiE(lepJet.uncorrPt(),lepJet.Eta(),lepJet.Phi(),lepJet.uncorrE());
    TLorentzVector thelepton={0,0,0,0};
    thelepton.SetPtEtaPhiE(Pt(),Eta(),Phi(),E());
    TLorentzVector lep_jet={0,0,0,0};
    lep_jet = (UncorrJet - thelepton*(1.0/L1Factor))*(lepJet.Pt()/lepJet.uncorrPt())+thelepton;
    TLorentzVector lep_lv    = TLorentzVector(Px(),Py(),Pz(),E());
    TLorentzVector lepjet_lv = TLorentzVector(lep_jet.Px(),lep_jet.Py(),lep_jet.Pz(),lep_jet.E());
    lepptrel = lep_jet.Perp((lep_jet-thelepton).Vect());
    lepptratio = min(Pt()/lep_jet.Pt(), 1.5);
    //lepptrel = lep_lv.Perp((lepjet_lv).Vect());
    //lepptrel = lep_lv.Perp((lepjet_lv-lep_lv).Vect());
    //if( eventNumber==13583222 ){
    //    std::cout<<" lepPt "<< Pt()<<" lepEta "<<Eta()<<" JetPt "<< lepJet.Pt() <<" JetUncorrPt "<< lepJet.uncorrPt() << " JetE "<<lepJet.E()<<" JetUncorrE "<<lepJet.uncorrE()<<" ptratio " << lepptratio<<" ptrel "<< lepptrel<< " L1 Factor "<< L1Factor<< " L1L2L3 "<< lepJet.Pt()/lepJet.uncorrPt()<<" lep_jet.Pt " <<lep_jet.Pt()<<" lep_jet.Px "<< lep_jet.Px()<<" lep_jet.Py "<<lep_jet.Py()<<" lep_jet.Pz "<<lepJet.Pz()<<" lep_jet.E "<<lep_jet.E() <<std::endl;
    //}
  }
  */
  if(jetislep()>0.5){ // set to default if jet is matched to lepton
    SetjetptratioV2(1);
    Setptrel(0);
    Setlepjetchtrks(0);
  }else if(jetidx()>=0){ // recalculate ptratio and ptrel for JesSF && ele Scale & Smear purpose and only for the case where jet is found
    SetjetptratioV2(jetptratio());
  }

  // **************************************************************
  // Pt and Eta Cuts
  // **************************************************************
  // If event passes or fails requirements
  Bool_t passMinPt  = kTRUE;
  Bool_t passMaxEta = kTRUE;

  Bool_t passCustomVeto = kTRUE;
  
  Bool_t passFake = kFALSE;
  Bool_t passTight = kFALSE;
  
  ////////////////////////////////
  /// Electron Cleaning
  ////////////////////////////////
  
  Bool_t passesCleaning = kTRUE;
 
  Double_t closestMuon = 999.;

  for (auto const & mu : selectedMuons){
    if (mu.DeltaR(*this) < closestMuon && pdgid == 11) closestMuon = mu.DeltaR(*this);
  }
  if (closestMuon < _closestMuonCut) passesCleaning = kFALSE;
  
  //parts of definition of ttH loose leptons
  if (
      !passesCleaning || TMath::Abs(expectedMissingInnerHits()) > 1 ||
      TMath::Abs(dxy())		>= _maxDxyCuts[leptonType] ||
      TMath::Abs(dz())		>= _maxDzCuts[leptonType] ||
      IP3Dsig()	>=  _maxIP3DsigCuts[leptonType]   ||
      miniIsoRel()	>=  _maxMiniIsoRelCuts[leptonType]
      ) 
    passCustomVeto = kFALSE;

  // definition of ttH fake lepton
  // isMedium_ST
  /*
  Bool_t ishipsave = sNumber < 210000; // data period GH (sNumber>21000) is not hipsave 
  Bool_t GoodGlobal = (isGlobal()==1 && chi2() <3 && chi2LocalPosition() < 12 && trkKink() < 20);
  Bool_t isMedium = TMath::Abs(pdgId())==11 || (passLooseId() ==1 && validFraction() > (ishipsave? 0.49 : 0.80) && segmentCompatibility() > ( GoodGlobal? 0.303 : 0.451));
  */
  Bool_t isMedium = TMath::Abs(pdgId())==11 || passMediumId();
  // calculate lepton BDT
  SetBDT(get_LeptonMVA(eventNumber));
  /*
  if(eventNumber == 13579745){
    std::cout << " nEvent " <<eventNumber << " LepGood_pt "<<  varpt << " LepGood_eta " << vareta << " LepGood_jetNDauChargedMVASel "<< varjetNDauCharged_in << " LepGood_miniRelIsoCharged "<< varchRelIso << " LepGood_miniRelIsoNeutral "<< varneuRelIso << " LepGood_jetPtRelv2 "<< varjetPtRel_in << " LepGood_jetBTagCSV " << varjetBTagCSV_in << " LepGood_jetPtRatiov2 " << varjetPtRatio_in << " LepGood_sip3d "<< varsip3d << " LepGood_dxy " << vardxy << " LepGood_dz " << vardz<< " LepGood_mvaIdFall17noIso "<< varmvaId << " LepGood_segmentCompatibility "<< varSegCompat << " output MVA "<< BDT() <<std::endl; 
  }
  */
  // calculate conept
  Setconept((isMedium && BDT() > 0.9) ?  lepPt : 0.9 * lepPt / jetptratioV2());
  // calculate lepton tight selections
  SetpassTightCharge   ((pdgid==13 && TMath::Abs(pTErrOVpT_bt())<0.2)||(pdgid==11 && (isGsfCtfScPixChargeConsistent() + isGsfScPixChargeConsistent()) >1));
  SetpassMissHit       ((pdgid==13)||(expectedMissingInnerHits()==0 && pdgid ==11));
  
  /*
  if(lepPt <=10){
    if((TMath::Abs(SCeta()) <0.8 && mvaValue_nonIso() > -0.13285867293779202)||
          (0.8 <= TMath::Abs(SCeta()) && TMath::Abs(SCeta()) <1.479 && mvaValue_nonIso() > -0.31765300958836074)||
        (1.479 <=TMath::Abs(SCeta()) && TMath::Abs(SCeta())<500 && mvaValue_nonIso()>-0.0799205914718861)
    ) eleMVAId = kTRUE;
  }else{
    if((TMath::Abs(SCeta()) <0.8 && mvaValue_nonIso() > -0.856871961305474 )||
          (0.8 <= TMath::Abs(SCeta()) && TMath::Abs(SCeta()) <1.479 && mvaValue_nonIso() > -0.8107642141584835)||
        (1.479 <=TMath::Abs(SCeta()) && TMath::Abs(SCeta())<500 && mvaValue_nonIso()> -0.7179265933023059)
    ) eleMVAId = kTRUE;
  }
  */
    Bool_t passCuts = kFALSE;
    /*
    if (TMath::Abs(SCeta()) < 0.8){
        passCuts = full5x5_sigmaIetaIeta() < 0.011 &&
        hOverE() < 0.10 &&
        TMath::Abs(dEtaIn()) < 0.01 &&
        TMath::Abs(dPhiIn()) < 0.04 &&
        ooEmooP() > -0.05 &&
        ooEmooP() < 0.010;
    }
    */
    if (TMath::Abs(SCeta()) < 1.479) {
        passCuts = full5x5_sigmaIetaIeta() < 0.011 &&
        hOverE() < 0.10 &&
        ooEmooP() > -0.04; 
        //TMath::Abs(dEtaIn()) < 0.01 &&
        //TMath::Abs(dPhiIn()) < 0.04 &&
        //&&ooEmooP() < 0.010;
    }
    else if (TMath::Abs(SCeta()) < 2.5) {
        passCuts = full5x5_sigmaIetaIeta() < 0.030 &&
        hOverE() < 0.10 &&
        ooEmooP() > -0.04; 
        /*
        hOverE() < 0.07 &&
        TMath::Abs(dEtaIn()) < 0.008 &&
        TMath::Abs(dPhiIn()) < 0.07 &&
        ooEmooP() > -0.05 &&
        ooEmooP() < 0.005;
        */
    }
    else passCuts = kTRUE;

  if(
     pdgid==13 && conept() > _ConePtCuts[leptonType]
     && (
      (BDT() > _BDTCuts[leptonType] && jetdeepcsv() < _jetcsvHCuts[leptonType]) ||
      (BDT() < _BDTCuts[leptonType] && jetdeepcsv() < _jetcsvLCuts[leptonType] 
       && jetptratioV2() > _jetptratioCuts[leptonType] && segmentCompatibility() > _SegmentCompCuts[leptonType] )
      )
     )passFake = kTRUE;
   
  if(
     pdgid==11 && conept() > _ConePtCuts[leptonType]
     && passCuts && (
      (BDT() > _BDTCuts[leptonType] && jetdeepcsv() < _jetcsvHCuts[leptonType] ) ||
      (BDT() < _BDTCuts[leptonType] && jetdeepcsv() < _jetcsvLCuts[leptonType] 
       && jetptratioV2() > _jetptratioCuts[leptonType] && mvaValue_nonIso() > 0.5 )
       && expectedMissingInnerHits() == 0
      )
     )passFake = kTRUE;
  
  // definition of ttH Tgiht lepton
    if( conept() > _ConePtCuts[leptonType] 
      && jetdeepcsv() < _jetcsvHCuts[leptonType]
      && BDT() > _BDTCuts[leptonType]
      && isMedium
      )passTight = kTRUE;
  /*
  if(eventNumber == 2139411){
     std::cout << eventNumber << " " << lepPt << " "<< lepEta <<" " <<passMinPt << " " << passMaxEta << " " << passCustomVeto<< " "<< passLooseId() << " "<< passTight << std::endl;
     //std::cout << eventNumber << " conept " << conept() << " >? "<< _ConePtCuts[leptonType] <<" BDT " << BDT() << " >? " << _BDTCuts[leptonType] << " jetscsv " << jetdeepcsv() << " <? "<< _jetcsvHCuts[leptonType] << " isMedium? "<< isMedium << std::endl;
     //std::cout << eventNumber << " sNumber " << sNumber << " <21000? ishipsave? "<< ishipsave <<" pasLooseId()? " << passLooseId() << " validFraction " << validFraction() << " segmentCompat " << segmentCompatibility() << " GoodGlobal? " << GoodGlobal << std::endl;
  }
  */
  // Test Requirements
  if(lepPt <= _minPtCuts[leptonType])               passMinPt  = kFALSE;
  if(TMath::Abs(lepEta) >= _maxEtaCuts[leptonType]) passMaxEta = kFALSE;
  
  Int_t ispassTight = passTight;
  SetisTight(ispassTight);
  Bool_t PassFake = false;
  Bool_t PassTight = false;
  if(TMath::Abs(pdgId())==11){
      PassFake=passMinPt && passMaxEta  && passCustomVeto && passFake &&  passMissHit() && isPassMvanonIsowpLoose() && passConversionVeto() ;
      PassTight=passMinPt && passMaxEta  && passCustomVeto && passFake  && passTight &&  passMissHit() && passConversionVeto() && isPassMvanonIsowpLoose();
  }else{
      PassFake = passMinPt && passMaxEta  && passCustomVeto && passLooseId() && passFake;
      PassTight = passMinPt && passMaxEta  && passCustomVeto && passLooseId() && passFake && passTight;
  }
  SetisFake(PassFake);
  SetisMVASel(PassTight);
  //  if(     "Tight"      == leptonType) return( passMinPt && passMaxEta  && IsTight() && Isolation() && !GetOverlapWithJet() && IsCombinedMuon());
  if(     "MuTight"      == leptonType) return (passMinPt && passMaxEta  && passCustomVeto && passLooseId() && passTight);
  else if("MuLoose"       == leptonType) return (passMinPt && passMaxEta && passCustomVeto && passLooseId());
  else if("MuFake" == leptonType) return (passMinPt && passMaxEta  && passCustomVeto && passLooseId() && passFake); 
  else if("EleLoose"       == leptonType) return (passMinPt && passMaxEta && passCustomVeto && isPassMvanonIsowpLoose() );
  else if("EleTight"      == leptonType) return (PassTight );
  else if("EleFake" == leptonType) return (PassFake); 
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


