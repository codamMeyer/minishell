#!/bin/bash
source ./tests/acceptance/common.sh

printTestName "SYNTAX_CHECKER_FOR_PIPES"
runWithoutQuotes "| echo Hello" "| echo Hello" "Pipe in the beginning"

cleanUp

exit $EXIT_CODE