#!/bin/bash

source ./tests/acceptance/common.sh

printTestName "ENV"

INPUT="export SECOND_VAR=Testing"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR=Testing
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT"
cleanUp

INPUT='export SECOND_VAR="Testing     with     quotes     $USER"'
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR="Testing     with     quotes     $USER"
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT with quotes"
cleanUp

INPUT='export SECOND_VAR=testing$USER$USER$'
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR=testing$USER$USER$
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "EXPORT env var"
cleanUp

INPUT='export SECOND_VAR$USER=testing$USER$USER$'
runMinishell "$INPUT\nenv | grep SECOND_VAR$USER"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export SECOND_VAR$USER=testing$USER$USER$
EXPECTED=$(env | grep SECOND_VAR$USER)
assertEqual "EXPORT env var with variable in the key"
cleanUp
unset SECOND_VAR$USER

INPUT='export TEST_1=1 TEST_2=2 TEST_3=3'
runMinishell "$INPUT\nenv | grep TEST_3"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_1=1 TEST_2=2 TEST_3=3
EXPECTED=$(env | grep TEST_3)
assertEqual "EXPORT more than one variable"
cleanUp
unset TEST_1 TEST_2 TEST_3

INPUT='export TEST_1_$USER=1 TEST_2=2 TEST_3=3'
runMinishell "$INPUT\nenv | grep TEST_3"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_1_$USER=1 TEST_2=2 TEST_3=3
EXPECTED=$(env | grep TEST_3)
assertEqual "EXPORT more than one variable with env variable in name"
cleanUp
unset TEST_1_$USER TEST_2 TEST_3

INPUT='export TEST_4="$PATH" TEST_5=5 TEST_6=6'
runMinishell "$INPUT\nenv | grep TEST_6"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export TEST_4="$PATH" TEST_5=5 TEST_6=6
EXPECTED=$(env | grep TEST_6)
assertEqual "EXPORT more than one variable with quotes"
cleanUp
unset TEST_4 TEST_5 TEST_6

INPUT='export A=a B=$A C=$B'
runMinishell "$INPUT\necho \$A\$B\$C"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export A=a B=$A C=$B
EXPECTED=$(echo $A$B$C)
assertEqual "EXPORT use variable exported in the same line"
cleanUp
unset A B C

runMinishell "export key='test with single quotes' TEST_5=5 TEST_6=6\nenv | grep TEST_5"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export key='test with single quotes' TEST_5=5 TEST_6=6
EXPECTED=$(env | grep TEST_5)
assertEqual "EXPORT more than one variable with single quotes"
cleanUp
unset TEST_4 TEST_5 TEST_6

runMinishell "export test_mixed_str=this\"is a test with mixed\"str\$USER\nenv | grep test_mixed"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export test_mixed_str=this"is a test with mixed"str$USER
EXPECTED=$(env | grep test_mixed)
assertEqual "EXPORT value with and without quotes"
cleanUp
unset test_mixed_str

runMinishell "export DUMMY test1=hello DUMMY2 test2=you\necho \$DUMMY\$test1\$DUMMY2\$test2"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export DUMMY test1=hello DUMMY2 test2=you
EXPECTED=$(echo $DUMMY$test1$DUMMY2$test2)
assertEqual "EXPORT with loose word in between"
cleanUp
unset test1 test2

runMinishell "export DUMMY DUMMY1 test1=hello DUMMY2 test2=you\necho \$DUMMY\$DUMMY1\$test1\$DUMMY2\$test2"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
export DUMMY DUMMY1 test1=hello DUMMY2 test2=you
EXPECTED=$(echo $DUMMY$DUMMY1$test1$DUMMY2$test2)
assertEqual "EXPORT with two consecutive loose words in between"
cleanUp
unset test1 test2

echo -e "export \"DUMMY \"test1=hello \"DUMMY2 \"test2=you\necho \$DUMMY\$test1\$DUMMY2\$test2\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: export: \`DUMMY test1=hello': not a valid identifier
BestShellEver: export: \`DUMMY2 test2=you': not a valid identifier"
assertEqual "EXPORT with space between quotes (should be part of key)"
cleanUp
unset test1 test2

echo -e "export test = test\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1 
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: export: \`=': not a valid identifier"
assertEqual "EXPORT = with spaces in both sides"
cleanUp
unset test1 test2

export TEST="$USER "
echo -e "export \"$TEST\"test1=hello \"DUMMY2 \"test2=you\necho \$DUMMY\$test1\$DUMMY2\$test2\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: export: \`$USER test1=hello': not a valid identifier
BestShellEver: export: \`DUMMY2 test2=you': not a valid identifier"
assertEqual "EXPORT with variable containing space between quotes (should be part of key)"
cleanUp
unset test1 test2

echo -e "export =test\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="BestShellEver: export: \`=test': not a valid identifier"
assertEqual "EXPORT missing key"
cleanUp

export TEST="ls       -la"
echo -e "echo \$TEST\nexit" | ./$MINISHELL_PROGRAM > $MINISHELL_OUTPUT
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(echo $TEST)
assertEqual "EXPORT with variable outside quotes"
cleanUp

echo -e "export test\"=\"hello\necho \$test\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="hello"
assertEqual "EXPORT missing key"
cleanUp

echo -e "export \"test=hello\"\necho \$test\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="hello"
assertEqual "EXPORT missing key"
cleanUp

echo -e "export EQUAL=\"=\"\nexport this_should_work\"\$EQUAL\"hehe\necho \$this_should_work\nexit" | ./$MINISHELL_PROGRAM >> $MINISHELL_OUTPUT 2>&1
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED="hehe"
assertEqual "EXPORT missing key"
cleanUp


INPUT="unset SECOND_VAR"
runMinishell "$INPUT\nenv | grep SECOND_VAR"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset SECOND_VAR
EXPECTED=$(env | grep SECOND_VAR)
assertEqual "UNSET"
cleanUp

INPUT="unset"
runMinishell "$INPUT"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=""
assertEqual "UNSET without arg"
cleanUp

export KEY_NAME="This_should_stay" KEY="Should_unset_this_var"
INPUT="unset KEY"
runMinishell "$INPUT\nenv | grep KEY"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset KEY
EXPECTED=$(env | grep KEY)
assertEqual "UNSET test correct len"
cleanUp

export KEY_"$USER"="should_unset_this" 
INPUT="unset KEY_\"\$USER\""
runMinishell "$INPUT\nenv | grep KEY_"$USER""
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset KEY_"$USER"
EXPECTED=$(env | grep KEY_"$USER")
assertEqual "UNSET with key containing quotes"
cleanUp

export a=1 b=2 c=3 
INPUT="unset a b c"
runMinishell "$INPUT\necho \"\$a \$b \$c\" | cat -e"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
unset a b c
EXPECTED=$(echo "$a $b $c" | cat -e)
assertEqual "UNSET more than one variable"
cleanUp

export a=" TEST       test     "
INPUT="echo \$a \"\$a\" \$a"
runMinishell "$INPUT | cat -e"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(echo $a "$a" $a | cat -e)
assertEqual "Variable expansion trimmed"
cleanUp
unset a

INPUT="echo \$\"USER\""
runMinishell "$INPUT | cat -e"
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(echo $"USER" | cat -e)
assertEqual "echo $\"USER\""
cleanUp

writeReport
exit $EXIT_CODE