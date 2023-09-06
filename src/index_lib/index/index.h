#pragma once

#include "third_party/parallel_hashmap/phmap.h"
#include "third_party/parallel_hashmap/phmap_dump.h"
#include <atomic>
#include <cstdint>
#include <gflags/gflags.h>
#include <optional>
#include <string>
#include <unistd.h>

namespace index_lib {

struct DocInfo {
  uint32_t doc_id;
  uint32_t var_addr;
  uint32_t version; // 循环使用
};

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

  DocInfo *GetDoc(uint64_t item_id) {
    auto it = index_.find(item_id);
    if (it == index_.end()) {
      return nullptr;
    }
    return &it->second;
  };

  // return nullptr if item_id exist
  DocInfo *AddDoc(uint64_t item_id, uint32_t doc_id) {
    auto ret = index_.emplace(item_id, DocInfo{doc_id, 0, 0});
    if (!ret.second || ret.first == index_.end()) {
      return nullptr;
    }
    return &ret.first->second;
  };

  DocInfo *AddDoc(uint64_t item_id, uint32_t doc_id, uint32_t var_addr,
                  uint32_t version) {
    auto ret = index_.emplace(item_id, DocInfo{doc_id, var_addr, version});
    if (!ret.second || ret.first == index_.end()) {
      return nullptr;
    }
    return &ret.first->second;
  };

private:
  std::string path_;
  phmap::parallel_flat_hash_map<uint64_t, DocInfo> index_;
};

} // namespace index_lib
