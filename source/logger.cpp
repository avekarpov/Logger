#include "logger.hpp"

uint8_t Logger::_level{};
std::mutex Logger::_mutex{};
