const int nh = 59;
std::string hname[nh] =
{
   "h_pt_t",
   "h_pt_tb",
   "h_pt_tWl",
   "h_pt_tWnu",
   "h_pt_W",
   "h_pt_H",
   "h_pt_Hb",

   "h_eta_t",
   "h_eta_tb",
   "h_eta_tWl",
   "h_eta_tWnu",
   "h_eta_W",
   "h_eta_H",
   "h_eta_Hb",

   "h_phi_t",
   "h_phi_tb",
   "h_phi_tWl",
   "h_phi_tWnu",
   "h_phi_W",
   "h_phi_H",
   "h_phi_Hb",
   
   "h_dr_tb_tWl",
   "h_dr_tb_tWnu",
   "h_dr_Hb_tb",
   "h_dr_tb_W",
   "h_dr_H_tb",
   "h_dr_t_H",
   "h_dr_t_Hb",
   "h_dr_H_Hb",
   "h_dr_H_W",
   "h_dr_H_tWl",
   "h_dr_H_tWnu",
   "h_dr_Hb1_Hb2",
   "h_dr_Hb_tWl",
   "h_dr_Hb_tWnu",
   "h_dr_Hb_W",
   "h_dr_W_tWl",
   "h_dr_W_tWnu",
   "h_dr_t_W",
   "h_dr_tWl_tWnu",

   "h_costheta_tb_tWl",
   "h_costheta_tb_tWnu",
   "h_costheta_Hb_tb",
   "h_costheta_tb_W",
   "h_costheta_H_tb",
   "h_costheta_t_H",
   "h_costheta_t_Hb",
   "h_costheta_H_Hb",
   "h_costheta_H_W",
   "h_costheta_H_tWl",
   "h_costheta_H_tWnu",
   "h_costheta_Hb1_Hb2",
   "h_costheta_Hb_tWl",
   "h_costheta_Hb_tWnu",
   "h_costheta_Hb_W",
   "h_costheta_W_tWl",
   "h_costheta_W_tWnu",
   "h_costheta_t_W",
   "h_costheta_tWl_tWnu"
};

std::string xtit[nh] =
{
   "P_{T} (t) [GeV]",
   "P_{T} (b_{t}) [GeV]",
   "P_{T} (l) [GeV]",
   "P_{T} (#nu) [GeV]",
   "P_{T} (W) [GeV]",
   "P_{T} (H) [GeV]",
   "P_{T} (b_{H}) [GeV]",

   "#eta (t)",
   "#eta (b_{t})",
   "#eta (l)",
   "#eta (#nu)",
   "#eta (W)",
   "#eta (H)",
   "#eta (b_{H})",

   "#varphi (t)",
   "#varphi (b_{t})",
   "#varphi (l)",
   "#varphi (#nu)",
   "#varphi (W)",
   "#varphi (H)",
   "#varphi (b_{H})",
   
   "#Delta R (b_{t},l)",
   "#Delta R (b_{t},#nu)",
   "#Delta R (b_{t},b_{H})",
   "#Delta R (b_{t},W)",
   "#Delta R (b_{t},H)",
   "#Delta R (t,H)",
   "#Delta R (t,b_{H})",
   "#Delta R (H,b_{H})",
   "#Delta R (H,W)",
   "#Delta R (H,l)",
   "#Delta R (H,#nu)",
   "#Delta R (b1_{H},b2_{H})",
   "#Delta R (b_{H},l)",
   "#Delta R (b_{H},#nu)",
   "#Delta R (b_{H},W)",
   "#Delta R (W,l)",
   "#Delta R (W,#nu)",
   "#Delta R (W,t)",
   "#Delta R (l,#nu)",

   "cos#theta (b_{t},l)",
   "cos#theta (b_{t},#nu)",
   "cos#theta (b_{t},b_{H})",
   "cos#theta (b_{t},W)",
   "cos#theta (b_{t},H)",
   "cos#theta (t,H)",
   "cos#theta (t,b_{H})",
   "cos#theta (H,b_{H})",
   "cos#theta (H,W)",
   "cos#theta (H,l)",
   "cos#theta (H,#nu)",
   "cos#theta (b1_{H},b2_{H})",
   "cos#theta (b_{H},l)",
   "cos#theta (b_{H},#nu)",
   "cos#theta (b_{H},W)",
   "cos#theta (W,l)",
   "cos#theta (W,#nu)",
   "cos#theta (W,t)",
   "cos#theta (l,#nu)"
};

// samples
const int nf = 3;
std::string fname[nf] =
{
   "tHToBB-1L-Kappa-hut_CMS",
   "tHToBB-1L-Kappa-hct_CMS",
   "TTtoHToBB-1L-Kappa-hut_CMS"
};

std::string glab[nf] =
{
   "Hut",
   "Hct",
   "Hut (ttbar)"
};
