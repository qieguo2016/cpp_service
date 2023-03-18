#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
namespace cpp_service {
namespace cache {

size_t GetValidBucketCount(size_t cap) {
  const size_t count = 26;
  static const size_t nums[count] = {
      16,       32,        64,        128,       512,       1024,     2048,
      4096,     8192,      16384,     32768,     65536,     131072,   262144,
      524288,   1048576,   2097152,   4194304,   8388608,   16777216, 33554432,
      67108864, 134217728, 268435456, 536870912, 1073741824};
  size_t i = 0;
  for (i = 0; i < count; i++) {
    if (nums[i] > cap) {
      return nums[i];
    }
  }

  return nums[i];
}

template <typename K, typename V> struct Node {
  Node *next_hash;
  Node *next;
  Node *prev;
  bool in_use;   // Whether entry is in use.
  uint32_t refs; // References, including cache reference, if present.
  uint32_t hash; // Hash of key(); used for fast sharding and comparisons
  uint32_t expire_ts;
  K *key;
  V *value;

  Node(uint32_t hash_, K *key_, V *value_)
      : hash(hash_), key(key_), value(value_) {}
};

template <typename K, typename V> class HashTable {

public:
  using NodeRef = Node<K, V>;

  HashTable(uint32_t cap) : cap_(cap), size_(0), buckets_(nullptr) {
    // 取比cap大的第一个2^n次方
    size_t buckets_count = GetValidBucketCount(cap);
    buckets_ = new NodeRef *[buckets_count];
  };

  ~HashTable() { delete[] buckets_; };

  NodeRef *Lookup(const K &key, uint32_t hash) {
    return *FindPointer(key, hash);
  };

  void Insert(const K &key, uint32_t hash, V &value) {
    NodeRef **ptr = FindPointer(key, hash);
    NodeRef *old = *ptr;
    if (old != nullptr) {
      old->value = &value;
      return;
    }

    NodeRef *node = new NodeRef(hash, const_cast<K *>(&key), &value);
    node->next_hash = (old == nullptr ? nullptr : old->next_hash);
    *ptr = node;
    ++size_;
  };

  void Erase(const K &key, uint32_t hash) {
    NodeRef **ptr = FindPointer(key, hash);
    NodeRef *result = *ptr;
    if (result != nullptr) {
      *ptr = result->next_hash;
      size_--;
    }
  };

private:
  uint32_t cap_;
  uint32_t size_;
  NodeRef **buckets_;

  // Return a pointer to slot that points to a cache entry that
  // matches key/hash.  If there is no such cache entry, return a
  // pointer to the trailing slot in the corresponding linked list.
  NodeRef **FindPointer(const K &key, uint32_t hash) {
    NodeRef **ptr = &buckets_[hash & (cap_ - 1)];
    while (*ptr != nullptr && ((*ptr)->hash != hash || key != *(*ptr)->key)) {
      ptr = &(*ptr)->next_hash;
    }
    return ptr;
  }
};

} // namespace cache
} // namespace cpp_service