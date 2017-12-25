#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "CGSolver.hpp"
#include "matvecops.hpp"

/* Function that implements the CG algorithm for a linear system
 *
 * Ax = b
 *
 * where A is in CSR format.  The starting guess for the solution
 * is provided in x, and the solver runs a maximum number of iterations
 * equal to the size of the linear system.  Function returns the
 * number of iterations to converge the solution to the specified
 * tolerance, or -1 if the solver did not converge.
 */

int CGSolver(std::vector<double> &val, 
             std::vector<int>    &row_ptr,
             std::vector<int>    &col_idx,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol,
             std::string soln_prefix) {

	int nitermax = (int)x.size();
	if (!same_size(x,b)) return 0;
	std::vector<double> r = b;
	std::vector<double> Ax = matdotvec(val,row_ptr,col_idx,x);
	sum(r, Ax,-1.);
	double norm0 = L2norm(r);
	std::vector<double> p = r;
	int niter = 0;
	soln_write(soln_prefix, niter, x);

	while (niter < nitermax) {
		niter += 1;
		std::vector<double> Ap = matdotvec(val,row_ptr,col_idx,p);
		double rr = dotprod(r,r);
		double alpha = rr/dotprod(p, Ap);
		sum(x, p, alpha);
		sum(r, Ap, -alpha);
		double norm = L2norm(r);
		if (norm/norm0 < tol) break;
		if (niter%10 == 0) soln_write(soln_prefix, niter, x);
		double beta = norm*norm/rr;
		scalarprod(p,beta);
		sum(p,r,1.);
	}

	soln_write(soln_prefix, niter, x);

	if (niter <= nitermax) return niter;
	else return -1;
}

std::string soln_name(std::string soln_prefix, int niter) {
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << niter;
    std::string s = soln_prefix;
    s += ss.str();
    s += ".txt";
    return s;
}

void soln_write(std::string soln_prefix, int niter, std::vector<double> &x) {

	std::string s = soln_name(soln_prefix, niter);

	std::ofstream sol_f(s);
	if (sol_f.is_open()) {
		// sol_f.setf(std::ios::scientific, std::ios::floatfield);
		// sol_f.precision(4); // 4 decimal places

		for (auto sols : x)
			sol_f << sols << std::endl;

		sol_f.close();
	}

	return;
}

