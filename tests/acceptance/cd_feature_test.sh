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

exit $EXIT_CODE