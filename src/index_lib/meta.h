#pragma once

#include <cstdint>
#include <string>
namespace index_lib {
struct TableConf {
  std::string schema_path;
  std::string index_path;
  uint32_t max_doc_id;       // 当前最大doc_id
  uint32_t table_size_limit; // 最大docid限制

  std::string fixed_data_path;
  uint64_t fixed_file_size;
  uint64_t fixed_row_size;
};
} // namespace index_lib
