#!/bin/bash
source ./tests/acceptance/common.sh
	
MINI_FILE_WITH_SPACES="mini      out    "
BASH_FILE_WITH_SPACES="bash      out    "

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


INPUT="cat -e >"$MINI_OUT"1 < main.c | <"$MINI_OUT"1 grep int > "$MINI_OUT"2"
cat -e >"$BASH_OUT"1 < main.c | <"$BASH_OUT"1 grep int > "$BASH_OUT"2
runMinishell "$INPUT"
check_multiple_files 2
assertEqual "Reading and outputting to multiple outfiles"
remove_multiple_files 2
cleanUp


INPUT="echo first test > $MINI_OUT"
echo first test > "$BASH_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Basic outfile"
cleanUp

INPUT="< main.c cat -e | grep int > $MINI_OUT"
< main.c cat -e | grep int > "$BASH_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Basic in and outfile"
cleanUp

INPUT="< main.c cat <Makefile -e | grep int > $MINI_OUT"
< main.c cat <Makefile -e | grep int > "$BASH_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Multiple infiles"
cleanUp

INPUT="echo halla > "$MINI_OUT"1 > "$MINI_OUT"2 > "$MINI_OUT"3"
echo halla > "$BASH_OUT"1 > "$BASH_OUT"2 > "$BASH_OUT"3
runMinishell "$INPUT"
check_multiple_files 3
assertEqual "Multiple outfiles"
remove_multiple_files 3
cleanUp

INPUT="< main.c cat -e <Makefile | grep > "$MINI_OUT"1 int > "$MINI_OUT"2 > "$MINI_OUT"3"
< main.c cat -e <Makefile | grep > "$BASH_OUT"1 int  > "$BASH_OUT"2 > "$BASH_OUT"3
runMinishell "$INPUT"
check_multiple_files 3
assertEqual "Multiple in and outfiles"
remove_multiple_files 3
cleanUp

# INPUT="cat -e >"$MINI_OUT"1 < main.c | <"$MINI_OUT"1 grep int > "$MINI_OUT"2"
# cat -e >"$BASH_OUT"1 < main.c | <"$BASH_OUT"1 grep int > "$BASH_OUT"2
# runMinishell "$INPUT"
# check_multiple_files 2
# assertEqual "Reading and outputting to multiple outfiles"
# remove_multiple_files 2
# cleanUp

INPUT="echo Rhino >"$MINI_OUT"1 Saurus >"$MINI_OUT"2 Rex >"$MINI_OUT"3"
echo Rhino >"$BASH_OUT"1 Saurus >"$BASH_OUT"2 Rex >"$BASH_OUT"3
runMinishell "$INPUT"
check_multiple_files 3
assertEqual "echo with outfiles in-between commands"
remove_multiple_files 3
cleanUp

INPUT="echo halla > \""$MINI_FILE_WITH_SPACES"\""
echo halla > "$BASH_FILE_WITH_SPACES"
runMinishell "$INPUT"
ACTUAL=$(cat "$MINI_FILE_WITH_SPACES")
EXPECTED=$(cat "$BASH_FILE_WITH_SPACES")
assertEqual 
rm -f "$MINI_FILE_WITH_SPACES" "$BASH_FILE_WITH_SPACES"
cleanUp

exit $EXIT_CODE