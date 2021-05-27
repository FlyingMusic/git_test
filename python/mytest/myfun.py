#!/usr/bin/python3

import sys

def my_input(info, lable='string'):
    result = input(info)
    if lable == 'string':
        return result
    if lable == 'int':
        try:
            result = int(result)
        except:
            print("invalid input, please re-enter!!!")
            my_input(info, lable)
    if lable == 'float':
        try:
            result = float(result)
        except:
            print("invalid input, please re-enter!!!")
            my_input(info, lable)
    return result

def student_input():
    stu_info = {}
    stu_info['name'] = my_input("please input stu name：")
    stu_info['math'] = my_input("please input math score:", 'float')
    stu_info['chinese'] = my_input("please input chinese score:", 'float')
    stu_info['english'] = my_input("please input english score:", 'float')
    return stu_info

def student_output(stu):
    print("student name:", stu['name'])
    print("student math:", stu['math'])
    print("student chinese:", stu['chinese'])
    print("student english:", stu['english'])


if __name__ == '__main__':
    stu_array = []
    for i in range(3):
        stu_array.append(student_input())
    for stu in stu_array:
        student_output(stu)
