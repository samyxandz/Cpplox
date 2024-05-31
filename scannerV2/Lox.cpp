#include <cstring>      
#include <fstream>      
#include <iostream>     
#include <string>
#include <vector>


std::string readFile(std::string_view path) {
  std::ifstream file{path.data(), std::ios::in | std::ios::binary | std::ios::ate};
  if (!file) {
    std::cerr << "Failed to open file " << path << ": ";
    std::exit(74);
  };

  std::string contents;
  contents.resize(file.tellg());

  file.seekg(0, std::ios::beg);
  file.read(contents.data(), contents.size());

  return contents;
}

void run(std::string_view source) {
  Scanner scanner {source};
  std::vector<Token> tokens = scanner.scanTokens();
  for (const Token& token : tokens) {
    std::cout << token.toString() << "\n";
  }
}

void runFile(std::string_view path) {
  std::string contents = readFile(path);
  run(contents);
  if (hadError) std::exit(65);
}

void runPrompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line)) break;
    run(line);
    hadError = false;
  }
}

int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cout << "Usage: jlox [script]\n";
    std::exit(64);
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
}