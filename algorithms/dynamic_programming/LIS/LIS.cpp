#include <iostream>
#include <vector>

using namespace std;

void print_all(int dyn[], int A[], int size, int pos, vector<int> items) {
    if(size == 1) {
        for(auto i : items) cout<<i<<" ";
        cout<<endl;
        return;
    }
    for(int i = pos - 1; i >= 0; --i) {
        if(dyn[i] == size - 1 && A[i] < A[pos]) {
            items.push_back(A[i]);
            print_all(dyn, A, size - 1, i, items);
            items.pop_back();
        }
    }
}

int main() {
    //first element does not matter, just to start indexing from 1, in order to like in the notes
    int A[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15},
        dyn[16], n = 16;
    for(int i = 0; i < n; ++i) dyn[i] = 1;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < i; ++j) {
            if(A[i] > A[j] && dyn[j] + 1 > dyn[i]) {
                dyn[i] = dyn[j] + 1;
            }
        }
    }
    int max_pos = 0;
    for(int i = 0; i < n; ++i)  {
        cout<<dyn[i]<<" ";
        max_pos = dyn[max_pos] > dyn[i] ? max_pos : i;
    }
    cout<<endl;
    vector<int> items;
    items.push_back(A[max_pos]);
    print_all(dyn, A, dyn[max_pos], max_pos, items);
    cout<<endl;
    return 0;
}
