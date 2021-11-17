#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "SYNTAX_CHECKER"

INPUT="| echo hello | cat -e"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | cat -e  |"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >>> cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello > > cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >>"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT=">"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`newline'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello < <<"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`<<'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | >>> cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello | > >> cat -e"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`>>'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello >1>2>3"
STD=$(echo -e "$INPUT\nexit" | ./minishell 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`1'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello| |cat -e"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo hello||cat -e"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="|"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: syntax error near unexpected token \`|'"
assertEqual "$INPUT"
cleanUp

INPUT="echo -e 'test '   '"
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: Missing closing quote"
assertEqual "$INPUT"
cleanUp

INPUT="echo -e 'test '   ' ' | cat -e \"   "
STD=$(echo -e "$INPUT\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: Missing closing quote"
assertEqual "$INPUT"
cleanUp

STD=$(echo -e "cat <abc <main.c\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: abc: No such file or directory"
assertEqual "Invalid file and cat command"
cleanUp

STD=$(echo -e "<Filename cat -e\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: Filename: No such file or directory"
assertEqual "Invalid in file and cat command"
cleanUp

STD=$(echo -e "<Filename | cat -e\nexit" | ./$MINISHELL_PROGRAM 2> $MINISHELL_OUTPUT)
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: Filename: No such file or directory"
assertEqual "Invalid in file and cat command after pipe"
cleanUp

writeReport
exit $EXIT_CODE