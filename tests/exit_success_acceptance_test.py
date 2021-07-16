#!/usr/bin/python3

from pathlib import Path
import random
import subprocess
from enum import IntEnum

LIGHT_RED = "\033[1;31m"
LIGHT_GREEN = "\033[1;32m"
LIGHT_PURPLE = "\033[1;35m"
LIGHT_WHITE = "\033[0;37m"
LIGHT_YELLOW = "\033[0;33m"
RESET = "\033[0m"
RUN_COMMAND = "echo {} | ./minishell"
EXPECTED_OUTPUT = "\nExpect: {}\nActual: {}\n"

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

class ExitFeature:
    
    def __init__(self):
        self.name = "Exit test"

    def _runInput(self, command, expected):
        ret = subprocess.run(RUN_COMMAND.format(command), shell=True)
        Status.print(expected, ret.returncode)
        assert ret.returncode == int(expected)

    def _testExit(self, command, expected):
        self._runInput(command, expected)

    def runTests(self, command, expected):
        printTestBanner(self.name)
        self._testExit(command, expected)


def main():
    assert Path('./minishell').is_file()
    ExitFeature().runTests("exit", Status.SUCCESS)

main()
