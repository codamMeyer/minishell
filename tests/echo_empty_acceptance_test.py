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
        self.filename = "tests/echo_empty.txt"

    def _createFile(self, content):
        f = open(self.filename, "w")
        f.write(content)
        f.close()

    def _addExitToFile(self):
        f = open(self.filename, "a")
        f.write("exit\n")
        f.close()

    def _getFirstLine(self):
        f = open(self.filename, "r")
        return f.read()

    def _runRealShell(self):
        printSeparationBanner("Real Shell:")
        self._createFile("echo\n")
        shell_input = self._getFirstLine()
        print("RealShell: {}".format(shell_input))
        self._addExitToFile()
        return subprocess.run(shell_input, shell=True).returncode

    def _runMinishell(self):
        printSeparationBanner("Minishell:")
        minishell_input = Popen("cat {}".format(self.filename).split(), stdout=PIPE)
        minishell_output = subprocess.run("./minishell", stdin=minishell_input.stdout, stdout=PIPE, universal_newlines=True)
        print("{}".format(minishell_output.stdout))
        minishell_input.stdout.close()
        return minishell_output.returncode

    def _runInput(self, command, expected):
        real_shell_output = self._runRealShell()
        minishell_output = self._runMinishell()

        printSeparationBanner("Result:")
        Status.print(real_shell_output, minishell_output)
        assert minishell_output == real_shell_output

    def _testEchoEmpty(self, command, expected):
        self._runInput(command, expected)

    def runTests(self, command, expected):
        printTestBanner(self.name)
        self._testEchoEmpty(command, expected)


def main():
    assert Path('./minishell').is_file()
    EchoEmptyFeature().runTests("echo", Status.SUCCESS)

main()
