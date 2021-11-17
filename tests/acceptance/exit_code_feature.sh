#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "Exit_code"

INPUT="echo \"\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 258)
EXPECTED="should display 258"
assertEqual "return value for syntax error"
cleanUp

INPUT="echo Hello\necho \"should display \$?\"\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 0)
EXPECTED="should display 0"
assertEqual "\$? inside quotes"
cleanUp

INPUT="<abcdef\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 1)
EXPECTED="should display 1"
assertEqual "return value for invalid file"
cleanUp

INPUT="<<< EOF cat -e\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 258)
EXPECTED="should display 258"
assertEqual "invalid redirection"
cleanUp


INPUT="cat main.c >outfile | rm outfile\necho should display \$?\nexit"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT | grep 0)
EXPECTED="should display 0"
assertEqual "return value on success"
cleanUp

INPUT="exit abc123"
echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: abc123: numeric argument required"
assertEqual "Invalid exit arg"
cleanUp

INPUT="exit -1"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="255"
assertEqual "Exit with negative arg"
cleanUp

# long max + 1
INPUT="exit 9223372036854775808"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: 9223372036854775808: numeric argument required"
assertEqual "Exit with long max + 1"
cleanUp

# long max
INPUT="exit 9223372036854775807"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: 9223372036854775807: numeric argument required"
assertEqual "Exit with long max"
cleanUp

INPUT="exit 9223372036854775800000"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: 9223372036854775800000: numeric argument required"
assertEqual "Exit with big zero ending overflow"
cleanUp

INPUT="exit -9223372036854775809"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: -9223372036854775809: numeric argument required"
assertEqual "Long min - 1"
cleanUp

INPUT="exit -9223372036854775808"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="0"
assertEqual "Exit with long min"
cleanUp

INPUT="exit -92233720369760"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="160"
assertEqual "Exit with minus overflow"
cleanUp

INPUT="exit 1"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="1"
assertEqual "Base test 1"
cleanUp

INPUT="exit 0"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="0"
assertEqual "Base test 0"
cleanUp

INPUT="exit 123         456\nexit"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: too many arguments"
assertEqual "exit with too many arguments"
cleanUp

INPUT="export test=69\nexit \$test"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="69"
assertEqual "Exit with env var"
cleanUp

INPUT="export test=\nexit \$test"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="0"
assertEqual "Exit with env var without value"
cleanUp

INPUT="exit 123 *\nexit"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: too many arguments"
assertEqual "@ args, one non alphanum"
cleanUp

INPUT="exit *\nexit"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: exit: *: numeric argument required"
assertEqual "2 args, one non alphanum"
cleanUp

INPUT="exit *"
STD=$(echo -e "$INPUT" | ./$MINISHELL_PROGRAM)
ACTUAL=$(echo $?)
EXPECTED="255"
assertEqual "Non alphanum arg"
cleanUp

writeReport
exit $EXIT_CODE