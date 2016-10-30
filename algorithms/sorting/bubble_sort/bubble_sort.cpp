#include <iostream>

template<typename T>
bool def_cmp(T &a, T &b) {
    return a < b;
}

template<typename T>
void bubble_sort(T arr[], int n, bool (&cmp)(T &a, T &b) = def_cmp) {
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < n; ++j) {
            if(cmp(arr[j], arr[j -1])) {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

int main() {
    return 0;
}
