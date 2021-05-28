
// The trick of customizing a derived class in place of directly the
// class generated by MakeSelector has two advantages:
// 1) you don't overwrite your code if you execute again MakeSelector
//    by mistake
// 2) if you extend your TTree with other Branches, you can execute
//    MakeSelector to update your base class, and your customizations
//    in the derived class will still work
//
// N.B. Remember to check the branches with a variable size
// array. MakeSelector try to guess the maximum possible number of
// elements, but it can be wrong..
 
 

#include "ProcessClassify.hh"

//GABRIELE

string ProcessClassify::convertInt(Int_t number)
     
{
  //Create the table in order to covert the PDGEconding 
  // to the symbol of the particle
  
  string tmps;

  //gamma
  if(number == 22) 
    {
      tmps = "g";
    }
  //proton
  else if(number == 2212) 
    {
      tmps = "p";
    }
  //neutron
  else if(number == 2112) 
    {
      tmps = "n";
    }
  //ArgonIon40
  else if(number == 1000180400) 
    {
      tmps = "Ar40";
    }
  //ArgonIon36
  else if(number == 1000180360) 
    {
      tmps = "Ar36";
    }
  //ArgonIon37
  else if(number == 1000180370) 
    {
      tmps = "Ar37";
    }
  //ArgonIon38
  else if(number == 1000180380) 
    {
      tmps = "Ar38";
    }
  //ArgonIon41
  else if(number == 1000180410)
    {
      tmps = "Ar41";
    }
  //CarbonIon12
  else if(number == 1000060120) 
    { 
      tmps = "C12";
    }
  //CarbonIon13
  else if(number == 1000060130) 
    { 
      tmps = "C13";
    }
  //OxygenIon16
  else if(number == 1000080160) 
    {
      tmps = "O16";
    }
  //OxygenIon17
  else if(number == 1000080170) 
    {
      tmps = "O17";
    }
  //OxygenIon18
  else if(number == 1000080180) 
    {
      tmps = "O18";
    }
  //CopperIon63
  else if(number == 1000290630) 
    {
      tmps = "Cu63";
    }
  //CopperIon65
  else if(number == 1000290650) 
    { 
      tmps = "Cu65";
    }
  //HeliumIon4
  else if(number == 1000020040)
    {
      tmps = "He4";
    }
  //SulfurIon33
  else if(number == 1000160330)
    {
      tmps = "S33";
    }
  //SulfurIon37
  else if(number == 1000160370)
    {
      tmps = "S37";
    }
  //NichelIon63
  else if(number == 1000280630)
    {
      tmps = "Ni63";
    }
  //ClorumIon36
  else if(number == 1000170360)
    {
      tmps = "Cl36";
    }
  //DeuteriumIon
  else if(number == 1000010020)
    {
      tmps = "H2";
    }
  //Germanium70
  else if(number == 1000320700)
    {
      tmps = "Ge70";
    }
  //Germanium72
  else if(number == 1000320720)
    {
      tmps = "Ge72";
    }
  //Germanium74
  else if(number == 1000320740)
    {
      tmps = "Ge74";
    }
  //Germanium76
  else if(number == 1000320760)
    {
      tmps = "Ge76";
    }
  
  
  else
    {
      
      stringstream ss;//create a stringstream
      ss << number;//add number to the stream
      tmps = ss.str();
    }
  
  return tmps;//return a string with the contents of the stream
  

}


Bool_t ProcessClassify::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either sel_baseclass::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  //GABRIELE from chrunmap

  fChain->GetTree()->GetEntry(entry);
  //this->GetTree()->GetEntry(entry);
  //GetEntry(entry);
  
  //Info("Process","Entry number %d processed",entry);

  Int_t i = 0;
  Double_t etot=0;
  Int_t tmp[300];

  for(int ii = 0; i<300; i++) tmp[ii]=0;

  Int_t itmp=0;
  string compos;
  bool mum1 = false;


  
  //Sum the energy to get the total and save the particles
  //with mumID==1
  for(i=0 ; i <ntracks ; i++)
    {
      etot+= edep[i];
      
      if(mum[i] == 1)
	{
	  mum1 = true;
	  tmp[i] = type[i];
	  itmp++;
	}
      
    }	
  
  //Process this particles in order to create the key for the
  //map

  if(mum1)
    {
      for(int j=0; j<itmp; j++)
	{
	  //if(tmp[j]==6) cout << "!!!!!!!!!!We found 6 in entry " << entry << endl;
	  if(j!=itmp-1) compos += convertInt(tmp[j]) + "_" ;
	  else compos+= convertInt(tmp[j]);
	}
      
      ProcessMap_t::iterator it = processmap.find(compos);

      TH1F* h;
      
      if ( it != processmap.end() )
	{
	  //This process has been already
	  //found
	  //get it and fill the histogram
	  h = it->second;

	  //std::cout << "Process already exists" << endl;
	  h->Fill(etot);
	}
      else
	{
	  //This process has not yet been found
	  //We have to create it
	  
	  h = new TH1F(compos.c_str(),compos.c_str(),2000,0,2000);
	  
	  processmap.insert( std::make_pair(compos,h) );
	  
	  cout << "New process " << compos << " inserted" << endl;

	  h->Fill(etot);
	    
	  
	}
       

      //std::cout << "The composed string is: " << compos << endl;
    }

   return kTRUE;
}


void ProcessClassify::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   Info("Begin","Executing ProcessClassify::Begin");

}

void ProcessClassify::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  Info("Terminate","Executing ProcessClassify::Terminate");

}
