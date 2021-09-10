#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "ENV"

export TEST_VAR=Hello
TEST="env | grep TEST_VAR"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(env | grep TEST_VAR)
assertEqual "$1"

TEST="export TEST_1=Testing"
echo -e "$TEST\nenv | grep TEST_1\nexit\n" | ./minishell > $MININHELL_OUTPUT
ACTUAL=$(sed -n 3p $MININHELL_OUTPUT)
export TEST_1=Testing
EXPECTED=$(env | grep TEST_1)
assertEqual "$1"

cleanUp

exit $EXIT_CODE