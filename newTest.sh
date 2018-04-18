#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/ttH.MultiLeptons.DiLep.config -inlist config/files/ttH_test/ttH.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/ttHV3.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis -FakeRate -TriggerSFs -mcPromptFS # 2>errorLog #1>muon_sync_0410.txt

