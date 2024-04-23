
#!/bin/bash

getPath()
{
    local SOURCE=${BASH_SOURCE[0]}
    while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
        DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
        SOURCE=$(readlink "$SOURCE")
    [[  $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
    done
        DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
}

# stop on first error
set -e

if [ $# -ne 1 ]; then
    echo "Error: the number or arguments does not match the required ones!"
    echo "Arguments accepted:"
    echo "- Option to build:"
    echo "    1. Release"
    echo "    2. Debug"
    exit 1
fi

getPath

BUILD_DIR=${DIR}/../build

if [ -d "${BUILD_DIR}" ]; then
    rm -rf ${BUILD_DIR}
fi

mkdir ${BUILD_DIR}

cd ${BUILD_DIR}
if [ $1 -eq 2 ]; then
    cmake -DCMAKE_BUILD_TYPE="Debug" ..
else
    cmake ..
fi
cmake --build .