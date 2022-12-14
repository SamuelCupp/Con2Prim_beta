#include <stdio.h>
#include "con2prim.h"

/* Function    : limit_utilde_and_compute_v()
 * Authors     : Samuel Cupp
 * Description : Initialize the primitives struct from user
 *               input
 * Dependencies: None
 *
 * Inputs      : eos             - an initialized eos_parameters struct
 *                                 with data for the EOS of the simulation
 *             : metric          - an initialized metric_quantities struct
 *                                 with data for the gridpoint of interest
 *             : u0_ptr          - an initialized conservative_quantities
 *                                 struct with data for the gridpoint of
 *                                 interest
 *             : utcon1_ptr      - pointer to the x component of u tilde
 *             : utcon2_ptr      - pointer to the y component of u tilde
 *             : utcon3_ptr      - pointer to the z component of u tilde
 *
 * Outputs     : utcon1_ptr      - if velocity is limited, data of utcon1 is changed
 *             : utcon2_ptr      - if velocity is limited, data of utcon2 is changed
 *             : utcon3_ptr      - if velocity is limited, data of utcon3 is changed
 *             : u0_ptr          -
 *             : prims           - primitive_quantities struct containing the
 *                                 velocities v calculated from the (velocity-
 *                                 limited) u tilde
 *             : diagnostics     - con2prim_diagnostics struct which
 *                                 tracks if the velocity was limited
 */

//Now that we have found some solution, we first limit velocity:
//FIXME: Probably want to use exactly the same velocity limiter function here as in mhdflux.C
void limit_utilde_and_compute_v( const eos_parameters *restrict eos,
                                             const metric_quantities *restrict metric,
                                             double *restrict u0_ptr,
                                             double *restrict utcon1_ptr,
                                             double *restrict utcon2_ptr,
                                             double *restrict utcon3_ptr,
                                             primitive_quantities *restrict prims,
                                             con2prim_diagnostics *restrict diagnostics ) {

  double utcon1 = *utcon1_ptr;
  double utcon2 = *utcon2_ptr;
  double utcon3 = *utcon3_ptr;

  //Velocity limiter:
  double gijuiuj = metric->adm_gxx*SQR(utcon1 ) +
    2.0*metric->adm_gxy*utcon1*utcon2 + 2.0*metric->adm_gxz*utcon1*utcon3 +
    metric->adm_gyy*SQR(utcon2) + 2.0*metric->adm_gyz*utcon2*utcon3 +
    metric->adm_gzz*SQR(utcon3);
  double au0m1 = gijuiuj/( 1.0+sqrt(1.0+gijuiuj) );
  double u0 = (au0m1+1.0)*metric->lapseinv;

  // *** Limit velocity
  if (au0m1 > 0.9999999*(eos->W_max-1.0)) {
    double fac = sqrt((SQR(eos->W_max)-1.0)/(SQR(1.0+au0m1) - 1.0));
    utcon1 *= fac;
    utcon2 *= fac;
    utcon3 *= fac;
    gijuiuj = gijuiuj * SQR(fac);
    au0m1 = gijuiuj/( 1.0+sqrt(1.0+gijuiuj) );
    // Reset rho_b and u0
    u0 = (au0m1+1.0)*metric->lapseinv;
    diagnostics->vel_limited_ptcount=1;
    diagnostics->failure_checker+=1000;
  } //Finished limiting velocity

  *u0_ptr = u0;
  *utcon1_ptr = utcon1;
  *utcon2_ptr = utcon2;
  *utcon3_ptr = utcon3;

  // Calculate v^i from \tilde{u}^i
  prims->vx = utcon1/u0 - metric->betax;
  prims->vy = utcon2/u0 - metric->betay;
  prims->vz = utcon3/u0 - metric->betaz;
}
