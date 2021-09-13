#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "PIPES"

cases="tests/pipe_tests/commands.txt"
prompt="-►"

TEST="echo first test"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$($TEST)
assertEqual "$TEST "

TEST='echo "This      Should Wooooork       !     |       "'
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(echo "This      Should Wooooork       !     |       ")
assertEqual "$TEST "

TEST="echo buillt-in with a system command | cat -e"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(echo buillt-in with a system command | cat -e)
assertEqual "$TEST "

TEST="< tests/acceptance/bigfile grep int | /../../../bin/cat -e"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | /../../../bin/cat -e)
assertEqual "$TEST "

TEST="< tests/acceptance/bigfile grep int | /bin/cat -e"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | /bin/cat -e)
assertEqual "$TEST "

TEST="cat tests/acceptance/bigfile | wc -l"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(cat tests/acceptance/bigfile | wc -l)
assertEqual "$TEST "

TEST="cat tests/acceptance/bigfile | wc -l | cat -e | cat -e"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(cat tests/acceptance/bigfile | wc -l | cat -e | cat -e)
assertEqual "$TEST "

TEST="< tests/acceptance/bigfile grep int | cat -e"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | cat -e)
assertEqual "$TEST "

TEST="< tests/acceptance/bigfile grep int | cat -e > $TMP_FILE"
echo -e "$TEST\nexit" | ./minishell > $MININHELL_OUTPUT
sed -i "/$prompt/d" $MININHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | cat -e > $TMP_FILE)
assertEqual "$TEST "

cleanUp

exit $EXIT_CODE