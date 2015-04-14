// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// <sys/capsicum.h> - file descriptor access controls
//
// Extensions:
// - cap_rights_get_explicit() and cap_rights_limit_explicit():
//   Capabilities are expressed as a pair of base and inheriting rights
//   in this environment.
//
// Features missing:
// - CAP_LOOKUP:
//   TODO(edje): Add.
// - CAP_FCHDIR:
//   Per-process working directory is not available. Use *at() instead.
// - CAP_FCHFLAGS, CAP_CHFLAGSAT, CAP_FCHMOD, CAP_FCHMODAT, CAP_FCHOWN,
//   CAP_FCHOWNAT:
//   Filesystem access control management not available.
// - CAP_FLOCK:
//   File locking not available.
// - CAP_FPATHCONF:
//   TODO(edje): Add.
// - CAP_FSCK:
//   Not applicable to this environment.
// - CAP_FSTATFS:
//   Filesystem-level statistics not available.
// - CAP_MKNODAT:
//   Device nodes cannot be created.
// - CAP_SETSOCKOPT:
//   Socket parameters cannot be adjusted.
// - CAP_MAC_*:
//   Mandatory Access Control not available.
// - CAP_SEM_*:
//   Semaphores are not represented as file descriptors.
// - CAP_IOCTL and cap_ioctls_*():
//   ioctl() not available.
// - CAP_FCNTL and cap_fcntl_*():
//   fcntl() can always be used.
// - CAP_TTYHOOK:
//   Terminal management is not available.
// - CAP_PDGETPID:
//   Process identifiers are not exposed.
// - CAP_PDKILL:
//   Explicit signal delivery is not supported.
// - CAP_EXTATTR_*:
//   Extended inode attributes not available.
// - CAP_ACL_*:
//   Access Control Lists not available.

#ifndef _SYS_CAPSICUM_H_
#define _SYS_CAPSICUM_H_

#include <_/limits.h>
#include <_/types.h>

typedef __uint64_t __cap_rights_bits_t;
typedef struct { __cap_rights_bits_t __value; } cap_rights_t;

#define _CAP_BIT(f) (_UINT64_C(1) << (f))
#define _CAP_SENTINEL _UINT64_C(0)

// General file I/O.
#define CAP_CREATE (_CAP_BIT(10) | _CAP_BIT(13))
#define CAP_FEXECVE _CAP_BIT(30)
#define CAP_FSYNC (_CAP_BIT(0) | _CAP_BIT(4))
#define CAP_FTRUNCATE _CAP_BIT(18)
#define CAP_MMAP _CAP_BIT(24)
#define CAP_MMAP_R (CAP_MMAP | CAP_READ)
#define CAP_MMAP_RW (CAP_MMAP_R | CAP_MMAP_W)
#define CAP_MMAP_RWX (CAP_MMAP_R | CAP_MMAP_W | CAP_MMAP_X)
#define CAP_MMAP_RX (CAP_MMAP_R | CAP_MMAP_X)
#define CAP_MMAP_W (CAP_MMAP | CAP_WRITE)
#define CAP_MMAP_WX (CAP_MMAP_W | CAP_MMAP_X)
#define CAP_MMAP_X (CAP_MMAP | _CAP_BIT(25))
#define CAP_PREAD (CAP_READ | _CAP_BIT(2))
#define CAP_PWRITE (CAP_WRITE | _CAP_BIT(2))
#define CAP_READ _CAP_BIT(1)
#define CAP_SEEK (CAP_SEEK_TELL | _CAP_BIT(2))
#define CAP_SEEK_TELL _CAP_BIT(5)
#define CAP_WRITE _CAP_BIT(6)

// VFS methods.
#define CAP_BINDAT _CAP_BIT(32)
#define CAP_CONNECTAT _CAP_BIT(34)
#define CAP_FSTAT _CAP_BIT(17)
#define CAP_FSTATAT _CAP_BIT(20)
#define CAP_FUTIMES _CAP_BIT(19)
#define CAP_FUTIMESAT _CAP_BIT(21)
#define CAP_LINKAT _CAP_BIT(12)
#define CAP_MKDIRAT _CAP_BIT(9)
#define CAP_MKFIFOAT _CAP_BIT(11)
#define CAP_RENAMEAT _CAP_BIT(16)
#define CAP_SYMLINKAT _CAP_BIT(22)
#define CAP_UNLINKAT _CAP_BIT(23)

// Socket operations.
#define CAP_ACCEPT _CAP_BIT(31)
#define CAP_BIND _CAP_BIT(33)
#define CAP_CONNECT _CAP_BIT(35)
#define CAP_GETPEERNAME CAP_GETSOCKOPT
#define CAP_GETSOCKNAME CAP_GETSOCKOPT
#define CAP_GETSOCKOPT _CAP_BIT(38)
#define CAP_LISTEN _CAP_BIT(36)
#define CAP_RECV CAP_READ
#define CAP_SEND CAP_WRITE
#define CAP_SHUTDOWN _CAP_BIT(37)

// Commonly used socket operations.
#define CAP_SOCK_CLIENT                                               \
  (CAP_CONNECT | CAP_GETPEERNAME | CAP_GETSOCKNAME | CAP_GETSOCKOPT | \
   CAP_RECV | CAP_SEND | CAP_SHUTDOWN)
#define CAP_SOCK_SERVER                                        \
  (CAP_ACCEPT | CAP_BIND | CAP_GETPEERNAME | CAP_GETSOCKNAME | \
   CAP_GETSOCKOPT | CAP_LISTEN | CAP_RECV | CAP_SEND | CAP_SHUTDOWN)

// Polling.
#define CAP_EVENT _CAP_BIT(26)
#define CAP_KQUEUE (CAP_KQUEUE_EVENT | CAP_KQUEUE_CHANGE)
#define CAP_KQUEUE_CHANGE _CAP_BIT(27)
#define CAP_KQUEUE_EVENT _CAP_BIT(29)

// Process descriptors.
#define CAP_PDWAIT _CAP_BIT(28)

#define cap_rights_clear(rights, ...) \
  __cap_rights_clear(rights, ##__VA_ARGS__, _CAP_SENTINEL)
#define cap_rights_init(rights, ...) \
  __cap_rights_init(rights, ##__VA_ARGS__, _CAP_SENTINEL)
#define cap_rights_is_set(rights, ...) \
  __cap_rights_is_set(rights, ##__VA_ARGS__, _CAP_SENTINEL)
#define cap_rights_set(rights, ...) \
  __cap_rights_set(rights, ##__VA_ARGS__, _CAP_SENTINEL)

__BEGIN_DECLS
cap_rights_t *__cap_rights_clear(cap_rights_t *, ...);
cap_rights_t *__cap_rights_init(cap_rights_t *, ...);
_Bool __cap_rights_is_set(const cap_rights_t *, ...);
cap_rights_t *__cap_rights_set(cap_rights_t *, ...);
int cap_enter(void);
int cap_getmode(unsigned int *);
_Bool cap_rights_contains(const cap_rights_t *, const cap_rights_t *);
int cap_rights_get(int, cap_rights_t *);
int cap_rights_get_explicit(int, cap_rights_t *, cap_rights_t *);
int cap_rights_limit(int, const cap_rights_t *);
int cap_rights_limit_explicit(int, const cap_rights_t *, const cap_rights_t *);
cap_rights_t *cap_rights_merge(cap_rights_t *, const cap_rights_t *);
cap_rights_t *cap_rights_remove(cap_rights_t *, const cap_rights_t *);
_Bool cap_sandboxed(void);
__END_DECLS

#endif
