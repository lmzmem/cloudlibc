// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <fenv.h>
#include <testing.h>

TEST(feupdateenv, example) {
  // Come up with a rounding mode and exception state.
  ASSERT_EQ(0, fesetround(FE_TONEAREST));
  ASSERT_EQ(0, feclearexcept(FE_ALL_EXCEPT));
  ASSERT_EQ(0, feraiseexcept(FE_DIVBYZERO));
  fenv_t env;
  ASSERT_EQ(0, fegetenv(&env));

  // Switch to a different rounding mode and exception state.
  ASSERT_EQ(0, fesetround(FE_DOWNWARD));
  ASSERT_EQ(0, feclearexcept(FE_ALL_EXCEPT));
  ASSERT_EQ(0, feraiseexcept(FE_INEXACT));

  // feupdateenv() should restore the rounding mode and union the exceptions.
  ASSERT_EQ(0, feupdateenv(&env));
  ASSERT_EQ(FE_TONEAREST, fegetround());
  ASSERT_EQ(FE_DIVBYZERO | FE_INEXACT, fetestexcept(FE_ALL_EXCEPT));
}
