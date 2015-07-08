// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#ifndef COMMON_ARGDATA_H
#define COMMON_ARGDATA_H

#include <sys/types.h>

#include <argdata.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>

struct __argdata {
  enum { AD_BUFFER, AD_BINARY, AD_MAP, AD_SEQ, AD_STR } type;
  union {
    const uint8_t *buffer;  // Buffer to code.
    const void *binary;     // Binary block of data.
    const char *str;        // UTF-8 string.
    struct {
      argdata_t const *const *keys;
      argdata_t const *const *values;
      size_t count;
    } map;  // Map.
    struct {
      argdata_t const *const *entries;
      size_t count;
    } seq;  // Sequence.
  };
  // Length of the resulting binary code.
  size_t length;
};

enum {
  ADT_BINARY = 1,    // A sequence of zero or more octets.
  ADT_BOOL = 2,      // Mathematical Booleans.
  ADT_FD = 3,        // Extension to YAML: file descriptor.
  ADT_FLOAT = 4,     // Floating-point approximation to real numbers.
  ADT_INT = 5,       // Mathematical integers.
  ADT_MAP = 6,       // Unordered set of key: value pairs without duplicates.
  ADT_SEQ = 7,       // Sequence of arbitrary values.
  ADT_STR = 8,       // A sequence of zero or more Unicode characters.
  ADT_TIMESTAMP = 9  // A point in time.
};

static inline void argdata_init_buffer(argdata_t *ad, const void *buffer,
                                       size_t length) {
  ad->type = AD_BUFFER;
  ad->buffer = buffer;
  ad->length = length;
}

// Parses a field embedded in the input stream.
static inline int parse_subfield(argdata_t *ad, const uint8_t **bufp,
                                 size_t *lenp) {
  // Parse the field length. The length is stored in big endian form,
  // seven bits per byte. The top bit is used to indicate whether the
  // last byte of the field length has been reached.
  const uint8_t *buf = *bufp;
  size_t len = *lenp;

  // Disallow overlong encodings.
  if (len == 0 || *buf == 0)
    return EINVAL;

  size_t reclen = 0;
  for (;;) {
    // Fetch digit.
    if (len-- == 0)
      return EINVAL;
    uint8_t c = *buf++;

    // Make space to fit the digit.
    if (reclen >> (sizeof(reclen) * CHAR_BIT - 7) != 0)
      return EINVAL;
    reclen <<= 7;

    if ((c & 0x80) != 0) {
      // Last byte.
      reclen |= c & 0x7f;
      break;
    } else {
      // More bytes to come.
      reclen |= c;
    }
  }
  if (reclen > len)
    return EINVAL;

  // Successfully obtained a subfield.
  argdata_init_buffer(ad, buf, reclen);
  *bufp = buf + reclen;
  *lenp = len - reclen;
  return 0;
}

// Computes the total size of a subfield, including the length that is
// prefixed to it.
static inline size_t get_subfield_length(const argdata_t *ad) {
  size_t total = ad->length;
  size_t field = ad->length;
  do {
    ++total;
    field >>= 7;
  } while (field != 0);
  return total;
}

// Encodes the length of a field and stores it in an output buffer.
static inline void encode_subfield_length(const argdata_t *ad, uint8_t **buf) {
  uint8_t digits[sizeof(size_t) * CHAR_BIT / 7 + 1];
  uint8_t *start = digits + sizeof(digits);
  size_t len = ad->length;
  *--start = len | 0x80;
  for (;;) {
    len >>= 7;
    if (len == 0)
      break;
    *--start = len & 0x7f;
  }
  size_t digitslen = digits + sizeof(digits) - start;
  memcpy(*buf, start, digitslen);
  *buf += digitslen;
}

// Parses a type byte in the input stream.
static inline int parse_type(uint8_t type, const uint8_t **buf, size_t *len) {
  if (*len < 1 || **buf != type)
    return EINVAL;
  ++*buf;
  --*len;
  return 0;
}

// Parses a file descriptor number in the input stream.
static inline int parse_fd(int *value, const uint8_t **buf, size_t *len) {
  if (*len != sizeof(uint32_t))
    return EINVAL;
  uint32_t fd = (uint32_t)(*buf)[0] << 24 | (uint32_t)(*buf)[1] << 16 |
                (uint32_t)(*buf)[2] << 8 | (uint32_t)(*buf)[3];
  if (fd > INT_MAX)
    return EINVAL;
  *value = fd;
  *buf += sizeof(uint32_t);
  *len = 0;
  return 0;
}

static inline void encode_fd(int value, uint8_t **buf) {
  *(*buf)++ = value >> 24;
  *(*buf)++ = value >> 16;
  *(*buf)++ = value >> 8;
  *(*buf)++ = value;
}

// Validates whether a string uses valid UTF-8.
static inline int validate_string(const char *buf, size_t len) {
  // TODO(ed): Any way we can prevent pulling in the entire locale?
  locale_t locale = LC_C_UNICODE_LOCALE;
  mbstate_t mbs;
  memset(&mbs, '\0', sizeof(mbs));
  while (len > 0) {
    ssize_t clen = mbrtowc_l(NULL, buf, len, &mbs, locale);
    if (clen <= 0) {
      if (clen < 0)
        return EILSEQ;
      // Skip null bytes.
      clen = 1;
    }
    buf += clen;
    len -= clen;
  }
  return 0;
}

#endif
