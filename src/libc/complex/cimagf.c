// Copyright (c) 2016 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <complex.h>

float cimagf(float complex z) {
  return __imag__(z);
}
