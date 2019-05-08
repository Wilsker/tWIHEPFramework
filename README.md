# tWIHEPFramework
tW code based on IHEP framework

SetUp Environment:
    source /cvmfs/sft.cern.ch/lcg/views/LCG_94/x86_64-slc6-gcc7-opt/setup.sh
    export LD_LIBRARY_PATH=$ROOTSYS/lib:$LD_LIBRARY_PATH:<FullPATH>/tWIHEPFramework/lib/

Compile:
    make clean
    make ttH

It produces an excutable bin/ttH/ttH\_generic.x

An example test program can be run using 'bash newTest.sh', which calls the program bin/ttH/ttH\_generic.cpp.

The framework is very modular and you can hopefully see in the ttH\_generic.cpp where the various cuts are added - there are then also a whole bunch of configuration files in the config/ directory that you can tune for your particular object/event selections.
The newTest.sh bash script is enough to run the code on a single file of the ttH MC as it stands.

Arguments I usally use in newTest.sh are as follows:
	  -config		 - Generic configuration file containing links to object defintions, cuts and dataset weights.
	  -inlist   	 - List of files to run over. In newTest.sh this is a single ttH file (for testing purposes)
	  -skimfile 	 - The output skim file after all cuts are applied. 
	  -mc	      	 - Tells the script that it's simulation. Leave off for data.
	  -UseTotalEvtFromFile 	 - This gets the number of MC events from a file (already saved in MCDatasets.info)
	  -MCatNLO		 - Tells the code to use MCatNLO weights.
	  -PileUpWgt	 - Read the pileup weight from the event tree
      -ReCalPU       - ReCalculate the Pileup Weight
      -lepSFs        - Apply lepSFs
      -bTagReShape   - ReShape b-tagging 
      -chargeMis     - Apply Flip Rate
      -Prefire       - Apply Prefire weight
      -FakeRate      - Apply FakeRate
      -TriggerSFs    - Apply TriggerSFs


Main modules:
    src/Base/EventContainer.cpp - Contains all the event objects
    src/Particles/Recon/        - Define reco objects
    src/Cuts/                   - All the event cuts
    src/Vars/                   - Add some additional variables

 
