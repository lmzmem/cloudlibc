// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <stdio.h>

#ifndef setbuf
#error "setbuf is supposed to be a macro as well"
#endif

// clang-format off
void (setbuf)(FILE *restrict stream, char *restrict buf) {
  setbuf(stream, buf);
}
