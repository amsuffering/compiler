#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "scanner.h"
#include "ErrorReporter/ErrorReporter.h"

using std::cout, std::endl, std::string, std::vector;

ErrorReporter e = ErrorReporter();

// function declarations cause i dont want to use a header file for driver code and c++ doesn't support hoisting cause idk why
void run(string source);
void runFile(string filePath);

void run(string source) {
    Scanner scanner = Scanner(source);
    vector<Token> tokens = scanner.scanTokens();
    // print tokens
    for(Token t : tokens) {
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
    cout << source;
    run(source);
    if(e.hadError()) {
        exit(EXIT_FAILURE);
    };
}

int main(int argc, char* argv[]) {
    e.hadError(true);
    if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        cout << "Usage: ./build/testScanner.o [filePath]" << endl;
        return -1;
    }
    return 0;
}