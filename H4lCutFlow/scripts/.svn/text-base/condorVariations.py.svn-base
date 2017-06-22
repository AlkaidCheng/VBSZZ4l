#!/usr/bin/env python

import os, stat

var_path = "/disk/userdata00/atlas_data2/bijanh/HZZRun2"
rc_path = "/home/bijanh/trunk_FidCutFlow"

if not os.path.exists(var_path+"/condor_var"):
    os.makedirs(var_path+"/condor_var")
if not os.path.exists(var_path+"/condor_var/submit"):
    os.makedirs(var_path+"/condor_var/submit")
if not os.path.exists(var_path+"/condor_var/log"):
    os.makedirs(var_path+"/condor_var/log")
if not os.path.exists(var_path+"/condor_var/out"):
    os.makedirs(var_path+"/condor_var/out")

condor = open(var_path+"/condor_var/submit/condor.sh","w")
condor.write("#!/bin/bash\n\n")

condorTemplate = \
"""universe   = vanilla
Executable = %s.sh
Initialdir = %s/condor_var/submit
getenv     = True
output     = %s/condor_var/log/%s.out
error      = %s/condor_var/log/%s.err
log        = %s/condor_var/log/%s.log
arguments  = 
should_transfer_files = YES
when_to_transfer_output = ON_EXIT_OR_EVICT

queue
"""
submitTemplate = \
"""#!/bin/bash

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
cd %s
source ${ATLAS_LOCAL_RCSETUP_PATH}/rcSetup.sh

runAnalysisGrid -sampleName %s/ -sampleFile %s/%s/%s_%06d.DAOD_TRUTH0.truth.pool.root -outputBaseName %s/condor_var/out/%s%s -analType fid -truthLeptonType dressed


echo done.
"""

def WriteVariations(process,filepath,dataset,datafile,nfiles) :
        for i in nfiles :
            tag = '%s_%06d'%(process,i)
            outtag = '%s_%06d'%(process,i)
            submit_name = "%s/condor_var/submit/%s.sh" % (var_path,tag)
            with open(submit_name, "w") as sub:
                sub.write(submitTemplate % (rc_path,dataset,filepath,dataset,datafile,i,var_path,datafile,tag))
            #st = os.stat(submit_name).st_mode
            #os.chmod(submit_name, st | stat.S_IEXEC)
            #doEmail = '-N -u \"person@domain.edu\"' if (i == nfiles) else ''
            #all.write("bsub -q 8nh -J %s -o condor_var/log/%s %s < %s\n" % (tag,tag,doEmail,submit_name))

            condor_name = "%s/condor_var/submit/%s.job" % (var_path,tag)
            with open(condor_name, "w") as sub:
                sub.write(condorTemplate % (tag,var_path,var_path,tag,var_path,tag,var_path,tag))
            st = os.stat(condor_name).st_mode
            os.chmod(condor_name, st | stat.S_IEXEC)
            condor.write("condor_submit %s.job\n" % (tag))

## ggF125
h_process = 'ggF125'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal2016/truth'
h_dataset = 'mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau.evgen.EVNT.e3951_prod09_EXT0'
h_datafile = 'user.gabarone.8350657.EXT0.'
h_nfiles = range(11,31)
h_nfiles.extend([36,37,38,39,40])
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

## VBF125
h_process = 'VBFH125'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal2016/truth'
h_dataset = 'mc15_13TeV.341518.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_ZZ4lep_noTau.evgen.EVNT.e3951_prod09_EXT0'
h_datafile = 'user.gabarone.8350671.EXT0.'
h_nfiles = range(1,17)
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

## ZH125
h_process = 'ZH125'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal2016/truth'
h_dataset = 'mc15_13TeV.341947.Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZ4l.evgen.EVNT.e4161_prod09_EXT0'
h_datafile = 'user.gabarone.8350781.EXT0.'
h_nfiles = range(1,12)
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

# WH125
h_process = 'WH125'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal2016/truth'
h_dataset = 'mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l.evgen.EVNT.e4161_prod09_EXT0'
h_datafile = 'user.gabarone.8350793.EXT0.'
h_nfiles = range(1,10)
h_nfiles.extend([12,13])
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

# ttH125
h_process = 'ttH125'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal2016/truth'
h_dataset = 'mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l.evgen.EVNT.e4540_prod09_EXT0'
h_datafile = 'user.gabarone.8350806.EXT0.'
h_nfiles = range(1,12)
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

## ggF126
'''
h_process = 'ggF126'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal'
h_dataset = 'mc15_13TeV.341506.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH126_ZZ4lep_noTau.merge.DAOD_HIGG2D1.e3951_s2608_s2183_r6869_r6282_p2425'
h_datafile = 'DAOD_HIGG2D1.06607087.'
h_nfiles = [1,2,3,4,5,6,7,8,9,10,11]
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

## VBF126
h_process = 'VBFH126'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal'
h_dataset = 'mc15_13TeV.341519.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH126_ZZ4lep_noTau.merge.DAOD_HIGG2D1.e3951_s2608_s2183_r6869_r6282_p2425'
h_datafile = 'DAOD_HIGG2D1.06606939.'
h_nfiles = [1,2,3,4,5,6,7,8,9]
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

## ZH126
h_process = 'ZH126'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal'
h_dataset = 'mc15_13TeV.341948.Pythia8EvtGen_A14NNPDF23LO_ZH126_ZZ4l.merge.DAOD_HIGG2D1.e4161_s2608_s2183_r6869_r6282_p2425'
h_datafile = 'DAOD_HIGG2D1.06607724.'
h_nfiles = [1,2,3]
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

# WH126
h_process = 'WH126'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal'
h_dataset = 'mc15_13TeV.341965.Pythia8EvtGen_A14NNPDF23LO_WH126_ZZ4l.merge.DAOD_HIGG2D1.e4161_s2608_s2183_r6869_r6282_p2425'
h_datafile = 'DAOD_HIGG2D1.06607308.'
h_nfiles = [1,2,3]
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

# ttH126
h_process = 'ttH126'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal'
h_dataset = 'mc15_13TeV.342566.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH126_4l.merge.DAOD_HIGG2D1.e4540_s2726_r6869_r6282_p2425'
h_datafile = 'DAOD_HIGG2D1.06826999.'
h_nfiles = [1]
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)

# WH125

h_process = 'WH125_AOD'
h_filepath = '/disk/userdata00/atlas_data2/bijanh/HZZRun2/signal'
h_dataset = 'mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l.merge.AOD.e4161_s2608_s2183_r6869_r6282_tid06247577_00'
h_datafile = 'AOD.06247577.'
h_nfiles = range(1,31)
WriteVariations(h_process,h_filepath,h_dataset,h_datafile,h_nfiles)
'''

condor.close()
st = os.stat(var_path+'/condor_var/submit/condor.sh').st_mode
os.chmod(var_path+'/condor_var/submit/condor.sh',st | stat.S_IEXEC)
