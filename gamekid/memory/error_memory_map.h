#pragma once
#include "error_page.h"

namespace gamekid::memory {
    class error_memory_map : public memory_map {
    private:
        error_memory_map() {
            for (auto& page : pages) {
                page = &gamekid::memory::error_page::instance();
            }
        }
    public:
        error_memory_map(const error_memory_map&) = delete;
        error_memory_map& operator=(const error_memory_map&) = delete;
        
        static error_memory_map& instance() {
            static error_memory_map _instance;
            return _instance;
        }
    };
}
