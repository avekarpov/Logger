#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <logger.hpp>
#include <thread>
#include <chrono>

class CaptureCerr
{
public:
    explicit CaptureCerr(std::ostream &stream = std::cerr) :
    _stream(stream)
    {
        _sbuf = _stream.rdbuf();
        _stream.rdbuf(_ss.rdbuf());
    }

    ~CaptureCerr()
    {
        _stream.rdbuf(_sbuf);
    }

    std::string data() const
    {
        return _ss.str();
    }

    CaptureCerr(const CaptureCerr &) = delete;
    CaptureCerr &operator=(const CaptureCerr &) = delete;

private:
    std::stringstream _ss;
    std::streambuf *_sbuf;
    std::ostream &_stream;

};

void testPrint()
{
    Logger::debug() << "Debug level" << 15;
    Logger::info() << "Info level" << 7;
    Logger::warning() << "Warning level" << 3;
    Logger::error() << "Error level" << 1;
}

TEST_CASE("Logger")
{
    SECTION("Printing")
    {
        CaptureCerr captureCerr;

        Logger::setLevel(ELogLevel::Debug);
        testPrint();

        REQUIRE(captureCerr.data() == "D: Debug level 15\n"
                                      "I: Info level 7\n"
                                      "W: Warning level 3\n"
                                      "E: Error level 1\n");
    }

    SECTION("Level")
    {
        SECTION("None")
        {
            CaptureCerr captureCerr;

            Logger::setLevel(ELogLevel::Silent);
            testPrint();

            REQUIRE(captureCerr.data().empty());
        }

        SECTION("Debug")
        {
            CaptureCerr captureCerr;

            Logger::setLevel(ELogLevel::Debug);
            testPrint();

            REQUIRE(captureCerr.data() == "D: Debug level 15\n"
                                          "I: Info level 7\n"
                                          "W: Warning level 3\n"
                                          "E: Error level 1\n");
        }

        SECTION("Info")
        {
            CaptureCerr captureCerr;

            Logger::setLevel(ELogLevel::Info);
            testPrint();

            REQUIRE(captureCerr.data() == "I: Info level 7\n"
                                          "W: Warning level 3\n"
                                          "E: Error level 1\n");
        }

        SECTION("Warning")
        {
            CaptureCerr captureCerr;

            Logger::setLevel(ELogLevel::Warning);
            testPrint();

            REQUIRE(captureCerr.data() == "W: Warning level 3\n"
                                          "E: Error level 1\n");
        }

        SECTION("Error")
        {
            CaptureCerr captureCerr;

            Logger::setLevel(ELogLevel::Error);
            testPrint();

            REQUIRE(captureCerr.data() == "E: Error level 1\n");
        }
    }

    SECTION("Thread safety")
    {
        CaptureCerr captureCerr;

        Logger::setLevel(ELogLevel::Debug);

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

        REQUIRE(captureCerr.data() == "I: start first thread end first thread\n"
                                      "I: start second thread end second thread\n");
    }
}

