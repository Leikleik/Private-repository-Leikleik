#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

mkdir -p "${BUILD_DIR}"

echo "== Quest 1 =="
gcc -Wall -Wextra -Werror \
  "${ROOT_DIR}/src/data_module/data_module_entry.c" \
  "${ROOT_DIR}/src/data_module/data_process.c" \
  "${ROOT_DIR}/src/data_libs/data_io.c" \
  "${ROOT_DIR}/src/data_libs/data_stat.c" \
  -o "${BUILD_DIR}/Quest_1"
echo "5 1 2 3 4 5" | "${BUILD_DIR}/Quest_1"
echo

echo "== Quest 2 =="
gcc -Wall -Wextra -Werror \
  "${ROOT_DIR}/src/yet_another_decision_module/yet_another_decision_module_entry.c" \
  "${ROOT_DIR}/src/yet_another_decision_module/decision.c" \
  "${ROOT_DIR}/src/data_libs/data_io.c" \
  "${ROOT_DIR}/src/data_libs/data_stat.c" \
  -o "${BUILD_DIR}/Quest_2"
echo "4 1 2 3 4" | "${BUILD_DIR}/Quest_2"
echo

echo "== Quest 3 =="
make -C "${ROOT_DIR}/src/main_executable_module" Quest_3
echo

echo "== Quest 4 =="
make -C "${ROOT_DIR}/src/main_executable_module" build_with_static
echo

echo "== Quest 5 =="
make -C "${ROOT_DIR}/src/main_executable_module" build_with_dynamic
echo

echo "== Quest 6 =="
make -C "${ROOT_DIR}/src/s21_string" strlen_tests
echo

echo "== Quest 7 =="
make -C "${ROOT_DIR}/src/s21_string" strcmp_tests
echo

echo "== Quest 8 =="
make -C "${ROOT_DIR}/src/s21_string" strcpy
echo

echo "== Quest 9 =="
make -C "${ROOT_DIR}/src/s21_string" strcat
echo

echo "== Quest 10 =="
make -C "${ROOT_DIR}/src/s21_string" strchr
echo

echo "== Quest 11 =="
make -C "${ROOT_DIR}/src/s21_string" strstr
echo

echo "== Quest 12 =="
make -C "${ROOT_DIR}/src/s21_string" full_coverage_tests
echo

echo "== Quest 13 =="
make -C "${ROOT_DIR}/src/s21_string" text_processor
echo -e "10\nhello how are you" | "${BUILD_DIR}/Quest_13" -w
echo
