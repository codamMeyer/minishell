#!/bin/bash
TITLE_COLOR='\033[0;35m'
SUCCESS_COLOR='\033[1;32m'
ERROR_COLOR="\033[1;31m"
NORMAL_COLOR="\033[0m"
TMP="tmp.txt"
MININHELL_OUTPUT="output_minishell.txt"

function readOutputFile ()
{
    sed -n $1p $2
}


function runMinishell ()
{
    echo -e "echo $1\nexit" | ./../../minishell > $MININHELL_OUTPUT
    sed "s7/77g" "$MININHELL_OUTPUT" > $TMP
    sed -i "s7 homemoniqueDocumentsworkspacecodamMeyerminishelltestsacceptance 77g" "$TMP"
    sed -i "s7exit77g" "$TMP"
    sed -i "s7-►77g" "$TMP"
    ACTUAL=$(readOutputFile 2 $TMP)
}

function runBashWithQuotes ()
{
    EXPECTED=$(echo "$1")
}

function runBashWithoutQuotes ()
{
    EXPECTED=$(echo $1)
}

function assertEqual ()
{
    printf "$TITLE_COLOR Test case: %-40s" "$1"
    if [[ "$EXPECTED" == "$ACTUAL" ]]; then
        echo -e "$SUCCESS_COLOR[✓] $NORMAL_COLOR"
        echo "   expected: $EXPECTED"
        echo "   actual:   $ACTUAL"
    else
        echo -e "$ERROR_COLOR[✗] $NORMAL_COLOR"
        echo "   expected: $EXPECTED"
        echo "   actual:   $ACTUAL"
    fi
    echo ""
}

function assertNotEqual ()
{
    printf "$TITLE_COLOR Test case: %-40s" "$1"
    if [[ "$ACTUAL" != *"-n"* ]]; then
        echo -e "$SUCCESS_COLOR[✓] $NORMAL_COLOR"
        echo "   expected: $EXPECTED"
        echo "   actual:   $ACTUAL"
    else
        echo -e "$ERROR_COLOR[✗]$NORMAL_COLOR"
        echo "   expected: $EXPECTED"
        echo "   actual:   $ACTUAL"
    fi
    echo ""
}

function runWithoutQuotes ()
{
    runBashWithoutQuotes "$1"
    runMinishell "$2"
    assertEqual "$3"
}

function runWithQuotes ()
{
    runBashWithQuotes "$1"
    runMinishell "$2"
    assertEqual "$3"
}

function runNFlagTest ()
{
    runBashWithoutQuotes "$1"
    runMinishell "$2"
    assertNotEqual "$3"
}

runWithoutQuotes "Hello" "Hello" "Simple String"
runWithoutQuotes "Hello      Hello" "Hello      Hello" "String with spaces to be trimmed"
runWithoutQuotes "-n-n Hello" "-n-n Hello" "String with invalid n flag"
runWithQuotes "Hello      Hello" "\"Hello      Hello\"" "Quoted string, shouldn't trim"
runWithQuotes "                Hello      Hello" "\"                Hello      Hello\"" "Quoted string, shouldn't trim"
runNFlagTest "-n Hello" "-n Hello" "With valid -n flag"

rm $TMP
rm $MININHELL_OUTPUT