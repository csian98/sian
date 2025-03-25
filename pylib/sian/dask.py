#!/usr/bin/env python
""" dask.py
Description
	dask client
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"
__email__ = "csian7386@gmail.com"

from dask.distributed import Client, progress
import dask.dataframe as dd

if __name__ == "__main__":
    client = Client()
    client
