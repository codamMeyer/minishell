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

class Minishell:

    @classmethod
    def runInputFile(cls, file):
        cat_process = Popen(RUN_CAT_COMMAND.format(file.filename).split(), stdout=PIPE)
        minishell_process = subprocess.run(LAUNCH_MINISHELL_COMMAND, stdin=cat_process.stdout, stdout=subprocess.DEVNULL)
        stdout, strerr = cat_process.communicate()
        assert strerr is None, "cat process returned error"
        return minishell_process

class TestExit(unittest.TestCase):

    def setUp(self):
        self.filename = "tests/acceptance/exit_feature.txt"
        self.exitFile = File(self.filename)
    
    def tearDown(self):
        os.remove(self.filename)
    
    def test_exit(self):
        printTestName(self.test_exit.__name__)

    def test_exit_success(self):
        self.exitFile.appendCommand("exit\n")
        minishell_output = Minishell.runInputFile(self.exitFile)
        expected_output = 0
        self.assertEqual(expected_output, minishell_output.returncode, "{}Exit command should return 0 but returned: {}{}{}".format(LIGHT_RED, LIGHT_YELLOW, minishell_output.returncode, RESET))
