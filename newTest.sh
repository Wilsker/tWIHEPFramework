#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/SingleTop.Wt.LP.mm1+j.muonMSSmeardown.config -inlist config/files/ttH_test/ttH.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.rootskimBkgd.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger TTHLep_2L -lepSFs -bTagReshape -PileUpWgt -chargeMis 1>synch.txt 2>errorLog

