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

STD=$(echo -e "./\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: ./: is a directory
126"
assertEqual "./ as input and error code"
cleanUp

STD=$(echo -e "/\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: /: is a directory
126"
assertEqual "Single Slash as arg wih return"
cleanUp

STD=$(echo -e "/ls\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: /ls: No such file or directory
127"
assertEqual "no dir or file with return"
cleanUp

STD=$(echo -e "asdfjkasvdf\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: asdfjkasvdf: command not found
127"
assertEqual "unknown command with return"
cleanUp

STD=$(echo -e "/////////\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: /////////: is a directory
126"
assertEqual "multi forward slashes with return"
cleanUp

exit $EXIT_CODE