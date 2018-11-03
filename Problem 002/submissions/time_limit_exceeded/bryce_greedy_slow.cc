#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

struct dumb_range_agg {
    vi t;
    vi gap;
    ll n;
    ll size = 0;

    dumb_range_agg(ll n) : n(n) {
        t = vi(n, 0);
        gap = vi(n, INF);
    }

    void add(ll idx, ll t_i, ll gap_i) {
        t[idx] = t_i;
        gap[idx] = gap_i;
        ++size;
    }

    void suffix_update(ll start, ll gap_i) {
        for (ll i = start; i < n; ++i) {
            gap[i] += gap_i;
        }
    }

    ll prefix_sum(ll idx) {
        ll sum = 0;
        for (ll i = 0; i < idx; ++i) {
            sum += t[i];
        }
        return sum;
    }

    ll suffix_min(ll idx) {
        ll ans = INF;
        for (ll i = idx; i < n; ++i) {
            ans = min(ans, gap[i]);
        }
        return ans;
    }
};

int main() {
    ll n;
    cin >> n;
    
    vi t(n), h(n);
    vii t_sorted(n), h_sorted(n);

    for (ll i = 0; i < n; ++i) {
        cin >> t[i] >> h[i];
        t_sorted[i] = ii(t[i], i);
        h_sorted[i] = ii(h[i], i);
    }

    sort(t_sorted.begin(), t_sorted.end());
    sort(h_sorted.begin(), h_sorted.end());

    vi i_to_h_idx(n);
    for (ll i = 0; i < n; ++i) {
        i_to_h_idx[h_sorted[i].second] = i;
    }

    dumb_range_agg dra(n);

    vii taken;

    for (ll i = 0; i < n; ++i) {
        ll cur_t = t_sorted[i].first;
        ll cur_h = h[t_sorted[i].second];
        ll place = i_to_h_idx[t_sorted[i].second];

        ll sum_before = dra.prefix_sum(place) + cur_t;
        ll gap = cur_h - sum_before;

        if (gap >= 0) {
            if (dra.suffix_min(place) >= cur_t) {
            //    cerr << "adding t_i=" << cur_t << " h_i=" << cur_h << " at place:" << place << endl;
                
                taken.push_back(ii(cur_h, cur_t));
                dra.add(place, cur_t, gap);
                dra.suffix_update(place+1, -cur_t);
            }
        }
    }

    sort(taken.begin(), taken.end());

    /*
    for (ll i = 0; i < taken.size(); ++i) {
        cerr << "t_i=" << taken[i].second << ", h_i=" << taken[i].first << endl;
    }*/

    ll sumbefore = 0;
    for (ll i = 0; i < taken.size(); ++i) {
        sumbefore += taken[i].second;
        if (sumbefore > taken[i].first) {
            cerr << "ERROR in AC solution at index " << i << ", t_i=" << taken[i].second << ", h_i=" << taken[i].first << endl;
        }
    }

    cout << dra.size << endl;
}
