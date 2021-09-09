#!/bin/bash
TITLE_COLOR='\033[0;35m'
YELLOW='\033[0;33m'
SUCCESS_COLOR='\033[1;32m'
ERROR_COLOR="\033[1;31m"
NORMAL_COLOR="\033[0m"
TMP_FILE="tmp.txt"
MININHELL_OUTPUT="output_minishell.txt"
EXIT_CODE=0

function runMinishell ()
{
    echo -e "echo $1\nexit" | ./minishell > $MININHELL_OUTPUT
}

function runBashWithQuotes ()
{
    EXPECTED=$(echo "$1")
}

function runBashWithoutQuotes ()
{
    EXPECTED=$(echo $1)
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
    rm -f $MININHELL_OUTPUT
}