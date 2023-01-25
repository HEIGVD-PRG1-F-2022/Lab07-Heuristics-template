//
// Created by Linus Gasser on 2023-01-09
//

#include "NumericVector.h"
#include "OnePerson.h"
#include "Solve.h"
#include "Tunnels.h"
#include "TwoPersons.h"
#include <cmath>
#include <iostream>

using namespace std;

int main() {
    testNumeric();
    test_tunnels();

    // For OnePlayer, the solutions are:
    // - 'sample-input.txt': 1651
    // - 'input.txt': 1940

    // For TwoPlayers, the solutions are:
    // - `sample-input.txt`: 1707
    // - `input.txt`: unknown :(

    Tunnels t("../input.txt");
    cout << t << endl;
        OnePerson input(t);
//    TwoPersons input(t);
    Solve solver_rnd(input);
    Solve solver_annealing(input);
        vector<Solve<OnePerson>> solvers;
//    vector<Solve<TwoPersons>> solvers;
    for (int i = 0; i < 10; i++) {
        solvers.emplace_back(input);
    }
    unsigned rounds = 50;
    for (unsigned i = 0; i < rounds; i++) {
        double mutate = pow(1 - i / (rounds - 1.), 10.);
        cout << "Round " << i;
        cout << " - random: " << solver_rnd.run_random(1000);
        cout << " - annealing: " << solver_annealing.run_annealing(1000, mutate);
        cout << " - genetics: ";
        unsigned random = 0;
        vector<unsigned> fitnesses;
        for (auto &solver: solvers) {
            auto latest = solver.run_genetic(1000, 10 * (random + 1), random, 0.01);
            cout << latest << " ";
            fitnesses.push_back(latest);
            ++random;
        }
        cout << endl;
        sort(fitnesses.begin(), fitnesses.end());
        cout << "Best is: " << fitnesses.back() << endl;
    }
    return 0;
}
