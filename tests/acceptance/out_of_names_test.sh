source ./tests/acceptance/common.sh

STD=$(echo -e "echo halla | cat -e\n echo \$?\nexit"| ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(echo halla | cat -e && echo $?)
assertEqual "./ as input and error code"
cleanUp