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
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR=Testing
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT"

INPUT='export SECOND_VAR="Testing     with     quotes     $USER"'
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR="Testing     with     quotes     $USER"
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT with quotes"

INPUT='export SECOND_VAR=testing$USER$USER$'
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR=testing$USER$USER$
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT env var"

INPUT='export SECOND_VAR$USER=testing$USER$USER$'
runMinishell "$INPUT\nenv | grep SECOND_VAR$USER"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR$USER=testing$USER$USER$
EXPECTED=$(env | grep SECOND_VAR$USER)
assertEqual "EXPORT env var with variable in the key"

INPUT="unset SECOND_VAR"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset SECOND_VAR
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "UNSET"

cleanUp

exit $EXIT_CODE