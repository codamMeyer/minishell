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
LAUNCH_MINISHELL_COMMAND = "./minishell"
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

	def find_start_position_for_search(self, input_string):
		return self.minishell_output.find(input_string) + len(input_string)

	def test_echo(self):
		printTestName(self.test_echo.__name__)
	
	def test_str_without_quotes(self):
		input_string = "echo Hello\nexit\n"
		expected_output = "Hello\n"

		self.echoFile.appendCommand(input_string)
		self.minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
		start_position_for_search = self.find_start_position_for_search(input_string)
		self.assertNotEqual(self.minishell_output.find(expected_output, start_position_for_search), -1)
	
	def test_str_with_quotes(self):
		input_string = 'echo "Hello      you"\nexit\n'
		expected_output = "Hello      you\n"

		self.echoFile.appendCommand(input_string)
		self.minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
		start_position_for_search = self.find_start_position_for_search(input_string)
		self.assertNotEqual(self.minishell_output.find("Hello      you\n", start_position_for_search), -1)

	def test_str_with_quotes_and_n_flag(self):
		input_string = 'echo -n "Hello      you"\nexit'
		expected_output = 'Hello      you'

		self.echoFile.appendCommand(input_string)
		self.minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
		start_position_for_search = self.find_start_position_for_search(input_string)
		self.assertNotEqual(self.minishell_output.find(expected_output, start_position_for_search), -1)

	def test_str_with_quotes_and_spaces_in_the_beginnig(self):
		input_string = 'echo "     Hello      you"\nexit'
		expected_output = '     Hello      you\n'

		self.echoFile.appendCommand(input_string)
		self.minishell_output = Minishell.runInputFile(self.echoFile).decode("utf-8")
		start_position_for_search = self.find_start_position_for_search(input_string)
		self.assertNotEqual(self.minishell_output.find(expected_output, start_position_for_search), -1)
