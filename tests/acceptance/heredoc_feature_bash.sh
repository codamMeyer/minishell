#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "HEREDOC"

echo -e "cat -e << EOF
Hello world
Today date is $(date +%F)
My home directory = ${HOME}
EOF" | ./minishell > $MINISHELL_OUTPUT
removePrompt $MINISHELL_OUTPUT
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    sed -i /">"/d $MINISHELL_OUTPUT
else
    sed -i "" /">"/d $MINISHELL_OUTPUT
fi
ACTUAL=$(cat $MINISHELL_OUTPUT)

EXPECTED="$(cat -e << EOF
Hello world
Today date is $(date +%F)
My home directory = ${HOME}
EOF
)"
assertEqual "HEREDOC"
cleanUp

exit $EXIT_CODE