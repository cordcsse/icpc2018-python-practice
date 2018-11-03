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

struct range_agg {
    vi t;
    vi gap;
    vi sum_agg;
    vi min_agg;
    vi min_up;
    ll n;
    ll k;
    ll size = 0;

    range_agg(ll k) : n(k*k), k(k) {
        t = vi(n, 0);
        gap = vi(n, INF);
        sum_agg = vi(k, 0);
        min_agg = vi(k, INF);
        min_up = vi(k, 0);
    }

    void push_updates(ll idx) {
        // push pending updates
        if (min_up[idx/k] != 0) {
            for (ll i = (idx/k)*k; i < (idx/k+1)*k; ++i) {
                gap[i] += min_up[idx/k];
            }
            min_up[idx/k] = 0;
        }

    }

    void add(ll idx, ll t_i, ll gap_i) {
        push_updates(idx);

        // update index and aggregates
        ++size;
        t[idx] = t_i;
        gap[idx] = gap_i;
        sum_agg[idx/k] += t_i;
        min_agg[idx/k] = min(min_agg[idx/k], gap_i);
    }

    void suffix_update(ll start, ll gap_i) {
        push_updates(start);
        
        // update gap[i] and aggregate from start to multiple of k
        for (ll i = start; i < (start/k+1)*k; ++i) {
            gap[i] += gap_i;
            // this last part only works because gap_i will always be negative
            min_agg[start/k] = min(min_agg[start/k], gap[i]);
        }

        // update aggregates beyond this point and child update status
        for (ll i = start/k+1; i < k; ++i) {
            min_up[i] += gap_i;
            min_agg[i] += gap_i;
        }
    }

    // returns sum from 0 to idx, inclusive
    ll prefix_sum(ll idx) {
        ll sum = 0;
        for (ll i = 0; i < idx/k; ++i) {
            sum += sum_agg[i];
        }

        for (ll i = (idx/k)*k; i <= idx; ++i) {
            sum += t[i];
        }
        return sum;
    }

    // returns min from idx to end, inclusive
    ll suffix_min(ll idx) {
        push_updates(idx);

        ll ans = INF;
        for (ll i = idx; i < (idx/k+1)*k; ++i) {
            ans = min(ans, gap[i]);
        }
        
        for (ll i = idx/k+1; i < k; ++i) {
            ans = min(ans, min_agg[i]);
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

    range_agg ra(448);

    vii taken;

    for (ll i = 0; i < n; ++i) {
        ll cur_t = t_sorted[i].first;
        ll cur_h = h[t_sorted[i].second];
        ll place = i_to_h_idx[t_sorted[i].second];

        ll sum_before = ra.prefix_sum(place) + cur_t;
        ll gap = cur_h - sum_before;

        if (gap >= 0) {
            if (ra.suffix_min(place) >= cur_t) {
            //    cerr << "adding t_i=" << cur_t << " h_i=" << cur_h << " at place:" << place << endl;
                
                taken.push_back(ii(cur_h, cur_t));
                ra.add(place, cur_t, gap);
                ra.suffix_update(place+1, -cur_t);
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

    cout << ra.size << endl;
}
