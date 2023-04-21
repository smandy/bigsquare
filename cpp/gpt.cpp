#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Example input 2D array
    vector<vector<int>> arr = {
        {1, 0, 1, 1, 1},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    int n = arr.size();
    int m = arr[0].size();
    
    // Define a 2D array for dynamic programming
    vector<vector<int>> dp(n, vector<int>(m));
    
    // Initialize the first row and column
    for (int i = 0; i < n; i++) {
        dp[i][0] = arr[i][0];
    }
    for (int j = 0; j < m; j++) {
        dp[0][j] = arr[0][j];
    }
    
    // Fill in the rest of the dynamic programming table
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (arr[i][j] == 0) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
            }
        }
    }
    
    // Find the largest square
    int max_size = 0;
    int max_i = 0;
    int max_j = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dp[i][j] > max_size) {
                max_size = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    
    // Print the result
    cout << "Largest square is located at (" << max_i - max_size + 1 << ", " << max_j - max_size + 1 << ")" << endl;
    cout << "with size " << max_size << endl;
    
    return 0;
}
