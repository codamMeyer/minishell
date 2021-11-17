#!/bin/bash

source ./tests/acceptance/common.sh

function run ()
{
    runBashWithoutQuotes "$1"
    runMinishell "$1"
    readMinishellOutput
    assertEqual "$2"
}

printTestName "PWD"

run "pwd" "Just pwd"
run "pwd blah blah echo" "pwd followed by random things"
cleanUp


STD=$(echo -e "mkdir test\ncd test\nrm -r ../test\npwd\nexit" | ./minishell > $MINISHELL_OUTPUT)
removePrompt $MINISHELL_OUTPUT
ACTUAL=$(cat $MINISHELL_OUTPUT)
EXPECTED=$(mkdir test && cd test && rm -r ../test && pwd)
assertEqual "pwd within a removed file"
cleanUp

writeReport
exit $EXIT_CODE