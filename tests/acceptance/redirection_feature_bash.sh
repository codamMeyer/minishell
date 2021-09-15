source ./tests/acceptance/common.sh

function check_file_content ()
{
	if [ -f "$MINI_REDIRECT_OUT" ]; then
		removePrompt "$MINI_REDIRECT_OUT"
		ACTUAL=$(cat "$MINI_REDIRECT_OUT")
	fi
	EXPECTED=$(cat "$BASH_REDIRECT_OUT")
}

printTestName "Redirection"

INPUT="echo"
echo first test > "$BASH_REDIRECT_OUT"
runMinishell "$INPUT"
check_file_content
assertEqual "Redirection basic"
cleanUp
