# MIT License
# 
# Copyright (c) 2023 Matthias Heinz
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

from sys import argv


def print_usage(code):
    print("python3 {} [files_to_process]".format(__file__))
    exit(code)


def process_include(line):
    return line.split("//")[0].strip()


def line_needs_work(line, basics_includes):
    return "#include" in line and process_include(line) in basics_includes 


def manage_line(line, basics_includes, basics_header):
    if line_needs_work(line, basics_includes):
        return "#include \"{}\"\n".format(basics_header)
    return line


if len(argv) < 2:
    print_usage(1)

if argv[1] in ["--help", "-h"]:
    print_usage(0)

BASICS_HEADER = "nui/core/basics/basics.h"
BASICS_PATH = "{}/../{}".format(
    "/".join(__file__.split("/")[:-1]),
    BASICS_HEADER,
)

IGNORE_PATTERNS = [
    "nui/core/basics",
    "lib"
]

FILES_TO_PROCESS = argv[1:]


with open(BASICS_PATH) as f:
    BASICS_INCLUDES = {process_include(line) for line in f if "#include" in line}


for f in FILES_TO_PROCESS:
    f = f.replace("//", "/")
    # Check if we should skip
    skip = False
    for x in IGNORE_PATTERNS:
        if x in f:
            skip = True
    if skip:
        print(f"Skipping {f}")
        continue

    # First pass to check if we need to do anything
    print(f"Checking {f}")
    needs_work = False
    with open(f) as fin:
      for line in fin:
          needs_work = line_needs_work(line, BASICS_INCLUDES)
          if needs_work:
              break
    if not needs_work:
        continue
    
    print(f"Processing {f}")
    with open(f) as fin:
        lines = [manage_line(line, BASICS_INCLUDES, BASICS_HEADER) for line in fin]
    
    with open(f, "w") as fout:
        for line in lines:
            fout.write(line)
          


