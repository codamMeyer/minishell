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

function check_multiple_files ()
{
	for (( c=1; c<=$1; c++ ))
	do  
	   check_file_content mini_"$c" bash_"$c"
	done
}

function remove_multiple_files
(
	for (( c=1; c<=$1; c++ ))
	do  
	   rm -f mini_"$c" bash_"$c"
	done
)

printTestName "Redirection"

INPUT="echo first test > $MINI_OUT"1
echo first test > "$BASH_OUT"1
runMinishell "$INPUT"
check_file_content "$MINI_OUT"1 "$BASH_OUT"1
assertEqual "Redirection basic"
cleanUp

exit $EXIT_CODE