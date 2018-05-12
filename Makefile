CXX = g++
FLAGS = -std=c++11 -lm -lcrypt -pipe -g
PROB=10032.cpp
# use "PROB=*.cpp" to override it

Program: a.out

run: a.out
	./a.out < ./input.txt

get_output: a.out
	./a.out < ./input.txt | xclip -selection clipboard
get_code:
	cat $(PROB) | xclip -selection clipboard

a.out: $(PROB)
	$(CXX) $< $(FLAGS) -o a.out


.PHONY: clean
clean:
	rm a.out
