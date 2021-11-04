#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "Exit_code"

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

INPUT="<<< EOF cat -e\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 258)
EXPECTED="should display 258"
assertEqual "invalid redirection"
cleanUp


INPUT="cat main.c >outfile | rm outfile\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 0)
EXPECTED="should display 0"
assertEqual "return value on success"
cleanUp


exit $EXIT_CODE