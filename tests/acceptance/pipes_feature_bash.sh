#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "PIPES"

prompt="-►"

function runMinishell ()
{
    echo -e "$1\nexit" | ./minishell > $MINISHELL_OUTPUT
    readMinishellOutput
}

INPUT="echo first test"
runMinishell "$INPUT"
EXPECTED=$($INPUT)
assertEqual "$INPUT"

INPUT='echo "This      Should Wooooork       !     |       "'
runMinishell "$INPUT"
EXPECTED=$(echo "This      Should Wooooork       !     |       ")
assertEqual "$INPUT"

INPUT="echo buillt-in with a system command | cat -e"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(echo buillt-in with a system command | cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | /../../../bin/cat -e"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | /../../../bin/cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | /bin/cat -e"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | /bin/cat -e)
assertEqual "$INPUT"

INPUT="cat tests/acceptance/bigfile | wc -l"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(cat tests/acceptance/bigfile | wc -l)
assertEqual "$INPUT"

INPUT="cat tests/acceptance/bigfile | wc -l | cat -e | cat -e"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(cat tests/acceptance/bigfile | wc -l | cat -e | cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | cat -e"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | cat -e > $TMP_FILE"
echo -e "$INPUT\nexit" | ./minishell > $MINISHELL_OUTPUT
sed -i "/$prompt/d" $MINISHELL_OUTPUT
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | cat -e > $TMP_FILE)
assertEqual "$INPUT"

cleanUp

exit $EXIT_CODE