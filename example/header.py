#!/usr/bin/env python
""" header.py
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
os.environ["TF_CPP_MIN_LOG_LEVEL"] = '2'
sys.path.append("pylib/")
import wanrings
warnings.filterwarnings("ignore")
import logging

import asyncio
import operator as ops
import functools
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

import sklearn
import tensorflow as tf
from tensorflow import keras
from keras import backend as K
from kears.utils.generic_utils import get_custom_objects
from scikeras.wrappers import KerasClassifier
tf.get_logger().setLevel(logging.ERROR)
tf.random.set_seed()
