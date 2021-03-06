// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <sys/stat.h>

#include <cloudabi_syscalls.h>
#include <errno.h>

#include "stat_impl.h"

int fstat(int fildes, struct stat *buf) {
  cloudabi_filestat_t internal_stat;
  cloudabi_errno_t error = cloudabi_sys_file_stat_fget(fildes, &internal_stat);
  if (error != 0) {
    errno = error;
    return -1;
  }
  to_public_stat(&internal_stat, buf);
  return 0;
}
