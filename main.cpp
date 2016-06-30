#include "generator_utils"
#include "graph_utils"

#include <iostream>
using namespace std;

int main() {
    vector<int> x({1, 2, 3, 4, 5});
//    cerr << rand() << '\n';
    RandomShuffle(x.begin(), x.end());

    for (auto itr : x) {
        cerr << itr << '\n';
    }
    cerr << rand() << '\n';
    return 0;
}