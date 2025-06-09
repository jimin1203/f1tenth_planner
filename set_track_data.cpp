#include "include/rapidcsv.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "makeCSV.hpp"

using namespace std;

void computeXY(
    const string& alpha, int sign,
    const string& out_x_name, const string& out_y_name
) {
    size_t N = multiColumns.at(__x_ref).size();
    vector<double> x_out(N), y_out(N);

    for (size_t i = 0; i < N; ++i) {
        x_out[i] = multiColumns.at(__x_ref)[i] + sign * multiColumns.at(__x_normvec)[i] * multiColumns.at(alpha)[i];
        y_out[i] = multiColumns.at(__y_ref)[i] + sign * multiColumns.at(__y_normvec)[i] * multiColumns.at(alpha)[i];
    }

    multiColumns[out_x_name] = x_out;
    multiColumns[out_y_name] = y_out;
}

int main() {
    rapidcsv::Document csv("inputs/gtpl_levine.csv",
                            rapidcsv::LabelParams(0, -1),
                            rapidcsv::SeparatorParams(';'));
    
    readCSV(csv, multiColumns);

    // 연산 총 3O(N)번 돌아감.
    computeXY(__width_right, +1, "x_bound_r", "y_bound_r");
    computeXY(__width_left, -1, "x_bound_l", "y_bound_l");
    computeXY(__alpha, +1, "x_raceline", "y_raceline");

    return 0;
}
