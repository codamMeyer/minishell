#!/bin/bash
source ./tests/acceptance/common.sh

INPUT="| echo hello | cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | cat -e  |"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "$INPUT"
cleanUp


exit $EXIT_CODE