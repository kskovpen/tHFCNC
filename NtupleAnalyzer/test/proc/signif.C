void signif()
{
   gROOT->SetBatch(1);

   gROOT->ProcessLine(".x common.C");
   gROOT->ProcessLine(".L addbin.C");
   gROOT->ProcessLine(".x def.C");
   gROOT->ProcessLine(".L doublepl.C");
   
   std::string ana = "TZq";
   const int nchan = 1;
   std::string chan[nchan] = {"LL"};
   std::string sel = "L2OS_4J";
   std::string sys = "NOMINAL";

//   Double_t cut = 110.;
   
   const int nvar = 2;
   std::string var[nvar] = 
     {
	"b_btag",
	"met"
     };

   const int nsampSIG = v_sig_name.size();
   std::string sampSIG[nsampSIG];
   std::string sampSIGfile[nsampSIG];
   for(int i=0;i<nsampSIG;i++)
     {
	sampSIG[i] = v_sig_name[i].c_str();
	sampSIGfile[i] = v_sig[i].c_str();
     }   
   
   int n_zjets = v_zjets_name.size();
   int n_top = v_top_name.size();
   int n_dbx = v_dbx_name.size();
   const int nsampBKG = n_zjets +
     n_top + n_dbx;
//   const int nsampBKG = n_dbx;
   std::string sampBKG[nsampBKG];
   std::string sampBKGfile[nsampBKG];
   for(int i=0;i<n_zjets;i++)
     {
	sampBKG[i] = v_zjets_name[i].c_str();
	sampBKGfile[i] = v_zjets[i].c_str();
     }   
   for(int i=0;i<n_top;i++)
     {
	sampBKG[i+n_zjets] = v_top_name[i].c_str();
	sampBKGfile[i+n_zjets] = v_top[i].c_str();
     }   
   for(int i=0;i<n_dbx;i++)
     {
	sampBKG[i+n_zjets+n_top] = v_dbx_name[i].c_str();
	sampBKGfile[i+n_zjets+n_top] = v_dbx[i].c_str();
     }
/*   for(int i=0;i<n_dbx;i++)
     {
	sampBKG[i] = v_dbx_name[i].c_str();
	sampBKGfile[i] = v_dbx[i].c_str();
     }*/

   double l1_pt, l1_eta, l1_phi, l1_m;
   int l1_type, l1_charge;
   double l2_pt, l2_eta, l2_phi, l2_m;
   int l2_type, l2_charge;
   double l3_pt, l3_eta, l3_phi, l3_m;
   int l3_type, l3_charge;
   double j1_pt, j1_eta, j1_phi, j1_m, j1_btag;
   int j1_ntrk;
   double j2_pt, j2_eta, j2_phi, j2_m, j2_btag;
   int j2_ntrk;
   double j3_pt, j3_eta, j3_phi, j3_m, j3_btag;
   int j3_ntrk;
   double b_pt, b_eta, b_phi, b_m, b_btag;
   int b_ntrk;
   double met, met_phi, weight;
   
   TChain *ch[2];
   
   for(int k=0;k<2;k++)
     {	
	ch[k] = new TChain("tr");
   
	ch[k]->SetBranchAddress("l1_pt",&l1_pt);
	ch[k]->SetBranchAddress("l1_eta",&l1_eta);
	ch[k]->SetBranchAddress("l1_phi",&l1_phi);
	ch[k]->SetBranchAddress("l1_m",&l1_m);
	ch[k]->SetBranchAddress("l1_type",&l1_type);
	ch[k]->SetBranchAddress("l1_charge",&l1_charge);

	ch[k]->SetBranchAddress("l2_pt",&l2_pt);
        ch[k]->SetBranchAddress("l2_eta",&l2_eta);
	ch[k]->SetBranchAddress("l2_phi",&l2_phi);
	ch[k]->SetBranchAddress("l2_m",&l2_m);
	ch[k]->SetBranchAddress("l2_type",&l2_type);
	ch[k]->SetBranchAddress("l2_charge",&l2_charge);
	
	ch[k]->SetBranchAddress("l3_pt",&l3_pt);
	ch[k]->SetBranchAddress("l3_eta",&l3_eta);
	ch[k]->SetBranchAddress("l3_phi",&l3_phi);
	ch[k]->SetBranchAddress("l3_m",&l3_m);
	ch[k]->SetBranchAddress("l3_type",&l3_type);
	ch[k]->SetBranchAddress("l3_charge",&l3_charge);
	
	ch[k]->SetBranchAddress("j1_pt",&j1_pt);
	ch[k]->SetBranchAddress("j1_eta",&j1_eta);
	ch[k]->SetBranchAddress("j1_phi",&j1_phi);
	ch[k]->SetBranchAddress("j1_m",&j1_m);
	ch[k]->SetBranchAddress("j1_ntrk",&j1_ntrk);
	ch[k]->SetBranchAddress("j1_btag",&j1_btag);
	
	ch[k]->SetBranchAddress("j2_pt",&j2_pt);
	ch[k]->SetBranchAddress("j2_eta",&j2_eta);
	ch[k]->SetBranchAddress("j2_phi",&j2_phi);
	ch[k]->SetBranchAddress("j2_m",&j2_m);
	ch[k]->SetBranchAddress("j2_ntrk",&j2_ntrk);
	ch[k]->SetBranchAddress("j2_btag",&j2_btag);
	
	ch[k]->SetBranchAddress("j3_pt",&j3_pt);
	ch[k]->SetBranchAddress("j3_eta",&j3_eta);
	ch[k]->SetBranchAddress("j3_phi",&j3_phi);
	ch[k]->SetBranchAddress("j3_m",&j3_m);
	ch[k]->SetBranchAddress("j3_ntrk",&j3_ntrk);
	ch[k]->SetBranchAddress("j3_btag",&j3_btag);
	
	ch[k]->SetBranchAddress("b_pt",&b_pt);
	ch[k]->SetBranchAddress("b_eta",&b_eta);
	ch[k]->SetBranchAddress("b_phi",&b_phi);
	ch[k]->SetBranchAddress("b_m",&b_m);
	ch[k]->SetBranchAddress("b_ntrk",&b_ntrk);
	ch[k]->SetBranchAddress("b_btag",&b_btag);
	
	ch[k]->SetBranchAddress("met",&met);
	ch[k]->SetBranchAddress("met_phi",&met_phi);
	ch[k]->SetBranchAddress("weight",&weight);

	int nsamp = nsampSIG;
	if( k == 1 ) nsamp = nsampBKG;
	
	for(int i=0;i<nsamp;i++)
	  {	
	     for(int j=0;j<nchan;j++)
	       {
		  std::string treeName = "";
		  if( k == 0 ) treeName = ana+"MEM/"+chan[j]+"/"+sel+"/"+sampSIG[i]+"/"+sys+"/tr";
		  if( k == 1 ) treeName = ana+"MEM/"+chan[j]+"/"+sel+"/"+sampBKG[i]+"/"+sys+"/tr";
		  ch[k]->SetName(treeName.c_str());
		  std::string fileName = "";
		  if( k == 0 ) fileName = sampSIGfile[i];
		  if( k == 1 ) fileName = sampBKGfile[i];
		  ch[k]->Add(fileName.c_str());
	       }	
	  }   
     }

   TH1D *h_sig[nvar];
   TH1D *h_bkg[nvar];
   
   for(int j=0;j<nvar;j++)
     {
	std::string hname_sig = "h_sig_" + var[j];
	std::string hname_bkg = "h_bkg_" + var[j];
	
	if( var[j] == "b_btag" )
	  {
	     h_sig[j] = new TH1D(hname_sig.c_str(),hname_sig.c_str(),3,0.5,3.5);
	     h_bkg[j] = new TH1D(hname_bkg.c_str(),hname_bkg.c_str(),3,0.5,3.5);
	     h_sig[j]->Sumw2();
	     h_bkg[j]->Sumw2();
	  }	
	else if( var[j] == "met" )
	  {
	     h_sig[j] = new TH1D(hname_sig.c_str(),hname_sig.c_str(),30,0.,100.);
	     h_bkg[j] = new TH1D(hname_bkg.c_str(),hname_bkg.c_str(),30,0.,100.);
	     h_sig[j]->Sumw2();
	     h_bkg[j]->Sumw2();
	  }	
     }  
   
   int nEventsSig = ch[0]->GetEntries();
   for(int i=0;i<nEventsSig;i++)
     {
	ch[0]->GetEntry(i);
	
	for(int j=0;j<nvar;j++)
	  {
	     if( var[j] == "b_btag" )
	       {
		  double j1_btag_res = 0;
		  if( j1_btag > 0.244 ) j1_btag_res = 1;
		  if( j1_btag > 0.679 ) j1_btag_res = 2;
		  if( j1_btag > 0.898 ) j1_btag_res = 3;
		  double j2_btag_res = 0;
		  if( j2_btag > 0.244 ) j2_btag_res = 1;
		  if( j2_btag > 0.679 ) j2_btag_res = 2;
		  if( j2_btag > 0.898 ) j2_btag_res = 3;
		  double j3_btag_res = 0;
		  if( j3_btag > 0.244 ) j3_btag_res = 1;
		  if( j3_btag > 0.679 ) j3_btag_res = 2;
		  if( j3_btag > 0.898 ) j3_btag_res = 3;
		  double b_btag_res = 0;
		  if( b_btag > 0.244 ) b_btag_res = 1;
		  if( b_btag > 0.679 ) b_btag_res = 2;
		  if( b_btag > 0.898 ) b_btag_res = 3;
		  // at least one b-tagged
/*		  if( j1_btag_res == 1 || j2_btag_res == 1 || j3_btag_res == 1 || b_btag_res == 1 )
		    {
		       h_sig[j]->Fill(1,weight);
		    }		  
		  else if( j1_btag_res == 2 || j2_btag_res == 2 || j3_btag_res == 2 || b_btag_res == 2 )
		    {
		       h_sig[j]->Fill(2,weight);
		       h_sig[j]->Fill(1,weight);
		    }		  
		  else if( j1_btag_res == 3 || j2_btag_res == 3 || j3_btag_res == 3 || b_btag_res == 3 )
		    {
		       h_sig[j]->Fill(3,weight);
		       h_sig[j]->Fill(2,weight);
		       h_sig[j]->Fill(1,weight);
		    }*/
		  // only one b-tagged
		  if( ((j1_btag_res == 1) && j2_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j2_btag_res == 1) && j1_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j3_btag_res == 1) && j1_btag_res == 0 && j2_btag_res == 0 && b_btag_res == 0) ||
		      ((b_btag_res == 1) && j1_btag_res == 0 && j2_btag_res == 0 && j3_btag_res == 0) ) 
		    {
		       h_sig[j]->Fill(1,weight);
		    }		  
		  else if( ((j1_btag_res == 2) && j2_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j2_btag_res == 2) && j1_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j3_btag_res == 2) && j1_btag_res == 0 && j2_btag_res == 0 && b_btag_res == 0) ||
		      ((b_btag_res == 2) && j1_btag_res == 0 && j2_btag_res == 0 && j3_btag_res == 0) ) 
		    {
		       h_sig[j]->Fill(2,weight);
		       h_sig[j]->Fill(1,weight);
		    }		  
		  else if( ((j1_btag_res == 3) && j2_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j2_btag_res == 3) && j1_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j3_btag_res == 3) && j1_btag_res == 0 && j2_btag_res == 0 && b_btag_res == 0) ||
		      ((b_btag_res == 3) && j1_btag_res == 0 && j2_btag_res == 0 && j3_btag_res == 0) ) 
		    {
		       h_sig[j]->Fill(3,weight);
		       h_sig[j]->Fill(2,weight);
		       h_sig[j]->Fill(1,weight);
		    }
		  else h_sig[j]->Fill(0,weight);
	       }	     
	     else if( var[j] == "met" )
	       {
		  h_sig[j]->Fill(met,weight);
	       }	     
	  }	
     }  

   int nEventsBkg = ch[0]->GetEntries();
   for(int i=0;i<nEventsBkg;i++)
     {
	ch[1]->GetEntry(i);
	
	for(int j=0;j<nvar;j++)
	  {
	     if( var[j] == "b_btag" )
	       {		  
		  double j1_btag_res = 0;
		  if( j1_btag > 0.244 ) j1_btag_res = 1;
		  if( j1_btag > 0.679 ) j1_btag_res = 2;
		  if( j1_btag > 0.898 ) j1_btag_res = 3;
		  double j2_btag_res = 0;
		  if( j2_btag > 0.244 ) j2_btag_res = 1;
		  if( j2_btag > 0.679 ) j2_btag_res = 2;
		  if( j2_btag > 0.898 ) j2_btag_res = 3;
		  double j3_btag_res = 0;
		  if( j3_btag > 0.244 ) j3_btag_res = 1;
		  if( j3_btag > 0.679 ) j3_btag_res = 2;
		  if( j3_btag > 0.898 ) j3_btag_res = 3;
		  double b_btag_res = 0;
		  if( b_btag > 0.244 ) b_btag_res = 1;
		  if( b_btag > 0.679 ) b_btag_res = 2;
		  if( b_btag > 0.898 ) b_btag_res = 3;
		  // at least one b-tagged
/*		  if( j1_btag_res == 1 || j2_btag_res == 1 || j3_btag_res == 1 || b_btag_res == 1 )
		    {
		       h_bkg[j]->Fill(1,weight);
		    }		  
		  else if( j1_btag_res == 2 || j2_btag_res == 2 || j3_btag_res == 2 || b_btag_res == 2 )
		    {
		       h_bkg[j]->Fill(2,weight);
		       h_bkg[j]->Fill(1,weight);
		    }		  
		  else if( j1_btag_res == 3 || j2_btag_res == 3 || j3_btag_res == 3 || b_btag_res == 3 )
		    {
		       h_bkg[j]->Fill(3,weight);
		       h_bkg[j]->Fill(2,weight);
		       h_bkg[j]->Fill(1,weight);
		    }*/
		  // only one b-tagged
		  if( ((j1_btag_res == 1) && j2_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j2_btag_res == 1) && j1_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j3_btag_res == 1) && j1_btag_res == 0 && j2_btag_res == 0 && b_btag_res == 0) ||
		      ((b_btag_res == 1) && j1_btag_res == 0 && j2_btag_res == 0 && j3_btag_res == 0) ) 
		    {
		       h_bkg[j]->Fill(1,weight);
		    }		  
		  else if( ((j1_btag_res == 2) && j2_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j2_btag_res == 2) && j1_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j3_btag_res == 2) && j1_btag_res == 0 && j2_btag_res == 0 && b_btag_res == 0) ||
		      ((b_btag_res == 2) && j1_btag_res == 0 && j2_btag_res == 0 && j3_btag_res == 0) ) 
		    {
		       h_bkg[j]->Fill(2,weight);
		       h_bkg[j]->Fill(1,weight);
		    }		  
		  else if( ((j1_btag_res == 3) && j2_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j2_btag_res == 3) && j1_btag_res == 0 && j3_btag_res == 0 && b_btag_res == 0) ||
		      ((j3_btag_res == 3) && j1_btag_res == 0 && j2_btag_res == 0 && b_btag_res == 0) ||
		      ((b_btag_res == 3) && j1_btag_res == 0 && j2_btag_res == 0 && j3_btag_res == 0) ) 
		    {
		       h_bkg[j]->Fill(3,weight);
		       h_bkg[j]->Fill(2,weight);
		       h_bkg[j]->Fill(1,weight);
		    }
		  else h_bkg[j]->Fill(0,weight);
	       }	     
	     else if( var[j] == "met" )
	       {
		  h_bkg[j]->Fill(met,weight);
	       }	     
	  }	
     }   
   
   for(int i=0;i<nvar;i++)
     {
	TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,500);
	
	TPad *c1_1;
	c1->Range(0,0,1,1);
	c1_1 = new TPad("c1_1","main",0.01,0.35,0.99,0.99);
	c1_1->Draw();
	c1_1->cd();
	
	gStyle->SetHistTopMargin(0);
	
	h_sig[i]->Scale(22.2);
	h_bkg[i]->Scale(22.2);
	
	Int_t nbins_sig = h_sig[i]->GetXaxis()->GetNbins();
	Int_t nbins_bkg = h_bkg[i]->GetXaxis()->GetNbins();
	
	Int_t xmin_sig = h_sig[i]->GetXaxis()->GetXmin();
	Int_t xmax_sig = h_sig[i]->GetXaxis()->GetXmax();
	Int_t xmin_bkg = h_bkg[i]->GetXaxis()->GetXmin();
	Int_t xmax_bkg = h_bkg[i]->GetXaxis()->GetXmax();
	
	TH1D *h_sig_eff_1d = new TH1D("h_sig_eff_1d","h_sig_eff_1d",nbins_sig,xmin_sig,xmax_sig);
	TH1D *h_bkg_eff_1d = new TH1D("h_bkg_eff_1d","h_bkg_eff_1d",nbins_sig,xmin_sig,xmax_sig);
	h_sig_eff_1d->Sumw2();
	h_bkg_eff_1d->Sumw2();
	TH1D *h_1d = new TH1D("h_1d","h_1d",nbins_sig,xmin_sig,xmax_sig);
	h_1d->Sumw2();
	if( var[i] == "met" ) h_1d->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
	else if( var[i] == "b_btag" ) 
	  {
	     h_sig_eff_1d->GetXaxis()->SetBinLabel(1,"");
	     h_sig_eff_1d->GetXaxis()->SetBinLabel(2,"");
	     h_sig_eff_1d->GetXaxis()->SetBinLabel(3,"");

	     h_1d->GetXaxis()->SetBinLabel(1,"CSVL");
	     h_1d->GetXaxis()->SetBinLabel(2,"CSVM");
	     h_1d->GetXaxis()->SetBinLabel(3,"CSVT");
	  }	
	
	Double_t sig_int_err = 0.;
	Double_t sig_int = h_sig[i]->IntegralAndError(0,nbins_sig+1,sig_int_err);
	Double_t bkg_int_err = 0.;
	Double_t bkg_int = h_bkg[i]->IntegralAndError(0,nbins_bkg+1,bkg_int_err);
	
	Double_t sig_c[1000], bkg_c[1000], cut_v, 
	  q_v, q_v_err, sig_eff[1000], bkg_eff[1000], 
	  sig_c_err[1000], bkg_c_err[1000];
	
	for(Int_t ib=0;ib<1000;ib++)
	  {	     
	     sig_c[ib] = 0.;
	     sig_eff[ib] = 0.;
	     bkg_c[ib] = 0.;
	     bkg_eff[ib] = 0.;
	  }	
	
	for(Int_t ib=1;ib<nbins_sig+1;ib++)
	  {
	     Double_t err = pow(10.,-10.);
	     if( var[i] == "b_bjet" )
	       bkg_c[ib-1] = h_bkg[i]->IntegralAndError(ib,ib,err);
	     else if( var[i] != "met" )
	       bkg_c[ib-1] = h_bkg[i]->IntegralAndError(ib,nbins_sig,err);
	     else 
	       bkg_c[ib-1] = h_bkg[i]->IntegralAndError(1,ib,err);
	     bkg_eff[ib-1] = fabs(bkg_c[ib-1])/bkg_int;
	     
	     Double_t n1 = bkg_c[ib-1];
	     Double_t bkg_eff_err = 0.;
	     bkg_eff_err = errfMC(n1,err,bkg_int,bkg_int_err);
	     
	     if( bkg_eff_err == 0 ) bkg_eff_err = pow(10.,-10.);
	     h_bkg_eff_1d->SetBinContent(ib,bkg_eff[ib-1]);
	     h_bkg_eff_1d->SetBinError(ib,bkg_eff_err);
	     
	     Double_t err2 = pow(10.,-10.);
	     cut_v = h_sig[i]->GetBinLowEdge(ib);
	     if( var[i] == "b_bjet" )
	       sig_c[ib-1] = h_sig[i]->IntegralAndError(ib,ib,err2);
	     else if( var[i] != "met" )
	       sig_c[ib-1] = h_sig[i]->IntegralAndError(ib,nbins_sig,err2);
	     else 
	       sig_c[ib-1] = h_sig[i]->IntegralAndError(1,ib,err2);
	     
	     sig_eff[ib-1] = sig_c[ib-1]/sig_int;
	     
	     Double_t n1_2 = sig_c[ib-1];
	     if( (sig_c[ib-1] + fabs(bkg_c[ib-1])) > 0. )
	       {		  
		  Double_t s = n1_2;
		  Double_t b = n1;
		  q_v = s/TMath::Sqrt(s+fabs(b));
		  q_v_err = errfMCSig(s,err2,fabs(b),err);
	       }	     
	     else
	       {		  
		  q_v = 0.;
		  q_v_err = pow(10.,-10.);
	       }	     
		  
	     if( q_v_err == 0 ) q_v_err = pow(10.,-10.);
	     h_1d->SetBinContent(ib,q_v);
	     h_1d->SetBinError(ib,q_v_err);
	     h_sig_eff_1d->SetBinContent(ib,sig_eff[ib-1]);
	     Double_t sig_eff_err = pow(10.,-10.);	     
	     Double_t cor = errfMC(n1_2,err2,sig_int,sig_int_err);
	     
	     if( cor < 0 )
	       sig_eff_err = pow(10.,-10.);
	     else
	       sig_eff_err = cor;
	     if( sig_eff_err == 0. ) sig_eff_err = pow(10.,-10.);
	     h_sig_eff_1d->SetBinError(ib,sig_eff_err);
	  }

	h_1d->GetYaxis()->SetTitle("S/#sqrt{S+B}");
	h_sig_eff_1d->SetMarkerStyle(20);
	h_sig_eff_1d->SetMarkerColor(kAzure);
	h_sig_eff_1d->SetLineColor(kAzure);
	h_1d->SetMarkerColor(kAzure);
	h_1d->SetLineColor(kAzure);
	
	h_bkg_eff_1d->SetMarkerColor(kBlack);
	h_bkg_eff_1d->SetMarkerStyle(22);
	h_bkg_eff_1d->SetLineColor(kBlack);
	
	TLegend *leg = new TLegend(0.68,0.92,0.90,0.72);
	leg->SetFillColor(253);
	leg->SetBorderSize(1);
	
	TString leg_sb = "S/#sqrt{S+B}";
	TString leg_bkg = "MC background";
	
	h_sig_eff_1d->GetXaxis()->SetTitle("b-tag");
	h_sig_eff_1d->GetYaxis()->SetTitle("Efficiency");
	h_sig_eff_1d->Draw("e1p");
	h_sig_eff_1d->GetYaxis()->SetRangeUser(-0.05,1.05);
	leg->AddEntry(h_sig_eff_1d,"Signal","lp");
	
	h_bkg_eff_1d->Draw("e1p same");
	leg->AddEntry(h_bkg_eff_1d,"Background","lp");
	leg->Draw();
	
//	TLine *l=new TLine(cut,c1->GetUymin()-0.05,cut,c1->GetUymax()+0.05);
//	l->SetLineStyle(2);
//	l->SetLineWidth(2);
//	l->Draw("same");
	
	doublepl(c1,h_1d);

	std::string picname = "pics/"+var[i]+".eps";
	c1->Print(picname.c_str());
	c1->Clear();
	
	delete c1;
	delete h_sig_eff_1d;
	delete h_bkg_eff_1d;
	delete h_1d;
     }   
   
   gApplication->Terminate();
}

double errfMC(double v1,double ve1,double v2,double ve2)
{
   if( v2 == 0 ) return -666;
   
   double err = pow(v2-v1,2)*ve1*ve1/pow(v2,4) +
     v1*v1*(ve2*ve2-ve1*ve1)/pow(v2,4);
   
   err = sqrt(err);
   
   return err;
}

double errfMCSig(double v1,double ve1,double v2,double ve2)
{
   if( v2 == 0 ) return -666;
   
   double err = pow(v1+2*v2,2)*ve1*ve1/pow(v1+v2,3)/4. +
     v1*v1*ve2*ve2/pow(v1+v2,3)/4.;
   
   err = sqrt(err);
   
   return err;
}
