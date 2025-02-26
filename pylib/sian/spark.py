#!/usr/bin/env spark-submit
""" spark.py
Description
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"
__email__ = "csian7386@gmail.com"

from pyspark import SparkContext
from operator import add

import pyspark.sql.functions as fc

sc = SparkContext(appName = "Bonita")
# data = sc.textFile(FILE_NAME, N_PARTITION)
# data = sc.parallelize(PYTHON_COLLECTION, N_PARTITION)
