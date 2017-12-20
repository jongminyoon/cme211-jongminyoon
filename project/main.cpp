#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "COO2CSR.hpp"
#include "CGSolver.hpp"


int main (int argc, char *argv[]){
	if (argc < 3) {
		std::cout << "Usage:" << std::endl;
		std::cout << "  " << argv[0] << " <input matrix file name> <output solution file name>" << std::endl;
		return 0;
	}

	std::string mat_name = argv[1];
	std::string sol_name = argv[2];

	std::vector<double> val;
	std::vector<int> r_idx, c_idx;
	int nrows, ncols;

	std::ifstream mat_f(mat_name);
	if (mat_f.is_open()) {
		mat_f >> nrows >> ncols;
		int row, col;
		double dat;
		while (mat_f >> row >> col >> dat) {
			r_idx.push_back(row);
			c_idx.push_back(col);
			val.push_back(dat);
		}
		mat_f.close();
	}
	else {
		std::cerr << "ERROR : Cannot read the input matrix" << std::endl;
	}

	COO2CSR(val,r_idx,c_idx);

	std::vector<double> b(ncols,0.), x(ncols,1.);

	double tol = 1.e-5;
	int niter = CGSolver(val,r_idx,c_idx,b,x,tol);

	if (niter == -1) {
		std::cout << "Solution does not converge" << std::endl;
		return 0;
	}

	std::ofstream sol_f(sol_name);
	if (sol_f.is_open()) {
		sol_f.setf(std::ios::scientific, std::ios::floatfield);
		sol_f.precision(4); // 4 decimal places

		for (auto sols : x)
			sol_f << sols << std::endl;

		sol_f.close();
	}
	std::cout << "SUCCESS: CG solver converged in " << niter << " iterations." << std::endl;

	return 0;

}