#include <iostream>
#include <cstdio>

using namespace std;


int partition(int arr[], int l, int r) {
    int pivot = arr[l], pos = l+1;
    for(int i = l + 1; i < r; ++i) {
        if(arr[i] < pivot) {
            swap(arr[pos], arr[i]);
            ++pos;
        }
    }
    swap(arr[l], arr[pos-1]);
    return pos - 1;
    
}

void quick_sort(int arr[], int l, int r, int n) {
    if(l >= r) return;
    int p = partition(arr, l, r);
    quick_sort(arr, l, p, n);
    quick_sort(arr, p + 1, r, n);
}

int main() {
    return 0;
}
