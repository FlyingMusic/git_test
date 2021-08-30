import os, time

if __name__ == '__main__':
    
    t0 = time.time()
    sum = 0
    for i in range(0, 10000000):
        sum += i
    print sum
    t1 = time.time()
    
    print('%d'%int((t1-t0)*1000))

