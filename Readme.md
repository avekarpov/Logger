## Simple thread safe logger

<h4>Levels</h4>

```c++
Logger::setLevel(1 | 2 | 4 | 8)
```
1 - info <br/>
2 - warning <br/>
4 - error <br/>
8 - debug <br/>

<h4>Printing</h4>

```c++
Logger::info() << "What is the answer to all questions?";
Logger::info() << "Answer is" << 42;
```

```text
"I: What is the answer to all questions?"
"I: Answer is 42"
```
Methods for other levels
```c++
Logger::warning()
Logger::error()
Logger::debug()
```