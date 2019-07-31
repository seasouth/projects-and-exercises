import NFA1
import time

"""
 A Python application to demonstrate the NFA1 class by
 using it to filter the standard input stream.  Those
 lines that are accepted by NFA1 are echoed to the
 standard output.
"""

try:
    s = input()
except (EOFError):
    exit()

time_of_five = 0
count = 0
while True:
    start_time = time.perf_counter()
    if NFA1.accepts(s):
        print(s)
    end_time = time.perf_counter()
    total_time = end_time - start_time
    if count < 10:
        time_of_five += total_time
        count = count + 1
    if count == 10:
        print(time_of_five)
        count = 0
    try:
        s = input()
    except (EOFError):
        exit()
