// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <string.h>
#include <testing.h>

TEST(memcmp, null) {
  ASSERT_EQ(0, memcmp(NULL, NULL, 0));
}

TEST(memcmp, example) {
  const char buf1[] = "Hello";
  const char buf2[] = "Helxo";
  ASSERT_EQ(0, memcmp(buf1, buf1, sizeof(buf1)));
  ASSERT_GT(0, memcmp(buf1, buf2, sizeof(buf1)));
  ASSERT_LT(0, memcmp(buf2, buf1, sizeof(buf1)));
}
