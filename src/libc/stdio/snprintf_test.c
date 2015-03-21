// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <fenv.h>
#include <float.h>
#include <locale.h>
#include <stdio.h>
#include <testing.h>

TEST(snprintf, null) {
  ASSERT_EQ(12, snprintf(NULL, 0, "Hello, world"));
}

TEST(snprintf, null_string) {
  char buf[14];
  char *ptr = NULL;
  ASSERT_EQ(13, snprintf(buf, sizeof(buf), "Hello%.3sworld", ptr));
  ASSERT_STREQ("Hello(nuworld", buf);
}

TEST(snprintf, truncation) {
  char buf[10];
  ASSERT_EQ(12, snprintf(buf, sizeof(buf), "Hello, world"));
  ASSERT_STREQ("Hello, wo", buf);
}

TEST(snprintf, number_width_precision_left) {
  char buf[30];
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%20.10d", 5));
  ASSERT_STREQ("          0000000005", buf);
}

TEST(snprintf, number_width_precision_right) {
  char buf[30];
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%-20.10d", 5));
  ASSERT_STREQ("0000000005          ", buf);
}

TEST(snprintf, grouping_en_us) {
  locale_t locale = newlocale(LC_NUMERIC_MASK, "en_US", 0);
  ASSERT_NE(0, locale);
  char buf[21];
  ASSERT_EQ(20, snprintf_l(buf, sizeof(buf), locale, "%'020d", 12345678));
  ASSERT_STREQ("000000000012,345,678", buf);
  freelocale(locale);
}

#if 0
TEST(snprintf, grouping_ru_ru) {
  locale_t locale = newlocale(LC_NUMERIC_MASK, "ru_RU", 0);
  ASSERT_NE(0, locale);
  char buf[21];
  ASSERT_EQ(20, snprintf_l(buf, sizeof(buf), locale, "%'020d", -123456789));
  ASSERT_STREQ("-00000000123 456 789", buf);
  freelocale(locale);
}
#endif

TEST(snprintf, numbered_arguments) {
  char buf[4];
  ASSERT_EQ(3, snprintf(buf, sizeof(buf), "%2$d %1$d", 5, 7));
  ASSERT_STREQ("7 5", buf);
}

TEST(snprintf, hex_left) {
  char buf[21];
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%-#20.10x", 0x1337));
  ASSERT_STREQ("0x0000001337        ", buf);
}

TEST(snprintf, hex_right) {
  char buf[21];
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%#20.10x", 0x1337));
  ASSERT_STREQ("        0x0000001337", buf);
}

TEST(snprintf, octal1) {
  char buf[2];
  ASSERT_EQ(1, snprintf(buf, sizeof(buf), "%o", 1));
  ASSERT_STREQ("1", buf);
}

TEST(snprintf, octal2) {
  char buf[3];
  ASSERT_EQ(2, snprintf(buf, sizeof(buf), "%#o", 1));
  ASSERT_STREQ("01", buf);
}

#if 0
TEST(snprintf, float16_simple_zero) {
  char buf[7];
  ASSERT_EQ(6, snprintf(buf, sizeof(buf), "%a", 0.0));
  ASSERT_STREQ("0x0p+0", buf);
}

TEST(snprintf, float16_simple_one) {
  char buf[7];
  ASSERT_EQ(6, snprintf(buf, sizeof(buf), "%a", 1.0));
  ASSERT_STREQ("0x1p+0", buf);
}
#endif

TEST(snprintf, float16_simple_number) {
  char buf[16];
  ASSERT_EQ(15, snprintf(buf, sizeof(buf), "%a", 0x1234.5678p12));
  ASSERT_STREQ("0x1.2345678p+24", buf);
}

TEST(snprintf, float16_negative) {
  char buf[17];
  ASSERT_EQ(16, snprintf(buf, sizeof(buf), "%a", -0x1234.5678p12));
  ASSERT_STREQ("-0x1.2345678p+24", buf);
}

TEST(snprintf, float16_round) {
  char buf[21];
  ASSERT_EQ(0, fesetround(FE_DOWNWARD));
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%.2a %.2a", 1.51, -1.51));
  ASSERT_STREQ("0x1.82p+0 -0x1.83p+0", buf);
  ASSERT_EQ(0, fesetround(FE_TONEAREST));
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%.2a %.2a", 1.51, -1.51));
  ASSERT_STREQ("0x1.83p+0 -0x1.83p+0", buf);
  ASSERT_EQ(0, fesetround(FE_TOWARDZERO));
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%.2a %.2a", 1.51, -1.51));
  ASSERT_STREQ("0x1.82p+0 -0x1.82p+0", buf);
  ASSERT_EQ(0, fesetround(FE_UPWARD));
  ASSERT_EQ(20, snprintf(buf, sizeof(buf), "%.2a %.2a", 1.51, -1.51));
  ASSERT_STREQ("0x1.83p+0 -0x1.82p+0", buf);
}

TEST(snprintf, float16_align) {
  char buf[31];
  ASSERT_EQ(30, snprintf(buf, sizeof(buf), "%#30.15a", 0x12.345p12));
  ASSERT_STREQ("       0x1.234500000000000p+16", buf);
}

#if 0
TEST(snprintf, float16_subnormal) {
#if LDBL_MANT_DIG == 64
  char buf[11];
  ASSERT_EQ(10, snprintf(buf, sizeof(buf), "%La", LDBL_TRUE_MIN));
  ASSERT_STREQ("0x1p-16445", buf);
#else
#error "Unknown floating point type"
#endif
}
#endif
