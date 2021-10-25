#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "ENV"

# runMinishell "export"
# removePrompt $MINISHELL_OUTPUT
# ACTUAL=$(cat $MINISHELL_OUTPUT)
# EXPECTED=$(export)
# assertEqual "ENV empty"
# cleanUp
# OLDPWD is always printed on export, but not on env

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
runMinishell "$INPUT\nenv | grep TEST_3"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_1=1 TEST_2=2 TEST_3=3
EXPECTED=$(env | grep TEST_3)
assertEqual "EXPORT more than one variable"
unset TEST_1 TEST_2 TEST_3


INPUT='export TEST_1_$USER=1 TEST_2=2 TEST_3=3'
runMinishell "$INPUT\nenv | grep TEST_3"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_1_$USER=1 TEST_2=2 TEST_3=3
EXPECTED=$(env | grep TEST_3)
assertEqual "EXPORT more than one variable with env variable in name"
unset TEST_1_$USER TEST_2 TEST_3

INPUT='export TEST_4="$PATH" TEST_5=5 TEST_6=6'
runMinishell "$INPUT\nenv | grep TEST_6"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_4="$PATH" TEST_5=5 TEST_6=6
EXPECTED=$(env | grep TEST_6)
assertEqual "EXPORT more than one variable with quotes"
unset TEST_4 TEST_5 TEST_6

runMinishell "export key='test with single quotes' TEST_5=5 TEST_6=6\nenv | grep TEST_5"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export key='test with single quotes' TEST_5=5 TEST_6=6
EXPECTED=$(env | grep TEST_5)
assertEqual "EXPORT more than one variable with single quotes"
unset TEST_4 TEST_5 TEST_6

runMinishell "export test_mixed_str=this\"is a test with mixed\"str\$USER\nenv | grep test_mixed"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export test_mixed_str=this"is a test with mixed"str$USER
EXPECTED=$(env | grep test_mixed)
assertEqual "EXPORT value with and without quotes"
unset test_mixed_str

INPUT="unset SECOND_VAR"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset SECOND_VAR
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "UNSET"


INPUT="unset"
runMinishell "$INPUT"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=""
assertEqual "UNSET without arg"


export KEY_NAME="This_should_stay" KEY="Should_unset_this_var"
INPUT="unset KEY"
runMinishell "$INPUT\nenv | grep KEY"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset KEY
EXPECTED=$(env | grep KEY)
assertEqual "UNSET test correct len"

export KEY_"$USER"="should_unset_this" 
INPUT="unset KEY_\"\$USER\""
runMinishell "$INPUT\nenv | grep KEY_"$USER""
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset KEY_"$USER"
EXPECTED=$(env | grep KEY_"$USER")
assertEqual "UNSET with key containing quotes"

export a=1 b=2 c=3 
INPUT="unset a b c"
runMinishell "$INPUT\necho \"\$a \$b \$c\" | cat -e"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset a b c
EXPECTED=$(echo "$a $b $c" | cat -e)
assertEqual "UNSET more than one variable"

export a=" TEST "
INPUT="echo \$a \"\$a\""
runMinishell "$INPUT | cat -e"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(echo $a "$a" | cat -e)
assertEqual "Variable expansion trimmed"
unset a
cleanUp

exit $EXIT_CODE