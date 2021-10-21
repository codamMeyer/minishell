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

# env var outside quotes should trim spaces
# export var+=lol

cleanUp

exit $EXIT_CODE