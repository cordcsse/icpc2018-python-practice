#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

struct cls {
    unordered_set<cls*> is_a;
    unordered_set<cls*> has_a;

    bool query_is_a(cls* query, unordered_set<cls*> &seen) {
        if (is_a.count(query))
            return true;

        seen.insert(this);
        for (auto it = is_a.begin(); it != is_a.end(); ++it) {
            if (seen.count(*it)) continue;
            
            if ((*it)->query_is_a(query, seen))
                return true;
        }

        return false;
    }

    bool query_has_a(cls* query, unordered_set<cls*> &seen_is_a, unordered_set<cls*> &seen_has_a) {
        if (has_a.count(query))
            return true;

        seen_has_a.insert(this);
        for (auto it = is_a.begin(); it != is_a.end(); ++it) {
            if (!seen_has_a.count(*it)) {
                if ((*it)->query_has_a(query, seen_is_a, seen_has_a))
                    return true;
            }
        }

        for (auto it = has_a.begin(); it != has_a.end(); ++it) {
            if (!seen_has_a.count(*it)) {
                if ((*it)->query_has_a(query, seen_is_a, seen_has_a))
                    return true;
            }

            if (!seen_is_a.count(*it)) {
                if ((*it)->query_is_a(query, seen_is_a))
                    return true;
            }
        }

        return false;
    }
};

unordered_map<string, cls*> string_to_cls;

cls* get_class(string cls_str) {
    if (!string_to_cls.count(cls_str)) {
        string_to_cls[cls_str] = new cls();
        string_to_cls[cls_str]->is_a.insert(string_to_cls[cls_str]);
    }

    return string_to_cls[cls_str];
}

int main() {
    ll n, m;
    cin >> n >> m;

    for (ll i = 0; i < n; ++i) {
        string c_1, r, c_2;
        cin >> c_1 >> r >> c_2;

        cls* c_1_cls = get_class(c_1);
        cls* c_2_cls = get_class(c_2);

        if (r == "is-a") {
            c_1_cls->is_a.insert(c_2_cls);
        }
        else {
            c_1_cls->has_a.insert(c_2_cls);
        }
    }

    for (ll i = 0; i < m; ++i) {
        string c_1, r, c_2;
        cin >> c_1 >> r >> c_2;

        cls* c_1_cls = get_class(c_1);
        cls* c_2_cls = get_class(c_2);

        bool success;
        unordered_set<cls*> seen, seen2;
        if (r == "is-a") {
            success = c_1_cls->query_is_a(c_2_cls, seen);
        }
        else {
            success = c_1_cls->query_has_a(c_2_cls, seen, seen2);
        }

        if (success)
            cout << "Query " << i+1 << ": true" << endl;
        else
            cout << "Query " << i+1 << ": false" << endl;
    }
}
