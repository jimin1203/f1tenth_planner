#include <Eigen/Dense>
#include <vector>
#include <cmath>
#include <iostream>

using namespace Eigen;
using namespace std;

struct SplineResult {
    MatrixXd coeffs_x;
    MatrixXd coeffs_y;
    MatrixXd M;
    MatrixXd normvec_normalized;
};

VectorXd computeEuclideanDistances(const MatrixXd& path) {
    int N = path.rows() - 1;
    VectorXd dists(N);
    for (int i = 0; i < N; ++i) {
        dists(i) = (path.row(i + 1) - path.row(i)).norm();
    }
    return dists;
}

SplineResult calcSplines(const MatrixXd& path, const VectorXd* el_lengths = nullptr,
                         double psi_s = NAN, double psi_e = NAN,
                         bool use_dist_scaling = true) {
    MatrixXd updated_path = path;
    bool closed = (path.row(0) - path.row(path.rows() - 1)).norm() < 1e-6;

    if (closed) {
        updated_path.conservativeResize(path.rows() + 1, NoChange);
        updated_path.row(path.rows()) = path.row(1);
    }

    int no_splines = updated_path.rows() - 1;
    VectorXd ds;
    if (el_lengths == nullptr) {
        ds = computeEuclideanDistances(updated_path);
    } else {
        ds = *el_lengths;
    }

    MatrixXd M = MatrixXd::Zero(no_splines * 4, no_splines * 4);
    VectorXd b_x = VectorXd::Zero(no_splines * 4);
    VectorXd b_y = VectorXd::Zero(no_splines * 4);

    for (int j = 0; j < no_splines; ++j) {
        int row0 = j * 4;
        M(row0, row0) = 1;
        b_x(row0) = updated_path(j, 0);
        b_y(row0) = updated_path(j, 1);

        RowVector4d T;
        double d = ds(j);
        T << 1, d, pow(d, 2), pow(d, 3);

        M(row0 + 1, row0) = T(0);
        M(row0 + 1, row0 + 1) = T(1);
        M(row0 + 1, row0 + 2) = T(2);
        M(row0 + 1, row0 + 3) = T(3);

        b_x(row0 + 1) = updated_path(j + 1, 0);
        b_y(row0 + 1) = updated_path(j + 1, 1);
    }

    for (int j = 0; j < no_splines - 1; ++j) {
        int row = 2 * no_splines + j;
        double d = ds(j);
        RowVector4d T;
        T << 0, 1, 2 * d, 3 * pow(d, 2);
        for (int k = 0; k < 4; ++k) {
            M(row, 4 * j + k) = T(k);
            M(row, 4 * (j + 1) + k) = -T(k);
        }
    }

    for (int j = 0; j < no_splines - 1; ++j) {
        int row = 3 * no_splines - 1 + j;
        double d = ds(j);
        RowVector4d T;
        T << 0, 0, 2, 6 * d;
        for (int k = 0; k < 4; ++k) {
            M(row, 4 * j + k) = T(k);
            M(row, 4 * (j + 1) + k) = -T(k);
        }
    }

    if (!std::isnan(psi_s)) {
        M.row(4 * no_splines - 2).setZero();
        M(4 * no_splines - 2, 1) = 1;
        b_x(4 * no_splines - 2) = cos(psi_s);
        b_y(4 * no_splines - 2) = sin(psi_s);
    }

    if (!std::isnan(psi_e)) {
        double d = ds(no_splines - 1);
        M.row(4 * no_splines - 1).setZero();
        M(4 * no_splines - 1, 4 * (no_splines - 1) + 1) = 1;
        M(4 * no_splines - 1, 4 * (no_splines - 1) + 2) = 2 * d;
        M(4 * no_splines - 1, 4 * (no_splines - 1) + 3) = 3 * pow(d, 2);
        b_x(4 * no_splines - 1) = cos(psi_e);
        b_y(4 * no_splines - 1) = sin(psi_e);
    }

    VectorXd x_les = M.colPivHouseholderQr().solve(b_x);
    VectorXd y_les = M.colPivHouseholderQr().solve(b_y);

    MatrixXd coeffs_x = Map<MatrixXd>(x_les.data(), 4, no_splines).transpose();
    MatrixXd coeffs_y = Map<MatrixXd>(y_les.data(), 4, no_splines).transpose();

    MatrixXd normvec(no_splines, 2);
    for (int i = 0; i < no_splines; ++i) {
        double dx = coeffs_x(i, 1);
        double dy = coeffs_y(i, 1);
        normvec(i, 0) = -dy;
        normvec(i, 1) = dx;
    }

    VectorXd norms = normvec.rowwise().norm();
    MatrixXd normvec_normalized(no_splines, 2);
    for (int i = 0; i < no_splines; ++i) {
        normvec_normalized.row(i) = normvec.row(i) / norms(i);
    }

    return {coeffs_x, coeffs_y, M, normvec_normalized};
}

int main() {
    MatrixXd path(4, 2);
    path << 0, 0,
            1, 2,
            3, 3,
            4, 0;

    SplineResult result = calcSplines(path);

    cout << "Coefficients X:\n" << result.coeffs_x << endl;
    cout << "Coefficients Y:\n" << result.coeffs_y << endl;
    cout << "Normalized Normals:\n" << result.normvec_normalized << endl;

    return 0;
}
