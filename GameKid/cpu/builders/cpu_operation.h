#pragma once
#include <functional>


class cpu;

template <typename T>
class operand;

template <typename... operand_types>
using cpu_operation = std::function<void(cpu&, operand<operand_types>&...)>;

template <typename... operand_types>
using operand_tuple = std::tuple<operand<operand_types>&...>;