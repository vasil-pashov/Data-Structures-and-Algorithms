#include <iostream>

template<typename T>
bool def_cmp(T &a, T &b) {
    return a < b;
}

template<typename T>
void selection_sort(T arr[], int n,
        bool (&cmp)(T &a, T &b) = def_cmp) {
    for(int i = 0; i < n - 1; ++i) {
        int max_index = i;
        for(int j = i + 1; j < n; ++j) {
            if(cmp(arr[j], arr[max_index])) {
                max_index = j;
            }
        }
        std::swap(arr[max_index], arr[i]);
    }
}

int main() {
    int a[] = {1,5,-24,12,0,-43};
    selection_sort<int>(a, 6);
    for(int i = 0; i < 6; ++i) std::cout<<a[i]<<" ";
    return 0;
}
