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
EventWeight::EventWeight(EventContainer *EventContainerObj,Double_t TotalMCatNLOEvents,const std::string& MCtype, Bool_t pileup, Bool_t reCalPU, Bool_t bWeight, Bool_t useLeptonSFs, Bool_t usebTagReshape, Bool_t useChargeMis, Bool_t useFakeRate, Bool_t useTriggerSFs, Int_t whichTrig, Bool_t verbose):
  _reCalPU(reCalPU),
  _useLeptonSFs(useLeptonSFs),
  _useChargeMis(useChargeMis),
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
  SetEventContainer(EventContainerObj);
  if(MCtype.find("UseTotalEvtFromFile")<=MCtype.size()){
    Int_t sNumber = EventContainerObj -> GetSourceNumber();
    stringstream strNumber;
    strNumber<<"Events.Source."<<sNumber;
    Double_t totMCnloEvt = conf -> GetValue(strNumber.str().c_str(), -1.);

    SetTotalMCatNLOEvents(totMCnloEvt);
  } else {
    SetTotalMCatNLOEvents(TotalMCatNLOEvents);
  }
  setPileUpSyst(false);
  if(pileup){
    setPileUpWgt(true);
    TFile* dataPVFile = TFile::Open(conf -> GetValue("Include.dataPVFile","null"),"READ");
    _dataPV = (TH1F*)dataPVFile->Get("pileup");
    _dataPV->SetDirectory(0);
    _dataPV->Scale(1./_dataPV->Integral());
    dataPVFile->Close();
    delete dataPVFile;
    
    TFile* mcPVFile = TFile::Open(conf -> GetValue("Include.mcPVFile","null"),"READ");
    _mcPV = (TH1F*)mcPVFile->Get("pileup");
    _mcPV->SetDirectory(0);
    _mcPV->Scale(1./_mcPV->Integral());
    mcPVFile->Close();
    delete mcPVFile;

    //Load in the pileup distributions with the min bias x-section altered for systematic studies
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
  _bTagSystNames = {"central","down_jes","up_lf","down_lf","up_hfstats1","down_hfstats1","up_hfstats2","down_hfstats2","up_cferr1","down_cferr1","up_cferr2","down_cferr2","up_jes"};
  
  
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

  //Create one histogtam per b-tag systematic (and central value)
  for (auto const bTagSystName: _bTagSystNames){
    // Histogram of bTag shape weight
    _hbTagReshape[bTagSystName] =  DeclareTH1F("bTagReshape_"+bTagSystName,"bTag reshaping "+bTagSystName,100,-5.0,5.);
    _hbTagReshape[bTagSystName] -> SetXAxisTitle("bTag Reshape " + bTagSystName);
    _hbTagReshape[bTagSystName] -> SetYAxisTitle("Events");
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
  Int_t sNumber = EventContainerObj -> GetSourceNumber();
  stringstream strNumber;
  strNumber<<"Weight.Source."<<sNumber;
  //string wq = "Weight.Source."+strNumber.str();
  //wq += strNumber.str();
  //  cout << EventContainerObj->GetEventTree()->GetEntries() << endl;
  Double_t xsecstuff = conf -> GetValue(strNumber.str().c_str(), 0.0);

  //Get the lumi of the data from the config file
  Double_t lumi = conf -> GetValue("Weight.Lumi",100);
  
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
  if (_useLeptonSFs) setLeptonHistograms(conf->GetValue("Include.MuonIDSFsFile","null"),conf->GetValue("LeptonID.MuonIDSFHistName","null"),conf->GetValue("Include.MuonISOSFsFile","null"),conf->GetValue("LeptonID.MuonIsoSFHistName","null"),conf->GetValue("Include.MuonTrigSFsFile","null"),conf->GetValue("LeptonID.MuonTrigSFHistName","null"),conf->GetValue("Include.MuonTKSFsFile","null"),conf->GetValue("Include.EleRecoFileName","null"),conf->GetValue("LeptonID.EleRecoHistName","null"),conf->GetValue("Include.EleIDFileName","null"),conf->GetValue("LeptonID.EleID_1_HistName","null"),conf->GetValue("LeptonID.EleID_2_HistName","null"),conf->GetValue("LeptonID.EleID_3_HistName","null"),conf->GetValue("Include.MuonLooseToTightSFsFile","null"),conf->GetValue("LeptonID.MuonLooseToTightHistName","null"),conf->GetValue("Include.EleLooseToTightSFsFile","null"),conf->GetValue("LeptonID.EleLooseToTightHistName","null"));

  //Set up the lepton charge mismeasurement histograms
  if (_useChargeMis) setChargeMisHistograms(conf->GetValue("Include.ChargeMisFile","null"),conf->GetValue("ChargeMis.HistName","null"));
  
  //Set up the lepton fake rate histograms
  if (_useFakeRate) setFakeRateHistograms(conf->GetValue("Include.LeptonFakeRateFile","null"),conf->GetValue("FakeRate.Muon.HistName","null"),conf->GetValue("FakeRate.Electron.HistName","null"));
  
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
   if (_reCalPU && _mcPV->GetBinContent(tree->trueInteractions) > 0){
     pileupEventWeight = _dataPV->GetBinContent(tree->trueInteractions) / _mcPV->GetBinContent(tree->trueInteractions);
     if (isPileupSysts()){
       pileupMinBiasUpWeight = _minBiasUpPV->GetBinContent(tree->trueInteractions) / _mcPV->GetBinContent(tree->trueInteractions);
       pileupMinBiasDownWeight = _minBiasDownPV->GetBinContent(tree->trueInteractions) / _mcPV->GetBinContent(tree->trueInteractions);
     }
   }
   else {
     pileupEventWeight = tree->PUWeight;
     pileupMinBiasUpWeight = tree->PUWeight;
     pileupMinBiasDownWeight = tree->PUWeight;
   }
   wgt *= pileupEventWeight;
 }

 float bEventWeight(1.0);
 
 if (isbWeight()){
   bEventWeight = tree->bWeight;
   wgt *= bEventWeight;
 }
  
 
 float lepSFWeight(1.0), lepSFWeightUp(1.0), lepSFWeightDown(1.0);

 if(_useLeptonSFs){
   std::tie(lepSFWeight,lepSFWeightUp,lepSFWeightDown) = getLeptonWeight(EventContainerObj);
   wgt *= lepSFWeight;
 }
  
 float ChargeMisWeight(1.0), ChargeMisWeightUp(1.0), ChargeMisWeightDown(1.0);

 if(_useChargeMis){
   std::tie(ChargeMisWeight,ChargeMisWeightUp,ChargeMisWeightDown) = getChargeMisWeight(EventContainerObj);
   //std::cout << EventContainerObj->eventNumber <<" "<<ChargeMisWeight <<"  " << ChargeMisWeightUp << "  " <<ChargeMisWeightDown << std::endl;
   wgt *= ChargeMisWeight;
 }
  
 float FakeRateWeight(1.0), FakeRateWeightUp(1.0), FakeRateWeightDown(1.0);

 if(_useFakeRate){
   std::tie(FakeRateWeight,FakeRateWeightUp,FakeRateWeightDown) = getFakeRateWeight(EventContainerObj);
   //std::cout << EventContainerObj->eventNumber <<" " <<FakeRateWeight <<"  " << FakeRateWeightUp << "  " <<FakeRateWeightDown << std::endl;
   wgt *= FakeRateWeight;
 }
  
 float TriggerWeight(1.0), TriggerWeightUp(1.0), TriggerWeightDown(1.0);

 if(_useTriggerSFs){
   std::tie(TriggerWeight,TriggerWeightUp,TriggerWeightDown) = getTriggerWeight();
   //std::cout << EventContainerObj->eventNumber <<" " <<TriggerWeight <<"  " << TriggerWeightUp << "  " <<TriggerWeightDown << std::endl;
   wgt *= TriggerWeight;
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
  EventContainerObj -> SetGenWeight(genWeight);
  for (auto const bSystName: _bTagSystNames) EventContainerObj -> SetEventbTagReshape(bTagReshape[bSystName],bSystName);

  EventContainerObj -> SetEventLepSFWeightUp(lepSFWeightUp);
  EventContainerObj -> SetEventLepSFWeightDown(lepSFWeightDown);

  EventContainerObj -> SetEventChargeMisWeight(ChargeMisWeight);
  EventContainerObj -> SetEventChargeMisWeightUp(ChargeMisWeightUp);
  EventContainerObj -> SetEventChargeMisWeightDown(ChargeMisWeightDown);
  
  EventContainerObj -> SetEventFakeRateWeight(FakeRateWeight);
  EventContainerObj -> SetEventFakeRateWeightUp(FakeRateWeightUp);
  EventContainerObj -> SetEventFakeRateWeightDown(FakeRateWeightDown);
  
  EventContainerObj -> SetEventTriggerWeight(TriggerWeight);
  EventContainerObj -> SetEventTriggerWeightUp(TriggerWeightUp);
  EventContainerObj -> SetEventTriggerWeightDown(TriggerWeightDown);
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
  _hGenWeight	   -> FillWithoutWeight(EventContainerObj -> GetGenWeight());
  _hChargeMis -> FillWithoutWeight(EventContainerObj -> GetEventChargeMisWeight());
  _hFakeRate -> FillWithoutWeight(EventContainerObj -> GetEventFakeRateWeight());
  _hTriggerSFs -> FillWithoutWeight(EventContainerObj -> GetEventTriggerWeight());
  for (auto const bSystName: _bTagSystNames) _hbTagReshape[bSystName] -> FillWithoutWeight(EventContainerObj -> GetEventbTagReshape(bSystName));

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
  if (muonIsoFileName == "null" || muonIDFileName == "null"){
    std::cout << "You want lepton SFs included in the weight but you haven't specified files for this! Fix your config!" << std::endl;
  }

  //std::cout << " before muonID " << std::endl;  
  TFile* muonIDFile = TFile::Open(muonIDFileName,"READ");
  if (!muonIDFile) std::cout << "Muon ID file not found!" << std::endl;
  _muonIDSF = (TH2F*)muonIDFile->Get(muonIDHistName)->Clone();
  _muonIDSF->SetDirectory(0);
  muonIDFile->Close();

  //std::cout << " before muonIso " << std::endl;  
  TFile* muonIsoFile = TFile::Open(muonIsoFileName,"READ");
  if (!muonIsoFile) std::cout << "Muon iso file not found!" << std::endl;
  _muonIsoSF = (TH2F*)muonIsoFile->Get(muonIsoHistName)->Clone();
  _muonIsoSF->SetDirectory(0);
  muonIsoFile->Close();

  //std::cout << " before muonTrig " << std::endl;  
  TFile* muonTrigFile = TFile::Open(muonTrigFileName,"READ");
  if (!muonTrigFile) std::cout << "Muon trig file not found!" << std::endl;
  _muonTrigSF = (TH2F*)muonTrigFile->Get(muonTrigHistName)->Clone();
  _muonTrigSF->SetDirectory(0);
  muonTrigFile->Close();

  //std::cout << " before muonTk " << std::endl;  
  TFile* muonTkFile = TFile::Open(muonTkFileName,"READ");
  if (!muonTkFile) std::cout << "Muon tracker file not found!" << std::endl;
  _muonTkSF = (TGraphAsymmErrors*)muonTkFile->Get("ratio_eff_eta3_dr030e030_corr")->Clone();
  //  _muonTkSF->SetDirectory(0);
  muonTkFile->Close();

  //std::cout << " before eleReco " << std::endl;  
  TFile* eleRecoFile = TFile::Open(eleRecoFileName,"READ");
  if (!eleRecoFile) std::cout << "Electron reco SF file not found!" << std::endl;
  _eleRecoSF = (TH2F*)eleRecoFile->Get(eleRecoHistName)->Clone();
  _eleRecoSF->SetDirectory(0);
  eleRecoFile->Close();

  //std::cout << " before eleID " << std::endl;  
  TFile* eleIDFile = TFile::Open(eleIDFileName,"READ");
  if (!eleIDFile) std::cout << "Electron ID SF file not found!" << std::endl;
  _eleID1SF = (TH2F*)eleIDFile->Get(eleID_1_HistName)->Clone();
  _eleID1SF->SetDirectory(0);
  _eleID2SF = (TH2F*)eleIDFile->Get(eleID_2_HistName)->Clone();
  _eleID2SF->SetDirectory(0);
  _eleID3SF = (TH2F*)eleIDFile->Get(eleID_3_HistName)->Clone();
  _eleID3SF->SetDirectory(0);
  eleIDFile->Close();
  
  //std::cout << " before muonLooseToTightFile " << std::endl;  
  TFile* muonLooseToTightFile = TFile::Open(muonLooseToTightFileName,"READ");
  if (!muonLooseToTightFile) std::cout << "Muon looseToTight file not found!" << std::endl;
  //std::cout << " before muonLooseToTightHist " << std::endl;  
  _muonLooseToTightSF = (TH2F*)muonLooseToTightFile->Get(muonLooseToTightHistName)->Clone();
  //_muonLooseToTightSF = (TH2F*)muonLooseToTightFile->Get("sf")->Clone();
  //std::cout << " before muonLooseToTightDirectory " << std::endl;  
  _muonLooseToTightSF->SetDirectory(0);
  //std::cout << " before muonLooseToTightClose " << std::endl;  
  muonLooseToTightFile->Close();

  //std::cout << " before eleLooseToTight " << std::endl;  
  TFile* eleLooseToTightFile = TFile::Open(eleLooseToTightFileName,"READ");
  if (!eleLooseToTightFile) std::cout << "Ele looseToTight file not found!" << std::endl;
  //std::cout<< "ele hist name " << eleLooseToTightHistName << std::endl;
  _eleLooseToTightSF = (TH2F*)eleLooseToTightFile->Get(eleLooseToTightHistName)->Clone();
  //_eleLooseToTightSF = (TH2F*)eleLooseToTightFile->Get("sf")->Clone();
  _eleLooseToTightSF->SetDirectory(0);
  eleLooseToTightFile->Close();

  delete muonIsoFile,muonIDFile,muonTrigFile,muonTkFile,eleRecoFile,eleIDFile, muonLooseToTightFile, eleLooseToTightFile;

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
std::tuple<Double_t,Double_t,Double_t> EventWeight::getLeptonWeight(EventContainer* EventContainerObj){

  Double_t leptonWeight = 1.0, leptonWeightUp = 1.0, leptonWeightDown = 1.0;
  if(_whichTrigger <=5 && _whichTrigger >=2 ){//if it is ttH 2l category
    for(auto const & lep: *EventContainerObj->leptonsToUsePtr){
        Float_t _L1_SF = 1.0, _L1_SFUnc =0.;//iso; id1
        Float_t _L2_SF = 1.0, _L2_SFUnc =0.;//id; id2
        Float_t _L3_SF = 1.0, _L3_SFUnc =0.;//trig; id3
        Float_t _L4_SF = 1.0, _L4_SFUnc =0.;//tk; gsf
        Float_t _ttH_SF = 1.0, _ttH_SFUnc =0.;
        if(fabs(lep.pdgId()==13)){
            // get iso
            int ptbin  = std::max(1, std::min(_muonIsoSF->GetNbinsX(), _muonIsoSF->GetXaxis()->FindBin(lep.Pt()))); 
            int etabin = std::max(1, std::min(_muonIsoSF->GetNbinsY(), _muonIsoSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
            _L1_SF = _muonIsoSF->GetBinContent(ptbin, etabin);
            _L1_SFUnc = _muonIsoSF->GetBinError(ptbin, etabin);
            // id
            ptbin  = std::max(1, std::min(_muonIDSF->GetNbinsX(), _muonIDSF->GetXaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_muonIDSF->GetNbinsY(), _muonIDSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
            _L2_SF = _muonIDSF->GetBinContent(ptbin, etabin);
            _L2_SFUnc = _muonIDSF->GetBinError(ptbin, etabin);
            // get trig
            ptbin  = std::max(1, std::min(_muonTrigSF->GetNbinsX(), _muonTrigSF->GetXaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_muonTrigSF->GetNbinsY(), _muonTrigSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
            _L3_SF = _muonTrigSF->GetBinContent(ptbin, etabin);
            _L3_SFUnc = _muonTrigSF->GetBinError(ptbin, etabin);
            // get Tk SF
            double eta1 = std::max(float(_muonTkSF->GetXaxis()->GetXmin()+1e-5), std::min(float(_muonTkSF->GetXaxis()->GetXmax()-1e-5), float(lep.Eta())));
            _L4_SF = _muonTkSF->Eval(eta1);
            //get ttH SF
            ptbin  = std::max(1, std::min(_muonLooseToTightSF->GetNbinsX(), _muonLooseToTightSF->GetXaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_muonLooseToTightSF->GetNbinsY(), _muonLooseToTightSF->GetYaxis()->FindBin(fabs(lep.Eta()))));
            _ttH_SF = _muonLooseToTightSF->GetBinContent(ptbin, etabin);
            _ttH_SFUnc = _muonLooseToTightSF->GetBinError(ptbin, etabin);
        }else{
            //get id1
            int ptbin  = std::max(1, std::min(_eleID1SF->GetNbinsX(), _eleID1SF->GetXaxis()->FindBin(lep.Pt()))); 
            int etabin = std::max(1, std::min(_eleID1SF->GetNbinsY(), _eleID1SF->GetYaxis()->FindBin(lep.SCeta())));
            _L1_SF = _eleID1SF->GetBinContent(ptbin, etabin);
            _L1_SFUnc = _eleID1SF->GetBinError(ptbin, etabin);
            //get id2
            ptbin  = std::max(1, std::min(_eleID2SF->GetNbinsX(), _eleID2SF->GetXaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_eleID2SF->GetNbinsY(), _eleID2SF->GetYaxis()->FindBin(lep.SCeta())));
            _L2_SF = _eleID2SF->GetBinContent(ptbin, etabin);
            _L2_SFUnc = _eleID2SF->GetBinError(ptbin, etabin);
            //get id3
            ptbin  = std::max(1, std::min(_eleID3SF->GetNbinsX(), _eleID3SF->GetXaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_eleID3SF->GetNbinsY(), _eleID3SF->GetYaxis()->FindBin(lep.SCeta())));
            _L3_SF = _eleID3SF->GetBinContent(ptbin, etabin);
            _L3_SFUnc = _eleID3SF->GetBinError(ptbin, etabin);
            //get reco be careful of swapped pt eta bin
            ptbin  = std::max(1, std::min(_eleID3SF->GetNbinsY(), _eleID3SF->GetYaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_eleID3SF->GetNbinsX(), _eleID3SF->GetXaxis()->FindBin(lep.SCeta())));
            _L4_SF = _eleID3SF->GetBinContent(etabin, ptbin);
            _L4_SFUnc = _eleID3SF->GetBinError(etabin, ptbin);
            //get ttH SF
            ptbin  = std::max(1, std::min(_eleLooseToTightSF->GetNbinsX(), _eleLooseToTightSF->GetXaxis()->FindBin(lep.Pt()))); 
            etabin = std::max(1, std::min(_eleLooseToTightSF->GetNbinsY(), _eleLooseToTightSF->GetYaxis()->FindBin(fabs(lep.SCeta()))));
            _ttH_SF = _eleLooseToTightSF->GetBinContent(ptbin, etabin);
            _ttH_SFUnc = _eleLooseToTightSF->GetBinError(ptbin, etabin);
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
      Float_t idSF = _muonIDSF->GetBinContent(xAxisBin,yAxisBin);
      Float_t idUnc = _muonIDSF->GetBinError(xAxisBin,yAxisBin);
      
      //Get the bin for trigger SF
      Int_t xAxisBinTrig = _muonTrigSF->GetXaxis()->FindBin(muon.Pt());
      if (muon.Pt() > 500.) xAxisBinTrig = _muonTrigSF->GetXaxis()->FindBin(499.);
      Int_t yAxisBinTrig = _muonTrigSF->GetYaxis()->FindBin(std::fabs(muon.Eta()));
      if (std::fabs(muon.Eta()) > 2.4) yAxisBinTrig = _muonTrigSF->GetYaxis()->FindBin(2.39);
      //Get the trigSF
      Float_t trigSF = _muonTrigSF->GetBinContent(xAxisBinTrig,yAxisBinTrig);
      Float_t trigUnc = _muonTrigSF->GetBinError(xAxisBinTrig,yAxisBinTrig);
  
      //Evaluate muon tk
      Float_t tkSF = _muonTkSF->Eval(std::fabs(muon.Eta()));
  
      leptonWeight *= isoSF * idSF * trigSF * tkSF;
      leptonWeightUp *= (isoSF + isoUnc) * (idSF + idUnc) * (trigSF + trigUnc) * tkSF;
      leptonWeightDown *= (isoSF - isoUnc) * (idSF - idUnc) * (trigSF - trigUnc) * tkSF;
    }
  
    for (auto const & ele : *EventContainerObj->electronsToUsePtr){
      //Get which bins we're in need of for the reco SF
      Int_t xAxisBin = _eleRecoSF->GetXaxis()->FindBin(ele.scEta());
      if (ele.scEta() > 2.5) xAxisBin = _eleRecoSF->GetXaxis()->FindBin(2.49);
      Int_t yAxisBin = _eleRecoSF->GetYaxis()->FindBin(ele.Pt());
      if (ele.Pt() > 500) xAxisBin = _eleRecoSF->GetYaxis()->FindBin(499.);
      //Now get the reco and id SFs
      Float_t recoSF = _eleRecoSF->GetBinContent(xAxisBin,yAxisBin);
      Float_t recoUnc = _eleRecoSF->GetBinError(xAxisBin,yAxisBin);
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

  return std::make_tuple(leptonWeight,leptonWeightUp,leptonWeightDown);
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
void EventWeight::setFakeRateHistograms(TString FakeRateFileName,TString FakeRateMuonHistName, TString FakeRateElectronHistName){
  if (FakeRateFileName == "null" || FakeRateMuonHistName == "null" || FakeRateElectronHistName == "null"){
    std::cout << "You want lepton fake rate included in the weight but you haven't specified files for this! Fix your config!" << std::endl;
  }
  TFile* FakeRateFile = TFile::Open(FakeRateFileName,"READ");
  if (!FakeRateFile) std::cout << "FakeRate file not found!" << std::endl;
  _MuonFakeRate = (TH2F*)FakeRateFile->Get(FakeRateMuonHistName)->Clone();
  _MuonFakeRate->SetDirectory(0);
  _ElectronFakeRate = (TH2F*)FakeRateFile->Get(FakeRateElectronHistName)->Clone();
  _ElectronFakeRate->SetDirectory(0);
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
std::tuple<Double_t,Double_t,Double_t> EventWeight::getFakeRateWeight(EventContainer* EventContainerObj){

  Double_t FakeRateWeight = 1.0, FakeRateWeightUp = 1.0, FakeRateWeightDown = 1.0;
  if(EventContainerObj->fakeleptonsVetoPtr->size()<2) return std::make_tuple(FakeRateWeight,FakeRateWeightUp,FakeRateWeightDown);
  Lepton lep1 =  EventContainerObj->fakeleptonsVetoPtr->at(0);
  Lepton lep2 =  EventContainerObj->fakeleptonsVetoPtr->at(1);
  if(lep1.isTight()==1 && lep2.isTight()==1) return std::make_tuple(FakeRateWeight,FakeRateWeightUp,FakeRateWeightDown);
  int xAxisBin1 = 0, yAxisBin1 = 0, xAxisBin2 = 0, yAxisBin2 = 0;
  Double_t FakeRateWeight1 = 0., FakeRateUnc1 = 0., FakeRateWeight2 = 0., FakeRateUnc2 = 0.;
  //Get the bin and fake rate for each lepton
  if(lep1.isTight()==1){
    // choose fr so that fr/(1-fr)==1
    FakeRateWeight1 = 0.5;
    FakeRateUnc1 = 0.;
  }else if(fabs(lep1.pdgId())==13){
    xAxisBin1  = std::max(1, std::min(_MuonFakeRate->GetNbinsX(), _MuonFakeRate->GetXaxis()->FindBin(lep1.conept())));
    yAxisBin1  = std::max(1, std::min(_MuonFakeRate->GetNbinsY(), _MuonFakeRate->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
    FakeRateWeight1 = _MuonFakeRate->GetBinContent(xAxisBin1,yAxisBin1);
    FakeRateUnc1 = _MuonFakeRate->GetBinError(xAxisBin1,yAxisBin1); 
  }else{
    xAxisBin1  = std::max(1, std::min(_ElectronFakeRate->GetNbinsX(), _ElectronFakeRate->GetXaxis()->FindBin(lep1.conept())));
    yAxisBin1  = std::max(1, std::min(_ElectronFakeRate->GetNbinsY(), _ElectronFakeRate->GetYaxis()->FindBin(std::fabs(lep1.Eta()))));
    FakeRateWeight1 = _ElectronFakeRate->GetBinContent(xAxisBin1,yAxisBin1);
    FakeRateUnc1 = _ElectronFakeRate->GetBinError(xAxisBin1,yAxisBin1); 
  }
  if(lep2.isTight()==1){
    // choose fr so that fr/(1-fr)==1
    FakeRateWeight2 = 0.5;
    FakeRateUnc2 = 0.;
  }else if(fabs(lep2.pdgId())==13){
    xAxisBin2  = std::max(1, std::min(_MuonFakeRate->GetNbinsX(), _MuonFakeRate->GetXaxis()->FindBin(lep2.conept())));
    yAxisBin2  = std::max(1, std::min(_MuonFakeRate->GetNbinsY(), _MuonFakeRate->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
    FakeRateWeight2 = _MuonFakeRate->GetBinContent(xAxisBin2,yAxisBin2);
    FakeRateUnc2 = _MuonFakeRate->GetBinError(xAxisBin2,yAxisBin2); 
  }else{
    xAxisBin2  = std::max(1, std::min(_ElectronFakeRate->GetNbinsX(), _ElectronFakeRate->GetXaxis()->FindBin(lep2.conept())));
    yAxisBin2  = std::max(1, std::min(_ElectronFakeRate->GetNbinsY(), _ElectronFakeRate->GetYaxis()->FindBin(std::fabs(lep2.Eta()))));
    FakeRateWeight2 = _ElectronFakeRate->GetBinContent(xAxisBin2,yAxisBin2);
    FakeRateUnc2 = _ElectronFakeRate->GetBinError(xAxisBin2,yAxisBin2); 
  }
  //And now get the Event Weights/uncs
  FakeRateWeight = (FakeRateWeight1/(1-FakeRateWeight1))*(FakeRateWeight2/(1-FakeRateWeight2));
  FakeRateWeightUp = ((FakeRateWeight1+FakeRateUnc1)/(1-(FakeRateWeight1+FakeRateUnc1)))*((FakeRateWeight2+FakeRateUnc2)/(1-(FakeRateWeight2+FakeRateUnc2)));
  FakeRateWeightDown = ((FakeRateWeight1-FakeRateUnc1)/(1-(FakeRateWeight1-FakeRateUnc1)))*((FakeRateWeight2-FakeRateUnc2)/(1-(FakeRateWeight2-FakeRateUnc2)));
  if(lep1.isTight()==0 && lep2.isTight()==0){
      FakeRateWeight *= -1;
      FakeRateWeightUp *= -1;
      FakeRateWeightDown *= -1;
  }
  //std::cout << EventContainerObj->eventNumber <<" "<< lep1.conept()<< " " << lep1.Eta()<< " " << lep1.pdgId() << " "<< FakeRateWeight1<<" "<< lep2.conept()<< " " << lep2.Eta()<< " " << lep2.pdgId() <<" " << FakeRateWeight2 <<FakeRateWeight <<"  " << FakeRateWeightUp << "  " <<FakeRateWeightDown << std::endl;
  return std::make_tuple(FakeRateWeight,FakeRateWeightUp,FakeRateWeightDown);
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
std::tuple<Double_t,Double_t,Double_t> EventWeight::getTriggerWeight(){
  Double_t TriggerWeight = 1.0, TriggerWeightUp = 1.0, TriggerWeightDown = 1.0;
  if(_whichTrigger==2){//mm
      TriggerWeight = 1.0; 
      TriggerWeightUp = 1.01;
      TriggerWeightDown = 0.99;
  }else if(_whichTrigger==3){//ee
      TriggerWeight = 1.01; 
      TriggerWeightUp = 1.03;
      TriggerWeightDown = 0.99;
  }else if(_whichTrigger==4){//em
      TriggerWeight = 1.01; 
      TriggerWeightUp = 1.02;
      TriggerWeightDown = 1.00;
  }else if(_whichTrigger==5){//2l
      TriggerWeight = 1.01; 
      TriggerWeightUp = 1.02;
      TriggerWeightDown = 1.00;
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
        float jetSF = _bTagCalibReader.eval_auto_bounds(syst, BTagEntry::FLAV_B, jet.Eta(), jet.Pt(), jet.bDiscriminator());
        if (jetSF == 0) jetSF = _bTagCalibReader.eval_auto_bounds("central", BTagEntry::FLAV_B, jet.Eta(), jet.Pt(), jet.bDiscriminator());
        bTagWeight *= jetSF;
    }else if(jet.GethadronFlavour() == 4){
        float jetSF = _bTagCalibReader.eval_auto_bounds(syst, BTagEntry::FLAV_C, jet.Eta(), jet.Pt(), jet.bDiscriminator());
        if (jetSF == 0) jetSF = _bTagCalibReader.eval_auto_bounds("central", BTagEntry::FLAV_C, jet.Eta(), jet.Pt(), jet.bDiscriminator());
        bTagWeight *= jetSF;
    }else{
        float jetSF = _bTagCalibReader.eval_auto_bounds(syst, BTagEntry::FLAV_UDSG, jet.Eta(), jet.Pt(), jet.bDiscriminator());
        if (jetSF == 0) jetSF = _bTagCalibReader.eval_auto_bounds("central", BTagEntry::FLAV_UDSG, jet.Eta(), jet.Pt(), jet.bDiscriminator());
        bTagWeight *= jetSF;
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
