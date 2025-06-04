#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>  
#include "include/rapidcsv.h"

using namespace std;

// 벡터 받으면 CSV에 만들어서 저장하는 함수 
void makeCSV(const string& filename, const vector<double>& data) {
    ofstream file("inputs/glob_inputs/" + filename + ".csv");
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다." << endl;
        return;
    }

    file << std::fixed << std::setprecision(7);  // << 여기서 정밀도 설정!
    for (const auto& val : data)
        file << val << '\n';

    file.close();
}

void makeCSV_XY(const string& filename, const vector<vector<double>>& data) {
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

void addCSV_XY(const string& filename,
                const vector<double>& x,
                const vector<double>& y) {

    if (x.size() != y.size()) {
        cerr << "x와 y 벡터의 크기가 다릅니다!" << std::endl;
        return;
    }

    ofstream file("inputs/glob_inputs/" + filename + ".csv");
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return;
    }


    for (size_t i = 0; i < x.size(); ++i) {
        file << x[i] << "," << y[i] << "\n";
    }

    file.close();
}

// 각 열을 읽어서 모두 CSV로 만드는 함수.
vector<vector<double>> readCSV(const string& filename,
            const vector<int>& idxs) {
  rapidcsv::Document csv("inputs/gtpl_levine.csv",
                          rapidcsv::LabelParams(0, -1),
                          rapidcsv::SeparatorParams(';')
  );
  
  vector<string> col_names = csv.GetColumnNames(); // 벡터 생성 
  vector<vector<double>> selected_col;

//   for (auto iter:col_names) {
//     cout << iter << endl;
//   }
    for (int idx: idxs) {
        string name = col_names[idx];
        cout << name << endl;
        if (name[0] == ' ') name = name.substr(1);
        vector<double> col = csv.GetColumn<double>(name);
        makeCSV(name, col);
        selected_col.push_back(col);
    }
    makeCSV_XY("select", selected_col);
    return selected_col;
}