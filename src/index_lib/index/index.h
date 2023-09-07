#pragma once

#include "index_lib/defines.h"
#include "third_party/parallel_hashmap/phmap.h"
#include "third_party/parallel_hashmap/phmap_dump.h"
#include <atomic>
#include <cstdint>
#include <gflags/gflags.h>
#include <optional>
#include <string>
#include <unistd.h>

namespace index_lib {

class InvertIndex {
public:
  InvertIndex(const std::string &path) : path_(path), index_(){};
  ~InvertIndex(){};

  bool Load() {
    if (access(path_.c_str(), 4) == 0) {
      phmap::BinaryInputArchive ar_in(path_.c_str());
      return index_.phmap_load(ar_in);
    }
    return true;
  };

  bool Dump() {
    phmap::BinaryOutputArchive ar_out(path_.c_str());
    return index_.phmap_dump(ar_out);
  };

  uint32_t GetDoc(uint64_t item_id) {
    auto it = index_.find(item_id);
    if (it == index_.end()) {
      return kInvalidDocId;
    }
    return it->second;
  };

  // return false if item_id exist
  bool AddDoc(uint64_t item_id, uint32_t doc_id) {
    auto ret = index_.emplace(item_id, doc_id);
    if (!ret.second || ret.first == index_.end()) {
      return false;
    }
    return true;
  };

private:
  std::string path_;
  phmap::parallel_flat_hash_map<uint64_t, uint32_t> index_;
};

} // namespace index_lib
