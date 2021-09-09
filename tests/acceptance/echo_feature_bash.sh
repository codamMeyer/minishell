#!/bin/bash
source ./tests/acceptance/common.sh

function readOutputFile ()
{
    sed -n $1p $2
}

function readMinishellOutput ()
{
    TEST=$(echo $PWD | sed "s7/77g")
    sed -i 's/\x1b\[[0-9;]*m//g' "$MININHELL_OUTPUT"
    sed -i 's///g' "$MININHELL_OUTPUT"
    sed "s7/77g" "$MININHELL_OUTPUT" > $TMP_FILE
    sed -i "s7exit77g" "$TMP_FILE"
    sed -i "s7-►77g" "$TMP_FILE"
    sed -i "s7^(TEST)77g" "$TMP_FILE"
    ACTUAL=$(readOutputFile 2 $TMP_FILE)
}


function assertNotEqual ()
{
    displayTitle "$1"
    if [[ "$ACTUAL" != *"-n"* ]]; then
        displaySuccessMessage
    else
       displayFailureMessage
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