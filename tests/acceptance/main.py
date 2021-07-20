#!/usr/bin/python3
import unittest
from pathlib import Path
from exit_feature_test import TestExit
from echo_feature_test import TestEcho

if __name__ == '__main__':
    assert Path("./minishell").is_file()
    unittest.main()
