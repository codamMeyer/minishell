#!/bin/bash
source ./tests/acceptance/common.sh
RESULT=0

function compileMinishell ()
{
    make
}

compileMinishell

printf "$YELLOW=========================================================\n"
printf "$TITLE_COLOR %30s \n" "ECHO"
printf "$YELLOW=========================================================$NORMAL_COLOR\n\n"

./tests/acceptance/echo_feature_bash.sh

RESULT+=$?

printf "$YELLOW=========================================================\n"
printf "$TITLE_COLOR %30s \n" "EXIT"
printf "$YELLOW=========================================================$NORMAL_COLOR\n\n"
./tests/acceptance/exit_feature_bash.sh

RESULT+=$?
exit $RESULT