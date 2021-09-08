#!/bin/bash
SUCCESS_COLOR='\033[1;32m'
ERROR_COLOR="\033[1;31m"
NORMAL_COLOR="\033[0m"

function readOutputFile ()
{
    sed -n $1p $2
}

function runMinishell ()
{
    # printf "minishell $1\n"
    echo -e "echo $1\nexit" | ./../../minishell > output_minishell.txt
    ACTUAL=$(readOutputFile 2 output_minishell.txt)
}

function runBashWithQuotes ()
{
    EXPECTED=$(echo "$1")
}

function runBashWithoutQuotes ()
{
    # printf "bash $1\n"
    EXPECTED=$(echo $1)
}

function asserEqual ()
{
    if [[ "$EXPECTED" == "$ACTUAL" ]]; then
        echo "   expected: |$EXPECTED|"
        echo "   actual:   |$ACTUAL|"
        echo -e "$SUCCESS_COLOR✓ $NORMAL_COLOR"
    else
        echo "   expected: |$EXPECTED|"
        echo "   actual:   |$ACTUAL|"
        echo -e "$ERROR_COLOR✗$NORMAL_COLOR"
    fi
}

function runWithoutQuotes ()
{
    runBashWithoutQuotes "$1"
    runMinishell "$2"
    asserEqual
}

function runWithQuotes ()
{
    runBashWithQuotes "$1"
    runMinishell "$2"
    asserEqual
}

runWithoutQuotes "Hello" "Hello"
runWithoutQuotes "Hello      Hello" "Hello      Hello"
runWithoutQuotes "-n Hello" "-n Hello"
runWithoutQuotes "-n-n Hello" "-n-n Hello"
runWithQuotes "Hello      Hello" "\"Hello      Hello\""
runWithQuotes "                Hello      Hello" "\"                Hello      Hello\""
