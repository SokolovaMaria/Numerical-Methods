#ifndef LINEAREQUATIONSYSTEMS_SLAE_SOLVER_H
#define LINEAREQUATIONSYSTEMS_SLAE_SOLVER_H

#include <vector>
#include <string>

using namespace std;

const double EPS = 0.00000001;
const int64_t INF = INT64_MAX;
const size_t MATRIX_SIZE = 10;

struct matrix {

    std::vector<std::vector<double>> coeffs;


    explicit matrix(const std::string& file) {
        init_with_file(file);
    }

    double cond();

    double determinant();

    double norm();

    matrix transpose(const matrix &);

private:
    void init_with_file(std::string path);
};

struct result {
    result(const matrix& s, std::vector<double> x, size_t amount) :
        system(s), amount_of_solutions(amount)
    {
        solution = std::move(x);
    }
    const matrix system;
    std::vector<double> solution;
    int amount_of_solutions;
};

using method_t = result (const matrix&);

vector<result> solveSystems(string method);

result Gauss(const matrix &system);

result Jacobi(const matrix &system);

result Seidel(const matrix &system);

result descent(const matrix &system);

result sequentialRelaxation(const matrix &system);


#endif //LINEAREQUATIONSYSTEMS_SLAE_SOLVER_H
