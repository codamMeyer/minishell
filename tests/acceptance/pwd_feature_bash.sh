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

exit $EXIT_CODE