int minPathSum(int** grid, int gridSize, int* gridColSize){
    int m = gridSize;
    int n = gridColSize[0];

    int f[m][n];
    f[0][0] = grid[0][0];
    for (int i = 1; i < m; ++i) {
        f[i][0] = f[i-1][0] + grid[i][0];
    }
    for (int j = 1; j < n; ++j) {
        f[0][j] = f[0][j-1] + grid[0][j];
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            f[i][j] = f[i-1][j] > f[i][j-1] ? f[i-1][j] : f[i][j-1];
            f[i][j] += grid[i][j];
        }
    }
    return f[m - 1][n - 1];
}
