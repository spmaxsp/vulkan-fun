#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"


int main() {
    spdlog::info("Sample Info output.");
    spdlog::warn("Sample Warn output.");
    spdlog::error("Sample Error output.");

    return 0;
}