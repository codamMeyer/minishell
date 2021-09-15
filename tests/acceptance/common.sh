#!/bin/bash
TITLE_COLOR='\033[0;35m'
YELLOW='\033[0;33m'
SUCCESS_COLOR='\033[1;32m'
ERROR_COLOR="\033[1;31m"
NORMAL_COLOR="\033[0m"
TMP_FILE="tmp.txt"
MINISHELL_OUTPUT="output_minishell.txt"
EXIT_CODE=0
MINI_REDIRECT_OUT="mini_outfile"
BASH_REDIRECT_OUT="bash_outfile"

function printTestName ()
{
    printf "$YELLOW=========================================================\n"
    printf "$TITLE_COLOR %30s \n" $1
    printf "$YELLOW=========================================================$NORMAL_COLOR\n\n"
}

function runMinishell ()
{
    echo -e "$1\nexit" | ./minishell > $MINISHELL_OUTPUT
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
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS_TYPE=2
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        OS_TYPE=1
    fi
    ACTUAL=$(readOutputFile $OS_TYPE $MINISHELL_OUTPUT)
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
    displayTitle "$1"
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
    rm -f $MINI_REDIRECT_OUT
    rm -f $BASH_REDIRECT_OUT
}

function removePrompt ()
{
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        sed -i "/-►/d" $1
    fi
}