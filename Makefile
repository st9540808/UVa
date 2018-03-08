CXX = g++
FLAGS = -std=c++11 -lm -lcrypt -pipe -g
PROB=10032
# use "PROB=..." to override it

Program: a.out

run: a.out
	./a.out < ./input.txt

a.out: $(PROB).cpp
	$(CXX) $< $(FLAGS) -o a.out


.PHONY: clean
clean:
	rm a.out
