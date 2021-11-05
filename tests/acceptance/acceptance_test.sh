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
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/exit_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/pwd_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/pipes_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/env_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/redirection_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/variable_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/syntax_checker_test.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/heredoc_feature_bash.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/cd_feature_test.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/edge_cases_feature.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/error_handling.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

./tests/acceptance/exit_code_feature.sh
if [ $? -ne 0 ]; then
    RESULT=1
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    printTestName "Prompt_Display"
    echo -e "\necho hello\npwd\nexport TEST=test\nunset TEST\nenv\ncd falseDir\nls\nexit\n" | ./minishell > $MINISHELL_OUTPUT
    ACTUAL=$(cat $MINISHELL_OUTPUT | grep -e '-►' | wc -l)
    EXPECTED=9
    assertEqual "Checking if prompt is being displayed"
    cleanUp
fi

exit $RESULT