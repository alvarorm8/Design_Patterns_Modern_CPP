# ©2023-2024 Airbus Defence and Space GmbH
# ©2023-2024 Indra Sistemas SA, Indra Factoria Tecnologica
# ©2023-2024 Thales SIX GTS France SAS, Thales AVS France SAS, Thales LAS France SAS, Thales DMS France SAS
# Export Controlled ML22
# VS nur für den Dienstgebrauch
# NGWS RESTRICTED

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

${BUILD_DIR}/14_PointerChain