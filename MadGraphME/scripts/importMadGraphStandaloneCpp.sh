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

echo /afs/cern.ch/user/k/karolos/work/PROC_SA_CPP_sm_pp_4l/SubProcesses/P0_Sigma_sm_uux_epemepem/CPPProcess.cc

for i in ${SUBPROC_SRCS[*]} ; do
  procName=${PROC_DIR/*PROC_SA_CPP_}
  subProcName=${i/*P0_Sigma_}
  subProcName=${subProcName/\/*}
  outBaseName=P0_Sigma_${procName}/CPPProc_${subProcName}

  mkdir -p $(dirname ${HDRS_DIR}/${outBaseName})
  mkdir -p $(dirname ${DEST_DIR}/${outBaseName})

  cp ${i/.cc/.h} ${HDRS_DIR}/${outBaseName}.h
  cp ${i} ${DEST_DIR}/${outBaseName}.cxx

  # Updating the ifdef/endif statements
  sed -i "s/${subProcName}/${procName}_${subProcName}/g" ${HDRS_DIR}/${outBaseName}.h
  # Encapsulating code within namespaces
  sed -i "s/^class CPPProcess.*$/namespace ${procName} { \n  namespace ${subProcName} {\n\n&/" ${HDRS_DIR}/${outBaseName}.h
  sed -i "s@^};@&\n\n  } /* namespace ${subProcName} */ \n} /* namespace ${procName} */@" ${HDRS_DIR}/${outBaseName}.h
  # Using namespace in cxx file
  sed -i "s/^using namespace MG5.*$/&\nusing namespace ${procName}::${subProcName};/" ${DEST_DIR}/${outBaseName}.cxx

  # Performing some cleanup:
  sed -i '/printIndependent/s/pars->print/if(MG_PRINT_PARS) pars->print/' ${DEST_DIR}/${outBaseName}.cxx

  # Adding virtual destructor to header
  lineNo=$(grep -n '// Constructor' ${HDRS_DIR}/${outBaseName}.h | sed 's/:.*//')
  cat >/tmp/sed.setM4l.$$ <<EOF
    // Destructor.
    virtual ~CPPProcess() {}

EOF
  sed -i "$(( ${lineNo} + 2 ))r /tmp/sed.setM4l.$$" ${HDRS_DIR}/${outBaseName}.h

  # Adding setM4l function to header
  lineNo=$(grep -n 'virtual void sigmaKin();' ${HDRS_DIR}/${outBaseName}.h | sed 's/:.*//')
  cat >/tmp/sed.setM4l.$$ <<EOF
    // Set M4l Mass
    void setM4l(double m_m4l);

EOF
  sed -i "$(( ${lineNo} - 2 ))r /tmp/sed.setM4l.$$" ${HDRS_DIR}/${outBaseName}.h

  # Adding setM4l function to source
  lineNo=$(grep -n '::sigmaKin()' ${DEST_DIR}/${outBaseName}.cxx | sed 's/:.*//')
  cat >/tmp/sed.setM4l.$$ <<EOF
//--------------------------------------------------------------------------
// Set M4l Mass

void CPPProcess::setM4l(double m_m4l){
   //Adujst Parameters_sm to include new function if you wish to use m4l as mH, following Parameters_heft
   //pars->set4lepMass(m_m4l);
}

EOF
  sed -i "$(( ${lineNo} - 4 ))r /tmp/sed.setM4l.$$" ${DEST_DIR}/${outBaseName}.cxx

  # Adding notice for automatic modifications
  lineNo=$( grep -n '^//==========================================================================' ${DEST_DIR}/${outBaseName}.cxx | sed 's/:.*//' | head -2 | tail -1 )
  cat >/tmp/sed.setM4l.$$ <<EOF
// This code is adjusted to handle some features. For more info, see README.
// Contact: K. Potamianos <karolos.potamianos@cern.ch>
//==========================================================================
EOF
  sed -i "$(( ${lineNo} - 0 ))r /tmp/sed.setM4l.$$" ${DEST_DIR}/${outBaseName}.cxx
  lineNo=$( grep -n '^//==========================================================================' ${HDRS_DIR}/${outBaseName}.h | sed 's/:.*//' | head -2 | tail -1 )
  sed -i "$(( ${lineNo} - 0 ))r /tmp/sed.setM4l.$$" ${HDRS_DIR}/${outBaseName}.h

  rm /tmp/sed.setM4l.$$

done

echo Model: $( find ${PROC_DIR} -name "Parameters_*cc" | sed 's/.*Parameters_\(.*\).cc/\1/' )
exit


for i in Parameters HelAmps ; do
	file=$(find ${PROC_DIR} -name "${i}_*h")
	cp ${file} ${DEST_DIR}
	cp ${file/.h/.cc} ${DEST_DIR}/$(basename ${file/.h/.cxx})
  sed -i 's@complex<double> cI = complex<double>@// &@' ${DEST_DIR}/$(basename ${file})
done

if [ -e ${DEST_DIR}/read_slha.h ] ; then
	echo "read_slha.h already present!! Please check that's OK (by comparing the versions)"
else
	file=$(find ${PROC_DIR} -name "read_slha*h")
	cp ${file/.h/.cc} ${DEST_DIR}/$(basename ${file/.h/.cxx})
  # Preventing compilation warnings
	sed -i 's/int space_pos/std::size_t space_pos/' ${DEST_DIR}/$(basename ${file/.h/.cxx})
	
	echo "#ifndef __READ_SLHA_H__" > tmpFile
	echo "#define __READ_SLHA_H__" >> tmpFile
	cat ${file} >> tmpFile
	echo "#endif //__READ_SLHA_H__" >> tmpFile
	mv tmpFile ${DEST_DIR}/read_slha.h
fi

cp $( find ${PROC_DIR} -name "param_card*.dat" ) Cards/param_card_$( basename ${PROC_DIR} ).dat

mv ${DEST_DIR}/*.h ${HDRS_DIR}
