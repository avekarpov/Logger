## Simple thread safe logger

#### Levels

```c++
Logger::setLevel(1 | 2 | 4 | 8)
```
- 1 - info
- 2 - warning
- 4 - error
- 8 - debug

#### Printing

```c++
Logger::info() << "What is the answer to all questions?";
Logger::info() << "Answer is" << 42;
```

```text
"I: What is the answer to all questions?"
"I: Answer is 42"
```

##### Methods for other levels
```c++
Logger::warning();
Logger::error();
Logger::debug();
```
