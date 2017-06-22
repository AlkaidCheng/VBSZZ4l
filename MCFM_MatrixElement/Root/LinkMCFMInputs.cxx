#include <boost/filesystem.hpp>
#include <iostream>
#include <string>
#include "PathResolver/PathResolver.h"

// method to link the MCFM input files into the current working directory.
// This is needed as the limited input file name length in mcfm_init_
// prevents passing the standard <...>/RootCoreBin/Data/MCFM_MatrixElement path

namespace HSG2_MCFM{
  bool OrganiseMCFMStuff(){

    std::cout << "  --> Organising the MCFM inputs... "<<std::endl;
    std::string DataPath = PathResolverFindCalibFile("MCFM_MatrixElement/input13TeV.DAT");
    // we link the contents of DataPath into the cwd
    if (DataPath == ""){
      std::cerr << "Unable to pick up the data path from which to collect the MCFM files! Is everything compiled correctly?"<<std::endl;
      return false;
    }
    boost::filesystem::path Path(DataPath);
    Path = Path.parent_path();
    std::cout <<" My Data path is "<<DataPath<<std::endl;
    boost::filesystem::path CWD(boost::filesystem::current_path());
    try {
      if (boost::filesystem::exists(Path)){
        if (!boost::filesystem::is_directory(Path)){
          std::cerr << "The passed data path "<<Path<<" for the MCFM files is not a directory!"<<std::endl;
          return 1;
        }
        for (boost::filesystem::directory_entry & entry : boost::filesystem::directory_iterator(Path)){
          std::cout << " Taking care of "<<entry.path()<<std::endl;
          boost::filesystem::path tarpath = CWD;
          tarpath += boost::filesystem::path("/");
          tarpath += entry.path().filename();
          if (boost::filesystem::exists(tarpath)){
            std::cout << tarpath <<" already exists, cool! "<<std::endl;
            continue;
          }
          if(boost::filesystem::is_directory(entry.path())){
            std::cout << "Creating a symlink "<< tarpath<<" to dir "<<entry.path()<<std::endl;
            boost::filesystem::create_directory_symlink(entry.path(), tarpath);
          }
          else {
            std::cout << "Creating a symlink "<<tarpath<<" to file "<<entry.path()<<std::endl;
            boost::filesystem::create_symlink(entry.path(),tarpath);
          }
        }
      }
    }
    catch (const boost::filesystem::filesystem_error & err) {
        std::cerr << err.what()<<std::endl;
        return false;
    }
    std::cout << " ---> Done! "<<std::endl;
    return true;

  }
}
