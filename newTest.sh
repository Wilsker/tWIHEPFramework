#!/bin/bash

bin/ttH/ttH_generic.x -config config/overall/ttHRunII/2016/ttH.MultiLeptons.DiLepton.All.config -inlist config/files/ttH_test/ttH_2016.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHDiLep_2016.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -Prefire -FakeRate -TriggerSFs -mcPromptFS -mcRightCharge 2>errorLog 

