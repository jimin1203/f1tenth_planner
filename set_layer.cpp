#include "include/rapidcsv.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
  rapidcsv::Document kappa_c("inputs/glob_inputs/kappa_racetraj_radpm.csv",
                            rapidcsv::LabelParams(-1, -1));
  rapidcsv::Document s_raceline_c("inputs/glob_inputs/s_racetraj_m.csv", 
                            rapidcsv::LabelParams(-1, -1));

  vector<double> kappa = kappa_c.GetColumn<double>(0);
  vector<double> s_raceline = s_raceline_c.GetColumn<double>(0);

  vector<double> delta_s;
  for (size_t i = 0; i < s_raceline.size()-1; ++i) {
    // if (i==0) delta_s.push_back(0);
    delta_s.push_back(s_raceline[i+1] - s_raceline[i]);
}
  // for (size_t i = 0; i < 5; ++i)
  //       cout << "delta_s["<< i<< "]" << delta_s[i] << endl;

}