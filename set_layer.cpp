#include "include/rapidcsv.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "include/config.h"

using namespace std;

vector<int> variable_step_size(const vector<double>& kappa,
                               const vector<double>& dist,
                               double d_curve,
                               double d_straight,
                               double curve_th) {
    double next_dist = 0.0;
    double next_dist_min = 0.0;
    double cur_dist = 0.0;
    vector<int> idx_array;

    for (size_t idx = 0; idx < kappa.size(); ++idx) {
        double kappa_val = kappa[idx];
        double dist_val = dist[idx];

        if ((cur_dist + dist_val) > next_dist_min) {
            if (fabs(kappa_val) > curve_th) {
                next_dist = cur_dist;
            }
        }

        if ((cur_dist + dist_val) > next_dist) {
            idx_array.push_back(static_cast<int>(idx));

            if (fabs(kappa_val) < curve_th) { // 직선 구간
                next_dist += d_straight;
            } else { // 곡선 구간
                next_dist += d_curve;
            }
            next_dist_min = cur_dist + d_curve;
        }

        cur_dist += dist_val;
    }


    return idx_array;
}

int main() {
  rapidcsv::Document kappa_c("inputs/glob_inputs/kappa_racetraj_radpm.csv",
                            rapidcsv::LabelParams(-1, -1));
  rapidcsv::Document s_raceline_c("inputs/glob_inputs/s_racetraj_m.csv", 
                            rapidcsv::LabelParams(-1, -1));
  rapidcsv::Document raceline_c("inputs/glob_inputs/raceline.csv",
                            rapidcsv::LabelParams(-1, -1));

  vector<double> kappa = kappa_c.GetColumn<double>(0);
  vector<double> s_raceline = s_raceline_c.GetColumn<double>(0);
  // 구간별 s 저장 
  vector<double> delta_s;
  for (size_t i = 0; i < s_raceline.size()-1; ++i) {
    // if (i==0) delta_s.push_back(0);
    delta_s.push_back(s_raceline[i+1] - s_raceline[i]);
}

  // cout << delta_s.size() << endl;
  // for (size_t i = 0; i < 5; ++i)
  //       cout << "delta_s["<< i<< "]" << fixed << setprecision(7) << delta_s[i] << endl;

  vector<double> rx = raceline_c.GetColumn<double>(0);
  vector<double> ry = raceline_c.GetColumn<double>(1);
  
  double x_start = rx.front();
  double y_start = ry.front();

  // 끝점
  double x_end = rx.back();
  double y_end = ry.back();

  // 유클리드 거리 계산
  double dx = x_start - x_end;
  double dy = y_start - y_end;
  double dist = sqrt(dx * dx + dy * dy); // distance = 0.0543304

  Offline_Params params;
  // 판단
  if (dist < params.CLOSURE_DETECTION_DIST) { // 임계값: 0.1
      cout << "폐회로" << endl;
  } else {
      cout << "개방 회로" << endl;
  }

  vector<int> idx_array = variable_step_size(kappa, 
                                            delta_s, 
                                            params.LON_CURVE_STEP, 
                                            params.LON_STRAIGHT_STEP,
                                            params.CURVE_THR);
  
  cout << idx_array.size();
                                            // for (int i = 0; i < )
}