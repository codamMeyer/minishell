#!/bin/bash
source ./tests/acceptance/common.sh
RESULT=0

function compileMinishell ()
{
    make
}

compileMinishell

./tests/acceptance/echo_feature_bash.sh
RESULT+=$?

./tests/acceptance/exit_feature_bash.sh
RESULT+=$?

./tests/acceptance/pwd_feature_bash.sh
RESULT+=$?

./tests/acceptance/pipes_feature_bash.sh
RESULT+=$?

./tests/acceptance/env_feature_bash.sh
RESULT+=$?

./tests/acceptance/redirection_feature_bash.sh
RESULT+=$?

exit $RESULT