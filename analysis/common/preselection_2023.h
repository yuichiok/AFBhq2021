//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct  3 21:26:35 2023 by ROOT version 6.24/00
// from TTree Stats/tree
// found on file: /group/ilc/users/yokugawa/QQbar250/l5/P4f_ww_h/eLpR/500066/15311/dEdx_corr/QQbarProcessor_out/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500066.P4f_ww_h.eL.pR.n078.d_dstm_15311_38.root
//////////////////////////////////////////////////////////

#ifndef preselection_2023_h
#define preselection_2023_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class preselection_2023 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         mc_quark_E[2];
   Float_t         mc_quark_px[2];
   Float_t         mc_quark_py[2];
   Float_t         mc_quark_pz[2];
   Float_t         mc_quark_m[2];
   Float_t         mc_quark_pdg[2];
   Float_t         mc_quark_charge[2];
   Float_t         mc_ISR_E[2];
   Float_t         mc_ISR_px[2];
   Float_t         mc_ISR_py[2];
   Float_t         mc_ISR_pz[2];
   Float_t         mc_ISR_m[2];
   Float_t         mc_ISR_pdg[2];
   Float_t         mc_ISR_charge[2];
   Int_t           mc_quark_ps_n;
   Float_t         mc_quark_ps_E[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_px[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_py[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_pz[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_m[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_pdg[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_charge[1];   //[mc_quark_ps_n]
   Float_t         mc_quark_ps_y12;
   Float_t         mc_quark_ps_y23;
   Float_t         mc_quark_ps_d12;
   Float_t         mc_quark_ps_d23;
   Float_t         mc_quark_ps_jet_E[2];
   Float_t         mc_quark_ps_jet_px[2];
   Float_t         mc_quark_ps_jet_py[2];
   Float_t         mc_quark_ps_jet_pz[2];
   Int_t           mc_stable_n;
   Float_t         mc_stable_E[1];   //[mc_stable_n]
   Float_t         mc_stable_px[1];   //[mc_stable_n]
   Float_t         mc_stable_py[1];   //[mc_stable_n]
   Float_t         mc_stable_pz[1];   //[mc_stable_n]
   Float_t         mc_stable_m[1];   //[mc_stable_n]
   Int_t           mc_stable_pdg[1];   //[mc_stable_n]
   Float_t         mc_stable_charge[1];   //[mc_stable_n]
   Int_t           mc_stable_isoverlay[1];   //[mc_stable_n]
   Int_t           mc_stable_isisr[1];   //[mc_stable_n]
   Float_t         mc_stable_y12;
   Float_t         mc_stable_y23;
   Float_t         mc_stable_d12;
   Float_t         mc_stable_d23;
   Float_t         mc_stable_jet_E[2];
   Float_t         mc_stable_jet_px[2];
   Float_t         mc_stable_jet_py[2];
   Float_t         mc_stable_jet_pz[2];
   Float_t         truejet_E[5];
   Float_t         truejet_px[5];
   Float_t         truejet_py[5];
   Float_t         truejet_pz[5];
   Int_t           truejet_type[5];
   Int_t           truejet_pdg[5];
   Float_t         jet_E[2];
   Float_t         jet_px[2];
   Float_t         jet_py[2];
   Float_t         jet_pz[2];
   Float_t         jet_btag[2];
   Float_t         jet_ctag[2];
   Float_t         y23;
   Float_t         y12;
   Float_t         d23;
   Float_t         d12;
   Float_t         oblateness;
   Float_t         aplanarity;
   Float_t         major_thrust_value;
   Float_t         major_thrust_axis[3];
   Float_t         minor_thrust_value;
   Float_t         minor_thrust_axis[3];
   Float_t         principle_thrust_value;
   Float_t         principle_thrust_axis[3];
   Float_t         sphericity;
   Float_t         sphericity_tensor[3];
   Int_t           jet_npfo[2];
   Int_t           jet_nvtx[2];
   Float_t         vtx_d0[2][10];
   Float_t         vtx_z0[2][10];
   Int_t           pfo_n;
   Int_t           nvtx;
   Int_t           pfo_match[172];   //[pfo_n]
   Int_t           pfo_truejet_pdg[172];   //[pfo_n]
   Int_t           pfo_truejet_type[172];   //[pfo_n]
   Int_t           pfo_pdgcheat[172];   //[pfo_n]
   Int_t           pfo_pdgcheat_id[172];   //[pfo_n]
   Int_t           pfo_nparents[172];   //[pfo_n]
   Int_t           pfo_pdgcheat_parent[172][1000];   //[pfo_n]
   Float_t         pfo_E[172];   //[pfo_n]
   Float_t         pfo_px[172];   //[pfo_n]
   Float_t         pfo_py[172];   //[pfo_n]
   Float_t         pfo_pz[172];   //[pfo_n]
   Float_t         pfo_m[172];   //[pfo_n]
   Int_t           pfo_type[172];   //[pfo_n]
   Int_t           pfo_isoverlay[172];   //[pfo_n]
   Int_t           pfo_isisr[172];   //[pfo_n]
   Int_t           pfo_vtx[172];   //[pfo_n]
   Int_t           pfo_charge[172];   //[pfo_n]
   Int_t           pfo_ntracks[172];   //[pfo_n]
   Int_t           pfo_tpc_hits[172];   //[pfo_n]
   Float_t         pfo_dedx[172];   //[pfo_n]
   Float_t         pfo_dedxerror[172];   //[pfo_n]
   Float_t         pfo_d0[172];   //[pfo_n]
   Float_t         pfo_d0error[172];   //[pfo_n]
   Float_t         pfo_z0[172];   //[pfo_n]
   Float_t         pfo_z0error[172];   //[pfo_n]
   Float_t         pfo_phi[172];   //[pfo_n]
   Float_t         pfo_phierror[172];   //[pfo_n]
   Float_t         pfo_omega[172];   //[pfo_n]
   Float_t         pfo_omegaerror[172];   //[pfo_n]
   Float_t         pfo_tanlambda[172];   //[pfo_n]
   Float_t         pfo_tanlambdaerror[172];   //[pfo_n]
   Float_t         pfo_chi2[172];   //[pfo_n]
   Float_t         pfo_ndf[172];   //[pfo_n]
   Float_t         pfo_vtxpt[172][3];   //[pfo_n]
   Float_t         pfo_endpt[172][3];   //[pfo_n]
   Int_t           pfo_pid[172];   //[pfo_n]
   Float_t         pfo_pid_likelihood[172];   //[pfo_n]
   Float_t         pfo_pid_eprob[172];   //[pfo_n]
   Float_t         pfo_pid_muprob[172];   //[pfo_n]
   Float_t         pfo_pid_piprob[172];   //[pfo_n]
   Float_t         pfo_pid_kprob[172];   //[pfo_n]
   Float_t         pfo_pid_pprob[172];   //[pfo_n]
   Float_t         pfo_pid_hprob[172];   //[pfo_n]
   Int_t           pfo_piddedx[172];   //[pfo_n]
   Float_t         pfo_piddedx_likelihood[172];   //[pfo_n]
   Float_t         pfo_piddedx_eprob[172];   //[pfo_n]
   Float_t         pfo_piddedx_muprob[172];   //[pfo_n]
   Float_t         pfo_piddedx_piprob[172];   //[pfo_n]
   Float_t         pfo_piddedx_kprob[172];   //[pfo_n]
   Float_t         pfo_piddedx_pprob[172];   //[pfo_n]
   Float_t         pfo_piddedx_hprob[172];   //[pfo_n]
   Float_t         pfo_piddedx_e_dedxdist[172];   //[pfo_n]
   Float_t         pfo_piddedx_mu_dedxdist[172];   //[pfo_n]
   Float_t         pfo_piddedx_pi_dedxdist[172];   //[pfo_n]
   Float_t         pfo_piddedx_k_dedxdist[172];   //[pfo_n]
   Float_t         pfo_piddedx_p_dedxdist[172];   //[pfo_n]
   Float_t         pfo_piddedx_e_lkhood[172];   //[pfo_n]
   Float_t         pfo_piddedx_mu_lkhood[172];   //[pfo_n]
   Float_t         pfo_piddedx_pi_lkhood[172];   //[pfo_n]
   Float_t         pfo_piddedx_k_lkhood[172];   //[pfo_n]
   Float_t         pfo_piddedx_p_lkhood[172];   //[pfo_n]
   Float_t         pfo_pidtof_p_at_calo[172];   //[pfo_n]
   Float_t         pfo_pidtof_closest_beta_0ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closest_beta_10ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closest_beta_50ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closest_beta_100ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_fastest_beta_0ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_fastest_beta_10ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_fastest_beta_50ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_fastest_beta_100ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_cylfit_beta_0ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_cylfit_beta_10ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_cylfit_beta_50ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_cylfit_beta_100ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closestfit_beta_0ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closestfit_beta_10ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closestfit_beta_50ps[172];   //[pfo_n]
   Float_t         pfo_pidtof_closestfit_beta_100ps[172];   //[pfo_n]

   // List of branches
   TBranch        *b_mc_quark_E;   //!
   TBranch        *b_mc_quark_px;   //!
   TBranch        *b_mc_quark_py;   //!
   TBranch        *b_mc_quark_pz;   //!
   TBranch        *b_mc_quark_m;   //!
   TBranch        *b_mc_quark_pdg;   //!
   TBranch        *b_mc_quark_charge;   //!
   TBranch        *b_mc_ISR_E;   //!
   TBranch        *b_mc_ISR_px;   //!
   TBranch        *b_mc_ISR_py;   //!
   TBranch        *b_mc_ISR_pz;   //!
   TBranch        *b_mc_ISR_m;   //!
   TBranch        *b_mc_ISR_pdg;   //!
   TBranch        *b_mc_ISR_charge;   //!
   TBranch        *b_mc_quark_ps_n;   //!
   TBranch        *b_mc_quark_ps_E;   //!
   TBranch        *b_mc_quark_ps_px;   //!
   TBranch        *b_mc_quark_ps_py;   //!
   TBranch        *b_mc_quark_ps_pz;   //!
   TBranch        *b_mc_quark_ps_m;   //!
   TBranch        *b_mc_quark_ps_pdg;   //!
   TBranch        *b_mc_quark_ps_charge;   //!
   TBranch        *b_mc_quark_ps_y12;   //!
   TBranch        *b_mc_quark_ps_y23;   //!
   TBranch        *b_mc_quark_ps_d12;   //!
   TBranch        *b_mc_quark_ps_d23;   //!
   TBranch        *b_mc_quark_ps_jet_E;   //!
   TBranch        *b_mc_quark_ps_jet_px;   //!
   TBranch        *b_mc_quark_ps_jet_py;   //!
   TBranch        *b_mc_quark_ps_jet_pz;   //!
   TBranch        *b_mc_stable_n;   //!
   TBranch        *b_mc_stable_E;   //!
   TBranch        *b_mc_stable_px;   //!
   TBranch        *b_mc_stable_py;   //!
   TBranch        *b_mc_stable_pz;   //!
   TBranch        *b_mc_stable_m;   //!
   TBranch        *b_mc_stable_pdg;   //!
   TBranch        *b_mc_stable_charge;   //!
   TBranch        *b_mc_stable_isoverlay;   //!
   TBranch        *b_mc_stable_isisr;   //!
   TBranch        *b_mc_stable_y12;   //!
   TBranch        *b_mc_stable_y23;   //!
   TBranch        *b_mc_stable_d12;   //!
   TBranch        *b_mc_stable_d23;   //!
   TBranch        *b_mc_stable_jet_E;   //!
   TBranch        *b_mc_stable_jet_px;   //!
   TBranch        *b_mc_stable_jet_py;   //!
   TBranch        *b_mc_stable_jet_pz;   //!
   TBranch        *b_truejet_E;   //!
   TBranch        *b_truejet_px;   //!
   TBranch        *b_truejet_py;   //!
   TBranch        *b_truejet_pz;   //!
   TBranch        *b_truejet_type;   //!
   TBranch        *b_truejet_pdg;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_px;   //!
   TBranch        *b_jet_py;   //!
   TBranch        *b_jet_pz;   //!
   TBranch        *b_jet_btag;   //!
   TBranch        *b_jet_ctag;   //!
   TBranch        *b_y23;   //!
   TBranch        *b_y12;   //!
   TBranch        *b_d23;   //!
   TBranch        *b_d12;   //!
   TBranch        *b_oblateness;   //!
   TBranch        *b_aplanarity;   //!
   TBranch        *b_major_thrust_value;   //!
   TBranch        *b_major_thrust_axis;   //!
   TBranch        *b_minor_thrust_value;   //!
   TBranch        *b_minor_thrust_axis;   //!
   TBranch        *b_principle_thrust_value;   //!
   TBranch        *b_principle_thrust_axis;   //!
   TBranch        *b_sphericity;   //!
   TBranch        *b_sphericity_tensor;   //!
   TBranch        *b_jet_npfo;   //!
   TBranch        *b_jet_nvtx;   //!
   TBranch        *b_vtx_d0;   //!
   TBranch        *b_vtx_z0;   //!
   TBranch        *b_pfo_n;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_pfo_match;   //!
   TBranch        *b_pfo_truejet_pdg;   //!
   TBranch        *b_pfo_truejet_type;   //!
   TBranch        *b_pfo_pdgcheat;   //!
   TBranch        *b_pfo_pdgcheat_id;   //!
   TBranch        *b_pfo_nparents;   //!
   TBranch        *b_pfo_pdgcheat_parent;   //!
   TBranch        *b_pfo_E;   //!
   TBranch        *b_pfo_px;   //!
   TBranch        *b_pfo_py;   //!
   TBranch        *b_pfo_pz;   //!
   TBranch        *b_pfo_m;   //!
   TBranch        *b_pfo_type;   //!
   TBranch        *b_pfo_isoverlay;   //!
   TBranch        *b_pfo_isisr;   //!
   TBranch        *b_pfo_vtx;   //!
   TBranch        *b_pfo_charge;   //!
   TBranch        *b_pfo_ntracks;   //!
   TBranch        *b_pfo_tpc_hits;   //!
   TBranch        *b_pfo_dedx;   //!
   TBranch        *b_pfo_dedxerror;   //!
   TBranch        *b_pfo_d0;   //!
   TBranch        *b_pfo_d0error;   //!
   TBranch        *b_pfo_z0;   //!
   TBranch        *b_pfo_z0error;   //!
   TBranch        *b_pfo_phi;   //!
   TBranch        *b_pfo_phierror;   //!
   TBranch        *b_pfo_omega;   //!
   TBranch        *b_pfo_omegaerror;   //!
   TBranch        *b_pfo_tanlambda;   //!
   TBranch        *b_pfo_tanlambdaerror;   //!
   TBranch        *b_pfo_chi2;   //!
   TBranch        *b_pfo_ndf;   //!
   TBranch        *b_pfo_vtxpt;   //!
   TBranch        *b_pfo_endpt;   //!
   TBranch        *b_pfo_pid;   //!
   TBranch        *b_pfo_pid_likelihood;   //!
   TBranch        *b_pfo_pid_eprob;   //!
   TBranch        *b_pfo_pid_muprob;   //!
   TBranch        *b_pfo_pid_piprob;   //!
   TBranch        *b_pfo_pid_kprob;   //!
   TBranch        *b_pfo_pid_pprob;   //!
   TBranch        *b_pfo_pid_hprob;   //!
   TBranch        *b_pfo_piddedx;   //!
   TBranch        *b_pfo_piddedx_likelihood;   //!
   TBranch        *b_pfo_piddedx_eprob;   //!
   TBranch        *b_pfo_piddedx_muprob;   //!
   TBranch        *b_pfo_piddedx_piprob;   //!
   TBranch        *b_pfo_piddedx_kprob;   //!
   TBranch        *b_pfo_piddedx_pprob;   //!
   TBranch        *b_pfo_piddedx_hprob;   //!
   TBranch        *b_pfo_piddedx_e_dedxdist;   //!
   TBranch        *b_pfo_piddedx_mu_dedxdist;   //!
   TBranch        *b_pfo_piddedx_pi_dedxdist;   //!
   TBranch        *b_pfo_piddedx_k_dedxdist;   //!
   TBranch        *b_pfo_piddedx_p_dedxdist;   //!
   TBranch        *b_pfo_piddedx_e_lkhood;   //!
   TBranch        *b_pfo_piddedx_mu_lkhood;   //!
   TBranch        *b_pfo_piddedx_pi_lkhood;   //!
   TBranch        *b_pfo_piddedx_k_lkhood;   //!
   TBranch        *b_pfo_piddedx_p_lkhood;   //!
   TBranch        *b_pfo_pidtof_p_at_calo;   //!
   TBranch        *b_pfo_pidtof_closest_beta_0ps;   //!
   TBranch        *b_pfo_pidtof_closest_beta_10ps;   //!
   TBranch        *b_pfo_pidtof_closest_beta_50ps;   //!
   TBranch        *b_pfo_pidtof_closest_beta_100ps;   //!
   TBranch        *b_pfo_pidtof_fastest_beta_0ps;   //!
   TBranch        *b_pfo_pidtof_fastest_beta_10ps;   //!
   TBranch        *b_pfo_pidtof_fastest_beta_50ps;   //!
   TBranch        *b_pfo_pidtof_fastest_beta_100ps;   //!
   TBranch        *b_pfo_pidtof_cylfit_beta_0ps;   //!
   TBranch        *b_pfo_pidtof_cylfit_beta_10ps;   //!
   TBranch        *b_pfo_pidtof_cylfit_beta_50ps;   //!
   TBranch        *b_pfo_pidtof_cylfit_beta_100ps;   //!
   TBranch        *b_pfo_pidtof_closestfit_beta_0ps;   //!
   TBranch        *b_pfo_pidtof_closestfit_beta_10ps;   //!
   TBranch        *b_pfo_pidtof_closestfit_beta_50ps;   //!
   TBranch        *b_pfo_pidtof_closestfit_beta_100ps;   //!

   preselection_2023(TTree *tree=0);
   virtual ~preselection_2023();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef preselection_2023_cxx
preselection_2023::preselection_2023(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/group/ilc/users/yokugawa/QQbar250/l5/P4f_ww_h/eLpR/500066/15311/dEdx_corr/QQbarProcessor_out/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500066.P4f_ww_h.eL.pR.n078.d_dstm_15311_38.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/group/ilc/users/yokugawa/QQbar250/l5/P4f_ww_h/eLpR/500066/15311/dEdx_corr/QQbarProcessor_out/rv02-02.sv02-02.mILD_l5_o1_v02.E250-SetA.I500066.P4f_ww_h.eL.pR.n078.d_dstm_15311_38.root");
      }
      f->GetObject("Stats",tree);

   }
   Init(tree);
}

preselection_2023::~preselection_2023()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t preselection_2023::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t preselection_2023::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void preselection_2023::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mc_quark_E", mc_quark_E, &b_mc_quark_E);
   fChain->SetBranchAddress("mc_quark_px", mc_quark_px, &b_mc_quark_px);
   fChain->SetBranchAddress("mc_quark_py", mc_quark_py, &b_mc_quark_py);
   fChain->SetBranchAddress("mc_quark_pz", mc_quark_pz, &b_mc_quark_pz);
   fChain->SetBranchAddress("mc_quark_m", mc_quark_m, &b_mc_quark_m);
   fChain->SetBranchAddress("mc_quark_pdg", mc_quark_pdg, &b_mc_quark_pdg);
   fChain->SetBranchAddress("mc_quark_charge", mc_quark_charge, &b_mc_quark_charge);
   fChain->SetBranchAddress("mc_ISR_E", mc_ISR_E, &b_mc_ISR_E);
   fChain->SetBranchAddress("mc_ISR_px", mc_ISR_px, &b_mc_ISR_px);
   fChain->SetBranchAddress("mc_ISR_py", mc_ISR_py, &b_mc_ISR_py);
   fChain->SetBranchAddress("mc_ISR_pz", mc_ISR_pz, &b_mc_ISR_pz);
   fChain->SetBranchAddress("mc_ISR_m", mc_ISR_m, &b_mc_ISR_m);
   fChain->SetBranchAddress("mc_ISR_pdg", mc_ISR_pdg, &b_mc_ISR_pdg);
   fChain->SetBranchAddress("mc_ISR_charge", mc_ISR_charge, &b_mc_ISR_charge);
   fChain->SetBranchAddress("mc_quark_ps_n", &mc_quark_ps_n, &b_mc_quark_ps_n);
   fChain->SetBranchAddress("mc_quark_ps_E", &mc_quark_ps_E, &b_mc_quark_ps_E);
   fChain->SetBranchAddress("mc_quark_ps_px", &mc_quark_ps_px, &b_mc_quark_ps_px);
   fChain->SetBranchAddress("mc_quark_ps_py", &mc_quark_ps_py, &b_mc_quark_ps_py);
   fChain->SetBranchAddress("mc_quark_ps_pz", &mc_quark_ps_pz, &b_mc_quark_ps_pz);
   fChain->SetBranchAddress("mc_quark_ps_m", &mc_quark_ps_m, &b_mc_quark_ps_m);
   fChain->SetBranchAddress("mc_quark_ps_pdg", &mc_quark_ps_pdg, &b_mc_quark_ps_pdg);
   fChain->SetBranchAddress("mc_quark_ps_charge", &mc_quark_ps_charge, &b_mc_quark_ps_charge);
   fChain->SetBranchAddress("mc_quark_ps_y12", &mc_quark_ps_y12, &b_mc_quark_ps_y12);
   fChain->SetBranchAddress("mc_quark_ps_y23", &mc_quark_ps_y23, &b_mc_quark_ps_y23);
   fChain->SetBranchAddress("mc_quark_ps_d12", &mc_quark_ps_d12, &b_mc_quark_ps_d12);
   fChain->SetBranchAddress("mc_quark_ps_d23", &mc_quark_ps_d23, &b_mc_quark_ps_d23);
   fChain->SetBranchAddress("mc_quark_ps_jet_E", mc_quark_ps_jet_E, &b_mc_quark_ps_jet_E);
   fChain->SetBranchAddress("mc_quark_ps_jet_px", mc_quark_ps_jet_px, &b_mc_quark_ps_jet_px);
   fChain->SetBranchAddress("mc_quark_ps_jet_py", mc_quark_ps_jet_py, &b_mc_quark_ps_jet_py);
   fChain->SetBranchAddress("mc_quark_ps_jet_pz", mc_quark_ps_jet_pz, &b_mc_quark_ps_jet_pz);
   fChain->SetBranchAddress("mc_stable_n", &mc_stable_n, &b_mc_stable_n);
   fChain->SetBranchAddress("mc_stable_E", &mc_stable_E, &b_mc_stable_E);
   fChain->SetBranchAddress("mc_stable_px", &mc_stable_px, &b_mc_stable_px);
   fChain->SetBranchAddress("mc_stable_py", &mc_stable_py, &b_mc_stable_py);
   fChain->SetBranchAddress("mc_stable_pz", &mc_stable_pz, &b_mc_stable_pz);
   fChain->SetBranchAddress("mc_stable_m", &mc_stable_m, &b_mc_stable_m);
   fChain->SetBranchAddress("mc_stable_pdg", &mc_stable_pdg, &b_mc_stable_pdg);
   fChain->SetBranchAddress("mc_stable_charge", &mc_stable_charge, &b_mc_stable_charge);
   fChain->SetBranchAddress("mc_stable_isoverlay", &mc_stable_isoverlay, &b_mc_stable_isoverlay);
   fChain->SetBranchAddress("mc_stable_isisr", &mc_stable_isisr, &b_mc_stable_isisr);
   fChain->SetBranchAddress("mc_stable_y12", &mc_stable_y12, &b_mc_stable_y12);
   fChain->SetBranchAddress("mc_stable_y23", &mc_stable_y23, &b_mc_stable_y23);
   fChain->SetBranchAddress("mc_stable_d12", &mc_stable_d12, &b_mc_stable_d12);
   fChain->SetBranchAddress("mc_stable_d23", &mc_stable_d23, &b_mc_stable_d23);
   fChain->SetBranchAddress("mc_stable_jet_E", mc_stable_jet_E, &b_mc_stable_jet_E);
   fChain->SetBranchAddress("mc_stable_jet_px", mc_stable_jet_px, &b_mc_stable_jet_px);
   fChain->SetBranchAddress("mc_stable_jet_py", mc_stable_jet_py, &b_mc_stable_jet_py);
   fChain->SetBranchAddress("mc_stable_jet_pz", mc_stable_jet_pz, &b_mc_stable_jet_pz);
   fChain->SetBranchAddress("truejet_E", truejet_E, &b_truejet_E);
   fChain->SetBranchAddress("truejet_px", truejet_px, &b_truejet_px);
   fChain->SetBranchAddress("truejet_py", truejet_py, &b_truejet_py);
   fChain->SetBranchAddress("truejet_pz", truejet_pz, &b_truejet_pz);
   fChain->SetBranchAddress("truejet_type", truejet_type, &b_truejet_type);
   fChain->SetBranchAddress("truejet_pdg", truejet_pdg, &b_truejet_pdg);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_px", jet_px, &b_jet_px);
   fChain->SetBranchAddress("jet_py", jet_py, &b_jet_py);
   fChain->SetBranchAddress("jet_pz", jet_pz, &b_jet_pz);
   fChain->SetBranchAddress("jet_btag", jet_btag, &b_jet_btag);
   fChain->SetBranchAddress("jet_ctag", jet_ctag, &b_jet_ctag);
   fChain->SetBranchAddress("y23", &y23, &b_y23);
   fChain->SetBranchAddress("y12", &y12, &b_y12);
   fChain->SetBranchAddress("d23", &d23, &b_d23);
   fChain->SetBranchAddress("d12", &d12, &b_d12);
   fChain->SetBranchAddress("oblateness", &oblateness, &b_oblateness);
   fChain->SetBranchAddress("aplanarity", &aplanarity, &b_aplanarity);
   fChain->SetBranchAddress("major_thrust_value", &major_thrust_value, &b_major_thrust_value);
   fChain->SetBranchAddress("major_thrust_axis", major_thrust_axis, &b_major_thrust_axis);
   fChain->SetBranchAddress("minor_thrust_value", &minor_thrust_value, &b_minor_thrust_value);
   fChain->SetBranchAddress("minor_thrust_axis", minor_thrust_axis, &b_minor_thrust_axis);
   fChain->SetBranchAddress("principle_thrust_value", &principle_thrust_value, &b_principle_thrust_value);
   fChain->SetBranchAddress("principle_thrust_axis", principle_thrust_axis, &b_principle_thrust_axis);
   fChain->SetBranchAddress("sphericity", &sphericity, &b_sphericity);
   fChain->SetBranchAddress("sphericity_tensor", sphericity_tensor, &b_sphericity_tensor);
   fChain->SetBranchAddress("jet_npfo", jet_npfo, &b_jet_npfo);
   fChain->SetBranchAddress("jet_nvtx", jet_nvtx, &b_jet_nvtx);
   fChain->SetBranchAddress("vtx_d0", vtx_d0, &b_vtx_d0);
   fChain->SetBranchAddress("vtx_z0", vtx_z0, &b_vtx_z0);
   fChain->SetBranchAddress("pfo_n", &pfo_n, &b_pfo_n);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("pfo_match", pfo_match, &b_pfo_match);
   fChain->SetBranchAddress("pfo_truejet_pdg", pfo_truejet_pdg, &b_pfo_truejet_pdg);
   fChain->SetBranchAddress("pfo_truejet_type", pfo_truejet_type, &b_pfo_truejet_type);
   fChain->SetBranchAddress("pfo_pdgcheat", pfo_pdgcheat, &b_pfo_pdgcheat);
   fChain->SetBranchAddress("pfo_pdgcheat_id", pfo_pdgcheat_id, &b_pfo_pdgcheat_id);
   fChain->SetBranchAddress("pfo_nparents", pfo_nparents, &b_pfo_nparents);
   fChain->SetBranchAddress("pfo_pdgcheat_parent", pfo_pdgcheat_parent, &b_pfo_pdgcheat_parent);
   fChain->SetBranchAddress("pfo_E", pfo_E, &b_pfo_E);
   fChain->SetBranchAddress("pfo_px", pfo_px, &b_pfo_px);
   fChain->SetBranchAddress("pfo_py", pfo_py, &b_pfo_py);
   fChain->SetBranchAddress("pfo_pz", pfo_pz, &b_pfo_pz);
   fChain->SetBranchAddress("pfo_m", pfo_m, &b_pfo_m);
   fChain->SetBranchAddress("pfo_type", pfo_type, &b_pfo_type);
   fChain->SetBranchAddress("pfo_isoverlay", pfo_isoverlay, &b_pfo_isoverlay);
   fChain->SetBranchAddress("pfo_isisr", pfo_isisr, &b_pfo_isisr);
   fChain->SetBranchAddress("pfo_vtx", pfo_vtx, &b_pfo_vtx);
   fChain->SetBranchAddress("pfo_charge", pfo_charge, &b_pfo_charge);
   fChain->SetBranchAddress("pfo_ntracks", pfo_ntracks, &b_pfo_ntracks);
   fChain->SetBranchAddress("pfo_tpc_hits", pfo_tpc_hits, &b_pfo_tpc_hits);
   fChain->SetBranchAddress("pfo_dedx", pfo_dedx, &b_pfo_dedx);
   fChain->SetBranchAddress("pfo_dedxerror", pfo_dedxerror, &b_pfo_dedxerror);
   fChain->SetBranchAddress("pfo_d0", pfo_d0, &b_pfo_d0);
   fChain->SetBranchAddress("pfo_d0error", pfo_d0error, &b_pfo_d0error);
   fChain->SetBranchAddress("pfo_z0", pfo_z0, &b_pfo_z0);
   fChain->SetBranchAddress("pfo_z0error", pfo_z0error, &b_pfo_z0error);
   fChain->SetBranchAddress("pfo_phi", pfo_phi, &b_pfo_phi);
   fChain->SetBranchAddress("pfo_phierror", pfo_phierror, &b_pfo_phierror);
   fChain->SetBranchAddress("pfo_omega", pfo_omega, &b_pfo_omega);
   fChain->SetBranchAddress("pfo_omegaerror", pfo_omegaerror, &b_pfo_omegaerror);
   fChain->SetBranchAddress("pfo_tanlambda", pfo_tanlambda, &b_pfo_tanlambda);
   fChain->SetBranchAddress("pfo_tanlambdaerror", pfo_tanlambdaerror, &b_pfo_tanlambdaerror);
   fChain->SetBranchAddress("pfo_chi2", pfo_chi2, &b_pfo_chi2);
   fChain->SetBranchAddress("pfo_ndf", pfo_ndf, &b_pfo_ndf);
   fChain->SetBranchAddress("pfo_vtxpt", pfo_vtxpt, &b_pfo_vtxpt);
   fChain->SetBranchAddress("pfo_endpt", pfo_endpt, &b_pfo_endpt);
   fChain->SetBranchAddress("pfo_pid", pfo_pid, &b_pfo_pid);
   fChain->SetBranchAddress("pfo_pid_likelihood", pfo_pid_likelihood, &b_pfo_pid_likelihood);
   fChain->SetBranchAddress("pfo_pid_eprob", pfo_pid_eprob, &b_pfo_pid_eprob);
   fChain->SetBranchAddress("pfo_pid_muprob", pfo_pid_muprob, &b_pfo_pid_muprob);
   fChain->SetBranchAddress("pfo_pid_piprob", pfo_pid_piprob, &b_pfo_pid_piprob);
   fChain->SetBranchAddress("pfo_pid_kprob", pfo_pid_kprob, &b_pfo_pid_kprob);
   fChain->SetBranchAddress("pfo_pid_pprob", pfo_pid_pprob, &b_pfo_pid_pprob);
   fChain->SetBranchAddress("pfo_pid_hprob", pfo_pid_hprob, &b_pfo_pid_hprob);
   fChain->SetBranchAddress("pfo_piddedx", pfo_piddedx, &b_pfo_piddedx);
   fChain->SetBranchAddress("pfo_piddedx_likelihood", pfo_piddedx_likelihood, &b_pfo_piddedx_likelihood);
   fChain->SetBranchAddress("pfo_piddedx_eprob", pfo_piddedx_eprob, &b_pfo_piddedx_eprob);
   fChain->SetBranchAddress("pfo_piddedx_muprob", pfo_piddedx_muprob, &b_pfo_piddedx_muprob);
   fChain->SetBranchAddress("pfo_piddedx_piprob", pfo_piddedx_piprob, &b_pfo_piddedx_piprob);
   fChain->SetBranchAddress("pfo_piddedx_kprob", pfo_piddedx_kprob, &b_pfo_piddedx_kprob);
   fChain->SetBranchAddress("pfo_piddedx_pprob", pfo_piddedx_pprob, &b_pfo_piddedx_pprob);
   fChain->SetBranchAddress("pfo_piddedx_hprob", pfo_piddedx_hprob, &b_pfo_piddedx_hprob);
   fChain->SetBranchAddress("pfo_piddedx_e_dedxdist", pfo_piddedx_e_dedxdist, &b_pfo_piddedx_e_dedxdist);
   fChain->SetBranchAddress("pfo_piddedx_mu_dedxdist", pfo_piddedx_mu_dedxdist, &b_pfo_piddedx_mu_dedxdist);
   fChain->SetBranchAddress("pfo_piddedx_pi_dedxdist", pfo_piddedx_pi_dedxdist, &b_pfo_piddedx_pi_dedxdist);
   fChain->SetBranchAddress("pfo_piddedx_k_dedxdist", pfo_piddedx_k_dedxdist, &b_pfo_piddedx_k_dedxdist);
   fChain->SetBranchAddress("pfo_piddedx_p_dedxdist", pfo_piddedx_p_dedxdist, &b_pfo_piddedx_p_dedxdist);
   fChain->SetBranchAddress("pfo_piddedx_e_lkhood", pfo_piddedx_e_lkhood, &b_pfo_piddedx_e_lkhood);
   fChain->SetBranchAddress("pfo_piddedx_mu_lkhood", pfo_piddedx_mu_lkhood, &b_pfo_piddedx_mu_lkhood);
   fChain->SetBranchAddress("pfo_piddedx_pi_lkhood", pfo_piddedx_pi_lkhood, &b_pfo_piddedx_pi_lkhood);
   fChain->SetBranchAddress("pfo_piddedx_k_lkhood", pfo_piddedx_k_lkhood, &b_pfo_piddedx_k_lkhood);
   fChain->SetBranchAddress("pfo_piddedx_p_lkhood", pfo_piddedx_p_lkhood, &b_pfo_piddedx_p_lkhood);
   fChain->SetBranchAddress("pfo_pidtof_p_at_calo", pfo_pidtof_p_at_calo, &b_pfo_pidtof_p_at_calo);
   fChain->SetBranchAddress("pfo_pidtof_closest_beta_0ps", pfo_pidtof_closest_beta_0ps, &b_pfo_pidtof_closest_beta_0ps);
   fChain->SetBranchAddress("pfo_pidtof_closest_beta_10ps", pfo_pidtof_closest_beta_10ps, &b_pfo_pidtof_closest_beta_10ps);
   fChain->SetBranchAddress("pfo_pidtof_closest_beta_50ps", pfo_pidtof_closest_beta_50ps, &b_pfo_pidtof_closest_beta_50ps);
   fChain->SetBranchAddress("pfo_pidtof_closest_beta_100ps", pfo_pidtof_closest_beta_100ps, &b_pfo_pidtof_closest_beta_100ps);
   fChain->SetBranchAddress("pfo_pidtof_fastest_beta_0ps", pfo_pidtof_fastest_beta_0ps, &b_pfo_pidtof_fastest_beta_0ps);
   fChain->SetBranchAddress("pfo_pidtof_fastest_beta_10ps", pfo_pidtof_fastest_beta_10ps, &b_pfo_pidtof_fastest_beta_10ps);
   fChain->SetBranchAddress("pfo_pidtof_fastest_beta_50ps", pfo_pidtof_fastest_beta_50ps, &b_pfo_pidtof_fastest_beta_50ps);
   fChain->SetBranchAddress("pfo_pidtof_fastest_beta_100ps", pfo_pidtof_fastest_beta_100ps, &b_pfo_pidtof_fastest_beta_100ps);
   fChain->SetBranchAddress("pfo_pidtof_cylfit_beta_0ps", pfo_pidtof_cylfit_beta_0ps, &b_pfo_pidtof_cylfit_beta_0ps);
   fChain->SetBranchAddress("pfo_pidtof_cylfit_beta_10ps", pfo_pidtof_cylfit_beta_10ps, &b_pfo_pidtof_cylfit_beta_10ps);
   fChain->SetBranchAddress("pfo_pidtof_cylfit_beta_50ps", pfo_pidtof_cylfit_beta_50ps, &b_pfo_pidtof_cylfit_beta_50ps);
   fChain->SetBranchAddress("pfo_pidtof_cylfit_beta_100ps", pfo_pidtof_cylfit_beta_100ps, &b_pfo_pidtof_cylfit_beta_100ps);
   fChain->SetBranchAddress("pfo_pidtof_closestfit_beta_0ps", pfo_pidtof_closestfit_beta_0ps, &b_pfo_pidtof_closestfit_beta_0ps);
   fChain->SetBranchAddress("pfo_pidtof_closestfit_beta_10ps", pfo_pidtof_closestfit_beta_10ps, &b_pfo_pidtof_closestfit_beta_10ps);
   fChain->SetBranchAddress("pfo_pidtof_closestfit_beta_50ps", pfo_pidtof_closestfit_beta_50ps, &b_pfo_pidtof_closestfit_beta_50ps);
   fChain->SetBranchAddress("pfo_pidtof_closestfit_beta_100ps", pfo_pidtof_closestfit_beta_100ps, &b_pfo_pidtof_closestfit_beta_100ps);
   Notify();
}

Bool_t preselection_2023::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void preselection_2023::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t preselection_2023::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef preselection_2023_cxx
