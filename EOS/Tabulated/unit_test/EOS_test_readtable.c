#include "NRPyEOS_Tabulated.h"
/*
 * (c) 2022 Leo Werneck
 */
void EOS_test_readtable(const char *EOS_tablepath) {

  printf("(GRHayL - EOS) Beginning readtable unit test\n");

  // Step 1: Initialize the EOS struct
  eos_parameters eos;
  initialize_tabulated_functions(&eos);
  eos.tabulated_read_table_set_EOS_params(EOS_tablepath, &eos);

  printf("(GRHayL - EOS) Table dimensions: rho, T, Ye: %d, %d, %d\n", eos.N_rho, eos.N_T, eos.N_Ye);

  printf("(GRHayL - EOS) Performing one interpolation\n");
  // Step 2: Perform one interpolation
  const double xrho = 1e-6;
  const double xY_e = 0.4;
  const double xT   = 1.1;
  double xP, xeps;
  eos.tabulated_compute_P_eps_from_T(&eos, xrho, xY_e, xT, &xP, &xeps);

  // Step 3: Print information
  printf("(GRHayL - EOS) Input Density    : %.15e\n", xrho);
  printf("(GRHayL - EOS) Input e- fraction: %.15e\n", xY_e);
  printf("(GRHayL - EOS) Input Temperature: %.15e\n", xT);
  printf("(GRHayL - EOS) Output Pressure  : %.15e\n", xP);
  printf("(GRHayL - EOS) Output Energy    : %.15e\n", xeps);

  // Step 4: Free memory
  eos.tabulated_free_memory(&eos);

  printf("(GRHayL - EOS) Test finished successfully.\n");

  // All done!
  exit(0);
}
