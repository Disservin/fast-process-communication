# Simple C++ Process Communication

This is a simple C++ implementation to start a process and communicate with it.

## Usage

C++17

You can use the single header file from the SHL directory.

Create a class which inherits the Process class. Easiest example:

```cpp
class Wrapper : public Communication::Process
{
  public:
    void write(const std::string &input)
    {
        writeProcess(input + "\n");
    }

    std::vector<std::string> read(std::string_view last_word, int64_t timeout_threshold = 0)
    {
        return readProcess(last_word, timeout_threshold);
    }
};
```

You have access to this interface

```cpp
class IProcess
{
  public:
    // Initialize the engine process
    virtual void initProcess(const std::string &command) = 0;

    // Returns true if the engine process is alive
    virtual bool isAlive() = 0;

    bool timeout() const;

  protected:
    // Read engine's stdout until the line matches last_word or timeout is reached
    virtual std::vector<std::string> readProcess(std::string_view last_word, int64_t timeout_threshold) = 0;

    virtual void writeProcess(const std::string &input) = 0;
};
```

You may want to catch `std::runtime_error` since these can be thrown from almost any function or do something with cerr.
