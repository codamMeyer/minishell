#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "HEREDOC"

function removeHeredocPrompt ()
{
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sed -i /">"/d $MINISHELL_OUTPUT
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        sed -i "" /">"/d $MINISHELL_OUTPUT
    fi
}


echo -e "cat -e << EOF
Hello world
Today date is $(date +%F)
My home directory = ${HOME}
EOF\nexit" | ./minishell > $MINISHELL_OUTPUT
removePrompt $MINISHELL_OUTPUT
removeHeredocPrompt
ACTUAL=$(cat $MINISHELL_OUTPUT)

EXPECTED="$(cat -e << EOF
Hello world
Today date is $(date +%F)
My home directory = ${HOME}
EOF
)"
assertEqual "HEREDOC"
cleanUp

writeReport
exit $EXIT_CODE