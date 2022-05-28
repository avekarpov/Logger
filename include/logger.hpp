#pragma once

#include <iostream>
#include <mutex>


class Logger
{
public:
    static uint8_t setLevel(uint8_t level);
    
    static uint8_t level();
    
    static Logger info();

    static Logger warning();

    static Logger error();

    static Logger debug();

    template<class T>
    Logger &operator<<(T t)
    {
        if (_level & _currentLevel)
        {
            _stream << " " << t;
        }

        return *this;
    }

    ~Logger();

private:
    explicit Logger(const std::string &prefix, uint8_t level);
    
    static uint8_t _level;
    
    static std::ostream &_stream;
    static std::mutex _mutex;
    
    uint8_t _currentLevel;
};


