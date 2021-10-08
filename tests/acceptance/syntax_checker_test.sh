#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "SYNTAX_CHECKER"

INPUT="| echo hello | cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | cat -e  |"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >>> cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello > > cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >>"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT=">"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello < <<"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`<<'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | >>> cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | > >> cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`>>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >1>2>3"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`1'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello| |cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello||cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="|"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo -e 'test '   '"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="Missing closing quote"
assertEqual "$INPUT"
cleanUp


INPUT="echo -e 'test '   ' ' | cat -e \"   "
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="Missing closing quote"
assertEqual "$INPUT"
cleanUp

exit $EXIT_CODE