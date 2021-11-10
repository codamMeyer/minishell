source ./tests/acceptance/common.sh

STD=$(echo -e "echo halla | cat -e\n echo \$?\nexit"|  ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(echo halla | cat -e ; echo $?)
assertEqual "basic test with exit code"
cleanUp

STD=$(echo -e "exit a b c d e f\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
readMinishellOutput
EXPECTED="BestShellEver: exit: a: numeric argument required"
assertEqual "./ as input and error code"
cleanUp

INPUT="echo WORKING! > $MINI_OUT | cat -e $MINI_OUT"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(echo WORKING! > $TMP_FILE | cat -e $TMP_FILE)
assertEqual "$INPUT"
cleanUp

INPUT="unset OLDPWD | unset OLDPWD\necho \$? > $MINI_OUT | cat -e $MINI_OUT"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(unset OLDPWD | unset OLDPWD && echo $? > $TMP_FILE | cat -e $TMP_FILE)
assertEqual "$INPUT"
cleanUp

INPUT="echo $"
runMinishell "$INPUT"
readMinishellOutput
EXPECTED=$(echo $)
assertEqual "$INPUT"
cleanUp

STD=$(echo -e "cd \$NADA\n pwd\nexit"| ./minishell > $MINISHELL_OUTPUT)
readMinishellOutput
EXPECTED=$(cd $NADA &&  pwd)
assertEqual "cd non existant env var"
cleanUp

STD=$(echo -e "export | grep NONEXISTANT_VAR\n echo \$?\nexit"| ./minishell > $MINISHELL_OUTPUT)
readMinishellOutput
EXPECTED=$(export | grep NONEXISTANT_VAR ; echo $?)
assertEqual "Grep non existant var with return code"
cleanUp

STD=$(echo -e "export PATH="/usr/bin/baguette"\n ls\n echo \$?\nexit"| ./minishell >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: ls: command not found
127"
assertEqual "Removed path execution of system command"
cleanUp
