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
	   check_file_content "mini_"$c"" "bash_"$c""
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

# INPUT="cat -e >"$MINI_OUT"1 < main.c | <"$MINI_OUT"1 grep int > "$MINI_OUT"2"
# cat -e > "$BASH_OUT"1 < main.c | < "$BASH_OUT"1 grep int > "$BASH_OUT"2
# runMinishell "$INPUT"
# check_multiple_files 2
# assertEqual "Reading and outputting to multiple outfiles"
# remove_multiple_files 2
# cleanUp

INPUT="echo first test > $MINI_OUT"
echo first test > "$BASH_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Basic outfile"
cleanUp

INPUT="< main.c > $MINI_OUT"
< main.c > "$BASH_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "In and outfile with no command"
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
assertEqual "File name with spaces"
rm -f "$MINI_FILE_WITH_SPACES" "$BASH_FILE_WITH_SPACES"
cleanUp


INPUT1="echo halla1 >>            $MINI_OUT"
INPUT2="echo halla2 >>$MINI_OUT"
echo halla1 >>            $BASH_OUT && echo halla2 >> $BASH_OUT
runMinishell "$INPUT1"
runMinishell "$INPUT2"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Append mode >> with and without spaces before the file name"
cleanUp

INPUT1="cat -e < main.c | grep int >            $MINI_OUT"
INPUT2="echo halla2 >>$MINI_OUT"
cat -e < main.c | grep int >            $BASH_OUT && echo halla2 >> $BASH_OUT
runMinishell "$INPUT1"
runMinishell "$INPUT2"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Multi_pipes with system and built-in command, in/output with append mode"
cleanUp


# <> is valid only if no spaces are in between
# >< is invalid

INPUT="<> main.c grep int > $MINI_OUT"
<> main.c grep int > "$BASH_OUT"
runMinishell "$INPUT"
check_file_content "$MINI_OUT" "$BASH_OUT"
assertEqual "Diamond brackets <>"
cleanUp

export A="APPLE"
STD=$(echo -e "echo hello >mini_\"\$A\"_test apple test\nexit" | ./minishell > $MINISHELL_OUTPUT)
echo hello >bash_"$A"_test apple test
check_file_content "mini_APPLE_test" "bash_APPLE_test"
assertEqual "Test with variable in filename double quotes"
rm mini_APPLE_test bash_APPLE_test

# STD=$(echo -e "echo hello >\$A hello apple test |cat -e APPLE\nexit" | ./minishell > $MINISHELL_OUTPUT)
# removePrompt $MINISHELL_OUTPUT
# ACTUAL=$(cat $MINISHELL_OUTPUT | grep "test")
# rm APPLE
# EXPECTED=$(echo hello >$A hello apple test |cat -e APPLE)
# assertEqual "Test with variable in filename no quotes"
# rm APPLE

# STD=$(echo -e "echo hello >'\$A' apple hello test |cat -e \$A\nexit" | ./minishell > $MINISHELL_OUTPUT)
# removePrompt $MINISHELL_OUTPUT
# ACTUAL=$(cat $MINISHELL_OUTPUT | grep "test")
# rm '$A'
# EXPECTED=$(echo hello >'$A' apple hello test |cat -e '$A')
# assertEqual "Test with variable in filename, but inside single quotes"
# rm '$A'

exit $EXIT_CODE