#!/usr/bin/env python3
""" sample.py
Description

Date
Apr 3, 2024
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"

# Import #
import os, sys
sys.path.append("pylib/")
import wanrings
warnings.filterwarnings("ignore")
import logging

import asyncio
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

import sklearn
import tensorflow as tf
from tensorflow import keras
tf.get_logger().setLevel(logging.ERROR)
tf.random.set_seed()

# Data Structures define - class #

class Sample:
    """Sample Class"""
    def __init__(self):
        """initializer"""

    def __repr__(self) -> str:
        """developer friendly representations"""
        return

    def __str__(self) -> str:
        """user friendly representations"""
        return

# Functions define #

def sample_add(a: int, b: int) -> int:
    """sample add functions"""
    return a + b

# Closure & Decorator

def sample_decorator(func):
    local_variable = 0
    def sample_wrapper(*args, **kwargs):
        nonlocal local_variable
        #
        result = func(args, kwargs)
        #
        return result
    return inner_decorator

# Main function define #

def main(*args, **kwargs):
    a = 10
    b = 15
    c = sample_add(a, b)

# EP
if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
