#!/bin/bash
TITLE_COLOR='\033[0;35m'
YELLOW='\033[0;33m'
SUCCESS_COLOR='\033[1;32m'
ERROR_COLOR="\033[1;31m"
NORMAL_COLOR="\033[0m"
TMP_FILE="tmp.txt"
MINISHELL_OUTPUT="output_minishell.txt"
EXIT_CODE=0
MINI_OUT="mini_"
BASH_OUT="bash_"
prompt="-►"
MINISHELL_PROGRAM=minishell
function printTestName ()
{
    printf "$YELLOW=========================================================\n"
    printf "$TITLE_COLOR %30s \n" $1
    printf "$YELLOW=========================================================$NORMAL_COLOR\n\n"
}

function runMinishell ()
{
    echo -e "$1\nexit" | ./$MINISHELL_PROGRAM > $MINISHELL_OUTPUT
}

function runBashWithoutQuotes ()
{
    EXPECTED=$($1)
}

function readOutputFile ()
{
    sed -n $1p $2
}

function readMinishellOutput ()
{
    removePrompt $MINISHELL_OUTPUT
    ACTUAL=$(readOutputFile 1 $MINISHELL_OUTPUT)
}

function displayTitle ()
{
    printf "$YELLOW Test case:$TITLE_COLOR %-40s" "$1"
}

function displaySuccessMessage ()
{
    echo -e "$SUCCESS_COLOR[✓] $NORMAL_COLOR"
    echo "   expected: $EXPECTED"
    echo "   actual:   $ACTUAL"
}

function displayFailureMessage ()
{
    echo -e "$ERROR_COLOR[✗] $NORMAL_COLOR"
    echo "   expected: $EXPECTED"
    echo "   actual:   $ACTUAL"
}

function assertEqual ()
{
    displayTitle "$1 "
    if [[ "$EXPECTED" == "$ACTUAL" ]]; then
        displaySuccessMessage
    else
       displayFailureMessage
       EXIT_CODE=1
    fi
    echo ""
}

function cleanUp ()
{
    rm -f $TMP_FILE
    rm -f $MINISHELL_OUTPUT
    rm -f $MINI_OUT
    rm -f $BASH_OUT
}

function removePrompt ()
{
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sed -i "/-►/d" $1
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        sed -i "" "/-►/d" $1
    fi
}