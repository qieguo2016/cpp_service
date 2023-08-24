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

class FixedMemStore {
public:
  FixedMemStore(int fixed_file_size, int fixed_row_size)
      : fixed_file_size_(fixed_file_size), fixed_row_size_(fixed_row_size),
        fixed_fd_(0), fixed_data_(){};

  ~FixedMemStore() {
    if (fixed_fd_ != 0) {
      munmap(fixed_data_, fixed_file_size_);
      close(fixed_fd_);
    }
  }

   // todo: check doc_id
  inline const char *GetFixedRow(const u_int32_t doc_id) {
    return (char *)fixed_data_ + doc_id * fixed_row_size_;
  }

  inline char *GetMutableFixedRow(const u_int32_t doc_id) {
    return (char *)fixed_data_ + doc_id * fixed_row_size_;
  }

  int load(std::string path) { return _load_fixed_data(path); };

  template <typename T> T *get(const u_int32_t doc_id) {
    return (T *)GetFixedRow(doc_id);
  }

  template <typename T> bool set(u_int32_t doc_id, T value) {
    T *pointer = (T *)GetMutableFixedRow(doc_id);
    std::cout << fixed_data_
              << ", doc_id*fixed_row_size_: " << doc_id * fixed_row_size_
              << std::endl;
    *pointer = value;
    return true;
  }

private:
  int _load_fixed_data(std::string path) {
    // todo: use write mode flag, online reading no write back to file
    fixed_fd_ = open(path.c_str(), O_RDWR | O_CREAT, 0666);
    if (fixed_fd_ == -1) {
      return -1;
    }

    if (ftruncate(fixed_fd_, fixed_file_size_) == -1) {
      std::cerr << "ftruncate fail" << std::endl;
      return -1;
    }

    // todo: enable hugetlb use gflag
    int err = mmap_helper(&fixed_data_, nullptr, fixed_file_size_,
                          PROT_READ | PROT_WRITE,
                          MAP_LOCKED | MAP_SHARED | MAP_POPULATE, fixed_fd_, 0);
    if (err != 0) {
      return err;
    }
    return 0;
  };

private:
  int fixed_file_size_; // in byte
  int fixed_row_size_;  // in byte
  int fixed_fd_;
  void *fixed_data_;
};