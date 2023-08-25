#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace index_lib {
enum DataType {
  UNKNOWN = 0,
  INT8 = 1,
  UINT8 = 2,
  INT16 = 3,

};
enum RepeatType {
  SINGLE = 0,
  FIX_LENGTH = 1,
  VAR_LENGTH = 2,
};

} // namespace index_lib