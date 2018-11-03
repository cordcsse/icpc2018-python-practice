#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

#define INF 1000000000000000000LL

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

#define MAXN 200010 // the maximum input length of the sequnece, good idea to add 10 or so to this

typedef signed long long int T; // the type of the underlying sequence

struct SegmentNode {
    // segment data
    T minVal;
    T sumVal;

    // update data
    T updateVal;
};

SegmentNode st[MAXN*4];
T width[MAXN];
T gap[MAXN];

size_t left(size_t cur) { return cur << 1; }
size_t right(size_t cur) { return (cur << 1) + 1; }

// create merging function here
void merge(SegmentNode &left, SegmentNode &right, SegmentNode &result) {
    result.minVal = min(left.minVal, right.minVal);
    result.sumVal = left.sumVal + right.sumVal;
}

// only use if range update is needed
void updateChildren(size_t cur, size_t L, size_t R);

// merge handles all querying, no changes needed here
// note that when calling any segment funcitons in main,
// the first three parameters will be 1, 0, length-1
SegmentNode query(size_t cur, size_t L, size_t R, size_t LQ, size_t RQ) {
    if (L >= LQ && R <= RQ)
        return st[cur];

    updateChildren(cur, L, R);
    size_t M = (L+R)/2;

    if (M < LQ)
        return query(right(cur), M+1, R, LQ, RQ);

    if (M+1 > RQ)
        return query(left(cur), L, M, LQ, RQ);

    SegmentNode leftResult = query(left(cur), L, M, LQ, RQ);
    SegmentNode rightResult = query(right(cur), M+1, R, LQ, RQ);
    SegmentNode result;

    merge(leftResult, rightResult, result);

    return result;
}

// only implement if necessary
void update(size_t cur, size_t L, size_t R, size_t idx, T curGap, T curWidth) {
    if (L == idx && R == idx) {
        // write update of single value here
        st[cur].minVal = curGap;
        st[cur].sumVal = curWidth;
    }
    else if (L <= idx && R >= idx) {
        size_t M = (L+R)/2;
        update(left(cur), L, M, idx, curGap, curWidth);
        update(right(cur), M+1, R, idx, curGap, curWidth);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

// only implement if necessary
void rangeUpdate(size_t cur, size_t L, size_t R, size_t Lbound, size_t Rbound, T val) {
    if (L >= Lbound && R <= Rbound) {
        // implement range update here
        st[cur].minVal += val;

        // set update vals here
        st[cur].updateVal += val;
    }
    else if (L <= Rbound && R >= Lbound) {
        updateChildren(cur, L, R);

        size_t M = (L+R)/2;
        rangeUpdate(left(cur), L, M, Lbound, Rbound, val);
        rangeUpdate(right(cur), M+1, R, Lbound, Rbound, val);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

void updateChildren(size_t cur, size_t L, size_t R) {
    rangeUpdate(left(cur), L, R, L, R, st[cur].updateVal);
    rangeUpdate(right(cur), L, R, L, R, st[cur].updateVal);

    // reset update vals
    st[cur].updateVal = 0;
}

void build(size_t cur, size_t L, size_t R) {
    // initialize update vals
    st[cur].updateVal = 0;
    
    if (L == R) {
        // initialize single valiue here
        st[cur].minVal = gap[L];
        st[cur].sumVal = width[L];
    }
    else {
        size_t M = (L+R)/2;
        build(left(cur), L, M);
        build(right(cur), M+1, R);

        merge(st[left(cur)], st[right(cur)], st[cur]);
    }
}

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

    for (ll i = 0; i < MAXN; ++i) {
        width[i] = 0;
        gap[i] = INF;
    }
    build(1, 0, n-1);

    vii taken;

    for (ll i = 0; i < n; ++i) {
        ll cur_t = t_sorted[i].first;
        ll cur_h = h[t_sorted[i].second];
        ll place = i_to_h_idx[t_sorted[i].second];

        ll sum_before = query(1, 0, n-1, 0, place).sumVal + cur_t;
        ll cur_gap = cur_h - sum_before;

        if (cur_gap >= 0) {
            if (query(1, 0, n-1, place, n-1).minVal >= cur_t) {
            //    cerr << "adding t_i=" << cur_t << " h_i=" << cur_h << " at place:" << place << endl;
                
                taken.push_back(ii(cur_h, cur_t));
                update(1, 0, n-1, place, cur_gap, cur_t);
                rangeUpdate(1, 0, n-1, place+1, n-1, -cur_t);
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

    cout << taken.size() << endl;
}
