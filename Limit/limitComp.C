TStyle* PlotStyle();
TStyle* PlotStyleCMS();
void SetPlotStyle();

void limitComp()
{
   gROOT->SetBatch(1);

   SetPlotStyle();

   const int nChan = 9;

   std::string coup = "Hut";
   
   float xsec = 50.82;
   if( coup == "Hct" ) xsec = 38.88;
   
   float xbins[nChan];
   for(int j=0;j<=nChan;j++)
     {
	xbins[j] = j;
     }

   // Hut 2D
   float med_Hut[nChan] = {0.2471,0.2021,0.0786,0.0679,0.0483,0.0366,0.0220,0.0142,0.0903};
   float s1p_Hut[nChan] = {0.3387,0.2771,0.1090,0.0947,0.0665,0.0486,0.0307,0.0200,0.1289};
   float s1m_Hut[nChan] = {0.1801,0.1487,0.0574,0.0493,0.0357,0.0280,0.0157,0.0104,0.0635};
   float s2p_Hut[nChan] = {0.4434,0.3654,0.1441,0.1256,0.0875,0.0628,0.0412,0.0269,0.1761};
   float s2m_Hut[nChan] = {0.1385,0.1133,0.0433,0.0374,0.0276,0.0220,0.0113,0.0075,0.0469};

   // HutST
   float med_HutST[nChan] = {0.2646,0.2236,0.0825,0.0845,0.0483,0.0376,0.0171,0.0161,0.0967};
   float s1p_HutST[nChan] = {0.3628,0.3083,0.1144,0.1138,0.0665,0.0502,0.0255,0.0230,0.1410};
   float s1m_HutST[nChan] = {0.1922,0.1637,0.0600,0.0640,0.0352,0.0274,0.0113,0.0117,0.0671};
   float s2p_HutST[nChan] = {0.4784,0.4085,0.1512,0.1479,0.0882,0.0655,0.0359,0.0308,0.1966};
   float s2m_HutST[nChan] = {0.1473,0.1240,0.0451,0.0505,0.0268,0.0209,0.0083,0.0083,0.0487};

   // HutTT
   float med_HutTT[nChan] = {0.2627,0.2100,0.0903,0.0796,0.0571,0.0288,0.0210,0.0142,0.1001};
   float s1p_HutTT[nChan] = {0.3601,0.2870,0.1253,0.1104,0.0785,0.0403,0.0294,0.0191,0.1412};
   float s1m_HutTT[nChan] = {0.1932,0.1547,0.0659,0.0581,0.0416,0.0211,0.0146,0.0096,0.0714};
   float s2p_HutTT[nChan] = {0.4715,0.3762,0.1655,0.1458,0.1034,0.0532,0.0404,0.0262,0.1916};
   float s2m_HutTT[nChan] = {0.1473,0.1181,0.0498,0.0438,0.0317,0.0158,0.0108,0.0075,0.0536};
   
   // Hct 2D
   float med_Hct[nChan] = {0.3271,0.2646,0.1099,0.1323,0.0728,0.0620,0.0298,0.0190,0.0316};
   float s1p_Hct[nChan] = {0.4484,0.3606,0.1506,0.1666,0.0962,0.0783,0.0417,0.0260,0.0449};
   float s1m_Hct[nChan] = {0.2407,0.1938,0.0799,0.1078,0.0554,0.0472,0.0218,0.0139,0.0225};
   float s2p_Hct[nChan] = {0.5914,0.4734,0.1986,0.2062,0.1241,0.0968,0.0566,0.0345,0.0613};
   float s2m_Hct[nChan] = {0.1834,0.1483,0.0614,0.0915,0.0443,0.0363,0.0163,0.0104,0.0163};

   // HctST
   float med_HctST[nChan] = {0.3408,0.2900,0.1216,0.1499,0.0776,0.0669,0.0259,0.0220,0.0462};
   float s1p_HctST[nChan] = {0.4672,0.3976,0.1676,0.1911,0.1033,0.0864,0.0378,0.0300,0.0650};
   float s1m_HctST[nChan] = {0.2507,0.2140,0.0885,0.1203,0.0582,0.0517,0.0189,0.0161,0.0333};
   float s2p_HctST[nChan] = {0.6117,0.5243,0.2205,0.2397,0.1329,0.1079,0.0509,0.0401,0.0884};
   float s2m_HctST[nChan] = {0.1910,0.1637,0.0679,0.1007,0.0458,0.0374,0.0142,0.0120,0.0249};

   // HctTT
   float med_HctTT[nChan] = {0.3135,0.2471,0.1040,0.1245,0.0747,0.0591,0.0259,0.0171,0.0285};
   float s1p_HctTT[nChan] = {0.4297,0.3367,0.1426,0.1568,0.0970,0.0756,0.0370,0.0234,0.0408};
   float s1m_HctTT[nChan] = {0.2292,0.1818,0.0757,0.1014,0.0582,0.0452,0.0182,0.0118,0.0203};
   float s2p_HctTT[nChan] = {0.5667,0.4452,0.1880,0.1940,0.1240,0.0931,0.0504,0.0319,0.0555};
   float s2m_HctTT[nChan] = {0.1751,0.1385,0.0581,0.0861,0.0476,0.0337,0.0142,0.0093,0.0147};
   
   TH1F *hLimitXsec2D[nChan];
   TH1F *hLimitXsecs1p2D[nChan];
   TH1F *hLimitXsecs1m2D[nChan];
   TH1F *hLimitXsecs2p2D[nChan];
   TH1F *hLimitXsecs2m2D[nChan];

   TH1F *hLimitXsecST[nChan];
   TH1F *hLimitXsecs1pST[nChan];
   TH1F *hLimitXsecs1mST[nChan];
   TH1F *hLimitXsecs2pST[nChan];
   TH1F *hLimitXsecs2mST[nChan];

   TH1F *hLimitXsecTT[nChan];
   TH1F *hLimitXsecs1pTT[nChan];
   TH1F *hLimitXsecs1mTT[nChan];
   TH1F *hLimitXsecs2pTT[nChan];
   TH1F *hLimitXsecs2mTT[nChan];
   
   for(int i=0;i<nChan;i++)
     {	
	std::string nameLimitXsec2D = "hLimitXsec"+std::string(Form("2D-%d",i));
	std::string nameLimitXsecs1p2D = "hLimitXsecs1p"+std::string(Form("2D-%d",i));
	std::string nameLimitXsecs1m2D = "hLimitXsecs1m"+std::string(Form("2D-%d",i));
	std::string nameLimitXsecs2p2D = "hLimitXsecs2p"+std::string(Form("2D-%d",i));
	std::string nameLimitXsecs2m2D = "hLimitXsecs2m"+std::string(Form("2D-%d",i));

	std::string nameLimitXsecST = "hLimitXsec"+std::string(Form("ST-%d",i));
	std::string nameLimitXsecs1pST = "hLimitXsecs1p"+std::string(Form("ST-%d",i));
	std::string nameLimitXsecs1mST = "hLimitXsecs1m"+std::string(Form("ST-%d",i));
	std::string nameLimitXsecs2pST = "hLimitXsecs2p"+std::string(Form("ST-%d",i));
	std::string nameLimitXsecs2mST = "hLimitXsecs2m"+std::string(Form("ST-%d",i));

	std::string nameLimitXsecTT = "hLimitXsec"+std::string(Form("TT-%d",i));
	std::string nameLimitXsecs1pTT = "hLimitXsecs1p"+std::string(Form("TT-%d",i));
	std::string nameLimitXsecs1mTT = "hLimitXsecs1m"+std::string(Form("TT-%d",i));
	std::string nameLimitXsecs2pTT = "hLimitXsecs2p"+std::string(Form("TT-%d",i));
	std::string nameLimitXsecs2mTT = "hLimitXsecs2m"+std::string(Form("TT-%d",i));
	
	hLimitXsec2D[i] = new TH1F(nameLimitXsec2D.c_str(),nameLimitXsec2D.c_str(),nChan,xbins);
	hLimitXsecs1p2D[i] = new TH1F(nameLimitXsecs1p2D.c_str(),nameLimitXsecs1p2D.c_str(),nChan,xbins);
	hLimitXsecs1m2D[i] = new TH1F(nameLimitXsecs1m2D.c_str(),nameLimitXsecs1m2D.c_str(),nChan,xbins);
	hLimitXsecs2p2D[i] = new TH1F(nameLimitXsecs2p2D.c_str(),nameLimitXsecs2p2D.c_str(),nChan,xbins);
        hLimitXsecs2m2D[i] = new TH1F(nameLimitXsecs2m2D.c_str(),nameLimitXsecs2m2D.c_str(),nChan,xbins);

	hLimitXsecST[i] = new TH1F(nameLimitXsecST.c_str(),nameLimitXsecST.c_str(),nChan,xbins);
	hLimitXsecs1pST[i] = new TH1F(nameLimitXsecs1pST.c_str(),nameLimitXsecs1pST.c_str(),nChan,xbins);
	hLimitXsecs1mST[i] = new TH1F(nameLimitXsecs1mST.c_str(),nameLimitXsecs1mST.c_str(),nChan,xbins);
	hLimitXsecs2pST[i] = new TH1F(nameLimitXsecs2pST.c_str(),nameLimitXsecs2pST.c_str(),nChan,xbins);
        hLimitXsecs2mST[i] = new TH1F(nameLimitXsecs2mST.c_str(),nameLimitXsecs2mST.c_str(),nChan,xbins);

	hLimitXsecTT[i] = new TH1F(nameLimitXsecTT.c_str(),nameLimitXsecTT.c_str(),nChan,xbins);
	hLimitXsecs1pTT[i] = new TH1F(nameLimitXsecs1pTT.c_str(),nameLimitXsecs1pTT.c_str(),nChan,xbins);
	hLimitXsecs1mTT[i] = new TH1F(nameLimitXsecs1mTT.c_str(),nameLimitXsecs1mTT.c_str(),nChan,xbins);
	hLimitXsecs2pTT[i] = new TH1F(nameLimitXsecs2pTT.c_str(),nameLimitXsecs2pTT.c_str(),nChan,xbins);
        hLimitXsecs2mTT[i] = new TH1F(nameLimitXsecs2mTT.c_str(),nameLimitXsecs2mTT.c_str(),nChan,xbins);
     }
   
   for(int ib=0;ib<nChan;ib++)
     {          	
	if( coup == "Hut" )
	  {	     
	     hLimitXsec2D[ib]->SetBinContent(ib+1,med_Hut[ib]*xsec);
	     hLimitXsecs1p2D[ib]->SetBinContent(ib+1,s1p_Hut[ib]*xsec);
	     hLimitXsecs1m2D[ib]->SetBinContent(ib+1,s1m_Hut[ib]*xsec);
	     hLimitXsecs2p2D[ib]->SetBinContent(ib+1,s2p_Hut[ib]*xsec);
	     hLimitXsecs2m2D[ib]->SetBinContent(ib+1,s2m_Hut[ib]*xsec);

	     hLimitXsecST[ib]->SetBinContent(ib+1,med_HutST[ib]*xsec);
	     hLimitXsecs1pST[ib]->SetBinContent(ib+1,s1p_HutST[ib]*xsec);
	     hLimitXsecs1mST[ib]->SetBinContent(ib+1,s1m_HutST[ib]*xsec);
	     hLimitXsecs2pST[ib]->SetBinContent(ib+1,s2p_HutST[ib]*xsec);
	     hLimitXsecs2mST[ib]->SetBinContent(ib+1,s2m_HutST[ib]*xsec);

	     hLimitXsecTT[ib]->SetBinContent(ib+1,med_HutTT[ib]*xsec);
	     hLimitXsecs1pTT[ib]->SetBinContent(ib+1,s1p_HutTT[ib]*xsec);
	     hLimitXsecs1mTT[ib]->SetBinContent(ib+1,s1m_HutTT[ib]*xsec);
	     hLimitXsecs2pTT[ib]->SetBinContent(ib+1,s2p_HutTT[ib]*xsec);
	     hLimitXsecs2mTT[ib]->SetBinContent(ib+1,s2m_HutTT[ib]*xsec);
	  }
	else
	  {
	     hLimitXsec2D[ib]->SetBinContent(ib+1,med_Hct[ib]*xsec);
	     hLimitXsecs1p2D[ib]->SetBinContent(ib+1,s1p_Hct[ib]*xsec);
	     hLimitXsecs1m2D[ib]->SetBinContent(ib+1,s1m_Hct[ib]*xsec);
	     hLimitXsecs2p2D[ib]->SetBinContent(ib+1,s2p_Hct[ib]*xsec);
	     hLimitXsecs2m2D[ib]->SetBinContent(ib+1,s2m_Hct[ib]*xsec);

	     hLimitXsecST[ib]->SetBinContent(ib+1,med_HctST[ib]*xsec);
	     hLimitXsecs1pST[ib]->SetBinContent(ib+1,s1p_HctST[ib]*xsec);
	     hLimitXsecs1mST[ib]->SetBinContent(ib+1,s1m_HctST[ib]*xsec);
	     hLimitXsecs2pST[ib]->SetBinContent(ib+1,s2p_HctST[ib]*xsec);
	     hLimitXsecs2mST[ib]->SetBinContent(ib+1,s2m_HctST[ib]*xsec);

	     hLimitXsecTT[ib]->SetBinContent(ib+1,med_HctTT[ib]*xsec);
	     hLimitXsecs1pTT[ib]->SetBinContent(ib+1,s1p_HctTT[ib]*xsec);
	     hLimitXsecs1mTT[ib]->SetBinContent(ib+1,s1m_HctTT[ib]*xsec);
	     hLimitXsecs2pTT[ib]->SetBinContent(ib+1,s2p_HctTT[ib]*xsec);
	     hLimitXsecs2mTT[ib]->SetBinContent(ib+1,s2m_HctTT[ib]*xsec);	     
	  }	
     }   
   
   TCanvas *c1 = new TCanvas("c1","c1",0,0,700,500);

   TLine *line2D[nChan], *lineST[nChan], *lineTT[nChan];
   
   const int np = 5;
   
   double xp_s1_2D[nChan][np];
   double yp_s1_2D[nChan][np];
   double xp_s2_2D[nChan][np];
   double yp_s2_2D[nChan][np];

   double xp_s1_ST[nChan][np];
   double yp_s1_ST[nChan][np];
   double xp_s2_ST[nChan][np];
   double yp_s2_ST[nChan][np];

   double xp_s1_TT[nChan][np];
   double yp_s1_TT[nChan][np];
   double xp_s2_TT[nChan][np];
   double yp_s2_TT[nChan][np];
   
   for(int i=0;i<nChan;i++)
     {	
	xp_s1_2D[i][0] = hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_2D[i][0] = hLimitXsecs1m2D[i]->GetBinContent(i+1);
	xp_s1_2D[i][1] = hLimitXsec2D[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s1_2D[i][1] = hLimitXsecs1m2D[i]->GetBinContent(i+1);
	xp_s1_2D[i][2] = hLimitXsec2D[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s1_2D[i][2] = hLimitXsecs1p2D[i]->GetBinContent(i+1);
	xp_s1_2D[i][3] = hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_2D[i][3] = hLimitXsecs1p2D[i]->GetBinContent(i+1);
	xp_s1_2D[i][4] = hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_2D[i][4] = hLimitXsecs1m2D[i]->GetBinContent(i+1);

	xp_s2_2D[i][0] = hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_2D[i][0] = hLimitXsecs2m2D[i]->GetBinContent(i+1);
	xp_s2_2D[i][1] = hLimitXsec2D[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s2_2D[i][1] = hLimitXsecs2m2D[i]->GetBinContent(i+1);
	xp_s2_2D[i][2] = hLimitXsec2D[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s2_2D[i][2] = hLimitXsecs2p2D[i]->GetBinContent(i+1);
	xp_s2_2D[i][3] = hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_2D[i][3] = hLimitXsecs2p2D[i]->GetBinContent(i+1);
	xp_s2_2D[i][4] = hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_2D[i][4] = hLimitXsecs2m2D[i]->GetBinContent(i+1);
	
	line2D[i] = new TLine(hLimitXsec2D[i]->GetXaxis()->GetBinLowEdge(i+1),
			      hLimitXsec2D[i]->GetBinContent(i+1),
			      hLimitXsec2D[i]->GetXaxis()->GetBinUpEdge(i+1),
			      hLimitXsec2D[i]->GetBinContent(i+1));
	
	line2D[i]->SetLineStyle(2);
	line2D[i]->SetLineWidth(2);

	xp_s1_ST[i][0] = hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_ST[i][0] = hLimitXsecs1mST[i]->GetBinContent(i+1);
	xp_s1_ST[i][1] = hLimitXsecST[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s1_ST[i][1] = hLimitXsecs1mST[i]->GetBinContent(i+1);
	xp_s1_ST[i][2] = hLimitXsecST[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s1_ST[i][2] = hLimitXsecs1pST[i]->GetBinContent(i+1);
	xp_s1_ST[i][3] = hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_ST[i][3] = hLimitXsecs1pST[i]->GetBinContent(i+1);
	xp_s1_ST[i][4] = hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_ST[i][4] = hLimitXsecs1mST[i]->GetBinContent(i+1);

	xp_s2_ST[i][0] = hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_ST[i][0] = hLimitXsecs2mST[i]->GetBinContent(i+1);
	xp_s2_ST[i][1] = hLimitXsecST[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s2_ST[i][1] = hLimitXsecs2mST[i]->GetBinContent(i+1);
	xp_s2_ST[i][2] = hLimitXsecST[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s2_ST[i][2] = hLimitXsecs2pST[i]->GetBinContent(i+1);
	xp_s2_ST[i][3] = hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_ST[i][3] = hLimitXsecs2pST[i]->GetBinContent(i+1);
	xp_s2_ST[i][4] = hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_ST[i][4] = hLimitXsecs2mST[i]->GetBinContent(i+1);
	
	lineST[i] = new TLine(hLimitXsecST[i]->GetXaxis()->GetBinLowEdge(i+1),
			      hLimitXsecST[i]->GetBinContent(i+1),
			      hLimitXsecST[i]->GetXaxis()->GetBinUpEdge(i+1),
			      hLimitXsecST[i]->GetBinContent(i+1));
	
	lineST[i]->SetLineColor(kBlue);
	lineST[i]->SetLineStyle(1);
	lineST[i]->SetLineWidth(2);

	xp_s1_TT[i][0] = hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_TT[i][0] = hLimitXsecs1mTT[i]->GetBinContent(i+1);
	xp_s1_TT[i][1] = hLimitXsecTT[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s1_TT[i][1] = hLimitXsecs1mTT[i]->GetBinContent(i+1);
	xp_s1_TT[i][2] = hLimitXsecTT[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s1_TT[i][2] = hLimitXsecs1pTT[i]->GetBinContent(i+1);
	xp_s1_TT[i][3] = hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_TT[i][3] = hLimitXsecs1pTT[i]->GetBinContent(i+1);
	xp_s1_TT[i][4] = hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s1_TT[i][4] = hLimitXsecs1mTT[i]->GetBinContent(i+1);

	xp_s2_TT[i][0] = hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_TT[i][0] = hLimitXsecs2mTT[i]->GetBinContent(i+1);
	xp_s2_TT[i][1] = hLimitXsecTT[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s2_TT[i][1] = hLimitXsecs2mTT[i]->GetBinContent(i+1);
	xp_s2_TT[i][2] = hLimitXsecTT[i]->GetXaxis()->GetBinUpEdge(i+1);
	yp_s2_TT[i][2] = hLimitXsecs2pTT[i]->GetBinContent(i+1);
	xp_s2_TT[i][3] = hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_TT[i][3] = hLimitXsecs2pTT[i]->GetBinContent(i+1);
	xp_s2_TT[i][4] = hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1);
	yp_s2_TT[i][4] = hLimitXsecs2mTT[i]->GetBinContent(i+1);
	
	lineTT[i] = new TLine(hLimitXsecTT[i]->GetXaxis()->GetBinLowEdge(i+1),
			      hLimitXsecTT[i]->GetBinContent(i+1),
			      hLimitXsecTT[i]->GetXaxis()->GetBinUpEdge(i+1),
			      hLimitXsecTT[i]->GetBinContent(i+1));
	
	lineTT[i]->SetLineColor(kRed);
	lineTT[i]->SetLineStyle(1);
	lineTT[i]->SetLineWidth(2);
     }   

   TPolyLine *s1_2D[nChan];
   TPolyLine *s2_2D[nChan];

   TPolyLine *s1_ST[nChan];
   TPolyLine *s2_ST[nChan];

   TPolyLine *s1_TT[nChan];
   TPolyLine *s2_TT[nChan];
   
   hLimitXsec2D[0]->Reset();
   hLimitXsec2D[0]->Draw("");
   
   for(int i=0;i<nChan;i++)
     {	
	s1_2D[i] = new TPolyLine(np,xp_s1_2D[i],yp_s1_2D[i]);
	s1_2D[i]->SetFillColor(kGreen);
	s2_2D[i] = new TPolyLine(np,xp_s2_2D[i],yp_s2_2D[i]);
	s2_2D[i]->SetFillColor(kYellow);
	s2_2D[i]->Draw("fSAME");
	s1_2D[i]->Draw("fSAME");	
	line2D[i]->Draw("same");
	
	s1_ST[i] = new TPolyLine(np,xp_s1_ST[i],yp_s1_ST[i]);
	s2_ST[i] = new TPolyLine(np,xp_s2_ST[i],yp_s2_ST[i]);
	s1_TT[i] = new TPolyLine(np,xp_s1_TT[i],yp_s1_TT[i]);
	s2_TT[i] = new TPolyLine(np,xp_s2_TT[i],yp_s2_TT[i]);
	lineST[i]->Draw("same");
	lineTT[i]->Draw("same");
     }   
	
   hLimitXsec2D[0]->GetYaxis()->SetTitle("#sigma (95\% CL) [pb]");
   hLimitXsec2D[0]->GetXaxis()->SetTitle("");
   hLimitXsec2D[0]->GetYaxis()->SetRangeUser(0.1,200.);
   
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(1,"b0j3");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(2,"b0j4");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(3,"b1j3");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(4,"b1j4");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(5,"b2j3");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(6,"b2j4");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(7,"b3j3");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(8,"b3j4");
   hLimitXsec2D[0]->GetXaxis()->SetBinLabel(9,"b4j4");
   
   TLegend *leg;
   leg = new TLegend(0.75,0.90,0.90,0.70);
   leg->SetFillColor(253);
   leg->SetBorderSize(0);
   
   leg->AddEntry(line2D[0],"2D Expected","l");
   leg->AddEntry(s1_2D[0],"2D 68\%","f");
   leg->AddEntry(s2_2D[0],"2D 95\%","f");
   leg->AddEntry(lineST[0],"ST Expected","l");
   leg->AddEntry(lineTT[0],"TT Expected","l");
   
   c1->RedrawAxis("g");
   c1->SetLogy(1);
   
   leg->Draw();
   
   TLatex *tex = new TLatex(0.1969,0.906825,"CMS");
   tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.07475);
   tex->SetLineWidth(2);
   tex->Draw();

   TLatex *tex2 = new TLatex(0.1969,0.817125,"Preliminary");
   tex2->SetNDC();
   tex2->SetTextAlign(13);
   tex2->SetTextFont(52);
   tex2->SetTextSize(0.05681);
   tex2->SetLineWidth(2);
   tex2->Draw();

   TLatex *text1 = new TLatex(0.98,0.95125,"#sqrt{s} = 13 TeV");
   text1->SetNDC();
   text1->SetTextAlign(31);
   text1->SetTextFont(42);
   text1->SetTextSize(0.04875);
   text1->SetLineWidth(2);
   text1->Draw();
   
   std::string picname = "pics/LimitComp.eps";
   c1->Print(picname.c_str());
   c1->Clear();
   
   delete c1;
   delete leg;
     
   gApplication->Terminate();
}

void SetPlotStyle()
{
   TStyle *styleCurrent = gROOT->GetStyle("PLOT");
   if( !styleCurrent )
     {
	static TStyle* plotStyle = 0;
	if( plotStyle == 0 ) plotStyle = PlotStyleCMS();
	gROOT->SetStyle("PLOT");
	gROOT->ForceStyle();
     }
}

TStyle* PlotStyleCMS()
{
   TStyle *plotStyle = new TStyle("PLOT","Plot style CMS");

   plotStyle->SetOptTitle(0);
   plotStyle->SetOptStat(0);
   plotStyle->SetOptFit(0);
   
   plotStyle->SetPaperSize(20.,26.);

   plotStyle->SetEndErrorSize(2);
//   plotStyle->SetErrorX(0.);
   
   plotStyle->SetFrameBorderMode(0);
   plotStyle->SetFrameFillColor(0);
   plotStyle->SetFrameFillStyle(0);
   plotStyle->SetCanvasBorderMode(0);
   plotStyle->SetFillColor(0);
   plotStyle->SetCanvasColor(0);
   plotStyle->SetCanvasBorderSize(2);
   
   plotStyle->SetPadBorderMode(0);
   plotStyle->SetPadColor(0);
   plotStyle->SetPadGridX(false);
   plotStyle->SetPadGridY(false);
   plotStyle->SetGridColor(0);
   plotStyle->SetGridStyle(3);
   plotStyle->SetGridWidth(1);
   
//   plotStyle->SetCanvasDefH(600);
//   plotStyle->SetCanvasDefW(600);
   plotStyle->SetCanvasDefX(0);
   plotStyle->SetCanvasDefY(0);
     
   plotStyle->SetHistLineColor(1);
   plotStyle->SetHistLineStyle(0);
   plotStyle->SetHistLineWidth(1);
   
   plotStyle->SetPadTickX(1);
   plotStyle->SetPadTickY(1);
   
   plotStyle->SetPadLeftMargin(0.16);
   plotStyle->SetPadRightMargin(0.02);
   plotStyle->SetPadTopMargin(0.06);
   plotStyle->SetPadBottomMargin(0.13);

   plotStyle->SetLabelFont(42,"x");
   plotStyle->SetTitleFont(42,"x");
   plotStyle->SetLabelFont(42,"y");
   plotStyle->SetTitleFont(42,"y");
   plotStyle->SetLabelFont(42,"z");
   plotStyle->SetTitleFont(42,"z");

   plotStyle->SetLabelSize(0.05,"x");
   plotStyle->SetTitleSize(0.06,"x");
   plotStyle->SetLabelSize(0.05,"y");
   plotStyle->SetTitleSize(0.06,"y");
   plotStyle->SetLabelSize(0.035,"z");
   plotStyle->SetTitleSize(0.035,"z");

   plotStyle->SetLabelOffset(0.007,"XYZ");
   
   plotStyle->SetNdivisions(510,"XYZ");
   plotStyle->SetStripDecimals(kTRUE);
   plotStyle->SetTickLength(0.03, "XYZ");
   
   plotStyle->SetTitleXOffset(0.9);
   plotStyle->SetTitleYOffset(1.25);

   plotStyle->SetMarkerStyle(20);
   plotStyle->SetMarkerSize(1.2);
   
   return plotStyle;
}

TStyle* PlotStyle()
{
   TStyle *plotStyle = new TStyle("PLOT","Plot style");
   
   // use plain black on white colors
   Int_t icol=0; // WHITE
   plotStyle->SetFrameBorderMode(icol);
   plotStyle->SetFrameFillColor(icol);
   plotStyle->SetCanvasBorderMode(icol);
   plotStyle->SetCanvasColor(icol);
   plotStyle->SetPadBorderMode(icol);
   plotStyle->SetPadColor(icol);
   plotStyle->SetStatColor(icol);
   
   // set the paper & margin sizes
   plotStyle->SetPaperSize(20,26);
   
   // set margin sizes
   plotStyle->SetPadTopMargin(0.05);
   plotStyle->SetPadRightMargin(0.05);
   plotStyle->SetPadBottomMargin(0.16);
   plotStyle->SetPadLeftMargin(0.16);
   
   // set title offsets (for axis label)
   plotStyle->SetTitleXOffset(1.4);
   plotStyle->SetTitleYOffset(1.4);
   
   // use large fonts
   Int_t font=42;
   Double_t tsize=0.05;
   plotStyle->SetTextFont(font);
   
   plotStyle->SetTextSize(tsize);
   plotStyle->SetLabelFont(font,"x");
   plotStyle->SetTitleFont(font,"x");
   plotStyle->SetLabelFont(font,"y");
   plotStyle->SetTitleFont(font,"y");
   plotStyle->SetLabelFont(font,"z");
   plotStyle->SetTitleFont(font,"z");
   
   plotStyle->SetLabelSize(tsize,"x");
   plotStyle->SetTitleSize(tsize,"x");
   plotStyle->SetLabelSize(tsize,"y");
   plotStyle->SetTitleSize(tsize,"y");
   plotStyle->SetLabelSize(tsize,"z");
   plotStyle->SetTitleSize(tsize,"z");
   
   // use bold lines and markers
   plotStyle->SetMarkerStyle(20);
   plotStyle->SetMarkerSize(1.2);
   plotStyle->SetHistLineWidth(2.);
   plotStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
   
   // get rid of X error bars
   // plotStyle->SetErrorX(0.001);
   // get rid of error bar caps
   plotStyle->SetEndErrorSize(0.);
   
   // do not display any of the standard histogram decorations
   plotStyle->SetOptTitle(0);
   //plotStyle->SetOptStat(1111);
   plotStyle->SetOptStat(0);
   //plotStyle->SetOptFit(1111);
   plotStyle->SetOptFit(0);
   
   // put tick marks on top and RHS of plots
   plotStyle->SetPadTickX(1);
   plotStyle->SetPadTickY(1);
   
   return plotStyle;
}
