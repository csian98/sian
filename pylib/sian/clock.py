#!/usr/bin/env python
""" clock.py
Description
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"
__email__ = "csian7386@gmail.com"

import time
import functools

DEFAULT_FMT = '[{elapsed:0.8f}s] {name}({args}) -> {result}'

def clock(fmt = DEFAULT_FMT):
    """clock decorator function"""
    def decorate(func):
        @functools.wraps(func)
        def clocked(*args, **kwargs):
            t0 = time.perf_counter()
            result = func(*args, **kwargs)
            elapsed = time.perf_counter() - t0
            name = func.__name__
            arg_lst = [repr(arg) for arg in args]
            arg_lst.extend(f'{k}={v!r}' for k, v in kwargs.items())
            arg_str = ', '.join(arg_lst)
            print(fmt.format(**locals()))
            return result
        return clocked
    return decorate
