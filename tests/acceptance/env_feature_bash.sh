#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "ENV"



export FIRST_VAR=Hello
INPUT="env | grep FIRST_VAR"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(env | grep FIRST_VAR)
assertEqual "ENV"

INPUT="export SECOND_VAR=Testing"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt
ACTUAL=$(cat $MININHELL_OUTPUT)
export SECOND_VAR=Testing
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT"

INPUT="unset SECOND_VAR"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt
ACTUAL=$(cat $MININHELL_OUTPUT)
unset SECOND_VAR
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "UNSET"

cleanUp

exit $EXIT_CODE