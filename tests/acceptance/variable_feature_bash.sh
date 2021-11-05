#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "Commands_in_variables"

INPUT="export TEST=echo\n\$TEST hello you | cat -e"
runMinishell "$INPUT"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST=echo
EXPECTED=$($TEST hello you | cat -e)
assertEqual "Variable echo"
cleanUp

INPUT="export TEST=\"echo  testing\"\n\$TEST hello you | cat -e"
runMinishell "$INPUT"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST="echo  testing"
EXPECTED=$($TEST hello you | cat -e)
assertEqual "Variable echo"
cleanUp

INPUT="export TEST=\"cat -e\"\necho hello you | \$TEST | \$TEST | \$TEST | \$TEST | \$TEST"
runMinishell "$INPUT"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST="cat -e"
EXPECTED=$(echo hello you | $TEST | $TEST | $TEST | $TEST | $TEST)
assertEqual "Variable after pipe"
cleanUp

INPUT="echo \"\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 258)
EXPECTED="should display 258"
assertEqual "return value for syntax error"
cleanUp

INPUT="<abcdef\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 1)
EXPECTED="should display 1"
assertEqual "return value for invalid file"
cleanUp

INPUT="cat main.c >outfile | rm outfile\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 0)
EXPECTED="should display 0"
assertEqual "return value for invalid file"
cleanUp

exit $EXIT_CODE