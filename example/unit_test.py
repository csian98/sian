#!/usr/bin/env python
""" unit_test.py
Description
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"
__email__ = "csian7386@gmail.com"

import pytest
#from pylib.sian import *

class Multiply:
    def __call__(self, a, b):
        return a * b

@pytest.fixture
def FIXTURE():
    fixture = Multiply()
    return fixture

@pytest.mark.parametrize(
    "a, b, expected",
    [(1, 2, 2),
     (2, 3, 6)]
)
def test_multiply(FIXTURE, a, b, expected):
    assert FIXTURE(a, b) == expected

