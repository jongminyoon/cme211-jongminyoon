CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Wconversion -pedantic -L/home/jmyoon/anaconda3/lib -ljpeg 

main: main.cpp image.cpp image.hpp hw6.cpp hw6.hpp 
	$(CXX) $(CXXFLAGS) main.cpp image.cpp hw6.cpp -o main

.PHONY: run
run: main
	./main

.PHONY: clean
clean:
	$(RM) main