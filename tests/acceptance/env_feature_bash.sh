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
unset SECOND_VAR$USER

INPUT='export TEST_1=1 TEST_2=2 TEST_3=3'
runMinishell "$INPUT\nenv | grep TEST"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_1=1 TEST_2=2 TEST_3=3
EXPECTED=$(env | grep TEST)
assertEqual "EXPORT more than one variable"
unset TEST_1 TEST_2 TEST_3

INPUT='export TEST_4="First env var" TEST_5=5 TEST_6=6'
runMinishell "$INPUT\nenv | grep TEST_6"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_4="First env var" TEST_5=5 TEST_6=6
EXPECTED=$(env | grep TEST_6)
assertEqual "EXPORT more than one variable with quotes"
unset TEST_4 TEST_5 TEST_6

INPUT="unset SECOND_VAR"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset SECOND_VAR
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "UNSET"

cleanUp

exit $EXIT_CODE