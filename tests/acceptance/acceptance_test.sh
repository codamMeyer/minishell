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

./tests/acceptance/syntax_checker_test.sh
RESULT+=$?

./tests/acceptance/cd_feature_test.sh
RESULT+=$?

exit $RESULT