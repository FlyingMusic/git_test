#!/bin/python3
# -*- coding: UTF-8 -*-

if __name__ == "__main__":
    char_cnt = 0
    num_cnt = 0
    space_cnt = 0
    other_cnt = 0
    str = input("请输出字符串:")
    for c in str:
        if c >= 'a' and c <= 'z' or c >= 'A' and c <= 'Z':
           char_cnt += 1
        elif c == ' ':
            space_cnt += 1
        elif c >= '0' and c <= '9':
            num_cnt += 1
        else:
            other_cnt += 1

    print("char_cnt = %d" % (char_cnt))
    print("space_cnt = %d" % (space_cnt))
    print("num_cnt = %d" % (num_cnt))
    print("other_cnt = %d" % (other_cnt))

