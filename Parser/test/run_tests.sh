#!/bin/bash

# Navigate to project root from Parser/test/
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROJECT_ROOT"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

BINARY="./build/testParser"
TEST_DIR="Parser/test/inputs"

# ── Build ──────────────────────────────────────────────────────────────────────
echo "=== Building ==="
make testParser
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

    is_error_test=$(grep -c "^// expect-error:" "$test_file")
    expected=$(grep "^// expect: " "$test_file" | sed 's|^// expect: ||' | tr -d '\r')

    STDERR_TMP=$(mktemp)
    actual=$("$BINARY" "$test_file" 2>"$STDERR_TMP" | tr -d '\r')
    stderr_out=$(cat "$STDERR_TMP")
    rm -f "$STDERR_TMP"

    if [ "$is_error_test" -gt 0 ]; then
        expected_err=$(grep "^// expect-error:" "$test_file" | sed 's|^// expect-error: ||' | tr -d '\r')
        # First line only — strips trailing "error" printed by testParser's runFile
        actual_err=$(echo "$stderr_out" | head -1 | tr -d '\r')
        if [ -z "$actual" ] && [ "$actual_err" = "$expected_err" ]; then
            echo -e "  ${GREEN}PASS${NC}: $name"
            echo "    Expected error: '$expected_err'"
            echo "    Got error:      '$actual_err'"
            PASS=$((PASS + 1))
        else
            echo -e "  ${RED}FAIL${NC}: $name"
            echo "    Expected error: '$expected_err'"
            echo "    Got error:      '$actual_err'"
            [ -n "$actual" ] && echo "    Unexpected stdout: '$actual'"
            FAIL=$((FAIL + 1))
        fi
    else
        if [ "$actual" = "$expected" ]; then
            echo -e "  ${GREEN}PASS${NC}: $name"
            echo "    Expected: '$expected'"
            echo "    Got:      '$actual'"
            PASS=$((PASS + 1))
        else
            echo -e "  ${RED}FAIL${NC}: $name"
            echo "    Expected: '$expected'"
            echo "    Got:      '$actual'"
            FAIL=$((FAIL + 1))
        fi
    fi
done

# ── Summary ────────────────────────────────────────────────────────────────────
echo ""
echo "=== Results: $PASS passed, $FAIL failed ==="

[ $FAIL -eq 0 ] && exit 0 || exit 1
