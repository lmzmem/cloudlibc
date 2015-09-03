// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

noreturn void __assertion_failed(const char *func, int line,
                                 const char *expression) {
  fprintf(stderr, "%s():%d: assertion failed: %s\n", func, line, expression);
  abort();
}
