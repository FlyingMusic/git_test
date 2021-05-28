#!/bin/python3
# -*- coding: UTF-8 -*-

import time

#print(*objects, sep=' ', end='\n', file=sys.stdout, flush=False)

print(time.time())
print(time.localtime(time.time()))

print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), flush=True)
time.sleep(1)
print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), flush=True)

print="print"
print("print")
