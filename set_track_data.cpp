#include "include/rapidcsv.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "makeCSV.hpp"

using namespace std;


int main() {
    rapidcsv::Document csv("inputs/gtpl_levine.csv",
                            rapidcsv::LabelParams(0, -1),
                            rapidcsv::SeparatorParams(';'));
    vector<int> idx = {0, 1, 2, 3, 4, 5, 6};
    vector<vector<double>> cols = readCSV("selected_data", idx);

    vector<vector<double>> refline, raceline, bound_r, bound_l;
    // 0번 x_ref 
    // 1번 y_ref
    // 2번 width_right 
    // 3번 width_left 
    // 4번 x_normvec 
    // 5번 y_normvec 
    // 6번 alpha 

    for (size_t i = 0; i < cols[0].size(); ++i) {
        
        refline.push_back({cols[0][i], cols[1][i]});

        double br_x = cols[0][i] + cols[4][i] * cols[2][i];
        double br_y = cols[1][i] + cols[5][i] * cols[2][i];
        bound_r.push_back({br_x, br_y});

        double bl_x = cols[0][i] - cols[4][i] * cols[3][i];
        double bl_y = cols[1][i] - cols[5][i] * cols[3][i];
        bound_l.push_back({bl_x, bl_y});

        double rx = cols[0][i] + cols[4][i] * cols[6][i];
        double ry = cols[1][i] + cols[5][i] * cols[6][i];
        raceline.push_back({rx, ry});
    }

    makeCSV_XY("refline", refline);
    makeCSV_XY("raceline", raceline);
    makeCSV_XY("bound_r", bound_r);
    makeCSV_XY("bound_l", bound_l);

    return 0;
}
