## Simple thread safe logger

### Levels

```c++
Logger::setLevel(ELogLevel::Info);
```
#### Available values
- Debug - Print every log level
- Info - Print info and lower
- Warning - Print warning and lower
- Error - Print error
- Silent - No output at all

### Printing

```c++
Logger::setLevel(ELogLevel::Info);

// This message will be ignored because log level is set to Info
Logger::debug() << "I am a debug message you never gonna see :)";

Logger::info() << "What is the answer to all questions?";
Logger::info() << "Answer is" << 42;
```
#### Output:
```text
"I: What is the answer to all questions?"
"I: Answer is 42"
```

#### All methods
```c++
Logger::debug();
Logger::info();
Logger::warning();
Logger::error();
```

