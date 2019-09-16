#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/ttV-modelling/ttH.Multilepton.2lss_1bgeq4j.gencuts.config -inlist config/files/ttH_test/ttH_2016.list -hfile hists/2LSS/1bgeq4j/ttV-modelling-TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root -skimfile skims/2LSS/1bgeq4j/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_2016.root -mc -BkgdTreeName DiElectronPreTagTree -DEBUG -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog
