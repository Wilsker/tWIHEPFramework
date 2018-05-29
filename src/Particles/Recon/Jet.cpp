/******************************************************************************
 * Jet.cpp                                                                    *
 *                                                                            *
 * Store information about final state jets                                   *
 *                                                                            *
 * Derived from Particle class                                                *
 *                                                                            *
 * Public Member Functions of Jet class                                       *
 *    Jet()                              -- Default Constructor               *
 *    Jet()                              -- Parameterized Constructor         *
 *    ~Jet()                             -- Destructor                        *
 *    Clear()                            -- Set contents to default           *
 *    Fill                               -- Fill jet from event tree          *
 *    FillFastSim                        -- Fill jet from FastSim tree        *
 *    SetEtM0                            -- Set ET for EM layer 0             *
 *    GetEtM0                            -- Set ET for EM layer 0             *
 *    EtEM0                              -- Set ET for EM layer 0             *
 *    ApplyJESCorrection                 -- Shift jet energy by some amount   *
 *    operator+=                         -- Overload +=                       *
 *    operator+                          -- Overload +                        *
 *    operator=                          -- Overload = Particle               *
 *    operator=                          -- Overload = const Jet              *
 *    operator=                          -- Overload =                        *
 *                                                                            *
 * Private Data Members of Jet class                                          *
 *    Double_t _EtEm0                     -- Et for ME layer 0                *
 *                                                                            *
 * History                                                                    *
 *      16 Nov 2006 - Created by R. Schwienhorst                              *
 *      17 Nov 2006 - Modified by P. Ryan - cleanup and reorganized           *
 *      20 Mar 2007 - RS: Add filling from fastsim tree                       *
 *      29 Nov 2007 - RS: Add b-tagging choice when filling                   *
 *      11 Jan 2008 - RS: Fill only if object passes ID cuts                  *
 *      14 Jan 2008 - RS: For TRFIP2D, add systematics                        *
 *      08 May 2009 - J. Holzbauer: added quarkFlavorLabel tag                *
 *****************************************************************************/
#include "SingleTopRootAnalysis/Particles/Recon/Jet.hpp"
#include "SingleTopRootAnalysis/Particles/Recon/Electron.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <TRandom3.h>
#include<TString.h>


using namespace std;
//using namespace Analysis;

//
// give me a random number generator.
// put it here and make it static so that I don't create multiple copies
static TRandom3 jet_myran;
static TRandom3 jet_jer_myran;

// Integrate classes into the Root system
ClassImp(Jet)

/******************************************************************************
 * Jet::Jet()                                                                 *
 *                                                                            *
 * Default Constructor                                                        *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
  Jet::Jet() : Particle::Particle(),
  _numberOfConstituents(0), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _pileupId ( 0.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), _photonEnergy(0.0), _jesUp(false), _jesDown(false), _jerUp(false), _jerDown(false),
  _isLooseBdisc       (0.0),
  _isMediumBdisc       (0.0),
  _isTightBdisc       (0.0),
  _qg       (0.0),
  _axis2       (0.0),
  _ptD       (0.0),
  _mult       (0.0),
  _pfCombinedCvsLJetTags       (0.0),
  _pfCombinedCvsBJetTags       (0.0),
  _pfCombinedInclusiveSecondaryVertexV2BJetTags       (0.0),
  _pfCombinedMVAV2BJetTags       (0.0),
  _pfJetProbabilityBJetTags       (0.0),
  _pfDeepCSVCvsLJetTags       (0.0),
  _pfDeepCSVCvsBJetTags       (0.0),
  _lepdrmax       (0.0),
  _lepdrmin       (0.0),
  _isToptag       (0.0),
  _L1corrPt       (0.0),
  _uncorrE       (0.0),
  _partonFlavour       (0.0),
  _hadronFlavour       (0.0),
  _genMother_pdgId       (0.0),
  _genGrandMother_pdgId       (0.0),
  _matchId       (0.0),
  _isFromTop       (0.0),
  _isFromH       (0.0),
  _matchMother_Id       (0.0),
  _matchGrandMother_Id       (0.0),
  _HjDisc       (0.0)
{
} //Jet()

/******************************************************************************
 * Jet::~Jet()                                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
Jet::~Jet()
{
} //~Jet()

/******************************************************************************
 * Jet::Jet(const Jet& other)                                                 *
 *                                                                            *
 * Copy Constructor Jet const                                                 *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet(const Jet& other): Particle(other),
_numberOfConstituents		(other.GetnumberOfConstituents()), 
_chargedMultiplicity		(other.GetchargedMultiplicity()),  
_bDiscriminator 		(other.GetbDiscriminator()), 
_pileupId 			(other.GetpileupId()), 
_mass 				(other.Getmass()), 
_uncorrPt 			(other.GetuncorrPt()), 
_L1corrPt 			(other.GetL1corrPt()), 
_uncorrE 			(other.GetuncorrE()), 
_neutralHadEnergyFraction	(other.GetneutralHadEnergyFraction()), 
_neutralEmEmEnergyFraction 	(other.GetneutralEmEmEnergyFraction()),
 _chargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction()), 
_chargedEmEnergyFraction	(other.GetchargedEmEnergyFraction()), 
_muonEnergyFraction		(other.GetmuonEnergyFraction()), 
_electronEnergy			(other.GetelectronEnergy()), 
  _isLooseBdisc(other.GetisLooseBdisc()),
  _isMediumBdisc(other.GetisMediumBdisc()),
  _isTightBdisc(other.GetisTightBdisc()),
  _qg(other.Getqg()),
  _axis2(other.Getaxis2()),
  _ptD(other.GetptD()),
  _mult(other.Getmult()),
  _pfCombinedCvsLJetTags(other.GetpfCombinedCvsLJetTags()),
  _pfCombinedCvsBJetTags(other.GetpfCombinedCvsBJetTags()),
  _pfCombinedInclusiveSecondaryVertexV2BJetTags(other.GetpfCombinedInclusiveSecondaryVertexV2BJetTags()),
  _pfCombinedMVAV2BJetTags(other.GetpfCombinedMVAV2BJetTags()),
  _pfJetProbabilityBJetTags(other.GetpfJetProbabilityBJetTags()),
  _pfDeepCSVCvsLJetTags(other.GetpfDeepCSVCvsLJetTags()),
  _pfDeepCSVCvsBJetTags(other.GetpfDeepCSVCvsBJetTags()),
  _lepdrmax(other.Getlepdrmax()),
  _lepdrmin(other.Getlepdrmin()),
  _partonFlavour(other.GetpartonFlavour()),
  _hadronFlavour(other.GethadronFlavour()),
  _isToptag(other.GetisToptag()),
  _HjDisc(other.GetHjDisc()),
  _genMother_pdgId(other.GetgenMother_pdgId()),
  _genGrandMother_pdgId(other.GetgenGrandMother_pdgId()),
  _matchId(other.GetmatchId()),
  _isFromTop(other.GetisFromTop()),
  _isFromH(other.GetisFromH()),
  _matchMother_Id(other.GetmatchMother_Id()),
  _matchGrandMother_Id(other.GetmatchGrandMother_Id()),
_photonEnergy			(other.GetphotonEnergy())
{
} //Jet()

/******************************************************************************
 * Jet::Jet(const Particle& other)                                            *
 *                                                                            *
 * Copy Constructor Particle const                                            *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: None                                                               *
 ******************************************************************************/
Jet::Jet(const Particle& other): Particle(other),
_numberOfConstituents(0), _chargedMultiplicity(0),  _bDiscriminator ( -999.0), _pileupId ( 0.0), _mass ( 0.0), _uncorrPt ( 0.0), _neutralHadEnergyFraction(0.0), _neutralEmEmEnergyFraction ( 0.0), _chargedHadronEnergyFraction (0.0), _chargedEmEnergyFraction(0.0), _muonEnergyFraction(0.0), _electronEnergy(0.0), 
  _isLooseBdisc       (0.0),
  _isMediumBdisc       (0.0),
  _isTightBdisc       (0.0),
  _qg       (0.0),
  _axis2       (0.0),
  _ptD       (0.0),
  _mult       (0.0),
  _pfCombinedCvsLJetTags       (0.0),
  _pfCombinedCvsBJetTags       (0.0),
  _pfCombinedInclusiveSecondaryVertexV2BJetTags       (0.0),
  _pfCombinedMVAV2BJetTags       (0.0),
  _pfJetProbabilityBJetTags       (0.0),
  _pfDeepCSVCvsLJetTags       (0.0),
  _pfDeepCSVCvsBJetTags       (0.0),
  _L1corrPt  (0.0),
  _uncorrE  (0.0),
  _lepdrmax       (0.0),
  _lepdrmin       (0.0),
  _partonFlavour       (0.0),
  _hadronFlavour       (0.0),
  _isToptag       (0.0),
  _HjDisc       (0.0),
  _genMother_pdgId       (0.0),
  _genGrandMother_pdgId       (0.0),
  _matchId       (0.0),
  _isFromTop       (0.0),
  _isFromH       (0.0),
  _matchMother_Id       (0.0),
  _matchGrandMother_Id       (0.0),
_photonEnergy(0.0)
{
 
} //Jet()


/******************************************************************************
 * Jet& Jet::operator+=(const Jet& other)                                     *
 *                                                                            *
 * Overload +=                                                                *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator+=(const Jet& other)
{
  
  Particle::operator+=(other);
  return *this;
} //+=

/******************************************************************************
 * Jet& Jet::operator+(const Jet& other)                                      *
 *                                                                            *
 * Overload +                                                                 *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet Jet::operator+(const Jet& other)
{
  Particle particleTemp = Particle::operator+(other);
  Jet jetTemp = particleTemp;
  return jetTemp;

} //+

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = Particle                                                        *
 *                                                                            *
 * Input:  Particle                                                           *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(const Particle& other)
{
  
  Particle::operator=(other);
  SetnumberOfConstituents(0); 
  SetchargedMultiplicity(0); 
  SetbDiscriminator ( -999.0); 
  SetpileupId ( 0.0); 
  Setmass ( 0.0); 
  SetuncorrPt ( 0.0); 
  SetL1corrPt ( 0.0); 
  SetuncorrE ( 0.0); 
  SetneutralHadEnergyFraction(0.0); 
  SetneutralEmEmEnergyFraction ( 0.0); 
  SetchargedHadronEnergyFraction (0.0); 
  SetchargedEmEnergyFraction(0.0); 
  SetmuonEnergyFraction(0.0); 
  SetelectronEnergy(0.0); 
  SetisLooseBdisc       (0.0);
  SetisMediumBdisc       (0.0);
  SetisTightBdisc       (0.0);
  Setqg       (0.0);
  Setaxis2       (0.0);
  SetptD       (0.0);
  Setmult       (0.0);
  SetpfCombinedCvsLJetTags       (0.0);
  SetpfCombinedCvsBJetTags       (0.0);
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags       (0.0);
  SetpfCombinedMVAV2BJetTags       (0.0);
  SetpfJetProbabilityBJetTags       (0.0);
  SetpfDeepCSVCvsLJetTags       (0.0);
  SetpfDeepCSVCvsBJetTags       (0.0);
  Setlepdrmax       (0.0);
  Setlepdrmin       (0.0);
  SetpartonFlavour       (0.0);
  SethadronFlavour       (0.0);
  SetisToptag       (0.0);
  SetHjDisc       (0.0);
  SetgenMother_pdgId       (0.0);
  SetgenGrandMother_pdgId       (0.0);
  SetmatchId       (0.0);
  SetisFromTop       (0.0);
  SetisFromH       (0.0);
  SetmatchMother_Id       (0.0);
  SetmatchGrandMother_Id       (0.0);
  SetphotonEnergy(0.0);

  return *this;
} //= Particle

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = const Jet                                                       *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(const Jet& other)
{
  
  Particle::operator=(other);
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  SetpileupId 				(other.GetpileupId());
  Setmass 				(other.Getmass());
  SetuncorrPt 				(other.GetuncorrPt());
  SetL1corrPt 				(other.GetL1corrPt());
  SetuncorrE 				(other.GetuncorrE());
  SetneutralHadEnergyFraction		(other.GetneutralHadEnergyFraction());
  SetneutralEmEmEnergyFraction 		(other.GetneutralEmEmEnergyFraction());
  SetchargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction());
  SetchargedEmEnergyFraction		(other.GetchargedEmEnergyFraction());
  SetmuonEnergyFraction			(other.GetmuonEnergyFraction());
  SetelectronEnergy			(other.GetelectronEnergy());
  SetisLooseBdisc(other.GetisLooseBdisc());
  SetisMediumBdisc(other.GetisMediumBdisc());
  SetisTightBdisc(other.GetisTightBdisc());
  Setqg(other.Getqg());
  Setaxis2(other.Getaxis2());
  SetptD(other.GetptD());
  Setmult(other.Getmult());
  SetpfCombinedCvsLJetTags(other.GetpfCombinedCvsLJetTags());
  SetpfCombinedCvsBJetTags(other.GetpfCombinedCvsBJetTags());
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags(other.GetpfCombinedInclusiveSecondaryVertexV2BJetTags());
  SetpfCombinedMVAV2BJetTags(other.GetpfCombinedMVAV2BJetTags());
  SetpfJetProbabilityBJetTags(other.GetpfJetProbabilityBJetTags());
  SetpfDeepCSVCvsLJetTags(other.GetpfDeepCSVCvsLJetTags());
  SetpfDeepCSVCvsBJetTags(other.GetpfDeepCSVCvsBJetTags());
  Setlepdrmax(other.Getlepdrmax());
  Setlepdrmin(other.Getlepdrmin());
  SetpartonFlavour(other.GetpartonFlavour());
  SethadronFlavour(other.GethadronFlavour());
  SetisToptag(other.GetisToptag());
  SetHjDisc(other.GetHjDisc());
  SetgenMother_pdgId(other.GetgenMother_pdgId());
  SetgenGrandMother_pdgId(other.GetgenGrandMother_pdgId());
  SetmatchId(other.GetmatchId());
  SetisFromTop(other.GetisFromTop());
  SetisFromH(other.GetisFromH());
  SetmatchMother_Id(other.GetmatchMother_Id());
  SetmatchGrandMother_Id(other.GetmatchGrandMother_Id());
  SetphotonEnergy			(other.GetphotonEnergy());
  return *this;
} //= const

/******************************************************************************
 * Jet& Jet::operator=(const Jet& other)                                      *
 *                                                                            *
 * Overload = non-const Jet                                                   *
 *                                                                            *
 * Input:  Jet                                                                *
 * Output: Jet                                                                *
 ******************************************************************************/
Jet& Jet::operator=(Jet& other)
{
  Particle::operator=(other);
  SetnumberOfConstituents		(other.GetnumberOfConstituents());
  SetchargedMultiplicity		(other.GetchargedMultiplicity()); 
  SetbDiscriminator 			(other.GetbDiscriminator());
  SetpileupId 				(other.GetpileupId());
  Setmass 				(other.Getmass());
  SetuncorrPt 				(other.GetuncorrPt());
  SetL1corrPt 				(other.GetL1corrPt());
  SetuncorrE 				(other.GetuncorrE());
  SetneutralHadEnergyFraction		(other.GetneutralHadEnergyFraction());
  SetneutralEmEmEnergyFraction 		(other.GetneutralEmEmEnergyFraction());
  SetchargedHadronEnergyFraction 	(other.GetchargedHadronEnergyFraction());
  SetchargedEmEnergyFraction		(other.GetchargedEmEnergyFraction());
  SetmuonEnergyFraction			(other.GetmuonEnergyFraction());
  SetelectronEnergy			(other.GetelectronEnergy());
  SetisLooseBdisc(other.GetisLooseBdisc());
  SetisMediumBdisc(other.GetisMediumBdisc());
  SetisTightBdisc(other.GetisTightBdisc());
  Setqg(other.Getqg());
  Setaxis2(other.Getaxis2());
  SetptD(other.GetptD());
  Setmult(other.Getmult());
  SetpfCombinedCvsLJetTags(other.GetpfCombinedCvsLJetTags());
  SetpfCombinedCvsBJetTags(other.GetpfCombinedCvsBJetTags());
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags(other.GetpfCombinedInclusiveSecondaryVertexV2BJetTags());
  SetpfCombinedMVAV2BJetTags(other.GetpfCombinedMVAV2BJetTags());
  SetpfJetProbabilityBJetTags(other.GetpfJetProbabilityBJetTags());
  SetpfDeepCSVCvsLJetTags(other.GetpfDeepCSVCvsLJetTags());
  SetpfDeepCSVCvsBJetTags(other.GetpfDeepCSVCvsBJetTags());
  Setlepdrmax(other.Getlepdrmax());
  Setlepdrmin(other.Getlepdrmin());
  SetpartonFlavour(other.GetpartonFlavour());
  SethadronFlavour(other.GethadronFlavour());
  SetisToptag(other.GetisToptag());
  SetHjDisc(other.GetHjDisc());
  SetgenMother_pdgId(other.GetgenMother_pdgId());
  SetgenGrandMother_pdgId(other.GetgenGrandMother_pdgId());
  SetmatchId(other.GetmatchId());
  SetisFromTop(other.GetisFromTop());
  SetisFromH(other.GetisFromH());
  SetmatchMother_Id(other.GetmatchMother_Id());
  SetmatchGrandMother_Id(other.GetmatchGrandMother_Id());
  SetphotonEnergy			(other.GetphotonEnergy());
  return *this;
} //= non-const

/******************************************************************************         
 * void Jet::SetCuts(TEnv* config)                                            *
 *                                                                            *         
 * Set the cuts to be used on the jet objects                                 *
 *                                                                            *         
 * Input:  TEnv* config                                                       * 
 *         - Contains the cuts to be applied to each jet                      *
 * Output: None                                                               *
 ******************************************************************************/

void Jet::SetCuts(TEnv * config)
{
  _maxEtaCut = 		config -> GetValue("ObjectID.Jet.MaxEta",100.);
  _minPtCut = 		config -> GetValue("ObjectID.Jet.MinPt",0.);
  _bMaxEtaCut = 	config -> GetValue("ObjectID.BJet.MaxEta",100.);
  _bMinPtCut = 		config -> GetValue("ObjectID.BJet.MinPt",0.);
  _LWPbTagCut = 		config -> GetValue("ObjectID.BJet.LWPBTagCut",0.0);
  _MWPbTagCut = 		config -> GetValue("ObjectID.BJet.MWPBTagCut",0.0);
  _TWPbTagCut = 		config -> GetValue("ObjectID.BJet.TWPBTagCut",0.0);
  _closestLeptonCut = 	config -> GetValue("ObjectID.Jet.LepCleanR",0.0);
  _jesUp = 		config -> GetValue("Systs.doJESUp",0);
  _jesDown = 		config -> GetValue("Systs.doJESDown",0);
  _jerUp = 		config -> GetValue("Systs.doJERUp",0);
  _jerDown = 		config -> GetValue("Systs.doJERDown",0);
}

/***************************************************************
 * void Jet Jet::set_HjMVAreader()                       *
 *                                                              * 
 * Set up the MVA xml file                                      *
 *                                                              *
 * Input: TEnv* config                                          *
 * Output: None                                                 *
 * **************************************************************/
 
void Jet::set_HjMVAreader(TEnv* config)
{
    readerjet = new TMVA::Reader("!Color:!Silent");
    readerjet->AddVariable("Jet_lepdrmin",&jetvarlepdrmin);
    readerjet->AddVariable("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags := max(Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags,0.)",&jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags);
    readerjet->AddVariable("Jet_qg := max(Jet_qg,0.)",&jetvarqg);
    readerjet->AddVariable("Jet_lepdrmax",&jetvarlepdrmax);
    readerjet->AddVariable("Jet_pt",&jetvarpt);
    readerjet->BookMVA("BDTG method", config -> GetValue("Include.HjTaggerMVAFile","null")); 
}

/***************************************************************
 * double Jet Jet::get_JetMVA()                *
 *                                                              * 
 * Read the Hj Tagger MVA value                                      *
 *                                                              *
 * Input: None                                          *
 * Output: Hj Tagger MVA value                                     *
 * **************************************************************/
 
double Jet::get_JetMVA()
{
    jetvarqg = qg();
    jetvarlepdrmax = lepdrmax();
    jetvarpt = Pt();
    jetvarlepdrmin = lepdrmin();
    //jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags = bDiscriminator();
    jetvarpfCombinedInclusiveSecondaryVertexV2BJetTags = pfCombinedInclusiveSecondaryVertexV2BJetTags();
    return readerjet->EvaluateMVA("BDTG method");
}

/******************************************************************************         
 * void Jet::Fill(EventTree *evtr, Int_t iE,const TString& tagName)           *         
 *                                                                            *         
 * Fill jet vector from tree                                                  *         
 *                                                                            *         
 * Input:  Event Tree pointer                                                 *         
 *         - which jet                                                        *
 * Output: True if this jet passes jet ID cuts                                *         
 ******************************************************************************/

Bool_t Jet::Fill( double myJESCorr, double myJERCorr, std::vector<Lepton>& selectedLeptons, std::vector<Tau>& selectedTaus, EventTree *evtr, Int_t iE, TLorentzVector * met, Bool_t useLepAwareJets, Bool_t isSimulation, int whichtrig)
{

  Double_t jetPt, jetEta,jetPhi,jetE, jetCharge, jetM;
  Double_t jetUncorrPt, jetUncorrE, jesSF, jerSF;
  jetUncorrPt = evtr->Jet_Uncorr_pt -> operator[](iE);
  jetUncorrE = (evtr -> Jet_energy -> operator[](iE))/(evtr -> Jet_pt -> operator[](iE))*jetUncorrPt;
  jesSF = evtr->Jet_JesSF -> operator[](iE);
  //jerSF = evtr->Jet_JerSF -> operator[](iE);
  jerSF = 1.0; 
 
  if (useLepAwareJets){ 
    jetPt     = jetUncorrPt * jesSF;
    jetE      = (evtr -> Jet_energy -> operator[](iE))/(evtr -> Jet_pt -> operator[](iE))*jetUncorrPt * jesSF;
    //std::cout<<jetPt<<" "<<jetE<<" "<<std::endl;
  }else{
    jetPt     = jetUncorrPt * jesSF * jerSF;
    jetE      = (evtr -> Jet_energy -> operator[](iE))/(evtr -> Jet_pt -> operator[](iE))*jetUncorrPt * jesSF * jerSF;
  }
  jetEta    = evtr -> Jet_eta    -> operator[](iE);
  jetPhi    = evtr -> Jet_phi    -> operator[](iE);

  if(jetE > 0){
    SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  }else{
    SetPtEtaPhiE(1,1,1,3);
  }

  SetnumberOfConstituents		(evtr -> Jet_numberOfConstituents     	-> operator[](iE));
  SetchargedMultiplicity		(evtr -> Jet_chargedMultiplicity     	-> operator[](iE)); 
  //SetbDiscriminator 			(evtr -> Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags     	-> operator[](iE));
  SetbDiscriminator 			(evtr -> Jet_pfDeepCSVBJetTags     	-> operator[](iE));
  SetpileupId 				(evtr -> Jet_pileupId     		-> operator[](iE));
  Setmass 				(evtr -> Jet_mass     			-> operator[](iE));
  SetuncorrPt 				(evtr -> Jet_Uncorr_pt     		-> operator[](iE));
  SetL1corrPt 				(evtr -> Jet_L1corr_pt     		-> operator[](iE));
  SetuncorrE 				(jetUncorrE);
  SetneutralHadEnergyFraction		(evtr -> Jet_neutralHadEnergyFraction	-> operator[](iE));
  SetneutralEmEmEnergyFraction 		(evtr -> Jet_neutralEmEnergyFraction  -> operator[](iE));
  SetchargedHadronEnergyFraction 	(evtr -> Jet_chargedHadronEnergyFraction-> operator[](iE));
  SetchargedEmEnergyFraction		(evtr -> Jet_chargedEmEnergyFraction    -> operator[](iE));
  SetmuonEnergyFraction			(evtr -> Jet_muonEnergyFraction     	-> operator[](iE));
  SetelectronEnergy			(evtr -> Jet_electronEnergy     	-> operator[](iE));
  SetphotonEnergy			(evtr -> Jet_photonEnergy     		-> operator[](iE));
  Setqg       (evtr -> Jet_qg      -> operator[](iE));
  Setaxis2       (evtr -> Jet_axis2      -> operator[](iE));
  SetptD       (evtr -> Jet_ptD      -> operator[](iE));
  Setmult       (evtr -> Jet_mult      -> operator[](iE));
  SetpfCombinedCvsLJetTags       (evtr -> Jet_pfCombinedCvsLJetTags      -> operator[](iE));
  SetpfCombinedCvsBJetTags       (evtr -> Jet_pfCombinedCvsBJetTags      -> operator[](iE));
  SetpfCombinedInclusiveSecondaryVertexV2BJetTags       (evtr -> Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags      -> operator[](iE));
  SetpfCombinedMVAV2BJetTags       (evtr -> Jet_pfCombinedMVAV2BJetTags      -> operator[](iE));
  SetpfJetProbabilityBJetTags       (evtr -> Jet_pfJetProbabilityBJetTags      -> operator[](iE));
  SetpfDeepCSVCvsLJetTags       (evtr -> Jet_pfDeepCSVCvsLJetTags      -> operator[](iE));
  SetpfDeepCSVCvsBJetTags       (evtr -> Jet_pfDeepCSVCvsBJetTags      -> operator[](iE));
  if(isSimulation){
    SetpartonFlavour       (evtr -> Jet_partonFlavour      -> operator[](iE));
    SethadronFlavour       (evtr -> Jet_hadronFlavour      -> operator[](iE));
  }else{
    SetpartonFlavour       (-999.);
    SethadronFlavour       (-999.);
  }
  //SetgenMother_pdgId       (evtr -> Jet_genMother_pdgId      -> operator[](iE));
  //SetgenGrandMother_pdgId       (evtr -> Jet_genGrandMother_pdgId      -> operator[](iE));
  SetgenMother_pdgId       (-999.);
  SetgenGrandMother_pdgId       (-999.);

  SetisLooseBdisc      ( bDiscriminator() > _LWPbTagCut ); 
  SetisMediumBdisc       ( bDiscriminator() > _MWPbTagCut );
  SetisTightBdisc       ( bDiscriminator() > _TWPbTagCut );
 
  // Now we want to do the JER and JES systematic adjustments to the jet. This also requires correcting the MET.
  if (_jesUp || _jesDown || _jerUp || _jerDown) SystematicPtShift(evtr, iE, met, useLepAwareJets);  

  if (useLepAwareJets) return kTRUE;

/*
  SetPdgId      ( evtr -> Jet_flavor_truth_trueflav -> operator[](iE));
  SetIsBadLoose ( evtr -> Jet_isBadLoose            -> operator[](iE));
  ///////////////////////////////////////////////////////////////////////////////
  //
  // b-tagging choices
  /////////////////////////////////////////////////////////////////////////////////
  // Upated for version 14
  //currently no TRF b-taggers, so using a cut on weights
  
  std::vector<Double_t> bweight;
  bweight.clear();
  //cout<<evtr -> Jet_flavor_weight -> operator[](iE)<<endl;
  bweight.push_back(evtr -> Jet_flavor_weight -> operator[](iE));//0
  bweight.push_back(evtr -> Jet_flavor_weight_IP1D -> operator[](iE));//1
  bweight.push_back(evtr -> Jet_flavor_weight_IP2D -> operator[](iE));//2
  bweight.push_back(evtr -> Jet_flavor_weight_IP3D -> operator[](iE));//3
  bweight.push_back(evtr -> Jet_flavor_weight_SV1 -> operator[](iE));//4
  bweight.push_back(evtr -> Jet_flavor_weight_SV2 -> operator[](iE));//5
  //for JetProb, we actually use -ln(JetProb)
  bweight.push_back(-TMath::Log10(evtr -> Jet_flavor_weight_JetProb -> operator[](iE)));//6
  bweight.push_back(evtr -> Jet_flavor_weight_TrackCounting2D -> operator[](iE));//7
  bweight.push_back(evtr -> Jet_flavor_weight_SV0 -> operator[](iE));//8 
  bweight.push_back(evtr -> Jet_flavor_weight_JetFitterCOMBNN-> operator[](iE));//9
  SetBWeight(bweight);
  //cout<<bweight.size()<<endl;
  
  double tagCut = 0;

  tagCut = btagCut;

  if(tagName=="default" || tagName=="bTagged" || tagName=="IP3DSV1") {
    if(evtr -> Jet_flavor_weight -> operator[](iE) > tagCut) SetTagged(kTRUE);
    else SetTagged(kFALSE);
  } // if
  else if(tagName=="SV0") {
    if(evtr->Jet_flavor_weight_SV0->operator[](iE) > tagCut) SetTagged(kTRUE);
    else SetTagged(kFALSE);
  } 
  else {
    cout<<"<ERROR>: Error in jet.cpp: invalid tagger, "<<tagName<<endl;
    exit(8);
  }
*/
  /////////////////////////////////////////////////////////////////////////////
  // Jet Pt and Eta Cuts
  /////////////////////////////////////////////////////////////////////////////

  Bool_t passPt = Pt() > _minPtCut;
  Bool_t passEta = TMath::Abs(Eta()) < _maxEtaCut;

  /////////////////////////////////////////////////////////////////////////
  // Jet ID
  /////////////////////////////////////////////////////////////////////////
  

  //Bool_t neutralID = (TMath::Abs(Eta()) > 3. || (neutralHadEnergyFraction() < 0.99 &&  neutralEmEmEnergyFraction() < 0.99 && numberOfConstituents() > 1));
  //Bool_t chargedID = (TMath::Abs(Eta()) > 2.4 || (chargedHadronEnergyFraction() > 0. && chargedMultiplicity() > 0. && chargedEmEnergyFraction() < 0.99));
  //Bool_t neutralHighEtaID = (TMath::Abs(Eta()) < 3. || (neutralEmEmEnergyFraction() < 0.9 && (numberOfConstituents() - chargedMultiplicity()) > 10));

  Bool_t LowEtaID = (neutralHadEnergyFraction()<0.90 && neutralEmEmEnergyFraction()<0.90 && numberOfConstituents()>1) && ((TMath::Abs(Eta())<=2.4 && chargedHadronEnergyFraction()>0 && chargedMultiplicity()>0) || TMath::Abs(Eta())>2.4) && TMath::Abs(Eta())<=2.7;
  Bool_t MediumEtaID = (neutralEmEmEnergyFraction()<0.99 && neutralEmEmEnergyFraction()>0.02 && (numberOfConstituents() - chargedMultiplicity())>2 && TMath::Abs(Eta())>2.7 && TMath::Abs(Eta())<=3.0 ); 
  Bool_t HighEtaID = (neutralEmEmEnergyFraction()<0.90 && neutralHadEnergyFraction()>0.02 &&(numberOfConstituents() - chargedMultiplicity())>10 && TMath::Abs(Eta())>3.0 ); 

  //Bool_t passesJetID = neutralID && chargedID && neutralHighEtaID;
  Bool_t passesJetID = LowEtaID || MediumEtaID || HighEtaID;

  

  /////////////////////////////////////////////////////////////////////////
  // Jet Cleaning
  /////////////////////////////////////////////////////////////////////////

  Bool_t passesCleaning = kTRUE;
 
  Double_t closestLepton = 999.;
  Double_t minlepdr = -1.;
  Double_t maxlepdr = -1.;
  
  int lep_num =selectedLeptons.size();
  
  if (lep_num == 1){
    minlepdr = selectedLeptons.at(0).DeltaR(*this);
    maxlepdr = minlepdr;
  }
 
  if (lep_num >= 2){
    minlepdr = TMath::Min(selectedLeptons.at(0).DeltaR(*this),selectedLeptons.at(1).DeltaR(*this));
    maxlepdr = TMath::Max(selectedLeptons.at(0).DeltaR(*this),selectedLeptons.at(1).DeltaR(*this));
  }

  int clean_num =0;
  if(whichtrig>=2 && whichtrig <= 5){//2L categories
      clean_num = TMath::Min(2,lep_num);
  }else if(whichtrig ==6){//3L
      clean_num = TMath::Min(3,lep_num);
  }
    

  for(int lep_en=0; lep_en< clean_num; lep_en++){
    Lepton lep = selectedLeptons.at(lep_en);
    if (lep.DeltaR(*this) < closestLepton){
        closestLepton = lep.DeltaR(*this);
    }
  }
 /*
  int clean_tau=0;
  int tau_num = selectedTaus.size();
  clean_tau= TMath::Min(1,tau_num);
  
  for(int tau_en=0; tau_en< clean_tau; tau_en++){
    Tau tau = selectedTaus.at(tau_en);
    if (tau.DeltaR(*this) < closestLepton){
        closestLepton = tau.DeltaR(*this);
    }
  }
  */

  /*
  for (auto const & lep : selectedLeptons){
    if (lep.DeltaR(*this) < closestLepton){
        closestLepton = lep.DeltaR(*this);
    }
  }
  for (auto const & tau : selectedTaus){
    if (tau.DeltaR(*this) < closestLepton) closestLepton = tau.DeltaR(*this);
  }
  */

  if (closestLepton < _closestLeptonCut) passesCleaning = kFALSE;

  SetClosestLep(closestLepton);
  Setlepdrmax       (maxlepdr);
  Setlepdrmin       (minlepdr);
  SetHjDisc       (get_JetMVA());
  SetmatchId       (-999);
  SetisFromTop       (-999);
  SetisFromH       (-999);
  SetmatchMother_Id       (-999);
  SetmatchGrandMother_Id       (-999);

  /////////////////////////////////////////////////////////////////////////
  // B-tag related cuts
  /////////////////////////////////////////////////////////////////////////

  Bool_t passbPt = Pt() > _bMinPtCut;
  Bool_t passbEta = TMath::Abs(Eta()) < _bMaxEtaCut;
  Bool_t passTagCut = bDiscriminator() > _LWPbTagCut;

  if (passbPt && passbEta && passTagCut) SetTagged(kTRUE);
  else SetTagged(kFALSE);

  if (passPt && passEta && passesJetID && passesCleaning) return kTRUE;
  
  return kFALSE;

} //Fill()

/******************************************************************************         
 * void Jet::FillFastSim(FastSimTree *tr, Int_t iE,const TString& tagName )   *         
 *                                                                            *         
 * Fill jet vector from fastsim tree                                          *         
 *                                                                            *         
 * Input:  - FastSim tree pointer                                             *         
 *         - which jet                                                        *
 *         - tagName, either default or IP2D                                  *
 * Output: True if this jet passes jet ID cuts                                *         
 ******************************************************************************/
Bool_t Jet::FillFastSim( std::vector<MCJet>& MCBJets, std::vector<MCJet>& MCCJets, std::vector<MCTau>& MCTaus, std::vector<Electron>& electrons, FastSimTree *tr,Int_t iE,TEnv* config,const TString& tagName, Double_t btagCut, Double_t mistagCut, Double_t eshift)
{  
  Double_t jetPt, jetEta,jetPhi,jetE, jetCharge;
  jetPt     = tr -> PJet_p_T    -> operator[](iE);
  jetEta    = tr -> PJet_eta    -> operator[](iE);
  jetPhi    = tr -> PJet_phi    -> operator[](iE);
  jetE      = tr -> PJet_E      -> operator[](iE);
  jetCharge = tr -> PJet_charge -> operator[](iE); 
  
  SetPtEtaPhiE(jetPt,jetEta,jetPhi,jetE);
  SetCharge(jetCharge);

  if(eshift != 0){
    
    Double_t diffx,diffy,diffz,diffe;
    
    //  cout<<"OLD "<<Px()<<"  "<<Py()<<"  "<<Pz()<<"  "<<E()<<endl;
    //  cout<<"OLD "<<Pt()<<"  "<<Eta()<<"  "<<Phi()<<endl;
    
    diffx = eshift * Px();
    diffy = eshift * Py();
    diffz = eshift * Pz();
    diffe = eshift * E();
    SetPxPyPzE(diffx + Px(),
	       diffy + Py(),
	       diffz + Pz(),
	       diffe + E());
    
    //cout<<diffx<<"  "<<diffy<<"  "<<diffz<<"  "<<diffe<<"  "<<eshift<<endl;
    //cout<<"NEW "<<Px()<<"  "<<Py()<<"  "<<Pz()<<"  "<<E()<<endl;
    //cout<<"NEW "<<Pt()<<"  "<<Eta()<<"  "<<Phi()<<endl;
    
    // if met pointers have been provided, update those also
    //cout<<"OLDMET "<<metx<<"  "<<mety<<endl;
    
    // cout<<"NEWMET "<<*metx<<"  "<<*mety<<endl;
   
  }
  //##########################################################################
  //b-tagging.  Insert info when available, based on reco tree.
  //##########################################################################



  //##########################################################################
  //PdgId()
  //
  //identifies jet with a MC quark.  5=bquark, 4=cquark, 15=tau(mc), 0=lightquark or gluon, etc
  //
  //This section identifies the MC particle (b, c, tau, or other (light quark)
  //that the jet is closest to and labels it as that, by pdgid, where light quark
  //is 0.  Jets are labeled starting with b, then c, then tau, and then, if none
  //of these match, as light quark.  This follows proceedure in b-tagging csc note.
  //Jet must be within deltaR of 0.3 of particle to be matched, and mc particle
  //must have Pt > 5 GeV, also per the csc note.
  //
  //Currently modified to use the Jet_Truth_Label variable from tree
  //Currently no charge information carried in this label
  //
  //NOTE: This PDGId() method returns the flavor of the MC particle associated
  //with the jet (wrt position).  It is NOT nessesarily the jet's flavor, but
  //a reasonable assumption BASED ON MC AND RECO INFORMATION
  //##########################################################################

  Double_t DeltaRCurrent = 0;
  Double_t EtaCurrent  = 0;
  Double_t PhiCurrent  = 0;
  Double_t PtCurrent   = 0;
  //SetPdgId(999);//not set yet
  
  //SetPdgId(tr -> Jet_Truth_Label -> operator[](iE));//not set yet
  
  
  //////////////////////////////////////////////////
  // Overlap with Electron
  //////////////////////////////////////////////////
  // Get Minimum separation between the electron and jet from the config file
  Double_t electronDeltaRMin = config -> GetValue("ObjectID.Jet.ElectronDeltaRMin", 0.0);
  Double_t electronDeltaR = 0.0;
  std::vector<Electron>::iterator electronIterator;
  for(electronIterator = electrons.begin(); electronIterator != electrons.end(); electronIterator++){
    electronDeltaR = electronIterator->DeltaR(*this);
    // If jet is too close to any electron set overlap to 1 and break
    if(electronDeltaR < electronDeltaRMin ){
      //SetOverlapWithElectron(1);
      break;
    } //if
  } //for
  
  //
  // now check jet object ID cuts
  double maxEta=config->GetValue("ObjectID.Jet.MaxEta",100.);
  double minPt=config->GetValue("ObjectID.Jet.MinPt",0.);
  
  
  //if(jetPt<minPt) return kFALSE;
  //if(TMath::Abs(jetEta)>maxEta) return kFALSE;

  // Set to false if jet fails pT requirement, eta reqiurement, is overlapped with electron
  //if( jetPt <= minPt || TMath::Abs(jetEta) >= maxEta  || GetOverlapWithElectron() ) return kFALSE;
  //else return kTRUE;
  return kTRUE;
  
} //FillFastSim()

/******************************************************************************         
 * void Jet::SystematicPtShift(EventTree * evtr)                         *
 *                                                                            *         
 * Apply systematic shifts in jet pt                                          *
 *                                                                            *         
 * Input:  - the event tree (to access systematic SFs and MET info)      *
 * Output: -                                                                  *
 ******************************************************************************/
void Jet::SystematicPtShift(EventTree * evtr, Int_t iE, TLorentzVector * met, Bool_t useLepAware){


  //  std::cout << "syst correct" << std::endl;
  float ptSF = 1.0;
  if (_jesUp){
    ptSF = evtr->Jet_JesSFup->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
  }
  if (_jesDown){
    ptSF = evtr->Jet_JesSFdown->operator[](iE)/evtr->Jet_JesSF->operator[](iE);
  }
  if (_jerUp && !useLepAware){
    ptSF = evtr->Jet_JerSFup->operator[](iE)/evtr->Jet_JerSF->operator[](iE);
  }
  if (_jerDown && !useLepAware){
    ptSF = evtr->Jet_JerSFdown->operator[](iE)/evtr->Jet_JerSF->operator[](iE);
  }
  //  float ptBefore = Pt();
  //Remove jet from MET
  met->SetPx(met->Px() + Px());
  met->SetPy(met->Py() + Py());
  //Apply the correction
  //  std::cout << Px() << " " << Py() << " " << Pt() << std::endl;
  SetPx(Px()*ptSF);
  SetPy(Py()*ptSF);
  SetPz(Pz()*ptSF);
  //std::cout << Px() << " " << Py() << " " << Pt() << std::endl << std::endl;
  
  //Propagate to MET
  met->SetPx(met->Px() - Px());
  met->SetPy(met->Py() - Py());

  //  float ptAfter = Pt();
  //  if (ptBefore < 30 && ptAfter > 30) {
  //  std::cout << "Now selected: Jet #" << iE << "Jet Pt: " << ptBefore << " JER SF: " << evtr->Jet_JerSF->operator[](iE) << " up: " << evtr->Jet_JerSFup->operator[](iE) << " down: " << evtr->Jet_JerSFdown->operator[](iE) << " JES SF: " << evtr->Jet_JesSF->operator[](iE) << " up: " << evtr->Jet_JesSFup->operator[](iE) << " down: " << evtr->Jet_JesSFdown->operator[](iE);
  //  std::cout << " Pt SF: " << ptSF << " Jet pt after: " << Pt() << std::endl;
  //}
  //if (ptBefore > 30 && ptAfter < 30) {
  //  std::cout << "No longer selected: Jet #" << iE << "Jet Pt: " << ptBefore << " JER SF: " << evtr->Jet_JerSF->operator[](iE) << " up: " << evtr->Jet_JerSFup->operator[](iE) << " down: " << evtr->Jet_JerSFdown->operator[](iE) << " JES SF: " << evtr->Jet_JesSF->operator[](iE) << " up: " << evtr->Jet_JesSFup->operator[](iE) << " down: " << evtr->Jet_JesSFdown->operator[](iE);
  //  std::cout << " Pt SF: " << ptSF << " Jet pt after: " << Pt() << std::endl;
  //}



}
