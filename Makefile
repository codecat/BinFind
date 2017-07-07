test: main.cpp BinFind.cpp BinFind.h
	g++ -std=c++11 -ggdb main.cpp BinFind.cpp -o test

clean:
	rm test
