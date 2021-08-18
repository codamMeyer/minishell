#!/usr/bin/python3
import unittest
from pathlib import Path
from exit_feature_test import TestExit
from echo_feature_test import TestEcho
from pwd_feature_test import TestPWD

if __name__ == '__main__':
    assert Path("./minishell_asan").is_file()
    unittest.main()
