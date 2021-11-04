#!/bin/bash
source ./tests/acceptance/common.sh


EXPECTED=$(ec"ho" hello)
STD=$(echo -e "ec\"ho\" hello\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "With quotes in echo name"

STD=$(echo -e "export LS=\"s -l\"\nl\$LS\"a\"\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep d | wc)
export LS="s -l"
EXPECTED=$(l$LS"a" | grep d | wc)
assertEqual "Weird LS | grep d | wc"
unset LS

STD=$(echo -e "cat /dev/urandom | base64 | head -c 100 | wc -c\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export LS="s -l"
EXPECTED=$(cat /dev/urandom | base64 | head -c 100 | wc -c)
assertEqual "Weird random test"
unset LS
cleanUp

exit $EXIT_CODE