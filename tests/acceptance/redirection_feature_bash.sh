source ./tests/acceptance/common.sh

# function to loop through file (num file)
	# function check_that_file_exists
	# check content

function check_file_content ()
{
	if [ -f "$1" ]; then
		removePrompt "$1"
		ACTUAL=$(cat "$1")
	fi
	EXPECTED=$(cat "$2")
}

printTestName "Redirection"

INPUT="echo first test > $MINI_REDIRECT_OUT"
echo first test > "$BASH_REDIRECT_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_REDIRECT_OUT" "$BASH_REDIRECT_OUT"
assertEqual "Redirection basic"
cleanUp

exit $EXIT_CODE