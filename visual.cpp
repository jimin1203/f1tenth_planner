#define _USE_MATH_DEFINES
#include <cmath>
#include "include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

#if 1
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

bool readXYcsv(const string& filename, vector<double>& xs, vector<double>& ys)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string x_str, y_str;
        if (!getline(ss, x_str, ',')) continue;
        if (!getline(ss, y_str, ',')) continue;

        xs.push_back(stod(x_str));
        ys.push_back(stod(y_str));
    }
    return true;
}

int main(int argc, char *argv[])
{
    vector<double> x_left, y_left;
    vector<double> x_right, y_right;
    vector<double> x_refline, y_refline;
    vector<double> x_raceline, y_raceline;
    vector<double> x_sampling, y_sampling;

    if (!readXYcsv("inputs/glob_inputs/bound_l.csv", x_left, y_left)) return -1;
    if (!readXYcsv("inputs/glob_inputs/bound_r.csv", x_right, y_right)) return -1;
    if (!readXYcsv("inputs/glob_inputs/refline.csv", x_refline, y_refline)) return -1;
    if (!readXYcsv("inputs/glob_inputs/raceline.csv", x_raceline, y_raceline)) return -1;
    if (!readXYcsv("inputs/glob_inputs/sampling_xy.csv", x_sampling, y_sampling)) return -1;

	// Clear previous plot
	plt::clf();

	// Plot line from given x and y data. Color is selected automatically.
	plt::plot(x_left, y_left, {{"color", "black"}});
	plt::plot(x_right, y_right, {{"color", "black"}});
    plt::plot(x_refline, y_refline, {{"color", "blue"}});
    plt::plot(x_raceline, y_raceline, {{"color", "red"}});
    plt::scatter(x_sampling, y_sampling, 40.0, {{"color", "pink"}});

	plt::title("Track");
    plt::grid(true);
	plt::axis("equal");
	plt::show();

	return 0;
}
#endif




#if 0
int main()
{
	int n = 1000;
	std::vector<double> x, y, z;

	for(int i=0; i<n; i++) {
		x.push_back(i*i);
		y.push_back(sin(2*M_PI*i/360.0));
		z.push_back(log(i));

		if (i % 10 == 0) {
			// Clear previous plot
			plt::clf();
			// Plot line from given x and y data. Color is selected automatically.
			plt::plot(x, y);
			// Plot a line whose name will show up as "log(x)" in the legend.
			plt::named_plot("log(x)", x, z);

			// Set x-axis to interval [0,1000000]
			plt::xlim(0, n*n);

			// Add graph title
			plt::title("Sample figure");
			// Enable legend.
			plt::legend();
			// Display plot continuously
			plt::pause(0.01);
		}
	}
}
#endif 