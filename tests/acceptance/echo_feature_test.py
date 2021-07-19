#!/usr/bin/python3

from pathlib import Path
import random
import subprocess
from enum import IntEnum
from subprocess import Popen, PIPE

LIGHT_RED = "\033[1;31m"
LIGHT_GREEN = "\033[1;32m"
LIGHT_PURPLE = "\033[1;35m"
LIGHT_WHITE = "\033[0;37m"
LIGHT_YELLOW = "\033[0;33m"
RESET = "\033[0m"
RUN_COMMAND = ""
EXPECTED_OUTPUT = "Expect: {}\nActual: {}\n"

class Status(IntEnum):
    SUCCESS = 0
    ERROR = 1

    @classmethod
    def print(cls, expected, actual):
        print(EXPECTED_OUTPUT.format(expected, actual))
    

def printTestBanner(testName):
    print("{}======================================================================{}".format(LIGHT_PURPLE, LIGHT_WHITE))
    print("                          {}".format(testName))
    print("{}======================================================================{}".format(LIGHT_PURPLE, LIGHT_WHITE))

def printSeparationBanner(sectionName):
    print("{}{}{}".format(LIGHT_YELLOW, sectionName, LIGHT_WHITE))


class EchoEmptyFeature:
    
    def __init__(self):
        self.name = "Echo Empty test"
        self.filename = "tests/acceptance/echo_empty.txt"

    def _createFile(self, content):
        with open(self.filename, "w") as f:
            f.write(content)

    def _addExitToFile(self):
        with open(self.filename, "a") as f:
            f.write("exit\n")

    def _getFirstLine(self):
        with open(self.filename, "r") as f:
            return f.read()

    def _runRealShell(self):
        self._createFile("echo\n")
        shell_input = self._getFirstLine()
        self._addExitToFile()
        return subprocess.check_output(shell_input, shell=True)

    def _runMinishell(self):
        minishell_input = Popen("cat {}".format(self.filename).split(), stdout=PIPE)
        minishell_output = subprocess.check_output("./minishell", stdin=minishell_input.stdout)
        minishell_input.stdout.close()
        return minishell_output

    def _runInput(self, command, expected):
        real_shell_output = self._runRealShell()
        minishell_output = self._runMinishell()
        real_shell_len = len(real_shell_output.decode("utf-8").split())
        expected_len = 4 #4 because it will print "BestShellEver" 2 times, plus "echo", plus "exit", the '\n' doesnt count
        minishell_len = len(minishell_output.decode("utf-8").split()) - expected_len
        assert minishell_len == real_shell_len


    def _testEchoEmpty(self, command, expected):
        self._runInput(command, expected)

    def runTests(self, command, expected):
        printTestBanner(self.name)
        self._testEchoEmpty(command, expected)


def main():
    assert Path('./minishell').is_file()
    EchoEmptyFeature().runTests("echo", Status.SUCCESS)

main()
