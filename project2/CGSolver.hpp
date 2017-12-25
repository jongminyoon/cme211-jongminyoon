#ifndef CGSOLVER_HPP
#define CGSOLVER_HPP

#include <vector>
#include <string>

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
             std::string soln_prefix);

std::string soln_name(std::string soln_prefix, int niter);

void soln_write(std::string soln_prefix, int ninter, std::vector<double> &x);

#endif /* CGSOLVER_HPP */
