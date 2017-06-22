# $Id: CMakeLists.txt 790746 2016-12-21 14:00:25Z torrence $
################################################################################
# Package: H4lBDTWeights
################################################################################

# Declare the package name:
atlas_subdir( H4lBDTWeights )

# Extra dependencies based on the environment:
set( extra_dep )
if( XAOD_STANDALONE )
   set( extra_dep Control/xAODRootAccess )
else()
   set( extra_dep GaudiKernel )
endif()

# Declare the package's dependencies:
atlas_depends_on_subdirs(
  PUBLIC
  PRIVATE
  Control/AthToolSupport/AsgTools
  Event/xAOD/xAODBase
  Event/xAOD/xAODTruth
  PhysicsAnalysis/HiggsPhys/HSG2/H4lMVDiscriminants/MadGraphME
  Tools/PathResolver
${extra_dep} )

# External dependencies:
find_package( ROOT COMPONENTS Core MathCore Hist RooFitCore RooFit TMVA )

# Component(s) in the package:
atlas_add_library( H4lBDTWeightsLib
  H4lBDTWeights/*.h Root/*.cxx
  PUBLIC_HEADERS H4lBDTWeights
  PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} 
  PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES}
  AsgTools
  xAODBase
  xAODTruth
  MadGraphMELib
  PathResolver
  )

# Install files from the package:
atlas_install_data( data/* )
