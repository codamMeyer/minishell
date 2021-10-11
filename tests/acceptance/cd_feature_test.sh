#!/bin/bash
source ./tests/acceptance/common.sh

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

TMP_HOME=$(echo $HOME)
unset HOME
STD=$(echo -e "cd"| ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="cd: HOME not set"
assertEqual "HOME UNSET"
cleanUp
export HOME=$TMP_HOME

exit $EXIT_CODE