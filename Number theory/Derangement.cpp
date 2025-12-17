#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5; 

ll der[MAXN];

/**
 * Precalculate Derangements up to MAXN
 * Base cases:
 * D[0] = 1 (Empty set has 1 derangement)
 * D[1] = 0 (1 item cannot be misplaced)
 * D[2] = 1 (2,1 is the only derangement)
 */
void precalculate_derangements() {
    der[0] = 1;
    der[1] = 0;
    der[2] = 1;
    
    for (int i = 3; i < MAXN; i++) {
        der[i] = (i - 1) * (der[i - 1] + der[i - 2]) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precalculate_derangements();

    int n;
    while (cin >> n) {
        if (n < 0 || n >= MAXN) break;
        cout << "!n = " << der[n] << endl;
    }

    return 0;
}