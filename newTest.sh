#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/ttH.MultiLeptons.DiLep.config -inlist config/files/condor_test/TTHnobb0.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.rootskimBkgd.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2Ele -lepSFs -bTagReshape -PileUpWgt -chargeMis -FakeRate -TriggerSFs  2>errorLog

