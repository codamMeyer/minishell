#!/usr/bin/python3
import os
import subprocess
import unittest
from utils import Minishell, File, printTestName

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
		self.minishell_output = self.minishell_output.replace("echo Hello", "")
		self.assertNotEqual(self.minishell_output.find("Hello\n"), -1)
	
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
