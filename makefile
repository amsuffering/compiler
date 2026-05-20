# === Compiler settings ===
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -ILexer -IErrorReporter -IParser

# === Directory setup ===
OBJ_DIR = build
BIN_DIR = build

# === Source files ===
PARSER_SRC = Parser/parser.cpp Parser/AstPrinter.cpp
LEXER_SRC = Lexer/scanner.cpp Lexer/token.cpp
ERROR_SRC = ErrorReporter/ErrorReporter.cpp
SCANNER_TEST_SRC = Lexer/test/testScanner.cpp

# === Object files ===
PARSER_OBJ = ${PARSER_SRC:%.cpp=$(OBJ_DIR)/%.o}
LEXER_OBJ = $(LEXER_SRC:%.cpp=$(OBJ_DIR)/%.o)
ERROR_OBJ = $(ERROR_SRC:%.cpp=$(OBJ_DIR)/%.o)
PARSER_TEST_OBJ = $(OBJ_DIR)/Parser/test/testParser.o
SCANNER_TEST_OBJ = $(OBJ_DIR)/Lexer/test/testScanner.o

# === Executables ===
SCANNER_BIN = $(BIN_DIR)/testScanner
PARSER_BIN = $(BIN_DIR)/testParser

# === Phony targets ===
.PHONY: all clean testParser testScanner
testParser: $(PARSER_BIN)
testScanner: $(SCANNER_BIN)

# === Default target ===
all: $(SCANNER_BIN) $(PARSER_BIN)

# === Link final binary ===
$(PARSER_BIN): $(PARSER_TEST_OBJ) $(PARSER_OBJ) $(LEXER_OBJ) $(ERROR_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
$(SCANNER_BIN): $(SCANNER_TEST_OBJ) $(LEXER_OBJ) $(ERROR_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# === Compile .cpp -> .o ===
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# === Clean up ===
clean:
	rm -rf $(OBJ_DIR)
