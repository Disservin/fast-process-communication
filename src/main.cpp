#include <iostream>

#include "../SHL/communication.hpp"

class UciEngine : public Communication::Process {
   public:
    void write(const std::string &input) { writeProcess(input + "\n"); }

    std::vector<std::string> read(std::string_view last_word, int64_t timeout_threshold = 0) {
        return readProcess(last_word, timeout_threshold);
    }
};

int main(int argc, const char **argv) {
    UciEngine engine;
    engine.initProcess("smallbrain.exe");

    engine.write("uci");
    auto output = engine.read("uciok");

    for (const auto &line : output) {
        std::cout << line << std::endl;
    }

    return 0;
}