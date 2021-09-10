#!/bin/bash
source ./tests/acceptance/common.sh


function assertNotEqual ()
{
    displayTitle "$1"
    if [[ "$ACTUAL" != *"-n"* ]]; then
        displaySuccessMessage
    else
       displayFailureMessage
       EXIT_CODE=1
    fi
    echo ""
}

function runBashWithQuotes ()
{
    EXPECTED=$(echo "$1")
}

function runWithoutQuotes ()
{
    runBashWithoutQuotes "$1"
    runMinishell "$2"
    readMinishellOutput
    assertEqual "$3"
}

function runWithQuotes ()
{
    runBashWithQuotes "$1"
    runMinishell "$2"
    readMinishellOutput
    assertEqual "$3"
}

function runNFlagTest ()
{
    runBashWithoutQuotes "$1"
    runMinishell "$2"
    readMinishellOutput
    assertNotEqual "$3"
}

printTestName "ECHO"
runWithoutQuotes "echo Hello" "echo Hello" "Simple String"
runWithoutQuotes "echo Hello      Hello" "echo Hello      Hello" "String with spaces to be trimmed"
runWithoutQuotes "echo -n-n Hello" "echo -n-n Hello" "String with invalid n flag"
runWithQuotes "Hello      Hello" "echo \"Hello      Hello\"" "Quoted string, shouldn't trim"
runWithQuotes "                Hello      Hello" "echo \"                Hello      Hello\"" "Quoted string, shouldn't trim"
runNFlagTest "echo -n Hello" "echo -n Hello" "With valid -n flag"

cleanUp

exit $EXIT_CODE