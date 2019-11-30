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
${CPPCHECK} source  --library=googletest --enable=all --error-exitcode=1 -I source/Application -I source/Base_manager -I source/Event -I source/Event_throwable -I source/Game_context -I source/Input -I source/Loader -I source/Network -I source/Renderer  -I ../3rdparty/tinyxml2 --suppress=missingIncludeSystem # --check-config

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=c,cpp --headers=h,hpp --filter=-runtime/references source/main.cpp source/main_test_external.cpp source/main_test_internal.cpp source/Application/* source/Base_manager/* source/Event/* source/Event_throwable/* source/Game_context/* source/Input/* source/Loader/* source/Network/* source/Renderer/*

print_header "SUCCESS"
