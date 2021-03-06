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
runWithoutQuotes "echo Hello" "echo Hello" "Simple String"
runWithoutQuotes "echo Hello      Hello" "echo Hello      Hello" "String with spaces to be trimmed"
runWithoutQuotes "echo -n-n Hello" "echo -n-n Hello" "String with invalid n flag"
runWithoutQuotes "echo $PWD" "echo \$PWD" "With env var"
runWithoutQuotes "echo $USER$" "echo \$USER$" "With $ that isn't followed by anything"
runWithoutQuotes "echo $" "echo $" "Just $"
runWithQuotes 'Hello      Hello $PWD' "echo 'Hello      Hello \$PWD'" "String with single quotes"
runWithQuotes "Hello      Hello" "echo \"Hello      Hello\"" "Quoted string, shouldn't trim"
runWithQuotes "Hello      Hello $PWD " "echo \"Hello      Hello \$PWD \"" "Quoted string, shouldn't trim and should get var name"
runWithQuotes "Hello      Hello $PWD $USER" "echo \"Hello      Hello \$PWD \$USER\"" "With many env variables"
runWithQuotes "Hello      Hello $PWDs " "echo \"Hello      Hello \$PWDs \"" "Quoted string, shouldn't trim, and variable is invalid"
runWithQuotes "                Hello      Hello" "echo \"                Hello      Hello\"" "Quoted string, shouldn't trim"

runNFlagTest "echo -n Hello" "echo -n Hello" "With valid -n flag"

cleanUp
writeReport

exit $EXIT_CODE