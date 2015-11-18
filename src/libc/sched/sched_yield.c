// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/syscalls.h>

#include <errno.h>
#include <sched.h>

int sched_yield(void) {
  cloudabi_errno_t error = cloudabi_sys_thread_yield();
  if (error != 0) {
    errno = error;
    return -1;
  }
  return 0;
}
