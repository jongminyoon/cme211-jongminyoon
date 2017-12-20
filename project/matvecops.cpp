#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

bool same_size(std::vector<double> &a,std::vector<double> &b) {
	if (a.size()!=b.size()) {
		std::cerr << "ERROR : two vectors are of different sizes" << std::endl;
		return false;
	}
	return true;
}

void sum(std::vector<double> &a, std::vector<double> &b, double c) {
	if (!same_size(a,b)) return;
	for (unsigned int i = 0 ; i < a.size() ; i++) 
		a[i] += c*b[i];
}

void scalarprod(std::vector<double> &a, double c) {
	for (unsigned int i = 0 ; i < a.size() ; i++) 
		a[i] *= c;
}

double dotprod(std::vector<double> &a, std::vector<double> &b) {
	if (!same_size(a,b)) return 0.;
	double sum = 0.;
	for (unsigned int i = 0 ; i < a.size() ; i++) 
		sum += a[i]*b[i];
	return sum;
}

double L2norm(std::vector<double> &a) {
	return std::sqrt(dotprod(a,a));
}

std::vector<double> matdotvec(std::vector<double> &val, 
				             std::vector<int>    &row_ptr,
				             std::vector<int>    &col_idx,
				             std::vector<double> &x) {

	std::vector<double> b;
	
	/* check the sizes of matrix and vector are good for multiplication*/
	unsigned int max_col = *std::max_element(col_idx.begin(), col_idx.end());
	if (max_col+1 > x.size()) {
		std::cerr << "ERROR : matrix size bigger than x" << std::endl;
		return b;
	}

	for (unsigned int i = 0 ; i < row_ptr.size()-1 ; i++) {
		double temp = 0.;
		for (int j = row_ptr[i] ; j < row_ptr[i+1] ; j++) 
			temp += val[j]*x[col_idx[j]];
		b.push_back(temp);
	}
	return b;
}