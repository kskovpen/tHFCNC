void plotTest(std::string fname)
{
   int wrmass, nrmass, npe, random;
   double med, p2, p1, m1, m2, obsl;

   const int N = 10000;
   int wrmassA[N], nrmassA[N], npeA[N], randomA[N];
   double medA[N], p2A[N], p1A[N], m1A[N], m2A[N], obslA[N];
   
   std::ifstream f(fname.c_str());

   int i=0;
   while (!f.eof())
     {	
	f >> wrmass >> nrmass >> npe >> random >> med >> p2 >> p1 >> m1 >> m2 >> obsl;
	wrmassA[i] = wrmass;
	nrmassA[i] = nrmass;
	npeA[i] = npe;
	randomA[i] = random;
	medA[i] = med;
	p2A[i] = p2;
	p1A[i] = p1;
	m1A[i] = m1;
	m2A[i] = m2;
	obslA[i] = obsl;
	i++;
     }
   int np = i-1;

   double av = 0.;
   for(int j=0;j<np;j++)
     {
//	av += obslA[j]/double(np);
	av += medA[j]/double(np);
     }   

   double sum = 0.;
   for(int j=0;j<np;j++)
     {
//	sum += pow(obslA[j]-av,2.)/(double(np)-1);
	sum += pow(medA[j]-av,2.)/(double(np)-1);
     }   
   sum = sqrt(sum);

   std::cout << "sig/A = " << sum/av << std::endl;
   
   f.close();
   
   gApplication->Terminate();
}
