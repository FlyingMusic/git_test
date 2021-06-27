#!/usr/bin/python3

class OpenFile(object):
    def __init__(self, input):
        print("init", input) 

    def __enter__(self):
        print("enter")
 
    def __exit__(self, exc_type, exc_val, exc_tb):
        print("exit")
 
 
def main():
    with OpenFile('text.txt') as f:
        print(f)
    print(f)
 
        
if __name__ == "__main__":
    main()
