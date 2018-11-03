#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll n;
    cin >> n;

    if (n < 1 || n > 200000) {
        cerr << "n out of bounds" << endl;
        return 1;
    }

    for (ll i = 0; i < n; ++i) {
        ll t_i, h_i;
        cin >> t_i >> h_i;

        if (t_i < 1 || t_i > 1000000000 || h_i < 1 || h_i > 1000000000) {
            cerr << "height or times out of bounds" << endl;
            return 2;
        }
    }

    ll blah1, blah2;
    if (cin >> blah1 >> blah2) {
        cerr << "input too long" << endl;
        return 3;
    }

    return 42;
}
