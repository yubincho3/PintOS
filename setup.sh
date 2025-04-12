#!/bin/bash

PINTOS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
THREADS_PATH="${PINTOS_DIR}/src/threads"
UTILS_PATH="${PINTOS_DIR}/src/utils"
MISC_PATH="${PINTOS_DIR}/src/misc"

# 1. export path
if [[ ":$PATH:" != *":$UTILS_PATH:"* ]]; then
    echo "export PATH=\$PATH:${UTILS_PATH}" > ~/.profile
    source ~/.profile
fi

# 2. change gdb
TARGET_FILE="${UTILS_PATH}/pintos-gdb"
NEW_MACROS_PATH="${MISC_PATH}/gdb-macros"
sed -i "s|^GDBMACROS *= *.*|GDBMACROS = ${NEW_MACROS_PATH}|" "$TARGET_FILE"

# 3. change simulator to qemu
TARGET_FILE="${THREADS_PATH}/Make.vars"
sed -i 's|^SIMULATOR *= *--.*|SIMULATOR = --qemu|' "$TARGET_FILE"

# 4. make
cd $UTILS_PATH
make
cd $THREADS_PATH
make
