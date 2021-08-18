#!/usr/bin/python3
import os
from pathlib import Path
import subprocess
from enum import IntEnum
from subprocess import Popen, PIPE
import unittest

LIGHT_RED = "\033[1;31m"
LIGHT_GREEN = "\033[1;32m"
LIGHT_PURPLE = "\033[1;35m"
LIGHT_WHITE = "\033[0;37m"
LIGHT_YELLOW = "\033[0;33m"
RESET = "\033[0m"
RUN_CAT_COMMAND = "cat {}"
LAUNCH_MINISHELL_COMMAND = "./minishell_asan"
def printTestName(testName):
	print("\n{}======================= {}{}{}".format(LIGHT_PURPLE, LIGHT_YELLOW, testName, RESET))

class File:
	
	def __init__(self, filename):
		self.filename = filename
		f = open(self.filename, "w")
		f.close()

	def appendCommand(self, command):
		with open(self.filename, "a") as f:
			f.write(command)

	def getFirstLine(self):
		with open(self.filename, "r") as f:
			return f.read()

class Bash:

	@classmethod
	def runInputFile(cls, file):
		shell_input = file.getFirstLine()
		return subprocess.check_output(shell_input, shell=True)

class Minishell:

	@classmethod
	def runInputFile(cls, file):
		file.appendCommand("exit\n")
		cat_process = Popen(RUN_CAT_COMMAND.format(file.filename).split(), stdout=PIPE)
		minishell_process = subprocess.check_output(LAUNCH_MINISHELL_COMMAND, stdin=cat_process.stdout, shell=True)
		stdout, strerr = cat_process.communicate()
		assert strerr is None, "cat process returned error"
		return minishell_process


class TestEcho(unittest.TestCase):

	def setUp(self):
		self.filename = "tests/acceptance/echo_feature.txt"
		self.echoFile = File(self.filename)
	
	def tearDown(self):
		os.remove(self.filename)

	def test_echo(self):
		printTestName(self.test_echo.__name__)

	def test_empty(self):
		self.echoFile.appendCommand("echo\n")
		bash_output = Bash.runInputFile(self.echoFile)
		minishell_output = Minishell.runInputFile(self.echoFile)
		bash_len = len(bash_output.decode("utf-8").split())
		expected_split_len = 4 #4 because it will print "BestShellEver" 2 times, plus "echo", plus "exit", the '\n' doesnt count
		minishell_len = len(minishell_output.decode("utf-8").split()) - expected_split_len
		self.assertEqual(minishell_len, bash_len, "{}Should display a \\n line, but it displyed:  {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output, RESET))

	def test_empty_quotes(self):
		self.echoFile.appendCommand('echo ""\n')
		bash_output = Bash.runInputFile(self.echoFile)
		minishell_output = Minishell.runInputFile(self.echoFile)
		bash_len = len(bash_output.decode("utf-8").split())
		expected_len = 5 #5 because it will print "BestShellEver" 2 times, plus "echo", plus "", plus "exit", the '\n' doesnt count
		minishell_len = len(minishell_output.decode("utf-8").split()) - expected_len
		self.assertEqual(minishell_len, bash_len, "{}Should display a \\n line, but it displyed:  {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output, RESET))
	
	def test_str_without_quotes(self):
		self.echoFile.appendCommand("echo Hello\n")
		bash_output = Bash.runInputFile(self.echoFile).decode("utf-8")
		minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
		self.assertEqual(bash_output.split("\n")[1], minishell_output.split("\n")[3], "{}Should display a Hello\\n,  but it displyed:  {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output.split("\n")[3], RESET))
	
	def test_str_with_quotes(self):
		self.echoFile.appendCommand('echo "Hello      you"\n')
		bash_output = Bash.runInputFile(self.echoFile).decode("utf-8")
		minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
		self.assertEqual(bash_output.split("\n")[0], minishell_output.split("\n")[1], "{}Should display a 'Hello      you',  but it displyed:  {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output.split("\n")[1], RESET))

	# def test_str_with_quotes_and_n_flag(self):
	# 	self.echoFile.appendCommand('echo -n "Hello      you"\n')
	# 	bash_output = Bash.runInputFile(self.echoFile).decode("utf-8")
	# 	minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
	# 	self.assertEqual("Hello      youBestShellEver: exit", minishell_output.split("\n")[1], "{}Should display a 'Hello      youBestShellEver: exit',  but it displyed:  {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output.split("\n")[1], RESET))

	# def test_str_with_quotes_and_spaces_in_the_beginnig(self):
	# 	self.echoFile.appendCommand('echo "     Hello      you" \n')
	# 	bash_output = Bash.runInputFile(self.echoFile).decode("utf-8")
	# 	minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
	# 	print(minishell_output.split("\n")[1])
	# 	self.assertEqual("     Hello      you", minishell_output.split("\n")[1], "{}Should display a '     Hello      you',  but it displyed:  {}'{}'{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output.split("\n")[1], RESET))
