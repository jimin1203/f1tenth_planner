#include "makeCSV.hpp"

using namespace std;

map<string, vector<double> > multiColumns;

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

void writeCSV(const string& filename, const map<string, vector<double>>& data, char delimiter = ',') {
    ofstream file(filename);
    if (!file.is_open()) throw runtime_error("Can't open file.");

    size_t col_count = data.size();
    size_t row_count = data.begin()->second.size();

    // Header
    size_t i = 0;
    for (const auto& [key, _] : data) {
        file << key;
        if (++i != col_count) file << delimiter;
    }
    file << '\n';

    // Row data
    for (size_t row = 0; row < row_count; ++row) {
        size_t j = 0;
        for (const auto& [_, col] : data) {
            file << col[row];
            if (++j != col_count) file << delimiter;
        }
        file << '\n';
    }

    file.close();
}

void readCSV(rapidcsv::Document& csv, map<string, vector<double> >& multiColumns) {
    vector<string> col_names = csv.GetColumnNames();

    for (auto& name: col_names) {
        // cout << '"' << name << '"' << endl; 
        // cout << "-----" << endl;
        multiColumns[name] = csv.GetColumn<double>(name);
        
        // for (int i = 0; i < multiColumns[name].size(); i++)
        //     cout <<  multiColumns[name][i] << endl;
    }  
}

#if 0
// 각 열을 읽어서 모두 CSV로 만드는 함수.
// 기존에 있는 CSV를 읽는 함수. 읽을 파일을 받아오도록 한다.
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
#endif
