#pragma once

#include "third_party/parallel_hashmap/phmap.h"
#include "third_party/parallel_hashmap/phmap_dump.h"
#include <cstdint>
#include <optional>
#include <string>

namespace index_lib {

static const uint32_t kInvalidDocId = static_cast<uint32_t>(-1);

class InvertIndex {
public:
  InvertIndex(const std::string &path) : path_(path), index_(){};
  ~InvertIndex(){};

  bool Load() {
    phmap::BinaryInputArchive ar_in(path_.c_str());
    return index_.phmap_load(ar_in);
  };

  bool Dump() {
    phmap::BinaryOutputArchive ar_out(path_.c_str());
    return index_.phmap_dump(ar_out);
  };

  uint32_t GetDocId(uint64_t item_id) {
    auto it = index_.find(item_id);
    if (it == index_.end()) {
      return kInvalidDocId;
    }
    return it->second;
  };
  bool SetDocId(uint64_t item_id, uint32_t doc_id) {
    auto ret = index_.emplace(item_id, doc_id);
    return ret.second;
  };

private:
  std::string path_;
  phmap::parallel_flat_hash_map<uint64_t, uint32_t> index_;
};

class RevertIndex {};
} // namespace index_lib
