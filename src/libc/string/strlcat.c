// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <string.h>

size_t strlcat(char *restrict s1, const char *restrict s2, size_t n) {
  // Skip the part of the destination buffer that is used.
  size_t skipped = 0;
  while (n > 0 && *s1 != '\0') {
    ++s1;
    --n;
    ++skipped;
  }

  // Copy up to n - 1 characters into the destination buffer.
  const char *begin = s2;
  while (n > 1) {
    *s1 = *s2;
    if (*s2 == '\0')
      return s2 - begin + skipped;
    ++s1;
    ++s2;
    --n;
  }

  // Nul-terminate the destination buffer if space is available.
  if (n > 0)
    *s1 = '\0';

  // Continue computing the length of s2.
  while (*s2 != '\0')
    ++s2;
  return s2 - begin + skipped;
}
