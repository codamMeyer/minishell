#!/bin/bash
source ./tests/acceptance/common.sh
RESULT=0

function compileMinishell ()
{
    make
    make minishell_asan
}

if [ $# -ne 1 ]; then
    MINISHELL_PROGRAM=minishell_asan
fi

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

./tests/acceptance/variable_feature_bash.sh
RESULT+=$?

./tests/acceptance/syntax_checker_test.sh
RESULT+=$?

./tests/acceptance/heredoc_feature_bash.sh
RESULT+=$?

./tests/acceptance/cd_feature_test.sh
RESULT+=$?


if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    printTestName "Prompt_Display"
    echo -e "\necho hello\npwd\nexport TEST=test\nunset TEST\nenv\ncd falseDir\nls\nexit\n" | ./minishell > $MINISHELL_OUTPUT
    ACTUAL=$(cat $MINISHELL_OUTPUT | grep -e '-►' | wc -l)
    EXPECTED=9
    assertEqual "Checking if prompt is being displayed"
    cleanUp
fi

exit $RESULT