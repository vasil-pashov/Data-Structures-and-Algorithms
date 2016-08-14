#include<iostream>
#include <array>
	
using namespace std;

template <typename T>
void insertion_sort(T A[], size_t size) {
    for(size_t j = 1; j < size; j++) {
        T key = A[j];
        size_t i = j - 1;
        while(i>=0 && A[i] > key) {
            A[i+1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
}


template <typename T>
void insertion_sort_dec(T A[], size_t size) {
    for(int j = size - 2; j >= 0; j--) {
        T key = A[j];
        size_t i = j + 1;
        while(i < size && A[i] > key) {
            A[i-1] = A[i];
            i++;
        }
        A[i-1] = key;
    }
}

int main(int, char**) {
    int a[] = {5,2,4,6,1,3};
    insertion_sort(a, 6);
    for(int i = 0; i < 6; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    //int b[] = {31, 41, 59, 26, 41, 58};
    insertion_sort_dec(a, 6);
    for(int i = 0; i < 6; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
	return 0;
}
