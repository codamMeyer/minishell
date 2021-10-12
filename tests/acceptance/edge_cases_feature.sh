#!/bin/bash
source ./tests/acceptance/common.sh


EXPECTED=$(ec"ho" hello)
STD=$(echo -e "ec\"ho\" hello\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
assertEqual "With quotes in echo name"


# export var+=lol
# env var outside quotes should trim spaces
#  export LS=“s -l”    -- l$LS"a"
# ls ""
# ec"ho"
# cat << EOF and  cat << 'EOF'
# echo -n -n -n
# echo -nnnn
# EcHO

cleanUp

exit $EXIT_CODE