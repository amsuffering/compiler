#!/bin/bash

# Navigate to project root from Lexer/test/
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROJECT_ROOT"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

BINARY="./build/testScanner"
TEST_DIR="Lexer/test/inputs"

# ── Build ──────────────────────────────────────────────────────────────────────
echo "=== Building ==="
make testScanner
if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed.${NC}"
    exit 1
fi

PASS=0
FAIL=0

# ── Run tests ──────────────────────────────────────────────────────────────────
echo ""
echo "=== Running tests ==="

for test_file in "$TEST_DIR"/*.lox; do
    name=$(basename "$test_file")

    # Unlike the parser, the scanner emits one token per line, so every
    # "// expect:" line in the file is part of one multi-line expectation.
    expected=$(grep "^// expect: " "$test_file" | sed 's|^// expect: ||' | tr -d '\r')

    STDERR_TMP=$(mktemp)
    actual=$("$BINARY" "$test_file" 2>"$STDERR_TMP" | tr -d '\r')
    stderr_out=$(cat "$STDERR_TMP")
    rm -f "$STDERR_TMP"

    # Unlike the parser, the scanner keeps scanning after an error, so an error
    # test still has expected stdout -- check both streams rather than
    # requiring stdout to be empty.
    ok=1
    [ "$actual" = "$expected" ] || ok=0

    expected_err=""
    if grep -q "^// expect-error:" "$test_file"; then
        expected_err=$(grep "^// expect-error:" "$test_file" | sed 's|^// expect-error: ||' | tr -d '\r')
        actual_err=$(echo "$stderr_out" | head -1 | tr -d '\r')
        [ "$actual_err" = "$expected_err" ] || ok=0
    fi

    if [ $ok -eq 1 ]; then
        echo -e "  ${GREEN}PASS${NC}: $name"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}FAIL${NC}: $name"
        diff <(echo "$expected") <(echo "$actual") \
            --label expected --label actual -u | sed 's|^|    |'
        if [ -n "$expected_err" ]; then
            echo "    Expected error: '$expected_err'"
            echo "    Got error:      '$actual_err'"
        elif [ -n "$stderr_out" ]; then
            echo "    stderr: '$stderr_out'"
        fi
        FAIL=$((FAIL + 1))
    fi
done

# ── Summary ────────────────────────────────────────────────────────────────────
echo ""
echo "=== Results: $PASS passed, $FAIL failed ==="

[ $FAIL -eq 0 ] && exit 0 || exit 1
