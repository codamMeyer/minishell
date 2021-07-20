#!/usr/bin/python3

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
EXPECTED_OUTPUT = "Expect: {}\nActual: {}\n"

class File:
    
    def __init__(self, filename, content):
        self.filename = "tests/acceptance/echo_empty.txt"
        self._write(content)

    def _write(self, content):
        with open(self.filename, "w") as f:
            f.write(content)

    def appendExitCommand(self):
        with open(self.filename, "a") as f:
            f.write("exit\n")

    def getFirstLine(self):
        with open(self.filename, "r") as f:
            return f.read()

class Bash:

    @classmethod
    def runInputFile(cls, file):
        shell_input = file.getFirstLine()
        file.appendExitCommand()
        return subprocess.check_output(shell_input, shell=True)

class Minishell:

    @classmethod
    def runInputFile(cls, file):
        file.appendExitCommand()
        cat_process = Popen(RUN_CAT_COMMAND.format(file.filename).split(), stdout=PIPE)
        minishell_process = subprocess.check_output(LAUNCH_MINISHELL_COMMAND, stdin=cat_process.stdout)
        stdout, strerr = cat_process.communicate()
        assert strerr is None, "cat process returned error"
        return minishell_process

class TestEcho(unittest.TestCase):

    def test_empty(self):
        self.echoFile = File("tests/acceptance/echo_feature.txt", "echo\n")
        bash_output = Bash.runInputFile(self.echoFile)
        minishell_output = Minishell.runInputFile(self.echoFile)
        bash_len = len(bash_output.decode("utf-8").split())
        expected_len = 4 #4 because it will print "BestShellEver" 2 times, plus "echo", plus "exit", the '\n' doesnt count
        minishell_len = len(minishell_output.decode("utf-8").split()) - expected_len
        self.assertEqual(minishell_len, bash_len, "{}Should display a \\n line, but it displyed:  {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output, RESET))


if __name__ == '__main__':
    assert Path('./minishell').is_file()
    unittest.main()
