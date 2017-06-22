###################################################################################
# Package: CategoriesMVA
###################################################################################

# Declare the package name:
atlas_subdir( CategoriesMVA )

# Extra dependencies based on the environment:
set( extra_dep )
if( XAOD_STANDALONE )
   set( extra_dep Control/xAODRootAccess )
   set( extra_libs xAODRootAccess )
else()
   set( extra_dep GaudiKernel )
   set( extra_libs GaudiKernel )
endif()

# Declare the package's dependencies:
atlas_depends_on_subdirs(
  PUBLIC
  PRIVATE
  Control/AthToolSupport/AsgTools
  Event/FourMomUtils
  Event/xAOD/xAODBase
  PhysicsAnalysis/HiggsPhys/HSG2/H4lMVDiscriminants/MadGraphME
  Tools/PathResolver
  ${extra_dep} )


# External dependencies:
find_package( ROOT COMPONENTS Core Tree MathCore MathMore Hist RIO pthread RooFitCore RooFit TMVA LHAPDF)

# Component(s) in the package:
atlas_add_library( CategoriesMVALib
                   src/*.cxx
                   Root/*.cxx
                   PUBLIC_HEADERS CategoriesMVA
                   PRIVATE_INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                   LINK_LIBRARIES 
                   PRIVATE_LINK_LIBRARIES ${ROOT_LIBRARIES} xAODBase AsgTools PathResolver  MadGraphMELib ${extra_libs})

if( NOT XAOD_STANDALONE )
  atlas_add_component( CategoriesMVA
    src/components/*.cxx
    INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
    LINK_LIBRARIES ${ROOT_LIBRARIES} xAODBase AsgTools PathResolver MadGraphMELib CategoriesMVALib ${extra_libs} )

atlas_add_dictionary( CategoriesMVADict
                      CategoriesMVA/CategoriesMVADict.h
                      CategoriesMVA/selection.xml
                      INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
                      LINK_LIBRARIES ${ROOT_LIBRARIES} xAODBase AsgTools xAODCore PathResolver MadGraphMELib CategoriesMVALib ${extra_libs})

endif()

# Install files from the package:
atlas_install_data( data/* )

