#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
	CPPCHECK="cppcheck --check-config"
else
	CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} source --library=googletest --enable=all --error-exitcode=1 -I source/game_logic -I source/game_manager --suppress=missingIncludeSystem # --check-config

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=c,cpp --headers=h,hpp --filter=-runtime/references source/game_logic/* source/game_manager/*

print_header "SUCCESS"
