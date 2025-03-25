#!/usr/bin/env python
""" ipynb_rm_output.py
Description
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"
__email__ = "csian7386@gmail.com"

import os, sys
from nbformat import read, write

def strip_output(nb):
    for cell in nb.cells:
        if hasattr(cell, "outputs"):
            cell.outputs = []
        if hasattr(cell, "prompt_number"):
            del cell["prompt_number"]

if __name__ == "__main__":
    if (len(sys.argv) != 3):
        print("ipynb_rm_output.py <old .ipynb file name> <new .ipynb file name>")
        sys.exit(1)

    old_ipynb = sys.argv[1]
    new_ipynb = sys.argv[2]

    old_file_name, old_file_extension = os.path.splitext(old_ipynb)
    new_file_name, new_file_extension = os.path.splitext(new_ipynb)

    if (old_file_extension != ".ipynb") or (new_file_extension != ".ipynb"):
        print("file name required to *.ipynb")
        sys.exit(1)

    nb = read(open(old_ipynb, encoding = "utf8"), 4)
    strip_output(nb)
    write(nb, open(save_file_name, "w", encoding = "utf8"), 4)

    
