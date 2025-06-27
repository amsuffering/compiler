#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "scanner.h"

using std::cout, std::endl, std::string, std::vector;

ErrorReporter e = ErrorReporter();

// function declarations cause i dont want to use a header file for driver code and c++ doesn't support hoisting cause idk why
void run(string source);
void runFile(string filePath);

void run(string source) {
    Scanner scanner = Scanner(source, e);
    vector<Token> tokens = scanner.scanTokens();
    // print tokens
    for(Token &t : tokens) {
        cout << t.tokenToString() << endl;
    }
}

void runFile(string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "filePath " << filePath << " cannot be opened";
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    string source = buffer.str();
    run(source);
    if(e.hadError()) {
        std::cerr << "error" << endl;
        exit(EXIT_FAILURE);
    };
}

int main(int argc, char* argv[]) {
    e.hadError(false);
    if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        cout << "Usage: ./build/testScanner [filePath]" << endl;
        return -1;
    }
    return 0;
}