#include "generator_utils"
#include "graph_utils"

#include <iostream>
#include <iomanip>
using namespace std;

typedef long long int64;
typedef __int128_t int128;
typedef double float64;
typedef long double float128;

int main() {
    srand(time(NULL));
    rand();
    rand();
    auto x = RandLog<int64>(1e1, 1e18);
    cout << fixed << setprecision(5) << x << '\n';
    return 0;
}