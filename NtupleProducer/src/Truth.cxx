#include "include/NtupleProducer.h"

// t(2) > U/C(22) B(21) W(20) > [l(220) nu(221)] [q(222) q(223)]
// tbar(3) > U/C(32) B(31) W(30) > [l(330) nu(331)] [q(332) q(333)]
// H(1) > B(10) Bbar(11)

ClassImp(Truth)
    
Truth::Truth()
{
}

Truth::~Truth()
{
}

void Truth::read()
{
   bool verbose = 0;
   
   _mc_truth_n = 0;

   bool foundHiggs = 0;
   bool foundTop1 = 0;
   bool foundTop2 = 0;

   int nGen = ntP->gen_n;

   if( verbose ) std::cout << "---BEGIN---" << std::endl; 
   for(int i=0;i<nGen;i++)
     {
	if( abs(ntP->gen_id->at(i)) != 25 && abs(ntP->gen_id->at(i)) != 6 ) continue;

	int c = getUnique(i);
	
	int pdgid = ntP->gen_id->at(c);
	int status = ntP->gen_status->at(c);
	
	// Higgs
	if( pdgid == 25 && (status == 52 || status == 62 || status == 22) && !foundHiggs )
	  {
	     foundHiggs = 1;
	     
	     if( verbose ) std::cout << "Higgs " << std::endl;
	     
	     float pt_c = ntP->gen_pt->at(c);
	     float eta_c = ntP->gen_eta->at(c);
	     float phi_c = ntP->gen_phi->at(c);
	     float E_c = ntP->gen_E->at(c);
	     
	     _mc_truth_id.push_back(pdgid);
	     _mc_truth_pt.push_back(pt_c);
	     _mc_truth_eta.push_back(eta_c);
	     _mc_truth_phi.push_back(phi_c);
	     _mc_truth_E.push_back(E_c);
	     _mc_truth_label.push_back(1);
	     
	     for(int j=0;j<ntP->gen_daughter_n->at(c);j++)
	       {
		  int idx = ntP->gen_daughter_index->at(c)[j];
		  
		  int pdgid_c = ntP->gen_id->at(idx);
		  
		  if( abs(pdgid_c) == 5 && ntP->gen_status->at(idx) == 23 )
		    {
		       int cc = getUnique(idx);
		       
		       float pt_cc = ntP->gen_pt->at(cc);
		       float eta_cc = ntP->gen_eta->at(cc);
		       float phi_cc = ntP->gen_phi->at(cc);
		       float E_cc = ntP->gen_E->at(cc);
		       
		       _mc_truth_id.push_back(pdgid_c);
		       _mc_truth_pt.push_back(pt_cc);
		       _mc_truth_eta.push_back(eta_cc);
		       _mc_truth_phi.push_back(phi_cc);
		       _mc_truth_E.push_back(E_cc);
		       
		       if( pdgid_c == 5 ) 
			 {
			    _mc_truth_label.push_back(10);
			    if( verbose ) std::cout << "Higgs B1" << std::endl;
			 }
		       else 
			 {
			    _mc_truth_label.push_back(11);
			    if( verbose ) std::cout << "Higgs B2" << std::endl;
			 }
		    }
	       }
	  }	

	// Top
	if( status == 62 && ((pdgid == 6 && !foundTop1) || (pdgid == -6 && !foundTop2)) )
	  {
	     if( pdgid == 6 ) foundTop1 = 1;
	     if( pdgid == -6 ) foundTop2 = 1;
	     
	     float pt_c = ntP->gen_pt->at(c);
	     float eta_c = ntP->gen_eta->at(c);
	     float phi_c = ntP->gen_phi->at(c);
	     float E_c = ntP->gen_E->at(c);
	     
	     _mc_truth_id.push_back(pdgid);
	     _mc_truth_pt.push_back(pt_c);
	     _mc_truth_eta.push_back(eta_c);
	     _mc_truth_phi.push_back(phi_c);
	     _mc_truth_E.push_back(E_c);
	     
	     if( pdgid == 6 ) 
	       {
		  _mc_truth_label.push_back(2);
		  if( verbose ) std::cout << "Top 1" << std::endl;
	       }
	     else 
	       {
		  _mc_truth_label.push_back(3);
		  if( verbose ) std::cout << "Top 2" << std::endl;
	       }

	     for(int j=0;j<ntP->gen_daughter_n->at(c);j++)
	       {
		  int idx = ntP->gen_daughter_index->at(c)[j];
		  
		  int pdgid_c = ntP->gen_id->at(idx);

		  bool foundq1 = 0;
		  bool foundq2 = 0;
		  
		  // TopW
		  if( abs(pdgid_c) == 24 )
		    {
		       int cc = getUnique(idx);
		       
		       float pt_cc = ntP->gen_pt->at(cc);
		       float eta_cc = ntP->gen_eta->at(cc);
		       float phi_cc = ntP->gen_phi->at(cc);
		       float E_cc = ntP->gen_E->at(cc);

		       _mc_truth_id.push_back(pdgid_c);
		       _mc_truth_pt.push_back(pt_cc);
		       _mc_truth_eta.push_back(eta_cc);
		       _mc_truth_phi.push_back(phi_cc);
		       _mc_truth_E.push_back(E_cc);
		       
		       if( pdgid == 6 ) 
			 {
			    _mc_truth_label.push_back(20);
			    if( verbose ) std::cout << "Top W 1" << std::endl;
			 }
		       else 
			 {
			    _mc_truth_label.push_back(30);
			    if( verbose ) std::cout << "Top W 2" << std::endl;
			 }

		       for(int j2=0;j2<ntP->gen_daughter_n->at(cc);j2++)
			 {
			    int idx2 = ntP->gen_daughter_index->at(cc)[j2];
		  
			    int pdgid_cc = ntP->gen_id->at(idx2);
		  
			    int momPdgid_cc = ntP->gen_id->at(ntP->gen_mother_index->at(idx2));
			    
			    // TopWl/nu
			    if( (abs(pdgid_cc) == 11 || abs(pdgid_cc) == 13 || abs(pdgid_cc) == 15 ||
				 abs(pdgid_cc) == 12 || abs(pdgid_cc) == 14 || abs(pdgid_cc) == 16) &&
				abs(momPdgid_cc) != 15 )
			      {
				 int ccc = getUnique(idx2);
				 
				 float pt_ccc = ntP->gen_pt->at(ccc);
				 float eta_ccc = ntP->gen_eta->at(ccc);
				 float phi_ccc = ntP->gen_phi->at(ccc);
				 float E_ccc = ntP->gen_E->at(ccc);

				 _mc_truth_id.push_back(pdgid_cc);
				 _mc_truth_pt.push_back(pt_ccc);
				 _mc_truth_eta.push_back(eta_ccc);
				 _mc_truth_phi.push_back(phi_ccc);
				 _mc_truth_E.push_back(E_ccc);
				 
				 if( (abs(pdgid_cc) == 11 || abs(pdgid_cc) == 13 || abs(pdgid_cc) == 15) && pdgid == 6 ) 
				   {
				      _mc_truth_label.push_back(220);
				      if( verbose ) std::cout << "Top W l 1 " << momPdgid_cc << std::endl;
				   }
				 if( (abs(pdgid_cc) == 11 || abs(pdgid_cc) == 13 || abs(pdgid_cc) == 15) && pdgid == -6 ) 
				   {
				      _mc_truth_label.push_back(330);
				      if( verbose ) std::cout << "Top W l 2 " << momPdgid_cc << std::endl;
				   }
				 if( (abs(pdgid_cc) == 12 || abs(pdgid_cc) == 14 || abs(pdgid_cc) == 16) && pdgid == 6 ) 
				   {
				      _mc_truth_label.push_back(221);
				      if( verbose ) std::cout << "Top W nu 1 " << momPdgid_cc << std::endl;
				   }
				 if( (abs(pdgid_cc) == 12 || abs(pdgid_cc) == 14 || abs(pdgid_cc) == 16) && pdgid == -6 ) 
				   {
				      _mc_truth_label.push_back(331);
				      if( verbose ) std::cout << "Top W nu 2 " << momPdgid_cc << std::endl;
				   }
			      }

			    // TopWqq
			    if( abs(pdgid_cc) <= 6 && ntP->gen_status->at(idx2) == 23 )
			      {
				 int ccc = getUnique(idx2);
				 
				 float pt_ccc = ntP->gen_pt->at(ccc);
				 float eta_ccc = ntP->gen_eta->at(ccc);
				 float phi_ccc = ntP->gen_phi->at(ccc);
				 float E_ccc = ntP->gen_E->at(ccc);

				 _mc_truth_id.push_back(pdgid_cc);
				 _mc_truth_pt.push_back(pt_ccc);
				 _mc_truth_eta.push_back(eta_ccc);
				 _mc_truth_phi.push_back(phi_ccc);
				 _mc_truth_E.push_back(E_ccc);

				 if( pdgid == 6 ) 
				   {
				      if( !foundq1 ) 
					{
					   _mc_truth_label.push_back(222);
					   if( verbose ) std::cout << "Top W q 1" << std::endl;
					}
				      else 
					{
					   _mc_truth_label.push_back(223);
					   if( verbose ) std::cout << "Top W q 1" << std::endl;
					}
				      foundq1 = 1;
				   }
				 else 
				   {
				      if( !foundq2 ) 
					{
					   _mc_truth_label.push_back(332);
					   if( verbose ) std::cout << "Top W q 2" << std::endl;
					}
				      else 
					{
					   _mc_truth_label.push_back(333);
					   if( verbose ) std::cout << "Top W q 2" << std::endl;
					}
				      foundq2 = 1;
				   }
			      }
			 }
		    }
		 
		  // TopB
		  if( (abs(pdgid_c) == 5 || abs(pdgid_c) == 3 || abs(pdgid_c) == 1) &&
		      ntP->gen_status->at(idx) == 23 )
		    {
		       int cc = getUnique(idx);
		       
		       float pt_cc = ntP->gen_pt->at(cc);
		       float eta_cc = ntP->gen_eta->at(cc);
		       float phi_cc = ntP->gen_phi->at(cc);
		       float E_cc = ntP->gen_E->at(cc);

		       _mc_truth_id.push_back(pdgid_c);
		       _mc_truth_pt.push_back(pt_cc);
		       _mc_truth_eta.push_back(eta_cc);
		       _mc_truth_phi.push_back(phi_cc);
		       _mc_truth_E.push_back(E_cc);
		       
		       if( pdgid == 6 ) 
			 {
			    _mc_truth_label.push_back(21);
			    if( verbose ) std::cout << "Top B 1" << std::endl;
			 }
		       else 
			 {
			    _mc_truth_label.push_back(31);
			    if( verbose ) std::cout << "Top B 2" << std::endl;
			 }
		    }		  

		  // TopU/C
		  if( (abs(pdgid_c) == 2 || abs(pdgid_c) == 4) &&
		      ntP->gen_status->at(idx) == 23 )
		    {
		       int cc = getUnique(idx);
		       
		       float pt_cc = ntP->gen_pt->at(cc);
		       float eta_cc = ntP->gen_eta->at(cc);
		       float phi_cc = ntP->gen_phi->at(cc);
		       float E_cc = ntP->gen_E->at(cc);

		       _mc_truth_id.push_back(pdgid_c);
		       _mc_truth_pt.push_back(pt_cc);
		       _mc_truth_eta.push_back(eta_cc);
		       _mc_truth_phi.push_back(phi_cc);
		       _mc_truth_E.push_back(E_cc);
		       
		       if( pdgid == 6 ) 
			 {
			    _mc_truth_label.push_back(22);
			    if( verbose ) std::cout << "Top U/C 1" << std::endl;
			 }
		       else 
			 {
			    _mc_truth_label.push_back(32);
			    if( verbose ) std::cout << "Top U/C 2" << std::endl;
			 }
		    }		  
	       }
	  }	
     }
   
   _mc_truth_n = _mc_truth_id.size();
   
   if( verbose ) std::cout << "--END---" << std::endl;
}

void Truth::init()
{
   _mc_truth_n = 0;
   
   _mc_truth_id.clear();
   _mc_truth_pt.clear();
   _mc_truth_eta.clear();
   _mc_truth_phi.clear();
   _mc_truth_E.clear();
   _mc_truth_label.clear();
}

int Truth::getUnique(int p)
{   
   int pcur = p;
   
   int nLimit = 1000; // temporary fix
      
   int iter = 0;
   while( 1 )
     {	
	bool foundDupl = false;
	
	std::vector<int> daug = ntP->gen_daughter_index->at(pcur);
	int Ndaug = ntP->gen_daughter_n->at(pcur);
	  
	for(int ip=0;ip<Ndaug;ip++)
	  {	     
	     int d = daug[ip];

	     if( ntP->gen_id->at(d) == ntP->gen_id->at(pcur) && pcur != d )
	       {
		  pcur = d;
		  foundDupl = true;
		  break;
	       }
	  }	
	
	if( !foundDupl ) break;
	if( iter > nLimit ) break;
	iter++;
     }
   
   return pcur;
}
