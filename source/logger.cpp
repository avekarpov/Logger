#include "logger.hpp"

ELogLevel Logger::_level{ELogLevel::Info}; // Default level is Info
std::mutex Logger::_mutex{};
std::ostream& Logger::_stream{std::cerr}; // Default stream is cerr

ELogLevel Logger::setLevel(ELogLevel level)
{
    return _level = level;
}

ELogLevel Logger::level()
{
    return _level;
}

Logger Logger::error()
{
    return Logger{"E:", 1};
}

Logger Logger::warning()
{
    return Logger{"W:", 2};
}

Logger Logger::info()
{
    return Logger{"I:", 4};
}

Logger Logger::debug()
{
    return Logger{"D:", 8};
}

Logger::~Logger()
{
    if (static_cast<loglevel_t>(_level) & _currentLevel)
    {
        _stream << std::endl;
    }
    _mutex.unlock();
}

Logger::Logger(const std::string &prefix, loglevel_t level):
_currentLevel(level)
{
    _mutex.lock();
    if (static_cast<loglevel_t>(_level) & _currentLevel)
    {
        _stream << prefix;
    }
}

