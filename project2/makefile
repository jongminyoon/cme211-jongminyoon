main: main.cpp CGSolver.cpp CGSolver.hpp matvecops.cpp matvecops.hpp COO2CSR.cpp COO2CSR.hpp sparse.cpp sparse.hpp heat.cpp heat.hpp
	g++ -std=c++11 -Wall -Wextra -Wconversion -o main main.cpp CGSolver.cpp matvecops.cpp COO2CSR.cpp sparse.cpp heat.cpp

.PHONY: clean
clean:
	$(RM) main main.o CGSolver.o matvecops.o COO2CSR.o