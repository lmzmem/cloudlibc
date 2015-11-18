// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/locale.h>

#include <locale.h>
#include <stdio.h>

int vdprintf(int fildes, const char *restrict format, va_list ap) {
  DEFAULT_LOCALE(locale, LC_CTYPE_MASK | LC_NUMERIC_MASK);
  return vdprintf_l(fildes, locale, format, ap);
}
