#!/bin/bash
bin/ttH/ttH_generic.x -config config/overall/SingleTop.Wt.LP.mm1+j.muonMSSmeardown.config -inlist config/files/fullSmallerJobs/tW_top0.list -hfile hists/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.root -skimfile skims/SingleTop.105200_1.t.LP2fb_v5.MC.mm1+j.muonMSSmeardown.WtDilepton.rootskimBkgd.root -mc -BkgdTreeName DiElectronPreTagTree  -UseTotalEvtFromFile -MCatNLO -mc -SelectTrigger Muon -lepSFs -bTagReshape -PileUpWgt 2>errorLog

