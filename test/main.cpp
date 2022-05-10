#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <logger.hpp>

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

TEST_CASE("Logger")
{
    SECTION("Printing")
    {
        CaptureCout captureCout;
        
        Logger::setLevel(1 | 2 | 4 | 8);
        Logger::info() << "Info level" << 1;
        Logger::warning() << "Warning level" << 2;
        Logger::error() << "Error level" << 4;
        Logger::debug() << "Debug level" << 8;
    
        REQUIRE(captureCout.data() == "I: Info level 1\n"
                                      "W: Warning level 2\n"
                                      "E: Error level 4\n"
                                      "D: Debug level 8\n");
    }
}
