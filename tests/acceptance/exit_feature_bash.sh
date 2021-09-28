#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "EXIT"

EXPECTED=0
echo "exit" | ./minishell > $TMP_FILE
ACTUAL=$?
assertEqual "Exit without argument"

EXPECTED=1
echo "exit 1" | ./minishell  > $TMP_FILE
ACTUAL=$?
assertEqual "Exit with 1 as argument"

EXPECTED=123
echo "exit 123" | ./minishell  > $TMP_FILE
ACTUAL=$?
assertEqual "Exit with 123 as argument"

cleanUp

exit $EXIT_CODE