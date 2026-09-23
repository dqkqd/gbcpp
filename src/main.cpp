#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

enum class OpCode : std::uint8_t {
  NOP,  // 00
  JPn16 // C3
};

static std::string_view opcode_name(OpCode opcode) {
  switch (opcode) {
  case OpCode::NOP:
    return "NOP";
  case OpCode::JPn16:
    return "JPn16";
  }
}

class CpuState {
public:
  const std::size_t pos;

  // TODO(khanhdq): start from 0x0000?
  static CpuState start() { return {0x0100}; }
};

class Cpu {
public:
  Cpu(const Cpu &&) = delete;
  Cpu &operator=(const Cpu &&) = delete;
  Cpu(const Cpu &) = delete;
  Cpu &operator=(const Cpu &) = delete;
  ~Cpu() = default;

  explicit Cpu(const std::string &filename) {
    std::ifstream file{filename, std::ifstream::in | std::ifstream::binary};
    if (file.is_open()) {
      data = {std::istreambuf_iterator<char>(file),
              std::istreambuf_iterator<char>()};
    }
  }

  [[nodiscard]] std::pair<OpCode, CpuState> fetch(const CpuState &state) const {
    auto opcode = data[state.pos];
    switch (opcode) {
    case 0x00:
      return std::make_pair(OpCode::NOP, CpuState{state.pos + 1});
    case 0xc3:
      return std::make_pair(OpCode::JPn16, CpuState{state.pos + 1});
    default:
      throw std::runtime_error(std::format("Unknow opcode {}", opcode));
    }
  }

private:
  std::vector<std::uint8_t> data;
};

int main(int /*argc*/, char **argv) {
  auto filename = argv[1]; // NOLINT
  auto cpu = Cpu(filename);
  auto [opcode1, state1] = cpu.fetch(CpuState::start());

  std::cout << opcode_name(opcode1) << "\n";

  auto [opcode2, state2] = cpu.fetch(state1);
  std::cout << opcode_name(opcode2) << "\n";

  return 0;
}
