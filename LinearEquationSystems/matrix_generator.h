#include <random>
#include <fstream>
#include <functional>
#include "slae_solver.h"

using namespace std;

const double N = 100;

std::random_device rd;
std::mt19937 gen(rd());

void generate(string matrix_type, std::function<double(int, int, double)> &&gen_coeff) {
    std::ofstream fout(matrix_type);

    std::uniform_int_distribution<> dis(1, N);
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        for (size_t j = 0; j < MATRIX_SIZE; j++) {
            fout << gen_coeff(i, j, dis(gen)) << " ";
        }
        fout << endl;
    }
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        fout << dis(gen) << endl;
    }
    fout.close();
}

void generate_files_with_matrices() {
    generate("good",
             [](int i, int j, double coeff) { return (i == j) ? 1000.0 + coeff : coeff;});
    generate("random",
             [](int i, int j, double coeff) {return coeff;});
    generate("Gilbert",
             [](int i, int j, double coeff) {return static_cast<double>(1. / (1 + i + j));});
}

