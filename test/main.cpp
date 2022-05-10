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

}
