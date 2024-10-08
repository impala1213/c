#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int U = 1 << 1;
const int R = 1 << 0;
const int D = 1 << 3;
const int L = 1 << 2;

int dr[] = {0, -1, 0, 1};
int dc[] = {1, 0, -1, 0};

struct P {
    int r, c;
};

bool check(int n, int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    queue<P> q;
    q.push({0, 0});

    vector<vector<int>> v(n, vector<int>(n, 0));
    v[0][0] = 1;

    vector<vector<P>> p(n, vector<P>(n, {-1, -1}));
    p[0][0] = {0, 0};

    while (!q.empty()) {
        P cur = q.front();
        q.pop();

        int curDir = a[cur.r][cur.c];

        for (int i = 0; i < 4; ++i) {
            if (curDir & (1 << i)) {
                int newR = cur.r + dr[i];
                int newC = cur.c + dc[i];

                if (check(n, newR, newC) && !v[newR][newC]) {
                    v[newR][newC] = 1;
                    p[newR][newC] = cur;
                    q.push({newR, newC});
                }
            }
        }
    }

    vector<P> path;
    P end = {n - 1, n - 1};

    if (v[end.r][end.c]) {
        while (!(end.r == 0 && end.c == 0)) {
            path.push_back(end);
            end = p[end.r][end.c];
        }
        path.push_back({0, 0});

        cout << path.size() << endl;
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << it->r + 1 << " " << it->c + 1 << endl;
        }
    } else {
        cout << 0 << endl;
    }

    return 0;
}
