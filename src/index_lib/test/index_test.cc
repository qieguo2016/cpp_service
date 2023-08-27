#include "index_lib/schema/reflection.h"
// #include "index_lib/table.h"
#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <sys/types.h>

using namespace index_lib;

// TEST(INDEX_LIB, segment_get_set) {
//   std::cout << "simple_get_set, path=./segment_test";
//   Table t(1024, 8);
//   auto ok = t.load("./segment_test");
//   std::cout << "load: " << ok << std::endl;
//   t.set(0, 10000);
//   std::cout << "row 0 set" << std::endl;
//   std::cout << "row 0: " << *t.get<u_int64_t>(0) << std::endl;
//   t.set(1, 10001);
//   std::cout << "row 1: " << *t.get<u_int64_t>(1) << std::endl;
//   t.set(10, 10010);
//   t.set(10, 20010);
//   std::cout << "row 10: " << *t.get<u_int64_t>(10) << std::endl;
// }

// TEST(INDEX_LIB, schema_test) {
//   std::cout << "schema_test, schema path=./schema.json";
// //   std::cout << "row 10: " << *t.get<u_int64_t>(10) << std::endl;
// }

TEST(INDEX_LIB, reflection_test) {
  srand((unsigned)time(NULL));
  std::cout << "reflection_test" << std::endl;
  char *buf = new char[10000];
  char *cur = buf;
  index_lib::Reflection ref;
  for (int j = 0; j < 8; j++) {
    int64_t tmp = rand() * 100 - 100000;
    std::cout << "<int64_t>" << tmp << ", set: " << ref.set<int64_t>(cur, tmp)
              << ", get: " << (ref.get<int64_t>(cur) == tmp) << std::endl;
    cur += sizeof(int64_t);
  }
  for (int j = 0; j < 8; j++) {
    uint64_t tmp = rand() * 100;
    std::cout << "<uint64_t>" << tmp << ", set: " << ref.set<uint64_t>(cur, tmp)
              << ", get: " << (ref.get<uint64_t>(cur) == tmp) << std::endl;
    cur += sizeof(uint64_t);
  }
  for (int j = 0; j < 8; j++) {
    int32_t tmp = rand() - 10000;
    std::cout << "<int32_t>" << tmp << ", set: " << ref.set<int32_t>(cur, tmp)
              << ", get: " << (ref.get<int32_t>(cur) == tmp) << std::endl;
    cur += sizeof(int32_t);
  }
  for (int j = 0; j < 8; j++) {
    uint32_t tmp = rand();
    std::cout << "<uint32_t>" << tmp << ", set: " << ref.set<uint32_t>(cur, tmp)
              << ", get: " << (ref.get<uint32_t>(cur) == tmp) << std::endl;
    cur += sizeof(uint32_t);
  }
  for (int j = 0; j < 8; j++) {
    float tmp = (rand() - 1e9) * 3.1415926;
    std::cout << "<float>" << tmp << ", set: " << ref.set<float>(cur, tmp)
              << ", get: " << ref.get<float>(cur) << std::endl;
    cur += sizeof(float);
  }
  for (int j = 0; j < 8; j++) {
    double tmp = (rand() - 1e9) * 3.1415926;
    std::cout << "<double>" << tmp << ", set: " << ref.set<double>(cur, tmp)
              << ", get: " << ref.get<double>(cur) << std::endl;
    cur += sizeof(double);
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}