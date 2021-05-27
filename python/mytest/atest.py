#!/usr/bin/python3

import sys

if __name__=='__main__':
    try:
        n = int(input("请输入人数："))
    except:
        print("输入有误！")
        sys.exit(-1)
    arr = []
    for i in range(n):
        arr.append(i+1)
    print(arr)
    left = n #剩下的人数
    count = 0 #数的数，到3归零
    index = 0 #控制arr的下标
    while(left != 1):
        if(arr[index] != -1):
            count += 1
        if(count == 3):
            arr[index] = -1
            left -= 1
            count = 0
            print(arr)
        index = (index + 1) % n


