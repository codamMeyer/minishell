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

exit $EXIT_CODE