#include "COO2CSR.hpp"
#include <cassert>
#include <map>
#include <vector>

/* In place conversion of square matrix from COO to CSR format */
void COO2CSR(std::vector<double>& val, std::vector<int>& i_idx,
             std::vector<int>& j_idx) {
  // assert lengths of input vectors are the same
  const auto val_size = val.size();
  assert(i_idx.size() == val_size);
  assert(j_idx.size() == val_size);

  // map from column index to value
  using ColMap = std::map<int, double>;
  // map from row index to column
  using RowMap = std::map<int, ColMap>;

  // empty map based sparse matrix
  RowMap A;
  // keep track of largest row index
  int max_row = 0;
  // add entries to map based representation
  for (std::vector<double>::size_type i = 0; i < val_size; ++i) {
    // add value to matrix
    A[i_idx[i]][j_idx[i]] += val[i];
    // update max row
    if (i_idx[i] > max_row) {
      max_row = i_idx[i];
    }
  }

  // resize row index vector
  i_idx.resize(max_row + 2);
  i_idx[0] = 0;

  // clear out old data
  val.clear();
  j_idx.clear();

  // iterate over all row indices
  for (int i = 0; i <= max_row; ++i) {
    // update row index vector
    i_idx[i + 1] = i_idx[i] + static_cast<int>(A[i].size());
    // add column indices and values
    for (auto& c : A[i]) {
      j_idx.push_back(c.first);
      val.push_back(c.second);
    }
  }
}
