#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
	
using namespace std;
const int SENTINEL = INT_MAX;

template <typename T>
void print(T A[], int size) {
    for(int i = 0; i < size; i++) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

template <typename T>
void copy(T src[], T dest[], int left, int size) {
    for(int i = 0; i < size; i++) {
        dest[i] = src[left + i];
    }
}

template <typename T>
void merge_sentinel(T A[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    T L[n1+1], R[n2+1];
    copy(A, L, left, n1);
    L[n1] = SENTINEL;
    copy(A, R, mid + 1, n2);
    R[n2] = SENTINEL;
    int i = 0, j = 0;
    for(int k = left; k <= right; k++) {
        if(L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}


template <typename T>
void merge(T A[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    T L[n1], R[n2];
    copy(A, L, left, n1);
    copy(A, R, mid + 1, n2);
    int i = 0, j = 0, k = left;
    for(;k <= right; k++) {
        if(i < n1 && L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        if(i == n1 || j == n2) break;
    }
    while(i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
    while(j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void merge_sort(T A[], int left, int right) {
    if(left < right) {
        int mid = (left + right)/2;
        merge_sort(A, left, mid);
        merge_sort(A, mid + 1, right);
        merge_sentinel(A, left, mid, right);
    }
}

int main(int, char **) {
    srand(time(NULL));
    int size = 101;
    int a[size];
    for(int i = 0; i < size; i++) {
        a[i] = rand() % 50;
        cout<<a[i]<<" ";
    }
    cout<<endl;
    merge_sort(a, 0, size - 1);
    print(a, size);
	return 0;
}
