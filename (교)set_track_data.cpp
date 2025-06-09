#include "include/rapidcsv.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "makeCSV.hpp"

#include <map>

using namespace std;

void getTrueColumnNames(rapidcsv::Document& csv, vector<string>& col_names_out) {
    vector<string> col_names = csv.GetColumnNames();

    for (auto& name : col_names) {
        name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char c){ return std::isspace(c); }), name.end());
        cout << '"' << name << '"' << endl;
        col_names_out.push_back(name);
    }
}

#define __x_ref_m "x_ref_m"

int main() {
    map<string, vector<double> > multiColumns;

    rapidcsv::Document csv("inputs/gtpl_levine.csv",
                            rapidcsv::LabelParams(0, -1),
                            rapidcsv::SeparatorParams(';'));

    vector<string> true_col_names;
    getTrueColumnNames(csv, true_col_names);
    for (auto& name: true_col_names)
        cout << '"' << name << '"' << endl; 

    vector<double> col_vec;
    for (auto& col_name: true_col_names) {
        //col_vec.clear();
        vector<double> col_vec = csv.GetColumn<double>(col_name);
        multiColumns[col_name] = col_vec;

        cout << "---" << col_name << endl;
        for (auto& val: col_vec)
            cout << val << endl;
    }

    cout << "x_ref_m:" << endl;
    col_vec = multiColumns[__x_ref_m];
    for (int i = 0; i < col_vec.size(); i++)
        cout <<  col_vec[i] << endl;

    return 0;
}


