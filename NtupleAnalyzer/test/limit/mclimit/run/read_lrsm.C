double xsec(double,double,bool,double);

void read_lrsm(TString file,TString cont,double kf)
{
   std::vector<double> arr;
   
   std::ifstream f(file);
   
   double wrmass, nrmass, med, p2, p1, m1, m2, obs, xsc, eff, vis, pval;

   while( ! f.eof() )
     {
	f >> wrmass >> nrmass >> med >> p2 >> p1 >> m1 >> m2 >> obs >> xsc >> eff >> vis >> pval;
	if( f.eof() ) break;
	if( cont == "med" || cont == "nelem" ) arr.push_back(med);
	if( cont == "p1" ) arr.push_back(p1);
	if( cont == "p2" ) arr.push_back(p2);
	if( cont == "m1" ) arr.push_back(m1);
	if( cont == "m2" ) arr.push_back(m2);
	if( cont == "obs" ) arr.push_back(obs);
	if( cont == "xsec" ) arr.push_back(xsc);
	if( cont == "wrmass" ) arr.push_back(wrmass);
	if( cont == "nrmass" ) arr.push_back(nrmass);
	if( cont == "eff" ) arr.push_back(eff);
	if( cont == "vis" ) arr.push_back(vis);
	if( cont == "pval" ) arr.push_back(pval);
     }   
     
   f.close();
   
   std::vector<double>::const_iterator ib = arr.begin();
   std::vector<double>::const_iterator ie = arr.end();
   for(;ib!=ie;++ib)
     {
	if( cont != "nelem" )
	  std::cout << (*ib) << ",";
     }   
   if( cont != "nelem" ) std::cout << std::endl;

   if( cont == "nelem" ) std::cout << arr.size() << std::endl;
   
   gApplication->Terminate();
}
