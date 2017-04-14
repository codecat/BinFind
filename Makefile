test: main.cpp BinFind.cpp BinFind.h
	g++ -ggdb main.cpp BinFind.cpp -o test

clean:
	rm test
