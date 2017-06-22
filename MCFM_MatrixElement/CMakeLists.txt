# $Id: CMakeLists.txt 790746 2016-12-21 14:00:25Z torrence $
################################################################################
# Package: MCFM_MatrixElement
################################################################################

# Declare the package name:
atlas_subdir( MCFM_MatrixElement )

# Declare the package's dependencies:
atlas_depends_on_subdirs(
  PUBLIC
  PRIVATE
  Event/xAOD/xAODBase
  Event/xAOD/xAODTruth
  PhysicsAnalysis/HiggsPhys/Run2/HZZ/Tools/MCFMGlue
  Tools/PathResolver
  )

# External dependencies:
find_package( Boost )
find_package( ROOT COMPONENTS Core MathCore Hist )

# Component(s) in the package:
atlas_add_library( MCFM_MatrixElementLib
  MCFM_MatrixElement/*.h Root/*.cxx
  PUBLIC_HEADERS MCFM_MatrixElement
  PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}  ${BOOST_INCLUDE_DIRS}
# PACKAGE_LDFLAGS      = -L$ROOTCOREBIN/../MCFM_MatrixElement/data -lmcfm_8p0    -lov_8p0 -lpv_8p0 -lrecur_8p0 -lgfortran
  PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES}
  xAODBase
  xAODTruth
  GoodRunsListsLib
  PathResolver
  )

if( XAOD_STANDALONE )

  atlas_add_executable( testME.cxx
    util/testME.cxx
    LINK_LIBRARIES  MCFM_MatrixElementLib  )
  
endif()

# Install files from the package:
atlas_install_scripts( scripts/combineDataSet.py  scripts/combineZZBkg.py  scripts/createFileList.py  scripts/getDataSets.py  scripts/unTarDataSet.py scripts/checkForCompleteness.py ) 
