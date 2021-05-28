all:d2c

d2c:libdigitToChinese.a d2c.cpp
	g++ -g d2c.cpp -o d2c -static -ldigitToChinese -L.

libdigitToChinese.a:digitToChinese.cpp digitToChinese.h
	g++ -g -c digitToChinese.cpp -o libdigitToChinese.a

clean:
	rm *.a d2c -rf

