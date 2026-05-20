#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "parser.h"
#include "AstPrinter.h"

using std::cout, std::endl, std::string, std::vector;

ErrorReporter e = ErrorReporter();

// function declarations cause i dont want to use a header file for driver code and c++ doesn't support hoisting cause idk why
void run(string source);
void runFile(string filePath);

void run(string source) {
    Scanner scanner = Scanner(source, e);
    vector<Token> tokens = scanner.scanTokens();

    Parser parser = Parser(tokens, e);
    std::unique_ptr<Expr> expression = parser.parse();

    if (e.hadError()) return;
    ASTPrinter printer;
    std::cout << printer.print(*expression);
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
        cout << "Usage: ./build/testParser [filePath]" << endl;
        return -1;
    }
    return 0;
}