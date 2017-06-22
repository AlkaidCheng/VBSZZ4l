# $Id: CMakeLists.txt 790746 2016-12-21 14:00:25Z torrence $
################################################################################
# Package: HZZUtils
################################################################################

# Declare the package name:
atlas_subdir( HZZUtils )

# Extra dependencies based on the environment:
set( extra_dep )
# set( extra_libs )
if( XAOD_STANDALONE )
   set( extra_dep Control/xAODRootAccess )
   # set( extra_libs xAODRootAccess )
else()
   set( extra_dep GaudiKernel )
   # set( extra_libs GaudiKernel AthAnalysisBaseCompsLib )
endif()

# Declare the package's dependencies:
atlas_depends_on_subdirs(
  PUBLIC
  PRIVATE
  Control/AthToolSupport/AsgTools
  Event/FourMomUtils
  Event/xAOD/xAODEgamma
  Event/xAOD/xAODEventInfo
  Event/xAOD/xAODJet
  Event/xAOD/xAODTruth
  PhysicsAnalysis/AnalysisCommon/PATInterfaces
  PhysicsAnalysis/MCTruthClassifier
  Tools/PathResolver
  ${extra_dep} )

# External dependencies:
find_package( ROOT COMPONENTS Core MathCore Hist )

# Component(s) in the package:
atlas_add_library( HZZUtilsLib
  HZZUtils/*.h Root/*.cxx
  PUBLIC_HEADERS HZZUtils
  PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} Root
  PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES}
  AsgTools
  FourMomUtils
  xAODEgamma
  xAODEventInfo
  xAODJet
  xAODTruth
  MCTruthClassifierLib
  PATInterfaces
  PathResolver
  # ${extra_libs}
  )

if( XAOD_STANDALONE )
  atlas_add_executable( testHZZUtils
    util/testHZZUtils.cxx
    INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} 
    LINK_LIBRARIES ${ROOT_LIBRARIES} xAODRootAccess HZZUtilsLib )
  
  # atlas_add_executable( testHZZUtilsElectronClassifier
  #   util/testHZZUtilsElectronClassifier.cxx
  #   PRIVATE_CXXFLAGS -DROOTCORE
  #   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS}
  #   LINK_LIBRARIES ${ROOT_LIBRARIES} HZZUtilsLib )
endif()

# Install files from the package:

