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

getPath

BUILD_DIR=${DIR}/../build

${BUILD_DIR}/14_Assignment