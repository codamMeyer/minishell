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
EXPECTED="BestShellEver: cd: invalid_path: No such file or directory"
assertEqual "Invalid path"
cleanUp

STD=$(echo -e "cd invalid_path  ..\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: cd: invalid_path: No such file or directory"
assertEqual "Invalid path followed by .."
cleanUp

TMP_HOME=$(echo $HOME)
unset HOME
STD=$(echo -e "cd\necho \$?\nexit"| ./minishell  >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: cd: HOME not set
1"
assertEqual "HOME UNSET"
cleanUp
export HOME=$TMP_HOME

writeReport

exit $EXIT_CODE