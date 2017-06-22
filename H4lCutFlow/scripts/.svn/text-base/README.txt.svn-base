This script is from Bijan Haney <bijan.haney@cern.ch>.


condorVariations.py

condorVariations.py is a script that creates job submission scripts for the condor batch system. It takes runAnalysisGrid and data files that you want to run over as input, and produces an executable .sh file for a condor .job file for each data file as output. 

running 'python condorVariations.py'

will create three directories: condor_var/submit, condor_var/log, and condor_var/out.

condor_var/submit is where the .sh and .job files for each data file are located. It also has a file called condor.sh which will submit all jobs to condor when executed.

condor_var/log is where the .out and .err files for the condor jobs are saved.

condor_var/out is where the .root output files after the jobs complete are saved.

Once all the jobs complete, in the condor_var/out directory, you can run 'hadd -f final_output.root output_*.root' to combine all the output files into one file. 