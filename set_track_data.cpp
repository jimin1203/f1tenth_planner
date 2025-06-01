#include "include/rapidcsv.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Track {
    vector<vector<double>> refline;
    vector<vector<double>> normvec;
    vector<vector<double>> bound_r;
    vector<vector<double>> bound_l;
    vector<vector<double>> raceline;

    vector<double> x_ref;
    vector<double> y_ref;
    vector<double> width_right;
    vector<double> width_left;
    vector<double> x_normvec;
    vector<double> y_normvec;
    vector<double> alpha;
};

void makeCSVFile2D(const string& filename, const vector<vector<double>>& data) {
    ofstream file("inputs/glob_inputs/" + filename + ".csv");
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다." << endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) file << ',';  // 쉼표로 구분
        }
        file << '\n';
    }

    file.close();
}

int main() {
    rapidcsv::Document csv("inputs/gtpl_levine.csv",
                            rapidcsv::LabelParams(0, -1),
                            rapidcsv::SeparatorParams(';'));
    
    Track data;
    data.x_ref = csv.GetColumn<double>("x_ref_m");
    data.y_ref = csv.GetColumn<double>(" y_ref_m");
    data.width_right = csv.GetColumn<double>(" width_right_m");
    data.width_left = csv.GetColumn<double>(" width_left_m");
    data.x_normvec = csv.GetColumn<double>(" x_normvec_m");
    data.y_normvec = csv.GetColumn<double>(" y_normvec_m");
    data.alpha = csv.GetColumn<double>(" alpha_m");

    for (size_t i = 0; i < data.x_ref.size(); ++i) {
        
        data.refline.push_back({data.x_ref[i], data.y_ref[i]});
        data.normvec.push_back({data.x_normvec[i], data.x_normvec[i]});

        double br_x = data.x_ref[i] + data.x_normvec[i] * data.width_right[i];
        double br_y = data.y_ref[i] + data.y_normvec[i] * data.width_right[i];
        data.bound_r.push_back({br_x, br_y});

        double bl_x = data.x_ref[i] - data.x_normvec[i] * data.width_left[i];
        double bl_y = data.y_ref[i] - data.y_normvec[i] * data.width_left[i];
        data.bound_l.push_back({bl_x, bl_y});

        double rx = data.x_ref[i] + data.x_normvec[i] * data.alpha[i];
        double ry = data.y_ref[i] + data.y_normvec[i] * data.alpha[i];
        data.raceline.push_back({rx, ry});
    }

    makeCSVFile2D("refline", data.refline);
    makeCSVFile2D("raceline", data.raceline);
    makeCSVFile2D("bound_r", data.bound_r);
    makeCSVFile2D("bound_l", data.bound_l);

    return 0;
}
