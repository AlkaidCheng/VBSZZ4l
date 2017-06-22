# $Id: CMakeLists.txt 790746 2016-12-21 14:00:25Z torrence $
################################################################################
# Package: H4lProcessMinitree
################################################################################

# Declare the package name:
atlas_subdir( H4lProcessMinitree )

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
  DataQuality/GoodRunsLists
  PhysicsAnalysis/HiggsPhys/Run2/HZZ/Tools/HZZUtils
  ${extra_dep} )

# External dependencies:
find_package( ROOT COMPONENTS Core MathCore Hist )

# Component(s) in the package:
atlas_add_library( H4lProcessMinitreeLib
  H4lProcessMinitree/*.h Root/*.cxx
  PUBLIC_HEADERS H4lProcessMinitree
  PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} 
  PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES}
  GoodRunsListsLib
  AsgTools
  HZZUtilsLib )

if( XAOD_STANDALONE )

  atlas_add_executable( combineMinitree
    util/combineMinitree.cxx
    INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} 
    LINK_LIBRARIES  ${ROOT_LIBRARIES} H4lProcessMinitreeLib )
  
endif()

# Install files from the package:
atlas_install_scripts( scripts/combineDataSet.py  scripts/combineZZBkg.py  scripts/createFileList.py  scripts/getDataSets.py  scripts/unTarDataSet.py scripts/checkForCompleteness.py ) 
