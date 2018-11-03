#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<ll> vi;
typedef vector<vi> vvi;

int main() {
    ll n;
    cin >> n;
    vii store(n);

    for (ll i = 0; i < n; ++i) {
        cin >> store[i].second >> store[i].first;
    }

    sort(store.begin(), store.end());
    vi t(n), h(n);
    for (ll i = 0; i < n; ++i) {
        t[i] = store[i].second;
        h[i] = store[i].first;
    }

    vvi DP(n, vi(n+1, -1));

    for (ll i = 0; i < n; ++i) {
        DP[i][1] = h[i]-t[i];
    }

    ll ans = -1;
    for (ll j = 1; j <= n; ++j) {
        for (ll i = n-2; i >= 0; --i) {
            DP[i][j] = max(DP[i][j], max(DP[i+1][j], min(DP[i+1][j-1] - t[i], h[i]-t[i])));
            if (DP[i][j] >= 0)
                ans = max(ans, j);
        }
    }

    cout << ans << endl;
}
