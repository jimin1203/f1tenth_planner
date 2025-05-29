#include <iostream>
#include <vector>
#include "include/rapidcsv.h"

using namespace std;

int main() {
  rapidcsv::Document csv("inputs/gtpl_levine.csv",
                          rapidcsv::LabelParams(0, -1),
                          rapidcsv::SeparatorParams(';')
  );
  
  vector<string> col_names = csv.GetColumnNames();
  map<string, vector<double>> data_col;

  for (const string& name : col_names) {
    vector<double> col = csv.GetColumn<double>(name);
    data_col[name] = col;
    
    cout << "load " << name << ": " << col.size() << endl;
  }

  return 0;
}