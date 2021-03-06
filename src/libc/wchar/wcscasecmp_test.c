// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <testing.h>
#include <wchar.h>

TEST(wcscasecmp, example) {
  ASSERT_EQ(0, wcscasecmp(L"hello", L"hello"));
  ASSERT_EQ(0, wcscasecmp(L"hElLo", L"hello"));

  ASSERT_GT(0, wcscasecmp(L"doge", L"dogS"));
  ASSERT_LT(0, wcscasecmp(L"dogs", L"dogE"));

  ASSERT_LT(0, wcscasecmp(L"München?", L"MÜNCHEN!"));
  ASSERT_EQ(0, wcscasecmp(L"München", L"MÜNCHEN"));
}
