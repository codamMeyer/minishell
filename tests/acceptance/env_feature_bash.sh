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
echo -e "$TEST\nenv | grep TEST_1 exit" | ./minishell > $MININHELL_OUTPUT
ACTUAL=$(sed 4p $MININHELL_OUTPUT)
EXPECTED=$(env | grep TEST_VAR)
assertEqual "$1"

cleanUp

exit $EXIT_CODE