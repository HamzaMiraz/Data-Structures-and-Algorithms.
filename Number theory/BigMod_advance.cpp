#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll mul(ll a, ll b, ll mod) { // a * b % mod
  return __int128(a) * b % mod;
}

ll power(ll a, ll b, ll mod) { // a^b % mod
  ll ans = 1 % mod;
  while (b) {
    if (b & 1) ans = mul(ans, a, mod);
    a = mul(a, a, mod);
    b >>= 1;
  }
  return ans;
}

ll inverse(ll a, ll mod) { // (1 / a) % mod
  return power(a, mod - 2, mod);
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll a, b, mod; cin >> a >> b >> mod;
  cout << power(a, b, mod) << '\n';//(a^b)%p
  cout << mul(a, b, mod) << '\n';//(a×b)%p
  cout << mul(a, inverse(b, mod), mod) << '\n';//(a/b)%p
  return 0;
}



