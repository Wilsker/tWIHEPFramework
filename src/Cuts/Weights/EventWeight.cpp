/******************************************************************************
 * EventWeight.hpp                                                            *
 *                                                                            *
 * Weight events in the histograms                                            *
 *                                                                            *
 * This class is derived from the BaseCut Class and simply                    *
 * cuts on if the event has reconstructed objects                             *
 *                                                                            *
 * Derived from HistoCut which is in turn derived from BaseCut                *
 *                                                                            *
 * Public Member Functions of AnalysisMain class                              *
 *    EventWeight()                     -- Parameterized Constructor          *
 *    ~EventWeight()                    -- Destructor                         *
 *    BookHistogram()                   -- Book histograms of weights         *
 *    Apply()                           -- Apply weight and fill histograms   *
 *    GetCutName()                      -- Returns "EventWeight"              *
 *                                                                            *
 * Private Data Members of AnalysisMain class                                 *
 *    myTH1F* _hTreeWeight              -- Histogram of Input Tree Weights    *
 *    myTH1F* _hGlobalWeight            -- Histogram of Global Weights        *
 *    myTH1F* _hOutputWeight            -- Histogram of Output Weights        *
 *                                                                            *
 * History                                                                    *
 *     28 Apr 2005 - Created by R. Schwienhorst at D0                         *
 *      7 Nov 2006 - Modified by R. Schwienhorst for ATLAS                    *
 *      9 Nov 2006 - Modified by P. Ryan - cleanup and reorganized            *
 *     11 Sep 2007 - RS: Add MCatNLO weight                                   *
 *****************************************************************************/

#include "SingleTopRootAnalysis/Cuts/Weights/EventWeight.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>

using namespace std;


/******************************************************************************
 * EventWeight::EventWeight(EventContainer *obj)                              *
 *                                                                            *
 * Parameterized Constructor                                                  *
 *                                                                            *
 * Input:  Particle class                                                     *
 * Output: None                                                               *
 ******************************************************************************/
EventWeight::EventWeight(EventContainer *EventContainerObj,Double_t TotalMCatNLOEvents,const std::string& MCtype, Bool_t pileup, Bool_t reCalPU, Bool_t bWeight, Bool_t useLeptonSFs, Bool_t usebTagReshape, Bool_t useChargeMis, Bool_t useFakeRate, Bool_t useTriggerSFs, Bool_t usePrefire, Int_t whichTrig, Bool_t verbose):
  _reCalPU(reCalPU),
  _useLeptonSFs(useLeptonSFs),
  _useChargeMis(useChargeMis),
  _usePrefire(usePrefire),
  _useFakeRate(useFakeRate),
  _useTriggerSFs(useTriggerSFs),
  _usebTagReshape(usebTagReshape),
  _whichTrigger(whichTrig),
  _verbose(verbose)
{
  //pileup is NOT applied by default.  Instead it is applied by the user, and stored in the tree for later application

  TEnv* conf = EventContainerObj -> GetConfig();
  /**
  if(MCtype.find("PileUpWgt")<=MCtype.size()){
    cout<<"EventWeight: This version of pileup weights is based on primary vertex number and no longer used!!!"<<endl;
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV0", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV1", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV2", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV3", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV4", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV5", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV6", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV7", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV8", 1.));
    vecPileUpWgt.push_back(conf->GetValue("Weight.Source.nPvtx.NPV9", 1.));
  }
  **/
  // Set Particle object
  _totalMCatNLOEvents = 0;

 if(MCtype.find("MCatNLO")<=MCtype.size()){
    setMCatNLO(true);
  }else{
    setMCatNLO(false);
  }
 /**
 if(MCtype.find("PileUpWgt")<=MCtype.size()){
    setPileUpWgt(true);
  }else{
    setPileUpWgt(false);
  }
 **/
  //std::cout << "Debug line 89 ######### " << std::endl;
  SetEventContainer(EventContainerObj);
  TString pileupHistName=" ";
  if(MCtype.find("UseTotalEvtFromFile")<=MCtype.size()){ // please keep this to be true so that we can read pileup histograms
    Int_t sNumber = EventContainerObj -> GetSourceNumber();
    stringstream strNumber, puName;
    strNumber<<"Events.Source."<<sNumber;
    puName <<"PileUp.Source."<<sNumber;
    Double_t totMCnloEvt = conf -> GetValue(strNumber.str().c_str(), -1.);
    pileupHistName=conf -> GetValue(puName.str().c_str(),"null");
    SetTotalMCatNLOEvents(totMCnloEvt);
  } else {
    SetTotalMCatNLOEvents(TotalMCatNLOEvents);
  }
  setPileUpSyst(false);
  if(pileup){
    setPileUpWgt(true);
    TFile* dataPVFile = TFile::Open(conf -> GetValue("Include.dataPVFile","null"),"READ");
    _dataPV = (TH1D*)dataPVFile->Get("pileup");
    _dataPV->SetDirectory(0);
    _dataPV->Scale(1./_dataPV->Integral());

    setPileUpSyst(true);
    _minBiasUpPV = (TH1D*)dataPVFile->Get("pileup_plus");
    _minBiasUpPV->SetDirectory(0);
    _minBiasUpPV->Scale(1./_minBiasUpPV->Integral());

    _minBiasDownPV = (TH1D*)dataPVFile->Get("pileup_minus");
    _minBiasDownPV->SetDirectory(0);
    _minBiasDownPV->Scale(1./_minBiasDownPV->Integral());
    dataPVFile->Close();
    delete dataPVFile;


    TFile* mcPVFile = TFile::Open(conf -> GetValue("Include.mcPVFile","null"),"READ");
    std::cout << "pileupHistName is " << pileupHistName << std::endl;
    _mcPV = (TH1D*)mcPVFile->Get(pileupHistName);
    _mcPV->SetDirectory(0);
    _mcPV->Scale(1./_mcPV->Integral());
    mcPVFile->Close();
    delete mcPVFile;

    //Load in the pileup distributions with the min bias x-section altered for systematic studies
    /*
    string minBiasFileName = conf -> GetValue("Include.minBiasUp","null");
    if (minBiasFileName != "null"){
      TFile* minBiasUpFile = TFile::Open(minBiasFileName.c_str(),"READ");
      setPileUpSyst(true);
      _minBiasUpPV = (TH1F*)minBiasUpFile->Get("pileup");
      _minBiasUpPV->SetDirectory(0);
      _minBiasUpPV->Scale(1./_minBiasUpPV->Integral());
      minBiasUpFile->Close();
      delete minBiasUpFile;
    }

    string minBiasDownFileName = conf -> GetValue("Include.minBiasDown","null");
    if (minBiasDownFileName != "null"){
      TFile* minBiasDownFile = TFile::Open(minBiasDownFileName.c_str(),"READ");
      _minBiasDownPV = (TH1F*)minBiasDownFile->Get("pileup");
      _minBiasDownPV->SetDirectory(0);
      _minBiasDownPV->Scale(1./_minBiasDownPV->Integral());
      minBiasDownFile->Close();
      delete minBiasDownFile;
    }
    */

  }
  else setPileUpWgt(false);

  if (bWeight) setbWeight(true);
  else setbWeight(false);

  ostringstream strFileData;
  ostringstream strFileMC;
  ostringstream strHistMC;
  TString rootfileData;
  TString rootfileMC;
  TString histMC;
  //strFileData<<"Weight.Pileup.Data.File";
  //strFileMC<<"Weight.Pileup.MC.File";
  //strHistMC<<"Weight.Pileup.MC.Hist";

  //rootfileData = conf -> GetValue(strFileData.str().c_str(), "null.root");
  //rootfileMC = conf -> GetValue(strFileMC.str().c_str(), "null.root");

  histMC = conf -> GetValue(strHistMC.str().c_str(), "null");

  //PileupReweighting = new Root::TPileupReweighting("pileuprw");
  //int isGood = PileupReweighting->initialize(rootfileData, "avgintperbx", rootfileMC, histMC);
  //if ( isGood == 0 ) cout<< "EventContainer:: Initialization of TPileupReweighting successful"<<endl;
  //else  cout<<"EventContainer:: Initialization of TPileupReweighting NOT successful!"<<endl;

  //Default list of b tagging systematics. This could possibly become customisable, but it probably doesn't need to be.
  _bTagSystNames = {"central","up_jes","down_jes","up_lf","down_lf","up_hfstats1","down_hfstats1","up_hfstats2","down_hfstats2","up_cferr1","down_cferr1","up_cferr2","down_cferr2","up_hf","down_hf","up_lfstats1","down_lfstats1","up_lfstats2","down_lfstats2" };

  _frSystNames = {"central","up","down","pt1","pt2","be1","be2","QCD","TT"};


} // EventWeight

/******************************************************************************
 * EventWeight::~EventWeight()                                                *
 *                                                                            *
 * Destructor                                                                 *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
EventWeight::~EventWeight()
{
 //if(isPileUpWgt()) {
 // delete PileupReweighting;
 //}
} //~EventWeight

/******************************************************************************
 * void EventWeight::BookHistogram()                                          *
 *                                                                            *
 * Book Histograms                                                            *
 *                                                                            *
 * Input:  None                                                               *
 * Output: None                                                               *
 ******************************************************************************/
void EventWeight::BookHistogram()
{

  //cout<<"EventWeight::BookHistogram, debug level "<<obj->GetDebugLevel()<<endl;

  // Histogram of Input Tree Weights
  _hTreeWeight   =  DeclareTH1F("TreeWeight","Event Weight from the input tree",100,-10.,10.);
  _hTreeWeight   -> SetXAxisTitle("tree weight");

  // Histogram of Global Weights
  _hGlobalWeight =  DeclareTH1F("GlobalWeight","Global Event Weight",100,-10.,10.);
  _hGlobalWeight -> SetXAxisTitle("Global Weight");
  _hGlobalWeight -> SetYAxisTitle("Events");

  // Histogram of MC@NLO Weight. This is one of the global weights
  _hMCatNLOWeight =  DeclareTH1F("MCatNLOWeight","Event Weight for MCatNLO",100,-10.,10.);
  _hMCatNLOWeight -> SetXAxisTitle("MCatNLO Weight");
  _hMCatNLOWeight -> SetYAxisTitle("Events");

  // Histogram of pile up Weight(vtx). This is one of the global weights
  _hPileUpWeight =  DeclareTH1F("PileUpWgtWeight","Event Weight for PileUpWgt",100,-10.,10.);
  _hPileUpWeight -> SetXAxisTitle("PileUpWgt Weight");
  _hPileUpWeight -> SetYAxisTitle("Events");

  // Histogram of pile up Weight(vtx). This is one of the global weights
  _hbWeight =  DeclareTH1F("bWeight","Event Weight for b tagging",100,0.,10.);
  _hbWeight -> SetXAxisTitle("b Weight");
  _hbWeight -> SetYAxisTitle("Events");

  // Histogram of lepton weight
  _hLeptonSFWeight =  DeclareTH1F("leptonSFWeight","Event Weight for lepton SFs",100,0.,2.);
  _hLeptonSFWeight -> SetXAxisTitle("Lep SF");
  _hLeptonSFWeight -> SetYAxisTitle("Events");

  // Histogram of lepton weight
  _helelooseSFWeight =  DeclareTH1F("elelooseSFWeight","Event Weight for eleloose SFs",100,0.,2.);
  _helelooseSFWeight -> SetXAxisTitle("eleloose SF");
  _helelooseSFWeight -> SetYAxisTitle("Events");

  // Histogram of lepton weight
  _heletightSFWeight =  DeclareTH1F("eletightSFWeight","Event Weight for eletight SFs",100,0.,2.);
  _heletightSFWeight -> SetXAxisTitle("eletight SF");
  _heletightSFWeight -> SetYAxisTitle("Events");

  // Histogram of lepton weight
  _hmulooseSFWeight =  DeclareTH1F("mulooseSFWeight","Event Weight for muloose SFs",100,0.,2.);
  _hmulooseSFWeight -> SetXAxisTitle("muloose SF");
  _hmulooseSFWeight -> SetYAxisTitle("Events");

  // Histogram of lepton weight
  _hmutightSFWeight =  DeclareTH1F("mutightSFWeight","Event Weight for mutight SFs",100,0.,2.);
  _hmutightSFWeight -> SetXAxisTitle("mutight SF");
  _hmutightSFWeight -> SetYAxisTitle("Events");

  // Histogram of chargeMis weight
  _hChargeMis =  DeclareTH1F("ChargeMisWeight","Event Weight for chargeMis",100,0.,0.001);
  _hChargeMis -> SetXAxisTitle("Charge Mis");
  _hChargeMis -> SetYAxisTitle("Events");

  // Histogram of FakeRate weight
  _hFakeRate =  DeclareTH1F("FakeRateWeight","Event Weight for FakeRate",100,0.,0.1);
  _hFakeRate -> SetXAxisTitle("Fake Rate");
  _hFakeRate -> SetYAxisTitle("Events");

  // Histogram of Trigger weight
  _hTriggerSFs =  DeclareTH1F("TriggerWeight","Event Weight for Trigger",100,0.5,1.5);
  _hTriggerSFs -> SetXAxisTitle("TriggerSFs");
  _hTriggerSFs -> SetYAxisTitle("Events");

  // Histogram of Prefire weight
  _hPrefire =  DeclareTH1F("PrefireWeight","Event Weight for Prefire",100,0.,2);
  _hPrefire -> SetXAxisTitle("Prefire");
  _hPrefire -> SetYAxisTitle("Events");

  //Create one histogtam per b-tag systematic (and central value)
  for (auto const bTagSystName: _bTagSystNames){
    // Histogram of bTag shape weight
    _hbTagReshape[bTagSystName] =  DeclareTH1F("bTagReshape_"+bTagSystName,"bTag reshaping "+bTagSystName,100,-5.0,5.);
    _hbTagReshape[bTagSystName] -> SetXAxisTitle("bTag Reshape " + bTagSystName);
    _hbTagReshape[bTagSystName] -> SetYAxisTitle("Events");
  }

  //Create one histogtam per b-tag systematic (and central value)
  for (auto const frSystName: _frSystNames){
    // Histogram of bTag shape weight
    _hefrReweight[frSystName] =  DeclareTH1F("efrReweight_"+frSystName,"efr reweight "+frSystName,100,-5.0,5.);
    _hefrReweight[frSystName] -> SetXAxisTitle("efr reweight " + frSystName);
    _hefrReweight[frSystName] -> SetYAxisTitle("Events");
    _hmfrReweight[frSystName] =  DeclareTH1F("mfrReweight_"+frSystName,"mfr reweight "+frSystName,100,-5.0,5.);
    _hmfrReweight[frSystName] -> SetXAxisTitle("mfr reweight " + frSystName);
    _hmfrReweight[frSystName] -> SetYAxisTitle("Events");
  }

  //Create the histograms to show the gen weight of the sample.
  _hGenWeight = DeclareTH1F("genWeight","Generator level event weight",10,-2.,2.);
  _hGenWeight -> SetXAxisTitle("Gen Weight");
  _hGenWeight -> SetYAxisTitle("Events");

  // Histogram of Output Weights
  _hOutputWeight =  DeclareTH1F("OutputWeight","Output Event Weight",100,-10.,10.);
  _hOutputWeight -> SetXAxisTitle("Output Weight");
  _hOutputWeight -> SetXAxisTitle("Events");

  // Get configuration
  EventContainer *EventContainerObj =  GetEventContainer();
  TEnv* conf = EventContainerObj -> GetConfig();

  // Use configuration parameters to set weights
  TString sName = EventContainerObj -> GetSourceName();
  cout << "sName: " << sName << endl;

  Int_t sNumber = EventContainerObj -> GetSourceNumber();
  stringstream strNumber;

  strNumber<<"Weight.Source."<<sNumber;
  cout << "strNumber: " << std::str(strNumber) << endl;
  //string wq = "Weight.Source."+strNumber.str();
  //wq += strNumber.str();
  //  cout << EventContainerObj->GetEventTree()->GetEntries() << endl;
  Double_t xsecstuff = conf -> GetValue(strNumber.str().c_str(), 0.0);

  //Get the lumi of the data from the config file
  Double_t lumi = conf -> GetValue("Weight.Lumi",100);
  cout << "lumi: " << lumi << endl;

  //Now multiply the xsec by the lumi
  xsecstuff *= lumi;

  //NOTE: 0.0 is a default value.  Will assume if xsecstuff is 0.0 that there is no cross-section available and the global weight will be set to 1.0.

  if(EventContainerObj -> GetDebugLevel() > 1) {
    cout << "<EventWeight::BookHistogram>          |     Source Name:   " << std::setw(12) << sName   << "|" << endl;
    cout << "<EventWeight::BookHistogram>          |     Source Num:    " << std::setw(12) << sNumber << "|" << endl;
    cout << "<EventWeight::BookHistogram>          |     xsec*BR*lum: " << std::setw(12) << xsecstuff<< "|" << endl;

    //wgt is set in BookHistogram to the value in the weight config file.  This value should be the x-sec*BR*lum
   //The total MC events count (including MCatNLO) is divided by in this program NOT EXTERNALLY
    Double_t gwgt = xsecstuff;
    if(_totalMCatNLOEvents != 0){
      gwgt = gwgt/_totalMCatNLOEvents;
    }else{
      cout<<"_totalMCatNLOEvents is zero- check EventWeight, executable, and AnalysisMain"<<endl;
    }
  // For now set output event weight equal to global event weight, including MCatNLO if needed
    if(gwgt == 0){
      gwgt = 1.0;
    }
    EventContainerObj -> SetGlobalEventWeight(gwgt);


    cout << "<EventWeight::BookHistogram>          |     Counts + MCatNLO: " << std::setw(12) <<_totalMCatNLOEvents<< "|" << endl;
    cout << "<EventWeight::BookHistogram>          |     Global Weight: " << std::setw(12) << EventContainerObj -> GetGlobalEventWeight()<< "|" << endl;
    //	 << sName << " ("<<sNumber<<") is " << EventContainerObj -> GetGlobalEventWeight() << endl;
  } //if

  //Set up the lepton efficiency SF histograms
  if (_useLeptonSFs){
      if(_whichTrigger <=5 && _whichTrigger >=2) setLeptonHistograms(conf->GetValue("Include.MuonIDSFsFile","null"),conf->GetValue("LeptonID.MuonIDSFHistName","null"),conf->GetValue("Include.MuonISOSFsFile","null"),conf->GetValue("LeptonID.MuonIsoSFHistName","null"),conf->GetValue("Include.MuonTrigSFsFile","null"),conf->GetValue("LeptonID.MuonTrigSFHistName","null"),conf->GetValue("Include.MuonTKSFsFile","null"),conf->GetValue("Include.EleRecoFileName","null"),conf->GetValue("LeptonID.EleRecoHistName","null"),conf->GetValue("Include.EleIDFileName","null"),conf->GetValue("LeptonID.EleID_1_HistName","null"),conf->GetValue("LeptonID.EleID_2_HistName","null"),conf->GetValue("LeptonID.EleID_3_HistName","null"),conf->GetValue("Include.MuonLooseToTightSFs2lFile","null"),conf->GetValue("LeptonID.MuonLooseToTight2lHistName","null"),conf->GetValue("Include.EleLooseToTightSFs2lFile","null"),conf->GetValue("LeptonID.EleLooseToTight2lHistName","null"));
      else if(_whichTrigger >=6) setLeptonHistograms(conf->GetValue("Include.MuonIDSFsFile","null"),conf->GetValue("LeptonID.MuonIDSFHistName","null"),conf->GetValue("Include.MuonISOSFsFile","null"),conf->GetValue("LeptonID.MuonIsoSFHistName","null"),conf->GetValue("Include.MuonTrigSFsFile","null"),conf->GetValue("LeptonID.MuonTrigSFHistName","null"),conf->GetValue("Include.MuonTKSFsFile","null"),conf->GetValue("Include.EleRecoFileName","null"),conf->GetValue("LeptonID.EleRecoHistName","null"),conf->GetValue("Include.EleIDFileName","null"),conf->GetValue("LeptonID.EleID_1_HistName","null"),conf->GetValue("LeptonID.EleID_2_HistName","null"),conf->GetValue("LeptonID.EleID_3_HistName","null"),conf->GetValue("Include.MuonLooseToTightSFs3lFile","null"),conf->GetValue("LeptonID.MuonLooseToTight3lHistName","null"),conf->GetValue("Include.EleLooseToTightSFs3lFile","null"),conf->GetValue("LeptonID.EleLooseToTight3lHistName","null"));
      else { std::cout << "You want leptonSFs included in the weight but you haven't specified correct trigger type for this! Fix your config!" << std::endl;}
  }
  //Set up the lepton charge mismeasurement histograms
  if (_useChargeMis) setChargeMisHistograms(conf->GetValue("Include.ChargeMisFile","null"),conf->GetValue("ChargeMis.HistName","null"));

  //Set up the lepton fake rate histograms
  if (_useFakeRate){
    for (auto const frSystName: _frSystNames){
      setFakeRateHistograms(conf->GetValue("Include.LeptonFakeRateFile","null"),conf->GetValue("FakeRate.Muon.HistName","null"),conf->GetValue("FakeRate.Electron.HistName","null"),frSystName, frSystName);
    }
  }

  //Set up bTagReShape
  if (_usebTagReshape){
    _bTagCalib = BTagCalibration(conf->GetValue("BTaggerAlgo","CSVv2"),conf->GetValue("Include.BTagCSVFile","null"));
    _bTagCalibReader = BTagCalibrationReader(BTagEntry::OP_RESHAPING, "central",_bTagSystNames);
    _bTagCalibReader.load(_bTagCalib, BTagEntry::FLAV_B,"iterativefit");
    _bTagCalibReader.load(_bTagCalib, BTagEntry::FLAV_C,"iterativefit");
    _bTagCalibReader.load(_bTagCalib, BTagEntry::FLAV_UDSG,"iterativefit");
  }

} //BookHistogram()

/******************************************************************************
 * Bool_t EventWeight::Apply()                                                *
 *                                                                            *
 * Apply weights and fill histograms                                          *
 *                                                                            *
 * Input:  None                                                               *
 * Output: kTrue if successful                                                *
 ******************************************************************************/
Bool_t EventWeight::Apply()
{
     EventContainer *EventContainerObj = GetEventContainer();
   // Set output event weight- no difference

     EventTree* tree = EventContainerObj->GetEventTree();

  Double_t wgt = EventContainerObj -> GetGlobalEventWeight();
 Double_t mnwgt = 1;
  //
  // multiply by MCatNLO weight if desired.
 //Note that if files like data are flagged as MCatNLO, strange weights might result (negative yields...)
  if(isMCatNLO()) {
    //  cout<<"we found MCatNLO"<<endl;
    if(EventContainerObj->DoFastSim()){
      mnwgt =EventContainerObj -> GetFastSimTree() ->eventWeightMCatNLO;
    }else{
      mnwgt = 1; //EventContainerObj -> GetEventTree() -> weight;
      // For comparison
      //mnwgt = 1;
    }
    //    cout << tree->EVENT_genWeight << " " << tree->bWeight << " " << tree->PUWeight << "weight" << endl;
    //  Double_t mnwgt = EventContainerObj->GetTruthTree()->eventWeightMCatNLO;
    // cout<<"the weight is "<<mnwgt<<endl;

    // cout<<wgt<<"  "<<mnwgt<<"  "<<endl;
    wgt *= mnwgt;
    _hMCatNLOWeight->FillWithoutWeight(mnwgt);
  }

  float genWeight(1.0);
  if (tree->EVENT_genWeight < 0.) genWeight = -1.;

  wgt *= genWeight;

  // LHE weight
  TString sName = EventContainerObj -> GetSourceName();
  float LHEWeight(1.0);
  float rwgt(1.0);
  if(sName.Contains("THW")){
       //https://github.com/cms-sw/genproductions/blob/8d97961cda6fffccfa09cc245b715ce6f2b43f6f/bin/MadGraph5_aMCatNLO/cards/production/2017/13TeV/Higgs/thq_4f_ckm_LO_ctcvcp_MH/thq_4f_ckm_LO_ctcvcp_MH_reweight_card.dat
       // find the rwgt_12 and normilaze it to the sum of rwgt_i ( i=1,2...50)
       rwgt = (tree->EVENT_rWeights -> operator[](11));
       LHEWeight = rwgt/5458.47479968;
    }else if(sName.Contains("THQ")){
       rwgt = (tree->EVENT_rWeights -> operator[](11));
       LHEWeight = rwgt/8837.23781460;
    }
  //std::cout<<" rwgt : " << rwgt << " LHEWeight : " << LHEWeight<<std::endl;

  wgt *= LHEWeight;

  // multiply by PileUpWgt weight if desired.
 float pileupEventWeight(-1.0);
 float pileupMinBiasUpWeight(-1.0);
 float pileupMinBiasDownWeight(-1.0);
 float mu = 1; //(float)EventContainerObj -> GetEventTree() -> lbn;
 //eventInfo->event_ID()->lumi_block();

 // Get the pileup weight for this event
 //int isGood = PileupReweighting->getPileupWeight( mu, pileupEventWeight );

 //if ( isGood == 0 )
 //  {
 //    // Printout message
 //    // cout << "Event has a mu of " << mu
 //    //	    << " and a resulting pileup weight of " << pileupEventWeight<<endl;;
 //  }
 //else if ( isGood == -1 )
 //  {
 //    cout << "Data histogram pointer got lost"<<endl;;
 //  }
 //else if ( isGood == -2 )
 //  {
 //    cout << "MC histogram pointer got lost"<<endl;;
 //  }
 //else {
 //  cout<<"unknown error"<<endl;
 //}
 //Adjust by the total uncut event yield over total pileup weighted uncut event yield
 //pileupEventWeight = pileupEventWeight*PileupAdjust(EventContainerObj ->eventNumber, EventContainerObj ->runNumber);

 //only apply pileup weight if specified
 if(isPileUpWgt()) {
   int PVbin  = std::max(1, std::min(_mcPV->GetNbinsX(), _mcPV->GetXaxis()->FindBin(tree->trueInteractions)));
   if (_reCalPU && _mcPV->GetBinContent(PVbin) > 0){
     pileupEventWeight = _dataPV->GetBinContent(PVbin) / _mcPV->GetBinContent(PVbin);
     if (pileupEventWeight==0){
          std::cout<<" trueInteractions: "<< tree->trueInteractions << " dataPV "<< _dataPV->GetBinContent(tree->trueInteractions) << " mcPV "<< _mcPV->GetBinContent(tree->trueInteractions)<< " pileupEventWeight " << pileupEventWeight;
     }
     if (isPileupSysts()){
       pileupMinBiasUpWeight = _minBiasUpPV->GetBinContent(PVbin) / _mcPV->GetBinContent(PVbin);
       pileupMinBiasDownWeight = _minBiasDownPV->GetBinContent(PVbin) / _mcPV->GetBinContent(PVbin);
     }
   }
   /*
   if (_reCalPU && _mcPV->GetBinContent(tree->trueInteractions) > 0){
     pileupEventWeight = _dataPV->GetBinContent(tree->trueInteractions) / _mcPV->GetBinContent(tree->trueInteractions);
     if (pileupEventWeight==0){
          std::cout<<" trueInteractions: "<< tree->trueInteractions << " dataPV "<< _dataPV->GetBinContent(tree->trueInteractions) << " mcPV "<< _mcPV->GetBinContent(tree->trueInteractions)<< " pileupEventWeight " << pileupEventWeight;
     }
     if (isPileupSysts()){
       pileupMinBiasUpWeight = _minBiasUpPV->GetBinContent(tree->trueInteractions) / _mcPV->GetBinContent(tree->trueInteractions);
       pileupMinBiasDownWeight = _minBiasDownPV->GetBinContent(tree->trueInteractions) / _mcPV->GetBinContent(tree->trueInteractions);
     }
   }
   */
   else {
     pileupEventWeight = tree->PUWeight;
     pileupMinBiasUpWeight = tree->PUWeight;
     pileupMinBiasDownWeight = tree->PUWeight;
   }
   wgt *= pileupEventWeight;
 }

 float bEventWeight(1.0);

 if (isbWeight()){
   //bEventWeight = tree->bWeight;
   bEventWeight =1; // temporarily set to 1
   wgt *= bEventWeight;
 }


 float lepSFWeight(1.0), lepSFWeightUp(1.0), lepSFWeightDown(1.0);
 float elelooseSFWeight(1.0), elelooseSFWeightUp(1.0), elelooseSFWeightDown(1.0);
 float eletightSFWeight(1.0), eletightSFWeightUp(1.0), eletightSFWeightDown(1.0);
 float mulooseSFWeight(1.0), mulooseSFWeightUp(1.0), mulooseSFWeightDown(1.0);
 float mutightSFWeight(1.0), mutightSFWeightUp(1.0), mutightSFWeightDown(1.0);

 if(_useLeptonSFs){
   std::tie(lepSFWeight,lepSFWeightUp,lepSFWeightDown, elelooseSFWeight, elelooseSFWeightUp, elelooseSFWeightDown, eletightSFWeight, eletightSFWeightUp, eletightSFWeightDown, mulooseSFWeight, mulooseSFWeightUp, mulooseSFWeightDown, mutightSFWeight, mutightSFWeightUp, mutightSFWeightDown) = getLeptonWeight(EventContainerObj);
   wgt *= lepSFWeight;
 }

 float ChargeMisWeight(1.0), ChargeMisWeightUp(1.0), ChargeMisWeightDown(1.0);

 if(_useChargeMis){
   std::tie(ChargeMisWeight,ChargeMisWeightUp,ChargeMisWeightDown) = getChargeMisWeight(EventContainerObj);
   //std::cout << EventContainerObj->eventNumber <<" "<<ChargeMisWeight <<"  " << ChargeMisWeightUp << "  " <<ChargeMisWeightDown << std::endl;
   wgt *= ChargeMisWeight;
 }

 float PrefireWeight(1.0), PrefireWeightUp(1.0), PrefireWeightDown(1.0);

 if(_usePrefire){
   PrefireWeight = tree -> EVENT_prefireWeight;
   PrefireWeightUp = tree -> EVENT_prefireWeightUp;
   PrefireWeightDown = tree -> EVENT_prefireWeightDown;
   //std::cout << EventContainerObj->eventNumber <<" "<<PrefireWeight <<"  " << PrefireWeightUp << "  " <<PrefireWeightDown << std::endl;
   wgt *= PrefireWeight;
 }

 float TriggerWeight(1.0), TriggerWeightUp(1.0), TriggerWeightDown(1.0);

 if(_useTriggerSFs){
   std::tie(TriggerWeight,TriggerWeightUp,TriggerWeightDown) = getTriggerWeight(EventContainerObj);
   //std::cout << EventContainerObj->eventNumber <<" " <<TriggerWeight <<"  " << TriggerWeightUp << "  " <<TriggerWeightDown << std::endl;
   wgt *= TriggerWeight;
 }

 std::map<std::string,float> mFakeRate;
 std::map<std::string,float> eFakeRate;
 float FakeRateWeight(1.0);

 if(_useFakeRate){
   FakeRateWeight = getFakeRateWeight(EventContainerObj);
   for(auto const frSystName: _frSystNames){
    mFakeRate[frSystName] = getFakeRateWeight(EventContainerObj,frSystName,"central");
    eFakeRate[frSystName] = getFakeRateWeight(EventContainerObj,"central",frSystName);
   }
   //std::cout << EventContainerObj->eventNumber <<" " <<FakeRateWeight <<"  " << FakeRateWeightUp << "  " <<FakeRateWeightDown << std::endl;
   wgt *= FakeRateWeight;
 }

 std::map<std::string,float> bTagReshape;

 if (_usebTagReshape){
   for (auto const bSystName: _bTagSystNames) bTagReshape[bSystName] = getBTagReshape(EventContainerObj,bSystName);
   wgt *= bTagReshape["central"];
 }


 // if(isPileUpWgt()) {
    //This version is based on primary vertex number and no longer used
    /**
    if(EventContainerObj->DoFastSim()){
      mnwgt = 1;
    }else{
      int n = EventContainerObj -> nPvtx;
      if(n>9) n=9; // Number of vertex >9 use the weight of nPvtx = 9
      mnwgt = vecPileUpWgt.at(n);
    }
    wgt *= mnwgt;
    _hPileUpWgtWeight->FillWithoutWeight(mnwgt);
    **/
 // }
 // cout << wgt << endl;
  EventContainerObj -> SetOutputEventWeight(wgt);
  EventContainerObj -> SetEventPileupWeight(pileupEventWeight);
  //Save systematic pileup weights
  EventContainerObj -> SetEventPileupMinBiasUpWeight(pileupMinBiasUpWeight);
  EventContainerObj -> SetEventPileupMinBiasDownWeight(pileupMinBiasDownWeight);
  EventContainerObj -> SetEventbWeight(bEventWeight);
  EventContainerObj -> SetEventLepSFWeight(lepSFWeight);
  EventContainerObj -> SetEventelelooseSFWeight(elelooseSFWeight);
  EventContainerObj -> SetEventeletightSFWeight(eletightSFWeight);
  EventContainerObj -> SetEventmulooseSFWeight(mulooseSFWeight);
  EventContainerObj -> SetEventmutightSFWeight(mutightSFWeight);
  EventContainerObj -> SetGenWeight(genWeight);
  for (auto const bSystName: _bTagSystNames) EventContainerObj -> SetEventbTagReshape(bTagReshape[bSystName],bSystName);

  for (auto const frSystName: _frSystNames){
    EventContainerObj -> SetEventmfrReweight(mFakeRate[frSystName],frSystName);
    EventContainerObj -> SetEventefrReweight(eFakeRate[frSystName],frSystName);
  }

  EventContainerObj -> SetEventFakeRateWeight(FakeRateWeight);

  EventContainerObj -> SetEventLepSFWeightUp(lepSFWeightUp);
  EventContainerObj -> SetEventLepSFWeightDown(lepSFWeightDown);
  EventContainerObj -> SetEventelelooseSFWeightUp(elelooseSFWeightUp);
  EventContainerObj -> SetEventelelooseSFWeightDown(elelooseSFWeightDown);
  EventContainerObj -> SetEventeletightSFWeightUp(eletightSFWeightUp);
  EventContainerObj -> SetEventeletightSFWeightDown(eletightSFWeightDown);
  EventContainerObj -> SetEventmulooseSFWeightUp(mulooseSFWeightUp);
  EventContainerObj -> SetEventmulooseSFWeightDown(mulooseSFWeightDown);
  EventContainerObj -> SetEventmutightSFWeightUp(mutightSFWeightUp);
  EventContainerObj -> SetEventmutightSFWeightDown(mutightSFWeightDown);

  EventContainerObj -> SetEventChargeMisWeight(ChargeMisWeight);
  EventContainerObj -> SetEventChargeMisWeightUp(ChargeMisWeightUp);
  EventContainerObj -> SetEventChargeMisWeightDown(ChargeMisWeightDown);

  EventContainerObj -> SetEventPrefireWeight(PrefireWeight);
  EventContainerObj -> SetEventPrefireWeightUp(PrefireWeightUp);
  EventContainerObj -> SetEventPrefireWeightDown(PrefireWeightDown);

  EventContainerObj -> SetEventTriggerWeight(TriggerWeight);
  EventContainerObj -> SetEventTriggerWeightUp(TriggerWeightUp);
  EventContainerObj -> SetEventTriggerWeightDown(TriggerWeightDown);

  EventContainerObj -> SetEventLHEWeight(LHEWeight);
  //Also save the systematic variations in these SFs
  //  EventContainerObj -> SetEventLepSFWeightUp(lepSFWeightUp);
  //EventContainerObj -> SetEventLepSFWeightDown(lepSFWeightDown);
  //  cout<<"weight "<<EventContainerObj -> GetOutputEventWeight()<<endl;;
  // Fill Histograms

  _hTreeWeight     -> FillWithoutWeight(EventContainerObj -> GetTreeEventWeight());
  _hGlobalWeight   -> FillWithoutWeight(EventContainerObj -> GetGlobalEventWeight());
  _hOutputWeight   -> FillWithoutWeight(EventContainerObj -> GetEventWeight());
  _hPileUpWeight   -> FillWithoutWeight(EventContainerObj -> GetEventPileupWeight());
  _hbWeight	   -> FillWithoutWeight(EventContainerObj -> GetEventbWeight());
  _hLeptonSFWeight -> FillWithoutWeight(EventContainerObj -> GetEventLepSFWeight());
  _helelooseSFWeight -> FillWithoutWeight(EventContainerObj -> GetEventelelooseSFWeight());
  _heletightSFWeight -> FillWithoutWeight(EventContainerObj -> GetEventeletightSFWeight());
  _hmulooseSFWeight -> FillWithoutWeight(EventContainerObj -> GetEventmulooseSFWeight());
  _hmutightSFWeight -> FillWithoutWeight(EventContainerObj -> GetEventmutightSFWeight());
  _hGenWeight	   -> FillWithoutWeight(EventContainerObj -> GetGenWeight());
  _hChargeMis -> FillWithoutWeight(EventContainerObj -> GetEventChargeMisWeight());
  _hPrefire -> FillWithoutWeight(EventContainerObj -> GetEventPrefireWeight());
  _hFakeRate -> FillWithoutWeight(EventContainerObj -> GetEventFakeRateWeight());
  _hTriggerSFs -> FillWithoutWeight(EventContainerObj -> GetEventTriggerWeight());
  for (auto const bSystName: _bTagSystNames) _hbTagReshape[bSystName] -> FillWithoutWeight(EventContainerObj -> GetEventbTagReshape(bSystName));
  for (auto const frSystName: _frSystNames){
      _hefrReweight[frSystName] -> FillWithoutWeight(EventContainerObj -> GetEventmfrReweight(frSystName));
      _hmfrReweight[frSystName] -> FillWithoutWeight(EventContainerObj -> GetEventefrReweight(frSystName));
  }
  return kTRUE;

} //Apply

//Used to set up the efficiency histograms for the first time
/******************************************************************************
 * Bool_t EventWeight::setLeptonHistograms()                                  *
 *                                                                            *
 * Sets up the histograms that will be used for lepton SF reweighting         *
 *                                                                            *
 * Input:  Names of files and histograms that are relevant to the calculation *
 * Output: none                                                               *
 ******************************************************************************/
void EventWeight::setLeptonHistograms(TString muonIDFileName, TString muonIDHistName, TString muonIsoFileName, TString muonIsoHistName, TString muonTrigFileName, TString muonTrigHistName, TString muonTkFileName, TString eleRecoFileName, TString eleRecoHistName, TString eleIDFileName, TString eleID_1_HistName, TString eleID_2_HistName, TString eleID_3_HistName, TString muonLooseToTightFileName, TString muonLooseToTightHistName, TString eleLooseToTightFileName, TString eleLooseToTightHistName){
  //if (muonIsoFileName == "null" || muonIDFileName == "null"){
  //  std::cout << "You want lepton SFs included in the weight but you haven't specified files for this! Fix your config!" << std::endl;
  //}

  //std::cout << " before muonID " << std::endl;
  //TFile* muonIDFile = NULL;
  //if(muonIDFileName!="null") muonIDFile = TFile::Open(muonIDFileName,"READ");
  TFile* muonIDLptFile = NULL;
  TFile* muonIDHptFile = NULL;
  if(muonIDFileName!="null"){
      muonIDLptFile = TFile::Open("config/weights/ttH2018/mu_scaleFactors_ptLt30.root","READ");
      muonIDHptFile = TFile::Open("config/weights/ttH2018/mu_scaleFactors_ptGt30.root","READ");
  }
  if(muonIDLptFile){
    _muonIDSFLpt = (TH2F*)muonIDLptFile->Get(muonIDHistName)->Clone();
    _muonIDSFLpt->SetDirectory(0);
    muonIDLptFile->Close();

    _muonIDSFHpt = (TH2F*)muonIDHptFile->Get(muonIDHistName)->Clone();
    _muonIDSFHpt->SetDirectory(0);
    muonIDHptFile->Close();
  }else{
      std::cout << "Muon ID file not found!" << std::endl;
  }

  TFile* muonIsoFile = NULL;
  //std::cout << " before muonIso " << std::endl;
  if(muonIsoFileName!="null") muonIsoFile = TFile::Open(muonIsoFileName,"READ");
  if (muonIsoFile){
    _muonIsoSF = (TH2F*)muonIsoFile->Get(muonIsoHistName)->Clone();
    _muonIsoSF->SetDirectory(0);
    muonIsoFile->Close();
  }else{
    std::cout << "Muon iso file not found!" << std::endl;
  }

  TFile* muonTrigFile = NULL;
  //std::cout << " before muonTrig " << std::endl;
  if(muonTrigFileName!="null") muonTrigFile = TFile::Open(muonTrigFileName,"READ");
  if(muonTrigFile){
    _muonTrigSF = (TH2F*)muonTrigFile->Get(muonTrigHistName)->Clone();
    _muonTrigSF->SetDirectory(0);
    muonTrigFile->Close();
  }else{
    std::cout << "Muon trig file not found!" << std::endl;
  }

  //TFile* muonTkFile = NULL;
  //if(muonTkFileName!="null") muonTkFile = TFile::Open(muonTkFileName,"READ");
  TFile* muonTkLptFile = NULL;
  TFile* muonTkHptFile = NULL;
  if(muonTkFileName!="null"){
      muonTkLptFile = TFile::Open("config/weights/ttH2018/mu_scaleFactors_trkEff_ptLt10.root","READ");
      muonTkHptFile = TFile::Open("config/weights/ttH2018/mu_scaleFactors_trkEff_ptGt10.root","READ");
  }
  if (muonTkLptFile){
    _muonTkSFLpt = (TGraphAsymmErrors*)muonTkLptFile->Get("ratio_eff_eta3_tk0_dr030e030_corr")->Clone();
    //  _muonTkSFLpt->SetDirectory(0);
    muonTkLptFile->Close();
    _muonTkSFHpt = (TGraphAsymmErrors*)muonTkHptFile->Get("ratio_eff_eta3_dr030e030_corr")->Clone();
    //  _muonTkSFHpt->SetDirectory(0);
    muonTkHptFile->Close();
  }else{
      std::cout << "Muon tracker file not found!" << std::endl;
  }

  //std::cout << " before eleReco " << std::endl;
  //TFile* eleRecoFile = NULL;
  //if(eleRecoFileName!="null") eleRecoFile = TFile::Open(eleRecoFileName,"READ");
  TFile* eleRecoLptFile = NULL;
  TFile* eleRecoHptFile = NULL;
  if(eleRecoFileName!="null"){
      eleRecoLptFile = TFile::Open("config/weights/ttH2018/el_scaleFactors_gsf_ptLt20.root","READ");
      eleRecoHptFile = TFile::Open("config/weights/ttH2018/el_scaleFactors_gsf_ptGt20.root","READ");
  }
  if(eleRecoLptFile){
    _eleRecoSFLpt = (TH2F*)eleRecoLptFile->Get(eleRecoHistName)->Clone();
    _eleRecoSFLpt->SetDirectory(0);
    _eleRecoSFHpt = (TH2F*)eleRecoHptFile->Get(eleRecoHistName)->Clone();
    _eleRecoSFHpt->SetDirectory(0);
    eleRecoLptFile->Close();
    eleRecoHptFile->Close();
  }else{
    std::cout << "Electron reco SF file not found!" << std::endl;
  }

  //std::cout << " before eleID " << std::endl;
  TFile* eleIDFile = NULL;
  if(eleIDFileName!="null") eleIDFile = TFile::Open(eleIDFileName,"READ");
  if(eleIDFile){
    _eleID1SF = (TH2F*)eleIDFile->Get(eleID_1_HistName)->Clone();
    _eleID1SF->SetDirectory(0);
    //_eleID2SF = (TH2F*)eleIDFile->Get(eleID_2_HistName)->Clone();
    //_eleID2SF->SetDirectory(0);
    //_eleID3SF = (TH2F*)eleIDFile->Get(eleID_3_HistName)->Clone();
    //_eleID3SF->SetDirectory(0);
    eleIDFile->Close();
  }else{
     std::cout << "Electron ID SF file not found!" << std::endl;
  }


  TFile* muonLooseToTightFile = NULL;
  //std::cout << " before muonLooseToTightFile " << std::endl;
  if(muonLooseToTightFileName!="null") muonLooseToTightFile = TFile::Open(muonLooseToTightFileName,"READ");
  if (muonLooseToTightFile){
  //std::cout << " before muonLooseToTightHist " << std::endl;
    _muonLooseToTightSF = (TH2F*)muonLooseToTightFile->Get(muonLooseToTightHistName)->Clone();
    _muonLooseToTightSF->SetDirectory(0);
    muonLooseToTightFile->Close();
  }else{
    std::cout << "Muon looseToTight file not found!" << std::endl;
  }

  //std::cout << " before eleLooseToTight " << std::endl;
  TFile* eleLooseToTightFile = NULL;
  if(eleLooseToTightFileName!="null") eleLooseToTightFile = TFile::Open(eleLooseToTightFileName,"READ");
  if (eleLooseToTightFile){
    //std::cout<< "ele hist name " << eleLooseToTightHistName << std::endl;
    _eleLooseToTightSF = (TH2F*)eleLooseToTightFile->Get(eleLooseToTightHistName)->Clone();
    //_eleLooseToTightSF = (TH2F*)eleLooseToTightFile->Get("sf")->Clone();
    _eleLooseToTightSF->SetDirectory(0);
    eleLooseToTightFile->Close();
  }else{
    std::cout << "Ele looseToTight file not found!" << std::endl;
  }

  //delete muonIsoFile,muonIDFile,muonTrigFile,muonTkFile,eleRecoFile,eleIDFile, muonLooseToTightFile, eleLooseToTightFile;
  delete muonIsoFile,muonIDLptFile,muonIDHptFile,muonTrigFile,muonTkLptFile,muonTkHptFile,eleRecoLptFile,eleRecoHptFile,eleIDFile, muonLooseToTightFile, eleLooseToTightFile;

}

/******************************************************************************
 * Bool_t EventWeight::getLeptonWeight()                                      *
 *                                                                            *
 * Get the relevant pt and eta dependent SFs for the leptons in the event     *
 * and put them into one weight that is returned                              *
 *                                                                            *
 * Input:  None                                                               *
 * Output: Double_t weight to be applied to the event weight                  *
 ******************************************************************************/
std::tuple<Double_t,Double_t, Double_t, Double_t, Double_t,Double_t,Double_t,Double_t, Double_t,Double_t,Double_t,Double_t, Double_t,Double_t,Double_t> EventWeight::getLeptonWeight(EventContainer * EventContainerObj){

  Double_t leptonWeight = 1.0, leptonWeightUp = 1.0, leptonWeightDown = 1.0;
  Double_t elelooseWeight = 1.0, elelooseWeightUp = 1.0, elelooseWeightDown = 1.0;
  Double_t eletightWeight = 1.0, eletightWeightUp = 1.0, eletightWeightDown = 1.0;
  Double_t mulooseWeight = 1.0, mulooseWeightUp = 1.0, mulooseWeightDown = 1.0;
  Double_t mutightWeight = 1.0, mutightWeightUp = 1.0, mutightWeightDown = 1.0;
  if(_whichTrigger <=7 && _whichTrigger >=2 ){//if it is ttH category
    for(auto const & lep: *EventContainerObj->leptonsToUsePtr){
        Float_t _L1_SF = 1.0, _L1_SFUnc =0.;//iso; id1
        Float_t _L2_SF = 1.0, _L2_SFUnc =0.;//id; id2
        Float_t _L3_SF = 1.0, _L3_SFUnc =0.;//trig; id3
        Float_t _L4_SF = 1.0, _L4_SFUnc =0.;//tk; gsf
        Float_t _ttH_SF = 1.0, _ttH_SFUnc =0.;
        if(lep.isMVASel() < 0.5) continue;
        if(fabs(lep.pdgId())==13){
            // get iso
            int ptbin, etabin;
            if(_muonIsoSF){
                ptbin  = std::max(1, std::min(_muonIsoSF->GetNbinsX(), _muonIsoSF->GetXaxis()->FindBin(lep.Pt())));
                etabin = std::max(1, std::min(_muonIsoSF->GetNbinsY(), _muonIsoSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
                _L1_SF = _muonIsoSF->GetBinContent(ptbin, etabin);
                _L1_SFUnc = _muonIsoSF->GetBinError(ptbin, etabin);
                /*
                if(_L1_SF<0.01) {
                    std::cout<< " mu _L1_SF +/- Uncerntainty " << _L1_SF <<" +/- "<< _L1_SFUnc<< std::endl;
                }
                */
            }
            // id
            if(_muonIDSFLpt){
                if(lep.Pt()<30){
                    ptbin  = std::max(1, std::min(_muonIDSFLpt->GetNbinsX(), _muonIDSFLpt->GetXaxis()->FindBin(lep.Pt())));
                    //etabin = std::max(1, std::min(_muonIDSFLpt->GetNbinsY(), _muonIDSFLpt->GetYaxis()->FindBin(fabs(lep.Eta()))));
                    etabin = std::max(1, std::min(_muonIDSFLpt->GetNbinsY(), _muonIDSFLpt->GetYaxis()->FindBin(std::min(fabs(lep.Eta()),2.09))));
                    _L2_SF = _muonIDSFLpt->GetBinContent(ptbin, etabin);
                    _L2_SFUnc = _muonIDSFLpt->GetBinError(ptbin, etabin);
                }else{
                    ptbin  = std::max(1, std::min(_muonIDSFHpt->GetNbinsX(), _muonIDSFHpt->GetXaxis()->FindBin(lep.Pt())));
                    etabin = std::max(1, std::min(_muonIDSFHpt->GetNbinsY(), _muonIDSFHpt->GetYaxis()->FindBin(fabs(lep.Eta()))));
                    _L2_SF = _muonIDSFHpt->GetBinContent(ptbin, etabin);
                    _L2_SFUnc = _muonIDSFHpt->GetBinError(ptbin, etabin);
                }
                //if(_L2_SF<0.01) {
                    //std::cout<< " mu _L2_SF +/- Uncerntainty " << _L2_SF <<" +/- "<< _L2_SFUnc<< std::endl;
                //}
            }
            // get trig
            if(_muonTrigSF){
                ptbin  = std::max(1, std::min(_muonTrigSF->GetNbinsX(), _muonTrigSF->GetXaxis()->FindBin(lep.Pt())));
                etabin = std::max(1, std::min(_muonTrigSF->GetNbinsY(), _muonTrigSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
                _L3_SF = _muonTrigSF->GetBinContent(ptbin, etabin);
                _L3_SFUnc = _muonTrigSF->GetBinError(ptbin, etabin);
                /*
                if(_L3_SF<0.01) {
                    std::cout<< " mu _L3_SF +/- Uncerntainty " << _L3_SF <<" +/- "<< _L3_SFUnc<< std::endl;
                }
                */
            }
            // get Tk SF
            double eta1;
            if(_muonTkSFLpt){
                if(lep.Pt()<10){
                    eta1 = std::max(float(_muonTkSFLpt->GetXaxis()->GetXmin()+1e-5), std::min(float(_muonTkSFLpt->GetXaxis()->GetXmax()-1e-5), float(lep.Eta())));
                    _L4_SF = _muonTkSFLpt->Eval(eta1);
                }else{
                    eta1 = std::max(float(_muonTkSFHpt->GetXaxis()->GetXmin()+1e-5), std::min(float(_muonTkSFHpt->GetXaxis()->GetXmax()-1e-5), float(lep.Eta())));
                    _L4_SF = _muonTkSFHpt->Eval(eta1);
                }
                /*
                if(_L4_SF<0.01) {
                    std::cout<< " mu _L4_SF +/- Uncerntainty " << _L4_SF <<" +/- "<< _L4_SFUnc<< std::endl;
                }
                */
            }
            //get ttH SF
            if(_muonLooseToTightSF){
                ptbin  = std::max(1, std::min(_muonLooseToTightSF->GetNbinsX(), _muonLooseToTightSF->GetXaxis()->FindBin(lep.Pt())));
                etabin = std::max(1, std::min(_muonLooseToTightSF->GetNbinsY(), _muonLooseToTightSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
                _ttH_SF = _muonLooseToTightSF->GetBinContent(ptbin, etabin);
                _ttH_SFUnc = _muonLooseToTightSF->GetBinError(ptbin, etabin);
               // std::cout<< " mu _ttH_SF +/- Uncerntainty " << _ttH_SF <<" +/- "<< _ttH_SFUnc<< std::endl;
            }
            mulooseWeight *= _L1_SF * _L2_SF * _L3_SF * _L4_SF ;
            mulooseWeightUp *= (_L1_SF + _L1_SFUnc) * (_L2_SF + _L2_SFUnc) * (_L3_SF + _L3_SFUnc) * (_L4_SF+_L4_SFUnc);
            mulooseWeightDown *= (_L1_SF - _L1_SFUnc) * (_L2_SF - _L2_SFUnc) * (_L3_SF - _L3_SFUnc) * ( _L4_SF - _L4_SFUnc);
            mutightWeight *=  _ttH_SF ;
            mutightWeightUp *= ( _ttH_SF + _ttH_SFUnc);
            mutightWeightDown *= ( _ttH_SF - _ttH_SFUnc);
                if(mulooseWeight<0.01) {
                 std::cout<< " mu looseWeight / Up/ Down " << mulooseWeight <<" / "<< mulooseWeightUp << " / "<<mulooseWeightDown << std::endl;
                 std::cout<< " mu tightWeight / Up/ Down " << mutightWeight <<" / "<< mutightWeightUp << " / "<<mutightWeightDown << std::endl;
                 std::cout<< " mu pt/eta " << lep.Pt() << " / " << lep.Eta()<<std::endl;
                }
        }else{
            //get id1
            int ptbin, etabin;
            if(_eleID1SF){
                etabin  = std::max(1, std::min(_eleID1SF->GetNbinsX(), _eleID1SF->GetXaxis()->FindBin(lep.Eta())));
                ptbin = std::max(1, std::min(_eleID1SF->GetNbinsY(), _eleID1SF->GetYaxis()->FindBin(lep.Pt())));
                _L1_SF = _eleID1SF->GetBinContent(etabin, ptbin);
                _L1_SFUnc = _eleID1SF->GetBinError(etabin, ptbin);
               //  std::cout<< " ele _L1_SF +/- Uncerntainty " << _L1_SF <<" +/- "<< _L1_SFUnc<< std::endl;
            }
            //get id2
            if(_eleID2SF){
                ptbin  = std::max(1, std::min(_eleID2SF->GetNbinsX(), _eleID2SF->GetXaxis()->FindBin(lep.Pt())));
                etabin = std::max(1, std::min(_eleID2SF->GetNbinsY(), _eleID2SF->GetYaxis()->FindBin(lep.Eta())));
                _L2_SF = _eleID2SF->GetBinContent(ptbin, etabin);
                _L2_SFUnc = _eleID2SF->GetBinError(ptbin, etabin);
               //  std::cout<< " ele _L2_SF +/- Uncerntainty " << _L2_SF <<" +/- "<< _L2_SFUnc<< std::endl;
            }
            //get id3
            if(_eleID3SF){
                ptbin  = std::max(1, std::min(_eleID3SF->GetNbinsX(), _eleID3SF->GetXaxis()->FindBin(lep.Pt())));
                etabin = std::max(1, std::min(_eleID3SF->GetNbinsY(), _eleID3SF->GetYaxis()->FindBin(lep.Eta())));
                _L3_SF = _eleID3SF->GetBinContent(ptbin, etabin);
                _L3_SFUnc = _eleID3SF->GetBinError(ptbin, etabin);
               //  std::cout<< " ele _L3_SF +/- Uncerntainty " << _L3_SF <<" +/- "<< _L3_SFUnc<< std::endl;
            }
            //get reco be careful of swapped pt eta bin
            if(_eleRecoSFLpt){
                if(lep.Pt()<20){
                    ptbin  = std::max(1, std::min(_eleRecoSFLpt->GetNbinsY(), _eleRecoSFLpt->GetYaxis()->FindBin(lep.Pt())));
                    etabin = std::max(1, std::min(_eleRecoSFLpt->GetNbinsX(), _eleRecoSFLpt->GetXaxis()->FindBin(lep.Eta())));
                    _L4_SF = _eleRecoSFLpt->GetBinContent(etabin, ptbin);
                    _L4_SFUnc = _eleRecoSFLpt->GetBinError(etabin, ptbin);
                }else{
                    ptbin  = std::max(1, std::min(_eleRecoSFHpt->GetNbinsY(), _eleRecoSFHpt->GetYaxis()->FindBin(lep.Pt())));
                    etabin = std::max(1, std::min(_eleRecoSFHpt->GetNbinsX(), _eleRecoSFHpt->GetXaxis()->FindBin(lep.Eta())));
                    _L4_SF = _eleRecoSFHpt->GetBinContent(etabin, ptbin);
                    _L4_SFUnc = _eleRecoSFHpt->GetBinError(etabin, ptbin);
                }
               //  std::cout<< " ele _L4_SF +/- Uncerntainty " << _L4_SF <<" +/- "<< _L4_SFUnc<< std::endl;
            }
            //get ttH SF
            if(_eleLooseToTightSF){
                ptbin  = std::max(1, std::min(_eleLooseToTightSF->GetNbinsX(), _eleLooseToTightSF->GetXaxis()->FindBin(lep.Pt())));
                etabin = std::max(1, std::min(_eleLooseToTightSF->GetNbinsY(), _eleLooseToTightSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
                _ttH_SF = _eleLooseToTightSF->GetBinContent(ptbin, etabin);
                _ttH_SFUnc = _eleLooseToTightSF->GetBinError(ptbin, etabin);
                //    std::cout<< " ele _ttH_SF +/- Uncerntainty " << _ttH_SF <<" +/- "<< _ttH_SFUnc<< std::endl;
            }
            elelooseWeight *= _L1_SF * _L2_SF * _L3_SF * _L4_SF ;
            elelooseWeightUp *= (_L1_SF + _L1_SFUnc) * (_L2_SF + _L2_SFUnc) * (_L3_SF + _L3_SFUnc) * (_L4_SF+_L4_SFUnc);
            elelooseWeightDown *= (_L1_SF - _L1_SFUnc) * (_L2_SF - _L2_SFUnc) * (_L3_SF - _L3_SFUnc) * ( _L4_SF - _L4_SFUnc);
            eletightWeight *=  _ttH_SF ;
            eletightWeightUp *= ( _ttH_SF + _ttH_SFUnc);
            eletightWeightDown *= ( _ttH_SF - _ttH_SFUnc);
                // std::cout<< " ele looseWeight / Up/ Down " << elelooseWeight <<" / "<< elelooseWeightUp << " / "<<elelooseWeightDown << std::endl;
                //  std::cout<< " ele tightWeight / Up/ Down " << eletightWeight <<" / "<< eletightWeightUp << " / "<<eletightWeightDown << std::endl;
        }
        leptonWeight *= _L1_SF * _L2_SF * _L3_SF * _L4_SF * _ttH_SF ;
        leptonWeightUp *= (_L1_SF + _L1_SFUnc) * (_L2_SF + _L2_SFUnc) * (_L3_SF + _L3_SFUnc) * (_L4_SF+_L4_SFUnc) * ( _ttH_SF + _ttH_SFUnc);
        leptonWeightDown *= (_L1_SF - _L1_SFUnc) * (_L2_SF - _L2_SFUnc) * (_L3_SF - _L3_SFUnc) * ( _L4_SF - _L4_SFUnc) * ( _ttH_SF - _ttH_SFUnc);
    }
  }
  else {
    for (auto const & muon : *EventContainerObj->muonsToUsePtr){
      //Get the bin shared by iso and id SFs
      Int_t xAxisBin = _muonIsoSF->GetXaxis()->FindBin(muon.Pt());
      if (muon.Pt() > 120.) xAxisBin = _muonIsoSF->GetXaxis()->FindBin(119.);
      Int_t yAxisBin = _muonIsoSF->GetYaxis()->FindBin(std::fabs(muon.Eta()));
      if (std::fabs(muon.Eta()) > 2.4) yAxisBin = _muonIsoSF->GetYaxis()->FindBin(2.39);
      //And now get the iso and id SFs/uncs
      Float_t isoSF = _muonIsoSF->GetBinContent(xAxisBin,yAxisBin);
      Float_t isoUnc = _muonIsoSF->GetBinError(xAxisBin,yAxisBin);
      Float_t idSF = _muonIDSFLpt->GetBinContent(xAxisBin,yAxisBin);
      Float_t idUnc = _muonIDSFLpt->GetBinError(xAxisBin,yAxisBin);

      //Get the bin for trigger SF
      Int_t xAxisBinTrig = _muonTrigSF->GetXaxis()->FindBin(muon.Pt());
      if (muon.Pt() > 500.) xAxisBinTrig = _muonTrigSF->GetXaxis()->FindBin(499.);
      Int_t yAxisBinTrig = _muonTrigSF->GetYaxis()->FindBin(std::fabs(muon.Eta()));
      if (std::fabs(muon.Eta()) > 2.4) yAxisBinTrig = _muonTrigSF->GetYaxis()->FindBin(2.39);
      //Get the trigSF
      Float_t trigSF = _muonTrigSF->GetBinContent(xAxisBinTrig,yAxisBinTrig);
      Float_t trigUnc = _muonTrigSF->GetBinError(xAxisBinTrig,yAxisBinTrig);

      //Evaluate muon tk
      Float_t tkSF = _muonTkSFLpt->Eval(std::fabs(muon.Eta()));

      leptonWeight *= isoSF * idSF * trigSF * tkSF;
      leptonWeightUp *= (isoSF + isoUnc) * (idSF + idUnc) * (trigSF + trigUnc) * tkSF;
      leptonWeightDown *= (isoSF - isoUnc) * (idSF - idUnc) * (trigSF - trigUnc) * tkSF;
    }

    for (auto const & ele : *EventContainerObj->electronsToUsePtr){
      //Get which bins we're in need of for the reco SF
      Int_t xAxisBin = _eleRecoSFLpt->GetXaxis()->FindBin(ele.scEta());
      if (ele.scEta() > 2.5) xAxisBin = _eleRecoSFLpt->GetXaxis()->FindBin(2.49);
      Int_t yAxisBin = _eleRecoSFLpt->GetYaxis()->FindBin(ele.Pt());
      if (ele.Pt() > 500) xAxisBin = _eleRecoSFLpt->GetYaxis()->FindBin(499.);
      //Now get the reco and id SFs
      Float_t recoSF = _eleRecoSFLpt->GetBinContent(xAxisBin,yAxisBin);
      Float_t recoUnc = _eleRecoSFLpt->GetBinError(xAxisBin,yAxisBin);
      //Now do ID
      xAxisBin = _eleID1SF->GetXaxis()->FindBin(ele.scEta());
      if (ele.scEta() > 2.5) xAxisBin = _eleID1SF->GetXaxis()->FindBin(2.49);
      yAxisBin = _eleID1SF->GetYaxis()->FindBin(ele.Pt());
      if (ele.Pt() > 500) xAxisBin = _eleID1SF->GetYaxis()->FindBin(499.);
      Float_t idSF = _eleID1SF->GetBinContent(xAxisBin,yAxisBin);
      Float_t idUnc = _eleID1SF->GetBinError(xAxisBin,yAxisBin);
      if (_verbose) std::cout << "Reco: " << recoSF << " ID: " << idSF << " x: " << xAxisBin << " y: " << yAxisBin <<std::endl;
      leptonWeight *= recoSF * idSF;
      leptonWeightUp *= (recoSF + recoUnc) * (idSF + idUnc);
      leptonWeightDown *= (recoSF - recoUnc) * (idSF - idUnc);
    }
  }

  return std::make_tuple(leptonWeight,leptonWeightUp,leptonWeightDown, elelooseWeight, elelooseWeightUp, elelooseWeightDown, eletightWeight, eletightWeightUp, eletightWeightDown, mulooseWeight, mulooseWeightUp, mulooseWeightDown, mutightWeight, mutightWeightUp, mutightWeightDown) ;
}

//Used to set up the efficiency histograms for the first time
/******************************************************************************
 * void EventWeight::setChargeMisHistograms()                                  *
 *                                                                            *
 * Sets up the histograms that will be used for charge mis measurement weighting         *
 *                                                                            *
 * Input:  Names of files and histograms that are relevant to the calculation *
 * Output: none                                                               *
 ******************************************************************************/
void EventWeight::setChargeMisHistograms(TString ChargeMisFileName,TString ChargeMisHistName){
  if (ChargeMisFileName == "null" || ChargeMisHistName == "null"){
    std::cout << "You want charge mismeasurement included in the weight but you haven't specified files for this! Fix your config!" << std::endl;
  }
  TFile* ChargeMisFile = TFile::Open(ChargeMisFileName,"READ");
  if (!ChargeMisFile) std::cout << "ChargeMis file not found!" << std::endl;
  _chargeMis = (TH2F*)ChargeMisFile->Get(ChargeMisHistName)->Clone();
  _chargeMis->SetDirectory(0);
  ChargeMisFile->Close();

  delete ChargeMisFile;
}

/******************************************************************************
 * Bool_t EventWeight::getChargeMisWeight()                                      *
 *                                                                            *
 * Get the relevant pt and eta dependent chargeMis for the leptons in the event     *
 * and put them into one weight that is returned                              *
 *                                                                            *
 * Input:  None                                                               *
 * Output: Double_t weight to be applied to the event weight                  *
 ******************************************************************************/
std::tuple<Double_t,Double_t,Double_t> EventWeight::getChargeMisWeight(EventContainer* EventContainerObj){

  Double_t ChargeMisWeight = 1., ChargeMisWeightUp = 1., ChargeMisWeightDown = 1.;
  if(EventContainerObj->fakeleptonsVetoPtr->size()<2) return std::make_tuple(ChargeMisWeight,ChargeMisWeightUp,ChargeMisWeightDown);
  Lepton lep1 =  EventContainerObj->fakeleptonsVetoPtr->at(0);
  Lepton lep2 =  EventContainerObj->fakeleptonsVetoPtr->at(1);
  if(lep1.charge()==lep2.charge()) return std::make_tuple(ChargeMisWeight,ChargeMisWeightUp,ChargeMisWeightDown);
  Double_t ChargeMisWeight1 = 0.;
  Double_t ChargeMisUnc1 = 0.;
  Double_t ChargeMisWeight2 = 0.;
  Double_t ChargeMisUnc2 = 0.;
  if(fabs(lep1.pdgId())==11){
    //Get the bin
    int xAxisBin1  = std::max(1, std::min(_chargeMis->GetNbinsX(), _chargeMis->GetXaxis()->FindBin(lep1.conept())));
    int yAxisBin1  = std::max(1, std::min(_chargeMis->GetNbinsY(), _chargeMis->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
    ChargeMisWeight1 = _chargeMis->GetBinContent(xAxisBin1,yAxisBin1);
    ChargeMisUnc1 = _chargeMis->GetBinError(xAxisBin1,yAxisBin1);
  }
  if(fabs(lep2.pdgId())==11){
    int xAxisBin2  = std::max(1, std::min(_chargeMis->GetNbinsX(), _chargeMis->GetXaxis()->FindBin(lep2.conept())));
    int yAxisBin2  = std::max(1, std::min(_chargeMis->GetNbinsY(), _chargeMis->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
    ChargeMisWeight2 = _chargeMis->GetBinContent(xAxisBin2,yAxisBin2);
    ChargeMisUnc2 = _chargeMis->GetBinError(xAxisBin2,yAxisBin2);
  }
  ChargeMisWeight = ChargeMisWeight1 + ChargeMisWeight2;
  ChargeMisWeightUp = ChargeMisWeight1 + ChargeMisUnc1 + ChargeMisWeight2 + ChargeMisUnc2;
  ChargeMisWeightDown = ChargeMisWeight1 - ChargeMisUnc1 + ChargeMisWeight2 - ChargeMisUnc2;
  //std::cout << EventContainerObj->eventNumber <<" "<< lep1.conept()<< " " << lep1.Eta()<< " " << lep1.pdgId() << " "<< ChargeMisWeight1<<" "<< lep2.conept()<< " " << lep2.Eta()<< " " << lep2.pdgId() <<" " << ChargeMisWeight2 <<ChargeMisWeight <<"  " << ChargeMisWeightUp << "  " <<ChargeMisWeightDown << std::endl;
  return std::make_tuple(ChargeMisWeight,ChargeMisWeightUp,ChargeMisWeightDown);
}

//Used to set up the efficiency histograms for the first time
/******************************************************************************
 * void EventWeight::setFakeRateHistograms()                                  *
 *                                                                            *
 * Sets up the histograms that will be used for charge mis measurement weighting         *
 *                                                                            *
 * Input:  Names of files and histograms that are relevant to the calculation *
 * Output: none                                                               *
 ******************************************************************************/
void EventWeight::setFakeRateHistograms(TString FakeRateFileName,TString FakeRateMuonHistName, TString FakeRateElectronHistName, std::string muSystName, std::string eleSystName){
  if (FakeRateFileName == "null" || FakeRateMuonHistName == "null" || FakeRateElectronHistName == "null"){
    std::cout << "You want lepton fake rate included in the weight but you haven't specified files for this! Fix your config!" << std::endl;
  }
  TFile* FakeRateFile = TFile::Open(FakeRateFileName,"READ");
  if (!FakeRateFile) std::cout << "FakeRate file not found!" << std::endl;
  if(muSystName=="central"){
      _MuonFakeRate[muSystName] = (TH2F*)FakeRateFile->Get(FakeRateMuonHistName)->Clone();
  }else if(muSystName=="QCD"){
      // histograms QCD and TT are used for fake rate closure systematics, I'm not going to put it in config files, because it's ttH exclusive file and I may need to change all(dozens of) config files if I do put it in config files
      _MuonFakeRate[muSystName] = (TH2F*)FakeRateFile->Get("FR_mva090_mu_QCD")->Clone();

  }else if(muSystName=="TT"){
      _MuonFakeRate[muSystName] = (TH2F*)FakeRateFile->Get("FR_mva090_mu_TT")->Clone();
  }else{
      _MuonFakeRate[muSystName] = (TH2F*)FakeRateFile->Get(FakeRateMuonHistName+"_"+muSystName)->Clone();
  }
  _MuonFakeRate[muSystName]->SetDirectory(0);
  if(eleSystName=="central"){
    _ElectronFakeRate[eleSystName] = (TH2F*)FakeRateFile->Get(FakeRateElectronHistName)->Clone();
  }else if(eleSystName=="QCD"){
    _ElectronFakeRate[eleSystName] = (TH2F*)FakeRateFile->Get("FR_mva090_el_QCD_NC")->Clone();
  }else if(eleSystName=="TT"){
    _ElectronFakeRate[eleSystName] = (TH2F*)FakeRateFile->Get("FR_mva090_el_TT")->Clone();
  }else{
     _ElectronFakeRate[eleSystName] = (TH2F*)FakeRateFile->Get(FakeRateElectronHistName+"_"+eleSystName)->Clone();
  }
   _ElectronFakeRate[eleSystName]->SetDirectory(0);
  FakeRateFile->Close();
  delete FakeRateFile;
}

/******************************************************************************
 * Bool_t EventWeight::getFakeRateWeight()                                      *
 *                                                                            *
 * Get the relevant pt and eta dependent FakeRate for the leptons in the event     *
 * and put them into one weight that is returned                              *
 *                                                                            *
 * Input:  None                                                               *
 * Output: Double_t weight to be applied to the event weight                  *
 ******************************************************************************/
Double_t EventWeight::getFakeRateWeight(EventContainer* EventContainerObj, std::string muSystName, std::string eleSystName){

  Double_t FakeRateWeight = 1.0;
  if(_whichTrigger <=5 && _whichTrigger >=2 ){//if it is ttH 2l category
      if(EventContainerObj->fakeleptonsVetoPtr->size()<2) return FakeRateWeight;
      Lepton lep1 =  EventContainerObj->fakeleptonsVetoPtr->at(0);
      Lepton lep2 =  EventContainerObj->fakeleptonsVetoPtr->at(1);
      if(lep1.isMVASel()==1 && lep2.isMVASel()==1) return FakeRateWeight;
      int xAxisBin1 = 0, yAxisBin1 = 0, xAxisBin2 = 0, yAxisBin2 = 0;
      Double_t FakeRateWeight1 = 0., FakeRateWeight2 = 0.;
      //Get the bin and fake rate for each lepton
      if(lep1.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight1 = 0.5;
      }else if(fabs(lep1.pdgId())==13){
        xAxisBin1  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep1.conept())));
        yAxisBin1  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
        FakeRateWeight1 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin1,yAxisBin1);
      }else{
        xAxisBin1  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep1.conept())));
        yAxisBin1  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
        FakeRateWeight1 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin1,yAxisBin1);
      }
      if(lep2.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight2 = 0.5;
      }else if(fabs(lep2.pdgId())==13){
        xAxisBin2  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep2.conept())));
        yAxisBin2  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
        FakeRateWeight2 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin2,yAxisBin2);
      }else{
        xAxisBin2  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep2.conept())));
        yAxisBin2  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
        FakeRateWeight2 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin2,yAxisBin2);
      }
      //And now get the Event Weights/uncs
      FakeRateWeight = (FakeRateWeight1/(1-FakeRateWeight1))*(FakeRateWeight2/(1-FakeRateWeight2));
      if(lep1.isMVASel()==0 && lep2.isMVASel()==0){
          FakeRateWeight *= -1;
      }
      //std::cout << EventContainerObj->eventNumber <<" "<< lep1.conept()<< " " << lep1.Eta()<< " " << lep1.pdgId() << " "<< FakeRateWeight1<<" "<< lep2.conept()<< " " << lep2.Eta()<< " " << lep2.pdgId() <<" " << FakeRateWeight2 <<FakeRateWeight <<"  " << FakeRateWeightUp << "  " <<FakeRateWeightDown << std::endl;
      return FakeRateWeight;
  }
  else if(_whichTrigger ==6 ){//if it is ttH 3l category
      if(EventContainerObj->fakeleptonsVetoPtr->size()<3) return FakeRateWeight;
      Lepton lep1 =  EventContainerObj->fakeleptonsVetoPtr->at(0);
      Lepton lep2 =  EventContainerObj->fakeleptonsVetoPtr->at(1);
      Lepton lep3 =  EventContainerObj->fakeleptonsVetoPtr->at(2);
      if(lep1.isMVASel()==1 && lep2.isMVASel()==1 && lep3.isMVASel()==1) return FakeRateWeight;
      int xAxisBin1 = 0, yAxisBin1 = 0, xAxisBin2 = 0, yAxisBin2 = 0, xAxisBin3 = 0, yAxisBin3 = 0;
      Double_t FakeRateWeight1 = 0., FakeRateWeight2 = 0.,  FakeRateWeight3 = 0.;
      //Get the bin and fake rate for each lepton
      if(lep1.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight1 = 0.5;
      }else if(fabs(lep1.pdgId())==13){
        xAxisBin1  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep1.conept())));
        yAxisBin1  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
        FakeRateWeight1 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin1,yAxisBin1);
      }else{
        xAxisBin1  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep1.conept())));
        yAxisBin1  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
        FakeRateWeight1 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin1,yAxisBin1);
      }
      if(lep2.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight2 = 0.5;
      }else if(fabs(lep2.pdgId())==13){
        xAxisBin2  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep2.conept())));
        yAxisBin2  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
        FakeRateWeight2 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin2,yAxisBin2);
      }else{
        xAxisBin2  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep2.conept())));
        yAxisBin2  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
        FakeRateWeight2 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin2,yAxisBin2);
      }
      if(lep3.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight3 = 0.5;
      }else if(fabs(lep3.pdgId())==13){
        xAxisBin3  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep3.conept())));
        yAxisBin3  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep3.Eta()))));
        FakeRateWeight3 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin3,yAxisBin3);
      }else{
        xAxisBin3  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep3.conept())));
        yAxisBin3  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep3.Eta()))));
        FakeRateWeight3 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin3,yAxisBin3);
      }
      //And now get the Event Weights/uncs
      //And now get the Event Weights/uncs
      FakeRateWeight = (FakeRateWeight1/(1-FakeRateWeight1))*(FakeRateWeight2/(1-FakeRateWeight2))*(FakeRateWeight3/(1-FakeRateWeight3));
      if((lep1.isMVASel()==0 + lep2.isMVASel()==0 + lep3.isMVASel()==0) == 2){
          FakeRateWeight *= -1;
      }
      //std::cout << EventContainerObj->eventNumber <<" "<< lep1.conept()<< " " << lep1.Eta()<< " " << lep1.pdgId() << " "<< FakeRateWeight1<<" "<< lep2.conept()<< " " << lep2.Eta()<< " " << lep2.pdgId() <<" " << FakeRateWeight2 <<FakeRateWeight <<"  " << FakeRateWeightUp << "  " <<FakeRateWeightDown << std::endl;
      return FakeRateWeight;
  }
  else if(_whichTrigger ==7 ){//if it is ttH 4l category
      if(EventContainerObj->fakeleptonsVetoPtr->size()<4) return FakeRateWeight;
      Lepton lep1 =  EventContainerObj->fakeleptonsVetoPtr->at(0);
      Lepton lep2 =  EventContainerObj->fakeleptonsVetoPtr->at(1);
      Lepton lep3 =  EventContainerObj->fakeleptonsVetoPtr->at(2);
      Lepton lep4 =  EventContainerObj->fakeleptonsVetoPtr->at(3);
      if(lep1.isMVASel()==1 && lep2.isMVASel()==1 && lep3.isMVASel()==1 && lep4.isMVASel()==1) return FakeRateWeight;
      int xAxisBin1 = 0, yAxisBin1 = 0, xAxisBin2 = 0, yAxisBin2 = 0, xAxisBin3 = 0, yAxisBin3 = 0, xAxisBin4 = 0, yAxisBin4 = 0;
      Double_t FakeRateWeight1 = 0., FakeRateWeight2 = 0.,  FakeRateWeight3 = 0., FakeRateWeight4 =0.;
      //Get the bin and fake rate for each lepton
      if(lep1.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight1 = 0.5;
      }else if(fabs(lep1.pdgId())==13){
        xAxisBin1  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep1.conept())));
        yAxisBin1  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
        FakeRateWeight1 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin1,yAxisBin1);
      }else{
        xAxisBin1  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep1.conept())));
        yAxisBin1  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
        FakeRateWeight1 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin1,yAxisBin1);
      }
      if(lep2.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight2 = 0.5;
      }else if(fabs(lep2.pdgId())==13){
        xAxisBin2  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep2.conept())));
        yAxisBin2  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
        FakeRateWeight2 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin2,yAxisBin2);
      }else{
        xAxisBin2  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep2.conept())));
        yAxisBin2  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
        FakeRateWeight2 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin2,yAxisBin2);
      }
      if(lep3.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight3 = 0.5;
      }else if(fabs(lep3.pdgId())==13){
        xAxisBin3  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep3.conept())));
        yAxisBin3  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep3.Eta()))));
        FakeRateWeight3 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin3,yAxisBin3);
      }else{
        xAxisBin3  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep3.conept())));
        yAxisBin3  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep3.Eta()))));
        FakeRateWeight3 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin3,yAxisBin3);
      }
      if(lep4.isMVASel()==1){
        // choose fr so that fr/(1-fr)==1
        FakeRateWeight4 = 0.5;
      }else if(fabs(lep4.pdgId())==13){
        xAxisBin4  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsX(), _MuonFakeRate[muSystName]->GetXaxis()->FindBin(lep4.conept())));
        yAxisBin4  = std::max(1, std::min(_MuonFakeRate[muSystName]->GetNbinsY(), _MuonFakeRate[muSystName]->GetYaxis()->FindBin(std::fabs(lep4.Eta()))));
        FakeRateWeight4 = _MuonFakeRate[muSystName]->GetBinContent(xAxisBin4,yAxisBin4);
      }else{
        xAxisBin4  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsX(), _ElectronFakeRate[eleSystName]->GetXaxis()->FindBin(lep4.conept())));
        yAxisBin4  = std::max(1, std::min(_ElectronFakeRate[eleSystName]->GetNbinsY(), _ElectronFakeRate[eleSystName]->GetYaxis()->FindBin(std::fabs(lep4.Eta()))));
        FakeRateWeight4 = _ElectronFakeRate[eleSystName]->GetBinContent(xAxisBin4,yAxisBin4);
      }
      //And now get the Event Weights/uncs
      //And now get the Event Weights/uncs
      FakeRateWeight = (FakeRateWeight1/(1-FakeRateWeight1))*(FakeRateWeight2/(1-FakeRateWeight2))*(FakeRateWeight3/(1-FakeRateWeight3))*(FakeRateWeight4/(1-FakeRateWeight4));
      if(((lep1.isMVASel()==0 + lep2.isMVASel()==0 + lep3.isMVASel()==0 + lep4.isMVASel())%2) == 0){
          FakeRateWeight *= -1;
      }
      //std::cout << EventContainerObj->eventNumber <<" "<< lep1.conept()<< " " << lep1.Eta()<< " " << lep1.pdgId() << " "<< FakeRateWeight1<<" "<< lep2.conept()<< " " << lep2.Eta()<< " " << lep2.pdgId() <<" " << FakeRateWeight2 <<FakeRateWeight <<"  " << FakeRateWeightUp << "  " <<FakeRateWeightDown << std::endl;
      return FakeRateWeight;
  }
  else return FakeRateWeight;
}

/******************************************************************************
 * Bool_t EventWeight::getTriggerWeight()                                      *
 *                                                                            *
 * Get the relevant pt and eta dependent Trigger for the leptons in the event     *
 * and put them into one weight that is returned                              *
 *                                                                            *
 * Input:  None                                                               *
 * Output: Double_t weight to be applied to the event weight                  *
 ******************************************************************************/
std::tuple<Double_t,Double_t,Double_t> EventWeight::getTriggerWeight(EventContainer * EventContainerObj){
  Double_t TriggerWeight = 1.0, TriggerWeightUp = 1.0, TriggerWeightDown = 1.0;
  Int_t category = 0;
  if((fabs(EventContainerObj->fakeLeptons.at(0).pdgId())+fabs(EventContainerObj->fakeLeptons.at(1).pdgId()))==22)category =1;
  else if((fabs(EventContainerObj->fakeLeptons.at(0).pdgId())+fabs(EventContainerObj->fakeLeptons.at(1).pdgId()))==24)category =2;
  else if((fabs(EventContainerObj->fakeLeptons.at(0).pdgId())+fabs(EventContainerObj->fakeLeptons.at(1).pdgId()))==26)category =3;
  Double_t lep1_conept = EventContainerObj->fakeLeptons.at(0).conept();
  if(_whichTrigger>=2 && _whichTrigger <=5){
    // updated trigger SF for 2017 , see link :
    // https://gitlab.cern.ch/ttH_leptons/doc/blob/master/2017/appendix_1.md#for-lepton-id-scale-factors
    if(category ==3){//mm
        if(lep1_conept <35){
            TriggerWeight = 0.972;
            TriggerWeightUp = 0.972 + 0.006;
            TriggerWeightDown = 0.972 - 0.006;
        }else{
            TriggerWeight = 0.994;
            TriggerWeightUp = 0.994 + 0.001;
            TriggerWeightDown = 0.994 - 0.001;
        }
    }else if(category==1){//ee
        if(lep1_conept < 30){
            TriggerWeight = 0.937;
            TriggerWeightUp = 0.937 + 0.027;
            TriggerWeightDown = 0.937 - 0.027;
        }else{
            TriggerWeight = 0.991;
            TriggerWeightUp = 0.991 + 0.002;
            TriggerWeightDown = 0.991 - 0.002;
        }
    }else if(category==2){//em
        if(lep1_conept < 35){
            TriggerWeight = 0.952;
            TriggerWeightUp = 0.952 + 0.008;
            TriggerWeightDown = 0.952 - 0.008;
        }else if(lep1_conept <50){
            TriggerWeight = 0.983;
            TriggerWeightUp = 0.983 + 0.003;
            TriggerWeightDown = 0.983 - 0.003;
        }else{
            TriggerWeight = 1.0;
            TriggerWeightUp = 1.0 + 0.001;
            TriggerWeightDown = 1.0 - 0.001;
        }
    }
  }else if(_whichTrigger==6 || _whichTrigger==7){//4l
      TriggerWeight = 1.00;
      TriggerWeightUp = 1.05;
      TriggerWeightDown = 0.95;
  }else{
      TriggerWeight = 1.00;
      TriggerWeightUp = 1.03;
      TriggerWeightDown = 0.97;
  }
  return std::make_tuple(TriggerWeight,TriggerWeightUp,TriggerWeightDown);
}
/******************************************************************************
******************************************************************************
 * Double_t EventWeight::getBTagReshape()                                     *
 *                                                                            *
 * Get the reshaped CSV discriminant from the reshaping class                 *
 *                                                                            *
 * Input:  EventContainer of the event                                        *
 * Output: Double_t weight to be applied to the event weight                  *
 ******************************************************************************/
Double_t EventWeight::getBTagReshape(EventContainer * EventContainerObj, std::string syst){

  Double_t bTagWeight = 1.0;
  for (auto const & jet : EventContainerObj->jets){
    if (jet.GethadronFlavour() == 5){
        float jetSF = _bTagCalibReader.eval_auto_bounds(syst, BTagEntry::FLAV_B, fabs(jet.Eta()), jet.Pt(), jet.bDiscriminator());
        //std::cout<<"jet pt: "<<jet.Pt()<<", Flavour is "<< jet.GethadronFlavour() << ", read Systematic "<<syst<<", returned value <bTagWeight, jetSF>: <"<<bTagWeight <<", "<<jetSF<<">";
        if (jetSF == 0) jetSF = _bTagCalibReader.eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(jet.Eta()), jet.Pt(), jet.bDiscriminator());
        bTagWeight *= jetSF;
        //std::cout<< ", <bTagWeight, jetSF> after jetSF==0 check : <"<<bTagWeight <<", "<<jetSF<<">"<<std::endl;
    }else if(jet.GethadronFlavour() == 4){
        float jetSF = _bTagCalibReader.eval_auto_bounds(syst, BTagEntry::FLAV_C, fabs(jet.Eta()), jet.Pt(), jet.bDiscriminator());
        //std::cout<<"jet pt: "<<jet.Pt()<<", Flavour is "<< jet.GethadronFlavour() << ", read Systematic "<<syst<<", returned value <bTagWeight, jetSF>: <"<<bTagWeight <<", "<<jetSF<<">";
        if (jetSF == 0) jetSF = _bTagCalibReader.eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(jet.Eta()), jet.Pt(), jet.bDiscriminator());
        bTagWeight *= jetSF;
        //std::cout<< ", <bTagWeight, jetSF> after jetSF==0 check : <"<<bTagWeight <<", "<<jetSF<<">"<<std::endl;
    }else{
        float jetSF = _bTagCalibReader.eval_auto_bounds(syst, BTagEntry::FLAV_UDSG, fabs(jet.Eta()), jet.Pt(), jet.bDiscriminator());
        //std::cout<<"jet pt: "<<jet.Pt()<<", Flavour is "<< jet.GethadronFlavour() << ", read Systematic "<<syst<<", returned value <bTagWeight, jetSF>: <"<<bTagWeight <<", "<<jetSF<<">";
        if (jetSF == 0) jetSF = _bTagCalibReader.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(jet.Eta()), jet.Pt(), jet.bDiscriminator());
        bTagWeight *= jetSF;
        //std::cout<< ", <bTagWeight, jetSF> after jetSF==0 check : <"<<bTagWeight <<", "<<jetSF<<">"<<std::endl;
    }
  }
  return bTagWeight;
}


Double_t EventWeight::PileupAdjust(int eventNumber, int runnumber)
{
  float frac = 1.0;

if (runnumber == 105200)  frac = 1.02596;
else if (runnumber == 105204)  frac = 1.0053;
else if (runnumber == 105205)  frac = 1.00194;
else if (runnumber == 105500)  frac = 1.00716;
else if (runnumber == 105860)  frac = 1.00061;
else if (runnumber == 105861)  frac = 1.00109;
else if (runnumber == 105985)  frac = 1.00013;
else if (runnumber == 105986)  frac = 1.00167;
else if (runnumber == 105987)  frac = 1.00041;

else if (runnumber == 107650)  frac = 1.00056;
else if (runnumber == 107651)  frac = 0.999814;
else if (runnumber == 107652)  frac = 0.999761;
else if (runnumber == 107653)  frac = 1;
else if (runnumber == 107654)  frac = 1.00621;
else if (runnumber == 107655)  frac = 1.0055;

else if (runnumber == 107661)  frac = 1.00339;
else if (runnumber == 107662)  frac = 1.00444;
else if (runnumber == 107663)  frac = 1.00222;
else if (runnumber == 107664)  frac = 1.00731;
else if (runnumber == 107665)  frac = 1.00674;
else if (runnumber == 107670)  frac = 0.998971;
else if (runnumber == 107671)  frac = 0.998627;
else if (runnumber == 107672)  frac = 0.99429;
else if (runnumber == 107673)  frac = 0.993913;
else if (runnumber == 107674)  frac = 0.990936;
else if (runnumber == 107675)  frac = 1.02436;

else if (runnumber == 107681)  frac = 0.995526;
else if (runnumber == 107682)  frac = 0.997984;
else if (runnumber == 107683)  frac = 0.994221;
else if (runnumber == 107684)  frac = 0.994099;
else if (runnumber == 107685)  frac = 1.00607;

else if (runnumber == 107691)  frac = 1.00435;
else if (runnumber == 107692)  frac = 1.00421;
else if (runnumber == 107693)  frac = 1.00402;
else if (runnumber == 107694)  frac = 1.00054;
else if (runnumber == 107695)  frac = 1.00184;
else if (runnumber == 107700)  frac = 1.00221;
else if (runnumber == 107701)  frac = 0.99912;
else if (runnumber == 107702)  frac = 1.00062;

else if (runnumber == 107704)  frac = 0.990074;
else if (runnumber == 107705)  frac = 0.994124;
else if (runnumber == 108340)  frac = 0.995628;
else if (runnumber == 108341)  frac = 1.00081;
else if (runnumber == 108342)  frac = 1.00517;
else if (runnumber == 108343)  frac = 0.996556;
else if (runnumber == 108344)  frac = 1.00456;
else if (runnumber == 108345)  frac = 1.0076;
else if (runnumber == 108346)  frac = 1.00447;
else if (runnumber == 117255)  frac = 0.999862;
else if (runnumber == 117256)  frac = 1.00185;
else if (runnumber == 117257)  frac = 1.00131;
else if (runnumber == 117258)  frac = 1.00001;
else if (runnumber == 117259)  frac = 1.00036;
else if (runnumber == 117260)  frac = 1.00263;
else if (runnumber == 117284)  frac = 0.998673;
else if (runnumber == 117285)  frac = 1.00038;
else if (runnumber == 117286)  frac = 0.998383;
else if (runnumber == 117287)  frac = 0.997502;

else if (runnumber == 117320)  frac = 1.00079;
else if (runnumber == 117321)  frac = 1.00362;
else if (runnumber == 117322)  frac = 1.00177;

else if (runnumber == 117324)  frac = 1.0027;
else if (runnumber == 117325)  frac = 0.996011;
else if (runnumber == 117326)  frac = 1.002;
else if (runnumber == 117330)  frac = 0.996473;
else if (runnumber == 117331)  frac = 1.00042;
else if (runnumber == 117332)  frac = 1.00385;
else if (runnumber == 117333)  frac = 0.995029;

else if (runnumber == 117335)  frac = 0.987182;
else if (runnumber == 117336)  frac = 1.0021;
else if (runnumber == 117340)  frac = 0.994011;
else if (runnumber == 117341)  frac = 1.00372;
else if (runnumber == 117342)  frac = 0.998009;
else if (runnumber == 117343)  frac = 0.995256;
else if (runnumber == 117344)  frac = 1.00386;
else if (runnumber == 117345)  frac = 0.990821;
else if (runnumber == 117346)  frac = 0.997322;
else if (runnumber == 117350)  frac = 0.995102;
else if (runnumber == 117351)  frac = 1.00322;
else if (runnumber == 117352)  frac = 1.00255;

else if (runnumber == 117356)  frac = 0.998025;
else if (runnumber == 117360)  frac = 0.994038;
else if (runnumber == 117361)  frac = 1.00316;
else if (runnumber == 117362)  frac = 0.994114;
else if (runnumber == 117363)  frac = 0.997215;
else if (runnumber == 117364)  frac = 1.00182;
else if (runnumber == 117365)  frac = 0.999941;
else if (runnumber == 117370)  frac = 0.996266;

else if (runnumber == 117372)  frac = 1.003;
else if (runnumber == 117373)  frac = 0.996895;
else if (runnumber == 117374)  frac = 1.00244;
else if (runnumber == 117375)  frac = 1.00104;
else if (runnumber == 117376)  frac = 0.995137;
else if (runnumber == 117380)  frac = 0.994951;
else if (runnumber == 117381)  frac = 1.00204;
else if (runnumber == 117382)  frac = 1.00991;
else if (runnumber == 117383)  frac = 1.00025;
else if (runnumber == 117384)  frac = 1.00303;
else if (runnumber == 117385)  frac = 1.001;
else if (runnumber == 117386)  frac = 1.00197;

else if (runnumber == 117391)  frac = 1.00353;
else if (runnumber == 117392)  frac = 1.00345;
else if (runnumber == 117393)  frac = 0.993738;
else if (runnumber == 117394)  frac = 1.00359;
else if (runnumber == 117395)  frac = 1.01838;
else if (runnumber == 117396)  frac = 1.00084;

else if (runnumber == 107280)  frac = 0.994461;
else if (runnumber == 107281)  frac = 0.993678;
else if (runnumber == 107282)  frac = 0.998292;
else if (runnumber == 107283)  frac = 1.00964;
else if (runnumber == 107660)  frac = 1.00989;
else if (runnumber == 107680)  frac = 0.993555;
else if (runnumber == 107690)  frac = 1.00323;
else if (runnumber == 107703)  frac = 0.999144;
else if (runnumber == 117293)  frac = 0.998648;
else if (runnumber == 117294)  frac = 0.998781;
else if (runnumber == 117295)  frac = 0.998505;
else if (runnumber == 117296)  frac = 1.00431;
else if (runnumber == 117297)  frac = 0.99105;
else if (runnumber == 117323)  frac = 0.999915;
else if (runnumber == 117334)  frac = 1.00099;
else if (runnumber == 117353)  frac = 1.00225;
else if (runnumber == 117354)  frac = 1.00332;
else if (runnumber == 117355)  frac = 1.00345;
else if (runnumber == 117371)  frac = 1.00331;
else if (runnumber == 117390)  frac = 0.996491;

    // else cout<<"EventWeight: Pileup correction run number not listed!! fraction is 1"<<endl;

    return frac;
}
