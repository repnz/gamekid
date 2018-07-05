#pragma once
#include <functional>
#include <gamekid/cpu/operand.h>

namespace gamekid::cpu {
    template <typename... operand_types>
    using cpu_operation = std::function<void(cpu&, operand<operand_types>&...)>;
}