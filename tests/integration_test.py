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
EXPECT_OK = "Expect ok"
EXPECT_ERROR = "Expect Error"
EXPECT_DEATH = "Expect Death"

class Status(IntEnum):
    SUCCESS = 0
    ERROR = 1

    @classmethod
    def print(cls, expected):
        if expected == cls.OK:
            print(EXPECT_OK)
        else:
            print(EXPECT_ERROR)

def printTestBanner(testName):
    print("{}======================================================================{}".format(LIGHT_PURPLE, LIGHT_WHITE))
    print("                          {}".format(testName))
    print("{}======================================================================{}".format(LIGHT_PURPLE, LIGHT_WHITE))

class ExitFeature:
    
    def __init__(self):
        self.name = "Exit test"

    def _runInput(self, command):
        ret = subprocess.run(RUN_COMMAND.format(command), shell=True)
        assert ret.returncode == int(Status.SUCCESS)

    def _testExit(self, command):
        self._runInput(command)

    def runTests(self, command):
        printTestBanner(self.name)
        self._testExit(command)


def main():
    assert Path('./minishell').is_file()
    ExitFeature().runTests("exit")

main()
