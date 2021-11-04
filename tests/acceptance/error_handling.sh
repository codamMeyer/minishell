#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "Inavlid_filename"

STD=$(echo -e "cat -e <1 <main.c | cat -e\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: 1: No such file or directory"
assertEqual "Invalid filename should stop execution"
cleanUp

STD=$(echo -e "cat -e main.c | ls | echo\necho \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="
0"
assertEqual "ls after pipe shouldn't give error 13"
cleanUp

exit $EXIT_CODE