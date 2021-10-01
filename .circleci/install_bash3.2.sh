#!/bin/bash

set -e

cp ./bash3.2 /bin/bash
EXPECTED_VERSION=$(bash --version | grep 3.2.48)
if [!EXPECTED_VERSION]; then
    echo "Got incorrect version of bash"
    exit 1
fi
