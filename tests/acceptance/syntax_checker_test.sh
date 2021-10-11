#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "SYNTAX_CHECKER"

INPUT="| echo hello | cat -e"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | cat -e  |"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "$INPUT"
cleanUp

INPUT="echo hello| |cat -e"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "$INPUT"
cleanUp

INPUT="echo hello||cat -e"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "$INPUT"
cleanUp

INPUT="|"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "$INPUT"
cleanUp

INPUT="echo -e 'test '   '"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="Missing closing quote"
assertEqual "$INPUT"
cleanUp


INPUT="echo -e 'test '   ' ' | cat -e \"   "
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="Missing closing quote"
assertEqual "$INPUT"
cleanUp

exit $EXIT_CODE