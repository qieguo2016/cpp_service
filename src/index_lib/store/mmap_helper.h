#pragma once

#include <cerrno>
#include <errno.h>
#include <iostream>
#include <ostream>
#include <sys/mman.h>

static int mmap_helper(void **ret, void *addr, size_t length, int prot,
                       int flags, int fd, off_t offset) {
  *ret = mmap(addr, length, prot, flags, fd, offset);
  if (ret == MAP_FAILED) {
    if ((flags & MAP_HUGETLB) && EINVAL == errno) {
      flags &= ~MAP_HUGETLB;
      *ret = mmap(addr, length, prot, flags, fd, offset);
    }
  }
  // MADV_DONTDUMP: don't dump memory while coredump
  if (madvise(addr, length, MADV_DONTDUMP) != 0) {
    std::cerr << "Failed to set madvise, errno=" << errno
              << ", length=" << length << std::endl;
  }

  if (*ret == MAP_FAILED) {
    return errno;
  }
  return 0;
}