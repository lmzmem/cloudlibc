// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <testing.h>
#include <uchar.h>

TEST(c32rtomb, ascii) {
  char c;

  // Valid characters.
  ASSERT_EQ(1, c32rtomb(&c, U'A', NULL));
  ASSERT_EQ('A', c);
  ASSERT_EQ(1, c32rtomb(&c, U'\0', NULL));
  ASSERT_EQ('\0', c);

  // Characters cannot be expressed as ASCII.
  ASSERT_EQ((size_t)-1, c32rtomb(&c, U'€', NULL));
  ASSERT_EQ(EILSEQ, errno);

  // Surrogate pair. Should not be allowed.
  ASSERT_EQ((size_t)-1, c32rtomb(&c, 0xd801, NULL));
  ASSERT_EQ(EILSEQ, errno);
}

TEST(c32rtomb, unicode) {
  char buf[MB_LEN_MAX];

  // Valid characters.
  ASSERT_EQ(1, c32rtomb_l(buf, U'A', NULL, LC_C_UNICODE_LOCALE));
  ASSERT_EQ('A', buf[0]);
  ASSERT_EQ(1, c32rtomb_l(buf, U'\0', NULL, LC_C_UNICODE_LOCALE));
  ASSERT_EQ('\0', buf[0]);
  ASSERT_EQ(3, c32rtomb_l(buf, U'€', NULL, LC_C_UNICODE_LOCALE));
  ASSERT_ARREQ("€", buf, 3);

  // Surrogate pair. Should not be allowed.
  ASSERT_EQ((size_t)-1, c32rtomb_l(buf, 0xd801, NULL, LC_C_UNICODE_LOCALE));
  ASSERT_EQ(EILSEQ, errno);
}
