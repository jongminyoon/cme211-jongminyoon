#ifndef MATVECOPS_HPP
#define MATVECOPS_HPP

#include <vector>

/* check if the two vectors are of the same size */
bool same_size(std::vector<double> &a,std::vector<double> &b);

/* calculate a vector sum a = a + c*b where a,b are vectors and c is a constant */
void sum(std::vector<double> &a, std::vector<double> &b, double c);

/* scalar product c*a */
void scalarprod(std::vector<double> &a, double c);

/* dot product of the two vectors */
double dotprod(std::vector<double> &a, std::vector<double> &b);

double L2norm(std::vector<double> &a);

/* matrix-vector product when matrix is in csr format */
std::vector<double> matdotvec(std::vector<double> &val, 
				             std::vector<int>    &row_ptr,
				             std::vector<int>    &col_idx,
				             std::vector<double> &x);

#endif /* MATVECOPS_HPP */