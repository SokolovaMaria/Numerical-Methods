#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "slae_solver.h"

void matrix::init_with_file(std::string path) {
    std::ifstream in(path);
    this->coeffs.resize(MATRIX_SIZE);
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        this->coeffs[i].resize(MATRIX_SIZE + 1);
        for (size_t j = 0; j < MATRIX_SIZE; j++) {
            double a;
            in >> a;
            this->coeffs[i][j] = a;
        }
    }

    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        double b;
        in >> b;
        this->coeffs[i][MATRIX_SIZE] = b;
    }
}

static std::unordered_map<std::string, method_t*> reflection (
        {    {"Gauss", &Gauss},
            /* {"Jacobi", &Jacobi},*/
             /*{"Seidel", &Seidel},*/
            /* {"descent", &descent},*/
             /*{"seqRelaxations", &sequentialRelaxation}*/
        }
);

vector<result> solveSystems(const std::string method) {
    if (!reflection.count(method)) {
        std::cerr << "No such method\n";
    }
    method_t* m = reflection[method];

    matrix good_system("good");
    matrix random_system("random");
    matrix gilbert_system("Gilbert");

    vector<result> results;
    results.push_back(m(good_system));
    results.push_back(m(random_system));
    results.push_back(m(gilbert_system));
    return results;
}
