#!/bin/bash
source ./tests/acceptance/common.sh

function readOutputFile ()
{
    sed -n $1p $2
}

function readMinishellOutput ()
{
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS_TYPE=2
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS_TYPE=1
    fi
    ACTUAL=$(readOutputFile $OS_TYPE $MININHELL_OUTPUT)
}


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

runWithoutQuotes "Hello" "Hello" "Simple String"
runWithoutQuotes "Hello      Hello" "Hello      Hello" "String with spaces to be trimmed"
runWithoutQuotes "-n-n Hello" "-n-n Hello" "String with invalid n flag"
runWithQuotes "Hello      Hello" "\"Hello      Hello\"" "Quoted string, shouldn't trim"
runWithQuotes "                Hello      Hello" "\"                Hello      Hello\"" "Quoted string, shouldn't trim"
runNFlagTest "-n Hello" "-n Hello" "With valid -n flag"

cleanUp

exit $EXIT_CODE