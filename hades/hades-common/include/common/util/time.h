#pragma once

#include <chrono>

namespace hades {
    static long currentTimeMillis() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}