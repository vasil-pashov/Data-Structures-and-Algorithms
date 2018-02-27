#include <iostream>

using namespace std;

int main() {
    //first element does not matter, just to start indexing from 1, in order to like in the notes
    int A[] = {100000, 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15},
        dyn[17], n = 16;
    dyn[0] = 0;
    for(int k = 1; k <= n; ++k) {
        int i = k - 1;
        while(i >= 1 && A[i] > A[k]) {
            --i;
        }
        dyn[k] = max(dyn[k-1], dyn[i] + 1);
    }
    for(int i = 0; i <= n; ++i) cout<<dyn[i]<<" ";
    cout<<endl;
    return 0;
}
