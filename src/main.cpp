#include "utils/murmurhash3.h"
#include "cache/hashtable.h"
#include <cstdio>
#include <functional>
#include <iostream>
#include <string>

int main(int argc, const char **argv) {
  std::cout << "/* message */" << std::endl;

  cpp_service::cache::HashTable<std::string, std::string> t(8);

  for (size_t i = 0; i < 10; i++) {
    uint32_t hash;
    std::string key = "k" + std::to_string(i);
    std::string value = "v" + std::to_string(i);
    MurmurHash3_x64_128(key.c_str(), sizeof(key), 0, &hash);
    t.Insert(key, hash, value);
  }

  for (size_t i = 0; i < 10; i++) {
    uint32_t hash;
    std::string key = "k" + std::to_string(i);
    MurmurHash3_x64_128(key.c_str(), sizeof(key), 0, &hash);
    auto node = t.Lookup(key, hash);
    if (node != nullptr) {
      std::printf("lookup node, key=%s, value=%s", key.c_str(),
                  node->value->c_str());
    }
  }

  return 0;
}