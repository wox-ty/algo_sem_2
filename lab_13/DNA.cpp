#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

map<char, int> zoom;

int n;
int t[MAXN][11][10][4];

void upd(int i, int j, int k, int c, int val) {
    for(; i <= n; i |= (i + 1)) {
        t[i][j][k][c] += val;
    }
}

int get(int r, int j, int k, int c) {
    int total = 0;
    for(; r >= 0; r = (r & (r + 1)) - 1) {
        total += t[r][j][k][c];
    }
    return total;
}

void update(int pos, int c, int val) {
    for(int i = 1; i <= 10; i++) {
        upd(pos, i, pos % i, c, val);
    }
}

int getAtRange(int l, int r, int j, int k, int c) {
    return get(r, j, k, c) - get(l - 1, j, k, c);
}

string s;

int get(int l, int r, string e) {
    int total = 0;
    for(int i = 0; i < e.size(); i++) {
        total += getAtRange(l, r, e.size(), (l + i) % e.size(), zoom[e[i]]);
    }

    return total;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    zoom['A'] = 0;
    zoom['G'] = 1;
    zoom['C'] = 2;
    zoom['T'] = 3;

    cin >> s;
    n = s.size();
    s = "*" + s;
    for(int i = 1; i <= n; i++){
        update(i, zoom[s[i]], 1);
    }

    int m;
    cin >> m;
    while(m--) {
        int type;
        cin >> type;
        if(type == 1) {
            int pos; char c;
            cin >> pos >> c;
            update(pos, zoom[s[pos]], -1);
            s[pos] = c;
            update(pos, zoom[s[pos]], 1);
        }
        else {
            int l, r;
            string e;
            cin >> l >> r >> e;
            cout << get(l, r, e) << "\n";
        }
    }
}