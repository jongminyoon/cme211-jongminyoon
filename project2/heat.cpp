#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>


#include "sparse.hpp"
#include "heat.hpp"
#include "CGSolver.hpp"


int HeatEquation2D::Setup(std::string inputfile) {
    std::ifstream input_f(inputfile);

    if (input_f.is_open()) {
        input_f >> this->xlen >> this->ylen >> this->h;
        input_f >> this->tc >> this->th;

        input_f.close();
    }
    else {
        std::cerr << "ERROR : Cannot read the input file" << std::endl;
        return 1;
    }

    this->nx = (int)(this->xlen/this->h);
    this->ny = (int)(this->ylen/this->h) -1; // -1 for removing the top and bottom row

    this->x.resize(this->nx*this->ny,1.);

    for (int j = 0 ; j < this->ny ; j++) {
        for (int i = 0 ; i < this->nx ; i++) {
            int center = i + this->nx*j;
            int left   = (i+nx-1)%nx + this->nx*j; // use mod nx for periodic b.c.
            int right  = (i+1)%nx + this->nx*j;    // use mod nx for periodic b.c.
            int up     = i+this->nx*(j+1);
            int down   = i+this->nx*(j-1);
            this->A.AddEntry(center, center, 4.);
            this->A.AddEntry(center, left, -1.);
            this->A.AddEntry(center, right, -1.);
            if (j==ny-1) this->b.push_back(this->th);
            else this->A.AddEntry(center, up, -1.);
            
            if (j==0) this->b.push_back(coldT(i));
            else this->A.AddEntry(center, down, -1.);

            if (j!=0 and j!=ny-1) this->b.push_back(0.);
        }
    }

    return 0;

}

double HeatEquation2D::coldT(int i_idx) {
    return -this->tc*(exp(-10*(i_idx-this->nx/2.)*(i_idx-this->nx/2.)*this->h*this->h)-2);
}


int HeatEquation2D::Solve(std::string soln_prefix) {
    int success = 0;

    double tol = 1.e-5;
    int niter = A.CGSolve(this->b, this->x, tol, soln_prefix);
    if (niter == -1) {
        niter = (int)this->x.size()+1;
        success = 1;
    }
    else {
        std::cout << "SUCCESS: CG solver converged in " << niter << " iterations." << std::endl;
    }

    int n = 0;
    while (n < niter) {
        Formatsoln(soln_prefix, n);
        n += 10;
    }
    Formatsoln(soln_prefix, niter);

    return success;

}

void HeatEquation2D::Formatsoln(std::string soln_prefix, int n) {
    std::string filename = soln_name(soln_prefix, n);
    
    std::ifstream input_f(filename);
    if (input_f.is_open()) {
        for (int i = 0 ; i < (int)this->x.size() ; i++) {
            input_f >> this->x[i];
        }
        input_f.close();
    }
    else {
        std::cerr << "ERROR : Cannot read the solution files" << std::endl;
    }

    std::ofstream sol_f(filename);
    if (sol_f.is_open()) {
        // sol_f.setf(std::ios::scientific, std::ios::floatfield);
        // sol_f.precision(4); // 4 decimal places

        for (int i = 0 ; i < this->nx+1 ; i++) {
            sol_f << this->b[i%this->nx] << " ";
        }
        sol_f << std::endl;

        for (int j = 0 ; j < this->ny ; j++) {
            for (int i = 0 ; i < this->nx+1 ; i++) {
                sol_f << this->x[i%nx + j*nx] << " ";
            }
            sol_f << std::endl;
        }

        for (int i = 0 ; i < this->nx+1 ; i++) {
            sol_f << this->th << " ";
        }
        sol_f << std::endl;

        sol_f.close();
    }

    return;
}
