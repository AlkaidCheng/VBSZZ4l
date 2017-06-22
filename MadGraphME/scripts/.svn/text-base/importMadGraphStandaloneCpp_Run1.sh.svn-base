#!/bin/bash

# Author: K. Potamianos <karolos.potamianos@cern.ch>
# Date: 2013-XI-11

PROC_DIR=${1%/}

if [[ -z ${PROC_DIR} || ! -d ${PROC_DIR} ]] ; then
	echo "Usage: ${0} PROC_SA_CPP_xxx"
	echo "where PROC_SA_CPP_xxx is the output from MadGraph (output standalone_cpp PROC_SA_CPP_xxx)"
	echo "Adjust xxx by the name you want to give to your process: P0_Sigma_xxx"
	[ ! -d ${PROC_DIR} ] && ls ${PROC_DIR}
	exit
fi

# Destination directory

DEST_DIR=src/$(basename ${PROC_DIR})
# Because RootCore is crappy at finding sources, and is _very_ restrictive
DEST_DIR=src
HDRS_DIR=inc

# Process analytics

SUBPROC_HDRS=( $(find ${PROC_DIR} -name "CPPProcess.h") )
SUBPROC_SRCS=( $(find ${PROC_DIR} -name "CPPProcess.cc") )

echo Importing from ${PROC_DIR}
echo Number of subprocesses: ${#SUBPROC_HDRS[@]}
echo ${SUBPROC_HDRS[*]} | tr ' ' '\n' | sed 's@.*SubProcesses/\(.*\)/CPP.*@\t\1@g'

mkdir -p ${DEST_DIR} 

for i in ${SUBPROC_SRCS[*]} ; do
	proc_base=$( echo ${i} | sed -e "s@${PROC_DIR}.*P0_Sigma\(.*\)/CPPProcess.cc@\1@" | sed "s@^@P0_Sigma_${PROC_DIR/*PROC_SA_CPP_/}@" )
	
	cp ${i/.cc/.h} ${DEST_DIR}/$(basename ${i/.cc/_${proc_base}.h}) 
	cp ${i} ${DEST_DIR}/$(basename ${i/.cc/_${proc_base}.cxx}) 
	sed -i "/CPPProcess/s//CPPProcess_${proc_base}/g" ${DEST_DIR}/CPPProcess_*${proc_base}*.{cxx,h}
done

echo Model: $( find ${PROC_DIR} -name "Parameters_*cc" | sed 's/.*Parameters_\(.*\).cc/\1/' )


for i in Parameters HelAmps ; do
	file=$(find ${PROC_DIR} -name "${i}_*h")
	cp ${file} ${DEST_DIR}
	cp ${file/.h/.cc} ${DEST_DIR}/$(basename ${file/.h/.cxx})
done

if [ -e ${DEST_DIR}/read_slha.h ] ; then
	echo "read_slha.h already present!! Please check that's OK (by comparing the versions)"
else
	file=$(find ${PROC_DIR} -name "read_slha*h")
	cp ${file/.h/.cc} ${DEST_DIR}/$(basename ${file/.h/.cxx})
	
	echo "#ifndef __READ_SLHA_H__" > tmpFile
	echo "#define __READ_SLHA_H__" >> tmpFile
	cat ${file} >> tmpFile
	echo "#endif //__READ_SLHA_H__" >> tmpFile
	mv tmpFile ${DEST_DIR}/read_slha.h
fi

cp $( find ${PROC_DIR} -name "param_card*.dat" ) Cards/param_card_$( basename ${PROC_DIR} ).dat

mv ${DEST_DIR}/*.h ${HDRS_DIR}
