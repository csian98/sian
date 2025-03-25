#!/usr/bin/env python
""" spinning.py
Description
	spinning decorator
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"
__email__ = "csian7386@gmail.com"

import time
import asyncio

import functools
import itertools

async def spin(msg: str) -> None:
    t0 = time.perf_counter()
    for char in itertools.cycle(r"\|/-"):
        status = f"\r{char} {msg}"
        print(status , flush = True, end = "")
        try:
            await asyncio.sleep(.1)
        except asyncio.CancelledError:
            break

    elapsed = time.perf_counter() - t0
    blanks = " " * len(status)
    filled = f"[{elapsed:0.8f}s]"
    print(f"\r{blanks}\r{filled}\n", end = "")
    
def spinning(func):
    """spinning decorator function"""
    async def decorate(*args, **kwargs):
        print(f"{func.__name__}")
        spinner = asyncio.create_task(spin("processing..."))
        result = await func()
        spinner.cancel()
        return result
    return decorate

"""
@spinning
async def complex_function():
    await asyncio.sleep(10)
    return 42

if __name__ == "__main__":
    asyncio.run(complex_function())
"""
