void get_xsec_lrsm(double wrmass,double nrmass,double kf)
{
   double xsc = 1.;

   xsc = xsec(wrmass,nrmass,kf);

   printf("%.10f", xsc);
   
   gApplication->Terminate();
}

double xsec(double wr, double nr, double k)
{
   double xs = -1.;

   if( wr == 600 && nr == 50 ) xs = 7.33*k;
   if( wr == 600 && nr == 100 ) xs = 7.16*k;
   if( wr == 600 && nr == 300 ) xs = 5.15*k;
   if( wr == 600 && nr == 500 ) xs = 1.20*k;
   if( wr == 800 && nr == 50 ) xs = 2.18*k;
   if( wr == 800 && nr == 100 ) xs = 2.15*k;
   if( wr == 800 && nr == 300 ) xs = 1.83*k;
   if( wr == 800 && nr == 500 ) xs = 1.13*k;
   if( wr == 1000 && nr == 50 ) xs = 0.78*k;
   if( wr == 1000 && nr == 200 ) xs = 0.75*k;
   if( wr == 1000 && nr == 500 ) xs = 0.54*k;
   if( wr == 1000 && nr == 800 ) xs = 0.169*k;
   if( wr == 1200 && nr == 50 ) xs = 0.316*k;
   if( wr == 1200 && nr == 200 ) xs = 0.306*k;
   if( wr == 1200 && nr == 600 ) xs = 0.220*k;
   if( wr == 1200 && nr == 1000 ) xs = 0.0508*k;
   if( wr == 1500 && nr == 50 ) xs = 0.090*k;
   if( wr == 1500 && nr == 300 ) xs = 0.086*k;
   if( wr == 1500 && nr == 800 ) xs = 0.059*k;
   if( wr == 1500 && nr == 1300 ) xs = 0.0099*k;   
   if( wr == 1800 && nr == 50 ) xs = 0.0297*k;
   if( wr == 1800 && nr == 500 ) xs = 0.0237*k;
   if( wr == 1800 && nr == 1000 ) xs = 0.0150*k;
   if( wr == 1800 && nr == 1500 ) xs = 0.0040*k;
   if( wr == 1000 && nr == 100 ) xs = 0.76333*k;
   if( wr == 1200 && nr == 100 ) xs = 0.30600*k;
   if( wr == 1500 && nr == 100 ) xs = 0.09000*k;
   if( wr == 1800 && nr == 100 ) xs = 0.02900*k;
   if( wr == 2100 && nr == 50 ) xs = 0.01033*k;
   if( wr == 2100 && nr == 100 ) xs = 0.01000*k;
   if( wr == 2100 && nr == 600 ) xs = 0.00733*k;
   if( wr == 2100 && nr == 1200 ) xs = 0.00433*k;
   if( wr == 2100 && nr == 1800 ) xs = 0.000833*k;
   if( wr == 2300 && nr == 50 ) xs = 0.00533*k;
   if( wr == 2300 && nr == 100 ) xs = 0.00500*k;
   if( wr == 2300 && nr == 700 ) xs = 0.00333*k;
   if( wr == 2300 && nr == 1400 ) xs = 0.001767*k;
   if( wr == 2300 && nr == 2000 ) xs = 0.000323*k;
   if( wr == 2500 && nr == 50 ) xs = 0.002933*k;
   if( wr == 2500 && nr == 100 ) xs = 0.002767*k;
   if( wr == 2500 && nr == 800 ) xs = 0.001567*k;
   if( wr == 2500 && nr == 1600 ) xs = 0.000733*k;
   if( wr == 2500 && nr == 2200 ) xs = 0.000127*k;
   if( wr == 2700 && nr == 50 ) xs = 0.001466*k;
   if( wr == 2700 && nr == 100 ) xs = 0.001400*k;
   if( wr == 2700 && nr == 800 ) xs = 0.000800*k;
   if( wr == 2700 && nr == 1700 ) xs = 0.000366*k;
   if( wr == 2700 && nr == 2500 ) xs = 0.000063*k;
   if( wr == 2900 && nr == 50 ) xs = 0.000733*k;
   if( wr == 2900 && nr == 100 ) xs = 0.000700*k;
   if( wr == 2900 && nr == 900 ) xs = 0.000400*k;
   if( wr == 2900 && nr == 1800 ) xs = 0.000183*k;
   if( wr == 2900 && nr == 2700 ) xs = 0.000033*k;
   
   return xs;
}
