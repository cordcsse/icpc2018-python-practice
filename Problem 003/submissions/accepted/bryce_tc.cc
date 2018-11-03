#include <iostream>
#include <vector>
#include <unordered_map>

#define MAXN 500

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;

unordered_map<string, ll> cls_to_idx;

ll get_idx(string cls) {
    if (!cls_to_idx.count(cls)) {
        ll size = cls_to_idx.size();
        cls_to_idx[cls] = size;
    }

    return cls_to_idx[cls];
}

int main() {
    ll n, m;
    cin >> n >> m;

    vvb is_a(MAXN, vb(MAXN, false));
    vvb has_a(MAXN, vb(MAXN, false));

    for (ll i = 0; i < MAXN; ++i)
        is_a[i][i] = true;

    for (ll i = 0; i < n; ++i) {
        string c1, r, c2;
        cin >> c1 >> r >> c2;

        ll id1 = get_idx(c1);
        ll id2 = get_idx(c2);

        if (r == "is-a") {
            is_a[id1][id2] = true;
        }
        else
            has_a[id1][id2] = true;
    }

    // modified floyd-warshall
    for (ll k = 0; k < MAXN; ++k) {
        for (ll i = 0; i < MAXN; ++i) {
            for (ll j = 0; j < MAXN; ++j) {
                is_a[i][j] = is_a[i][j] || (is_a[i][k] && is_a[k][j]);
                has_a[i][j] = has_a[i][j] || (has_a[i][k] && has_a[k][j]);

                has_a[i][j] = has_a[i][j] || (is_a[i][k] && has_a[k][j]);
                has_a[i][j] = has_a[i][j] || (has_a[i][k] && is_a[k][j]);
            }
        }
    }

    for (ll i = 0; i < m; ++i) {
        string c1, r, c2;
        cin >> c1 >> r >> c2;

        ll id1 = get_idx(c1);
        ll id2 = get_idx(c2);

        bool success = false;
        if (r == "is-a") {
            success = is_a[id1][id2];
        }
        else {
            success = has_a[id1][id2];
        }

        if (success)
            cout << "Query " << i+1 << ": true" << endl;
        else
            cout << "Query " << i+1 << ": false" << endl;
    }
}
