#include <iostream>
#include <array>

using namespace std;

template<size_t m, size_t n>
int compute_paths(bool cells[m][n]) {
    //computes all posible paths from the top left corner to the bottom right corner
    //allowed directions: down, right
    //cells[i][j] == false means cell is unreachable

    int dyn[m][n]; //dyn[i][j] - the number of possible ways to get to cell m-1, n-1 from cell i, j
    dyn[m-1][n-1] = 1;

    //if we have only the last column
    for(int i = m - 2; i >= 0 ; --i) {
        if(cells[i][n-1]) {
            dyn[i][n-1] = dyn[i+1][n-1];
        } else {
            //we cant step on cell i, n-1 -> 0 ways to get from i, n-1 to m-1, n-1
            dyn[i][n-1] = 0;
        }
    }

    for(int i = n - 2; i >= 0; --i) {
        if(cells[m-1][i]) {
            dyn[m-1][i] = dyn[m-1][i+1];
        } else {
            dyn[m-1][i] = 0;
        }
    }

    for(int i = m - 2; i >= 0; --i) {
        for(int j = n - 2; j >= 0; --j) {
            if(cells[i][j]) {
                dyn[i][j] = dyn[i+1][j] + dyn[i][j+1];
            } else {
                dyn[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cout<<dyn[i][j]<<" ";
        }
        cout<<endl;
    }
    return dyn[0][0];
}

int main() {
    bool cells[][4] = {
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 1, 1},
        {1, 0, 1, 1}
    };
    compute_paths<6,4>(cells);
    return 0;
}
