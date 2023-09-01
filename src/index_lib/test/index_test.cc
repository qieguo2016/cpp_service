#include "index_lib/meta.h"
#include "index_lib/schema/reflection.h"
#include "index_lib/table.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <vector>

using namespace index_lib;

template <typename T>
typename std::enable_if<is_number<typename T::value_type>, std::string>::type
print_vec(const T &vec) {
  std::string ret;
  for (const auto el : vec) {
    ret += std::to_string(el) + ",";
  }
  return ret;
}

template <typename T>
typename std::enable_if<
    std::is_same<typename T::value_type, std::string>::value, std::string>::type
print_vec(const T &vec) {
  std::string ret;
  for (const auto el : vec) {
    ret += el + ",";
  }
  return ret;
}

template <typename T> void test_integer(char *cur) {
  std::vector<T> req;
  auto pos = cur;
  for (int j = 0; j < 8; j++) {
    if (std::is_unsigned_v<T>) {
      req.emplace_back(rand() % 100);
    } else {
      req.emplace_back(rand() % 100 - 50);
    }
    index_lib::Reflection::set<T>(cur, req.back());
    cur += sizeof(T);
  }
  std::vector<T> res;
  for (int j = 0; j < 8; j++) {
    res.emplace_back(index_lib::Reflection::get<T>(pos));
    pos += sizeof(T);
  }
  ASSERT_EQ(req, res);
  std::cout << typeid(T).name() << ", equal:" << std::to_string(req == res)
            << ", req: " << print_vec<std::vector<T>>(req)
            << ", res: " << print_vec<std::vector<T>>(res) << std::endl;
}

template <typename T> void test_float(char *cur) {
  std::vector<T> req;
  auto pos = cur;
  for (int j = 0; j < 8; j++) {
    req.emplace_back((T)(rand() % 100 - 50) * 3.1415926);
    index_lib::Reflection::set<T>(cur, req.back());
    cur += sizeof(T);
  }
  std::vector<T> res;
  for (int j = 0; j < 8; j++) {
    res.emplace_back(index_lib::Reflection::get<T>(pos));
    pos += sizeof(T);
  }
  ASSERT_EQ(req, res);
  std::cout << typeid(T).name() << ", equal:" << std::to_string(req == res)
            << ", req: " << print_vec<std::vector<T>>(req)
            << ", res: " << print_vec<std::vector<T>>(res) << std::endl;
}

TEST(INDEX_LIB, reflection_test) {
  srand((unsigned)time(NULL));
  std::cout << "reflection_test" << std::endl;
  char *buf = new char[10000];
  char *cur = buf;
  std::cout << "<bool>"
            << ", set: " << index_lib::Reflection::set<bool>(cur, true)
            << ", get: " << index_lib::Reflection::get<bool>(cur) << std::endl;
  cur += sizeof(bool);
  std::cout << "<bool>"
            << ", set: " << index_lib::Reflection::set<bool>(cur, false)
            << ", get: " << index_lib::Reflection::get<bool>(cur) << std::endl;
  cur += sizeof(bool);
  std::cout << "<int64_t>"
            << ", set: " << index_lib::Reflection::set<int64_t>(cur, 0)
            << ", get: " << (index_lib::Reflection::get<int64_t>(cur) == 0)
            << std::endl;
  cur += sizeof(int64_t);

  test_integer<int64_t>(cur);
  test_integer<uint64_t>(cur);
  test_integer<uint32_t>(cur);
  test_integer<int32_t>(cur);
  test_integer<int8_t>(cur);
  test_integer<uint8_t>(cur);
  test_integer<uint16_t>(cur);
  test_integer<int16_t>(cur);
  test_float<float>(cur);
  test_float<double>(cur);

  for (int j = 0; j < 8; j++) {
    std::string s = "string_" + std::to_string(j);
    auto ok = index_lib::Reflection::set<std::string>(cur, s);
    std::string q = index_lib::Reflection::get<std::string>(cur);
    std::cout << "<string>" << s << ", set: " << ok << ", get: " << q
              << std::endl;
    cur += 1 + s.size();
  }

  for (int j = 0; j < 8; j++) {
    std::vector<uint8_t> req = {7, 4};
    req.push_back(j);
    index_lib::Reflection::set<std::vector<uint8_t>>(cur, req);
    auto res = index_lib::Reflection::get<std::vector<uint8_t>>(cur);

    std::cout << "<std::vector<uint8_t>>, equal:" << std::to_string(req == res)
              << " origin: " << print_vec<std::vector<uint8_t>>(req)
              << " get: " << print_vec<std::vector<uint8_t>>(res) << std::endl;
    cur += 1 + req.size() * sizeof(uint8_t);
  }

  for (int j = 0; j < 8; j++) {
    std::vector<int64_t> req = {21312, -487312};
    req.push_back(j * 107);
    index_lib::Reflection::set<std::vector<int64_t>>(cur, req);
    auto res = index_lib::Reflection::get<std::vector<int64_t>>(cur);

    std::cout << "<std::vector<int64_t>>, equal:" << std::to_string(req == res)
              << " origin: " << print_vec<std::vector<int64_t>>(req)
              << " get: " << print_vec<std::vector<int64_t>>(res) << std::endl;
    cur += 1 + req.size() * sizeof(int64_t);
  }

  for (int j = 0; j < 8; j++) {
    std::vector<float> req = {5.112387, 87234.12312};
    req.push_back(j * 3.14159);
    index_lib::Reflection::set<std::vector<float>>(cur, req);
    auto res = index_lib::Reflection::get<std::vector<float>>(cur);

    std::cout << "<std::vector<float>>, equal:" << std::to_string(req == res)
              << " origin: " << print_vec<std::vector<float>>(req)
              << " get: " << print_vec<std::vector<float>>(res) << std::endl;
    cur += 1 + req.size() * sizeof(float);
  }

  for (int j = 0; j < 8; j++) {
    std::vector<double> req = {5238.1123123, -8234.0979123};
    req.push_back(j * 3.14159);
    index_lib::Reflection::set<std::vector<double>>(cur, req);
    auto res = index_lib::Reflection::get<std::vector<double>>(cur);

    std::cout << "<std::vector<double>>, equal:" << std::to_string(req == res)
              << " origin: " << print_vec<std::vector<double>>(req)
              << " get: " << print_vec<std::vector<double>>(res) << std::endl;
    cur += 1 + req.size() * sizeof(double);
  }

  for (int j = 0; j < 5; j++) {
    std::vector<std::string> req;
    int len = 0;
    for (int i = 0; i < 3; i++) {
      req.push_back("s_" + std::to_string(j * 10 + i));
      len += req.back().size() + 1;
    }
    index_lib::Reflection::set<std::vector<std::string>>(cur, req);
    auto res = index_lib::Reflection::get<std::vector<std::string>>(cur);

    std::cout << "<std::vector<std::string>>, equal:"
              << std::to_string(req == res)
              << " origin: " << print_vec<std::vector<std::string>>(req)
              << " get: " << print_vec<std::vector<std::string>>(res)
              << std::endl;
    cur += 1 + len;
  }

  std::cout << "<int64_t>"
            << ", set: " << index_lib::Reflection::set<int64_t>(cur, 0)
            << ", get: " << (index_lib::Reflection::get<int64_t>(cur) == 0)
            << std::endl;
  cur += sizeof(int64_t);
}

TEST(INDEX_LIB, table) {
  std::cout << "table test";
  TableConf conf{"", "./schema", 0, 100, "./fixed_data", 64 * 16, 64};
  Table t(conf);
  auto ok = t.Init();
  std::cout << "load: " << ok << std::endl;
  t.Set((uint64_t)12345, (uint16_t)0, (uint64_t)12345);
  t.Set((uint64_t)12345, (uint16_t)1, std::string("hello"));
  std::cout << "row 12345, 0: " << t.Get<uint64_t>(12345, 0).value()
            << std::endl;
  std::cout << "row 12345, 1: " << t.Get<uint64_t>(12345, 1).value()
            << std::endl;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}