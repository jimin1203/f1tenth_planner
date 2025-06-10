#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>  
#include "include/rapidcsv.h"

#define __x_ref "x_ref_m"
#define __y_ref " y_ref_m"
#define __width_right " width_right_m"
#define __width_left " width_left_m"
#define __x_normvec " x_normvec_m"
#define __y_normvec " y_normvec_m"
#define __alpha " alpha_m"
#define __kappa " kappa_racetraj_radpm"
#define __s_racetraj " s_racetraj_m"
#define __x_raceline "x_raceline"
#define __y_raceline "y_raceline"
#define __x_bound_r "x_bound_r"
#define __y_bound_r "y_bound_r"
#define __x_bound_l "x_bound_l"
#define __y_bound_l "y_bound_l"

using namespace std;

extern map<string, vector<double> > multiColumns;

void makeCSV(const string& filename, const vector<double>& data);
void writeCSV(const string& filename, const map<string, vector<double>>& data, char delimiter);
void readCSV(rapidcsv::Document& csv, map<string, vector<double> >& multiColumns);

void computeOffsetXY(const string& alpha, int sign,
                    const string& out_x_name, const string& out_y_name);

void setTrackData(rapidcsv::Document& csv);