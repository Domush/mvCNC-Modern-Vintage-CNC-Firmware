/**
 * Modern Vintage CNC Firmware
*/
#pragma once

/**
 * Incremental Least Squares Best Fit  By Roxy and Ed Williams
 *
 * This algorithm is high speed and has a very small code footprint.
 * Its results are identical to both the Iterative Least-Squares published
 * earlier by Roxy and the QR_SOLVE solution. If used in place of QR_SOLVE
 * it saves roughly 10K of program memory.   And even better...  the data
 * fed into the algorithm does not need to all be present at the same time.
 * A point can be probed and its values fed into the algorithm and then discarded.
 */

#include "../inc/mvCNCConfig.h"
#include <math.h>

struct linear_fit_data {
  float xbar, ybar, zbar,
        x2bar, y2bar,
        xybar, xzbar, yzbar,
        max_absx, max_absy,
        A, B, D, N;
};

inline void incremental_LSF_reset(struct linear_fit_data *lsf) {
  memset(lsf, 0, sizeof(linear_fit_data));
}

inline void incremental_WLSF(struct linear_fit_data *lsf, const_float_t x, const_float_t y, const_float_t z, const_float_t w) {
  // weight each accumulator by factor w, including the "number" of samples
  // (analogous to calling inc_LSF twice with same values to weight it by 2X)
  const float wx = w * x, wy = w * y, wz = w * z;
  lsf->xbar  += wx;
  lsf->ybar  += wy;
  lsf->zbar  += wz;
  lsf->x2bar += wx * x;
  lsf->y2bar += wy * y;
  lsf->xybar += wx * y;
  lsf->xzbar += wx * z;
  lsf->yzbar += wy * z;
  lsf->N     += w;
  lsf->max_absx = _MAX(ABS(wx), lsf->max_absx);
  lsf->max_absy = _MAX(ABS(wy), lsf->max_absy);
}
inline void incremental_WLSF(struct linear_fit_data *lsf, const xy_pos_t &pos, const_float_t z, const_float_t w) {
  incremental_WLSF(lsf, pos.x, pos.y, z, w);
}

inline void incremental_LSF(struct linear_fit_data *lsf, const_float_t x, const_float_t y, const_float_t z) {
  lsf->xbar += x;
  lsf->ybar += y;
  lsf->zbar += z;
  lsf->x2bar += sq(x);
  lsf->y2bar += sq(y);
  lsf->xybar += x * y;
  lsf->xzbar += x * z;
  lsf->yzbar += y * z;
  lsf->max_absx = _MAX(ABS(x), lsf->max_absx);
  lsf->max_absy = _MAX(ABS(y), lsf->max_absy);
  lsf->N += 1.0;
}
inline void incremental_LSF(struct linear_fit_data *lsf, const xy_pos_t &pos, const_float_t z) {
  incremental_LSF(lsf, pos.x, pos.y, z);
}

int finish_incremental_LSF(struct linear_fit_data *);
