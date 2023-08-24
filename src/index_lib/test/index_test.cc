#include "index_lib/table.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sys/types.h>

TEST(INDEX_LIB, segment_get_set) {
  std::cout << "simple_get_set, path=./segment_test";
  Table t(1024, 8);
  auto ok = t.load("./segment_test");
  std::cout << "load: " << ok << std::endl;
  t.set(0, 10000);
  std::cout << "row 0 set" << std::endl;
  std::cout << "row 0: " << *t.get<u_int64_t>(0) << std::endl;
  t.set(1, 10001);
  std::cout << "row 1: " << *t.get<u_int64_t>(1) << std::endl;
  t.set(10, 10010);
  t.set(10, 20010);
  std::cout << "row 10: " << *t.get<u_int64_t>(10) << std::endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}