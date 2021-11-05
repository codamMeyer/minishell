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

echo -e "export MINISHELL_LEVEL_1=1\n./minishell\nenv | grep MINISHELL_LEVEL_1\nexit\nexit" | ./minishell > $MINISHELL_OUTPUT
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="MINISHELL_LEVEL_1=1"
assertEqual "Passing updated env"
unset LS
cleanUp

STD=$(echo -e "cat /dev/urandom | base64 | head -c 100 | wc -c\nexit" | ./minishell > 1)
removePrompt 1
ACTUAL=$(cat 1)
export LS="s -l"
EXPECTED=$(cat /dev/urandom | base64 | head -c 100 | wc -c)
assertEqual "Weird random test"
unset LS
rm 1
cleanUp


exit $EXIT_CODE