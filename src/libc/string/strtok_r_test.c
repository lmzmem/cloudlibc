// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <string.h>
#include <testing.h>

TEST(strtok_r, example) {
  char line[] = "LINE  TO BE\t\tSEPARATED\n";
  const char *split = " \t\n";
  char *lasts;
  ASSERT_STREQ("LINE", strtok_r(line, split, &lasts));
  ASSERT_STREQ("TO", strtok_r(NULL, split, &lasts));
  ASSERT_STREQ("BE", strtok_r(NULL, split, &lasts));
  ASSERT_STREQ("SEPARATED", strtok_r(NULL, split, &lasts));
  ASSERT_EQ(NULL, strtok_r(NULL, split, &lasts));
}
