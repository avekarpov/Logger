#include "logger.hpp"

uint8_t Logger::_level{};
std::mutex Logger::_mutex{};

uint8_t Logger::setLevel(uint8_t level)
{
    _level = level;
    
    return _level;
}

uint8_t Logger::level()
{
    return _level;
}

Logger Logger::info()
{
    return Logger{"I:", 1};
}

Logger Logger::warning()
{
    return Logger{"W:", 2};
}

Logger Logger::error()
{
    return Logger{"E:", 4};
}

Logger Logger::debug()
{
    return Logger{"D:", 8};
}

Logger::~Logger()
{
    if (_level & _currentLevel)
    {
        std::cout << std::endl;
    }
    _mutex.unlock();
}

Logger::Logger(const std::string &prefix, uint8_t level):
_currentLevel(level)
{
    _mutex.lock();
    if (_level & _currentLevel)
    {
        std::cout << prefix;
    }
}