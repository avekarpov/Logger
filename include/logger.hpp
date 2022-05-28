#pragma once

#include <iostream>
#include <mutex>

using loglevel_t = uint8_t;

enum class ELogLevel : loglevel_t
{
    Debug = 15u,
    Info = 7u,
    Warning = 3u,
    Error = 1u,
    Silent = 0u,
};

class Logger
{
public:
    static ELogLevel setLevel(ELogLevel level);

    static ELogLevel level();

    static Logger info();

    static Logger warning();

    static Logger error();

    static Logger debug();

    template<class T>
    Logger &operator<<(T t)
    {
        if (static_cast<loglevel_t>(_level) & _currentLevel)
        {
            _stream << " " << t;
        }

        return *this;
    }

    ~Logger();

private:
    explicit Logger(const std::string &prefix, loglevel_t level);

    static ELogLevel _level;

    static std::ostream &_stream;
    static std::mutex _mutex;

    loglevel_t _currentLevel;
};

