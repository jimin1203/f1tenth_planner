#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "include/rapidcsv.h"

using namespace std;

void makeCSVFile (const string& filename, const vector<double>& data) {

    ofstream file("inputs/glob_inputs/"+filename+".csv");
    if (!file.is_open()) {
        cout << "파일을 열 수 없습니다." << endl;
        return;
    }

    for (const auto& val : data) file << val << '\n';  
    
    file.close();
}


int main() {
  rapidcsv::Document csv("inputs/gtpl_levine.csv",
                          rapidcsv::LabelParams(0, -1),
                          rapidcsv::SeparatorParams(';')
  );
  
  vector<string> col_names = csv.GetColumnNames(); // 벡터 생성 
  unordered_map<string, vector<double>> data_col;
//   for (auto iter:col_names) {
//     cout << iter << endl;
//   }
    for (const string& names : col_names) {
        string name = (names[0] == ' ') ? names.substr(1) : names;
        vector<double> col = csv.GetColumn<double>(names);
        data_col[name] = col;
        makeCSVFile(name, col);
    }

    return 0;
}