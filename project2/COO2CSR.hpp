#ifndef COO2CSR_HPP
#define COO2CSR_HPP

#include <vector>

/* In place conversion of square matrix from COO to CSR format */
void COO2CSR(std::vector<double> &val,
             std::vector<int>    &i_idx,
             std::vector<int>    &j_idx);

#endif /* COO2CSR_HPP */
