/************************************************************************************
   in ROOT interpreted mode, e.g.:

   $ root -b ApplyBDTforCategories_Example.C'("you_ntuple_file","Categories_BDTG_mjjAbove130GeV.class.C")'

   Should you encounter any problem, don't hesitate to contact us.

        Authors: G. Artoni  [Giacomo.Artoni@cern.ch]
                 G. Sciolla [sciolla@brandeis.edu]
                 S. Zambito [stefano.zambito@cern.ch]

        Brandeis University (US) 

************************************************************************************/

void ApplyCategoriesDiscriminant( TString tree_name, TString ntuple_fname, TString weights_fname, TString branch_name, TString config_file ) 
{
  gROOT->LoadMacro( weights_fname+"++" ); // usage in ROOT

  std::vector<std::string> inputVars;
  inputVars.push_back("dijet_invmass");
  inputVars.push_back("dijet_deltaeta");
  inputVars.push_back("leading_jet_pt");
  inputVars.push_back("subleading_jet_pt");
  inputVars.push_back("leading_jet_eta");
    
  // create a class object for the BDT response
  IClassifierReader* MVAResponseBDTG = new ReadBDTG( inputVars );
  
  // open input ntuple
  TFile *input  = TFile::Open( ntuple_fname, "READ" ); 
  TTree *theTree     = (TTree*)input->Get(tree_name);
  theTree->Print();
  std::cout << "--- MVAClassificationApplication       :: Processing input file " << input->GetName() << std::endl;

  // create output ntuple
  TString out_fname = ntuple_fname;
  TString add;
  if( weights_fname.Contains( "VBF" ) ) add = "_withVBF_MVA.root";
  else if( weights_fname.Contains( "HadVH" ) ) add = "_withHadVH_MVA.root";
  else add = "_withMVA.root";
  out_fname.ReplaceAll(".root",add);
  TFile *output = TFile::Open( out_fname, "RECREATE" ); 
  TTree *theClonedTree     = (TTree*)theTree->CloneTree();

  Float_t dijet_m_leadsub, dijet_deltaeta_leadsub, lead_jet_pt, sub_jet_pt, lead_jet_eta;
  Int_t has2jetbins; // flag that identifies all the events with at least 2 jets

  // N.B. modify this according to your ntuple's nomenclature!!!
  TString dijet_invmass_name = GetName( config_file, "Di-Jet Invariant Mass" );
  TString dijet_deltaeta_name = GetName( config_file, "Di-Jet Delta Eta" );
  TString leadjet_pt_name = GetName( config_file, "Leading Jet Pt" );
  TString subjet_pt_name = GetName( config_file, "Sub-leading Jet Pt" );
  TString leadjet_eta_name = GetName( config_file, "Leading Jet Eta" );
  TString has2jets_name = GetName( config_file, "Has At Least 2 Jets" );
  cout << dijet_invmass_name << endl;
  theTree->SetBranchAddress( dijet_invmass_name, &dijet_m_leadsub );//CHANGEME
  theTree->SetBranchAddress( dijet_deltaeta_name, &dijet_deltaeta_leadsub );//CHANGEME
  theTree->SetBranchAddress( leadjet_pt_name, &lead_jet_pt );//CHANGEME
  theTree->SetBranchAddress( subjet_pt_name, &sub_jet_pt );//CHANGEME
  theTree->SetBranchAddress( leadjet_eta_name, &lead_jet_eta );//CHANGEME
  theTree->SetBranchAddress( has2jets_name, &has2jetbins );

  // add the MVA output to the tree
  std::vector<double> inputVec( inputVars.size() );
  Float_t discriminant(-999.9); // dummy value
  TBranch *br_discriminant = theClonedTree->Branch( branch_name, &discriminant, branch_name + "/F" );

  for (Long64_t ievt=0; ievt<theTree->GetEntries(); ievt++) {

    //if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
    theTree->GetEntry(ievt);
    
    // missing the variables needed for computing the discriminant! 
    if( has2jetbins == 0 ) {
      discriminant = -999.9;
    } else {

      // compute the input variables for the event
      // BEWARE OF THE VECTOR'S ORDERING //
      inputVec[0] = dijet_m_leadsub;
      inputVec[1] = dijet_deltaeta_leadsub;
      inputVec[2] = lead_jet_pt;
      inputVec[3] = sub_jet_pt;
      inputVec[4] = lead_jet_eta;

      // get the Discriminant response                              
      discriminant = MVAResponseBDTG->GetMvaValue( inputVec );
    }
    br_discriminant->Fill();
  }
  
  theClonedTree->Write();
  output->Write();
  output->Close();
  input->Close();
  std::cout << "--- MVAClassificationApplication       :: Done! Output file saved as '" << output->GetName() << "'." << std::endl;

}

TString GetName( TString config_file, TString variable ) {
  TString result = "";
  ifstream fin;
  const int MAX_CHARS_PER_LINE = 512;
  const int MAX_TOKENS_PER_LINE = 40;
  const char* const DELIMITER = "|";
  fin.open( config_file );
  if( !fin.good() ) { std::cout << "Problem opening " << config_file << " file, exiting." << std::endl; exit( -1 ); }
  while( !fin.eof()) {
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    TString line = buf;
    if( line.Contains( "#" ) ) continue;
    if( line.Contains( variable ) ) {
      const char* token[MAX_TOKENS_PER_LINE] = {};
      token[ 0 ] = strtok( buf, DELIMITER );
      if ( token[ 0 ] ) {
        token[ 1 ] = strtok( 0, DELIMITER ); // subsequent tokens
      }
      if( token[ 1 ] ) result = token[ 1 ];
      result = result.ReplaceAll( " ", "" );
    }
  }
  if( result == "" ) {
    std::cout << "Problem while reading " << config_file << ", variable " << variable << " not found, exiting." << std::endl; 
    exit( -1 );;
  }
  else return result;
}
