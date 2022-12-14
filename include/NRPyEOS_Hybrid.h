#ifndef NRPYEOS_HYBRID_H_
#define NRPYEOS_HYBRID_H_

#include "GRHayL.h"

int NRPyEOS_find_polytropic_index(
      const eos_parameters *restrict eos,
      const double rho_in);

void NRPyEOS_get_K_and_Gamma(
      const eos_parameters *restrict eos,
      const double rho_in,
      double *restrict K,
      double *restrict Gamma);

void NRPyEOS_set_K_ppoly_and_eps_integ_consts(eos_parameters *restrict eos);

void NRPyEOS_compute_P_cold(
      const struct eos_parameters *restrict eos,
      const double rho_in,
      double *restrict P_cold_ptr);

void NRPyEOS_compute_P_cold_and_eps_cold(
      const struct eos_parameters *restrict eos,
      const double rho_in,
      double *restrict P_cold_ptr,
      double *restrict eps_cold_ptr);

void NRPyEOS_compute_entropy_function(
      const struct eos_parameters *restrict eos,
      const double rho,
      const double P,
      double *restrict S );

void NRPyEOS_initialize_hybrid_functions(eos_parameters *restrict eos);

#endif // NRPYEOS_HYBRID_H_
