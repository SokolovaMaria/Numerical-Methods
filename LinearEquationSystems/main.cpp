#include <iostream>
#include "slae_solver.h"
#include "matrix_generator.h"

using namespace std;

void print_result(result res) {
    for (size_t i = 0; i < MATRIX_SIZE; i++) {
        for (size_t j = 0; j < MATRIX_SIZE + 1; j++) {
            cout << res.system.coeffs[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Amount of solutions: " << res.amount_of_solutions << endl;
    if (res.amount_of_solutions == 1) {
        for (size_t j = 0; j < MATRIX_SIZE; j++) {
            cout << res.solution[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    generate_files_with_matrices();

    cout << "Enter name of method to solve SLAE (Gauss | Seidel | Jacobi | descent | seqRelaxations ):\n";
    string method;
    cin >> method;

    vector<result> results = solveSystems(method);
    for (result res : results) {
        print_result(res);
    }

    return 0;
}