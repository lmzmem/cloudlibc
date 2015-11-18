// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/syscalls.h>

#include <sys/mman.h>

#include <errno.h>

int munmap(void *addr, size_t len) {
  cloudabi_errno_t error = cloudabi_sys_mem_unmap(addr, len);
  if (error != 0) {
    errno = error;
    return -1;
  }
  return 0;
}
