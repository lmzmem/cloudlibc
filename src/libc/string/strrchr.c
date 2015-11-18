// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <string.h>

char *strrchr(const char *s, int c) {
  char *last = NULL;
  for (;;) {
    if (*s == (char)c)
      last = (char *)s;
    if (*s++ == '\0')
      return last;
  }
}
