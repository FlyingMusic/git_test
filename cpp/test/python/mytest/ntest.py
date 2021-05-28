#!/bin/python3
# -*- coding: UTF-8 -*-

import datetime
import ftest

if __name__ == '__main__':
    # 输出今日日期，格式为 dd/mm/yyyy。
    print(datetime.date.today().strftime('%d/%m/%Y'))

    # 创建日期对象
    birthDate = datetime.date(1991, 5, 15)

    print(birthDate.strftime('%d/%m/%Y'))

    # 日期算术运算
    birthNextDay = birthDate + datetime.timedelta(days=1)

    print(birthNextDay.strftime('%d/%m/%Y'))
    
    # 日期替换
    firstBirthDay = birthDate.replace(year=birthDate.year + 1)

    print(firstBirthDay.strftime('%d/%m/%Y'))
