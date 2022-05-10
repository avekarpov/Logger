#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <mutex>
#include <iostream>

#include <bitset>

class Logger
{
public:
    static uint8_t setLevel(uint8_t level)
    {
        _level = level;
        
        return _level;
    }
    
    static uint8_t level()
    {
        return _level;
    }
    
    static Logger info()
    {
        return Logger{"I:", 1};
    }
    
    static Logger warning()
    {
        return Logger{"W:", 2};
    }
    
    static Logger error()
    {
        return Logger{"E:", 4};
    }
    
    static Logger debug()
    {
        return Logger{"D:", 8};
    }
    
    template<class T>
    Logger &operator<<(T t)
    {
        if (_level & _currentLevel)
        {
            std::cout << " " << t;
        }
        
        return *this;
    }
    
    ~Logger()
    {
        if (_level & _currentLevel)
        {
            std::cout << std::endl;
        }
        _mutex.unlock();
    }
    
private:
    explicit Logger(const std::string &prefix, uint8_t level) : _currentLevel(level)
    {
        _mutex.lock();
        if (_level & _currentLevel)
        {
            std::cout << prefix;
        }
    }
    
    static uint8_t _level;
    
    static std::ostream &_stream;
    static std::mutex _mutex;
    
    uint8_t _currentLevel;
};


#endif //LOGGER_HPP
