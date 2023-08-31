#pragma once

#include "mmap_helper.h"
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace index_lib {
class FixedMemStore {
public:
  FixedMemStore(std::string path, int file_size, int row_size)
      : path_(path), file_size_(file_size), row_size_(row_size), fd_(0),
        data_(){};

  ~FixedMemStore() {
    if (fd_ != 0) {
      munmap(data_, file_size_);
      close(fd_);
    }
  }

  inline const char *GetFixedRow(const u_int32_t doc_id) {
    return (char *)data_ + doc_id * row_size_;
  }

  inline char *GetMutableFixedRow(const u_int32_t doc_id) {
    return (char *)data_ + doc_id * row_size_;
  }

  // todo: use write mode flag, online reading no write back to file
  int Load() {
    fd_ = open(path_.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd_ == -1) {
      return -1;
    }

    if (ftruncate(fd_, file_size_) == -1) {
      std::cerr << "ftruncate fail" << std::endl;
      return -1;
    }

    // todo: enable hugetlb use gflag
    int err = mmap_helper(&data_, nullptr, file_size_, PROT_READ | PROT_WRITE,
                          MAP_LOCKED | MAP_SHARED | MAP_POPULATE, fd_, 0);
    if (err != 0) {
      return err;
    }
    return 0;
  };

private:
  std::string path_;
  int file_size_; // in byte
  int row_size_;  // in byte
  int fd_;
  void *data_;
};
} // namespace index_lib
