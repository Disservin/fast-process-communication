#pragma once

#include <cstdint>
#include <string>
#include <vector>

#ifdef _WIN64
#include <windows.h>
#endif

namespace Communication
{

class IProcess
{
  public:
    virtual ~IProcess() = default;

    // Initialize the engine process
    virtual void initProcess(const std::string &command) = 0;

    // Returns true if the engine process is alive
    virtual bool isAlive() = 0;

    bool timeout() const
    {
        return timeout_;
    }

  protected:
    // Read engine's stdout until the line matches last_word or timeout is reached
    virtual std::vector<std::string> readProcess(std::string_view last_word, int64_t timeout_threshold) = 0;

    // Write input to the engine's stdin
    virtual void writeProcess(const std::string &input) = 0;

    bool is_initalized_ = false;
    bool timeout_ = false;
};

#ifdef _WIN64

class Process : public IProcess
{
  public:
    ~Process() override;

    void initProcess(const std::string &command) override;
    bool isAlive() override;

    void killProcess();

  protected:
    std::vector<std::string> readProcess(std::string_view last_word, int64_t timeout_threshold) override;
    void writeProcess(const std::string &input) override;

  private:
    void closeHandles();

    PROCESS_INFORMATION pi_;
    HANDLE child_std_out_;
    HANDLE child_std_in_;
};

#else

class Process : public IProcess
{
  public:
    ~Process() override;

    void initProcess(const std::string &command) override;
    bool isAlive() override;

    void killProcess();

  protected:
    std::vector<std::string> readProcess(std::string_view last_word, int64_t timeout_threshold) override;
    void writeProcess(const std::string &input) override;

  private:
    pid_t process_pid_;
    int in_pipe_[2], out_pipe_[2];
};

#endif

} // namespace Communication
