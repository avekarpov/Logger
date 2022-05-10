#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <logger.hpp>
#include <thread>
#include <chrono>

class CaptureCout
{
public:
    explicit CaptureCout(std::ostream &stream = std::cout) :
    _stream(stream)
    {
        _sbuf = _stream.rdbuf();
        _stream.rdbuf(_ss.rdbuf());
    }
    
    ~CaptureCout()
    {
        _stream.rdbuf(_sbuf);
    }
    
    std::string data() const
    {
        return _ss.str();
    }
    
    CaptureCout(const CaptureCout &) = delete;
    CaptureCout &operator=(const CaptureCout &) = delete;

private:
    std::stringstream _ss;
    std::streambuf *_sbuf;
    std::ostream &_stream;

};

void testPrint()
{
    Logger::info() << "Info level" << 1;
    Logger::warning() << "Warning level" << 2;
    Logger::error() << "Error level" << 4;
    Logger::debug() << "Debug level" << 8;
}

TEST_CASE("Logger")
{
    SECTION("Printing")
    {
        CaptureCout captureCout;
        
        Logger::setLevel(1 | 2 | 4 | 8);
        testPrint();
    
        REQUIRE(captureCout.data() == "I: Info level 1\n"
                                      "W: Warning level 2\n"
                                      "E: Error level 4\n"
                                      "D: Debug level 8\n");
    }
    
    SECTION("Level")
    {
        SECTION("None")
        {
            CaptureCout captureCout;
        
            Logger::setLevel(0);
            testPrint();
        
            REQUIRE(captureCout.data().empty());
        }
    
        SECTION("Info")
        {
            CaptureCout captureCout;
        
            Logger::setLevel(1);
            testPrint();
        
            REQUIRE(captureCout.data() == "I: Info level 1\n");
        }
        
        SECTION("Warning")
        {
            CaptureCout captureCout;
    
            Logger::setLevel(2);
            testPrint();
    
            REQUIRE(captureCout.data() == "W: Warning level 2\n");
        }
        
        SECTION("Error")
        {
            CaptureCout captureCout;
    
            Logger::setLevel(4);
            testPrint();
    
            REQUIRE(captureCout.data() == "E: Error level 4\n");
        }
    
        SECTION("Debug")
        {
            CaptureCout captureCout;
        
            Logger::setLevel(8);
            testPrint();
        
            REQUIRE(captureCout.data() == "D: Debug level 8\n");
        }
    }
    
    SECTION("Thread safety")
    {
        CaptureCout captureCout;
        
        Logger::setLevel(1 | 2 | 4 | 8);
        
        std::thread first([](){
            auto logger = Logger::info();
            logger << "start first thread";
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
            logger << "end first thread";
        });
    
        std::thread second([](){
            std::this_thread::sleep_for(std::chrono::milliseconds{100});
            auto logger = Logger::info();
            logger << "start second thread";
            logger << "end second thread";
        });
        
        first.join();
        second.join();
    
        REQUIRE(captureCout.data() == "I: start first thread end first thread\n"
                                      "I: start second thread end second thread\n");
    }
}
