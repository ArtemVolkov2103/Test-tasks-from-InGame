#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> image;
vector<vector<bool>> visited;

void dfs(int i, int j) {
    visited[i][j] = true;
    if (i > 0 && !visited[i - 1][j] && image[i - 1][j] == image[i][j]) dfs(i - 1, j);
    if (i < n - 1 && !visited[i + 1][j] && image[i + 1][j] == image[i][j]) dfs(i + 1, j);
    if (j > 0 && !visited[i][j - 1] && image[i][j - 1] == image[i][j]) dfs(i, j - 1);
    if (j < m - 1 && !visited[i][j + 1] && image[i][j + 1] == image[i][j]) dfs(i, j + 1);
}

int main() {
    cin >> n >> m;
    image.resize(n, vector<int>(m));
    visited.resize(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> image[i][j];
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && image[i][j] == 1) {
                count++;
                dfs(i, j);
            }
        }
    }

    cout << count << endl;
    return 0;
}