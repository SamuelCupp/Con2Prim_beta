#include "NRPyEOS_Tabulated.h"

void NRPyEOS_initialize_tabulated_functions(eos_parameters *restrict eos) {
  eos->tabulated_read_table_set_EOS_params              = &NRPyEOS_read_table_set_EOS_params;
  eos->tabulated_free_memory                            = &NRPyEOS_free_memory;
  eos->tabulated_compute_P_from_T                       = &NRPyEOS_P_from_rho_Ye_T;
  eos->tabulated_compute_eps_from_T                     = &NRPyEOS_eps_from_rho_Ye_T;
  eos->tabulated_compute_P_eps_from_T                   = &NRPyEOS_P_and_eps_from_rho_Ye_T;
  eos->tabulated_compute_P_eps_S_from_T                 = &NRPyEOS_P_eps_and_S_from_rho_Ye_T;
  eos->tabulated_compute_P_eps_S_cs2_from_T             = &NRPyEOS_P_eps_S_and_cs2_from_rho_Ye_T;
  eos->tabulated_compute_P_eps_depsdT_from_T            = &NRPyEOS_P_eps_and_depsdT_from_rho_Ye_T;
  eos->tabulated_compute_P_eps_muhat_mue_mup_mun_from_T = &NRPyEOS_P_eps_muhat_mue_mup_and_mun_from_rho_Ye_T;
  eos->tabulated_compute_muhat_mue_mup_mun_Xn_Xp_from_T = &NRPyEOS_muhat_mue_mup_mun_Xn_and_Xp_from_rho_Ye_T;
  eos->tabulated_compute_P_T_from_eps                   = &NRPyEOS_P_and_T_from_rho_Ye_eps;
  eos->tabulated_compute_P_S_depsdT_T_from_eps          = &NRPyEOS_P_S_depsdT_and_T_from_rho_Ye_eps;
  eos->tabulated_compute_eps_S_T_from_P                 = &NRPyEOS_eps_S_and_T_from_rho_Ye_P;
  eos->tabulated_compute_P_eps_T_from_S                 = &NRPyEOS_P_eps_and_T_from_rho_Ye_S;
}
