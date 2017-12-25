#include <vector>
#include <iostream>

#include "sparse.hpp"
#include "matvecops.hpp"
#include "COO2CSR.hpp"
#include "CGSolver.hpp"

void SparseMatrix::Resize(int nrows, int ncols) {

}

void SparseMatrix::AddEntry(int i, int j, double val) {
    if (this->is_csr) {
        std::cerr << "ERROR : the matrix is already in CSR form. Cannot add entry using (i,j,val) form" << std::endl;
        return;
    }

    this->i_idx.push_back(i);
    this->j_idx.push_back(j);
    this->a.push_back(val);

    return;
}

void SparseMatrix::ConvertToCSR() {
    if (this->is_csr) return;
    else {
        COO2CSR(this->a , this->i_idx, this->j_idx);
        this->is_csr = true;
        return;
    }
}

std::vector<double> SparseMatrix::MulVec(std::vector<double> &vec) {
    if (!(this->is_csr)) SparseMatrix::ConvertToCSR();

    return matdotvec(this->a , this->i_idx, this->j_idx, vec);
}

int SparseMatrix::CGSolve(std::vector<double> &b, std::vector<double> &x, double tol, std::string soln_prefix) {
    ConvertToCSR();
    int niter = CGSolver(this->a,this->i_idx,this->j_idx,b,x,tol,soln_prefix);
    return niter;
}
