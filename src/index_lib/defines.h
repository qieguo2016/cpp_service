
#include "index_lib/table.h"
#include <cstddef>
namespace index_lib {

static constexpr size_t kMemIncStep = (1UL << 26); // 64MB
static const uint32_t kInvalidDocId = static_cast<uint32_t>(-1);

}; // namespace index_lib