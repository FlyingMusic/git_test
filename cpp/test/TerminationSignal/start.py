#!/usr/bin/python

import time
import subprocess
from multiprocessing import Process

#print("start...")
#subprocess.call("./test")
#print("end...")

 
class MyProcess(Process):
    def __init__(self,name):
        super(MyProcess,self).__init__()
        self.name=name

    def run(self):
        print("%s is starting " %self.name)
        subprocess.call("./test", shell=True)
 

if __name__ == '__main__':
    p1 = MyProcess('monicx1')
    p2 = MyProcess('monicx2')
    p3 = MyProcess('monicx3')
    p1.start()
    p2.start()
    p3.start()
    time.sleep(20)
    print('====main===')
