#include "system.h"

void gamekid::system::schedule_operation(system_operation<> operation, 
    int instruction_count) {
    _scheduled_operations.emplace_back(operation, instruction_count);
}
