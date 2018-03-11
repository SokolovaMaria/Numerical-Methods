#include <cmath>
#include "slae_solver.h"

result Gauss(const matrix& system) {
    std::vector<std::vector<double>> a = system.coeffs;
    vector<double> ans;


    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i) {
            if (std::fabs (a[i][col]) > std::fabs (a[sel][col]))
                sel = i;
        }
        if (abs (a[sel][col]) < EPS) {
            continue;
        }
        for (int i=col; i<=m; ++i) {
            swap (a[sel][i], a[row][i]);
        }
        where[col] = row;

        for (int i=0; i<n; ++i) {
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i) {
        if (where[i] != -1) {
            ans[i] = a[where[i]][m] / a[where[i]][i];
        }
    }

    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j) {
            sum += ans[j] * a[i][j];
        }
        if (abs (sum - a[i][m]) > EPS)
            return result(system, ans, 0);
    }

    for (int i=0; i<m; ++i) {
        if (where[i] == -1)
            return result(system, ans, INF);
    }
    return result(system, ans, 1);
}

