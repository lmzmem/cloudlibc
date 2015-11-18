// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <errno.h>
#include <string.h>
#include <time.h>

#include "time_impl.h"

time_t mktime(struct tm *tm) {
  // Convert unsanitized struct tm to a struct timespec.
  struct timespec result;
  __mktime_utc(tm, &result);

  // Convert struct timespec back to a sanitized struct tm.
  int error = __localtime_utc(result.tv_sec, tm);
  strlcpy(tm->tm_zone, "UTC", sizeof(tm->tm_zone));
  tm->tm_nsec = result.tv_nsec;

  // Only return number of seconds since the Epoch.
  if (error != 0) {
    errno = error;
    return -1;
  }
  return result.tv_sec;
}

__strong_reference(mktime, timegm);
