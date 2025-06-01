#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>  
#include "include/rapidcsv.h"

using namespace std;

// 벡터 받으면 CSV에 만들어서 저장하는 함수 
void makeCSVFile(const string& filename, const vector<double>& data) {
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


// 각 열을 읽어서 모두 CSV로 만드는 함수.
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