#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "CD"

STD=$(echo -e "cd\npwd\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(cd && pwd)
assertEqual "cd"
cleanUp

STD=$(echo -e "cd ~\npwd\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(cd ~ && pwd)
assertEqual "cd ~"
cleanUp

STD=$(echo -e "cd ../\npwd\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(cd ../ && pwd)
assertEqual "cd ../"
cleanUp

STD=$(echo -e "cd ../../\npwd\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(cd ../../ && pwd)
assertEqual "cd ../../"
cleanUp

STD=$(echo -e "cd invalid_path\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="cd: invalid_path: No such file or directory"
assertEqual "Invalid path"
cleanUp


TMP_HOME=$(echo $HOME)
unset HOME
STD=$(echo -e "cd\nexit"| ./minishell  >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="cd: HOME not set"
assertEqual "HOME UNSET"
cleanUp
export HOME=$TMP_HOME

exit $EXIT_CODE