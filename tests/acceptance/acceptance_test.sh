#!/bin/bash
source ./tests/acceptance/common.sh
RESULT=0

function compileMinishell ()
{
    make
    make minishell_asan
}

function updateResult ()
{
    if [ $1 -ne 0 ]; then
        RESULT=1
    fi
}

if [ $# -ne 1 ]; then
    MINISHELL_PROGRAM=minishell_asan
fi

compileMinishell

./tests/acceptance/echo_feature_bash.sh
updateResult $?

./tests/acceptance/exit_feature_bash.sh
updateResult $?

./tests/acceptance/pwd_feature_bash.sh
updateResult $?

./tests/acceptance/pipes_feature_bash.sh
updateResult $?

./tests/acceptance/env_feature_bash.sh
updateResult $?

./tests/acceptance/redirection_feature_bash.sh
updateResult $?

./tests/acceptance/variable_feature_bash.sh
updateResult $?

./tests/acceptance/syntax_checker_test.sh
updateResult $?

./tests/acceptance/heredoc_feature_bash.sh
updateResult $?

./tests/acceptance/cd_feature_test.sh
updateResult $?

./tests/acceptance/edge_cases_feature.sh
updateResult $?

./tests/acceptance/error_handling.sh
updateResult $?

./tests/acceptance/exit_code_feature.sh
updateResult $?

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    printTestName "Prompt_Display"
    echo -e "\necho hello\npwd\nexport TEST=test\nunset TEST\nenv\ncd falseDir\nls\nexit\n" | ./minishell > $MINISHELL_OUTPUT
    ACTUAL=$(cat $MINISHELL_OUTPUT | grep -e '-►' | wc -l)
    EXPECTED=9
    assertEqual "Checking if prompt is being displayed"
    cleanUp
fi

exit $RESULT