#!/bin/python
# -*- coding: UTF-8 -*-

import re
import sys

date = raw_input("data:")
print "data: %s" % date

date = re.split("[ ,.-]",date)

try:
    year = int(date[0])
    month = int(date[1])
    day = int(date[2])
except:
    info = sys.exc_info() 
    print info[0],":",info[1]
    sys.exit(-1)

print "year: %d" % year
print "month: %d" % month
print "day: %d" % day

is_leap_year = year%4==0 and year%100!=0 or year%400==0
print "is_leap_year:", is_leap_year

month_arry = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

day_num = day
for i in range(len(month_arry)):
    if i >= month-1:
        break;
    day_num += month_arry[i]

if month > 2 and is_leap_year:
    day_num += 1

print "day_num = %d" % day_num
