#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "PIPES"

INPUT="echo first test"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$($INPUT)
assertEqual "$INPUT"

INPUT='echo "This      Should Wooooork       !     |       "'
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(echo "This      Should Wooooork       !     |       ")
assertEqual "$INPUT"

INPUT="echo buillt-in with a system cmd | cat -e"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(echo buillt-in with a system cmd | cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | /../../../bin/cat -e"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | /../../../bin/cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | /bin/cat -e"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | /bin/cat -e)
assertEqual "$INPUT"

INPUT="cat tests/acceptance/bigfile | wc -l"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(cat tests/acceptance/bigfile | wc -l)
assertEqual "$INPUT"

INPUT="cat tests/acceptance/bigfile | wc -l | cat -e | cat -e"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(cat tests/acceptance/bigfile | wc -l | cat -e | cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | cat -e"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(< tests/acceptance/bigfile grep int | cat -e)
assertEqual "$INPUT"

INPUT="< tests/acceptance/bigfile grep int | cat -e > $TMP_FILE"
runMinishell "$INPUT"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(< tests/acceptance/bigfile grep int | cat -e > $TMP_FILE)
assertEqual "$INPUT"

cleanUp

exit $EXIT_CODE